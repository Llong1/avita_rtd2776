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
// ID Code      : UserCommonAdjust.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_ADJUST__

#include "UserCommonInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_VGA_SUPPORT == _ON)

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
//----------------------------------------------------------------------------------------------------
// TABLE DIGITAL FILTER ENHANCE PHASE MODE
//----------------------------------------------------------------------------------------------------
#include _DIGITAL_FILTER_ENHANCE_PHASE_TABLE
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// TABLE RINGING FILTER OFFSET COEFFICIENT
//----------------------------------------------------------------------------------------------------
#include _RINGING_FILTER_TABLE
#endif

#endif  // End of #if(_VGA_SUPPORT == _ON)

#if(_FALSE_COLOR_SUPPORT == _ON)
BYTE code tFALSECOLOR_TABLE[][3] =
{
    {  0,   0, 255}, // _FC_BLUE,
    {  0,  64, 255}, // _FC_BLUECYAN1,
    {  0, 128, 255}, // _FC_BLUECYAN2,
    {  0, 192, 255}, // _FC_BLUECYAN3,
    {  0, 255, 255}, // _FC_CYAN,
    {  0, 255, 192}, // _FC_CYANGREEN1,
    {  0, 255, 128}, // _FC_CYANGREEN2,
    {  0, 255,  64}, // _FC_CYANGREEN3,
    {  0, 255,   0}, // _FC_GREEN,
    { 64, 255,   0}, // _FC_GREENYELLOW1,
    {128, 255,   0}, // _FC_GREENYELLOW2,
    {192, 255,   0}, // _FC_GREENYELLOW3,
    {255, 255,   0}, // _FC_YELLOW,
    {255, 192,   0}, // _FC_ORANGE1,
    {255, 128,   0}, // _FC_ORANGE2,
    {255,  64,   0}, // _FC_ORANGE3,
    {255,   0,   0}, // _FC_RED,

    {255, 255, 255}, // _FC_WHITE,
    {128, 128, 128}, // _FC_GRAY,
    {  0,   0,   0}, // _FC_BLACK,
};
#endif



//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_UNIFORMITY_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// TABLE Uniformity Gain
//----------------------------------------------------------------------------------------------------
WORD code tUNIFORMITY_OSD_TYPE_ADDRESS_INDEX[] =
{
    _UNIFORMITY_TYPE1_ADDRESS,
    _UNIFORMITY_TYPE2_ADDRESS,
    _UNIFORMITY_TYPE3_ADDRESS,
    _UNIFORMITY_TYPE4_ADDRESS,
    _UNIFORMITY_TYPE5_ADDRESS,
    _UNIFORMITY_TYPE6_ADDRESS,
};

BYTE code tUNIFORMITY_OSD_TYPE_BANK_INDEX[] =
{
    _UNIFORMITY_TYPE1_BANK,
    _UNIFORMITY_TYPE2_BANK,
    _UNIFORMITY_TYPE3_BANK,
    _UNIFORMITY_TYPE4_BANK,
    _UNIFORMITY_TYPE5_BANK,
    _UNIFORMITY_TYPE6_BANK,
};

#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// TABLE Uniformity Offset and Decay Address
//----------------------------------------------------------------------------------------------------
WORD code tUNIFORMITY_OSD_TYPE_OFFSET_ADDRESS_INDEX[] =
{
    _UNIFORMITY_TYPE1_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE2_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE3_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE4_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE5_OFFSET_ADDRESS,
    _UNIFORMITY_TYPE6_OFFSET_ADDRESS,
};
BYTE code tUNIFORMITY_OSD_TYPE_OFFSET_BANK_INDEX[] =
{
    _UNIFORMITY_TYPE1_OFFSET_BANK,
    _UNIFORMITY_TYPE2_OFFSET_BANK,
    _UNIFORMITY_TYPE3_OFFSET_BANK,
    _UNIFORMITY_TYPE4_OFFSET_BANK,
    _UNIFORMITY_TYPE5_OFFSET_BANK,
    _UNIFORMITY_TYPE6_OFFSET_BANK,
};
WORD code tUNIFORMITY_OSD_TYPE_DECAY_ADDRESS_INDEX[] =
{
    _UNIFORMITY_TYPE1_DECAY_ADDRESS,
    _UNIFORMITY_TYPE2_DECAY_ADDRESS,
    _UNIFORMITY_TYPE3_DECAY_ADDRESS,
    _UNIFORMITY_TYPE4_DECAY_ADDRESS,
    _UNIFORMITY_TYPE5_DECAY_ADDRESS,
    _UNIFORMITY_TYPE6_DECAY_ADDRESS,
};
BYTE code tUNIFORMITY_OSD_TYPE_DECAY_BANK_INDEX[] =
{
    _UNIFORMITY_TYPE1_DECAY_BANK,
    _UNIFORMITY_TYPE2_DECAY_BANK,
    _UNIFORMITY_TYPE3_DECAY_BANK,
    _UNIFORMITY_TYPE4_DECAY_BANK,
    _UNIFORMITY_TYPE5_DECAY_BANK,
    _UNIFORMITY_TYPE6_DECAY_BANK,
};
BYTE code tUNIFORMITY_OSD_TYPE_OFFSET_ENABLE_INDEX[] =
{
    _UNIFORMITY_OFFSET_TYPE0,
    _UNIFORMITY_OFFSET_TYPE1,
    _UNIFORMITY_OFFSET_TYPE2,
    _UNIFORMITY_OFFSET_TYPE3,
    _UNIFORMITY_OFFSET_TYPE4,
    _UNIFORMITY_OFFSET_TYPE5,
};
#endif // End of #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

void UserCommonAdjustDisplayMode(EnumDisplayMode enumDisplayMode);
void UserCommonAdjustRegionInputPort(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort);

#if(_VGA_SUPPORT == _ON)
WORD UserCommonAdjustGetAdcClockRange(BYTE ucPar);
void UserCommonAdjustClock(WORD usUserIHTotal);
void UserCommonAdjustPhase(BYTE ucPhase);

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
void UserCommonAdjustDigitalFilterEnhancePhase(void);
#endif

#if(_RINGING_FILTER_SUPPORT == _ON)
void UserCommonAdjustRingingFilter(void);
#endif
#endif

WORD UserCommonAdjustGetHPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion);
WORD UserCommonAdjustGetHPositionHBiasValue(EnumDisplayRegion enumDisplayRegion);
WORD UserCommonAdjustGetVPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion);
WORD UserCommonAdjustGetVPositionVBiasValue(EnumDisplayRegion enumDisplayRegion);
void UserCommonAdjustHPosition(BYTE ucUserHPosition, EnumDisplayRegion enumDisplayRegion);
void UserCommonAdjustVPosition(BYTE ucUserVPosition, EnumDisplayRegion enumDisplayRegion);

BYTE UserCommonAdjustRealValueToPercent(WORD usRealValue, WORD usMax, WORD usMin, WORD usCenter);
WORD UserCommonAdjustPercentToRealValue(BYTE ucPercentValue, WORD usMax, WORD usMin, WORD usCenter);

#if(_OVERSCAN_SUPPORT == _ON)
void UserCommonAdjustOverScan(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_ASPECT_RATIO_SUPPORT == _ON)
void UserCommonAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
void UserCommonAdjustRotationInputSize(void);
void UserCommonAdjustRotationDisplaySize(void);
#endif

#if(_PIP_DISPLAY_SUPPORT == _ON)
void UserCommonAdjustPipSubTimingFormat(void);
#endif

#if(_I_DITHER_SUPPORT == _ON)
void UserCommonAdjustIDither(void);
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
void UserCommonAdjustPanelUniformity(EnumUniformityTypeSelect enumUniformityType, EnumUniformityModeSelect enumUniformityMode);
#endif

#if(_ULTRA_VIVID_SUPPORT == _ON)
void UserCommonAdjustUltraVivid(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_D_DITHER_SUPPORT == _ON)
void UserCommonAdjustDDither(void);
#endif

// 10  bit Panel
WORD UserCommonAdjust10bitPanelCompensate(WORD usData);

#if(_ULTRA_HDR_SUPPORT == _ON)
EnumHDRChangeStatus UserCommonAdjustHDRChangeStatus(EnumDisplayRegion enumDisplayRegion);
EnumHDRTargetStatus UserCommonAdjustHDRTargetStatus(EnumDisplayRegion enumDisplayRegion);
EnumHDRTargetStatus UserCommonAdjustHDRAutoModeInitial(EnumDisplayRegion enumDisplayRegion);
EnumHDRMaxMasteringLvType UserCommonAdjustHDRGetLvType(EnumDisplayRegion enumDisplayRegion);
void UserCommonAdjustHDRAutoMode(EnumDisplayRegion enumDisplayRegion, bit bDarkEnhanceEnable);
bit UserCommonAdjustHDREnableStatus(EnumDisplayRegion enumDisplayRegion, EnumHDRModeDef enumHDRModeDef);
#endif

#if(_DCR_SUPPORT == _ON)
void UserCommonAdjustDCR(void);
#endif

#if(_FREEZE_SUPPORT == _ON)
void UserCommonAdjustDisplayFreeze(bit bEn);
#endif

#if(_SHARPNESS_SUPPORT == _ON)
void UserCommonAdjustSharpness(EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort);
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
void UserCommonAdjustFalseColorEnable(EnumSelRegion enumSelRegion, EnumFunctionOnOFF enumOn);
void UserCommonAdjustFalseColorSRGBCtsAdjust(EnumSelRegion enumSelRegion);
void UserCommonAdjustFalseColorUpDateOGLUTInterpo(EnumSelRegion enumSelRegion, BYTE ucMode, BYTE ucLevel, BYTE ucColorCodeLast, BYTE ucColorCodeCur, BYTE ucColorCodeNext);
void UserCommonAdjustFalseColorModeChange(EnumSelRegion enumSelRegion, BYTE *pucFalseColorTable, BYTE ucBankNum);
void UserCommonAdjustFalseColorAdjust(EnumSelRegion enumSelRegion, BYTE ucLevel, BYTE ucColorCodeLast, BYTE ucColorCodeCur, BYTE ucColorCodeNext);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : User adjust target display mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustDisplayMode(EnumDisplayMode enumDisplayMode)
{
    EnumDisplayRegion enumAutoSearchTargetRegion = UserInterfaceGetAutoSearchTarget();

    EnumSourceSearchPort enumSourceSearchPort0 = UserInterfaceGetInputPort0();
#if(_MULTI_DISPLAY_MAX >= 0x02)
    EnumSourceSearchPort enumSourceSearchPort1 = UserInterfaceGetInputPort1();
#if(_4P_DISPLAY_SUPPORT == _ON)
    EnumSourceSearchPort enumSourceSearchPort2 = UserInterfaceGetInputPort2();
    EnumSourceSearchPort enumSourceSearchPort3 = UserInterfaceGetInputPort3();
#endif
#endif

    // Reset select region info
    SysRegionResetInfo();

    // Update display mode
    SysModeSetDisplayMode(enumDisplayMode);
    UserCommonNVRamSetSystemData(_DISPLAY_MODE, enumDisplayMode);

    // Update auto search target
    SysSourceSetMultiAutoSearchTarget(enumAutoSearchTargetRegion);

#if(_FREESYNC_SUPPORT == _ON)
    if(UserInterfaceGetFREESYNCEnable() == _TRUE)
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        ScalerSyncDpFREESYNCSupportSwitch(_DP_FREESYNC_CAPABILITY_SWITCH, _ON);
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        ScalerSyncSetFREESYNCSupport(_ON);
#endif
    }
    else
    {
#if(_DP_FREESYNC_SUPPORT == _ON)
        ScalerSyncDpFREESYNCSupportSwitch(_DP_FREESYNC_CAPABILITY_SWITCH, _OFF);
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        ScalerSyncSetFREESYNCSupport(_OFF);
#endif
    }
