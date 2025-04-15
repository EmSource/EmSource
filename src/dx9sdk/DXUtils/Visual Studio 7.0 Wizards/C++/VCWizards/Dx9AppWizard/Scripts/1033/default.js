
function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfig(selProj, strProjectName);
		AddFilters(selProj);

		var InfFile = CreateCustomInfFile();
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		PchSettings(selProj);
		InfFile.Delete();

		selProj.Object.Save();
	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		strProjTemplate = strProjTemplatePath + '\\default.vcproj';

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

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.vcproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
	try
	{
		// Add the folders to your project
		var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
		var group = proj.Object.AddFilter('Source Files');
		group.Filter = strSrcFilter;
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{
		var bDirectPlay = wizard.FindSymbol("DPLAY");
		var bUseNonMFC = wizard.FindSymbol("WINDOW");
		
		var config = proj.Object.Configurations('Debug');
		config.IntermediateDirectory = 'Debug';
		config.OutputDirectory = 'Debug';

		var CLTool = config.Tools('VCCLCompilerTool');
		
		// Add MFC if using MFC
        if( bUseNonMFC )
        {
		    config.UseOfMFC = useMfcStdWin;
		    CLTool.RuntimeLibrary = rtMultiThreaded;
    	}
        else
        {
		    config.UseOfMFC = useMfcDynamic;              
    		CLTool.RuntimeLibrary = rtMultiThreadedDLL;
		}
		
        // Add _WIN32_DCOM if using DPlay
		var strDefines = GetPlatformDefine(config);	
	    strDefines += "_WINDOWS;_DEBUG";
        if( bDirectPlay )
		    strDefines += ";_WIN32_DCOM";
	    CLTool.PreprocessorDefinitions = strDefines;
		CLTool.TreatWChar_tAsBuiltInType = true;
		CLTool.WarningLevel = warningLevelOption.warningLevel_4;
		CLTool.DebugInformationFormat = debugEditAndContinue;
		CLTool.Optimization = optimizeDisabled;
		CLTool.OmitFramePointers = false;
		CLTool.InlineFunctionExpansion = expandDisable;
		CLTool.StringPooling = false;
		CLTool.EnableFunctionLevelLinking = true;
		CLTool.MinimalRebuild = true;
		CLTool.BasicRuntimeChecks = basicRuntimeCheckOption.runtimeBasicCheckAll;

		var LinkTool = config.Tools('VCLinkerTool');
        LinkTool.AdditionalDependencies = "dsound.lib dinput8.lib dxerr9.lib d3dx9.lib d3d9.lib d3dxof.lib dxguid.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib"
        LinkTool.SubSystem = subSystemWindows;
        LinkTool.GenerateDebugInformation = true;
        if( !bUseNonMFC )
            LinkTool.IgnoreDefaultLibraryNames = "MSVCRT";

		config = proj.Object.Configurations('Release');
		config.IntermediateDirectory = 'Release';
		config.OutputDirectory = 'Release';

		var CLTool = config.Tools('VCCLCompilerTool');
		
		// Add MFC if using MFC
        if( bUseNonMFC )
        {
		    config.UseOfMFC = useMfcStdWin;
		    CLTool.RuntimeLibrary = rtMultiThreaded;
    	}
        else
        {
		    config.UseOfMFC = useMfcDynamic;              
    		CLTool.RuntimeLibrary = rtMultiThreadedDLL
		}
		
        // Add _WIN32_DCOM if using DPlay
		var strDefines = GetPlatformDefine(config);	
	    strDefines += "_WINDOWS;NDEBUG";
        if( bDirectPlay )
		    strDefines += ";_WIN32_DCOM";
	    CLTool.PreprocessorDefinitions = strDefines;
		CLTool.InlineFunctionExpansion = expandOnlyInline;
		CLTool.MinimalRebuild = false;
		CLTool.TreatWChar_tAsBuiltInType = true;
		CLTool.WarningLevel = warningLevelOption.warningLevel_4;
		CLTool.DebugInformationFormat = debugEnabled;
		CLTool.Optimization = optimizeMaxSpeed;
		CLTool.OmitFramePointers = true;
		CLTool.InlineFunctionExpansion = expandOnlyInline;
		CLTool.StringPooling = true;
		CLTool.EnableFunctionLevelLinking = true;
		CLTool.MinimalRebuild = false;

		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalNo;
		LinkTool.AdditionalDependencies = "dsound.lib dinput8.lib dxerr9.lib d3dx9.lib d3d9.lib d3dxof.lib dxguid.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib"
        LinkTool.SubSystem = subSystemWindows;
        LinkTool.GenerateDebugInformation = false;
        if( !bUseNonMFC )
            LinkTool.IgnoreDefaultLibraryNames = "MSVCRT";
	}
	catch(e)
	{
		throw e;
	}
}

