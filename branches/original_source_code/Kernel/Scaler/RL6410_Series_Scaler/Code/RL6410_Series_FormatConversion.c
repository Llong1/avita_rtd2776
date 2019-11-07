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
// ID Code      : RL6410_Series_FormatConversion.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _FB_OFF = 0x00,
    _FB_ON = _BIT7,
    _FB_FULL_TO_FB = (_BIT7 | _BIT6),
} EnumFrontBackMode;

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

#if(_VGA_SUPPORT == _ON)
void ScalerFmtCnvVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable);
#endif

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
void ScalerFmtCnvFBSetOutputFormat(WORD usHwidth, BYTE ucHstart, BYTE ucHSwidth);
void ScalerFmtCnvFBSetStatus(EnumFrontBackMode enumFrontBackMode);
void ScalerFmtCnvFBSetInitialExtension(void);
#endif

bit ScalerFmtCnvFBGetStatus(void);

#if(_HDMI_2_0_SUPPORT == _ON)

void ScalerFmtCnv420To422FinalSetting(EnumSourceSearchPort enumSourceSearchPort);

#if(_D2_HDMI_2_0_SUPPORT == _ON)
void ScalerFmtCnv420To422D2InitialSetting(void);
void ScalerFmtCnv420To422D2FinalSetting(EnumInputDataPath enumInputDataPath);
bit ScalerFmtCnv420To422D2GetStatus(void);
#endif

#if(_D3_HDMI_2_0_SUPPORT == _ON)
void ScalerFmtCnv420To422D3InitialSetting(void);
void ScalerFmtCnv420To422D3FinalSetting(EnumInputDataPath enumInputDataPath);
bit ScalerFmtCnv420To422D3GetStatus(void);
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
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        case _INPUT_PATH_ALL:
#endif
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
#if(_VGA_SUPPORT == _ON)
        case _A0_INPUT_PORT:

            // Set source index to A0
            ucSourceSetting = _FC_SOURCE_ADC;
            break;
#endif

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

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(ScalerTMDSRx4GetDualDVIMode() == _TRUE)
            {
                // Set source index to DUAL DVI
                ucSourceSetting = _FC_SOURCE_DUAL_DVI;
            }
            else
#endif
            {
                // Set source index to D4
                ucSourceSetting = _FC_SOURCE_D4;
            }

            break;

        case _D5_INPUT_PORT:

            // Set source index to D5
            ucSourceSetting = _FC_SOURCE_D5;
            break;

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:

            if(GET_D7_SWITCH_SELECT() == _D1_INPUT_PORT)
            {
                // Set source index to D1
                ucSourceSetting = _FC_SOURCE_D1;
            }
            else
            {
                // Set source index to D0
                ucSourceSetting = _FC_SOURCE_D0;
            }

            break;
#endif

        default:
            break;
    }

    // Set format conversion source type
    ScalerFmtCnvSetSourceType(enumInputDataPath, ucSourceSetting);

#if(_VGA_SUPPORT == _ON)
    // Disable VS edge align for VGA
    if(ucSourceSetting == _FC_SOURCE_ADC)
    {
        ScalerFmtCnvVsBypassEnable(enumInputDataPath, _ENABLE);
    }
    else
    {
        ScalerFmtCnvVsBypassEnable(enumInputDataPath, _DISABLE);
    }
#endif

    // Check input pixel rate
#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
    if((enumSourceSearchPort == _D7_INPUT_PORT) &&
       (GET_D7_SWITCH_SELECT() == _D7_INPUT_PORT) &&
       ((ScalerSyncGetInputPixelClk(_D7_INPUT_PORT) / 2) > _DATA_PATH_SPEED_LIMIT))
    {
        ScalerFmtCnvHalfSDSetFirstPixel(enumInputDataPath, 0);

        // Enable 1/2 scaling down
        ScalerFmtCnvHalfSDControl(enumInputDataPath, _ENABLE);
    }
    else
#endif
    {
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
    }

    // Disable F-to-P
    ScalerFmtCnvFtoPControl(enumInputDataPath, _DISABLE);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    // Set extension length to 0
    SET_FMTCNV_EXTENSION_LEN(0);

    // Disable F/B
    ScalerFmtCnvFBSetStatus(_FB_OFF);
#endif

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

