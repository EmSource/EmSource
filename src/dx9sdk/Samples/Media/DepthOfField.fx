//
// Depth of field effect
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Note: This effect file does not work with EffectEdit.
//

float4 Ambient;
float4 Specular;
float4 Diffuse;
float4 Emissive;
float Power;

texture RenderTargetTexture;
texture EarthTexture;

float4x4 mWorldView;
float4x4 mProjection;

float3 vLightDir = normalize(float3(1.0f, 1.0f, 1.0f));

float4 vFocalPlane;
float  fHyperfocalDistance = 0.4f;

float MaxBlurFactor = 3.0f / 4.0f;

sampler RenderTarget = 
sampler_state
{
    Texture = <RenderTargetTexture>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;

    AddressU = Clamp;
    AddressV = Clamp;
};

float2 TwelveKernel[12];
float2 TwelveKernelBase[12] =
{
    { 1.0f,  0.0f},
    { 0.5f,  0.8660f},
    {-0.5f,  0.8660f},
    {-1.0f,  0.0f},
    {-0.5f, -0.8660f},
    { 0.5f, -0.8660f},
    
    { 1.5f,  0.8660f},
    { 0.0f,  1.7320f},
    {-1.5f,  0.8660f},
    {-1.5f, -0.8660f},
    { 0.0f, -1.7320f},
    { 1.5f, -0.8660f},
};

//
// HLSL can't currently generate a 5 sample DepthOfField
// shader within ps1.4 instruction limits.
//
PIXELSHADER ps14DepthOfFieldNoRings = 
asm
{
    ps.1.4
    
    def c0, 0.66666, 0, 0.4, 0.5

    texld r0, t0
    texld r1, t1
    texld r2, t2
    texld r3, t3

    mul_sat r1.a, r1.a, r0.a
    lrp r1.rgb, r1.a, r1, r0

    +mul_sat r2.a, r2.a, r0.a
    lrp r2.rgb, r2.a, r2, r0

    +mul_sat r3.a, r3.a, r0.a
    lrp r3.rgb, r3.a, r3, r0

    lrp r1, c0.a, r1, r2

    lrp r3.rgb, c0.r, r1, r3

    phase

    texld r0, t0
    texld r1, t4
    texld r2, t5

    mul_sat r1.a, r1.a, r0.a
    lrp r1.rgb, r1.a, r1, r0

    +mul_sat r2.a, r2.a, r0.a
    lrp r2.rgb, r2.a, r2, r0

    lrp r1.rgb, c0.a, r1, r2

    lrp r0.rgb, c0.z, r1, r3
};

PIXELSHADER ps11DepthOfFieldNoRings = 
asm
{
    ps_1_1
    
    def c0, 0, 0, 0, 0.5
    def c1, 0, 0, 0, 0.666666

    tex t0
    tex t1
    tex t2
    tex t3

    mul_sat t1.a, t1.a, t0.a
    lrp t1.rgb, t1.a, t1, t0

    +mul_sat t2.a, t2.a, t0.a
    lrp t2.rgb, t2.a, t2, t0

    +mul_sat t3.a, t3.a, t0.a
    lrp t3.rgb, t3.a, t3, t0

    lrp t1, c0.a, t1, t2
    lrp r0, c1.a, t1, t3
};

float4 DepthOfFieldNoRings
    (
    in float2 OriginalUV : TEXCOORD0,
    in float2 JitterUV[3] : TEXCOORD1
    ) : COLOR
{
    float4 Original = tex2D(RenderTarget, OriginalUV);
    float4 Jitter[3];
    float3 Blurred;
    
    for(int i = 0; i < 3; i++)
    {
        Jitter[i] = tex2D(RenderTarget, JitterUV[i]);
        Jitter[i].rgb = lerp(Original.rgb, Jitter[i].rgb, saturate(Original.a*Jitter[i].a));
    }
        
    // Average the first two jitter samples
    Blurred = lerp(Jitter[0].rgb, Jitter[1].rgb, 0.5);
    
    // Equally weight all three jitter samples
    Blurred = lerp(Jitter[2].rgb, Blurred, 0.66666);
    
    return float4(Blurred, 1.0f);
}
    
