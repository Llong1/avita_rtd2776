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
// ID Code      : RL6193_Series_FormatConversion.c No.0000
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
EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(EnumInputDataPath enumInputDataPath);
void ScalerFmtCnvInitialSetting(EnumSourceSearchPort enumSourceSearchPort, EnumInputDataPath enumInputDataPath);

void ScalerFmtCnvFinalSetting(EnumSourceSearchPort enumSourceSearchPort, EnumInputDataPath enumInputDataPath, bit bWait);
void ScalerFmtCnvSetSourceType(EnumInputDataPath enumInputDataPath, EnumFormatConversionSourceType enumFormatConversionSourceType);
EnumSourceSearchPort ScalerFmtCnvGetInputPortType(EnumInputDataPath enumInputDataPath);

void ScalerFmtCnvFtoPControl(EnumInputDataPath enumInputDataPath, bit bEnable);
bit ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(EnumInputDataPath enumInputDataPath);
void ScalerFmtCnvSetBackgroundColor(EnumInputDataPath enumInputDataPath);

#if(_HDMI_2_0_SUPPORT == _ON)

void ScalerFmtCnv420To422FinalSetting(EnumSourceSearchPort enumSourceSearchPort);

#if(_D0_HDMI_2_0_SUPPORT == _ON)
void ScalerFmtCnv420To422D0InitialSetting(void);
void ScalerFmtCnv420To422D0FinalSetting(EnumInputDataPath enumInputDataPath);
bit ScalerFmtCnv420To422D0GetStatus(void);
#endif

