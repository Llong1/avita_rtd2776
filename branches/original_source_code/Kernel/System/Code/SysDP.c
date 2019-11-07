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
// ID Code      : SysDP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SYSTEM_DP__

#include "SysInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//--------------------------------------------------
// Definitions of mode search status
//--------------------------------------------------


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_DP_TYPE_C_SUPPORT == _ON)

#if(_D0_DP_TYPE_C_SUPPORT == _ON)
StructPortController g_stD0PortControllerInfo;

#if(_D0_DP_USB_HUB_SUPPORT == _ON)
StructUsbHubInfo g_stD0UsbHubInfo;
#endif

#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
StructPortController g_stD1PortControllerInfo;

#if(_D1_DP_USB_HUB_SUPPORT == _ON)
StructUsbHubInfo g_stD1UsbHubInfo;
#endif

#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
StructPortController g_stD6PortControllerInfo;

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
StructUsbHubInfo g_stD6UsbHubInfo;
#endif

#endif

#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
void SysDpRxHandler(void);

#if(_DP_TYPE_C_SUPPORT == _ON)

void SysDpTypeCHandler(void);
void SysDpTypeCPortControllerProc(void);

#if(_DP_USB_HUB_SUPPORT == _ON)
void SysDpUsbHubProc(void);
void SysDpUsbHubConfigProc(BYTE ucInputPort, BYTE ucDpLanes);
void SysDpUsbHubDetectProc(BYTE ucInputPort);

#if(_D0_DP_USB_HUB_SUPPORT == _ON)
void SysDpD0UsbHubDetectProc(void);
#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)
void SysDpD1UsbHubDetectProc(void);
#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
void SysDpD6UsbHubDetectProc(void);
#endif

BYTE SysDpGetUsbHubDeviceInfo(BYTE ucInputPort);
bit SysDpGetUsbHubChangeFlg(BYTE ucInputPort);
#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DP_TYPE_C_SUPPORT == _ON))
bit SysDpTypeCGetD0AltModeCheck(void);
void SysDpTypeCSetD0LaneCount(BYTE ucTypeCLane);
#endif

#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DP_TYPE_C_SUPPORT == _ON))
bit SysDpTypeCGetD1AltModeCheck(void);
void SysDpTypeCSetD1LaneCount(BYTE ucTypeCLane);
#endif

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_DP_TYPE_C_SUPPORT == _ON))
bit SysDpTypeCGetD6AltModeCheck(void);
void SysDpTypeCSetD6LaneCount(BYTE ucTypeCLane);
#endif

#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)

#endif

#if(_DP_TX_SUPPORT == _ON)
void SysDpTxHandler(void);
BYTE SysDpTxCloneGetInputPort(void);
bit SysDpTxCloneOutputStatus(void);
#endif

#if(_DP_MST_SUPPORT == _ON)
void SysDpMstHandler(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpRxHandler(void)
{
    ScalerSyncDpCapabilitySwitchProc();

#if(_DP_TX_SUPPORT == _ON)
    ScalerSyncDpTxHdcpUpstreamSwitchProc(GET_MODE_DISPLAY_MODE(), SysDpTxCloneGetInputPort());
#endif

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
    ScalerDpTxCloneOutputProc(SysSourceGetInputPort(), GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())), SysDpTxCloneOutputStatus());
#endif
}

#if(_DP_TYPE_C_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTypeCHandler(void)
{
    SysDpTypeCPortControllerProc();

#if(_DP_USB_HUB_SUPPORT == _ON)
    SysDpUsbHubProc();
#endif
}