float4 DepthOfFieldWithSixTexcoords
    (
    in float2 OriginalUV : TEXCOORD0,
    in float2 JitterUV[5] : TEXCOORD1
    ) : COLOR
{
    float4 Original = tex2D(RenderTarget, OriginalUV);
    float4 Jitter[5];
    float3 Blurred = 0;
    
    for(int i = 0; i < 5; i++)
    {
        Jitter[i] = tex2D(RenderTarget, JitterUV[i]);
        Blurred += lerp(Original.rgb, Jitter[i].rgb, saturate(Original.a*Jitter[i].a));
    }
            
    return float4(Blurred / 5.0f, 1.0f);
}
    
float4 DepthOfFieldManySamples
    (
    in float2 OriginalUV : TEXCOORD0,
    uniform float2 KernelArray[12],
    uniform int NumSamples
    ) : COLOR
{
    float4 Original = tex2D(RenderTarget, OriginalUV);
    float3 Blurred = 0;
    
    for(int i = 0; i < NumSamples; i++)
    {
        float4 Current = tex2D(RenderTarget, OriginalUV + KernelArray[i]);
        Blurred += lerp(Original.rgb, Current.rgb, saturate(Original.a*Current.a));
    }
            
    return float4(Blurred / NumSamples, 1.0f);
}

PIXELSHADER ps11DepthOfFieldWithRings = 
asm
{
    ps.1.1
    
    def c0, 0.33333, 0.33333, 0.33333, 0.33333
    def c1, 0.66666, 0.5, 0.5, 0.5
    def c2, 0.66666, 0.5, 0.5, 0.666666

    tex t0
    tex t1
    tex t2
    tex t3

    lrp t1.rgb, t0.a, t1, t0

    lrp t2.rgb, t0.a, t2, t0

    lrp t3.rgb, t0.a, t3, t0

    lrp t1, c1.a, t1, t2
    lrp r0, c2.a, t1, t3
};

float4 DepthOfFieldWithRings
    (
    in float2 OriginalUV : TEXCOORD0,
    in float2 JitterUV[3] : TEXCOORD1
    ) : COLOR
{
    float4 Original = tex2D(RenderTarget, OriginalUV);
    float4 Jitter[3];
    float3 Blurred;
    
    for(int i = 0; i < 3; i++)
    {
        Jitter[i] = tex2D(RenderTarget, JitterUV[i]);
        Jitter[i].rgb = lerp(Original.rgb, Jitter[i].rgb, Original.a);
    }
        
    // Average the first two jitter samples
    Blurred = lerp(Jitter[0].rgb, Jitter[1].rgb, 0.5);
    
    // Equally weight all three jitter samples
    Blurred = lerp(Jitter[2].rgb, Blurred, 0.66666);
    
    return float4(Blurred, 1.0f);
}
    

PIXELSHADER ps11ShowAlpha = 
asm
{
    ps.1.1
    tex t0
    mov r0, t0.a
};


PIXELSHADER ps11ShowUnmodified = 
asm
{
    ps.1.1
    tex t0
    mov r0, t0
};


// Output structure for WorldTransform
struct VS_OUTPUT_TEXCOORD0
{
    float4 Position : POSITION;
    float4 Diffuse : COLOR;
    float2 Texture0 : TEXCOORD0;
};


// Transform objects into the view, also setting the appropriate blur factor
VS_OUTPUT_TEXCOORD0 WorldTransform
    (
    float4 vPos : POSITION, 
    float3 vNormal : NORMAL,
    float2 vTexCoord0 : TEXCOORD0
    )
{
    VS_OUTPUT_TEXCOORD0 Output;
    float3 vTransformedPosition;
    float3 vTransformedNormal;
    float fBlurFactor;
  
    // tranform the position/normal into view space
    vTransformedPosition = mul(vPos, (float4x3)mWorldView);
    vTransformedNormal = mul(vNormal, (float3x3)mWorldView);       
    
    // tranform view space position into screen space
    Output.Position = mul(float4(vTransformedPosition, 1.0), mProjection);
    
    // Compute simple lighting equation
    //   NOTE: color could be negative with this equation, but will be clamped to zero before pixel shader
    Output.Diffuse.rgb = Diffuse * dot(vTransformedNormal, vLightDir) + Ambient;
    
    // Compute blur factor and place in output alpha
    fBlurFactor      = dot(float4(vTransformedPosition, 1.0), vFocalPlane)*fHyperfocalDistance;
    Output.Diffuse.a = fBlurFactor*fBlurFactor;
    
    // put a cap on the max blur value.  This is required to ensure that the center pixel
    //  is always weighted in the blurred image.  I.E. in the PS11 case, the correct maximum
    //  value is (NumSamples - 1) / NumSamples, otherwise at BlurFactor == 1.0f, only the outer
    //  samples are contributing to the blurred image which causes annoying ring artifacts
    Output.Diffuse.a = min(Output.Diffuse.a, MaxBlurFactor);
    
    // just copy the texture coordinate through
    Output.Texture0 = float2(1.0-vTexCoord0.x, vTexCoord0.y);
    
    return Output;    
}


