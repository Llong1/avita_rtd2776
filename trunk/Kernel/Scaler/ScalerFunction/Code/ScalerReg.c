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
// ID Code      : ScalerReg.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_REG__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _NUM_FONT_WIDTH_4_SERIAL                3


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
BYTE ScalerBurstWriteTimeoutCal(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Calculate OSD Burst Write Timeout
// Input Value  :
// Output Value : Burst Write Required Time
//--------------------------------------------------
BYTE ScalerBurstWriteTimeoutCal(void)
{
    WORD usTimeout = 0;

    // Time of MCU Write Cycle > 21 x TDCLK + 28 x TDCLK + (8 + 4 x _NUM_FONT_WIDTH_4_SERIAL) x TDCLK
    // => Tm2pll x Flash Div x Mcu Div x (0xFFFB x 2 + 4) > (49 + 8 + 4 x _NUM_FONT_WIDTH_4_SERIAL) x TDCLK
    // => 0xFFFB > (57 + 4 x _NUM_FONT_WIDTH_4_SERIAL) x TDCLK / (2 x Tm2pll x Flash Div x Mcu Div) - 2
    usTimeout = (DWORD)(57 + 4 * _NUM_FONT_WIDTH_4_SERIAL) * _M2PLL_CLK_MHZ * 1000 * 2 / ((DWORD)GET_D_CLK_FREQ() * _FLASH_CLK_DIV * _MCU_CLK_DIV) - 2;

    // Double timeout if OSD double function is enabled
    if(ScalerOsdGetDoubleFunctionH() == _ENABLE)
    {
        usTimeout *= 2;
    }

    if(usTimeout > 0xFF)
    {
        return 0xFF;
    }

    return (BYTE)usTimeout;
}