#if(_D1_HDMI_2_0_SUPPORT == _ON)
void ScalerFmtCnv420To422D1InitialSetting(void);
void ScalerFmtCnv420To422D1FinalSetting(EnumInputDataPath enumInputDataPath);
bit ScalerFmtCnv420To422D1GetStatus(void);
#endif

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Show format conversion input source
// Input Value  : NONE
// Output Value : Current format conversino source
//--------------------------------------------------
EnumFormatConversionSourceType ScalerFmtCnvGetSourceType(EnumInputDataPath enumInputDataPath)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1:
            return (EnumFormatConversionSourceType)(ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

        case _INPUT_PATH_M2:
            return (EnumFormatConversionSourceType)(ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        case _INPUT_PATH_S1_S2:
        case _INPUT_PATH_S1:
            return (EnumFormatConversionSourceType)(ScalerGetBit(P31_01_FC_INPUT_SEL_P23, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);

        case _INPUT_PATH_S2:
            return (EnumFormatConversionSourceType)(ScalerGetBit(P31_01_FC_INPUT_SEL_P23, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

        default:
            return _FC_SOURCE_NONE;
    }
}

//--------------------------------------------------
// Description  : Initialize for format conversion
// Input Value  : enumSourceSearchPort --> input port
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvInitialSetting(EnumSourceSearchPort enumSourceSearchPort, EnumInputDataPath enumInputDataPath)
{
    BYTE ucSourceSetting = 0;

    // Enable reset path
    ScalerFmtCnvResetPath(enumInputDataPath, _ENABLE);

    switch(enumSourceSearchPort)
    {
        case _A0_INPUT_PORT:

            // Set source index to A0
            ucSourceSetting = _FC_SOURCE_ADC;
            break;

        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif
            // Set source index to D0
            ucSourceSetting = _FC_SOURCE_D0;
            break;

        case _D1_INPUT_PORT:

            // Set source index to D1
            ucSourceSetting = _FC_SOURCE_D1;
            break;

        case _D2_INPUT_PORT:

            // Set source index to D2
            ucSourceSetting = _FC_SOURCE_D2;
            break;

        case _D3_INPUT_PORT:

            // Set source index to D3
            ucSourceSetting = _FC_SOURCE_D3;
            break;

        case _D4_INPUT_PORT:

            // Set source index to D4
            ucSourceSetting = _FC_SOURCE_D4;
            break;

        case _D5_INPUT_PORT:

            // Set source index to D5
            ucSourceSetting = _FC_SOURCE_D5;
            break;

        default:
            break;
    }

    // Set format conversion source type
    ScalerFmtCnvSetSourceType(enumInputDataPath, ucSourceSetting);

    // Check input pixel rate
    if(ScalerSyncGetInputPixelClk(ScalerFmtCnvGetInputPortType(enumInputDataPath)) > _DATA_PATH_SPEED_LIMIT)
    {
        ScalerFmtCnvHalfSDSetFirstPixel(enumInputDataPath, 0);

        // Enable 1/2 scaling down
        ScalerFmtCnvHalfSDControl(enumInputDataPath, _ENABLE);
    }
    else
    {
        // Disable 1/2 scaling down
        ScalerFmtCnvHalfSDControl(enumInputDataPath, _DISABLE);
    }

    // Disable F-to-P
    ScalerFmtCnvFtoPControl(enumInputDataPath, _DISABLE);

    // Disable reset path
    ScalerFmtCnvResetPath(enumInputDataPath, _DISABLE);
}

//--------------------------------------------------
// Description  : Final format conversion setting
// Input Value  : enumSourceSearchPort --> input port
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFinalSetting(EnumSourceSearchPort enumSourceSearchPort, EnumInputDataPath enumInputDataPath, bit bWait)
{
    WORD usHwidth = GET_INPUT_TIMING_HWIDTH();

    enumSourceSearchPort = enumSourceSearchPort;

    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_S1_S2:

#if(_D0_HDMI_2_0_SUPPORT == _ON)
            // Check 420 status
            if(enumSourceSearchPort == _D0_INPUT_PORT)
            {
                if(ScalerFmtCnv420To422D0GetStatus() == _TRUE)
                {
                    usHwidth = (usHwidth << 1);
                }
            }
#endif

#if(_D1_HDMI_2_0_SUPPORT == _ON)
            if(enumSourceSearchPort == _D1_INPUT_PORT)
            {
                if(ScalerFmtCnv420To422D1GetStatus() == _TRUE)
                {
                    usHwidth = (usHwidth << 1);
                }
            }
#endif
            // Set main F-to-P FIFO
            ScalerFmtCnvFtoPSetFifo(enumInputDataPath, usHwidth, GET_INPUT_TIMING_VSTART());

            // Enable main F-to-P
            ScalerFmtCnvFtoPControl(enumInputDataPath, _ENABLE);

            if(bWait == _WAIT)
            {
                // Wait 4 IVS after format conversion setting
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
            }

            if(enumInputDataPath == _INPUT_PATH_M1_M2)
            {
                // Clear VGIP Interlace Toggle Flag
                ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
            }
            else
            {
                // Clear VGIP Interlace Toggle Flag
                ScalerSetBit(P80_1A_S1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
            }

            break;

        default:

#if(_4P_DISPLAY_SUPPORT == _ON)
            if(ScalerSyncGetInputPixelClk(ScalerFmtCnvGetInputPortType(enumInputDataPath)) > _DATA_PATH_SPEED_LIMIT)
            {
                // Enable half scaling down
                ScalerFmtCnvHalfSDControl(enumInputDataPath, _ENABLE);
            }

            if(bWait == _WAIT)
            {
                // Wait 4 IVS after format conversion setting
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
            }

            // Clear VGIP Interlace Toggle Flag
            switch(enumInputDataPath)
            {
                case _INPUT_PATH_M1:
                    ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
                    break;
                case _INPUT_PATH_M2:
                    ScalerSetBit(P40_1A_M2_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
                    break;
                case _INPUT_PATH_S1:
                    ScalerSetBit(P80_1A_S1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
                    break;
                case _INPUT_PATH_S2:
                    ScalerSetBit(PC0_1A_S2_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
                    break;

                default:
                    break;
            }
#endif  // End of #if(_4P_DISPLAY_SUPPORT == _ON)

            break;
    }
}

//--------------------------------------------------
// Description  : Assign source type for specific input data path
// Input Value  : enumInputDataPath --> target input path
//                enumFormatConversionSourceType --> target source type
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetSourceType(EnumInputDataPath enumInputDataPath, EnumFormatConversionSourceType enumFormatConversionSourceType)
{
    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2:

            // Set path 0 & 1
            ScalerSetByte(P31_00_FC_INPUT_SEL_P01, ((enumFormatConversionSourceType << 4) | enumFormatConversionSourceType));

            // Disable clock gating
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _INPUT_PATH_M1:

            // Set path 0
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumFormatConversionSourceType << 4));

            // Disable clock gating
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT0, _BIT0);
            break;


        case _INPUT_PATH_M2:

            // Set path 1
            ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumFormatConversionSourceType);

            // Disable clock gating
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT1, _BIT1);
            break;

        case _INPUT_PATH_S1_S2:
            // Set path 2 & 3
            ScalerSetByte(P31_01_FC_INPUT_SEL_P23, ((enumFormatConversionSourceType << 4) | enumFormatConversionSourceType));

            // Disable clock gating
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
            break;

        case _INPUT_PATH_S1:
            // Set path 2
            ScalerSetBit(P31_01_FC_INPUT_SEL_P23, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumFormatConversionSourceType << 4));

            // Disable clock gating
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT2, _BIT2);
            break;

        case _INPUT_PATH_S2:
            // Set path 3
            ScalerSetBit(P31_01_FC_INPUT_SEL_P23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumFormatConversionSourceType);

            // Disable clock gating
            ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT3, _BIT3);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Show format conversion input port type
