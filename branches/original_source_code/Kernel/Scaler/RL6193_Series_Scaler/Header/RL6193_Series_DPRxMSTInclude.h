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
// ID Code      : RL6193_Series_DPRxMSTInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_DP_MST_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

#define RET_REG_ADDR_DP_RX_UPSTREAM_REPLY_RAD0_RAD1()               (((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_44_MSG_TX_SET1 : PBA_44_MSG_TX_SET1))
#define RET_REG_ADDR_DP_RX_UPSTREAM_DOWN_RAD0_RAD1()                ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_06_MSG_RX_DATA1 : PBA_06_MSG_RX_DATA1)

//--------------------------------------------------
// Daisy Chain MTP Scheduler Related Register Macro
//--------------------------------------------------
#define RET_REG_ADDR_DP_RX0_DAIZY_ST3_START()                       (PB5_11_DAISY_CTRL_1)
#define RET_REG_ADDR_DP_RX0_DAIZY_ST3_END()                         (PB5_12_DAISY_CTRL_2)
#define RET_REG_ADDR_DP_RX1_DAIZY_ST3_START()                       (PB8_11_DAISY_CTRL_1)
#define RET_REG_ADDR_DP_RX1_DAIZY_ST3_END()                         (PB8_12_DAISY_CTRL_2)

#define GET_REG_DP_RX_DAIZY_ST3_START()                             (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_11_DAISY_CTRL_1 : PB8_11_DAISY_CTRL_1)) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST3_END()                               (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_12_DAISY_CTRL_2 : PB8_12_DAISY_CTRL_2)) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST4_START()                             (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_13_DAISY_CTRL_3 : PB8_13_DAISY_CTRL_3)) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST4_END()                               (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_14_DAISY_CTRL_4 : PB8_14_DAISY_CTRL_4)) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST5_START()                             (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_15_DAISY_CTRL_5 : PB8_15_DAISY_CTRL_5)) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST5_END()                               (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_16_DAISY_CTRL_6 : PB8_16_DAISY_CTRL_6)) & 0x3F)

#define SET_REG_DP_RX_DAISY_CHAIN_LANE_NUM(x)                       (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_10_DAISY_CTRL_0 : PB8_10_DAISY_CTRL_0), ~(_BIT5 | _BIT4), ((x) << 4)))
#define SET_REG_DP_RX_DAIZY_ST3_START(x)                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_11_DAISY_CTRL_1 : PB8_11_DAISY_CTRL_1), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST3_END(x)                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_12_DAISY_CTRL_2 : PB8_12_DAISY_CTRL_2), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST4_START(x)                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_13_DAISY_CTRL_3 : PB8_13_DAISY_CTRL_3), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST4_END(x)                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_14_DAISY_CTRL_4 : PB8_14_DAISY_CTRL_4), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST5_START(x)                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_15_DAISY_CTRL_5 : PB8_15_DAISY_CTRL_5), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST5_END(x)                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_16_DAISY_CTRL_6 : PB8_16_DAISY_CTRL_6), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))

#define SET_REG_DP_RX_SEND_ACT_ENABLE()                             (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_10_DAISY_CTRL_0 : PB8_10_DAISY_CTRL_0), ~_BIT1, _BIT1))
#define GET_REG_DP_RX_SEND_ACT_FLAG()                               ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_10_DAISY_CTRL_0 : PB8_10_DAISY_CTRL_0), _BIT0))
#define CLR_REG_DP_RX_SEND_ACT_FLAG()                               (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB5_10_DAISY_CTRL_0 : PB8_10_DAISY_CTRL_0), ~_BIT0, _BIT0))

