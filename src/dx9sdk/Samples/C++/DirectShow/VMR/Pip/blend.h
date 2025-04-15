//------------------------------------------------------------------------------
// File: Blend.h
//
// Desc: DirectShow sample code - header file for video stream manipulation
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

//
// Constants
//
#define TRANSPARENCY_VALUE   (0.6f)  // Alpha ranges from 0.0 to 1.0f

enum QUAD
{
    TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT, NUM_QUADRANTS
};

const int DEFAULT_QUADRANT = BOTTOM_RIGHT;

const float X_EDGE_BUFFER = 0.025f;  // Distance from screen border
const float Y_EDGE_BUFFER = 0.05f;   // Distance from screen border

const float SECONDARY_WIDTH =  0.4f; // Width of subpicture in comp space
const float SECONDARY_HEIGHT = 0.4f; // Height of subpicture in comp space

const int UPDATE_TIMER = 2000;
const int POSITION_TIMEOUT = 100;    // 100ms tick for adjusting stream sizes
const int ALPHA_TIMEOUT = 50;        // 50ms tick for adjusting stream alphas

const float NUM_ANIMATION_STEPS = 10.0f; // Use float for easy floating point division

const int PRIMARY_STREAM   = 0;
const int SECONDARY_STREAM = 1;

const int ZORDER_CLOSE = 0;   // Closest stream in Z order
const int ZORDER_FAR   = 1;   // Higher values indicate 'farther away'

const float MOVEVAL = 0.05f;  // Amount to move subpicture stream on keystrokes

const int SWAP_NOTHING  = 0;  // States used in 'swap with animation'
const int SWAP_POSITION = 1;
const int SWAP_ALPHA    = 2;

//
// Structures
//
typedef struct
{
    FLOAT   xPos,  yPos;
    FLOAT   xSize, ySize;
    FLOAT   fAlpha;
    BOOL    bFlipped, bMirrored;
    NORMALIZEDRECT rect;

} STRM_PARAM;

typedef struct 
{
    float   xPos,  yPos;
    float   xSize, ySize;

} QUADRANT;

//
// Global data
//
extern STRM_PARAM strParam[2];
extern int g_nSubpictureID;

//
// Function prototypes
//

void StartTimer(int nTimeout);
void StopTimer(void);

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

HRESULT UpdatePinAlpha(int nStreamID);
HRESULT UpdatePinPos(int nStreamID);
HRESULT UpdatePinZOrder(int nStreamID, DWORD dwZOrder);

void InitStreamParams(void);
void PositionStream(int nStream, int nQuadrant);
void AdjustVideo(int nStream, float fX, float fY, float fWidth, float fHeight);
void CenterStream(int nStream);

void FlipStream(int nStream);
void MirrorStream(int nStream);
void SwapStreams(void);
void AdjustAlpha(int nStream, STRM_PARAM *pStream);
void AdjustStreamRect(int nStream, STRM_PARAM *pStream);
void StartSwapAnimation(void);

