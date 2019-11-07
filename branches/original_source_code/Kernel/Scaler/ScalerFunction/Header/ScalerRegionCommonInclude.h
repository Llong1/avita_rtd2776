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
// ID Code      : ScalerRegionCommonInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern EnumInputDataPath ScalerRegionGetInputDataPath(EnumDisplayRegion enumDisplayRegion);
extern EnumDisplayDataPath ScalerRegionGetDisplayDataPath(EnumDisplayRegion enumDisplayRegion);
extern WORD ScalerRegionGetRegisterPage(EnumRegisterDataPosition enumRegisterDataPosition, EnumSelRegion enumSelRegion);
extern EnumSelRegion ScalerRegionGetInverse(EnumSelRegion enumSelRegion);
extern BYTE ScalerRegionGetUltraVividActivePath(EnumSelRegion enumSelRegion);
extern EnumHLWType ScalerRegionGetSelectArea(EnumSelRegion enumSelRegion);