//--------------------------------------------------
// Definitions of Down Request Related Register Macro
//--------------------------------------------------
#define SET_REG_DP_RX_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE()  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_00_AUX_RX_MSG_RX_CTRL : PBA_00_AUX_RX_MSG_RX_CTRL), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_REG_DP_RX_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE()  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_00_AUX_RX_MSG_RX_CTRL : PBA_00_AUX_RX_MSG_RX_CTRL), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00))
#define CLR_REG_DP_RX_DOWN_REQUEST_MSG_FINISH()                     (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_02_MSG_RX_FINISH : PBA_02_MSG_RX_FINISH), 0xFF))
#define CLR_REG_DP_RX_DOWN_REQUEST_MSG_ERROR()                      (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_03_MSG_RX_FLAG : PBA_03_MSG_RX_FLAG), 0xFF))
#define SET_REG_DP_RX_DOWN_REQUEST_MSG_DOUBLE_BUFFER_ENABLE()       (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_04_MSG_RX_BUF_CLR : PBA_04_MSG_RX_BUF_CLR), ~_BIT6, _BIT6))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF0_BUF1()                      (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_04_MSG_RX_BUF_CLR : PBA_04_MSG_RX_BUF_CLR), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define RST_REG_DP_RX_DOWN_REQUEST_FSM_WRITTEN()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_1B_MSG_EXCEPT_CTRL0 : PBA_1B_MSG_EXCEPT_CTRL0), ~_BIT7, _BIT7))

#define SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE()        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_00_AUX_RX_MSG_RX_CTRL : PBA_00_AUX_RX_MSG_RX_CTRL), ~_BIT0, _BIT0))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH()                (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_02_MSG_RX_FINISH : PBA_02_MSG_RX_FINISH), _BIT0))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH()                (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_02_MSG_RX_FINISH : PBA_02_MSG_RX_FINISH), ~(_BIT4 | _BIT0), _BIT0))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_LENGTH()                (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_10_MSG_RX_BUF0_LEN : PBA_10_MSG_RX_BUF0_LEN)) & 0x7F)
#define GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_ERROR()                 (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_03_MSG_RX_FLAG : PBA_03_MSG_RX_FLAG), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_ERROR()                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_03_MSG_RX_FLAG : PBA_03_MSG_RX_FLAG), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_DOWN_REQUEST_BUF0_READ_PTR(x)                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_12_MSG_RX_BUF0_RDPTR : PBA_12_MSG_RX_BUF0_RDPTR), ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF0_DATA()                      (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_13_MSG_RX_BUF0_RD_DATA : PBA_13_MSG_RX_BUF0_RD_DATA)))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF0()                           (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_04_MSG_RX_BUF_CLR : PBA_04_MSG_RX_BUF_CLR), ~(_BIT3 | _BIT1), (_BIT3 | _BIT1)))

#define GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN()                   ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_1B_MSG_EXCEPT_CTRL0 : PBA_1B_MSG_EXCEPT_CTRL0), _BIT0))
#define CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN()                   (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_1B_MSG_EXCEPT_CTRL0 : PBA_1B_MSG_EXCEPT_CTRL0), ~_BIT0, _BIT0))

#define SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE()        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_00_AUX_RX_MSG_RX_CTRL : PBA_00_AUX_RX_MSG_RX_CTRL), ~_BIT1, _BIT1))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH()                ((ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_02_MSG_RX_FINISH : PBA_02_MSG_RX_FINISH), _BIT4)) >> 4)
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH()                (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_02_MSG_RX_FINISH : PBA_02_MSG_RX_FINISH), ~(_BIT4 | _BIT0), _BIT4))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_LENGTH()                (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_14_MSG_RX_BUF1_LEN : PBA_14_MSG_RX_BUF1_LEN)) & 0x7F)
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_ERROR()                 (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_03_MSG_RX_FLAG : PBA_03_MSG_RX_FLAG), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_ERROR()                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_03_MSG_RX_FLAG : PBA_03_MSG_RX_FLAG), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define SET_REG_DP_RX_DOWN_REQUEST_BUF1_READ_PTR(x)                 (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_16_MSG_RX_BUF1_RDPTR : PBA_16_MSG_RX_BUF1_RDPTR), ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_WRITE_PTR()                 (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_15_MSG_RX_BUF1_WRPTR : PBA_15_MSG_RX_BUF1_WRPTR)))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_DATA()                      (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_17_MSG_RX_BUF1_RD_DATA : PBA_17_MSG_RX_BUF1_RD_DATA)))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF1()                           (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_04_MSG_RX_BUF_CLR : PBA_04_MSG_RX_BUF_CLR), ~(_BIT2 | _BIT0), (_BIT2 | _BIT0)))

