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
// ID Code      : ScalerOsdInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_OSD_POSITION_OFFSET_CORRECTION == _OFF)
#define GET_OSD_POSITION_GOLOBAL_OFFSET_H()                     (g_ucOsdPositionGlobalOffsetH)
#define SET_OSD_POSITION_GOLOBAL_OFFSET_H(x)                    (g_ucOsdPositionGlobalOffsetH = (x))

#define GET_OSD_POSITION_GOLOBAL_OFFSET_V()                     (g_ucOsdPositionGlobalOffsetV)
#define SET_OSD_POSITION_GOLOBAL_OFFSET_V(x)                    (g_ucOsdPositionGlobalOffsetV = (x))
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_OSD_POSITION_OFFSET_CORRECTION == _OFF)
extern BYTE g_ucOsdPositionGlobalOffsetH;
extern BYTE g_ucOsdPositionGlobalOffsetV;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerOsdPositionOffset(EnumOsdPositionOffsetType enumOsdPositionOffsetType, BYTE ucHOffset, BYTE ucVOffset);

