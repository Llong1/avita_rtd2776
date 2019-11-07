/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerDPRxMSTInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Port Info
//--------------------------------------------------
#define _DP_OUTPUT_PORT                                                                         0
#define _DP_INPUT_PORT                                                                          1

#if(_DP_TX_SUPPORT == _ON)
#define _DP_NUM_OF_PORTS                                                                        3
#else
#define _DP_NUM_OF_PORTS                                                                        2
#endif

//--------------------------------------------------
// Definitions of Reply Type
//--------------------------------------------------
#define _DP_MSG_ACK                                                                             0
#define _DP_MSG_NACK                                                                            1

//--------------------------------------------------
// Definitions of Connection Status
//--------------------------------------------------
#define _DP_UNPLUG                                                                              0
#define _DP_PLUG                                                                                1

//--------------------------------------------------
// Definitions of Secondary Data Info
//--------------------------------------------------
#define _DP_NUM_OF_SDP_STREAMS                                                                  1
#define _DP_NUM_OF_SDP_SINKS                                                                    1

//--------------------------------------------------
// Definitions of Secondary Data Info
//--------------------------------------------------
#define _DP_TIMESLOT_SHIFT_DOWN                                                                 1
#define _DP_TIMESLOT_SHIFT_UP                                                                   0

//--------------------------------------------------
// Definitions of MSG Byte-Wise Access
//--------------------------------------------------
#define _DP_REQUEST_MSG_BYTE_WISE_MAX_LEN                                                       24
#define _DP_REPLY_MSG_BYTE_WISE_MAX_LEN                                                         132

#define _DP_TOTAL_TIME_SLOT_NUM                                                                 64

//--------------------------------------------------
// Definitions of Buffer Priority Info
//--------------------------------------------------
#define _DP_DOWN_REQUEST_BUF0                                                                   0
#define _DP_DOWN_REQUEST_BUF1                                                                   1
#define _DP_UP_REPLY_BUF0                                                                       0
#define _DP_UP_REPLY_BUF1                                                                       1

//--------------------------------------------------
// DP Down Reply Mannual Mode
//--------------------------------------------------
#define _DOWN_REPLY_MANUAL_MODE_SUPPORT                                                         _ON
#define _DOWN_REPLY_MANUAL_MODE_MAX_LEN                                                         36


#define GET_DP_MST_RX_CABLE_STATUS()                                                            ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? (PCB_D0_HOTPLUG_DETECT() == _D0_HOT_PLUG_HIGH) : (PCB_D1_HOTPLUG_DETECT() == _D1_HOT_PLUG_HIGH))

//--------------------------------------------------
// Definitions of Rx MAC MST Enable Macro
//--------------------------------------------------
#define GET_REG_DP_RX_MST_ENABLE()                                                              ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_01_PHY_DIG_RESET_CTRL : PB0_01_PHY_DIG_RESET_CTRL), _BIT7))
#define SET_REG_DP_RX_MST_ENABLE()                                                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_01_PHY_DIG_RESET_CTRL : PB0_01_PHY_DIG_RESET_CTRL), ~_BIT7, _BIT7))
#define CLR_REG_DP_RX_MST_ENABLE()                                                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_01_PHY_DIG_RESET_CTRL : PB0_01_PHY_DIG_RESET_CTRL), ~_BIT7, 0x00))

//--------------------------------------------------
// Definitions of Rx Ignore Rx Error Macro
//--------------------------------------------------
#define SET_REG_DP_IGNORE_RX_ERROR()                                                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_D1_DP_IIC_SET : PBA_D1_DP_IIC_SET), ~_BIT3, _BIT3))
#define CLR_REG_DP_IGNORE_RX_ERROR()                                                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_D1_DP_IIC_SET : PBA_D1_DP_IIC_SET), ~_BIT3, 0x00))

//--------------------------------------------------
// Definitions of MST Get DPCD Macro
//--------------------------------------------------
#if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

#define GET_REG_DP_DPCD_INFO(x, y, z)                                                           ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ScalerDpRx0GetDpcdInfo((x), (y), (z)) : ScalerDpRx1GetDpcdInfo((x), (y), (z)))
#define SET_REG_DP_DPCD_INFO(x, y, z, w)                                                        ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ScalerDpRx0SetDpcdValue((x), (y), (z), (w)) : ScalerDpRx1SetDpcdValue((x), (y), (z), (w)))
#define GET_REG_DP_DPCD_INFO_EXINT0(x, y, z)                                                    ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ScalerDpRx0GetDpcdInfo_EXINT0((x), (y), (z)) : ScalerDpRx1GetDpcdInfo_EXINT0((x), (y), (z)))
#define SET_REG_DP_DPCD_INFO_EXINT0(x, y, z, w)                                                 ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ScalerDpRx0SetDpcdValue_EXINT0((x), (y), (z), (w)) : ScalerDpRx1SetDpcdValue_EXINT0((x), (y), (z), (w)))

#define SET_DP_MST_HPD_IRQ()                                                                    ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ScalerDpRx0HotPlugDuration(1) : ScalerDpRx1HotPlugDuration(1))
#define GET_DP_POWER_STATE_INTO_PS()                                                            ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? GET_DP_RX0_POWER_STATE_INTO_PS() : GET_DP_RX1_POWER_STATE_INTO_PS())
#define GET_DP_CHECK_AUX_CH_POWER_OFF()                                                         ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? GET_DP_RX0_CHECK_AUX_CH_POWER_OFF() : GET_DP_RX1_CHECK_AUX_CH_POWER_OFF())
#define GET_DP_LT_STATUS_CHCEK()                                                                ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ScalerDpRx0LTStatusCheck() : ScalerDpRx1LTStatusCheck())
#define GET_DP_SOURCE_FIRST_POWER_ON()                                                          ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? GET_DP_RX0_SOURCE_FIRST_POWER_ON() : GET_DP_RX1_SOURCE_FIRST_POWER_ON())

#define GET_DP_MST_VBIOS_BACKUP_INFO()                                                          (g_stDpRx0MiscInfo.b1DpMstEnableBackup | g_stDpRx1MiscInfo.b1DpMstEnableBackup)

#define CLR_DP_MST_VBIOS_BACKUP_INFO()                                                          {\
                                                                                                    g_stDpRx0MiscInfo.b1DpMstEnableBackup = _FALSE;\
                                                                                                    g_stDpRx1MiscInfo.b1DpMstEnableBackup = _FALSE;\
                                                                                                }


#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Rx HDCP Macro
//--------------------------------------------------
#define GET_DP_RX_HDCP_AUTH_ENCRYPTION()                                                        ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ScalerDpRx0HdcpEnebled() : ScalerDpRx1HdcpEnebled())
#define GET_DP_RX_HDCP_AUTH_PROC_DONE()                                                         ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? (GET_DP_RX0_HDCP_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_DONE) : (GET_DP_RX1_HDCP_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_DONE))
#define GET_DP_RX_HDCP_REPEATER_SUPPORTED()                                                     ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x28) == (_BIT1 | _BIT0)) : (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x28) == (_BIT1 | _BIT0)))
#define GET_DP_RX_HDCP_POWER_STATUS_NORMAL()                                                    ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ((ScalerDpRx0GetDpcdInfo(0x00, 0x06, 0x00) & 0x07) == _BIT0) : ((ScalerDpRx1GetDpcdInfo(0x00, 0x06, 0x00) & 0x07) == _BIT0))
#define SET_DP_RX_HDCP_SHA_INPUT_RUN(x)                                                         ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? ScalerDpRx0HDCPAuthShaRun(x) : ScalerDpRx1HDCPAuthShaRun(x))
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#define GET_DP_RX_HDCP2_MODE()                                                                  ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? (GET_DP_RX0_HDCP2_MODE()) : (GET_DP_RX1_HDCP2_MODE()))
#endif

#define SET_REG_DP_RX_AUX_TO_MANUAL_MODE_EXINT()                                                {\
                                                                                                    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)\
                                                                                                    {\
                                                                                                        SET_DP_RX0_AUX_MANUAL_MODE_EXINT();\
                                                                                                    }\
                                                                                                    else\
                                                                                                    {\
                                                                                                        SET_DP_RX1_AUX_MANUAL_MODE_EXINT();\
                                                                                                    }\
                                                                                                }

#define SET_REG_DP_RX_AUX_TO_MANUAL_MODE()                                                      {\
                                                                                                    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)\
                                                                                                    {\
                                                                                                        SET_DP_RX0_AUX_MANUAL_MODE();\
                                                                                                    }\
                                                                                                    else\
                                                                                                    {\
                                                                                                        SET_DP_RX1_AUX_MANUAL_MODE();\
                                                                                                    }\
                                                                                                }

#define SET_REG_DP_RX_AUX_TO_AUTO_MODE_EXINT()                                                  {\
                                                                                                    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)\
                                                                                                    {\
                                                                                                        SET_DP_RX0_AUX_AUTO_MODE_EXINT();\
                                                                                                    }\
                                                                                                    else\
                                                                                                    {\
                                                                                                        SET_DP_RX1_AUX_AUTO_MODE_EXINT();\
                                                                                                    }\
                                                                                                }

#define SET_REG_DP_RX_AUX_TO_AUTO_MODE()                                                        {\
                                                                                                    if(g_enumDpMSTCapablePort == _DP_MST_RX0_PORT)\
                                                                                                    {\
                                                                                                        SET_DP_RX0_AUX_AUTO_MODE();\
                                                                                                    }\
                                                                                                    else\
                                                                                                    {\
                                                                                                        SET_DP_RX1_AUX_AUTO_MODE();\
                                                                                                    }\
                                                                                                }

#elif(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

#define GET_REG_DP_DPCD_INFO(x, y, z)                                                           (ScalerDpRx0GetDpcdInfo((x), (y), (z)))
#define SET_REG_DP_DPCD_INFO(x, y, z, w)                                                        (ScalerDpRx0SetDpcdValue((x), (y), (z), (w)))
#define GET_REG_DP_DPCD_INFO_EXINT0(x, y, z)                                                    (ScalerDpRx0GetDpcdInfo_EXINT0((x), (y), (z)))
#define SET_REG_DP_DPCD_INFO_EXINT0(x, y, z, w)                                                 (ScalerDpRx0SetDpcdValue_EXINT0((x), (y), (z), (w)))

