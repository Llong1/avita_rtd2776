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
// ID Code      : ScalerLDO.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_LDO__

#include "ScalerFunctionInclude.h"

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
void ScalerLDOPowerControl(EnumPowerStatus enumPorStatus);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : LDO Power Control.
// Input Value  : ucPorStatus    --> _POWER_STATUS_NORMAL/_POWER_STATUS_SAVING/_POWER_STATUS_OFF Select.
// Output Value : None
//--------------------------------------------------
void ScalerLDOPowerControl(EnumPowerStatus enumPorStatus)
{
    switch(enumPorStatus)
    {
        case _POWER_STATUS_NORMAL:

            break;

        case _POWER_STATUS_OFF:
        case _POWER_STATUS_SAVING:

            break;

        default:

            break;
    }
}

