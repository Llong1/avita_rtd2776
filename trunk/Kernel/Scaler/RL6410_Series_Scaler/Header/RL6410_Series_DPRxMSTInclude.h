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
// ID Code      : RL6410_Series_DPRxMSTInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_DP_MST_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Register Address define
//--------------------------------------------------
#define RET_REG_ADDR_DP_RX_UPSTREAM_REPLY_RAD0_RAD1()               (PB7_44_MSG_TX_SET1)
#define RET_REG_ADDR_DP_RX_UPSTREAM_DOWN_RAD0_RAD1()                (PB7_06_MSG_RX_DATA1)

#define RET_REG_ADDR_DP_RX0_DAIZY_ST3_START()                       (PA_92_DAISY_CTRL_1)
#define RET_REG_ADDR_DP_RX0_DAIZY_ST3_END()                         (PA_93_DAISY_CTRL_2)
#define RET_REG_ADDR_DP_RX1_DAIZY_ST3_START()                       (PA_92_DAISY_CTRL_1)
#define RET_REG_ADDR_DP_RX1_DAIZY_ST3_END()                         (PA_93_DAISY_CTRL_2)
//--------------------------------------------------
// Daisy Chain MTP Scheduler Related Register Macro
//--------------------------------------------------
#define GET_REG_DP_RX_DAIZY_ST3_START()                             (ScalerGetByte(PA_92_DAISY_CTRL_1) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST3_END()                               (ScalerGetByte(PA_93_DAISY_CTRL_2) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST4_START()                             (ScalerGetByte(PA_94_DAISY_CTRL_3) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST4_END()                               (ScalerGetByte(PA_95_DAISY_CTRL_4) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST5_START()                             (ScalerGetByte(PA_96_DAISY_CTRL_5) & 0x3F)
#define GET_REG_DP_RX_DAIZY_ST5_END()                               (ScalerGetByte(PA_97_DAISY_CTRL_6) & 0x3F)

#define SET_REG_DP_RX_DAISY_CHAIN_LANE_NUM(x)                       (ScalerSetBit(PA_91_DAISY_CTRL_0, ~(_BIT5 | _BIT4), ((x) << 4)))
#define SET_REG_DP_RX_DAIZY_ST3_START(x)                            (ScalerSetBit(PA_92_DAISY_CTRL_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST3_END(x)                              (ScalerSetBit(PA_93_DAISY_CTRL_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST4_START(x)                            (ScalerSetBit(PA_94_DAISY_CTRL_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST4_END(x)                              (ScalerSetBit(PA_95_DAISY_CTRL_4, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST5_START(x)                            (ScalerSetBit(PA_96_DAISY_CTRL_5, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_DAIZY_ST5_END(x)                              (ScalerSetBit(PA_97_DAISY_CTRL_6, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))

#define SET_REG_DP_RX_SEND_ACT_ENABLE()                             (ScalerSetBit(PA_91_DAISY_CTRL_0, ~_BIT1, _BIT1))
#define GET_REG_DP_RX_SEND_ACT_FLAG()                               ((bit)ScalerGetBit(PA_91_DAISY_CTRL_0, _BIT0))
#define CLR_REG_DP_RX_SEND_ACT_FLAG()                               (ScalerSetBit(PA_91_DAISY_CTRL_0, ~_BIT0, _BIT0))

//--------------------------------------------------
// Definitions of Down Request Related Register Macro
//--------------------------------------------------
#define SET_REG_DP_RX_DOWN_REQUEST_MSG_D0_SUPPORT_ENABLE()          (ScalerSetBit(PB7_00_AUX_RX_MSG_RX_CTRL, ~_BIT6, 0x00))
#define SET_REG_DP_RX_DOWN_REQUEST_MSG_D1_SUPPORT_ENABLE()          (ScalerSetBit(PB7_00_AUX_RX_MSG_RX_CTRL, ~_BIT6, _BIT6))
#define SET_REG_DP_RX_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE()  (ScalerSetBit(PB7_00_AUX_RX_MSG_RX_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_REG_DP_RX_DOWN_REQUEST_MSG_RECEIVE_CRC_IGNORE_ENABLE()  (ScalerSetBit(PB7_00_AUX_RX_MSG_RX_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00))
#define CLR_REG_DP_RX_DOWN_REQUEST_MSG_FINISH()                     (ScalerSetByte(PB7_02_MSG_RX_FINISH, 0xFF))
#define CLR_REG_DP_RX_DOWN_REQUEST_MSG_ERROR()                      (ScalerSetByte(PB7_03_MSG_RX_FLAG, 0xFF))
#define SET_REG_DP_RX_DOWN_REQUEST_MSG_DOUBLE_BUFFER_ENABLE()       (ScalerSetBit(PB7_04_MSG_RX_BUF_CLR, ~_BIT6, _BIT6))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF0_BUF1()                      (ScalerSetBit(PB7_04_MSG_RX_BUF_CLR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define RST_REG_DP_RX_DOWN_REQUEST_FSM_WRITTEN()                    (ScalerSetBit(PB7_1B_MSG_EXCEPT_CTRL0, ~_BIT7, _BIT7))