#define SET_DP_MST_HPD_IRQ()                                                                    (ScalerDpRx0HotPlugDuration(1))
#define GET_DP_POWER_STATE_INTO_PS()                                                            (GET_DP_RX0_POWER_STATE_INTO_PS())
#define GET_DP_CHECK_AUX_CH_POWER_OFF()                                                         (GET_DP_RX0_CHECK_AUX_CH_POWER_OFF())
#define GET_DP_LT_STATUS_CHCEK()                                                                (ScalerDpRx0LTStatusCheck())
#define GET_DP_SOURCE_FIRST_POWER_ON()                                                          (GET_DP_RX0_SOURCE_FIRST_POWER_ON())

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
#define GET_DP_MST_VBIOS_BACKUP_INFO()                                                          (g_stDpRx0MiscInfo.b1DpMstEnableBackup | g_stDpRx0MiscInfo.b1DpRx6MstEnableBackup)

#define CLR_DP_MST_VBIOS_BACKUP_INFO()                                                          {\
                                                                                                    g_stDpRx0MiscInfo.b1DpMstEnableBackup = _FALSE;\
                                                                                                    g_stDpRx0MiscInfo.b1DpRx6MstEnableBackup = _FALSE;\
                                                                                                }
#else
#define GET_DP_MST_VBIOS_BACKUP_INFO()                                                          (g_stDpRx0MiscInfo.b1DpMstEnableBackup)

#define CLR_DP_MST_VBIOS_BACKUP_INFO()                                                          {\
                                                                                                    g_stDpRx0MiscInfo.b1DpMstEnableBackup = _FALSE;\
                                                                                                }
#endif


#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_RX_HDCP_AUTH_ENCRYPTION()                                                        (ScalerDpRx0HdcpEnebled())
#define GET_DP_RX_HDCP_AUTH_PROC_DONE()                                                         (GET_DP_RX0_HDCP_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_DONE)
#define GET_DP_RX_HDCP_REPEATER_SUPPORTED()                                                     (ScalerDpRx0GetDpcdInfo(0x06, 0x80, 0x28) == (_BIT1 | _BIT0))
#define GET_DP_RX_HDCP_POWER_STATUS_NORMAL()                                                    ((ScalerDpRx0GetDpcdInfo(0x00, 0x06, 0x00) & 0x07) == _BIT0)
#define SET_DP_RX_HDCP_SHA_INPUT_RUN(x)                                                         (ScalerDpRx0HDCPAuthShaRun(x))
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#define GET_DP_RX_HDCP2_MODE()                                                                  (GET_DP_RX0_HDCP2_MODE())
#endif

#define SET_REG_DP_RX_AUX_TO_MANUAL_MODE_EXINT()                                                {SET_DP_RX0_AUX_MANUAL_MODE_EXINT()}
#define SET_REG_DP_RX_AUX_TO_MANUAL_MODE()                                                      {SET_DP_RX0_AUX_MANUAL_MODE()}
#define SET_REG_DP_RX_AUX_TO_AUTO_MODE_EXINT()                                                  {SET_DP_RX0_AUX_AUTO_MODE_EXINT()}
#define SET_REG_DP_RX_AUX_TO_AUTO_MODE()                                                        {SET_DP_RX0_AUX_AUTO_MODE()}

#elif(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

#define GET_REG_DP_DPCD_INFO(x, y, z)                                                           (ScalerDpRx1GetDpcdInfo((x), (y), (z)))
#define SET_REG_DP_DPCD_INFO(x, y, z, w)                                                        (ScalerDpRx1SetDpcdValue((x), (y), (z), (w)))
#define GET_REG_DP_DPCD_INFO_EXINT0(x, y, z)                                                    (ScalerDpRx1GetDpcdInfo_EXINT0((x), (y), (z)))
#define SET_REG_DP_DPCD_INFO_EXINT0(x, y, z, w)                                                 (ScalerDpRx1SetDpcdValue_EXINT0((x), (y), (z), (w)))

#define SET_DP_MST_HPD_IRQ()                                                                    (ScalerDpRx1HotPlugDuration(1))
#define GET_DP_POWER_STATE_INTO_PS()                                                            (GET_DP_RX1_POWER_STATE_INTO_PS())
#define GET_DP_CHECK_AUX_CH_POWER_OFF()                                                         (GET_DP_RX1_CHECK_AUX_CH_POWER_OFF())
#define GET_DP_LT_STATUS_CHCEK()                                                                (ScalerDpRx1LTStatusCheck())
#define GET_DP_SOURCE_FIRST_POWER_ON()                                                          (GET_DP_RX1_SOURCE_FIRST_POWER_ON())

#define GET_DP_MST_VBIOS_BACKUP_INFO()                                                          (g_stDpRx1MiscInfo.b1DpMstEnableBackup)

#define CLR_DP_MST_VBIOS_BACKUP_INFO()                                                          {\
                                                                                                    g_stDpRx1MiscInfo.b1DpMstEnableBackup = _FALSE;\
                                                                                                }


#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_RX_HDCP_AUTH_ENCRYPTION()                                                        (ScalerDpRx1HdcpEnebled())
#define GET_DP_RX_HDCP_AUTH_PROC_DONE()                                                         (GET_DP_RX1_HDCP_AUTH_STATE() == _DP_RX_HDCP_STATE_AUTH_DONE)
#define GET_DP_RX_HDCP_REPEATER_SUPPORTED()                                                     (ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x28) == (_BIT1 | _BIT0))
#define GET_DP_RX_HDCP_POWER_STATUS_NORMAL()                                                    ((ScalerDpRx1GetDpcdInfo(0x00, 0x06, 0x00) & 0x07) == _BIT0)
#define SET_DP_RX_HDCP_SHA_INPUT_RUN(x)                                                         (ScalerDpRx1HDCPAuthShaRun(x))
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#define GET_DP_RX_HDCP2_MODE()                                                                  (GET_DP_RX1_HDCP2_MODE())
#endif

#define SET_REG_DP_RX_AUX_TO_MANUAL_MODE_EXINT()                                                {SET_DP_RX1_AUX_MANUAL_MODE_EXINT()}
#define SET_REG_DP_RX_AUX_TO_MANUAL_MODE()                                                      {SET_DP_RX1_AUX_MANUAL_MODE()}
#define SET_REG_DP_RX_AUX_TO_AUTO_MODE_EXINT()                                                  {SET_DP_RX1_AUX_AUTO_MODE_EXINT()}
#define SET_REG_DP_RX_AUX_TO_AUTO_MODE()                                                        {SET_DP_RX1_AUX_AUTO_MODE()}

#endif // End of #if((_D0_INPUT_PORT_TYPE == _D0_DP_PORT) && (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

#define GET_DP_RX_HDCP_AN(x)                                                                    (GET_REG_DP_DPCD_INFO(0x06, 0x80, (0x0C + (x))))
#define GET_DP_RX_HDCP_V(x)                                                                     (GET_REG_DP_DPCD_INFO(0x06, 0x80, (0x14 + (x))))

//--------------------------------------------------
// Definitions of MST Stream Related Macro
//--------------------------------------------------
#define GET_DP_RX_MST_STREAM_TIME_SLOT(x)                                                       ((ScalerGetByte((((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_04_STHD_CTRL_3 : PB8_04_STHD_CTRL_3) + ((x) << 1)))) -\
                                                                                                 (ScalerGetByte((((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_03_STHD_CTRL_2 : PB8_03_STHD_CTRL_2) + ((x) << 1)))) + 1)

#define GET_DP_RX_MST_ST_START_POSITION(x)                                                      (ScalerGetBit((((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_03_STHD_CTRL_2 : PB8_03_STHD_CTRL_2) + ((x) << 1)), 0x3F))
#define SET_DP_RX_MST_ST_START_POSITION(x, y)                                                   (ScalerSetByte((((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_03_STHD_CTRL_2 : PB8_03_STHD_CTRL_2) + (((x) << 1))), (y)))
#define SET_DP_RX_MST_ST_END_POSITION(x, y)                                                     (ScalerSetByte((((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_04_STHD_CTRL_3 : PB8_04_STHD_CTRL_3) + (((x) << 1))), (y)))


#define GET_REG_DP_RX_MST_ST1_SOURCE_STATUS()                                                   (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0D_SOURCE_SEL_0 : PB8_0D_SOURCE_SEL_0), (_BIT6 | _BIT5 | _BIT4)) >> 4)
#define SET_REG_DP_RX_MST_ST1_SOURCE_STATUS(x)                                                  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0D_SOURCE_SEL_0 : PB8_0D_SOURCE_SEL_0), ~(_BIT6 | _BIT5 | _BIT4), (x)))
#define GET_REG_DP_RX_MST_ST2_SOURCE_STATUS()                                                   (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0D_SOURCE_SEL_0 : PB8_0D_SOURCE_SEL_0), (_BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_MST_ST2_SOURCE_STATUS(x)                                                  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0D_SOURCE_SEL_0 : PB8_0D_SOURCE_SEL_0), ~(_BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_MST_ST3_SOURCE_STATUS()                                                   (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0E_SOURCE_SEL_1 : PB8_0E_SOURCE_SEL_1), (_BIT6 | _BIT5 | _BIT4)) >> 4)
#define SET_REG_DP_RX_MST_ST3_SOURCE_STATUS(x)                                                  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0E_SOURCE_SEL_1 : PB8_0E_SOURCE_SEL_1), ~(_BIT6 | _BIT5 | _BIT4), (x)))
#define GET_REG_DP_RX_MST_ST4_SOURCE_STATUS()                                                   (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0E_SOURCE_SEL_1 : PB8_0E_SOURCE_SEL_1), (_BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_MST_ST4_SOURCE_STATUS(x)                                                  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0E_SOURCE_SEL_1 : PB8_0E_SOURCE_SEL_1), ~(_BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_MST_ST5_SOURCE_STATUS()                                                   (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0F_SOURCE_SEL_2 : PB8_0F_SOURCE_SEL_2), (_BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_MST_ST5_SOURCE_STATUS(x)                                                  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_0F_SOURCE_SEL_2 : PB8_0F_SOURCE_SEL_2), ~(_BIT2 | _BIT1 | _BIT0), (x)))

