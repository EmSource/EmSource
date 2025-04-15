//
// Shaders used by the MotionBlur D3D sample
//
// Note: This effect file does not work with EffectEdit.
//

VertexShader MotionBlur = asm
{
    vs.1.1 

    dcl_position0 v0   // v0 = position
    dcl_normal0 v1   // v1 = normal

    // The following constants are set externally
    // c0 ...c3  = world matrix, previous frame
    // c4 ...c7  = world matrix, current frame
    // c8 ...c11 = rotation matrix (from Arcball)
    // c12...c15 = view matrix
    // c16...c19 = projection matrix
    // c20.x     = trail length
    // c20.y     = 0
    // c20.z     = 1

    //-------------------------------------------------------------------------
    // POSITION
    //-------------------------------------------------------------------------

    m4x4 r0, v0, c0 
    // r0.xyz = POSITION of previous frame

    m4x4 r1, v0, c4 
    // r1.xyz = POSITION of current frame

    m3x3 r2.xyz, v1, c4 
    // r2.xyz = N = NORMAL of current frame 

    sub r3, r1, r0 
    dp3 r4.x, r3.xyz, r3.xyz 
    rsq r4.x, r4.x 
    mul r3, r3, r4.x 
    dp3 r4.x, r2.xyz, r3.xyz 
    // r3.xyz = M = normalized moving vector
    // r4.x = (N dot M)

    slt r4.y, r4.x, c20.y 
    mul r4.y, r4.y, c20.x 
    mad r1.xyz, -r3, r4.y, r1 
    // if N points toward M, leave current POSITION unchanged
    // else                , offset current POSITION with (-M * trail length)

    m4x4 r5, r1, c8 
    m4x4 r6, r5, c12 
    m4x4 oPos, r6, c16 
    // POSITION in clipping space

    //-------------------------------------------------------------------------
    // DIFFUSE
    //-------------------------------------------------------------------------

    m3x3 r5.xyz, r2, c8 
    m3x3 r6.xyz, r5, c12 
    mov oD0.xyz, -r6.z 
    // oD0.xyz = DIFFUSE color, assuming fixed light direction (0, 0, -1)

    sge oD0.w, r4.x, c20.y  // oD0.w = (r4.x >= 0 ? 1 : 0 )
    // if (N dot M) < 0, oD0.w = 0
    // else            , oD0.w = 1
};

VertexShader NoMotionBlur = asm
{
    vs.1.1 

    dcl_position0 v0   // v0 = position
    dcl_normal0   v1   // v1 = normal

    // The following constants are set externally
    // c4 ...c7  = world matrix, current frame
    // c8 ...c11 = rotation matrix (from Arcball)
    // c12...c15 = view matrix
    // c16...c19 = projection matrix
    // c20.z     = 1

    //-------------------------------------------------------------------------
    // POSITION
    //-------------------------------------------------------------------------

    m4x4 r1, v0, c4 
    m4x4 r2, r1, c8 
    m4x4 r3, r2, c12 
    m4x4 oPos, r3, c16 

    //-------------------------------------------------------------------------
    // DIFFUSE
    //-------------------------------------------------------------------------

    m3x3 r0.xyz, v1, c4 
    m3x3 r1.xyz, r0, c8 
    m3x3 r2.xyz, r1, c12 
    mov oD0.xyz, -r2.z 
    mov oD0.w, c20.z 
    // oD0.xyz = DIFFUSE color, assuming fixed light direction (0, 0, -1)
    // oD0.w   = 1.0f = alpha (opaque)
};

technique MotionBlur
{
    pass p0
    {
        VertexShader = (NoMotionBlur);
    }
    pass p1
    {
        VertexShader = (MotionBlur);
        AlphaBlendEnable = True;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
    }
}
