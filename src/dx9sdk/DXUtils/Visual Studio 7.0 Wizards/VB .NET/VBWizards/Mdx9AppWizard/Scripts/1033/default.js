// (c) 2001 Microsoft Corporation

function OnFinish(selProj, selObj)
{
	try
	{	
		var strProjectName = wizard.FindSymbol("PROJECT_NAME");				
		var strProjectPath = wizard.FindSymbol("PROJECT_PATH");		
		var strProductPath = wizard.FindSymbol("PRODUCT_INSTALLATION_DIR");
		
		selProj = CreateVBProject(strProjectName, strProjectPath, strProductPath + "\\VBProjects\\EmptyProject.vbproj"); 		
		var InfFile = CreateInfFile();
				
		AddFilesToProject(selProj, strProjectName, strProjectPath, InfFile, false);				
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

/******************************************************************************
     Description: Creates a VB Project
  strProjectName: Project Name
  strProjectPath: The path that the project will be created in
 strTemplateFile: Project template file e.g. "defualt.vbproj"
******************************************************************************/
function CreateVBProject(strProjectName, strProjectPath, strTemplateFile)
{
	try
	{
		// Make sure user sees ui.
		dte.SuppressUI = false;
		var strProjTemplatePath = wizard.FindSymbol("PROJECT_TEMPLATE_PATH") + "\\";
		var strProjTemplate = strTemplateFile; 
		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{

				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		strProjectNameWithExt = strProjectName + ".vbproj";

		var oTarget = wizard.FindSymbol("TARGET");
		var oPrj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
            var nPos = strProjectPath.search("http://");
            var prjItem
            if(nPos == 0)
                prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectPath + "/" + strProjectNameWithExt);    
            else
			    prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectPath + "\\" + strProjectNameWithExt);
			oPrj = prjItem.SubProject;
		}
		else
		{
			oPrj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		var strNameSpace = "";
		strNameSpace = oPrj.Properties("RootNamespace").Value;
		wizard.AddSymbol("SAFE_NAMESPACE_NAME",  strNameSpace);

		return oPrj;
	}
	catch(e)
	{
		// propagate all errors back to the caller
		throw e;
	}
}

/******************************************************************************
 Description: Creates the Templates.inf file.
              Templates.inf is created based on TemplatesInf.txt and contains
			  a list of file names to be created by the wizard.
******************************************************************************/
function CreateInfFile()
{
	try
	{
		var oFSO, TemplatesFolder, TemplateFiles, strTemplate;
		oFSO = new ActiveXObject("Scripting.FileSystemObject");

		var TemporaryFolder = 2;
		var oFolder = oFSO.GetSpecialFolder(TemporaryFolder);

		var strTempFolder = oFSO.GetAbsolutePathName(oFolder.Path);
		var strWizTempFile = strTempFolder + "\\" + oFSO.GetTempName();

		var strTemplatePath = wizard.FindSymbol("TEMPLATES_PATH");
		var strInfFile = strTemplatePath + "\\Templates.inf";
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var oWizTempFile = oFSO.GetFile(strWizTempFile);
		return oWizTempFile;

	}
	catch(e)
	{   
		throw e;
	}
}

/******************************************************************************
    Description: Adds all the files to the project based on the Templates.inf file.
          oProj: Project object
 strProjectName: Project name
 strProjectPath: Project path
        InfFile: Templates.inf file object
    AddItemFile: Wether the wizard is invoked from the Add Item Dialog or not
******************************************************************************/
function AddFilesToProject(oProj, strProjectName, strProjectPath, InfFile, AddItemFile)
{
	try
	{
		dte.SuppressUI = false;
					
		var projItems;
		if(AddItemFile)
	  	    projItems = oProj;
		else
	  	    projItems = oProj.ProjectItems;
    
		var strTemplatePath = wizard.FindSymbol("TEMPLATES_PATH");

		var strTpl = "";
		var strName = "";

		// if( Not a web project )
		if(strProjectPath.charAt(strProjectPath.length - 1) != "\\")
		    strProjectPath += "\\";	

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
				
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != "")
			{
				strName = strTpl;
				var strTarget = "";
				var strFile = "";
				if(!AddItemFile)
				{
					strTarget = GetTargetName(strName, strProjectName);
				}
				else
				{
					strTarget = wizard.FindSymbol("ITEM_NAME");
				}

				var fso;
				fso = new ActiveXObject("Scripting.FileSystemObject");
				var TemporaryFolder = 2;
				var tfolder = fso.GetSpecialFolder(TemporaryFolder);
				var strTempFolder = fso.GetAbsolutePathName(tfolder.Path);

				var strFile = strTempFolder + "\\" + fso.GetTempName();

				var strClassName = strTarget.split(".");
				wizard.AddSymbol("SAFE_CLASS_NAME", strClassName[0]);
	    			wizard.AddSymbol("SAFE_ITEM_NAME", strClassName[0]);

				var strTemplate = strTemplatePath + "\\" + strTpl;
				var bCopyOnly = false;
				var strExt = strTpl.substr(strTpl.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly, true);
				
				var projfile = projItems.AddFromTemplate(strFile, strTarget);
				SafeDeleteFile(fso, strFile);
				
				var bOpen = false;
				if(AddItemFile)
					bOpen = true;
				else if (DoOpenFile(strTarget))
					bOpen = true;

				if(bOpen)
				{
					var window = projfile.Open(vsViewKindPrimary);
					window.visible = true;
				}
			}			
		}
		strTextStream.Close();			
	}
	catch(e)
	{
		strTextStream.Close();
		throw e;
 	}
}

function DoOpenFile(strName)
{
	var bOpen = false;
    
	if (strName == wizard.FindSymbol("FILENAME"))
		bOpen = true;

	return bOpen; 
}

function GetTargetName(strName, strProjectName)
{
	return strName;	
}
