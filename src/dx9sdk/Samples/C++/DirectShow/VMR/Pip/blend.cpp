//------------------------------------------------------------------------------
// File: Blend.cpp
//
// Desc: DirectShow sample code - Video manipulation routines for 
//       VMR alpha-blended streams
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include <dshow.h>
#include <tchar.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>
#include <atlbase.h>

#include "vmrpip.h"
#include "blend.h"

//
// Global data
//
int gnTimer=0, g_nSwapSteps=0, g_nSwapState=SWAP_NOTHING;

// Default initialization values for the video streams
const STRM_PARAM strParamInit[1] = {
    {0.0F, 0.0F, 1.0F, 1.0F, 1.0F, 0, 0, {0,0,0,0}}
};

// Initial and current values for the video streams
STRM_PARAM strParam[2] = {0}, strDelta[2] = {0};

// Coordinates (in composition space units) that specify each corner of
// the window for positioning the subpicture stream
const QUADRANT quad[4] = {
    X_EDGE_BUFFER, Y_EDGE_BUFFER, 
        SECONDARY_WIDTH, SECONDARY_HEIGHT,
    (1.0f - SECONDARY_WIDTH - X_EDGE_BUFFER), Y_EDGE_BUFFER, 
        SECONDARY_WIDTH, SECONDARY_HEIGHT,
    (1.0f - SECONDARY_WIDTH - X_EDGE_BUFFER), (1.0f - SECONDARY_HEIGHT - Y_EDGE_BUFFER), 
        SECONDARY_WIDTH, SECONDARY_HEIGHT,
    X_EDGE_BUFFER, (1.0f - SECONDARY_HEIGHT - Y_EDGE_BUFFER), 
        SECONDARY_WIDTH, SECONDARY_HEIGHT
};

int g_nCurrentQuadrant[2] = {0}, g_nSubpictureID = SECONDARY_STREAM;



void PositionStream(int nStream, int nQuadrant)
{
    strParam[nStream].xPos  = quad[nQuadrant].xPos;
    strParam[nStream].yPos  = quad[nQuadrant].yPos;
    strParam[nStream].xSize = quad[nQuadrant].xSize;
    strParam[nStream].ySize = quad[nQuadrant].ySize;

    // Reposition the selected stream
    UpdatePinPos(nStream);

    // Save the current quadrant of the selected stream
    g_nCurrentQuadrant[nStream] = nQuadrant;
}

void SetNextQuadrant(int nStream)
{
    int nNewQuadrant = (g_nCurrentQuadrant[nStream] + 1) % NUM_QUADRANTS;
    PositionStream(nStream, nNewQuadrant);
}

HRESULT UpdatePinAlpha(int nStreamID)
{
    HRESULT hr=S_OK;

    // Get a pointer to the selected stream's information
    STRM_PARAM* p = &strParam[nStreamID];

    // Update the alpha value for the selected stream
    if(pMix)
        hr = pMix->SetAlpha(nStreamID, p->fAlpha);

    return hr;
}

HRESULT UpdatePinZOrder(int nStreamID, DWORD dwZOrder)
{
    HRESULT hr=S_OK;

    // Update the alpha value for the selected stream
    if(pMix)
        hr = pMix->SetZOrder(nStreamID, dwZOrder);

    return hr;
}

HRESULT UpdatePinPos(int nStreamID)
{
    HRESULT hr=S_OK;

    // Get a pointer to the selected stream's information
    STRM_PARAM* p = &strParam[nStreamID];

    // Set the left, right, top, and bottom coordinates
    NORMALIZEDRECT r = {p->xPos, p->yPos, p->xPos + p->xSize, p->yPos + p->ySize};

    // If mirrored, swap the left/right coordinates in the destination rectangle
    if (strParam[nStreamID].bMirrored)
    {
        float fLeft = strParam[nStreamID].xPos;
        float fRight = strParam[nStreamID].xPos + strParam[nStreamID].xSize;
        r.left = fRight;
        r.right = fLeft;
    }

    // If flipped, swap the top/bottom coordinates in the destination rectangle
    if (strParam[nStreamID].bFlipped)
    {
        float fTop = strParam[nStreamID].yPos;
        float fBottom = strParam[nStreamID].yPos + strParam[nStreamID].ySize;
        r.top = fBottom;
        r.bottom = fTop;
    }

    // Update the destination rectangle for the selected stream
    if(pMix)
        hr = pMix->SetOutputRect(nStreamID, &r);

    return hr;
}