#define GET_REG_DP_RX_HDCP_M0(x)                                                                (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_2F_M0_BYTE_0 : PB0_2F_M0_BYTE_0) - (x)))
#define GET_REG_DP_RX_HDCP_SHA_RESULT(x)                                                        (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_36_SHA_0 : PB0_36_SHA_0) + (x)))

#define SET_REG_DP_RX_SHA_ENABLE()                                                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_30_SHA_CONTRL : PB0_30_SHA_CONTRL), ~_BIT3, 0x00))
#define CLR_REG_DP_RX_SHA_ENABLE()                                                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_30_SHA_CONTRL : PB0_30_SHA_CONTRL), ~_BIT3, _BIT3))

#define SET_REG_DP_RX_SHA_INPUT_0(x)                                                            (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_31_SHA_DATA1 : PB0_31_SHA_DATA1), (x)))
#define SET_REG_DP_RX_SHA_INPUT_1(x)                                                            (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_32_SHA_DATA2 : PB0_32_SHA_DATA2), (x)))
#define SET_REG_DP_RX_SHA_INPUT_2(x)                                                            (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_33_SHA_DATA3 : PB0_33_SHA_DATA3), (x)))
#define SET_REG_DP_RX_SHA_INPUT_3(x)                                                            (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_34_SHA_DATA4 : PB0_34_SHA_DATA4), (x)))
#define SET_REG_DP_RX_SHA_INPUT_DB()                                                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB_30_SHA_CONTRL : PB0_30_SHA_CONTRL), ~_BIT0, _BIT0))

//--------------------------------------------------
// Definitions of AUX Mac Related Register Macro
//--------------------------------------------------

#define SET_REG_DP_RX_CLEAR_PAYLOAD_ID_TABLE()                                                  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B0_AUX_PAYLOAD_CLEAR : PBA_B0_AUX_PAYLOAD_CLEAR), ~_BIT6, _BIT6))
#define CLR_REG_DP_RX_CLEAR_PAYLOAD_ID_TABLE()                                                  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B0_AUX_PAYLOAD_CLEAR : PBA_B0_AUX_PAYLOAD_CLEAR), ~_BIT6, 0x00))
#define GET_REG_DP_RX_111_IRQ()                                                                 ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B2_AUX_SPECIAL_IRQ_EN : PBA_B2_AUX_SPECIAL_IRQ_EN), _BIT7))
#define SET_REG_DP_RX_111_IRQ()                                                                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B2_AUX_SPECIAL_IRQ_EN : PBA_B2_AUX_SPECIAL_IRQ_EN), ~_BIT7, _BIT7))
#define CLR_REG_DP_RX_111_IRQ()                                                                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B2_AUX_SPECIAL_IRQ_EN : PBA_B2_AUX_SPECIAL_IRQ_EN), ~_BIT7, 0x00))
#define GET_REG_DP_RX_111_IRQ_FLAG()                                                            ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B3_AUX_SPECIAL_IRQ_FLAG : PBA_B3_AUX_SPECIAL_IRQ_FLAG), _BIT7))
#define CLR_REG_DP_RX_111_IRQ_FLAG()                                                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B3_AUX_SPECIAL_IRQ_FLAG : PBA_B3_AUX_SPECIAL_IRQ_FLAG), ~(_BIT7 | _BIT4 | _BIT3), _BIT7))
#define GET_REG_DP_RX_1C2_IRQ()                                                                 ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B2_AUX_SPECIAL_IRQ_EN : PBA_B2_AUX_SPECIAL_IRQ_EN), _BIT4))
#define SET_REG_DP_RX_1C2_IRQ()                                                                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B2_AUX_SPECIAL_IRQ_EN : PBA_B2_AUX_SPECIAL_IRQ_EN), ~_BIT4, _BIT4))
#define GET_REG_DP_RX_1C2_IRQ_FLAG()                                                            (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B3_AUX_SPECIAL_IRQ_FLAG : PBA_B3_AUX_SPECIAL_IRQ_FLAG), _BIT4) >> 4)
#define CLR_REG_DP_RX_1C2_IRQ_FLAG()                                                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B3_AUX_SPECIAL_IRQ_FLAG : PBA_B3_AUX_SPECIAL_IRQ_FLAG), ~(_BIT7 | _BIT4 | _BIT3), _BIT4))
#define GET_REG_DP_RX_2C0_IRQ()                                                                 ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B2_AUX_SPECIAL_IRQ_EN : PBA_B2_AUX_SPECIAL_IRQ_EN), _BIT3))
#define SET_REG_DP_RX_2C0_IRQ()                                                                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B2_AUX_SPECIAL_IRQ_EN : PBA_B2_AUX_SPECIAL_IRQ_EN), ~_BIT3, _BIT3))
#define CLR_REG_DP_RX_2C0_IRQ()                                                                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B2_AUX_SPECIAL_IRQ_EN : PBA_B2_AUX_SPECIAL_IRQ_EN), ~_BIT3, 0x00))
#define GET_REG_DP_RX_2C0_IRQ_FLAG()                                                            (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B3_AUX_SPECIAL_IRQ_FLAG : PBA_B3_AUX_SPECIAL_IRQ_FLAG), _BIT3) >> 3)
#define CLR_REG_DP_RX_2C0_IRQ_FLAG()                                                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_B3_AUX_SPECIAL_IRQ_FLAG : PBA_B3_AUX_SPECIAL_IRQ_FLAG), ~(_BIT7 | _BIT4 | _BIT3), _BIT3))
#define SET_REG_DP_RX_REPLY_RAD_MSB(x, y)                                                       (ScalerSetBit((x), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (y)))
#define SET_REG_DP_RX_REPLY_RAD_LSB(x, y)                                                       (ScalerSetBit((x), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (y)))
#define GET_REG_DP_RX_BYPASS_RAD_MSB(x)                                                         ((ScalerGetBit((x), (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4))
#define GET_REG_DP_RX_BYPASS_RAD_LSB(x)                                                         (ScalerGetBit((x), (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4)

//--------------------------------------------------
// Definitions of MST Mode Status Macro
//--------------------------------------------------
#define GET_DP_RX_MST_MODE_STATE()                                                              (g_enumDpMSTModeStatus)
#define SET_DP_RX_MST_MODE_STATE(x)                                                             (g_enumDpMSTModeStatus = (x))

//--------------------------------------------------
// Definitions of Request Memory Pool Macro
//--------------------------------------------------
#define GET_DP_MSG_REQUEST_ARRAY(x)                                                             (g_unDpRequestPool.pucData[x])
#define SET_DP_MSG_REQUEST_ARRAY(x, y)                                                          (g_unDpRequestPool.pucData[x] = (y))

//--------------------------------------------------
// Definitions of Reply Memory Pool Macro
//--------------------------------------------------
#define GET_DP_MSG_REPLY_ARRAY(x)                                                               (g_unDpReplyPool.pucData[x])
#define SET_DP_MSG_REPLY_ARRAY(x, y)                                                            (g_unDpReplyPool.pucData[x] = (y))

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Definitions of Total Receipt Msg Count Macro
//--------------------------------------------------
#define GET_DP_TOTAL_RECEIVED_MSG_COUNT()                                                       (g_ucTotalReceivedMsgCount)
#define SET_DP_TOTAL_RECEIVED_MSG_COUNT(x)                                                      (g_ucTotalReceivedMsgCount = (x))

//--------------------------------------------------
// Definitions of Total Receipt Msg Count Macro
//--------------------------------------------------
#define GET_DP_RX_SELF_GEN_UP_REQUEST_RETRY()                                                   (g_ucSelfGenUpRequestRetry)
#define SET_DP_RX_SELF_GEN_UP_REQUEST_RETRY(x)                                                  (g_ucSelfGenUpRequestRetry = (x))
#define CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY()                                                   (g_ucSelfGenUpRequestRetry = _DP_MSG_NONE)
#endif

//--------------------------------------------------
// Definitions of Down Request Allocate Payload MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()                                   (g_unDpRequestPool.stAllocatePayload.b7PayloadID)
#define GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN()                                          (g_unDpRequestPool.stAllocatePayload.usPBN)
#define GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM()                                     (g_unDpRequestPool.stAllocatePayload.b4PortNum)
#define GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_SDP_NUM()                                      (g_unDpRequestPool.stAllocatePayload.b4NumOfSDPStreams)

//--------------------------------------------------
// Definitions of Down Reply Allocate Payload MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REPLY_TYPE(x)                                    (g_unDpReplyPool.stAllocatePayload.b1RepType = (x))
#define SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REQUEST_ID(x)                                    (g_unDpReplyPool.stAllocatePayload.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PORT_NUM(x)                                      (g_unDpReplyPool.stAllocatePayload.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(x)                                    (g_unDpReplyPool.stAllocatePayload.b7PayloadID = (x))
#define GET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()                                     (g_unDpReplyPool.stAllocatePayload.b7PayloadID)
#define SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(x)                                           (g_unDpReplyPool.stAllocatePayload.usAllocatePBN = (x))
#define GET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN()                                            (g_unDpReplyPool.stAllocatePayload.usAllocatePBN)
#define SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_ZEROS()                                          {\
                                                                                                    g_unDpReplyPool.stAllocatePayload.b1Zero1 = 0;\
                                                                                                    g_unDpReplyPool.stAllocatePayload.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Query Payload MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM()                                        (g_unDpRequestPool.stQueryPayload.b4PortNum)
#define GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID()                                      (g_unDpRequestPool.stQueryPayload.b7PayloadID)

//--------------------------------------------------
// Definitions of Down Reply Query Payload MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_REPLY_TYPE(x)                                       (g_unDpReplyPool.stQueryPayload.b1RepType = (x))
#define SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_REQUEST_ID(x)                                       (g_unDpReplyPool.stQueryPayload.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_PORT_NUM(x)                                         (g_unDpReplyPool.stQueryPayload.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(x)                                    (g_unDpReplyPool.stQueryPayload.usAllocatePBN = (x))
#define SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_ZEROS()                                             {\
                                                                                                    g_unDpReplyPool.stQueryPayload.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Power Up MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_POWER_UP_MSG_PORT_NUM()                                             (g_unDpRequestPool.stPowerUpPHY.b4PortNum)

