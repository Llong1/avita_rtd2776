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
// ID Code      : RTD2014Osd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSD__

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
StructOsdInfo g_stOsdInfo;

WORD g_usAdjustValue;
WORD g_usBackupValue;
WORD g_usItemNum;

BYTE g_ucLogoTimerCounter;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserOsdHandler(void);
void RTDOsdSystemFlowProc(void);
void RTDOsdEventMsgProc(void);

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserOsdHandler(void)
{
    RTDOsdSystemFlowProc();
    RTDOsdEventMsgProc();
}

//--------------------------------------------------
// Description  : OSD system flow
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdSystemFlowProc(void)
{
    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            break;

        case _MODE_STATUS_INITIAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
#if(_FREESYNC_OD_MEASURE == _ON)
                UserAdjustFREESYNCODMeasure();
#endif

#if 0 // disable logo
			OsdDispShowLogo();
			UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
			ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE_OSD_LOGO);
#else
			OsdDispDisableOsd();
			SET_OSD_LOGO_ON(_OFF);
				
#endif

            }

            break;

        case _MODE_STATUS_DISPLAY_INITIAL:

            if(SysModeGetModeStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);
                }
            }

            break;

        case _MODE_STATUS_DISPLAY_SETTING:
        case _MODE_STATUS_DISPLAY_CHECK:

            // Polling display state change
            if(SysRegionCheckUserDisplayStateChange() == _TRUE)
            {
                if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
                {
                    // Update LED status
                    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_ACTIVE) == 0X00)
                    {
                        UserInterfaceKeyPadLedControl(_LED_POWER_SEARCH);
#if(_FREEZE_SUPPORT == _ON)
                        if(GET_OSD_FREEZE_STATUS() == _ON)
                        {
                            SET_OSD_FREEZE_STATUS(_OFF);
                        }
#endif
                    }
                    else
                    {
                        UserInterfaceKeyPadLedControl(_LED_POWER_ACTIVE);
                    }
                }

                // Perform display state change actions
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
                {
                    switch(SysRegionGetDisplayState(_DISPLAY_RGN_1P))
                    {
                        case _DISPLAY_STATE_NO_SIGNAL:

                            // Check NSG to PS condition in single display
                            if(SysSourceGetCableDetect(UserCommonNVRamGetSystemData(_SEARCH_PORT_0)) == _TRUE)
                            {
                                ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
                            }
                            else
                            {
                                ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
                            }
                            break;

                        case _DISPLAY_STATE_OOR:

                            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_NOSUPPORT_MSG);
                            break;

                        default:
                            break;
                    }
                }
#if(_MULTI_DISPLAY_MAX != 0X01)
                else
                {
                    EnumDisplayRegion enumIndexRegion = _DISPLAY_RGN_NONE;
                    BYTE ucIndex = 0x00;
                    BYTE ucMaxIndex = SysRegionGetDisplayStateCount(_DISPLAY_STATE_MAX);

                    // Check separate display state
                    for(ucIndex = 0x00; ucIndex < ucMaxIndex; ++ucIndex)
                    {
                        enumIndexRegion = SysRegionGetDisplayRegion(ucIndex);

                        if(SysRegionCheckDisplayEvent(enumIndexRegion, _DISPLAY_EVENT_STATE_CHANGE_USR) == _TRUE)
                        {
                            switch(SysRegionGetDisplayState(enumIndexRegion))
                            {
                                case _DISPLAY_STATE_NO_SIGNAL:
                                case _DISPLAY_STATE_OOR:
                                case _DISPLAY_STATE_NONE:
                                    if((GET_OSD_STATE() == _MENU_NONE) ||
                                       (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION))
                                    {
                                        OsdDispMpUpdateDisplayStateNotice(_OFF, enumIndexRegion);
                                        ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
                                    }
                                    break;

                                default:
                                    break;
                            }
                        }
                    }

                    // Check NSG to PS condition in multi-display
                    if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)
                    {
                        if((GET_OSD_STATE() != _MENU_NONE) &&
                           (GET_OSD_STATE() != _MENU_HOTKEY_INFORMATION))
                        {
                            OsdDispDisableOsd();
                        }

                        ScalerTimerActiveTimerEvent(SEC(6), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
                    }
                }
#endif // End of #if(_MULTI_DISPLAY_MAX != 0X01)
            }

#if(_DCR_SUPPORT == _ON)
            if(GET_OSD_DCR_STATUS() == _ON)
            {
                if((SysModeGetDisplayMode() == _DISPLAY_MODE_1P) &&
                   (SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_ACTIVE))
                {
                    UserCommonAdjustDCR();
                }
            }
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)

            if(GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()) == _HDR_MODE_AUTO)
            {
                if((SysModeGetDisplayMode() != _DISPLAY_MODE_4P) && (SysRegionGetDisplayState(GET_OSD_SYSTEM_DISPLAY_REGION()) == _DISPLAY_STATE_ACTIVE))//By Jerry -2016-10-03//
                {
                    switch(UserCommonAdjustHDRTargetStatus(GET_OSD_SYSTEM_DISPLAY_REGION()))
                    {
                        case _HDR_TARGET_STATUS_SMPTE_ST_2084:

                            UserCommonAdjustHDRAutoMode(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
                            UserAdjustBacklight(_BACKLIGHT_MAX); // Must!!!!
                            break;

                        case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:

                            OsdFuncColorPcmAdjust();
                            UserAdjustBacklight(GET_OSD_BACKLIGHT());
                            break;

                        case _HDR_TARGET_STATUS_DO_NOTHING:
                        default:
                            break;
                    }
                }
            }
#endif

            break;

        case _MODE_STATUS_POWER_SAVING:

            if(SysSourceGetCableStatusChange(SysSourceGetInputPort()) == _TRUE)// when cable ststua change, continue source handler.
            {
                SET_FORCE_POW_SAV_STATUS(_FALSE);
            }

            if(SysPowerGetPowerStatus() == _POWER_STATUS_NORMAL)
            {
                if(GET_OSD_POWER_SAVING_SHOW_SOURCE() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_SOURCE(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG);
                }
                else if(GET_OSD_WAKE_UP_SWITCH_DDCCI_PORT() == _TRUE)
                {
                    SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG);
                }
                else if(GET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_DISPLAY_MODE(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_DISPLAY_MODE_MENU_MSG);
                }
#if(_DP_SUPPORT == _ON)
                else if(GET_OSD_POWER_SAVING_SHOW_DP_OPTION() == _TRUE)
                {
                    SET_OSD_POWER_SAVING_SHOW_DP_OPTION(_FALSE);

                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SHOW_DP_VERSION_MSG);
                }
#endif
            }

            break;

        case _MODE_STATUS_FACTORY:

            break;

        default:

            break;
    }

    switch(SysModeGetModeState())
    {
        case _MODE_STATUS_POWER_OFF:
        case _MODE_STATUS_INITIAL:
        case _MODE_STATUS_DISPLAY_INITIAL:

            // Skip key process check in off, initial, and display initial states
            return;

        default:

            if(GET_KEYMESSAGE() < _KEY_AMOUNT)
            {
                // Set repeat-key enable
                if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) ||
                   (SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
                {
                    if((GET_OSD_STATE() != _MENU_NONE) &&
                       ((GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE) || (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)))
                    {
                        SET_KEYREPEATENABLE();
                    }
                }

                if(GET_OSD_IN_FACTORY_MENU_STATUS() == _TRUE)
                {
                    RTDFactoryMenuOperation();
                    ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                }
                else
                {
#if(_FREEZE_SUPPORT == _ON)
                    if(OsdFuncCheckFreezeDisableMsg() == _TRUE)
                    {
                        break;
                    }
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
                    if(OsdFuncCheckFalseColorDisableMsg() == _TRUE)
                    {
                        break;
                    }
#endif
                    // back up previous OSD State
                    SET_OSD_STATE_PREVIOUS(GET_OSD_STATE());

#if(_FREEZE_SUPPORT == _ON)
                    if(OsdFuncCheckFreezeDisable() == _TRUE) // Confirm whether disable the freeze status
                    {
                        break;
                    }
#endif
                    if((GET_OSD_STATE() > _MENU_NONE) &&
                       (GET_OSD_STATE() < _MENU_HOTKEY_DDCCI))
                    {
                        OsdDispMainMenuKeyInfo(GET_KEYMESSAGE(), _OSD_HIGHLIGHT);
                    }

                    // Perform OSD action
                    (*OperationTable[GET_OSD_STATE()])();

                    // Reactive OSD disable event in check state
                    if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (GET_OSD_IN_FACTORY_MENU_STATUS() != _TRUE))
                    {
                        if(GET_OSD_TIME_OUT() <= _OSD_TIMEOUT_MIN)
                        {
                            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE);
                        }
                        else
                        {
                            ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
                        }
                    }


#if(_FALSE_COLOR_SUPPORT == _ON)
                    if(OsdFuncCheckFalseColorDisable() == _TRUE) // Confirm whether disable the False Color status
                    {
                        break;
                    }
#endif
                }
            }
            break;
    }
}

//--------------------------------------------------
// Description  : OSD event message processing function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void RTDOsdEventMsgProc(void)
{
    switch(GET_OSD_EVENT_MESSAGE())
    {
        case _OSDEVENT_SHOW_NOSIGNAL_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOSIGNAL_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            //ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOCABLE_MSG:
            OsdDispOsdMessage(_OSD_DISP_NOCABLE_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            //ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_NOSUPPORT_MSG:
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);

            OsdDispOsdMessage(_OSD_DISP_NOSUPPORT_MSG);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            //ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_SHOW_POWER_SAVING);
            break;

        case _OSDEVENT_SHOW_CHANGE_SOURCE_MENU_MSG:
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            OsdDispHotKeySourceMenu();

            //ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            break;

        case _OSDEVENT_SHOW_DISPLAY_MODE_MENU_MSG: // wake up show display mode
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            OsdDispHotKeyDisplayModeMenu();
            //ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            break;

        case _OSDEVENT_WAKE_UP_SWITCH_DDCCI_PORT_MSG: // wake up show DDCCI

            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_CABLE);
            ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_OSD_SHOW_NO_SIGNAL);
            SET_OSD_STATE(_MENU_HOTKEY_DDCCI);
            OsdDispHotKeyOptionMenu(_HOTKEY_DDCCI);
            //ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

            break;

        case _OSDEVENT_SHOW_POWER_SAVING_EVENT_MSG:

            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                // OsdDispDisableOsd();
                OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);
                UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

               // ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            }
            else
            {
                // For multi-display, show PS message only when all NSG
                if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _FALSE)
                {
                    break;
                }
                else
                {
                    // OsdDispDisableOsd();
                    OsdDispOsdMessage(_OSD_DISP_POWER_SAVING_MSG);
                    UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);

                  //  ScalerTimerActiveTimerEvent(SEC(2), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
                }
            }

            break;

        case _OSDEVENT_GO_TO_POWER_SAVING_EVENT_MSG:

            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                OsdDispDisableOsd();

                if(SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_OOR)
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NOSUPPORT_SAVING);
                }
                else
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
                }
            }
            else
            {
                // For multi-display, go to PS only when all NSG
                if(SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _FALSE)
                {
                    break;
                }
                else
                {
                    OsdDispDisableOsd();

                    if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) != 0x00)
                    {
                        SysPowerSetTargetPowerStatus(_POWER_STATUS_NOSUPPORT_SAVING);
                    }
                    else
                    {
                        SysPowerSetTargetPowerStatus(_POWER_STATUS_SAVING);
                    }
                }
            }

            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_DO_AUTO_CONFIG_MSG:
#if(_FREEZE_SUPPORT == _ON)
            ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif
            OsdDispAutoConfigProc();
            break;
#endif

        case _OSDEVENT_SHOW_FAIL_SAFE_MODE_MSG:
            if((GET_OSD_STATE() == _MENU_NONE) || (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION))
            {
                OsdDispMpUpdateDisplayStateNotice(_OFF, _DISPLAY_RGN_NONE);
                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            break;

        case _OSDEVENT_ACTIVE_DO_ONE_TIME_MSG:

#if(_FREEZE_SUPPORT == _ON)
            ScalerTimerWaitForActiveTimerEvent(_USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
#endif

#if(_VGA_SUPPORT == _ON)
            if(SysRegionGetPortType(SysModeGetDisplayTarget()) == _A0_INPUT_PORT)
            {
                if(UserInterfaceGetFirstAutoConfigStatus() == _TRUE)
                {
                    OsdDispAutoConfigProc();
                }
            }
#endif

            if((GET_OSD_STATE() == _MENU_NONE) || (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION))
            {
                OsdDispMpUpdateDisplayStateNotice(_OFF, _DISPLAY_RGN_NONE);
                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            break;

        case _OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG:
            UserCommonNVRamSaveSystemData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG:
            UserCommonNVRamSaveModeUserData();
            break;
#endif
        case _OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG:
            RTDNVRamSaveOsdUserData();
            break;

#if(_VGA_SUPPORT == _ON)
        case _OSDEVENT_SAVE_NVRAM_ADCDATA_MSG:
            if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace(_A0_INPUT_PORT)) == _TRUE)
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
            }
            else
            {
                UserCommonNVRamSaveADCSetting(_COLOR_SPACE_RGB);
            }
            break;
#endif

        case _OSDEVENT_SAVE_NVRAM_COLORPROC_MSG:
            RTDNVRamSaveColorSetting(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            break;

        case _OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG:
            RTDNVRamSaveOsdInputPortData(UserAdjustGetSelectRegionPort());
            break;

        case _OSDEVENT_SAVE_NVRAM_INPUTSOURCEDATA_MSG:
            RTDNVRamSaveOsdInputSourceData(SysRegionGetSourceType(GET_OSD_SYSTEM_DISPLAY_REGION()));
            break;

        case _OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG:
            RTDNVRamSaveOsdRegionData(GET_OSD_DISPLAY_MODE(), GET_OSD_SELECT_REGION());
            break;


        case _OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG:
            RTDNVRamSaveOsdDisplayModeData(GET_OSD_DISPLAY_MODE());
            break;

        case _OSDEVENT_SHOW_MP_NOSIGNAL_NOCABLE_MSG:
            if(((GET_OSD_STATE() == _MENU_NONE) ||
                (GET_OSD_STATE() == _MENU_HOTKEY_INFORMATION)) &&
               (SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK))
            {
                OsdDispMpUpdateDisplayStateNotice(_OFF, _DISPLAY_RGN_NONE);
                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            break;

#if(_DP_SUPPORT == _ON)

        case _OSDEVENT_SHOW_DP_VERSION_MSG:

            g_usItemNum= _MENU_NONE;
            OsdFuncDisableOsd();
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
#endif
            OsdDispMainMenu();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DP_OPTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
#endif
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_1_DOT_X);

            UserCommonInterfacePanelPowerAction(_BACKLIGHT_ON);
            ScalerTimerActiveTimerEvent(SEC(4), _USER_TIMER_EVENT_OSD_DISABLE);

            break;
#endif

        default:
            break;
    }
    SET_OSD_EVENT_MESSAGE(_OSDEVENT_NONE_MSG);
}

void MenuNone(void)
{
    // OsdDispDisableOsd();

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) &&
               (SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _FALSE))
            {
                OsdDispDisableOsd();
                SET_OSD_STATE(_MENU_DISPLAYMODE);
                OsdFuncSetOsdItemFlag();
                OsdDispMainMenu();
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            // input source
            CLR_KEYREPEATENABLE();

            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_POWER_SAVING_SHOW_SOURCE(_TRUE);

                if((SysPowerGetPowerStatus() == _POWER_STATUS_SAVING) || (SysPowerGetPowerStatus() == _POWER_STATUS_NOSUPPORT_SAVING))
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            else if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdFuncShowSourceMenuCheck();

                OsdDispHotKeySourceMenu();
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) && (SysRegionGetDisplayState(_DISPLAY_RGN_1P) != _DISPLAY_STATE_ACTIVE)) ||
               ((GET_OSD_DISPLAY_MODE() != _OSD_DM_1P) && (SysRegionCheckAllDisplayState(_DISPLAY_STATE_NO_SIGNAL) == _TRUE)))
            {
                break;
            }
            else
            {
                // active show input information
                OsdDispMpUpdateDisplayStateNotice(_ON, _DISPLAY_RGN_NONE);
                ScalerTimerActiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            // auto adjust
#if(_VGA_SUPPORT == _ON)
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) &&
               (SysVgaGetRegion() != _DISPLAY_RGN_NONE) &&
               (GET_FAIL_SAFE_MODE(ScalerRegionGetIndex(SysVgaGetRegion())) == _FALSE) &&
               (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
#if(_FREEZE_SUPPORT == _ON)
                if(GET_OSD_FREEZE_STATUS() == _ON)
                {
                    SET_OSD_FREEZE_STATUS(_OFF);
                    UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
                    OsdDispOsdMessage(_OSD_DISP_DISABLE_FREEZE_MSG);
                    ScalerTimerActiveTimerEvent(SEC(1), _USER_TIMER_EVENT_OSD_DISABLE_FREEZE_MSG);
                }
#endif

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_DO_AUTO_CONFIG_MSG);
            }
#endif

            // ddcci
            if(SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)
            {
                SET_OSD_WAKE_UP_SWITCH_DDCCI_PORT(_TRUE);

                if((SysPowerGetPowerStatus() == _POWER_STATUS_SAVING) || (SysPowerGetPowerStatus() == _POWER_STATUS_NOSUPPORT_SAVING))
                {
                    SysPowerSetTargetPowerStatus(_POWER_STATUS_NORMAL);
                }
            }
            break;

        default:
            break;
    }
}

void MenuDisplayMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(GET_OSD_DISPLAY_MODE() + _MENU_DISPLAYMODE_1P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _SELECT, GET_OSD_DISPLAY_MODE());
            break;

        case _RIGHT_KEY_MESSAGE:
            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP))
            {
                SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            }
            else if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
            {
                SET_OSD_STATE(_MENU_SELECTREGION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_2P_TB);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                    }
                    else if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                    }
                    else
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                    }
                }
            }
            else
            {
                SET_OSD_STATE(_MENU_PICTURE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_FACTORY);
#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
            if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
               (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
            {
                OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdHeight, 5);
            }
            else
#endif
            {
                OsdFuncClearOsd(ROW(14), COL(0), g_ucOsdWidth, 5);
            }
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FACTORY_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuDisplayFunction(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
#if (_D_DOMAIN_PATH != _D_DOMAIN_4_PATH)
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_DISPLAYFUN_DISP_ROTATE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);

                if(GET_OSD_DISP_ROTATE() >= (_DISP_ROTATE_0 + 4))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
                }
#endif
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
#if (_D_DOMAIN_PATH != _D_DOMAIN_4_PATH)
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_DISPLAYFUN_LR_RATIO);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LR_RATIO, GET_OSD_PBP_LR_RATIO());
#else
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_DISPLAYFUN_LR_INPUT_SWAP);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
#endif
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_DISPLAYFUN_TB_INPUT_SWAP);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _UNSELECT, GET_OSD_PIP_POSITION_TYPE());
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
                OsdDispMainMenuIconPage(_DOWN, (_ICON_PAGE_PIP_POSITION_0 + (GET_OSD_PIP_POSITION_TYPE() / 4)));
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) || (GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF))
            {
                SET_OSD_STATE(_MENU_PICTURE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            }
            else
            {
                SET_OSD_STATE(_MENU_SELECTREGION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_2P_LR);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_2P_TB);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_2P_PIP);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                    }
                    else if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                    }
                    else
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                    }
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYMODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
            if(GET_OSD_DISPLAY_MODE() < _OSD_DM_4P)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_0);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuSelectRegion(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
                SET_OSD_STATE(_MENU_SELECTREGIOM_2P_LR_L + GET_OSD_SELECT_REGION());
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
            {
                SET_OSD_STATE(_MENU_SELECTREGIOM_2P_TB_T + GET_OSD_SELECT_REGION());
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
            {
                SET_OSD_STATE(_MENU_SELECTREGIOM_2P_PIP_MAIN + GET_OSD_SELECT_REGION());
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
            {
                SET_OSD_STATE(_MENU_SELECTREGIOM_4P_LT_IN + GET_OSD_SELECT_REGION());
            }

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _SELECT, GET_OSD_SELECT_REGION());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        case _LEFT_KEY_MESSAGE:
            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) || (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP))
            {
                SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            }
            else
            {
                SET_OSD_STATE(_MENU_DISPLAYMODE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                if(GET_OSD_DISPLAY_MODE() < _OSD_DM_4P)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuPicture(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {
#if (_SHARPNESS_SUPPORT == _ON)
                SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);
                OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()));
#endif

                return;
            }
#endif
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PICTURE_0);

            // OsdDispMainMenuKeyInfo(_KEY_INFO_BACK, _OSD_UNSELECT);
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ANALOG_0);
            break;

        case _LEFT_KEY_MESSAGE:
            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) ||
               ((GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF) &&
                ((GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR) ||
                 (GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP))))
            {
                SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            }
            else if(GET_OSD_HLWIN_TYPE() == _HL_WIN_OFF)
            {
                SET_OSD_STATE(_MENU_SELECTREGION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_2P_LR);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_2P_TB);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_2P_PIP);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                    }
                    else if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                    }
                    else
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                    }
                }
            }
            else
            {
                SET_OSD_STATE(_MENU_DISPLAYMODE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                if(GET_OSD_DISPLAY_MODE() < _OSD_DM_4P)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuAnalog(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(SysVgaGetRegion() != _DISPLAY_RGN_NONE)
            {
                if(SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE)
                {
                    SET_OSD_STATE(_MENU_ANALOG_AUTO);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ANALOG_0);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                }
            }
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuColor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {
                SET_OSD_STATE(_MENU_COLOR_EFFECT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));

                if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) >= _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
                }
                break;
            }
#endif

            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ANALOG_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuAdvance(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_ASPECT);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_0);
            OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _UNSELECT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));


            if(GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()) == _OSD_ASPECT_RATIO_ORIGIN)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
            }

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());

                if((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                   (GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_D7))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
                else if((GET_OSD_1P_INPUT_SOURCE() >= _OSD_INPUT_A0) &&
                        (GET_OSD_1P_INPUT_SOURCE() <= _OSD_INPUT_D2))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((GET_OSD_1P_INPUT_SOURCE() >= _OSD_INPUT_D3) &&
                        (GET_OSD_1P_INPUT_SOURCE() <= _OSD_INPUT_D6))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
            }
            else
            {
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_LR);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_TB);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_PIP);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_4P);
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuInput(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                g_usBackupValue = GET_OSD_1P_INPUT_SOURCE();
                SET_OSD_STATE(_MENU_INPUT_SOURCE_1P_ADJ);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _SELECT, GET_OSD_1P_INPUT_SOURCE());
            }
            else
            {
                g_usItemNum = GET_OSD_STATE_PREVIOUS();
                SET_OSD_STATE(_MENU_INPUT_SOURCE_1P);
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
                OsdDispHotKeySourceMenuIcon(GET_OSD_1P_INPUT_SOURCE());
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_1P_INPUT_SOURCE());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuAudio(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_VOLUME);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_0);
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_SOURCE_TYPE, _UNSELECT, SysSourceGetScanType());

                if((GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_AUTO) ||
                   (GET_OSD_1P_INPUT_SOURCE() == _OSD_INPUT_D7))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2);
                }
                else if((GET_OSD_1P_INPUT_SOURCE() >= _OSD_INPUT_A0) &&
                        (GET_OSD_1P_INPUT_SOURCE() <= _OSD_INPUT_D2))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_0);
                }
                else if((GET_OSD_1P_INPUT_SOURCE() >= _OSD_INPUT_D3) &&
                        (GET_OSD_1P_INPUT_SOURCE() <= _OSD_INPUT_D6))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_1);
                }
            }
            else
            {
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_LR);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_TB);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_PIP);
                }
                else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_4P);
                }
            }

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuOther(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_RESET);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_0);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INFORMATION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INFORMATION_0);
            OsdDispShowInformation();
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuInformation(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_FACTORY);

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
            if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
               (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
            {
                OsdFuncClearOsd(ROW(11), COL(0), g_ucOsdHeight, 9);
            }
            else
#endif
            {
                OsdFuncClearOsd(ROW(11), COL(0), g_ucOsdWidth, 9);
            }
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FACTORY_0);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
            if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
               (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
            {
                OsdFuncClearOsd(ROW(11), COL(0), g_ucOsdHeight, 9);
            }
            else
#endif
            {
                OsdFuncClearOsd(ROW(11), COL(0), g_ucOsdWidth, 9);
            }
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuFactory(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDispDisableOsd();
            ScalerOsdMapRotation(0, _ENABLE, HEIGHT(_FACTORY_OSD_ROW), _DISABLE, 0, _DISABLE);
            RTDFactoryMainMenu();
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYMODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
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
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INFORMATION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INFORMATION_0);
            OsdDispShowInformation();
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }
}

