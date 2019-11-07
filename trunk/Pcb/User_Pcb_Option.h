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
// ID Code      : User_PCB_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// eDPTx 1.2 HBR2 FB/Lane Config
//--------------------------------------------------
#if((_PCB_TYPE == _RL6410_DEMO_A_1A4MHL2DP_DPTX_LVDS_eDP) || (_PCB_TYPE == _RL6410_QA_A_1A4MHL1DP1mDP_DPTX_LVDS_eDP) || (_PCB_TYPE == _RL6410_QA_B_1A6mDP_DPTX_LVDS_eDP))
#if(_PANEL_TYPE == _LG_LED_DP_27_QQHD)
#undef _PANEL_DPTX_1_2_FB_SWAP
#undef _PANEL_DPTX_1_2_LANE_SWAP
#undef _PANEL_DPTX_1_2_LANE_PN_SWAP
#define _PANEL_DPTX_1_2_FB_SWAP                 _ENABLE
#define _PANEL_DPTX_1_2_LANE_SWAP               _ENABLE
#define _PANEL_DPTX_1_2_LANE_PN_SWAP            _ENABLE
#endif
#endif