//--------------------------------------------------
// Definitions of Down Reply Power Up MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_POWER_UP_MSG_REPLY_TYPE(x)                                            (g_unDpReplyPool.stPowerUpPHY.b1RepType = (x))
#define SET_DP_DOWN_REPLY_POWER_UP_MSG_REQUEST_ID(x)                                            (g_unDpReplyPool.stPowerUpPHY.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_POWER_UP_MSG_PORT_NUM(x)                                              (g_unDpReplyPool.stPowerUpPHY.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_POWER_UP_MSG_ZEROS()                                                  {\
                                                                                                    g_unDpReplyPool.stPowerUpPHY.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Power Down MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_POWER_DOWN_MSG_PORT_NUM()                                           (g_unDpRequestPool.stPowerDownPHY.b4PortNum)

//--------------------------------------------------
// Definitions of Down Reply Power Down MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_POWER_DOWN_MSG_REPLY_TYPE(x)                                          (g_unDpReplyPool.stPowerDownPHY.b1RepType = (x))
#define SET_DP_DOWN_REPLY_POWER_DOWN_MSG_REQ_ID(x)                                              (g_unDpReplyPool.stPowerDownPHY.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_POWER_DOWN_MSG_PORT_NUM(x)                                            (g_unDpReplyPool.stPowerDownPHY.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_POWER_DOWN_MSG_ZEROS()                                                {\
                                                                                                    g_unDpReplyPool.stPowerDownPHY.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Remote DPCD Read MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_PORT_NUM()                                     (g_unDpRequestPool.stRemoteDpcdRead.b4PortNum)
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ()                                  (g_unDpRequestPool.stRemoteDpcdRead.ucNumOfRead)
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H()                                    (g_unDpRequestPool.stRemoteDpcdRead.b4DpcdAddressH)
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M()                                    (g_unDpRequestPool.stRemoteDpcdRead.ucDpcdAddressM)
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L()                                    (g_unDpRequestPool.stRemoteDpcdRead.ucDpcdAddressL)


//--------------------------------------------------
// Definitions of Down Reply Remote DPCD Read MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REPLY_TYPE(x)                                    (g_unDpReplyPool.stRemoteDpcdRead.b1RepType = (x))
#define SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REQUEST_ID(x)                                    (g_unDpReplyPool.stRemoteDpcdRead.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_PORT_NUM(x)                                      (g_unDpReplyPool.stRemoteDpcdRead.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_NUM_OF_READ(x)                                   (g_unDpReplyPool.stRemoteDpcdRead.ucNumOfRead = (x))
#define SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(x)                                          (g_unDpReplyPool.stRemoteDpcdRead.pucDpcdRead[x])
#define SET_DP_DOWN_REPLY_MSG_REMOTE_DPCD_READ_MSG_ZEROS()                                      {\
                                                                                                    g_unDpReplyPool.stRemoteDpcdRead.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Remote DPCD Write MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM()                                    (g_unDpRequestPool.stRemoteDpcdWrite.b4PortNum)
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_H()                                   (g_unDpRequestPool.stRemoteDpcdWrite.b4DpcdAddressH)
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M()                                   (g_unDpRequestPool.stRemoteDpcdWrite.ucDpcdAddressM)
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_L()                                   (g_unDpRequestPool.stRemoteDpcdWrite.ucDpcdAddressL)
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_DATA(x)                                       (g_unDpRequestPool.stRemoteDpcdWrite.pucDpcdByteToWrite[x])
#define GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_NUM_OF_WRITE()                                (g_unDpRequestPool.stRemoteDpcdWrite.ucNumOfByteToWrite)

