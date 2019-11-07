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
// ID Code      : RL6410_Series_ADC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
void ScalerADCSetClampToTopStatus(bit bEn);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set clamp-to-top status
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerADCSetClampToTopStatus(bit bEn)
{
    EnumInputDataPath enumInputDataPath = ScalerFmtCnvGetInputPath(_A0_INPUT_PORT);
    WORD usPage = 0x0000;

    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M2:

            usPage = 0x0040;
            break;

        case _INPUT_PATH_S1:

            usPage = 0x0080;
            break;

        case _INPUT_PATH_S2:

            usPage = 0x00C0;
            break;

        default:

            break;
    }

    if(bEn == _TRUE)
    {
        // Enable clamp-to-top
        ScalerSetBit(P0_D6_ADC_CLAMP_TOP, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Enable YPbPr clamp
        ScalerSetBit(P0_CF_ADC_CTL_RED, ~_BIT7, _BIT7);
        ScalerSetBit(P0_D0_ADC_CTL_GRN, ~_BIT7, _BIT7);
        ScalerSetBit(P0_D1_ADC_CTL_BLU, ~_BIT7, _BIT7);
    }
    else
    {
        // Disable clamp-to-top
        ScalerSetBit(P0_D6_ADC_CLAMP_TOP, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Restore to RGB/YPbPr clamp, according to I-domain color conversion output select bit,
        // D-domain color enable bit, and D-domain identity matrix enable bit
        if((ScalerGetBit((P14_A1_SR_YCC2RGB_CTRL + usPage), _BIT0) == ScalerGetBit((P0_9C_RGB2YCC_CTRL + usPage), _BIT0)) ||
           (ScalerGetBit((P14_A1_SR_YCC2RGB_CTRL + usPage), _BIT4) == _BIT4))
        {
            pData[0] = 0; // RGB
        }
        else
        {
            pData[0] = _BIT7; // YPbPr
        }

        ScalerSetBit(P0_CF_ADC_CTL_RED, ~_BIT7, pData[0]);
        ScalerSetBit(P0_D0_ADC_CTL_GRN, ~_BIT7, 0x00);
        ScalerSetBit(P0_D1_ADC_CTL_BLU, ~_BIT7, pData[0]);
    }
}
#endif

