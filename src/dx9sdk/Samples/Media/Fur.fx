//
// Fur effect using shells and fins
//
// Note: This effect file does not work with EffectEdit.
//
#define C_ZERO              0 
#define C_ONE               1 
#define C_HALF              2 
#define C_MATTOTAL          4 
#define C_MATWORLD          8 
#define C_LIGHT_DIRECTION   20
#define C_LIGHT_AMBIENT     21
#define C_LIGHT_DIFFUSE     22
#define C_LIGHT_SPECULAR    23
#define C_MATERIAL_SPECULAR 26
#define C_EYE_POSITION      27
#define C_DISPLACEMENTS     30



// light direction
float3 L = normalize(float3(-0.2182f, -0.8729f, 0.4364f));

// light intensity
float4 I_a = float4(0.3f, 0.3f, 0.3f, 1.0f);    // ambient
float4 I_d = float4(0.6f, 0.6f, 0.6f, 1.0f);    // diffuse
float4 I_s = float4(0.8f, 0.8f, 0.8f, 1.0f);    // reflective

// material specular 
float4 k_s = float4(1.0f, 1.0f, 1.0f, 1.0f);

// transformations
float4x4 World      : WORLD;
float4x4 View       : VIEW;
float4x4 Projection : PROJECTION;

// eye position
float3 Eye;

// textures
texture FinTex;
texture ShellTex;

// shell properties
float ShellThickness = 0.4f;
float ShellScalingFactor;

static const float4 vOne = float4(1, 1, 1, 1);

// vertex shaders
VertexShader ShellVS = asm
{
	;------------------------------------------------------------------------------
	; Constants specified by the app
	;    c0      = ( 0, 0, 0, 0 )
	;    c1      = ( 1, 1, 1, 1 )
	;    c4-c7   = matWorldViewProjection
	;    c8-c10  = matWorld
	;    c20     = light direction (in model space)
	;    c21     = light ambient
	;    c22     = light diffuse
	;    c23     = light specular
	;    c26     = material specular
	;    c27     = eye position (world space)
	;    c30.x   = normal displacement total
	;    c30.y   = normal displacement as a 0 to 1 pct of total
	;    c30.z   = self-shadowing factor
	;
	; Vertex components (as specified in the vertex DECL)
	;    v0    = Position
	;    v3    = Normal
	;    v4    = diffuse
	;    v6    = Texcoords
	;------------------------------------------------------------------------------
	vs.1.1

	dcl_position v0
	dcl_normal   v3
	dcl_color0   v4
	dcl_texcoord v6

	// OUTPUT POSITION
	// in model space, add some normal to the position
	mul r5.z, c30.x, c30.y
	mul r5, r5.z, v3
	add r5, r5, v0
	mov r5.w, v0.w

	// transform vertex position by total matrix and output it
	dp4 oPos.x, r5, c4
	dp4 oPos.y, r5, c5
	dp4 oPos.z, r5, c6
	dp4 oPos.w, r5, c7

	// LIGHTING - WORK IN WORLD SPACE
	// Lighting is Ka + Kd(1-NdotL^2) + Ks(1-NdotH^2)
	// An alternative to calculating the total lighting here
	// is to map the total light into a texture(u,v) where
	// u maps to NdotL
	// v maps to NdotH
	// transform normal by world matrix
	dp3 r6.x, v3, c8
	dp3 r6.y, v3, c9
	dp3 r6.z, v3, c10

	// normalize normal
	dp3 r6.w, r6, r6
	rsq r6.w, r6.w
	mul r6, r6, r6.w

	// AMBIENT TERM 
	// modulate light ambient by material ambient
	mul r0, v4, c21

	// DIFFUSE TERM
	// For lighing purposes, consider the hair "direction" to be equivalent to the vertex normal (v3-r6).
	// For "directional" hair a second normal could be generated into Stream(1). This vector would contain
	// the general direction of the hair (to be used for lighting).
	// calculate light dot product with normal
	dp3 r2, r6, -c20

	// take Kd(1-LdotN^2)
	mad r2.x, r2.x, -r2.x, c1.x
	// modulate by light diffuse
	mul r2, r2.x, c22
	// modulate by material diffuse
	mad r0, r2, v4, r0

	// SPECULAR TERM
	// rather than use the "infinite viewer" eyepoint we can calculate it on a per-vertex basis
	// find eye direction
	add r3, v0, -c27
	// normalize the eye direction
	dp3 r3.w, r3, r3
	rsq r3.w, r3.w
	mul r3, r3, r3.w

	// add eye normal - light direction
	add r3, -c20, r3

	// normalize half-vector
	dp3 r3.w, r3, r3
	rsq r3.w, r3.w
	mul r3, r3, r3.w

	// evaluate (1-NdotH^2)
	dp3 r3.x, r6, r3
	mad r3.x, r3.x, -r3.x, c1.x
	// modulate by light specular
	mul r3, r3.x, c23

	// modulate by material specular, and add accumulator to yield final color
	mad r0, r3, c26, r0
	// now self-shadow "final" color
	mul oD0, c30.z, r0
	// make the shell diffuse opaque
	// this lets the texture control transparency by its alpha channel
	mov oD0.w, c1.w

	// output the texture coordinates
	mov oT0, v6
};


