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
// ID Code      : RL6193_Series_Color.c No.0000
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
#if(_UNIFORMITY_SUPPORT == _ON)
void ScalerColorPanelUniformityInitial(BYTE ucLUTMode);
#endif

#if(_PCM_FUNCTION == _ON)
void ScalerColorPCMOff(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE *pucInverseGammaTableArray, BYTE ucBankNum);
void ScalerColorPCMAdjust(EnumSelRegion enumSelRegion, EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucPCMBankNum, WORD usLength, BYTE *pucInverseGammaTableArray, BYTE ucGammaBankNum);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_UNIFORMITY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial Panel Uniformity Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorPanelUniformityInitial(BYTE ucLUTMode)
{
    BYTE ucMultiLUTMode = 0;
    ScalerSetBit(P34_00_UN_GLOBAL_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (((_PANEL_UNIFORMITY_HOR_INTERVAL / 64) << 5) | ((_PANEL_UNIFORMITY_VER_INTERVAL / 64) << 3)));
    switch(ucLUTMode)
    {
        case _UNIFORMITY_1LEVEL:

            ucMultiLUTMode = 0;
            break;

        case _UNIFORMITY_2LEVEL:

            ucMultiLUTMode = 1;
            break;

        case _UNIFORMITY_4LEVEL:

            ucMultiLUTMode = 2;
            break;

        default:
            break;
    }
    ScalerSetBit(P34_01_UN_MULTI_LUT_CTRL, ~(_BIT1 | _BIT0), (ucMultiLUTMode & 0x03));

    ScalerSetByte(P34_02_UN_GAIN_LUT_HOR_GRIDS, _PANEL_UNIFORMITY_HOR_GRIDS);
    ScalerSetByte(P34_03_UN_GAIN_LUT_VER_GRIDS, _PANEL_UNIFORMITY_VER_GRIDS);
    ScalerSetByte(P34_04_UN_GAIN_LUT_HOR_OFFSET, _PANEL_UNIFORMITY_HOR_OFFSET);
    ScalerSetByte(P34_05_UN_GAIN_LUT_VER_OFFSET, _PANEL_UNIFORMITY_VER_OFFSET);
}
#endif // End of #if(_UNIFORMITY_SUPPORT == _ON)

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set PCM OFF
// Input Value  : SelRegion and two OG Gamma Table and OG Gamma Table Bank
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMOff(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, BYTE *pucInverseGammaTableArray, BYTE ucBankNum)
{
    EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(enumSelRegion);

    if(ScalerDDomainBackgroundCheck(enumSelRegion) == _TRUE)   // Force to BG
    {
        ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);
        ScalerColorGammaSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);

        ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
        ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);

        if(pucGammaTableArray != _NULL_POINTER)
        {
            ScalerColorOutputGammaAdjust(enumSelRegion, pucGammaTableArray, ucBankNum);
            ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
        }

        if(pucInverseGammaTableArray != _NULL_POINTER)
        {
            ScalerColorOutputGammaAdjust(enumSelRegionInverse, pucInverseGammaTableArray, ucBankNum);
            ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
        }

#if(_GLOBAL_HUE_SATURATION == _ON)
        ScalerColorSRGBSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);

        ScalerColorSRGBSetGlobalHueSat(enumSelRegion, g_usRegSelHUEOSD, g_usRegSelSATOSD);    // Default Hue = 180
        ScalerColorSRGBSetGlobalHueSat(enumSelRegionInverse, g_usInverseRegSelHUEOSD, g_usInverseRegSelSATOSD);    // Default Hue = 180

        ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
        ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
#else
        ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
        ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _OFF);
#endif
    }
    else
    {
        switch(ScalerColorPCMGetStatus())
        {
            case _HLW_FULL_WINDOW:

                // ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF); //Mask PCM
                // ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, _DISPLAY_PATH_ALL);
                ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
                ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
                ScalerColorGammaSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
                ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
                ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);

                ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

                if(pucGammaTableArray != _NULL_POINTER)
                {
                    ScalerColorOutputGammaAdjust(enumSelRegion, pucGammaTableArray, ucBankNum);
                    ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }

                if(pucInverseGammaTableArray != _NULL_POINTER)
                {
                    ScalerColorOutputGammaAdjust(enumSelRegionInverse, pucInverseGammaTableArray, ucBankNum);
                    ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
                }

#if(_GLOBAL_HUE_SATURATION == _ON)
                ScalerColorSRGBSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
                ScalerColorSRGBSetGlobalHueSat(enumSelRegion, g_usRegSelHUEOSD, g_usRegSelSATOSD);    // Default Hue = 180
                ScalerColorSRGBSetGlobalHueSat(enumSelRegionInverse, g_usInverseRegSelHUEOSD, g_usInverseRegSelSATOSD);    // Default Hue = 180
                ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
                ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NO_POLLING, _ON);
