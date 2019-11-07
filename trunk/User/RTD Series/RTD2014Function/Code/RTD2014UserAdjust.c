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
// ID Code      : RTD2014UserAdjust.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST__
#define __USER_PANEL__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
#define _HLWIN_TYPE5_MOVE_TIME                      SEC(0.01)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// IR TABLE
//----------------------------------------------------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
BYTE code tIR_INITIAL_TABLE[] =
{
#if(_IR_PROTOCAL == _IR_NEC_DTV328)
    #include "IRRemote/NEC_DTV328.h"

#elif(_IR_PROTOCAL == _IR_SONY_B102P)
    #include "IRRemote/SONY_B102P.h"

#elif(_IR_PROTOCAL == _IR_PHILIPS_RC6)
    #include "IRRemote/PHILIPS_RC6.h"

#endif // End of #if(_IR_PROTOCAL == _IR_NEC_DTV328)
};
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
BYTE code tFALSECOLORMODE0[] =
{
#include "./FalseColor/FalseColorLUTMode0.h"
};

BYTE code tFALSECOLORMODE1[] =
{
#include "./FalseColor/FalseColorLUTMode1.h"
};

BYTE code tFALSECOLORMODE2[] =
{
#include "./FalseColor/FalseColorLUTMode2.h"
};


code BYTE *tOGFALSECOLOR_TABLE[] =
{
    tFALSECOLORMODE0,
    tFALSECOLORMODE1,
    tFALSECOLORMODE2,
};
#endif// End of #if(_FALSE_COLOR_SUPPORT == _ON)



//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
bit g_bHLWinRLMove = _RIGHT;
WORD g_usHLWinHPos;
WORD g_usHLWinHWidth;
WORD g_usHLWinVPos;
WORD g_usHLWinVHeight;
#endif


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//----------------------------------------------------------------------------
// Kernel Related Function
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Not Kernel Related Function
//----------------------------------------------------------------------------
//-------------------------------------------------------

#if((_OVERSCAN_SUPPORT == _ON) || (_ASPECT_RATIO_SUPPORT == _ON))
void UserAdjustResetDisplayByPort(EnumDisplayRegion enumDisplayRegion);
#endif

// Adjust Backlight
//-------------------------------------------------------
void UserAdjustBacklight(WORD usBacklight);

//-------------------------------------------------------
// Audio Related
//-------------------------------------------------------
#if(_AUDIO_SUPPORT == _ON)
void UserAdjustAudioMuteSwitch(void);
void UserAdjustAudioVolume(BYTE ucVolume);
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume);
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
void UserAdjustFREESYNCODMeasure(void);
#endif

//-------------------------------------------------------
// DCC
//-------------------------------------------------------
#if(_DCC_FUNCTION == _ON)
void UserAdjustDCC(EnumSelRegion enumSelRegion, BYTE ucColorEffect);
#endif // End of #if(_DCC_FUNCTION == _ON)

//-------------------------------------------------------
// CTS / BRI
//-------------------------------------------------------
#if(_CONTRAST_SUPPORT == _ON)
void UserAdjustContrast(EnumSelRegion enumSelRegion, WORD usContrast);
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
void UserAdjustBrightness(EnumSelRegion enumSelRegion, WORD usBrightness);
#endif

//-------------------------------------------------------
// ICM
//-------------------------------------------------------
#if(_ICM_SUPPORT == _ON)
void UserAdjustICM(EnumSelRegion enumSelRegion, BYTE ucColorEffect);
#endif

#if(_SCM_SUPPORT == _ON)
void UserAdjustSCM(EnumSelRegion enumSelRegion, BYTE ucColorEffect);
#endif

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
void UserAdjustColorEffectMode(EnumSelRegion enumSelRegion);
#endif

//-------------------------------------------------------
// 3D Gamma
//-------------------------------------------------------

//-------------------------------------------------------
// sRGB
//-------------------------------------------------------
#if(_GLOBAL_HUE_SATURATION == _ON)
void UserAdjustGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shHue, WORD usSat);
#endif

//-------------------------------------------------------
// Unifomity
//-------------------------------------------------------

//-------------------------------------------------------
// Output Gamma
//-------------------------------------------------------

//-------------------------------------------------------
// OD
//-------------------------------------------------------
#if(_OD_SUPPORT == _ON)
void UserAdjustOD(void);
#endif


//-------------------------------------------------------
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
void UserAdjustHLWinType(BYTE ucHLWinType);
void UserAdjustHLWinType5Move(void);
void UserAdjustHighLightWindowEffectSpace(void);
#endif

//-------------------------------------------------------
// PIP Sub config
//-------------------------------------------------------
#if(_PIP_DISPLAY_SUPPORT == _ON)

#if(_PIP_BLENDING_SUPPORT == _ON)
void UserAdjustPipTransparency(void);
#endif

#endif

void UserAdjustOsdSelectRegionColorProc(void);
void UserAdjustDisplayMode(void);
void UserAdjustRegionInputPort(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort);
#if(_2P_DISPLAY_SUPPORT == _ON)
void UserAdjustSwapInputPort(void);
#endif

EnumSelRegion UserAdjustConvertSystemSelectRegion(BYTE ucRegion);
EnumDisplayRegion UserAdjustConvertDisplayRegion(BYTE ucRegion);
EnumSourceSearchPort UserAdjustGetSelectRegionPort(void);

//-------------------------------------------------------
// PCM
//-------------------------------------------------------
#if((_OGC_SUPPORT == _ON) || (_PCM_FUNCTION == _ON))
BYTE UserAdjustGetOSDSelectRegion(EnumSelRegion enumSelRegion);
#endif

//-------------------------------------------------------
// HW IR Mode
//-------------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
void UserAdjusIR(void);
#endif

//-------------------------------------------------------
// DP EDID Switch
//-------------------------------------------------------
void UserAdjustDpEdidTableSwitch(BYTE ucSelectedPort);