VertexShader FinVS = asm
{
	;------------------------------------------------------------------------------
	; Constants specified by the app
	;    c0      = ( 0, 0, 0, 0 )
	;    c1      = ( 1, 1, 1, 1 )
	;    c2      = (.5,.5,.5,.5 )
	;    c4-c7   = matWorldViewProjection
	;    c8-c10  = matWorld
	;    c20     = light direction (in model space)
	;    c21     = light ambient
	;    c22     = light diffuse
	;    c23     = light specular
	;    c26     = material specular
	;    c27     = eye position (world space)
	;    c30.x   = normal displacement total
	;
	; Vertex components (as specified in the vertex DECL)
	;    v0    = Position
	;    v3    = Normal
	;    v4    = diffuse
	;    v6    = Texcoords    Note: v6.y is used as an extrusion factor
	;------------------------------------------------------------------------------
	vs.1.1

	dcl_position    v0
	dcl_normal      v3
	dcl_color0      v4
	dcl_texcoord    v6

	// OUTPUT POSITION
	// in model space, extrude vertex out by texture v coord, inverting it's direction (v6'.y = 1 - v6.y)
	mad r5.z, -c30.x, v6.y, c30.x
	// multiply the normal by the extrusion value
	mul r5, r5.z, v3
	// add to v0
	add r5, r5, v0
	mov r5.w, v0.w

	// transform vertex position by total matrix and output it
	dp4 oPos.x, r5, c4
	dp4 oPos.y, r5, c5
	dp4 oPos.z, r5, c6
	dp4 oPos.w, r5, c7

	// LIGHTING - WORK IN WORLD SPACE
	// Lighting is Ka + Kd(1-NdotL^2) + Ks(1-NdotH^2)
	// An alternative to calculating the total lighting here
	// is to map the total light into a texture(u,v) where
	// u maps to NdotL
	// v maps to NdotH
	// transform normal by world matrix
	dp3 r6.x, v3, c8
	dp3 r6.y, v3, c9
	dp3 r6.z, v3, c10

	// normalize normal
	dp3 r6.w, r6, r6
	rsq r6.w, r6.w
	mul r6, r6, r6.w

	// AMBIENT TERM 
	// modulate light ambient by material ambient
	mul r0, v4, c21

	// DIFFUSE TERM
	// For lighing purposes, consider the hair "direction" to be equivalent to the vertex normal (v3-r6).
	// For "directional" hair a second normal could be generated into Stream(1). This vector would contain
	// the general direction of the hair (to be used for lighting).
	// calculate light dot product with normal
	dp3 r2, r6, -c20

	// take Kd(1-LdotN^2)
	mad r2.x, r2.x, -r2.x, c1.x
	// modulate by light diffuse
	mul r2, r2.x, c22
	// modulate by material diffuse
	mad r0, r2, v4, r0

	// SPECULAR TERM
	// rather than use the "infinite viewer" eyepoint we can calculate it on a per-vertex basis
	// find eye direction
	add r3, v0, -c27
	// normalize eye direction
	dp3 r3.w, r3, r3
	rsq r3.w, r3.w
	mul r3, r3, r3.w

	// fade the fin in as it enters the model silhouette
	dp3 r2.w, r3, r6
	mad oD0.w, r2.w, -r2.w, c1.w

	// add eye normal - light direction
	add r3, -c20, r3

	// normalize half-vector
	dp3 r3.w, r3, r3
	rsq r3.w, r3.w
	mul r3, r3, r3.w

	// evaluate (1-LdotH^2)
	dp3 r3.x, r6, r3
	mad r3.x, r3.x, -r3.x, c1.x
	// modulate by light specular
	mul r3, r3.x, c23

	// modulate by material specular, and add accumulator to yield final color
	mad r3, r3, c26, r0
	// set self-shadowing to .5 -> 1.
	max r7.y, c2.y, v6.y
	mul oD0.xyz, r7.y, r3.xyz

	// output the texture coordinates
	mov oT0, v6
};