#define GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT()                        (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_05_MSG_RX_DATA0 : PBA_05_MSG_RX_DATA0), (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
#define GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR()                        (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_05_MSG_RX_DATA0 : PBA_05_MSG_RX_DATA0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM()            ((ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_06_MSG_RX_DATA1 : PBA_06_MSG_RX_DATA1), (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> 4)
#define GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(x)                       (ScalerGetBit((((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_06_MSG_RX_DATA1 : PBA_06_MSG_RX_DATA1) + (x)), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(x)                       (ScalerGetBit((((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_06_MSG_RX_DATA1 : PBA_06_MSG_RX_DATA1) + (x)), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD0()                           (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_06_MSG_RX_DATA1 : PBA_06_MSG_RX_DATA1), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD1()                           (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_06_MSG_RX_DATA1 : PBA_06_MSG_RX_DATA1), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD2()                           (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_07_MSG_RX_DATA2 : PBA_07_MSG_RX_DATA2), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD3()                           (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_07_MSG_RX_DATA2 : PBA_07_MSG_RX_DATA2), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD4()                           (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_08_MSG_RX_DATA3 : PBA_08_MSG_RX_DATA3), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD5()                           (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_08_MSG_RX_DATA3 : PBA_08_MSG_RX_DATA3), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD6()                           (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_09_MSG_RX_DATA4 : PBA_09_MSG_RX_DATA4), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD7()                           (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_09_MSG_RX_DATA4 : PBA_09_MSG_RX_DATA4), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))


#define GET_REG_DP_RX_DOWN_REQUEST_MSG_BROADCAST()                  (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_0D_MSG_RX_DATA8 : PBA_0D_MSG_RX_DATA8), _BIT7))
#define GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH()                       (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_0D_MSG_RX_DATA8 : PBA_0D_MSG_RX_DATA8), _BIT6))
#define GET_REG_DP_RX_DOWN_REQUEST_MSG_MSN()                        (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_0E_MSG_RX_DATA9 : PBA_0E_MSG_RX_DATA9), _BIT4))

#define SET_REG_DP_RX_DOWN_REQUEST_HEADER0_INFO()                   (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_04_MSG_RX_BUF_CLR : PBA_04_MSG_RX_BUF_CLR), ~_BIT4, 0x00))
#define SET_REG_DP_RX_DOWN_REQUEST_HEADER1_INFO()                   (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_04_MSG_RX_BUF_CLR : PBA_04_MSG_RX_BUF_CLR), ~_BIT4, _BIT4))


//--------------------------------------------------
// Definitions of Down Reply Related Register Macro
//--------------------------------------------------
#define GET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ()                    ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), _BIT5))
#define SET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~_BIT5, _BIT5))
#define CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~_BIT5, 0x00))

#define GET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ_FLAG()               ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_41_MSG_TX_FINISH : PBA_41_MSG_TX_FINISH), _BIT2))
#define CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ_FLAG()               (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_41_MSG_TX_FINISH : PBA_41_MSG_TX_FINISH), ~_BIT2, _BIT2))

#define GET_REG_DP_RX_DOWN_REPLY_BUFFER_END_FLAG()                  ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_52_BUF_END_FLAG : PBA_52_BUF_END_FLAG), _BIT0))
#define CLR_REG_DP_RX_DOWN_REPLY_BUFFER_END_FLAG()                  (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_52_BUF_END_FLAG : PBA_52_BUF_END_FLAG), ~_BIT0, _BIT0))
//--------------------------------------------------
// Definitions of Up Request Related Register Macro
//--------------------------------------------------
#define GET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ()                    ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), _BIT6))
#define SET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~_BIT6, _BIT6))
#define CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~_BIT6, 0x00))