//-------------------------------------------------------
// False Color
//-------------------------------------------------------
#if(_FALSE_COLOR_SUPPORT == _ON)
void UserAdjustFalseColorUserDefine(EnumSelRegion enumSelRegion, BYTE ucLevel, BYTE ucColorCodeLast, BYTE ucColorCodeCur, BYTE ucColorCodeNext);
void UserAdjustFalseColor(EnumSelRegion enumSelRegion, BYTE ucMode);
#endif
//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//----------------------------------------------------------------------------
// Kernel Related Function
//----------------------------------------------------------------------------
#if((_ASPECT_ORIGINAL_MODE_SUPPORT == _ON) || (_OVERSCAN_SUPPORT == _ON))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustResetDisplayByPort(EnumDisplayRegion enumDisplayRegion)
{
    if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
    {
       if((SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_ACTIVE) ||
                       (SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_DISPLAY_READY))// alant add
       {
          SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
          SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
       }
    }
    else
    {
        EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType(enumDisplayRegion);
        EnumDisplayRegion enumIndexRegion = _DISPLAY_RGN_NONE;
        BYTE ucIndex = 0x00;

        for(ucIndex = 0x00; ucIndex < SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX); ++ucIndex)
        {
            enumIndexRegion = SysRegionGetDisplayRegion(ucIndex);

            if(SysRegionGetPortType(enumIndexRegion) == enumSourceSearchPort)
            {
                if(enumIndexRegion == enumDisplayRegion)
                {
                    if((SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_ACTIVE) ||
                       (SysRegionGetDisplayState(enumDisplayRegion) == _DISPLAY_STATE_DISPLAY_READY))
                    {
                        SysModeSetDisplayTarget(enumDisplayRegion);
                        /// SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                        SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG);
                    }
                }
                else
                {
                    if((SysRegionGetDisplayState(enumIndexRegion) == _DISPLAY_STATE_ACTIVE) ||
                       (SysRegionGetDisplayState(enumIndexRegion) == _DISPLAY_STATE_DISPLAY_READY))
                    {
                        SysModeResetDisplayState(enumIndexRegion);
                    }
                }
            }
        }
    }
}
#endif // End of #if((_ASPECT_ORIGINAL_MODE_SUPPORT == _ON) || (_OVERSCAN_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Adjust backlight
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustBacklight(WORD usBacklight)
{
//    usBacklight = _BACKLIGHT_MIN + ((DWORD)(_BACKLIGHT_MAX - _BACKLIGHT_MIN) * usBacklight) / 100;

#if(_BACKLIGHT_PWM_INVERSE == _ON)
    //usBacklight = _BACKLIGHT_MAX - usBacklight;
     usBacklight = 255 -( usBacklight + GET_BL_OFFSET());
#endif

    // Adjust backlight by changing PWM duty
    PCB_BACKLIGHT_PWM(usBacklight);
}

//----------------------------------------------------------------------------
// Not Kernel Related Function
//----------------------------------------------------------------------------

#if(_AUDIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Mute/Unmute Aduio Volume
// Input Value  : bMute
// Output Value : None
//--------------------------------------------------
void UserAdjustAudioMuteSwitch(void)
{
    SysAudioMuteProc(UserInterfaceGetAudioMuteStatus());
}

//--------------------------------------------------
// Description  : Adjust Aduio Volume
// Input Value  : ucVolume
// Output Value : Node
//--------------------------------------------------
void UserAdjustAudioVolume(BYTE ucVolume)
{
    ScalerAudioDigitalAdjustVolume(UserAdjustAudioVolumeMapping(ucVolume));
}

//--------------------------------------------------
// Description  : OSD Volume Mapping to Real Value
// Input Value  : usVolume
// Output Value : usVolume
//--------------------------------------------------
WORD UserAdjustAudioVolumeMapping(BYTE ucVolume)
{
#if(_LINE_IN_SUPPORT == _ON)
    if(UserInterfaceGetAudioSource() == _LINE_IN_AUDIO)
    {
        return(UserCommonAdjustPercentToRealValue(ucVolume, _LINE_IN_VOLUME_MAX, _LINE_IN_VOLUME_MIN, _LINE_IN_VOLUME_CENTER));
    }
    else
#endif // End of #if(_LINE_IN_SUPPORT == _ON)
    {
        return(UserCommonAdjustPercentToRealValue(ucVolume, _DIGITAL_VOLUME_MAX, _DIGITAL_VOLUME_MIN, _DIGITAL_VOLUME_CENTER));
    }
}
#endif // End of #if(_AUDIO_SUPPORT == _ON)

#if(_FREESYNC_OD_MEASURE == _ON)
//--------------------------------------------------
// Description  : Set FREESYNC OD Measure
// Input Value  : Current DHtotal(pixel)/ Current Dclk(kHz)/ Target Measure VFreq(0.1Hz)
// Output Value : None
//--------------------------------------------------
void UserAdjustFREESYNCODMeasure(void)
{
    // Set Backlight
    UserAdjustBacklight(100);

    // Enable Backlight
    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

    // Disable OSD
    ScalerOsdDisableOsd();

    // Disable D-domain Pattern Gen.
    ScalerDDomainPatternGenEnable(_DISABLE);

    // According FREESYNC setting to set accurate Htotal/ Dclk
    ScalerMDomainFREESYNCODSetDisplayFormat(((WORD)_PANEL_DH_TOTAL), ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ), ((WORD)_PANEL_FREESYNC_MIN_FRAME_RATE));

    while(_TRUE)
    {
        ScalerDebug();
        ScalerDDomainFREESYNCODSetBackgroundGrayLevel();
    }
}
#endif

