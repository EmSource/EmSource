//
// Shaders used by the ClipVolume D3D sample to draw the teapot and sphere
//
// Note: This effect file does not work with EffectEdit.
//

VertexShader ClipVS = asm
{
    vs.1.1 

    dcl_position0 v0   // v0 = position
    dcl_normal0   v1   // v1 = normal

    // c0...c3  = rotation matrix (from Arcball)  (set externally)
    // c4...c7  = translation matrix              (set externally)
    // c8...c11 = projection matrix               (set externally)
    // c12.xyz  = center of sphere in world space (set externally)
    // c12.w    = radius of sphere                (set externally)
    // c91      = green color - red color (c91 + c92 = green color)
    // c92      = red color
    def c91, -1, 1, 0, 0 
    def c92, 1, 0, 0, 0 

    //-------------------------------------------------------------------------
    // POSITION
    //-------------------------------------------------------------------------

    m4x4 r0, v0, c0 
    m4x4 r1, r0, c4 
    m4x4 oPos, r1, c8 

    //-------------------------------------------------------------------------
    // Calculate per-vertex distance from center of sphere
    //-------------------------------------------------------------------------

    sub r2.xyz, r1.xyz, c12.xyz 
    dp3 r2.x, r2, r2 
    rsq r2.x, r2.x 
    rcp r2.x, r2.x 
    // r2.x = distance between current vertex and center of sphere

    sub oT0, r2.x, c12.w 
    // if the current vertex is inside the sphere, oT0 < 0
    // else                                      , oT0 >= 0

    //-------------------------------------------------------------------------
    // DIFFUSE (simple two-sided lighting)
    //-------------------------------------------------------------------------

    m3x3 r3.xyz, v1, c0 
    // NORMAL : rotation (from Arcball)

    sge r3.x, -r3.z, c91.w 
    // assume light vector = (0, 0, -1), -r3.z = [light] dot [normal]
    // if front-facing, r3.x = 1
    // else           , r3.x = 0

    mov r4, c91 
    mad r5, r4, r3.x, c92 
    // if r3.x == 1, r5 = (0, 1, 0, 0) = green (front-facing)
    // else        , r5 = (1, 0, 0, 0) = red (back-facing)

    max r6.x, -r3.z, r3.z 
    mul oD0, r5, r6.x 
    // output DIFFUSE : modulate with abs(LAMBERTIAN TERM) before output
};

PixelShader ClipPS = asm 
{
    ps.1.1

    texkill t0
    // discard the current pixel if any of t0.x | t0.y | t0.z | t0.w < 0

    mov r0, v0 
    // output DIFFUSE : r0.w is used as alpha-blending factor later
};

// Shader used by the ClipVolume D3D sample to draw the sphere

VertexShader SphereVS = asm
{
    vs.1.1

    // c4...c7  = translation matrix (set externally)
    // c8...c11 = projection matrix  (set externally)
    // c13      = color of sphere (.w is the alpha-blending factor)
    def c13, 0, 0, 0.5, 0.5

    dcl_position0 v0   // v0 = position (we don't use normal v1 here)

    m4x4 r0, v0, c4 
    m4x4 oPos, r0, c8 
    // output POSITION

    mov oD0, c13 
    // output DIFFUSE : .w is used as alpha-blending factor later
};

technique Teapot
{
    pass p0
    {
        CullMode = None;
        AlphaBlendEnable = False;
        VertexShader = (ClipVS);
        PixelShader  = (ClipPS);
    }
}

technique Sphere
{
    pass p0
    {
        CullMode = CCW;
        AlphaBlendEnable = True;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        VertexShader = (SphereVS);
        PixelShader  = Null;
    }
}

