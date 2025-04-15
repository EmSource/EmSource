//------------------------------------------------------------------------------
// File: CPoster.cpp
//
// Desc: DirectShow sample code - TransViewer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "transviewer.h"
#include "CPoster.h"


//-----------------------------------------------------------------------------
// Name: CPosterImage
// Desc: Constructor
//
// hwnd: Handle to the window that will display the preview image.
//-----------------------------------------------------------------------------

CPosterImage::CPosterImage(HWND hwnd) :
      m_pDet(NULL),
      m_bHasBitmap(FALSE),
      m_Color(RGB(0,0,0))
{
    RECT rc={0};

    _ASSERT(IsWindow(hwnd));
    m_hwnd = hwnd;

    // Get the window dimensions.
    GetClientRect(hwnd, &rc);
    m_width  = rc.right;
    m_height = rc.bottom;
}   


//-----------------------------------------------------------------------------
// Name: CPosterImage
// Desc: Destructor
//-----------------------------------------------------------------------------

CPosterImage::~CPosterImage()
{
    DeleteObject(m_hBitmap);

    if (m_pDet)
    {
        m_pDet->Release();
        m_pDet = NULL;
    }
}


//-----------------------------------------------------------------------------
// Name: SetColor
// Desc: Sets the preview image to a solid color.
//
// color: Specifies the color value.
//-----------------------------------------------------------------------------

HRESULT CPosterImage::SetColor(COLORREF color)
{
    m_Color = color;

    // Get rid of any bitmap we might be holding.
    m_bHasBitmap = FALSE;
    DeleteObject(m_hBitmap);

    Draw();
    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: GetColor
// Desc: Retrieves the color value that was last set.
//
// pColor: Receives the color value.
//
// Return value: S_OK if the preview is currently using this color,
//               S_FALSE if the preview is now a bitmap
//-----------------------------------------------------------------------------

HRESULT CPosterImage::GetColor(COLORREF *pColor)
{
    CheckPointer(pColor, E_POINTER);
    
    *pColor = m_Color;

    return (m_bHasBitmap ? S_FALSE : S_OK);
}


//-----------------------------------------------------------------------------
// Name: SetBitmap
// Desc: Sets the preview image to a bitmap, taken from a video source.
//
// szFileName: Specifies the name of the video source file
//-----------------------------------------------------------------------------

HRESULT CPosterImage::SetBitmap(const TCHAR* szFileName)
{
    HRESULT hr;
    long lStream;

    CheckPointer(szFileName, E_POINTER);

    m_bHasBitmap = FALSE;
    DeleteObject(m_hBitmap);
    
    // We use IMediaDet to get the bitmap. The IMediaDet object is a "one-shot".
    // Once you have used it to grab a bitmap, you can't switch it to another
    // file.  Therefore, we create a new one each time.
    if (m_pDet)
    {
        m_pDet->Release();
        m_pDet = NULL;
    }

    hr = CoCreateInstance(CLSID_MediaDet, NULL, CLSCTX_INPROC, IID_IMediaDet, (void**)&m_pDet);
    if (FAILED(hr)) {
        return hr;
    }

    // Set the file name
    CComBSTR bstrFileName(szFileName);

    hr = m_pDet->put_Filename(bstrFileName);
    if (FAILED(hr)) {
        return hr;
    }

    // Get the number of streams in this file
    hr = m_pDet->get_OutputStreams(&lStream);
    if (FAILED(hr)) {
        return hr;
    }

    // Look for a video stream.
    bool bFound = false;
    for (long i = 0; i < lStream; i++)
    {
        GUID majortype;
        hr = m_pDet->put_CurrentStream(i);
        hr = m_pDet->get_StreamType(&majortype);

        if (majortype == MEDIATYPE_Video)
        {
            bFound = true;
            break;
        }
    }

    if (!bFound) {
        return VFW_E_INVALIDMEDIATYPE;
    }

    // We found a video stream. Now get the buffer size for the bitmap.
    long size;
    hr = m_pDet->GetBitmapBits(0, &size, 0, m_width, m_height);
    
    if (SUCCEEDED(hr)) 
    {
        // Allocate and fill the buffer
        char *pBuffer = new char[size];
        
        if (!pBuffer)
            return E_OUTOFMEMORY;

        try {   

            hr = m_pDet->GetBitmapBits(0, 0, pBuffer, m_width, m_height);
        }
        
        catch (...) {
            delete [] pBuffer;
            return E_FAIL;
        }
    
        if (SUCCEEDED(hr))
        {
            // The buffer contains the BITMAPINFOHEADER followed by the bitmap bits.
            // Use this to create a GDI bitmap

            BITMAPINFOHEADER *bmih = (BITMAPINFOHEADER*)pBuffer;
            void *pData = pBuffer + sizeof(BITMAPINFOHEADER);

            HDC hdcDest = GetDC(0);
            
            BITMAPINFO bmi;
            ZeroMemory(&bmi, sizeof(BITMAPINFO));
            CopyMemory(&(bmi.bmiHeader), bmih, sizeof(BITMAPINFOHEADER));
            
            m_hBitmap = CreateDIBitmap(hdcDest,  bmih, CBM_INIT, pData, &bmi, DIB_RGB_COLORS);
            m_bHasBitmap = (m_hBitmap != NULL);
        }

        delete[] pBuffer;
        
    }

    return hr;
}


//-----------------------------------------------------------------------------
// Name: Draw
// Desc: Draws the preview image.
//-----------------------------------------------------------------------------

HRESULT CPosterImage::Draw()
{
    PAINTSTRUCT ps;
    BeginPaint(m_hwnd, &ps);

    HDC hdc = GetDC(m_hwnd);
    
    if (m_bHasBitmap)
    {
        HDC hdcMem = CreateCompatibleDC(hdc);
        
        SelectObject(hdcMem, m_hBitmap);
        BitBlt(hdc, 0, 0, m_width, m_height, hdcMem, 0, 0, SRCCOPY);
        
        DeleteDC(hdcMem);
    }   
    else // Paint a solid color
    {
        HBRUSH hBrush = CreateSolidBrush(m_Color);
        HBRUSH hPrev = (HBRUSH)SelectObject(hdc, hBrush);

        Rectangle(hdc, 0, 0, m_width, m_height);
        SelectObject(hdc, hPrev);
        DeleteObject(hBrush);
    }

    ReleaseDC(m_hwnd, hdc);    
    EndPaint(m_hwnd, &ps);
    
    return S_OK;
}

