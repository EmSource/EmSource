//------------------------------------------------------------------------------
// File: Bitmap.cpp
//
// Desc: DirectShow sample code - Bitmap manipulation routines for 
//       VMR alpha-blended bitmap
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <dshow.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <tchar.h>
#include <atlbase.h>

#include "text.h"
#include "bitmap.h"

//
// Constants
//
const float X_EDGE_BUFFER=0.05f; // Pixel buffer between bitmap and window edge
                                 // (represented in composition space [0 - 1.0f])
const float Y_EDGE_BUFFER=0.05f;

const int UPDATE_TIMER   = 2000;
const int UPDATE_TIMEOUT = 2000; // 2 seconds between ticker movements

//
// Global data
//
IVMRMixerBitmap9 *pBMP = NULL;
TCHAR g_szAppText[DYNAMIC_TEXT_SIZE]={0};
int gnTimer=0;

float g_fBitmapCompWidth=0;  // Width of bitmap in composition space units
int g_nImageWidth=0;         // Width of text bitmap

// Text font information
HFONT g_hFont=0;
LONG g_lFontPointSize   = DEFAULT_FONT_SIZE;
COLORREF g_rgbColors    = DEFAULT_FONT_COLOR;
TCHAR g_szFontName[100] = {DEFAULT_FONT_NAME};
TCHAR g_szFontStyle[32] = {DEFAULT_FONT_STYLE};

// Destination rectangle used for alpha-blended text
VMR9NormalizedRect  g_rDest={0};


HRESULT BlendText(HWND hwndApp, TCHAR *szNewText)
{
    LONG cx, cy;
    HRESULT hr;

    // Read the default video size
    hr = pWC->GetNativeVideoSize(&cx, &cy, NULL, NULL);
    if (FAILED(hr))
    {
        Msg(TEXT("GetNativeVideoSize FAILED!  hr=0x%x\r\n"), hr);
        return hr;
    }

    // Create a device context compatible with the current window
    HDC hdc = GetDC(hwndApp);
    HDC hdcBmp = CreateCompatibleDC(hdc);

    // Write with a known font by selecting it into our HDC
    HFONT hOldFont = (HFONT) SelectObject(hdcBmp, g_hFont);

    // Determine the length of the string, then determine the
    // dimensions (in pixels) of the character string using the
    // currently selected font.  These dimensions are used to create
    // a bitmap below.
    int nLength, nTextBmpWidth, nTextBmpHeight;
    SIZE sz={0};
    nLength = (int) _tcslen(szNewText);
    GetTextExtentPoint32(hdcBmp, szNewText, nLength, &sz);
    nTextBmpHeight = sz.cy;
    nTextBmpWidth  = sz.cx;

    // Create a new bitmap that is compatible with the current window
    HBITMAP hbm = CreateCompatibleBitmap(hdc, nTextBmpWidth, nTextBmpHeight);
    ReleaseDC(hwndApp, hdc);

    // Select our bitmap into the device context and save the old one
    BITMAP bm;
    HBITMAP hbmOld;
    GetObject(hbm, sizeof(bm), &bm);
    hbmOld = (HBITMAP)SelectObject(hdcBmp, hbm);

    // Set initial bitmap settings
    RECT rcText;
    SetRect(&rcText, 0, 0, nTextBmpWidth, nTextBmpHeight);
    SetBkColor(hdcBmp, RGB(255, 255, 255)); // Pure white background
    SetTextColor(hdcBmp, g_rgbColors);      // Write text with requested color

    // Draw the requested text string onto the bitmap
    TextOut(hdcBmp, 0, 0, szNewText, nLength);

    // Configure the VMR's bitmap structure
    VMR9AlphaBitmap bmpInfo;
    ZeroMemory(&bmpInfo, sizeof(bmpInfo) );
    bmpInfo.dwFlags = VMRBITMAP_HDC;
    bmpInfo.hdc = hdcBmp;  // DC which has selected our bitmap

    // Remember the width of this new bitmap
    g_nImageWidth = bm.bmWidth;

    // Save the ratio of the bitmap's width to the width of the video file.
    // This value is used to reposition the bitmap in composition space.
    g_fBitmapCompWidth = (float)g_nImageWidth / (float)cx;

    // Display the bitmap in the bottom right corner.
    // rSrc specifies the source rectangle in the GDI device context 
    // rDest specifies the destination rectangle in composition space (0.0f to 1.0f)
    bmpInfo.rDest.left  = 0.0f + X_EDGE_BUFFER;
    bmpInfo.rDest.right = 1.0f - X_EDGE_BUFFER;
    bmpInfo.rDest.top = (float)(cy - bm.bmHeight) / (float)cy - Y_EDGE_BUFFER;
    bmpInfo.rDest.bottom = 1.0f - Y_EDGE_BUFFER;
    bmpInfo.rSrc = rcText;

    // Transparency value 1.0 is opaque, 0.0 is transparent.
    bmpInfo.fAlpha = TRANSPARENCY_VALUE;

    // Set the COLORREF so that the bitmap outline will be transparent
    SetColorRef(bmpInfo);

    // Give the bitmap to the VMR for display
    hr = pBMP->SetAlphaBitmap(&bmpInfo);
    if (FAILED(hr))
        Msg(TEXT("SetAlphaBitmap FAILED!  hr=0x%x\r\n\r\n%s\0"), hr,
            STR_VMR_DISPLAY_WARNING);

    // Select the initial objects back into our device context
    DeleteObject(SelectObject(hdcBmp, hbmOld));
    SelectObject(hdc, hOldFont);

    // Clean up resources
    DeleteObject(hbm);
    DeleteDC(hdcBmp);

    return hr;
}