// Input Value  : input data path
// Output Value : Current port
//--------------------------------------------------
EnumSourceSearchPort ScalerFmtCnvGetInputPortType(EnumInputDataPath enumInputDataPath)
{
    BYTE ucSourceType = 0x00;

    switch(enumInputDataPath)
    {
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1:
            ucSourceType = (ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
            break;

        case _INPUT_PATH_M2:
            ucSourceType = ScalerGetBit(P31_00_FC_INPUT_SEL_P01, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            break;

        case _INPUT_PATH_S1_S2:
        case _INPUT_PATH_S1:
            ucSourceType = (ScalerGetBit(P31_01_FC_INPUT_SEL_P23, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4);
            break;

        case _INPUT_PATH_S2:
            ucSourceType = ScalerGetBit(P31_01_FC_INPUT_SEL_P23, (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            break;

        default:
            return _NO_INPUT_PORT;
    }

    switch(ucSourceType)
    {
        case _FC_SOURCE_ADC:
            return _A0_INPUT_PORT;

        case _FC_SOURCE_D0:
            return _D0_INPUT_PORT;

        case _FC_SOURCE_D1:
            return _D1_INPUT_PORT;

        case _FC_SOURCE_D2:
            return _D2_INPUT_PORT;

        case _FC_SOURCE_D3:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            return _D2_INPUT_PORT;
#else
            return _D3_INPUT_PORT;
#endif

        case _FC_SOURCE_D4:

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            return _D3_INPUT_PORT;
#else
            return _D4_INPUT_PORT;
#endif

        case _FC_SOURCE_D5:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            return _D4_INPUT_PORT;
#else
            return _D5_INPUT_PORT;
#endif

        default:
            return _NO_INPUT_PORT;
    }
}

//--------------------------------------------------
// Description  : Control for even/odd
// Input Value  : _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFtoPControl(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    if(enumInputDataPath <= _INPUT_PATH_M1_M2)
    {
        if(bEnable == _ENABLE)
        {
#if(_VGA_SUPPORT == _ON)
            if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
            {
                // Enable VS delay 8 line to enlarge front porch
                if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x08))
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT1, _BIT1);
                }
            }

            // Enable Main F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
        else
        {
            // Disable VS delay 8 line; Disable extended DEN
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT7 | _BIT6 | _BIT3 | _BIT1), 0x00);

            // Disable Main F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT7 | _BIT6), 0x00);
        }
    }
    else
    {
        if(bEnable == _ENABLE)
        {
#if(_VGA_SUPPORT == _ON)
            if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
            {
                // Enable VS delay 8 line to enlarge front porch
                if(GET_ACTIVE_V_START() >= (_VGIP_IV_CAPTURE_MIN_VALUE * 2 + 0x08))
                {
                    ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT0, _BIT0);
                }
            }

            // Enable Sub F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
        }
        else
        {
            // Disable VS delay 8 line; Disable extended DEN
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT5 | _BIT4 | _BIT2 | _BIT0), 0x00);

            // Disable Sub F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~(_BIT3 | _BIT2), 0x00);
        }
    }

    if((bEnable == _ENABLE) && (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE))
    {
        // Set interlace for E/O mode
        ScalerFmtCnvFtoPInterlaceSetting(enumInputDataPath);
    }
}

