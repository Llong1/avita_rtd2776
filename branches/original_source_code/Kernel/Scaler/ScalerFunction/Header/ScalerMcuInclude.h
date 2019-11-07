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
// ID Code      : ScalerMcuInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Macros of 5us Delay
//--------------------------------------------------
#define Delay5us(N)                                  {\
                                                         g_ucDelay5usI = (N);\
                                                         while(--g_ucDelay5usI) {};\
                                                     }

#define Delay5us_EXINT(N)                            {\
                                                         g_ucDelay5usI_EXINT = (N);\
                                                         while(--g_ucDelay5usI_EXINT) {};\
                                                     }

//--------------------------------------------------
// Macros of SW IIC Status
//--------------------------------------------------
#if(_SW_IIC_SUPPORT == _ON)
#define GET_SW_IIC_STATUS()                          (g_ucSwIICStatus)
#define SET_SW_IIC_STATUS(x)                         (g_ucSwIICStatus = (x))
#endif

//--------------------------------------------------
// MACRO for DDC CI Command status
//--------------------------------------------------
#define GET_RUN_DDCCI_COMMAND()                      ((bit)g_ucRunDdcciCommand)
#define CLR_RUN_DDCCI_COMMAND(x)                     (g_ucRunDdcciCommand &= (~(_BIT0 << (x))))

//--------------------------------------------------
// MACRO for DDC CI 0 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI0_COMMAND(x)                    (g_ucRunDdcciCommand = ((g_ucRunDdcciCommand & (~_BIT0)) | (x)))
#define GET_RUN_DDCCI0_COMMAND()                     ((bit)(g_ucRunDdcciCommand & _BIT0))

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// MACRO for DDC CI 1 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI1_COMMAND(x)                    (g_ucRunDdcciCommand = ((g_ucRunDdcciCommand & (~_BIT1)) | ((x) << 1)))
#define GET_RUN_DDCCI1_COMMAND()                     ((bit)(g_ucRunDdcciCommand & _BIT1))
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// MACRO for DDC CI 2 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI2_COMMAND(x)                    (g_ucRunDdcciCommand = ((g_ucRunDdcciCommand & (~_BIT2)) | ((x) << 2)))
#define GET_RUN_DDCCI2_COMMAND()                     ((bit)(g_ucRunDdcciCommand & _BIT2))

//--------------------------------------------------
// MACRO for DDC CI 3 Channel Command status
//--------------------------------------------------
#define SET_RUN_DDCCI3_COMMAND(x)                    (g_ucRunDdcciCommand = ((g_ucRunDdcciCommand & (~_BIT3)) | ((x) << 3)))
#define GET_RUN_DDCCI3_COMMAND()                     ((bit)(g_ucRunDdcciCommand & _BIT3))
#endif

//--------------------------------------------------
// MACRO for DDC CI For Auto Switch Channel Command status
//--------------------------------------------------
#define GET_RUN_DDCCI_AUTO_CHANNEL_COMMAND()         ((bit)(g_ucRunDdcciCommand & _BIT0))

//--------------------------------------------------
// MACRO for Current handle ddcci channel inx
//--------------------------------------------------
#define GET_RUN_DDCCI_HANDLE_CHANNEL()               (g_ucDDCCIHandlerInx)
#define SET_RUN_DDCCI_HANDLE_CHANNEL(x)              (g_ucDDCCIHandlerInx = (x))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern BYTE data g_ucDelay5usN;
extern BYTE data g_ucDelay5usI;
extern BYTE data g_ucDelay5usI_EXINT;

#if(_SW_IIC_SUPPORT == _ON)
extern BYTE idata g_ucSwIICStatus;
#endif

#if(_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D0_DDC_CHANNEL_SEL == _DDC0)
#if((_D7_INPUT_PORT_TYPE == _D7_DP_PORT) && (_D7_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
extern BYTE xdata MCU_DDCRAM_D0[_D7_D0_EMBEDDED_DDCRAM_SIZE];
#else
extern BYTE xdata MCU_DDCRAM_D0[_D0_EMBEDDED_DDCRAM_SIZE];
#endif
#endif // End of _DDC_CHANNEL_FOR_D0

#endif // End of #if(_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D1_DDC_CHANNEL_SEL == _DDC1)
#if((_D7_INPUT_PORT_TYPE == _D7_DP_PORT) && (_D7_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE))
extern BYTE xdata MCU_DDCRAM_D1[_D7_D1_EMBEDDED_DDCRAM_SIZE];
#else
extern BYTE xdata MCU_DDCRAM_D1[_D1_EMBEDDED_DDCRAM_SIZE];
#endif
#endif // End of _DDC_CHANNEL_FOR_D1

#endif // End of #if(_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

#if(_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)
extern BYTE xdata MCU_DDCRAM_D6[_D6_EMBEDDED_DDCRAM_SIZE];
#endif // End of #if(_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE)

extern BYTE g_ucRunDdcciCommand;

extern BYTE g_pucDdcciRxBuf[_DDCCI0_RXBUF_LENGTH];
extern BYTE g_pucDdcciTxBuf[_DDCCI_TXBUF_LENGTH];

extern BYTE g_pucDdcciGroupRxBuf[_MULTI_DISPLAY_MAX][_DDCCI_RXBUF_LENGTH];
extern BYTE g_ucDDCCIHandlerInx;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerMcuFlashClockDiv(EnumFlashClkDiv enumClkDiv);
extern void ScalerMcuClockDiv(EnumMcuClkDiv enumClkDiv);

#if(_SW_IIC_SUPPORT == _ON)
extern bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
extern bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

#if(_HW_IIC_SUPPORT == _ON)
extern bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
extern bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

extern void ScalerMcuIspInitial(void);

extern void ScalerMcuCacheInitial(void);
extern void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode);

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
extern void ScalerMcuDdcRamEDIDAddrSelect(EnumD0D1DDCRAMSelect enumDdcRamSel, EnumDDCAddrType enumDdcAddr);
#endif
