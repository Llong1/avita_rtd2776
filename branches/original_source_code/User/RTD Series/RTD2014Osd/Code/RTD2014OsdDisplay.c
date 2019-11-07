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
// ID Code      : RTD2014OsdDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDDISPLAY__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _VGA_A0 = 0x01,
} EnumOsdSourceTypeVga;

typedef enum
{
    _DVI = 0x02,
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
    _DVI_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
    _DVI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
    _DVI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
    _DVI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
    _DVI_D4,
#endif
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
    _DVI_D5,
#endif

    _HDMI = 0x10,
#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
    _HDMI_D0,
#endif
#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
    _HDMI_D1,
#endif
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    _HDMI_D2,
#endif
#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
    _HDMI_D3,
#endif
#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
    _HDMI_D4,
#endif
#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
    _HDMI_D5,
#endif
}EnumOsdSourceTypeTMDS;

typedef enum
{
    _DP = 0x0E,
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    _DP_D0,
#endif
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    _DP_D1,
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    _DP_D6,
#endif
} EnumOsdSourceTypeDP;

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
BYTE OsdDisplayGetSourcePortString(EnumSourceSearchPort enumSourceSearchPort);

#if(_VGA_SUPPORT == _ON)
BYTE OsdDisplayGetVGAModeString(bit bUserMode);
#endif

BYTE OsdDispJudgeSourceType(void);
void OsdDispDisableOsd(void);
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos);
void OsdDispMainMenuItemIndication(BYTE ucItem, BYTE ucAmount, BYTE ucState);
void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState);
void OsdDispClearSelectColor(BYTE ucUpDown);

#if(_VGA_SUPPORT == _ON)
void OsdDispMainSubString(BYTE ucState);
#endif

void OsdDispMainOptionIcon(BYTE ucIconPos, BYTE ucIcon, BYTE ucColor);
void OsdDispMainMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor);
void OsdDispMainMenuIconPage(BYTE ucUpDown, BYTE ucState);
void OsdDispMainMenuArrow(BYTE ucUpDown, BYTE ucLeftRight, BYTE ucState);
void OsdDispMainMenuOptionSetting(BYTE ucItem, BYTE ucSelectState, BYTE ucOption);
void OsdDispMainMenuItemSelection(BYTE ucIconPos, BYTE ucState);
void OsdDispClearArrow(BYTE ucUpDown);
void OsdDispMainMenuSubSelect(BYTE ucItem, WORD usOsdState, WORD usOsdStatePrevious);
void OsdDispMainMenuCursor(WORD usOsdState, WORD usOsdStatePrevious, bit bInSubsidiary);
void OsdDispMainMenu(void);
void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue);
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle);
void OsdDisplaySixColorGetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor);
void OsdDisplaySixColorSetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor);
void OsdDispHotKeyOptionMenu(BYTE ucOption);
void OsdDispHotKeyOptionMenuSwitch(BYTE ucOption);
void OsdDispHotKeySourceMenuIcon(BYTE ucPort);
void OsdDispHotKeySourceMenuSwitch(BYTE ucPort);
void OsdDispHotKeySourceMenu(void);
void OsdDispHotKeyDisplayModeMenuSwitch(BYTE ucMode);
void OsdDispHotKeyDisplayModeMenuIcon(BYTE ucMode);
void OsdDispHotKeyDisplayModeMenu(void);
void OsdDispPanelUniformityMsgSwitch(void);
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage);

#if(_VGA_SUPPORT == _ON)
void OsdDispAutoConfigProc(void);
void OsdDisplayAutoBalanceProc(void);
#endif

void OsdDispClearSliderAndNumber(void);
void OsdDispOsdReset(void);
void OsdDispShowLogo(void);
void OsdDispShowInformation(void);

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
void OsdDispOsdRotateSwitch(void);
#endif

void OsdDispMpDisplayStateNotice(BYTE ucNoticeInfoX, BYTE ucNoticeInfoY, BYTE ucNoticeInfo, BYTE ucMpPortregion);

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON))
void OsdDispMpDisplayStateNoticeFontB(BYTE ucNoticeInfoX, BYTE ucNoticeInfoY, BYTE ucNoticeInfo, BYTE ucMpPortregion);
#endif

void OsdDispMpUpdateDisplayStateNotice(bit bOn, EnumDisplayRegion enumSelRegion);

#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
BYTE OsdDispMpDisplayStateGetNoticeType(EnumDisplayRegion enumSelRegion, bit bOn);
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_2P_LR(BYTE ucNoticeL, BYTE ucNoticeR);
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_2P_TB(BYTE ucNoticeT, BYTE ucNoticeB);
#endif

#if(_PIP_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_2P_PIP(BYTE ucNoticeMain, BYTE ucNoticeSub);
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
void OsdDispMpDisplayStateNotice_4P(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P, BYTE ucNotice4P);
#endif

#if (_FALSE_COLOR_SUPPORT == _ON)
BYTE OSDDispFalseColorConvert(BYTE ucIndexsel);
void OsdDispFalseColorMenu(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : None
//--------------------------------------------------
BYTE OsdDisplayGetSourcePortString(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            return _STRING_A0_PORT;
#endif
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
            return _STRING_D0_PORT;
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
            return _STRING_D1_PORT;
#endif
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
            return _STRING_D2_PORT;
#endif
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
            return _STRING_D3_PORT;
#endif
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
            return _STRING_D4_PORT;
#endif
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
            return _STRING_D5_PORT;
#endif
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
            return _STRING_D6_PORT;
#endif
#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:
            return _STRING_D7_PORT;
#endif
        default:
            return _STRING_D0_PORT;
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
BYTE OsdDisplayGetVGAModeString(bit bUserMode)
{
    if(bUserMode == _USER_MODE_TYPE)
    {
        return _STRING_VGA_USER_MODE;
    }
    else
    {
        return _STRING_VGA_PRESET_MODE;
    }
}
#endif

//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : None
//--------------------------------------------------
/*
WORD OsdDispDetOverRange(WORD ucValue, WORD ucMax, WORD ucMin, bit bCycle)
{
    ucValue = ucMax = ucMin;
    bCycle = 0;
    return 0;
    //return tOSD_ITEM_MAIN[0]; // to prevent uncall
}
*/
//--------------------------------------------------
// Description :
// Input Value : None
// Output Value : Source Port Number
//--------------------------------------------------
BYTE OsdDispJudgeSourceType(void)
{
    BYTE ucOsdSourcePort = _VGA_A0;

    switch(UserAdjustGetSelectRegionPort())
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            ucOsdSourcePort = _VGA_A0;
            return ucOsdSourcePort;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:
#if(_D0_INPUT_PORT_TYPE == _D0_DVI_PORT)
            ucOsdSourcePort = _DVI_D0;
#endif

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) || (_D0_INPUT_PORT_TYPE == _D0_MHL_PORT))
            ucOsdSourcePort = _HDMI_D0;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            ucOsdSourcePort = _DP_D0;
#endif
            return ucOsdSourcePort;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:
#if(_D1_INPUT_PORT_TYPE == _D1_DVI_PORT)
            ucOsdSourcePort = _DVI_D1;
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) || (_D1_INPUT_PORT_TYPE == _D1_MHL_PORT))
            ucOsdSourcePort = _HDMI_D1;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            ucOsdSourcePort = _DP_D1;
#endif
            return ucOsdSourcePort;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:
#if((_D2_INPUT_PORT_TYPE == _D2_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
            if(_DVI_D2 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D2;
            }
#endif

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
            if(_HDMI_D2 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D2;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:
#if((_D3_INPUT_PORT_TYPE == _D3_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
            if(_DVI_D3 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D3;
            }
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
            if(_HDMI_D3 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D3;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:
#if((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
            if(_DVI_D4 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D4;
            }
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
            if(_HDMI_D4 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D4;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
        case _D5_INPUT_PORT:
#if(_D5_INPUT_PORT_TYPE == _D5_DVI_PORT)
            if(_DVI_D5 > 0x04)
            {
                ucOsdSourcePort = 0x03;
            }
            else
            {
                ucOsdSourcePort = _DVI_D5;
            }
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
            if(_HDMI_D5 > 0x12)
            {
                ucOsdSourcePort = 0x11;
            }
            else
            {
                ucOsdSourcePort = _HDMI_D5;
            }
#endif
            return ucOsdSourcePort;
#endif

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
        case _D6_INPUT_PORT:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            if(_DP_D6 > 0x10)
            {
                ucOsdSourcePort = 0x0F;
            }
            else
            {
                ucOsdSourcePort = _DP_D6;
            }
#endif
            return ucOsdSourcePort;
#endif

        default:
            return ucOsdSourcePort;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispDisableOsd(void)
{
    SET_OSD_IN_FACTORY_MENU_STATUS(_FALSE);
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
    SET_OSD_STATE(_MENU_NONE);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncDisableOsd();
    g_ucOsdWidth = 0;
    g_ucOsdHeight = 0;
    g_ucOsdWidthB = 0;
    g_ucOsdHeightB = 0;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispSetPosition(BYTE ucType, EnumOsdPositionType enumOsdPositionType, WORD usHPos, WORD usVPos)
{
    DWORD ulX = 0;
    DWORD ulY = 0;
    BYTE ucFonWidth = 12;
    BYTE ucFonHeight = 18;
    BYTE ucHorizontalDelayStep = 4;
    BYTE ucTempWidth = g_ucOsdWidth;
    BYTE ucTempHeight = g_ucOsdHeight;

    if((enumOsdPositionType == _OSD_POSITION_GLOBAL_B) ||
       (enumOsdPositionType == _OSD_POSITION_FONT_B))
    {
        ucTempWidth = g_ucOsdWidthB;
        ucTempHeight = g_ucOsdHeightB;
    }

    if(ScalerOsdGetHorizontalDelayStep() == _OSD_HORIZONTAL_DELAY_STEP_1_PIXEL)
    {
        ucHorizontalDelayStep = 1;
    }

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth *= 2;
        ucFonHeight *= 2;
    }

    if(ucType == _POS_PERCENT)
    {
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#elif(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempHeight * ucFonHeight) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempWidth * ucFonWidth) * usVPos) / _OSD_V_POS_MAX;
        }
        else
        {
            ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
            ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
        }
#else
        ulX = ((((DWORD)(_PANEL_DH_WIDTH) - (DWORD)ucTempWidth * ucFonWidth) / ucHorizontalDelayStep) * usHPos) / _OSD_H_POS_MAX;
        ulY = (((DWORD)_PANEL_DV_HEIGHT - (DWORD)ucTempHeight * ucFonHeight) * usVPos) / _OSD_V_POS_MAX;
#endif
    }
    else
    {
        // Notice!!! if osd set double size need to chek real position
        ulX = usHPos;
        ulY = usVPos;
    }
    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ulX = ulX / 2;
        ulY = ulY / 2;
    }

    OsdFuncSetPosition(enumOsdPositionType, ulX, ulY);
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuItemIndication(BYTE ucItem, BYTE ucAmount, BYTE ucState)
{
    BYTE ucI = 0;
    BYTE ucRow = 10;
    BYTE ucCol = 4;
    BYTE ucColor = 0;

    if(ucState == _OSD_REJECT)
    {
        OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));
        return;
    }

    for(ucI = 0; ucI < ucAmount; ucI++)
    {
        if((ucState == _OSD_SELECT) && (ucI == ucItem))
        {
            ucColor = COLOR(_CP_PINK, _CP_BG);
        }
        else
        {
            ucColor = COLOR(_CP_GRAY, _CP_BG);
        }

        OsdFontPut1Bit(ucRow, ucCol + ucI, _iINDICATE, ucColor);
    }

    if(ucAmount < 20)
    {
        OsdFuncClearOsd(ucRow, ucCol + ucAmount, WIDTH(20 - ucAmount), HEIGHT(1));
    }
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuKeyInfo(BYTE ucItem, BYTE ucState)
{
    // _KEY_INFO_ALL
    BYTE ucColor = COLOR(_CP_BLUE, _CP_BG);
    BYTE ucRow = 20;
    BYTE ucCol = 22;
    BYTE ucInterval = 5;
    BYTE ucIsMainMenu = _FALSE;

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        if((g_ucOsdWidth == _OSD_MAIN_MENU_HEIGHT) && (g_ucOsdHeight == _OSD_MAIN_MENU_WIDTH))
        {
            ucIsMainMenu = _TRUE;
        }
    }
    else
#endif
    {
        if((g_ucOsdWidth == _OSD_MAIN_MENU_WIDTH) && (g_ucOsdHeight == _OSD_MAIN_MENU_HEIGHT))
        {
            ucIsMainMenu = _TRUE;
        }
    }

    if(ucIsMainMenu == _FALSE)
    {
        return;
    }


    if((ucState == _OSD_SELECT) || (ucState == _OSD_HIGHLIGHT))
    {
        ucColor = COLOR(_CP_PINK, _CP_BG);
        ScalerTimerReactiveTimerEvent(SEC(0.05), _USER_TIMER_EVENT_OSD_KEYINFO_UNHIGHLIGHT);
    }

    switch(ucItem)
    {
        case _KEY_INFO_ENTER:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 0)), tOSD_iKEY_ENTER, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2));
            }

            break;

        case _KEY_INFO_EXIT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_EXIT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_LEFT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 2)), tOSD_iKEY_LEFT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_RIGHT:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 3)), tOSD_iKEY_RIGHT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_BACK:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_BACK, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
            }
            break;

        case _KEY_INFO_ALL:
            if((ucState == _OSD_SELECT) || (ucState == _OSD_UNSELECT))
            {
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 0)), tOSD_iKEY_ENTER, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 1)), tOSD_iKEY_EXIT, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 2)), tOSD_iKEY_LEFT, ucColor);
                OsdFontPut1BitTable(ucRow, (ucCol + (ucInterval * 3)), tOSD_iKEY_RIGHT, ucColor);
            }
            else if((ucState == _OSD_HIGHLIGHT) || (ucState == _OSD_UNHIGHLIGHT))
            {
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
                OsdFuncChangeColor1Bit(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2), ucColor, _FONTFROM_0_255);
            }
            else
            {
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 0)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 1)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 2)), WIDTH(2), HEIGHT(2));
                OsdFuncClearOsd(ucRow, (ucCol + (ucInterval * 3)), WIDTH(2), HEIGHT(2));
            }
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispClearSelectColor(BYTE ucUpDown)
{
    if(ucUpDown == _UP)
    {
        ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
    }
    else
    {
        ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
        // ScalerOsdWindowDisable(_OSD_WINDOW_4_3);
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainSubString(BYTE ucState)
{
    switch(ucState)
    {
        case _AUTO_CONFIG_DO:
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_RED, _CP_BG);
            OsdPropPutString(ROW(14), COL(19), _PFONT_PAGE_1, _STRING_AUTO_ADJUST, COLOR(_CP_BG, _CP_BG), _ENGLISH);
            OsdPropPutString(ROW(16), COL(19), _PFONT_PAGE_1, _STRING_PLEASE_WAIT, COLOR(_CP_BG, _CP_BG), _ENGLISH);
            break;

        case _AUTO_CONFIG_RESULT:
            if(g_usAdjustValue != 100)
            {
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_RED, _CP_BG);
                OsdPropPutStringCenter(ROW(15), COL(0), WIDTH(_OSD_MAIN_MENU_WIDTH), _PFONT_PAGE_1, _STRING_FAIL, COLOR(_CP_BG, _CP_BG), _ENGLISH);
            }
            else
            {
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(17), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_GREEN_119, _CP_BG);
                OsdPropPutStringCenter(ROW(15), COL(0), WIDTH(_OSD_MAIN_MENU_WIDTH), _PFONT_PAGE_1, _STRING_PASS, COLOR(_CP_BG, _CP_BG), _ENGLISH);
            }
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainOptionIcon(BYTE ucIconPos, BYTE ucIcon, BYTE ucColor)
{
    BYTE ucRow = 4;
    BYTE ucCol = 4;

    ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
    ucCol = COL(4) + ((ucIconPos % 4) * 10);

    if(ucIcon == _ICON_NONE)
    {
        OsdFuncClearOsd(ucRow, (ucCol - 2), WIDTH(10), HEIGHT(5));
        return;
    }

    // icon
    OsdFontVLCDynamicLoadIcon(ucIconPos, ucIcon);
    OsdFontPut1BitMainMenuIcon(ucRow, ucCol, (_1DYNAMIC_ICON_START + (ucIconPos * 24)), ucColor, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuIconString(BYTE ucIconPos, WORD usIcon, BYTE ucColor)
{
    BYTE ucRow = 4;
    BYTE ucCol = 4;
    BYTE ucFontPage = _PFONT_PAGE_0;
    WORD usIconLoad = 0;

    ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
    ucCol = COL(4) + ((ucIconPos % 4) * 10);

    if(usIcon == _MENU_NONE)
    {
        OsdFuncClearOsd(ucRow, (ucCol - 2), WIDTH(10), HEIGHT(5));
        return;
    }

    // icon
    if((usIcon >= _ICON_A0_PORT) && (usIcon <= _ICON_D7_PORT))
    {
        switch(usIcon)
        {
            case _ICON_A0_PORT:
                usIconLoad = _A0_INPUT_TYPE;
                break;
            case _ICON_D0_PORT:
                usIconLoad = _D0_INPUT_TYPE;
                break;
            case _ICON_D1_PORT:
                usIconLoad = _D1_INPUT_TYPE;
                break;
            case _ICON_D2_PORT:
                usIconLoad = _D2_INPUT_TYPE;
                break;
            case _ICON_D3_PORT:
                usIconLoad = _D3_INPUT_TYPE;
                break;
            case _ICON_D4_PORT:
                usIconLoad = _D4_INPUT_TYPE;
                break;
            case _ICON_D5_PORT:
                usIconLoad = _D5_INPUT_TYPE;
                break;
            case _ICON_D6_PORT:
                usIconLoad = _D6_INPUT_TYPE;
                break;
            case _ICON_D7_PORT:
                usIconLoad = _D7_INPUT_TYPE;
                break;
            default:
                break;
        }

        OsdFontVLCDynamicLoadIcon(ucIconPos, usIconLoad);
    }
    else
    {
        OsdFontVLCDynamicLoadIcon(ucIconPos, usIcon);
    }
    OsdFontPut1BitMainMenuIcon(ucRow, ucCol, (_1DYNAMIC_ICON_START + (ucIconPos * 24)), ucColor, _CP_BG);

    // string
    ucRow += 4;
    ucCol -= 2;
    OsdFuncClearOsd(ucRow, ucCol, WIDTH(10), HEIGHT(1));

    if((ucIconPos / 4) > 0)
    {
        ucFontPage = _PFONT_PAGE_1;
    }

    if((usIcon >= _ICON_A0_PORT) && (usIcon <= _ICON_D7_PORT))
    {
        OsdPropPutStringCenter(ucRow, ucCol, WIDTH(10), ucFontPage, (usIcon - _ICON_INPUT_END + _STRIN_END), COLOR(ucColor, _CP_BG), _ENGLISH);
    }
    else
    {
        OsdPropPutStringCenter(ucRow, ucCol, WIDTH(10), ucFontPage, usIcon - 1, COLOR(ucColor, _CP_BG), _ENGLISH);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuIconPage(BYTE ucUpDown, BYTE ucState)
{
    BYTE pucOsdItemColor[4];
    BYTE ucI = 0;

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    // color selection
    if(ucUpDown == _UP)
    {
        // up
        for(ucI = 0; ucI < 4; ucI++)
        {
            pucOsdItemColor[ucI] = _CP_LIGHTBLUE;
        }
    }
    else
    {
        // down
        for(ucI = 0; ucI < 4; ucI++)
        {
            pucOsdItemColor[ucI] = _CP_BLUE;
        }
    }

    // Arrow
    if(ucUpDown == _UP)
    {
        switch(ucState)
        {
            case _ICON_PAGE_CLEAR:
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                break;

            case _ICON_PAGE_ANALOG_0:
            case _ICON_PAGE_COLOR_0:
            case _ICON_PAGE_ADVANCE_0:
            case _ICON_PAGE_AUDIO_0:
            case _ICON_PAGE_OTHER_0:
#if (_EDID_SWITCH_BY_PORT_ITEM == _ON)
            case _ICON_PAGE_EDID_PORT_0:
#endif
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);

#if(_VGA_SUPPORT == _ON)
                if((ucState == _ICON_PAGE_ANALOG_0) &&
                   (SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
                   (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
                {
                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                }
                else
#endif
                {
                    OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_UNSELECT);
                }
                break;

            case _ICON_PAGE_MAIN_0:
            case _ICON_PAGE_MAIN_1:
            case _ICON_PAGE_MAIN_2:
            case _ICON_PAGE_COLOR_1:
            case _ICON_PAGE_OTHER_1:
            case _ICON_PAGE_ADVANCE_1:
#if((_ULTRA_HDR_SUPPORT == _ON) || (_FALSE_COLOR_SUPPORT == _ON))
            case _ICON_PAGE_ADVANCE_2:
#endif
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_UNSELECT);
                break;

            case _ICON_PAGE_ANALOG_1:
            case _ICON_PAGE_COLOR_2:
            case _ICON_PAGE_AUDIO_1:
            case _ICON_PAGE_OTHER_2:
            case _ICON_PAGE_ADVANCE_3:
#if (_EDID_SWITCH_BY_PORT_ITEM == _ON)
            case _ICON_PAGE_EDID_PORT_1:
#endif
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                break;

            default:
                OsdDispMainMenuArrow(_UP, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_UP, _RIGHT, _OSD_REJECT);
                break;
        }
    }
    else
    {
        switch(ucState)
        {
            case _ICON_PAGE_CLEAR:
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                break;

            case _ICON_PAGE_DISPLAYMODE_0:
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
#if(_4P_DISPLAY_SUPPORT == _ON)
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
#else
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
#endif
                break;
            case _ICON_PAGE_CLONE_0:
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                    break;
                }
                break;

            case _ICON_PAGE_SELECTREGION_4P_0:
            case _ICON_PAGE_ANALOG_0:
            case _ICON_PAGE_COLOR_0:
            case _ICON_PAGE_ADVANCE_0:
            case _ICON_PAGE_AUDIO_0:
            case _ICON_PAGE_OTHER_0:
            case _ICON_PAGE_GAMMA_0:
            case _ICON_PAGE_TEMPRATURE_0:
            case _ICON_PAGE_COLOR_EFFECT_0:
            case _ICON_PAGE_COLOR_DEMO_0:
            case _ICON_PAGE_COLOR_EFFECT_USER_0:
            case _ICON_PAGE_ASPECT_RATIO_0:
            case _ICON_PAGE_PIP_POSITION_0:
            case _ICON_PAGE_DISP_ROTATE_0:
#if (_FALSE_COLOR_SUPPORT == _ON)
            case _ICON_PAGE_FALSE_COLOR_0:
#endif
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);

#if(_VGA_SUPPORT == _ON)
                if((ucState == _ICON_PAGE_ANALOG_0) &&
                   (SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
                   (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
                {
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
#endif
                {
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
                break;

            case _ICON_PAGE_SELECTREGION_4P_1:
            case _ICON_PAGE_COLOR_1:
            case _ICON_PAGE_OTHER_1:
            case _ICON_PAGE_CLONE_1:
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                break;

            case _ICON_PAGE_COLOR_PCM_0:
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
#endif
                break;

            case _ICON_PAGE_DISPLAYMODE_1:
            case _ICON_PAGE_SELECTREGION_4P_2:
            case _ICON_PAGE_ANALOG_1:
            case _ICON_PAGE_COLOR_2:
            case _ICON_PAGE_ADVANCE_1:
            case _ICON_PAGE_AUDIO_1:
            case _ICON_PAGE_OTHER_2:
            case _ICON_PAGE_GAMMA_1:
            case _ICON_PAGE_TEMPRATURE_1:
            case _ICON_PAGE_COLOR_EFFECT_1:
            case _ICON_PAGE_COLOR_DEMO_1:
            case _ICON_PAGE_COLOR_PCM_1:
            case _ICON_PAGE_COLOR_EFFECT_USER_1:
            case _ICON_PAGE_ASPECT_RATIO_1:
            case _ICON_PAGE_PIP_POSITION_1:
            case _ICON_PAGE_AUDIO_SOURCE_1:
            case _ICON_PAGE_CLONE_2:
            case _ICON_PAGE_DISP_ROTATE_1:
#if (_FALSE_COLOR_SUPPORT == _ON)
            case _ICON_PAGE_FALSE_COLOR_1:
#endif

                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                break;

            case _ICON_PAGE_AUDIO_SOURCE_0:
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                break;

            case _ICON_PAGE_INPUT_0:
            case _ICON_PAGE_INPUT_1:
            case _ICON_PAGE_INPUT_2:
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                break;

            default:
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                break;
        }
    }

    ucUpDown *= _ICON_POS_DOWN_0;

    switch(ucState)
    {
        case _ICON_PAGE_CLEAR:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_NONE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_MAIN_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_DISPLAYMODE, pucOsdItemColor[0]);
            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB) ||
               (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP))
            {
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DISPLAYFUNCTION, pucOsdItemColor[1]);
            }
            else
            {
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DISPLAYFUNCTION, _CP_GRAY);
            }

            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) || (GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF))
            {
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_SELECTREGION, _CP_GRAY);
            }
            else
            {
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_SELECTREGION, pucOsdItemColor[2]);
            }
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_PICTURE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_MAIN_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_ANALOG, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_COLOR, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_ADVANCE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_INPUT, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_MAIN_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_AUDIO, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_OTHER, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_INFORMATION, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_FACTORY, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DISPLAYMODE_0:
#if(_PBP_LR_DISPLAY_SUPPORT == _OFF)
            pucOsdItemColor[1] = _CP_GRAY;
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _OFF)
            pucOsdItemColor[2] = _CP_GRAY;