//--------------------------------------------------
// Description  : Check conditions for E/O mode or single path mode
// Input Value  : input data path
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFmtCnvGetHalfDataPathEvenOddModeStatus(EnumInputDataPath enumInputDataPath)
{
    enumInputDataPath = enumInputDataPath;

#if(_FORMAT_CONVERSION_FORCE_EO_MODE == _ON)

    // Force E/O mode
    return _FALSE;

#else

    // Check if 1/2 H freq. > measure H freq. min
    if((GET_INPUT_TIMING_HFREQ() >> 1) < _MEASURE_H_FREQ_MIN)
    {
        return _TRUE;
    }

#if(_VGA_SUPPORT == _ON)
    if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
    {
        // Check if H-Width is ODD integer, Select Single Path
        if((GET_INPUT_TIMING_HWIDTH() % 2) != 0x00)
        {
            return _TRUE;
        }
    }

    if(ScalerGlobalGetIDCode() <= _RL6193_VER_C_ID_CODE)
    {
#if(_HDMI_2_0_SUPPORT == _ON)
        // E/O mode for 420 format
        switch(ScalerFmtCnvGetSourceType(enumInputDataPath))
        {
#if(_D0_HDMI_2_0_SUPPORT == _ON)
            case _FC_SOURCE_D0:

                if(ScalerFmtCnv420To422D0GetStatus() == _TRUE)
                {
                    return _FALSE;
                }
                break;
#endif

#if(_D1_HDMI_2_0_SUPPORT == _ON)
            case _FC_SOURCE_D1:

                if(ScalerFmtCnv420To422D1GetStatus() == _TRUE)
                {
                    return _FALSE;
                }
                break;
#endif

            default:

                break;
        }
#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

        // Single mode for pixel clock under 300M Hz
        if(ScalerSyncGetInputPixelClk(ScalerFmtCnvGetInputPortType(enumInputDataPath)) <= _DATA_PATH_SPEED_LIMIT)
        {
            // Enable I-domain pattern gen. for EMI issue
            switch(enumInputDataPath)
            {
                case _INPUT_PATH_M1_M2:
                    ScalerSetBit(P40_10_M2_VGIP_CTRL, ~_BIT7, _BIT7); // M2
                    break;

                case _INPUT_PATH_S1_S2:
                    ScalerSetBit(PC0_10_S2_VGIP_CTRL, ~_BIT7, _BIT7); // S2
                    break;

                default:
                    break;
            }

            return _TRUE;
        }

        return _FALSE;
    }
    else
    {
        // Check if V height is odd
#if(_VGA_SUPPORT == _ON)
        if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
        {
            if((ScalerSyncGetInputPixelClk(ScalerFmtCnvGetInputPortType(enumInputDataPath)) <= _DATA_PATH_SPEED_LIMIT) &&
               ((LOBYTE(GET_INPUT_TIMING_VHEIGHT()) % 2) != 0))
            {
                g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd += 1;
                return _TRUE;
            }
        }

        switch(enumInputDataPath)
        {
            case _INPUT_PATH_M1_M2:
                return (g_pstRegionTimingInfo[0].stTimingInfo.b1Interlace == _TRUE);

            case _INPUT_PATH_S1_S2:
                return (g_pstRegionTimingInfo[1].stTimingInfo.b1Interlace == _TRUE);

            default:
                return _FALSE;
        }
    }
#endif // End of #if(_FORMAT_CONVERSION_FORCE_EO_MODE == _ON)
}

