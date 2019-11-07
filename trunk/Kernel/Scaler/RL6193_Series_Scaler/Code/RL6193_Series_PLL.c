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
// ID Code      : RL6193_Series_PLL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)

//--------------------------------------------------
// Definations of LVDS VCO Range, convert into Dclk frequency
//--------------------------------------------------
#define _LVDS_PLL_BOUNDRY_0                         (250000  * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))
#define _LVDS_PLL_BOUNDRY_1                         (500000  * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))
#define _LVDS_PLL_BOUNDRY_2                         (1000000 * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))

#elif(_PANEL_STYLE == _PANEL_VBO)
//--------------------------------------------------
// Definations of Vby1 VCO Range
//--------------------------------------------------
#define _VBO_PLL_BOUNDRY_0                          500000
#define _VBO_PLL_BOUNDRY_1                          1000000
#define _VBO_PLL_BOUNDRY_2                          2000000
#define _VBO_PLL_BOUNDRY_3                          3000000

#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

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
#if(_PANEL_STYLE == _PANEL_DPTX)
bit ScalerPLLGetDptxPowerStatus(void);
#endif
void ScalerPLLSetDisplayPLL(DWORD ulFreq);
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Description  : Get Dptx Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerPLLGetDptxPowerStatus(void)
{
    bit bDISPPower = 0;

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

    bDISPPower = (ScalerGetBit(P38_AD_PHY0_APHY_0D, _BIT7) >> 7);

#else

    if((ScalerGetBit(PBB_01_DPTX_ML_PAT_SEL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4) == _DISPLAY_DP_TX_OUTPUT_VIDEO_PATTERN)
    {
        bDISPPower = 1;
    }

#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

    return bDISPPower;
}
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

//--------------------------------------------------
// Description  : Set Display Interface PLL: Frequency, VCO Band
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDisplayPLL(DWORD ulFreq)
{
    BYTE ucDispPllParam = 0x00;
    DWORD ulCLK = 0;
#if(_PANEL_STYLE == _PANEL_VBO)
    DWORD ulBoundary = 0;
#endif

    ulCLK = (ulFreq >> _D_DOMAIN_PATH) * 16 / 15;

    // ----------- Previous Select Band & Div Alg. -----------
#if(_PANEL_STYLE == _PANEL_LVDS)

    // ucDispPllParam: [7:6] = LVDS_PLL_VCO
    if(ulCLK < _LVDS_PLL_BOUNDRY_0)
    {
        ucDispPllParam |= (3 << 6);
    }
    else if(ulCLK < _LVDS_PLL_BOUNDRY_1)
    {
        ucDispPllParam |= (2 << 6);
    }
    else if(ulCLK < _LVDS_PLL_BOUNDRY_2)
    {
        ucDispPllParam |= (1 << 6);
    }
    else
    {
        ucDispPllParam |= (0 << 6);
    }

    // LVDS data rate = ((Pixel Clk) / (LVDS Outport)) * 7
    PDATA_DWORD(1) = ((ulCLK << _D_DOMAIN_PATH) / (1 << _LVDS_OUTPUT_PORT)) * 7;

    // ucDispPllParam: [3:2] = LVDS PI Operation Frequency Seletcion
    if(PDATA_DWORD(1) < 250000)
    {
        ucDispPllParam |= (0 << 2);
    }
    else if(PDATA_DWORD(1) < 400000)
    {
        ucDispPllParam |= (1 << 2);
    }
    else if(PDATA_DWORD(1) < 600000)
    {
        ucDispPllParam |= (2 << 2);
    }
    else
    {
        ucDispPllParam |= (3 << 2);
    }

#elif(_PANEL_STYLE == _PANEL_VBO)

    // VBO_PLL = (Pixel Clk * BYTE_MODE * 10) / (LANE_COUNT)
    ulBoundary = ((ulCLK << _D_DOMAIN_PATH) * _VBO_BYTE_MODE * 10) / (_VBO_OUTPUT_PORT);

    if(ScalerDisplayGetVboPowerStatus() == _OFF)
    {
        // Vbyone PLL VCO Gain
        ScalerSetBit(P38_AE_PHY0_APHY_0E, ~_BIT4, ((ulBoundary <= _VBO_PLL_BOUNDRY_2) ? 0x00 : _BIT4));
    }

    // Vbyone Analog TX Bandwidth
    ScalerSetBit(P38_AE_PHY0_APHY_0E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

    // PLL VCO LDO,1V regulator
    ScalerSetBit(P38_B0_PHY0_APHY_10, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));

    // ucDispPllParam: [7:6] = Vby1_PLL_VCO
    if(ulBoundary <= _VBO_PLL_BOUNDRY_0)
    {
        ucDispPllParam |= (3 << 6);
    }
    else if(ulBoundary <= _VBO_PLL_BOUNDRY_1)
    {
        ucDispPllParam |= (2 << 6);
    }
    else if(ulBoundary <= _VBO_PLL_BOUNDRY_2)
    {
        ucDispPllParam |= (1 << 6);
    }
    else if(ulBoundary <= _VBO_PLL_BOUNDRY_3)
    {
        // Vbyone Analog TX Bandwidth
        ScalerSetBit(P38_AE_PHY0_APHY_0E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT0));

        // PLL VCO LDO,1V regulator
        ScalerSetBit(P38_B0_PHY0_APHY_10, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3 | _BIT2));

        ucDispPllParam |= (0 << 6);
    }
    else
    {
        // Vbyone Analog TX Bandwidth
        ScalerSetBit(P38_AE_PHY0_APHY_0E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT0));

        // PLL VCO LDO,1V regulator
        ScalerSetBit(P38_B0_PHY0_APHY_10, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3 | _BIT2));

        ucDispPllParam |= (0 << 6);
    }

    // DPLL out = Pixel Clk * DIV_B
    PDATA_DWORD(1) = ((ulCLK << _D_DOMAIN_PATH) << ((ucDispPllParam & 0x30) >> 4));

    // pData[15]: [3:2] = DIV_A
    if(PDATA_DWORD(1) < 300000)
    {
        ucDispPllParam |= (0 << 2);
    }
    else if(PDATA_DWORD(1) < 600000)
    {
        ucDispPllParam |= (1 << 2);
    }
    else if(PDATA_DWORD(1) < 1200000)
    {
        ucDispPllParam |= (2 << 2);
    }
    else
    {
        ucDispPllParam |= (3 << 2);
    }

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

    // ----------- Set Display VCO Band -----------