void MenuDisplayMode1P(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(_OSD_DM_1P != GET_OSD_DISPLAY_MODE())
            {
                SET_OSD_DISPLAY_MODE(_OSD_DM_1P);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
                OsdDispDisableOsd();
                UserAdjustDisplayMode();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                SET_OSD_STATE(_MENU_DISPLAYMODE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
            break;

        case _RIGHT_KEY_MESSAGE:

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_LR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
#elif(_PBP_TB_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_TB);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
#elif(_PIP_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_PIP);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
#elif(_4P_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_4P);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
#else

#endif
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            if(_OSD_DM_1P != GET_OSD_DISPLAY_MODE())
            {
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());

                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
            }
            SET_OSD_STATE(_MENU_DISPLAYMODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuDisplayMode2P_LR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(_OSD_DM_2P_LR != GET_OSD_DISPLAY_MODE())
            {
                SET_OSD_DISPLAY_MODE(_OSD_DM_2P_LR);
                SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_L);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
                OsdDispDisableOsd();
                UserAdjustDisplayMode();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                SET_OSD_STATE(_MENU_DISPLAYMODE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
            break;

        case _RIGHT_KEY_MESSAGE:

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_TB);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
#elif(_PIP_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_PIP);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
#elif(_4P_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_4P);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
#else

#endif

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYMODE_1P);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(_OSD_DM_2P_LR != GET_OSD_DISPLAY_MODE())
            {
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
            }
            SET_OSD_STATE(_MENU_DISPLAYMODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}


void MenuDisplayMode2P_TB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(_OSD_DM_2P_TB != GET_OSD_DISPLAY_MODE())
            {
                SET_OSD_DISPLAY_MODE(_OSD_DM_2P_TB);
                SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_T);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
                OsdDispDisableOsd();
                UserAdjustDisplayMode();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                SET_OSD_STATE(_MENU_DISPLAYMODE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
            break;

        case _RIGHT_KEY_MESSAGE:

#if(_PIP_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_PIP);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
#elif(_4P_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_4P);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
#else

#endif
            break;

        case _LEFT_KEY_MESSAGE:

#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_LR);
#else
            SET_OSD_STATE(_MENU_DISPLAYMODE_1P);
#endif
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(_OSD_DM_2P_TB != GET_OSD_DISPLAY_MODE())
            {
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
            }
            SET_OSD_STATE(_MENU_DISPLAYMODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}


void MenuDisplayMode2P_PIP(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(_OSD_DM_2P_PIP != GET_OSD_DISPLAY_MODE())
            {
                SET_OSD_DISPLAY_MODE(_OSD_DM_2P_PIP);
                SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_MAIN);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
                OsdDispDisableOsd();
                UserAdjustDisplayMode();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                SET_OSD_STATE(_MENU_DISPLAYMODE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_4P_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_4P);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
#endif
            break;

        case _LEFT_KEY_MESSAGE:

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_TB);
#elif(_PBP_LR_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_LR);
#else
            SET_OSD_STATE(_MENU_DISPLAYMODE_1P);
#endif
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());

            break;


        case _EXIT_KEY_MESSAGE:
            if(_OSD_DM_2P_PIP != GET_OSD_DISPLAY_MODE())
            {
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());

                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_1);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
            }
            SET_OSD_STATE(_MENU_DISPLAYMODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuDisplayMode4P(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(_OSD_DM_4P != GET_OSD_DISPLAY_MODE())
            {
                SET_OSD_DISPLAY_MODE(_OSD_DM_4P);
                SET_OSD_SELECT_REGION(_OSD_SR_4P_LT_INSIDE);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
                OsdDispDisableOsd();
                UserAdjustDisplayMode();

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
                SET_OSD_STATE(_MENU_DISPLAYMODE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }

            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:

#if(_PIP_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_PIP);
#elif(_PBP_TB_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_TB);
#elif(_PBP_LR_DISPLAY_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYMODE_2P_LR);
#else
            SET_OSD_STATE(_MENU_DISPLAYMODE_1P);
#endif
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_DISPLAYMODE, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_0);
            break;

        case _EXIT_KEY_MESSAGE:
            if(_OSD_DM_4P != GET_OSD_DISPLAY_MODE())
            {
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());

                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYMODE_0);
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_DISPLATMODE_TYPE, _UNSELECT, GET_OSD_DISPLAY_MODE());
            }
            SET_OSD_STATE(_MENU_DISPLAYMODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

// display function
void MenuDisplayFunDispRotate(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                g_usBackupValue = GET_OSD_DISP_ROTATE();
                SET_OSD_STATE(_MENU_DISPLAYFUN_DISP_ROTATE_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _SELECT, GET_OSD_DISP_ROTATE());
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
            if(GET_OSD_DISP_ROTATE() == _DISP_ROTATE_0)
            {
                SET_OSD_STATE(_MENU_DISPLAYFUN_LATENCY);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LATENCY);
            }
#elif(_FREEZE_SUPPORT == _ON)

            SET_OSD_STATE(_MENU_DISPLAYFUN_FREEZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FREEZE_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);

#endif
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            break;

        default:
            break;
    }
}

void MenuDisplayFunLatency(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
            g_usBackupValue = GET_OSD_LATENCY();
            SET_OSD_STATE(_MENU_DISPLAYFUN_LATENCY_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _SELECT, GET_OSD_LATENCY());
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_FREEZE_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_DISPLAYFUN_FREEZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYFUN_DISP_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
            if(GET_OSD_DISP_ROTATE() >= (_DISP_ROTATE_0 + 4))
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);

            break;

        default:
            break;
    }
}

void MenuDisplayFunFreeze(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_FREEZE_SUPPORT == _ON)
            if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
            {
                SET_OSD_STATE(_MENU_DISPLAYFUN_FREEZE_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREEZE_STATUS());
                g_usBackupValue=GET_OSD_FREEZE_STATUS();
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
            if(GET_OSD_DISP_ROTATE() == _DISP_ROTATE_0)
            {
                SET_OSD_STATE(_MENU_DISPLAYFUN_LATENCY);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_LATENCY);
            }
            else
#endif
            {
                SET_OSD_STATE(_MENU_DISPLAYFUN_DISP_ROTATE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
                if(GET_OSD_DISP_ROTATE() >= (_DISP_ROTATE_0 + 4))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            break;

        default:
            break;
    }
}

void MenuDisplayFunLRratio(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_PBP_LR_RATIO();
            SET_OSD_STATE(_MENU_DISPLAYFUN_LR_RATIO_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LR_RATIO_ADJUST, GET_OSD_PBP_LR_RATIO());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_DISPLAYFUN_LR_INPUT_SWAP);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPosition(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_PIP_POSITION_TYPE();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _SELECT, GET_OSD_PIP_POSITION_TYPE());
            break;

        case _RIGHT_KEY_MESSAGE:

#if(_PIP_BLENDING_SUPPORT == _ON)
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_TRANSPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_TRANSPARENCY, GET_OSD_PIP_TRANSPARENCY());
#else
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_SIZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_SIZE, GET_OSD_PIP_SIZE());
#endif

            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipTransparency(void)
{
#if(_PIP_BLENDING_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_PIP_TRANSPARENCY();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST, GET_OSD_PIP_TRANSPARENCY());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_SIZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_SIZE, GET_OSD_PIP_SIZE());
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _UNSELECT, GET_OSD_PIP_POSITION_TYPE());
            OsdDispMainMenuIconPage(_DOWN, (_ICON_PAGE_PIP_POSITION_0 + (GET_OSD_PIP_POSITION_TYPE() / 4)));
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            break;

        default:
            break;
    }
#endif
}

void MenuDisplayFunPipSize(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_PIP_SIZE();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_SIZE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_SIZE_ADJUST, GET_OSD_PIP_SIZE());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_INPUT_SWAP);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _LEFT_KEY_MESSAGE:

#if(_PIP_BLENDING_SUPPORT == _ON)
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_TRANSPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_TRANSPARENCY, GET_OSD_PIP_TRANSPARENCY());
#else
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _UNSELECT, GET_OSD_PIP_POSITION_TYPE());
            OsdDispMainMenuIconPage(_DOWN, (_ICON_PAGE_PIP_POSITION_0 + (GET_OSD_PIP_POSITION_TYPE() / 4)));
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            break;

        default:
            break;
    }
}

void MenuDisplayFunInputSwap(void)
{
    BYTE ucSourceTemp = 0;

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            // 2P swap
            ucSourceTemp = GET_OSD_1P_INPUT_SOURCE();
            SET_OSD_1P_INPUT_SOURCE(GET_OSD_2P_INPUT_SOURCE());
            SET_OSD_2P_INPUT_SOURCE(ucSourceTemp);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);

#if(_2P_DISPLAY_SUPPORT == _ON)
            UserAdjustSwapInputPort();
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_LR)
            {
#if (_D_DOMAIN_PATH != _D_DOMAIN_4_PATH)
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_DISPLAYFUN_LR_RATIO);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LR_RATIO, GET_OSD_PBP_LR_RATIO());
#endif
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_TB)
            {
                // nop
            }
            else if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_SIZE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_SIZE, GET_OSD_PIP_SIZE());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_DISPLAYFUNCTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISPLAYFUNCTION);
            break;

        default:
            break;
    }
}

// select region
void MenuSelectRegion_2P_LR_L(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_LR_R);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _MENU_KEY_MESSAGE:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_FULL)
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_L);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_L);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_LR_L != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_2P_LR_R(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_LR_FULL);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_LR_L);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_FULL)
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_R);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_R);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_LR_R != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_2P_LR_FULL(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_LR_R);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_L) || (GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_R))
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_FULL);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_LR_FULL);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_LR_FULL != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_2P_TB_T(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_TB_B);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _MENU_KEY_MESSAGE:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_FULL)
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_T);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_T);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_TB_T != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_2P_TB_B(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_TB_FULL);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_TB_T);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_FULL)
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_B);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_B);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_TB_B != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_2P_TB_FULL(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_TB_B);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_T) || (GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_B))
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_FULL);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_TB_FULL);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_TB_FULL != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_2P_PIP_MAIN(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_PIP_SUB);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _MENU_KEY_MESSAGE:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_FULL)
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_MAIN);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_MAIN);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_PIP_MAIN != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_2P_PIP_SUB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_PIP_FULL);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_PIP_MAIN);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_FULL)
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_SUB);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_SUB);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_PIP_SUB != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_2P_PIP_FULL(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_2P_PIP_SUB);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_MAIN) || (GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_SUB))
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_FULL);
                UserAdjustOsdSelectRegionColorProc();
            }
            else
            {
                SET_OSD_SELECT_REGION(_OSD_SR_2P_PIP_FULL);
            }

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _EXIT_KEY_MESSAGE:
            if(_OSD_SR_2P_PIP_FULL != GET_OSD_SELECT_REGION())
            {
                OsdDispClearSelectColor(_DOWN);
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_LT_IN(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_LT_OUT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_LT_INSIDE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _EXIT_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_LT_OUT(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_LB_IN);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_LT_IN);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_LT_OUTSIDE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_LB_IN(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_LB_OUT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_LT_OUT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_LB_INSIDE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_LB_OUT(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_RT_IN);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_LB_IN);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_LB_OUTSIDE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif

            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_RT_IN(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_RT_OUT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_LB_OUT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_RT_INSIDE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_RT_OUT(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_RB_IN);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_RT_IN);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_RT_OUTSIDE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_RB_IN(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_RB_OUT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_RT_OUT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_RB_INSIDE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_RB_OUT(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_FULL);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_RB_IN);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_RB_OUTSIDE);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_RT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_RB_OUTSIDE))
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) &&
                   (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_2);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuSelectRegion_4P_FULL(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_SELECTREGIOM_4P_RB_OUT);
            OsdDispMainMenuSubSelect(_ICON_SUB_SEL_SELECTREGION, GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
            break;

        case _MENU_KEY_MESSAGE:
            SET_OSD_SELECT_REGION(_OSD_SR_4P_FULL);

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustHighlightWindow(_DB_APPLY_POLLING);
#endif
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            UserAdjustOsdSelectRegionColorProc();
            if(GET_OSD_SELECT_REGION() == _OSD_SR_4P_FULL)
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _EXIT_KEY_MESSAGE:
            if(GET_OSD_SELECT_REGION() == _OSD_SR_4P_FULL)
            {
                OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            }
            else
            {
                if((GET_OSD_SELECT_REGION() >= _OSD_SR_4P_LT_INSIDE) && (GET_OSD_SELECT_REGION() <= _OSD_SR_4P_LB_OUTSIDE))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_0);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SELECTREGION_4P_1);
                }
            }
            OsdDispMainMenuOptionSetting(_OPTION_SELECTREGION_TYPE, _UNSELECT, GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_SELECTREGION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuPictureBacklight(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_BACKLIGHT();

            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_BRIGHTNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
#elif(_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#elif(_SHARPNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()));
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            OsdDispMainMenuKeyInfo(_KEY_INFO_EXIT, _OSD_UNSELECT);
            break;

        default:
            break;
    }
}

void MenuPictureBrightness(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION());

            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#elif(_SHARPNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()));
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        default:
            break;
    }
}

void MenuPictureContrast(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_CONTRAST(GET_OSD_SELECT_REGION());

            SET_OSD_STATE(_MENU_PICTURE_CONTRAST_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_SHARPNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS, GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()));
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {

                break;
            }
#endif
#if(_BRIGHTNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
#else
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        default:
            break;
    }
}

void MenuPictureSharpness(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort());

            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {
                break;
            }
#endif

#if(_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST, GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#elif(_BRIGHTNESS_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS, GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
#else
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT, GET_OSD_BACKLIGHT());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_PICTURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PICTURE_0);
            break;

        default:
            break;
    }
}

void MenuAnalogAuto(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainSubString(_AUTO_CONFIG_DO);
                OsdDispSliderAndNumber(_MENU_ANALOG_AUTO, 0);
                OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
                OsdDispMainSubString(_AUTO_CONFIG_RESULT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSelectColor(_DOWN);
            OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
            SET_OSD_STATE(_MENU_ANALOG_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdDispSliderAndNumber(_MENU_ANALOG_HPOS, GET_VGA_MODE_ADJUST_H_POSITION());
            }
#endif

            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdFuncClearOsd(ROW(14), COL(19), WIDTH(10), HEIGHT(3));
            OsdDispClearSelectColor(_DOWN);
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_ANALOG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ANALOG_0);
            break;

        default:
            break;
    }
}

void MenuAnalogHPos(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                g_usBackupValue = GET_VGA_MODE_ADJUST_H_POSITION();
                SET_OSD_STATE(_MENU_ANALOG_HPOS_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            }
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdDispSliderAndNumber(_MENU_ANALOG_VPOS, GET_VGA_MODE_ADJUST_V_POSITION());
            }
#endif

            break;

        case _LEFT_KEY_MESSAGE:

#if(_VGA_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ANALOG_AUTO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSliderAndNumber();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_ANALOG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ANALOG_0);
            break;

        default:
            break;
    }
}

void MenuAnalogVPos(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                g_usBackupValue = GET_VGA_MODE_ADJUST_V_POSITION();
                SET_OSD_STATE(_MENU_ANALOG_VPOS_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG_CLOCK);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdDispSliderAndNumber(_MENU_ANALOG_CLOCK, GET_VGA_MODE_ADJUST_CLOCK());
            }
#endif

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdDispSliderAndNumber(_MENU_ANALOG_HPOS, GET_VGA_MODE_ADJUST_H_POSITION());
            }
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_ANALOG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ANALOG_0);
            break;

        default:
            break;
    }
}

void MenuAnalogClock(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                g_usBackupValue = GET_VGA_MODE_ADJUST_CLOCK();
                SET_OSD_STATE(_MENU_ANALOG_CLOCK_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usBackupValue, _SLIDER_0, _SELECT);
#else
                {
                    WORD usClockRangeMax = 0;
                    WORD usClockRangeMin = 0;
                    WORD usUserIHTotal = 0;

                    usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                    usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                    usUserIHTotal = UserCommonAdjustRealValueToPercent(g_usBackupValue, usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                    OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _SELECT);
                }
#endif
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG_PHASE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ANALOG_1);

#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdDispSliderAndNumber(_MENU_ANALOG_PHASE, GET_VGA_MODE_ADJUST_PHASE());
            }
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdDispSliderAndNumber(_MENU_ANALOG_VPOS, GET_VGA_MODE_ADJUST_V_POSITION());
            }
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_ANALOG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ANALOG_0);
            break;

        default:
            break;
    }
}

void MenuAnalogPhase(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                g_usBackupValue = GET_VGA_MODE_ADJUST_PHASE();

                SET_OSD_STATE(_MENU_ANALOG_PHASE_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ANALOG_CLOCK);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ANALOG_0);

            if((SysVgaGetRegion() != _DISPLAY_RGN_NONE) && (SysRegionGetDisplayState(SysVgaGetRegion()) == _DISPLAY_STATE_ACTIVE))
            {
                OsdDispSliderAndNumber(_MENU_ANALOG_CLOCK, GET_VGA_MODE_ADJUST_CLOCK());
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_ANALOG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ANALOG_0);
            break;

        default:
            break;
    }
}

void MenuColorPanelUniformity(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));

            break;

        case _RIGHT_KEY_MESSAGE:

#if(_PCM_FUNCTION == _ON)
            // Skip Gamma if PCM != native
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
            {
                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
                if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) > _CT_5800)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
                }
                break;
            }
#endif

            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));

            if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) == _GAMMA_24)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
            }

            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorGamma(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
            {
                g_usBackupValue = _FROM_STATE_GAMMA;
                g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION());
                OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
            }
            else
            {
                g_usBackupValue = GET_OSD_GAMMA(GET_OSD_SELECT_REGION());

                SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
            }
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) > _CT_5800)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
            }
#else
            SET_OSD_STATE(_MENU_COLOR_EFFECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));

            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) >= _COLOREFFECT_VIVID)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
            }
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorTemperature(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());

            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFFECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));

            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) >= _COLOREFFECT_VIVID)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
            }
            break;

        case _LEFT_KEY_MESSAGE:

#if(_PCM_FUNCTION == _ON)
            // Skip Gamma if PCM != native
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
            {
                SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
                break;
            }
#endif

            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));

            if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) == _GAMMA_24)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorEffect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());

            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {
                break;
            }
#endif
            SET_OSD_STATE(_MENU_COLOR_DEMO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
            if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
            }

            break;

        case _LEFT_KEY_MESSAGE:
#if(_ULTRA_HDR_SUPPORT == _ON)
            if(UserCommonAdjustHDREnableStatus(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort())) == _ON)
            {
                break;
            }
#endif
#if(_CONTRAST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));


            if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) > _CT_5800)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
            }
#else

#if(_PCM_FUNCTION == _ON)
            // Skip Gamma if PCM != native
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
            {
                SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
                break;
            }
#endif

            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));

            if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) == _GAMMA_24)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorDemo(void)
{
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType(GET_OSD_SYSTEM_DISPLAY_REGION());

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HLWIN_TYPE();

            SET_OSD_STATE(_MENU_COLOR_DEMO_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _SELECT, GET_OSD_HLWIN_TYPE());
            break;

        case _RIGHT_KEY_MESSAGE:

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
                    SET_OSD_STATE(_MENU_COLOR_FORMAT);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT(enumSourceSearchPort));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
                }
                else
#endif
                {
#if(_PCM_FUNCTION == _ON)

                    // Switch to PCM
                    SET_OSD_STATE(_MENU_COLOR_PCM);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                    if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) >= _PCM_OSD_SOFT_PROFT)
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                    }
                    else
#endif
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                    }

#else // else of #if(_PCM_FUNCTION == _ON)

                    // Switch to Hue
                    SET_OSD_STATE(_MENU_COLOR_HUE);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispClearSelectColor(_DOWN);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE(GET_OSD_SELECT_REGION()));

#endif // End of #if(_PCM_FUNCTION == _ON)
                }
            }
            else
            {
#if(_PCM_FUNCTION == _ON)

                // Switch to PCM
                SET_OSD_STATE(_MENU_COLOR_PCM);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) >= _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                }
                else
#endif
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }

#else // else of #if(_PCM_FUNCTION == _ON)

                // Switch to Hue
                SET_OSD_STATE(_MENU_COLOR_HUE);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE(GET_OSD_SELECT_REGION()));

#endif // End of #if(_PCM_FUNCTION == _ON)
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFFECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));

            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) >= _COLOREFFECT_VIVID)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorFormat(void)
{
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType((GET_OSD_SYSTEM_DISPLAY_REGION()));

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_FORMAT(enumSourceSearchPort);

            SET_OSD_STATE(_MENU_COLOR_FORMAT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT(enumSourceSearchPort));
            break;

        case _RIGHT_KEY_MESSAGE:

#if(_PCM_FUNCTION == _ON)

            // Switch to PCM
            SET_OSD_STATE(_MENU_COLOR_PCM);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) >= _PCM_OSD_SOFT_PROFT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
            }
            else
#endif
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
            }

#else

            // Switch to Hue
            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE(GET_OSD_SELECT_REGION()));

#endif // End of #if(_PCM_FUNCTION == _ON)
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_DEMO);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorPCM(void)
{
#if(_PCM_FUNCTION == _ON)
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType((GET_OSD_SYSTEM_DISPLAY_REGION()));

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
            {
                g_usBackupValue = _FROM_STATE_PCM;
                g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION());
                OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
            }
            else
            {
                g_usBackupValue = GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION());
                SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE(GET_OSD_SELECT_REGION()));

            break;

        case _LEFT_KEY_MESSAGE:
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
                   ((SysRegionGetSourceType((EnumDisplayRegion)GET_OSD_SYSTEM_DISPLAY_REGION()) == _SOURCE_VGA) ||
                    (SysRegionGetSourceType((EnumDisplayRegion)GET_OSD_SYSTEM_DISPLAY_REGION()) == _SOURCE_DVI)))
                {
                    SET_OSD_STATE(_MENU_COLOR_FORMAT);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT(enumSourceSearchPort));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
                }
                else
#endif
                {
                    SET_OSD_STATE(_MENU_COLOR_DEMO);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());

                    if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
                    }
                    else
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
                    }
                }
            }
            else
            {
                SET_OSD_STATE(_MENU_COLOR_DEMO);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());

                if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
#endif // End of #if(_PCM_FUNCTION == _ON)
}

void MenuColorHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HUE(GET_OSD_SELECT_REGION());

            SET_OSD_STATE(_MENU_COLOR_HUE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_SATURATION);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_SATURATION, GET_OSD_SATURATION(GET_OSD_SELECT_REGION()));
            break;

        case _LEFT_KEY_MESSAGE:

            OsdDispClearSliderAndNumber();

#if(_PCM_FUNCTION == _ON)

            SET_OSD_STATE(_MENU_COLOR_PCM);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) >= _PCM_OSD_SOFT_PROFT)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
            }
            else
#endif
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
            }

#else // else of #if(_PCM_FUNCTION == _ON)

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
                if((SysRegionGetDisplayState((EnumDisplayRegion)GET_OSD_SYSTEM_SELECT_REGION()) == _DISPLAY_STATE_ACTIVE) &&
                   ((SysRegionGetSourceType((EnumDisplayRegion)GET_OSD_SYSTEM_SELECT_REGION()) == _SOURCE_VGA) ||
                    (SysRegionGetSourceType((EnumDisplayRegion)GET_OSD_SYSTEM_SELECT_REGION()) == _SOURCE_DVI)))
                {
                    SET_OSD_STATE(_MENU_COLOR_FORMAT);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT(SysRegionGetPortType(UserAdjustConvertSystemSelectRegion(GET_OSD_SELECT_REGION()))));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_FORMAT);
                }
                else
#endif
                {
                    SET_OSD_STATE(_MENU_COLOR_DEMO);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());

                    if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
                    }
                    else
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
                    }
                }
            }
            else
            {
                SET_OSD_STATE(_MENU_COLOR_DEMO);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());

                if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
                }
            }
#endif // End of #if(_PCM_FUNCTION == _ON)

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuColorSaturation(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_SATURATION(GET_OSD_SELECT_REGION());

            SET_OSD_STATE(_MENU_COLOR_SATURATION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_HUE, GET_OSD_HUE(GET_OSD_SELECT_REGION()));
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceAspect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            switch(GET_OSD_DISPLAY_MODE())
            {
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _OSD_DM_2P_LR:
                    if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_FULL)
                    {
                        return;
                    }
                    break;
#endif
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _OSD_DM_2P_TB:
                    if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_FULL)
                    {
                        return;
                    }
                    break;
#endif
#if(_PIP_DISPLAY_SUPPORT == _ON)
                case _OSD_DM_2P_PIP:
                    if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_FULL)
                    {
                        return;
                    }
                    break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                case _OSD_DM_4P:
                    switch(GET_OSD_SELECT_REGION())
                    {
                        case _OSD_SR_4P_LT_INSIDE:
                        case _OSD_SR_4P_LB_INSIDE:
                        case _OSD_SR_4P_RT_INSIDE:
                        case _OSD_SR_4P_RB_INSIDE:
                            break;
                        default:
                            return;
                    }
                    break;
#endif
                default:
                case _OSD_DM_1P:
                    break;
            }

            g_usBackupValue = GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort());

            SET_OSD_STATE(_MENU_ADVANCE_ASPECT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));

            break;

        case _RIGHT_KEY_MESSAGE:
#if(_OVERSCAN_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_OVER_SCAN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _UNSELECT, GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#else

            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OD_ADJUST);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceOverScan(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            switch(GET_OSD_DISPLAY_MODE())
            {
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
                case _OSD_DM_2P_LR:
                    if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_LR_FULL)
                    {
                        return;
                    }
                    break;
#endif
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
                case _OSD_DM_2P_TB:
                    if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_TB_FULL)
                    {
                        return;
                    }
                    break;
#endif
#if(_PIP_DISPLAY_SUPPORT == _ON)
                case _OSD_DM_2P_PIP:
                    if(GET_OSD_SELECT_REGION() == _OSD_SR_2P_PIP_FULL)
                    {
                        return;
                    }
                    break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                case _OSD_DM_4P:
                    switch(GET_OSD_SELECT_REGION())
                    {
                        case _OSD_SR_4P_LT_INSIDE:
                        case _OSD_SR_4P_LB_INSIDE:
                        case _OSD_SR_4P_RT_INSIDE:
                        case _OSD_SR_4P_RB_INSIDE:
                            break;
                        default:
                            return;
                    }
                    break;
#endif
                default:
                case _OSD_DM_1P:
                    break;
            }

            g_usBackupValue = GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort());

            SET_OSD_STATE(_MENU_ADVANCE_OVER_SCAN_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _SELECT, GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()));

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OD_ADJUST);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_ASPECT);
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
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceOverDrive(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OD_ADJUST);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DDCCI);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _UNSELECT, GET_OSD_DDCCI_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _LEFT_KEY_MESSAGE:
#if(_OVERSCAN_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_OVER_SCAN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _UNSELECT, GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#else
            SET_OSD_STATE(_MENU_ADVANCE_ASPECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _UNSELECT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));
            if(GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()) == _OSD_ASPECT_RATIO_ORIGIN)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
            }
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceDDCCI(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_DDCCI_STATUS();

            SET_OSD_STATE(_MENU_ADVANCE_DDCCI_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_ULTRA_VIVID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ULTRA_VIVID);

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OD_ADJUST);

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceUltraVivid(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION());

            SET_OSD_STATE(_MENU_ADVANCE_ULTRA_VIVID_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _SELECT, GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()));
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_DCR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DCR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _UNSELECT, GET_OSD_DCR_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DDCCI);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_0);
            OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _UNSELECT, GET_OSD_DDCCI_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceDCR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_DCR_STATUS();

            SET_OSD_STATE(_MENU_ADVANCE_DCR_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_ULTRA_VIVID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ULTRA_VIVID);

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);

            break;

        default:
            break;
    }
}

void MenuAdvanceDpOption(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
#endif
            g_usItemNum = _MENU_ADVANCE_DP_OPTION;
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DP_OPTION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
#endif
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_1_DOT_X);
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_DP_MST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DP_MST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _UNSELECT, GET_OSD_DP_MST());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_MST);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_EDID);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_DCR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DCR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _UNSELECT, GET_OSD_DCR_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#else
            SET_OSD_STATE(_MENU_ADVANCE_ULTRA_VIVID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ULTRA_VIVID);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceDpMST(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_DP_MST_SUPPORT == _ON)
            // when Auto Search is disable, MST can be selected
            if((UserInterfaceGetAutoSearchTarget() == _DISPLAY_RGN_NONE))
            {
                g_usBackupValue = GET_OSD_DP_MST();
                SET_OSD_STATE(_MENU_ADVANCE_DP_MST_ADJUST);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _SELECT, GET_OSD_DP_MST());
            }
            else
            {
                OsdDispOsdMessage(_OSD_DISP_MST_WARNING_MSG);
                SET_OSD_STATE(_MENU_NONE);
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_OSD_DISABLE);
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if (_EDID_SWITCH_BY_PORT_ITEM == _OFF)
            SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_EDID);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(),_OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            g_usAdjustValue=0;
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_EDID_PORT_0);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceDpEDID(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if (_EDID_SWITCH_BY_PORT_ITEM == _OFF)
            SET_OSD_STATE(_MENU_ADVANCE_SINGLE_DP_EDID);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DP_EDID);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SINGLE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#else
            g_usAdjustValue=0;
            SET_OSD_STATE(_MENU_ADVANCE_EDID_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(),_OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT+g_usAdjustValue)))
            {
                case _PORT_DP:
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SINGLE_DP_EDID);
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT));
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 0)
                        break;
#endif
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 1)
                        break;
#endif
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 2)
                        break;
#endif
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 3)
                        break;
#endif
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 4)
                        break;
#endif
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 5)
                        break;
#endif
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_EDID_D0+g_usAdjustValue);
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT));
                    break;
                default:
                    break;
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:

#if(_FREESYNC_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREE_SYNC_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#endif

            SET_OSD_STATE(_MENU_ADVANCE_CLONE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE_MTP());
                if(GET_OSD_CLONE_MODE_MTP() <= _OSD_CLONE_MTP_D1)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
                }
                else if((GET_OSD_CLONE_MODE_MTP() <= _OSD_CLONE_MTP_D5))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_1);
                }
                else if((GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_D6))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE_1P());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
            }
            break;

        case _LEFT_KEY_MESSAGE:
#if(_DP_MST_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_DP_MST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _UNSELECT, GET_OSD_DP_MST());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_MST);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceClone(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_CLONE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                g_usBackupValue = GET_OSD_CLONE_MODE_MTP();
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE_MTP());
            }
            else
            {
                g_usBackupValue = GET_OSD_CLONE_MODE_1P();
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE_1P());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_FREESYNC_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREE_SYNC_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_LANE_COUNT);
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if (_EDID_SWITCH_BY_PORT_ITEM == _OFF)
            SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            // OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_EDID);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(),_OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_EDID_PORT_0);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}
void MenuAdvanceFreeSync(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, GET_OSD_FREE_SYNC_STATUS());
            g_usBackupValue=GET_OSD_FREE_SYNC_STATUS();
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_LANE_COUNT);
            break;

        case _LEFT_KEY_MESSAGE:
#if(_DP_MST_SUPPORT == _ON)
            if(GET_OSD_DP_MST() != _MST_OFF)
            {
                SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);

                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_EDID);
                break;
            }
#endif

            SET_OSD_STATE(_MENU_ADVANCE_CLONE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE_MTP());
                if(GET_OSD_CLONE_MODE_MTP() <= _OSD_CLONE_MTP_D1)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
                }
                else if((GET_OSD_CLONE_MODE_MTP() <= _OSD_CLONE_MTP_D5))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_1);
                }
                else if((GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_D6))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE_1P());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}

void MenuAdvanceDpLaneCount(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D0);
            g_usBackupValue = GET_OSD_DP_D0_LANE_MODE();
#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D1);
            g_usBackupValue = GET_OSD_DP_D1_LANE_MODE();
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D6);
            g_usBackupValue = GET_OSD_DP_D6_LANE_MODE();
#endif
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DP_OPTION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, g_usBackupValue);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_LANE_X);

            break;

        case _RIGHT_KEY_MESSAGE:

#if(_ULTRA_HDR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_HDR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_3);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_ADJUST);

#else

#if(_FALSE_COLOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_3);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FALSE_COLOR_TYPE, _UNSELECT, GET_OSD_FALSE_COLOR_STATUS());
            if(GET_OSD_FALSE_COLOR_STATUS() >= _OSD_FALSE_COLOR_USER)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_0);
            }
#endif

#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_FREESYNC_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREE_SYNC_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
#else
            SET_OSD_STATE(_MENU_ADVANCE_CLONE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE_MTP());
                if(GET_OSD_CLONE_MODE_MTP() <= _OSD_CLONE_MTP_D1)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
                }
                else if((GET_OSD_CLONE_MODE_MTP() <= _OSD_CLONE_MTP_D5))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_1);
                }
                else if((GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_D6))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_2);
                }
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE_1P());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
            }
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;
        default:
            break;
    }
}

#if(_ULTRA_HDR_SUPPORT == _ON)
void MenuAdvanceHdr(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if((GET_OSD_DISPLAY_MODE() != _OSD_DM_4P)&&(SysRegionGetSourceType(GET_OSD_SYSTEM_DISPLAY_REGION())!= _SOURCE_VGA)&&(SysRegionGetSourceType(GET_OSD_SYSTEM_DISPLAY_REGION())!= _SOURCE_DVI))
            {
                if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
                {
                    g_usBackupValue = _FROM_STATE_HDR;
                    g_usAdjustValue = GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION());
                    OsdDispOsdMessage(_OSD_DISP_PANEL_UNIFORMITY_ONOFF_MSG);
                    OsdWindowDrawingByFontHighlight(_OSD_WINDOW_4_1, ROW(2), COL(27), WIDTH(6), HEIGHT(4), _CP_LIGHTBLUE, _CP_ORANGE, _CP_BG);
                    SET_OSD_STATE(_MENU_PANEL_UNIFORMITY_MSG_ADJUST);
                }
                else
                {
                    SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
                    OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_MODE);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                }
            }
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_FALSE_COLOR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FALSE_COLOR_TYPE, _UNSELECT, GET_OSD_FALSE_COLOR_STATUS());
            if(GET_OSD_FALSE_COLOR_STATUS() >= _OSD_FALSE_COLOR_USER)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_0);
            }
#endif

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_LANE_COUNT);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);
            break;

        default:
            break;
    }
}
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
void MenuAdvanceFalseColor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FALSE_COLOR_TYPE, _SELECT, GET_OSD_FALSE_COLOR_STATUS());
            g_usBackupValue=GET_OSD_FALSE_COLOR_STATUS();

            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
#if(_ULTRA_HDR_SUPPORT == _ON)
            SET_OSD_STATE(_MENU_ADVANCE_HDR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_ADJUST);
#else
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);

            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_LANE_COUNT);
#endif
            break;
        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ADVANCE_0);

            break;

        default:
            break;
    }
}

#endif

void MenuAudioVolume(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_VOLUME();

            SET_OSD_STATE(_MENU_AUDIO_VOLUME_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME_ADJUST, GET_OSD_VOLUME());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_AUDIO_MUTE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuAudioMute(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_VOLUME_MUTE();

            SET_OSD_STATE(_MENU_AUDIO_MUTE_ON_OFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _SELECT, GET_OSD_VOLUME_MUTE());

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);

            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            SET_OSD_STATE(_MENU_AUDIO_VOLUME);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuAudioStandAlong(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_AUDIO_STAND_ALONE();

            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG_SELECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);

            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) &&
               ((SysSourceGetSourceType() == _SOURCE_VGA) ||
                (SysSourceGetSourceType() == _SOURCE_DVI)))
            {
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, _OSD_AUDIO_SOURCE_ANALOG);
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
            }

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_SOURCE_0 + (GET_OSD_AUDIO_SOURCE() / 4));

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_MUTE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuAudioAudioSource(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if((GET_OSD_DISPLAY_MODE() != _OSD_DM_1P) ||
               ((SysRegionGetSourceType(_DISPLAY_RGN_1P) != _SOURCE_VGA) &&
                (SysRegionGetSourceType(_DISPLAY_RGN_1P) != _SOURCE_DVI)))
            {
                g_usBackupValue = GET_OSD_AUDIO_SOURCE();

                SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE_SELECT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _SELECT, GET_OSD_AUDIO_SOURCE());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_1);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuAudioSoundMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE_SELECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_AUDIO_0);

            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) &&
               ((SysRegionGetSourceType(_DISPLAY_RGN_1P) == _SOURCE_VGA) ||
                (SysRegionGetSourceType(_DISPLAY_RGN_1P) == _SOURCE_DVI)))
            {
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, _OSD_AUDIO_SOURCE_ANALOG);
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
            }

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_SOURCE_0 + (GET_OSD_AUDIO_SOURCE() / 4));
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_AUDIO_0);
            break;

        default:
            break;
    }
}

void MenuOtherReset(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            OsdDispOsdReset();
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherMenuTime(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_TIME_OUT();

            SET_OSD_STATE(_MENU_OTHER_MENU_TIME_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME_ADJUST, GET_OSD_TIME_OUT());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_RESET);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherOsdHPos(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_HPOS();

            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS_ADJUST, GET_OSD_HPOS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherOsdVPos(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_VPOS();

            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS_ADJUST, GET_OSD_VPOS());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherLanguage(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_LANGUAGE();

            SET_OSD_STATE(_MENU_OTHER_LANGUAGE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_0);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherTransparency(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_TRANSPARENCY_STATUS();

            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY_ADJUST, GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_ROTATE);
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherRotate(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_ROTATE_STATUS();
            g_usAdjustValue = GET_OSD_ROTATE_STATUS();

            SET_OSD_STATE(_MENU_OTHER_ROTATE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _SELECT, GET_OSD_ROTATE_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_OTHER_BORDER_WIDTH);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_BORDER_WIDTH, GET_OSD_SELECT_REGION_WIDTH());
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherBorderWidth(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_SELECT_REGION_WIDTH();
            SET_OSD_STATE(_MENU_OTHER_BORDER_WIDTH_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_BORDER_WIDTH_ADJUST, GET_OSD_SELECT_REGION_WIDTH());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_BORDER_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_BORDER_COLOR, _UNSELECT, GET_OSD_SELECT_REGION_COLOR());
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_BORDER_COLOR);
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OSD_ROTATE);
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

void MenuOtherBorderColor(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_SELECT_REGION_COLOR();
            SET_OSD_STATE(_MENU_OTHER_BORDER_COLOR_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_BORDER_COLOR, _SELECT, GET_OSD_SELECT_REGION_COLOR());
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_OTHER_BORDER_WIDTH);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_OTHER_1);
            OsdDispSliderAndNumber(_MENU_OTHER_BORDER_WIDTH, GET_OSD_SELECT_REGION_WIDTH());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_OTHER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OTHER_0);
            break;

        default:
            break;
    }
}

// display function adjust
void MenuDisplayFunDispRotateAdjust(void)
{
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DISP_ROTATE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_DISPLAYFUN_DISP_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            // OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
            OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
            break;

        case _RIGHT_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) &&
               (GET_OSD_DISP_ROTATE() != (_DISP_ROTATE_AMOUNT - 1)))
            {
                if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 3))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
                }
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_DISP_ROTATE_ADJUST, GET_OSD_DISP_ROTATE());

#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
                if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 1))
                {
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
                }
#endif
                UserCommonInterfacePanelPowerAction(_BACKLIGHT_OFF);
                SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (GET_OSD_DISP_ROTATE() != _DISP_ROTATE_0))
            {
                if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0 + 4))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
                }
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_DISP_ROTATE_ADJUST, GET_OSD_DISP_ROTATE());
#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
                if(GET_OSD_DISP_ROTATE() == (_DISP_ROTATE_0))
                {
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
                }
#endif
                SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_DISP_ROTATE())
                {
                    SET_OSD_DISP_ROTATE(g_usBackupValue);

                    SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);

                    if(GET_OSD_DISP_ROTATE() >= (_DISP_ROTATE_0 + 4))
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_1);
                    }
                    else
                    {
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DISP_ROTATE_0);
                    }
                }
                SET_OSD_STATE(_MENU_DISPLAYFUN_DISP_ROTATE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_DISP_ROTATE_TYPE, _UNSELECT, GET_OSD_DISP_ROTATE());
#if((_DISP_LATENCY_ADJUST_SUPPORT == _ON) || (_FREEZE_SUPPORT == _ON))
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
#endif
            }
            break;

        default:
            break;
    }
#endif
}

void MenuDisplayFunDispLatencyAdjust(void)
{
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_LATENCY())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_DISPLAYFUN_LATENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());

            break;

        case _RIGHT_KEY_MESSAGE:

            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (GET_OSD_LATENCY() != _LATENCY_H))
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LATENCY_ADJUST, GET_OSD_LATENCY());

                // Set Backlight OFF
                SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }

            break;

        case _LEFT_KEY_MESSAGE:

            if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) && (GET_OSD_LATENCY() != _LATENCY_L))
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LATENCY_ADJUST, GET_OSD_LATENCY());

                // Set Backlight OFF
                SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
            }

            break;

        case _EXIT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_LATENCY())
                {
                    SET_OSD_LATENCY(g_usBackupValue);

                    // Set Backlight OFF
                    SysModeSetDisplayTarget(_DISPLAY_RGN_1P);
                    SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_SETTING);
                }
                SET_OSD_STATE(_MENU_DISPLAYFUN_LATENCY);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_LATENCY_TYPE, _UNSELECT, GET_OSD_LATENCY());
            }

            break;

        default:
            break;
    }
#endif
}

void MenuDisplayFunFreezeAdjust(void)
{
#if(_FREEZE_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_DISPLAYFUN_FREEZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:

            if(GET_OSD_FREEZE_STATUS() != _OFF)
            {
                SET_OSD_FREEZE_STATUS(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, _OFF);
                UserCommonAdjustDisplayFreeze(_OFF);
            }


            break;

        case _LEFT_KEY_MESSAGE:

            if(GET_OSD_FREEZE_STATUS() != _ON)
            {
                SET_OSD_FREEZE_STATUS(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, _ON);
                UserCommonAdjustDisplayFreeze(_ON);
            }

            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_FREEZE_STATUS())
            {
                SET_OSD_FREEZE_STATUS(g_usBackupValue);
                UserCommonAdjustDisplayFreeze(GET_OSD_FREEZE_STATUS());
            }

            SET_OSD_STATE(_MENU_DISPLAYFUN_FREEZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREEZE_STATUS());
            break;

        default:
            break;
    }
#endif
}

void MenuDisplayFunLRratioAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PBP_LR_RATIO())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                SysModeSetResetTarget(_MODE_ACTION_RESET_TO_DISPLAY_INITIAL);
            }

            SET_OSD_STATE(_MENU_DISPLAYFUN_LR_RATIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LR_RATIO_ADJUST, GET_OSD_PBP_LR_RATIO());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LR_RATIO_ADJUST, GET_OSD_PBP_LR_RATIO());
//          call function to active width adjust
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PBP_LR_RATIO())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_PBP_LR_RATIO(g_usAdjustValue);
//              call function to active width adjust
            }
            SET_OSD_STATE(_MENU_DISPLAYFUN_LR_RATIO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_LR_RATIO, GET_OSD_PBP_LR_RATIO());
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPositionAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PIP_POSITION_TYPE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            if(_PIP_POSITON_USER == GET_OSD_PIP_POSITION_TYPE())
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearSelectColor(_DOWN);
                SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_H);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_PIP_USER_POSITION);
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_H, GET_OSD_PIP_USER_POSITION_H());
            }
            else
            {
                SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _UNSELECT, GET_OSD_PIP_POSITION_TYPE());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_ADJUST, GET_OSD_PIP_POSITION_TYPE());
                if(g_usAdjustValue != GET_OSD_PIP_POSITION_TYPE())
                {
                    if((g_usAdjustValue / 4) != (GET_OSD_PIP_POSITION_TYPE() / 4))
                    {
                        OsdDispMainMenuIconPage(_DOWN, (_ICON_PAGE_PIP_POSITION_0 + (g_usAdjustValue / 4)));
                    }
                    SET_OSD_PIP_POSITION_TYPE(g_usAdjustValue);

                    OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _SELECT, GET_OSD_PIP_POSITION_TYPE());

#if(_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonAdjustPipSubTimingFormat();
                    }
#endif
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_PIP_POSITION_TYPE())
                {
                    if((g_usBackupValue / 4) != (GET_OSD_PIP_POSITION_TYPE() / 4))
                    {
                        OsdDispMainMenuIconPage(_DOWN, (_ICON_PAGE_PIP_POSITION_0 + (g_usBackupValue / 4)));
                    }
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_PIP_POSITION_TYPE(g_usAdjustValue);

#if(_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonAdjustPipSubTimingFormat();
                    }
#endif
                }
                SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _UNSELECT, GET_OSD_PIP_POSITION_TYPE());
            }
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPositionH(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_PIP_USER_POSITION_H();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST, GET_OSD_PIP_USER_POSITION_H());
            break;

        case _RIGHT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_V);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_V, GET_OSD_PIP_USER_POSITION_V());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PIP_POSITION_1);
            OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _UNSELECT, GET_OSD_PIP_POSITION_TYPE());
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPositionV(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_PIP_USER_POSITION_V();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST, GET_OSD_PIP_USER_POSITION_V());
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_H);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_H, GET_OSD_PIP_USER_POSITION_H());
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispClearSliderAndNumber();
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_DISPLAYFUNCTION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PIP_POSITION_1);
            OsdDispMainMenuOptionSetting(_OPTION_PIP_POSITION, _UNSELECT, GET_OSD_PIP_POSITION_TYPE());
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPositionHAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PIP_USER_POSITION_H())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_H);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_H, GET_OSD_PIP_USER_POSITION_H());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_H_ADJUST, GET_OSD_PIP_USER_POSITION_H());

