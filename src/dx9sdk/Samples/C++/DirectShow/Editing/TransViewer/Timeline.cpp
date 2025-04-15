//------------------------------------------------------------------------------
// File: Timeline.cpp
//
// Desc: DirectShow sample code - TransViewer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "transviewer.h"
#include "Timeline.h"
#include "PropSetter.h"


//-----------------------------------------------------------------------------
// Name: CTimeline
// Desc: Constructor
//-----------------------------------------------------------------------------

CTimeline::CTimeline()
        : m_rtClipStop(5 * UNITS), 
          m_rtTransLength(5 * UNITS)
{
}


//-----------------------------------------------------------------------------
// Name: ~CTimeline
// Desc: Destructor
//-----------------------------------------------------------------------------

CTimeline::~CTimeline()
{
    m_TransList.clear(); 

    if (m_pTL)
    {
        m_pTL->ClearAllGroups();
        m_pTL = NULL;
    }   

    if (m_pRenderEngine)
    {
        m_pRenderEngine->ScrapIt();
        m_pRenderEngine = NULL;
    }
}


//-----------------------------------------------------------------------------
// Name: InitTransitionList
// Desc: Enumerates the transitions on the user's system, fills the
//       Transitions list box with the names, and stores the CLSIDs for later.
//-----------------------------------------------------------------------------

HRESULT CTimeline::InitTransitionList(HWND hListBox)
{
    HRESULT hr;
    int iCurrent = 0, iNumTransitions = 0;

    CComPtr<ICreateDevEnum> pSysDevEnum;
    hr = pSysDevEnum.CoCreateInstance(CLSID_SystemDeviceEnum);

    if (FAILED(hr)) {
        return hr;
    }

    CComPtr<IEnumMoniker> pEnumCat;
    hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoEffects2Category, &pEnumCat, 0);

    if (FAILED(hr)) {
        return hr;
    }

    CComPtr<IMoniker> pMoniker;

    while (pEnumCat->Next(1, &pMoniker, NULL) == S_OK)
    {
        CComPtr<IPropertyBag> pPropBag;
        hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag);

        if (FAILED(hr)) {
            continue;    // Maybe the next one will work
        }

        // Find the friendly name and add it to the combo box
        CComVariant varName, varGuid;

        CLSID clsid;
        varName.vt = VT_BSTR;
        varGuid.vt = VT_BSTR;

        hr = pPropBag->Read(L"FriendlyName", &varName, 0);
        {
            USES_CONVERSION;
            iCurrent = (int) SendMessage(hListBox, LB_ADDSTRING, 0, 
                                        (LPARAM) OLE2T(varName.bstrVal));
        }

        // Find the CLSID and add it to the global list
        hr = pPropBag->Read(L"guid", &varGuid, NULL);

        CLSIDFromString(varGuid.bstrVal, &clsid);
        m_TransList.insert(m_TransList.begin() + iCurrent, clsid);

        pPropBag = 0;
        pMoniker = 0;
    }

    // Select the first transition in the list
    SendMessage(hListBox, LB_SETCURSEL, 0, 0);
    SetTransition(0);

    return hr;
}


//-----------------------------------------------------------------------------
// Name: InitTimeline
// Desc: Creates the timeline and populates it. 
//-----------------------------------------------------------------------------