#define GET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ_FLAG()               ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_41_MSG_TX_FINISH : PBA_41_MSG_TX_FINISH), _BIT3))
#define CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ_FLAG()               (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_41_MSG_TX_FINISH : PBA_41_MSG_TX_FINISH), ~_BIT3, _BIT3))

//--------------------------------------------------
// Definitions of Upstream Reply RelatedRegister Macro
//--------------------------------------------------
#define CLR_REG_DP_RX_DOWN_REPLY_UP_REQUEST_READY_BIT_IRQ()         (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~(_BIT6 | _BIT5), 0x00))

#define SET_REG_DP_RX_UPSTREAM_REPLY()                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~_BIT0, _BIT0))
#define CLR_REG_DP_RX_UPSTREAM_REPLY()                              (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~_BIT0, 0x00))
#define SET_REG_DP_RX_UPSTREAM_HW_AUTO_MODE()                       (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~_BIT2, 0x00))
#define SET_REG_DP_RX_UPSTREAM_HW_MANUAL_MODE()                     (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_40_AUX_RX_MSG_TX_CTRL : PBA_40_AUX_RX_MSG_TX_CTRL), ~_BIT2, _BIT2))
#define SET_REG_DP_RX_UPSTREAM_START_BIT()                          (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4C_MSG_TX_SET9 : PBA_4C_MSG_TX_SET9), ~_BIT7, _BIT7))
#define CLR_REG_DP_RX_UPSTREAM_START_BIT()                          (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4C_MSG_TX_SET9 : PBA_4C_MSG_TX_SET9), ~_BIT7, 0x00))
#define SET_REG_DP_RX_UPSTREAM_END_BIT()                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4C_MSG_TX_SET9 : PBA_4C_MSG_TX_SET9), ~_BIT6, _BIT6))
#define CLR_REG_DP_RX_UPSTREAM_END_BIT()                            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4C_MSG_TX_SET9 : PBA_4C_MSG_TX_SET9), ~_BIT6, 0x00))
#define SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(x)                      (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_42_MSG_TX_LENGTH : PBA_42_MSG_TX_LENGTH), (x)))
#define GET_REG_DP_RX_UPSTREAM_REPLY_LENGTH()                       (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_42_MSG_TX_LENGTH : PBA_42_MSG_TX_LENGTH)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_LCT(x)                         (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_43_MSG_TX_SET0 : PBA_43_MSG_TX_SET0), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define GET_REG_DP_RX_UPSTREAM_REPLY_LCT()                          ((ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_43_MSG_TX_SET0 : PBA_43_MSG_TX_SET0), (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> 4)
#define SET_REG_DP_RX_UPSTREAM_REPLY_LCR(x)                         (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_43_MSG_TX_SET0 : PBA_43_MSG_TX_SET0), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_UPSTREAM_REPLY_LCR()                          (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_43_MSG_TX_SET0 : PBA_43_MSG_TX_SET0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD0(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_44_MSG_TX_SET1 : PBA_44_MSG_TX_SET1), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD1(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_44_MSG_TX_SET1 : PBA_44_MSG_TX_SET1), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD2(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_45_MSG_TX_SET2 : PBA_45_MSG_TX_SET2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD3(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_45_MSG_TX_SET2 : PBA_45_MSG_TX_SET2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD4(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_46_MSG_TX_SET3 : PBA_46_MSG_TX_SET3), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD5(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_46_MSG_TX_SET3 : PBA_46_MSG_TX_SET3), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD6(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_47_MSG_TX_SET4 : PBA_47_MSG_TX_SET4), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD7(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_47_MSG_TX_SET4 : PBA_47_MSG_TX_SET4), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(x)                   (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4B_MSG_TX_SET8 : PBA_4B_MSG_TX_SET8), ~_BIT7, ((BYTE)((bit)(x)) << 7)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_PATH(x)                        (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4B_MSG_TX_SET8 : PBA_4B_MSG_TX_SET8), ~_BIT6, ((BYTE)((bit)(x)) << 6)))
#define GET_REG_DP_RX_UPSTREAM_REPLY_MSN()                          (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4C_MSG_TX_SET9 : PBA_4C_MSG_TX_SET9), _BIT4))
#define SET_REG_DP_RX_UPSTREAM_REPLY_MSN(x)                         (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4C_MSG_TX_SET9 : PBA_4C_MSG_TX_SET9), ~_BIT4, ((BYTE)((bit)(x)) << 4)))
#define CLR_REG_DP_RX_USTERAM_REPLY_BUF()                           (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4F_BUF_CLR : PBA_4F_BUF_CLR), ~_BIT0, _BIT0))
#define CLR_REG_DP_RX_UPSTREAM_REPLY_WRITE_PTR()                    (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_50_BUF_FW_WRPTR : PBA_50_BUF_FW_WRPTR), 0x00))
#define SET_REG_DP_RX_UPSTREAM_REPLY_BUF_DATA(x)                    (ScalerSetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_51_BUF_FW_WR_DATA : PBA_51_BUF_FW_WR_DATA), (x)))
#define GET_REG_DP_RX_UPSTREAM_TRANSITION_ADDRESS()                 (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4D_MSG_TX_ADR_SEL : PBA_4D_MSG_TX_ADR_SEL), _BIT0))
#define SET_REG_DP_RX_UPSTREAM_REPLY_DOWN_REPLY_ADDRESS()           (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4D_MSG_TX_ADR_SEL : PBA_4D_MSG_TX_ADR_SEL), ~_BIT0, 0x00))
#define SET_REG_DP_RX_UPSTREAM_REPLY_UP_REQUEST_ADDRESS()           (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_4D_MSG_TX_ADR_SEL : PBA_4D_MSG_TX_ADR_SEL), ~_BIT0, _BIT0))


