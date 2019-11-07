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
// ID Code      : ScalerMcuInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Macros of MCU Watch Dog
//--------------------------------------------------
#define CLR_MCU_WATCH_DOG()                            (MCU_FFEA_WATCHDOG_TIMER |= _BIT6)

//--------------------------------------------------
// Macros of DDC-CI0
//--------------------------------------------------
#define GET_DDCCI0_SLAVE_ADDRESS()                     (MCU_FF23_IIC_SET_SLAVE & 0xFE)
#define GET_DDCCI0_SUBADDRESS()                        (MCU_FF24_IIC_SUB_IN)
#define GET_DDCCI0_DATA_IN()                           (MCU_FF25_IIC_DATA_IN)
#define GET_DDCCI0_STATUS1()                           (MCU_FF27_IIC_STATUS)
#define GET_DDCCI0_STATUS2()                           (MCU_FF29_IIC_STATUS2)
#define GET_DDCCI0_IRQ_STATUS()                        (MCU_FF2A_IIC_IRQ_CONTROL2)

#define SET_DDCCI0_SLAVE_ADDRESS(x)                    (MCU_FF23_IIC_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI0_DATA_OUT(x)                         (MCU_FF26_IIC_DATA_OUT = (x))
#define CLR_DDCCI0_STATUS1(x)                          (MCU_FF27_IIC_STATUS &= ~(x))
#define SET_DDCCI0_STATUS2(x)                          (MCU_FF29_IIC_STATUS2 = (x))
#define SET_DDCCI0_IRQ_STATUS(x)                       (MCU_FF2A_IIC_IRQ_CONTROL2 = (x))
#define GET_DDCCI0_DDC_CHANNEL()                       (MCU_FF22_IIC_CH_SEL & (_BIT2 | _BIT1 | _BIT0))

//--------------------------------------------------
// MACRO for DDC CI Command status
//--------------------------------------------------
#define GET_RUN_DDCCI_COMMAND()                        ((bit)g_ucRunDdcciCommand)
#define CLR_RUN_DDCCI_COMMAND(x)                       (g_ucRunDdcciCommand &= (~(_BIT0 << (x))))

//--------------------------------------------------
// MACRO for DDC CI 0 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI0_COMMAND(x)                      (g_ucRunDdcciCommand = ((g_ucRunDdcciCommand & (~_BIT0)) | (x)))
#define GET_RUN_DDCCI0_COMMAND()                       ((bit)(g_ucRunDdcciCommand & _BIT0))

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// MACRO for DDC CI 1 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI1_COMMAND(x)                      (g_ucRunDdcciCommand = ((g_ucRunDdcciCommand & (~_BIT1)) | ((x) << 1)))
#define GET_RUN_DDCCI1_COMMAND()                       ((bit)(g_ucRunDdcciCommand & _BIT1))
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// MACRO for DDC CI 2 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI2_COMMAND(x)                      (g_ucRunDdcciCommand = ((g_ucRunDdcciCommand & (~_BIT2)) | ((x) << 2)))
#define GET_RUN_DDCCI2_COMMAND()                       ((bit)(g_ucRunDdcciCommand & _BIT2))

//--------------------------------------------------
// MACRO for DDC CI 3 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI3_COMMAND(x)                      (g_ucRunDdcciCommand = ((g_ucRunDdcciCommand & (~_BIT3)) | ((x) << 3)))
#define GET_RUN_DDCCI3_COMMAND()                       ((bit)(g_ucRunDdcciCommand & _BIT3))
#endif

//--------------------------------------------------
// MACRO for DDC CI For Auto Switch Channel Command status
//--------------------------------------------------
#define GET_RUN_DDCCI_AUTO_CHANNEL_COMMAND()           ((bit)(g_ucRunDdcciCommand & _BIT0))

//--------------------------------------------------
// MACRO for Current handle ddcci channel inx
//--------------------------------------------------
#define GET_RUN_DDCCI_HANDLE_CHANNEL()                 (g_ucDDCCIHandlerInx)
#define SET_RUN_DDCCI_HANDLE_CHANNEL(x)                (g_ucDDCCIHandlerInx = (x))


#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Macros of DDC-CI1
//--------------------------------------------------
#define GET_DDCCI1_SLAVE_ADDRESS()                     (MCU_FE87_IIC_1_SET_SLAVE & 0xFE)
#define GET_DDCCI1_SUBADDRESS()                        (MCU_FE88_IIC_1_SUB_IN)
#define GET_DDCCI1_DATA_IN()                           (MCU_FE89_IIC_1_DATA_IN)
#define GET_DDCCI1_STATUS1()                           (MCU_FE8B_IIC_1_STATUS)
#define GET_DDCCI1_STATUS2()                           (MCU_FE8D_IIC_1_STATUS2)
#define GET_DDCCI1_IRQ_STATUS()                        (MCU_FE8E_IIC_1_IRQ_CONTROL2)