#if(_DCC_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set DCC Table
// Input Value  : Request DCC Table
// Output Value : None
//--------------------------------------------------
void UserAdjustDCC(EnumSelRegion enumSelRegion, BYTE ucColorEffect)
{
    if((ucColorEffect != _COLOREFFECT_STANDARD) && (ucColorEffect != _COLOREFFECT_USER))
    {
        ScalerColorDCCAdjust(enumSelRegion, tDCC_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_CONTRAST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust Contrast
// Input Value  : 12 bit input, old 8 bit contrast input value must left shift 4 bit
//                0 (00h) ~ 1(800h) ~  2(FFFh)
// Output Value : void
//--------------------------------------------------
void UserAdjustContrast(EnumSelRegion enumSelRegion, WORD usContrast)
{
    WORD pusData[3] = {0};

    pusData[0] = (WORD)(((DWORD)g_stColorProcData.usColorTempR * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempR * usContrast / 2048);
    pusData[1] = (WORD)(((DWORD)g_stColorProcData.usColorTempG * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempG * usContrast / 2048);
    pusData[2] = (WORD)(((DWORD)g_stColorProcData.usColorTempB * usContrast / 2048) > 4095) ? 4095 : (WORD)((DWORD)g_stColorProcData.usColorTempB * usContrast / 2048);

    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
    {
        // 10-bit Panel
        pusData[0] = UserCommonAdjust10bitPanelCompensate(pusData[0]);
        pusData[1] = UserCommonAdjust10bitPanelCompensate(pusData[1]);
        pusData[2] = UserCommonAdjust10bitPanelCompensate(pusData[2]);
    }

    ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
    ScalerColorContrastAdjust(enumSelRegion, pusData);
    ScalerColorContrastEnable(_FUNCTION_ON);
}
#endif

#if(_BRIGHTNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : User Adjust Brightness
// Input Value  : 10 bit input, old 8 bit brightness input value must left shift 2 bit
//                -2048(00h) ~ 0(200h) ~  +2044(3FFh)
// Output Value : void
//--------------------------------------------------
void UserAdjustBrightness(EnumSelRegion enumSelRegion, WORD usBrightness)
{
    WORD pusData[3] = {0};
    pusData[0] = usBrightness;
    pusData[1] = usBrightness;
    pusData[2] = usBrightness;

    ScalerColorBrightnessAdjust(enumSelRegion, pusData);
    ScalerColorBrightnessEnable(_FUNCTION_ON);
}
#endif

#if(_ICM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set ICM parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustICM(EnumSelRegion enumSelRegion, BYTE ucColorEffect)
{
    if((ucColorEffect != _COLOREFFECT_STANDARD) && (ucColorEffect != _COLOREFFECT_USER))
    {
        ScalerColorICMLoadTable(enumSelRegion, tICM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_ICM_SUPPORT == _ON)

#if(_SCM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set SCM parameter
// Input Value  : Adjust Option
// Output Value : None
//--------------------------------------------------
void UserAdjustSCM(EnumSelRegion enumSelRegion, BYTE ucColorEffect)
{
    if((ucColorEffect != _COLOREFFECT_STANDARD) && (ucColorEffect != _COLOREFFECT_USER))
    {
        ScalerColorSCMLoadTable(enumSelRegion, tSCM_TABLE[ucColorEffect], GET_CURRENT_BANK_NUMBER());
    }
}
#endif // End of #if(_SCM_SUPPORT == _ON)


#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set UltraVivid Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustColorEffectMode(EnumSelRegion enumSelRegion)
{
    BYTE ucIndex = 0;
    BYTE ucBackupSixColor = 0;
    BYTE ucBackupHue = 0;
    BYTE ucBackupSaturation = 0;

    ucBackupSixColor = GET_OSD_SIX_COLOR();
    ucBackupHue = GET_OSD_SIX_COLOR_HUE();
    ucBackupSaturation = GET_OSD_SIX_COLOR_SATURATION();

    switch(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()))
    {
        case _COLOREFFECT_STANDARD:

#if(_DCC_FUNCTION == _ON)
#if(_ICM_SUPPORT == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#else
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
#endif

#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
#endif
            break;

        case _COLOREFFECT_USER:

#if(_DCC_FUNCTION == _ON)
#if(_ICM_SUPPORT == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#else
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
#endif

#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
            for(ucIndex = 0; ucIndex < 6; ucIndex++)
            {
                SET_OSD_SIX_COLOR(ucIndex);
                OsdDisplaySixColorGetOneColor(enumSelRegion, ucIndex);
                ScalerColorSixColorAdjust(enumSelRegion, ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
            }

            ScalerColorSixColorInitial(enumSelRegion);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);
#endif
            break;

        case _COLOREFFECT_MOVIE:
        case _COLOREFFECT_GAME:
        case _COLOREFFECT_PHOTO:
        case _COLOREFFECT_VIVID:

#if(_DCC_FUNCTION == _ON)
#if(_ICM_SUPPORT == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#else
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
#endif

#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
#endif

#if(_DCC_FUNCTION == _ON)
            UserAdjustDCC(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            ScalerColorSetDCCAutoModeRegion(g_enumDCCMeasureRegion);
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
            UserAdjustSCM(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
#endif

#if(_ICM_SUPPORT == _ON)
            UserAdjustICM(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
#endif


#if(_DCC_FUNCTION == _ON)
#if(_ICM_SUPPORT == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
#else
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);
#endif

#endif // End of #if(_DCC_FUNCTION == _ON)

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _ON);
#endif
            break;

        default:
            break;
    }

    SET_OSD_SIX_COLOR(ucBackupSixColor);
    SET_OSD_SIX_COLOR_HUE(ucBackupHue);
    SET_OSD_SIX_COLOR_SATURATION(ucBackupSaturation);
}
#endif // End of #if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))

#if(_GLOBAL_HUE_SATURATION == _ON)
//--------------------------------------------------
// Description  : Adjust Global Hue Saturation
// Input Value  : Hue and Saturation
// Output Value : None
//--------------------------------------------------
void UserAdjustGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shHue, WORD usSat)
{
#if((_PCM_FUNCTION == _ON) && (_PCM_TABLE_TYPE == _PCM_GEN_0))
    enumSelRegion = ScalerColorPCMCheckPCMRegion(enumSelRegion);
#endif

    ScalerColorSRGBSetGlobalHueSat(enumSelRegion, _DEFAULT_HUE - shHue, usSat);
}
#endif  // Enf of #if(_GLOBAL_HUE_SATURATION == _ON)



#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Load OD LUT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustOD(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(ScalerSyncGetFREESYNCEnable() == _TRUE)
    {
        ScalerODLoadLUT(tOD_FREESYNC_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
    }
    else
#endif
    {
        ScalerODLoadLUT(tOD_TABLE[0], GET_CURRENT_BANK_NUMBER(), _OD_LUT_MODE);
    }
}
#endif // End of #if(_OD_SUPPORT == _ON)

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust High Light Window
// Input Value  : HLWinType
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType(BYTE ucHLWinType)
{
    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

    if(ucHLWinType == _HL_WIN_OFF)
    {
        return;
    }

    g_usHLWinHPos = 0;
    g_usHLWinVPos = 0;

    switch(ucHLWinType)
    {
        case _HL_WIN_1:

            g_usHLWinHWidth = _PANEL_DH_WIDTH - _HL_WIN_BORDER_SIZE;
            g_usHLWinVHeight = _PANEL_DV_HEIGHT - _HL_WIN_BORDER_SIZE;

            break;

        case _HL_WIN_2:

            g_usHLWinHWidth = _PANEL_DH_WIDTH / 2;
            g_usHLWinVHeight = _PANEL_DV_HEIGHT - _HL_WIN_BORDER_SIZE;

            break;

        case _HL_WIN_3:

            g_usHLWinHWidth = _PANEL_DH_WIDTH - _HL_WIN_BORDER_SIZE;
            g_usHLWinVHeight = _PANEL_DV_HEIGHT / 2;

            break;

        case _HL_WIN_4:

            g_usHLWinHWidth = _PANEL_DH_WIDTH / 2;
            g_usHLWinVHeight = _PANEL_DV_HEIGHT / 2;
            g_usHLWinHPos = ((_PANEL_DH_WIDTH - g_usHLWinHWidth) / 2) + ((_PANEL_DH_WIDTH - _PANEL_DH_WIDTH) / 2) - 1;
            g_usHLWinVPos = (_PANEL_DV_HEIGHT - g_usHLWinVHeight) / 2 - 1;

            break;

        case _HL_WIN_5:

            g_usHLWinHWidth = _PANEL_DH_WIDTH / 6;
            g_usHLWinVHeight = _PANEL_DV_HEIGHT - _HL_WIN_BORDER_SIZE;
            g_usHLWinHPos = (_PANEL_DH_WIDTH - g_usHLWinHWidth) / 2;

            ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);

            break;

        default:

            break;
    }
    ScalerColorHLWBorderAdjust(_HL_WIN_BORDER_SIZE, 255, 0, 0, _DB_APPLY_NONE);
    ScalerColorHLWBorderEnable(_ON, _ON, _ON, _ON, _DB_APPLY_NONE);
    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NONE);
}

//--------------------------------------------------
// Description  : High Light Window Type5 Move
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHLWinType5Move(void)
{
    WORD usNonFullScreenOffset = 0;

    if(g_bHLWinRLMove == _RIGHT)
    {
        g_usHLWinHPos++;

        if((_PANEL_DH_WIDTH + usNonFullScreenOffset) <= (g_usHLWinHPos + g_usHLWinHWidth + _HL_WIN_BORDER_SIZE))
        {
            g_bHLWinRLMove = _LEFT;
            g_usHLWinHPos = (_PANEL_DH_WIDTH + usNonFullScreenOffset) - (g_usHLWinHWidth + _HL_WIN_BORDER_SIZE);
        }
    }
    else // _LEFT
    {
        g_usHLWinHPos--;

        if(g_usHLWinHPos <= usNonFullScreenOffset)
        {
            g_bHLWinRLMove = _RIGHT;
            g_usHLWinHPos = usNonFullScreenOffset;
        }
    }

    ScalerColorHLWBorderAdjust(_HL_WIN_BORDER_SIZE, 255, 0, 0, _DB_APPLY_NONE);
    ScalerColorHLWBorderEnable(_ON, _ON, _ON, _ON, _DB_APPLY_NONE);
    ScalerColorHLWAdjust(g_usHLWinHPos, g_usHLWinHWidth, g_usHLWinVPos, g_usHLWinVHeight, _DB_APPLY_NO_POLLING);

    ScalerTimerActiveTimerEvent(_HLWIN_TYPE5_MOVE_TIME, _USER_TIMER_EVENT_HLWIN_TYPE5_MOVE);
}

//--------------------------------------------------
// Description  : Adjust All High Light Window Effect Space
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustHighLightWindowEffectSpace(void)
{
#if(_IAPS_SUPPORT == _ON)
    ScalerColorHLWIAPSGainAdjust(_HLW_FULL_WINDOW, _DB_APPLY_NO_POLLING);
#endif

#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
    ScalerColorDCRSetMeasureRegion(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING);
#endif
}
#endif // End of #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#if(_PIP_DISPLAY_SUPPORT == _ON)
#if(_PIP_BLENDING_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustPipTransparency(void)
{
    if((SysModeGetDisplayMode() == _DISPLAY_MODE_PIP) &&
       (SysRegionGetDisplayState(_DISPLAY_RGN_MAIN) == _DISPLAY_STATE_ACTIVE))
    {
        ScalerColorPIPBlendingLevelAdjust((((WORD)GET_OSD_PIP_TRANSPARENCY() * 51) >> 1), _DB_APPLY_NO_POLLING);
    }
}
#endif

#endif

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserAdjustOsdSelectRegionColorProc(void)
{
#if(_SIX_COLOR_SUPPORT == _ON)
    BYTE ucIndex = 0;
#endif

    EnumSelRegion enumSelRegion = GET_OSD_SYSTEM_SELECT_REGION();
    EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(enumSelRegion);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
    if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
    {
        UserInterfaceAdjustHighlightWindow(_DB_APPLY_NONE);
    }
#endif

    // Adjust UltraVivid
#if(_ULTRA_VIVID_SUPPORT == _ON)
    if(enumSelRegionInverse == _NON_REGION)
    {
        UserCommonAdjustUltraVivid(enumSelRegion, _DB_APPLY_POLLING);
    }
    else
    {
        UserCommonAdjustUltraVivid(enumSelRegion, _DB_APPLY_NONE);
        UserCommonAdjustUltraVivid(enumSelRegionInverse, _DB_APPLY_POLLING);
    }
#endif

#if(_UNIFORMITY_SUPPORT == _ON)
    ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

    if((GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON) && (GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON))
    {
        ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);
    }
    else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
    {
        ScalerColorPanelUniformityRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
    }
    else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON)
    {
        ScalerColorPanelUniformityRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
    }
#endif

#if(_PCM_FUNCTION == _ON)
    if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
    {
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
        ScalerColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
#endif
        ScalerColorPCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NO_POLLING);

        if(GET_OSD_GAMMA(GET_OSD_INVERSE_REGION()) != _GAMMA_OFF)
        {
            UserAdjustGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }
    }
    else if((GET_OSD_PCM_STATUS(GET_OSD_INVERSE_REGION()) != _PCM_OSD_NATIVE))
    {
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
        ScalerColorBRICTSRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _OFF);
#endif
        ScalerColorPCMSetEffectiveRegion(enumSelRegionInverse, _DB_APPLY_NO_POLLING);

        if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
        {
            UserAdjustGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
        }
    }
    else
#endif // End of #if(_PCM_FUNCTION == _ON)
    {
#if((_CONTRAST_SUPPORT == _ON) || (_BRIGHTNESS_SUPPORT == _ON))
        ScalerColorBRICTSRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        ScalerColorBRICTSRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
#endif
        if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) == _GAMMA_OFF)
        {
            ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
        }
        else
        {
            if(enumSelRegion == _1P_NORMAL_DEMO_INSIDE)
            {
                ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                UserAdjustGamma(enumSelRegion, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
            }

            ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }

        if(GET_OSD_GAMMA(GET_OSD_INVERSE_REGION()) == _GAMMA_OFF)
        {
            ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _OFF);
        }
        else
        {
            ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
        }

