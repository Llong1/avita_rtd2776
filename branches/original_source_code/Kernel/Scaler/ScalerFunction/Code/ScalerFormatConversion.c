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
// ID Code      : ScalerFormatConversion.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_FMT_CNV__

#include "ScalerFunctionInclude.h"

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
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
#if(_MULTI_DISPLAY_MAX != 0x01)
void ScalerFmtCnvDuplicateSetting(EnumInputDataPath enumInputDataPath, EnumInputDataPath enumDuplicatePath);
#endif

void ScalerFmtCnvResetPath(EnumInputDataPath enumInputDataPath, bit bEnable);

void ScalerFmtCnvHalfSDControl(EnumInputDataPath enumInputDataPath, bit bEnable);
void ScalerFmtCnvHalfSDSetFirstPixel(EnumInputDataPath enumInputDataPath, WORD usHstart);
bit ScalerFmtCnvHalfSDGetStatus(EnumInputDataPath enumInputDataPath);

void ScalerFmtCnvFtoPSetFifo(EnumInputDataPath enumInputDataPath, WORD usHwidth, WORD usVstart);
bit ScalerFmtCnvFtoPGetStatus(EnumInputDataPath enumInputDataPath);
void ScalerFmtCnvFtoPInterlaceSetting(EnumInputDataPath enumInputDataPath);

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
EnumFormatConversionSourceType ScalerFmtCnvConvertPortType(EnumSourceSearchPort enumSourceSearchPort);
EnumInputDataPath ScalerFmtCnvGetInputPath(EnumSourceSearchPort enumSourceSearchPort);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MULTI_DISPLAY_MAX != 0x01)
//--------------------------------------------------
// Description  : Duplicate input data path setting in format conversion
// Input Value  : enumInputDataPath --> target path
//                enumDuplicatePath --> path being duplicated
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvDuplicateSetting(EnumInputDataPath enumInputDataPath, EnumInputDataPath enumDuplicatePath)
{
    // Duplicate input source select
    ScalerFmtCnvSetSourceType(enumInputDataPath, ScalerFmtCnvGetSourceType(enumDuplicatePath));

    if(enumInputDataPath == _INPUT_PATH_M1_M2)
    {
        // Duplicate 1/2 SD from S1/S2
        ScalerSetBit(P31_05_FC_SD_CTRL, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (ScalerGetBit(P31_05_FC_SD_CTRL, (_BIT5 | _BIT4 | _BIT1 | _BIT0)) << 2));

        // Duplicate even/odd status from S1/S2
        ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 4));
        ScalerSetWord(P31_07_FC_FORMAT_PRO_MAIN_0, ScalerGetWord(P31_09_FC_FORMAT_PRO_SUB_0));

        // Duplicate delay 8 line status from S1/S2
        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT3 | _BIT1), (ScalerGetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, (_BIT2 | _BIT0)) << 1));

        // Duplicate Vst toggle status from S1/S2
        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT7 | _BIT6), (ScalerGetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, (_BIT5 | _BIT4)) << 2));

#if(_VGA_SUPPORT == _ON)
        if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
        {
            // Wait 4 IVS after format conversion setting
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_M1_M2);

            // Clear VGIP Interlace Toggle Flag
            ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
            ScalerSetBit(P40_1A_M2_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        }
    }
    else if(enumInputDataPath == _INPUT_PATH_S1_S2)
    {
        // Duplicate 1/2 SD from M1/M2
        ScalerSetBit(P31_05_FC_SD_CTRL, ~(_BIT5 | _BIT4 | _BIT1 | _BIT0), (ScalerGetBit(P31_05_FC_SD_CTRL, (_BIT7 | _BIT6 | _BIT3 | _BIT2)) >> 2));

        // Duplicate even/odd status from M1/M2
        ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4));
        ScalerSetWord(P31_09_FC_FORMAT_PRO_SUB_0, ScalerGetWord(P31_07_FC_FORMAT_PRO_MAIN_0));

        // Duplicate delay 8 line status from M1/M2
        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT2 | _BIT0), (ScalerGetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, (_BIT3 | _BIT1)) >> 1));

        // Duplicate Vst toggle status from M1/M2
        ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT5 | _BIT4), (ScalerGetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, (_BIT7 | _BIT6)) >> 2));

#if(_VGA_SUPPORT == _ON)
        if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
        {
            // Wait 4 IVS after format conversion setting
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_S1_S2);
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_S1_S2);
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_S1_S2);
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, _INPUT_PATH_S1_S2);

            // Clear VGIP Interlace Toggle Flag
            ScalerSetBit(P80_1A_S1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
            ScalerSetBit(PC0_1A_S2_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
        }
    }