#endif

    // Update region info
    switch(enumDisplayMode)
    {
        default:
        case _DISPLAY_MODE_1P:
            SysRegionUpdateInterface(_DISPLAY_RGN_1P, enumSourceSearchPort0);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_0, enumSourceSearchPort0);
            break;

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PIP:
            SysRegionUpdateInterface(_DISPLAY_RGN_MAIN, enumSourceSearchPort0);
            SysRegionUpdateInterface(_DISPLAY_RGN_SUB, enumSourceSearchPort1);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_0, enumSourceSearchPort0);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_1, enumSourceSearchPort1);
            break;
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_LR:
            SysRegionUpdateInterface(_DISPLAY_RGN_LEFT, enumSourceSearchPort0);
            SysRegionUpdateInterface(_DISPLAY_RGN_RIGHT, enumSourceSearchPort1);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_0, enumSourceSearchPort0);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_1, enumSourceSearchPort1);
            break;
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_TB:
            SysRegionUpdateInterface(_DISPLAY_RGN_TOP, enumSourceSearchPort0);
            SysRegionUpdateInterface(_DISPLAY_RGN_BOTTOM, enumSourceSearchPort1);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_0, enumSourceSearchPort0);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_1, enumSourceSearchPort1);
            break;
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            SysRegionUpdateInterface(_DISPLAY_RGN_LT, enumSourceSearchPort0);
            SysRegionUpdateInterface(_DISPLAY_RGN_LB, enumSourceSearchPort1);
            SysRegionUpdateInterface(_DISPLAY_RGN_RT, enumSourceSearchPort2);
            SysRegionUpdateInterface(_DISPLAY_RGN_RB, enumSourceSearchPort3);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_0, enumSourceSearchPort0);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_1, enumSourceSearchPort1);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_2, enumSourceSearchPort2);
            UserCommonNVRamSetSystemData(_SEARCH_PORT_3, enumSourceSearchPort3);
            break;
#endif
    }

    if(enumAutoSearchTargetRegion != _DISPLAY_RGN_NONE)
    {
        // Switch to auto target region
        SysSourceSwitchInputPort(SysRegionGetPortType(enumAutoSearchTargetRegion));
    }
    else
    {
        // Switch to region 0
        SysSourceSwitchInputPort(enumSourceSearchPort0);
    }

    // Save system data
    UserCommonNVRamSaveSystemData();

    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_DISPLAY_INITIAL:
        case _MODE_STATUS_DISPLAY_SETTING:
        case _MODE_STATUS_DISPLAY_CHECK:

            // Reset to display initial
            SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : User adjust input port of target display region
// Input Value  : enumDisplayRegion --> adjust target region
//                enumSourceSearchPort --> adjust target port
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustRegionInputPort(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort)
{
    // Reset to display initial under power saving
    if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
    {
        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
    }
    else
    {
        // Reset path
        SysModeResetDataPath(ScalerRegionGetIndex(enumDisplayRegion));
    }

    // Update region/port mapping
    SysRegionUpdateInterface(enumDisplayRegion, enumSourceSearchPort);

    // Update auto search target
    SysSourceSetMultiAutoSearchTarget(UserInterfaceGetAutoSearchTarget());

    // Update system data in NVRAM
    switch(ScalerRegionGetIndex(enumDisplayRegion))
    {
        default:
        case 0x00:
            UserCommonNVRamSetSystemData(_SEARCH_PORT_0, enumSourceSearchPort);
            break;

#if(_MULTI_DISPLAY_MAX >= 0X02)
        case 0x01:
            UserCommonNVRamSetSystemData(_SEARCH_PORT_1, enumSourceSearchPort);
            break;

#if(_4P_DISPLAY_SUPPORT == _ON)
        case 0x02:
            UserCommonNVRamSetSystemData(_SEARCH_PORT_2, enumSourceSearchPort);
            break;

        case 0x03:
            UserCommonNVRamSetSystemData(_SEARCH_PORT_3, enumSourceSearchPort);
            break;
#endif

#endif
    }

    // Switch source handler search port
    SysSourceSwitchInputPort(enumSourceSearchPort);

    // Save system data
    UserCommonNVRamSaveSystemData();
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check if the ADC clock (IHTotal) is out of range. Range = (BackPorch + FrontPorch) * 2 / 5 .
// Input Value  : usClock   --> ADC Clock (IHTotal)
// Output Value : Return _TRUE if not out of range
//--------------------------------------------------
WORD UserCommonAdjustGetAdcClockRange(BYTE ucPar)
{
    WORD usDelta1 = 0;
    WORD usDelta2 = 0;
    WORD usDelta = 0;

    usDelta1 = GET_ADC_LIMIT_CLOCK() - g_stVGAModeUserData.usCenterClock;

    usDelta2 = g_stVGAModeUserData.usCenterClock - ScalerVgaTopGetCaptureHStartPosition() - ScalerVgaTopGetCaptureHWidth();

    usDelta = (usDelta1 < usDelta2) ? usDelta1 : usDelta2;

    if(ucPar == _GET_CLOCKRANGE_MAX)
    {
        if(usDelta < _CLOCK_BIAS)
        {
            return (g_stVGAModeUserData.usCenterClock + usDelta);
        }
        else
        {
            return (g_stVGAModeUserData.usCenterClock + _CLOCK_BIAS);
        }
    }
    else if(ucPar == _GET_CLOCKRANGE_MIN)
    {
        if(usDelta < _CLOCK_BIAS)
        {
            return (g_stVGAModeUserData.usCenterClock - usDelta);
        }
        else
        {
            return (g_stVGAModeUserData.usCenterClock - _CLOCK_BIAS);
        }
    }

    return (g_stVGAModeUserData.usCenterClock);
}

//--------------------------------------------------
// Description  : Adjust clock.
// Input Value  : usUserIHTotal --> OSD Value(0~100) or Real Value
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustClock(WORD usUserIHTotal)
{
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)

    WORD usClockRangeMax = 0;
    WORD usClockRangeMin = 0;

    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
    usUserIHTotal = UserCommonAdjustPercentToRealValue((BYTE)usUserIHTotal, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

#endif

    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(SysVgaGetRegion());

    SysVgaWatchDog(_DISABLE);

    ScalerAPLLFastLockAdjust(usUserIHTotal);

    SysVgaWatchDog(_ENABLE);
}

//--------------------------------------------------
// Description  : Adjust phase
// Input Value  : ucPhase --> phase value
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustPhase(BYTE ucPhase)
{
    // Set timing info index
    SysRegionSetMeasureResultPointerRegion(SysVgaGetRegion());

    ucPhase = UserCommonAdjustPercentToRealValue(ucPhase, _ADJUST_PHASE_MAX, _ADJUST_PHASE_MIN, _ADJUST_PHASE_CENTER);

    SysVgaWatchDog(_DISABLE);

    ScalerPLLSetPhase(ucPhase, UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVFREQ));

    SysVgaWatchDog(_ENABLE);
}

#if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)
//--------------------------------------------------
// Description  : Adjust Digital Filter Enhanced Phase Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustDigitalFilterEnhancePhase(void)
{
    BYTE ucI = 0;
    BYTE ucTemp = 0;
    BYTE ucSpan = 0;
    SWORD shTemp = 0;
    WORD usPixelRate = (ScalerSyncGetInputPixelClk(_A0_INPUT_PORT) + 5) / 10;

    if(usPixelRate <= tDF_ENHANCE_PHASE_SETTING[0])
    {
        pData[0] = tDF_ENHANCE_PHASE_SETTING[1];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[2];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[3];
    }
    else if(usPixelRate >= tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 4])
    {
        pData[0] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 3];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 2];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[sizeof(tDF_ENHANCE_PHASE_SETTING) - 1];
    }
    else
    {
        for(ucI = 0; tDF_ENHANCE_PHASE_SETTING[ucI * 4] < usPixelRate; ucI++) {};

        ucI--;

        ucTemp = usPixelRate - tDF_ENHANCE_PHASE_SETTING[ucI * 4];
        ucSpan = tDF_ENHANCE_PHASE_SETTING[(ucI + 1) * 4] - tDF_ENHANCE_PHASE_SETTING[ucI * 4];

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 1] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 1];
        pData[0] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 1] + (SWORD)ucTemp * shTemp / ucSpan;

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 2] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 2];
        pData[1] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 2] + (SWORD)ucTemp * shTemp / ucSpan;

        shTemp = tDF_ENHANCE_PHASE_SETTING[((ucI + 1) * 4) + 3] - tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 3];
        pData[2] = tDF_ENHANCE_PHASE_SETTING[(ucI * 4) + 3] + (SWORD)ucTemp * shTemp / ucSpan;
    }

    ScalerColorDigitalFilterEnhancePhaseAdjust(pData);
}
#endif // End of #if(_DIG_FILTER_ENHANCE_PHASE_ENABLE == _ENABLE)


#if(_RINGING_FILTER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Ringing Filter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustRingingFilter(void)
{
    BYTE ucI = 0;
    BYTE ucTemp = 0;
    BYTE ucSpan = 0;
    SWORD shTemp = 0;
    WORD usPixelRate = (ScalerSyncGetInputPixelClk(_A0_INPUT_PORT) + 5) / 10;

    if(usPixelRate <= tRF_OFFSET_COEF_SETTING[0])
    {
        pData[0] = tRF_OFFSET_COEF_SETTING[1];
    }
    else if(usPixelRate >= tRF_OFFSET_COEF_SETTING[sizeof(tRF_OFFSET_COEF_SETTING) - 2])
    {
        pData[0] = tRF_OFFSET_COEF_SETTING[sizeof(tRF_OFFSET_COEF_SETTING) - 1];
    }
    else
    {
        for(ucI = 0; tRF_OFFSET_COEF_SETTING[ucI * 2] < usPixelRate; ucI++) {};

        ucI--;

        ucTemp = usPixelRate - tRF_OFFSET_COEF_SETTING[ucI * 2];
        ucSpan = tRF_OFFSET_COEF_SETTING[(ucI + 1) * 2] - tRF_OFFSET_COEF_SETTING[ucI * 2];

        shTemp = tRF_OFFSET_COEF_SETTING[((ucI + 1) * 2) + 1] - tRF_OFFSET_COEF_SETTING[(ucI * 2) + 1];
        pData[0] = tRF_OFFSET_COEF_SETTING[(ucI * 2) + 1] + (SWORD)ucTemp * shTemp / ucSpan;
    }

    ScalerColorRingingFilterAdjust(pData);
}
#endif // End of #if(_RINGING_FILTER_SUPPORT == _ON)
#endif // End of #if(_VGA_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get Max or Min H-Position
// Input Value  : ucPar--> Max or Min paramater
// Output Value : Max or Min H-Position
//--------------------------------------------------
WORD UserCommonAdjustGetHPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion)
{
    WORD usDeltaIHWidthOverScan = 0;
    WORD usIHWidth = 0;

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        usIHWidth = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IHWIDTH);
    }
    else
