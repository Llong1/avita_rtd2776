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
// ID Code      : ScalerDPRx0Interface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
//****************************************************************************
// INTERFACE DEFINITIONS / MACROS
//****************************************************************************
#define CLR_DP_RX0_VALID_VIDEO_CHECK()                  (g_ucDpRx0Info &= ~_BIT6)


//****************************************************************************
// INTERFACE VARIABLE DECLARATIONS
//****************************************************************************
extern BYTE g_ucDpRx0Info;

//****************************************************************************
// INTERFACE FUNCTIONS
//****************************************************************************
extern void ScalerDpRx0Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumDisplayMode enumDisplayMode);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
extern void ScalerDpRx6Initial(EnumDpVersionType enumDpVersion, EnumDpLaneCount enumDpLaneCount, EnumDPMSTPort enumDpRxMstPort, EnumDisplayMode enumDisplayMode);
#endif

extern void ScalerDpRx0InterfaceInitial(void);
extern void ScalerDpRx0HotPlugEvent(EnumDpHotPlugAssertType enumHpdType);

#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpRx0AuxChPowerStatusCheck(bit bCableStatus);
extern void ScalerDpRx0MstInfoBackup(EnumDpMstBackup enumDpMstBackup);

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
extern void ScalerDpRx6AuxChPowerStatusCheck(bit bCableStatus);
extern void ScalerDpRx6MstInfoBackup(EnumDpMstBackup enumDpMstBackup);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx0HDCPHandler(void);
#endif

#endif

#endif