//--------------------------------------------------
// Definitions of Up Reply Related Register Macro
//--------------------------------------------------
#define SET_REG_DP_RX_UP_REPLY_MSG_RECEIVE_CRC_IGNORE_ENABLE()      (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_20_AUX_RX_MSG_RX_CTRL : PBA_20_AUX_RX_MSG_RX_CTRL), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_REG_DP_RX_UP_REPLY_MSG_RECEIVE_CRC_IGNORE_ENABLE()      (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_20_AUX_RX_MSG_RX_CTRL : PBA_20_AUX_RX_MSG_RX_CTRL), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00))

#define SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE()            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_20_AUX_RX_MSG_RX_CTRL : PBA_20_AUX_RX_MSG_RX_CTRL), ~_BIT0, _BIT0))
#define GET_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH()                    (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_22_MSG_RX_FINISH : PBA_22_MSG_RX_FINISH), _BIT0))
#define CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_22_MSG_RX_FINISH : PBA_22_MSG_RX_FINISH), ~(_BIT4 | _BIT0), _BIT0))
#define GET_REG_DP_RX_UP_REPLY_BUF0_MSG_LENGTH()                    (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_30_MSG_RX_BUF0_LEN : PBA_30_MSG_RX_BUF0_LEN)) & 0x7F)
#define GET_REG_DP_RX_UP_REPLY_BUF0_MSG_ERROR()                     (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_23_MSG_RX_FLAG : PBA_23_MSG_RX_FLAG), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_ERROR()                     (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_23_MSG_RX_FLAG : PBA_23_MSG_RX_FLAG), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_UP_REPLY_BUF0_RDAD_PTR(x)                     (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_32_MSG_RX_BUF0_RDPTR : PBA_32_MSG_RX_BUF0_RDPTR), ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_UP_REPLY_BUF0_DATA()                          (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_33_MSG_RX_BUF0_RD_DATA : PBA_33_MSG_RX_BUF0_RD_DATA)))
#define CLR_REG_DP_RX_UP_REPLY_BUF0()                               (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_24_MSG_RX_BUF_CLR : PBA_24_MSG_RX_BUF_CLR), ~(_BIT3 | _BIT1), (_BIT3 | _BIT1)))