function PchSettings(proj)
{
	var bUseNonMFC = wizard.FindSymbol("WINDOW");
    if( !bUseNonMFC )
    {
		// setup /Yu (using precompiled headers)
		var configs = proj.Object.Configurations;
		config = configs("Debug");

		var CLTool = config.Tools("VCCLCompilerTool");
		CLTool.UsePrecompiledHeader = pchUseUsingSpecific;
		config = configs("Release");

		var CLTool = config.Tools("VCCLCompilerTool");
		CLTool.UsePrecompiledHeader = pchUseUsingSpecific;

		// setup /Yc (create precompiled header)
		var files = proj.Object.Files;
		file = files("StdAfx.cpp");

		config = file.FileConfigurations("Debug");
		config.Tool.UsePrecompiledHeader = pchCreateUsingSpecific;

		config = file.FileConfigurations("Release");
		config.Tool.UsePrecompiledHeader = pchCreateUsingSpecific;
	}
}

function DelFile(fso, strWizTempFile)
{
	try
	{
		if (fso.FileExists(strWizTempFile))
		{
			var tmpFile = fso.GetFile(strWizTempFile);
			tmpFile.Delete();
		}
	}
	catch(e)
	{
		throw e;
	}
}

function CreateCustomInfFile()
{
	try
	{
		var fso, TemplatesFolder, TemplateFiles, strTemplate;
		fso = new ActiveXObject('Scripting.FileSystemObject');

		var TemporaryFolder = 2;
		var tfolder = fso.GetSpecialFolder(TemporaryFolder);
		var strTempFolder = tfolder.Drive + '\\' + tfolder.Name;

		var strWizTempFile = strTempFolder + "\\" + fso.GetTempName();

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strInfFile = strTemplatePath + '\\Templates.inf';
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var WizTempFile = fso.GetFile(strWizTempFile);
		return WizTempFile;
	}
	catch(e)
	{
		throw e;
	}
}

function GetTargetName(strName, strProjectName)
{
	try
	{
		var strTarget = strName;
		var strSafeProjectName = wizard.FindSymbol("SAFE_PROJECT_NAME");
		if (strName.substr(0, 4) == "root")
		{
			var strlen = strName.length;
			strTarget = strProjectName + strName.substr(4, strlen - 4);
			return strTarget;
		}
		
		switch (strName)
		{
			case "readme.txt":
				strTarget = "ReadMe.txt";
				break;
				
			case "d3d_win\\d3d_win.cpp":
				strTarget = strProjectName + ".cpp";
			    break;
			case "d3d_win\\d3d_win.h":
				strTarget = strProjectName + ".h";
			    break;
			case "d3d_win\\d3d_win.rc":
				strTarget = strProjectName + ".rc";
			    break;
			case "d3d_win\\d3d_winres.h":
				strTarget = "resource.h";
			    break;
			    
			case "d3d_dlg\\d3d_dlg.cpp":
				strTarget = strProjectName + ".cpp";
			    break;
			case "d3d_dlg\\d3d_dlg.h":
				strTarget = strProjectName + ".h";
			    break;
			case "d3d_dlg\\d3d_dlg.rc":
				strTarget = strProjectName + ".rc";
			    break;
			case "d3d_dlg\\d3d_dlgres.h":
				strTarget = "resource.h";
			    break;
			case "d3d_dlg\\d3d_dlgStdAfx.cpp":
				strTarget = "StdAfx.cpp";
			    break;
			case "d3d_dlg\\d3d_dlgStdAfx.h":
				strTarget = "StdAfx.h";
			    break;
			    
			case "gdi_win\\gdi_win.cpp":
				strTarget = strProjectName + ".cpp";
			    break;
			case "gdi_win\\gdi_win.h":
				strTarget = strProjectName + ".h";
			    break;
			case "gdi_win\\gdi_win.rc":
				strTarget = strProjectName + ".rc";
			    break;
			case "gdi_win\\gdi_winres.h":
				strTarget = "resource.h";
			    break;
			    
			case "gdi_dlg\\gdi_dlg.cpp":
				strTarget = strProjectName + ".cpp";
			    break;
			case "gdi_dlg\\gdi_dlg.h":
				strTarget = strProjectName + ".h";
			    break;
			case "gdi_dlg\\gdi_dlg.rc":
				strTarget = strProjectName + ".rc";
			    break;
			case "gdi_dlg\\gdi_dlgres.h":
				strTarget = "resource.h";
			    break;
			case "gdi_dlg\\gdi_dlgStdAfx.cpp":
				strTarget = "StdAfx.cpp";
			    break;
			case "gdi_dlg\\gdi_dlgStdAfx.h":
				strTarget = "StdAfx.h";
			    break;
			    
			default:
				break;
		}

		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}


function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems;

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

		var strTpl = '';
		var strName = '';

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != '')
			{
				strName = strTpl;
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".wav" || strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
				proj.Object.AddFile(strFile);
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}