#if(_PIP_DISPLAY_SUPPORT == _ON)
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    UserCommonAdjustPipSubTimingFormat();
                }
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_PIP_USER_POSITION_H())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_PIP_USER_POSITION_H(g_usAdjustValue);

#if(_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonAdjustPipSubTimingFormat();
                    }
#endif
                }
                SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_H);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_H, GET_OSD_PIP_USER_POSITION_H());
            }
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipPositionVAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PIP_USER_POSITION_V())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_V);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_V, GET_OSD_PIP_USER_POSITION_V());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_V_ADJUST, GET_OSD_PIP_USER_POSITION_V());

#if(_PIP_DISPLAY_SUPPORT == _ON)
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    UserCommonAdjustPipSubTimingFormat();
                }
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_PIP_USER_POSITION_V())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_PIP_USER_POSITION_V(g_usAdjustValue);

#if(_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonAdjustPipSubTimingFormat();
                    }
#endif
                }
                SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_POSITION_V);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_POSITION_V, GET_OSD_PIP_USER_POSITION_V());
            }
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipTransparencyAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PIP_TRANSPARENCY())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_TRANSPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_TRANSPARENCY, GET_OSD_PIP_TRANSPARENCY());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_TRANSPARENCY_ADJUST, GET_OSD_PIP_TRANSPARENCY());
//          call function to active width adjust
#if(_PIP_BLENDING_SUPPORT == _ON)
            UserAdjustPipTransparency();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PIP_TRANSPARENCY())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_PIP_TRANSPARENCY(g_usAdjustValue);
//              call function to active width adjust
#if(_PIP_BLENDING_SUPPORT == _ON)
                UserAdjustPipTransparency();
#endif
            }
            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_TRANSPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_TRANSPARENCY, GET_OSD_PIP_TRANSPARENCY());
            break;

        default:
            break;
    }
}

void MenuDisplayFunPipSizeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PIP_SIZE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_SIZE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_SIZE, GET_OSD_PIP_SIZE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_SIZE_ADJUST, GET_OSD_PIP_SIZE());

#if(_PIP_DISPLAY_SUPPORT == _ON)
                if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                {
                    UserCommonAdjustPipSubTimingFormat();
                }
#endif
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_PIP_SIZE())
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_PIP_SIZE(g_usAdjustValue);

#if(_PIP_DISPLAY_SUPPORT == _ON)
                    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_2P_PIP)
                    {
                        UserCommonAdjustPipSubTimingFormat();
                    }
#endif
                }
                SET_OSD_STATE(_MENU_DISPLAYFUN_PIP_SIZE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispSliderAndNumber(_MENU_DISPLAYFUN_PIP_SIZE, GET_OSD_PIP_SIZE());
            }
            break;

        default:
            break;
    }
}

// picture adjust
void MenuPictureBacklightAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BACKLIGHT())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_BACKLIGHT_ADJUST, GET_OSD_BACKLIGHT());
            UserAdjustBacklight(GET_OSD_BACKLIGHT());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BACKLIGHT())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_BACKLIGHT(g_usAdjustValue);
                UserAdjustBacklight(GET_OSD_BACKLIGHT());
            }
            SET_OSD_STATE(_MENU_PICTURE_BACKLIGHT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BACKLIGHT(), _BACKLIGHT_MAX, _BACKLIGHT_MIN, _BACKLIGHT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        default:
            break;
    }
}

void MenuPictureBrightnessAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_BRIGHTNESS_ADJUST, GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));

#if(_BRIGHTNESS_SUPPORT == _ON)
            UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_BRIGHTNESS_SUPPORT == _ON)
                UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()));
#endif
            }
            SET_OSD_STATE(_MENU_PICTURE_BRIGHTNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_BRIGHTNESS(GET_OSD_SELECT_REGION()), _BRIGHTNESS_MAX, _BRIGHTNESS_MIN, _BRIGHTNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        default:
            break;
    }
}

void MenuPictureContrastAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_CONTRAST_ADJUST, GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_CONTRAST(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            }
            SET_OSD_STATE(_MENU_PICTURE_CONTRAST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()), _CONTRAST_MAX, _CONTRAST_MIN, _CONTRAST_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        default:
            break;
    }
}

void MenuPictureSharpnessAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
            }

            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_PICTURE_SHARPNESS_ADJUST, GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()));
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
#if(_SHARPNESS_SUPPORT == _ON)
            UserCommonAdjustSharpness(GET_OSD_SYSTEM_SELECT_REGION(), UserAdjustGetSelectRegionPort());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort(), g_usAdjustValue);
#if(_SHARPNESS_SUPPORT == _ON)
                UserCommonAdjustSharpness(GET_OSD_SYSTEM_SELECT_REGION(), UserAdjustGetSelectRegionPort());
#endif
            }
            SET_OSD_STATE(_MENU_PICTURE_SHARPNESS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SHARPNESS(UserAdjustGetSelectRegionPort()), _SHARPNESS_MAX, _SHARPNESS_MIN, _SHARPNESS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}
void MenuDisplayHPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_H_POSITION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
            }
#endif

            SET_OSD_STATE(_MENU_ANALOG_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_ANALOG_HPOS_ADJUST, GET_VGA_MODE_ADJUST_H_POSITION());
            UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION(), SysVgaGetRegion());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_H_POSITION())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_H_POSITION(g_usAdjustValue);
                UserCommonAdjustHPosition(GET_VGA_MODE_ADJUST_H_POSITION(), SysVgaGetRegion());
            }
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_H_POSITION(), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_H_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
#endif

            break;

        default:
            break;
    }
}

void MenuDisplayVPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_V_POSITION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
            }
#endif

            SET_OSD_STATE(_MENU_ANALOG_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_ANALOG_VPOS_ADJUST, GET_VGA_MODE_ADJUST_V_POSITION());
            UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION(), SysVgaGetRegion());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ANALOG_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_V_POSITION())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_V_POSITION(g_usAdjustValue);
                UserCommonAdjustVPosition(GET_VGA_MODE_ADJUST_V_POSITION(), SysVgaGetRegion());
            }
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_V_POSITION(), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_V_POSITION(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
#endif

            break;

        default:
            break;
    }
}

void MenuDisplayClockAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_CLOCK())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
            }
#endif
            SET_OSD_STATE(_MENU_ANALOG_CLOCK);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
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
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_ANALOG_CLOCK_ADJUST, GET_VGA_MODE_ADJUST_CLOCK());
            UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_CLOCK())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_CLOCK(g_usAdjustValue);
                UserCommonAdjustClock(GET_VGA_MODE_ADJUST_CLOCK());
            }
            SET_OSD_STATE(_MENU_ANALOG_CLOCK);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_AUTO_CLOCK_SAVE_VALUE_OPTION == _CLOCK_SAVE_PERCENT_VALUE)
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_CLOCK(), _SLIDER_0, _UNSELECT);
#else
            {
                WORD usClockRangeMax = 0;
                WORD usClockRangeMin = 0;
                WORD usUserIHTotal = 0;

                usClockRangeMax = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MAX);
                usClockRangeMin = UserCommonAdjustGetAdcClockRange(_GET_CLOCKRANGE_MIN);
                usUserIHTotal = UserCommonAdjustRealValueToPercent(GET_VGA_MODE_ADJUST_CLOCK(), usClockRangeMax, usClockRangeMin, (((usClockRangeMax - usClockRangeMin) / 2) + usClockRangeMin));

                OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), usUserIHTotal, _SLIDER_0, _UNSELECT);
            }
#endif
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_CLOCK(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
#endif

            break;

        default:
            break;
    }
}

void MenuDisplayPhaseAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_PHASE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_MODEUSERDATA_MSG);
            }
#endif
            SET_OSD_STATE(_MENU_ANALOG_PHASE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            OsdDispSliderAndNumber(_MENU_ANALOG_PHASE_ADJUST, GET_VGA_MODE_ADJUST_PHASE());
            UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
#if(_VGA_SUPPORT == _ON)
            if(g_usBackupValue != GET_VGA_MODE_ADJUST_PHASE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_VGA_MODE_ADJUST_PHASE(g_usAdjustValue);
                UserCommonAdjustPhase(GET_VGA_MODE_ADJUST_PHASE());
            }
            SET_OSD_STATE(_MENU_ANALOG_PHASE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_VGA_MODE_ADJUST_PHASE(), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_VGA_MODE_ADJUST_PHASE(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
#endif
            break;

        default:
            break;
    }
}

void MenuColorPanelUniformityAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), _OFF);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

            UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
            // UserAdjustPanelUniformityMode(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
            if((GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON) && (GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON))
            {
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);
            }
            else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
            {
                ScalerColorPanelUniformityRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
            }
            else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON)
            {
                ScalerColorPanelUniformityRegionEnable(ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()), _DB_APPLY_NO_POLLING, _ON);
            }
#endif

            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));

            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), _ON);

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

            UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
            // UserAdjustPanelUniformityMode(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
            if((GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON) && (GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON))
            {
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);
            }
            else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
            {
                ScalerColorPanelUniformityRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
            }
            else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON)
            {
                ScalerColorPanelUniformityRegionEnable(ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()), _DB_APPLY_NO_POLLING, _ON);
            }
#endif

            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _SELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_UNIFORMITY_SUPPORT == _ON)
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

                UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
                // UserAdjustPanelUniformityMode(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
                if((GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON) && (GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON))
                {
                    ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);
                }
                else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
                {
                    ScalerColorPanelUniformityRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
                }
                else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON)
                {
                    ScalerColorPanelUniformityRegionEnable(ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()), _DB_APPLY_NO_POLLING, _ON);
                }
#endif
            }
            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_PANEL_UNIFORMITY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_PANEL_UNIFORMITY_ONOFF, _UNSELECT, GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()));

            break;

        default:
            break;
    }
}

void MenuColorGammaAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_GAMMA(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_24)
            {
                if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) == _GAMMA_22)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
                }

                OsdDispSliderAndNumber(_MENU_COLOR_GAMMA_ADJUST, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));

#if(_GAMMA_FUNCTION == _ON)
                UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING, _OFF);
                if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
                {
                    UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
                    UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
                }
#endif
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
            {
                if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) == _GAMMA_24)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
                }

                OsdDispSliderAndNumber(_MENU_COLOR_GAMMA_ADJUST, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));

#if(_GAMMA_FUNCTION == _ON)
                UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING, _OFF);
                if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
                {
                    UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
                    UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
                }
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_GAMMA(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_GAMMA(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if(_GAMMA_FUNCTION == _ON)
                UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING, _OFF);

                if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) != _GAMMA_OFF)
                {
                    UserAdjustGamma(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
                    UserAdjustGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
                }
#endif
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_GAMMA);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
            if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) >= _GAMMA_24)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
            }
            break;

        default:
            break;
    }
}

void MenuColorColortempAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) == _CT_USER)
            {
                g_usBackupValue = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
                OsdDispClearSelectColor(_UP);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispClearArrow(_DOWN);
                OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());
            }
            else
            {
                OsdDispClearArrow(_DOWN);
                SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_USER)
            {
                if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) == _CT_5800)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
                }

                OsdDispSliderAndNumber(_MENU_COLOR_TEMPERATURE_ADJUST, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            }
            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) != _CT_9300)
            {
                if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) == _CT_SRGB)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_TEMPERATURE_ADJUST, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()))
            {
                SET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION(), g_usBackupValue);
                // Adjust Color
                RTDNVRamLoadColorSetting(GET_OSD_SELECT_REGION());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _UNSELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            if(GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()) >= _CT_5800)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_0);
            }

            break;

        default:
            break;
    }
}

void MenuColorColorEffectAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) == _COLOREFFECT_USER)
            {
                g_usBackupValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());
                OsdDispClearSelectColor(_UP);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
                SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
                OsdDispClearArrow(_DOWN);
            }
            else
            {
                OsdDispClearArrow(_DOWN);
                SET_OSD_STATE(_MENU_COLOR_EFFECT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
                if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) >= _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
                }
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) != _COLOREFFECT_AMOUNT)
            {
                if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) == _COLOREFFECT_PHOTO)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_EFFECT_ADJUST, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
                UserAdjustColorEffectMode(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }

            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) != _COLOREFFECT_STANDARD)
            {
                if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) == _COLOREFFECT_VIVID)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_EFFECT_ADJUST, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
                UserAdjustColorEffectMode(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:

            if(g_usBackupValue != GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if((_DCC_FUNCTION == _ON) || (_ICM_SUPPORT == _ON) || (_SCM_SUPPORT == _ON) || (_SIX_COLOR_SUPPORT == _ON))
                UserAdjustColorEffectMode(GET_OSD_SYSTEM_SELECT_REGION());
#endif
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_EFFECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _UNSELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            if(GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()) >= _COLOREFFECT_VIVID)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_0);
            }

            break;

        default:
            break;
    }
}

void MenuColorColorDemoAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HLWIN_TYPE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_DEMO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_HLWIN_TYPE() != _HL_WIN_5)
            {
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_3)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_DEMO_ADJUST, GET_OSD_HLWIN_TYPE());

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
                UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                UserAdjustOsdSelectRegionColorProc();
#endif

#if(_DCC_FUNCTION == _ON)
                ScalerColorDCCNormalizeFactorAdjust(g_enumDCCMeasureRegion);
#endif
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_HLWIN_TYPE() != _HL_WIN_OFF)
            {
                if(GET_OSD_HLWIN_TYPE() == _HL_WIN_4)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
                }
                OsdDispSliderAndNumber(_MENU_COLOR_DEMO_ADJUST, GET_OSD_HLWIN_TYPE());

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
                UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                UserAdjustOsdSelectRegionColorProc();
#endif

#if(_DCC_FUNCTION == _ON)
                ScalerColorDCCNormalizeFactorAdjust(g_enumDCCMeasureRegion);
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HLWIN_TYPE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HLWIN_TYPE(g_usAdjustValue);
                // Adjust HLWIN
#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
                UserAdjustHLWinType(GET_OSD_HLWIN_TYPE());

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
                UserAdjustOsdSelectRegionColorProc();
#endif

#if(_DCC_FUNCTION == _ON)
                ScalerColorDCCNormalizeFactorAdjust(g_enumDCCMeasureRegion);
#endif
            }
            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_COLOR_DEMO);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_DEMO_TYPE, _UNSELECT, GET_OSD_HLWIN_TYPE());
            if(GET_OSD_HLWIN_TYPE() >= _HL_WIN_4)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_DEMO_0);
            }

            break;

        default:
            break;
    }
}

void MenuColorColorFormatAdjust(void)
{
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType((GET_OSD_SYSTEM_DISPLAY_REGION()));

    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_COLOR_FORMAT(enumSourceSearchPort))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_FORMAT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT(enumSourceSearchPort));
            break;

        case _RIGHT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(GET_OSD_COLOR_FORMAT(enumSourceSearchPort) != _COLOR_SPACE_YPBPR)
                {
                    SET_OSD_COLOR_FORMAT(enumSourceSearchPort, _COLOR_SPACE_YPBPR);
                    OsdFuncColorFormatAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT(enumSourceSearchPort));
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(GET_OSD_COLOR_FORMAT(enumSourceSearchPort) != _COLOR_SPACE_RGB)
                {
                    SET_OSD_COLOR_FORMAT(enumSourceSearchPort, _COLOR_SPACE_RGB);
                    OsdFuncColorFormatAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _SELECT, GET_OSD_COLOR_FORMAT(enumSourceSearchPort));
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_COLOR_FORMAT(enumSourceSearchPort))
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_COLOR_FORMAT(enumSourceSearchPort, g_usAdjustValue);
                    OsdFuncColorFormatAdjust(GET_OSD_SYSTEM_DISPLAY_REGION());
                }
                SET_OSD_STATE(_MENU_COLOR_FORMAT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_FORMAT_TYPE, _UNSELECT, GET_OSD_COLOR_FORMAT(enumSourceSearchPort));
            }
            break;

        default:
            break;
    }
}

void MenuColorColorPCMAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_SOFT_PROFT)
            {
                g_usBackupValue = GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION());
                OsdDispClearArrow(_UP);
                OsdDispClearArrow(_DOWN);
                SET_OSD_STATE(_MENU_COLOR_PCM_SOFT_PROFT_ADJUST);
                SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_1);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_PCM_1);

                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_PCM_SOFT_PROFT);
            }
            else
#endif
            {
                if(g_usBackupValue != GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()))
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
                }

                SET_OSD_STATE(_MENU_COLOR_PCM);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
            }
            break;

        case _RIGHT_KEY_MESSAGE:

#if(_OCC_SUPPORT == _ON)
#if(_RGB_3D_GAMMA == _ON)
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_SOFT_PROFT)
#else
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
#endif
            {
                OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));

#if(_RGB_3D_GAMMA == _ON)
                if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                }
                else
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                }
#else
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
#endif
                OsdFuncColorPcmAdjust();
            }
#else    //#if(_OCC_SUPPORT == _ON)
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_NATIVE)
            {
                OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                OsdFuncColorPcmAdjust();
            }
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));

#endif
            break;

        case _LEFT_KEY_MESSAGE:

#if(_OCC_SUPPORT == _ON)
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_SRGB)
            {
                OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));

                if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_NATIVE)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
                else
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                }
                OsdFuncColorPcmAdjust();
            }
#else   //#if(_OCC_SUPPORT == _ON)
            if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_USER)
            {
                OsdDispSliderAndNumber(_MENU_COLOR_PCM_ADJUST, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_NATIVE)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
                else
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                }
                OsdFuncColorPcmAdjust();
            }
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()))
            {
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                if(g_usBackupValue == _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                }
#endif

                SET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION(), g_usBackupValue);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) == _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                }
                else if((g_usAdjustValue == _PCM_OSD_SOFT_PROFT) && (GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) != _PCM_OSD_SOFT_PROFT))
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
                else
                {
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
#else
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
#endif
                OsdFuncColorPcmAdjust();
            }
            else
            {
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
            }

            SET_OSD_STATE(_MENU_COLOR_PCM);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            break;

        default:
            break;
    }
}

void MenuColorColorHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HUE(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_HUE_ADJUST, GET_OSD_HUE(GET_OSD_SELECT_REGION()));
#if(_GLOBAL_HUE_SATURATION == _ON)
            UserAdjustGlobalHueSat(GET_OSD_SYSTEM_SELECT_REGION(), (SWORD)GET_OSD_HUE(GET_OSD_SELECT_REGION()), GET_OSD_SATURATION(GET_OSD_SELECT_REGION()));
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HUE(GET_OSD_SELECT_REGION()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HUE(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_GLOBAL_HUE_SATURATION == _ON)
                UserAdjustGlobalHueSat(GET_OSD_SYSTEM_SELECT_REGION(), (SWORD)GET_OSD_HUE(GET_OSD_SELECT_REGION()), GET_OSD_SATURATION(GET_OSD_SELECT_REGION()));
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_HUE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_HUE(GET_OSD_SELECT_REGION()), _HUE_MAX, _HUE_MIN, _HUE_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);


            break;

        default:
            break;
    }
}

void MenuColorColorSaturationAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SATURATION(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_SATURATION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_SATURATION_ADJUST, GET_OSD_SATURATION(GET_OSD_SELECT_REGION()));
#if(_GLOBAL_HUE_SATURATION == _ON)
            UserAdjustGlobalHueSat(GET_OSD_SYSTEM_SELECT_REGION(), (SWORD)GET_OSD_HUE(GET_OSD_SELECT_REGION()), GET_OSD_SATURATION(GET_OSD_SELECT_REGION()));
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SATURATION(GET_OSD_SELECT_REGION()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_SATURATION(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_GLOBAL_HUE_SATURATION == _ON)
                UserAdjustGlobalHueSat(GET_OSD_SYSTEM_SELECT_REGION(), (SWORD)GET_OSD_HUE(GET_OSD_SELECT_REGION()), GET_OSD_SATURATION(GET_OSD_SELECT_REGION()));
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_SATURATION);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_SATURATION(GET_OSD_SELECT_REGION()), _SATURATION_MAX, _SATURATION_MIN, _SATURATION_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        default:
            break;
    }
}

void MenuAdvanceAspectAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
            }

            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_ADVANCE_ASPECT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _UNSELECT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));
            break;

        case _RIGHT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()) == _OSD_ASPECT_RATIO_5_BY_4)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
                }
                OsdDispSliderAndNumber(_MENU_ADVANCE_ASPECT_ADJUST, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));

                if(g_usAdjustValue != GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()))
                {
                    SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), g_usAdjustValue);
                    OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));
#if(_ASPECT_RATIO_SUPPORT == _ON)
                    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()) == _OSD_ASPECT_RATIO_ORIGIN)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
                }
                OsdDispSliderAndNumber(_MENU_ADVANCE_ASPECT_ADJUST, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));

                if(g_usAdjustValue != GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()))
                {
                    SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), g_usAdjustValue);
                    OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _SELECT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));
#if(_ASPECT_RATIO_SUPPORT == _ON)
                    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()))
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort(), g_usAdjustValue);
                    // Adjust HLW
#if(_ASPECT_RATIO_SUPPORT == _ON)
                    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }

                OsdDispClearArrow(_DOWN);
                SET_OSD_STATE(_MENU_ADVANCE_ASPECT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_ASPECT_RATIO_TYPE, _UNSELECT, GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()));

                if(GET_OSD_ASPECT_RATIO_TYPE(UserAdjustGetSelectRegionPort()) >= _OSD_ASPECT_RATIO_ORIGIN)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ASPECT_RATIO_0);
                }
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceOverScanAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_INPUTPORTDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_OVER_SCAN);
            OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _UNSELECT, GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()));
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_OVER_SCAN_ADJUST, GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()));

#if(_OVERSCAN_SUPPORT == _ON)
                UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK)
            {
                if(g_usBackupValue != GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()))
                {
                    g_usAdjustValue = g_usBackupValue;
                    SET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort(), g_usAdjustValue);
#if(_OVERSCAN_SUPPORT == _ON)
                    UserAdjustResetDisplayByPort(GET_OSD_SYSTEM_DISPLAY_REGION());
#endif
                }
                SET_OSD_STATE(_MENU_ADVANCE_OVER_SCAN);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_OVERSCAN_ONOFF, _UNSELECT, GET_OSD_OVERSCAN_STATUS(UserAdjustGetSelectRegionPort()));
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceOverDriveOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_OD_STATUS();
            SET_OSD_STATE(_MENU_ADVANCE_OD_ONOFF_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_0);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OD_ADJUST);
            break;

        default:
            break;
    }
}


void MenuAdvanceOverDriveGain(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_OD_GAIN();
            SET_OSD_STATE(_MENU_ADVANCE_OD_GAIN_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:

            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_0);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_OD_ADJUST);
            break;

        default:
            break;
    }
}


void MenuAdvanceDdcciAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_DDCCI);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _UNSELECT, GET_OSD_DDCCI_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_DDCCI_STATUS() != _OFF)
            {
                SET_OSD_DDCCI_STATUS(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
                ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS());
                UserCommonDdcciMapping();
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DDCCI_STATUS() != _ON)
            {
                SET_OSD_DDCCI_STATUS(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _SELECT, GET_OSD_DDCCI_STATUS());
                ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS());
                UserCommonDdcciMapping();
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DDCCI_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_DDCCI_STATUS(g_usAdjustValue);
                ScalerMcuDdcciSwitchPort(GET_OSD_DDCCI_STATUS());
                UserCommonDdcciMapping();
            }
            SET_OSD_STATE(_MENU_ADVANCE_DDCCI);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DDCCI_ONOFF, _UNSELECT, GET_OSD_DDCCI_STATUS());

            break;

        default:
            break;
    }
}

void MenuAdvanceUltraVividAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_ULTRA_VIVID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()));
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(((GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()) == _ULTRA_VIVID_H) &&
                (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
               ((GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()) == _ULTRA_VIVID_OFF) &&
                (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
            {
            }
            else
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_ULTRA_VIVID_ADJUST, GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()));

#if(_ULTRA_VIVID_SUPPORT == _ON)
                UserCommonAdjustUltraVivid(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING);
#endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION(), g_usAdjustValue);
#if(_ULTRA_VIVID_SUPPORT == _ON)
                UserCommonAdjustUltraVivid(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING);
#endif // End of #if(_ULTRA_VIVID_SUPPORT == _ON)
            }
            SET_OSD_STATE(_MENU_ADVANCE_ULTRA_VIVID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ULTRA_VIVID_TYPE, _UNSELECT, GET_OSD_ULTRA_VIVID_STATUS(GET_OSD_SELECT_REGION()));

            break;

        default:
            break;
    }
}


void MenuAdvanceDCRAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DCR_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_DCR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _UNSELECT, GET_OSD_DCR_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_DCR_STATUS() != _OFF)
            {
                SET_OSD_DCR_STATUS(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DCR_STATUS() != _ON)
            {
                SET_OSD_DCR_STATUS(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _SELECT, GET_OSD_DCR_STATUS());
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DCR_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_DCR_STATUS(g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DCR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DCR_ONOFF, _UNSELECT, GET_OSD_DCR_STATUS());

            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD0(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_DP_D0_VERSION();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D0_VERSION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
#endif
            break;

        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usItemNum == _MENU_NONE)
            {
                OsdDispDisableOsd();
            }
            else
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_1);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD1(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_DP_D1_VERSION();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D1_VERSION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usItemNum == _MENU_NONE)
            {
                OsdDispDisableOsd();
            }
            else
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_1);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceDpOptionD6(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_DP_D6_VERSION();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D6_VERSION_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            break;

        case _RIGHT_KEY_MESSAGE:

            break;

        case _LEFT_KEY_MESSAGE:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usItemNum == _MENU_NONE)
            {
                OsdDispDisableOsd();
            }
            else
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_1);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_OPTION);
            }
            break;

        default:
            break;
    }
}

void MenuAdvanceDPMstAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_MST())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
            }

            SET_OSD_STATE(_MENU_ADVANCE_DP_MST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _UNSELECT, GET_OSD_DP_MST());
            break;

        case _RIGHT_KEY_MESSAGE:

            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) && (SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT))
            {
                switch(GET_OSD_DP_MST())
                {
                    case _MST_OFF:

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
                        if(GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2)
                        {
                            SET_OSD_DP_MST(_MST_D0);
                        }
                        else
#endif
                        {
#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
                            if(GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2)
                            {
                                SET_OSD_DP_MST(_MST_D1);
                            }
                            else
#endif
                            {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
                                if(GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2)
                                {
                                    SET_OSD_DP_MST(_MST_D6);
                                }
#endif
                            }
                        }

                        break;

                    case _MST_D0:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
                        if(GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2)
                        {
                            SET_OSD_DP_MST(_MST_D1);
                        }
                        else
#endif
                        {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
                            if(GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2)
                            {
                                SET_OSD_DP_MST(_MST_D6);
                            }
#endif
                        }

                        break;

                    case _MST_D1:

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) &&\
    ((_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0) && (_D0_DP_MST_PORT_SUPPORT == _ON)))
                        if(GET_OSD_DP_D6_VERSION() >= _DP_VER_1_DOT_2)
                        {
                            SET_OSD_DP_MST(_MST_D6);
                        }
#endif

                        break;

                    default:
                        break;
                }
            }
            else
            {
                SET_OSD_DP_MST(_MST_OFF);
            }

            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_MST_ADJUST, GET_OSD_DP_MST());

            break;

        case _LEFT_KEY_MESSAGE:

            if((GET_OSD_DISPLAY_MODE() == _OSD_DM_1P) && (SysSourceGetScanType() == _SOURCE_SWITCH_FIXED_PORT))
            {
                switch(GET_OSD_DP_MST())
                {
                    case _MST_D6:

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
                        if(GET_OSD_DP_D1_VERSION() >= _DP_VER_1_DOT_2)
                        {
                            SET_OSD_DP_MST(_MST_D1);
                        }
                        else
#endif
                        {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
                            if(GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2)
                            {
                                SET_OSD_DP_MST(_MST_D0);
                            }
                            else
#endif
                            {
                                SET_OSD_DP_MST(_MST_OFF);
                            }
                        }

                        break;

                    case _MST_D1:

#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
                        if(GET_OSD_DP_D0_VERSION() >= _DP_VER_1_DOT_2)
                        {
                            SET_OSD_DP_MST(_MST_D0);
                        }
                        else
#endif
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }

                        break;

                    case _MST_D0:
                        SET_OSD_DP_MST(_MST_OFF);
                        break;

                    default:
                        break;
                }
            }
            else
            {
                SET_OSD_DP_MST(_MST_OFF);
            }

            OsdDispSliderAndNumber(_MENU_ADVANCE_DP_MST_ADJUST, GET_OSD_DP_MST());

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_MST())
            {
                // g_usAdjustValue = g_usBackupValue;
                SET_OSD_DP_MST(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_MST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_MST_TYPE, _UNSELECT, GET_OSD_DP_MST());
            break;

        default:
            break;
    }
}

void MenuAdvanceCloneAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_CLONE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

#if(_MULTI_DISPLAY_MAX != 0x01)
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                if(g_usBackupValue != GET_OSD_CLONE_MODE_MTP())
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                }
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE_MTP());
            }
            else
#endif
            {
                if(g_usBackupValue != GET_OSD_CLONE_MODE_1P())
                {
                    SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                }
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, GET_OSD_CLONE_MODE_1P());
            }
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, GET_OSD_CLONE_MODE_MTP());
                if(GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_D2)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_1);
                }
                else if(GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_D6)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_2);
                }
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE_MTP());
            }
            else
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, GET_OSD_CLONE_MODE_1P());
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE_1P());
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DISPLAY_MODE() != _OSD_DM_1P)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, GET_OSD_CLONE_MODE_MTP());
                if(GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_D1)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_0);
                }
                else if(GET_OSD_CLONE_MODE_MTP() == _OSD_CLONE_MTP_D5)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLONE_1);
                }
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE_MTP());
            }
            else
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_CLONE_ADJUST, GET_OSD_CLONE_MODE_1P());
                OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _SELECT, GET_OSD_CLONE_MODE_1P());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_CLONE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_CLONE_TYPE, _UNSELECT, 0);
            break;

        default:
            break;
    }
}

void MenuAdvanceFreeSyncAdjust(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_FREE_SYNC_STATUS())
            {
                SET_OSD_FREE_SYNC_STATUS(g_usBackupValue);
                ScalerSyncSetFREESYNCSupport(GET_OSD_FREE_SYNC_STATUS());
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREE_SYNC_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:

            if(g_usBackupValue != _OFF)
            {
                g_usBackupValue = _OFF;
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, g_usBackupValue);
            }

            break;

        case _LEFT_KEY_MESSAGE:

            if(g_usBackupValue != _ON)
            {
                g_usBackupValue = _ON;
                OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _SELECT, g_usBackupValue);
            }

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_FREESYNC);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FREESYNC_ONOFF_TYPE, _UNSELECT, GET_OSD_FREE_SYNC_STATUS());
            break;

        default:
            break;
    }
#endif
}

void MenuAdvanceSingleDpEDID(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = UserCommonNVRamGetSystemData(_DP_EDID_SELECT);
            SET_OSD_STATE(_MENU_ADVANCE_SINGLE_DP_EDID_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            break;

        case _RIGHT_KEY_MESSAGE:
#if (_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DUAL_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuOptionSetting(_OPTION_DUAL_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DUAL_DP_EDID);
#endif
            break;

        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_EDID);
            break;

        default:
            break;
    }
}
void MenuAdvanceDualDpEDID(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT);
            SET_OSD_STATE(_MENU_ADVANCE_DUAL_DP_EDID_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DUAL_DP_EDID_TYPE, _SELECT, UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_SINGLE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, GET_OSD_OD_STATUS());
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SINGLE_DP_EDID);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_EDID);
            break;

        default:
            break;
    }
}


void MenuAdvanceSingleDPEdidAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_EDID_SELECT))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                UserAdjustDpEdidTableSwitch(_D0_INPUT_PORT);
                UserAdjustDpEdidTableSwitch(_D1_INPUT_PORT);
                UserAdjustDpEdidTableSwitch(_D6_INPUT_PORT);
            }

            SET_OSD_STATE(_MENU_ADVANCE_SINGLE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            break;

        case _RIGHT_KEY_MESSAGE:
            if(UserCommonNVRamGetSystemData(_DP_EDID_SELECT) != _DP_EDID_4K2K_60HZ)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_SINGLE_DP_EDID_ADJUST, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(UserCommonNVRamGetSystemData(_DP_EDID_SELECT) != _DP_EDID_1080P)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_SINGLE_DP_EDID_ADJUST, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != UserCommonNVRamGetSystemData(_DP_EDID_SELECT))
            {
                UserCommonNVRamSetSystemData(_DP_EDID_SELECT, g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_SINGLE_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_DP_EDID_SELECT));
            break;

        default:
            break;
    }
}


void MenuAdvanceDualDPEdidAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                UserAdjustDpEdidTableSwitch(_D7_INPUT_PORT);
            }

            SET_OSD_STATE(_MENU_ADVANCE_DUAL_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DUAL_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
            break;

        case _RIGHT_KEY_MESSAGE:
            if(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT) != _DUAL_DP_EDID_4K2K_144HZ)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_DUAL_DP_EDID_ADJUST, UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT) != _DUAL_DP_EDID_5K3K_60HZ)
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_DUAL_DP_EDID_ADJUST, UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT))
            {
                UserCommonNVRamSetSystemData(_DUAL_DP_EDID_SELECT, g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DUAL_DP_EDID);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DUAL_DP_EDID_TYPE, _UNSELECT, UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
            break;

        default:
            break;
    }
}
#if(_EDID_SWITCH_BY_PORT_ITEM == _ON)
void MenuAdvanceEdidAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                    if((g_usAdjustValue == 6)&&(SysRegionGetPortType(_DISPLAY_MODE_1P) == _D7_INPUT_PORT)&&(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P))//D7 =>DD_PORT
                    {
                        SET_OSD_STATE(_MENU_ADVANCE_EDID_DX_ADJUST);
                        OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_PRE_SELECT);
                        g_usBackupValue = UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT);
                        OsdDispMainMenuOptionSetting(_OPTION_DUAL_DP_EDID_TYPE,_SELECT,UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
                    }
                    else if(SysRegionGetPortType(_DISPLAY_MODE_1P) != _D7_INPUT_PORT)
                    {
                        SET_OSD_STATE(_MENU_ADVANCE_EDID_DX_ADJUST);
                        OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_PRE_SELECT);
                        g_usBackupValue = UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue);
                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_SELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                    }
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 0)
                        break;
#endif
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 1)
                        break;
#endif
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 2)
                        break;
#endif
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 3)
                        break;
#endif
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 4)
                        break;
#endif
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
                    if(g_usAdjustValue == 5)
                        break;
#endif
                    SET_OSD_STATE(_MENU_ADVANCE_EDID_DX_ADJUST);
                    OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_PRE_SELECT);
                    g_usBackupValue = UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue);
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_SELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                    break;
                default:
                    break;
            }


            break;

        case _RIGHT_KEY_MESSAGE:
            if(g_usAdjustValue == 3)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_1);
            }
            if(g_usAdjustValue < 7)//D0-D7
            {
                g_usAdjustValue++;
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(),_OUTSUBSET);

                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                DebugMessageOsd("g_usAdjustValue",g_usAdjustValue);
                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
                {
                    case _PORT_DP:
                        if((g_usAdjustValue == 6)&&(SysRegionGetPortType(_DISPLAY_MODE_1P) == _D7_INPUT_PORT)&&(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P))//D7 =>DD_PORT
                        {
                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DUAL_DP_EDID);
                            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
                        }
                        else if(SysRegionGetPortType(_DISPLAY_MODE_1P) != _D7_INPUT_PORT)
                        {
                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SINGLE_DP_EDID);
                            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                        }
                        break;

                    case _PORT_HDMI20:
                    case _PORT_HDMI:
                    case _PORT_MHL:
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 0)
                            break;
#endif
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 1)
                            break;
#endif
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        DebugMessageOsd("D2 g_usAdjustValue",g_usAdjustValue);
                        if(g_usAdjustValue == 2)
                            break;
#endif
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 3)
                            break;
#endif
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 4)
                            break;
#endif
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 5)
                            break;
#endif
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_EDID_D0+g_usAdjustValue);
                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                        break;
                    default:
                        break;
                }

            }

            break;

        case _LEFT_KEY_MESSAGE:
            if(g_usAdjustValue == 4)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_EDID_PORT_0);
            }
            if(g_usAdjustValue > 0)//D0-D7
            {
                g_usAdjustValue--;
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(),_OUTSUBSET);

                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
                {
                    case _PORT_DP:
                        if((g_usAdjustValue == 6)&&(SysRegionGetPortType(_DISPLAY_MODE_1P) == _D7_INPUT_PORT)&&(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P))//D7 =>DD_PORT
                        {
                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DUAL_DP_EDID);
                            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
                        }
                        else if(SysRegionGetPortType(_DISPLAY_MODE_1P) != _D7_INPUT_PORT)
                        {
                            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_SINGLE_DP_EDID);
                            OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));
                        }
                        break;

                    case _PORT_HDMI20:
                    case _PORT_HDMI:
                    case _PORT_MHL:
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 0)
                            break;
#endif
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 1)
                            break;
#endif
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 2)
                            break;
#endif
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 3)
                            break;
#endif
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 4)
                            break;
#endif
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _OFF)
                        if(g_usAdjustValue == 5)
                            break;
#endif
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDMI_EDID_D0+g_usAdjustValue);
                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT+g_usAdjustValue));
                        break;
                    default:
                        break;
                }
            }

            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_DP_EDID);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(),_OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_EDID_PORT_0);
            break;

        default:
            break;
    }



}
BYTE MenuAdvanceHdmiEdidAdjCheck(EnumSourceSearchPort ucPort , EnumHDMIEDIDSelection ucoption , BYTE ucKeyMessage)
{
    if(ucKeyMessage == _RIGHT_KEY_MESSAGE)
    {
        if(ucoption < _HDMI_EDID_2)
        {
            ucoption++;
        }
        switch(ucPort)
        {
            case _D0_INPUT_PORT:
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 2;
#endif
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 0;
#endif
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 1;
#endif

                break;
            case _D1_INPUT_PORT:
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 2;
#endif
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 0;
#endif
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 1;
#endif
                break;
            case _D2_INPUT_PORT:
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 2;
#endif
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 0;
#endif
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 1;
#endif

                break;
            case _D3_INPUT_PORT:
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 2;
#endif
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 0;
#endif
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 1;
#endif
                break;
            case _D4_INPUT_PORT:
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 2;
#endif
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 0;
#endif
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 1;
#endif

                break;
            case _D5_INPUT_PORT:
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 2;
#endif
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 0;
#endif
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 1;
#endif

                break;
        }

    }
    else if (ucKeyMessage == _LEFT_KEY_MESSAGE)
    {

        if(ucoption > _HDMI_EDID_0)
           ucoption--;

        switch(ucPort)
        {
            case _D0_INPUT_PORT:
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 0;
#endif
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 2;
#endif
#if(_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 1;
#endif

                break;
            case _D1_INPUT_PORT:
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 0;
#endif
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 2;
#endif
#if(_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 1;
#endif

                break;
            case _D2_INPUT_PORT:
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 0;
#endif
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 2;
#endif
#if(_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 1;
#endif

                break;
            case _D3_INPUT_PORT:

#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 0;
#endif
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 2;
#endif
#if(_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 1;
#endif

                break;
            case _D4_INPUT_PORT:
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 0;
#endif
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 2;
#endif
#if(_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 1;
#endif

                break;
            case _D5_INPUT_PORT:

#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST)
                if(ucoption == 1)
                    ucoption = 0;
#endif
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST)
                if(ucoption == 0)
                    ucoption = 2;
#endif
#if(_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)
                if(ucoption == 2)
                    ucoption = 1;
#endif

                break;
        }
    }
    return ucoption;

}
void MenuAdvanceEdidDXAdjust(void)
{
    DebugMessageOsd("g_usBackupValue",g_usBackupValue);
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                     if(g_usAdjustValue == 6)//D7=DP_PORT
                    {
                        if(g_usBackupValue != UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT))
                        {
                            UserCommonNVRamSetSystemData(_DUAL_DP_EDID_SELECT, g_usBackupValue);
                            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            UserAdjustDpEdidTableSwitch(_D7_INPUT_PORT_TYPE);
                        }
                    }
                    else
                    {
                        if(g_usBackupValue != UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue))
                        {
                            UserCommonNVRamSetSystemData(_EDID_D0_SELECT + g_usAdjustValue, g_usBackupValue);
                            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);
                            UserAdjustDpEdidTableSwitch(_D0_INPUT_PORT+g_usAdjustValue);
                        }
                    }
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                    if(g_usBackupValue != UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue))
                    {
                        UserCommonNVRamSetSystemData(_EDID_D0_SELECT + g_usAdjustValue, g_usBackupValue);

                        DebugMessageOsd("!!!!!Into OSD Change, Nvram number", UserCommonNVRamGetSystemData(_EDID_D0_SELECT + g_usAdjustValue));

                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_SYSTEMDATA_MSG);

                        // Add EDID DDCRAM Switch & HPD event
#if (_HDMI_MULTI_EDID_SUPPORT == _ON)
                        DebugMessageOsd("!!!!!Into switch edid function", g_usBackupValue);
                        UserCommonInterfaceHDMISwithEdid(_D0_INPUT_PORT + g_usAdjustValue, g_usBackupValue);
#endif
                    }
                    break;
                default:
                    break;
            }

            break;

        case _RIGHT_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                    if(g_usAdjustValue == 6)//D7=DP_PORT
                    {
                        if(g_usBackupValue < _DUAL_DP_EDID_4K2K_144HZ)
                            g_usBackupValue++;

                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, g_usBackupValue);
                    }
                    else
                    {
                        if(g_usBackupValue < _DP_EDID_4K2K_60HZ)
                            g_usBackupValue++;

                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, g_usBackupValue);
                    }
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                    g_usBackupValue = MenuAdvanceHdmiEdidAdjCheck((_D0_INPUT_PORT + g_usAdjustValue),g_usBackupValue,GET_KEYMESSAGE());
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, g_usBackupValue);
                    break;
                default:
                    break;
            }


            break;

        case _LEFT_KEY_MESSAGE:
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                     if(g_usAdjustValue == 6)//D7=DP_PORT
                    {
                        if(g_usBackupValue > _DUAL_DP_EDID_5K3K_60HZ)
                             g_usBackupValue--;

                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE, _SELECT, g_usBackupValue);
                    }
                    else
                    {
                        if(g_usBackupValue > _DP_EDID_1080P)
                          g_usBackupValue--;

                       OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_SELECT,g_usBackupValue);
                    }

                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                    g_usBackupValue = MenuAdvanceHdmiEdidAdjCheck((_D0_INPUT_PORT + g_usAdjustValue),g_usBackupValue,GET_KEYMESSAGE());
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_SELECT,g_usBackupValue);
                    break;
                default:
                    break;
            }

            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_EDID_ADJUST);
            OsdDispMainMenuItemSelection((g_usAdjustValue % 4), _OSD_SELECT);
            switch(GET_PORT_TYPE(SysSourceGetInputPortType(_D0_INPUT_PORT + g_usAdjustValue)))
            {
                case _PORT_DP:
                    if(g_usAdjustValue == 6)//D7==DP_PORT
                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_DUAL_DP_EDID_SELECT));
                    else
                        OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT+g_usAdjustValue));
                    break;

                case _PORT_HDMI20:
                case _PORT_HDMI:
                case _PORT_MHL:
                    OsdDispMainMenuOptionSetting(_OPTION_DP_EDID_TYPE,_UNSELECT,UserCommonNVRamGetSystemData(_EDID_D0_SELECT+g_usAdjustValue));
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }

}

#endif

void MenuAdvanceDpLaneCountD0(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            g_usBackupValue = GET_OSD_DP_D0_LANE_MODE();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D0_LANE_COUNT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D1_LANE_MODE());
#elif(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D6_LANE_MODE());
#endif
            break;

        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_LANE_COUNT);
            break;

        default:
            break;
    }
}

void MenuAdvanceDpLaneCountD1(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            g_usBackupValue = GET_OSD_DP_D1_LANE_MODE();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D1_LANE_COUNT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D6_LANE_MODE());
#endif
            break;

        case _LEFT_KEY_MESSAGE:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D0_LANE_MODE());
#endif
            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_LANE_COUNT);
            break;
        default:
            break;
    }
}

void MenuAdvanceDpLaneCountD6(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            g_usBackupValue = GET_OSD_DP_D6_LANE_MODE();
            SET_OSD_STATE(_MENU_ADVANCE_DP_D6_LANE_COUNT_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:

            break;

        case _LEFT_KEY_MESSAGE:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D1_LANE_MODE());
#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D0_LANE_MODE());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_DP_LANE_COUNT);
            break;

        default:
            break;
    }
}

#if(_ULTRA_HDR_SUPPORT == _ON)
void MenuAdvanceHdrMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort());

            SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _SELECT, GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()));
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_DARK_ENHANCE_ON_OFF, _UNSELECT, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_ON_OFF);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR);
            SET_OSD_STATE(_MENU_ADVANCE_HDR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_3);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_ADJUST);
            break;

        default:
            break;
    }
}

void MenuAdvanceHdrDarkEnhanceOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort());
            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF_ADJUST);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DARK_ENHANCE_ON_OFF, _SELECT, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_MODE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_HDR);
            SET_OSD_STATE(_MENU_ADVANCE_HDR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_3);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_ADJUST);
            break;

        default:
            break;
    }
}
#endif