#endif

#if(_PIP_DISPLAY_SUPPORT == _OFF)
            pucOsdItemColor[3] = _CP_GRAY;
#endif

            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_1P, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_2P_LR, pucOsdItemColor[1]);

            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_2P_TB, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_2P_PIP, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DISPLAYMODE_1:

            pucOsdItemColor[1] = _CP_GRAY;

            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_4P, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DISPLAYFUNCTION:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
#if (_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                // Force Display_Rotate & Lantency set Gray Icon
                pucOsdItemColor[0] = _CP_GRAY;
                pucOsdItemColor[1] = _CP_GRAY;
#endif
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_DISP_ROTATE, pucOsdItemColor[0]);

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
                if(GET_OSD_DISP_ROTATE() != _DISP_ROTATE_0)
                {
                    pucOsdItemColor[1] = _CP_GRAY;
                }
#endif
#else
                pucOsdItemColor[1] = _CP_GRAY;
#endif // End of #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)

                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_LANTENCY, pucOsdItemColor[1]);

#if(_FREEZE_SUPPORT == _ON)
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_FREEZE, pucOsdItemColor[2]);
#else
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_FREEZE, _CP_GRAY);
#endif

                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
#if (_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                // Force to Gray Icon
                pucOsdItemColor[0] = _CP_GRAY;
#endif
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_DISP_LR_RATIO, pucOsdItemColor[0]);
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_INPUT_SWAP, pucOsdItemColor[1]);
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
            {
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_INPUT_SWAP, pucOsdItemColor[0]);
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            }

            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
            {
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PIP_POSITION, pucOsdItemColor[0]);

#if(_PIP_BLENDING_SUPPORT == _ON)
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_PIP_TRANSPARENCY, pucOsdItemColor[1]);
#else
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_PIP_TRANSPARENCY, _CP_GRAY);
#endif

                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_PIP_SIZE, pucOsdItemColor[2]);
                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_INPUT_SWAP, pucOsdItemColor[3]);
            }
            break;

        case _ICON_PAGE_SELECTREGION_2P_LR:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_2P_LR_L, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_2P_LR_R, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_2P_LR_FULL, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_SELECTREGION_2P_TB:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_2P_TB_T, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_2P_TB_B, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_2P_TB_FULL, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_SELECTREGION_2P_PIP:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_2P_PIP_MAIN, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_2P_PIP_SUB, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_2P_PIP_FULL, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_SELECTREGION_4P_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_4P_LT_INSIDE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_4P_LT_OUTSIDE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_4P_LB_INSIDE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_4P_LB_OUTSIDE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_SELECTREGION_4P_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_4P_RT_INSIDE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_4P_RT_OUTSIDE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_4P_RB_INSIDE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_4P_RB_OUTSIDE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_SELECTREGION_4P_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_4P_FULL, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INPUT_2P_LR:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_2P_LR_L, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_2P_LR_R, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INPUT_2P_TB:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_2P_TB_T, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_2P_TB_B, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INPUT_2P_PIP:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_2P_PIP_MAIN, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_2P_PIP_SUB, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INPUT_4P:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_4P_LT_INSIDE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_4P_LB_INSIDE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_4P_RT_INSIDE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_4P_RB_INSIDE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_PICTURE_0:

#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {
                pucOsdItemColor[0] = _CP_GRAY;
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
            }
#endif
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_BACKLIGHT, pucOsdItemColor[0]);

#if(_BRIGHTNESS_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_BRIGHTNESS, pucOsdItemColor[1]);
#else
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_BRIGHTNESS, _CP_GRAY);
#endif

#if(_CONTRAST_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_CONTRAST, pucOsdItemColor[2]);
#else
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_CONTRAST, _CP_GRAY);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_SHARPNESS, pucOsdItemColor[3]);
#else
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_SHARPNESS, _CP_GRAY);
#endif
            break;

        case _ICON_PAGE_ANALOG_0:

#if(_VGA_SUPPORT == _ON)
            if(((SysVgaGetRegion() == _DISPLAY_RGN_NONE) || (SysRegionGetDisplayState(SysVgaGetRegion()) != _DISPLAY_STATE_ACTIVE)))
#endif
            {
                for(ucI = 0; ucI < 4; ucI++)
                {
                    pucOsdItemColor[ucI] = _CP_GRAY;
                }
            }
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_HPOS, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_VPOS, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_AUTO_ADJUST, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_CLOCK, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ANALOG_1:

#if(_VGA_SUPPORT == _ON)
            if(((SysVgaGetRegion() == _DISPLAY_RGN_NONE) || (SysRegionGetDisplayState(SysVgaGetRegion()) != _DISPLAY_STATE_ACTIVE)))
#endif
            {
                pucOsdItemColor[0] = _CP_GRAY;
            }
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PHASE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_0:
#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {
                pucOsdItemColor[0] = _CP_GRAY;
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
            }
#endif

            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PANEL_UNIFORMITY, pucOsdItemColor[0]);

#if(_PCM_FUNCTION == _ON)
            // Skip Gamma if PCM != native
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
            {
                pucOsdItemColor[1] = _CP_GRAY;
            }
#endif
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_GAMMA, pucOsdItemColor[1]);

#if(_CONTRAST_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_COLOR_TEMPERATURE, pucOsdItemColor[2]);
#else
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_COLOR_TEMPERATURE, _CP_GRAY);
#endif
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_COLOR_EFFECT, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_1:
#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {
                pucOsdItemColor[1] = _CP_GRAY;
                pucOsdItemColor[2] = _CP_GRAY;
                pucOsdItemColor[3] = _CP_GRAY;
            }
#endif
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_COLOR_DEMO, pucOsdItemColor[0]);

#if(_PCM_FUNCTION == _ON)
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_PCM, pucOsdItemColor[2]);
#else
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_PCM, _CP_GRAY);
#endif

            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_HUE, pucOsdItemColor[3]);

            if((GET_OSD_SYSTEM_SELECT_REGION() != _PBP_LR_FULL_REGION) &&
               (GET_OSD_SYSTEM_SELECT_REGION() != _PBP_TB_FULL_REGION) &&
               (GET_OSD_SYSTEM_SELECT_REGION() != _PIP_FULL_REGION) &&
               (GET_OSD_SYSTEM_SELECT_REGION() != _4P_FULL_REGION) &&
               (GET_OSD_SYSTEM_SELECT_REGION() != _4P_LT_OUTSIDE) &&
               (GET_OSD_SYSTEM_SELECT_REGION() != _4P_LB_OUTSIDE) &&
               (GET_OSD_SYSTEM_SELECT_REGION() != _4P_RT_OUTSIDE) &&
               (GET_OSD_SYSTEM_SELECT_REGION() != _4P_RB_OUTSIDE) &&
               (GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF))
            {
#if(_COLOR_FORMAT_CONVERT == _ON)
                if((SysRegionGetDisplayState(GET_OSD_SYSTEM_DISPLAY_REGION()) == _DISPLAY_STATE_ACTIVE) &&
                   ((SysRegionGetSourceType((EnumDisplayRegion)GET_OSD_SYSTEM_SELECT_REGION()) == _SOURCE_VGA) ||
                    (SysRegionGetSourceType((EnumDisplayRegion)GET_OSD_SYSTEM_SELECT_REGION()) == _SOURCE_DVI)))
                {
                    OsdDispMainMenuIconString((ucUpDown + 1), _ICON_COLOR_FORMAT, pucOsdItemColor[1]);
                }
                else
#endif
                {
                    OsdDispMainMenuIconString((ucUpDown + 1), _ICON_COLOR_FORMAT, _CP_GRAY);
                }
            }
            else
            {
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_COLOR_FORMAT, _CP_GRAY);
            }

            break;

        case _ICON_PAGE_COLOR_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_SATURATION, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ADVANCE_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_ASPECT, pucOsdItemColor[0]);
#if(_OVERSCAN_SUPPORT == _OFF)
            pucOsdItemColor[1] = _CP_GRAY;
#endif
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_OVER_SCAN, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_OVER_DRIVE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_DDCCI, pucOsdItemColor[3]);

            break;

        case _ICON_PAGE_ADVANCE_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_ULTRAVIVID, pucOsdItemColor[0]);

#if(_DCR_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DCR, pucOsdItemColor[1]);
#else
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DCR, _CP_GRAY);
#endif

            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_DP_OPTION, pucOsdItemColor[2]);

#if(_DP_MST_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_DP_MST, pucOsdItemColor[3]);
#endif
            break;

        case _ICON_PAGE_ADVANCE_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_DP_EDID, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_CLONE, pucOsdItemColor[1]);

#if(_FREESYNC_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_FREESYNC, pucOsdItemColor[2]);
#else
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_FREESYNC, _CP_GRAY);
#endif

            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_DP_LANE, pucOsdItemColor[3]);

            break;

        case _ICON_PAGE_ADVANCE_3:

#if(_ULTRA_HDR_SUPPORT == _ON)
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_4P)
            {
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_HDR, pucOsdItemColor[0]);
            }
            else
            {
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_HDR, _CP_GRAY);
            }
#if(_FALSE_COLOR_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_FASLE_COLOR, pucOsdItemColor[0]);
#else
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[0]);
#endif

            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
#else

#if(_FALSE_COLOR_SUPPORT == _ON)
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_FASLE_COLOR, pucOsdItemColor[0]);
#else
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_NONE, pucOsdItemColor[0]);
#endif
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
#endif
            break;

        case _ICON_PAGE_INPUT_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_A0_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D0_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D1_PORT, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D2_PORT, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INPUT_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D3_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D4_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D5_PORT, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D6_PORT, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INPUT_2:

            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D7_PORT, pucOsdItemColor[0]);
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_INPUT_AUTO, pucOsdItemColor[1]);
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            }
            else
            {
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D7_PORT, _CP_GRAY);
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_INPUT_AUTO, pucOsdItemColor[1]);
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            }
            break;

        case _ICON_PAGE_AUDIO_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_VOLUME, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_MUTE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_STAND_ALONG, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_AUDIO_SOURCE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_AUDIO_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_SOUND_MODE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_OTHER_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_RESET, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_MENU_TIME, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_OSD_HPOS, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_OSD_VPOS, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_OTHER_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_LANGUAGE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_TRNASPARENCY, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_ROTATE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_BORDER_WIDTH, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_OTHER_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_BORDER_COLOR, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_INFORMATION_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_NONE, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ON_OFF:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ON, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_OFF, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ASPECT_RATIO_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AS_RATIO_FULL, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_AS_RATIO_16_9, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_AS_RATIO_4_3, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_AS_RATIO_5_4, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ASPECT_RATIO_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AS_RATIO_ORIGINAL, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_AUDIO_SOURCE_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AUDIO_ANALOG, pucOsdItemColor[0]);

            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) &&
               ((SysRegionGetSourceType(_DISPLAY_RGN_1P) == _SOURCE_VGA) ||
                (SysRegionGetSourceType(_DISPLAY_RGN_1P) == _SOURCE_DVI)))
            {
                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            }
            else
            {
                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_AUDIO_DIGITAL_REGION_1, pucOsdItemColor[1]);
            }

            OsdDispMainOptionIcon((ucUpDown + 2), ((GET_OSD_DISPLAY_MODE() >= _OSD_DM_2P_LR) ? (_ICON_AUDIO_DIGITAL_REGION_2) : (_ICON_NONE)), pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), ((GET_OSD_DISPLAY_MODE() >= _OSD_DM_4P) ? (_ICON_AUDIO_DIGITAL_REGION_3) : (_ICON_NONE)), pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_AUDIO_SOURCE_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_AUDIO_DIGITAL_REGION_4, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_ULTRA_VIVID:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ULTRA_VIVID_L, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_ULTRA_VIVID_M, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_ULTRA_VIVID_H, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_GAMMA_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_GAMMA_1_8, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_GAMMA_2_0, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_GAMMA_2_2, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_GAMMA_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_GAMMA_2_4, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_TEMPRATURE_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_9300, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_7500, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_6500, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_TEMP_5800, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_TEMPRATURE_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_SRGB, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_USER, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_EFFECT_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_EFF_STD, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_GAME, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_EFF_MOVIE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_EFF_PHOTO, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_EFFECT_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_EFF_VIVID, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_DEMO_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_DEMO_TYPE1, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_DEMO_TYPE2, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_DEMO_TYPE3, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_DEMO_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_DEMO_TYPE4, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_DEMO_TYPE5, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_FORMAT:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_FORMAT_RGB, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_FORMAT_YUV, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_TEMPERATURE_USER:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_R, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_TEMP_USER_G, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_USER_B, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_PCM_0:
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_PCM_USER, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_PCM_NACTIVE, pucOsdItemColor[3]);
#if(_OCC_SUPPORT == _ON)
            for(ucI = 0; ucI < 4; ucI++)
            {
                pucOsdItemColor[ucI] = _CP_BLUE;
            }
#else
            for(ucI = 0; ucI < 4; ucI++)
            {
                pucOsdItemColor[ucI] = _CP_GRAY;
            }
