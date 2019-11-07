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
// ID Code      : RTD2014OsdFunc.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFUNC__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
WORD g_usFontSelectStart;
WORD g_usFontTableStart;
BYTE g_ucOsdWidth;
BYTE g_ucOsdHeight;
BYTE g_ucOsdWidthB;
BYTE g_ucOsdHeightB;
BYTE g_ucFontPointer0 = _OSD_PAGE_0_START;
BYTE g_ucFontPointer1 = _OSD_PAGE_1_START;
BYTE g_ucFontPointer2 = _OSD_PAGE_2_START;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor);

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON))
void OsdFuncApplyMapOsdAB(BYTE ucWidthA, BYTE ucHeightA, BYTE ucColorA, BYTE ucWidthB, BYTE ucHeightB, BYTE ucColorB);
#endif

void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
void OsdFuncTransparency(BYTE ucTrans);
void OsdFuncBlending(BYTE ucType);
//BYTE OsdFuncGetOsdFontPointer(BYTE ucPointerSelect);
//BYTE OsdFuncSetOsdFontPointer(BYTE ucPointerSelect,BYTE ucPointer);
void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex);
void OsdFuncDisableOsd(void);
void OsdFuncEnableOsd(void);
void OsdFuncChangeIconColor1Bit(BYTE ucRow, BYTE ucItem, BYTE ucWidth, BYTE ucHeight, BYTE ucColor);
void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom);
void OsdFuncSet2BitIconOffset(BYTE ucOffset);
void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight);
#if(_SIX_COLOR_SUPPORT == _ON)
void OsdFuncSixColorAdjust(void);
#endif
void OsdFuncColorFormatAdjust(EnumDisplayRegion enumRegion);
void OsdFuncColorPcmAdjust(void);
void OsdFuncSetOsdItemFlag(void);
BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum, BYTE ucRegion);
#if(_FREEZE_SUPPORT == _ON)
bit OsdFuncCheckFreezeDisableMsg(void);
bit OsdFuncCheckFreezeDisable(void);
void OsdFuncShowOSDAfterClosedFreezeMsg(void);
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
bit OsdFuncCheckFalseColorDisableMsg(void);
bit OsdFuncCheckFalseColorDisable(void);
void OsdFuncShowOSDAfterClosedFalseColorMsg(void);
void OsdBlankFont(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType);
#endif

void OsdFuncShowSourceMenuCheck(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncApplyMap(BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
    BYTE ucI = 0;
    BYTE ucTmp = 17; // Row Height = 18

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidth;
        ucWidth = ucHeight;
        ucHeight = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif

    // Row Command
    for(ucI = 0; ucI < ucHeight; ucI++)
    {
        ScalerOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidth);
    }

    // Row Command end
    ScalerOsdCommandByte(ucHeight, _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = ucHeight + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidth * ucHeight);
    ScalerOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);

    // Character Command initial
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucTmp = 0x4E;  // 18 Pixel
    }
    else
#endif
    {
        ucTmp = 0x4C;  // 12 Pixel
    }

    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColor, (WORD)ucWidth * ucHeight);

    // for calculation (unit: word count)
    g_ucOsdWidth = ucWidth;
    g_ucOsdHeight = ucHeight;
    SET_OSD_MAPA_COL_MAX(WIDTH(g_ucOsdWidth));

    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
}

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncApplyMapOsdAB(BYTE ucWidthA, BYTE ucHeightA, BYTE ucColorA, BYTE ucWidthB, BYTE ucHeightB, BYTE ucColorB)
{
    BYTE ucI = 0;
    BYTE ucTmp = 17; // Row Height = 18

////////// OSD A Row command
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidthA;
        ucWidthA = ucHeightA;
        ucHeightA = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif
    // Row Command
    for(ucI = 0; ucI < ucHeightA; ucI++)
    {
        ScalerOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidthA);
    }
    // Row Command end
    ScalerOsdCommandByte(ucHeightA, _OSD_BYTE0, 0x00);