#if(_VGA_SUPPORT == _ON)
    if(enumSourceSearchPort == _A0_INPUT_PORT)
    {
        // Enable VS edge align
        ScalerFmtCnvVsBypassEnable(enumInputDataPath, _DISABLE);
    }
#endif

    switch(enumInputDataPath)
    {
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        case _INPUT_PATH_ALL:
#endif
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_S1_S2:

            // Update H width
            switch(enumSourceSearchPort)
            {
#if((_HDMI_2_0_SUPPORT == _ON) && (_D2_HDMI_2_0_SUPPORT == _ON))
                case _D2_INPUT_PORT:
                    // Check 420 status
                    if(ScalerFmtCnv420To422D2GetStatus() == _TRUE)
                    {
                        usHwidth <<= 1;
                    }
                    break;
#endif


#if((_HDMI_2_0_SUPPORT == _ON) && (_D3_HDMI_2_0_SUPPORT == _ON))
                case _D3_INPUT_PORT:
                    if(ScalerFmtCnv420To422D3GetStatus() == _TRUE)
                    {
                        usHwidth <<= 1;
                    }
                    break;
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
                case _D7_INPUT_PORT:
                    // Double H width for dual DP
                    if(GET_D7_SWITCH_SELECT() == _D7_INPUT_PORT)
                    {
                        usHwidth <<= 1;
                    }
                    break;
#endif

                default:
                    break;
            }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(enumInputDataPath == _INPUT_PATH_ALL)
            {
                WORD usHstart = 0;

                // Set E/O H width to half
                usHwidth >>= 1;

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
                if((enumSourceSearchPort == _D7_INPUT_PORT) &&
                   (GET_D7_SWITCH_SELECT() == _D7_INPUT_PORT))
                {
#if(_D7_D0_EMBEDDED_DDCRAM_SIZE == _EDID_SIZE_384)
                    // Set sub to D0
                    ScalerFmtCnvSetSourceType(_INPUT_PATH_M1_M2, _FC_SOURCE_D1);
                    ScalerFmtCnvSetSourceType(_INPUT_PATH_S1_S2, _FC_SOURCE_D0);
#else
                    // Set sub to D1
                    ScalerFmtCnvSetSourceType(_INPUT_PATH_S1_S2, _FC_SOURCE_D1);
#endif

                    // Enable F/B
                    ScalerFmtCnvFBSetStatus(_FB_ON);

                    // H start limit = H blanking / 2
                    usHstart = (GET_INPUT_TIMING_HTOTAL() - GET_INPUT_TIMING_HWIDTH()) / 2;
                }
                else
#endif
                {
                    // Enable full-to-F/B
                    ScalerFmtCnvFBSetStatus(_FB_FULL_TO_FB);

                    // H start limit = H blanking / 4
                    usHstart = (GET_INPUT_TIMING_HTOTAL() - GET_INPUT_TIMING_HWIDTH()) / 4;
                }

                // Set max H start to 0x1E
                if(usHstart > 0x1E)
                {
                    usHstart = 0x1E;
                }

                // Set F/B format
#if((_HDMI_2_0_SUPPORT == _ON) && (_D2_HDMI_2_0_SUPPORT == _ON))
                // Check D2 420 status
                if((enumSourceSearchPort == _D2_INPUT_PORT) && (ScalerFmtCnv420To422D2GetStatus() == _TRUE))
                {
                    ScalerFmtCnvFBSetOutputFormat((GET_INPUT_TIMING_HWIDTH() << 1), usHstart, usHstart - 2);
                }
                else
#endif
                {
#if((_HDMI_2_0_SUPPORT == _ON) && (_D3_HDMI_2_0_SUPPORT == _ON))
                    // Check D3 420 status
                    if((enumSourceSearchPort == _D3_INPUT_PORT) && (ScalerFmtCnv420To422D3GetStatus() == _TRUE))
                    {
                        ScalerFmtCnvFBSetOutputFormat((GET_INPUT_TIMING_HWIDTH() << 1), usHstart, usHstart - 2);
                    }
                    else
#endif
                    {
                        ScalerFmtCnvFBSetOutputFormat(GET_INPUT_TIMING_HWIDTH(), usHstart, usHstart - 2);
                    }
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

            if((enumInputDataPath & _INPUT_PATH_M1_M2) != 0x00)
            {
                // Clear VGIP Interlace Toggle Flag
                ScalerSetBit(P0_1A_M1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
            }

            if((enumInputDataPath & _INPUT_PATH_S1_S2) != 0x00)
            {
                // Clear VGIP Interlace Toggle Flag
                ScalerSetBit(P80_1A_S1_IPV_ACT_LEN_H, ~_BIT5, _BIT5);
            }

            if(enumInputDataPath == _INPUT_PATH_ALL)
            {
                // Clear S1/S2 SRAM overflow/underflow flags
                ScalerSetByte(P31_6F_FB_SRAM_CTRL, 0xFF);

                // Clear extension overflow/underflow flags
                ScalerSetByte(P31_72_FB_EXT_FIFO_CTRL, 0xFF);
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
    if((enumInputDataPath & _INPUT_PATH_M1) != 0)
    {
        // Set path 0
        ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumFormatConversionSourceType << 4));

        // Disable clock gating
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT0, _BIT0);
    }

    if((enumInputDataPath & _INPUT_PATH_M2) != 0)
    {
        // Set path 1
        ScalerSetBit(P31_00_FC_INPUT_SEL_P01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumFormatConversionSourceType);

        // Disable clock gating
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT1, _BIT1);
    }

    if((enumInputDataPath & _INPUT_PATH_S1) != 0)
    {
        // Set path 2
        ScalerSetBit(P31_01_FC_INPUT_SEL_P23, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (enumFormatConversionSourceType << 4));

        // Disable clock gating
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT2, _BIT2);
    }

    if((enumInputDataPath & _INPUT_PATH_S2) != 0)
    {
        // Set path 3
        ScalerSetBit(P31_01_FC_INPUT_SEL_P23, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumFormatConversionSourceType);

        // Disable clock gating
        ScalerSetBit(P31_0D_FC_INPUT_CLK_GATING, ~_BIT3, _BIT3);
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
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        case _INPUT_PATH_ALL:
#endif
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
            return _D3_INPUT_PORT;

        case _FC_SOURCE_D4:
            return _D4_INPUT_PORT;

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
    if((enumInputDataPath & _INPUT_PATH_M1_M2) != 0x00)
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
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, _BIT7);
        }
        else
        {
            // Disable E/O interlace Vst control; Disable VS delay 8 line; Disable extended DEN
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT7 | _BIT6 | _BIT3 | _BIT1), 0x00);

            // Set E/O H width to 0
            ScalerSetBit(P31_07_FC_FORMAT_PRO_MAIN_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P31_08_FC_FORMAT_PRO_MAIN_1, 0x00);

            // Disable Main F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT7, 0x00);
        }
    }

    if((enumInputDataPath & _INPUT_PATH_S1_S2) != 0x00)
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
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT3, _BIT3);
        }
        else
        {
            // Disable E/O interlace Vst control; Disable VS delay 8 line; Disable extended DEN
            ScalerSetBit(P31_0B_FC_FPRMAT_PRO_OUTPUT, ~(_BIT5 | _BIT4 | _BIT2 | _BIT0), 0x00);

            // Set E/O H width to 0
            ScalerSetBit(P31_09_FC_FORMAT_PRO_SUB_0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P31_0A_FC_FORMAT_PRO_SUB_1, 0x00);

            // Disable Sub F-to-P
            ScalerSetBit(P31_06_FC_EO_LINE_CTRL, ~_BIT3, 0x00);
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

#if((_FORMAT_CONVERSION_FORCE_EO_MODE == _ON) || (_D_DOMAIN_PATH == _D_DOMAIN_4_PATH))

    // Force E/O mode
    return _FALSE;

#else

#if(_VGA_SUPPORT == _ON)
    if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
    {
        // Check if H-Width is ODD integer, Select Single Path
        if((GET_INPUT_TIMING_HWIDTH() % 2) != 0x00)
        {
            return _TRUE;
        }

        // Check if V height is odd
        if((ScalerSyncGetInputPixelClk(ScalerFmtCnvGetInputPortType(enumInputDataPath)) <= _DATA_PATH_SPEED_LIMIT) &&
           ((LOBYTE(GET_INPUT_TIMING_VHEIGHT()) % 2) != 0x00))
        {
            g_pstRegionTimingInfoPointer->stAutoActiveData.usVActiveEnd += 1;
            return _TRUE;
        }
    }

    return _FALSE;

#endif // #if((_FORMAT_CONVERSION_FORCE_EO_MODE == _ON) || (_D_DOMAIN_PATH == _D_DOMAIN_4_PATH))
}