#endif
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_PCM_SRGB, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_PCM_ADOBE_RGB, pucOsdItemColor[1]);
            break;

        case _ICON_PAGE_COLOR_PCM_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_PCM_SOFT_PROFT, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_EFFECT_USER_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_R, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER_Y, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_TEMP_USER_G, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_EFF_USER_C, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_EFFECT_USER_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER_B, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_EFF_USER_M, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_COLOR_RGBYCM_HUE_SAT:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_HUE, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_SATURATION, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_PCM_SOFT_PROFT:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_MODE1, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_MODE2, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_OSD_ROTATE:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_0_DEGREE, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_90_DEGREE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_270_DEGREE, pucOsdItemColor[2]);

#if(_OSD_ROTATE_CW180_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_180_DEGREE, pucOsdItemColor[3]);
#else
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_180_DEGREE, _CP_GRAY);
#endif
            break;

        case _ICON_PAGE_OD_ADJUST:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ONOFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_OD_GAIN, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DP_OPTION:
#if(_D0_INPUT_PORT_TYPE != _D0_DP_PORT)
            pucOsdItemColor[0] = _CP_GRAY;
#endif
#if(_D1_INPUT_PORT_TYPE != _D1_DP_PORT)
            pucOsdItemColor[1] = _CP_GRAY;
#endif
#if(_D6_INPUT_PORT_TYPE != _D6_DP_PORT)
            pucOsdItemColor[2] = _CP_GRAY;
#endif

            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D6, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DP_1_DOT_X:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_1_DOT_1, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_1_DOT_2, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_1_DOT_3, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DP_MST:
#if((_D0_INPUT_PORT_TYPE != _D0_DP_PORT) || (_D0_DP_MST_PORT_SUPPORT == _OFF))
            pucOsdItemColor[1] = _CP_GRAY;
#else
            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                pucOsdItemColor[1] = _CP_GRAY;
            }
#endif

#if((_D1_INPUT_PORT_TYPE != _D1_DP_PORT) || (_D1_DP_MST_PORT_SUPPORT == _OFF))
            pucOsdItemColor[2] = _CP_GRAY;
#else
            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                pucOsdItemColor[2] = _CP_GRAY;
            }
#endif

#if((_D6_INPUT_PORT_TYPE != _D6_DP_PORT) ||\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _OFF)))
            pucOsdItemColor[3] = _CP_GRAY;
#else
            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                pucOsdItemColor[3] = _CP_GRAY;
            }
#endif
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D0, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D1, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_D6, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DISP_ROTATE_0:
            OsdDispMainOptionIcon((ucUpDown++), _ICON_0_DEGREE, pucOsdItemColor[0]);
#if(_DISPLAY_ROTATION_90_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown++), _ICON_90_DEGREE, pucOsdItemColor[0]);
#endif
#if(_DISPLAY_ROTATION_180_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown++), _ICON_180_DEGREE, pucOsdItemColor[0]);
#endif
#if(_DISPLAY_ROTATION_270_SUPPORT == _ON)
            OsdDispMainOptionIcon((ucUpDown++), _ICON_270_DEGREE, pucOsdItemColor[0]);
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
            if(_DISP_ROTATE_HOR_MIRROR <= 3)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_HOR_MIRROR, pucOsdItemColor[0]);
            }
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
            if(_DISP_ROTATE_VER_MIRROR <= 3)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_VER_MIRROR, pucOsdItemColor[0]);
            }
#endif
            break;

        case _ICON_PAGE_DISP_ROTATE_1:

#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
            if(_DISP_ROTATE_HOR_MIRROR > 3)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_HOR_MIRROR, pucOsdItemColor[0]);
            }
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
            if(_DISP_ROTATE_VER_MIRROR > 3)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_VER_MIRROR, pucOsdItemColor[0]);
            }
#endif
            OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[3]);
            if(_DISP_ROTATE_AMOUNT < 6)
            {
                OsdDispMainOptionIcon((ucUpDown++), _ICON_NONE, pucOsdItemColor[0]);
            }

            break;

        case _ICON_PAGE_LATENCY:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_ULTRA_VIVID_L, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ULTRA_VIVID_M, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_ULTRA_VIVID_H, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_DP_EDID:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_SINGLE_DP_EDID, pucOsdItemColor[0]);
#if (_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DUAL_DP_EDID, pucOsdItemColor[1]);
#else
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_DUAL_DP_EDID, _CP_GRAY);
#endif
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_CLONE_0:
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                OsdDispMainMenuIconString((ucUpDown + 0), _ICON_NONE, pucOsdItemColor[0]);
                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
                OsdDispMainMenuIconString((ucUpDown + 1), _ICON_A0_PORT, pucOsdItemColor[1]);
                OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D0_PORT, pucOsdItemColor[2]);
                OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D1_PORT, pucOsdItemColor[3]);
            }
            else
            {
                OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
                OsdDispMainOptionIcon((ucUpDown + 1), _ICON_ON, pucOsdItemColor[1]);
                OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
                OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            }
            break;

        case _ICON_PAGE_CLONE_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D2_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D3_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D4_PORT, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D5_PORT, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_CLONE_2:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D6_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_BORDER_COLOR:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_COLOR_R, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_G, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_B, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_W, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_PIP_POSITION_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_PIP_POSITION_LT, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_PIP_POSITION_RT, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_PIP_POSITION_LB, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_PIP_POSITION_RB, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_PIP_POSITION_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_PIP_POSITION_MIDDLE, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_PIP_POSITION_USER, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_PIP_USER_POSITION:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_PIP_USER_POSITION_H, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_PIP_USER_POSITION_V, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_SINGLE_DP_EDID:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_DP_1080P, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_DP_2560_1440, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_DP_4K2K_30HZ, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_DP_4K2K_60HZ, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_DUAL_DP_EDID:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_DP_5K3K_60HZ, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_DP_4K2K_144HZ, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
#if(_EDID_SWITCH_BY_PORT_ITEM == _ON)
        case _ICON_PAGE_EDID_PORT_0:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D0_PORT, pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D1_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D2_PORT, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_D3_PORT, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_EDID_PORT_1:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_D4_PORT,  pucOsdItemColor[0]);
            OsdDispMainMenuIconString((ucUpDown + 1), _ICON_D5_PORT, pucOsdItemColor[1]);
            OsdDispMainMenuIconString((ucUpDown + 2), _ICON_D6_PORT, pucOsdItemColor[2]);
            OsdDispMainMenuIconString((ucUpDown + 3), _ICON_DUAL_DP_EDID, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_HDMI_EDID_D0:
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_NONE,  pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_EDID_HDMI_1_4,  pucOsdItemColor[0]);
#endif
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE,  pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_EDID_HDMI_2_0, pucOsdItemColor[1]);
#endif
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE,  pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_EDID_HDMI_2_0_HDR, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_HDMI_EDID_D1:
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_NONE,  pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_EDID_HDMI_1_4,  pucOsdItemColor[0]);
#endif
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE,  pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_EDID_HDMI_2_0, pucOsdItemColor[1]);
#endif
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE,  pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_EDID_HDMI_2_0_HDR, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_HDMI_EDID_D2:
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_NONE,  pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_EDID_HDMI_1_4,  pucOsdItemColor[0]);
#endif
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE,  pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_EDID_HDMI_2_0, pucOsdItemColor[1]);
#endif
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE,  pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_EDID_HDMI_2_0_HDR, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_HDMI_EDID_D3:
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_NONE,  pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_EDID_HDMI_1_4,  pucOsdItemColor[0]);
#endif
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE,  pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_EDID_HDMI_2_0, pucOsdItemColor[1]);
#endif
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE,  pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_EDID_HDMI_2_0_HDR, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_HDMI_EDID_D4:
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_NONE,  pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_EDID_HDMI_1_4,  pucOsdItemColor[0]);
#endif
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE,  pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_EDID_HDMI_2_0, pucOsdItemColor[1]);
#endif
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE,  pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_EDID_HDMI_2_0_HDR, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_HDMI_EDID_D5:
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_NONE,  pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_EDID_HDMI_1_4,  pucOsdItemColor[0]);
#endif
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE,  pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_EDID_HDMI_2_0, pucOsdItemColor[1]);
#endif
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE,  pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_EDID_HDMI_2_0_HDR, pucOsdItemColor[2]);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
#endif

        case _ICON_PAGE_DP_LANE_COUNT:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, pucOsdItemColor[0]);
#else
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_D0, _CP_GRAY);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, pucOsdItemColor[1]);
#else
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_D1, _CP_GRAY);
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D6, pucOsdItemColor[2]);
#else
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_D6, _CP_GRAY);
#endif
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);

            break;
        case _ICON_PAGE_DP_LANE_X:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_INPUT_AUTO, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_2_LANE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_4_LANE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

#if(_ULTRA_HDR_SUPPORT == _ON)
        case _ICON_PAGE_HDR_ADJUST:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
            {
                for(ucI = 0; ucI < 4; ucI++)
                {
                    pucOsdItemColor[ucI] = _CP_GRAY;
                }
            }
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_HDR_MODE, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_DARK_ENHANCE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;

        case _ICON_PAGE_HDR_MODE:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_INPUT_AUTO, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_HDR_MODE_SMPTE_ST_2084, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
#endif

#if (_FALSE_COLOR_SUPPORT == _ON)
        case _ICON_PAGE_FALSE_COLOR_0:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_OFF, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_COLOR_DEMO_TYPE1, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_COLOR_DEMO_TYPE2, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_COLOR_DEMO_TYPE3, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_FALSE_COLOR_1:
            OsdDispMainOptionIcon((ucUpDown + 0), _ICON_TEMP_USER, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
        case _ICON_PAGE_FALSE_COLOR_USER:
            OsdDispMainMenuIconString((ucUpDown + 0), _ICON_FASLE_COLOR, pucOsdItemColor[0]);
            OsdDispMainOptionIcon((ucUpDown + 1), _ICON_NONE, pucOsdItemColor[1]);
            OsdDispMainOptionIcon((ucUpDown + 2), _ICON_NONE, pucOsdItemColor[2]);
            OsdDispMainOptionIcon((ucUpDown + 3), _ICON_NONE, pucOsdItemColor[3]);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuArrow(BYTE ucUpDown, BYTE ucLeftRight, BYTE ucState)
{
    BYTE ucIcon = _iLEFT_00;
    BYTE ucColor = COLOR(_CP_WHITE, _CP_BG);
    BYTE ucCol = 1;
    BYTE ucRow = 5;

    if(ucUpDown == _DOWN)
    {
        ucRow = 15;
        ucColor = COLOR(_CP_BLUE, _CP_BG);
    }

    if(ucLeftRight == _RIGHT)
    {
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            ucCol = g_ucOsdHeight - 2;
        }
        else
#endif
        {
            ucCol = g_ucOsdWidth - 2;
        }
        ucIcon = _iRIGHT_00;
    }

    if(ucState == _OSD_SELECT)
    {
        ucColor = COLOR(_CP_ORANGE, _CP_BG);
    }

    if(ucState == _OSD_REJECT)
    {
        OsdFontPut1Bit(ucRow, ucCol, ___, ucColor);
        OsdFontPut1Bit(ucRow + 1, ucCol, ___, ucColor);
    }
    else
    {
        OsdFontPut1Bit(ucRow, ucCol, ucIcon, ucColor);
        OsdFontPut1Bit(ucRow + 1, ucCol, ucIcon + 1, ucColor);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuOptionSetting(BYTE ucItem, BYTE ucSelectState, BYTE ucOption)
{
    BYTE ucRow = 0;
    BYTE ucCol = COL(4);
    BYTE ucWin = _OSD_WINDOW_4_2;
    BYTE ucWinColor = _CP_LIGHTBLUE;
    BYTE ucForegroundColor = _CP_ORANGE;

    ucRow = ROW(14);

    if(ucSelectState == _SELECT)
    {
        ucForegroundColor = _CP_ORANGE;
    }
    else
    {
        ucForegroundColor = _CP_WHITE;
    }

    switch(ucItem)
    {
        case _OPTION_OVERSCAN_ONOFF:
        case _OPTION_OVERDRIVE_ONOFF:
        case _OPTION_DCR_ONOFF:
        case _OPTION_DDCCI_ONOFF:
        case _OPTION_MUTE_ONOFF:
        case _OPTION_STAND_ALONG_ONOFF:
        case _OPTION_PANEL_UNIFORMITY_ONOFF:
        case _OPTION_COLOR_EFFC_USER_RGBYCM:
        case _OPTION_FREESYNC_ONOFF_TYPE:
        case _OPTION_FREEZE_ONOFF_TYPE:
#if(_ULTRA_HDR_SUPPORT == _ON)
        case _OPTION_DARK_ENHANCE_ON_OFF:
#endif
            if(ucOption == _ON)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_AUDIO_SOURCE:
            ucCol = COL(4) + ((ucOption % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_ASPECT_RATIO_TYPE:
            if((ucOption == _OSD_ASPECT_RATIO_FULL) ||
               (ucOption == _OSD_ASPECT_RATIO_ORIGIN))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ASPECT_RATIO_16_BY_9)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ASPECT_RATIO_4_BY_3)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ASPECT_RATIO_5_BY_4)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_ADVANCE_ASPECT_ADJUST)
            {
                if(ucOption >= _OSD_ASPECT_RATIO_ORIGIN)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_ULTRA_VIVID_TYPE:
            if(ucOption == _ULTRA_VIVID_OFF)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _ULTRA_VIVID_L)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _ULTRA_VIVID_M)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _ULTRA_VIVID_H)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_GAMMA_TYPE:
            if((ucOption == _GAMMA_OFF) || (ucOption == _GAMMA_24))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _GAMMA_18)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _GAMMA_20)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _GAMMA_22)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_COLOR_GAMMA_ADJUST)
            {
                if(ucOption >= _GAMMA_24)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_TEMPRATURE_TYPE:
            if((ucOption == _CT_9300) || (ucOption == _CT_SRGB))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if((ucOption == _CT_7500) || (ucOption == _CT_USER))
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _CT_6500)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _CT_5800)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_COLOR_TEMPERATURE_ADJUST)
            {
                if(ucOption >= _CT_SRGB)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_EFFECT_TYPE:
            if((ucOption == _COLOREFFECT_STANDARD) || (ucOption == _COLOREFFECT_VIVID))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if((ucOption == _COLOREFFECT_GAME) || (ucOption == _COLOREFFECT_USER))
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _COLOREFFECT_MOVIE)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _COLOREFFECT_PHOTO)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_COLOR_EFFECT_ADJUST)
            {
                if(ucOption >= _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_DEMO_TYPE:
            if((ucOption == _HL_WIN_OFF) || (ucOption == _HL_WIN_4))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if((ucOption == _HL_WIN_1) || (ucOption == _HL_WIN_5))
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _HL_WIN_2)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _HL_WIN_3)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            if(GET_OSD_STATE() == _MENU_COLOR_DEMO_ADJUST)
            {
                if(ucOption >= _HL_WIN_4)
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
                }
                else
                {
                    OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                    OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
                }
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_FORMAT_TYPE:
            if(ucOption == _COLOR_SPACE_RGB)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else
            {
                // digital
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_PCM_TYPE:
#if(_OCC_SUPPORT == _ON)
#if(_RGB_3D_GAMMA == _ON)
            if((ucOption == _PCM_OSD_SRGB) || (ucOption == _PCM_OSD_SOFT_PROFT))
#else
            if(ucOption == _PCM_OSD_SRGB)
#endif
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_OSD_ADOBE_RGB)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_OSD_USER)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_OSD_NATIVE)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
#else
            if(ucOption == _PCM_OSD_USER)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_OSD_NATIVE)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
#endif

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
            if(ucOption >= _PCM_OSD_SOFT_PROFT)
            {
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_UNSELECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_REJECT);
            }
            else
            {
                OsdDispMainMenuArrow(_DOWN, _LEFT, _OSD_REJECT);
                OsdDispMainMenuArrow(_DOWN, _RIGHT, _OSD_UNSELECT);
            }