#endif
    {
        usIHWidth = GET_INPUT_TIMING_HWIDTH();

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _TRUE)
        {
            if(usIHWidth >= ScalerVgipGetCaptureHWidth())
            {
                if((SysModeGetDisplayMode() == _DISPLAY_MODE_4P) ||
                   (ScalerFmtCnvFtoPGetStatus(ScalerRegionGetInputDataPath(enumDisplayRegion)) == _FALSE))
                {
                    usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()) / 2);
                }
                else
                {
                    usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()));
                }
            }
        }
#endif
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_OVERSCAN_SUPPORT == _ON)
    if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _FALSE)
#endif
    {
        if((ScalerRotationCheckStatus() == _TRUE) && (GET_ROT_DISP_SIZE() == _ROT_PIXEL_BY_PIXEL))
        {
            if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
            {
                if(_PANEL_DV_HEIGHT < usIHWidth)
                {
                    usDeltaIHWidthOverScan = (usIHWidth - _PANEL_DV_HEIGHT);
                }
            }
            else if(GET_ROT_TYPE() == _ROT_CW180)
            {
                // Calculate / Set H
                if(_PANEL_DH_WIDTH < usIHWidth)
                {
                    usDeltaIHWidthOverScan = (usIHWidth - _PANEL_DH_WIDTH);
                }
            }
        }
    }
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        if(ucPar == _GET_HPOSITIONRANGE_MAX)
        {
            return (g_stVGAModeUserData.usCenterHPosition + _HPOSITION_BIAS);
        }
        else if(ucPar == _GET_HPOSITIONRANGE_MIN)
        {
            return (g_stVGAModeUserData.usCenterHPosition - _HPOSITION_BIAS);
        }
        else
        {
            return (g_stVGAModeUserData.usCenterHPosition);
        }
    }
    else
#endif
    {
        if(ucPar == _GET_HPOSITIONRANGE_MAX)
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan + _HPOSITION_BIAS);
        }
        else if(ucPar == _GET_HPOSITIONRANGE_MIN)
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - _HPOSITION_BIAS);
        }
        else
        {
            return (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan);
        }
    }
}

//--------------------------------------------------
// Description  : Get HPosition H Bias Value
// Input Value  : None
// Output Value : H Bias Value
//--------------------------------------------------
WORD UserCommonAdjustGetHPositionHBiasValue(EnumDisplayRegion enumDisplayRegion)
{
    WORD usHBias = 0;
    WORD usDeltaIHWidthOverScan = 0;
    WORD usIHWidth = 0;

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        usIHWidth = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IHWIDTH);

        usHBias = ((g_stVGAModeUserData.usCenterHPosition - ScalerVgaTopGetCaptureHStartPosition()) <= (_MAX_H_POSITION_RANGE / 2)) ?
                  (g_stVGAModeUserData.usCenterHPosition - ScalerVgaTopGetCaptureHStartPosition() - 1) : (_MAX_H_POSITION_RANGE / 2);
    }
    else
#endif
    {
        usIHWidth = GET_INPUT_TIMING_HWIDTH();

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _TRUE)
        {
            if(usIHWidth >= ScalerVgipGetCaptureHWidth())
            {
                usDeltaIHWidthOverScan = ((usIHWidth - ScalerVgipGetCaptureHWidth()) / 2);
            }
        }
#endif

        usHBias = ((GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - ScalerVgipGetCaptureHStartPosition()) <= (_MAX_H_POSITION_RANGE / 2)) ?
                  (GET_INPUT_TIMING_HSTART() + usDeltaIHWidthOverScan - ScalerVgipGetCaptureHStartPosition() - 1) : (_MAX_H_POSITION_RANGE / 2);
    }

    return usHBias;
}

//--------------------------------------------------
// Description  : Get Max or Min V-Position
// Input Value  : ucPar--> Max or Min paramater
// Output Value : Max or Min V-Position
//--------------------------------------------------
WORD UserCommonAdjustGetVPositionRange(BYTE ucPar, EnumDisplayRegion enumDisplayRegion)
{
    WORD usDeltaIVHeightOverScan = 0;
    WORD usDeltaIVHeightUnderScan = 0;
    WORD usIVHeight = 0;

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        usIVHeight = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVHEIGHT);

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _TRUE)
        {
            if(usIVHeight >= ScalerVgaTopGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgaTopGetCaptureVHeight()) / 2);
            }
        }
#endif
    }
    else
#endif
    {
        usIVHeight = GET_INPUT_TIMING_VHEIGHT();

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _TRUE)
        {
            if(usIVHeight >= ScalerVgipGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgipGetCaptureVHeight()) / 2);
            }
        }
#endif
    }

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_OVERSCAN_SUPPORT == _ON)
    if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _FALSE)
#endif
    {
        if((ScalerRotationCheckStatus() == _TRUE) && (GET_ROT_DISP_SIZE() == _ROT_PIXEL_BY_PIXEL))
        {
            if((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270))
            {
                // Calculate / Set V
                if(_PANEL_DH_WIDTH < usIVHeight)
                {
                    usDeltaIVHeightOverScan = ((usIVHeight - _PANEL_DH_WIDTH) / 2);
                }
            }
            else if(GET_ROT_TYPE() == _ROT_CW180)
            {
                if(_PANEL_DV_HEIGHT < usIVHeight)
                {
                    usDeltaIVHeightOverScan = ((usIVHeight - _PANEL_DV_HEIGHT) / 2);
                }
            }
        }
    }
#endif

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        if(usIVHeight <= ScalerVgaTopGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgaTopGetCaptureVHeight() - usIVHeight) / 2);
        }

        if(ucPar == _GET_VPOSITIONRANGE_MAX)
        {
            return (g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan + _VPOSITION_BIAS);
        }
        else if(ucPar == _GET_VPOSITIONRANGE_MIN)
        {
            return (g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - _VPOSITION_BIAS);
        }
        else
        {
            return (g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan);
        }
    }
    else
#endif
    {
        if(usIVHeight <= ScalerVgipGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgipGetCaptureVHeight() - usIVHeight) / 2);
        }

        if(ucPar == _GET_VPOSITIONRANGE_MAX)
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan + _VPOSITION_BIAS);
        }
        else if(ucPar == _GET_VPOSITIONRANGE_MIN)
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - _VPOSITION_BIAS);
        }
        else
        {
            return (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan);
        }
    }
}

//--------------------------------------------------
// Description  : Get VPosition V Bias Value
// Input Value  : None
// Output Value : V Bias Value
//--------------------------------------------------
WORD UserCommonAdjustGetVPositionVBiasValue(EnumDisplayRegion enumDisplayRegion)
{
    WORD usVBias = 0;
    WORD usDeltaIVHeightOverScan = 0;
    WORD usDeltaIVHeightUnderScan = 0;
    WORD usIVHeight = 0;

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        usIVHeight = UserCommonModeSearchGetModetableTimingDataItem(g_stVGAModeUserData.ucModeNumber, _IVHEIGHT);


#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _TRUE)
        {
            if(usIVHeight >= ScalerVgaTopGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgaTopGetCaptureVHeight()) / 2);
            }
        }
#endif

        if(usIVHeight <= ScalerVgaTopGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgaTopGetCaptureVHeight() - usIVHeight) / 2);
        }

        usVBias = ((g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgaTopGetCaptureVStartPosition()) < (_MAX_V_POSITION_RANGE / 2)) ?
                  (g_stVGAModeUserData.usCenterVPosition + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgaTopGetCaptureVStartPosition()) : (_MAX_V_POSITION_RANGE / 2);
    }
    else
#endif
    {
        usIVHeight = GET_INPUT_TIMING_VHEIGHT();

#if(_OVERSCAN_SUPPORT == _ON)
        if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _TRUE)
        {
            if(usIVHeight >= ScalerVgipGetCaptureVHeight())
            {
                usDeltaIVHeightOverScan = ((usIVHeight - ScalerVgipGetCaptureVHeight()) / 2);
            }
        }
#endif

        if(usIVHeight <= ScalerVgipGetCaptureVHeight())
        {
            usDeltaIVHeightUnderScan = ((ScalerVgipGetCaptureVHeight() - usIVHeight) / 2);
        }

        usVBias = ((GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgipGetCaptureVStartPosition()) < (_MAX_V_POSITION_RANGE / 2)) ?
                  (GET_INPUT_TIMING_VSTART() + usDeltaIVHeightOverScan - usDeltaIVHeightUnderScan - ScalerVgipGetCaptureVStartPosition()) : (_MAX_V_POSITION_RANGE / 2);
    }

    return usVBias;
}

//--------------------------------------------------
// Description  : Adjust picture position.
// Input Value  : ucUserHPosition --> Current percentage of H position associate to OSD bar
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustHPosition(BYTE ucUserHPosition, EnumDisplayRegion enumDisplayRegion)
{
    WORD usTargetIHStart = 0;
    WORD usHPositionRangeMax = 0;
    WORD usHPositionRangeMin = 0;
    SWORD shHDelay = 0;
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType(enumDisplayRegion);

    ScalerVgipSetInputRegion(enumDisplayRegion);
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    usHPositionRangeMax = UserCommonAdjustGetHPositionRange(_GET_HPOSITIONRANGE_MAX, enumDisplayRegion);
    usHPositionRangeMin = UserCommonAdjustGetHPositionRange(_GET_HPOSITIONRANGE_MIN, enumDisplayRegion);

    usTargetIHStart = UserCommonAdjustPercentToRealValue((100 - ucUserHPosition), usHPositionRangeMax, usHPositionRangeMin, (((usHPositionRangeMax - usHPositionRangeMin) / 2) + usHPositionRangeMin));

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        // Disable Wach dog
        SysVgaWatchDog(_DISABLE);

        shHDelay = (SWORD)usTargetIHStart - (SWORD)ScalerVgaTopGetCaptureHStartPosition();

        if((ScalerColorGetColorSpace(enumSourceSearchPort) == _COLOR_SPACE_YCBCR422) || (ScalerColorGetColorSpace(enumSourceSearchPort) == _COLOR_SPACE_YCBCR420))
        {
            shHDelay += ((shHDelay - ScalerVgaTopGetCaptureHDelay()) % 2);
        }

        // Can't set IH delay to 0 by HW limit
        shHDelay = (shHDelay < 1) ? 1 : shHDelay;

        // Compensate IHS delay
        ScalerVgaTopSetCaptureHDelay(shHDelay);

        // Apply the above setting by setting Double Buffer Ready in VGIP
        ScalerVgaTopDoubleBufferApply();

        // Enable Wach dog
        SysVgaWatchDog(_ENABLE);
    }
    else