//--------------------------------------------------
// Definitions of Down Reply Remote DPCD Write MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REPLY_TYPE(x)                                   (g_unDpReplyPool.stRemoteDpcdWrite.b1RepType = (x))
#define SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REQUEST_ID(x)                                   (g_unDpReplyPool.stRemoteDpcdWrite.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_PORT_NUM(x)                                     (g_unDpReplyPool.stRemoteDpcdWrite.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_REMOTE_DPCE_WRITE_MSG_ZEROS()                                         {\
                                                                                                    g_unDpReplyPool.stRemoteDpcdWrite.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Reply Link Address MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_REPLY_TYPE(x)                                           (g_unDpReplyPool.stLinkAddress.b1RepType = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_REQUEST_ID(x)                                           (g_unDpReplyPool.stLinkAddress.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_GUID(x, y)                                              (g_unDpReplyPool.stLinkAddress.pucGuid[x] = (y))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_NUM_OF_PORT(x)                                          (g_unDpReplyPool.stLinkAddress.b4NumOfPort = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_TYPE(x)                                           (g_unDpReplyPool.stLinkAddress.b1InputPort0 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_TYPE(x)                                           (g_unDpReplyPool.stLinkAddress.b1InputPort1 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_PORT1_TYPE(x)                                               (g_unDpReplyPool.stLinkAddress.b1InputPort2 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_NUM(x)                                            (g_unDpReplyPool.stLinkAddress.b4Port0Num = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_NUM(x)                                            (g_unDpReplyPool.stLinkAddress.b4Port1Num = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM(x)                                            (g_unDpReplyPool.stLinkAddress.b4Port2Num = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_PEER_DEVICE_TYPE(x)                               (g_unDpReplyPool.stLinkAddress.b3PeerDeviceType0 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_PEER_DEVICE_TYPE(x)                               (g_unDpReplyPool.stLinkAddress.b3PeerDeviceType1 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_PEER_DEVICE_TYPE(x)                               (g_unDpReplyPool.stLinkAddress.b3PeerDeviceType2 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_MSG_CAP(x)                                        (g_unDpReplyPool.stLinkAddress.b1MsgCapability0 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_MSG_CAP(x)                                        (g_unDpReplyPool.stLinkAddress.b1MsgCapability1 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_MSG_CAP(x)                                        (g_unDpReplyPool.stLinkAddress.b1MsgCapability2 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT0_DP_PLUG_STATUS(x)                                 (g_unDpReplyPool.stLinkAddress.b1DpPlugStatus0 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_DP_PLUG_STATUS(x)                                 (g_unDpReplyPool.stLinkAddress.b1DpPlugStatus1 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_DP_PLUG_STATUS(x)                                 (g_unDpReplyPool.stLinkAddress.b1DpPlugStatus2 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_LEGACY_PLUG_STATUS(x)                             (g_unDpReplyPool.stLinkAddress.b1LegacyPlugStatus1 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_LEGACY_PLUG_STATUS(x)                             (g_unDpReplyPool.stLinkAddress.b1LegacyPlugStatus2 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_DPCD_REV(x)                                       (g_unDpReplyPool.stLinkAddress.ucDpcdRevision1 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_DPCD_REV(x)                                       (g_unDpReplyPool.stLinkAddress.ucDpcdRevision2 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_GUID(x, y)                                        (g_unDpReplyPool.stLinkAddress.pucPeer1Guid[x] = (y))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_GUID(x, y)                                        (g_unDpReplyPool.stLinkAddress.pucPeer2Guid[x] = (y))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_NUM_OF_SDP(x)                                     (g_unDpReplyPool.stLinkAddress.b4NumSDPStreams1 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT8_NUM_OF_SDP_SINK(x)                                (g_unDpReplyPool.stLinkAddress.b4NumSDPStreamSink1 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM_OF_SDP(x)                                     (g_unDpReplyPool.stLinkAddress.b4NumSDPStreams2 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_PORT1_NUM_OF_SDP_SINK(x)                                (g_unDpReplyPool.stLinkAddress.b4NumSDPStreamSink2 = (x))
#define SET_DP_DOWN_REPLY_LINK_ADDR_MSG_ZEROS()                                                 {\
                                                                                                    g_unDpReplyPool.stLinkAddress.b5Zero2 = 0;\
                                                                                                    g_unDpReplyPool.stLinkAddress.b4Port0Num = 0;\
                                                                                                    g_unDpReplyPool.stLinkAddress.b4Port1Num = 0;\
                                                                                                    g_unDpReplyPool.stLinkAddress.b4Port2Num = 0;\
                                                                                                    g_unDpReplyPool.stLinkAddress.b4Zero = 0;\
                                                                                                    g_unDpReplyPool.stLinkAddress.b5Zero3 = 0;\
                                                                                                    g_unDpReplyPool.stLinkAddress.b6Zero1 = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Enum Payload MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM()                                            (g_unDpRequestPool.stEnumPathResource.b4PortNum)


//--------------------------------------------------
// Definitions of Enum Payload MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_ENUM_PATH_MSG_REPLY_TYPE(x)                                           (g_unDpReplyPool.stEnumPathResource.b1RepType = (x))
#define SET_DP_DOWN_REPLY_ENUM_PATH_MSG_REQUEST_ID(x)                                           (g_unDpReplyPool.stEnumPathResource.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_ENUM_PATH_MSG_PORT_NUM(x)                                             (g_unDpReplyPool.stEnumPathResource.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN(x)                                             (g_unDpReplyPool.stEnumPathResource.usFullPBN = (x))
#define GET_DP_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN()                                              (g_unDpReplyPool.stEnumPathResource.usFullPBN)
#define SET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(x)                                        (g_unDpReplyPool.stEnumPathResource.usAvailablePBN = (x))
#define GET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN()                                         (g_unDpReplyPool.stEnumPathResource.usAvailablePBN)
#define SET_DP_DOWN_REPLY_ENUM_PATH_MSG_ZEROS()                                                 {\
                                                                                                    g_unDpReplyPool.stEnumPathResource.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Clear ID Table MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REQUEST_CLEAR_ID_TABLE_MSG_REQUEST_ID(x)                                    (g_unDpRequestPool.stClearPayloadID.b7ReqID = (x))


//--------------------------------------------------
// Definitions of Clear ID Table MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REPLY_TYPE(x)                                      (g_unDpReplyPool.stClearPayloadID.b1RepType = (x))
#define SET_DP_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REQUEST_ID(x)                                      (g_unDpReplyPool.stClearPayloadID.b7ReqID = (x))

//--------------------------------------------------
// Definitions of Down Request Remote I2C Read MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM()                                      (g_unDpRequestPool.stRemoteI2CRead.b4PortNum)
#define GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE()                                  (g_unDpRequestPool.stRemoteI2CRead.b2NumOfI2CWriteTran)

//--------------------------------------------------
// Definitions of Down Reply Remote I2C Read MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_REPLY_TYPE(x)                                     (g_unDpReplyPool.stRemoteI2CRead.b1RepType = (x))
#define SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_REQUEST_ID(x)                                     (g_unDpReplyPool.stRemoteI2CRead.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_PORT_NUM(x)                                       (g_unDpReplyPool.stRemoteI2CRead.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(x)                                    (g_unDpReplyPool.stRemoteI2CRead.ucNumOfRead = (x))
#define SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_ZEROS()                                           {\
                                                                                                    g_unDpReplyPool.stRemoteI2CRead.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Remote I2C Write MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM()                                     (g_unDpRequestPool.stRemoteI2CWrite.b4PortNum)
#define GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_WRITE_DEVICE_ID()                              (g_unDpRequestPool.stRemoteI2CWrite.b7WriteI2CDeviceID)
#define GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE()                                 (g_unDpRequestPool.stRemoteI2CWrite.ucNumOfByteToWrite)
#define GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(x)                               (g_unDpRequestPool.stRemoteI2CWrite.pucI2CDateToWrite[x])

//--------------------------------------------------
// Definitions of Down Request Remote I2C Reply MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REPLY_TYPE(x)                                    (g_unDpReplyPool.stRemoteI2CWrite.b1RepType = (x))
#define SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REQUEST_ID(x)                                    (g_unDpReplyPool.stRemoteI2CWrite.b7ReqID = (x))
#define SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_PORT_NUM(x)                                      (g_unDpReplyPool.stRemoteI2CWrite.b4PortNum = (x))
#define SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_ZEROS()                                          {\
                                                                                                    g_unDpReplyPool.stRemoteI2CWrite.b4Zero = 0;\
                                                                                                }

//--------------------------------------------------
// Definitions of Down Request Query Stream Encryption Status MSG Macro
//--------------------------------------------------
#define GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REQUEST_ID()                     (g_unDpRequestPool.stStructReqQueryStreamEncryptionStatus.b7ReqID)
#define SET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID(x)                     (g_unDpRequestPool.stStructReqQueryStreamEncryptionStatus.ucStreamID = (x))
#define GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID()                      (g_unDpRequestPool.stStructReqQueryStreamEncryptionStatus.ucStreamID)
#define GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_CLIENT_ID(x)                     (g_unDpRequestPool.stStructReqQueryStreamEncryptionStatus.pucClientID[x])
#define GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_EVENT()                   (g_unDpRequestPool.stStructReqQueryStreamEncryptionStatus.b2StreamEvent)
#define GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_EVENT_MASK()              (g_unDpRequestPool.stStructReqQueryStreamEncryptionStatus.b1StreamEventMask)
#define GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_BEHAVIOR()                (g_unDpRequestPool.stStructReqQueryStreamEncryptionStatus.b2StreamBehavior)
#define GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_BEHAVIOR_MASK()           (g_unDpRequestPool.stStructReqQueryStreamEncryptionStatus.b1StreamBehaviorMask)

//--------------------------------------------------
// Definitions of Down Reply Query Stream Encryption Status MSG Macro
//--------------------------------------------------
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REPLY_TYPE(x)                      (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1RepType = (x))
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REQUEST_ID(x)                      (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b7ReqID = (x))
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE()                     (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b2StreamState)
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE(x)                    (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b2StreamState = (x))
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(x)         (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamRepeaterFunction = (x))
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT()          (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamRepeaterFunction)
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION()                (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamEncryption)
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION(x)               (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamEncryption = (x))
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN()                    (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamAuthentication)
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(x)                   (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1StreamAuthentication = (x))
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE()          (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b3StreamOuputSinkType)
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE(x)         (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b3StreamOuputSinkType = (x))
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE()            (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b2StreamOuputCpType)
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(x)           (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b2StreamOuputCpType = (x))
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED()                           (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1Signed)
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(x)                          (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b1Signed = (x))
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID()                        (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.ucStreamID)
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID(x)                       (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.ucStreamID = (x))
#define GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(x)              (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.pucSignatureL[x])
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(x, y)           (g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.pucSignatureL[x] = (y))
#define SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_ZEROS()                            {\
                                                                                                    g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b3Zero = 0;\
                                                                                                    g_unDpReplyPool.stStructRepQueryStreamEncryptionStatus.b2Zero = 0;\
                                                                                                }
//--------------------------------------------------
// Definitions of Connection Status Notify Message Macro
//--------------------------------------------------
#define GET_DP_UP_REQUEST_CONNECTION_STATUS_NOTIFY_DP_PLUG_STATUS()                             (g_unDpRequestPool.stConnectionStatusNotify.b1DpPlugStatus)

//--------------------------------------------------
// Definitions of Connection Status Notify Message Macro
//--------------------------------------------------
#define SET_DP_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REPLY_TYPE(x)                                 (g_unDpReplyPool.stConnectionStatusNotify.b1RepType = (x))
#define SET_DP_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REQUEST_ID(x)                                 (g_unDpReplyPool.stConnectionStatusNotify.b7ReqID = (x))

//--------------------------------------------------
// Definitions of Resource Status Notify Message Macro
//--------------------------------------------------
#define SET_DP_REPLY_MSG_RESOURCE_STATUS_NOTIFY_REPLY_TYPE(x)                                   (g_unDpReplyPool.stResourceStatusNotify.b1RepType = (x))
#define SET_DP_REPLY_MSG_RESOURCE_STATUS_NOTIFY_REQUEST_ID(x)                                   (g_unDpReplyPool.stResourceStatusNotify.b7ReqID = (x))

//--------------------------------------------------
// Definitions of Illegal MSG Reply Macro
//--------------------------------------------------
#define SET_DP_REPLY_ILLEGAL_MSG_REPLY_TYPE(x)                                                  (g_unDpReplyPool.stStructRepNak.b1RepType = (x))
#define SET_DP_REPLY_ILLEGAL_MSG_REQUESET_ID(x)                                                 (g_unDpReplyPool.stStructRepNak.b7ReqID = (x))
#define SET_DP_REPLY_ILLEGAL_MSG_GUID(x, y)                                                     (g_unDpReplyPool.stStructRepNak.pucGuid[x] = (y))
#define SET_DP_REPLY_ILLEGAL_MSG_NACK_REASON(x)                                                 (g_unDpReplyPool.stStructRepNak.ucNakReason = (x))
#define SET_DP_REPLY_ILLEGAL_MSG_NACK_DATA(x)                                                   (g_unDpReplyPool.stStructRepNak.ucNakData = (x))

//--------------------------------------------------
// Macro of Message Common Array Usage info
//--------------------------------------------------
#define GET_DP_REQUEST_POOL_FREE()                                                              (g_stPoolUsage.b1ReqArray)
#define SET_DP_REQUEST_POOL_FREE()                                                              (g_stPoolUsage.b1ReqArray = _TRUE)
#define CLR_DP_REQUEST_POOL_FREE()                                                              (g_stPoolUsage.b1ReqArray = _FALSE)
#define GET_DP_REPLY_POOL_FREE()                                                                (g_stPoolUsage.b1ReplyArray)
#define SET_DP_REPLY_POOL_FREE()                                                                (g_stPoolUsage.b1ReplyArray = _TRUE)
#define CLR_DP_REPLY_POOL_FREE()                                                                (g_stPoolUsage.b1ReplyArray = _FALSE)

//--------------------------------------------------
// Macro of Message Buffer Usage info
//--------------------------------------------------
#define GET_DP_RX_REPLY_BUF_FREE()                                                              (g_bDpRxReplyBufFree)
#define SET_DP_RX_REPLY_BUF_FREE()                                                              (g_bDpRxReplyBufFree = _TRUE)
#define CLR_DP_RX_REPLY_BUF_FREE()                                                              (g_bDpRxReplyBufFree = _FALSE)

#define GET_DP_RX_DOWN_REQ_BUF_RELEASE()                                                        (g_stPoolUsage.b1DownReqBufRelease)
#define SET_DP_RX_DOWN_REQ_BUF_RELEASE()                                                        (g_stPoolUsage.b1DownReqBufRelease = _TRUE)
#define CLR_DP_RX_DOWN_REQ_BUF_RELEASE()                                                        (g_stPoolUsage.b1DownReqBufRelease = _FALSE)
#define GET_DP_RX_UP_REPLY_BUF_RELEASE()                                                        (g_stPoolUsage.b1UpReplyBufRelease)
#define SET_DP_RX_UP_REPLY_BUF_RELEASE()                                                        (g_stPoolUsage.b1UpReplyBufRelease = _TRUE)
#define CLR_DP_RX_UP_REPLY_BUF_RELEASE()                                                        (g_stPoolUsage.b1UpReplyBufRelease = _FALSE)

#define GET_DP_RX_DOWN_REQUEST_BUF_PRIORITY()                                                   (g_stPoolUsage.b1DownRequestBufPriority)
#define SET_DP_RX_DOWN_REQUEST_BUF_PRIORITY(x)                                                  (g_stPoolUsage.b1DownRequestBufPriority = (x))

#define GET_DP_RX_UP_REPLY_BUF_PRIORITY()                                                       (g_stPoolUsage.b1UpReplyBufPriority)
#define SET_DP_RX_UP_REPLY_BUF_PRIORITY(x)                                                      (g_stPoolUsage.b1UpReplyBufPriority = (x))

//--------------------------------------------------
// Macro of Message Function Action info
//--------------------------------------------------
#define GET_DP_RX_DOWN_REQUEST_ANAL()                                                           (g_stMsgFunction.b1DownRequestAnal)
#define SET_DP_RX_DOWN_REQUEST_ANAL()                                                           (g_stMsgFunction.b1DownRequestAnal = _TRUE)
#define CLR_DP_RX_DOWN_REQUEST_ANAL()                                                           (g_stMsgFunction.b1DownRequestAnal = _FALSE)

#define GET_DP_RX_DOWN_REPLY_READY()                                                            (g_stMsgFunction.b1DownReplyReady)
#define SET_DP_RX_DOWN_REPLY_READY()                                                            (g_stMsgFunction.b1DownReplyReady = _TRUE)
#define CLR_DP_RX_DOWN_REPLY_READY()                                                            (g_stMsgFunction.b1DownReplyReady = _FALSE)

#define GET_DP_RX_DOWN_REPLY_SET_HPD()                                                          (g_bDpRxDownReplyHPD)
#define SET_DP_RX_DOWN_REPLY_SET_HPD()                                                          (g_bDpRxDownReplyHPD = _TRUE)
#define CLR_DP_RX_DOWN_REPLY_SET_HPD()                                                          (g_bDpRxDownReplyHPD = _FALSE)

#define GET_DP_RX_DOWN_REPLY_DIRECTLY()                                                         (g_stMsgFunction.b1DownReplyDirect)
#define SET_DP_RX_DOWN_REPLY_DIRECTLY()                                                         (g_stMsgFunction.b1DownReplyDirect = _TRUE)
#define CLR_DP_RX_DOWN_REPLY_DIRECTLY()                                                         (g_stMsgFunction.b1DownReplyDirect = _FALSE)

#define GET_DP_RX_DOWN_REPLY_BYPASS()                                                           (g_stMsgFunction.b1DownReplyBypass)
#define SET_DP_RX_DOWN_REPLY_BYPASS()                                                           (g_stMsgFunction.b1DownReplyBypass = _TRUE)
#define CLR_DP_RX_DOWN_REPLY_BYPASS()                                                           (g_stMsgFunction.b1DownReplyBypass = _FALSE)

#define GET_DP_RX_UP_REQUEST_READY()                                                            (g_stMsgFunction.b1UpRequestReady)
#define SET_DP_RX_UP_REQUEST_READY()                                                            (g_stMsgFunction.b1UpRequestReady = _TRUE)
#define CLR_DP_RX_UP_REQUEST_READY()                                                            (g_stMsgFunction.b1UpRequestReady = _FALSE)

#define GET_DP_RX_UP_REQUEST_ANAL()                                                             (g_stMsgFunction.b1UpRequestAnal)
#define SET_DP_RX_UP_REQUEST_ANAL()                                                             (g_stMsgFunction.b1UpRequestAnal = _TRUE)
#define CLR_DP_RX_UP_REQUEST_ANAL()                                                             (g_stMsgFunction.b1UpRequestAnal = _FALSE)

#define GET_DP_RX_UP_REQUEST_BYPASS_DONE()                                                      (g_bUpRequestBypassDone)
#define SET_DP_RX_UP_REQUEST_BYPASS_DONE()                                                      (g_bUpRequestBypassDone = _TRUE)
#define CLR_DP_RX_UP_REQUEST_BYPASS_DONE()                                                      (g_bUpRequestBypassDone = _FALSE)

#define GET_DP_RX_UP_REPLY_ANAL()                                                               (g_stMsgFunction.b1UpReplyAnal)
#define SET_DP_RX_UP_REPLY_ANAL()                                                               (g_stMsgFunction.b1UpReplyAnal = _TRUE)
#define CLR_DP_RX_UP_REPLY_ANAL()                                                               (g_stMsgFunction.b1UpReplyAnal = _FALSE)

#define GET_DP_RX_UP_REPLY_DIRECTLY()                                                           (g_stMsgFunction.b1UpReplyDirect)
#define SET_DP_RX_UP_REPLY_DIRECTLY()                                                           (g_stMsgFunction.b1UpReplyDirect = _TRUE)
#define CLR_DP_RX_UP_REPLY_DIRECTLY()                                                           (g_stMsgFunction.b1UpReplyDirect = _FALSE)

#define GET_DP_GEN_DOWN_REQUEST_MSG()                                                           (g_stMsgFunction.ucGenDownRequestMsg)
#define SET_DP_GEN_DOWN_REQUEST_MSG(x)                                                          (g_stMsgFunction.ucGenDownRequestMsg = (x))
#define CLR_DP_GEN_DOWN_REQUEST_MSG()                                                           (g_stMsgFunction.ucGenDownRequestMsg = _DP_MSG_NONE)

#define GET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG()                                                   (g_stMsgFunction.b1SelfGenDownRequest)
#define SET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG()                                                   (g_stMsgFunction.b1SelfGenDownRequest = _TRUE)
#define CLR_DP_RX_SELF_GEN_DOWN_REQUEST_MSG()                                                   (g_stMsgFunction.b1SelfGenDownRequest = _FALSE)

#if(_DP_TX_SUPPORT == _ON)
#define GET_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY()                                              (g_stMsgFunction.b1WaitRemoteLinkAddressReply)
#define SET_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY()                                              (g_stMsgFunction.b1WaitRemoteLinkAddressReply = _TRUE)
#define CLR_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY()                                              (g_stMsgFunction.b1WaitRemoteLinkAddressReply = _FALSE)
#endif

#define GET_DP_RX_CANCEL_MSG_TIMEOUT_EVENT()                                                    (g_bCancelMsgTimeoutEvent)
#define SET_DP_RX_CANCEL_MSG_TIMEOUT_EVENT()                                                    (g_bCancelMsgTimeoutEvent = _TRUE)
#define CLR_DP_RX_CANCEL_MSG_TIMEOUT_EVENT()                                                    (g_bCancelMsgTimeoutEvent = _FALSE)

#define GET_DP_RX_UP_REQUEST_RETRY_NUM()                                                        (g_stMsgOtherInfo.ucRetryNum)
#define INCREASE_DP_RX_UP_REQUEST_RETRY_NUM()                                                   (g_stMsgOtherInfo.ucRetryNum = g_stMsgOtherInfo.ucRetryNum + 1)
#define CLR_DP_RX_UP_REQUEST_RETRY_NUM()                                                        (g_stMsgOtherInfo.ucRetryNum = 0)

#define GET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS()                                           (g_stMsgOtherInfo.b1ReportTxDpCableStatus)
#define SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(x)                                          (g_stMsgOtherInfo.b1ReportTxDpCableStatus = (x))

#define GET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG()                                                    (g_stMsgOtherInfo.b1IllegalDownRequestMSG)
#define SET_DP_RX_ILLEGAL_DOWN_REQUEST_MSG()                                                    (g_stMsgOtherInfo.b1IllegalDownRequestMSG = _TRUE)
#define CLR_DP_RX_ILLEGAL_DOWN_REQUEST_MSG()                                                    (g_stMsgOtherInfo.b1IllegalDownRequestMSG = _FALSE)
#define GET_DP_RX_ILLEGAL_UP_REQUEST_MSG()                                                      (g_stMsgOtherInfo.b1IllegalUpRequestMSG)
#define SET_DP_RX_ILLEGAL_UP_REQUEST_MSG()                                                      (g_stMsgOtherInfo.b1IllegalUpRequestMSG = _TRUE)
#define CLR_DP_RX_ILLEGAL_UP_REQUEST_MSG()                                                      (g_stMsgOtherInfo.b1IllegalUpRequestMSG = _FALSE)
#define GET_DP_MSG_REQUEST_ID()                                                                 (g_unDpRequestPool.pucData[0] & 0x7F)
#define GET_DP_MSG_REPLY_ID()                                                                   (g_unDpReplyPool.pucData[0] & 0x7F)

#define GET_DP_MSG_UP_REPLY_TYPE()                                                              ((g_unDpReplyPool.pucData[0]) >> 7)

#define GET_DP_RX_MST2SST_ENABLE()                                                              (g_bMst2SstEnable)
#define SET_DP_RX_MST2SST_ENABLE(x)                                                             (g_bMst2SstEnable = (x))

#define GET_DP_PBN_PER_TIME_SLOT(x, y)                                                          (((x) == _DP_HIGH_SPEED2_540MHZ) ? (10 * (y)) : (((x) == _DP_HIGH_SPEED_270MHZ) ? (5 * (y)) : (3 * (y))))

//--------------------------------------------------
// DP Rx EVENT
//--------------------------------------------------
#define GET_DP_RX_EVENT()                                                                       (g_ucRxEvent)
#define SET_DP_RX_EVENT(x)                                                                      (g_ucRxEvent = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Enumerations of Message Type
//--------------------------------------------------
typedef enum
{
    _DP_RX_MST_MODE_STATUS_NONE_MSG = 0x00,
    _DP_RX_MST_MODE_STATUS_BUILD_TOPOLOGY,
    _DP_RX_MST_MODE_STATUS_ALLOCATED_PBN,
} EnumDpMstModeStatus;

//--------------------------------------------------
// Enumerations of Message Type
//--------------------------------------------------
typedef enum
{
    _DP_DOWN_REQUEST_MSG,
    _DP_DOWN_REPLY_MSG,
    _DP_UP_REQUEST_MSG,
    _DP_UP_REPLY_MSG,
} EnumDpMessageType;

//--------------------------------------------------
// Enumerations of Message Type
//--------------------------------------------------
typedef enum
{
    _DP_MSG_NONE = 0x00,
    _DP_MSG_LINK_ADDRESS = 0x01,
    _DP_MSG_CONNECTION_STATUS_NOTIFY = 0x02,
    _DP_MSG_ENUM_PATH_RESOURCES = 0x10,
    _DP_MSG_ALLOCATE_PAYLOAD = 0x11,
    _DP_MSG_QUERY_PAYLOAD = 0x12,
    _DP_MSG_RESOURCE_STATUS_NOTIFY = 0x13,
    _DP_MSG_CLEAR_PAYLOAD_ID_TABLE = 0x14,
    _DP_MSG_REMOTE_DPCD_READ = 0x20,
    _DP_MSG_REMOTE_DPCD_WRITE = 0x21,
    _DP_MSG_REMOTE_I2C_READ = 0x22,
    _DP_MSG_REMOTE_I2C_WRITE = 0x23,
    _DP_MSG_POWER_UP_PHY = 0x24,
    _DP_MSG_POWER_DOWN_PHY = 0x25,
    _DP_MSG_SINK_EVENT_NOTIFY = 0x30,
    _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS = 0x38,
} EnumMessageReuqestID;

//--------------------------------------------------
// Enumerations of Message Type
//--------------------------------------------------
typedef enum
{
    _DP_ADD_PAYLOAD_ID,
    _DP_MODIFY_PAYLOAD_ID_TABLE,
    _DP_CLEAR_PAYLOAD_ID_TABLE,
    _DP_RX_NONE_ACTION,
} EnumSyncPayloadTableAction;

//--------------------------------------------------
// Enumerations of Message NAK Reasons
//--------------------------------------------------
typedef enum
{
    _NONE_MSG_ERROR = 0x00,
    _WRITE_FAILURE = 0x01,
    _INVALID_RAD = 0x02,
    _CRC_FAILURE = 0x03,
    _BAD_PARAM = 0x04,
    _DEFER = 0x05,
    _LINK_FAILURE = 0x06,
    _NO_RESOURCES = 0x07,
    _DPCD_FAIL = 0x08,
    _I2C_NAK = 0x09,
    _ALLOCATE_FAIL = 0x0A,
} EnumMessageNakReasons;

//--------------------------------------------------
// Enumerations of Physical Port
//--------------------------------------------------
typedef enum
{
    _DP_PORT0 = 0x00,
    _DP_PORT1 = 0x01,
    _DP_PORT2 = 0x02,
    _DP_PORT3 = 0x03,
    _DP_PORT4 = 0x04,
    _DP_PORT5 = 0x05,
    _DP_PORT6 = 0x06,
    _DP_PORT7 = 0x07,
} EnumDpPhysicalPort;

//--------------------------------------------------
// Enumerations of Logical Port
//--------------------------------------------------
typedef enum
{
    _DP_PORT8 = 0x08,
    _DP_PORT9 = 0x09,
    _DP_PORT10 = 0x0A,
    _DP_PORT11 = 0x0B,
    _DP_PORT12 = 0x0C,
    _DP_PORT13 = 0x0D,
    _DP_PORT14 = 0x0E,
    _DP_PORT15 = 0x0F,
} EnumDpLogicalPort;

//--------------------------------------------------
// Enumerations of Multi-Stream Source Number
//--------------------------------------------------
typedef enum
{
    _DP_ST_1 = 0x00,
    _DP_ST_2 = 0x01,
    _DP_ST_3 = 0x02,
    _DP_ST_4 = 0x03,
    _DP_ST_5 = 0x04,
    _DP_ST_NONE = 0x05,
} EnumDpStreamNum;

//--------------------------------------------------
// Enumerations of Multi-Stream Source Number
//--------------------------------------------------
typedef enum
{
    _DP_ST_SOURCE1 = 0x00,
    _DP_ST_SOURCE2 = 0x01,
    _DP_ST_SOURCE3 = 0x02,
    _DP_ST_SOURCE4 = 0x03,
    _DP_ST_SOURCE5 = 0x04,
    _DP_NO_SOURCE = 0x05,
} EnumDpStreamSourceNum;

//--------------------------------------------------
// Enumerations of DP Rx Event Which Result From Message
//--------------------------------------------------
typedef enum
{
    _DP_RX_NONE_EVENT,
    _DP_RX_DPCD_WRITE_REQUEST,
    _DP_RX_DPCD_READ_REQUEST,
    _DP_RX_REMOTE_MST_DISPLAY_REQUEST,
    _DP_RX_REMOTE_SST_DISPLAY_REQUEST,
    _DP_RX_REMOTE_SST_WITH_AUDIO_DISPLAY_REQUEST,
    _DP_RX_DELETE_REMOTE_DISPLAY_REQUEST,
    _DP_RX_NATIVE_DISPLAY_REQUEST,
    _DP_RX_I2C_READ,
    _DP_RX_I2C_WRITE,
    _DP_RX_QUERY_STREAM_ECRYPTION_STATUS,
} EnumRxEventType;

//--------------------------------------------------
// Enumerations of DP I2C EVENT
//--------------------------------------------------
typedef enum
{
    _DP_RX_IIC_NONE_EVENT = 0x00,
    _DP_RX_IIC_READ_EDID = 0x50,
    _DP_RX_IIC_DDCCI_COMMAND = 0x37,
} EnumDpIICEventType;

//--------------------------------------------------
// Enumerations of DP Query Msg
//--------------------------------------------------
typedef enum
{
    _DP_STREAM_NOT_EXIST = 0x00,
    _DP_STREAM_NOT_ACTIVE = _BIT0,
    _DP_STREAM_ACTIVE = _BIT1,
} EnumDpQueryEncryptStreamState;

typedef enum
{
    _DP_OUTPUT_SINK_TYPE_NON_AUTHENTICABLE = _BIT0,
    _DP_OUTPUT_SINK_TYPE_MSG_NO_SUPPORT = _BIT1,
    _DP_OUTPUT_SINK_TYPE_MSG_SUPPORT = _BIT2,
} EnumDpQueryEncryptOutputSinkType;

//****************************************************************************
// Structures
//****************************************************************************
//--------------------------------------------------
// Definitions for DP LINK ADDRESS  REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
}StructReqLinkAddress;

//--------------------------------------------------
// Definitions of DP ALLOCATE PAYLOAD REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4NumOfSDPStreams : 4;
    BYTE b4PortNum : 4;
    BYTE b7PayloadID : 7;
    BYTE b1Zero1 : 1;
    WORD usPBN;
    BYTE pucRemainPart[8];
}StructReqAllocatePayload;

//--------------------------------------------------
// Definitions of DP CLEAR PAYLOAD ID TABLE REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
}StructReqClearPayloadIDTable;

//--------------------------------------------------
// Definitions of DP ENUM PATH RESOURCE REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
}StructReqEnumPathResource;

//--------------------------------------------------
// Definitions of DP CONNECTION STATUS NOTIFY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
    BYTE pucGUID[16];
    BYTE b3PeerDeviceType : 3;
    BYTE b1InputPort : 1;
    BYTE b1MsgCabability : 1;
    BYTE b1DpPlugStatus : 1;
    BYTE b1LegacyPlugStatus : 1;
    BYTE b1Zero2 : 1;
}StructReqConnectionStatusNotify;

//--------------------------------------------------
// Definitions of DP POWER DOWN PHY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
}StructReqPowerDownPHY;

//--------------------------------------------------
// Definitions of DP POWER UP PHY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
}StructReqPowerUpPHY;

//--------------------------------------------------
// Definitions of DP QUERY PAYLOAD REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
    BYTE b7PayloadID : 7;
    BYTE b1Zero2 : 1;
}StructReqQueryPayload;

//--------------------------------------------------
// Definitions of DP REMOTE DPCD READ REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4DpcdAddressH : 4;
    BYTE b4PortNum : 4;
    BYTE ucDpcdAddressM;
    BYTE ucDpcdAddressL;
    BYTE ucNumOfRead;
}StructReqRemoteDpcdRead;

//--------------------------------------------------
// Definitions of DP REMOTE DPCD WRITE REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4DpcdAddressH : 4;
    BYTE b4PortNum : 4;
    BYTE ucDpcdAddressM;
    BYTE ucDpcdAddressL;
    BYTE ucNumOfByteToWrite;
    BYTE pucDpcdByteToWrite[16];
}StructReqRemoteDpcdWrite;

//--------------------------------------------------
// Definitions of DP REMOTE I2C READ REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b2NumOfI2CWriteTran : 2;
    BYTE b2Zero1 : 2;
    BYTE b4PortNum : 4;
    BYTE pucRemainPart[46];
}StructReqRemoteI2CRead;

//--------------------------------------------------
// Definitions of DP REMOTE I2C WRITE REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
    BYTE b7WriteI2CDeviceID : 7;
    BYTE b1Zero2 : 1;
    BYTE ucNumOfByteToWrite;
    BYTE pucI2CDateToWrite[44];
}StructReqRemoteI2CWrite;

//--------------------------------------------------
// Definitions of DP RESOURCE STATUS NOTIFY REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE b4Zero1 : 4;
    BYTE b4PortNum : 4;
    BYTE pucGUID[16];
    WORD usAvailablePBN;
}StructReqResourceStatusNotify;

//--------------------------------------------------
// Definitions of DP QUERY STREAM ENCRYPTION STATUS REQUEST MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1Zero : 1;
    BYTE ucStreamID;
    BYTE pucClientID[7];
    BYTE b2Zero : 2;
    BYTE b1StreamBehaviorMask : 1;
    BYTE b2StreamBehavior : 2;
    BYTE b1StreamEventMask : 1;
    BYTE b2StreamEvent : 2;
}StructReqQueryStreamEncryptionStatus;

//--------------------------------------------------
// Definitions for DP LINK ADDRESS REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE pucGuid[16];
    BYTE b4NumOfPort : 4;
    BYTE b4Zero : 4;
    BYTE b4Port0Num : 4;
    BYTE b3PeerDeviceType0 : 3;
    BYTE b1InputPort0 : 1;
    BYTE b6Zero1 : 6;
    BYTE b1DpPlugStatus0 : 1;
    BYTE b1MsgCapability0 : 1;
    BYTE b4Port1Num : 4;
    BYTE b3PeerDeviceType1 : 3;
    BYTE b1InputPort1 : 1;
    BYTE b5Zero2 : 5;
    BYTE b1LegacyPlugStatus1 : 1;
    BYTE b1DpPlugStatus1 : 1;
    BYTE b1MsgCapability1 : 1;
    BYTE ucDpcdRevision1;
    BYTE pucPeer1Guid[16];
    BYTE b4NumSDPStreamSink1 : 4;
    BYTE b4NumSDPStreams1 : 4;
    BYTE b4Port2Num : 4;
    BYTE b3PeerDeviceType2 : 3;
    BYTE b1InputPort2 : 1;
    BYTE b5Zero3 : 5;
    BYTE b1LegacyPlugStatus2 : 1;
    BYTE b1DpPlugStatus2 : 1;
    BYTE b1MsgCapability2 : 1;
    BYTE ucDpcdRevision2;
    BYTE pucPeer2Guid[16];
    BYTE b4NumSDPStreamSink2 : 4;
    BYTE b4NumSDPStreams2 : 4;
}StructRepLinkAddress;

//--------------------------------------------------
// Definitions for DP ALLOCATE PAYLOAD REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    BYTE b4PortNum : 4;
    BYTE b7PayloadID : 7;
    BYTE b1Zero1 : 1;
    WORD usAllocatePBN;
}StructRepAllocatePayload;

//--------------------------------------------------
// Definitions for DP CLEAR PAYLOAD ID TABLE REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
}StructRepClearPayloadIDTable;

//--------------------------------------------------
// Definitions for DP ENUM PATH RESOURCE REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    BYTE b4PortNum : 4;
    WORD usFullPBN;
    WORD usAvailablePBN;
}StructRepEnumPathResource;

//--------------------------------------------------
// Definitions for DP CONNECTION STATUS NOTIFY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
}StructRepConnectionStatusNotify;

//--------------------------------------------------
// Definitions for DP POWER DOWN PHY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    BYTE b4PortNum : 4;
}StructRepPowerDownPHY;

//--------------------------------------------------
// Definitions for DP POWER UP PHY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    BYTE b4PortNum : 4;
}StructRepPowerUpPHY;

//--------------------------------------------------
// Definitions for DP QUERY PAYLOAD REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4Zero : 4;
    BYTE b4PortNum : 4;
    WORD usAllocatePBN;
}StructRepQueryPayload;

//--------------------------------------------------
// Definitions for DP REMOTE DPCD READ REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4PortNum : 4;
    BYTE b4Zero : 4;
    BYTE ucNumOfRead;
    BYTE pucDpcdRead[32];
}StructRepRemoteDpcdRead;

