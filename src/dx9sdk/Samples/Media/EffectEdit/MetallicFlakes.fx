//
// Metallic Flakes Shader
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Note: This effect file works with EffectEdit.
//
// NOTE:
// The metallic surface consists of 2 layers - 
// 1. a polished layer of wax on top (contributes a smooth specular reflection and an environment mapped reflection with a Fresnel term), and 
// 2. a blue metallic layer with a sprinkling of gold metallic flakes underneath


// sparkle parameters
#define SPRINKLE    0.3
#define SCATTER     0.3

#define VOLUME_NOISE_SCALE  10

// scene info (EffectEdit specific controls)
string XFile = "bigship1.x";
int    BCLR  = 0xff404080;

// textures
texture EnvironmentMap 
< 
    string type = "CUBE"; 
    string name = "lobbycube.dds"; 
>;

// procedural texture that contains a normal map used for the metal sparkles
texture NoiseMap 
< 
    string type = "VOLUME"; 
    string function = "GenerateSparkle"; 
    int width = 32;
    int height = 32;
    int depth = 32; 
>;

// transformations
float4x3 WorldView  : WORLDVIEW;
float4x4 Projection : PROJECTION;

// light direction (view space)
float3 L < string UIDirectional = "Light Direction"; > = normalize(float3(-0.397f, -0.397f, 0.827f));

// light intensity
float4 I_a = { 0.3f, 0.3f, 0.3f, 1.0f };    // ambient
float4 I_d = { 1.0f, 1.0f, 1.0f, 1.0f };    // diffuse
float4 I_s = { 0.7f, 0.7f, 0.7f, 1.0f };    // specular

// material reflectivity
float4 k_a : MATERIALAMBIENT = { 0.2f, 0.2f, 0.2f, 1.0f };    // ambient  (metal)
float4 k_d : MATERIALDIFFUSE = { 0.1f, 0.1f, 0.9f, 1.0f };    // diffuse  (metal)
float4 k_s = { 0.4f, 0.3f, 0.1f, 1.0f };    // specular (metal)
float4 k_r = { 0.7f, 0.7f, 0.7f, 1.0f };    // specular (wax)

// function used to fill the volume noise texture
float4 GenerateSparkle(float3 Pos : POSITION) : COLOR
{
    float4 Noise = (float4)0;

    // scatter the normal (in vertex space) based on SCATTER
    Noise.rgb = float3(1 - SCATTER * abs(noise(Pos * 500)), SCATTER * noise((Pos + 1) * 500), SCATTER * noise((Pos + 2) * 500));
    Noise.rgb = normalize(Noise.rgb);

    // set the normal to zero with a probability based on SPRINKLE
    if (SPRINKLE < abs(noise(Pos * 600)))
        Noise.rgb = 0;

    // bias the normal
    Noise.rgb = (Noise.rgb + 1)/2;

    // diffuse noise
    Noise.w = abs(noise(Pos * 500)) * 0.0 + 1.0;

    return Noise;
}

struct VS_OUTPUT
{
    float4 Position   : POSITION;
    float3 Diffuse    : COLOR0;
    float3 Specular   : COLOR1;               
    float3 Reflection : TEXCOORD0;               
    float3 NoiseCoord : TEXCOORD1;               
    float3 Glossiness : TEXCOORD2;               
    float3 HalfVector : TEXCOORD3;
};

// vertex shader
VS_OUTPUT VS(    
    float3 Position : POSITION,
    float3 Normal   : NORMAL, 
    float3 Tangent  : TANGENT)
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    L = -L;

    float3 P = mul(float4(Position, 1), (float4x3)WorldView);   // position (view space)
    float3 N = normalize(mul(Normal, (float3x3)WorldView));     // normal (view space)
    float3 T = normalize(mul(Tangent, (float3x3)WorldView));    // tangent (view space)
    float3 B = cross(N, T);                                     // binormal (view space)
    float3 R = normalize(2 * dot(N, L) * N - L);                // reflection vector (view space)
    float3 V = -normalize(P);                                   // view direction (view space)
    float3 G = normalize(2 * dot(N, V) * N - V);                // glance vector (view space)
    float3 H = normalize(L + V);                                // half vector (view space)
    float  f = 0.5 - dot(V, N); f = 1 - 4 * f * f;              // fresnel term

    // position (projected)
    Out.Position = mul(float4(P, 1), Projection);             

    // diffuse + ambient (metal)
    Out.Diffuse = I_a * k_a + I_d * k_d * max(0, dot(N, L)); 

    // specular (wax)
    Out.Specular  = saturate(dot(H, N));
    Out.Specular *= Out.Specular;
    Out.Specular *= Out.Specular;
    Out.Specular *= Out.Specular;
    Out.Specular *= Out.Specular;                              
    Out.Specular *= Out.Specular;                        
    Out.Specular *= k_r;                                       

     // glossiness (wax)
    Out.Glossiness = f * k_r;

    // transform half vector into vertex space
    Out.HalfVector = float3(dot(H, N), dot(H, B), dot(H, T));   
    Out.HalfVector = (1 + Out.HalfVector) / 2;  // bias

    // environment cube map coordinates
    Out.Reflection = float3(-G.x, G.y, -G.z);                   

    // volume noise coordinates
    Out.NoiseCoord = Position * VOLUME_NOISE_SCALE;             

    return Out;
}

// samplers
sampler Environment = sampler_state
{ 
    Texture = (EnvironmentMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler SparkleNoise = sampler_state
{ 
    Texture = (NoiseMap);
    MipFilter = LINEAR; 
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// pixel shader
float4 PS(VS_OUTPUT In) : COLOR
{   
    float4 Color = (float4)0;
    float3 Diffuse, Specular, Gloss, Sparkle;

    // volume noise
    float4 Noise = tex3D(SparkleNoise, In.NoiseCoord);

    // noisy diffuse of metal
    Diffuse = In.Diffuse * Noise.a;
    
    // glossy specular of wax
    Specular  = In.Specular;
    Specular *= Specular;
    Specular *= Specular;
    
    // glossy reflection of wax 
    Gloss = texCUBE(Environment, In.Reflection) * saturate(In.Glossiness);              

    // specular sparkle of flakes
    Sparkle  = saturate(dot((saturate(In.HalfVector) - 0.5) * 2, (Noise.rgb - 0.5) * 2));
    Sparkle *= Sparkle;
    Sparkle *= Sparkle;
    Sparkle *= Sparkle;                                                                    
    Sparkle *= k_s;      

    // combine the contributions
    Color.rgb = Diffuse + Specular + Gloss + Sparkle;
    Color.w   = 1;

    return Color;
}  

// technique
technique TMetallicFlakes
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_1_1 PS();

        AlphaBlendEnable = FALSE;
        CullMode         = NONE;
    }
}