#endif

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_PCM_SOFT_PROFT_TYPE:

            if(ucOption == _PCM_SOFT_MODE_1)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _PCM_SOFT_MODE_2)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_TEMPRATURE_USER_ADJUST:
            ucWin = _OSD_WINDOW_4_1;
            ucWinColor = _CP_BLUE;
            ucRow = ROW(4);
            ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            ucForegroundColor = _CP_BLUE_120;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_EFFC_USER_ADJUST:
            ucWin = _OSD_WINDOW_4_1;
            ucWinColor = _CP_BLUE;
            ucRow = ROW(4);
            ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            ucForegroundColor = _CP_BLUE_120;

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_COLOR_RGBYCM_HUE_STA:

            if(ucOption == _COLOR_HUE)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _COLOR_SATURATION)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_ROTATE_ADJUST:
            if(ucOption == _OSD_ROTATE_DEGREE_0)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ROTATE_DEGREE_90)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ROTATE_DEGREE_270)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_ROTATE_DEGREE_180)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_INPUT_SOURCE_TYPE:
            ucCol = COL(4) + ((GET_OSD_1P_INPUT_SOURCE() % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_INPUT_MF_SOURCE_TYPE:
            ucCol = COL(4) + ((ucOption % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DP_PORT_VERSION:
            if(ucOption == _DP_VER_1_DOT_1)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_VER_1_DOT_2)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_VER_1_DOT_3)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DP_MST_TYPE:

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, (COL(4) + ((ucOption % 4) * 10) - 2), WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DISP_ROTATE_TYPE:
            if((ucOption % 4 == 0))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if((ucOption % 4 == 1))
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }

            else if((ucOption % 4 == 2))
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }

            else if((ucOption % 4 == 3))
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;

        case _OPTION_LATENCY_TYPE:
            if(ucOption == _LATENCY_L)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _LATENCY_M)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _LATENCY_H)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }

            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;

        case _OPTION_DP_EDID_TYPE:
            if(ucOption == _DP_EDID_1080P)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_EDID_2560_1440)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_EDID_4K2K_30HZ)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_EDID_4K2K_60HZ)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);

            break;

        case _OPTION_CLONE_TYPE:
            ucCol = COL(4) + ((ucOption % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DISPLATMODE_TYPE:
            ucCol = COL(4) + ((ucOption % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_SELECTREGION_TYPE:
            ucCol = COL(4) + ((ucOption % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_BORDER_COLOR:
            ucCol = COL(4) + ((ucOption % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_PIP_POSITION:
            ucCol = COL(4) + ((ucOption % 4) * 10) - 2;
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DUAL_DP_EDID_TYPE:
            if(ucOption == _DUAL_DP_EDID_5K3K_60HZ)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _DUAL_DP_EDID_4K2K_144HZ)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

        case _OPTION_DP_LANE_COUNT_SELECT:
            if(ucOption == _DP_LANE_AUTO_MODE)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            if(ucOption == _DP_TWO_LANE)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _DP_FOUR_LANE)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;

#if(_ULTRA_HDR_SUPPORT == _ON)
        case _OPTION_HDR_MODE_SELECT:
            if(ucOption == _HDR_MODE_OFF)
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            if(ucOption == _HDR_MODE_AUTO)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _HDR_MODE_SMPTE_ST_2084)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
        case _OPTION_FALSE_COLOR_TYPE:
            if((ucOption == _OSD_FALSE_COLOR_OFF) || (ucOption == _OSD_FALSE_COLOR_USER))
            {
                ucCol = COL(4) + ((_ITEM_0 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_FALSE_COLOR_MODE1)
            {
                ucCol = COL(4) + ((_ITEM_1 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_FALSE_COLOR_MODE2)
            {
                ucCol = COL(4) + ((_ITEM_2 % 4) * 10) - 2;
            }
            else if(ucOption == _OSD_FALSE_COLOR_MODE3)
            {
                ucCol = COL(4) + ((_ITEM_3 % 4) * 10) - 2;
            }
            OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
            break;
#endif

        default:
            break;
    }

    // ??
    if(ucItem == _OPTION_COLOR_PCM_TYPE)
    {
#if(_OCC_SUPPORT == _ON)
        OsdFuncChangeIconColor1Bit(ROW(14), _ITEM_6, WIDTH(g_ucOsdWidth), HEIGHT(4), _CP_BLUE);
#endif
    }
    else
    {
        // OsdFuncChangeIconColor1Bit(ROW(14), _ITEM_4, WIDTH(g_ucOsdWidth), HEIGHT(4), _CP_BLUE);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuItemSelection(BYTE ucIconPos, BYTE ucState)
{
    BYTE ucRow = 0;
    BYTE ucCol = 0;
    BYTE ucWin = _OSD_WINDOW_4_1;
    BYTE ucWinColor = _CP_BLUE;
    BYTE ucForegroundColor = _CP_ORANGE;

    ucRow = ((ucIconPos / 4) ? ROW(14) : ROW(4));
    ucCol = COL(4) + ((ucIconPos % 4) * 10) - 2;

    if(ucState == _OSD_UNSELECT)
    {
        if((ucIconPos / 4) > 0)
        {
            ScalerOsdWindowDisable(_OSD_WINDOW_4_2);
        }
        else
        {
            ScalerOsdWindowDisable(_OSD_WINDOW_4_1);
        }
        return;
    }
    else if(ucState == _OSD_PRE_SELECT)
    {
        ucForegroundColor = _CP_BLUE_120;
    }
    else if(ucState == _OSD_SELECT_ADJUST)
    {
        ucForegroundColor = _CP_ORANGE_DARK;
    }

    if((ucIconPos / 4) > 0)
    {
        ucWin = _OSD_WINDOW_4_2;
        ucWinColor = _CP_LIGHTBLUE;
    }

    OsdWindowDrawingByFontHighlight(ucWin, ucRow, ucCol, WIDTH(10), HEIGHT(5), ucWinColor, ucForegroundColor, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispClearArrow(BYTE ucUpDown)
{
    OsdDispMainMenuArrow(ucUpDown, _LEFT, _OSD_REJECT);
    OsdDispMainMenuArrow(ucUpDown, _RIGHT, _OSD_REJECT);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuSubSelect(BYTE ucItem, WORD usOsdState, WORD usOsdStatePrevious)
{
    WORD usItemPrev = 0;
    WORD usItemCurr = 0;

    switch(ucItem)
    {
        case _ICON_SUB_SEL_DISPLAYMODE:
            // previous state
            if((usOsdStatePrevious >= _MENU_DISPLAYMODE_1P) && (usOsdStatePrevious <= _MENU_DISPLAYMODE_4P))
            {
                usItemPrev = usOsdStatePrevious - _MENU_DISPLAYMODE_1P;
            }
            // current state
            if((usOsdState >= _MENU_DISPLAYMODE_1P) && (usOsdState <= _MENU_DISPLAYMODE_4P))
            {
                usItemCurr = usOsdState - _MENU_DISPLAYMODE_1P;
            }
            break;

        case _ICON_SUB_SEL_SELECTREGION:
            // previous state
            if((usOsdStatePrevious >= _MENU_SELECTREGIOM_2P_LR_L) && (usOsdStatePrevious <= _MENU_SELECTREGIOM_2P_LR_FULL))
            {
                usItemPrev = usOsdStatePrevious - _MENU_SELECTREGIOM_2P_LR_L;
            }
            else if((usOsdStatePrevious >= _MENU_SELECTREGIOM_2P_TB_T) && (usOsdStatePrevious <= _MENU_SELECTREGIOM_2P_TB_FULL))
            {
                usItemPrev = usOsdStatePrevious - _MENU_SELECTREGIOM_2P_TB_T;
            }
            else if((usOsdStatePrevious >= _MENU_SELECTREGIOM_2P_PIP_MAIN) && (usOsdStatePrevious <= _MENU_SELECTREGIOM_2P_PIP_FULL))
            {
                usItemPrev = usOsdStatePrevious - _MENU_SELECTREGIOM_2P_PIP_MAIN;
            }
            else if((usOsdStatePrevious >= _MENU_SELECTREGIOM_4P_LT_IN) && (usOsdStatePrevious <= _MENU_SELECTREGIOM_4P_FULL))
            {
                usItemPrev = usOsdStatePrevious - _MENU_SELECTREGIOM_4P_LT_IN;
            }

            // current state
            if((usOsdState >= _MENU_SELECTREGIOM_2P_LR_L) && (usOsdState <= _MENU_SELECTREGIOM_2P_LR_FULL))
            {
                usItemCurr = usOsdState - _MENU_SELECTREGIOM_2P_LR_L;
            }
            else if((usOsdState >= _MENU_SELECTREGIOM_2P_TB_T) && (usOsdState <= _MENU_SELECTREGIOM_2P_TB_FULL))
            {
                usItemCurr = usOsdState - _MENU_SELECTREGIOM_2P_TB_T;
            }
            else if((usOsdState >= _MENU_SELECTREGIOM_2P_PIP_MAIN) && (usOsdState <= _MENU_SELECTREGIOM_2P_PIP_FULL))
            {
                usItemCurr = usOsdState - _MENU_SELECTREGIOM_2P_PIP_MAIN;
            }
            else if((usOsdState >= _MENU_SELECTREGIOM_4P_LT_IN) && (usOsdState <= _MENU_SELECTREGIOM_4P_FULL))
            {
                usItemCurr = usOsdState - _MENU_SELECTREGIOM_4P_LT_IN;
            }
            break;

        default:
            break;
    }
    OsdDispMainMenuItemSelection((usItemPrev % 4) + 4, _OSD_UNSELECT);
    OsdDispMainMenuItemSelection((usItemCurr % 4) + 4, _OSD_SELECT);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenuCursor(WORD usOsdState, WORD usOsdStatePrevious, bit bInSubsidiary)
{
    WORD usItem = 0;
    WORD usAmount = 0;
    WORD usOsdCount = 0;

    if(bInSubsidiary == _OUTSUBSET)
    {
        usOsdCount = usOsdState;
    }
    else
    {
        usOsdCount = usOsdStatePrevious;
    }

    if((usOsdCount >= _MENU_DISPLAYMODE) && (usOsdCount <= _MENU_FACTORY))
    {
        usItem = usOsdCount - _MENU_DISPLAYMODE;
        usAmount = (_MENU_FACTORY - _MENU_DISPLAYMODE + 1);
    }
    else if((usOsdCount >= _MENU_DISPLAYMODE_1P) && (usOsdCount <= _MENU_DISPLAYMODE_4P))
    {
        usItem = usOsdCount - _MENU_DISPLAYMODE_1P;
        usAmount = (_MENU_DISPLAYMODE_4P - _MENU_DISPLAYMODE_1P + 1);
    }
    else if((usOsdCount >= _MENU_DISPLAYFUN_DISP_ROTATE) && (usOsdCount <= _MENU_DISPLAYFUN_FREEZE))
    {
        usItem = usOsdCount - _MENU_DISPLAYFUN_DISP_ROTATE;
        usAmount = (_MENU_DISPLAYFUN_FREEZE - _MENU_DISPLAYFUN_DISP_ROTATE + 1);
    }
    else if((usOsdCount >= _MENU_DISPLAYFUN_LR_RATIO) && (usOsdCount <= _MENU_DISPLAYFUN_LR_INPUT_SWAP))
    {
        usItem = usOsdCount - _MENU_DISPLAYFUN_LR_RATIO;
        usAmount = (_MENU_DISPLAYFUN_LR_INPUT_SWAP - _MENU_DISPLAYFUN_LR_RATIO + 1);
    }
    else if((usOsdCount >= _MENU_DISPLAYFUN_TB_INPUT_SWAP) && (usOsdCount <= _MENU_DISPLAYFUN_TB_INPUT_SWAP))
    {
        usItem = usOsdCount - _MENU_DISPLAYFUN_TB_INPUT_SWAP;
        usAmount = (_MENU_DISPLAYFUN_TB_INPUT_SWAP - _MENU_DISPLAYFUN_TB_INPUT_SWAP + 1);
    }
    else if((usOsdCount >= _MENU_DISPLAYFUN_PIP_POSITION) && (usOsdCount <= _MENU_DISPLAYFUN_PIP_INPUT_SWAP))
    {
        usItem = usOsdCount - _MENU_DISPLAYFUN_PIP_POSITION;
        usAmount = (_MENU_DISPLAYFUN_PIP_INPUT_SWAP - _MENU_DISPLAYFUN_PIP_POSITION + 1);
    }
    else if((usOsdCount >= _MENU_DISPLAYFUN_PIP_POSITION_H) && (usOsdCount <= _MENU_DISPLAYFUN_PIP_POSITION_V))
    {
        usItem = usOsdCount - _MENU_DISPLAYFUN_PIP_POSITION_H;
        usAmount = (_MENU_DISPLAYFUN_PIP_POSITION_V - _MENU_DISPLAYFUN_PIP_POSITION_H + 1);
    }
    else if((usOsdCount >= _MENU_PICTURE_BACKLIGHT) && (usOsdCount <= _MENU_PICTURE_SHARPNESS))
    {
        usItem = usOsdCount - _MENU_PICTURE_BACKLIGHT;
        usAmount = (_MENU_PICTURE_SHARPNESS - _MENU_PICTURE_BACKLIGHT + 1);
    }
    else if((usOsdCount >= _MENU_ANALOG_AUTO) && (usOsdCount <= _MENU_ANALOG_PHASE))
    {
        usItem = usOsdCount - _MENU_ANALOG_AUTO;
        usAmount = (_MENU_ANALOG_PHASE - _MENU_ANALOG_AUTO + 1);
    }
    else if((usOsdCount >= _MENU_COLOR_PANEL_UNIFORMITY) && (usOsdCount <= _MENU_COLOR_SATURATION))
    {
        usItem = usOsdCount - _MENU_COLOR_PANEL_UNIFORMITY;
        usAmount = (_MENU_COLOR_SATURATION - _MENU_COLOR_PANEL_UNIFORMITY + 1);
    }
#if(_ULTRA_HDR_SUPPORT == _ON)
#if(_FALSE_COLOR_SUPPORT == _ON)
    else if((usOsdCount >= _MENU_ADVANCE_ASPECT) && (usOsdCount <= _MENU_ADVANCE_FALSE_COLOR))
    {
        usItem = usOsdCount - _MENU_ADVANCE_ASPECT;
        usAmount = (_MENU_ADVANCE_FALSE_COLOR - _MENU_ADVANCE_ASPECT + 1);
    }
#else
    else if((usOsdCount >= _MENU_ADVANCE_ASPECT) && (usOsdCount <= _MENU_ADVANCE_HDR))
    {
        usItem = usOsdCount - _MENU_ADVANCE_ASPECT;
        usAmount = (_MENU_ADVANCE_HDR - _MENU_ADVANCE_ASPECT + 1);
    }
#endif
#else

#if(_FALSE_COLOR_SUPPORT == _ON)
    else if((usOsdCount >= _MENU_ADVANCE_ASPECT) && (usOsdCount <= _MENU_ADVANCE_FALSE_COLOR))
    {
        usItem = usOsdCount - _MENU_ADVANCE_ASPECT;
        usAmount = (_MENU_ADVANCE_FALSE_COLOR - _MENU_ADVANCE_ASPECT + 1);
    }
#else
    else if((usOsdCount >= _MENU_ADVANCE_ASPECT) && (usOsdCount <= _MENU_ADVANCE_DP_LANE_COUNT))
    {
        usItem = usOsdCount - _MENU_ADVANCE_ASPECT;
        usAmount = (_MENU_ADVANCE_DP_LANE_COUNT - _MENU_ADVANCE_ASPECT + 1);
    }
#endif

#endif
    else if((usOsdCount >= _MENU_INPUT_SOURCE_1P) && (usOsdCount <= _MENU_INPUT_SOURCE_4P))
    {
        usItem = usOsdCount - _MENU_INPUT_SOURCE_1P;
        if(GET_OSD_DISPLAY_MODE() != _OSD_DM_4P)
        {
            usAmount = 2;
        }
        else
        {
            usAmount = 4;
        }
    }
    else if((usOsdCount >= _MENU_AUDIO_VOLUME) && (usOsdCount <= _MENU_AUDIO_SOUND_MODE))
    {
        usItem = usOsdCount - _MENU_AUDIO_VOLUME;
        usAmount = (_MENU_AUDIO_SOUND_MODE - _MENU_AUDIO_VOLUME + 1);
    }
    else if((usOsdCount >= _MENU_OTHER_RESET) && (usOsdCount <= _MENU_OTHER_BORDER_COLOR))
    {
        usItem = usOsdCount - _MENU_OTHER_RESET;
        usAmount = (_MENU_OTHER_BORDER_COLOR - _MENU_OTHER_RESET + 1);
    }
    else if(usOsdCount == _MENU_COLOR_EFFECT_ADJUST)
    {
        usItem = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) - _COLOREFFECT_STANDARD;
        usAmount = _COLOREFFECT_AMOUNT;
    }
    else if((usOsdCount >= _MENU_COLOR_TEMP_USER_R) && (usOsdCount <= _MENU_COLOR_TEMP_USER_B))
    {
        usItem = usOsdCount - _MENU_COLOR_TEMP_USER_R;
        usAmount = (_MENU_COLOR_TEMP_USER_B - _MENU_COLOR_TEMP_USER_R + 1);
    }
    else if((usOsdCount >= _MENU_COLOR_EFF_USER_R) && (usOsdCount <= _MENU_COLOR_EFF_USER_M))
    {
        usItem = usOsdCount - _MENU_COLOR_EFF_USER_R;
        usAmount = (_MENU_COLOR_EFF_USER_M - _MENU_COLOR_EFF_USER_R + 1);
    }
    else if((usOsdCount >= _MENU_ADVANCE_OVER_DRIVE_ONOFF) && (usOsdCount <= _MENU_ADVANCE_OVER_DRIVE_GAIN))
    {
        usItem = usOsdCount - _MENU_ADVANCE_OVER_DRIVE_ONOFF;
        usAmount = (_MENU_ADVANCE_OVER_DRIVE_GAIN - _MENU_ADVANCE_OVER_DRIVE_ONOFF + 1);
    }
    else if((usOsdCount >= _MENU_ADVANCE_DP_OPTION_D0) && (usOsdCount <= _MENU_ADVANCE_DP_OPTION_D6))
    {
        usItem = usOsdCount - _MENU_ADVANCE_DP_OPTION_D0;
        usAmount = (_MENU_ADVANCE_DP_OPTION_D6 - _MENU_ADVANCE_DP_OPTION_D0 + 1);
    }
    else if((usOsdCount >= _MENU_ADVANCE_SINGLE_DP_EDID) && (usOsdCount <= _MENU_ADVANCE_DUAL_DP_EDID))
    {
        usItem = usOsdCount - _MENU_ADVANCE_SINGLE_DP_EDID;
        usAmount = (_MENU_ADVANCE_DUAL_DP_EDID - _MENU_ADVANCE_SINGLE_DP_EDID + 1);
    }

    else if((usOsdCount >= _MENU_ADVANCE_DP_LANE_COUNT_D0) && (usOsdCount <= _MENU_ADVANCE_DP_LANE_COUNT_D6))
    {
        usItem = usOsdCount - _MENU_ADVANCE_DP_LANE_COUNT_D0;
        usAmount = (_MENU_ADVANCE_DP_LANE_COUNT_D6 - _MENU_ADVANCE_DP_LANE_COUNT_D0 + 1);
    }
#if(_ULTRA_HDR_SUPPORT == _ON)
    else if((usOsdCount >= _MENU_ADVANCE_HDR_MODE) && (usOsdCount <= _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF))
    {
        usItem = usOsdCount - _MENU_ADVANCE_HDR_MODE;
        usAmount = (_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF - _MENU_ADVANCE_HDR_MODE + 1);
    }
#endif
#if (_EDID_SWITCH_BY_PORT_ITEM == _ON)
    else if((usOsdCount >= _MENU_ADVANCE_EDID_ADJUST))
    {
        usItem = g_usAdjustValue;
        usAmount = (_D7_INPUT_PORT-_D0_INPUT_PORT+1);
    }
#endif
    // Selection
    if(bInSubsidiary == _OUTSUBSET)
    {
        OsdDispMainMenuItemSelection((usItem % 4), _OSD_SELECT);
    }
    else if(bInSubsidiary == _INSUBSET)
    {
        OsdDispMainMenuItemSelection((usItem % 4), _OSD_PRE_SELECT);
    }

    // indicate
    if(bInSubsidiary == _OUTSUBSET)
    {
        OsdDispMainMenuItemIndication(usItem, usAmount, _OSD_SELECT);
    }
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMainMenu(void)
{
    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    OsdFuncApplyMap(WIDTH(_OSD_MAIN_MENU_WIDTH), HEIGHT(_OSD_MAIN_MENU_HEIGHT), COLOR(_CP_BLACK, _CP_BG));

//20140304 Abel
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdHeight / 2), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight / 2), _CP_LIGHTBLUE);
    }

    // Realtek Mark
    OsdFontPut1BitTable(ROW(0), COL(32), tOSD_iREALTEK, COLOR(_CP_WHITE, _CP_BG));

    // Main Menu Icon & String
    if(GET_OSD_STATE() == _MENU_DISPLAYMODE)
    {
        OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
        OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
        if(GET_OSD_DISPLAY_MODE() < _OSD_DM_4P)
        {
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_0);
        }
        else
        {
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
        }

        // Selection Arrow Indication
        OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
    }

    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
// VLC
// font put 1 bit
// font put 1 bit table
// font put 2 bit
// font put 2 bit table
// font put 4 bit
// font put 4 bit color

// Prop
// font put prop string

// window
// draw window

//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
void OsdDispSliderAndNumber(WORD usOsdState, WORD usValue)
{
    g_usAdjustValue = usValue;

    switch(usOsdState)
    {
        case _MENU_DISPLAYFUN_LR_RATIO:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PBP_LR_RATIO_MAX, _OSD_PBP_LR_RATIO_MIN, _OSD_PBP_LR_RATIO_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_DISPLAYFUN_PIP_TRANSPARENCY:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PIP_TRANSPARENCY_MAX, _OSD_PIP_TRANSPARENCY_MIN, _OSD_PIP_TRANSPARENCY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_DISPLAYFUN_PIP_SIZE:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PIP_SIZE_MAX, _OSD_PIP_SIZE_MIN, _OSD_PIP_SIZE_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_PICTURE_BACKLIGHT:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_BRIGHTNESS:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_CONTRAST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_SHARPNESS:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_PICTURE_BACKLIGHT_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_BACKLIGHT(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_BRIGHTNESS_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION(), UserCommonAdjustPercentToRealValue(g_usAdjustValue, _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_CONTRAST_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_CONTRAST(GET_OSD_SELECT_REGION(), UserCommonAdjustPercentToRealValue(g_usAdjustValue, _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_PICTURE_SHARPNESS_ADJUST:
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _SHARPNESS_MAX, _SHARPNESS_MIN, _OFF);
            SET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort(), g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_ANALOG_HPOS:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_ANALOG_VPOS:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_ANALOG_CLOCK:
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usAdjustValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _UNSELECT);
            }
#endif
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_ANALOG_PHASE:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_ANALOG_AUTO:
#if(_VGA_SUPPORT == _ON)
            g_usAdjustValue = 0;
            UserCommonAutoConfig();
#endif
            break;

        case _MENU_ANALOG_HPOS_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);

#if(_VGA_SUPPORT == _ON)
            SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_H_POSITION(), _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
#endif
            break;

        case _MENU_ANALOG_VPOS_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);

#if(_VGA_SUPPORT == _ON)
            SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_V_POSITION(), _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
#endif
            break;

#if(_VGA_SUPPORT == _ON)
        case _MENU_ANALOG_CLOCK_ADJUST:
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_CLOCK(), _SLIDER_0, _SELECT);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, usClockRangeMax, usClockRangeMin, _OFF);
                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usAdjustValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _SELECT);
            }
#endif
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_ANALOG_PHASE_ADJUST:
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PHASE_MAX, _OSD_PHASE_MIN, _OFF);
            SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_PHASE(), _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;
#endif

        case _MENU_COLOR_HUE:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_COLOR_SATURATION:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

#if(_GAMMA_FUNCTION == _ON)
        case _MENU_COLOR_GAMMA_ADJUST:
            SET_OSD_GAMMA(GET_OSD_SELECT_REGION(), OsdDisplayDetOverRange(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()), _GAMMA_24, _GAMMA_OFF, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));

            break;
#endif // End of #if(_GAMMA_FUNCTION == _ON)

        case _MENU_COLOR_TEMPERATURE_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _CT_USER, _CT_9300, _OFF);
            SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), g_usAdjustValue);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            break;

        case _MENU_COLOR_EFFECT_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _COLOREFFECT_USER, _COLOREFFECT_STANDARD, _OFF);
            SET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION(), g_usAdjustValue);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            break;

        case _MENU_COLOR_DEMO_ADJUST:
            SET_OSD_HLWIN_TYPE(OsdDisplayDetOverRange(GET_OSD_HLWIN_TYPE(), _HL_WIN_AMOUNT, _HL_WIN_OFF, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _SELECT, GET_OSD_HLWIN_TYPE());
            break;

        case _MENU_COLOR_PCM_ADJUST:
#if(_OCC_SUPPORT == _ON)
            SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), OsdDisplayDetOverRange(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()), _PCM_OSD_AMOUNT, _PCM_OSD_SRGB, _OFF));
            g_usAdjustValue = GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION());