#endif
    {
        if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
        {
            // Disable Wach dog
            ScalerGlobalWatchDog(enumDisplayRegion, _DISABLE);

            shHDelay = (SWORD)usTargetIHStart - (SWORD)ScalerVgipGetCaptureHStartPosition();

            if((ScalerColorGetColorSpace(enumSourceSearchPort) == _COLOR_SPACE_YCBCR422) || (ScalerColorGetColorSpace(enumSourceSearchPort) == _COLOR_SPACE_YCBCR420))
            {
                shHDelay += ((shHDelay - ScalerVgipGetCaptureHDelay()) % 2);
            }

            // Can't set IH delay to 0 by HW limit
            shHDelay = (shHDelay < 1) ? 1 : shHDelay;

            // Compensate IHS delay
            ScalerVgipSetCaptureHDelay(shHDelay);

            // Apply the above setting by setting Double Buffer Ready in VGIP
            ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

            // Enable Wach dog
            ScalerGlobalWatchDog(enumDisplayRegion, _ENABLE);
        }
    }
}

//--------------------------------------------------
// Description  : Adjust picture position.
// Input Value  : ucUserVPosition --> Current percentage of V position associate to OSD bar
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustVPosition(BYTE ucUserVPosition, EnumDisplayRegion enumDisplayRegion)
{
    WORD usTargetIVStart = 0;
    WORD usVDelayAdjustDeltaLimit = 0;
    WORD usVPositionRangeMax = 0;
    WORD usVPositionRangeMin = 0;
    SWORD shVDelay = 0;
    BYTE ucTimeoutCounter = 0;

    ScalerVgipSetInputRegion(enumDisplayRegion);
    SysRegionSetMeasureResultPointerRegion(enumDisplayRegion);

    usVPositionRangeMax = UserCommonAdjustGetVPositionRange(_GET_VPOSITIONRANGE_MAX, enumDisplayRegion);
    usVPositionRangeMin = UserCommonAdjustGetVPositionRange(_GET_VPOSITIONRANGE_MIN, enumDisplayRegion);

    usTargetIVStart = UserCommonAdjustPercentToRealValue(ucUserVPosition, usVPositionRangeMax, usVPositionRangeMin, (((usVPositionRangeMax - usVPositionRangeMin) / 2) + usVPositionRangeMin));

#if(_VGA_SUPPORT == _ON)
    if(SysRegionGetSourceType(enumDisplayRegion) == _SOURCE_VGA)
    {
        SysVgaWatchDog(_DISABLE);

        shVDelay = (SWORD)usTargetIVStart - (SWORD)ScalerVgaTopGetCaptureVStartPosition();

        shVDelay = (shVDelay < 0) ? 0 : shVDelay;

        // Get current V adjust limit
        usVDelayAdjustDeltaLimit = ScalerMDomainGetVerticalAdjustLimit(_SOURCE_VGA);

        ucTimeoutCounter = (abs(shVDelay - ScalerVgaTopGetCaptureVDelay()) / usVDelayAdjustDeltaLimit) + 1;

        do
        {
            if(shVDelay > ScalerVgaTopGetCaptureVDelay())
            {
                ScalerVgaTopSetCaptureVDelay(shVDelay);
            }
            else
            {
                if((ScalerVgaTopGetCaptureVDelay() - shVDelay) <= usVDelayAdjustDeltaLimit)
                {
                    ScalerVgaTopSetCaptureVDelay(shVDelay);
                }
                else
                {
                    ScalerVgaTopSetCaptureVDelay(ScalerVgaTopGetCaptureVDelay() - usVDelayAdjustDeltaLimit);
                }
            }

            ScalerVgaTopDoubleBufferApply();

            ucTimeoutCounter--;
        }
        while((shVDelay != ScalerVgaTopGetCaptureVDelay()) && (ucTimeoutCounter > 0));

        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, ScalerRegionGetInputDataPath(enumDisplayRegion));
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, ScalerRegionGetInputDataPath(enumDisplayRegion));

        SysVgaWatchDog(_ENABLE);
    }
    else
#endif
    {
        if(ScalerVgipGetDigitalCaptureStatus() == _FALSE)
        {
            ScalerGlobalWatchDog(enumDisplayRegion, _DISABLE);

            shVDelay = (SWORD)usTargetIVStart - (SWORD)ScalerVgipGetCaptureVStartPosition();

            shVDelay = (shVDelay < 0) ? 0 : shVDelay;

            // Get current V adjust limit
            usVDelayAdjustDeltaLimit = ScalerMDomainGetVerticalAdjustLimit(SysRegionGetSourceType(enumDisplayRegion));

            ucTimeoutCounter = (abs(shVDelay - ScalerVgipGetCaptureVDelay()) / usVDelayAdjustDeltaLimit) + 1;

            do
            {
                if(shVDelay > ScalerVgipGetCaptureVDelay())
                {
                    ScalerVgipSetCaptureVDelay(shVDelay);
                }
                else
                {
                    if((ScalerVgipGetCaptureVDelay() - shVDelay) <= usVDelayAdjustDeltaLimit)
                    {
                        ScalerVgipSetCaptureVDelay(shVDelay);
                    }
                    else
                    {
                        ScalerVgipSetCaptureVDelay(ScalerVgipGetCaptureVDelay() - usVDelayAdjustDeltaLimit);
                    }
                }

                ScalerGlobalIDomainDBApply(GET_VGIP_INPUT_PATH(), _DB_APPLY_POLLING);

                ucTimeoutCounter--;
            }
            while((shVDelay != ScalerVgipGetCaptureVDelay()) && (ucTimeoutCounter > 0));

            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, ScalerRegionGetInputDataPath(enumDisplayRegion));

            ScalerGlobalWatchDog(enumDisplayRegion, _ENABLE);
        }
    }
}

//--------------------------------------------------
// Description  :  Calculate value to percent for input range for 2 Sectors
// Input Value  :  usRealValue --> input real value
//                 usMax       --> the max value
//                 usMin       --> the min value
//                 usCenter    --> the Center Value
// Output Value :  Percent
//--------------------------------------------------
BYTE UserCommonAdjustRealValueToPercent(WORD usRealValue, WORD usMax, WORD usMin, WORD usCenter)
{
    WORD usTemp = 0;
    usRealValue = MINOF(usRealValue, usMax);
    usRealValue = MAXOF(usRealValue, usMin);

    if((usMax <= usMin) || (usCenter <= usMin) || (usCenter >= usMax))
    {
        usTemp = 0;
    }
    else
    {
        if(usRealValue < usCenter)
        {
            usTemp = (((DWORD)(usRealValue - usMin) * 10000) / (usCenter - usMin)) / 2;
        }
        else if(usRealValue > usCenter)
        {
            usTemp = (((DWORD)(usRealValue - usCenter) * 10000) / (usMax - usCenter)) / 2 + 5000;
        }
        else
        {
            return 50;
        }
    }

    if((usTemp % 100) > 49)
    {
        usTemp = usTemp + 100;
    }

    usTemp = usTemp / 100;

    return ((BYTE)usTemp);
}

//--------------------------------------------------
// Description  :  Calculate percent to real value for input range for 2 Sectors
// Input Value  :  ucPercentValue --> input percent value
//                 usMax          --> the max value
//                 usMin          --> the min value
//                 usCenter       --> the Center Value
// Output Value :  Real value
//--------------------------------------------------
WORD UserCommonAdjustPercentToRealValue(BYTE ucPercentValue, WORD usMax, WORD usMin, WORD usCenter)
{
    DWORD ulTemp = 0;

    ucPercentValue = MINOF(100, ucPercentValue);

    if(ucPercentValue > 50)
    {
        ulTemp = (((DWORD)(ucPercentValue - 50) * (usMax - usCenter) * 10) / 50);
    }
    else if(ucPercentValue < 50)
    {
        ulTemp = (((DWORD)ucPercentValue * (usCenter - usMin) * 10) / 50);
    }
    else
    {
        return usCenter;
    }

    if((ulTemp % 10) > 5)
    {
        ulTemp = ulTemp + 10;
    }

    if(ucPercentValue > 50)
    {
        return (WORD)((ulTemp / 10) + usCenter);
    }
    else
    {
        return (WORD)((ulTemp / 10) + usMin); // <= 50
    }
}

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Overscan
// Input Value  : Current Input Timing
// Output Value : Modified Input Timing
//--------------------------------------------------
void UserCommonAdjustOverScan(EnumDisplayRegion enumDisplayRegion)
{
    BYTE ucDelta = 0;

    if(UserInterfaceGetOverScanStatus(enumDisplayRegion) == _FALSE)
    {
        return;
    }

    // Modify Over Scanned H
    ucDelta = (BYTE)((DWORD)GET_MDOMAIN_INPUT_HWIDTH() * _OVERSCAN_H_RATIO / 1000);

    // Let Adjusted Value be 2's multiple
    ucDelta += ucDelta % 2;

    SET_MDOMAIN_INPUT_HSTART(GET_MDOMAIN_INPUT_HSTART() + ucDelta);
    SET_MDOMAIN_INPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH() - 2 * ucDelta);

    // Modify Over Scanned V
    ucDelta = (BYTE)((DWORD)GET_MDOMAIN_INPUT_VHEIGHT() * _OVERSCAN_V_RATIO / 1000);

    if(ScalerFmtCnvFtoPGetStatus(ScalerRegionGetInputDataPath(enumDisplayRegion)) == _TRUE)
    {
        // Let Adjusted Value be 2's multiple under E/O mode
        ucDelta += ucDelta % 2;
    }

    SET_MDOMAIN_INPUT_VSTART(GET_MDOMAIN_INPUT_VSTART() + ucDelta);
    SET_MDOMAIN_INPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT() - 2 * ucDelta);
}
#endif  // End of #if(_OVERSCAN_SUPPORT == _ON)