#define SET_DDCCI1_SLAVE_ADDRESS(x)                    (MCU_FE87_IIC_1_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI1_DATA_OUT(x)                         (MCU_FE8A_IIC_1_DATA_OUT = (x))
#define CLR_DDCCI1_STATUS1(x)                          (MCU_FE8B_IIC_1_STATUS &= ~(x))
#define SET_DDCCI1_STATUS2(x)                          (MCU_FE8D_IIC_1_STATUS2 = (x))
#define SET_DDCCI1_IRQ_STATUS(x)                       (MCU_FE8E_IIC_1_IRQ_CONTROL2 = (x))
#define GET_DDCCI1_DDC_CHANNEL()                       (MCU_FE86_IIC_1_CH_SEL & (_BIT2 | _BIT1 | _BIT0))
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Macros of DDC-CI2
//--------------------------------------------------
#define GET_DDCCI2_SLAVE_ADDRESS()                     (MCU_FE95_IIC_2_SET_SLAVE & 0xFE)
#define GET_DDCCI2_SUBADDRESS()                        (MCU_FE96_IIC_2_SUB_IN)
#define GET_DDCCI2_DATA_IN()                           (MCU_FE97_IIC_2_DATA_IN)
#define GET_DDCCI2_STATUS1()                           (MCU_FE99_IIC_2_STATUS)
#define GET_DDCCI2_STATUS2()                           (MCU_FE9B_IIC_2_STATUS2)
#define GET_DDCCI2_IRQ_STATUS()                        (MCU_FE9C_IIC_2_IRQ_CONTROL2)

#define SET_DDCCI2_SLAVE_ADDRESS(x)                    (MCU_FE95_IIC_2_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI2_DATA_OUT(x)                         (MCU_FE98_IIC_2_DATA_OUT = (x))
#define CLR_DDCCI2_STATUS1(x)                          (MCU_FE99_IIC_2_STATUS &= ~(x))
#define SET_DDCCI2_STATUS2(x)                          (MCU_FE9B_IIC_2_STATUS2 = (x))
#define SET_DDCCI2_IRQ_STATUS(x)                       (MCU_FE9C_IIC_2_IRQ_CONTROL2 = (x))
#define GET_DDCCI2_DDC_CHANNEL()                       (MCU_FE94_IIC_2_CH_SEL & (_BIT2 | _BIT1 | _BIT0))

//--------------------------------------------------
// Macros of DDC-CI3
//--------------------------------------------------
#define GET_DDCCI3_SLAVE_ADDRESS()                     (MCU_FEA4_IIC_3_SET_SLAVE & 0xFE)
#define GET_DDCCI3_SUBADDRESS()                        (MCU_FEA5_IIC_3_SUB_IN)
#define GET_DDCCI3_DATA_IN()                           (MCU_FEA6_IIC_3_DATA_IN)
#define GET_DDCCI3_STATUS1()                           (MCU_FEA8_IIC_3_STATUS)
#define GET_DDCCI3_STATUS2()                           (MCU_FEAA_IIC_3_STATUS2)
#define GET_DDCCI3_IRQ_STATUS()                        (MCU_FEAB_IIC_3_IRQ_CONTROL2)

#define SET_DDCCI3_SLAVE_ADDRESS(x)                    (MCU_FEA4_IIC_3_SET_SLAVE = ((x) & 0xFE))
#define SET_DDCCI3_DATA_OUT(x)                         (MCU_FEA7_IIC_3_DATA_OUT = (x))
#define CLR_DDCCI3_STATUS1(x)                          (MCU_FEA8_IIC_3_STATUS &= ~(x))
#define SET_DDCCI3_STATUS2(x)                          (MCU_FEAA_IIC_3_STATUS2 = (x))
#define SET_DDCCI3_IRQ_STATUS(x)                       (MCU_FEAB_IIC_3_IRQ_CONTROL2 = (x))
#define GET_DDCCI3_DDC_CHANNEL()                       (MCU_FEA3_IIC_3_CH_SEL & (_BIT2 | _BIT1 | _BIT0))
#endif

//--------------------------------------------------
// Macros of 5us Delay
//--------------------------------------------------
#define Delay5us(N)                                    {\
                                                            g_ucDelay5usI = (N);\
                                                            while(--g_ucDelay5usI) {};\
                                                       }

//--------------------------------------------------
// Macros of SW IIC Status
//--------------------------------------------------
#if(_SW_IIC_SUPPORT == _ON)
#define GET_SW_IIC_STATUS()                            (g_ucSwIICStatus)
#define SET_SW_IIC_STATUS(x)                           (g_ucSwIICStatus = (x))
#endif

//--------------------------------------------------
// Macros of UART Status
//--------------------------------------------------
#if(_UART_SUPPORT == _ON)
#define GET_UART_TRANSMIT_STATUS()                     (TI)
#define CLR_UART_TRANSMIT_STATUS()                     (TI = 0)

#define GET_UART_RECEIVE_STATUS()                      (RI)
#define CLR_UART_RECEIVE_STATUS()                      (RI = 0)

#define GET_UART_DATA()                                (SBUF)
#endif

