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
// ID Code      : RL6410_Series_OsdInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define OSD_POSITION_OFFSET_WINDOW_V_OFFSET_ADJUST(x)        (x)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerOsdDoubleFunction(EnumOsdDoubleWidthType enumOsdDoubleWidthType, EnumOsdDoubleHeightType enumOsdDoubleHeightType);
extern void ScalerOsdMapRotation(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, BYTE ucMapARowSize, EnumOsdRotateMapB enumOsdRotateMapB, BYTE ucMapBRowSize, EnumOsdRotateFontLib enumOsdRotateFontLib);

