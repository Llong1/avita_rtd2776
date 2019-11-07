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
// ID Code      : RL6410_Series_DP.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_SUPPORT == _ON)

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
StructDpInterlaceStatus g_stDpInterlaceStatus;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction);
EnumDpRefLinkClock ScalerDpLinkClockValid(void);

#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
void ScalerDpTxSSTSetAmdSpdInfo(bit bPlayback);
#endif
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Check DP Into Power Saving
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpPowerSwitch(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Power Down MST Reset
#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

            ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

            // Power Down HDCP Reset
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D0_DP_MST_PORT_SUPPORT == _ON))
            ScalerDpRx0HDCPBlockReset();
#endif

#if((_D1_INPUT_PORT_TYPE == _D1_DP_PORT) && (_D1_DP_MST_PORT_SUPPORT == _ON))
            ScalerDpRx1HDCPBlockReset();
#endif
#endif // End of #if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            // Add for DPCD 2002h Bug
            CLR_DP_RX0_AUX_COMMAND_NO_REPLY();
            SET_DP_RX0_POWER_STATE_INTO_PS();

            SET_DP_RX0_FAKE_LINK_TRAINING();

            SET_DP_RX0_AUX_MANUAL_MODE();

            if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
            {
                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
            }

            SET_DP_RX0_AUX_AUTO_MODE();

#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
            {
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                if(GET_D6_SWITCH_SELECT() == _D0_INPUT_PORT)
#endif
                {
                    ScalerDpRx0MstInfoBackup(_DP_MST_BACKUP_INFO);
                }
#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                else if(GET_D6_SWITCH_SELECT() == _D6_INPUT_PORT)
                {
                    ScalerDpRx6MstInfoBackup(_DP_MST_BACKUP_INFO);
                }
#endif
                ScalerDpMstReset(_DP_MST_RX0_PORT);

                ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);
                ScalerDpRx0HotPlugEvent(_DP_HPD_LOW_RESET_AUX);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
            }
            else
#endif
            {
                if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
                {
                    ScalerDpRx0DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);
                    ScalerDpRx0HotPlugEvent(_DP_HPD_LOW_RESET_AUX);

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HOTPLUG_ASSERTED);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_HDCP_LONG_HOTPLUG_EVENT);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX0_LINK_STATUS_IRQ);
                }
                else
                {
                    // Disable HDCP support
                    ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
                    // Disable Write AKSV int
                    ScalerSetBit(PB7_A5_AUX_RESERVE5, ~_BIT6, 0x00);
#endif
                    // Disable Write 68xxx int
                    ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~_BIT2, 0x00);
                }
            }
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            // Add for DPCD 2002h Bug
            CLR_DP_RX1_AUX_COMMAND_NO_REPLY();
            SET_DP_RX1_POWER_STATE_INTO_PS();

            SET_DP_RX1_FAKE_LINK_TRAINING();

            SET_DP_RX1_AUX_MANUAL_MODE();

            if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
            {
                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
            }

            SET_DP_RX1_AUX_AUTO_MODE();

#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
            {
                ScalerDpRx1MstInfoBackup(_DP_MST_BACKUP_INFO);

                ScalerDpMstReset(_DP_MST_RX1_PORT);

                ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);
                ScalerDpRx1HotPlugEvent(_DP_HPD_LOW_RESET_AUX);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
            }
            else
#endif
            {
                if(GET_DP_DC_OFF_HPD_HIGH() == _FALSE)
                {
                    ScalerDpRx1DpcdLinkStatusReset(_DP_DPCD_LINK_STATUS_INITIAL);
                    ScalerDpRx1HotPlugEvent(_DP_HPD_LOW_RESET_AUX);

                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HOTPLUG_ASSERTED);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_HDCP_LONG_HOTPLUG_EVENT);
                    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX1_LINK_STATUS_IRQ);
                }
                else
                {
                    // Disable HDCP support
                    ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x00);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
                    // Disable Write AKSV int
                    ScalerSetBit(PBA_A5_AUX_RESERVE5, ~_BIT6, 0x00);