//--------------------------------------------------
// Description  : Set background color for format conversion
// Input Value  : enumInputDataPath --> input path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetBackgroundColor(EnumInputDataPath enumInputDataPath)
{
    // Capture last line for odd V height (before E/O)
    if((GET_INPUT_TIMING_VHEIGHT() % 2) == 0x01)
    {
        switch(enumInputDataPath)
        {
            case _INPUT_PATH_M1_M2:
                // Extend format conversion DEN
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT3, _BIT3);

                // Enlarge H width by 1
                ScalerSetWord(P31_07_FC_FORMAT_PRO_MAIN_0, (ScalerGetWord(P31_07_FC_FORMAT_PRO_MAIN_0) + 1));
                break;

            case _INPUT_PATH_S1_S2:
                // Extend format conversion DEN
                ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~_BIT2, _BIT2);

                // Enlarge H width by 1
                ScalerSetWord(P31_09_FC_FORMAT_PRO_SUB_0, (ScalerGetWord(P31_09_FC_FORMAT_PRO_SUB_0) + 1));
                break;

            default:
                break;
        }
    }
}

#if(_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Final setting for D0/D1 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422FinalSetting(EnumSourceSearchPort enumSourceSearchPort)
{
    // Check 420 setting for D0/D1
    switch(enumSourceSearchPort)
    {
        case _D0_INPUT_PORT:

#if(_D0_HDMI_2_0_SUPPORT == _ON)
            // Final 420 setting
            ScalerFmtCnv420To422D0FinalSetting(GET_MEASURE_INPUT_PATH());
#endif
            break;

        case _D1_INPUT_PORT:

#if(_D1_HDMI_2_0_SUPPORT == _ON)
            // Final 420 setting
            ScalerFmtCnv420To422D1FinalSetting(GET_MEASURE_INPUT_PATH());
#endif
            break;

        default:
            break;
    }
}

#if(_D0_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial setting for D0 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D0InitialSetting(void)
{
    // Disble 420-to-422
    ScalerColor420To422D0Enable(_FUNCTION_OFF);
}

//--------------------------------------------------
// Description  : Final setting for D0 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D0FinalSetting(EnumInputDataPath enumInputDataPath)
{
    if(GET_COLOR_SPACE(_D0_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
    {
        // Update actual 420-422 state
        if(ScalerFmtCnvHalfSDGetStatus(enumInputDataPath) == _TRUE)
        {
            ScalerColor420To422D0Setting(GET_ACTIVE_H_START() << 1, GET_ACTIVE_H_WIDTH() << 1);
        }
        else
        {
            ScalerColor420To422D0Setting(GET_ACTIVE_H_START(), GET_ACTIVE_H_WIDTH());
        }
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerColor420To422D0Enable(_FUNCTION_ON);
    }
}

//--------------------------------------------------
// Description  : Get D0 420 block status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerFmtCnv420To422D0GetStatus(void)
{
    return (ScalerGetBit(P31_20_YUV420_TO_YUV422_D0, _BIT7));
}
#endif // Endi of #if(_D0_HDMI_2_0_SUPPORT == _ON)

#if(_D1_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial setting for D1 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D1InitialSetting(void)
{
    // Disble 420-to-422
    ScalerColor420To422D1Enable(_FUNCTION_OFF);
}

//--------------------------------------------------
// Description  : Final setting for D1 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D1FinalSetting(EnumInputDataPath enumInputDataPath)
{
    if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
    {
        // Update actual 420-422 state
        if(ScalerFmtCnvHalfSDGetStatus(enumInputDataPath) == _TRUE)
        {
            ScalerColor420To422D1Setting(GET_ACTIVE_H_START() << 1, GET_ACTIVE_H_WIDTH() << 1);
        }
        else
        {
            ScalerColor420To422D1Setting(GET_ACTIVE_H_START(), GET_ACTIVE_H_WIDTH());
        }
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerColor420To422D1Enable(_FUNCTION_ON);
    }
}

//--------------------------------------------------
// Description  : Get D1 420 block status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerFmtCnv420To422D1GetStatus(void)
{
    return (ScalerGetBit(P31_21_YUV420_TO_YUV422_D1, _BIT7));
}
#endif // End of #if(_D1_HDMI_2_0_SUPPORT == _ON)

#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

