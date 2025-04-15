// (c) 2001 Microsoft Corporation

function OnFinish(selProj, selObj)
{
	try
	{	
		var strProjectName 	= wizard.FindSymbol("PROJECT_NAME");				
		var strProjectPath	= wizard.FindSymbol("PROJECT_PATH");		
		
		selProj = CreateCSharpProject(strProjectName, strProjectPath, "DefaultWinExe.csproj");
		
		var InfFile = CreateInfFile();
		AddFilesToCSharpProject(selProj, strProjectName, strProjectPath, InfFile, false);
		InfFile.Delete();
		
		var vsProj = selProj.Object;	
		vsProj.References.Add("system.dll");
		vsProj.References.Add("System.Drawing.dll");
		vsProj.References.Add("System.Windows.Forms.dll");
		
		vsProj.References.Add("Microsoft.DirectX.dll");
		
		if(wizard.FindSymbol("GRAPHICSTYPE_DIRECT3D"))
		{
			vsProj.References.Add("Microsoft.DirectX.Direct3D.dll");
			vsProj.References.Add("Microsoft.DirectX.Direct3DX.dll");
		}
		
		if(wizard.FindSymbol("GRAPHICSTYPE_DIRECTDRAW"))
			vsProj.References.Add("Microsoft.DirectX.DirectDraw.dll");
		
		if(wizard.FindSymbol("USE_DIRECTINPUT"))
			vsProj.References.Add("Microsoft.DirectX.DirectInput.dll");
		
		if(wizard.FindSymbol("USE_AUDIO"))
		{
			vsProj.References.Add("Microsoft.DirectX.DirectSound.dll");
			vsProj.References.Add("Microsoft.DirectX.AudioVideoPlayback.dll");
		}
		
		if(wizard.FindSymbol("USE_DIRECTPLAY"))
		{
			if(wizard.FindSymbol("USE_VOICE") && !wizard.FindSymbol("USE_AUDIO"))
				vsProj.References.Add("Microsoft.DirectX.DirectSound.dll");

			vsProj.References.Add("Microsoft.DirectX.DirectPlay.dll");
		}
			
	}
	catch(e)
	{		
		wizard.ReportError(e.description);
	}
}

function GetCSharpTargetName(strName, strProjectName)
{
	return strName;	
}

function DoOpenFile(strName)
{
	var bOpen = false;
    
	if (strName == wizard.FindSymbol("FILENAME"))
		bOpen = true;

	return bOpen; 
}

function SetFileProperties(oFileItem, strFileName)
{
}
