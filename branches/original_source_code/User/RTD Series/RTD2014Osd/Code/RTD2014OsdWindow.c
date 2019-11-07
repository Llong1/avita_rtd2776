/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RTD2014OsdWindow.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDWINDOW__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _BORDER_PIXEL_WIDTH             3

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor);
void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor);
void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState);
void OsdWindowSliderDisable(void);

#if (_FALSE_COLOR_SUPPORT == _ON)
void OsdWindowDrawingByFontBorder(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
#endif

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawing(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor)
{
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    WORD xdata usTemp = 0;
    WORD xdata usTemp1 = 0;
    WORD xdata usTemp2 = 0;
    usTemp  = usXEnd - usXStart;    // calculate X
    usTemp1 = usYEnd - usYStart;    // calculate Y
    usTemp2 = usXStart;

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        usXEnd = (g_ucOsdWidth * 18 - usYStart);
        usXStart = usXEnd - usTemp1;
        usYStart = usTemp2;
        usYEnd = usYStart + usTemp;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        usXStart = usYStart;

        usYStart = (g_ucOsdHeight * 12) - usXEnd;
        usXEnd = usXStart + usTemp1;
        usYEnd = usYStart + usTemp;
    }
    else
    {
    }

#elif(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    WORD xdata usTemp = 0;
    WORD xdata usTemp1 = 0;
    WORD xdata usTemp2 = 0;
    usTemp  = usXEnd - usXStart;    // calculate X
    usTemp1 = usYEnd - usYStart;    // calculate Y
    usTemp2 = usXStart;

    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        usXEnd = (g_ucOsdHeight * 18 - usYStart);
        usXStart = usXEnd - usTemp1;
        usYStart = usTemp2;
        usYEnd = usYStart + usTemp;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        usXStart = usYStart;
        usYStart = (g_ucOsdWidth * 12) - usXEnd;
        usXEnd = usXStart + usTemp1;
        usYEnd = usYStart + usTemp;
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        usXStart = (g_ucOsdWidth * 12) - usTemp - usXStart;
        usXEnd = usXStart + usTemp;
        usYStart = (g_ucOsdHeight * 18) - usTemp1 - usYStart;
        usYEnd = usYStart + usTemp1;
    }
    else
    {
    }

#else//#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)

#endif

    SET_OSD_WINDOW_NUMBER(ucWindow);
    SET_OSD_WINDOW_COLOR(ucColor);

    SET_OSD_WINDOW_BLEND_ENABLE(_ENABLE);
    SET_OSD_WINDOW_ENABLE(_ENABLE);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerOsdDrawWindow(usXStart, usYStart, usXEnd, usYEnd);
}