void InitStreamParams(void)
{
    // Set default values for X, Y, Width, Height and Alpha values
    // for both streams.
    CopyMemory(&strParam[PRIMARY_STREAM],   strParamInit, sizeof(strParamInit));
    CopyMemory(&strParam[SECONDARY_STREAM], strParamInit, sizeof(strParamInit));

    // Set the alpha value of the secondary stream to partially transparent
    strParam[1].fAlpha = TRANSPARENCY_VALUE;

    // Position the secondary stream in a small portion of the window
    PositionStream(SECONDARY_STREAM, DEFAULT_QUADRANT);
}

void AdjustVideo(int nStream, float fX, float fY, float fWidth, float fHeight)
{
    // Add positive or negative values to the X, Y, width, or height
    // of the selected video stream.
    strParam[nStream].xPos  += fX;
    strParam[nStream].yPos  += fY;
    strParam[nStream].xSize += fWidth;
    strParam[nStream].ySize += fHeight;

    // Apply the new coordinates and size
    UpdatePinPos(nStream);
}

void AdjustStreamRect(int nStream, STRM_PARAM *pStream)
{
    if (!pStream)
        return;

    // Add positive or negative values to the X, Y, width, or height
    // of the selected video stream.
    strParam[nStream].xPos  += pStream->xPos;
    strParam[nStream].yPos  += pStream->yPos;
    strParam[nStream].xSize += pStream->xSize;
    strParam[nStream].ySize += pStream->ySize;

    // Apply the new coordinates and size
    UpdatePinPos(nStream);
}

void AdjustAlpha(int nStream, STRM_PARAM *pStream)
{
    if (!pStream)
        return;

    // Add positive or negative values to the alpha value
    // of the selected video stream.
    strParam[nStream].fAlpha += pStream->fAlpha;

    // Apply the new coordinates and size
    UpdatePinAlpha(nStream);
}

void CenterStream(int nStream)
{
    // Set coordinates for small rectange in center of window
    strParam[nStream].xPos  = 0.3f;
    strParam[nStream].yPos  = 0.3f;
    strParam[nStream].xSize = 0.4f;
    strParam[nStream].ySize = 0.4f;

    // Apply the new coordinates and size
    UpdatePinPos(nStream);
}

void FlipStream(int nStream)
{
    strParam[nStream].bFlipped ^= 1;
    UpdatePinPos(nStream);
}

void MirrorStream(int nStream)
{
    strParam[nStream].bMirrored ^= 1;
    UpdatePinPos(nStream);
}

void SwapStreams(void)
{
    STRM_PARAM strSwap={0};

    // Swap stream information
    strSwap                    = strParam[PRIMARY_STREAM];
    strParam[PRIMARY_STREAM]   = strParam[SECONDARY_STREAM];
    strParam[SECONDARY_STREAM] = strSwap;

    // Resize and move the streams
    UpdatePinPos(PRIMARY_STREAM);
    UpdatePinPos(SECONDARY_STREAM);

    // Update the alpha values so that the main stream is fully opaque
    // and the subpicture stream is partially transparent.
    UpdatePinAlpha(PRIMARY_STREAM);
    UpdatePinAlpha(SECONDARY_STREAM);
    
    // Remember which stream is the logical 'subpicture' stream so
    // that the correct stream will be moved and resized by keystrokes
    g_nSubpictureID ^= 1;

    // Make sure that the subpicture stream is always on top of the Z order
    UpdatePinZOrder(!g_nSubpictureID, ZORDER_FAR);
    UpdatePinZOrder(g_nSubpictureID, ZORDER_CLOSE);
}