//--------------------------------------------------
// Macros of DDC-CI
//--------------------------------------------------
#define GET_DDCCI_AUTO_SWITCH()                        ((bit)(MCU_FF2A_IIC_IRQ_CONTROL2 & _BIT4))
#define SET_DDCCI_AUTO_SWITCH()                        (MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT4)
#define CLR_DDCCI_AUTO_SWITCH()                        (MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT4)

//--------------------------------------------------
// Macros of relocatable user bank
//--------------------------------------------------
#define SET_BANK_SWITCH_OFFSET(x)                      (g_ucBankOffset = (x))


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************

extern BYTE data g_ucDelay5usN;
extern BYTE data g_ucDelay5usI;
extern BYTE data g_ucDelay5usI_EXINT;

#if(_SW_IIC_SUPPORT == _ON)
extern BYTE idata g_ucSwIICStatus;
#endif

#if(_A0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_A0[_A0_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
#if((_D7_INPUT_PORT_TYPE == _D7_DP_PORT) && (_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
extern BYTE xdata MCU_DDCRAM_D0[_D7_D0_EMBEDDED_DDCRAM_SIZE];
#else
extern BYTE xdata MCU_DDCRAM_D0[_D0_EMBEDDED_DDCRAM_SIZE];
#endif
#endif

#if(_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
#if((_D7_INPUT_PORT_TYPE == _D7_DP_PORT) && (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
extern BYTE xdata MCU_DDCRAM_D1[_D7_D1_EMBEDDED_DDCRAM_SIZE];
#else
extern BYTE xdata MCU_DDCRAM_D1[_D1_EMBEDDED_DDCRAM_SIZE];
#endif
#endif

#if(_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D2[_D2_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D3_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D3[_D3_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D4_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D4[_D4_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D5_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D5[_D5_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D6[_D6_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D0[_D0_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D1[_D1_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D2[_D2_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D3[_D3_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D4[_D4_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

#if(_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_MHL_D5[_D5_MHL_EMBEDDED_DDCRAM_SIZE];
#endif

extern BYTE g_ucRunDdcciCommand;

extern BYTE g_pucDdcciRxBuf[_DDCCI0_RXBUF_LENGTH];
extern BYTE g_pucDdcciTxBuf[_DDCCI_TXBUF_LENGTH];

extern BYTE g_pucDdcciGroupRxBuf[_MULTI_DISPLAY_MAX][_DDCCI_RXBUF_LENGTH];
extern BYTE g_ucDDCCIHandlerInx;

#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)
extern BYTE data g_ucBankOffset;
#endif

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerMcuInitial(void);

extern void ScalerMcuDdcciSendData(EnumDDCCIPort enumDdcciChannel, BYTE *pucWriteArray);
extern BYTE ScalerMcuDdcciGetInputPort(EnumDDCCIPort enumDdcciChannel);
extern void ScalerMcuDdcciSelectDdcChannel(EnumDDCCIPort enumDdcciChannel, BYTE ucInputPort);

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern BYTE ScalerMcuDdcci0IntGetData_EXINT1(BYTE *pucReadArray, BYTE ucBufLength);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern BYTE ScalerMcuDdcci1IntGetData_EXINT1(BYTE *pucReadArray);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
extern BYTE ScalerMcuDdcci2IntGetData_EXINT1(BYTE *pucReadArray);
extern BYTE ScalerMcuDdcci3IntGetData_EXINT1(BYTE *pucReadArray);
#endif

#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
extern void ScalerMcuDdcciReleaseScl(EnumDDCCIPort enumDDCCIPort);
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern void ScalerMcuDdcciHoldScl_EXINT1(EnumDDCCIPort enumDDCCIPort);
#endif
#endif

extern BYTE ScalerMcuDdcciGetBufferSize(void);

extern void ScalerMcuFlashClockDiv(EnumFlashClkDiv enumClkDiv);
extern void ScalerMcuClockDiv(EnumMcuClkDiv enumClkDiv);
extern void ScalerMcuClockSel(EnumClkSel enumClock);

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
extern void ScalerMcuSwitchFlashMcuFastSpeed(bit bEnable);
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
extern void ScalerMcuIntoIdle(void);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
extern void ScalerMcuSarAdcClkSel(EnumClkSel enumClock);
#endif

#if(_PWM_FUNCTION_SUPPORT == _ON)
extern void ScalerMcuPwmClockSel(EnumClkSel enumClock);
extern void ScalerMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency);
#endif

extern void ScalerMcu5usDelayCalc(EnumClkSel enumClock);

#if(_SW_IIC_SUPPORT == _ON)
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuIICWritePolling(BYTE ucSlaveAddr);
#endif
extern bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

#if(_HW_IIC_SUPPORT == _ON)
extern void ScalerMcuHwIICSetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
extern bit ScalerMcuHwIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
extern bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
extern bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

#if(_UART_SUPPORT == _ON)
extern bit ScalerMcuUartWrite(BYTE ucValue);
#endif

extern void ScalerMcuPwmControl(EnumPowerStatus enumPowStatus);

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
extern void ScalerMcuBootInitial(void);
#endif

extern void ScalerMcuCacheInitial(void);
extern void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode);

