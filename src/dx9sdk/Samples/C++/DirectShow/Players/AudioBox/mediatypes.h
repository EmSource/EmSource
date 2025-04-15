//------------------------------------------------------------------------------
// File: MediaTypes.h
//
// Desc: DirectShow sample code - hardware/project-specific support for
//       Audio Jukebox application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
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

#define NUM_MEDIA_TYPES   12

const MEDIA_INFO TypeInfo[NUM_MEDIA_TYPES] = {
      {TEXT("*.wma\0"),  TEXT("Windows Audio\0")},  /* Windows Media Audio */
      {TEXT("*.mp3\0"),  TEXT("MP3 audio\0")    },  /* MPEG-1 Layer III */
      {TEXT("*.wav\0"),  TEXT("WAV audio\0")    },
      {TEXT("*.au\0"),   TEXT("AU audio\0")     },
      {TEXT("*.aif*\0"), TEXT("AIFF audio\0")   },  /* AIF, AIFF, AIFC */
      {TEXT("*.snd\0"),  TEXT("SND audio\0")    },
      {TEXT("*.mpa\0"),  TEXT("MPEG audio\0")   },  /* MPEG audio */
      {TEXT("*.mp1\0"),  TEXT("MPEG audio\0")   },  /* MPEG audio */
      {TEXT("*.mp2\0"),  TEXT("MPEG audio\0")   },  /* MPEG audio */
      {TEXT("*.mid\0"),  TEXT("MIDI\0")         },  /* MIDI       */
      {TEXT("*.midi\0"), TEXT("MIDI\0")         },  /* MIDI       */
      {TEXT("*.rmi\0"),  TEXT("MIDI\0")         },  /* MIDI       */
};