#if(_4P_DISPLAY_SUPPORT == _ON)
    else
    {
        BYTE ucMaskFrom = 0x00;
        BYTE ucMaskTo = 0x00;

        // Disable E/O mode
        ScalerFmtCnvFtoPControl(enumInputDataPath, _DISABLE);

        // Get input bit position
        switch(enumInputDataPath)
        {
            case _INPUT_PATH_M1:
                ucMaskTo = _BIT3;
                break;

            case _INPUT_PATH_M2:
                ucMaskTo = _BIT2;
                break;

            case _INPUT_PATH_S1:
                ucMaskTo = _BIT1;
                break;

            case _INPUT_PATH_S2:
                ucMaskTo = _BIT0;
                break;

            default:
                break;
        }

        // Get duplicate bit position
        switch(enumDuplicatePath)
        {
            case _INPUT_PATH_M1:
                ucMaskFrom = _BIT3;
                break;

            case _INPUT_PATH_M2:
                ucMaskFrom = _BIT2;
                break;

            case _INPUT_PATH_S1:
                ucMaskFrom = _BIT1;
                break;

            case _INPUT_PATH_S2:
                ucMaskFrom = _BIT0;
                break;

            default:
                break;
        }

        // Duplicate 1/2 SD status in 4P mode
        ScalerSetBit(P31_05_FC_SD_CTRL, ~ucMaskTo, ((ScalerGetBit(P31_05_FC_SD_CTRL, ucMaskFrom) == 0x00) ? 0x00 : ucMaskTo));
        ScalerSetBit(P31_05_FC_SD_CTRL, ~(ucMaskTo << 4), ((ScalerGetBit(P31_05_FC_SD_CTRL, (ucMaskFrom << 4)) == 0x00) ? 0x00 : (ucMaskTo << 4)));
    }
#endif // End of #if(_4P_DISPLAY_SUPPORT == _ON)
}
#endif // End of #if(_MULTI_DISPLAY_MAX != 0x01)

//--------------------------------------------------
// Description  : Reset input data path in format conversion
// Input Value  : enumInputDataPath --> input data path
//                bEnable --> enable/disable after reset
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvResetPath(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    BYTE ucMask = 0x00;

    switch(enumInputDataPath)
    {
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        case _INPUT_PATH_ALL:
            ucMask = (_BIT7 | _BIT6 | _BIT5 | _BIT4);
            break;
#endif

        case _INPUT_PATH_M1_M2:
            ucMask = (_BIT5 | _BIT4);
            break;

        case _INPUT_PATH_M1:
            ucMask = (_BIT4);
            break;

        case _INPUT_PATH_M2:
            if(ScalerGetBit(P0_10_M1_VGIP_CTRL, _BIT0) == _BIT0)
            {
                ucMask = (_BIT5);
            }
            else
            {
                // Reset M1 & M2 when M1 VGIP not activated
                ucMask = (_BIT5 | _BIT4);
            }
            break;

        case _INPUT_PATH_S1_S2:
            ucMask = (_BIT7 | _BIT6);
            break;

        case _INPUT_PATH_S1:
            ucMask = (_BIT6);
            break;

        case _INPUT_PATH_S2:
            if(ScalerGetBit(P80_10_S1_VGIP_CTRL, _BIT0) == _BIT0)
            {
                ucMask = (_BIT7);
            }
            else
            {
                // Reset S1 & S2 when S1 VGIP not activated
                ucMask = (_BIT7 | _BIT6);
            }
            break;

        default:
            break;
    }

    if(bEnable == _TRUE)
    {
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~ucMask, ucMask);
    }
    else
    {
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~ucMask, 0x00);
    }
}

//--------------------------------------------------
// Description  : Control half scaling down on/off
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvHalfSDControl(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    BYTE ucMask = 0;

    if((enumInputDataPath & _INPUT_PATH_M1) != 0)
    {
        ucMask |= _BIT7;
    }

    if((enumInputDataPath & _INPUT_PATH_M2) != 0)
    {
        ucMask |= _BIT6;
    }

    if((enumInputDataPath & _INPUT_PATH_S1) != 0)
    {
        ucMask |= _BIT5;
    }

    if((enumInputDataPath & _INPUT_PATH_S2) != 0)
    {
        ucMask |= _BIT4;
    }

    if(bEnable == _ENABLE)
    {
        // Enable 1/2 SD
        ScalerSetBit(P31_05_FC_SD_CTRL, ~ucMask, 0x00);

        if((enumInputDataPath & _INPUT_PATH_M1_M2) != 0x00)
        {
            // Main output from 1/2 SD
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, 0x00);
        }

        if((enumInputDataPath & _INPUT_PATH_S1_S2) != 0x00)
        {
            // Sub output from 1/2 SD
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT3, 0x00);
        }
    }
    else
    {
        // Disable 1/2 SD
        ScalerSetBit(P31_05_FC_SD_CTRL, ~ucMask, ucMask);
    }
}