#else
            SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), OsdDisplayDetOverRange(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()), _PCM_OSD_AMOUNT, _PCM_OSD_USER, _OFF));
#endif
            break;

        case _MENU_COLOR_HUE_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            SET_OSD_HUE(GET_OSD_SELECT_REGION(), UserCommonAdjustPercentToRealValue(g_usAdjustValue, _HUE_MAX, _HUE_MIN, _HUE_CENTER));
            break;

        case _MENU_COLOR_SATURATION_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            SET_OSD_SATURATION(GET_OSD_SELECT_REGION(), UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER));
            break;

        case _MENU_ADVANCE_ASPECT_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _OSD_ASPECT_RATIO_AMOUNT, _OSD_ASPECT_RATIO_FULL, _OFF);
            break;

        case _MENU_ADVANCE_OVER_SCAN_ADJUST:
            SET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort(), OsdDisplayDetOverRange(GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()), _ON, _OFF, _ON));
            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _SELECT, GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()));
            break;


        case _MENU_ADVANCE_ULTRA_VIVID_ADJUST:
            SET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION(), OsdDisplayDetOverRange(GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()), _ULTRA_VIVID_AMOUNT, _ULTRA_VIVID_OFF, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _SELECT, GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()));
            break;

        case _MENU_ADVANCE_DP_MST_ADJUST:
            OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _SELECT, GET_OSD_DP_MST());
            break;

        case _MENU_ADVANCE_FREESYNC_ADJUST:
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREE_SYNC_STATUS());
            break;

        case _MENU_ADVANCE_CLONE_ADJUST:
#if(_MULTI_DISPLAY_MAX != 0x01)
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_CLONE_MODE_MTP(), _OSD_CLONE_MTP_D6, _OSD_CLONE_MTP_OFF, _OFF);
                SET_OSD_CLONE_MODE_MTP(g_usAdjustValue);
            }
            else
#endif
            {
                g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_CLONE_MODE_1P(), _OSD_CLONE_1P_ON, _OSD_CLONE_1P_OFF, _OFF);
                SET_OSD_CLONE_MODE_1P(g_usAdjustValue);
            }
            break;

        case _MENU_ADVANCE_SINGLE_DP_EDID_ADJUST:
            UserCommonNVRamSetSystemData(_DP_EDID_SELECT, OsdDisplayDetOverRange(UserCommonNVRamGetSystemData(_DP_EDID_SELECT), _DP_EDID_4K2K_60HZ, _DP_EDID_1080P, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            break;

        case _MENU_ADVANCE_DUAL_DP_EDID_ADJUST:
            UserCommonNVRamSetSystemData(_DUAL_DP_EDID_SELECT, OsdDisplayDetOverRange(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT), _DUAL_DP_EDID_4K2K_144HZ, _DUAL_DP_EDID_5K3K_60HZ, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_DUAL_DP_EDID_TYPE, _SELECT, UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
            break;

#if(_FALSE_COLOR_SUPPORT == _ON)
        case _MENU_ADVANCE_FALSE_COLOR_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_FALSE_COLOR_STATUS(), _OSD_FALSE_COLOR_USER, _OSD_FALSE_COLOR_OFF, _OFF);
            SET_OSD_FALSE_COLOR_STATUS(g_usAdjustValue);
            break;
#endif

        case _MENU_AUDIO_VOLUME:
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_AUDIO_VOLUME_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_VOLUME(), _OSD_VOLUME_MAX, _OSD_VOLUME_MIN, _OFF);
            SET_OSD_VOLUME(g_usAdjustValue);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _SELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _MENU_AUDIO_MUTE_ON_OFF:
            SET_OSD_VOLUME_MUTE(OsdDisplayDetOverRange(GET_OSD_VOLUME_MUTE(), _ON, _OFF, _ON));
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _SELECT, GET_OSD_VOLUME_MUTE());
            break;

        case _MENU_AUDIO_AUDIO_SOURCE_SELECT:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(GET_OSD_AUDIO_SOURCE(), ((GET_OSD_DISPLAY_MODE() >= _OSD_DM_4P) ? (_OSD_AUDIO_SOURCE_DIGITAL_REGION_4) : (((GET_OSD_DISPLAY_MODE() >= _OSD_DM_2P_LR) ? (_OSD_AUDIO_SOURCE_DIGITAL_REGION_2) : (_OSD_AUDIO_SOURCE_DIGITAL_REGION_1)))), _OSD_AUDIO_SOURCE_ANALOG, _OFF);
            break;

        case _MENU_AUDIO_SOUND_MODE_SELECT:
            break;

        case _MENU_OTHER_MENU_TIME:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_OTHER_OSD_HPOS:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_OTHER_OSD_VPOS:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_OTHER_TRNASPARENCY:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_OTHER_BORDER_WIDTH:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_SR_WIDTH_MAX, _OSD_SR_WIDTH_MIN, _OSD_SR_WIDTH_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_DISPLAYFUN_DISP_ROTATE_ADJUST:
            SET_OSD_DISP_ROTATE(OsdDisplayDetOverRange(GET_OSD_DISP_ROTATE(), (_DISP_ROTATE_AMOUNT - 1), _DISP_ROTATE_0, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _SELECT, GET_OSD_DISP_ROTATE());
            break;

        case _MENU_DISPLAYFUN_LATENCY_ADJUST:
            SET_OSD_LATENCY(OsdDisplayDetOverRange(GET_OSD_LATENCY(), _LATENCY_AMOUNT, _LATENCY_L, _OFF));
            OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _SELECT, GET_OSD_LATENCY());
            break;

        case _MENU_DISPLAYFUN_LR_RATIO_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PBP_LR_RATIO_MAX, _OSD_PBP_LR_RATIO_MIN, _OFF);
            SET_OSD_PBP_LR_RATIO(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_PBP_LR_RATIO(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PBP_LR_RATIO_MAX, _OSD_PBP_LR_RATIO_MIN, _OSD_PBP_LR_RATIO_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_DISPLAYFUN_PIP_POSITION_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _PIP_POSITON_USER, _PIP_POSITON_LT, _OFF);
            break;

        case _MENU_DISPLAYFUN_PIP_POSITION_H:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PIP_USER_POSITION_H_MAX, _OSD_PIP_USER_POSITION_H_MIN, _OSD_PIP_USER_POSITION_H_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_DISPLAYFUN_PIP_POSITION_V:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PIP_USER_POSITION_V_MAX, _OSD_PIP_USER_POSITION_V_MIN, _OSD_PIP_USER_POSITION_V_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PIP_USER_POSITION_H_MAX, _OSD_PIP_USER_POSITION_H_MIN, _OFF);
            SET_OSD_PIP_USER_POSITION_H(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_PIP_USER_POSITION_H(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PIP_USER_POSITION_H_MAX, _OSD_PIP_USER_POSITION_H_MIN, _OSD_PIP_USER_POSITION_H_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PIP_USER_POSITION_V_MAX, _OSD_PIP_USER_POSITION_V_MIN, _OFF);
            SET_OSD_PIP_USER_POSITION_V(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_PIP_USER_POSITION_V(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PIP_USER_POSITION_V_MAX, _OSD_PIP_USER_POSITION_V_MIN, _OSD_PIP_USER_POSITION_V_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PIP_TRANSPARENCY_MAX, _OSD_PIP_TRANSPARENCY_MIN, _OFF);
            SET_OSD_PIP_TRANSPARENCY(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_PIP_TRANSPARENCY(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PIP_TRANSPARENCY_MAX, _OSD_PIP_TRANSPARENCY_MIN, _OSD_PIP_TRANSPARENCY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_DISPLAYFUN_PIP_SIZE_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_PIP_SIZE_MAX, _OSD_PIP_SIZE_MIN, _OFF);
            SET_OSD_PIP_SIZE(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_PIP_SIZE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_PIP_SIZE_MAX, _OSD_PIP_SIZE_MIN, _OSD_PIP_SIZE_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_MENU_TIME_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OFF);
            SET_OSD_TIME_OUT(g_usAdjustValue);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_OSD_HPOS_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_HPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_OSD_VPOS_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_VPOS(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_LANGUAGE_ADJUST:
            if((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE))
            {
                if(g_usAdjustValue == _ENGLISH)
                {
                    g_usAdjustValue = _CHINESE_T;
                }
                else
                {
                    g_usAdjustValue = _ENGLISH;
                }
            }
            break;

        case _MENU_OTHER_TRNASPARENCY_ADJUST:
            g_usAdjustValue= (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OFF);
            SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_ROTATE_ADJUST:
#if(_OSD_ROTATE_CW180_SUPPORT == _ON)
            g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_180, _OSD_ROTATE_DEGREE_0, _OFF);
#else
            g_usAdjustValue = OsdDisplayDetOverRange(GET_OSD_ROTATE_STATUS(), _OSD_ROTATE_DEGREE_270, _OSD_ROTATE_DEGREE_0, _OFF);
#endif
            break;

        case _MENU_OTHER_BORDER_WIDTH_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _OSD_SR_WIDTH_MAX, _OSD_SR_WIDTH_MIN, _OFF);
            SET_OSD_SELECT_REGION_WIDTH(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_SELECT_REGION_WIDTH(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_SR_WIDTH_MAX, _OSD_SR_WIDTH_MIN, _OSD_SR_WIDTH_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_OTHER_BORDER_COLOR_ADJUST:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _SELECT_REGION_COLOR_3, _SELECT_REGION_COLOR_0, _OFF);
            break;

        case _MENU_COLOR_TEMP_USER_R:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_COLOR_TEMP_USER_G:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_COLOR_TEMP_USER_B:
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _MENU_COLOR_TEMP_USER_ADJUST_R:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_COLOR_TEMP_USER_ADJUST_G:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_COLOR_TEMP_USER_ADJUST_B:
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, _USER_RGB_MAX, _USER_RGB_MIN, _OFF);
            SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_COLOR_EFF_USER_R_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_Y_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_G_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_C_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_B_HUE_ADJUST:
        case _MENU_COLOR_EFF_USER_M_HUE_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SIX_COLOR_HUE_MAX, _SIX_COLOR_HUE_MIN, _SIX_COLOR_HUE_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_SIX_COLOR_HUE(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SIX_COLOR_HUE_MAX, _SIX_COLOR_HUE_MIN, _SIX_COLOR_HUE_CENTER));
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_COLOR_EFF_USER_R_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_Y_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_G_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_C_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_B_SAT_ADJUST:
        case _MENU_COLOR_EFF_USER_M_SAT_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _SIX_COLOR_SATURATION_MAX, _SIX_COLOR_SATURATION_MIN, _SIX_COLOR_SATURATION_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            SET_OSD_SIX_COLOR_SATURATION(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _SIX_COLOR_SATURATION_MAX, _SIX_COLOR_SATURATION_MIN, _SIX_COLOR_SATURATION_CENTER));
            OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _MENU_ADVANCE_OD_GAIN_ADJUST:
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
            g_usAdjustValue = (BYTE)OsdDisplayDetOverRange(g_usAdjustValue, 100, 0, _OFF);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            SET_OSD_OD_GAIN(UserCommonAdjustPercentToRealValue(g_usAdjustValue, _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER));
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

#if(_ULTRA_HDR_SUPPORT == _ON)
        case _MENU_ADVANCE_HDR_MODE_ADJUST:
            g_usAdjustValue = OsdDisplayDetOverRange(g_usAdjustValue, _HDR_MODE_SMPTE_ST_2084, _HDR_MODE_OFF, _OFF);
            SET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort(),g_usAdjustValue);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _SELECT, GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()));
            break;

        case _MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST:
            SET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort(),OsdDisplayDetOverRange(GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()), _ON, _OFF, _ON));
            OsdDispMainMenuOptionSetting(_OPTION_DARK_ENHANCE_ON_OFF, _SELECT, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description    :
// Input Value    : None
// Output Value : None
//--------------------------------------------------
WORD OsdDisplayDetOverRange(WORD usValue, WORD usMax, WORD usMin, bit bCycle)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            if(usValue >= usMax)
            {
                if(bCycle == _ON)
                {
                    return usMin;
                }
                else
                {
                    return usMax;
                }
            }
            else
            {
                usValue++;
            }

            break;

        case _LEFT_KEY_MESSAGE:
            if (usValue <= usMin)
            {
                if(bCycle == _ON)
                {
                    return usMax;
                }
                else
                {
                    return usMin;
                }
            }
            else
            {
                usValue--;
            }
            break;

        default:
            break;
    }

    return usValue;
}