#define SET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_RECEIVE_ENABLE()        (ScalerSetBit(PB7_00_AUX_RX_MSG_RX_CTRL, ~_BIT0, _BIT0))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH()                (ScalerGetBit(PB7_02_MSG_RX_FINISH, _BIT0))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_FINISH()                (ScalerSetBit(PB7_02_MSG_RX_FINISH, ~(_BIT4 | _BIT0), _BIT0))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_LENGTH()                (ScalerGetByte(PB7_10_MSG_RX_BUF0_LEN) & 0x7F)
#define GET_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_ERROR()                 (ScalerGetBit(PB7_03_MSG_RX_FLAG, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF0_MSG_ERROR()                 (ScalerSetBit(PB7_03_MSG_RX_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_DOWN_REQUEST_BUF0_READ_PTR(x)                 (ScalerSetBit(PB7_12_MSG_RX_BUF0_RDPTR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF0_DATA()                      (ScalerGetByte(PB7_13_MSG_RX_BUF0_RD_DATA))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF0()                           (ScalerSetBit(PB7_04_MSG_RX_BUF_CLR, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1)))

#define GET_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN()                   ((bit)ScalerGetBit(PB7_1B_MSG_EXCEPT_CTRL0, _BIT0))
#define CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN()                   (ScalerSetBit(PB7_1B_MSG_EXCEPT_CTRL0, ~_BIT0, _BIT0))