#if(_PANEL_STYLE == _PANEL_LVDS)

    // Manual set LVDS VCO band
    ScalerDisplayLvdsSetVcoBand((ucDispPllParam & 0xC0) >> 6);

    // Set LVDS PI Operation band
    ScalerDisplayLvdsSetPhaseBand(((ucDispPllParam & 0x0C) >> 2) << 5);

#elif(_PANEL_STYLE == _PANEL_VBO)

    // Manual set Vby1 VCO band
    ScalerSetBit(P38_AF_PHY0_APHY_0F, ~(_BIT4 | _BIT3), ((ucDispPllParam & 0xC0) >> 3));

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

    // ----------- Set Vby1 Phy Div -----------
#if(_PANEL_STYLE == _PANEL_VBO)
    // Set Vby1 phy clk divider (DIV_A)
    ScalerSetBit(P1_DA_DPLL_OUTPUT_CLK_DIV, ~(_BIT5 | _BIT4), ((ucDispPllParam & 0x0C) << 2));

    switch(_VBO_OUTPUT_PORT)
    {
        case _VBO_1_DATA_LANE:

            PDATA_DWORD(0) = 0;
            break;

        case _VBO_2_DATA_LANE:

            PDATA_DWORD(0) = 1;
            break;

        case _VBO_4_DATA_LANE:

            PDATA_DWORD(0) = 2;
            break;

        case _VBO_8_DATA_LANE:

            PDATA_DWORD(0) = 3;
            break;

        default:

            PDATA_DWORD(0) = 3;
            break;
    }

    // Set Vby1 M code and N code: M = BYTE_MODE, N = (DIV_B * LANE_COUNT) / DIV_A
    ScalerSetBit(P38_AF_PHY0_APHY_0F, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1), ((((ucDispPllParam & 0x30) >> 4) + PDATA_DWORD(0) - ((ucDispPllParam & 0x0C) >> 2)) << 5) | ((_VBO_BYTE_MODE - 2) << 1));

#endif // #if(_PANEL_STYLE == _PANEL_VBO)
}

//--------------------------------------------------
// Description  : Get DPLL Ref Clk from DPTx PLL or Xtal
// Input Value  : Dclk
// Output Value : DPTx PLL clk or Xtal Clk
//--------------------------------------------------
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq)
{
    ulFreq = ulFreq;

    return _EXT_XTAL;
}
