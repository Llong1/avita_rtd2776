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
// ID Code      : ScalerSyncCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of DP Link Traiinng Status
//--------------------------------------------------
#define _DP_LINK_TRAINING_NONE                          0
#define _DP_NORMAL_TRAINING_PATTERN_1_PASS              1
#define _DP_NORMAL_TRAINING_PATTERN_1_FAIL              2
#define _DP_FAKE_TRAINING_PATTERN_1_PASS                3
#define _DP_FAKE_TRAINING_PATTERN_1_FAIL                4
#define _DP_NORMAL_TRAINING_PATTERN_2_PASS              5
#define _DP_NORMAL_TRAINING_PATTERN_2_FAIL              6
#define _DP_FAKE_TRAINING_PATTERN_2_PASS                7
#define _DP_FAKE_TRAINING_PATTERN_2_FAIL                8
#define _DP_NORMAL_LINK_TRAINING_PASS                   9
#define _DP_FAKE_LINK_TRAINING_PASS                     10
#define _DP_FAKE_LINK_TRAINING_PASS_VBIOS               11
#define _DP_LINK_TRAINING_FAIL                          12
#define _DP_LINK_STATUS_FAIL                            13

//--------------------------------------------------
// Macro of Link Training Status
//--------------------------------------------------
#define GET_DP_RX0_LINK_TRAINING_STATUS()               (g_ucDpRx0LTStatus)
#define SET_DP_RX0_LINK_TRAINING_STATUS(x)              (g_ucDpRx0LTStatus = (x))
#define GET_DP_RX1_LINK_TRAINING_STATUS()               (g_ucDpRx1LTStatus)
#define SET_DP_RX1_LINK_TRAINING_STATUS(x)              (g_ucDpRx1LTStatus = (x))

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDpRx0LTStatus;
extern BYTE g_ucDpRx1LTStatus;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