#if(_GLOBAL_HUE_SATURATION == _ON)
        ScalerColorSRGBSetEffectiveRegion(enumSelRegion, _DB_APPLY_NO_POLLING);
#endif

#if(_GAMMA_FUNCTION == _ON)
        ScalerColorGammaSetEffectiveRegion(enumSelRegion, _DB_APPLY_NO_POLLING);
#endif
    }

#if(_IAPS_SUPPORT == _ON)
    ScalerColorIAPSGainSetEffectiveRegion(enumSelRegion, _DB_APPLY_NO_POLLING);
#endif

#if(_DCC_FUNCTION == _ON)
    ScalerColorDCCSetEffectiveRegion(enumSelRegion, _DB_APPLY_NO_POLLING);
#endif

#if((_ICM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON) || (_ICM_BRI_SUPPORT == _ON) || (_SCM_SUPPORT == _ON))
    ScalerColorICMSCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NO_POLLING);
#endif

    switch(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()))
    {
        case _COLOREFFECT_STANDARD:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
#endif
            break;

        case _COLOREFFECT_USER:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
            for(ucIndex = 0; ucIndex < 6; ucIndex++)
            {
                SET_OSD_SIX_COLOR(ucIndex);
                OsdDisplaySixColorGetOneColor(enumSelRegion, ucIndex);
                ScalerColorSixColorAdjust(enumSelRegion, ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
            }

            ScalerColorSixColorInitial(enumSelRegion);
#endif
            break;

        case _COLOREFFECT_MOVIE:
        case _COLOREFFECT_GAME:
        case _COLOREFFECT_PHOTO:
        case _COLOREFFECT_VIVID:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
#endif

#if(_DCC_FUNCTION == _ON)
            UserAdjustDCC(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            ScalerColorSetDCCAutoModeRegion(g_enumDCCMeasureRegion);
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
            UserAdjustSCM(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
#endif

#if(_ICM_SUPPORT == _ON)
            UserAdjustICM(enumSelRegion, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
#endif
            break;

        default:
            break;
    }

    switch(GET_OSD_COLOR_EFFECT(GET_OSD_INVERSE_REGION()))
    {
        case _COLOREFFECT_STANDARD:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _OFF);
#endif
            break;

        case _COLOREFFECT_USER:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _OFF);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
            for(ucIndex = 0; ucIndex < 6; ucIndex++)
            {
                SET_OSD_SIX_COLOR(ucIndex);
                OsdDisplaySixColorGetOneColor(enumSelRegionInverse, ucIndex);
                ScalerColorSixColorAdjust(enumSelRegionInverse, ucIndex, GET_OSD_SIX_COLOR_HUE(), GET_OSD_SIX_COLOR_SATURATION());
            }

            ScalerColorSixColorInitial(enumSelRegionInverse);
#endif
            break;

        case _COLOREFFECT_MOVIE:
        case _COLOREFFECT_GAME:
        case _COLOREFFECT_PHOTO:
        case _COLOREFFECT_VIVID:
#if(_DCC_FUNCTION == _ON)
            ScalerColorDCCRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
#endif

#if(_ICM_SUPPORT == _ON)
            ScalerColorICMSCMRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
#endif

#if(_DCC_FUNCTION == _ON)
            UserAdjustDCC(enumSelRegionInverse, GET_OSD_COLOR_EFFECT(GET_OSD_INVERSE_REGION()));
            ScalerColorSetDCCAutoModeRegion(g_enumDCCMeasureRegion);
#endif

// Adjust SCM Table, Should before ICM Adjust
#if(_SCM_SUPPORT == _ON)
            UserAdjustSCM(enumSelRegionInverse, GET_OSD_COLOR_EFFECT(GET_OSD_INVERSE_REGION()));
#endif

#if(_ICM_SUPPORT == _ON)
            UserAdjustICM(enumSelRegionInverse, GET_OSD_COLOR_EFFECT(GET_OSD_INVERSE_REGION()));
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : User adjust display mode function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustDisplayMode(void)
{
#if(_ULTRA_HDR_SUPPORT == _ON)
    if((GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()) != _HDR_MODE_OFF)&&(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P))
    {
        SET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort(),_HDR_MODE_OFF);
    }
#endif

    // Load user data
    RTDNVRamSaveOsdUserData();
    RTDNVRamLoadOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
    RTDNVRamLoadOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)// alant debug
    // Disable HLW
    //SET_OSD_HLWIN_TYPE(_HL_WIN_OFF);
    UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());//(_HL_WIN_OFF);
    ScalerColorHLWSetting(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING);
