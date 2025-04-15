//------------------------------------------------------------------------------
// File: MediaTypes.h
//
// Desc: DirectShow sample code - hardware/project-specific support for
//       StillView application.
//
// Copyright (c) 1998 - 2002 Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

//
// Structures
//
typedef struct _media_info
{
    LPTSTR pszType;
    LPTSTR pszName;

} MEDIA_INFO, *PMEDIA_INFO;

//
// Some projects support different types of DirectShow media
//
#define DEFAULT_SEARCH_PATH   TEXT("\\\0")

#define NUM_MEDIA_TYPES   5

const MEDIA_INFO TypeInfo[NUM_MEDIA_TYPES] = {
      {TEXT("*.bmp\0"),  TEXT("Bitmap\0")       },
      {TEXT("*.jpg\0"),  TEXT("JPEG Image\0")   },
      {TEXT("*.jpeg\0"), TEXT("JPEG Image\0")   },
      {TEXT("*.gif\0"),  TEXT("GIF Image\0")    },
      {TEXT("*.tga\0"),  TEXT("Targa File\0")   },
};