////////// OSD B Row command
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucI = ucWidthB;
        ucWidthB = ucHeightB;
        ucHeightB = ucI;
        ucTmp = 11;  // Row Height = 12
    }
#endif
    // Row Command
    for(ucI = (ucHeightA + 1); ucI < (ucHeightA + 1 + ucHeightB); ucI++)
    {
        ScalerOsdCommandAllByte(ucI, 0x80, ucTmp, ucWidthB);
    }
    // Row Command end
    ScalerOsdCommandByte((ucHeightA + 1 + ucHeightB), _OSD_BYTE0, 0x00);

    // Frame Control (set font start address)
    g_usFontSelectStart = (ucHeightA + 1 + ucHeightB) + 1;
    g_usFontTableStart = g_usFontSelectStart + (WORD)(ucWidthA * ucHeightA) + (WORD)(ucWidthB * ucHeightB);
    ScalerOsdSramBaseAddressSet(_OSD_A, 0, g_usFontSelectStart, g_usFontTableStart);
    ScalerOsdSramBaseAddressSet(_OSD_B, (ucHeightA + 1), (g_usFontSelectStart + (WORD)(ucWidthA * ucHeightA)), g_usFontTableStart);

    // Character Command initial
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucTmp = 0x4E;  // 18 Pixel
    }
    else
#endif
    {
        ucTmp = 0x4C;  // 12 Pixel
    }

    ScalerOsdCharCommandAllByteSeries(g_usFontSelectStart, ucTmp, 0, ucColorA, (WORD)ucWidthA * ucHeightA);
    ScalerOsdCharCommandAllByteSeries((g_usFontSelectStart + (WORD)(ucWidthA * ucHeightA)), ucTmp, 0, ucColorB, (WORD)ucWidthB * ucHeightB);

    g_ucOsdWidth = ucWidthA;
    g_ucOsdHeight = ucHeightA;
    g_ucOsdWidthB = ucWidthB;
    g_ucOsdHeightB = ucHeightB;
    SET_OSD_MAPA_COL_MAX(WIDTH(g_ucOsdWidth));
    SET_OSD_MAPB_COL_MAX(WIDTH(g_ucOsdWidthB));

    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdDoubleFunction(GET_OSD_DOUBLE_SIZE(), GET_OSD_DOUBLE_SIZE());
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY)
{
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    WORD usShiftValue = 0;
    BYTE ucXdouble = 1;
    WORD usTemp = 0;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucXdouble = 2;
    }

    if(ScalerOsdGetHorizontalDelayStep() == _OSD_HORIZONTAL_DELAY_STEP_4_PIXEL)
    {
        // change horizontal delay step to 1 pixel for FB shift
        ScalerOsdHorizontalDelayStep(_OSD_HORIZONTAL_DELAY_STEP_1_PIXEL);
        usX *= 4;
    }

    if(enumOsdPositionType == _OSD_POSITION_GLOBAL_A)
    {
        if((usX * ucXdouble) <= 100)
        {
            // ScalerOsdPosition(enumOsdPositionType, (usX * ucXdouble), usY);
            ScalerOsdPosition(enumOsdPositionType, (usX), usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, 0);
        }
        else if((usX * ucXdouble) <= (4094 + 100))
        {
            ScalerOsdPosition(enumOsdPositionType, 100 / ucXdouble, usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, (usX * ucXdouble) - 100);
        }
        else // > 4095+100
        {
            ScalerOsdPosition(enumOsdPositionType, ((usX * ucXdouble) - 4094) / ucXdouble, usY);
            ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE, 4094);
        }

        ScalerOsdFBShiftValue(_OSD_FRONT_BACK_SHIFT_INSIDE, 0x00);
        ScalerOsdFBShiftBoundarySize(0x00, 0x00);
    }
    else if(enumOsdPositionType == _OSD_POSITION_GLOBAL_B)
    {
        usShiftValue = ScalerOsdGetFBShiftValue(_OSD_FRONT_BACK_SHIFT_OUTSIDE);

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            usTemp = g_ucOsdWidthB * 12;
        }
        else
        {
            usTemp = g_ucOsdHeightB * 18;
        }

        // if HPOS over halt of Panel width + shift value, adjust to adaptable HPOS
        if((usX * ucXdouble) > ((_PANEL_DH_WIDTH / 2 + usShiftValue) - (usTemp * ucXdouble)))
        {
            ScalerOsdPosition(enumOsdPositionType, (((_PANEL_DH_WIDTH / 2 + usShiftValue) - (usTemp * ucXdouble)) / ucXdouble), usY);
        }
        else
        {
            ScalerOsdPosition(enumOsdPositionType, ((usX * ucXdouble) - usShiftValue) / ucXdouble, usY);
        }
    }