//--------------------------------------------------
// Definitions for DP REMOTE DPCD WRITE REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4PortNum : 4;
    BYTE b4Zero : 4;
}StructRepRemoteDpcdWrite;

//--------------------------------------------------
// Definitions for DP REMOTE I2C READ REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4PortNum : 4;
    BYTE b4Zero : 4;
    BYTE ucNumOfRead;
    BYTE pucI2CRead[256];
}StructRepRemoteI2CRead;

//--------------------------------------------------
// Definitions for DP REMOTE I2C WRITE REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b4PortNum : 4;
    BYTE b4Zero : 4;
}StructRepRemoteI2CWrite;

//--------------------------------------------------
// Definitions for DP RESOURCE STATUS NOTIFY REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
}StructRepResourceStatusNotify;

//--------------------------------------------------
// Definitions for DP NAK REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE pucGuid[16];
    BYTE ucNakReason;
    BYTE ucNakData;
}StructRepNak;

//--------------------------------------------------
// Definitions for DP REMOTE I2C READ NAK REPLY MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE pucGuid[16];
    BYTE b4zero : 4;
    BYTE b4Port : 4;
    BYTE ucNakReason;
    BYTE b2I2CNakTransaction : 2;
    BYTE b6zero1 : 6;
}StructRepRemoteI2CReadNak;

