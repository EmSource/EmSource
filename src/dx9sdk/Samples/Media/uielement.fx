//
// UIElement.fx
//
// Note: This effect file works with EffectEdit.
//

technique Unselected
{
    pass p0
    {
        // Set up reasonable material defaults
        MaterialAmbient   = {1.0, 1.0, 1.0, 1.0}; 
        MaterialDiffuse   = {1.0, 1.0, 1.0, 1.0}; 
        MaterialSpecular  = {1.0, 1.0, 1.0, 1.0}; 
        MaterialPower     = 40.0;
        
        // Set up one directional light
        LightType[0]      = DIRECTIONAL;
        LightAmbient[0]   = {0.2, 0.2, 0.2, 1.0};
        LightDiffuse[0]   = {0.0, 0.0, 0.8, 1.0};
        LightSpecular[0]  = {1.0, 1.0, 1.0, 1.0}; 
        LightDirection[0] = {0.7, -0.7, 0.0 };
        LightRange[0]     = 100000.0f;
        
        // Turn lighting on and use light 0
        LightEnable[0] = True;
        Lighting = True;
        SpecularEnable = False;
        FillMode = Solid;
        
        // Set up textures and texture stage states
        ColorOp[0] = SelectArg2;
        ColorArg1[0] = Texture;
        ColorArg2[0] = Diffuse;
        AlphaOp[0] = SelectArg2;
        AlphaArg1[0] = Texture;
        AlphaArg2[0] = Diffuse;

        ColorOp[1] = Disable;
        AlphaOp[1] = Disable;
    }
}

technique Selected
{
    pass p0
    {
        // Set up reasonable material defaults
        MaterialAmbient   = {1.0, 1.0, 1.0, 1.0}; 
        MaterialDiffuse   = {1.0, 1.0, 1.0, 1.0}; 
        MaterialSpecular  = {1.0, 1.0, 1.0, 1.0}; 
        MaterialPower = 40.0;
        
        // Set up one directional light
        LightType[0]      = DIRECTIONAL;
        LightAmbient[0]   = {0.2, 0.2, 0.2, 1.0};
        LightDiffuse[0]   = {0.6, 0.6, 1.0, 1.0};
        LightSpecular[0]  = {1.0, 1.0, 1.0, 1.0}; 
        LightDirection[0] = {0.7, -0.7, 0.0 };
        LightRange[0]     = 100000.0f;
        
        // Turn lighting on and use light 0
        LightEnable[0] = True;
        Lighting = True;
        SpecularEnable = False;
        FillMode = Solid;
        
        // Set up textures and texture stage states
        ColorOp[0] = SelectArg2;
        ColorArg1[0] = Texture;
        ColorArg2[0] = Diffuse;
        AlphaOp[0] = SelectArg2;
        AlphaArg1[0] = Texture;
        AlphaArg2[0] = Diffuse;

        ColorOp[1] = Disable;
        AlphaOp[1] = Disable;
    }
}