//--------------------------------------------------
// Description  : Set the first pixel for half scaling down
// Input Value  : usHstart --> H start
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvHalfSDSetFirstPixel(EnumInputDataPath enumInputDataPath, WORD usHstart)
{
    BYTE ucMask = 0;

    if((enumInputDataPath & _INPUT_PATH_M1) != 0)
    {
        ucMask |= _BIT3;
    }

    if((enumInputDataPath & _INPUT_PATH_M2) != 0)
    {
        ucMask |= _BIT2;
    }

    if((enumInputDataPath & _INPUT_PATH_S1) != 0)
    {
        ucMask |= _BIT1;
    }

    if((enumInputDataPath & _INPUT_PATH_S2) != 0)
    {
        ucMask |= _BIT0;
    }

    if((LOBYTE(usHstart) & _BIT0) == 0x00)
    {
        // Set first pixel = even
        ScalerSetBit(P31_05_FC_SD_CTRL, ~ucMask, ucMask);
    }
    else
    {
        // Set first pixel = odd
        ScalerSetBit(P31_05_FC_SD_CTRL, ~ucMask, 0x00);
    }
}

//--------------------------------------------------
// Description  : Half Scaling down status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFmtCnvHalfSDGetStatus(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        case _INPUT_PATH_ALL:
#endif
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1:
            return ((ScalerGetBit(P31_05_FC_SD_CTRL, _BIT7) == 0x00) && (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT7) == 0x00));

        case _INPUT_PATH_M2:
            return ((ScalerGetBit(P31_05_FC_SD_CTRL, _BIT6) == 0x00) && (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT7) == 0x00));

        case _INPUT_PATH_S1_S2:
        case _INPUT_PATH_S1:
            return ((ScalerGetBit(P31_05_FC_SD_CTRL, _BIT5) == 0x00) && (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT3) == 0x00));

        case _INPUT_PATH_S2:
            return ((ScalerGetBit(P31_05_FC_SD_CTRL, _BIT4) == 0x00) && (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT3) == 0x00));

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Set even/odd resolution
// Input Value  : usHwidth, usVstart  --> resolution for even/odd
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPSetFifo(EnumInputDataPath enumInputDataPath, WORD usHwidth, WORD usVstart)
{
    if((enumInputDataPath & _INPUT_PATH_M1_M2) != 0x00)
    {
        if((LOBYTE(usVstart) & _BIT0) == _BIT0)
        {
            // Set vertical start field = even
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT4, _BIT4);
        }
        else
        {
            // Set vertical start field = odd
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT4, 0x00);
        }

        // Toggle vertical start field for VS bypass
        if(ScalerGetBit(P0_11_M1_VGIP_SIGINV, _BIT6) == _BIT6)
        {
            ScalerSetByte(P31_06_FC_EO_LINE_CTRL, (ScalerGetByte(P31_06_FC_EO_LINE_CTRL) ^ _BIT4));
        }

        // Set horizontal width
        ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHwidth) & 0x1F));
        ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, LOBYTE(usHwidth));
    }

    if((enumInputDataPath & _INPUT_PATH_S1_S2) != 0x00)
    {
        if((LOBYTE(usVstart) & _BIT0) == _BIT0)
        {
            // Set vertical start field = even
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT0, _BIT0);
        }
        else
        {
            // Set vertical start field = odd
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT0, 0x00);
        }

        // Toggle vertical start field for VS bypass
        if(ScalerGetBit(P80_11_S1_VGIP_SIGINV, _BIT6) == _BIT6)
        {
            ScalerSetByte(P31_06_FC_EO_LINE_CTRL, (ScalerGetByte(P31_06_FC_EO_LINE_CTRL) ^ _BIT0));
        }

        // Set horizontal width
        ScalerSetBit(P31_09_FC_FORMAT_PRO_SUB_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHwidth) & 0x1F));
        ScalerSetByte(P31_0A_FC_FORMAT_PRO_SUB_1, LOBYTE(usHwidth));
    }
}

