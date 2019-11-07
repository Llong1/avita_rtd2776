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
// ID Code      : RL6410_Series_TMDSRx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D2_TMDS_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_D2_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Macro of HDMI 2.0 Format Reset Check Wait
//--------------------------------------------------
#define GET_TMDS_RX2_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx2CtrlInfo.b1HDMI2FormatResetWaiting)
#define SET_TMDS_RX2_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx2CtrlInfo.b1HDMI2FormatResetWaiting = _TRUE)
#define CLR_TMDS_RX2_HDMI_2_0_FORMAT_RESET_WAITING()    (g_stTMDSRx2CtrlInfo.b1HDMI2FormatResetWaiting = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 Read Request Enable Flag
//--------------------------------------------------
#define GET_HDMI_2_0_RX2_RR_ENABLE()                    (g_stTMDSRx2CtrlInfo.b1HDMI2RREnable)
#define SET_HDMI_2_0_RX2_RR_ENABLE()                    (g_stTMDSRx2CtrlInfo.b1HDMI2RREnable = _TRUE)
#define CLR_HDMI_2_0_RX2_RR_ENABLE()                    (g_stTMDSRx2CtrlInfo.b1HDMI2RREnable = _FALSE)

//--------------------------------------------------
// Macro of HDMI 2.0 High Speed Mode
//--------------------------------------------------
#define GET_TMDS_RX2_HIGH_SPEED_MODE()                  (g_stTMDSRx2CtrlInfo.b1HDMI2HighSpeedMode)
#define SET_TMDS_RX2_HIGH_SPEED_MODE()                  (g_stTMDSRx2CtrlInfo.b1HDMI2HighSpeedMode = _TRUE)
#define CLR_TMDS_RX2_HIGH_SPEED_MODE()                  (g_stTMDSRx2CtrlInfo.b1HDMI2HighSpeedMode = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
extern BYTE g_pucTmdsRx2Caps[3];
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerTMDSRx2Initial(BYTE ucInputPort);
extern void ScalerTMDSRx2InterruptInitial(void);

#if((_MHL_SUPPORT == _ON) && (_MHL_3_0_SUPPORT == _ON))

#if(_ECBUS_TX_TEST_FUNCTION == _ON)
extern void ScalerTMDSRx2MHL3SetCmu(BYTE ucCmuSel);
#endif

extern void ScalerTMDSRx2MHL3SetCmu_EXINT0(BYTE ucCmuSel);
extern void ScalerTMDSRx2MHL3SetDFEInitial(void);
extern void ScalerTMDSRx2MHL3SetDFEInitial_EXINT0(void);

#if(_MHL3_ECBUS_AVLINK_CDR_MODE == _ACDR_MODE)
extern void ScalerTMDSRx2MHL3AcdrSetPhy(void);
extern void ScalerTMDSRx2MHL3AcdrSetPhy_EXINT0(void);
#endif

#if(_MHL3_ECBUS_AVLINK_CDR_MODE == _DCDR_MODE)
extern void ScalerTMDSRx2MHL3DcdrSetPhy(void);
extern void ScalerTMDSRx2MHL3DcdrSetPhy_EXINT0(void);
#endif

#endif

extern WORD ScalerTMDSRx2MeasureClk(BYTE ucMeasureClk);
extern WORD ScalerTMDSRx2MeasureClk_EXINT0(BYTE ucMeasureClk);

#if(_D2_HDMI_SUPPORT == _ON)
#if(_D2_INPUT_PORT_TYPE != _D2_DUAL_DVI_PORT)
extern bit ScalerTMDSRx2HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
#endif
#endif

extern void ScalerTMDSRx2PowerSavingProc(void);
extern void ScalerTMDSRx2HotPlugEvent(void);


#endif // End of #if(_D2_TMDS_SUPPORT == _ON)

