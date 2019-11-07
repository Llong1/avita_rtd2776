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
// ID Code      : SysTimer.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_TIMER__

#include "SysInclude.h"

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
// Backup for Burst Write Bug
BYTE g_ucBackup_TIMER0;
BYTE g_ucBackup_TIMER1;
BYTE g_ucBackup_TIMER2;
BYTE g_ucBackup_WDTIMER;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void SysTimerHandler(void);
void SysTimerEventProc(EnumScalerTimerEventID enumEventID);
void SysTimerIntProc0(void);
void SysTimerIntProc1(void);
void SysTimerIntProc2(void);
void SysTimerWDIntProc(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Timer Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysTimerHandler(void)
{
    BYTE ucTimerEventIndex = 0;
    BYTE ucTimerEventID = 0;

    for(ucTimerEventIndex = 0; ucTimerEventIndex < _TIMER_EVENT_COUNT; ucTimerEventIndex++)
    {
        if((ScalerTimerCheckEventValid(ucTimerEventIndex) == _TRUE) &&
           (ScalerTimerGetTimerCounter() > ScalerTimerGetEventTime(ucTimerEventIndex)))
        {
            ucTimerEventID = ScalerTimerGetEventID(ucTimerEventIndex);
            ScalerTimerClrEventValid(ucTimerEventIndex);

            if(ucTimerEventID < _USER_TIMER_EVENT_END)
            {
                UserInterfaceTimerEventProc(ucTimerEventID);
            }
            else if(ucTimerEventID < _SYSTEM_TIMER_EVENT_END)
            {
                SysTimerEventProc(ucTimerEventID);
            }
            else
            {
                ScalerTimerEventProc(ucTimerEventID);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Timer Event Process
// Input Value  : enumEventID --> Event to be processed
// Output Value : None
//--------------------------------------------------
void SysTimerEventProc(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
        case _SYSTEM_TIMER_EVENT_SOURCE_CLEAR_DETECTING:
            SysSourceClearDetectingEvent();
            break;

        case _SYSTEM_TIMER_EVENT_JUDGE_ACTIVE_STATE:
            SET_MODE_ACTIVE_READY();
            break;

        case _SYSTEM_TIMER_EVENT_JUDGE_NOSUPPORT_STATE:

            // Set no support flag for current display setting target
            SET_RGN_DISPLAY_ACTION(GET_MODE_DISPLAY_TARGET_INDEX(), _DISPLAY_ACTION_OOR);

            DebugMessageSystem("Display OOR", GET_MODE_DISPLAY_TARGET_INDEX());

            break;

        case _SYSTEM_TIMER_EVENT_SOURCE_NOSUPPORT_STATE:

            // Set no support flag for current display setting target
            SET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX(), _DISPLAY_ACTION_OOR);

            // Clear display stop flag
            CLR_RGN_MEASURE_CHECKING(GET_SOURCE_MEASURE_TARGET_INDEX());

            DebugMessageSystem("Source OOR", GET_SOURCE_MEASURE_TARGET_INDEX());

            break;

        case _SYSTEM_TIMER_EVENT_SOURCE_NOSIGNAL_STATE:

            DebugMessageSystem("Measure Timeout", GET_SOURCE_MEASURE_TARGET_INDEX());

            // Reset region interface
            SysSourceResetRegion(GET_SOURCE_MEASURE_TARGET_INDEX());

            // Switch to NSG, if not already there
            if((GET_RGN_DISPLAY_STATE(GET_SOURCE_MEASURE_TARGET_INDEX()) != _DISPLAY_STATE_NO_SIGNAL) &&
               (GET_RGN_DISPLAY_ACTION(GET_SOURCE_MEASURE_TARGET_INDEX()) != _DISPLAY_ACTION_NO_SIGNAL))
            {
                SysRegionSetDisplayStateBySearchIndex(GET_RGN_SOURCE_INDEX(GET_SOURCE_MEASURE_TARGET_INDEX()), _DISPLAY_STATE_NO_SIGNAL);
            }

            break;

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _SYSTEM_TIMER_EVENT_SOURCE_DP_SWITCH_TIMEOUT:
            SET_SOURCE_DP_SWITCH_TIMEOUT();
            break;
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
        case _SYSTEM_TIMER_EVENT_SOURCE_DP_DUAL_SWITCH_TIMEOUT:
            SET_SOURCE_DP_DUAL_SWITCH_TIMEOUT();
            break;
#endif

#if(_EMBEDDED_DAC_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_INITIAL:
            ScalerAudioDACSetState(_AUDIO_DAC_CHARGE);
            break;

        case _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_VCM_CHARGE:
            ScalerAudioDACSetState(_AUDIO_DAC_DEPOP);
            break;

        case _SYSTEM_TIMER_EVENT_AUDIO_DAC_WAIT_DEPOP_TO_NORMAL:
            ScalerAudioDACDepopToNormal();
            break;
#endif // End of #if(_EMBEDDED_DAC_SUPPORT == _ON)

#if(_D0_DP_TYPE_C_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D0_TYPEC_CABLE_DETECT:
            SET_D0_DP_TYPE_C_CABLE_DETECT();
            break;

#if(_D0_DP_USB_HUB_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT:
            SET_D0_USB_HUB_SS_DEVICE_DETECT_FLG();
            break;
#endif
#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D1_TYPEC_CABLE_DETECT:
            SET_D1_DP_TYPE_C_CABLE_DETECT();
            break;

#if(_D1_DP_USB_HUB_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT:
            SET_D1_USB_HUB_SS_DEVICE_DETECT_FLG();
            break;
#endif
#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D6_TYPEC_CABLE_DETECT:
            SET_D6_DP_TYPE_C_CABLE_DETECT();
            break;

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
        case _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT:
            SET_D6_USB_HUB_SS_DEVICE_DETECT_FLG();
            break;
#endif
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Timer0 Int Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void SysTimerIntProc0(void) interrupt 1
{
    // Backup for Burst Write Bug
    g_ucBackup_TIMER0 = MCU_FFF4_SCA_INF_ADDR;

#if(_INSTANT_TIMER_EVENT_0 == _ON)
    // Clear Timer0 flag
    TF0 = 0;

    TL0 = g_ucTimerCountLByte0;
    TH0 = g_ucTimerCountHByte0;

    TR0 = _ON;

    if(++g_usTimerAxisCnt0 == g_usTimerEventPeriod0)
    {
        g_usTimerAxisCnt0 = 0;
        UserInterfaceTimer0InstantAccess_EXINT();
    }
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_TIMER0;
}
#pragma restore

//--------------------------------------------------
// Description  : Timer1 Int Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void SysTimerIntProc1(void) interrupt 3
{
    // Backup for Burst Write Bug
    g_ucBackup_TIMER1 = MCU_FFF4_SCA_INF_ADDR;

#if(_INSTANT_TIMER_EVENT_1 == _ON)
    // Clear Timer1 flag
    TF1 = 0;

    TL1 = g_ucTimerCountLByte1;
    TH1 = g_ucTimerCountHByte1;

    TR1 = _ON;

    if(++g_usTimerAxisCnt1 == g_usTimerEventPeriod1)
    {
        g_usTimerAxisCnt1 = 0;
        UserInterfaceTimer1InstantAccess_EXINT();
    }
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_TIMER1;
}
#pragma restore

//--------------------------------------------------
// Description  : Timer2 Int Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void SysTimerIntProc2(void) interrupt 5
{
    // Backup for Burst Write Bug
    g_ucBackup_TIMER2 = MCU_FFF4_SCA_INF_ADDR;

    // Clear Timer2 flag
    TF2 = 0;

#if(_WD_TIMER_INT_SUPPORT == _OFF)
    // Clear watchdog
    CLR_MCU_WATCH_DOG();
#else
    // Latch Current Counter and not clear any WD timer counter
    MCU_FFEB_WDT_TEST |= _BIT3;

    // Add to Prevent INT Lock Reset
    if((MCU_FFAD_WATCHDOG_CNT1_VALUE & 0x07) > 0x04)
    {
        // Clear watchdog
        CLR_MCU_WATCH_DOG();
    }
#endif

#if(_SYSTEM_TIMER_QUARTER_RESOLUTION == _OFF)

    g_bNotifyTimer2Int = _TRUE;

    // Timer Counter
    g_usTimerCounter += 1;

#else

    if(g_ucTimerQuarterCount >= 3)
    {
        g_ucTimerQuarterCount = 0;

        g_bNotifyTimer2Int = _TRUE;

        // Timer Counter
        g_usTimerCounter += 1;
    }
    else
    {
        g_ucTimerQuarterCount++;
    }

    UserInterfaceTimer2InstantAccess_EXINT();

#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_TIMER2;
}
#pragma restore

//--------------------------------------------------
// Description  : WD Timer Int Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
void SysTimerWDIntProc(void) interrupt 8 using 3
{
    // Backup for Burst Write Bug
    g_ucBackup_WDTIMER = MCU_FFF4_SCA_INF_ADDR;

    // Clear Flag
    EXIF &= ~_BIT4;

#if(_WD_TIMER_INT_SUPPORT == _ON)
    ScalerTimerWDEventProc_WDINT();
#endif

    // Reload Backup for Burst Write Bug
    MCU_FFF4_SCA_INF_ADDR = g_ucBackup_WDTIMER;
}
#pragma restore