//
// Technique "World" - Draws the original, unblurred image
//
technique World
{
    pass P0
    {        
        VertexShader = compile vs_1_1 WorldTransform();

        MinFilter[0] = Linear;
        MagFilter[0] = Linear;
        MipFilter[0] = Linear;

        // Stage0
        ColorOp[0]   = Modulate;
        ColorArg1[0] = Texture;
        ColorArg2[0] = Current;
        AlphaOp[0]   = SelectArg1;
        AlphaArg1[0] = Current;

        Texture[0] = <EarthTexture>;

        // Stage1
        ColorOp[1] = Disable;
        AlphaOp[1] = Disable;
    }
}


//
// Various techniques for simulating depth of field
// 

technique UsePS11WithRings
<
    float MaxBlurFactor = 3.0f / 4.0f;
>
{
    pass P0
    {        
        PixelShader = compile ps_1_1 DepthOfFieldWithRings();
    }
}

technique UsePS11WithRingsAsm
<
    float MaxBlurFactor = 3.0f / 4.0f;
>
{
    pass P0
    {        
        Sampler[0] = <RenderTarget>;
        Sampler[1] = <RenderTarget>;
        Sampler[2] = <RenderTarget>;
        Sampler[3] = <RenderTarget>;

        PixelShader = <ps11DepthOfFieldWithRings>;
    }
}

technique UsePS11NoRings
<
    float MaxBlurFactor = 3.0f / 4.0f;
>
{
    pass P0
    {        
        PixelShader = compile ps_1_1 DepthOfFieldNoRings();
    }
}

technique UsePS11NoRingsAsm
<
    float MaxBlurFactor = 3.0f / 4.0f;
>
{
    pass P0
    {        
        Sampler[0] = <RenderTarget>;
        Sampler[1] = <RenderTarget>;
        Sampler[2] = <RenderTarget>;
        Sampler[3] = <RenderTarget>;

        PixelShader = <ps11DepthOfFieldNoRings>;
    }
}

technique UsePS14NoRingsAsm
<
    float MaxBlurFactor = 4.0f / 5.0f;
>
{
    pass P0
    {        
        Sampler[0] = <RenderTarget>;
        Sampler[1] = <RenderTarget>;
        Sampler[2] = <RenderTarget>;
        Sampler[3] = <RenderTarget>;

        PixelShader = <ps14DepthOfFieldNoRings>;
    }
}

technique UsePS20SixTexcoords
<
    float MaxBlurFactor = 4.0f / 5.0f;
>
{
    pass P0
    {        
        PixelShader = compile ps_2_0 DepthOfFieldWithSixTexcoords();
    }
}

technique UsePS20SevenLookups
<
    float MaxBlurFactor = 6.0f / 7.0f;
    int NumKernelEntries = 12;
    string KernelInputArray = "TwelveKernelBase";
    string KernelOutputArray = "TwelveKernel";  
>
{
    pass P0
    {        
        PixelShader = compile ps_2_0 DepthOfFieldManySamples(TwelveKernel, 6);
    }
}

technique UsePS20ThirteenLookups
<
    float MaxBlurFactor = 12.0f / 13.0f;
    int NumKernelEntries = 12;
    string KernelInputArray = "TwelveKernelBase";
    string KernelOutputArray = "TwelveKernel";  
>
{
    pass P0
    {        
        PixelShader = compile ps_2_0 DepthOfFieldManySamples(TwelveKernel, 12);
    }
}

//
// Technique "ShowAlpha" - display the per pixel blur factor
// 
technique ShowAlpha
{
    pass P0
    {        
        Sampler[0] = <RenderTarget>;

        PixelShader = <ps11ShowAlpha>;
    }
}

//
// Technique "ShowUnmodified" - display the original unblurred image
// 
technique ShowUnmodified
{
    pass P0
    {        
        Sampler[0] = <RenderTarget>;

        PixelShader = <ps11ShowUnmodified>;
    }
}