#else
    ScalerOsdPosition(enumOsdPositionType, usX, usY);
#endif

    ScalerTimerWaitForEvent(_EVENT_DVS);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncTransparency(BYTE ucTrans)
{
    ScalerOsdSetTransparency(ucTrans);
}

//--------------------------------------------------
// Description  :
// Input Value  : Blending type1:Only windows blending.
//                Blending type2:All blending.
//                Blending type3:Windows & Character background blending.
// Output Value : None
//--------------------------------------------------
void OsdFuncBlending(BYTE ucType)
{
    ScalerOsdVerticalStartSelect(_OSD_VSYNC_SELECT_DVS);
    ScalerOsdWindow7SpecialFunction(_OSD_WINDOW_7_FUNCTION_MASK_REGION_TRANSPARENT_ALL);
    ScalerOsdSetTransparencyType(ucType);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncCloseWindow(EnumOsdWindowsType enumWinIndex)
{
    ScalerOsdWindowDisable(enumWinIndex);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncDisableOsd(void)
{
    ScalerOsdDisableOsd();
    ScalerOsd2FontFunction(_DISABLE);
    OsdFuncCloseWindow(_OSD_WINDOW_ALL);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncEnableOsd(void)
{
    ScalerOsdEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncChangeIconColor1Bit(BYTE ucRow, BYTE ucItem, BYTE ucWidth, BYTE ucHeight, BYTE ucColor)
{
//    BYTE ucRow;
    BYTE ucCol = 3;

    if((ucRow == 18) || (ucRow == 8))
    {
        OsdFuncChangeColor1Bit(ucRow, ucCol, 8, ucHeight, (ucColor << 4) & 0xF0, _FONTFROM_256_512);
    }
    else
    {
        ucCol = COL(4) + ((ucItem % 4) * 10) - 2;
        OsdFuncChangeColor1Bit(ucRow, ucCol, ucWidth, ucHeight, (ucColor << 4) & 0xF0, _FONTFROM_0_255);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncChangeColor1Bit(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight, BYTE ucColor, BYTE ucFontSelectFrom)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;
    // BYTE ucWidthCount = 0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdWidth - ucRow - ucHeight) + g_ucOsdWidth * (ucCol + ucWidthCount) + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4E | ucFontSelectFrom), ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
        }
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4E | ucFontSelectFrom), ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucHeight);
        }
    }
    else
#endif
    {
        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
        {
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, (0x4C | ucFontSelectFrom), ucWidth);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, ucColor, ucWidth);
            usOsdAddr += g_ucOsdWidth;
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSet2BitIconOffset(BYTE ucOffset)
{
    ScalerOsd2BitFontOffset(ucOffset);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncClearOsd(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucHeight)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;
    // BYTE ucWidthCount = 0;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdWidth - ucRow - ucHeight) + g_ucOsdWidth * (ucCol + ucWidthCount) + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4E, ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucHeight);
        }
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        for(ucWidthCount = 0; ucWidthCount < ucWidth; ucWidthCount++)
        {
            usOsdAddr = (WORD)(g_ucOsdHeight - 1 - ucCol - ucWidthCount) * g_ucOsdWidth + ucRow + g_usFontSelectStart;
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4E, ucHeight);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucHeight);
        }
    }
    else