#if(_ASPECT_RATIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Display Timing For Aspect Ratio
// Input Value  : Current Display Timing and Input H/V
// Output Value : Modified Display Timing
//--------------------------------------------------
void UserCommonAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion)
{
    WORD usHRatio = 0x0000;
    WORD usVRatio = 0x0000;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    // No aspect ratio allowed in rotation 90/270
    if((ScalerRotationCheckStatus() == _TRUE) &&
       ((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270)))
    {
        return;
    }
#endif

    switch(UserInterfaceGetAspectRatioType(enumDisplayRegion))
    {
        case _ASPECT_RATIO_FULL:
        default:

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
            ScalerMDomainAspectOriginMode(_FALSE);
#endif
            break;

        case _ASPECT_RATIO_FIXED:

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
            ScalerMDomainAspectOriginMode(_FALSE);
#endif

            UserInterfaceGetAspectRatio(enumDisplayRegion, &usHRatio, &usVRatio);

            // Calculate H Width
            PDATA_WORD(0) = (DWORD)GET_MDOMAIN_OUTPUT_VHEIGHT() * usHRatio / usVRatio;

            // H Width Should be 4x
            PDATA_WORD(0) &= 0xFFFC;

            if(PDATA_WORD(0) > GET_MDOMAIN_OUTPUT_HWIDTH())
            {
                // Calculate V Height
                PDATA_WORD(0) = (DWORD)GET_MDOMAIN_OUTPUT_HWIDTH() * usVRatio / usHRatio;

                // V Height Should be 4x
                PDATA_WORD(0) &= 0xFFFC;

                // Set V Start, V Height
                SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + ((GET_MDOMAIN_OUTPUT_VHEIGHT() - PDATA_WORD(0)) / 2));
                SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(0));
            }
            else if(PDATA_WORD(0) < GET_MDOMAIN_OUTPUT_HWIDTH())
            {
                // Calculate H Start
                PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_HSTART() + ((GET_MDOMAIN_OUTPUT_HWIDTH() - PDATA_WORD(0)) / 2);

                // Set H Start, H Width
                SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(1));
                SET_MDOMAIN_OUTPUT_HWIDTH(PDATA_WORD(0));
            }

            break;

        case _ASPECT_RATIO_USER:

            // User defined adjust aspect ratio
            UserInterfaceAdjustAspectRatio(enumDisplayRegion);
            break;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
        case _ASPECT_RATIO_ORIGIN:

            ScalerMDomainAspectOriginMode(_TRUE);

            // Consider Panel Height and Input Height
            if(GET_MDOMAIN_OUTPUT_VHEIGHT() > GET_MDOMAIN_INPUT_VHEIGHT())
            {
                // Double V height for interlaced timing
                if((GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE) &&
                   (GET_MDOMAIN_INPUT_HWIDTH() > (GET_MDOMAIN_INPUT_VHEIGHT() << 1)))
                {
                    // Check if output V height > (input V height x 2)
                    if(GET_MDOMAIN_OUTPUT_VHEIGHT() > (GET_MDOMAIN_INPUT_VHEIGHT() << 1))
                    {
                        PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_VHEIGHT() - (GET_MDOMAIN_INPUT_VHEIGHT() << 1);
                        SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT() << 1);
                    }
                    else
                    {
                        // Output V height unchanged
                        PDATA_WORD(0) = 0x00;
                    }
                }
                else
                {
                    PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_VHEIGHT() - GET_MDOMAIN_INPUT_VHEIGHT();
                    SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_INPUT_VHEIGHT());
                }

                PDATA_WORD(0) &= 0xFFFC; // V start should be even
                SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + (PDATA_WORD(0) / 2));
            }
            else
            {
                usHRatio = 0x01;
            }

            // Consider Panel Width and Input Width
            if(GET_MDOMAIN_OUTPUT_HWIDTH() > GET_MDOMAIN_INPUT_HWIDTH())
            {
                PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_HWIDTH() - GET_MDOMAIN_INPUT_HWIDTH();
                PDATA_WORD(0) &= 0xFFFC; // H start should be even
                SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + (PDATA_WORD(0) / 2));
                SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_INPUT_HWIDTH());
            }
            else
            {
                usVRatio = 0x01;
            }

            if((usHRatio != 1) || (usVRatio != 1))
            {
                PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_VSTART() - ((DWORD)GET_MDOMAIN_OUTPUT_VSTART() * UserInterfaceGetAspectRatioOriginalRatio(enumDisplayRegion) / 0xFF);
                PDATA_WORD(1) &= 0xFFFE; // V start should be even

                SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() - PDATA_WORD(1));
                SET_MDOMAIN_OUTPUT_VHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT() + PDATA_WORD(1) * 2);

                PDATA_WORD(1) = GET_MDOMAIN_OUTPUT_HSTART() - ((DWORD)GET_MDOMAIN_OUTPUT_HSTART() * UserInterfaceGetAspectRatioOriginalRatio(enumDisplayRegion) / 0xFF);
                PDATA_WORD(1) &= 0xFFFE; // H start should be even

                SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() - PDATA_WORD(1));
                SET_MDOMAIN_OUTPUT_HWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH() + PDATA_WORD(1) * 2);
            }

            break;
#endif // End of #if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    }
}
#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust input size for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustRotationInputSize(void)
{
    if((ScalerRotationCheckStatus() == _FALSE) ||
       ((GET_ROT_TYPE() != _ROT_CW90) && (GET_ROT_TYPE() != _ROT_CW270)))
    {
        return;
    }

    switch(GET_ROT_DISP_SIZE())
    {
        case _ROT_PIXEL_BY_PIXEL:
            // Calculate / Set V
            if(_PANEL_DH_WIDTH < GET_INPUT_TIMING_VHEIGHT())
            {
                PDATA_WORD(0) = ((GET_INPUT_TIMING_VHEIGHT() - _PANEL_DH_WIDTH) / 2);
                PDATA_WORD(0) += GET_INPUT_TIMING_VSTART();

                // VStart / VHeight
                SET_MDOMAIN_INPUT_VSTART(PDATA_WORD(0));
                SET_MDOMAIN_INPUT_VHEIGHT(_PANEL_DH_WIDTH);
            }

            // Calculate / Set H
            if(_PANEL_DV_HEIGHT < GET_INPUT_TIMING_HWIDTH())
            {
                PDATA_WORD(0) = (GET_INPUT_TIMING_HWIDTH() - _PANEL_DV_HEIGHT);
                PDATA_WORD(0) += GET_INPUT_TIMING_HSTART();
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);

                // HStart / HWidth
                SET_MDOMAIN_INPUT_HSTART(PDATA_WORD(0));
                SET_MDOMAIN_INPUT_HWIDTH(_PANEL_DV_HEIGHT);
            }
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust display size for rotation
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustRotationDisplaySize(void)
{
    if((ScalerRotationCheckStatus() == _FALSE) ||
       ((GET_ROT_TYPE() != _ROT_CW90) && (GET_ROT_TYPE() != _ROT_CW270)))
    {
        return;
    }

    switch(GET_ROT_DISP_SIZE())
    {
        default:
        case _ROT_FULL:

            // Set Size
            SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
            SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
            SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);

            break;

        case _ROT_PIXEL_BY_PIXEL:

            PDATA_WORD(0) = _PANEL_DH_START;
            PDATA_WORD(1) = _PANEL_DH_WIDTH;
            PDATA_WORD(2) = _PANEL_DV_START;
            PDATA_WORD(3) = _PANEL_DV_HEIGHT;

            // Calculate / Set Display Window H
            if(_PANEL_DH_WIDTH > GET_MDOMAIN_INPUT_VHEIGHT())
            {
                // Underscan
                PDATA_WORD(0) += ((_PANEL_DH_WIDTH - GET_MDOMAIN_INPUT_VHEIGHT()) / 2);
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                PDATA_WORD(1) = GET_MDOMAIN_INPUT_VHEIGHT();
            }

            // Calculate / Set Display Window V Start
            if(_PANEL_DV_HEIGHT > GET_MDOMAIN_INPUT_HWIDTH())
            {
                // Underscan
                PDATA_WORD(2) += ((_PANEL_DV_HEIGHT - GET_MDOMAIN_INPUT_HWIDTH()) / 2);
                PDATA_WORD(3) = GET_MDOMAIN_INPUT_HWIDTH();
            }

            // Set Display Window H Start/Width
            SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(0));
            SET_MDOMAIN_OUTPUT_HWIDTH(PDATA_WORD(1));

            // Set Display Window V Start/Height
            SET_MDOMAIN_OUTPUT_VSTART(PDATA_WORD(2));
            SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(3));

            break;

        case _ROT_KEEP_SRC_ASPECT_RATIO:

            if((GET_MDOMAIN_INPUT_INTERLACE_FLG() == _TRUE) &&
               (GET_MDOMAIN_INPUT_VHEIGHT() < (GET_MDOMAIN_INPUT_HWIDTH() / 2)))
            {
                PDATA_WORD(1) = GET_MDOMAIN_INPUT_VHEIGHT() * 2;
            }
            else
            {
                PDATA_WORD(1) = GET_MDOMAIN_INPUT_VHEIGHT();
            }

            // Calculate VHeight
            PDATA_WORD(0) = ((DWORD)_PANEL_DH_WIDTH * GET_MDOMAIN_INPUT_HWIDTH()) / PDATA_WORD(1);

            if(PDATA_WORD(0) > _PANEL_DV_HEIGHT)
            {
                // Calculate HWidth
                PDATA_WORD(0) = ((DWORD)_PANEL_DV_HEIGHT * PDATA_WORD(1)) / GET_MDOMAIN_INPUT_HWIDTH();

                // Set HWidth / VHeight
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                SET_MDOMAIN_OUTPUT_HWIDTH(PDATA_WORD(0));
                SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT);

                // HStart / VStart
                PDATA_WORD(0) = (_PANEL_DH_START + (_PANEL_DH_WIDTH - PDATA_WORD(0)) / 2);
                PDATA_WORD(0) += (PDATA_WORD(0) % 2);
                SET_MDOMAIN_OUTPUT_HSTART(PDATA_WORD(0));
                SET_MDOMAIN_OUTPUT_VSTART(_PANEL_DV_START);
            }
            else
            {
                // HWidth / VHeight
                SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH);
                SET_MDOMAIN_OUTPUT_VHEIGHT(PDATA_WORD(0));

                // HStart / VStart
                SET_MDOMAIN_OUTPUT_HSTART(_PANEL_DH_START);
                SET_MDOMAIN_OUTPUT_VSTART((_PANEL_DV_START + (_PANEL_DV_HEIGHT - PDATA_WORD(0)) / 2));
            }

            break;
    }
}
#endif  // #if(_DISPLAY_ROTATION_SUPPORT == _ON)

#if(_PIP_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust PIP sub position & size
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustPipSubTimingFormat(void)
{
    StructTimingFormat stTimingFormat;
    stTimingFormat = UserInterfaceGetPipSubTimingFormat();

    SET_MDOMAIN_OUTPUT_HTOTAL(_PANEL_DH_TOTAL);
    SET_MDOMAIN_OUTPUT_VTOTAL(_PANEL_DV_TOTAL);

    SET_MDOMAIN_OUTPUT_HWIDTH(stTimingFormat.usHWidth);
    SET_MDOMAIN_OUTPUT_VHEIGHT(stTimingFormat.usVHeight);
    SET_MDOMAIN_OUTPUT_HBWIDTH(stTimingFormat.usHWidth);
    SET_MDOMAIN_OUTPUT_VBHEIGHT(stTimingFormat.usVHeight);

    SET_MDOMAIN_OUTPUT_HSTART(stTimingFormat.usHStart);
    SET_MDOMAIN_OUTPUT_VSTART(stTimingFormat.usVStart);
    SET_MDOMAIN_OUTPUT_HBSTART(stTimingFormat.usHStart);
    SET_MDOMAIN_OUTPUT_VBSTART(stTimingFormat.usVStart);

    ScalerMDomainCheckDisplayFormat(_DISPLAY_RGN_SUB);

    if((SysRegionGetDisplayState(_DISPLAY_RGN_SUB) == _DISPLAY_STATE_ACTIVE) ||
       (SysRegionGetDisplayState(_DISPLAY_RGN_SUB) == _DISPLAY_STATE_DISPLAY_READY))
    {
#if(_PIP_BLENDING_SUPPORT == _ON)

#if(_ASPECT_RATIO_SUPPORT == _ON)
        // Calculate PIP sub active size
        UserCommonAdjustAspectRatio(_DISPLAY_RGN_SUB);
#endif

        ScalerMDomainCheckDisplayFormat(_DISPLAY_RGN_SUB);

        // Update active size
        ScalerMDomainSetSubActiveRegion();

        // Set D-domain background size to active size
        SET_MDOMAIN_OUTPUT_HBWIDTH(GET_MDOMAIN_OUTPUT_HWIDTH());
        SET_MDOMAIN_OUTPUT_HBSTART(GET_MDOMAIN_OUTPUT_HSTART());
        SET_MDOMAIN_OUTPUT_VBHEIGHT(GET_MDOMAIN_OUTPUT_VHEIGHT());
        SET_MDOMAIN_OUTPUT_VBSTART(GET_MDOMAIN_OUTPUT_VSTART());
#endif

        // Update M-domain back ground timing format
        ScalerMDomainSetSubBackground();

#if(_BORDER_WINDOW_SUPPORT == _ON)
        // Update border position
        UserInterfaceAdjustBorderWindow(_DB_APPLY_NONE);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
        // Update HLW position
        UserInterfaceAdjustHighlightWindow(_DB_APPLY_NONE);
#endif

        // Reset to display setting
        SysModeSetDisplayTarget(_DISPLAY_RGN_SUB);
        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
    }
    else
    {
        // Update M-domain timing format
        ScalerMDomainSetSubActiveRegion();
        ScalerMDomainSetSubBackground();

#if(_BORDER_WINDOW_SUPPORT == _ON)
        // Update border position
        UserInterfaceAdjustBorderWindow(_DB_APPLY_NONE);
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
        // Update HLW position
        UserInterfaceAdjustHighlightWindow(_DB_APPLY_NONE);
#endif

        // Apply D-domain DB
        ScalerGlobalDDomainDBApply(_DB_APPLY_NO_POLLING);
    }
}
#endif