HRESULT CTimeline::InitTimeline(RECT& VideoRect)
{
    HRESULT hr;

    // Create an empty timeline.
    hr = m_pTL.CoCreateInstance(CLSID_AMTimeline);

    if (FAILED(hr)) {
        return hr;
    }

    // Cache the IAMSetErrorLog pointer
    m_pTL.QueryInterface(&m_pSetErr);

    // GROUP: Add a video group to the timeline. 
    CComPtr<IAMTimelineObj> pGroupObj;
    hr = m_pTL->CreateEmptyNode(&pGroupObj, TIMELINE_MAJOR_TYPE_GROUP);

    CComQIPtr<IAMTimelineGroup> pGroup(pGroupObj);
    
    // Set the group media type. Use the specified rectangle dimensions, RGB 555 format
    AM_MEDIA_TYPE mtGroup;  
    ZeroMemory(&mtGroup, sizeof(AM_MEDIA_TYPE));
    mtGroup.majortype  = MEDIATYPE_Video;
    mtGroup.subtype    = MEDIASUBTYPE_RGB555;
    mtGroup.formattype = FORMAT_VideoInfo;
    mtGroup.bFixedSizeSamples = TRUE;
    mtGroup.pbFormat   = (BYTE *)CoTaskMemAlloc(sizeof(VIDEOINFOHEADER));
    
    // Verify that CoTaskMemAlloc was successful
    if (mtGroup.pbFormat == NULL)
        return E_OUTOFMEMORY;
        
    mtGroup.cbFormat = sizeof(VIDEOINFOHEADER);
    ZeroMemory(mtGroup.pbFormat, mtGroup.cbFormat);

    // The HEADER macro returns the BITMAPINFO within the VIDEOINFOHEADER
    BITMAPINFOHEADER *pbmi = HEADER(mtGroup.pbFormat);
    pbmi->biSize        = sizeof(BITMAPINFOHEADER);
    pbmi->biCompression = BI_RGB;
    pbmi->biBitCount    = 16;
    pbmi->biWidth       = VideoRect.right;
    pbmi->biHeight      = VideoRect.bottom;
    pbmi->biPlanes      = 1;
    pbmi->biSizeImage   = DIBSIZE(*pbmi);
    mtGroup.lSampleSize = DIBSIZE(*pbmi);
    hr = pGroup->SetMediaType(&mtGroup);

    // Now add the group to the timeline
    hr = m_pTL->AddGroup(pGroupObj);

    // Add the rest of the timeline objects...
    CComPtr<IAMTimelineComp> pComp1, pComp2;
    CComPtr<IAMTimelineTrack> pTrack1, pTrack2, pTrack3, pTrack4;

    // COMPOSITION: Add two compositions to the group. 
    hr = AddCompToGroup(pGroup, &pComp1);
    hr = AddCompToGroup(pGroup, &pComp2);

    // TRACK: Add two tracks to each composition.
    hr = AddTrackToComp(pComp1, &pTrack1);
    hr = AddTrackToComp(pComp1, &pTrack2);

    hr = AddTrackToComp(pComp2, &pTrack3);
    hr = AddTrackToComp(pComp2, &pTrack4);

    // SOURCE: Add a source to each track. Do not set any properties yet.
    hr = AddSourceToTrack(pTrack1, &m_pSource1);
    hr = AddSourceToTrack(pTrack3, &m_pSource2);

    hr = AddSourceToTrack(pTrack2, &m_pColor1, RESIZEF_STRETCH);  
    hr = AddSourceToTrack(pTrack4, &m_pColor2, RESIZEF_STRETCH);
    
    // TRANSITION: Add the transition to track 2
    hr = m_pTL->CreateEmptyNode(&m_pTrans, TIMELINE_MAJOR_TYPE_TRANSITION);
    
    if (SUCCEEDED(hr))
    {   
        // Insert the transition object into the timeline. 
        CComQIPtr<IAMTimelineTransable> pTransable(pComp2);
        hr = pTransable->TransAdd(m_pTrans);  
        hr = m_pTrans->SetStartStop(0, m_rtTransLength); 

        // Default to the first transition on the list
        SetTransition(0);
    }

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: AddCompToGroup
// Desc: Adds a new composition to a group. Returns the IAMTimelineComp pointer.
//-----------------------------------------------------------------------------

HRESULT CTimeline::AddCompToGroup(IAMTimelineGroup *pGroup, IAMTimelineComp **ppComp)
{
    _ASSERTE(ppComp != NULL);

    *ppComp = NULL;

    // Create a composition object
    CComPtr<IAMTimelineObj> pCompObj;
    HRESULT hr = m_pTL->CreateEmptyNode(&pCompObj, TIMELINE_MAJOR_TYPE_COMPOSITE);

    if (FAILED(hr)) {
        return hr;
    }

    // We need the group's composition interface ...

    CComQIPtr<IAMTimelineComp> pGroupComp(pGroup);
    _ASSERTE(pGroupComp);

    hr = pGroupComp->VTrackInsBefore(pCompObj, -1);
    if (SUCCEEDED(hr))
    {
        // Return an AddRef's IAMTimelineComp pointer
        hr = pCompObj->QueryInterface(IID_IAMTimelineComp, (void **)ppComp);
    }

    return hr;
}


//-----------------------------------------------------------------------------
// Name: AddTrackToComp
// Desc: Adds a new track to a composition. Returns the IAMTimelineTrack pointer.
//-----------------------------------------------------------------------------

HRESULT CTimeline::AddTrackToComp(IAMTimelineComp *pComp, IAMTimelineTrack **ppTrack)
{
    _ASSERTE(ppTrack != NULL);
    *ppTrack = NULL;

    CComPtr<IAMTimelineObj> pTrackObj;
    HRESULT hr = m_pTL->CreateEmptyNode(&pTrackObj, TIMELINE_MAJOR_TYPE_TRACK);

    if (FAILED(hr)) {
        return hr;
    }

    hr = pComp->VTrackInsBefore(pTrackObj, -1); // append to the end of the track list
    if (SUCCEEDED(hr))
    {
        // Return an AddRef'd IAMTimelineTrack pointer
        hr = pTrackObj->QueryInterface(IID_IAMTimelineTrack, (void **)ppTrack);
    }

    return hr;
}


//-----------------------------------------------------------------------------
// Name: AddSourceToTrack
// Desc: Adds a new source to a track. Returns the IAMTimelineObj pointer.
//-----------------------------------------------------------------------------

HRESULT CTimeline::AddSourceToTrack(IAMTimelineTrack *pTrack, 
                                    IAMTimelineObj **ppSourceObj, int nStretchMode)
{
    _ASSERTE(ppSourceObj != NULL);
    *ppSourceObj = NULL;

    HRESULT hr = m_pTL->CreateEmptyNode(ppSourceObj, TIMELINE_MAJOR_TYPE_SOURCE);
    
    if (FAILED(hr)) {
        return hr;
    }

    (*ppSourceObj)->SetStartStop(0, m_rtClipStop);

    CComQIPtr<IAMTimelineSrc> pSource(*ppSourceObj);
    hr = pSource->SetStretchMode(nStretchMode);

    hr = pTrack->SrcAdd(*ppSourceObj);

    return hr;
}


//-----------------------------------------------------------------------------
// Name: SetTransition
// Desc: Sets the transition object from the current listbox selection
//-----------------------------------------------------------------------------

HRESULT CTimeline::SetTransition(int n)
{
    if ((n < 0) || (n >= (int) m_TransList.size()))
    {
        return E_INVALIDARG;
    }

    HRESULT hr = m_pTrans->SetSubObjectGUID(m_TransList[n]); 

    return hr;
}


//-----------------------------------------------------------------------------
// Name: SetFileName
// Desc: Sets the file name on the source object.
//       
//        nSource: Index of the source in the timeline (1 or 2)
//        szFileName: Name of the source file
//-----------------------------------------------------------------------------

HRESULT CTimeline::SetFileName(int nSource, const TCHAR* szFileName)
{
    HRESULT hr;

    CComPtr<IAMTimelineObj> pSourceObj = (nSource == 1 ? m_pSource1 : m_pSource2); 
    CComQIPtr<IAMTimelineSrc> pSource(pSourceObj);

    _ASSERTE(pSource != 0);

    CComBSTR bstrFileName(szFileName);

    hr = pSource->SetMediaName(bstrFileName);

    // If the source clip is too short, it will generate a rendering error.
    // That's OK for this sample.
    hr = pSource->SetMediaTimes(0, m_rtClipStop);

    if (nSource == 1) 
    {
        m_pColor1->SetMuted(TRUE);
    }
    else
    {
        m_pColor2->SetMuted(TRUE);
    }

    if (pSourceObj)
        pSourceObj->SetMuted(FALSE);

    return hr;
}


HRESULT CTimeline::SetSolidColor(int nSource, COLORREF color)
{
    HRESULT hr;

    CComPtr<IAMTimelineObj> pSourceObj = (nSource == 1 ? m_pColor1 : m_pColor2); 

    // Convert B-G-R format to RGB
    DWORD dwColor = SwapRGB(color);


    if (nSource == 1) {
        m_pSource1->SetMuted(TRUE);
    }
    else {
        m_pSource2->SetMuted(TRUE);
    }

    // Set the color on the color source object
    hr = pSourceObj->SetSubObjectGUID(CLSID_ColorSource);

    CComPtr<IPropertySetter> pProp;
    hr = pSourceObj->GetPropertySetter(&pProp);

    if (FAILED(hr) || (pProp == 0))
    {
        hr = pProp.CoCreateInstance(CLSID_PropertySetter);
        if (SUCCEEDED(hr))
        {
            hr = pSourceObj->SetPropertySetter(pProp);
        }
    }

    if (SUCCEEDED(hr))
    {
        DEXTER_PARAM param;
        DEXTER_VALUE val;
        
        param.Name = SysAllocString(L"Color");
        param.dispID = 0;
        param.nValues = 1;
        
        val.v.vt = VT_I4;
        val.v.lVal = dwColor;
        val.rt = 0;  // Time must be zero.
        val.dwInterp = DEXTERF_JUMP;

        hr = pProp->AddProp(param, &val);

        // Clean up
        if (param.Name != NULL)
            SysFreeString(param.Name);
        VariantClear(&val.v);
    }

    pSourceObj->SetMuted(FALSE);
    return hr;
}


// Preview a timeline.
HRESULT CTimeline::RenderTimeline() 
{
    HRESULT hr;

    // Create the render engine if there isn't one already.
    if (!m_pRenderEngine)
    {       
        hr = m_pRenderEngine.CoCreateInstance(CLSID_RenderEngine);
        if (FAILED(hr)) {
            return hr;
        }

        hr = m_pRenderEngine->SetTimelineObject(m_pTL); 
    }
    
    hr = m_pRenderEngine->ConnectFrontEnd( );


    if (hr == (HRESULT) S_WARN_OUTPUTRESET)
    {
        hr = m_pRenderEngine->RenderOutputPins( );
    }

    return hr;
}


HRESULT CTimeline::SetProperties(HINSTANCE hinst, HWND hwnd)
{
    CBasePropSetter *pProp = 0;

    GUID guid;
    m_pTrans->GetSubObjectGUID(&guid);

    if (guid == CLSID_DxtJpeg)
    {
        pProp = new CWipeProp(m_pTrans);
    }
    else if (guid == CLSID_DxtKey)
    {
        pProp = new CKeyProp(m_pTrans);
    }
    else if (guid == CLSID_DxtCompositor)
    {
        pProp = new CPipProp(m_pTrans);
    }
    else  // Default, use generic property setter dialog
    {
        pProp = new CPropSetter(m_pTrans);
    }

    if (pProp)
    {
        if (pProp->ShowDialog(hinst, hwnd))
        {
            pProp->SetProperties();
        }

        delete pProp;
        return S_OK;
    }
    else
        return E_FAIL;

}