#endif
                break;

            case _HLW_INSIDE_WINDOW:

                ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF); // Mask PCM

                if(pucInverseGammaTableArray != _NULL_POINTER)
                {
                    ScalerColorOutputGammaAdjust(enumSelRegionInverse, pucInverseGammaTableArray, ucBankNum);
                }


                ScalerColorGammaSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);

                if(pucInverseGammaTableArray != _NULL_POINTER)
                {
                    ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _ON);
                }
                else
                {
                    ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
                }

#if(_GLOBAL_HUE_SATURATION == _ON)
                ScalerColorSRGBSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
                ScalerColorSRGBSetGlobalHueSat(enumSelRegionInverse, g_usInverseRegSelHUEOSD, g_usInverseRegSelSATOSD);    // Default Hue = 180
                ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _ON);
                ScalerColorSRGBSetGlobalHueSat(enumSelRegion, g_usRegSelHUEOSD, g_usRegSelSATOSD);    // Default Hue = 180
                ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
#else
                ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
                ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
#endif
                ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

                if(pucGammaTableArray != _NULL_POINTER)
                {
                    ScalerColorOutputGammaAdjust(enumSelRegion, pucGammaTableArray, ucBankNum);
                    ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }

                break;

            case _HLW_OUTSIDE_WINDOW:

                ScalerColorGammaSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);

                if(pucInverseGammaTableArray != _NULL_POINTER)
                {
                    ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _ON);
                }
                else
                {
                    ScalerColorGammaRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
                }

#if(_GLOBAL_HUE_SATURATION == _ON)
                ScalerColorSRGBSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
                ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _ON);
                ScalerColorSRGBSetGlobalHueSat(enumSelRegion, g_usRegSelHUEOSD, g_usRegSelSATOSD);    // Default Hue = 180
                ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _ON);
#else
                ScalerColorSRGBRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
                ScalerColorSRGBRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
#endif

                ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                ScalerColorPCMInputGammaEnable(_FUNCTION_OFF);

                if(pucGammaTableArray != _NULL_POINTER)
                {
                    ScalerColorOutputGammaAdjust(enumSelRegion, pucGammaTableArray, ucBankNum);
                    ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }

                break;

            default:
                break;
        }
    }
}

