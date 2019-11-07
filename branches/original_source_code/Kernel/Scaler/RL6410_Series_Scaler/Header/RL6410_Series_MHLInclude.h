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
// ID Code      : RL6410_Series_MHLInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_MHL_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// MHL 3.0 eCBUS Start-Up
//--------------------------------------------------
#define _MHL3_SOURCE_ECBUS_FWD_COMMA2_TMOUT_MAX         60
#define _MHL3_SOURCE_ECBUS_FWD_COMMA2_TMOUT_MIN         10
#define _MHL3_SOURCE_ECBUS_FWD_AVTIVE_TMOUT_MAX         60
#define _MHL3_SOURCE_ECBUS_FWD_AVTIVE_TMOUT_MIN         10


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of MHL Port Valid
//--------------------------------------------------
#define _MHL_PORT_VALID                                 ((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) + (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) + (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) + (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructMHLProcessInfo g_pstMHLProcess[_MHL_PORT_VALID];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

#endif // End of #if(_MHL_SUPPORT == _ON)