//--------------------------------------------------
// Definitions for DP QUERY STREAM ENCRYPTION STATUS MESSAGE
//--------------------------------------------------
typedef struct
{
    BYTE b7ReqID : 7;
    BYTE b1RepType : 1;
    BYTE b3Zero : 3;
    BYTE b1StreamAuthentication : 1;
    BYTE b1StreamEncryption : 1;
    BYTE b1StreamRepeaterFunction : 1;
    BYTE b2StreamState : 2;
    BYTE b1Signed : 1;
    BYTE b2Zero : 2;
    BYTE b2StreamOuputCpType : 2;
    BYTE b3StreamOuputSinkType : 3;
    BYTE ucStreamID;
    BYTE pucSignatureL[20];
}StructRepQueryStreamEncryptionStatus;

//--------------------------------------------------
// Struct for Pool Usage Info
//--------------------------------------------------
typedef struct
{
    BYTE b1ReqArray : 1;
    BYTE b1ReplyArray : 1;
    BYTE b1DownReqBufRelease : 1;
    BYTE b1UpReplyBufRelease : 1;
    BYTE b1DownRequestBufPriority : 1;
    BYTE b1UpReplyBufPriority : 1;
}StructPoolUsageInfo;

//--------------------------------------------------
// Struct for Message Function Action Info
//--------------------------------------------------
typedef struct
{
    BYTE b1DownRequestAnal : 1;
    BYTE b1DownReplyReady : 1;
    BYTE b1DownReplyBypass : 1;
    BYTE b1DownReplyDirect : 1;
    BYTE b1UpRequestReady : 1;
    BYTE b1UpRequestAnal : 1;
    BYTE b1UpReplyAnal : 1;
    BYTE b1UpReplyDirect : 1;
    BYTE ucGenDownRequestMsg;
    BYTE b1SelfGenDownRequest : 1;
#if(_DP_TX_SUPPORT == _ON)
    BYTE b1WaitRemoteLinkAddressReply : 1;
#endif
}StructRxMsgFunctionInfo;

