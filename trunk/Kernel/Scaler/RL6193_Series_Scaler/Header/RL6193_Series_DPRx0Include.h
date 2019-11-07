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
// ID Code      : RL6193_Series_DPRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX0_PHY_CTS_FLG()                        (!((bit)ScalerGetBit(PB_A7_CMU_07, _BIT0)))
#define SET_DP_RX0_PHY_CTS_FLG()                        (ScalerSetBit(PB_A7_CMU_07, ~_BIT0, 0x00))
#define CLR_DP_RX0_PHY_CTS_FLG()                        (ScalerSetBit(PB_A7_CMU_07, ~_BIT0, _BIT0))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_DP_TX_SUPPORT == _ON)
#define CLR_DP_RX0_HDCP_KSV_FIFO_INT_FLAG()             {\
                                                            ScalerSetBit(PB7_FA_DUMMY_0, ~_BIT2, _BIT2);\
                                                            ScalerSetBit(PB7_FA_DUMMY_0, ~_BIT2, 0x00);\
                                                        }

#define CLR_DP_RX0_HDCP_KSV_FIFO_INT_FLAG_EXINT()       {\
                                                            ScalerSetBit_EXINT(PB7_FA_DUMMY_0, ~_BIT2, _BIT2);\
                                                            ScalerSetBit_EXINT(PB7_FA_DUMMY_0, ~_BIT2, 0x00);\
                                                        }
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_pucDpRx0Tap0MaxTemp[4];
extern BYTE g_pucDpRx0LEMinTemp[4];
extern BYTE g_pucDpRx0LEMaxTemp[4];
extern BYTE g_pucDpRx0Tap1MaxTemp[4];
extern WORD g_usDpRx0ClockCount;
extern WORD g_usDpRx0ClockCount1;
extern BYTE g_pucDpRx0Backup[3];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx0ValidSignalDetection(void);
extern bit ScalerDpRx0DisplayFormatSetting(void);
extern bit ScalerDpRx0FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpRx0SetFifoWD(bit bEn);
extern void ScalerDpRx0SetFifoIRQ(bit bEn);
extern void ScalerDpRx0PhyCTS(void);
extern void ScalerDpRx0PhyInitial(void);
extern void ScalerDpRx0RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx0AuxIntInitial(void);
extern bit ScalerDpRx0CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx0SignalDetectInitial(BYTE ucDpLinkRate);
extern bit ScalerDpRx0MeasureLaneCDRClk(BYTE ucDpLinkRate, BYTE ucDpRx0LaneNumber);
extern void ScalerDpRx0HdcpCapableModify(void);

extern bit ScalerDpRx0MstToSstStreamClkRegenerate(void);
extern bit ScalerDpRx0MstToSstDisplayFormatSetting(void);
extern bit ScalerDpRx0MstToSstFifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern bit ScalerDpRx0MstToSstMeasureInput(void);

#endif