//--------------------------------------------------
// Description  : Set background color for format conversion
// Input Value  : enumInputDataPath --> input path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvSetBackgroundColor(EnumInputDataPath enumInputDataPath)
{
    if((enumInputDataPath & _INPUT_PATH_M1) != 0)
    {
        // M1 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT3, _BIT3);

        ScalerSetByte(P31_51_PORCH_COLOR_R_M1, 0x00);
        ScalerSetByte(P31_52_PORCH_COLOR_G_M1, 0x00);
        ScalerSetByte(P31_53_PORCH_COLOR_B_M1, 0x00);
    }

    if((enumInputDataPath & _INPUT_PATH_M2) != 0)
    {
        // M2 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT2, _BIT2);

        ScalerSetByte(P31_54_PORCH_COLOR_R_M2, 0x00);
        ScalerSetByte(P31_55_PORCH_COLOR_G_M2, 0x00);
        ScalerSetByte(P31_56_PORCH_COLOR_B_M2, 0x00);
    }

    if((enumInputDataPath & _INPUT_PATH_S1) != 0)
    {
        // S1 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT1, _BIT1);

        ScalerSetByte(P31_57_PORCH_COLOR_R_S1, 0x00);
        ScalerSetByte(P31_58_PORCH_COLOR_G_S1, 0x00);
        ScalerSetByte(P31_59_PORCH_COLOR_B_S1, 0x00);
    }

    if((enumInputDataPath & _INPUT_PATH_S2) != 0)
    {
        // S2 porch color enable
        ScalerSetBit(P31_50_PORCH_COLOR_CTRL, ~_BIT0, _BIT0);

        ScalerSetByte(P31_5A_PORCH_COLOR_R_S2, 0x00);
        ScalerSetByte(P31_5B_PORCH_COLOR_G_S2, 0x00);
        ScalerSetByte(P31_5C_PORCH_COLOR_B_S2, 0x00);
    }
}

