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
// ID Code      : ScalerDPRx1Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define CLR_DP_RX1_VALID_VIDEO_CHECK()                  (g_ucDpRx1Info &= ~_BIT6)


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern BYTE g_ucDpRx1Info;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerDpRx1Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumDisplayMode enumDisplayMode);
extern void ScalerDpRx1InterfaceInitial(void);
extern void ScalerDpRx1HotPlugEvent(EnumDpHotPlugAssertType enumHpdType);

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpRx1AuxChPowerStatusCheck(bit bCableStatus);
extern void ScalerDpRx1MstInfoBackup(EnumDpMstBackup enumDpMstBackup);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx1HDCPHandler(void);
#endif

#endif

#endif
