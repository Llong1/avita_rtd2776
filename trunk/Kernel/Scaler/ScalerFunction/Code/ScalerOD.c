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
// ID Code      : ScalerOD.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_OD__

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

#if(_OD_SUPPORT == _ON)
void ScalerODEnable(EnumFunctionOnOFF enumOn);
BYTE ScalerODGetCompressionBitNum(DWORD ulMemoryRemainSpace, WORD usMemoryRemainBW);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_OD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : OD on/off
// Input Value  : enumOn --> _FUNCTION_ON/_FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerODEnable(EnumFunctionOnOFF enumOn)
{
    //=================
    // Enable OD
    //=================
    if((enumOn == _FUNCTION_ON) && (GET_OD_USE_BIT() != _OFF))
    {
        // Disable OD clock gated
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT2, _BIT2);

#if(_FRC_SUPPORT == _ON)
        DebugMessageFRC("OD_ON", 0);

        if(GET_DYNAMIC_OD_STATUS() == _ENABLE)
        {
            DebugMessageFRC("Dynamic OD", GET_MEMORY_DVF_SELECT());

            // Enable DEN_START IRQ
            ScalerGlobalSetInterrupt(_IRQ_DEN, _ENABLE);
        }
        else
        {
            DebugMessageFRC("Static OD", 0);

            // Enable OD function, disable DEN_START IRQ
            ScalerGlobalSetInterrupt(_IRQ_DEN, _DISABLE);
            ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
#else
        // Enable OD function
        ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif
    }
    //=================
    // Disable OD
    //=================
    else
    {
        // Disable OD clock gated
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT2, _BIT2);

#if(_FRC_SUPPORT == _ON)
        DebugMessageFRC("OD_OFF", 0);

        ScalerGlobalSetInterrupt(_IRQ_DEN, _DISABLE);
#endif
        // Disable OD function
        ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

        //=================
        // Clock Gated
        //=================
        if(enumOn == _FUNCTION_CLOCK_GATED)
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
            ScalerTimerDelayXms(2);

            // Enable OD clock gated
            ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT2, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Get OD compression bit number
//                according to available memory space & BW.
// Input Value  : Remaining space & BW
// Output Value : OD compression bit number(10x)
//--------------------------------------------------
BYTE ScalerODGetCompressionBitNum(DWORD ulMemoryRemainSpace, WORD usMemoryRemainBW)
{
    BYTE ucDynamicODBWFactor = 1;
    WORD usODUseSpace = 0;
    WORD usODUseBW = 0;

#if(_FRC_SUPPORT == _ON)
    ucDynamicODBWFactor = (GET_DYNAMIC_OD_STATUS() == _ENABLE) ? 2 : 1;
#endif

    DebugMessageMemory("4. Remaining BW for OD", usMemoryRemainBW);
    DebugMessageMemory("4. Remaining Space for OD", ulMemoryRemainSpace);
    //=============================================
    // OD compression bit num: 7.5bits / pixel
    //=============================================
    usODUseSpace = ScalerMDomainODCalculateMemoryUseSpace(_OD_SUPERPIXEL1X2_75BIT_BIT_NUM);
    usODUseBW = ScalerMDomainODCalculateMemoryUseBW(_OD_SUPERPIXEL1X2_75BIT_BIT_NUM) / ucDynamicODBWFactor;

    DebugMessageMemory("4. 7_5_bit OD BW", usODUseBW);
    DebugMessageMemory("4. 7_5_bit OD Size", usODUseSpace);
    if((usODUseSpace < ulMemoryRemainSpace) && (usODUseBW < usMemoryRemainBW))
    {
        return _OD_SUPERPIXEL1X2_75BIT_BIT_NUM;
    }

    //=============================================
    // OD compression bit num: 6 bits / pixel
    //=============================================
    usODUseSpace = ScalerMDomainODCalculateMemoryUseSpace(_OD_SUPERPIXEL1X4_60BIT_BIT_NUM);
    usODUseBW = ScalerMDomainODCalculateMemoryUseBW(_OD_SUPERPIXEL1X4_60BIT_BIT_NUM) / ucDynamicODBWFactor;

    DebugMessageMemory("4. 6_0_bit OD BW", usODUseBW);
    DebugMessageMemory("4. 6_0_bit OD Size", usODUseSpace);
    if((usODUseSpace < ulMemoryRemainSpace) && (usODUseBW < usMemoryRemainBW))
    {
        return _OD_SUPERPIXEL1X4_60BIT_BIT_NUM;
    }

    //=============================================
    // Otherwise, OD off
    //=============================================
    return _OFF;
}
#endif // End of #if(_OD_SUPPORT == _ON)

