// Shaders used by the BumpEarth D3D sample

// Displacement mapping + bump mapping shader
//
// Float constants used:
//  C0 - C3 - transformation matrix
//  C4.x    - scale factor
//
VertexShader EarthBumpMap = asm
{
    vs_1_1
    // Input declaration
    dcl_position0 v0
    dcl_texcoord0 v1
    dcl_sample0   v2
    dcl_normal0   v3
    dcl_texcoord1 v4

    // Main function
    mul r0, v3, c4.x    // Multiply normal by a scale factor
    mul r0, r0, v2.x    // Multiply normal by the displacement value
    add r0, v0, r0      // Add normal to position
    mov r0.w, v0.w      // W component is taken from the input position
    m4x4 oPos, r0, c0   // Transform new position to the projection space
    mov oT0, v4         // Copy input texture coordinates
    mov oT1, v4         // Copy input texture coordinates
    mov oT2, v1         // Copy input texture coordinates
};

// Displacement mapping + no bump mapping shader
//
// Float constants used:
//  C0 - C3 - transformation matrix
//  C4.x    - scale factor
//
VertexShader EarthNoBumpMap = asm
{
    vs_1_1
    // Input declaration
    dcl_position0 v0
    dcl_texcoord0 v1
    dcl_sample0   v2
    dcl_normal0   v3
    dcl_texcoord1 v4

    // Main function
    mul r0, v3, c4.x    // Multiply normal by a scale factor
    mul r0, r0, v2.x    // Multiply normal by the displacement value
    add r0, v0, r0      // Add normal to position
    mov r0.w, v0.w      // W component is taken from the input position
    m4x4 oPos, r0, c0   // Transform new position to the projection space
    mov oT0, v4         // Copy input texture coordinates
    mov oT1, v1      
};

technique DisplacementMapping {}