#define GET_REG_DP_RX_UP_REPLY_ADDR_WRITTEN()                       ((bit)ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_3B_MSG_EXCEPT_CTRL0 : PBA_3B_MSG_EXCEPT_CTRL0), _BIT0))
#define CLR_REG_DP_RX_UP_REPLY_ADDR_WRITTEN()                       (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_3B_MSG_EXCEPT_CTRL0 : PBA_3B_MSG_EXCEPT_CTRL0), ~_BIT0, _BIT0))

#define SET_REG_DP_RX_UP_REPLY_BUF1_MSG_REVEIVE_ENABLE()            (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_20_AUX_RX_MSG_RX_CTRL : PBA_20_AUX_RX_MSG_RX_CTRL), ~_BIT1, _BIT1))
#define GET_REG_DP_RX_UP_REPLY_BUF1_MSG_FINISH()                    ((ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_22_MSG_RX_FINISH : PBA_22_MSG_RX_FINISH), _BIT4)) >> 4)
#define CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_FINISH()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_22_MSG_RX_FINISH : PBA_22_MSG_RX_FINISH), ~(_BIT4 | _BIT0), _BIT4))
#define GET_REG_DP_RX_UP_REPLY_BUF1_MSG_LENGTH()                    (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_34_MSG_RX_BUF1_LEN : PBA_34_MSG_RX_BUF1_LEN)) & 0x7F)
#define GET_REG_DP_RX_UP_REPLY_BUF1_MSG_ERROR()                     (ScalerGetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_23_MSG_RX_FLAG : PBA_23_MSG_RX_FLAG), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_ERROR()                     (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_23_MSG_RX_FLAG : PBA_23_MSG_RX_FLAG), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define SET_REG_DP_RX_UP_REPLY_BUF1_RDAD_PTR(x)                     (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_36_MSG_RX_BUF1_RDPTR : PBA_36_MSG_RX_BUF1_RDPTR), ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_UP_REPLY_BUF1_WRITE_PTR()                     (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_35_MSG_RX_BUF1_WRPTR : PBA_35_MSG_RX_BUF1_WRPTR)))
#define GET_REG_DP_RX_UP_REPLY_BUF1_DATA()                          (ScalerGetByte(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_37_MSG_RX_BUF1_RD_DATA : PBA_37_MSG_RX_BUF1_RD_DATA)))
#define CLR_REG_DP_RX_UP_REPLY_BUF1()                               (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_24_MSG_RX_BUF_CLR : PBA_24_MSG_RX_BUF_CLR), ~(_BIT2 | _BIT0), (_BIT2 | _BIT0)))

#define SET_REG_DP_RX_UP_REPLY_HEADER0_INFO()                       (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_24_MSG_RX_BUF_CLR : PBA_24_MSG_RX_BUF_CLR), ~_BIT4, 0x00))
#define SET_REG_DP_RX_UP_REPLY_HEADER1_INFO()                       (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PB7_24_MSG_RX_BUF_CLR : PBA_24_MSG_RX_BUF_CLR), ~_BIT4, _BIT4))

//--------------------------------------------------
// Definitions of Rx MST2SST Watch Dog Macro
//--------------------------------------------------
#define SET_REG_DP_RX_MST2SST_WATCH_DOG_ENABLE()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PA_F1_DP_RSV1 : P4A_F1_DP_RSV1), ~_BIT0, _BIT0))
#define CLR_REG_DP_RX_MST2SST_WATCH_DOG_ENABLE()                    (ScalerSetBit(((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? PA_F1_DP_RSV1 : P4A_F1_DP_RSV1), ~_BIT0, 0x00))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRxMstMsgPortSel(void);
extern void ScalerDpRxMstPortSel(void);

#endif // End of #if(_DP_MST_SUPPORT == _ON)
