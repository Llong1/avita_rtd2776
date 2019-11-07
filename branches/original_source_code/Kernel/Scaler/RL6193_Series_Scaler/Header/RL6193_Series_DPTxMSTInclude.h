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
// ID Code      : RL6193_Series_DPTxMSTInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_DP_TX_STX_START_ADDRESS(x)                              (((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? RET_REG_ADDR_DP_RX0_DAIZY_ST3_START() : RET_REG_ADDR_DP_RX1_DAIZY_ST3_START()) + (2 * ((x) - 2)))
#define GET_DP_TX_STX_END_ADDRESS(x)                                (((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? RET_REG_ADDR_DP_RX0_DAIZY_ST3_END() : RET_REG_ADDR_DP_RX1_DAIZY_ST3_END()) + (2 * ((x) - 2)))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_MST_SUPPORT == _ON)
extern void ScalerDpTxMstLinkClockEn(bit bEn);
#endif

#endif