//--------------------------------------------------
// Description  : Type-C Port Controller Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTypeCPortControllerProc(void)
{
#if(_D0_DP_TYPE_C_SUPPORT == _ON)
    if((UserCommonPortControllerGetD0PortPower() == _ON) && (GET_D0_DP_TYPE_C_LANE_STATUS() != UserInterfaceGetDpLaneCount(_D0_INPUT_PORT)))
    {
        if(UserCommonPortControllerConfig(_D0_INPUT_PORT) == _TRUE)
        {
            SET_D0_DP_TYPE_C_LANE_STATUS(UserInterfaceGetDpLaneCount(_D0_INPUT_PORT));
            ScalerDpLaneCountSwitch(_D0_INPUT_PORT, GET_D0_DP_TYPE_C_LANE_STATUS());
        }
    }
#endif

#if(_D1_DP_TYPE_C_SUPPORT == _ON)
    if((UserCommonPortControllerGetD1PortPower() == _ON) && (GET_D1_DP_TYPE_C_LANE_STATUS() != UserInterfaceGetDpLaneCount(_D1_INPUT_PORT)))
    {
        if(UserCommonPortControllerConfig(_D1_INPUT_PORT) == _TRUE)
        {
            SET_D1_DP_TYPE_C_LANE_STATUS(UserInterfaceGetDpLaneCount(_D1_INPUT_PORT));
            ScalerDpLaneCountSwitch(_D1_INPUT_PORT, GET_D1_DP_TYPE_C_LANE_STATUS());
        }
    }
#endif

#if(_D6_DP_TYPE_C_SUPPORT == _ON)
    if((UserCommonPortControllerGetD6PortPower() == _ON) && (GET_D6_DP_TYPE_C_LANE_STATUS() != UserInterfaceGetDpLaneCount(_D6_INPUT_PORT)))
    {
        if(UserCommonPortControllerConfig(_D6_INPUT_PORT) == _TRUE)
        {
            SET_D6_DP_TYPE_C_LANE_STATUS(UserInterfaceGetDpLaneCount(_D6_INPUT_PORT));
            ScalerDpLaneCountSwitch(_D6_INPUT_PORT, GET_D6_DP_TYPE_C_LANE_STATUS());
        }
    }
#endif
}

#if(_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Usb Hub Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpUsbHubProc(void)
{
#if(_D0_DP_USB_HUB_SUPPORT == _ON)

    SysDpUsbHubDetectProc(_D0_INPUT_PORT);
    SysDpUsbHubConfigProc(_D0_INPUT_PORT, GET_D0_DP_TYPE_C_LANE_STATUS());

#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)

    SysDpUsbHubDetectProc(_D1_INPUT_PORT);
    SysDpUsbHubConfigProc(_D1_INPUT_PORT, GET_D1_DP_TYPE_C_LANE_STATUS());

#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)

    SysDpUsbHubDetectProc(_D6_INPUT_PORT);
    SysDpUsbHubConfigProc(_D6_INPUT_PORT, GET_D6_DP_TYPE_C_LANE_STATUS());

#endif
}