void StartTimer(int nTimeout)
{
    gnTimer = (int) SetTimer(NULL, UPDATE_TIMER, nTimeout, TimerProc);
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
    // Increment count of timer ticks processed.  We will stop animating 
    // when the position and alpha transitions are complete.
    g_nSwapSteps++;

    // The first pass of the timer updates manipulates the streams'
    // position and size values, to animate their onscreen swap.
    if (g_nSwapState == SWAP_POSITION)
    {
        // Adjust each stream's size and position by a value
        // calculated when the animated stream swap begain.
        AdjustStreamRect(PRIMARY_STREAM,   &strDelta[0]);
        AdjustStreamRect(SECONDARY_STREAM, &strDelta[1]);

        // Complete the stream swap if we have reached the last step
        if (g_nSwapSteps == (int) NUM_ANIMATION_STEPS)
        {
            // Reset the timer for the faster alpha transition timeout value
            StopTimer();
            StartTimer(ALPHA_TIMEOUT);

            // Remember which stream is the logical 'subpicture' stream so
            // that the correct stream will be moved and resized by keystrokes
            g_nSubpictureID ^= 1;

            // Make sure that the subpicture stream is always on top of the Z order
            UpdatePinZOrder(!g_nSubpictureID, ZORDER_FAR);
            UpdatePinZOrder(g_nSubpictureID, ZORDER_CLOSE);

            // Reset count of swap steps for next pass
            g_nSwapSteps = 0;

            // Advance state to alpha transition for next timer pass
            g_nSwapState = SWAP_ALPHA;
        }
    }

    // The second pass of the timer will quickly adjust the alpha values
    // of both streams, so that the primary stream is opaque and the 
    // subpicture stream is partially transparent.
    else if (g_nSwapState == SWAP_ALPHA)
    {
        // Adjust each stream's alpha by the value calculated
        // when the animated stream swap begain.
        AdjustAlpha(PRIMARY_STREAM,   &strDelta[0]);
        AdjustAlpha(SECONDARY_STREAM, &strDelta[1]);

        // Complete the stream swap
        if (g_nSwapSteps == (int) NUM_ANIMATION_STEPS)
        {
            StopTimer();

            // Reinitialize states for next timer pass
            g_nSwapState = SWAP_NOTHING;
            g_nSwapSteps = 0;
        }
    }
}

void StartSwapAnimation(void)
{
    // Calculate the per-timer changes for each coordinate and alpha value.
    // The first pass of timer updates will affect the stream sizes and positions
    strDelta[0].xPos   = (strParam[1].xPos   - strParam[0].xPos)   / NUM_ANIMATION_STEPS;
    strDelta[0].yPos   = (strParam[1].yPos   - strParam[0].yPos)   / NUM_ANIMATION_STEPS;
    strDelta[0].xSize  = (strParam[1].xSize  - strParam[0].xSize)  / NUM_ANIMATION_STEPS;
    strDelta[0].ySize  = (strParam[1].ySize  - strParam[0].ySize)  / NUM_ANIMATION_STEPS;

    strDelta[1].xPos   = (strParam[0].xPos   - strParam[1].xPos)   / NUM_ANIMATION_STEPS;
    strDelta[1].yPos   = (strParam[0].yPos   - strParam[1].yPos)   / NUM_ANIMATION_STEPS;
    strDelta[1].xSize  = (strParam[0].xSize  - strParam[1].xSize)  / NUM_ANIMATION_STEPS;
    strDelta[1].ySize  = (strParam[0].ySize  - strParam[1].ySize)  / NUM_ANIMATION_STEPS;

    // The second pass of timer updates will affect the stream alpha values
    strDelta[0].fAlpha = (strParam[1].fAlpha - strParam[0].fAlpha) / NUM_ANIMATION_STEPS;
    strDelta[1].fAlpha = (strParam[0].fAlpha - strParam[1].fAlpha) / NUM_ANIMATION_STEPS;

    // Clear the count of steps between states
    g_nSwapSteps = 0;

    // Set for updating position and size on timer ticks, after which 
    // the alpha values will be updated on a faster timer.
    g_nSwapState = SWAP_POSITION;

    // Set a timer to smoothly change the stream sizes and positions
    StartTimer(POSITION_TIMEOUT);
}