void UpdateText(void)
{
    static int nCurrentTextLine=0;
    const int MAX_TEXT_LINES=5;

    static TCHAR szText[MAX_TEXT_LINES][80]  = {
        TEXT("Introducing the Video Mixing Renderer 9,"),
        TEXT("only available with Microsoft DirectX 9!"),
        TEXT("The VMR9 supports multiple video streams"),
        TEXT("and a static bitmap, all of which"),
        TEXT("can be mixed with alpha blending.")
    };

    // Update the text string
    BlendText(ghApp, szText[nCurrentTextLine]);

    // Advance to the next string in the list
    nCurrentTextLine++;

    // Wrap around to beginning of list
    if (nCurrentTextLine >= MAX_TEXT_LINES)
        nCurrentTextLine=0;
}

void SetColorRef(VMR9AlphaBitmap& bmpInfo)
{
    // Set the COLORREF so that the bitmap outline will be transparent
    bmpInfo.clrSrcKey = RGB(255, 255, 255);  // Pure white
    bmpInfo.dwFlags |= VMRBITMAP_SRCCOLORKEY;
}

HFONT UserSelectFont( void ) 
{
    // Allow the user to specify the text font to use with
    // dynamic text.  Display the Windows ChooseFont() dialog.
    return (SetTextFont(TRUE));
}

HFONT SetTextFont(BOOL bShowDialog) 
{ 
    CHOOSEFONT cf={0}; 
    LOGFONT lf={0}; 
    HFONT hfont; 
    HDC hdc;
    LONG lHeight;

    // Convert requested font point size to logical units
    hdc = GetDC( ghApp );
    lHeight = -MulDiv( g_lFontPointSize, GetDeviceCaps(hdc, LOGPIXELSY), 72 );
    ReleaseDC( ghApp, hdc );

    // Initialize members of the LOGFONT structure. 
    lstrcpyn(lf.lfFaceName, g_szFontName, 32);
    lf.lfHeight = lHeight;      // Logical units

    // Prevent font smoothing, which could distort the text and leave
    // white pixels on the edges.  Disabling antialiasing leads to 
    // smoother text in this context.
    lf.lfQuality = NONANTIALIASED_QUALITY;

    // Initialize members of the CHOOSEFONT structure. 
    cf.lStructSize = sizeof(CHOOSEFONT); 
    cf.hwndOwner   = ghApp; 
    cf.hDC         = (HDC)NULL; 
    cf.lpLogFont   = &lf; 
    cf.iPointSize  = g_lFontPointSize * 10; 
    cf.rgbColors   = g_rgbColors; 
    cf.lCustData   = 0L; 
    cf.lpfnHook    = (LPCFHOOKPROC)NULL; 
    cf.hInstance   = (HINSTANCE) NULL; 
    cf.lpszStyle   = g_szFontStyle; 
    cf.nFontType   = SCREEN_FONTTYPE; 
    cf.nSizeMin    = 0; 
    cf.lpTemplateName = NULL; 
    cf.Flags = CF_SCREENFONTS | CF_SCALABLEONLY | CF_INITTOLOGFONTSTRUCT | 
               CF_EFFECTS     | CF_USESTYLE     | CF_LIMITSIZE; 

    // Limit font size to prevent bitmap from becoming too wide
    cf.nSizeMax = MAX_FONT_SIZE; 
 
    // If we previously changed a pure white font to 'almost white'
    // to support writing white text over a white colorkey, then
    // configure the font dialog for pure white text.
    if (cf.rgbColors == ALMOST_WHITE)
        cf.rgbColors = PURE_WHITE;

    // Display the CHOOSEFONT common-dialog box.  When it closes,
    // the CHOOSEFONT structure members will be updated.
    if (bShowDialog)
        ChooseFont(&cf); 

    // Save the user's selections for configuring the dialog box next time.
    // The style is automatically saved in g_szFontStyle (cf.lpszStyle)
    lstrcpyn(g_szFontName, lf.lfFaceName, NUMELMS(g_szFontName));
    g_lFontPointSize = cf.iPointSize / 10;  // Specified in 1/10 point units
    g_rgbColors = cf.rgbColors;

    // Because we use a white colorkey to introduce transparency behind
    // our text, drawing white text will cause it to be transparent.
    // Therefore, filter out pure white (RGB(255,255,255)).
    if (g_rgbColors == PURE_WHITE)
        g_rgbColors = ALMOST_WHITE;

    // Create a logical font based on the user's selection and 
    // return a handle identifying that font.  
    hfont = CreateFontIndirect(cf.lpLogFont); 
    return (hfont); 
} 

void StartTimer(void)
{
    gnTimer = (int) SetTimer(NULL, UPDATE_TIMER, UPDATE_TIMEOUT, TimerProc);
}

void StopTimer(void)
{
    if (gnTimer)
    {
        KillTimer(NULL, gnTimer);
        gnTimer = 0;
    }
}

VOID CALLBACK TimerProc(
  HWND hwnd,         // handle to window
  UINT uMsg,         // WM_TIMER message
  UINT_PTR idEvent,  // timer identifier
  DWORD dwTime       // current system time
)
{
    // Draw a new line of text over the video in the main window
    UpdateText();
}