#endif
                    // Disable Write 68xxx int
                    ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT2, 0x00);
                }
            }
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            ScalerSyncDpLowPowerProc();

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            // Add for DPCD 2002h Bug
            CLR_DP_RX0_AUX_COMMAND_NO_REPLY();
            SET_DP_RX0_POWER_STATE_INTO_PS();

            SET_DP_RX0_FAKE_LINK_TRAINING();

            SET_DP_RX0_AUX_MANUAL_MODE();

            if(GET_DP_RX0_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
            {
                SET_DP_RX0_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
            }

            SET_DP_RX0_AUX_AUTO_MODE();

#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)
            {
                ScalerDpMstReset(_DP_MST_RX0_PORT);
            }
#endif

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            // Add for DPCD 2002h Bug
            CLR_DP_RX1_AUX_COMMAND_NO_REPLY();
            SET_DP_RX1_POWER_STATE_INTO_PS();

            SET_DP_RX1_FAKE_LINK_TRAINING();

            SET_DP_RX1_AUX_MANUAL_MODE();

            if(GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_LINK_TRAINING_PASS)
            {
                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);
            }

            SET_DP_RX1_AUX_AUTO_MODE();

#if(_DP_MST_SUPPORT == _ON)
            if(g_enumDpMSTCapablePort == _DP_MST_RX1_PORT)
            {
                ScalerDpMstReset(_DP_MST_RX1_PORT);
            }
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            ScalerSyncDpLowPowerProc();

            break;

        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

            // Disable Aux Power Saving Mode
            ScalerSetBit(PB7_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit(PB7_63_AUX_3, ~_BIT7, 0x00);

            // Aux comm current select max
            ScalerSetBit(PB7_64_AUX_4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Disable Aux INT
            ScalerSetBit(PB7_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

            // Stream Load By 63th MTPH
            ScalerSetBit(PB5_02_STHD_CTRL_1, ~_BIT7, 0x00);

            // Clear flag for write 68xxx int
            ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

            // Enable Write 68xxx int
            ScalerSetBit(PB7_DA_AUX_FIFO_RST, ~_BIT2, _BIT2);

#if((_DP_TX_SUPPORT == _ON) && (_D0_DP_MST_PORT_SUPPORT == _ON))
            // Clear flag for Write AKSV int
            ScalerSetBit(PB7_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

            // Enable Write AKSV int
            ScalerSetBit(PB7_A5_AUX_RESERVE5, ~_BIT6, _BIT6);

            // Enable HDCP and repeater support
            ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x03);
#else
            // Enable HDCP support
            ScalerDpRx0SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif
            if(ScalerGlobalGetIDCode() == _RL6410_VER_B_ID_CODE)
            {
                // Diable DP HDCP Capable
                ScalerDpRx0SetDpcdBitValue(0x06, 0x80, 0x28, ~_BIT0, 0x00);
            }
#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

            // Disable Aux Power Saving Mode
            ScalerSetBit(PBA_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit(PBA_63_AUX_3, ~_BIT7, 0x00);

            // Aux comm current select max
            ScalerSetBit(PBA_64_AUX_4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Disable Aux INT
            ScalerSetBit(PBA_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

            // Stream Load By 63th MTPH
            ScalerSetBit(PB8_02_STHD_CTRL_1, ~_BIT7, 0x00);

            // Clear flag for write 68xxx int
            ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

            // Enable Write 68xxx int
            ScalerSetBit(PBA_DA_AUX_FIFO_RST, ~_BIT2, _BIT2);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
            // Clear flag for Write AKSV int
            ScalerSetBit(PBA_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

            // Enable Write AKSV int
            ScalerSetBit(PBA_A5_AUX_RESERVE5, ~_BIT6, _BIT6);

            // Enable HDCP and repeater support
            ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x03);
#else
            // Enable HDCP support
            ScalerDpRx1SetDpcdValue(0x06, 0x80, 0x28, 0x01);
#endif
            if(ScalerGlobalGetIDCode() == _RL6410_VER_B_ID_CODE)
            {
                // Diable DP HDCP Capable
                ScalerDpRx1SetDpcdBitValue(0x06, 0x80, 0x28, ~_BIT0, 0x00);
            }
#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#if((_DP_TX_SUPPORT == _ON) && (_DP_FREESYNC_SUPPORT == _ON))

            // Specify Packet Detect Type
            ScalerSetByte(PBC_53_DP_INFO_FM_RSV0, _SPD_INFO_TYPE);

#endif

            IP = 0xA0;

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Check DP Link Clcok Vilid for MAC
// Input Value  : None
// Output Value : Invalid or Valid Div1 or Valid Div2
//--------------------------------------------------
EnumDpRefLinkClock ScalerDpLinkClockValid(void)
{
    if(ScalerGlobalGetIDCode() >= _RL6410_VER_C_ID_CODE)
    {
        return _DP_LCLK_DIVIDE_BY_2;
    }
    else
    {
        return _DP_LCLK_FAIL;
    }
}

#if(_DP_FREESYNC_SUPPORT == _ON)
#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set DP TX AMD SPD info, using MPEG info
// Input Value  : On/ Off
// Output Value : None
//--------------------------------------------------
void ScalerDpTxSSTSetAmdSpdInfo(bit bPlayback)
{
    BYTE pucData[9];

    memset(pucData, 0, sizeof(pucData));

    // Disable DP TX MPEG and timestamp
    ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~(_BIT5 | _BIT0), 0x00);

    if(bPlayback == _ON)
    {
        if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
        {
            // Get MST2SST AMD SPD Info frame, only support in RL6410 & RL6432
            ScalerGetDataPortByte(PBC_55_DP_INFO_FM_ADR, 0x21, 3, &pucData[1], _AUTOINC);

            if((pucData[1] == 0x1A) && (pucData[2] == 0x00) && (pucData[3] == 0x00))
            {
                // Get MST2SST AMD SPD Info frame, only support in RL6410 & RL6432
                ScalerGetDataPortByte(PBC_55_DP_INFO_FM_ADR, 0x21, 9, pucData, _AUTOINC);

                // Set AMD SPD INFO
                ScalerSetByte(PBC_3D_SEC_INFO_MPEG_DB0, pucData[0]);
                ScalerSetByte(PBC_3E_SEC_INFO_MPEG_DB1, pucData[1]);
                ScalerSetByte(PBC_3F_SEC_INFO_MPEG_DB2, pucData[2]);
                ScalerSetByte(PBC_40_SEC_INFO_MPEG_DB3, pucData[3]);
                ScalerSetByte(PBC_41_SEC_INFO_MPEG_DB4, pucData[4]);
                ScalerSetByte(PBC_42_SEC_INFO_MPEG_DB5, pucData[5]);
                ScalerSetByte(PBC_43_SEC_INFO_MPEG_DB6, pucData[6]);
                ScalerSetByte(PBC_44_SEC_INFO_MPEG_DB7, pucData[7]);
                ScalerSetByte(PBC_45_SEC_INFO_MPEG_DB8, pucData[8]);

                // Set Header for AMD SPD Info
                ScalerDpTxSetSecDataHeader(_SEC_PACKET_TYPE_INFOFRAME_RSV);

                // DP TX MPEG and timestamp enable
                ScalerSetBit(PBC_00_SEC_FUNCTION_CTRL, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));
            }
        }
    }
}
#endif
#endif // #if(_DP_FREESYNC_SUPPORT == _ON)

#endif // #if(_DP_SUPPORT == _ON)
