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
// ID Code      : RL6410_Series_DisplayDPTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PANEL_STYLE == _PANEL_DPTX)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
#define SET_DISPLAY_DP_TX1_MVID_FW_MODE()                   (ScalerSetBit(P9C_F3_DPTX_TOP_RSV6, ~_BIT0, 0x00))
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
#define SET_DISPLAY_DP_TX2_MVID_FW_MODE()                   (ScalerSetBit(P9E_F3_DPTX_TOP_RSV6, ~_BIT0, 0x00))
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayDPTxSSCSet(bit bSscEn);
extern void ScalerDisplayDPTxPhy(bit bOn);
extern void ScalerDisplayDPTxPLL(bit bOn);
extern void ScalerDisplayDPTxPower(bit bOn);
extern void ScalerDisplayDPTxSetLinkRate(void);

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
extern void ScalerDisplayDPTx1AuxInitial(void);
extern void ScalerDisplayDPTx1AuxPHYSet(BYTE ucMode);
extern bit ScalerDisplayDPTx1AuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDisplayDPTx1AuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerDisplayDPTx1HpdInitial(void);
extern void ScalerDisplayDPTx1SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
extern void ScalerDisplayDPTx1SignalInitialSetting(void);
extern void ScalerDisplayDPTx1LanePowerOff(void);
extern EnumDisplayDPTxTrainPattern ScalerDisplayDPTx1SetTp2PatternType(void);
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
extern void ScalerDisplayDPTx2AuxInitial(void);
extern void ScalerDisplayDPTx2AuxPHYSet(BYTE ucMode);
extern bit ScalerDisplayDPTx2AuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDisplayDPTx2AuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerDisplayDPTx2HpdInitial(void);
extern void ScalerDisplayDPTx2SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
extern void ScalerDisplayDPTx2SignalInitialSetting(void);
extern void ScalerDisplayDPTx2LanePowerOff(void);
extern EnumDisplayDPTxTrainPattern ScalerDisplayDPTx2SetTp2PatternType(void);
extern void ScalerDisplayDPTx2SetTps3PatternMux(bit bAphyMux);
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)