//--------------------------------------------------
// Description  : Adjust Type-C Dp Lanes
// Input Value  : ucInputPort --> Input Port
//                ucDpLanes   --> Target Dp Lanes
// Output Value : None
//--------------------------------------------------
void SysDpUsbHubConfigProc(BYTE ucInputPort, BYTE ucDpLanes)
{
    if(ucDpLanes == _DP_TWO_LANE)
    {
        switch(ucInputPort)
        {
#if(_D0_DP_USB_HUB_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                if(GET_D0_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(GET_D0_TYPE_C_USB_HUB_INFO() == 0x00)
                    {
                        break;
                    }

                    if(UserCommonUsbHubSetSSMode(_D0_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                if(GET_D1_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(GET_D1_TYPE_C_USB_HUB_INFO() == 0x00)
                    {
                        break;
                    }

                    if(UserCommonUsbHubSetSSMode(_D1_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
            case _D6_INPUT_PORT:

                if(GET_D6_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_SS_STATE)
                {
                    if(GET_D6_TYPE_C_USB_HUB_INFO() == 0x00)
                    {
                        break;
                    }

                    if(UserCommonUsbHubSetSSMode(_D6_INPUT_PORT, _ENABLE) == _TRUE)
                    {
                        SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);
                    }
                }

                break;
#endif

            default:
                break;
        }
    }
    else
    {
        switch(ucInputPort)
        {
#if(_D0_DP_USB_HUB_SUPPORT == _ON)
            case _D0_INPUT_PORT:

                if(GET_D0_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D0_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)
            case _D1_INPUT_PORT:

                if(GET_D1_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D1_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);
                    }
                }

                break;
#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
            case _D6_INPUT_PORT:

                if(GET_D6_USB_HUB_MODE_STATE() != _USB_MODE_STATUS_DETECT_SS_STATE)
                {
                    if(UserCommonUsbHubSetSSMode(_D6_INPUT_PORT, _DISABLE) == _TRUE)
                    {
                        SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
                        ScalerTimerReactiveTimerEvent(SEC(2), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);
                    }
                }

                break;
#endif
            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Detect Usb Hub Info
// Input Value  : ucInputPort --> Input Port
// Output Value : None
//--------------------------------------------------
void SysDpUsbHubDetectProc(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_USB_HUB_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            SysDpD0UsbHubDetectProc();

            break;
#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            SysDpD1UsbHubDetectProc();

            break;
#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)

        case _D6_INPUT_PORT:

            SysDpD6UsbHubDetectProc();

            break;
#endif

        default:
            break;
    }
}

#if(_D0_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpD0UsbHubDetectProc(void)
{
    BYTE ucUsbHubInfo = 0x00;

    CLR_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D0_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D0_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D0_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if((GET_D0_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE) && (UserInterfaceTypecGetUSBSupportStatus(_D0_INPUT_PORT) == _ON))
            {
                CLR_D0_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D0_INPUT_PORT), _SYSTEM_TIMER_EVENT_D0_USBHUB_DETECT);

                ucUsbHubInfo = UserCommonUsbHubDetectSSDevicePlugInfo(_D0_INPUT_PORT);

                if(GET_D0_TYPE_C_USB_HUB_INFO() != ucUsbHubInfo)
                {
                    SET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
                    SET_D0_TYPE_C_USB_HUB_INFO(ucUsbHubInfo);
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D0_DP_USB_HUB_SUPPORT == _ON)

#if(_D1_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpD1UsbHubDetectProc(void)
{
    BYTE ucUsbHubInfo = 0x00;

    CLR_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D1_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D1_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D1_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if((GET_D1_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE) && (UserInterfaceTypecGetUSBSupportStatus(_D1_INPUT_PORT) == _ON))
            {
                CLR_D1_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D1_INPUT_PORT), _SYSTEM_TIMER_EVENT_D1_USBHUB_DETECT);

                ucUsbHubInfo = UserCommonUsbHubDetectSSDevicePlugInfo(_D1_INPUT_PORT);

                if(GET_D1_TYPE_C_USB_HUB_INFO() != ucUsbHubInfo)
                {
                    SET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
                    SET_D1_TYPE_C_USB_HUB_INFO(ucUsbHubInfo);
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D1_DP_USB_HUB_SUPPORT == _ON)

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Detect SS Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpD6UsbHubDetectProc(void)
{
    BYTE ucUsbHubInfo = 0x00;

    CLR_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();

    switch(GET_D6_USB_HUB_MODE_STATE())
    {
        case _USB_MODE_STATUS_INITIAL:

            SET_D6_USB_HUB_MODE_STATE(_USB_MODE_STATUS_DETECT_SS_STATE);
            SET_D6_USB_HUB_SS_DEVICE_DETECT_FLG();

            break;

        case _USB_MODE_STATUS_DETECT_SS_STATE:
        case _USB_MODE_STATUS_SS_STATE:

            if((GET_D6_USB_HUB_SS_DEVICE_DETECT_FLG() == _TRUE) && (UserInterfaceTypecGetUSBSupportStatus(_D6_INPUT_PORT) == _ON))
            {
                CLR_D6_USB_HUB_SS_DEVICE_DETECT_FLG();
                ScalerTimerActiveTimerEvent(UserCommonUsbHubSetPollingStep(_D6_INPUT_PORT), _SYSTEM_TIMER_EVENT_D6_USBHUB_DETECT);

                ucUsbHubInfo = UserCommonUsbHubDetectSSDevicePlugInfo(_D6_INPUT_PORT);

                if(GET_D6_TYPE_C_USB_HUB_INFO() != ucUsbHubInfo)
                {
                    SET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
                    SET_D6_TYPE_C_USB_HUB_INFO(ucUsbHubInfo);
                }
            }

            break;

        default:
        case _USB_MODE_STATUS_PS_STATE:
        case _USB_MODE_STATUS_PD_STATE:

            break;
    }
}
#endif // End of #if(_D6_DP_USB_HUB_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Get Usb Hub Device Info
// Input Value  : ucInputPort --> Input Port
// Output Value : Usb Hub Info
//--------------------------------------------------
BYTE SysDpGetUsbHubDeviceInfo(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_USB_HUB_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            return GET_D0_TYPE_C_USB_HUB_INFO();
#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            return GET_D1_TYPE_C_USB_HUB_INFO();
#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            return GET_D6_TYPE_C_USB_HUB_INFO();
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : Get Usb Hub Device Info Change Flag
// Input Value  : ucInputPort --> Input Port
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit SysDpGetUsbHubChangeFlg(BYTE ucInputPort)
{
    switch(ucInputPort)
    {
#if(_D0_DP_USB_HUB_SUPPORT == _ON)

        case _D0_INPUT_PORT:

            return GET_D0_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
#endif

#if(_D1_DP_USB_HUB_SUPPORT == _ON)

        case _D1_INPUT_PORT:

            return GET_D1_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
#endif

#if(_D6_DP_USB_HUB_SUPPORT == _ON)
        case _D6_INPUT_PORT:

            return GET_D6_USB_HUB_PLUG_DEVICE_CHANGE_FLG();
#endif

        default:
            break;
    }

    return 0;
}
#endif // End of #if(_DP_USB_HUB_SUPPORT == _ON)

#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DP_TYPE_C_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get D0 Cable Status
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysDpTypeCGetD0AltModeCheck(void)
{
    if(GET_D0_DP_TYPE_C_CABLE_DETECT() == _FALSE)
    {
        if(GET_D0_DP_TYPE_C_ALTMODE_STATUS() == _TRUE)
        {
            return _FALSE;
        }

        return _TRUE;
    }
    else
    {
        CLR_D0_DP_TYPE_C_CABLE_DETECT();
        ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D0_TYPEC_CABLE_DETECT);

        if(UserCommonPortControllerCheckPCEnterAltMode(_D0_INPUT_PORT) == _FALSE)
        {
            CLR_D0_DP_TYPE_C_ALTMODE_STATUS();

            return _TRUE;
        }
        else
        {
            SET_D0_DP_TYPE_C_ALTMODE_STATUS();

            return _FALSE;
        }
    }
}

//--------------------------------------------------
// Description  : Set D0 Type-C Lane Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTypeCSetD0LaneCount(BYTE ucTypeCLane)
{
    SET_D0_DP_TYPE_C_LANE_STATUS(ucTypeCLane);
}
#endif

#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DP_TYPE_C_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get D1 Cable Status
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysDpTypeCGetD1AltModeCheck(void)
{
    if(GET_D1_DP_TYPE_C_CABLE_DETECT() == _FALSE)
    {
        if(GET_D1_DP_TYPE_C_ALTMODE_STATUS() == _TRUE)
        {
            return _FALSE;
        }

        return _TRUE;
    }
    else
    {
        CLR_D1_DP_TYPE_C_CABLE_DETECT();
        ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D1_TYPEC_CABLE_DETECT);

        if(UserCommonPortControllerCheckPCEnterAltMode(_D1_INPUT_PORT) == _FALSE)
        {
            CLR_D1_DP_TYPE_C_ALTMODE_STATUS();

            return _TRUE;
        }
        else
        {
            SET_D1_DP_TYPE_C_ALTMODE_STATUS();

            return _FALSE;
        }
    }
}

//--------------------------------------------------
// Description  : Set D1 Type-C Lane Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTypeCSetD1LaneCount(BYTE ucTypeCLane)
{
    SET_D1_DP_TYPE_C_LANE_STATUS(ucTypeCLane);
}
#endif

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_DP_TYPE_C_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get D6 Cable Status
// Input Value  : None
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit SysDpTypeCGetD6AltModeCheck(void)
{
    if(GET_D6_DP_TYPE_C_CABLE_DETECT() == _FALSE)
    {
        if(GET_D6_DP_TYPE_C_ALTMODE_STATUS() == _TRUE)
        {
            return _FALSE;
        }

        return _TRUE;
    }
    else
    {
        CLR_D6_DP_TYPE_C_CABLE_DETECT();
        ScalerTimerActiveTimerEvent(SEC(0.5), _SYSTEM_TIMER_EVENT_D6_TYPEC_CABLE_DETECT);

        if(UserCommonPortControllerCheckPCEnterAltMode(_D6_INPUT_PORT) == _FALSE)
        {
            CLR_D6_DP_TYPE_C_ALTMODE_STATUS();

            return _TRUE;
        }
        else
        {
            SET_D6_DP_TYPE_C_ALTMODE_STATUS();

            return _FALSE;
        }
    }
}

//--------------------------------------------------
// Description  : Set D6 Type-C Lane Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTypeCSetD6LaneCount(BYTE ucTypeCLane)
{
    SET_D6_DP_TYPE_C_LANE_STATUS(ucTypeCLane);
}
#endif

#endif // End of #if(_DP_TYPE_C_SUPPORT == _ON)
#endif // End of #if(_DP_SUPPORT == _ON)

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Tx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpTxHandler(void)
{
    if((GET_POWER_STATUS() == _POWER_STATUS_NORMAL) || (GET_POWER_STATUS() == _POWER_STATUS_FAKE_SAVING) || (GET_POWER_STATUS() == _POWER_STATUS_NOSUPPORT_SAVING))
    {
        // HPD Detection Function
        ScalerDpTxHPDProc();

        ScalerDpTxJudgeHandler();

        ScalerDpTxModeHandler();

#if(_DP_MST_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        ScalerDpRx0HDCPHandler();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        ScalerDpRx1HDCPHandler();
#endif
#endif

        ScalerDpTxHDCPHandler();
    }
}

//--------------------------------------------------
// Description  : DP Rx Handler
// Input Value  : None
// Output Value : Input Port
//--------------------------------------------------
BYTE SysDpTxCloneGetInputPort(void)
{
    return ((GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P) ? SysSourceGetInputPort() : UserInterfaceGetDpCloneOutputUserInputPort());
}

//--------------------------------------------------
// Description  : Decide whether to Clone output to DP Tx
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit SysDpTxCloneOutputStatus(void)
{
    BYTE ucDisplayStartRegion = _DISPLAY_RGN_NONE;
    BYTE ucDisplayEndRegion = _DISPLAY_RGN_NONE;

    if(UserInterfaceGetDpCloneOutputStatus() == _FALSE)
    {
        return _FALSE;
    }

    if(GET_MODE_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        if(SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_ACTIVE)
        {
            if(SysRegionGetSourceType(_DISPLAY_RGN_1P) == _SOURCE_DP)
            {
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _OFF))
                if(SysSourceGetInputPort() == _D0_INPUT_PORT)
                {
                    return _FALSE;
                }
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _OFF))
                if(SysSourceGetInputPort() == _D1_INPUT_PORT)
                {
                    return _FALSE;
                }
#endif

#if(_FREESYNC_SUPPORT == _ON)
                if(ScalerSyncGetFREESYNCEnable() == _TRUE)
                {
                    return _FALSE;
                }
#endif
            }

            return _TRUE;
        }
    }
    else
    {
        switch(GET_MODE_DISPLAY_MODE())
        {
            case _DISPLAY_MODE_4P:

                ucDisplayStartRegion = _DISPLAY_RGN_LT;
                ucDisplayEndRegion = _DISPLAY_RGN_RB;

                break;

            case _DISPLAY_MODE_PBP_TB:

                ucDisplayStartRegion = _DISPLAY_RGN_TOP;
                ucDisplayEndRegion = _DISPLAY_RGN_BOTTOM;

                break;

            case _DISPLAY_MODE_PIP:

                ucDisplayStartRegion = _DISPLAY_RGN_MAIN;
                ucDisplayEndRegion = _DISPLAY_RGN_SUB;

                break;

            case _DISPLAY_MODE_PBP_LR:

                ucDisplayStartRegion = _DISPLAY_RGN_LEFT;
                ucDisplayEndRegion = _DISPLAY_RGN_RIGHT;

                break;

            default:

                break;
        }

        while(ucDisplayStartRegion <= ucDisplayEndRegion)
        {
            if((SysRegionGetPortType(ucDisplayStartRegion) == UserInterfaceGetDpCloneOutputUserInputPort()) &&
               (SysRegionGetDisplayState(ucDisplayStartRegion) == _DISPLAY_STATE_ACTIVE))
            {
                return _TRUE;
            }

            ucDisplayStartRegion++;
        }
    }

    return _FALSE;
}
#endif

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Rx MST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void SysDpMstHandler(void)
{
    if((GET_POWER_STATUS() == _POWER_STATUS_NORMAL) || (GET_POWER_STATUS() == _POWER_STATUS_FAKE_SAVING) || (GET_POWER_STATUS() == _POWER_STATUS_NOSUPPORT_SAVING))
    {
        ScalerDpRxMstHandler();

#if(_DP_TX_SUPPORT == _ON)
        ScalerDpTxMstHandler();
#endif

        ScalerDpRxMstStreamsHandler();
    }
}
#endif