#if(_FALSE_COLOR_SUPPORT == _ON)
void MenuAdvanceFalseColorAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_FALSE_COLOR_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }


            g_usBackupValue = GET_OSD_FALSE_COLOR_STATUS();
            if(GET_OSD_FALSE_COLOR_STATUS() == _OSD_FALSE_COLOR_USER)
            {
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
                SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR_USER);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_UP);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_FALSE_COLOR_USER);
                OsdDispFalseColorMenu();
                g_usItemNum=0;
                OsdWindowDrawingByFontBorder(_OSD_WINDOW_2, ROW(14), COL(_DOWN_ICON_START_COL + 2 * g_usItemNum), WIDTH(1), HEIGHT(2), _CP_BLUE_120);
            }
            else
            {
                OsdDispClearArrow(_DOWN);
                SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuOptionSetting(_OPTION_FALSE_COLOR_TYPE, _UNSELECT, GET_OSD_FALSE_COLOR_STATUS());
            }
            // function adjust
            UserAdjustFalseColor(GET_OSD_SELECT_REGION(), GET_OSD_FALSE_COLOR_STATUS());
            if(GET_OSD_FALSE_COLOR_STATUS() == _OSD_FALSE_COLOR_OFF)
            {
                UserInterfaceAdjustInitialColorProc(GET_OSD_DISPLAY_MODE()); // IT IS MUST BE DONE
            }
            else
            {
                // GColor Temperature, Brightness, global hue/Saturation, PCM, Uniformity, Gamma, IAPS Gain, 3D Gamma
                // ScalerColorBrightnessEnable(_FUNCTION_ON);
                // UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), 0x800);
                // UserAdjustBrightness(GET_OSD_SYSTEM_SELECT_REGION(), 0x200);
            }
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_FALSE_COLOR_ADJUST, GET_OSD_FALSE_COLOR_STATUS());
            if(GET_OSD_FALSE_COLOR_STATUS() >= _OSD_FALSE_COLOR_USER)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_0);
            }
            OsdDispMainMenuOptionSetting(_OPTION_FALSE_COLOR_TYPE, _SELECT, GET_OSD_FALSE_COLOR_STATUS());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_FALSE_COLOR_STATUS(g_usBackupValue);
            OsdDispClearArrow(_DOWN);
            SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_FALSE_COLOR_TYPE, _UNSELECT, GET_OSD_FALSE_COLOR_STATUS());

            if(GET_OSD_FALSE_COLOR_STATUS() >= _OSD_FALSE_COLOR_USER)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_0);
            }


            break;

        default:
            break;
    }
}
void MenuAdvanceFalseColorUser(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR_USER_ADJUST);
            g_usAdjustValue=GET_OSD_FALSE_COLOR_LEVEL(g_usItemNum);
            OsdWindowDrawingByFontBorder(_OSD_WINDOW_3, ROW(18), COL(_DOWN_ICON_START_COL + 2 * g_usAdjustValue), WIDTH(1), HEIGHT(2), _CP_PINK);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            g_usItemNum=OsdDisplayDetOverRange(g_usItemNum, _FALSE_COLOR_ADJUSTABLE_MAX, 0, _OFF);

            OsdWindowDrawingByFontBorder(_OSD_WINDOW_2, ROW(14), COL(_DOWN_ICON_START_COL + 2 * g_usItemNum), WIDTH(1), HEIGHT(2), _CP_BLUE_120);
            break;
            break;

        case _EXIT_KEY_MESSAGE:

            OsdFuncCloseWindow(_OSD_WINDOW_2);
            OsdFuncCloseWindow(_OSD_WINDOW_3);

            OsdFuncClearOsd(12, (_DOWN_ICON_START_COL - 2), WIDTH(42), HEIGHT(8));
            OsdFuncChangeColor1Bit(12, (_DOWN_ICON_START_COL - 2), WIDTH(42), HEIGHT(8), _CP_BG, _FONTFROM_0_255);

            SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_2);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_FALSE_COLOR_TYPE, _UNSELECT, GET_OSD_FALSE_COLOR_STATUS());
            if(GET_OSD_FALSE_COLOR_STATUS() > _OSD_FALSE_COLOR_MODE3)
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_1);
            }
            else
            {
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_FALSE_COLOR_0);
            }

            break;

        default:
            break;
    }
}
void MenuAdvanceFalseColorUserAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

            SET_OSD_FALSE_COLOR_LEVEL(g_usItemNum, g_usAdjustValue);
            OsdFuncCloseWindow(_OSD_WINDOW_3);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

            SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR_USER);
            OsdDispFalseColorMenu();

            if(g_usItemNum == 0)
            {
                UserAdjustFalseColorUserDefine(GET_OSD_SELECT_REGION(), 0, g_usAdjustValue, g_usAdjustValue, GET_OSD_FALSE_COLOR_LEVEL(1));
            }
            else if(g_usItemNum >= _FALSE_COLOR_ADJUSTABLE_MAX)
            {
                UserAdjustFalseColorUserDefine(GET_OSD_SELECT_REGION(), _FALSE_COLOR_ADJUSTABLE_MAX, GET_OSD_FALSE_COLOR_LEVEL(_FALSE_COLOR_ADJUSTABLE_MAX - 1), g_usAdjustValue, g_usAdjustValue); // _FALSE_COLOR_ADJUSTABLE_MAX
            }
            else
            {
                UserAdjustFalseColorUserDefine(GET_OSD_SELECT_REGION(), g_usItemNum, GET_OSD_FALSE_COLOR_LEVEL(g_usItemNum - 1), g_usAdjustValue, GET_OSD_FALSE_COLOR_LEVEL(g_usItemNum + 1));
            }
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            g_usAdjustValue=OsdDisplayDetOverRange(g_usAdjustValue, _FALSE_COLOR_ADJUSTABLE_COLOR_COUNT, 0, _OFF);

            OsdWindowDrawingByFontBorder(_OSD_WINDOW_3, ROW(18), COL(_DOWN_ICON_START_COL + 2 * g_usAdjustValue), WIDTH(1), HEIGHT(2), _CP_PINK);
            break;

        case _EXIT_KEY_MESSAGE:
            // SET_OSD_FALSE_COLOR_LEVEL(g_usItemNum, g_usAdjustValue);
            OsdFuncCloseWindow(_OSD_WINDOW_3);
            SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            SET_OSD_STATE(_MENU_ADVANCE_FALSE_COLOR_USER);
            OsdDispFalseColorMenu();

            break;

        default:
            break;
    }
}
#endif

void MenuAudioVolumeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_AUDIO_VOLUME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME, GET_OSD_VOLUME());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_VOLUME_ADJUST, GET_OSD_VOLUME());

            if((GET_OSD_VOLUME_MUTE() == _ON) && (g_usBackupValue == GET_OSD_VOLUME()))
            {
                // RTDOsdDispOsdFunctionAdjust(_MENU_AUDIO_MUTE_ON_OFF);
                SET_OSD_VOLUME_MUTE(_OFF);
            }
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_VOLUME(g_usAdjustValue);
#if(_AUDIO_SUPPORT == _ON)
                UserAdjustAudioVolume(GET_OSD_VOLUME());
#endif
            }
            SET_OSD_STATE(_MENU_AUDIO_VOLUME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), GET_OSD_VOLUME(), _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VOLUME(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        default:
            break;
    }
}

void MenuAudioMuteOnOff(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME_MUTE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_AUDIO_MUTE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_MUTE_ON_OFF, GET_OSD_VOLUME_MUTE());
#if(_AUDIO_SUPPORT == _ON)
            UserAdjustAudioMuteSwitch();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VOLUME_MUTE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_VOLUME_MUTE(g_usAdjustValue);
#if(_AUDIO_SUPPORT == _ON)
                UserAdjustAudioMuteSwitch();
#endif
            }
            SET_OSD_STATE(_MENU_AUDIO_MUTE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_MUTE_ONOFF, _UNSELECT, GET_OSD_VOLUME_MUTE());
            break;

        default:
            break;
    }
}

void MenuAudioStandAlongSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_STAND_ALONE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_AUDIO_STAND_ALONE() == _ON)
            {
                SET_OSD_AUDIO_STAND_ALONE(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
            }
            break;

        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_AUDIO_STAND_ALONE() == _OFF)
            {
                SET_OSD_AUDIO_STAND_ALONE(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _SELECT, GET_OSD_AUDIO_STAND_ALONE());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_STAND_ALONE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_AUDIO_STAND_ALONE(g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_AUDIO_STAND_ALONG);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_STAND_ALONG_ONOFF, _UNSELECT, GET_OSD_AUDIO_STAND_ALONE());
            break;

        default:
            break;
    }
}

void MenuAudioAudioSourceSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_SOURCE())
            {
                // SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
            }

            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_AUDIO_AUDIO_SOURCE_SELECT, GET_OSD_AUDIO_SOURCE());
            if(g_usAdjustValue != GET_OSD_AUDIO_SOURCE())
            {
                if((g_usAdjustValue / 4) != (GET_OSD_AUDIO_SOURCE() / 4))
                {
                    OsdDispMainMenuIconPage(_DOWN, (_ICON_PAGE_AUDIO_SOURCE_0 + (g_usAdjustValue / 4)));
                }
                SET_OSD_AUDIO_SOURCE(g_usAdjustValue);
                // call function to active audio source select
                OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _SELECT, GET_OSD_AUDIO_SOURCE());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_AUDIO_SOURCE())
            {
                if((g_usBackupValue / 4) != (GET_OSD_AUDIO_SOURCE() / 4))
                {
                    OsdDispMainMenuIconPage(_DOWN, (_ICON_PAGE_AUDIO_SOURCE_0 + (g_usBackupValue / 4)));
                }
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_AUDIO_SOURCE(g_usAdjustValue);
                // call function to active audio source select
            }
            SET_OSD_STATE(_MENU_AUDIO_AUDIO_SOURCE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_AUDIO_SOURCE, _UNSELECT, GET_OSD_AUDIO_SOURCE());
            break;

        default:
            break;
    }
}

void MenuAudioSoundModeSelect(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_AUDIO_SOUND_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuOtherMenuTimeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_TIME_OUT())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME, GET_OSD_TIME_OUT());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_MENU_TIME_ADJUST, GET_OSD_TIME_OUT());
            ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_TIME_OUT())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_TIME_OUT(g_usAdjustValue);
                ScalerTimerReactiveTimerEvent(SEC(GET_OSD_TIME_OUT()), _USER_TIMER_EVENT_OSD_DISABLE);
            }
            SET_OSD_STATE(_MENU_OTHER_MENU_TIME);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TIME_OUT(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TIMEOUT_MAX, _OSD_TIMEOUT_MIN, _OSD_TIMEOUT_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            break;

        default:
            break;
    }
}

void MenuOtherOsdHPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HPOS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS, GET_OSD_HPOS());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_HPOS_ADJUST, GET_OSD_HPOS());
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_HPOS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_HPOS(g_usAdjustValue);
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            }
            SET_OSD_STATE(_MENU_OTHER_OSD_HPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_HPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_H_POS_MAX, _OSD_H_POS_MIN, _OSD_H_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuOtherOsdVPosAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VPOS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS, GET_OSD_VPOS());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_OSD_VPOS_ADJUST, GET_OSD_VPOS());
            OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_VPOS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_VPOS(g_usAdjustValue);
                OsdDispSetPosition(_POS_PERCENT, _OSD_POSITION_GLOBAL_A, GET_OSD_HPOS(), GET_OSD_VPOS());
            }
            SET_OSD_STATE(_MENU_OTHER_OSD_VPOS);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_VPOS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_V_POS_MAX, _OSD_V_POS_MIN, _OSD_V_POS_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuOtherLanguageAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LANGUAGE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_LANGUAGE_ADJUST, GET_OSD_LANGUAGE());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_LANGUAGE())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_LANGUAGE(g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_OTHER_LANGUAGE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        default:
            break;
    }
}

void MenuOtherTransparencyAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_TRANSPARENCY_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY, GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_TRNASPARENCY_ADJUST, GET_OSD_TRANSPARENCY_STATUS());
            OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_TRANSPARENCY_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_TRANSPARENCY_STATUS(g_usAdjustValue);
                OsdFuncTransparency(GET_OSD_TRANSPARENCY_STATUS());
            }
            SET_OSD_STATE(_MENU_OTHER_TRNASPARENCY);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_OSD_TRANSPARENCY_STATUS(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(g_usAdjustValue, _OSD_TRANSPARENCY_MAX, _OSD_TRANSPARENCY_MIN, _OSD_TRANSPARENCY_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuOtherRotateAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != g_usAdjustValue)
            {
                SET_OSD_ROTATE_STATUS(g_usAdjustValue);
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_ROTATE_ADJUST, g_usAdjustValue);
            if(g_usAdjustValue != GET_OSD_ROTATE_STATUS())
            {
                SET_OSD_ROTATE_STATUS(g_usAdjustValue);
#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
                OsdDispOsdRotateSwitch();
#endif
                OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _SELECT, GET_OSD_ROTATE_STATUS());
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_ROTATE_STATUS())
            {
                // g_usAdjustValue = g_usBackupValue;
                SET_OSD_ROTATE_STATUS(g_usBackupValue);

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
                OsdDispOsdRotateSwitch();
#endif
            }
            SET_OSD_STATE(_MENU_OTHER_ROTATE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_ROTATE_ADJUST, _UNSELECT, GET_OSD_ROTATE_STATUS());

            break;

        default:
            break;
    }
}

void MenuOtherSelectRegionWidthAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SELECT_REGION_WIDTH())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_BORDER_WIDTH);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_BORDER_WIDTH, GET_OSD_SELECT_REGION_WIDTH());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_BORDER_WIDTH_ADJUST, GET_OSD_SELECT_REGION_WIDTH());

#if(_BORDER_WINDOW_SUPPORT == _ON)
            UserInterfaceAdjustBorderWindow(_DB_APPLY_NO_POLLING);
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SELECT_REGION_WIDTH())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_SELECT_REGION_WIDTH(g_usAdjustValue);

#if(_BORDER_WINDOW_SUPPORT == _ON)
                UserInterfaceAdjustBorderWindow(_DB_APPLY_NO_POLLING);
#endif
            }
            SET_OSD_STATE(_MENU_OTHER_BORDER_WIDTH);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_OTHER_BORDER_WIDTH, GET_OSD_SELECT_REGION_WIDTH());
            break;

        default:
            break;
    }
}

void MenuOtherSelectRegionColorAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SELECT_REGION_COLOR())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_OTHER_BORDER_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_BORDER_COLOR, _UNSELECT, GET_OSD_SELECT_REGION_COLOR());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_OTHER_BORDER_COLOR_ADJUST, GET_OSD_SELECT_REGION_COLOR());
            if(g_usAdjustValue != GET_OSD_SELECT_REGION_COLOR())
            {
                SET_OSD_SELECT_REGION_COLOR(g_usAdjustValue);
                OsdDispMainMenuOptionSetting(_OPTION_BORDER_COLOR, _SELECT, GET_OSD_SELECT_REGION_COLOR());

#if(_BORDER_WINDOW_SUPPORT == _ON)
                UserInterfaceAdjustBorderWindow(_DB_APPLY_NO_POLLING);
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SELECT_REGION_COLOR())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_SELECT_REGION_COLOR(g_usAdjustValue);

#if(_BORDER_WINDOW_SUPPORT == _ON)
                UserInterfaceAdjustBorderWindow(_DB_APPLY_NO_POLLING);
#endif
            }
            SET_OSD_STATE(_MENU_OTHER_BORDER_COLOR);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_BORDER_COLOR, _UNSELECT, GET_OSD_SELECT_REGION_COLOR());
            break;

        default:
            break;
    }
}

void MenuColorColortempUserR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_R();

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_R, GET_COLOR_TEMP_TYPE_USER_R());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
            break;
        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
            g_usBackupValue = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());
            break;

        default:
            break;
    }
}

void MenuColorColortempUserG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_G();

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_G, GET_COLOR_TEMP_TYPE_USER_G());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_B, GET_COLOR_TEMP_TYPE_USER_B());
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
            g_usBackupValue = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());
            break;

        default:
            break;
    }
}


void MenuColorColortempUserB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_COLOR_TEMP_TYPE_USER_B();

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_ADJUST_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_B, GET_COLOR_TEMP_TYPE_USER_B());
            break;

        case _RIGHT_KEY_MESSAGE:

            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_TEMPERATURE_ADJUST);
            OsdDispClearSliderAndNumber();
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_TEMPRATURE_TYPE, _SELECT, GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_TEMPRATURE_1);
            OsdDispMainMenuItemIndication(_ITEM_2, 9, _OSD_SELECT);
            g_usBackupValue = GET_COLOR_TEMP_TYPE(GET_OSD_SELECT_REGION());
            break;

        default:
            break;
    }
}

void MenuColorColortempUserAdjustR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_R, GET_COLOR_TEMP_TYPE_USER_R());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_R, GET_COLOR_TEMP_TYPE_USER_R());

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_R())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_COLOR_TEMP_TYPE_USER_R(g_usAdjustValue);

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_R(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_R(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuColorColortempUserAdjustG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_G, GET_COLOR_TEMP_TYPE_USER_G());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_G, GET_COLOR_TEMP_TYPE_USER_G());

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_G())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_COLOR_TEMP_TYPE_USER_G(g_usAdjustValue);

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_G(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_G(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuColorColortempUserAdjustB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_COLORPROC_MSG);
            }

            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_B, GET_COLOR_TEMP_TYPE_USER_B());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_TEMP_USER_ADJUST_B, GET_COLOR_TEMP_TYPE_USER_B());

#if(_CONTRAST_SUPPORT == _ON)
            UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_COLOR_TEMP_TYPE_USER_B())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_COLOR_TEMP_TYPE_USER_B(g_usAdjustValue);

#if(_CONTRAST_SUPPORT == _ON)
                UserAdjustContrast(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_CONTRAST(GET_OSD_SELECT_REGION()));
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_TEMP_USER_B);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_TEMPERATURE_USER);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_COLOR_TEMP_TYPE_USER_B(), _USER_RGB_MAX, _USER_RGB_MIN, _USER_RGB_CENTER);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), GET_COLOR_TEMP_TYPE_USER_B(), (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserR(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_R);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), _SIXCOLOR_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _LEFT_KEY_MESSAGE:

            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserY(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_Y);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), _SIXCOLOR_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserG(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_G);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), _SIXCOLOR_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserC(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_C);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), _SIXCOLOR_C);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserB(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_B);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), _SIXCOLOR_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserM(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            SET_OSD_SIX_COLOR(_SIXCOLOR_M);
            OsdDisplaySixColorGetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), _SIXCOLOR_M);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;
        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            break;

        case _EXIT_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION());
            SET_OSD_STATE(_MENU_COLOR_EFFECT_ADJUST);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_EFFECT_TYPE, _SELECT, GET_OSD_COLOR_EFFECT(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_EFFECT_1);
            OsdDispMainMenuItemIndication(_ITEM_3, 9, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserRHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);


            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserCHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserCSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMHue(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_HUE();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
            OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMSat(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT_ADJUST);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_DOWN);
            g_usBackupValue = GET_OSD_SIX_COLOR_SATURATION();
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
            OsdDispMainMenuItemIndication(_ITEM_1, 2, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);


            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());

#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());

#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);

            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserRSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_R_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_R_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_0, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserYSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_Y_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_Y_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_1, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserGHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserGSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_G_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_G_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_2, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}


void MenuColorColorEffcUserCHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserCSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_C_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_C_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_3, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_0);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_3, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserBSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_B_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_B_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_4, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMHueAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_HUE_ADJUST, GET_OSD_SIX_COLOR_HUE());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_HUE())
            {
                SET_OSD_SIX_COLOR_HUE(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_HUE);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_HUE);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorEffcUserMSatAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_REGIONDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_COLOR_EFF_USER_M_SAT_ADJUST, GET_OSD_SIX_COLOR_SATURATION());
#if(_SIX_COLOR_SUPPORT == _ON)
            OsdFuncSixColorAdjust();
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_SIX_COLOR_SATURATION())
            {
                SET_OSD_SIX_COLOR_SATURATION(g_usBackupValue);
                OsdDisplaySixColorSetOneColor(GET_OSD_SYSTEM_SELECT_REGION(), GET_OSD_SIX_COLOR());
#if(_SIX_COLOR_SUPPORT == _ON)
                OsdFuncSixColorAdjust();
#endif
            }
            SET_OSD_STATE(_MENU_COLOR_EFF_USER_M_SAT);
            OsdDispClearSliderAndNumber();
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_CLEAR);
            OsdDispClearSelectColor(_UP);
            OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_EFFECT_USER_1);

            OsdDispMainMenuOptionSetting(_OPTION_COLOR_RGBYCM_HUE_STA, _SELECT, _COLOR_SATURATION);
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_RGBYCM_HUE_SAT);
            OsdDispMainMenuItemIndication(_ITEM_5, 6, _OSD_SELECT);
            break;

        default:
            break;
    }
}

void MenuColorColorPCMSoftProftAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PCM_SOFT_PROFT_MODE())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_PCM_SOFT_PROFT_MODE() == _PCM_SOFT_MODE_1)
            {
                SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_2);
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                // ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                // ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);
                // Region selected by user
                ScalerColor3DGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING, _OFF);
                UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());
                // ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                // ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
                // Region selected by user
                ScalerColor3DGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
#endif
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
            }
            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_PCM_SOFT_PROFT_MODE() == _PCM_SOFT_MODE_2)
            {
                SET_OSD_PCM_SOFT_PROFT_MODE(_PCM_SOFT_MODE_1);

#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                // ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                // ScalerColorRGB3DGammaEnable(_FUNCTION_OFF);

                // Region selected by user
                ScalerColor3DGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_POLLING, _OFF);
                UserAdjust3DGamma(GET_OSD_PCM_SOFT_PROFT_MODE());

                // Region selected by user
                ScalerColor3DGammaRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
                // ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
                // ScalerColorRGB3DGammaEnable(_FUNCTION_ON);
#endif
                OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_SOFT_PROFT_TYPE, _SELECT, GET_OSD_PCM_SOFT_PROFT_MODE());
            }
            break;


            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_PCM_SOFT_PROFT_MODE())
            {
                SET_OSD_PCM_SOFT_PROFT_MODE(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
            OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
            OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);

            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_CLEAR);
            OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
            OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
            break;

        default:
            break;
    }
}


void MenuAdvanceODOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OD_STATUS())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());

            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_OD_STATUS() != _OFF)
            {
                SET_OSD_OD_STATUS(_OFF);
                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
#if(_OD_SUPPORT == _ON)
                ScalerODEnable(GET_OSD_OD_STATUS());
#endif
            }

            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_OD_STATUS() != _ON)
            {
                SET_OSD_OD_STATUS(_ON);
                OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _SELECT, GET_OSD_OD_STATUS());
#if(_OD_SUPPORT == _ON)
                ScalerODEnable(GET_OSD_OD_STATUS());
#endif
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OD_STATUS())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_OD_STATUS(g_usAdjustValue);
#if(_OD_SUPPORT == _ON)
                ScalerODEnable(GET_OSD_OD_STATUS());
#endif
            }
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_OVERDRIVE_ONOFF, _UNSELECT, GET_OSD_OD_STATUS());

            break;

        default:
            break;
    }
}


void MenuAdvanceODGainAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OD_GAIN())
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispSliderAndNumber(_MENU_ADVANCE_OD_GAIN_ADJUST, GET_OSD_OD_GAIN());
#if(_OD_SUPPORT == _ON)
            ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
#endif
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_OD_GAIN())
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_OD_GAIN(g_usAdjustValue);
#if(_OD_SUPPORT == _ON)
                ScalerODAdjustDeltaGain(GET_OSD_OD_GAIN());
#endif // End of #if(_OD_SUPPORT == _ON)
            }
            SET_OSD_STATE(_MENU_ADVANCE_OVER_DRIVE_GAIN);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            g_usAdjustValue = UserCommonAdjustRealValueToPercent(GET_OSD_OD_GAIN(), _OD_GAIN_MAX, _OD_GAIN_MIN, _OD_GAIN_CENTER);
            OsdWindowSlider(ROW(_SLIDER_0_ROW), COL(_SLIDER_0_COL), g_usAdjustValue, _SLIDER_0, _UNSELECT);
            OsdPropShowNumber(ROW(_OSD_NUMBER_1_ROW), COL(_OSD_NUMBER_1_COL), g_usAdjustValue, (_ALIGN_LEFT | _FORCE_SHOW_NUMBER_OFF | _SHOW_3), _PFONT_PAGE_ITEM_1, _OSD_NUMBER_UNSTLECT_COLOR);




            break;

        default:
            break;
    }
}