//--------------------------------------------------
// Description  : Six Color Get One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorGetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor)
{
    BYTE ucType = _INSIDE;

    switch(enumSelRegion)
    {
        // INSIDE
        case _1P_NORMAL_FULL_REGION:
        case _1P_ROTATION_FULL_REGION:
        case _PIP_FULL_REGION:
        case _PBP_LR_FULL_REGION:
        case _PBP_TB_FULL_REGION:
        case _4P_FULL_REGION:
        case _PIP_SUB:
        case _PBP_LR_R:
        case _PBP_TB_B:
        case _4P_LT:
        case _4P_LB:
        case _4P_RT:
        case _4P_RB:
        case _1P_NORMAL_DEMO_INSIDE:
        case _PIP_DEMO_INSIDE:
        case _PBP_LR_DEMO_INSIDE:
        case _PBP_TB_DEMO_INSIDE:
        case _4P_DEMO_INSIDE:

            ucType = _INSIDE;
            break;

        // OUTSIDE
        case _PIP_MAIN:
        case _PBP_LR_L:
        case _PBP_TB_T:
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
        case _1P_NORMAL_DEMO_OUTSIDE:
        case _PIP_DEMO_OUTSIDE:
        case _PBP_LR_DEMO_OUTSIDE:
        case _PBP_TB_DEMO_OUTSIDE:
        case _4P_DEMO_OUTSIDE:

            ucType = _OUTSIDE;
            break;

        default:
            break;
    }

    switch(ucColor)
    {
        // DOUBLE CHECK HERE
        case _SIXCOLOR_R:
            SET_OSD_SIX_COLOR_HUE(g_pstOsdRegionData[ucType].ucSixColorHueR);
            SET_OSD_SIX_COLOR_SATURATION(g_pstOsdRegionData[ucType].ucSixColorSaturationR);
            break;

        case _SIXCOLOR_Y:
            SET_OSD_SIX_COLOR_HUE(g_pstOsdRegionData[ucType].ucSixColorHueY);
            SET_OSD_SIX_COLOR_SATURATION(g_pstOsdRegionData[ucType].ucSixColorSaturationY);
            break;

        case _SIXCOLOR_G:
            SET_OSD_SIX_COLOR_HUE(g_pstOsdRegionData[ucType].ucSixColorHueG);
            SET_OSD_SIX_COLOR_SATURATION(g_pstOsdRegionData[ucType].ucSixColorSaturationG);
            break;

        case _SIXCOLOR_C:
            SET_OSD_SIX_COLOR_HUE(g_pstOsdRegionData[ucType].ucSixColorHueC);
            SET_OSD_SIX_COLOR_SATURATION(g_pstOsdRegionData[ucType].ucSixColorSaturationC);
            break;

        case _SIXCOLOR_B:
            SET_OSD_SIX_COLOR_HUE(g_pstOsdRegionData[ucType].ucSixColorHueB);
            SET_OSD_SIX_COLOR_SATURATION(g_pstOsdRegionData[ucType].ucSixColorSaturationB);
            break;

        case _SIXCOLOR_M:
            SET_OSD_SIX_COLOR_HUE(g_pstOsdRegionData[ucType].ucSixColorHueM);
            SET_OSD_SIX_COLOR_SATURATION(g_pstOsdRegionData[ucType].ucSixColorSaturationM);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Six Color Set One Color
// Input Value  : SixColor
// Output Value : None
//--------------------------------------------------
void OsdDisplaySixColorSetOneColor(EnumSelRegion enumSelRegion, BYTE ucColor)
{
    BYTE ucType = _INSIDE;

    switch(enumSelRegion)
    {
        // INSIDE
        case _1P_NORMAL_FULL_REGION:
        case _1P_ROTATION_FULL_REGION:
        case _PIP_FULL_REGION:
        case _PBP_LR_FULL_REGION:
        case _PBP_TB_FULL_REGION:
        case _4P_FULL_REGION:
        case _PIP_SUB:
        case _PBP_LR_R:
        case _PBP_TB_B:
        case _4P_LT:
        case _4P_LB:
        case _4P_RT:
        case _4P_RB:
        case _1P_NORMAL_DEMO_INSIDE:
        case _PIP_DEMO_INSIDE:
        case _PBP_LR_DEMO_INSIDE:
        case _PBP_TB_DEMO_INSIDE:
        case _4P_DEMO_INSIDE:

            ucType = _INSIDE;
            break;

        // OUTSIDE
        case _PIP_MAIN:
        case _PBP_LR_L:
        case _PBP_TB_T:
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
        case _1P_NORMAL_DEMO_OUTSIDE:
        case _PIP_DEMO_OUTSIDE:
        case _PBP_LR_DEMO_OUTSIDE:
        case _PBP_TB_DEMO_OUTSIDE:
        case _4P_DEMO_OUTSIDE:

            ucType = _OUTSIDE;
            break;

        default:
            break;
    }

    switch(ucColor)
    {
        case _SIXCOLOR_R:
            g_pstOsdRegionData[ucType].ucSixColorHueR = GET_OSD_SIX_COLOR_HUE();
            g_pstOsdRegionData[ucType].ucSixColorSaturationR = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_Y:
            g_pstOsdRegionData[ucType].ucSixColorHueY = GET_OSD_SIX_COLOR_HUE();
            g_pstOsdRegionData[ucType].ucSixColorSaturationY = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_G:
            g_pstOsdRegionData[ucType].ucSixColorHueG = GET_OSD_SIX_COLOR_HUE();
            g_pstOsdRegionData[ucType].ucSixColorSaturationG = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_C:
            g_pstOsdRegionData[ucType].ucSixColorHueC = GET_OSD_SIX_COLOR_HUE();
            g_pstOsdRegionData[ucType].ucSixColorSaturationC = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_B:
            g_pstOsdRegionData[ucType].ucSixColorHueB = GET_OSD_SIX_COLOR_HUE();
            g_pstOsdRegionData[ucType].ucSixColorSaturationB = GET_OSD_SIX_COLOR_SATURATION();
            break;

        case _SIXCOLOR_M:
            g_pstOsdRegionData[ucType].ucSixColorHueM = GET_OSD_SIX_COLOR_HUE();
            g_pstOsdRegionData[ucType].ucSixColorSaturationM = GET_OSD_SIX_COLOR_SATURATION();
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispHotKeyOptionMenu(BYTE ucOption)
{
    BYTE uctemp = 0;

    OsdFuncDisableOsd();
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdWidth, _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(24), g_ucOsdHeight, _CP_LIGHTBLUE);
    }

    // title
    switch(ucOption)
    {
        case _HOTKEY_DDCCI:
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DDCCI);

            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // string
            OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_DDCCI, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);


            (GET_OSD_DDCCI_STATUS() == _ON) ? (uctemp = 1) : (uctemp = 2);

            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);


            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_ON);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);

            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_OFF);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;


        default:
            break;
    }
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyOptionMenuSwitch(BYTE ucOption)
{
    BYTE uctemp = 0;

    switch(ucOption)
    {
        case _HOTKEY_DDCCI:
            SET_OSD_DDCCI_STATUS(~(GET_OSD_DDCCI_STATUS()));
            (GET_OSD_DDCCI_STATUS() == _ON) ? (uctemp = 1) : (uctemp = 2);
            OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(3 + (12 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
            ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS());
            UserCommonDdcciMapping();
            break;

        default:
            break;
    }

    RTDNVRamSaveOsdUserData();
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuIcon(BYTE ucPort)
{
    BYTE ucCol = 5;

    if(GET_OSD_STATE() == _MENU_HOTKEY_SOURCE)
    {
        OsdFuncClearOsd(ROW(6), COL(13), WIDTH(47), HEIGHT(1));
        OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_INPUT, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

        // Left & Right Arrow
        OsdFontPut1Bit(ROW(3), COL(13), _iLEFT_00, COLOR(_CP_BLUE, _CP_BG));
        OsdFontPut1Bit(ROW(3) + 1, COL(13), _iLEFT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

        OsdFontPut1Bit(ROW(3), COL(62), _iRIGHT_00, COLOR(_CP_BLUE, _CP_BG));
        OsdFontPut1Bit(ROW(3) + 1, COL(62), _iRIGHT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

        if(ucPort <= _OSD_INPUT_D2)
        {
            // A0
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _A0_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_A0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D0
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D0_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D0_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);


            // D1
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D1_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D1_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D2
            OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D2_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D2_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        }
        else if((ucPort > _OSD_INPUT_D2) && (ucPort <= _OSD_INPUT_D6))
        {
            // D3
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D3_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D3_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D4
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _D4_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_D4_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D5
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _D5_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 3)), _PFONT_PAGE_1, _STRING_D5_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // D6
            OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _D6_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 4)), _PFONT_PAGE_1, _STRING_D6_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        }
        else
        {
            // D7
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _D7_INPUT_TYPE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 1)), _PFONT_PAGE_1, _STRING_D7_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // auto
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_INPUT_AUTO);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdPropPutString(ROW(6), COL(ucCol + (12 * 2)), _PFONT_PAGE_1, _STRING_AUTOSELECT_PORT, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            // None
            OsdFuncClearOsd(ROW(2), COL(3 + (12 * 3)), WIDTH(32 - 12), HEIGHT(4));
        }
    }
    else
    {
        if((ucPort >= _OSD_INPUT_D7) && (ucPort <= _OSD_INPUT_AUTO))
        {
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
        }
        else if((ucPort >= _OSD_INPUT_A0) && (ucPort <= _OSD_INPUT_D2))
        {
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
        }
        else if((ucPort >= _OSD_INPUT_D3) && (ucPort <= _OSD_INPUT_D6))
        {
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
        }
    }
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenuSwitch(BYTE ucPort)
{
    if(GET_OSD_STATE() == _MENU_HOTKEY_SOURCE)
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * ((ucPort % 4) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
    else
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_2, ROW(14), COL(4 + ((ucPort % 4) * 10) - 2), WIDTH(10), HEIGHT(5), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeySourceMenu(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        if(SysSourceGetScanType() == _SOURCE_SWITCH_AUTO_IN_GROUP)
        {
            SET_OSD_1P_INPUT_SOURCE(_OSD_INPUT_AUTO);
        }
        else if(GET_OSD_1P_INPUT_SOURCE() != _OSD_INPUT_AUTO)
        {
            SET_OSD_1P_INPUT_SOURCE(SysRegionGetPortType(_DISPLAY_RGN_1P));
        }
        g_usBackupValue = GET_OSD_1P_INPUT_SOURCE();
        SET_OSD_STATE(_MENU_HOTKEY_SOURCE);
        OsdFuncDisableOsd();
        OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_SOURCE_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_SOURCE_MENU_HEIGHT), COLOR(_CP_BLACK, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
#endif

        OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);

        // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdWidth, _CP_LIGHTBLUE);
        }
        else
#endif
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdHeight, _CP_LIGHTBLUE);
        }

        // title
        // icon
        // _MENU_INPUT
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_INPUT);

        OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

        // highligh window
        OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
        OsdDispHotKeySourceMenuIcon(GET_OSD_1P_INPUT_SOURCE());

        OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

        ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

        OsdFuncEnableOsd();
    }
    else // Multi Frame
    {
        g_usItemNum = _MENU_NONE;
        OsdDispDisableOsd();
        SET_OSD_STATE(_MENU_INPUT_SOURCE_1P);
        OsdDispMainMenu();

        // show display mode type icon
        if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
        {
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_INPUT_2P_LR);
        }
        else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
        {
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_INPUT_2P_TB);
        }
        else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
        {
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_INPUT_2P_PIP);
        }
        else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
        {
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_INPUT_4P);
        }
        // show source icon
        OsdDispHotKeySourceMenuIcon(GET_OSD_1P_INPUT_SOURCE());
        OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_1P_INPUT_SOURCE());
    }
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyDisplayModeMenuSwitch(BYTE ucMode)
{
    if(ucMode <= _OSD_DM_2P_PIP)
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * (ucMode + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
    else
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * ((ucMode - 4) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyDisplayModeMenuIcon(BYTE ucMode)
{
    BYTE ucCol = 5;
    OsdFuncClearOsd(ROW(6), COL(13), WIDTH(47), HEIGHT(1));
    OsdPropPutStringCenter(ROW(6), COL(0), WIDTH(12), _PFONT_PAGE_1, _STRING_DISPLAYMODE, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);

#if(_4P_DISPLAY_SUPPORT == _ON)
    // Left & Right Arrow
    OsdFontPut1Bit(ROW(3), COL(13), _iLEFT_00, COLOR(_CP_BLUE, _CP_BG));
    OsdFontPut1Bit(ROW(3) + 1, COL(13), _iLEFT_00 + 1, COLOR(_CP_BLUE, _CP_BG));

    OsdFontPut1Bit(ROW(3), COL(62), _iRIGHT_00, COLOR(_CP_BLUE, _CP_BG));
    OsdFontPut1Bit(ROW(3) + 1, COL(62), _iRIGHT_00 + 1, COLOR(_CP_BLUE, _CP_BG));
#endif

    if(ucMode <= _OSD_DM_2P_PIP)
    {
        // 1P
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_1P);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 1) + 2), _PFONT_PAGE_1, _STRING_1P, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

        // 2P LR
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_2P_LR);
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 2) + 1), _PFONT_PAGE_1, _STRING_2P_LR, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
#else
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 2)), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_GRAY, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 2) + 1), _PFONT_PAGE_1, _STRING_2P_LR, COLOR(_CP_GRAY, _CP_BG), _ENGLISH);
#endif
        // 2P TB
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_2P_TB);
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 3) + 1), _PFONT_PAGE_1, _STRING_2P_TB, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
#else
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 3)), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_GRAY, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 3) + 1), _PFONT_PAGE_1, _STRING_2P_TB, COLOR(_CP_GRAY, _CP_BG), _ENGLISH);
#endif
        // 2P PIP
        OsdFontVLCDynamicLoadIcon(_ICON_POS_DOWN_0, _ICON_2P_PIP);
#if(_PIP_DISPLAY_SUPPORT == _ON)
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 4) + 1), _PFONT_PAGE_1, _STRING_2P_PIP, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
#else
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 4)), (_1DYNAMIC_ICON_START + (4 * 24)), _CP_GRAY, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 4) + 1), _PFONT_PAGE_1, _STRING_2P_PIP, COLOR(_CP_GRAY, _CP_BG), _ENGLISH);
#endif
    }
    else
    {
        // 4P
        OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_4P);
        OsdFontPut1BitMainMenuIcon(ROW(2), COL(ucCol + (12 * 1)), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
        OsdPropPutString(ROW(6), COL(ucCol + (12 * 1) + 2), _PFONT_PAGE_1, _STRING_4P, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

        // None
        OsdFuncClearOsd(ROW(2), COL(3 + (12 * 2)), WIDTH(32), HEIGHT(4));
    }
}

//--------------------------------------------------
// Description :
// Input Value :
// Output Value :
//--------------------------------------------------
void OsdDispHotKeyDisplayModeMenu(void)
{
    g_usBackupValue = GET_OSD_DISPLAY_MODE();

    SET_OSD_STATE(_MENU_HOTKEY_DISPLAY_MODE);
    OsdFuncDisableOsd();
    OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_SOURCE_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_SOURCE_MENU_HEIGHT), COLOR(_CP_BLACK, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(8), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdWidth, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdWidth, _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(52), g_ucOsdHeight, _CP_LIGHTBLUE);
    }

    // title
    // icon
    OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _MENU_DISPLAYMODE);

    OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

    // highligh window
    if(GET_OSD_DISPLAY_MODE() <= _OSD_DM_2P_PIP)
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * (GET_OSD_DISPLAY_MODE() + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }
    else
    {
        OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(0), COL(3 + (12 * ((GET_OSD_DISPLAY_MODE() - 4) + 1))), WIDTH(10), HEIGHT(8), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
    }

    g_usBackupValue = GET_OSD_DISPLAY_MODE();

    OsdDispHotKeyDisplayModeMenuIcon(g_usBackupValue);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispPanelUniformityMsgSwitch(void)
{
    BYTE uctemp = 0;
    SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), ~(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION())));
    (GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON) ? (uctemp = 1) : (uctemp = 0);
    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(18 + (9 * uctemp)), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispOsdMessage(EnumOSDDispMsg enumMessage)
{
    OsdDispDisableOsd();

    g_ucFontPointer0 = _OSD_PAGE_0_START;
    g_ucFontPointer1 = _OSD_PAGE_1_START;
    g_ucFontPointer2 = _OSD_PAGE_2_START;

    OsdFuncApplyMap(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);

    // Background window Modify
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), HEIGHT(g_ucOsdWidth), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdHeight - 12), HEIGHT(g_ucOsdWidth), _CP_LIGHTBLUE);
    }
    else
#endif
    {
        if(enumMessage == _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG)
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight), _CP_LIGHTBLUE);
        }
        else
        {
            OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(0), COL(0), WIDTH(12), g_ucOsdHeight, _CP_BLUE);
            OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(12), WIDTH(g_ucOsdWidth - 12), HEIGHT(g_ucOsdHeight), _CP_LIGHTBLUE);
        }
    }

    //==== Show page item =======
    switch(enumMessage)
    {
        case _OSD_DISP_NOSIGNAL_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_SIGNAL);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SIGNAL_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SIGNAL_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_NOCABLE_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_CABLE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_CABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_CABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_NOSUPPORT_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_NO_SUPPORT);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_NO_SUPPORT_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_NO_SUPPORT_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            break;

        case _OSD_DISP_FAIL_SAFE_MODE_MSG:
            OsdPropPutStringCenter(ROW(_OSD_MESSAGE_ROW_START), COL(_OSD_MESSAGE_CENTER_COL_START), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_0, _STRING_NO_SUPPORT, COLOR(_CP_WHITE, _CP_BG), _ENGLISH);
            break;

        case _OSD_DISP_AUTO_CONFIG_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_AUTO_ADJUST);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);

            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_ADJUST_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_ADJUST_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_ADJUST_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;

        case _OSD_DISP_INPUT_SIGNAL_MSG:
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            return;

            break;

        case _OSD_DISP_AUTO_COLOR_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _MENU_COLOR);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_AUTO_COLOR_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_AUTO_COLOR_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_AUTO_COLOR_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;

        case _OSD_DISP_POWER_SAVING_MSG:
            // SET_OSD_STATE(_MENU_MESSAGE_DISPLAY);
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_POWER_SAVING);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_POWER_SAVING_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_POWER_SAVING_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_POWER_SAVING_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
        case _OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_TRUN_OFF_PANEL_UNI_TEXT0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_TRUN_OFF_PANEL_UNI_TEXT1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3 + 6), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_YES);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(18), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_NO);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(27), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);

            break;
#if(_FREEZE_SUPPORT == _ON)
        case _OSD_DISP_DISABLE_FREEZE_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_FREEZE);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_FREEZE_DISABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_FREEZE_DISABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_FREEZE_DISABLE_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
        case _OSD_DISP_DISABLE_FALSE_COLOR_MSG:
            // title
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_FASLE_COLOR);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            // icon
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_FASLE_COLOR_DISABLE_TEXT_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_FASLE_COLOR_DISABLE_TEXT_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_FASLE_COLOR_DISABLE_TEXT_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
#endif
#if(_DP_MST_SUPPORT == _ON)
        case _OSD_DISP_MST_WARNING_MSG:
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_DP_MST);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(3), (_1DYNAMIC_ICON_START + (0 * 24)), _CP_WHITE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_1, _ICON_MST_WARNING_MSG_0);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14), (_1DYNAMIC_ICON_START + (1 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_2, _ICON_MST_WARNING_MSG_1);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6), (_1DYNAMIC_ICON_START + (2 * 24)), _CP_BLUE, _CP_BG);
            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_3, _ICON_MST_WARNING_MSG_2);
            OsdFontPut1BitMainMenuIcon(ROW(2), COL(14 + 6 + 6), (_1DYNAMIC_ICON_START + (3 * 24)), _CP_BLUE, _CP_BG);
            break;
#endif

        default:
            break;
    }

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    OsdFuncEnableOsd();
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispAutoConfigProc(void)
{
    OsdDispOsdMessage(_OSD_DISP_AUTO_CONFIG_MSG);
    UserCommonAutoConfig();
    OsdDispDisableOsd();
}
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDisplayAutoBalanceProc(void)
{
//    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType(UserAdjustConvertSystemSelectRegion(GET_OSD_SELECT_REGION()));

    OsdDispDisableOsd();
    OsdDispOsdMessage(_OSD_DISP_AUTO_COLOR_MSG);

    if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
    {
        if(GET_OSD_COLOR_FORMAT(_A0_INPUT_PORT) == _COLOR_SPACE_RGB)
        {
            // Perform auto-color for RGB
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_RGB) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);

#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_FORMULA))
                // Calculate YPbPr gain/offset using formula
                g_stAdcData = ScalerAutoBalanceYPbPrFromFormula(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);

                // Restore RGB gain/offset
                ScalerAutoGetAutoColorResult(&g_stAdcData);
#endif
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#if((_YPBPR_SUPPORT == _ON) && (_YPBPR_AUTO_METHOD == _YPBPR_AUTO_BY_SOURCE))
        else
        {
            // Perform auto-color for YPbPr
            if(ScalerAutoDoWhiteBalance(_AUTO_TUNE_YPBPR) == _AUTO_SUCCESS)
            {
                ScalerAutoGetAutoColorResult(&g_stAdcData);
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_YPBPR);
            }
            else
            {
                UserCommonNVRamRestoreADCSetting();
            }
        }
#endif
    }

    OsdDispDisableOsd();
    // SET_KEYMESSAGE(_HOLD_KEY_MESSAGE);
}
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispClearSliderAndNumber(void)
{
    OsdWindowSliderDisable();
    OsdFuncClearOsd(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_ucOsdWidth, 1);
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdReset(void)
{
    BYTE ucIndex = GET_OSD_LANGUAGE();
    ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _ENABLE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    ScalerColorHLWDDomainEnable(_FUNCTION_OFF);
#endif

    OsdDispDisableOsd();

    UserCommonNVRamRestoreSystemData();

    RTDNVRamRestoreOsdUserData();
    RTDNVRamRestoreOsdRegionData();
    RTDNVRamLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());
    RTDNVRamRestoreOsdDisplayModeData();
    RTDNVRamLoadOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
    RTDNVRamRestoreUserColorSetting();
    RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());
    RTDNVRamRestoreOsdInputSourceData();
    RTDNVRamRestoreBacklight();

#if(_VGA_SUPPORT == _ON)
    UserCommonNVRamRestoreModeUserData();

    if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
    {
        SET_VGA_MODE_DO_FIRST_AUTO(_TRUE);
        UserCommonModeSearchInitalUserAndCenterData(g_stVGAModeUserData.ucModeNumber);
        UserCommonNVRamSaveModeUserData();
    }
#endif

    if(ucIndex != GET_OSD_LANGUAGE())
    {
        SET_OSD_LANGUAGE(ucIndex);
        RTDNVRamSaveOsdUserData();
    }

    OsdFuncSetOsdItemFlag();

    UserAdjustDisplayMode();

    SET_OSD_STATE(_MENU_NONE);

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
}

//--------------------------------------------------
// Description  : Logo showing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispShowLogo(void)
{
    g_ucLogoTimerCounter = 0;

    ScalerDDomainPatternGenAdjustColor(0, 0, 0);
    ScalerDDomainPatternGenEnable(_ENABLE);
    ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _DISABLE);

    OsdDispDisableOsd();
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);
    OsdFuncApplyMap(WIDTH(70), HEIGHT(10), COLOR(_LOGO_CP_WHITE, _LOGO_CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, g_ucOsdHeight, _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(_OSD_TRANSPARENCY_MAX);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO0);
    OsdFontVLCLoadFont(_REALTEK_1BIT_LOGO1);

    OsdFontPut1BitTable(ROW(0), COL(0), tiOSD_REALTEK_1BIT_LOGO0, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
    OsdFontPut1BitTable(ROW(0), COL(19), tiOSD_REALTEK_1BIT_LOGO1, COLOR(_LOGO_CP_BG, _LOGO_CP_BG));
    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, 50, 50);
    OsdWindowDrawing(_OSD_WINDOW_0, XSTART(1), YSTART(1), XEND(_LOGO_WINDOW_SIZE_X), YEND(_LOGO_WINDOW_SIZE_Y), _LOGO_CP_BLUE);
    OsdFuncEnableOsd();

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    ScalerTimer0SetTimerCount(16);
#endif

    SET_OSD_LOGO_ON(_ON);
}

