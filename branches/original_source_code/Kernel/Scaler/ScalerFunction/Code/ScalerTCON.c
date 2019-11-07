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
// ID Code      : ScalerTCON.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TCON__

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
#if(_PWM_RST_BY_TCON == _ON)
void ScalerTconAdjust(BYTE ucArea);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PWM_RST_BY_TCON == _ON)
//--------------------------------------------------
// Description  : PWM reset by TCON,adjust TCON
// Input Value  : usVstart --> TCON phase shift
// Output Value : None
//--------------------------------------------------
void ScalerTconAdjust(BYTE ucArea)
{
    WORD usVstart = 0;

    usVstart = (WORD)(((DWORD)(ucArea) * (DWORD)(GET_INPUT_TIMING_VTOTAL() - 100)) / 100);

    ScalerTcon4Adjust(0x0000, 0x1FFF, usVstart, (usVstart + 0x02)); // 0x02 indicate Tcon pulse width equal to 2 lines
}
#endif