#define SET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_RECEIVE_ENABLE()        (ScalerSetBit(PB7_00_AUX_RX_MSG_RX_CTRL, ~_BIT1, _BIT1))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH()                ((ScalerGetBit(PB7_02_MSG_RX_FINISH, _BIT4)) >> 4)
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_FINISH()                (ScalerSetBit(PB7_02_MSG_RX_FINISH, ~(_BIT4 | _BIT0), _BIT4))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_LENGTH()                (ScalerGetByte(PB7_14_MSG_RX_BUF1_LEN) & 0x7F)
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_ERROR()                 (ScalerGetBit(PB7_03_MSG_RX_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF1_MSG_ERROR()                 (ScalerSetBit(PB7_03_MSG_RX_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define SET_REG_DP_RX_DOWN_REQUEST_BUF1_READ_PTR(x)                 (ScalerSetBit(PB7_16_MSG_RX_BUF1_RDPTR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_WRITE_PTR()                 (ScalerGetByte(PB7_15_MSG_RX_BUF1_WRPTR))
#define GET_REG_DP_RX_DOWN_REQUEST_BUF1_DATA()                      (ScalerGetByte(PB7_17_MSG_RX_BUF1_RD_DATA))
#define CLR_REG_DP_RX_DOWN_REQUEST_BUF1()                           (ScalerSetBit(PB7_04_MSG_RX_BUF_CLR, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0)))

#define GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT()                        (ScalerGetBit(PB7_05_MSG_RX_DATA0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
#define GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR()                        (ScalerGetBit(PB7_05_MSG_RX_DATA0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_MSG_BYPASS_PORT_NUM()            ((ScalerGetBit(PB7_06_MSG_RX_DATA1, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> 4)
#define GET_REG_DP_RX_DOWN_REQUEST_RAD_MSB(x)                       (ScalerGetBit((PB7_06_MSG_RX_DATA1 + (x)), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD_LSB(x)                       (ScalerGetBit((PB7_06_MSG_RX_DATA1 + (x)), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD0()                           (ScalerGetBit(PB7_06_MSG_RX_DATA1, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD1()                           (ScalerGetBit(PB7_06_MSG_RX_DATA1, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD2()                           (ScalerGetBit(PB7_07_MSG_RX_DATA2, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD3()                           (ScalerGetBit(PB7_07_MSG_RX_DATA2, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD4()                           (ScalerGetBit(PB7_08_MSG_RX_DATA3, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD5()                           (ScalerGetBit(PB7_08_MSG_RX_DATA3, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD6()                           (ScalerGetBit(PB7_09_MSG_RX_DATA4, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_RX_DOWN_REQUEST_RAD7()                           (ScalerGetBit(PB7_09_MSG_RX_DATA4, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))


#define GET_REG_DP_RX_DOWN_REQUEST_MSG_BROADCAST()                  (ScalerGetBit(PB7_0D_MSG_RX_DATA8, _BIT7))
#define GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH()                       (ScalerGetBit(PB7_0D_MSG_RX_DATA8, _BIT6))
#define GET_REG_DP_RX_DOWN_REQUEST_MSG_MSN()                        (ScalerGetBit(PB7_0E_MSG_RX_DATA9, _BIT4))

#define SET_REG_DP_RX_DOWN_REQUEST_HEADER0_INFO()                   (ScalerSetBit(PB7_04_MSG_RX_BUF_CLR, ~_BIT4, 0x00))
#define SET_REG_DP_RX_DOWN_REQUEST_HEADER1_INFO()                   (ScalerSetBit(PB7_04_MSG_RX_BUF_CLR, ~_BIT4, _BIT4))


//--------------------------------------------------
// Definitions of Down Reply Related Register Macro
//--------------------------------------------------
#define GET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ()                    ((bit)ScalerGetBit(PB7_40_AUX_RX_MSG_TX_CTRL, _BIT5))
#define SET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ()                    (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~_BIT5, _BIT5))
#define CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ()                    (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~_BIT5, 0x00))

#define GET_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ_FLAG()               ((bit)ScalerGetBit(PB7_41_MSG_TX_FINISH, _BIT2))
#define CLR_REG_DP_RX_DOWN_REPLY_READY_BIT_IRQ_FLAG()               (ScalerSetBit(PB7_41_MSG_TX_FINISH, ~_BIT2, _BIT2))

#define GET_REG_DP_RX_DOWN_REPLY_BUFFER_END_FLAG()                  ((bit)ScalerGetBit(PB7_52_BUF_END_FLAG, _BIT0))
#define CLR_REG_DP_RX_DOWN_REPLY_BUFFER_END_FLAG()                  (ScalerSetBit(PB7_52_BUF_END_FLAG, ~_BIT0, _BIT0))
//--------------------------------------------------
// Definitions of Up Request Related Register Macro
//--------------------------------------------------
#define GET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ()                    ((bit)ScalerGetBit(PB7_40_AUX_RX_MSG_TX_CTRL, _BIT6))
#define SET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ()                    (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~_BIT6, _BIT6))
#define CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ()                    (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~_BIT6, 0x00))

#define GET_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ_FLAG()               ((bit)ScalerGetBit(PB7_41_MSG_TX_FINISH, _BIT3))
#define CLR_REG_DP_RX_UP_REQUEST_READY_BIT_IRQ_FLAG()               (ScalerSetBit(PB7_41_MSG_TX_FINISH, ~_BIT3, _BIT3))

//--------------------------------------------------
// Definitions of Upstream Reply RelatedRegister Macro
//--------------------------------------------------
#define CLR_REG_DP_RX_DOWN_REPLY_UP_REQUEST_READY_BIT_IRQ()         (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~(_BIT6 | _BIT5), 0x00))

#define SET_REG_DP_RX_UPSTREAM_REPLY()                              (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~_BIT0, _BIT0))
#define CLR_REG_DP_RX_UPSTREAM_REPLY()                              (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~_BIT0, 0x00))
#define SET_REG_DP_RX_UPSTREAM_HW_AUTO_MODE()                       (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~_BIT2, 0x00))
#define SET_REG_DP_RX_UPSTREAM_HW_MANUAL_MODE()                     (ScalerSetBit(PB7_40_AUX_RX_MSG_TX_CTRL, ~_BIT2, _BIT2))
#define SET_REG_DP_RX_UPSTREAM_START_BIT()                          (ScalerSetBit(PB7_4C_MSG_TX_SET9, ~_BIT7, _BIT7))
#define CLR_REG_DP_RX_UPSTREAM_START_BIT()                          (ScalerSetBit(PB7_4C_MSG_TX_SET9, ~_BIT7, 0x00))
#define SET_REG_DP_RX_UPSTREAM_END_BIT()                            (ScalerSetBit(PB7_4C_MSG_TX_SET9, ~_BIT6, _BIT6))
#define CLR_REG_DP_RX_UPSTREAM_END_BIT()                            (ScalerSetBit(PB7_4C_MSG_TX_SET9, ~_BIT6, 0x00))
#define SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(x)                      (ScalerSetByte(PB7_42_MSG_TX_LENGTH, (x)))
#define GET_REG_DP_RX_UPSTREAM_REPLY_LENGTH()                       (ScalerGetByte(PB7_42_MSG_TX_LENGTH))
#define SET_REG_DP_RX_UPSTREAM_REPLY_LCT(x)                         (ScalerSetBit(PB7_43_MSG_TX_SET0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define GET_REG_DP_RX_UPSTREAM_REPLY_LCT()                          ((ScalerGetBit(PB7_43_MSG_TX_SET0, (_BIT7 | _BIT6 | _BIT5 | _BIT4))) >> 4)
#define SET_REG_DP_RX_UPSTREAM_REPLY_LCR(x)                         (ScalerSetBit(PB7_43_MSG_TX_SET0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_UPSTREAM_REPLY_LCR()                          (ScalerGetBit(PB7_43_MSG_TX_SET0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD0(x)                        (ScalerSetBit(PB7_44_MSG_TX_SET1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD1(x)                        (ScalerSetBit(PB7_44_MSG_TX_SET1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD2(x)                        (ScalerSetBit(PB7_45_MSG_TX_SET2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD3(x)                        (ScalerSetBit(PB7_45_MSG_TX_SET2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD4(x)                        (ScalerSetBit(PB7_46_MSG_TX_SET3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD5(x)                        (ScalerSetBit(PB7_46_MSG_TX_SET3, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD6(x)                        (ScalerSetBit(PB7_47_MSG_TX_SET4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_RAD7(x)                        (ScalerSetBit(PB7_47_MSG_TX_SET4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(x)                   (ScalerSetBit(PB7_4B_MSG_TX_SET8, ~_BIT7, ((BYTE)((bit)(x)) << 7)))
#define SET_REG_DP_RX_UPSTREAM_REPLY_PATH(x)                        (ScalerSetBit(PB7_4B_MSG_TX_SET8, ~_BIT6, ((BYTE)((bit)(x)) << 6)))
#define GET_REG_DP_RX_UPSTREAM_REPLY_MSN()                          (ScalerGetBit(PB7_4C_MSG_TX_SET9, _BIT4))
#define SET_REG_DP_RX_UPSTREAM_REPLY_MSN(x)                         (ScalerSetBit(PB7_4C_MSG_TX_SET9, ~_BIT4, ((BYTE)((bit)(x)) << 4)))
#define CLR_REG_DP_RX_USTERAM_REPLY_BUF()                           (ScalerSetBit(PB7_4F_BUF_CLR, ~_BIT0, _BIT0))
#define CLR_REG_DP_RX_UPSTREAM_REPLY_WRITE_PTR()                    (ScalerSetByte(PB7_50_BUF_FW_WRPTR, 0x00))
#define SET_REG_DP_RX_UPSTREAM_REPLY_BUF_DATA(x)                    (ScalerSetByte(PB7_51_BUF_FW_WR_DATA, (x)))
#define GET_REG_DP_RX_UPSTREAM_TRANSITION_ADDRESS()                 (ScalerGetBit(PB7_4D_MSG_TX_ADR_SEL, _BIT0))
#define SET_REG_DP_RX_UPSTREAM_REPLY_DOWN_REPLY_ADDRESS()           (ScalerSetBit(PB7_4D_MSG_TX_ADR_SEL, ~_BIT0, 0x00))
#define SET_REG_DP_RX_UPSTREAM_REPLY_UP_REQUEST_ADDRESS()           (ScalerSetBit(PB7_4D_MSG_TX_ADR_SEL, ~_BIT0, _BIT0))


//--------------------------------------------------
// Definitions of Up Reply Related Register Macro
//--------------------------------------------------
#define SET_REG_DP_RX_UP_REPLY_MSG_RECEIVE_CRC_IGNORE_ENABLE()      (ScalerSetBit(PB7_20_AUX_RX_MSG_RX_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_REG_DP_RX_UP_REPLY_MSG_RECEIVE_CRC_IGNORE_ENABLE()      (ScalerSetBit(PB7_20_AUX_RX_MSG_RX_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00))

#define SET_REG_DP_RX_UP_REPLY_BUF0_MSG_RECEIVE_ENABLE()            (ScalerSetBit(PB7_20_AUX_RX_MSG_RX_CTRL, ~_BIT0, _BIT0))
#define GET_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH()                    (ScalerGetBit(PB7_22_MSG_RX_FINISH, _BIT0))
#define CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_FINISH()                    (ScalerSetBit(PB7_22_MSG_RX_FINISH, ~(_BIT4 | _BIT0), _BIT0))
#define GET_REG_DP_RX_UP_REPLY_BUF0_MSG_LENGTH()                    (ScalerGetByte(PB7_30_MSG_RX_BUF0_LEN) & 0x7F)
#define GET_REG_DP_RX_UP_REPLY_BUF0_MSG_ERROR()                     (ScalerGetBit(PB7_23_MSG_RX_FLAG, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define CLR_REG_DP_RX_UP_REPLY_BUF0_MSG_ERROR()                     (ScalerSetBit(PB7_23_MSG_RX_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define SET_REG_DP_RX_UP_REPLY_BUF0_RDAD_PTR(x)                     (ScalerSetBit(PB7_32_MSG_RX_BUF0_RDPTR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_UP_REPLY_BUF0_DATA()                          (ScalerGetByte(PB7_33_MSG_RX_BUF0_RD_DATA))
#define CLR_REG_DP_RX_UP_REPLY_BUF0()                               (ScalerSetBit(PB7_24_MSG_RX_BUF_CLR, ~(_BIT3 | _BIT1), (_BIT3 | _BIT1)))

#define GET_REG_DP_RX_UP_REPLY_ADDR_WRITTEN()                       ((bit)ScalerGetBit(PB7_3B_MSG_EXCEPT_CTRL0, _BIT0))
#define CLR_REG_DP_RX_UP_REPLY_ADDR_WRITTEN()                       (ScalerSetBit(PB7_3B_MSG_EXCEPT_CTRL0, ~_BIT0, _BIT0))

#define SET_REG_DP_RX_UP_REPLY_BUF1_MSG_REVEIVE_ENABLE()            (ScalerSetBit(PB7_20_AUX_RX_MSG_RX_CTRL, ~_BIT1, _BIT1))
#define GET_REG_DP_RX_UP_REPLY_BUF1_MSG_FINISH()                    ((ScalerGetBit(PB7_22_MSG_RX_FINISH, _BIT4)) >> 4)
#define CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_FINISH()                    (ScalerSetBit(PB7_22_MSG_RX_FINISH, ~(_BIT4 | _BIT0), _BIT4))
#define GET_REG_DP_RX_UP_REPLY_BUF1_MSG_LENGTH()                    (ScalerGetByte(PB7_34_MSG_RX_BUF1_LEN) & 0x7F)
#define GET_REG_DP_RX_UP_REPLY_BUF1_MSG_ERROR()                     (ScalerGetBit(PB7_23_MSG_RX_FLAG, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define CLR_REG_DP_RX_UP_REPLY_BUF1_MSG_ERROR()                     (ScalerSetBit(PB7_23_MSG_RX_FLAG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define SET_REG_DP_RX_UP_REPLY_BUF1_RDAD_PTR(x)                     (ScalerSetBit(PB7_36_MSG_RX_BUF1_RDPTR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define GET_REG_DP_RX_UP_REPLY_BUF1_WRITE_PTR()                     (ScalerGetByte(PB7_35_MSG_RX_BUF1_WRPTR))
#define GET_REG_DP_RX_UP_REPLY_BUF1_DATA()                          (ScalerGetByte(PB7_37_MSG_RX_BUF1_RD_DATA))
#define CLR_REG_DP_RX_UP_REPLY_BUF1()                               (ScalerSetBit(PB7_24_MSG_RX_BUF_CLR, ~(_BIT2 | _BIT0), (_BIT2 | _BIT0)))

#define SET_REG_DP_RX_UP_REPLY_HEADER0_INFO()                       (ScalerSetBit(PB7_24_MSG_RX_BUF_CLR, ~_BIT4, 0x00))
#define SET_REG_DP_RX_UP_REPLY_HEADER1_INFO()                       (ScalerSetBit(PB7_24_MSG_RX_BUF_CLR, ~_BIT4, _BIT4))


//--------------------------------------------------
// Definitions of Rx MST2SST Watch Dog Macro
//--------------------------------------------------
#define SET_REG_DP_RX_MST2SST_WATCH_DOG_ENABLE()                    {\
                                                                        (ScalerSetBit(PA_7A_MST2SST_IRQ, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2)));\
                                                                    }
#define CLR_REG_DP_RX_MST2SST_WATCH_DOG_ENABLE()                    {\
                                                                        (ScalerSetBit(PA_7A_MST2SST_IRQ, ~(_BIT3 | _BIT2), 0x00));\
                                                                    }

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