//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispShowInformation(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        OsdPropPutStringCenter(ROW(14), COL(11), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_1P)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

        if(SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_1P);

#if(_FREESYNC_SUPPORT == _ON)
            SET_FREESYNC_OSD_ADDRESS(g_ucFontPointer1);

            if(ScalerSyncGetFREESYNCEnable() == _TRUE)
            {
                ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_SHOW_FREESYNC_VFREQ);
            }
#endif

            OsdPropPutStringCenter(ROW(14 + 1), COL(11), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(14 + 2), COL(11), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_1P))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(11), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(14 + 3), COL(11 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(11), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
#if(_FREESYNC_SUPPORT == _ON)
                    if(ScalerSyncGetFREESYNCEnable() == _TRUE)
                    {
                        OsdPropPutString(ROW(14 + 4), COL(16), _PFONT_PAGE_INFORMATION, _STRING_FREESYNC_SUPPORT_V_RANGE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    }
#endif

                    break;
#endif
            }
        }
    }
    else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
    {
        // L
        OsdPropPutStringCenter(ROW(13), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_2P_LR_L, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(14), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_LEFT)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_LEFT) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_LEFT);
            OsdPropPutStringCenter(ROW(14 + 1), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(14 + 2), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_LEFT))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(14 + 3), COL(1 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
        // R
        OsdPropPutStringCenter(ROW(13), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_2P_LR_R, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(14), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_RIGHT)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_RIGHT) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_RIGHT);
            OsdPropPutStringCenter(ROW(14 + 1), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(14 + 2), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_RIGHT))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(14 + 3), COL(22 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
    }
    else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
    {
        // T
        OsdPropPutStringCenter(ROW(13), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_2P_TB_T, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(14), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_TOP)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_TOP) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_TOP);
            OsdPropPutStringCenter(ROW(14 + 1), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(14 + 2), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_TOP))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(14 + 3), COL(1 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
        // B
        OsdPropPutStringCenter(ROW(13), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_2P_TB_B, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(14), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_BOTTOM)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_BOTTOM) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_BOTTOM);
            OsdPropPutStringCenter(ROW(14 + 1), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(14 + 2), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_BOTTOM))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(14 + 3), COL(22 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
    }
    else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
    {
        // Main
        OsdPropPutStringCenter(ROW(13), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_2P_PIP_MAIN, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(14), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_MAIN)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_MAIN) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_MAIN);
            OsdPropPutStringCenter(ROW(14 + 1), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(14 + 2), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_MAIN))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(14 + 3), COL(1 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
        // Sub
        OsdPropPutStringCenter(ROW(13), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_2P_PIP_SUB, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(14), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_SUB)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_SUB) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_SUB);
            OsdPropPutStringCenter(ROW(14 + 1), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(14 + 2), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_SUB))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(14 + 3), COL(22 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(14 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
    }
    else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
    {
        // 1
        OsdPropPutString(ROW(11), COL(1 + 2), _PFONT_PAGE_INFORMATION, _STRING_1P, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(11), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_1P, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(11), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_LT)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_LT) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_LT);
            OsdPropPutStringCenter(ROW(11 + 1), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(11 + 2), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_LT))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(11 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(11 + 3), COL(1 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(11 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
        // 2
        OsdPropPutString(ROW(16), COL(1 + 2), _PFONT_PAGE_INFORMATION, _STRING_2P, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(16), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_LB)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_LB) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_LB);
            OsdPropPutStringCenter(ROW(16 + 1), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(16 + 2), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_LB))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(16 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(16 + 3), COL(1 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(16 + 3), COL(1), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
        // 3
        OsdPropPutString(ROW(11), COL(22 + 2), _PFONT_PAGE_INFORMATION, _STRING_3P, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(11), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_RT)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_RT) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_RT);
            OsdPropPutStringCenter(ROW(11 + 1), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(11 + 2), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_RT))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(11 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(11 + 3), COL(22 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(11 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
        // 4
        OsdPropPutString(ROW(16), COL(22 + 2), _PFONT_PAGE_INFORMATION, _STRING_4P, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        OsdPropPutStringCenter(ROW(16), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(_DISPLAY_RGN_RB)), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
        if(SysRegionGetDisplayState(_DISPLAY_RGN_RB) == _DISPLAY_STATE_ACTIVE)
        {
            SysRegionSetMeasureResultPointerRegion(_DISPLAY_RGN_RB);
            OsdPropPutStringCenter(ROW(16 + 1), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
            OsdPropPutStringCenter(ROW(16 + 2), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_RB))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(16 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    OsdPropShowNumber(ROW(16 + 3), COL(22 + 15), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_BG));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(16 + 3), COL(22), WIDTH(21), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
                    break;
#endif
            }
        }
    }
}

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
//--------------------------------------------------
// Description  : OSD information function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispOsdRotateSwitch(void)
{
    OsdFuncDisableOsd();

    OsdFuncApplyMap(WIDTH(44), HEIGHT(22), COLOR(_CP_WHITE, _CP_BG));

//20140304 Abel
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
    ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_MAIN_MENU_HEIGHT), _DISABLE, 0, _ENABLE);
#endif

    OsdFuncBlending(_OSD_TRANSPARENCY_ONLY_WINDOW);
    OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

    // Adjust Color Palette
    OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

    // Load Font & Icon
    OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

    OsdFontVLCLoadFont(_FONT1_GLOBAL);
    // OsdFontVLCLoadFont(_FONT2_ICON_MENU);

    // Background window
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdWidth / 2), COL(0), WIDTH(g_ucOsdHeight), HEIGHT(g_ucOsdWidth / 2), _CP_LIGHTBLUE);
    }
    else
#endif
    {
        OsdWindowDrawingByFont(_OSD_WINDOW_0, ROW(0), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight / 2), _CP_BLUE);
        OsdWindowDrawingByFont(_OSD_WINDOW_1, ROW(g_ucOsdHeight / 2), COL(0), WIDTH(g_ucOsdWidth), HEIGHT(g_ucOsdHeight / 2), _CP_LIGHTBLUE);
    }


    // Realtek Mark
    OsdFontPut1BitTable(ROW(0), COL(32), tOSD_iREALTEK, COLOR(_CP_WHITE, _CP_BG));

    // Main Menu Icon & String
    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_ROTATE);

    OsdDispClearSelectColor(_DOWN);
    OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
    OsdDispMainMenuItemIndication(_ITEM_6, 7, _OSD_SELECT);

    OsdDispMainMenuOptionSetting(_MENU_OTHER_ROTATE_ADJUST, _SELECT, GET_OSD_ROTATE_STATUS());

    // key info
    OsdDispMainMenuKeyInfo(_KEY_INFO_ALL, _OSD_UNSELECT);

    OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());

    // Osd Enable
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
#endif

//--------------------------------------------------
// Description  : Draw OSD notice window
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMpDisplayStateNotice(BYTE ucNoticeInfoX, BYTE ucNoticeInfoY, BYTE ucNoticeInfo, BYTE ucMpPortregion)
{
    switch(ucNoticeInfo)
    {
        case _OSD_NOTICE_KEEP:

            return;

        case _OSD_NOTICE_INFO:

            ScalerOsdChange1BitColor(ROW(ucNoticeInfoX), COL(ucNoticeInfoY), LENGTH(12), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), FG_COLOR(_CP_BLUE), BG_COLOR(_CP_BLUE));
            ScalerOsdChange1BitColor(ROW(ucNoticeInfoX), COL(ucNoticeInfoY + 12), LENGTH(_OSD_HOTKEY_MENU_WIDTH - 12), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), FG_COLOR(_CP_LIGHTBLUE), BG_COLOR(_CP_LIGHTBLUE));

            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_INFORMATION_HINT);
            OsdFontPut1BitMainMenuIcon(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 3), _1BIT_NOTICE_INFORMATION, _CP_WHITE, _CP_BLUE);
            OsdPropPutStringCenter(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(ucMpPortregion)), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);

            SysRegionSetMeasureResultPointerRegion(ucMpPortregion);
            OsdPropPutStringCenter(ROW(ucNoticeInfoX + 3), COL(ucNoticeInfoY + 12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            OsdPropPutStringCenter(ROW(ucNoticeInfoX + 4), COL(ucNoticeInfoY + 12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);

            switch(SysRegionGetSourceType(ucMpPortregion))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:

                    OsdPropPutStringCenter(ROW(ucNoticeInfoX + 5), COL(ucNoticeInfoY + 11), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                    OsdPropShowNumber(ROW(ucNoticeInfoX + 5), COL(ucNoticeInfoY + 26), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_LIGHTBLUE));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:

                    OsdPropPutStringCenter(ROW(ucNoticeInfoX + 5), COL(ucNoticeInfoY + 12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
#if(_FREESYNC_SUPPORT == _ON)
                    if(ScalerSyncGetFREESYNCEnable() == _TRUE)
                    {
                        OsdPropPutString(ROW(ucNoticeInfoX + 6), COL(ucNoticeInfoY + 16), _PFONT_PAGE_INFORMATION, _STRING_FREESYNC_SUPPORT_V_RANGE, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                    }
#endif
                    break;
#endif
            }

            break;

        case _OSD_NOTICE_NO_SUPPORT:
        case _OSD_NOTICE_NO_CABLE:
        case _OSD_NOTICE_NO_SIGNAL:

            ScalerOsdChange1BitColor(ROW(ucNoticeInfoX), COL(ucNoticeInfoY), LENGTH(12), HEIGHT(8), FG_COLOR(_CP_BLUE), BG_COLOR(_CP_BLUE));
            ScalerOsdChange1BitColor(ROW(ucNoticeInfoX), COL(ucNoticeInfoY + 12), LENGTH(36 - 12), HEIGHT(8), FG_COLOR(_CP_LIGHTBLUE), BG_COLOR(_CP_LIGHTBLUE));

            OsdFontPut1BitMainMenuIcon(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 3), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_ICON) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_ICON) : (_1BIT_NOTICE_NO_SIGNAL_ICON))), _CP_WHITE, _CP_BLUE);
            OsdFontPut1BitMainMenuIcon(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 18), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_TEXT_0) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_TEXT_0) : (_1BIT_NOTICE_NO_SIGNAL_TEXT_0))), _CP_BLUE, _CP_LIGHTBLUE);
            OsdFontPut1BitMainMenuIcon(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 18 + 6), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_TEXT_1) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_TEXT_1) : (_1BIT_NOTICE_NO_SIGNAL_TEXT_1))), _CP_BLUE, _CP_LIGHTBLUE);
            break;

        default:
        case _OSD_NOTICE_NONE:

            // Clear message here
            ScalerOsdChange1BitColor(ROW(ucNoticeInfoX), COL(ucNoticeInfoY), LENGTH(12), HEIGHT(8), FG_COLOR(_CP_BG), BG_COLOR(_CP_BG));
            ScalerOsdChange1BitColor(ROW(ucNoticeInfoX), COL(ucNoticeInfoY + 12), LENGTH(36 - 12), HEIGHT(8), FG_COLOR(_CP_BG), BG_COLOR(_CP_BG));
            break;
    }
}

#if((_4P_DISPLAY_SUPPORT == _ON) || (_2P_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispMpDisplayStateNoticeFontB(BYTE ucNoticeInfoX, BYTE ucNoticeInfoY, BYTE ucNoticeInfo, BYTE ucMpPortregion)
{
    switch(ucNoticeInfo)
    {
        case _OSD_NOTICE_KEEP:
            break;

        case _OSD_NOTICE_INFO:
            ScalerOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX), COL(ucNoticeInfoY), LENGTH(12), HEIGHT(8), FG_COLOR(_CP_BLUE), BG_COLOR(_CP_BLUE));
            ScalerOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX), COL(ucNoticeInfoY + 12), LENGTH(36 - 12), HEIGHT(8), FG_COLOR(_CP_LIGHTBLUE), BG_COLOR(_CP_LIGHTBLUE));

            OsdFontVLCDynamicLoadIcon(_ICON_POS_UP_0, _ICON_INFORMATION_HINT);
            OsdFontPut1BitMainMenuIconOsdB(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 3), _1BIT_NOTICE_INFORMATION, _CP_WHITE, _CP_BLUE);

            OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX + 2), COL(ucNoticeInfoY + 12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, OsdDisplayGetSourcePortString(SysRegionGetPortType(ucMpPortregion)), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);

            SysRegionSetMeasureResultPointerRegion(ucMpPortregion);
            OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX + 3), COL(ucNoticeInfoY + 12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_NOW_RESOLUTION, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
            OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX + 4), COL(ucNoticeInfoY + 12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_HFREQPCLK, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);

            switch(SysRegionGetSourceType(_DISPLAY_RGN_SUB))
            {
#if(_VGA_SUPPORT == _ON)
                case _SOURCE_VGA:
                    OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX + 5), COL(ucNoticeInfoY + 11), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, OsdDisplayGetVGAModeString(g_stVGAModeUserData.b1IsPresetMode), COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                    OsdPropShowNumber(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX + 5), COL(ucNoticeInfoY + 26), g_stVGAModeUserData.ucModeNumber, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_INFORMATION, COLOR(_CP_BLUE, _CP_LIGHTBLUE));
                    break;
#endif

#if(_DIGITAL_PORT_SUPPORT == _ON)
                default:
                    OsdPropPutStringCenter(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX + 5), COL(ucNoticeInfoY + 12), WIDTH(_OSD_MESSAGE_CENTER_COL_END), _PFONT_PAGE_INFORMATION, _STRING_HDCP_MODE, COLOR(_CP_BLUE, _CP_LIGHTBLUE), _ENGLISH);
                    break;
#endif
            }
            break;

        case _OSD_NOTICE_NO_SUPPORT:
        case _OSD_NOTICE_NO_CABLE:
        case _OSD_NOTICE_NO_SIGNAL:
            ScalerOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX), COL(ucNoticeInfoY), LENGTH(12), HEIGHT(8), FG_COLOR(_CP_BLUE), BG_COLOR(_CP_BLUE));
            ScalerOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX), COL(ucNoticeInfoY + 12), LENGTH(36 - 12), HEIGHT(8), FG_COLOR(_CP_LIGHTBLUE), BG_COLOR(_CP_LIGHTBLUE));

            OsdFontPut1BitMainMenuIconOsdB(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 3), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_ICON) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_ICON) : (_1BIT_NOTICE_NO_SIGNAL_ICON))), _CP_WHITE, _CP_BLUE);
            OsdFontPut1BitMainMenuIconOsdB(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 18), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_TEXT_0) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_TEXT_0) : (_1BIT_NOTICE_NO_SIGNAL_TEXT_0))), _CP_BLUE, _CP_LIGHTBLUE);
            OsdFontPut1BitMainMenuIconOsdB(ROW(ucNoticeInfoX + 2), COL(ucNoticeInfoY + 18 + 6), ((ucNoticeInfo == _OSD_NOTICE_NO_SUPPORT) ? (_1BIT_NOTICE_NO_SUPPORT_TEXT_1) : ((ucNoticeInfo == _OSD_NOTICE_NO_CABLE) ? (_1BIT_NOTICE_NO_CABLE_TEXT_1) : (_1BIT_NOTICE_NO_SIGNAL_TEXT_1))), _CP_BLUE, _CP_LIGHTBLUE);
            break;

        default:
        case _OSD_NOTICE_NONE:
            // Clear message here
            ScalerOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX), COL(ucNoticeInfoY), LENGTH(12), HEIGHT(8), FG_COLOR(_CP_BG), BG_COLOR(_CP_BG));
            ScalerOsdChange1BitColor(ROW(_OSD_MAP_B_ROW_OFFSET + ucNoticeInfoX), COL(ucNoticeInfoY + 12), LENGTH(36 - 12), HEIGHT(8), FG_COLOR(_CP_BG), BG_COLOR(_CP_BG));
            // ScalerOsd2FontFunction(_DISABLE);// must be remove

            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Update OSD notice window for current display mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpUpdateDisplayStateNotice(bit bOn, EnumDisplayRegion enumSelRegion)
{
    BYTE uc1pState = 0;
    BYTE uc2pState = 0;

#if(_4P_DISPLAY_SUPPORT == _ON)
    BYTE uc3pState = 0;
    BYTE uc4pState = 0;
#endif

    bOn = bOn;

    switch(GET_OSD_DISPLAY_MODE())
    {
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:

            uc1pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_LEFT, bOn);
            uc2pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_RIGHT, bOn);
            if((enumSelRegion == _DISPLAY_RGN_LEFT) && (bOn == _OFF))
            {
                uc2pState = _OSD_NOTICE_KEEP;
            }
            if((enumSelRegion == _DISPLAY_RGN_RIGHT) && (bOn == _OFF))
            {
                uc1pState = _OSD_NOTICE_KEEP;
            }

            OsdDispMpDisplayStateNotice_2P_LR(uc1pState, uc2pState);
            break;
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:

            uc1pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_TOP, bOn);
            uc2pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_BOTTOM, bOn);
            if((enumSelRegion == _DISPLAY_RGN_TOP) && (bOn == _OFF))
            {
                uc2pState = _OSD_NOTICE_KEEP;
            }
            if((enumSelRegion == _DISPLAY_RGN_BOTTOM) && (bOn == _OFF))
            {
                uc1pState = _OSD_NOTICE_KEEP;
            }

            OsdDispMpDisplayStateNotice_2P_TB(uc1pState, uc2pState);
            break;
#endif

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:

            uc1pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_MAIN, bOn);
            uc2pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_SUB, bOn);
            if((enumSelRegion == _DISPLAY_RGN_MAIN) && (bOn == _OFF))
            {
                uc2pState = _OSD_NOTICE_KEEP;
            }
            if((enumSelRegion == _DISPLAY_RGN_SUB) && (bOn == _OFF))
            {
                uc1pState = _OSD_NOTICE_KEEP;
            }

            OsdDispMpDisplayStateNotice_2P_PIP(uc1pState, uc2pState);
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:

            uc1pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_LT, bOn);
            uc2pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_LB, bOn);
            uc3pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_RT, bOn);
            uc4pState = OsdDispMpDisplayStateGetNoticeType(_DISPLAY_RGN_RB, bOn);

            if((enumSelRegion == _DISPLAY_RGN_LT) && (bOn == _OFF))
            {
                uc2pState = _OSD_NOTICE_KEEP;
                uc3pState = _OSD_NOTICE_KEEP;
                uc4pState = _OSD_NOTICE_KEEP;
            }
            if((enumSelRegion == _DISPLAY_RGN_LB) && (bOn == _OFF))
            {
                uc1pState = _OSD_NOTICE_KEEP;
                uc3pState = _OSD_NOTICE_KEEP;
                uc4pState = _OSD_NOTICE_KEEP;
            }
            if((enumSelRegion == _DISPLAY_RGN_RT) && (bOn == _OFF))
            {
                uc1pState = _OSD_NOTICE_KEEP;
                uc2pState = _OSD_NOTICE_KEEP;
                uc4pState = _OSD_NOTICE_KEEP;
            }
            if((enumSelRegion == _DISPLAY_RGN_RB) && (bOn == _OFF))
            {
                uc1pState = _OSD_NOTICE_KEEP;
                uc2pState = _OSD_NOTICE_KEEP;
                uc3pState = _OSD_NOTICE_KEEP;
            }

            OsdDispMpDisplayStateNotice_4P(uc1pState, uc2pState, uc3pState, uc4pState);
            break;
