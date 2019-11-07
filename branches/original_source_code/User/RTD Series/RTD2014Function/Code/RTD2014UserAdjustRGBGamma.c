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
// ID Code      : RTD2014UserAdjustRGBGamma.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_ADJUST_RGB_GAMMA__

#include "UserCommonInclude.h"

#if((_OSD_TYPE == _REALTEK_2014_OSD) && (_RGB_GAMMA_FUNCTION == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void UserAdjustRGBGamma(EnumSelRegion enumSelRegion, BYTE ucGamma);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Adjust Gamma
// Input Value  : Gamma type
// Output Value : None
//--------------------------------------------------
void UserAdjustRGBGamma(EnumSelRegion enumSelRegion, BYTE ucGamma)
{
    ScalerColorRGBOutputGammaAdjust(enumSelRegion, tRGBGAMMA_TABLE[ucGamma - 1], GET_CURRENT_BANK_NUMBER());
}


#endif // End of #if((_OSD_TYPE == _REALTEK_2014_OSD) && (_RGB_GAMMA_FUNCTION == _ON))