#endif

    // Adjust display mode
    UserCommonAdjustDisplayMode(UserInterfaceGetMultiDisplayMode());
}

//--------------------------------------------------
// Description  : User adjust display region function
// Input Value  : enumSelRegion --> target select region
//                enumSourceSearchPort --> target input port
// Output Value : None
//--------------------------------------------------
void UserAdjustRegionInputPort(EnumDisplayRegion enumDisplayRegion, EnumSourceSearchPort enumSourceSearchPort)
{
    // Save user display mode data
    RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());

    // Adjust display region
    UserCommonAdjustRegionInputPort(enumDisplayRegion, enumSourceSearchPort);

    // Update LED status
    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) == 0X00)
    {
        UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);
    }
}

#if(_2P_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Swap input port in 2P mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustSwapInputPort(void)
{
    EnumDisplayRegion enumAutoSearchTargetRegion = UserInterfaceGetAutoSearchTarget();
    EnumDisplayRegion enumRegion0 = 0x00;
    EnumDisplayRegion enumRegion1 = 0x00;
    EnumSourceSearchPort enumPort0 = 0x00;
    EnumSourceSearchPort enumPort1 = 0x00;

    switch(SysModeGetDisplayMode())
    {
#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PIP:
            enumRegion0 = _DISPLAY_RGN_MAIN;
            enumRegion1 = _DISPLAY_RGN_SUB;
            break;
#endif

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_LR:
            enumRegion0 = _DISPLAY_RGN_LEFT;
            enumRegion1 = _DISPLAY_RGN_RIGHT;
            break;
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_PBP_TB:
            enumRegion0 = _DISPLAY_RGN_TOP;
            enumRegion1 = _DISPLAY_RGN_BOTTOM;
            break;
#endif

        default:
            return;
    }

    // Enable background
    ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, _DISPLAY_PATH_ALL);
    ScalerDDomainBackgroundEnable(ScalerRegionGetDisplayDataPath(enumRegion0), _ENABLE);
    ScalerDDomainBackgroundEnable(ScalerRegionGetDisplayDataPath(enumRegion1), _ENABLE);

    // Reset data path for I/M/D domains
    SysModeResetDisplayState(enumRegion0);
    SysModeResetDisplayState(enumRegion1);
    ScalerIDomainResetDataPath(ScalerRegionGetInputDataPath(enumRegion0));
    ScalerIDomainResetDataPath(ScalerRegionGetInputDataPath(enumRegion1));

    // Set region input port
    enumPort0 = SysRegionGetPortType(enumRegion0);
    enumPort1 = SysRegionGetPortType(enumRegion1);

    // Swap region input ports in global variables
    SysRegionUpdateInterface(enumRegion0, _NO_INPUT_PORT);
    SysRegionUpdateInterface(enumRegion1, _NO_INPUT_PORT);
    SysRegionUpdateInterface(enumRegion0, enumPort1);
    SysRegionUpdateInterface(enumRegion1, enumPort0);

    // Swap region input ports in NVRAM
    enumPort0 = UserCommonNVRamGetSystemData(_SEARCH_PORT_0);
    enumPort1 = UserCommonNVRamGetSystemData(_SEARCH_PORT_1);
    UserCommonNVRamSetSystemData(_SEARCH_PORT_0, enumPort1);
    UserCommonNVRamSetSystemData(_SEARCH_PORT_1, enumPort0);

    // Update auto search target
    SysSourceSetMultiAutoSearchTarget(enumAutoSearchTargetRegion);

    if(enumAutoSearchTargetRegion != _DISPLAY_RGN_NONE)
    {
        // Switch to auto target region
        SysSourceSwitchInputPort(SysRegionGetPortType(enumAutoSearchTargetRegion));
    }
    else
    {
        // Switch to region 0
        SysSourceSwitchInputPort(SysRegionGetPortType(enumRegion0));
    }

    // Save system data
    UserCommonNVRamSaveSystemData();
}
#endif // End of #if(_2P_DISPLAY_SUPPORT == _ON)

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumSelRegion UserAdjustConvertSystemSelectRegion(BYTE ucRegion)
{
    if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
    {
        switch(GET_OSD_DISPLAY_MODE())
        {
            case _OSD_DM_1P:
                return _1P_NORMAL_DEMO_INSIDE;

            case _OSD_DM_2P_LR:
                return _PBP_LR_DEMO_INSIDE;

            case _OSD_DM_2P_PIP:
                return _PIP_DEMO_INSIDE;

            case _OSD_DM_2P_TB:
                return _PBP_TB_DEMO_INSIDE;

            case _OSD_DM_4P:
                return _4P_DEMO_INSIDE;

            default:
                break;
        }
    }

    switch(GET_OSD_DISPLAY_MODE())
    {
        case _OSD_DM_1P:
            return _1P_NORMAL_FULL_REGION;

        case _OSD_DM_2P_LR:
            if(ucRegion == _OSD_SR_2P_LR_L)
            {
                return _PBP_LR_L;
            }
            else if(ucRegion == _OSD_SR_2P_LR_R)
            {
                return _PBP_LR_R;
            }
            else
            {
                return _PBP_LR_FULL_REGION;
            }

        case _OSD_DM_2P_PIP:
            if(ucRegion == _OSD_SR_2P_PIP_MAIN)
            {
                return _PIP_MAIN;
            }
            else if(ucRegion == _OSD_SR_2P_PIP_SUB)
            {
                return _PIP_SUB;
            }
            else
            {
                return _PIP_FULL_REGION;
            }

        case _OSD_DM_2P_TB:
            if(ucRegion == _OSD_SR_2P_TB_T)
            {
                return _PBP_TB_T;
            }
            else if(ucRegion == _OSD_SR_2P_TB_B)
            {
                return _PBP_TB_B;
            }
            else
            {
                return _PBP_TB_FULL_REGION;
            }

        case _OSD_DM_4P:
            switch(ucRegion)
            {
                case _OSD_SR_4P_LT_INSIDE:
                    return _4P_LT;
                case _OSD_SR_4P_LT_OUTSIDE:
                    return _4P_LT_OUTSIDE;
                case _OSD_SR_4P_RT_INSIDE:
                    return _4P_RT;
                case _OSD_SR_4P_RT_OUTSIDE:
                    return _4P_RT_OUTSIDE;
                case _OSD_SR_4P_LB_INSIDE:
                    return _4P_LB;
                case _OSD_SR_4P_LB_OUTSIDE:
                    return _4P_LB_OUTSIDE;
                case _OSD_SR_4P_RB_INSIDE:
                    return _4P_RB;
                case _OSD_SR_4P_RB_OUTSIDE:
                    return _4P_RB_OUTSIDE;
                case _OSD_SR_4P_FULL:
                default:
                    return _4P_FULL_REGION;
            }

        default:
            break;
    }

    return _NON_REGION;
}
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDisplayRegion UserAdjustConvertDisplayRegion(BYTE ucRegion)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        case _OSD_DM_1P:
            return _DISPLAY_RGN_1P;
            break;

        case _OSD_DM_2P_LR:
            if(ucRegion == _OSD_SR_2P_LR_L)
            {
                return _DISPLAY_RGN_LEFT;
            }
            else if(ucRegion == _OSD_SR_2P_LR_R)
            {
                return _DISPLAY_RGN_RIGHT;
            }
            return _DISPLAY_RGN_LEFT;
            break;

        case _OSD_DM_2P_PIP:
            if(ucRegion == _OSD_SR_2P_PIP_MAIN)
            {
                return _DISPLAY_RGN_MAIN;
            }
            else if(ucRegion == _OSD_SR_2P_PIP_SUB)
            {
                return _DISPLAY_RGN_SUB;
            }
            return _DISPLAY_RGN_MAIN;
            break;

        case _OSD_DM_2P_TB:
            if(ucRegion == _OSD_SR_2P_TB_T)
            {
                return _DISPLAY_RGN_TOP;
            }
            else if(ucRegion == _OSD_SR_2P_TB_B)
            {
                return _DISPLAY_RGN_BOTTOM;
            }
            return _DISPLAY_RGN_TOP;
            break;
        case _OSD_DM_4P:
            switch(ucRegion)
            {
                case _OSD_SR_4P_LT_INSIDE:
                default:
                    return _DISPLAY_RGN_LT;
                case _OSD_SR_4P_RT_INSIDE:
                    return _DISPLAY_RGN_RT;
                case _OSD_SR_4P_LB_INSIDE:
                    return _DISPLAY_RGN_LB;
                case _OSD_SR_4P_RB_INSIDE:
                    return _DISPLAY_RGN_RB;
                    break;
            }
            break;
        default:
            break;
    }

    return _DISPLAY_RGN_NONE;
}

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
 EnumSourceSearchPort UserAdjustGetSelectRegionPort(void)
{
    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
        case _OSD_DM_1P:
            return SysRegionGetPortType(_DISPLAY_RGN_1P);

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_LR:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_2P_LR_L:
                    return SysRegionGetPortType(_DISPLAY_RGN_LEFT);
                case _OSD_SR_2P_LR_R:
                    return SysRegionGetPortType(_DISPLAY_RGN_RIGHT);
            }
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_TB:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_2P_TB_T:
                    return SysRegionGetPortType(_DISPLAY_RGN_TOP);
                case _OSD_SR_2P_TB_B:
                    return SysRegionGetPortType(_DISPLAY_RGN_BOTTOM);
            }
