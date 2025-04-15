//------------------------------------------------------------------------------
// File: MFCDMOUtil.h
//
// Desc: DirectShow sample code - Header for DMO utility functions 
//       used by MFC applications.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

//
//  Global data structure for storing GUIDs and friendly strings
//
typedef struct _dmo_category_info
{
    const GUID *pclsid;
    TCHAR szName[128];

} DMO_CATEGORY_INFO;


// The DirectShow reference documentation lists a set of DMO categories
// for which you can enumerate corresponding filters.  See 'Category GUIDs'
// under 'DirectShow->DirectX Media Objects->DMO Reference' in the SDK docs.
const DMO_CATEGORY_INFO dmo_categories[] = {
    
    &GUID_NULL,                  TEXT("All categories\0"),
    &DMOCATEGORY_AUDIO_DECODER,  TEXT("Audio Decoder\0"),
    &DMOCATEGORY_AUDIO_EFFECT,   TEXT("Audio Effect\0"),
    &DMOCATEGORY_AUDIO_ENCODER,  TEXT("Audio Encoder\0"),
    &DMOCATEGORY_VIDEO_DECODER,  TEXT("Video Decoder\0"),
    &DMOCATEGORY_VIDEO_EFFECT,   TEXT("Video Effect\0"),
    &DMOCATEGORY_VIDEO_ENCODER,  TEXT("Video Encoder\0"),
    &DMOCATEGORY_AUDIO_CAPTURE_EFFECT, TEXT("Audio Capture Effect\0"),
};

//
// Constants
//
#define NUM_CATEGORIES  (sizeof(dmo_categories) / sizeof(DMO_CATEGORY_INFO))
#define STR_CLASSES     TEXT("DMO Categories\0")
#define STR_FILTERS     TEXT("Registered DMOs\0")
#define STR_UNKNOWN     TEXT("<?>\0")
#define STR_NOTDMO      TEXT("---\0")

//
// Function prototypes
//
HRESULT EnumDMOsToList(IEnumDMO *pEnumCat, CListBox& ListFilters, int& nFilters);
HRESULT AddDMOsToList(const GUID *clsid, CListBox& ListFilters, BOOL bIncludeKeyed);

void DisplayDMOTypeInfo(const GUID *pCLSID, 
                        ULONG& ulNumInputsSupplied,  CListBox& ListInputTypes,
                        ULONG& ulNumOutputsSupplied, CListBox& ListOutputTypes);