void MenuAdvanceDpD0VersionAdjust(void)
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D0_VERSION())
            {
                if((GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D0))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                ScalerDpVersionSwitch(_D0_INPUT_PORT, UserInterfaceGetDPVersion(_D0_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
            break;

        case _RIGHT_KEY_MESSAGE:
            if((GET_OSD_DP_D0_VERSION() + 1) > _DP_VER_AMOUNT)
            {
                SET_OSD_DP_D0_VERSION(_DP_VER_1_DOT_1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            }
            else
            {
                SET_OSD_DP_D0_VERSION(GET_OSD_DP_D0_VERSION() + 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            }
            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DP_D0_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_D0_VERSION(_DP_VER_AMOUNT);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            }
            else
            {
                SET_OSD_DP_D0_VERSION(GET_OSD_DP_D0_VERSION() - 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D0_VERSION());
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D0_VERSION())
            {
                SET_OSD_DP_D0_VERSION(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D0_VERSION());
            break;

        default:
            break;
    }

#endif
}

void MenuAdvanceDpD1VersionAdjust(void)
{
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D1_VERSION())
            {
                if((GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D1))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                ScalerDpVersionSwitch(_D1_INPUT_PORT, UserInterfaceGetDPVersion(_D1_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());

            break;

        case _RIGHT_KEY_MESSAGE:
            if((GET_OSD_DP_D1_VERSION() + 1) > _DP_VER_AMOUNT)
            {
                SET_OSD_DP_D1_VERSION(_DP_VER_1_DOT_1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            }
            else
            {
                SET_OSD_DP_D1_VERSION(GET_OSD_DP_D1_VERSION() + 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            }
            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DP_D1_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_D1_VERSION(_DP_VER_AMOUNT);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            }
            else
            {
                SET_OSD_DP_D1_VERSION(GET_OSD_DP_D1_VERSION() - 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D1_VERSION());
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D1_VERSION())
            {
                SET_OSD_DP_D1_VERSION(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D1_VERSION());

            break;

        default:
            break;
    }
#endif
}

void MenuAdvanceDpD6VersionAdjust(void)
{
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D6_VERSION())
            {
                if((GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1) && (GET_OSD_DP_MST() == _MST_D6))
                {
                    SET_OSD_DP_MST(_MST_OFF);
                }

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                ScalerDpVersionSwitch(_D6_INPUT_PORT, UserInterfaceGetDPVersion(_D6_INPUT_PORT), UserInterfaceGetDpMSTCapablePort());
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());

            break;

        case _RIGHT_KEY_MESSAGE:
            if((GET_OSD_DP_D6_VERSION() + 1) > _DP_VER_AMOUNT)
            {
                SET_OSD_DP_D6_VERSION(_DP_VER_1_DOT_1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            }
            else
            {
                SET_OSD_DP_D6_VERSION(GET_OSD_DP_D6_VERSION() + 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            }
            break;
        case _LEFT_KEY_MESSAGE:
            if(GET_OSD_DP_D6_VERSION() == _DP_VER_1_DOT_1)
            {
                SET_OSD_DP_D6_VERSION(_DP_VER_AMOUNT);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            }
            else

            {
                SET_OSD_DP_D6_VERSION(GET_OSD_DP_D6_VERSION() - 1);
                OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _SELECT, GET_OSD_DP_D6_VERSION());
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DP_D6_VERSION())
            {
                SET_OSD_DP_D6_VERSION(g_usBackupValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_OPTION_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_PORT_VERSION, _UNSELECT, GET_OSD_DP_D6_VERSION());

            break;

        default:
            break;
    }
#endif
}

void MenuAdvanceDpD0LaneCountAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            if(g_usBackupValue != GET_OSD_DP_D0_LANE_MODE())
            {
                if(g_usBackupValue == _DP_TWO_LANE)
                {
                    SET_OSD_DP_D0_LANE_MODE(_DP_TWO_LANE);
                    UserCommonNVRamSetSystemData(_DP_D0_LANES, _DP_LINK_2_LANE);
                    UserCommonNVRamSaveSystemData();
                }
                else if(g_usBackupValue == _DP_FOUR_LANE)
                {
                    SET_OSD_DP_D0_LANE_MODE(_DP_FOUR_LANE);
                    UserCommonNVRamSetSystemData(_DP_D0_LANES, _DP_LINK_4_LANE);
                    UserCommonNVRamSaveSystemData();
                }
                else
                {
                    SET_OSD_DP_D0_LANE_MODE(_DP_LANE_AUTO_MODE);
                }

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                if(GET_OSD_DP_D0_LANE_MODE() != _DP_LANE_AUTO_MODE)
                {
                    ScalerDpLaneCountSwitch(_D0_INPUT_PORT, UserInterfaceGetDpLaneCount(_D0_INPUT_PORT));
                }
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, g_usBackupValue);
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
            if(g_usBackupValue == _DP_TWO_LANE)
            {
                g_usBackupValue = _DP_FOUR_LANE;
            }
            else if (g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_LANE_AUTO_MODE;
            }
            else// if (g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_TWO_LANE;
            }
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);
            break;
        case _LEFT_KEY_MESSAGE:
            if(g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_TWO_LANE;
            }
            else if(g_usBackupValue == _DP_TWO_LANE)
            {
                g_usBackupValue = _DP_LANE_AUTO_MODE;
            }
            else
            {
                g_usBackupValue = _DP_FOUR_LANE;
            }
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);

            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D0);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D0_LANE_MODE());
#endif
            break;

        default:
            break;
    }
}



void MenuAdvanceDpD1LaneCountAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            if(g_usBackupValue != GET_OSD_DP_D1_LANE_MODE())
            {
                if(GET_OSD_DP_D1_LANE_MODE() == _DP_TWO_LANE)
                {
                    SET_OSD_DP_D1_LANE_MODE(_DP_TWO_LANE);
                    UserCommonNVRamSetSystemData(_DP_D1_LANES, _DP_LINK_2_LANE);
                    UserCommonNVRamSaveSystemData();
                }
                else if(GET_OSD_DP_D1_LANE_MODE() == _DP_FOUR_LANE)
                {
                    SET_OSD_DP_D1_LANE_MODE(_DP_FOUR_LANE);
                    UserCommonNVRamSetSystemData(_DP_D1_LANES, _DP_LINK_4_LANE);
                    UserCommonNVRamSaveSystemData();
                }
                else
                {
                    SET_OSD_DP_D1_LANE_MODE(_DP_LANE_AUTO_MODE);
                }

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                if(GET_OSD_DP_D1_LANE_MODE() != _DP_LANE_AUTO_MODE)
                {
                    ScalerDpLaneCountSwitch(_D1_INPUT_PORT, UserInterfaceGetDpLaneCount(_D1_INPUT_PORT));
                }
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
            if(g_usBackupValue == _DP_TWO_LANE)
            {
                g_usBackupValue = _DP_FOUR_LANE;
            }
            else if (g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_LANE_AUTO_MODE;
            }
            else// if (g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_TWO_LANE;
            }
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);
            break;
        case _LEFT_KEY_MESSAGE:
            if(g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_TWO_LANE;
            }
            else if(g_usBackupValue == _DP_TWO_LANE)
            {
                g_usBackupValue = _DP_LANE_AUTO_MODE;
            }
            else
            {
                g_usBackupValue = _DP_FOUR_LANE;
            }
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);

            break;

        case _EXIT_KEY_MESSAGE:

            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D1);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D1_LANE_MODE());
#endif
            break;

        default:
            break;
    }
}

void MenuAdvanceDpD6LaneCountAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            if(g_usBackupValue != GET_OSD_DP_D6_LANE_MODE())
            {
                if(GET_OSD_DP_D6_LANE_MODE() == _DP_TWO_LANE)
                {
                    SET_OSD_DP_D6_LANE_MODE(_DP_TWO_LANE);
                    UserCommonNVRamSetSystemData(_DP_D6_LANES, _DP_LINK_2_LANE);
                    UserCommonNVRamSaveSystemData();
                }
                else if(GET_OSD_DP_D6_LANE_MODE() == _DP_FOUR_LANE)
                {
                    SET_OSD_DP_D6_LANE_MODE(_DP_FOUR_LANE);
                    UserCommonNVRamSetSystemData(_DP_D6_LANES, _DP_LINK_4_LANE);
                    UserCommonNVRamSaveSystemData();
                }
                else
                {
                    SET_OSD_DP_D6_LANE_MODE(_DP_LANE_AUTO_MODE);
                }

                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

                if(GET_OSD_DP_D6_LANE_MODE() != _DP_LANE_AUTO_MODE)
                {
                    ScalerDpLaneCountSwitch(_D6_INPUT_PORT, UserInterfaceGetDpLaneCount(_D6_INPUT_PORT));
                }
            }
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, g_usBackupValue);
#endif

            break;

        case _RIGHT_KEY_MESSAGE:
            if(g_usBackupValue == _DP_TWO_LANE)
            {
                g_usBackupValue = _DP_FOUR_LANE;
            }
            else if (g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_LANE_AUTO_MODE;
            }
            else// if (g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_TWO_LANE;
            }
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);
            break;
        case _LEFT_KEY_MESSAGE:
            if(g_usBackupValue == _DP_FOUR_LANE)
            {
                g_usBackupValue = _DP_TWO_LANE;
            }
            else if(g_usBackupValue == _DP_TWO_LANE)
            {
                g_usBackupValue = _DP_LANE_AUTO_MODE;
            }
            else
            {
                g_usBackupValue = _DP_FOUR_LANE;
            }
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _SELECT, g_usBackupValue);

            break;


        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_ADVANCE_DP_LANE_COUNT_D6);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
#if(_D6_INPUT_PORT_TYPE == _D6_DP_PORT)
            OsdDispMainMenuOptionSetting(_OPTION_DP_LANE_COUNT_SELECT, _UNSELECT, GET_OSD_DP_D6_LANE_MODE());
#endif
            break;

        default:
            break;
    }
}

#if(_ULTRA_HDR_SUPPORT == _ON)
void MenuAdvanceHdrModeAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }

            SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()));
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(((GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()) == _HDR_MODE_SMPTE_ST_2084) && (GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)) ||
               ((GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()) == _HDR_MODE_OFF) && (GET_KEYMESSAGE() == _LEFT_KEY_MESSAGE)))
            {
            }
            else
            {
                OsdDispSliderAndNumber(_MENU_ADVANCE_HDR_MODE_ADJUST, GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()));
            }

            if(SysModeGetDisplayMode() != _DISPLAY_MODE_4P)
            {
                switch(GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()))
                {
                    case _HDR_MODE_AUTO:

                        switch(UserCommonAdjustHDRAutoModeInitial(GET_OSD_SYSTEM_DISPLAY_REGION()))
                        {
                            case _HDR_TARGET_STATUS_SMPTE_ST_2084:
                                UserCommonAdjustHDRAutoMode(GET_OSD_SYSTEM_DISPLAY_REGION(), GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
                                UserAdjustBacklight(_BACKLIGHT_MAX);//Must!!!!!
                                break;

                            case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:
                                OsdFuncColorPcmAdjust();
                                UserAdjustBacklight(GET_OSD_BACKLIGHT());//Must!!!!!
                                break;

                            case _HDR_TARGET_STATUS_DO_NOTHING:
                            default:
                                break;
                        }
                        break;

                    case _HDR_MODE_SMPTE_ST_2084:
                        UserAdjustHDR2084(GET_OSD_SYSTEM_DISPLAY_REGION(), _HDR_MAX_MASTERING_LV_TYPE0, _HDR_COLOR_MATRIX_BT2020, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
                        UserAdjustBacklight(_BACKLIGHT_MAX);//Must!!!!!
                        break;

                    case _HDR_MODE_OFF:
                        OsdFuncColorPcmAdjust();
                        UserAdjustBacklight(GET_OSD_BACKLIGHT());//Must!!!!!
                        break;

                    default:
                        break;
                }
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort(),g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()));

            break;

        default:
            break;
    }
}



void MenuAdvanceHdrDarkEnhanceOnOffAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()))
            {
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DARK_ENHANCE_ON_OFF, _UNSELECT, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));

            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            if(GET_KEYMESSAGE() == _RIGHT_KEY_MESSAGE)
            {
                if(GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()) != _OFF)
                {
                    SET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort(),_OFF);
                    OsdDispMainMenuOptionSetting(_OPTION_DARK_ENHANCE_ON_OFF, _SELECT, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
                }
            }
            else
            {
                if(GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()) != _ON)
                {
                    SET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort(),_ON);
                    OsdDispMainMenuOptionSetting(_OPTION_DARK_ENHANCE_ON_OFF, _SELECT, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
                }
            }

            if(SysModeGetDisplayMode() == _DISPLAY_MODE_1P)
            {
                switch(GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()))
                {
                    case _HDR_MODE_AUTO:

                        switch(UserCommonAdjustHDRAutoModeInitial(_DISPLAY_RGN_1P))
                        {
                            case _HDR_TARGET_STATUS_SMPTE_ST_2084:
                                UserCommonAdjustHDRAutoMode(_DISPLAY_RGN_1P, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
                                break;

                            case _HDR_TARGET_STATUS_TRADITIONAL_GAMMA_SDR:
                            case _HDR_TARGET_STATUS_DO_NOTHING:
                            default:
                                break;
                        }
                        break;

                    case _HDR_MODE_SMPTE_ST_2084:

                        UserAdjustHDR2084(_DISPLAY_RGN_1P, _HDR_MAX_MASTERING_LV_TYPE0, _HDR_COLOR_MATRIX_BT2020, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));
                        break;

                    case _HDR_MODE_OFF:
                    default:
                        break;
                }
            }

            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()))
            {
                g_usAdjustValue = g_usBackupValue;
                SET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort(),g_usAdjustValue);
            }
            SET_OSD_STATE(_MENU_ADVANCE_HDR_DARK_ENHANCE_ONOFF);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_DARK_ENHANCE_ON_OFF, _UNSELECT, GET_OSD_REGION_DARK_ENHANCE(UserAdjustGetSelectRegionPort()));

            break;

        default:
            break;
    }
}
#endif


void MenuHotKeyDdcci(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) != 0x00)
            {
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NOSUPPORT_SAVING);
            }
//            else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
            {
                ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            }
            else
            {
                OsdDispDisableOsd();
            }
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispHotKeyOptionMenuSwitch(_HOTKEY_DDCCI);

//            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
            {
                ScalerTimerReactiveTimerEvent(SEC(3), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            }
            break;

        case _EXIT_KEY_MESSAGE:
            if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) != 0x00)
            {
                SysPowerSetTargetPowerStatus(_POWER_STATUS_NOSUPPORT_SAVING);
            }
//            else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING)||(SysModeGetModeState() == _MODE_STATUS_NOSIGNAL))
            else if((SysModeGetModeState() == _MODE_STATUS_POWER_SAVING))
            {
                ScalerTimerReactiveTimerEvent(SEC(0), _USER_TIMER_EVENT_GO_TO_POWER_SAVING);
            }
            else
            {
                OsdDispDisableOsd();
            }
            break;

        default:
            break;
    }
}

void MenuHotKeySource(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_1P_INPUT_SOURCE())
            {
                switch(g_usBackupValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_1P_INPUT_SOURCE(g_usBackupValue);
                        UserAdjustRegionInputPort(_DISPLAY_RGN_1P, g_usBackupValue);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_1P_INPUT_SOURCE(g_usBackupValue);
#if(_DP_MST_SUPPORT == _ON)
                        if(GET_OSD_DP_MST() != _MST_OFF)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }
#endif
                        SysSourceSetMultiAutoSearchTarget(_DISPLAY_RGN_1P);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
                RTDNVRamSaveOsdUserData();

#endif
            }

            OsdDispDisableOsd();
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            g_usBackupValue = OsdFuncCheckInputPortType(g_usBackupValue, _REGION_INDEX_0);

            OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
            OsdDispHotKeySourceMenuIcon(g_usBackupValue);

            break;

        case _EXIT_KEY_MESSAGE:

            OsdDispDisableOsd();
            break;

        default:
            break;
    }

    OsdFuncShowSourceMenuCheck();
}

void MenuHotKeyDisplayMode(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_DISPLAY_MODE())
            {
                SET_OSD_DISPLAY_MODE(g_usBackupValue);
                UserAdjustDisplayMode();
                SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_OSDUSERDATA_MSG);

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
#endif
            }
            OsdDispDisableOsd();
            break;

        case _RIGHT_KEY_MESSAGE:
            // g_usBackupValue = OsdDisplayDetOverRange(g_usBackupValue, _OSD_DM_4P, _OSD_DM_1P, _ON);
            switch(g_usBackupValue)
            {
                case _OSD_DM_1P:
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_LR;
#elif(_PBP_TB_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_TB;
#elif(_PIP_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_PIP;
#elif(_4P_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_4P;
#endif
                    break;

                case _OSD_DM_2P_LR:
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_TB;
#elif(_PIP_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_PIP;
#elif(_4P_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_4P;
#else
                    g_usBackupValue = _OSD_DM_1P;
#endif
                    break;

                case _OSD_DM_2P_TB:
#if(_PIP_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_PIP;
#elif(_4P_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_4P;
#else
                    g_usBackupValue = _OSD_DM_1P;
#endif
                    break;

                case _OSD_DM_2P_PIP:
#if(_4P_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_4P;
#else
                    g_usBackupValue = _OSD_DM_1P;
#endif
                    break;

                case _OSD_DM_4P:
                    g_usBackupValue = _OSD_DM_1P;
                    break;

                default:
                    break;
            }
            OsdDispHotKeyDisplayModeMenuSwitch(g_usBackupValue);
            if((g_usBackupValue == _OSD_DM_4P) || ((g_usBackupValue == _OSD_DM_1P) && (_4P_DISPLAY_SUPPORT == _ON)))
            {
                OsdDispHotKeyDisplayModeMenuIcon(g_usBackupValue);
            }

            break;

        case _LEFT_KEY_MESSAGE:
            // g_usBackupValue = OsdDisplayDetOverRange(g_usBackupValue, _OSD_DM_4P, _OSD_DM_1P, _ON);
            switch(g_usBackupValue)
            {
                case _OSD_DM_1P:
#if(_4P_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_4P;
                    OsdDispHotKeyDisplayModeMenuIcon(g_usBackupValue);
#elif(_PIP_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_PIP;
#elif(_PBP_TB_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_TB;
#elif(_PBP_LR_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_LR;
#endif
                    break;

                case _OSD_DM_2P_LR:
                    g_usBackupValue = _OSD_DM_1P;
                    break;

                case _OSD_DM_2P_TB:
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_LR;
#else
                    g_usBackupValue = _OSD_DM_1P;
#endif
                    break;

                case _OSD_DM_2P_PIP:
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_TB;
#elif(_PBP_LR_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_LR;
#else
                    g_usBackupValue = _OSD_DM_1P;
#endif
                    break;

                case _OSD_DM_4P:
#if(_PIP_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_PIP;
#elif(_PBP_TB_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_TB;
#elif(_PBP_LR_DISPLAY_SUPPORT == _ON)
                    g_usBackupValue = _OSD_DM_2P_LR;
#else
                    g_usBackupValue = _OSD_DM_1P;
#endif
                    OsdDispHotKeyDisplayModeMenuIcon(g_usBackupValue);
                    break;

                default:
                    break;
            }

            OsdDispHotKeyDisplayModeMenuSwitch(g_usBackupValue);
            /*
            if((g_usBackupValue == _OSD_DM_4P) || (g_usBackupValue == _OSD_DM_2P_PIP))
            {
                OsdDispHotKeyDisplayModeMenuIcon(g_usBackupValue);
            }
            */

            break;

        case _EXIT_KEY_MESSAGE:
            OsdDispDisableOsd();
            break;

        default:
            break;
    }


    OsdFuncShowSourceMenuCheck();
}


// hotkey information
void MenuHotKeyInformation(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        switch(GET_KEYMESSAGE())
        {
            case _MENU_KEY_MESSAGE:
            case _RIGHT_KEY_MESSAGE:
            case _LEFT_KEY_MESSAGE:
            case _EXIT_KEY_MESSAGE:
            default:
                OsdDispDisableOsd();
                break;
        }
    }
    else
    {
        switch(GET_KEYMESSAGE())
        {
            case _RIGHT_KEY_MESSAGE:
                OsdDispHotKeySourceMenu();
                break;
            case _MENU_KEY_MESSAGE:
            case _LEFT_KEY_MESSAGE:
            case _EXIT_KEY_MESSAGE:
            default:
                OsdDispDisableOsd();
                break;
        }
    }
}

void MenuPanelUniformityMsgAdjust(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _EXIT_KEY_MESSAGE:
        case _MENU_KEY_MESSAGE:

            if((g_usAdjustValue != GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION())) &&
               (GET_KEYMESSAGE() == _EXIT_KEY_MESSAGE))
            {
                SET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION(), g_usAdjustValue);

#if(_UNIFORMITY_SUPPORT == _ON)
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

                UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
                // UserAdjustPanelUniformityMode(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
                if((GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON) && (GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON))
                {
                    ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);
                }
                else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
                {
                    ScalerColorPanelUniformityRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
                }
                else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON)
                {
                    ScalerColorPanelUniformityRegionEnable(ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()), _DB_APPLY_NO_POLLING, _ON);
                }
#endif
            }

            RTDNVRamSaveOsdUserData();
            ScalerTimerWaitForEvent(_EVENT_DEN_STOP);
            OsdFuncDisableOsd();
            OsdDispMainMenu();

            if(g_usBackupValue == _FROM_STATE_GAMMA)
            {
                OsdDispMainMenuItemSelection(_ITEM_1, _OSD_PRE_SELECT);
                OsdDispMainMenuItemIndication(_ITEM_1, 9, _OSD_SELECT);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_0);

                if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
                {
                    SET_OSD_STATE(_MENU_COLOR_GAMMA);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _UNSELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
                }
                else
                {
                    SET_OSD_STATE(_MENU_COLOR_GAMMA_ADJUST);
                    g_usBackupValue = GET_OSD_GAMMA(GET_OSD_SELECT_REGION());
                    OsdDispMainMenuOptionSetting(_OPTION_GAMMA_TYPE, _SELECT, GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
                }


                if(GET_OSD_GAMMA(GET_OSD_SELECT_REGION()) >= _GAMMA_24)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_1);
                }
                else
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_GAMMA_0);
                }
            }
            else if(g_usBackupValue == _FROM_STATE_PCM)
            {
                OsdDispMainMenuItemSelection(_ITEM_2, _OSD_PRE_SELECT);
                OsdDispMainMenuItemIndication(_ITEM_7, 9, _OSD_SELECT);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_COLOR_1);
                if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
                {
                    SET_OSD_STATE(_MENU_COLOR_PCM);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _UNSELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                }
                else
                {
                    SET_OSD_STATE(_MENU_COLOR_PCM_ADJUST);
                    g_usBackupValue = GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION());
                    OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
                }

                // OsdDispMainMenuOptionSetting(_OPTION_COLOR_PCM_TYPE, _SELECT, GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()));
#if((_OCC_SUPPORT == _ON) && (_RGB_3D_GAMMA == _ON))
                if(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()) >= _PCM_OSD_SOFT_PROFT)
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_1);
                }
                else
#endif
                {
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_COLOR_PCM_0);
                }
            }

#if(_ULTRA_HDR_SUPPORT == _ON)
            else if(g_usBackupValue == _FROM_STATE_HDR)
            {
                if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
                {
                    OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
                    OsdDispMainMenuItemIndication(12, 13, _OSD_SELECT);
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_ADVANCE_3);
                    SET_OSD_STATE(_MENU_ADVANCE_HDR);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_ADJUST);
                }
                else
                {
                    OsdDispMainMenuItemSelection(_ITEM_0, _OSD_PRE_SELECT);
                    OsdDispMainMenuItemIndication(_ITEM_0, 2, _OSD_SELECT);
                    OsdDispMainMenuIconPage(_UP, _ICON_PAGE_HDR_ADJUST);
                    SET_OSD_STATE(_MENU_ADVANCE_HDR_MODE);
                    g_usBackupValue = GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort());
                    OsdDispMainMenuOptionSetting(_OPTION_HDR_MODE_SELECT, _UNSELECT, GET_OSD_REGION_HDR_MODE(UserAdjustGetSelectRegionPort()));
                    OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_HDR_MODE);
                    OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                }
            }
