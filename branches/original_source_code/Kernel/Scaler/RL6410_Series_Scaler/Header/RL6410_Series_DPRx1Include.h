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
// ID Code      : RL6410_Series_DPRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX1_PHY_CTS_FLG()                        (!((bit)ScalerGetBit(P7A_25_KOFFSET_01, _BIT5)))
#define SET_DP_RX1_PHY_CTS_FLG()                        (ScalerSetBit(P7A_25_KOFFSET_01, ~_BIT5, 0x00))
#define CLR_DP_RX1_PHY_CTS_FLG()                        (ScalerSetBit(P7A_25_KOFFSET_01, ~_BIT5, _BIT5))

#if(_DP_TX_SUPPORT == _ON)
#define CLR_DP_RX1_HDCP_KSV_FIFO_INT_FLAG()             {\
                                                            ScalerSetBit(PBA_FA_DUMMY_0, ~_BIT0, _BIT0);\
                                                        }

#define CLR_DP_RX1_HDCP_KSV_FIFO_INT_FLAG_EXINT()       {\
                                                            ScalerSetBit_EXINT(PBA_FA_DUMMY_0, ~_BIT0, _BIT0);\
                                                        }
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern WORD g_pusDpRx1ClockCount[4];
extern WORD g_pusDpRx1ClockCount1[4];
extern BYTE g_pucDpRx1Backup[3];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx1ValidSignalDetection(void);
extern bit ScalerDpRx1DisplayFormatSetting(void);
extern bit ScalerDpRx1FifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern void ScalerDpRx1SetFifoWD(bit bEn);
extern void ScalerDpRx1SetFifoIRQ(bit bEn);
extern void ScalerDpRx1PhyCTS(void);
extern void ScalerDpRx1PhyInitial(void);
extern void ScalerDpRx1RebuildPhy(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx1AuxIntInitial(void);
extern bit ScalerDpRx1CDRCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern void ScalerDpRx1SignalDetectInitial(BYTE ucDpLinkRate);
extern void ScalerDpRx1HdcpCapableModify(void);

#if(_DP_TX_SUPPORT == _ON)
extern BYTE ScalerDpRx1MstToSstScanInputPort(void);
extern bit ScalerDpRx1MstToSstMSAActiveChange(void);
extern bit ScalerDpRx1MstToSstMiscCheck(void);

extern bit ScalerDpRx1MstToSstFifoCheck(EnumDpFifoCheckCondition enumFifoCheckCondition);
extern bit ScalerDpRx1MstToSstMeasureInput(void);
#endif

#endif

