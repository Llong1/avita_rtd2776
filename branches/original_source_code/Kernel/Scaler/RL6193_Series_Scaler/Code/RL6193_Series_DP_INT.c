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
// ID Code      : RL6193_Series_DP_INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_SUPPORT == _ON)

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
void ScalerDpExitIntSetting_EXINT0(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Handle the DP settings when exiting sysint
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpExitIntSetting_EXINT0(void) using 1
{
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    if(ScalerGetBit_EXINT(PB7_D0_AUX_MODE_SET, _BIT1) == 0x00)
    {
        // Aux Hardware Control
        SET_DP_RX0_AUX_AUTO_MODE_EXINT();
    }

    // CLR Flag for 0x2002 bug
    ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PB7_FB_DUMMY_1, ~_BIT7, 0x00);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    if(ScalerGetBit_EXINT(PBA_D0_AUX_MODE_SET, _BIT1) == 0x00)
    {
        // Aux Hardware Control
        SET_DP_RX1_AUX_AUTO_MODE_EXINT();
    }

    // CLR Flag for 0x2002 bug
    ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~_BIT7, _BIT7);
    ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~_BIT7, 0x00);
#endif
}
#endif // #if(_DP_SUPPORT == _ON)