//--------------------------------------------------
// Description  : EVEN/Odd status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFmtCnvFtoPGetStatus(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        case _INPUT_PATH_ALL:
#endif
        case _INPUT_PATH_M1_M2:
            return (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT7) == _BIT7);

        case _INPUT_PATH_S1_S2:
            return (ScalerGetBit(P31_06_FC_EO_LINE_CTRL, _BIT3) == _BIT3);

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set V start line toggle for E/O mode
// Input Value  : enumInputDataPath --> target input path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPInterlaceSetting(EnumInputDataPath enumInputDataPath)
{
    if((enumInputDataPath & _INPUT_PATH_M1_M2) == _INPUT_PATH_M1_M2)
    {
        // Check V start changes by field
        if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT6) == 0x00)
        {
            // Disable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT7, 0x00);
        }
        else
        {
            // Enable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT7, _BIT7);

            // Check V start is even or odd
            if((GET_ACTIVE_V_START() & 0x0001) == 0x0001)
            {
                // Check the field with larger V start
                if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, 0x00);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, _BIT6);
                }

                // Disable VGIP odd delay 1 line
                ScalerSetBit(P0_13_M1_VGIP_ODD_CTRL, ~_BIT6, 0x00);
                ScalerSetBit(P40_13_M2_VGIP_ODD_CTRL, ~_BIT6, 0x00);
            }
            else
            {
                // Check the field with larger V start
                if(ScalerGetBit(P0_13_M1_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, _BIT6);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT6, 0x00);
                }
            }
        }
    }

    if((enumInputDataPath & _INPUT_PATH_S1_S2) == _INPUT_PATH_S1_S2)
    {
        if(ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, _BIT6) == 0x00)
        {
            // Disable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT5, 0x00);
        }
        else
        {
            // Enable Vst toggle
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT5, _BIT5);

            // Check V start is even or odd
            if((GET_ACTIVE_V_START() & 0x0001) == 0x0001)
            {
                // Check the field with larger V start
                if(ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT4, 0x00);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT4, _BIT4);
                }

                // Disable VGIP odd delay 1 line
                ScalerSetBit(P80_13_S1_VGIP_ODD_CTRL, ~_BIT6, 0x00);
                ScalerSetBit(PC0_13_S2_VGIP_ODD_CTRL, ~_BIT6, 0x00);
            }
            else
            {
                // Check the field with larger V start
                if(ScalerGetBit(P80_13_S1_VGIP_ODD_CTRL, _BIT7) == 0x00)
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT4, _BIT4);
                }
                else
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT4, 0x00);
                }
            }
        }
    }
}

#if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Convert enumeration from source port type to format conversion source type
// Input Value  : source port type
// Output Value : format conversion source type
//--------------------------------------------------
EnumFormatConversionSourceType ScalerFmtCnvConvertPortType(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
        case _A0_INPUT_PORT:
            return _FC_SOURCE_ADC;

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            return _FC_SOURCE_D0;

        case _D1_INPUT_PORT:
            return _FC_SOURCE_D1;

        case _D2_INPUT_PORT:
            return _FC_SOURCE_D2;

        case _D3_INPUT_PORT:
            return _FC_SOURCE_D3;

        case _D4_INPUT_PORT:
            return _FC_SOURCE_D4;

        case _D5_INPUT_PORT:
            return _FC_SOURCE_D5;

        default:
            return _FC_SOURCE_NONE;
    }
}

//--------------------------------------------------
// Description  : Get input data path corresponds to specific source type
// Input Value  : source port type
// Output Value : input data path
//--------------------------------------------------
EnumInputDataPath ScalerFmtCnvGetInputPath(EnumSourceSearchPort enumSourceSearchPort)
{
    EnumFormatConversionSourceType enumFmtCnvSource = ScalerFmtCnvConvertPortType(enumSourceSearchPort);

    if(ScalerFmtCnvGetSourceType(_INPUT_PATH_M1) == enumFmtCnvSource)
    {
        return _INPUT_PATH_M1;
    }
    else if(ScalerFmtCnvGetSourceType(_INPUT_PATH_M2) == enumFmtCnvSource)
    {
        return _INPUT_PATH_M2;
    }
    else if(ScalerFmtCnvGetSourceType(_INPUT_PATH_S1) == enumFmtCnvSource)
    {
        return _INPUT_PATH_S1;
    }
    else if(ScalerFmtCnvGetSourceType(_INPUT_PATH_S2) == enumFmtCnvSource)
    {
        return _INPUT_PATH_S2;
    }
    else
    {
        return _INPUT_PATH_NONE;
    }
}
#endif // End of #if(_VGA_CHROMA_PATTERN12_SUPPORT == _ON)

#endif // End of #if(_FORMAT_CONVERSION_SUPPORT == _ON)