#endif
    {
        for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
        {
            // 1 Bit Font
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, 0x4C, ucWidth);
            ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, 0x00, ucWidth);
            usOsdAddr += g_ucOsdWidth;
        }
    }
}

#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSixColorAdjust(void)
{
    ScalerColorSixColorAdjust(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR(), GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncColorFormatAdjust(EnumDisplayRegion enumRegion)
{
    EnumSourceTypeDef enumSourceType = SysRegionGetSourceType(enumRegion);
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType((GET_OSD_SYSTEM_DISPLAY_REGION()));

    if(enumSourceType == _SOURCE_VGA)
    {
        if(GET_OSD_COLOR_FORMAT(enumSourceSearchPort) == _COLOR_SPACE_RGB)
        {
            SET_VGA_COLOR_FORMAT_STATUS(_COLOR_SPACE_RGB);
        }
        else
        {
            SET_VGA_COLOR_FORMAT_STATUS(_COLOR_SPACE_YPBPR);
        }
    }
    else if(enumSourceType == _SOURCE_DVI)
    {
        if(GET_OSD_COLOR_FORMAT(enumSourceSearchPort) == _COLOR_SPACE_RGB)
        {
            SET_DVI_COLOR_FORMAT_STATUS(_COLOR_SPACE_RGB);
        }
        else
        {
            SET_DVI_COLOR_FORMAT_STATUS(_COLOR_SPACE_YPBPR);
        }
    }

#if(_OVERSCAN_SUPPORT == _ON)
    if(GET_OSD_OVERSCAN_STATUS(enumSourceSearchPort) == _ON)
    {
        UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
    }
    else
#endif
    {
        EnumDisplayRegion enumStartRegion = _DISPLAY_RGN_1P;
        EnumDisplayRegion enumStopRegion = _DISPLAY_RGN_1P;
        EnumDisplayRegion enumIndexRegion = 0;

        switch(GET_OSD_DISPLAY_MODE())
        {
            default:
                break;

            case _OSD_DM_2P_TB:
                enumStartRegion = _DISPLAY_RGN_TOP;
                enumStopRegion = _DISPLAY_RGN_BOTTOM;
                break;

            case _OSD_DM_2P_LR:
                enumStartRegion = _DISPLAY_RGN_LEFT;
                enumStopRegion = _DISPLAY_RGN_RIGHT;
                break;

            case _OSD_DM_2P_PIP:
                enumStartRegion = _DISPLAY_RGN_MAIN;
                enumStopRegion = _DISPLAY_RGN_SUB;
                break;

            case _OSD_DM_4P:
                enumStartRegion = _DISPLAY_RGN_LT;
                enumStopRegion = _DISPLAY_RGN_RB;
                break;
        }

        for(enumIndexRegion = enumStartRegion; enumIndexRegion <= enumStopRegion; ++enumIndexRegion)
        {
            if(SysRegionGetPortType(enumIndexRegion) == enumSourceSearchPort)
            {
                if(GET_OSD_COLOR_FORMAT(enumSourceSearchPort) == _COLOR_SPACE_RGB)
                {
                    SysModeColorSpaceConvert(enumIndexRegion, enumSourceSearchPort, _COLOR_SPACE_RGB, _DB_APPLY_POLLING);
                }
                else
                {
                    SysModeColorSpaceConvert(enumIndexRegion, enumSourceSearchPort, _COLOR_SPACE_YPBPR, _DB_APPLY_POLLING);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncColorPcmAdjust(void)
{
#if(_PCM_FUNCTION == _ON)

    EnumSelRegion enumSelRegion = GET_OSD_SYSTEM_SELECT_REGION();
    // EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(enumSelRegion);

    if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
        ScalerColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
#endif
        UserAdjustPCM(enumSelRegion, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
        ScalerColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF); // Region selected by user

        if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_SOFT_PROFT)
        {
            UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
            ScalerColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON); // Region selected by user
        }
#endif
    }
    else
    {
        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
        ScalerColor3DGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF); // Region selected by user
#endif

#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
        ScalerColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);
#endif
        UserAdjustPCM(enumSelRegion, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
    }

#endif  // End of #if(_PCM_FUNCTION == _ON)
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncSetOsdItemFlag(void)
{
/*
//input port
    if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
    {
        SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_AUTO);
    }
    else
    {
        switch(SysSourceGetInputPort())
        {
            case _A0_INPUT_PORT:
                SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_A0);
                break;

            case _D0_INPUT_PORT:
                SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_D0);
                break;

            case _D1_INPUT_PORT:
                SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_D1);
                break;

            case _D2_INPUT_PORT:
                SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_D2);
                break;

            case _D3_INPUT_PORT:
                SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_D3);
                break;

            case _D4_INPUT_PORT:
                SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_D4);
                break;

            case _D5_INPUT_PORT:
                SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_D5);
                break;

            case _D6_INPUT_PORT:
                SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_D6);
                break;

        }
    }
*/
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdFuncCheckInputPortType(BYTE ucOsdInputNum, BYTE ucRegion)
{
    BYTE ucCheckloop =0;
    do
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
                if (ucOsdInputNum >= _OSD_INPUT_AUTO)
                {
                    ucOsdInputNum = _OSD_INPUT_A0;
                }
                else
                {
                    ucOsdInputNum++;
                }
                break;

            case _LEFT_KEY_MESSAGE:
                if (ucOsdInputNum <= _OSD_INPUT_A0)
                {
                    ucOsdInputNum = _OSD_INPUT_AUTO;
                }
                else
                {
                    ucOsdInputNum--;
                }
                break;

            default:
                break;
        }

        switch(ucOsdInputNum)
        {
            case _OSD_INPUT_A0:
                ucCheckloop = (_A0_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D0:
                ucCheckloop = (_D0_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D1:
                ucCheckloop = (_D1_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D2:
                ucCheckloop = (_D2_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D3:
                ucCheckloop = (_D3_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D4:
                ucCheckloop = (_D4_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D5:
                ucCheckloop = (_D5_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D6:
                ucCheckloop = (_D6_INPUT_TYPE - _OPTION_ICON_END);
                break;
            case _OSD_INPUT_D7:

                if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
                {
                    ucCheckloop = 0x00;
                }
                else
                {
                    ucCheckloop = (_D7_INPUT_TYPE - _OPTION_ICON_END);
                }

                break;

            case _OSD_INPUT_AUTO:

                if((ucRegion == _REGION_INDEX_0) &&
                   ((GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                    (GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                    (GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)))
                {
                    ucCheckloop = 0x00;
                }
                else if((ucRegion == _REGION_INDEX_1) &&
                        ((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)))
                {
                    ucCheckloop = 0x00;
                }
                else if((ucRegion == _REGION_INDEX_2) &&
                        ((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_4P_INPUT_SOURCE() == _OSD_INPUT_AUTO)))
                {
                    ucCheckloop = 0x00;
                }
                else if((ucRegion == _REGION_INDEX_3) &&
                        ((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_2P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                         (GET_OSD_3P_INPUT_SOURCE() == _OSD_INPUT_AUTO)))
                {
                    ucCheckloop = 0x00;
                }
                else
                {
                    return ucOsdInputNum;
                }
                break;
            default:
                break;
        }
    }while(ucCheckloop == 0x00); // 0x00=>NO PORT

    return ucOsdInputNum;
}

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit OsdFuncCheckFreezeDisableMsg(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG) == _TRUE)
    {
        return _TRUE;
    }
#else
    if(GET_FREEZE_DISABLE_MSG_STATE() == _ON)
    {
        return _TRUE;
    }
#endif
    return _FALSE;
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit OsdFuncCheckFreezeDisable(void)
{
    if(GET_OSD_FREEZE_STATUS() == _OFF)
    {
        return _FALSE;
    }

    if((((GET_OSD_STATE() == _MENU_ANALOG) ||
         (GET_OSD_STATE() == _MENU_COLOR_FORMAT) ||
         (GET_OSD_STATE() == _MENU_ADVANCE_ASPECT) ||
         (GET_OSD_STATE() == _MENU_ADVANCE_OVER_SCAN) ||
         (GET_OSD_STATE() == _MENU_OTHER_RESET) ||
         (GET_OSD_STATE() == _MENU_DISPLAYMODE) ||
         (GET_OSD_STATE() == _MENU_DISPLAYFUN_LATENCY)) && (GET_KEYMESSAGE() == _MENU_KEY_MESSAGE)) ||
       ((GET_OSD_STATE() == _MENU_ADVANCE_ULTRA_VIVID_ADJUST) && (GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()) == _ULTRA_VIVID_OFF) && (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
       ((GET_OSD_STATE() == _MENU_ADVANCE_ULTRA_VIVID_ADJUST) && (GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()) == _ULTRA_VIVID_L) && (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
    {
        OsdDispOsdMessage(_OSD_DISP_DISABLE_FREEZE_MSG);
        ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
        SET_OSD_STATE(GET_OSD_STATE_PREVIOUS());
        SET_OSD_FREEZE_STATUS(_OFF);
        UserCommonAdjustDisplayFreeze(_OFF);
#if(_URGENT_EVENT_CHECK_MODE == _OFF)
        SET_FREEZE_DISABLE_MSG_STATE(_ON);
#endif
        return _TRUE;
    }
    return _FALSE;
}
//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
void OsdFuncShowOSDAfterClosedFreezeMsg(void)
{
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType(UserAdjustConvertSystemSelectRegion(GET_OSD_SELECT_REGION()));

    OsdDispMainMenu();

    switch(GET_OSD_STATE())
    {
        case _MENU_ANALOG:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ANALOG_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
            break;
        case _MENU_COLOR_FORMAT:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT(enumSourceSearchPort));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
            SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
            break;

        case _MENU_ADVANCE_ASPECT:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _UNSELECT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));
            if(GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()) == _OSD_ASPECT_RATIO_ORIGIN)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
            }
            SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
            break;

        case _MENU_ADVANCE_OVER_SCAN:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _UNSELECT, GET_OSD_OVERSCAN_STATUS(enumSourceSearchPort));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
            break;

        case _MENU_ADVANCE_ULTRA_VIVID_ADJUST:
            if(GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()) == _ULTRA_VIVID_OFF)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_1);
                OsdDispMainMenuCursor(_MENU_ADVANCE_ULTRA_VIVID, _MENU_ADVANCE_ULTRA_VIVID, _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, _ULTRA_VIVID_L);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ULTRA_VIVID);
                SET_KEYMESSAGE(_RIGHT_KEY_MESSAGE);
            }
            else if(GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()) == _ULTRA_VIVID_L)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_1);
                OsdDispMainMenuCursor(_MENU_ADVANCE_ULTRA_VIVID, _MENU_ADVANCE_ULTRA_VIVID, _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, _ULTRA_VIVID_OFF);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ULTRA_VIVID);
                SET_KEYMESSAGE(_LEFT_KEY_MESSAGE);
            }
            break;
        case _MENU_DISPLAYMODE:
            SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
            break;
        case _MENU_DISPLAYFUN_DISP_ROTATE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
            SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
            break;
        case _MENU_DISPLAYFUN_LATENCY:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LATENCY);
            SET_KEYMESSAGE(_MENU_KEY_MESSAGE);
            break;
        default:
            break;
    }
}
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit OsdFuncCheckFalseColorDisableMsg(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FALSE_COLOR_MSG) == _TRUE)
    {
        return _TRUE;
    }