#if(_VGA_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/disable format conversion VS latch
// Input Value  : enumInputDataPath --> selected path
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvVsBypassEnable(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if((enumInputDataPath & _INPUT_PATH_M1) != 0)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT0, 0x00);
        }

        if((enumInputDataPath & _INPUT_PATH_M2) != 0)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT1, 0x00);
        }

        if((enumInputDataPath & _INPUT_PATH_S1) != 0)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT2, 0x00);
        }

        if((enumInputDataPath & _INPUT_PATH_S2) != 0)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT3, 0x00);
        }
    }
    else
    {
        if((enumInputDataPath & _INPUT_PATH_M1) != 0)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT0, _BIT0);
        }

        if((enumInputDataPath & _INPUT_PATH_M2) != 0)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT1, _BIT1);
        }

        if((enumInputDataPath & _INPUT_PATH_S1) != 0)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT2, _BIT2);
        }

        if((enumInputDataPath & _INPUT_PATH_S2) != 0)
        {
            ScalerSetBit(P31_0E_FC_SYNC_CTRL, ~_BIT3, _BIT3);
        }
    }
}
#endif

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
//--------------------------------------------------
// Description  : Set format conversion output format
// Input Value  : ucHstart/ucHSwidth: H start & HS width
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFBSetOutputFormat(WORD usHwidth, BYTE ucHstart, BYTE ucHSwidth)
{
    ScalerSetBit(P31_61_FULLTOFB_HWIDTH_H, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usHwidth) & 0x1F));
    ScalerSetByte(P31_62_FULLTOFB_HWIDTH_L, LOBYTE(usHwidth));

    ScalerSetByte(P31_67_FB_OUT_HSYNC_WIDTH, ucHSwidth);
    ScalerSetByte(P31_68_FB_OUT_HSTART, ucHstart);
}

//--------------------------------------------------
// Description  : Set format conversion F/B status
// Input Value  : enumFrontBackMode
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFBSetStatus(EnumFrontBackMode enumFrontBackMode)
{
    ScalerSetBit(P31_60_FRONT_BACK_CTRL, ~(_BIT7 | _BIT6), enumFrontBackMode);
}