//--------------------------------------------------
// Description  : Set PCM(Input Gamma, Output Gamma, Color Matrix)
// Input Value  : PCM SelRegion(Not OSD SelRegion)
//                PCM Mode
//                PCM Input Gamma Table  & Its Bank Number
//                PCM Output Gamma Table & Its Bank Number
//                PCM Color Matrix       & Its Nank Number
//                Inverse Area OG Gamma Table & Its Bank Number
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMAdjust(EnumSelRegion enumSelRegion, EnumPCMType enumPCMMode, BYTE *pucIGammaTableArray, BYTE *pucOGammaTableArray, BYTE *pucColorMatrixArray, BYTE ucPCMBankNum, WORD usLength, BYTE *pucInverseGammaTableArray, BYTE ucGammaBankNum)
{
    EnumSelRegion enumSelRegionInverse = ScalerRegionGetInverse(enumSelRegion);
    EnumHLWType enumHLWType = ScalerRegionGetSelectArea(enumSelRegion);

    if(ScalerDDomainBackgroundCheck(enumSelRegion) == _TRUE)
    {
        ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
        ScalerColorPCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
        ScalerColorPCMRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);
        ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);

        ScalerColorPCMGammaRegionEnable(_DB_APPLY_POLLING, _OFF);

        if(enumHLWType == _HLW_INSIDE_WINDOW) // case 4
        {

#if(_GLOBAL_HUE_SATURATION == _ON)
            ScalerColorPCMSRGBRegionEnable(_DB_APPLY_NONE, _ON);
            ScalerColorSRGBSetGlobalHueSat(enumSelRegion, g_usInverseRegSelHUEOSD, g_usInverseRegSelSATOSD);    // Default Hue = 180
#endif

            if(pucInverseGammaTableArray != _NULL_POINTER)
            {
                ScalerColorOutputGammaAdjust(enumSelRegion, pucInverseGammaTableArray, ucGammaBankNum);
                ScalerColorPCMGammaRegionEnable(_DB_APPLY_NO_POLLING, _ON);
            }
        }
        else if(enumHLWType == _HLW_OUTSIDE_WINDOW)  // case 7
        {

#if(_GLOBAL_HUE_SATURATION == _ON)
            ScalerColorPCMSRGBRegionEnable(_DB_APPLY_NONE, _ON);
            ScalerColorSRGBSetGlobalHueSat(enumSelRegionInverse, g_usInverseRegSelHUEOSD, g_usInverseRegSelSATOSD);    // Default Hue = 180
#endif
            if(pucInverseGammaTableArray != _NULL_POINTER)
            {
                ScalerColorOutputGammaAdjust(enumSelRegionInverse, pucInverseGammaTableArray, ucGammaBankNum);
                ScalerColorPCMGammaRegionEnable(_DB_APPLY_NO_POLLING, _ON);
            }
        }

        ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
        ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
    }
    else
    {
        switch(ScalerColorPCMGetStatus())
        {
            case _HLW_FULL_WINDOW:
                ScalerColorPCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);

                if(enumHLWType == _HLW_INSIDE_WINDOW) // case 4
                {
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);

#if(_GLOBAL_HUE_SATURATION == _ON)
                    ScalerColorPCMSRGBRegionEnable(_DB_APPLY_NONE, _ON);
                    ScalerColorSRGBSetGlobalHueSat(enumSelRegion, g_usInverseRegSelHUEOSD, g_usInverseRegSelSATOSD);    // Default Hue = 180     Set Main2 Region
#endif
                    ScalerColorPCMGammaRegionEnable(_DB_APPLY_POLLING, _OFF);

                    if(pucInverseGammaTableArray != _NULL_POINTER)
                    {
                        ScalerColorOutputGammaAdjust(enumSelRegion, pucInverseGammaTableArray, ucGammaBankNum);
                        ScalerColorPCMGammaRegionEnable(_DB_APPLY_NONE, _ON);
                    }

                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }
                else if(enumHLWType == _HLW_OUTSIDE_WINDOW)  // case 7
                {
                    ScalerColorPCMRegionEnable(enumSelRegionInverse, _DB_APPLY_NONE, _OFF);

#if(_GLOBAL_HUE_SATURATION == _ON)
                    ScalerColorPCMSRGBRegionEnable(_DB_APPLY_NONE, _ON);
                    ScalerColorSRGBSetGlobalHueSat(enumSelRegionInverse, g_usInverseRegSelHUEOSD, g_usInverseRegSelSATOSD);    // Default Hue = 180
#endif
                    ScalerColorPCMGammaRegionEnable(_DB_APPLY_POLLING, _OFF);

                    if(pucInverseGammaTableArray != _NULL_POINTER)
                    {
                        ScalerColorOutputGammaAdjust(enumSelRegionInverse, pucInverseGammaTableArray, ucGammaBankNum);
                        ScalerColorPCMGammaRegionEnable(_DB_APPLY_NONE, _ON);
                    }

                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }
                else
                {
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }

                break;

            case _HLW_INSIDE_WINDOW:
                ScalerColorPCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
                if(enumHLWType == _HLW_INSIDE_WINDOW)
                {
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }
                else if(enumHLWType == _HLW_FULL_WINDOW)  // case 3
                {
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }

                break;

            case _HLW_OUTSIDE_WINDOW:
                ScalerColorPCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
                if(enumHLWType == _HLW_OUTSIDE_WINDOW)
                {
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }
                else if(enumHLWType == _HLW_FULL_WINDOW)  // case 8
                {
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }

                break;

            case _HLW_ALL_BYPASS:
                if(enumHLWType == _HLW_INSIDE_WINDOW) // case 5
                {
                    ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);

                    if(pucInverseGammaTableArray != _NULL_POINTER)
                    {
                        ScalerColorOutputGammaAdjust(enumSelRegion, pucInverseGammaTableArray, ucGammaBankNum);
                    }

                    ScalerColorPCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);

                    if(pucInverseGammaTableArray != _NULL_POINTER)
                    {
                        ScalerColorPCMGammaRegionEnable (_DB_APPLY_NONE, _ON);
                    }
                    else
                    {
                        ScalerColorPCMGammaRegionEnable(_DB_APPLY_NONE, _OFF);
                    }

#if(_GLOBAL_HUE_SATURATION == _ON)
                    ScalerColorPCMSRGBRegionEnable(_DB_APPLY_NONE, _ON);
                    ScalerColorSRGBSetGlobalHueSat(enumSelRegion, g_usInverseRegSelHUEOSD, g_usInverseRegSelSATOSD);    // Default Hue = 180
#endif

                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }
                else if(enumHLWType == _HLW_OUTSIDE_WINDOW)  // case 2
                {
                    ScalerColorPCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);

                    if(pucInverseGammaTableArray != _NULL_POINTER)
                    {
                        ScalerColorPCMGammaRegionEnable(_DB_APPLY_NONE, _ON);
                    }
                    else
                    {
                        ScalerColorPCMGammaRegionEnable(_DB_APPLY_NONE, _OFF);
                    }

#if(_GLOBAL_HUE_SATURATION == _ON)
                    ScalerColorPCMSRGBRegionEnable(_DB_APPLY_NONE, _ON);
#endif

                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);

                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }
                else
                {
                    ScalerColorGammaRegionEnable(enumSelRegion, _DB_APPLY_NONE, _OFF);
                    ScalerColorPCMSetEffectiveRegion(enumSelRegion, _DB_APPLY_NONE);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_POLLING, _OFF);
                    ScalerColorPCMInputGammaEnable(_FUNCTION_ON);
                    ScalerColorPCMLoadTable(enumPCMMode, pucIGammaTableArray, pucOGammaTableArray, pucColorMatrixArray, ucPCMBankNum, usLength);
                    ScalerColorPCMRegionEnable(enumSelRegion, _DB_APPLY_NO_POLLING, _ON);
                }

                break;

            default:
                break;
        }
    }
}

#endif // End ofif(_PCM_FUNCTION == _ON)