// sampler
sampler ClampedLinear = 
sampler_state
{
    Texture   = NULL;
    AddressU  = CLAMP;
    AddressV  = CLAMP;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// techniques
technique Init
{
    pass P0
    {
        // render states
        CullMode = NONE;

        AmbientMaterialSource = COLOR1;
        DiffuseMaterialSource = COLOR1;

        BlendOp   = ADD;
        SrcBlend  = SRCALPHA;
        DestBlend = INVSRCALPHA;

        AlphaTestEnable = FALSE;
        AlphaFunc       = GREATER;
        AlphaRef        = 0;

        AlphaBlendEnable = TRUE;

        // texture stage states
        AlphaOp[0]   = MODULATE;
        AlphaArg1[0] = TEXTURE;
        AlphaArg2[0] = CURRENT;

        // sampler
        Sampler[0]  = (ClampedLinear);

        // lighting
        LightType[0]      = DIRECTIONAL;
        LightDirection[0] = (L);
        LightAmbient[0]   = (I_a);
        LightDiffuse[0]   = (I_d);
        LightSpecular[0]  = (I_s);
        LightEnable[0]    = TRUE;

        Lighting = FALSE;

        // vertex shader constants
        VertexShaderConstantF[C_ZERO]              = (0.0f * vOne);
        VertexShaderConstantF[C_ONE]               = (1.0f * vOne);
        VertexShaderConstantF[C_HALF]              = (0.5f * vOne);
        VertexShaderConstantF[C_LIGHT_DIRECTION]   = (L);
        VertexShaderConstantF[C_LIGHT_AMBIENT]     = (I_a);
        VertexShaderConstantF[C_LIGHT_DIFFUSE]     = (I_d);
        VertexShaderConstantF[C_LIGHT_SPECULAR]    = (I_s);
        VertexShaderConstantF[C_MATERIAL_SPECULAR] = (k_s);

        // transforms
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
    }
}

technique Base
{
	pass P0
	{
        // render states
        CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
		Lighting = TRUE;

        // fixed function
		VertexShader = NULL;
		FVF = XYZ | NORMAL | DIFFUSE;

        // transforms
        WorldTransform[0]   = (World);
	}
}


technique Fins
{
    pass P0
    {
        // render states
        ZWriteEnable = FALSE;

        // texture
        Texture[0] = (FinTex);

        // vertex shader
        VertexShader = (FinVS);

        VertexShaderConstantF[C_DISPLACEMENTS] = float4(ShellThickness, 0.0f, 1.0f, 0.0f);
        VertexShaderConstantF[C_EYE_POSITION]  = (Eye);
        VertexShaderConstantF[C_MATTOTAL]      = (mul(mul(World, View), Projection));
        VertexShaderConstantF[C_MATWORLD]      = (World);
    }
}


technique Shells
{
    pass P0
    {
        // render states
        AlphaTestEnable  = TRUE;

        // texture
        Texture[0] = (ShellTex);

        // vertex shader
        VertexShader = (ShellVS);

        VertexShaderConstantF[C_DISPLACEMENTS] = float4(0.5f * ShellThickness, ShellScalingFactor, 0.5f * (1 + ShellScalingFactor), 0.0f) ;
        VertexShaderConstantF[C_EYE_POSITION]  = (Eye);
        VertexShaderConstantF[C_MATTOTAL]      = (mul(mul(World, View), Projection));
        VertexShaderConstantF[C_MATWORLD]      = (World);
    }
}

