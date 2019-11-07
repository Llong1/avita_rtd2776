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
// ID Code      : RL6410_Series_DPTxMST.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_DP_TX_SUPPORT == _ON)
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
#if(_DP_MST_SUPPORT == _ON)
void ScalerDpTxMstLinkClockEn(bit bEn);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP MST Link Clock Enable or Disable
// Input Value  : bEn  --> _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstLinkClockEn(bit bEn)
{
    if(bEn == _ENABLE)
    {
        // Enable DP Tx Link Clock
        ScalerSetBit(PA_81_MST2SST_CLK_GATE, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
    }
    else
    {
        // Disable DP Tx Link Clock for Power Saving Mode
        ScalerSetBit(PA_81_MST2SST_CLK_GATE, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }
}
#endif

#endif