#endif

        case _OSD_DM_1P:

            bOn = bOn;
            enumSelRegion = enumSelRegion;
            OsdDispOsdMessage(_OSD_DISP_INPUT_SIGNAL_MSG);
            OsdDispMpDisplayStateNotice(ROW(0), COL(0), _OSD_NOTICE_INFO, _1P_NORMAL_FULL_REGION);
            OsdFuncEnableOsd();

            break;

        default:

            break;
    }
}

#if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get current OSD notice type for specific display region
// Input Value  : select region
// Output Value : OSD notice type
//--------------------------------------------------
BYTE OsdDispMpDisplayStateGetNoticeType(EnumDisplayRegion enumSelRegion, bit bOn)
{
    bit bCableStatus = _FALSE;

    if((bOn == _ON) ||
       ((SysRegionCheckDisplayEvent(enumSelRegion, _DISPLAY_EVENT_STATE_CHANGE_USR) == _TRUE) &&
        ((GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION) ||
         (GET_OSD_STATE() == _MENU_NONE))))
    {
        switch(SysRegionGetDisplayState(enumSelRegion))
        {
            case _DISPLAY_STATE_OOR:
                DebugMessageOsd("4._OSD_NOTICE_NO_SUPPORT", enumSelRegion);
                return _OSD_NOTICE_NO_SUPPORT;

            case _DISPLAY_STATE_NO_SIGNAL:
                switch(ScalerRegionGetIndex(enumSelRegion))
                {
                    default:
                    case 0x00:
                        bCableStatus = SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_0));
                        break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
                    case 0x01:
                        bCableStatus = SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_1));
                        break;

#if(_4P_DISPLAY_SUPPORT == _ON)
                    case 0x02:
                        bCableStatus = SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_2));
                        break;
                    case 0x03:
                        bCableStatus = SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_3));
                        break;
#endif

#endif
                }

                if(bCableStatus == _TRUE)
                {
                    DebugMessageOsd("4._OSD_NOTICE_NO_SIGNAL", enumSelRegion);
                    return _OSD_NOTICE_NO_SIGNAL;
                }
                else
                {
                    DebugMessageOsd("4._OSD_NOTICE_NO_CABLE", enumSelRegion);
                    return _OSD_NOTICE_NO_CABLE;
                }

            case _DISPLAY_STATE_ACTIVE:

                if(GET_FAIL_SAFE_MODE(ScalerRegionGetIndex(enumSelRegion)) == _TRUE)
                {
                    // Show OOR in fail safe mode
                    DebugMessageOsd("4._OSD_NOTICE_NONE", enumSelRegion);
                    return _OSD_NOTICE_NONE;
                }
                else
                {
                    DebugMessageOsd("4._OSD_NOTICE_INFO", enumSelRegion);
                    return _OSD_NOTICE_INFO;
                }

            default:
            case _DISPLAY_STATE_NONE:
                DebugMessageOsd("4._OSD_NOTICE_NONE", enumSelRegion);
                return _OSD_NOTICE_NONE;
        }
    }
    else
    {
        DebugMessageOsd("4._OSD_NOTICE_KEEP", enumSelRegion);
        return _OSD_NOTICE_KEEP;
    }
}
#endif // End of #if((_2P_DISPLAY_SUPPORT == _ON) || (_4P_DISPLAY_SUPPORT == _ON))

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 2P LR
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_2P_LR(BYTE ucNoticeL, BYTE ucNoticeR)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;
    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);
        g_ucFontPointer0 = _OSD_PAGE_0_START;
        g_ucFontPointer1 = _OSD_PAGE_1_START;
        g_ucFontPointer2 = _OSD_PAGE_2_START;

        ScalerOsd2FontFunction(_ENABLE);
        ScalerOsdReferenceDelay(_OSD_A, _OSD_FIRST_DELAY);
        ScalerOsdReferenceDelay(_OSD_B, _OSD_SECOND_DELAY);

        OsdFuncApplyMapOsdAB(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG), WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _ENABLE);
#endif

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }

    // L/R swap check
    OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNoticeL, _PBP_LR_L);
    OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNoticeR, _PBP_LR_R);
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((((WORD)_PANEL_DH_WIDTH / 8 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth))), (((WORD)_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((((WORD)_PANEL_DH_WIDTH / 8 * 5) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth))), (((WORD)_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (((_PANEL_DH_WIDTH / 8 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight))), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (((_PANEL_DH_WIDTH / 8 * 5) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight))), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }

#else
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, ((((WORD)_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)) / 4), (((WORD)_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, ((((WORD)_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)) / 4), (((WORD)_PANEL_DV_HEIGHT / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (((_PANEL_DH_WIDTH / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)) / 4), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)) / 4), ((_PANEL_DV_HEIGHT / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }
#endif
    // ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
#endif // End of #if(_PBP_LR_DISPLAY_SUPPORT == _ON)

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 2P TB
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_2P_TB(BYTE ucNoticeT, BYTE ucNoticeB)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;
    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);
        g_ucFontPointer0 = _OSD_PAGE_0_START;
        g_ucFontPointer1 = _OSD_PAGE_1_START;
        g_ucFontPointer2 = _OSD_PAGE_2_START;

        ScalerOsd2FontFunction(_ENABLE);
        ScalerOsdReferenceDelay(_OSD_A, _OSD_FIRST_DELAY);
        ScalerOsdReferenceDelay(_OSD_B, _OSD_SECOND_DELAY);

        OsdFuncApplyMapOsdAB(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG), WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _ENABLE);
#endif

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }

    OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNoticeT, _PBP_TB_T);
    OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNoticeB, _PBP_TB_B);

    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)) / 4), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (((_PANEL_DH_WIDTH / 2) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)) / 4), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
            (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (((_PANEL_DH_WIDTH / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)) / 4), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (((_PANEL_DH_WIDTH / 2) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)) / 4), ((_PANEL_DV_HEIGHT / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
#endif // End of #if(_PBP_TB_DISPLAY_SUPPORT == _ON)

#if(_PIP_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 2P PIP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_2P_PIP(BYTE ucNoticeMain, BYTE ucNoticeSub)
{
    WORD usHPos = 0;
    WORD usHWidth = 0;
    WORD usVPos = 0;
    WORD usVHeight = 0;
    WORD usPostionH = 0xFFFF;
    WORD usPostionV = 0xFFFF;
    StructTimingFormat stTimingFormat;
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    memset(&stTimingFormat, 0x00, sizeof(StructTimingFormat));

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        ScalerOsd2FontFunction(_ENABLE);
        ScalerOsdReferenceDelay(_OSD_A, _OSD_FIRST_DELAY);
        ScalerOsdReferenceDelay(_OSD_B, _OSD_SECOND_DELAY);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_ucFontPointer0 = _OSD_PAGE_0_START;
        g_ucFontPointer1 = _OSD_PAGE_1_START;
        g_ucFontPointer2 = _OSD_PAGE_2_START;

        OsdFuncApplyMapOsdAB(WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG), WIDTH(_OSD_HOTKEY_MENU_WIDTH), HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
        ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _ENABLE, HEIGHT(_OSD_HOTKEY_MENU_HEIGHT), _ENABLE);
#endif

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }

    OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNoticeMain, _PIP_MAIN);
    OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNoticeSub, _PIP_SUB);

    ScalerMDomainGetSubBackground(&stTimingFormat);
    usHPos = (stTimingFormat.usHStart - _PANEL_DH_START);
    usHWidth = (stTimingFormat.usHWidth - GET_OSD_SELECT_REGION_WIDTH());
    usVPos = (stTimingFormat.usVStart - _PANEL_DV_START);
    usVHeight = (stTimingFormat.usVHeight - GET_OSD_SELECT_REGION_WIDTH());

    usPostionH = 0xFFFF;
    usPostionV = 0xFFFF;
    if(_TRUE)
    {
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            switch(GET_OSD_PIP_POSITION_TYPE())
            {
                case _PIP_POSITON_LT:
                    usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2)) / 4;
                    usPostionV = usVPos + usVHeight + ((_PANEL_DV_HEIGHT - usVPos - usVHeight - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2);
                    break;

                case _PIP_POSITON_LB:
                    usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2)) / 4;
                    usPostionV = (usVPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2;
                    break;

                case _PIP_POSITON_RT:
                    usPostionH = (usHPos - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 8;
                    usPostionV = usVPos + usVHeight + ((_PANEL_DV_HEIGHT - usVPos - usVHeight - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2);
                    break;

                case _PIP_POSITON_RB:
                    usPostionH = (usHPos - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 8;
                    usPostionV = (usVPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2;
                    break;

                case _PIP_POSITON_MIDDLE:
                    usPostionH = (_PANEL_DH_WIDTH - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 8;
                    usPostionV = (usVPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2;
                    break;

                case _PIP_POSITON_USER:
                    if(GET_OSD_PIP_USER_POSITION_H() >= _OSD_PIP_USER_POSITION_H_CENTER)
                    {
                        usPostionH = (usHPos - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 8;
                    }
                    else
                    {
                        usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2)) / 4;
                    }

                    if(GET_OSD_PIP_USER_POSITION_V() >= _OSD_PIP_USER_POSITION_V_CENTER)
                    {
                        usPostionV = (usVPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2;
                    }
                    else
                    {
                        usPostionV = usVPos + usVHeight + ((_PANEL_DV_HEIGHT - usVPos - usVHeight - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2);
                    }
                    break;

                default:
                    break;
            }
        }
        else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
                (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            switch(GET_OSD_PIP_POSITION_TYPE())
            {
                case _PIP_POSITON_LT:
                    usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2)) / 4;
                    usPostionV = usVPos + usVHeight + ((_PANEL_DV_HEIGHT - usVPos - usVHeight - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2);
                    break;

                case _PIP_POSITON_LB:
                    usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2)) / 4;
                    usPostionV = (usVPos - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                    break;

                case _PIP_POSITON_RT:
                    usPostionH = (usHPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 8;
                    usPostionV = usVPos + usVHeight + ((_PANEL_DV_HEIGHT - usVPos - usVHeight - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2);
                    break;

                case _PIP_POSITON_RB:
                    usPostionH = (usHPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 8;
                    usPostionV = (usVPos - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                    break;

                case _PIP_POSITON_MIDDLE:
                    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
                    {
                        usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2)) / 4;
                    }
                    else
                    {
                        usPostionH = (((usHPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2)) / 4;
                    }
                    usPostionV = (_PANEL_DV_HEIGHT - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                    break;

                case _PIP_POSITON_USER:
                    if(GET_OSD_PIP_USER_POSITION_H() >= _OSD_PIP_USER_POSITION_H_CENTER)
                    {
                        usPostionH = (usHPos - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 8;
                    }
                    else
                    {
                        usPostionH = (usHPos + usHWidth + ((_PANEL_DH_WIDTH - usHPos - usHWidth - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2)) / 4;
                    }

                    if(GET_OSD_PIP_USER_POSITION_V() >= _OSD_PIP_USER_POSITION_V_CENTER)
                    {
                        usPostionV = (_PANEL_DV_HEIGHT - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                    }
                    else
                    {
                        usPostionV = (_PANEL_DV_HEIGHT - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, usPostionH, usPostionV);

    ////////// Sub
    usPostionH = 0xFFFF;
    usPostionV = 0xFFFF;
    if(_TRUE)
    {
        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) || (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            if((_OSD_HOTKEY_MENU_WIDTH * ucFonWidth) > usHWidth)
            {
                usPostionH = (usHPos) / 4;
            }
            else
            {
                usPostionH = (usHPos + ((usHWidth - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2)) / 4;
            }

            if((_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) > usVHeight)
            {
                usPostionV = usVPos;
            }
            else
            {
                usPostionV = usVPos + ((usVHeight - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2);
            }
        }
        else if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
                (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
        {
            if((_OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) > usHWidth)
            {
                usPostionH = (usHPos) / 4;
            }
            else
            {
                usPostionH = (usHPos + ((usHWidth - _OSD_HOTKEY_MENU_HEIGHT * ucFonHeight) / 2)) / 4;
            }

            if((_OSD_HOTKEY_MENU_WIDTH * ucFonWidth) > usVHeight)
            {
                usPostionV = usVPos;
            }
            else
            {
                usPostionV = usVPos + ((usVHeight - _OSD_HOTKEY_MENU_WIDTH * ucFonWidth) / 2);
            }
        }
    }
    OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, usPostionH, usPostionV);
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
#endif // End of #if(_PIP_DISPLAY_SUPPORT == _ON)

#if(_4P_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : No signal & No cable & No support for Multi 4P
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdDispMpDisplayStateNotice_4P(BYTE ucNotice1P, BYTE ucNotice2P, BYTE ucNotice3P, BYTE ucNotice4P)
{
    BYTE ucFonWidth = _FONT_WIDTH;
    BYTE ucFonHeight = _FONT_HEIGHT;

    if(GET_OSD_DOUBLE_SIZE() == _ON)
    {
        ucFonWidth = _FONT_WIDTH * 2;
        ucFonHeight = _FONT_HEIGHT * 2;
    }

    DebugMessageOsd("4.ucNotice1P", ucNotice1P);
    DebugMessageOsd("4.ucNotice2P", ucNotice2P);
    DebugMessageOsd("4.ucNotice3P", ucNotice3P);
    DebugMessageOsd("4.ucNotice4P", ucNotice4P);

    if(GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION)
    {
        OsdFuncDisableOsd();

        ScalerOsd2FontFunction(_ENABLE);
        ScalerOsdReferenceDelay(_OSD_A, _OSD_FIRST_DELAY);
        ScalerOsdReferenceDelay(_OSD_B, _OSD_SECOND_DELAY);

        SET_OSD_STATE(_MENU_HOTKEY_INFORMATION);

        g_ucFontPointer0 = _OSD_PAGE_0_START;
        g_ucFontPointer1 = _OSD_PAGE_1_START;
        g_ucFontPointer2 = _OSD_PAGE_2_START;

        if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
           (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight)), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT((_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight))), _ENABLE, HEIGHT((_MESSAGE_HEIGHT_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonHeight))), _ENABLE);
#endif
        }
        else
        {
            OsdFuncApplyMapOsdAB(WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG), WIDTH(_MESSAGE_WIDTH_FONT_NUM + (_PANEL_DV_HEIGHT / 2 / ucFonWidth)), HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), COLOR(_CP_WHITE, _CP_BG));
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE)
            ScalerOsdMapRotation(GET_OSD_ROTATE_STATUS(), _ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _ENABLE, HEIGHT(_MESSAGE_HEIGHT_FONT_NUM), _ENABLE);
#endif
        }

        OsdFuncBlending(_OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND);
        OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());

        // Adjust Color Palette
        OsdPaletteSelectPalette(_PALETTE_MAIN_MENU);

        // Load Font & Icon
        OsdFuncSet2BitIconOffset(_2BIT_ICON_OFFSET);

        OsdFontVLCLoadFont(_FONT1_GLOBAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_ICON, _ICON_NO_SUPPORT);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_0, _ICON_NO_SUPPORT_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SUPPORT_TEXT_1, _ICON_NO_SUPPORT_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_ICON, _ICON_NO_CABLE);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_0, _ICON_NO_CABLE_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_CABLE_TEXT_1, _ICON_NO_CABLE_TEXT_1);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_ICON, _ICON_NO_SIGNAL);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_0, _ICON_NO_SIGNAL_TEXT_0);
        OsdFontLoadNoticeIcon(_POS_NOTICE_NO_SIGNAL_TEXT_1, _ICON_NO_SIGNAL_TEXT_1);
    }
    if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0)
    {
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice1P, _4P_LT);
        OsdDispMpDisplayStateNotice(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice2P, _4P_LB);

        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice3P, _4P_RT);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice4P, _4P_RB);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice2P, _4P_LB);
        OsdDispMpDisplayStateNotice(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice1P, _4P_LT);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice4P, _4P_RB);
        OsdDispMpDisplayStateNoticeFontB(ROW(_PANEL_DV_HEIGHT / 2 / ucFonHeight), COL(0), ucNotice3P, _4P_RT);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice3P, _4P_RT);
        OsdDispMpDisplayStateNotice(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice4P, _4P_RB);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice1P, _4P_LT);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice2P, _4P_LB);
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        ////////// OSD A
        OsdDispMpDisplayStateNotice(ROW(0), COL(0), ucNotice2P, _4P_LB);
        OsdDispMpDisplayStateNotice(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice1P, _4P_LT);

        ////////// OSD B
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(0), ucNotice4P, _4P_RB);
        OsdDispMpDisplayStateNoticeFontB(ROW(0), COL(_PANEL_DV_HEIGHT / 2 / ucFonWidth), ucNotice3P, _4P_RT);
    }

    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_0) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_180))
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (((_PANEL_DH_WIDTH / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)) / 4), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)) / 4), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)));
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)) / 4), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (((_PANEL_DH_WIDTH / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)) / 4), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }
    else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
    {
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_A, (((_PANEL_DH_WIDTH / 4) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)) / 4), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
        OsdDispSetPosition(_POS_DIRECT, _OSD_POSITION_GLOBAL_B, (((_PANEL_DH_WIDTH / 4 * 3) - (_MESSAGE_HEIGHT_MID_FONT_NUM * ucFonHeight)) / 4), ((_PANEL_DV_HEIGHT / 4) - (_MESSAGE_WIDTH_MID_FONT_NUM * ucFonWidth)));
    }
    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    OsdFuncEnableOsd();
}
#endif // End of #if(_4P_DISPLAY_SUPPORT == _ON)

#if (_FALSE_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE OSDDispFalseColorConvert(BYTE ucIndexsel)
{
    // false color palette from 16~47
    return ((ucIndexsel) + _BIT4);
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void OsdDispFalseColorMenu(void)
{
    BYTE ucTest = 0;

    OsdPaletteSelectPalette(_PALETTE_FALSE_COLOR_MENU);

    // down
    OsdPropPutString(ROW(12), COL(_DOWN_ICON_START_COL - 1), _PFONT_PAGE_1, _STRING_FALSE_COLOR_CURSOR_1, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);
    OsdPropPutString(ROW(12), COL(_DOWN_ICON_START_COL + 34 - 3), _PFONT_PAGE_1, _STRING_FALSE_COLOR_CURSOR_2, COLOR(_CP_BLUE, _CP_BG), _ENGLISH);

    //
    for(ucTest = 0; ucTest < 17; ucTest++)
    {
        OsdBlankFont(ROW(14), COL(_DOWN_ICON_START_COL + 2 * ucTest), 1, 2, 12, OSDDispFalseColorConvert(GET_OSD_FALSE_COLOR_LEVEL(ucTest)), _OSD_BLANK_FONT);
    }

    for(ucTest = 0; ucTest < 20; ucTest++)
    {
        OsdBlankFont(ROW(18), COL(_DOWN_ICON_START_COL + 2 * ucTest), 1, 2, 12, OSDDispFalseColorConvert(ucTest), _OSD_BLANK_FONT);
    }
}
#endif

#endif // End of #if(_OSD_TYPE == _REALTEK_2014_OSD)