#endif
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:
            OsdDispPanelUniformityMsgSwitch();

#if(_UNIFORMITY_SUPPORT == _ON)
            ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_POLLING, _OFF);

            UserAdjustPanelUniformityMode(_UNIFORMITY_OSD_TYPE1);
            // UserAdjustPanelUniformityMode(GET_OSD_PCM_STATUS(GET_OSD_SELECT_REGION()), GET_OSD_GAMMA(GET_OSD_SELECT_REGION()));
            if((GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON) &&
               (GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON))
            {
                ScalerColorPanelUniformityRegionEnable(_1P_NORMAL_FULL_REGION, _DB_APPLY_NO_POLLING, _ON);
            }
            else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_SELECT_REGION()) == _ON)
            {
                ScalerColorPanelUniformityRegionEnable(GET_OSD_SYSTEM_SELECT_REGION(), _DB_APPLY_NO_POLLING, _ON);
            }
            else if(GET_OSD_PANEL_UNIFORMITY(GET_OSD_INVERSE_REGION()) == _ON)
            {
                ScalerColorPanelUniformityRegionEnable(ScalerRegionGetInverse(GET_OSD_SYSTEM_SELECT_REGION()), _DB_APPLY_NO_POLLING, _ON);
            }
#endif
            break;

        default:
            break;
    }
}

void MenuMeseageDisplay(void)
{
}

void MenuSource_1P(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_1P_INPUT_SOURCE();
            SET_OSD_STATE(_MENU_INPUT_SOURCE_1P_ADJ);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _SELECT, GET_OSD_1P_INPUT_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_SOURCE_2P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispHotKeySourceMenuIcon(GET_OSD_2P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_2P_INPUT_SOURCE());
            break;

        case _LEFT_KEY_MESSAGE:
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usItemNum == _MENU_NONE)
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

                switch(GET_OSD_DISPLAY_MODE())
                {
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _OSD_DM_2P_LR:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_LR);
                        break;
#endif
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
                    case _OSD_DM_2P_TB:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_TB);
                        break;
#endif
#if(_PIP_DISPLAY_SUPPORT == _ON)
                    case _OSD_DM_2P_PIP:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_PIP);
                        break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                    case _OSD_DM_4P:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_4P);
                        break;
#endif
                    default:
                        break;
                }

                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            }
            break;

        default:
            break;
    }

    OsdFuncShowSourceMenuCheck();
}

void MenuSource_2P(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_2P_INPUT_SOURCE();
            SET_OSD_STATE(_MENU_INPUT_SOURCE_2P_ADJ);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _SELECT, GET_OSD_2P_INPUT_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_4P)
            {
                SET_OSD_STATE(_MENU_INPUT_SOURCE_3P);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispClearSelectColor(_DOWN);
                OsdDispHotKeySourceMenuIcon(GET_OSD_3P_INPUT_SOURCE());
                OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_3P_INPUT_SOURCE());
            }
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_SOURCE_1P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispHotKeySourceMenuIcon(GET_OSD_1P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_1P_INPUT_SOURCE());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usItemNum == _MENU_NONE)
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);

                switch(GET_OSD_DISPLAY_MODE())
                {
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _OSD_DM_2P_LR:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_LR);
                        break;
#endif
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
                    case _OSD_DM_2P_TB:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_TB);
                        break;
#endif
#if(_PIP_DISPLAY_SUPPORT == _ON)
                    case _OSD_DM_2P_PIP:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_2P_PIP);
                        break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                    case _OSD_DM_4P:
                        OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_4P);
                        break;
#endif
                    default:
                        break;
                }

                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            }
            break;

        default:
            break;
    }

    OsdFuncShowSourceMenuCheck();
}

void MenuSource_3P(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_3P_INPUT_SOURCE();
            SET_OSD_STATE(_MENU_INPUT_SOURCE_3P_ADJ);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _SELECT, GET_OSD_3P_INPUT_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_SOURCE_4P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispHotKeySourceMenuIcon(GET_OSD_4P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_4P_INPUT_SOURCE());
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_SOURCE_2P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispHotKeySourceMenuIcon(GET_OSD_2P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_2P_INPUT_SOURCE());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usItemNum == _MENU_NONE)
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_4P);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            }
            break;

        default:
            break;
    }

    OsdFuncShowSourceMenuCheck();
}

void MenuSource_4P(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            g_usBackupValue = GET_OSD_4P_INPUT_SOURCE();
            SET_OSD_STATE(_MENU_INPUT_SOURCE_4P_ADJ);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _INSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _SELECT, GET_OSD_4P_INPUT_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
            break;

        case _LEFT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_SOURCE_3P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispClearSelectColor(_DOWN);
            OsdDispHotKeySourceMenuIcon(GET_OSD_3P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_3P_INPUT_SOURCE());
            break;

        case _EXIT_KEY_MESSAGE:
            if(g_usItemNum == _MENU_NONE)
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_STATE(_MENU_INPUT);
                OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
                OsdDispMainMenuIconPage(_DOWN, _ICON_PAGE_INPUT_4P);
                OsdDispClearSelectColor(_DOWN);
                OsdDispMainMenuIconPage(_UP, _ICON_PAGE_MAIN_1);
            }
            break;

        default:
            break;
    }

    OsdFuncShowSourceMenuCheck();
}

void MenuSource_1P_ADJ(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:
            if(g_usBackupValue != GET_OSD_1P_INPUT_SOURCE())
            {
                switch(g_usBackupValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_1P_INPUT_SOURCE(g_usBackupValue);

                        switch(GET_OSD_DISPLAY_MODE())
                        {
                            case _OSD_DM_1P:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_1P, g_usBackupValue);
                                break;
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_LR:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_LEFT, g_usBackupValue);
                                break;
#endif
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_TB:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_TOP, g_usBackupValue);
                                break;
#endif
#if(_PIP_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_PIP:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_MAIN, g_usBackupValue);
                                break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_4P:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_LT, g_usBackupValue);
                                break;
#endif
                            default:
                                break;
                        }

                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_1P_INPUT_SOURCE(g_usBackupValue);
#if(_DP_MST_SUPPORT == _ON)
                        if(GET_OSD_DP_MST() != _MST_OFF)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }
#endif
                        SysSourceSetMultiAutoSearchTarget(UserInterfaceGetAutoSearchTarget());
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }

#if(_DP_MST_SUPPORT == _ON)
                ScalerDpRxMstRx0Rx1switch(UserInterfaceGetDpMSTCapablePort());
                RTDNVRamSaveOsdUserData();

#endif
            }

            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                OsdDispDisableOsd();
            }
            else
            {
                SET_OSD_STATE(_MENU_INPUT_SOURCE_1P);
            }
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_1P_INPUT_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            g_usBackupValue = OsdFuncCheckInputPortType(g_usBackupValue, _REGION_INDEX_0);

            OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
            OsdDispHotKeySourceMenuIcon(g_usBackupValue);

            break;


        case _EXIT_KEY_MESSAGE:
            if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
            {
                SET_OSD_STATE(_MENU_INPUT);
            }
            else
            {
                SET_OSD_STATE(_MENU_INPUT_SOURCE_1P);
            }
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispHotKeySourceMenuIcon(GET_OSD_1P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_1P_INPUT_SOURCE());
            break;

        default:
            break;
    }

    OsdFuncShowSourceMenuCheck();
}

void MenuSource_2P_ADJ(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_MULTI_DISPLAY_MAX >= 0x02)
            if(g_usBackupValue != GET_OSD_2P_INPUT_SOURCE())
            {
                switch(g_usBackupValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_2P_INPUT_SOURCE(g_usBackupValue);

                        switch(GET_OSD_DISPLAY_MODE())
                        {
#if(_PBP_LR_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_LR:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_RIGHT, g_usBackupValue);
                                break;
#endif
#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_TB:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_BOTTOM, g_usBackupValue);
                                break;
#endif
#if(_PIP_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_2P_PIP:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_SUB, g_usBackupValue);
                                break;
#endif
#if(_4P_DISPLAY_SUPPORT == _ON)
                            case _OSD_DM_4P:
                                UserAdjustRegionInputPort(_DISPLAY_RGN_LB, g_usBackupValue);
                                break;
#endif
                            default:
                                break;
                        }

                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_2P_INPUT_SOURCE(g_usBackupValue);
#if(_DP_MST_SUPPORT == _ON)
                        if(GET_OSD_DP_MST() != _MST_OFF)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }
#endif
                        SysSourceSetMultiAutoSearchTarget(UserInterfaceGetAutoSearchTarget());
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_MULTI_DISPLAY_MAX >= 0x02)

            SET_OSD_STATE(_MENU_INPUT_SOURCE_2P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_2P_INPUT_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            g_usBackupValue = OsdFuncCheckInputPortType(g_usBackupValue, _REGION_INDEX_1);

            OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
            OsdDispHotKeySourceMenuIcon(g_usBackupValue);

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_SOURCE_2P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispHotKeySourceMenuIcon(GET_OSD_2P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_2P_INPUT_SOURCE());

            break;

        default:
            break;
    }

    OsdFuncShowSourceMenuCheck();
}

void MenuSource_3P_ADJ(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_4P_DISPLAY_SUPPORT == _ON)
            if(g_usBackupValue != GET_OSD_3P_INPUT_SOURCE())
            {
                switch(g_usBackupValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_3P_INPUT_SOURCE(g_usBackupValue);
                        UserAdjustRegionInputPort(_DISPLAY_RGN_RT, g_usBackupValue);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_3P_INPUT_SOURCE(g_usBackupValue);
#if(_DP_MST_SUPPORT == _ON)
                        if(GET_OSD_DP_MST() != _MST_OFF)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }
#endif
                        SysSourceSetMultiAutoSearchTarget(UserInterfaceGetAutoSearchTarget());
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_4P_DISPLAY_SUPPORT == _ON)

            SET_OSD_STATE(_MENU_INPUT_SOURCE_3P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_3P_INPUT_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            g_usBackupValue = OsdFuncCheckInputPortType(g_usBackupValue, _REGION_INDEX_2);

            OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
            OsdDispHotKeySourceMenuIcon(g_usBackupValue);

            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_SOURCE_2P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispHotKeySourceMenuIcon(GET_OSD_3P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_3P_INPUT_SOURCE());
            break;

        default:
            break;
    }

    OsdFuncShowSourceMenuCheck();
}

void MenuSource_4P_ADJ(void)
{
    switch(GET_KEYMESSAGE())
    {
        case _MENU_KEY_MESSAGE:

#if(_4P_DISPLAY_SUPPORT == _ON)
            if(g_usBackupValue != GET_OSD_4P_INPUT_SOURCE())
            {
                switch(g_usBackupValue)
                {
                    case _OSD_INPUT_A0:
                    case _OSD_INPUT_D0:
                    case _OSD_INPUT_D1:
                    case _OSD_INPUT_D2:
                    case _OSD_INPUT_D3:
                    case _OSD_INPUT_D4:
                    case _OSD_INPUT_D5:
                    case _OSD_INPUT_D6:
                    case _OSD_INPUT_D7:
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_4P_INPUT_SOURCE(g_usBackupValue);
                        UserAdjustRegionInputPort(_DISPLAY_RGN_RB, g_usBackupValue);
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    case _OSD_INPUT_AUTO: // Auto
                        SET_FORCE_POW_SAV_STATUS(_FALSE);
                        SET_OSD_4P_INPUT_SOURCE(g_usBackupValue);
#if(_DP_MST_SUPPORT == _ON)
                        if(GET_OSD_DP_MST() != _MST_OFF)
                        {
                            SET_OSD_DP_MST(_MST_OFF);
                        }
#endif
                        SysSourceSetMultiAutoSearchTarget(UserInterfaceGetAutoSearchTarget());
                        SET_OSD_EVENT_MESSAGE(_OSDEVENT_SAVE_NVRAM_DISPLAYMODEDATA_MSG);
                        break;

                    default:
                        break;
                }
            }
#endif // End of #if(_4P_DISPLAY_SUPPORT == _ON)

            SET_OSD_STATE(_MENU_INPUT_SOURCE_4P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_4P_INPUT_SOURCE());
            break;

        case _RIGHT_KEY_MESSAGE:
        case _LEFT_KEY_MESSAGE:

            g_usBackupValue = OsdFuncCheckInputPortType(g_usBackupValue, _REGION_INDEX_3);

            OsdDispHotKeySourceMenuSwitch(g_usBackupValue);
            OsdDispHotKeySourceMenuIcon(g_usBackupValue);
            break;

        case _EXIT_KEY_MESSAGE:
            SET_OSD_STATE(_MENU_INPUT_SOURCE_4P);
            OsdDispMainMenuCursor(GET_OSD_STATE(), GET_OSD_STATE_PREVIOUS(), _OUTSUBSET);
            OsdDispHotKeySourceMenuIcon(GET_OSD_4P_INPUT_SOURCE());
            OsdDispMainMenuOptionSetting(_OPTION_INPUT_MF_SOURCE_TYPE, _UNSELECT, GET_OSD_4P_INPUT_SOURCE());
            break;

        default:
            break;
    }


    OsdFuncShowSourceMenuCheck();
}

code void (*OperationTable[])(void) =
{
    MenuNone,

    // main
    MenuDisplayMode,
    MenuDisplayFunction,
    MenuSelectRegion,
    MenuPicture,
    MenuAnalog,
    MenuColor,
    MenuAdvance,
    MenuInput,
    MenuAudio,
    MenuOther,
    MenuInformation,
    MenuFactory,

    // display mode
    MenuDisplayMode1P,
    MenuDisplayMode2P_LR,
    MenuDisplayMode2P_TB,
    MenuDisplayMode2P_PIP,
    MenuDisplayMode4P,

    // display function
    MenuDisplayFunDispRotate,
    MenuDisplayFunLatency,
    MenuDisplayFunFreeze,

    MenuDisplayFunLRratio,
    MenuDisplayFunInputSwap, // LR Swap
    MenuDisplayFunInputSwap,  // TB Swap
    MenuDisplayFunPipPosition,
    MenuDisplayFunPipTransparency,
    MenuDisplayFunPipSize,
    MenuDisplayFunInputSwap, // PIP Swap

    // select region
    MenuSelectRegion_2P_LR_L,
    MenuSelectRegion_2P_LR_R,
    MenuSelectRegion_2P_LR_FULL,

    MenuSelectRegion_2P_TB_T,
    MenuSelectRegion_2P_TB_B,
    MenuSelectRegion_2P_TB_FULL,

    MenuSelectRegion_2P_PIP_MAIN,
    MenuSelectRegion_2P_PIP_SUB,
    MenuSelectRegion_2P_PIP_FULL,

    MenuSelectRegion_4P_LT_IN,
    MenuSelectRegion_4P_LT_OUT,
    MenuSelectRegion_4P_LB_IN,
    MenuSelectRegion_4P_LB_OUT,
    MenuSelectRegion_4P_RT_IN,
    MenuSelectRegion_4P_RT_OUT,
    MenuSelectRegion_4P_RB_IN,
    MenuSelectRegion_4P_RB_OUT,
    MenuSelectRegion_4P_FULL,

    // picture
    MenuPictureBacklight,
    MenuPictureBrightness,
    MenuPictureContrast,
    MenuPictureSharpness,

    // Analog
    MenuAnalogAuto,
    MenuAnalogHPos,
    MenuAnalogVPos,
    MenuAnalogClock,
    MenuAnalogPhase,

    // color
    MenuColorPanelUniformity,
    MenuColorGamma,
    MenuColorTemperature,
    MenuColorEffect,
    MenuColorDemo,
    MenuColorFormat,
    MenuColorPCM,
    MenuColorHue,
    MenuColorSaturation,

    // advance
    MenuAdvanceAspect,
    MenuAdvanceOverScan,
    MenuAdvanceOverDrive,
    MenuAdvanceDDCCI,
    MenuAdvanceUltraVivid,
    MenuAdvanceDCR,
    MenuAdvanceDpOption,
    MenuAdvanceDpMST,
    MenuAdvanceDpEDID,
    MenuAdvanceClone,
    MenuAdvanceFreeSync,
    MenuAdvanceDpLaneCount,

#if(_ULTRA_HDR_SUPPORT == _ON)
    MenuAdvanceHdr,
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
    MenuAdvanceFalseColor,
#endif

    // input
    MenuSource_1P,
    MenuSource_2P,
    MenuSource_3P,
    MenuSource_4P,
    MenuSource_1P_ADJ,
    MenuSource_2P_ADJ,
    MenuSource_3P_ADJ,
    MenuSource_4P_ADJ,

    // audio
    MenuAudioVolume,
    MenuAudioMute,
    MenuAudioStandAlong,
    MenuAudioAudioSource,
    MenuAudioSoundMode,

    // other
    MenuOtherReset,
    MenuOtherMenuTime,
    MenuOtherOsdHPos,
    MenuOtherOsdVPos,
    MenuOtherLanguage,
    MenuOtherTransparency,
    MenuOtherRotate,
    MenuOtherBorderWidth,
    MenuOtherBorderColor,

    // display function adjust
    MenuDisplayFunDispRotateAdjust,
    MenuDisplayFunDispLatencyAdjust,
    MenuDisplayFunFreezeAdjust,

    MenuDisplayFunLRratioAdjust,
    MenuDisplayFunPipPositionAdjust,
    MenuDisplayFunPipPositionH,
    MenuDisplayFunPipPositionV,
    MenuDisplayFunPipPositionHAdjust,
    MenuDisplayFunPipPositionVAdjust,
    MenuDisplayFunPipTransparencyAdjust,
    MenuDisplayFunPipSizeAdjust,

    // picture adjust
    MenuPictureBacklightAdjust,
    MenuPictureBrightnessAdjust,
    MenuPictureContrastAdjust,
    MenuPictureSharpnessAdjust,

    // display adjust
    MenuDisplayHPosAdjust,
    MenuDisplayVPosAdjust,
    MenuDisplayClockAdjust,
    MenuDisplayPhaseAdjust,

    // color adjust
    MenuColorPanelUniformityAdjust,
    MenuColorGammaAdjust,
    MenuColorColortempAdjust,
    MenuColorColorEffectAdjust,
    MenuColorColorDemoAdjust,
    MenuColorColorFormatAdjust,
    MenuColorColorPCMAdjust,
    MenuColorColorHueAdjust,
    MenuColorColorSaturationAdjust,

    // advance adjust
    MenuAdvanceAspectAdjust,
    MenuAdvanceOverScanAdjust,
    MenuAdvanceOverDriveOnOff,
    MenuAdvanceOverDriveGain,
    MenuAdvanceDdcciAdjust,
    MenuAdvanceUltraVividAdjust,
    MenuAdvanceDCRAdjust,
    MenuAdvanceDpOptionD0,
    MenuAdvanceDpOptionD1,
    MenuAdvanceDpOptionD6,
    MenuAdvanceDPMstAdjust,
    MenuAdvanceCloneAdjust,
    MenuAdvanceFreeSyncAdjust,
    MenuAdvanceSingleDpEDID,
    MenuAdvanceDualDpEDID,
    MenuAdvanceSingleDPEdidAdjust,
    MenuAdvanceDualDPEdidAdjust,
#if(_EDID_SWITCH_BY_PORT_ITEM == _ON)
    MenuAdvanceEdidAdjust,
    MenuAdvanceEdidDXAdjust,
#endif
    MenuAdvanceDpLaneCountD0,
    MenuAdvanceDpLaneCountD1,
    MenuAdvanceDpLaneCountD6,

#if(_ULTRA_HDR_SUPPORT == _ON)
    MenuAdvanceHdrMode,
    MenuAdvanceHdrDarkEnhanceOnOff,
#endif
#if(_FALSE_COLOR_SUPPORT == _ON)
    MenuAdvanceFalseColorAdjust,
    MenuAdvanceFalseColorUser,
    MenuAdvanceFalseColorUserAdjust,
#endif

    // Audio adjust
    MenuAudioVolumeAdjust,
    MenuAudioMuteOnOff,
    MenuAudioStandAlongSelect,
    MenuAudioAudioSourceSelect,
    MenuAudioSoundModeSelect,

    // other adjust
    MenuOtherMenuTimeAdjust,
    MenuOtherOsdHPosAdjust,
    MenuOtherOsdVPosAdjust,
    MenuOtherLanguageAdjust,
    MenuOtherTransparencyAdjust,
    MenuOtherRotateAdjust,
    MenuOtherSelectRegionWidthAdjust,
    MenuOtherSelectRegionColorAdjust,

    // color temp user RGB
    MenuColorColortempUserR,
    MenuColorColortempUserG,
    MenuColorColortempUserB,

    // color temp user adjust RGB
    MenuColorColortempUserAdjustR,
    MenuColorColortempUserAdjustG,
    MenuColorColortempUserAdjustB,

    // color effect user adjust
    MenuColorColorEffcUserR,
    MenuColorColorEffcUserY,
    MenuColorColorEffcUserG,
    MenuColorColorEffcUserC,
    MenuColorColorEffcUserB,
    MenuColorColorEffcUserM,

    MenuColorColorEffcUserRHue,
    MenuColorColorEffcUserRSat,

    MenuColorColorEffcUserYHue,
    MenuColorColorEffcUserYSat,

    MenuColorColorEffcUserGHue,
    MenuColorColorEffcUserGSat,

    MenuColorColorEffcUserCHue,
    MenuColorColorEffcUserCSat,

    MenuColorColorEffcUserBHue,
    MenuColorColorEffcUserBSat,

    MenuColorColorEffcUserMHue,
    MenuColorColorEffcUserMSat,

    // color effect user adjust Hue & Sat
    MenuColorColorEffcUserRHueAdjust,
    MenuColorColorEffcUserRSatAdjust,

    MenuColorColorEffcUserYHueAdjust,
    MenuColorColorEffcUserYSatAdjust,

    MenuColorColorEffcUserGHueAdjust,
    MenuColorColorEffcUserGSatAdjust,

    MenuColorColorEffcUserCHueAdjust,
    MenuColorColorEffcUserCSatAdjust,

    MenuColorColorEffcUserBHueAdjust,
    MenuColorColorEffcUserBSatAdjust,

    MenuColorColorEffcUserMHueAdjust,
    MenuColorColorEffcUserMSatAdjust,

    MenuColorColorPCMSoftProftAdjust,

    MenuAdvanceODOnOffAdjust,
    MenuAdvanceODGainAdjust,

    MenuAdvanceDpD0VersionAdjust,
    MenuAdvanceDpD1VersionAdjust,
    MenuAdvanceDpD6VersionAdjust,

    MenuAdvanceDpD0LaneCountAdjust,
    MenuAdvanceDpD1LaneCountAdjust,
    MenuAdvanceDpD6LaneCountAdjust,

#if(_ULTRA_HDR_SUPPORT == _ON)
    MenuAdvanceHdrModeAdjust,
    MenuAdvanceHdrDarkEnhanceOnOffAdjust,
#endif

    // ddcci
    MenuHotKeyDdcci,

    // hotkey source
    MenuHotKeySource,
    MenuHotKeyDisplayMode,

    // hotkey information
    MenuHotKeyInformation,

    // ask turn off/on panel uniformity msg
    MenuPanelUniformityMsgAdjust,

    // display PS logo
    MenuMeseageDisplay,
};

#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