//--------------------------------------------------
// Struct for Other Message Info
//--------------------------------------------------
typedef struct
{
    BYTE b1ReportTxDpCableStatus : 1;
    BYTE ucRetryNum;
    BYTE b1IllegalDownRequestMSG : 1;
    BYTE b1IllegalUpRequestMSG : 1;
}StructRxMsgOtherInfo;

//****************************************************************************
// Union
//****************************************************************************
//--------------------------------------------------
// Unior for All Request Message Info
//--------------------------------------------------
typedef union
{
    BYTE pucData[_DP_REQUEST_MSG_BYTE_WISE_MAX_LEN];
    StructReqLinkAddress stLinkAddress;
    StructReqAllocatePayload stAllocatePayload;
    StructReqClearPayloadIDTable stClearPayloadID;
    StructReqEnumPathResource stEnumPathResource;
    StructReqConnectionStatusNotify stConnectionStatusNotify;
    StructReqPowerDownPHY stPowerDownPHY;
    StructReqPowerUpPHY stPowerUpPHY;
    StructReqQueryPayload stQueryPayload;
    StructReqRemoteDpcdRead stRemoteDpcdRead;
    StructReqRemoteDpcdWrite stRemoteDpcdWrite;
    StructReqRemoteI2CRead stRemoteI2CRead;
    StructReqRemoteI2CWrite stRemoteI2CWrite;
    StructReqResourceStatusNotify stStructReqResourceStatusNotify;
    StructReqQueryStreamEncryptionStatus stStructReqQueryStreamEncryptionStatus;
}UnionDpRxReqStrct;

//--------------------------------------------------
// Unior for All Reply Message Info
//--------------------------------------------------
typedef union
{
    BYTE pucData[_DP_REPLY_MSG_BYTE_WISE_MAX_LEN];
    StructRepLinkAddress stLinkAddress;
    StructRepAllocatePayload stAllocatePayload;
    StructRepClearPayloadIDTable stClearPayloadID;
    StructRepEnumPathResource stEnumPathResource;
    StructRepConnectionStatusNotify stConnectionStatusNotify;
    StructRepPowerUpPHY stPowerDownPHY;
    StructRepPowerUpPHY stPowerUpPHY;
    StructRepQueryPayload stQueryPayload;
    StructRepRemoteDpcdRead stRemoteDpcdRead;
    StructRepRemoteDpcdWrite stRemoteDpcdWrite;
    StructRepRemoteI2CRead stRemoteI2CRead;
    StructRepRemoteI2CWrite stRemoteI2CWrite;
    StructRepResourceStatusNotify stResourceStatusNotify;
    StructRepRemoteI2CReadNak stRemoteI2CReadNak;
    StructRepNak stStructRepNak;
    StructRepQueryStreamEncryptionStatus stStructRepQueryStreamEncryptionStatus;
}UnionDpRxRepStrct;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_DOWN_REPLY_MANUAL_MODE_SUPPORT == _ON)
extern BYTE g_ucDpDownReplyManualMsgCount;
extern BYTE g_ucDpDownReplyManualMsgLength;
#endif

extern EnumDPMSTPort g_enumDpMSTCapablePort;
extern EnumDpMstModeStatus g_enumDpMSTModeStatus;
extern BYTE g_pucDpStreamToIdMapping[5];
extern BYTE g_ucRxEvent;
extern StructPoolUsageInfo g_stPoolUsage;
extern bit g_bDpRxReplyBufFree;
extern bit g_bCancelMsgTimeoutEvent;
extern bit g_bDpRxAddPayload;

extern StructRxMsgFunctionInfo g_stMsgFunction;
extern StructRxMsgOtherInfo g_stMsgOtherInfo;
extern UnionDpRxReqStrct g_unDpRequestPool;
extern UnionDpRxRepStrct g_unDpReplyPool;
extern BYTE g_pucDpStreamToIdMapping[5];

#if(_DP_TX_SUPPORT == _ON)
extern BYTE g_ucTotalReceivedMsgCount;
extern BYTE g_ucSelfGenUpRequestRetry;
#endif

extern bit g_bMst2SstEnable;
extern bit g_bDpRxDownReplyHPD;

extern BYTE g_pucDPMsgQueryEncryptClientId[7];

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
extern bit g_bDpMSTD6Capable;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpRxMstInitial(EnumDPMSTPort enumRxMstPort);
extern void ScalerDpRxMstIntHandle_EXINT0(void);

#if(_DP_TX_SUPPORT == _ON)
extern bit ScalerDpRxMstToSstTxMeasureTimingChange(void);
extern bit ScalerDpRxMstCheckMsgTransition(void);
extern void ScalerDpRxMstMsgCountResetEvent(void);
#endif

extern void ScalerDpRxMstMsgTimeoutEvent(void);
extern void ScalerDpRxMstIllegalMsgReply(void);
extern void ScalerDpRxMstSyncPayloadIDTable_EXINT0(void);
extern BYTE ScalerDpRxMstStreamMuxCheck(BYTE ucSourceNum);
extern bit ScalerDpRxMstCheckMsgBufferFree(void);
extern EnumDpStreamNum ScalerDpRxMstSearchMatchStream(BYTE ucTargetID);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRxMstQueryEncryptionWriteShaInput(void);
#endif

#endif // End of #if(_DP_MST_SUPPORT == _ON)