#endif

#if(_PIP_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_2P_PIP:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_2P_PIP_MAIN:
                    return SysRegionGetPortType(_DISPLAY_RGN_MAIN);
                case _OSD_SR_2P_PIP_SUB:
                    return SysRegionGetPortType(_DISPLAY_RGN_SUB);
            }
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _OSD_DM_4P:
            switch(GET_OSD_SELECT_REGION())
            {
                default:
                case _OSD_SR_4P_LT_INSIDE:
                    return SysRegionGetPortType(_DISPLAY_RGN_LT);
                case _OSD_SR_4P_LB_INSIDE:
                    return SysRegionGetPortType(_DISPLAY_RGN_LB);
                case _OSD_SR_4P_RT_INSIDE:
                    return SysRegionGetPortType(_DISPLAY_RGN_RT);
                case _OSD_SR_4P_RB_INSIDE:
                    return SysRegionGetPortType(_DISPLAY_RGN_RB);
            }
#endif
    }
}

#if((_OGC_SUPPORT == _ON) || (_PCM_FUNCTION == _ON))
//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE UserAdjustGetOSDSelectRegion(EnumSelRegion enumSelRegion)
{
    EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION());

    switch(GET_OSD_DISPLAY_MODE())
    {
        default:
        case _OSD_DM_1P:
            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                return GET_OSD_INVERSE_REGION();
            }

        case _OSD_DM_2P_TB:
        case _OSD_DM_2P_LR:
        case _OSD_DM_2P_PIP:

            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _PIP_FULL_REGION:
                    case _PBP_LR_FULL_REGION:
                    case _PBP_TB_FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                        break;
                }
                return GET_OSD_INVERSE_REGION();
            }

        case _OSD_DM_4P:

            if(GET_OSD_SYSTEM_SELECT_REGION() == enumSelRegion)
            {
                return GET_OSD_SELECT_REGION();
            }
            else
            {
                switch(GET_OSD_SYSTEM_SELECT_REGION())
                {
                    case _4P_LT_OUTSIDE:
                    case _4P_LB_OUTSIDE:
                    case _4P_RT_OUTSIDE:
                    case _4P_RB_OUTSIDE:

                        if(enumSelRegionInverse == enumSelRegion)
                        {
                            return GET_OSD_INVERSE_REGION();
                        }
                        else
                        {
                            return GET_OSD_SELECT_REGION();
                        }

                    case _4P_FULL_REGION:
                        return GET_OSD_SELECT_REGION();

                    default:
                    case _4P_LT:
                    case _4P_LB:
                    case _4P_RT:
                    case _4P_RB:
                    case _4P_DEMO_INSIDE:
                    case _4P_DEMO_OUTSIDE:
                        return GET_OSD_INVERSE_REGION();
                }
            }
    }
}
#endif // End of #if((_OGC_SUPPORT == _ON) || _OCC_SUPPORT == _ON))

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//--------------------------------------------------
// Description  : Set IR Table
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjusIR(void)
{
    ScalerIRHWModeDecoder(tIR_INITIAL_TABLE, GET_CURRENT_BANK_NUMBER());
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)