#if(_I_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set IDither Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustIDither(void)
{
    ScalerColorIDitherAdjust(_IDITHER_12_TO_8, tIDITHER_TABLE_FIFO8, tIDITHER_SEQ_TABLE, tIDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
    ScalerColorIDitherAdjust(_IDITHER_12_TO_10, tIDITHER_TABLE_FIFO10, tIDITHER_SEQ_TABLE, tIDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
}
#endif // End of #if(_I_DITHER_SUPPORT == _ON)

#if(_UNIFORMITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load gain, offset and decay LUT, turn on/off offset function
// Input Value  : EnumUniformityType, EnumUniformityModeSelect
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustPanelUniformity(EnumUniformityTypeSelect enumUniformityType, EnumUniformityModeSelect enumUniformityMode)
{
#if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)
    if(tUNIFORMITY_OSD_TYPE_OFFSET_ENABLE_INDEX[enumUniformityType] == _ON)
    {
        ScalerColorPanelUniformityOffsetAdjust(g_pucDISP_CALIBRATION_FLASH + tUNIFORMITY_OSD_TYPE_OFFSET_ADDRESS_INDEX[enumUniformityType], _PANEL_UNIFORMITY_OFFSET_LUT_SIZE, tUNIFORMITY_OSD_TYPE_OFFSET_BANK_INDEX[enumUniformityType]);
        ScalerColorPanelUniformityDecayAdjust(g_pucDISP_CALIBRATION_FLASH + tUNIFORMITY_OSD_TYPE_DECAY_ADDRESS_INDEX[enumUniformityType], _PANEL_UNIFORMITY_DECAY_LUT_SIZE, tUNIFORMITY_OSD_TYPE_DECAY_BANK_INDEX[enumUniformityType], enumUniformityMode, _PANEL_UNIFORMITY_MULTI_LUT_MODE);
        ScalerColorPanelUniformityOffsetEnable(_FUNCTION_ON);
    }
    else
    {
        ScalerColorPanelUniformityOffsetEnable(_FUNCTION_OFF);
    }
#endif // End of #if(_UNIFORMITY_LEVEL0_SUPPORT == _ON)

    ScalerColorPanelUniformityAdjust(g_pucDISP_CALIBRATION_FLASH + tUNIFORMITY_OSD_TYPE_ADDRESS_INDEX[enumUniformityType], _PANEL_UNIFORMITY_LUT_SIZE, tUNIFORMITY_OSD_TYPE_BANK_INDEX[enumUniformityType], enumUniformityMode);
}
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

#if(_ULTRA_VIVID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustUltraVivid(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
    {
        UserInterfaceAdjustUltraVivid(enumSelRegion, _DB_APPLY_NONE);
        SysModeColorSpaceConvert(_DISPLAY_RGN_1P, SysRegionGetPortType(_DISPLAY_RGN_1P), UserInterfaceGetColorFormat(_DISPLAY_RGN_1P), enumDBApply);
    }
    else
    {
        UserInterfaceAdjustUltraVivid(enumSelRegion, enumDBApply);
    }
}
#endif  // End of #if(_ULTRA_VIVID_SUPPORT == _ON)

#if(_D_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DDither Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustDDither(void)
{
#if(_PANEL_EXIST_MULTIPANEL == _OFF)
    ScalerColorDDitherAdjust(tDDITHER_TABLE, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
#else
    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_18_BIT:
#if(_DDITHER_TYPE != _DDITHER_GEN_1_6BIT_DITHERTBL)
            ScalerColorDDitherAdjust(tDDITHER_TABLE18Bit, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
#else
            ScalerColorDDitherAdjust(_NULL_POINTER, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
#endif
            break;

        case _PANEL_DISP_24_BIT:
            ScalerColorDDitherAdjust(tDDITHER_TABLE24Bit, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
            break;

        case _PANEL_DISP_30_BIT:
        default:
            ScalerColorDDitherAdjust(tDDITHER_TABLE30Bit, tDDITHER_SEQ_TABLE, tDDITHER_TEMPOFFSET_TABLE, GET_CURRENT_BANK_NUMBER());
            break;
    }
#endif

#if(_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE)
#if(_PANEL_EXIST_MULTIPANEL == _OFF)
    ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE, tDDITHER_ADVANCE_SETTING_TABLE, GET_CURRENT_BANK_NUMBER());
#else
    switch(_PANEL_DISP_BIT_MODE)
    {
        case _PANEL_DISP_24_BIT:
            ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE24Bit, tDDITHER_ADVANCE_SETTING_TABLE24Bit, GET_CURRENT_BANK_NUMBER());
            break;

        case _PANEL_DISP_30_BIT:
        default:
            ScalerColorDDitherAdvanceSettingAdjust(tDDITHER_REALIGN_TABLE, tDDITHER_REALIGN_TEMPO_TABLE, tDDITHER_LSB_TABLE30Bit, tDDITHER_ADVANCE_SETTING_TABLE30Bit, GET_CURRENT_BANK_NUMBER());
            break;
    }
#endif
#endif
}
#endif // End of #if(_D_DITHER_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Color data
// Input Value  : None
// Output Value : compensate value
//--------------------------------------------------
WORD UserCommonAdjust10bitPanelCompensate(WORD usData)
{
    usData = (WORD)(((DWORD)usData * 1023 / 1020) > 4095) ? 4095 : (WORD)((DWORD)usData * 1023 / 1020);

    return usData;
}

#if(_ULTRA_HDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Check HDR change status according to EOTF, (primaries color), max mastering luminance
// Input Value  : EnumDisplayRegion
// Output Value : HDR chagne status
//--------------------------------------------------
EnumHDRChangeStatus UserCommonAdjustHDRChangeStatus(EnumDisplayRegion enumDisplayRegion)
{
    if(enumDisplayRegion == _DISPLAY_RGN_1P)
    {
        StructHDRStaticMetaData stHDRInfoData;
        memset(&stHDRInfoData, 0, sizeof(stHDRInfoData));

        // Get current HDR status
        ScalerSyncHDRGetCurrentStatus(&stHDRInfoData, SysRegionGetPortType(enumDisplayRegion));

        // Check if info changed
        if(stHDRInfoData.usMaxDisplayMasteringLv != GET_HDR_MAX_DISPLAY_MASTERING_LV(enumDisplayRegion))
        {
            SET_HDR_INFO_DATA(enumDisplayRegion, stHDRInfoData);
            return _HDR_INFO_MAX_LV_CHANGE;
        }
        else if(stHDRInfoData.ucEOTF != GET_HDR_EOTF(enumDisplayRegion))
        {
            SET_HDR_INFO_DATA(enumDisplayRegion, stHDRInfoData);
            return _HDR_INFO_EOTF_CHANGE;
        }
    }

    return _HDR_INFO_NO_CHANGE;
}

//--------------------------------------------------
// Description  : Check HDR target status to set HDR 2084, SDR or do nothing
// Input Value  : EnumDisplayRegion
// Output Value : HDR target status
//--------------------------------------------------
EnumHDRTargetStatus UserCommonAdjustHDRTargetStatus(EnumDisplayRegion enumDisplayRegion)
{
    if(enumDisplayRegion == _DISPLAY_RGN_1P)
    {
        // Check if DCC data ready
        if(ScalerColorDCCGetDataReadyStatus() == _TRUE)
        {
            // Clear DCC data ready status.
            ScalerColorDCCClrDataReadyStatus();

            if(UserCommonAdjustHDRChangeStatus(enumDisplayRegion) != _HDR_INFO_NO_CHANGE)
            {
                DebugMessageHDR("HDRCheckStatus EOTF", GET_HDR_EOTF(enumDisplayRegion));

                DebugMessageHDR("HDRCheckStatus X0", GET_HDR_DISPALY_PRIMARIES_X0(enumDisplayRegion));
                DebugMessageHDR("HDRCheckStatus Y0", GET_HDR_DISPALY_PRIMARIES_Y0(enumDisplayRegion));

                DebugMessageHDR("HDRCheckStatus X1", GET_HDR_DISPALY_PRIMARIES_X1(enumDisplayRegion));
                DebugMessageHDR("HDRCheckStatus Y1", GET_HDR_DISPALY_PRIMARIES_Y1(enumDisplayRegion));

                DebugMessageHDR("HDRCheckStatus X2", GET_HDR_DISPALY_PRIMARIES_X2(enumDisplayRegion));
                DebugMessageHDR("HDRCheckStatus Y2", GET_HDR_DISPALY_PRIMARIES_Y2(enumDisplayRegion));

                DebugMessageHDR("HDRCheckStatus Wx", GET_HDR_WHITE_POINT_X(enumDisplayRegion));
                DebugMessageHDR("HDRCheckStatus Wy", GET_HDR_WHITE_POINT_Y(enumDisplayRegion));

                DebugMessageHDR("HDRCheckStatus Mastering Lv", GET_HDR_MAX_DISPLAY_MASTERING_LV(enumDisplayRegion));

                if(GET_HDR_EOTF(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084) // HDR SMPTE ST 2084
                {
                    DebugMessageHDR("HDR Target Status HDR2084", 0x00);
                    return _HDR_TARGET_STATUS_SMPTE_ST_2084;
                }
                else // SDR Traditional gamma
                {
                    DebugMessageHDR("HDR Target Status SDR", 0x00);
                    return _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR;
                }
            }
        }
    }

    return _HDR_TARGET_STATUS_DO_NOTHING;
}

//--------------------------------------------------
// Description  : Initial HDR metadata and setting HDR or PCM
// Input Value  : EnumDisplayRegion
// Output Value : HDR target status
//--------------------------------------------------
EnumHDRTargetStatus UserCommonAdjustHDRAutoModeInitial(EnumDisplayRegion enumDisplayRegion)
{
    if(enumDisplayRegion == _DISPLAY_RGN_1P)
    {
        StructHDRStaticMetaData stHDRInfoData;
        memset(&stHDRInfoData, 0, sizeof(stHDRInfoData));

        // Get current HDR status
        ScalerSyncHDRGetCurrentStatus(&stHDRInfoData, SysRegionGetPortType(enumDisplayRegion));

        SET_HDR_INFO_DATA(enumDisplayRegion, stHDRInfoData);

        if(GET_HDR_EOTF(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084) // HDR SMPTE ST 2084
        {
            DebugMessageHDR("HDR Target Status HDR2084", 0x00);
            return _HDR_TARGET_STATUS_SMPTE_ST_2084;
        }
        else // SDR Traditional gamma
        {
            DebugMessageHDR("HDR Target Status SDR", 0x00);
            return _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR;
        }
    }

    return _HDR_TARGET_STATUS_DO_NOTHING;
}

//--------------------------------------------------
// Description  : Return HDR Max Mastering Lv Type by infoframe mastering Lv
// Input Value  : EnumDisplayRegion
// Output Value : HDR max mastering Lv type
//--------------------------------------------------
EnumHDRMaxMasteringLvType UserCommonAdjustHDRGetLvType(EnumDisplayRegion enumDisplayRegion)
{
    if(enumDisplayRegion == _DISPLAY_RGN_1P)
    {
        if(GET_HDR_MAX_DISPLAY_MASTERING_LV(enumDisplayRegion) > _HDR_MAX_MASTERING_LV_4000)
        {
            return _HDR_MAX_MASTERING_LV_TYPE2;
        }
        else if(GET_HDR_MAX_DISPLAY_MASTERING_LV(enumDisplayRegion) > _HDR_MAX_MASTERING_LV_1200)
        {
            return _HDR_MAX_MASTERING_LV_TYPE1;
        }
        else
        {
            return _HDR_MAX_MASTERING_LV_TYPE0;
        }
    }

    return _HDR_MAX_MASTERING_LV_TYPE0;
}

//--------------------------------------------------
// Description  : Adjust HDR by SelRegion, DarkEnhanceEnable
// Input Value  : EnumDisplayRegion, DarkEnhanceEnable
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustHDRAutoMode(EnumDisplayRegion enumDisplayRegion, bit bDarkEnhanceEnable)
{
    WORD usHDRInputGammaFlashAddress = 0x0000;
    WORD usHDRColorMatrixFlashAddress = 0x0000;

    if(enumDisplayRegion == _DISPLAY_RGN_1P)
    {
        // Input Gamma Setting
        switch(UserCommonAdjustHDRGetLvType(enumDisplayRegion))
        {
            case _HDR_MAX_MASTERING_LV_TYPE0:
                usHDRInputGammaFlashAddress = _OGC_HDR_IG_1200_NOR_ADDRESS;
                DebugMessageHDR("HDR apply type0 parameter", 0x00);
                break;

            case _HDR_MAX_MASTERING_LV_TYPE1:
                usHDRInputGammaFlashAddress = _OGC_HDR_IG_4000_NOR_ADDRESS;
                DebugMessageHDR("HDR apply type1 parameter", 0x00);
                break;

            case _HDR_MAX_MASTERING_LV_TYPE2:
                usHDRInputGammaFlashAddress = _OGC_HDR_IG_10000_NOR_ADDRESS;
                DebugMessageHDR("HDR apply type2 parameter", 0x00);
                break;

            default:
                usHDRInputGammaFlashAddress = _OGC_HDR_IG_1200_NOR_ADDRESS;
                DebugMessageHDR("HDR apply type0 parameter default", 0x00);
                break;
        }

        if(bDarkEnhanceEnable == _ON)
        {
            usHDRInputGammaFlashAddress += _OGC_HDR_IG_TABLE_SIZE;
            DebugMessageHDR("HDR apply Dark Enhance parameter", 0x00);
        }

        // Color Matrix Setting
        switch(ScalerColorGetColorimetry(SysRegionGetPortType(enumDisplayRegion)))
        {
            case _COLORIMETRY_RGB_SRGB:
            case _COLORIMETRY_RGB_XRRGB:
            case _COLORIMETRY_RGB_SCRGB:
            case _COLORIMETRY_YCC_SMPTE_170M:
            case _COLORIMETRY_YCC_ITUR_BT601:
            case _COLORIMETRY_YCC_ITUR_BT709:
            case _COLORIMETRY_YCC_XVYCC601:
            case _COLORIMETRY_YCC_XVYCC709:
                usHDRColorMatrixFlashAddress = _OCC_HDR_SRGB_MATRIX_ADDRESS;
                DebugMessageHDR("HDR apply SRGB matrix", 0x00);
                break;

            case _COLORIMETRY_RGB_ADOBERGB:
                usHDRColorMatrixFlashAddress = _OCC_HDR_ADOBE_MATRIX_ADDRESS;
                DebugMessageHDR("HDR apply AdobeRGB matrix", 0x00);
                break;

            case _COLORIMETRY_RGB_DCI_P3:
                usHDRColorMatrixFlashAddress = _OCC_HDR_DCIP3_D65_MATRIX_ADDRESS;
                DebugMessageHDR("HDR apply DCIP3_D65 matrix", 0x00);
                break;

            case _COLORIMETRY_EXT:
                switch(ScalerColorGetExtColorimetry(SysRegionGetPortType(enumDisplayRegion)))
                {
                    case _COLORIMETRY_EXT_RGB_SRGB:
                    case _COLORIMETRY_EXT_RGB_XRRGB:
                    case _COLORIMETRY_EXT_RGB_SCRGB:
                    case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                    case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                    case _COLORIMETRY_EXT_YCC_XVYCC601:
                    case _COLORIMETRY_EXT_YCC_XVYCC709:
                    case _COLORIMETRY_EXT_YCC_SYCC601:
                        usHDRColorMatrixFlashAddress = _OCC_HDR_SRGB_MATRIX_ADDRESS;
                        DebugMessageHDR("HDR apply SRGB matrix EXT", 0x00);
                        break;

                    case _COLORIMETRY_EXT_RGB_ADOBERGB:
                    case _COLORIMETRY_EXT_YCC_ADOBEYCC601:
                        usHDRColorMatrixFlashAddress = _OCC_HDR_ADOBE_MATRIX_ADDRESS;
                        DebugMessageHDR("HDR apply AdobeRGB matrix EXT", 0x00);
                        break;

                    case _COLORIMETRY_EXT_RGB_DCI_P3:
                        usHDRColorMatrixFlashAddress = _OCC_HDR_DCIP3_D65_MATRIX_ADDRESS;
                        DebugMessageHDR("HDR apply DCIP3_D65 matrix EXT", 0x00);
                        break;

#if(_COLOR_CONVERSION_TYPE == _COLOR_CONVERSION_GEN_2)
                    case _COLORIMETRY_EXT_RGB_ITUR_BT2020:
                    case _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL:
                    case _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL:
                        usHDRColorMatrixFlashAddress = _OCC_HDR_BT2020_MATRIX_ADDRESS;
                        DebugMessageHDR("HDR apply BT2020 matrix", 0x00);
                        break;
#endif

                    default:
                        usHDRColorMatrixFlashAddress = _OCC_HDR_BT2020_MATRIX_ADDRESS;
                        DebugMessageHDR("HDR apply BT2020 matrix EXT default", 0x00);
                        break;
                }
                break;

            default:
                usHDRColorMatrixFlashAddress = _OCC_HDR_BT2020_MATRIX_ADDRESS;
                DebugMessageHDR("HDR apply BT2020 matrix default", 0x00);
                break;
        }

#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
        ScalerColorBRICTSRegionEnable((EnumSelRegion)enumDisplayRegion, _DB_APPLY_NONE, _OFF);
#endif

#if(_RGB_3D_GAMMA == _ON)
        ScalerColor3DGammaRegionEnable((EnumSelRegion)enumDisplayRegion, _DB_APPLY_NONE, _OFF);
#endif

        ScalerColorPCMAdjust((EnumSelRegion)enumDisplayRegion, _PCM_HDR_2084,
                             (g_pucDISP_CALIBRATION_FLASH + usHDRInputGammaFlashAddress),
                             (g_pucDISP_CALIBRATION_FLASH + _OCC_HDR_GAMMA10_ADDRESS),
                             (g_pucDISP_CALIBRATION_FLASH + usHDRColorMatrixFlashAddress),
                             _OGC_FLASH_BANK, _OCC_COLORMATRIX_TABLE_SIZE, _NULL_POINTER, _OGC_FLASH_BANK);
    }
}

//--------------------------------------------------
// Description  : return applying HDR parameter or PCM parameter
// Input Value  : EnumHDRModeDef, EnumDisplayRegion
// Output Value : _ON(HDR), _OFF(PCM)
//--------------------------------------------------
bit UserCommonAdjustHDREnableStatus(EnumDisplayRegion enumDisplayRegion, EnumHDRModeDef enumHDRModeDef)
{
    if(enumDisplayRegion < _DISPLAY_RGN_LT)
    {
        switch(enumHDRModeDef)
        {
            case _HDR_MODE_OFF:

                return _OFF;

            case _HDR_MODE_AUTO:

                if(GET_HDR_EOTF(enumDisplayRegion) == _HDR_INFO_EOTF_SMPTE_ST_2084)
                {
                    return _ON;
                }
                else
                {
                    return _OFF;
                }

            case _HDR_MODE_SMPTE_ST_2084:

                return _ON;

            default:

                break;
        }
    }

    return _OFF;
}
#endif

#if(_DCR_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustDCR(void)
{
    // Check if DCR data ready.
    if(ScalerColorDCRGetDataReadyStatus() == _TRUE)
    {
        // Clear DCR data ready status.
        ScalerColorDCRClrDataReadyStatus();

        // freeze DCR data
        ScalerColorDCRDataRefreshControl(_DISABLE);

        // Read DCR Result
        UserInterfaceAdjustDCR();

        // release DCR data
        ScalerColorDCRDataRefreshControl(_ENABLE);
    }
}
#endif // End of #if(_DCR_SUPPORT == _ON)

#if(_FREEZE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Display freeze
// Input Value  : ON --> Display freeze
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustDisplayFreeze(bit bEn)
{
    ScalerFRCDisplayFreeze(bEn);
}
#endif // End of #if(_FREEZE_SUPPORT == _ON)

#if(_SHARPNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Sharpness Table
// Input Value  : Request Sharpness Table
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustSharpness(EnumSelRegion enumSelRegion, EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSelRegion)
    {
        case _1P_NORMAL_FULL_REGION:
        case _1P_ROTATION_FULL_REGION:
        case _PIP_MAIN:
        case _PBP_LR_L:
        case _PBP_TB_T:
        case _PIP_SUB:
        case _PBP_LR_R:
        case _PBP_TB_B:
        case _4P_LT:
        case _4P_LB:
        case _4P_RT:
        case _4P_RB:

            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel(enumSelRegion) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(enumSelRegion,
                                           UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(enumSelRegion,
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }

            break;

        case _PIP_FULL_REGION:
        case _PBP_LR_FULL_REGION:
            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel(_PIP_MAIN) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(_PIP_MAIN,
                                           UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(_PIP_MAIN,
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }

            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel(_PIP_SUB) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(_PIP_SUB,
                                           UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(_PIP_SUB,
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }

            break;

        case _PBP_TB_FULL_REGION:

            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel(_PBP_TB_T) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(_PBP_TB_T,
                                           UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(_PBP_TB_T,
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }

            // 1:1 Mode Use Different Scaling Table
            if((ScalerColorScalingByPassTableSel(_PBP_TB_B) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
            {
                ScalerMemorySetScalingCoef(_PBP_TB_B,
                                           UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            else
            {
                ScalerMemorySetScalingCoef(_PBP_TB_B,
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                           UserInterfaceGetSharpnessCoefBankNum());
            }
            break;

        case _4P_FULL_REGION:
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:

            if(enumSelRegion != _4P_LT_OUTSIDE)
            {
                if((ScalerColorScalingByPassTableSel(_4P_LT) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
                {
                    ScalerMemorySetScalingCoef(_4P_LT,
                                               UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoefBankNum());
                }
                else
                {
                    ScalerMemorySetScalingCoef(_4P_LT,
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoefBankNum());
                }
            }

            if(enumSelRegion != _4P_LB_OUTSIDE)
            {
                if((ScalerColorScalingByPassTableSel(_4P_LB) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
                {
                    ScalerMemorySetScalingCoef(_4P_LB,
                                               UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoefBankNum());
                }
                else
                {
                    ScalerMemorySetScalingCoef(_4P_LB,
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoefBankNum());
                }
            }

            if(enumSelRegion != _4P_RT_OUTSIDE)
            {
                if((ScalerColorScalingByPassTableSel(_4P_RT) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
                {
                    ScalerMemorySetScalingCoef(_4P_RT,
                                               UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoefBankNum());
                }
                else
                {
                    ScalerMemorySetScalingCoef(_4P_RT,
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoefBankNum());
                }
            }

            if(enumSelRegion != _4P_RB_OUTSIDE)
            {
                if((ScalerColorScalingByPassTableSel(_4P_RB) == _TRUE) || (UserInterfaceSharpnessBypassCheck() == _TRUE))
                {
                    ScalerMemorySetScalingCoef(_4P_RB,
                                               UserInterfaceGetSharpnessCoef(_H_SU_128TAPS_1_TO_1, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoefBankNum());
                }
                else
                {
                    ScalerMemorySetScalingCoef(_4P_RB,
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoef(_H_V_SU_128TAPS_NORMAL, enumSelRegion, enumSourceSearchPort),
                                               UserInterfaceGetSharpnessCoefBankNum());
                }
            }
            break;

        case _1P_NORMAL_DEMO_OUTSIDE:
        case _PIP_DEMO_OUTSIDE:
        case _PBP_LR_DEMO_OUTSIDE:
        case _PBP_TB_DEMO_OUTSIDE:
        case _4P_DEMO_OUTSIDE:
        case _1P_NORMAL_DEMO_INSIDE:
        case _PIP_DEMO_INSIDE:
        case _PBP_LR_DEMO_INSIDE:
        case _PBP_TB_DEMO_INSIDE:
        case _4P_DEMO_INSIDE:
        default:

            break;
    }
}
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable False Color function
// Input Value  : EnumFunctionOnOFF
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustFalseColorEnable(EnumSelRegion enumSelRegion, EnumFunctionOnOFF enumOn)
{
    if(enumOn == _FUNCTION_ON)
    {
#if(_BRIGHTNESS_SUPPORT == _ON)
        ScalerColorBrightnessEnable(_FUNCTION_OFF);
#endif
        ScalerColorSRGBSetEffectiveRegion(enumSelRegion, _DB_APPLY_POLLING);
        ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);

#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_ON);
#endif
        ScalerColorOutputGammaEnable(_FUNCTION_ON);
        ScalerColorGammaSetEffectiveRegion(enumSelRegion, _DB_APPLY_POLLING);
        ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);
        ScalerColorIAPSGainEnable(_FUNCTION_ON);
        ScalerColorSRGBCtsSwap(_FUNCTION_ON);
    }
    else if(enumOn == _FUNCTION_OFF)
    {
        ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
        ScalerColorOutputGammaEnable(_FUNCTION_OFF);

#if(_CONTRAST_SUPPORT == _ON)
        ScalerColorContrastEnable(_FUNCTION_OFF);
#endif
        ScalerColorIAPSGainEnable(_FUNCTION_OFF);
        ScalerColorSRGBCtsSwap(_FUNCTION_OFF);
    }
}

//--------------------------------------------------
// Description  : Adjust SRGB Matrix RGBtoYYY
// Input Value  : BYTE ucLevel: 0-15, adjust Y level
//                BYTE ucColorCode: Selected Color Code
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustFalseColorSRGBCtsAdjust(EnumSelRegion enumSelRegion)
{
    BYTE pucRGB2YYY[] =
    {
        0x61, 0x36, 0x20, 0xB7, 0x80, 0x12,
        0x60, 0x36, 0x21, 0xB7, 0x80, 0x12,
        0x60, 0x36, 0x20, 0xB7, 0x81, 0x12,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    WORD pusData[3] = {0x200, 0x200, 0x200};

    ScalerColorIAPSGainValueAdjust(enumSelRegion, 0x7FFF);
    ScalerColorIAPSGainSoftClampAdjust(enumSelRegion, 0x00);

#if(_CONTRAST_SUPPORT == _ON)
    ScalerColorContrastAdjust(enumSelRegion, pusData);
#endif

    ScalerColorSRGBAdjust(enumSelRegion, pucRGB2YYY, _SRGB_1_BIT_SHIFT_LEFT);
}

//--------------------------------------------------
// Description  : Interpolate and Update OG LUT
// Input Value  : EnumSelRegion enumSelRegion:Selected Region;
//                BYTE ucMode: 0- Interpolation Mode; 1- 16 Step Mode
//                BYTE ucLevel: Interpolation Mode 0-16, Interpolation Node ; Non-Interpolation: 0-15  Y level
//                BYTE ucColorCodeLast: the Interpolation node before Selected Color Code(only valid in Interpolation Mode)
//                BYTE ucColorCodeCur: Selected Color Code
//                BYTE ucColorCodeNext: the Interpolation node after Selected Color Code(only valid in Interpolation Mode)
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustFalseColorUpDateOGLUTInterpo(EnumSelRegion enumSelRegion, BYTE ucMode, BYTE ucLevel, BYTE ucColorCodeLast, BYTE ucColorCodeCur, BYTE ucColorCodeNext)
{
    WORD usLength = 128;
    BYTE pucGammaTableArray[132];
    BYTE ucI = 0;
    BYTE ucK = 0;
    BYTE ucJ = _GAMMA_RED_CHANNEL;
    WORD usStartAddr = 32 * ucLevel;
    WORD usInterpoColor = 0;
    BYTE ucIndex = 0;

    memset(pucGammaTableArray, 0, sizeof(pucGammaTableArray));

    for(ucJ = _GAMMA_RED_CHANNEL; ucJ <= _GAMMA_BLUE_CHANNEL; ucJ++)
    {
        if(ucMode == 0)  // Interpolation Mode: 17 Point
        {
            if(ucLevel != 16)
            {
                for(ucI = 0; ucI < 16; ucI++)
                {
                    usInterpoColor = tFALSECOLOR_TABLE[ucColorCodeCur][ucJ] + ucI * ((int)tFALSECOLOR_TABLE[ucColorCodeNext][ucJ] - (int)tFALSECOLOR_TABLE[ucColorCodeCur][ucJ]) / 16;

                    for(ucK = 0; ucK < 4; ucK++)
                    {
                        ucIndex = ucI * 4 + ucK;
                        pucGammaTableArray[2 * ucIndex] = (usInterpoColor & 0xFC) >> 2;
                        pucGammaTableArray[2 * ucIndex + 1] = (usInterpoColor & 0x03) << 6;
                    }
                }
                ScalerColorOutputGammaAdjustSector(enumSelRegion, ucJ, pucGammaTableArray, usStartAddr, usLength, GET_CURRENT_BANK_NUMBER());
            }

            if(ucLevel != 0)
            {
                for(ucI = 0; ucI < 16; ucI++)
                {
                    usInterpoColor = tFALSECOLOR_TABLE[ucColorCodeLast][ucJ] + ucI * ((int)tFALSECOLOR_TABLE[ucColorCodeCur][ucJ] - (int)tFALSECOLOR_TABLE[ucColorCodeLast][ucJ]) / 16;

                    for(ucK = 0; ucK < 4; ucK++)
                    {
                        ucIndex = ucI * 4 + ucK;
                        pucGammaTableArray[2 * ucIndex] = (usInterpoColor & 0xFC) >> 2;
                        pucGammaTableArray[2 * ucIndex + 1] = (usInterpoColor & 0x03) << 6;
                    }
                }

                if(ucLevel == 16)
                {
                    usLength = 132;
                    pucGammaTableArray[128] = pucGammaTableArray[126];
                    pucGammaTableArray[129] = pucGammaTableArray[127];
                    pucGammaTableArray[130] = 0;
                    pucGammaTableArray[131] = 0;
                }

                ScalerColorOutputGammaAdjustSector(enumSelRegion, ucJ, pucGammaTableArray, usStartAddr - 32, usLength, GET_CURRENT_BANK_NUMBER());
            }
        }
        else  // Non- Interpolation Mode  16 Step
        {
            for(ucI = 0; ucI < 128; ucI = ucI + 2)
            {
                pucGammaTableArray[ucI] = (tFALSECOLOR_TABLE[ucColorCodeCur][ucJ] & 0xFC) >> 2;
                pucGammaTableArray[ucI + 1] = (tFALSECOLOR_TABLE[ucColorCodeCur][ucJ] & 0x03) << 6;
            }

            if(ucLevel == 15)
            {
                pucGammaTableArray[128] = pucGammaTableArray[126];
                pucGammaTableArray[129] = pucGammaTableArray[127];
                pucGammaTableArray[130] = 0;
                pucGammaTableArray[131] = 0;
                usLength = 132;
            }

            ScalerColorOutputGammaAdjustSector(enumSelRegion, ucJ, pucGammaTableArray, usStartAddr, usLength, GET_CURRENT_BANK_NUMBER());
        }
    }
}

//--------------------------------------------------
// Description  : Change False Color Mode
// Input Value  : BYTE ucMode: 0- 16 Steps Color,
//                             1- 256 Steps Color,
//                             2- 256 Steps Color With White/Black/Gray
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustFalseColorModeChange(EnumSelRegion enumSelRegion, BYTE *pucFalseColorTable, BYTE ucBankNum)
{
    UserCommonAdjustFalseColorSRGBCtsAdjust(enumSelRegion);
    ScalerColorOutputGammaAdjust(enumSelRegion, pucFalseColorTable, ucBankNum);
}

//--------------------------------------------------
// Description  : Adjust False Color
// Input Value  : BYTE ucLevel: 0-15, adjust Y level
//                BYTE ucColorCode: Selected Color Code
// Output Value : None
//--------------------------------------------------
void UserCommonAdjustFalseColorAdjust(EnumSelRegion enumSelRegion, BYTE ucLevel, BYTE ucColorCodeLast, BYTE ucColorCodeCur, BYTE ucColorCodeNext)
{
    UserCommonAdjustFalseColorSRGBCtsAdjust(enumSelRegion);
    UserCommonAdjustFalseColorUpDateOGLUTInterpo(enumSelRegion, 0, ucLevel, ucColorCodeLast, ucColorCodeCur, ucColorCodeNext);
}
#endif // End of #if(_FALSE_COLOR_SUPPORT == _ON)
