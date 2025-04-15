// ---------------------------------------------------------------------------
// File: CPoster.h
// 
// CPosterImage: Manages a preview image, which can be a bitmap or a solid 
//               color. It uses the IMediaDet interface to get bitmaps from
//               video source files.
//      
// Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#ifndef _CPOSTER_H
#define _CPOSTER_H


class CPosterImage
{

private:

    IMediaDet   *m_pDet;
    
    long        m_width;    // Display dimensions
    long        m_height;

    HWND        m_hwnd;     // Window in which to display the image
    HBITMAP     m_hBitmap;  // Bitmap to display
    COLORREF    m_Color;    // Color to display
    BOOL        m_bHasBitmap;   // If true, display the bitmap. (If not, the color)

public:

    CPosterImage(HWND hwnd);
    ~CPosterImage();
        
    HRESULT SetBitmap(const TCHAR* szFileName);
    HRESULT SetColor(COLORREF);
    HRESULT GetColor(COLORREF*);
    HRESULT Draw();
};


#endif // _CPOSTER_H