//--------------------------------------------------
// Description  : DP EDID Switch
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserAdjustDpEdidTableSwitch(BYTE ucSelectedPort)
{
#if(_EMBEDDED_EDID_SUPPORT == _ON)

    switch(ucSelectedPort)
    {
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)

        case _D7_INPUT_PORT:

            if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
            {
                if((SysSourceGetInputPort() == _D7_INPUT_PORT) ||
                   ((SysSourceGetInputPort() != _D0_INPUT_PORT) &&
                    (SysSourceGetInputPort() != _D1_INPUT_PORT) &&
                    (UserInterfaceGetDpDualDefaultPort() == _TRUE)))
                {
                    UserCommonInterfaceInputPortLoadEdidData(_D7_INPUT_PORT_EDID);
                    ScalerDpEdidSwitch(_D7_INPUT_PORT);
                }
            }

            break;
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

        case _D0_INPUT_PORT:

            UserCommonInterfaceInputPortLoadEdidData(_D0_INPUT_PORT_EDID);
            ScalerDpEdidSwitch(_D0_INPUT_PORT);

            break;
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

        case _D1_INPUT_PORT:

            UserCommonInterfaceInputPortLoadEdidData(_D1_INPUT_PORT_EDID);
            ScalerDpEdidSwitch(_D1_INPUT_PORT);

            break;
#endif

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)

        case _D6_INPUT_PORT:

            UserCommonInterfaceInputPortLoadEdidData(_D6_INPUT_PORT_EDID);
            ScalerDpEdidSwitch(_D6_INPUT_PORT);

            break;