/*
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawingHighlight(BYTE ucWindow, WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor)
{
    OsdWindowDrawing(ucWindow, usXStart, usYStart, usXEnd, usYEnd, ucColor);

    ScalerOsdWindowHighlightFunction(_ENABLE, ucWindow, ucForegroundColor, ucBackgroundColor, _CP_BG);
}
*/

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawingByFont(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;

    usHstart = ((WORD)ucCol * 12);
    usHend = usHstart + ((WORD)ucWidth * 12);

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
    }
    usVend = usVstart + (18 * ucHeight);

    OsdWindowDrawing(ucWindow, usHstart, usVstart, usHend, usVend, ucColor);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawingByFontHighlight(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucForegroundColor, BYTE ucBackgroundColor)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;

    usHstart = ((WORD)ucCol * 12);
    usHend = usHstart + ((WORD)ucWidth * 12);

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
    }
    usVend = usVstart + (18 * ucHeight);

    OsdWindowDrawing(ucWindow, usHstart, usVstart, usHend, usVend, ucColor);

    ScalerOsdWindowHighlightFunction(_ENABLE, ucWindow, ucForegroundColor, ucBackgroundColor, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowSlider(BYTE ucRow, BYTE ucCol, BYTE ucPercentValue, BYTE ucSliderNumber, bit bSelectState)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;
    WORD usSliderPixel = 0;
    BYTE ucSliderBarWindow = 0;
    BYTE ucSliderBoderWindow = 0;
    BYTE ucSliderBackgroundWindow = 0;
    BYTE ucSliderColor = 0;
    BYTE ucSliderBackgroundColor = 0;
    BYTE ucSliderBoderColor = 0;

    usSliderPixel = (WORD)(_SLIDER_LENGHT * ucPercentValue) / 100;

    usHstart = ((WORD)ucCol * 12) + _SLIDER_OFFSET;
    usHend = usHstart + _SLIDER_LENGHT;

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
        usVend = usVstart + _SLIDER_HIGH;
    }
    else
    {
        usVstart = (ucRow * 18);
        usVend = usVstart + _SLIDER_HIGH;
    }

    if(ucSliderNumber == _SLIDER_0)
    {
        ucSliderBarWindow = _SLIDER_0_BAR_WINDOW;
        ucSliderBoderWindow = _SLIDER_0_BORDER_WINDOW;
        ucSliderBackgroundWindow = _SLIDER_0_BG_WINDOW;
    }
    else
    {
        ucSliderBarWindow = _SLIDER_1_BAR_WINDOW;
        ucSliderBoderWindow = _SLIDER_1_BORDER_WINDOW;
        ucSliderBackgroundWindow = _SLIDER_1_BG_WINDOW;
    }

    if(bSelectState == _TRUE)
    {
        ucSliderColor = _SLIDER_SELECT_COLOR;
        ucSliderBackgroundColor = _SLIDER_SELECT_BG_COLOR;
        ucSliderBoderColor = _SLIDER_SELECT_BORDER_COLOR;
    }
    else
    {
        ucSliderColor = _SLIDER_UNSELECT_COLOR;
        ucSliderBackgroundColor = _SLIDER_UNSELECT_BG_COLOR;
        ucSliderBoderColor = _SLIDER_UNSELECT_BORDER_COLOR;
    }

    SET_OSD_WINDOW_BUTTON_ENABLE(_DISABLE);
    // Slider Boder Window
    OsdWindowDrawing(ucSliderBoderWindow, usHstart - _SLIDER_BORDER_PIXEL, usVstart - _SLIDER_BORDER_PIXEL, usHend + _SLIDER_BORDER_PIXEL, usVend + _SLIDER_BORDER_PIXEL, ucSliderBoderColor); // Slider BG Color

    OsdWindowDrawing(ucSliderBackgroundWindow, usHstart, usVstart, usHend, usVend, ucSliderBackgroundColor);// Slider BG Window

    if(usSliderPixel == 0) // Slider Window
    {
        ScalerOsdWindowDisable(ucSliderBarWindow);
    }
    else
    {
        OsdWindowDrawing(ucSliderBarWindow, usHstart, usVstart, usHstart + usSliderPixel, usVend, ucSliderColor);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowSliderDisable(void)
{
    ScalerOsdWindowDisable(_SLIDER_0_BAR_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_0_BORDER_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_0_BG_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_1_BAR_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_1_BORDER_WINDOW);
    ScalerOsdWindowDisable(_SLIDER_1_BG_WINDOW);
}

#if (_FALSE_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdWindowDrawingByFontBorder(BYTE ucWindow, BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    WORD usHstart = 0;
    WORD usHend = 0;
    WORD usVstart = 0;
    WORD usVend = 0;

    usHstart = ((WORD)ucCol * 12);
    usHend = usHstart + ((WORD)ucWidth * 12);

    if(ucRow > 0)
    {
        usVstart = (ucRow * 18);
    }
    usVend = usVstart + (18 * ucHeight);
    SET_OSD_WINDOW_COLOR_BORDER(ucColor);
    SET_OSD_WINDOW_SHADOW_BORDER_PIXEL_WIDTH(_BORDER_PIXEL_WIDTH);
    SET_OSD_WINDOW_SHADOW_BORDER_PIXEL_HEIGHT(_BORDER_PIXEL_WIDTH);
    SET_OSD_WINDOW_BUTTON_ENABLE(_ENABLE);
    SET_OSD_WINDOW_BUTTON_TYPE(_OSD_WINDOW_BUTTON_TYPE_BORDER);

    OsdWindowDrawing(ucWindow, usHstart - (_BORDER_PIXEL_WIDTH + 1), usVstart - (_BORDER_PIXEL_WIDTH + 1), usHend, usVend, _CP_BG);
}
#endif

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)