//--------------------------------------------------
// Description  : Set initial format conversion extension value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnvFBSetInitialExtension(void)
{
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        if((GET_MDOMAIN_INPUT_HWIDTH() % 4) == 0)
        {
            SET_FMTCNV_EXTENSION_LEN(8); // amanda test // 18
        }
        else
        {
            SET_FMTCNV_EXTENSION_LEN(7); // amanda test // 17
        }
    }
    else
    {
        // Reset format conversion extension
        SET_FMTCNV_EXTENSION_LEN(0);
    }
}
#endif // End of #if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)

//--------------------------------------------------
// Description  : Get format conversion F/B status
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFmtCnvFBGetStatus(void)
{
    return (ScalerGetBit(P31_60_FRONT_BACK_CTRL, _BIT7) == _BIT7);
}

#if(_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Final setting for D2/D3 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422FinalSetting(EnumSourceSearchPort enumSourceSearchPort)
{
    // Check 420 setting for D2/D3
    switch(enumSourceSearchPort)
    {
        case _D2_INPUT_PORT:

#if(_D2_HDMI_2_0_SUPPORT == _ON)
            // Final 420 setting
            ScalerFmtCnv420To422D2FinalSetting(GET_MEASURE_INPUT_PATH());
#endif
            break;

        case _D3_INPUT_PORT:

#if(_D3_HDMI_2_0_SUPPORT == _ON)
            // Final 420 setting
            ScalerFmtCnv420To422D3FinalSetting(GET_MEASURE_INPUT_PATH());
#endif
            break;

        default:
            break;
    }
}

#if(_D2_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial setting for D0 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D2InitialSetting(void)
{
    // Disble 420-to-422
    ScalerColor420To422D2Enable(_FUNCTION_OFF);
}

//--------------------------------------------------
// Description  : Final setting for D0 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D2FinalSetting(EnumInputDataPath enumInputDataPath)
{
    if(GET_COLOR_SPACE(_D2_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
    {
        // Update actual 420-422 state
        if(ScalerFmtCnvHalfSDGetStatus(enumInputDataPath) == _TRUE)
        {
            ScalerColor420To422D2Setting(GET_ACTIVE_H_START() << 1, GET_ACTIVE_H_WIDTH() << 1);
        }
        else
        {
            ScalerColor420To422D2Setting(GET_ACTIVE_H_START(), GET_ACTIVE_H_WIDTH());
        }
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerColor420To422D2Enable(_FUNCTION_ON);
    }
}

//--------------------------------------------------
// Description  : Get D0 420 block status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerFmtCnv420To422D2GetStatus(void)
{
    return (ScalerGetBit(P31_32_YUV420_TO_YUV422_D2, _BIT7));
}
#endif // Endi of #if(_D2_HDMI_2_0_SUPPORT == _ON)

#if(_D3_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Initial setting for D1 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D3InitialSetting(void)
{
    // Disble 420-to-422
    ScalerColor420To422D3Enable(_FUNCTION_OFF);
}

//--------------------------------------------------
// Description  : Final setting for D1 420 block
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFmtCnv420To422D3FinalSetting(EnumInputDataPath enumInputDataPath)
{
    if(GET_COLOR_SPACE(_D3_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
    {
        // Update actual 420-422 state
        if(ScalerFmtCnvHalfSDGetStatus(enumInputDataPath) == _TRUE)
        {
            ScalerColor420To422D3Setting(GET_ACTIVE_H_START() << 1, GET_ACTIVE_H_WIDTH() << 1);
        }
        else
        {
            ScalerColor420To422D3Setting(GET_ACTIVE_H_START(), GET_ACTIVE_H_WIDTH());
        }
        ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, enumInputDataPath);
        ScalerColor420To422D3Enable(_FUNCTION_ON);
    }
}

//--------------------------------------------------
// Description  : Get D1 420 block status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerFmtCnv420To422D3GetStatus(void)
{
    return (ScalerGetBit(P31_33_YUV420_TO_YUV422_D3, _BIT7));
}
#endif // End of #if(_D3_HDMI_2_0_SUPPORT == _ON)

#endif // End of #if(_HDMI_2_0_SUPPORT == _ON)