#endif

        default:

            break;
    }
/////////////////////////////////////////////
#else
       	switch(ucSelectedPort)
		{
		   default:

            break;
		
		}
#endif
}

#if(_FALSE_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Do User Define False Color
// Input Value  : enumSelRegion:Selected Region, ucLevel:adjust level 0-16, ucColorCodeLast: last Color Code
//                ucColorCodeCur:Current Color Code, ucColorCodeNext:Next Color Code
// Output Value : None
//--------------------------------------------------
void UserAdjustFalseColorUserDefine(EnumSelRegion enumSelRegion, BYTE ucLevel, BYTE ucColorCodeLast, BYTE ucColorCodeCur, BYTE ucColorCodeNext)
{
    UserCommonAdjustFalseColorEnable(enumSelRegion, _FUNCTION_OFF);
    UserCommonAdjustFalseColorAdjust(enumSelRegion, ucLevel, ucColorCodeLast, ucColorCodeCur, ucColorCodeNext);
    UserCommonAdjustFalseColorEnable(enumSelRegion, _FUNCTION_ON);
}

//--------------------------------------------------
// Description  : Adjust False Color by fixed OG LUT OR Update all False color
// Input Value  : enumSelRegion:Selected Region, ucMode: Mode in OSD
// Output Value : None
//--------------------------------------------------
void UserAdjustFalseColor(EnumSelRegion enumSelRegion, BYTE ucMode)
{
    BYTE ucI = 0;
    switch(ucMode)
    {
        case _OSD_FALSE_COLOR_USER:  // Update all user define effect

            UserCommonAdjustFalseColorEnable(enumSelRegion, _FUNCTION_OFF);
            UserCommonAdjustFalseColorAdjust(enumSelRegion, 0, GET_OSD_FALSE_COLOR_LEVEL(0), GET_OSD_FALSE_COLOR_LEVEL(0), GET_OSD_FALSE_COLOR_LEVEL(1));

            for(ucI = 2; ucI < (_FALSE_COLOR_ADJUSTABLE_MAX); ucI = ucI + 2)
            {
                UserCommonAdjustFalseColorAdjust(enumSelRegion, ucI, GET_OSD_FALSE_COLOR_LEVEL(ucI - 1), GET_OSD_FALSE_COLOR_LEVEL(ucI), GET_OSD_FALSE_COLOR_LEVEL(ucI + 1));
            }
            UserCommonAdjustFalseColorAdjust(enumSelRegion, _FALSE_COLOR_ADJUSTABLE_MAX, GET_OSD_FALSE_COLOR_LEVEL(_FALSE_COLOR_ADJUSTABLE_MAX - 1), GET_OSD_FALSE_COLOR_LEVEL(_FALSE_COLOR_ADJUSTABLE_MAX), GET_OSD_FALSE_COLOR_LEVEL(_FALSE_COLOR_ADJUSTABLE_MAX));

            UserCommonAdjustFalseColorEnable(enumSelRegion, _FUNCTION_ON);

            break;

        case _OSD_FALSE_COLOR_MODE1:
        case _OSD_FALSE_COLOR_MODE2:
        case _OSD_FALSE_COLOR_MODE3:

            UserCommonAdjustFalseColorEnable(enumSelRegion, _FUNCTION_OFF);
            UserCommonAdjustFalseColorModeChange(enumSelRegion, tOGFALSECOLOR_TABLE[(ucMode - 1) % 3], GET_CURRENT_BANK_NUMBER());
            UserCommonAdjustFalseColorEnable(enumSelRegion, _FUNCTION_ON);
            break;

        case _OSD_FALSE_COLOR_OFF:
        default:
            UserCommonAdjustFalseColorEnable(enumSelRegion, _FUNCTION_OFF);
            break;
    }
}
#endif // end of #if(_FALSE_COLOR_SUPPORT == _ON)

////////////////
// new function
/////////////
void RTDFactoryBurnInPattern(void)
{
    BYTE code tPatternBurnIn[3][5] =
    {
        {255, 0, 255, 0, 0},
        {255, 0, 0, 255, 0},
        {255, 0, 0, 0, 255},
    };
      static BYTE g_ucColorTempBurnin = 0;

	 ScalerDDomainBackgroundEnable(_DISPLAY_PATH_ALL, _ENABLE);//  ScalerDDomainBackgroundEnable(_ENABLE);
				
     UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
	 UserInterfaceKeyPadLedControl(_LED_POWER_ON);

     ScalerTimerWaitForEvent(_EVENT_DEN_STOP);

    ScalerDDomainBackgroundSetColor(_DISPLAY_PATH_ALL,tPatternBurnIn[0][g_ucColorTempBurnin%0x05], tPatternBurnIn[1][g_ucColorTempBurnin%0x05], tPatternBurnIn[2][g_ucColorTempBurnin%0x05]);
    g_ucColorTempBurnin++;
  ScalerTimerActiveTimerEvent(SEC(5), _USER_TIMER_EVENT_BURN_IN);
}

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