#else
    if(GET_FALSE_COLOR_DISABLE_MSG_STATE() == _ON)
    {
        return _TRUE;
    }
#endif
    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit OsdFuncCheckFalseColorDisable(void)
{
    if(GET_OSD_FALSE_COLOR_STATUS() == _OSD_FALSE_COLOR_OFF)
    {
        return _FALSE;
    }

    // Color Temperature, Brightness, global hue/Saturation, PCM, Uniformity, Gamma, IAPS Gain, 3D Gamma
    if(((GET_OSD_STATE() >= _MENU_COLOR_PANEL_UNIFORMITY) && (GET_OSD_STATE() <= _MENU_COLOR_SATURATION)) ||
       (GET_OSD_STATE() == _MENU_PICTURE_BRIGHTNESS_ADJUST) ||
       (GET_OSD_STATE() == _MENU_PICTURE_CONTRAST_ADJUST))
    {
        SET_OSD_STATE_PREVIOUS(GET_OSD_STATE());
        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
        OsdDispOsdMessage(_OSD_DISP_DISABLE_FALSE_COLOR_MSG);
        ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_DISABLE_FALSE_COLOR_MSG);
        SET_OSD_STATE(GET_OSD_STATE_PREVIOUS());
        SET_OSD_FALSE_COLOR_STATUS(_OSD_FALSE_COLOR_OFF);
        // function adjust
        UserAdjustFalseColor(GET_OSD_SELECT_REGION(), GET_OSD_FALSE_COLOR_STATUS());

        // IT IS MUST BE DONE
        UserInterfaceAdjustInitialColorProc(GET_OSD_DISPLAY_MODE());
        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
#if(_URGENT_EVENT_CHECK_MODE == _OFF)
        SET_FALSE_COLOR_DISABLE_MSG_STATE(_ON);
#endif
        return _TRUE;
    }
    return _FALSE;
}
//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
void OsdFuncShowOSDAfterClosedFalseColorMsg(void)
{
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType(UserAdjustConvertSystemSelectRegion(GET_OSD_SELECT_REGION()));

    OsdDispMainMenu();

    switch(GET_OSD_STATE())
    {
        case _MENU_COLOR_PANEL_UNIFORMITY:
        case _MENU_COLOR_GAMMA:
        case _MENU_COLOR_TEMPERATURE:
        case _MENU_COLOR_EFFECT:
        case _MENU_COLOR_DEMO:
        case _MENU_COLOR_FORMAT:
        case _MENU_COLOR_PCM:
        case _MENU_COLOR_HUE:
        case _MENU_COLOR_SATURATION:

            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _MENU_PICTURE_BRIGHTNESS_ADJUST:
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
            break;

        case _MENU_PICTURE_CONTRAST_ADJUST:
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
            break;


        default:
            break;
    }
}

//--------------------------------------------------
// Description  : draw blank
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdBlankFont(BYTE ucRow, BYTE ucCol, BYTE ucLength, BYTE ucHeight, BYTE ucPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType)
{
    WORD usOsdAddr = (WORD)ucRow * g_ucOsdWidth + ucCol + g_usFontSelectStart;
    BYTE ucHeightCount = 0;
    BYTE ucWidthCount = 0;

    enumOsdBlankingType = (enumOsdBlankingType & 0x03);

    for(ucHeightCount = 0; ucHeightCount < ucHeight; ucHeightCount++)
    {
        ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE0, enumOsdBlankingType, ucLength);
        ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE1, (ucPixelLength & 0xFF), ucLength);
        ScalerOsdCharCommandByteSeries(usOsdAddr, _OSD_BYTE2, (ucBackgroundColor & 0x3F), ucLength);
        usOsdAddr += g_ucOsdWidth;
    }
}

#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdFuncShowSourceMenuCheck(void)
{
#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if (ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING) == _TRUE)
    {
        ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
    }
    else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING) || (ScalerTimerSearchActiveTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING) == _TRUE))
    {
        ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
    }
#else
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
    }
#endif
}
#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
