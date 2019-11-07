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
// ID Code      : ScalerColor.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_COLOR__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Color info size
//--------------------------------------------------
#define _COLOR_INFO_SIZE                        (_NO_INPUT_PORT)

//--------------------------------------------------
// Definitions of Digital Filter
//--------------------------------------------------
#define _DIG_FILTER_NSMEAR_THD                  4 // effective:0~7
#define _DIG_FILTER_NSMEAR_DIV_VALUE            1 // effective:0~3

#define _DIG_FILTER_PSMEAR_THD                  4 // effective:0~7
#define _DIG_FILTER_PSMEAR_DIV_VALUE            1 // effective:0~3

#define _DIG_FILTER_NRING_THD                   4 // effective:0~7
#define _DIG_FILTER_NRING_DIV_VALUE             1 // effective:0~3

#define _DIG_FILTER_PRING_THD                   4 // effective:0~7
#define _DIG_FILTER_PRING_DIV_VALUE             1 // effective:0~3

//--------------------------------------------------
// Definitions of Ddither
//--------------------------------------------------
#if(_D_DITHER_SUPPORT == _ON)
#if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)

#define _DDITHER_TEMPORAL_ENABLE                _ENABLE

#else // else of #if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)

#define _DDITHER_TEMPORAL_ENABLE                ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) ? _ENABLE : _D_DITHER_TEMP)

#endif // end of #if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#endif // end of #if(_D_DITHER_SUPPORT == _ON)
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructColorInfo g_pstColorInfo[_COLOR_INFO_SIZE];

#if(_PCM_FUNCTION == _ON)
// PCM Mode
WORD g_usRegSelHUEOSD = _HUE_CENTER;
WORD g_usInverseRegSelHUEOSD = _HUE_CENTER;
WORD g_usRegSelSATOSD = _SATURATION_CENTER;
WORD g_usInverseRegSelSATOSD = _SATURATION_CENTER;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_D_DITHER_SUPPORT == _ON)
void ScalerColorDDitherAdjust(BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress);
#endif

#if(_VGA_SUPPORT == _ON)
#if(_DIGITAL_FILTER_SUPPORT == _ON)
void ScalerColorDigitalFilterAdjust(void);
#endif
#endif

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
void ScalerColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply);
void ScalerColorHLWEnable(EnumFunctionOnOFF enumOn, EnumDBApply enumDBApply);
void ScalerColorHLWSetting(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_I_DITHER_SUPPORT == _ON)
void ScalerColorIDitherAdjust(EnumIDitherConvType enumIDitherConvType, BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress);
#endif

#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
void ScalerColorDCRSetSource(void);
#endif

#if(_ICM_SUPPORT == _ON)
void ScalerColorICMLoadTable(EnumSelRegion enumSelRegion, BYTE code *pucICMTable, BYTE ucBankNum);
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
void ScalerColorSixColorInitial(EnumSelRegion enumSelRegion);
void ScalerColorSixColorAdjust(EnumSelRegion enumSelRegion, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
#endif

#if(_PCM_FUNCTION == _ON)
void ScalerColorPCMSetHueSat(WORD usOSDHue, WORD usOSDInverHue, WORD usOSDSat, WORD usOSDInverseSat);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_D_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust D Dither Common Setting
// Input Value  :
//                pucDitherTable : Dither Table Pointer
//                pucSeqTable : Seq Table Pointer
//                pucTempoTable : Temporal Table Pointer
//                ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorDDitherAdjust(BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress)
{
    DWORD ulSettingOption = 0x00000000;
    BYTE ucKeepNFrame = _DDITHER_KEEP_1_FRAME;

    ScalerColorDDitherLoadDitherTable(pucDitherTable, ucBankAddress);

#if((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SERIES_SEQ_ENABLE == _ENABLE) || (_D_DITHER_ADVANCE_SETTING_ENABLE == _ENABLE))
    ScalerColorDDitherLoadSeqTable(pucSeqTable, 192, ucBankAddress);
#else
    ScalerColorDDitherLoadSeqTable(pucSeqTable, 48, ucBankAddress);
#endif

    ScalerColorDDitherLoadTempoTable(pucTempoTable, ucBankAddress);

#if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)

#if(((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) && (_D_DITHER_SERIES_SEQ_ENABLE == _DISABLE)) ||\
    (_D_DITHER_SHARE_SEQ_ENABLE == _ENABLE) ||\
    (_D_DITHER_SEQ_INV_ENABLE == _ENABLE))

    switch(_D_DITHER_SUPER_PIXEL_SIZE)
    {
        case _DDITHER_SUPER_PIXEL_2X2:
            if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
            {
                ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_16_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_2X4:
        case _DDITHER_SUPER_PIXEL_4X2:
            if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
            {
                ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_8_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_4X4:
            if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
            {
                ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
            }
            break;

        case _DDITHER_SUPER_PIXEL_4X8:
        case _DDITHER_SUPER_PIXEL_8X4:
            if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT)
            {
                ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            }
            else
            {
                ucKeepNFrame = _DDITHER_KEEP_2_FRAME;
            }
            break;

        default:
            ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
            break;
    }
#endif

#else // else of #if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)

#if((_D_DITHER_MULTI_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SHARE_SEQ_ENABLE == _ENABLE) || (_D_DITHER_SEQ_INV_ENABLE == _ENABLE))
    if(_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT)
    {
        ucKeepNFrame = _DDITHER_KEEP_4_FRAME;
    }
    else
    {
        ucKeepNFrame = _DDITHER_KEEP_1_FRAME;
    }
#endif

#endif // end of #if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)

    ulSettingOption = (_DDITHER_TEMPORAL_ENABLE << 4) | (_D_DITHER_V_FRAME_MOD << 1) | _D_DITHER_H_FRAME_MOD;
    ulSettingOption = ulSettingOption | (((DWORD)((ucKeepNFrame << 4) | _D_DITHER_SUPER_PIXEL_SIZE)) << 8);
    ulSettingOption = ulSettingOption | (((DWORD)((_D_DITHER_SERIES_SEQ_ENABLE << 3) | (_D_DITHER_MULTI_SEQ_ENABLE << 2))) << 16);
    ulSettingOption = ulSettingOption | (((DWORD)((_D_DITHER_SHARE_SEQ_ENABLE << 3) | (_D_DITHER_SEQ_INV_ENABLE << 1) | _D_DITHER_SEQ_INV_MODE)) << 24);

    ScalerColorDDitherLoadSetting(ulSettingOption);
}
#endif // #if(_D_DITHER_SUPPORT == _ON)

#if(_VGA_SUPPORT == _ON)
#if(_DIGITAL_FILTER_SUPPORT == _ON)
//-------------------------------------------------
// Description  : Set digital filter
// Input Value  : None
// Output Value : None
//-------------------------------------------------
void ScalerColorDigitalFilterAdjust(void)
{
    // Disable NR
    ScalerColorDigitalFilterNRDisableAdjust();

#if(_DIG_FILTER_NSMEAR_ENABLE == _ENABLE)
    // Set negative smear  parameter
    ScalerColorDigitalFilterNSmearAdjust(_DIG_FILTER_NSMEAR_THD, _DIG_FILTER_NSMEAR_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_NSMEAR_ENABLE == _ENABLE)

#if(_DIG_FILTER_PSMEAR_ENABLE == _ENABLE)
    // Set positive smear  parameter
    ScalerColorDigitalFilterPSmearAdjust(_DIG_FILTER_PSMEAR_THD, _DIG_FILTER_PSMEAR_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_PSMEAR_ENABLE == _ENABLE)

#if(_DIG_FILTER_NRING_ENABLE == _ENABLE)
    // Set negative ring  parameter
    ScalerColorDigitalFilterNRingAdjust(_DIG_FILTER_NRING_THD, _DIG_FILTER_NRING_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_NRING_ENABLE == _ENABLE)

#if(_DIG_FILTER_PRING_ENABLE == _ENABLE)
    // Set positive ring  parameter
    ScalerColorDigitalFilterPRingAdjust(_DIG_FILTER_PRING_THD, _DIG_FILTER_PRING_DIV_VALUE);
#endif  // End of #if(_DIG_FILTER_PRING_ENABLE == _ENABLE)

#if(_DIG_FILTER_EXTENSION_ENABLE == _ENABLE)
    // Use extension data
    ScalerColorDigitalFilterExtensionAdjust();
#endif  // End of #if(_DIG_FILTER_EXTENSION_ENABLE == _ENABLE)
}
#endif // #if(_DIGITAL_FILTER_SUPPORT == _ON)

#endif // #if(_VGA_SUPPORT == _ON)

#if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust highlight window region
// Input Value  : enumSelRegion, usHPos, usHWidth, usVPos, usVHeight, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply)
{
    ScalerColorHLWDDomainAdjust(usHPos, usHWidth, usVPos, usVHeight);

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorHLWIDLTILSRAdjust(usHPos, usHWidth, usVPos, usVHeight);

    // Not 1P Mode or 1P interlace Mode
    if((GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_1P) || (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE))
    {
        ScalerGlobalIDomainDBApply(_INPUT_PATH_ALL, enumDBApply);
        ScalerGlobalDDomainDBApply(enumDBApply);
    }
    else
    {
        ScalerGlobalIDDomainDBApply(_INPUT_PATH_ALL, enumDBApply);
    }
#else
    ScalerGlobalDDomainDBApply(enumDBApply);
#endif
}

//--------------------------------------------------
// Description  : Enable/Disable IDLTI, LSR, Ddomain HLW,
// Input Value  : enumOn, enumDBApply
// Output Value : none
//--------------------------------------------------
void ScalerColorHLWEnable(EnumFunctionOnOFF enumOn, EnumDBApply enumDBApply)
{
    ScalerColorHLWDDomainEnable(enumOn);

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorHLWIDLTILSREnable(enumOn);

    // Not 1P Mode or 1P interlace Mode
    if((GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_1P) || (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE))
    {
        ScalerGlobalIDomainDBApply(_INPUT_PATH_ALL, enumDBApply);
        ScalerGlobalDDomainDBApply(enumDBApply);
    }
    else
    {
        ScalerGlobalIDDomainDBApply(_INPUT_PATH_ALL, enumDBApply);
    }
#else
    ScalerGlobalDDomainDBApply(enumDBApply);
#endif
}

//--------------------------------------------------
// Description  : Get HLW Position , Set HLW Position
// Input Value  : enumSelRegion, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorHLWSetting(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply)
{
    // by enumSelRegion case, get M1's Background or S1's Background or Active size  from reference reg
    // becase Background/Active and HLW's reference position aren't the same!A
    // need to use Main1 Background's H/V start to change reference position
    // full region is equal to 1p mode
    // demo mode!A Movie HLW no deal

    WORD usRefHStart = 0;
    WORD usRefVStart = 0;
    WORD usHStart = 0;
    WORD usHEnd = 0;
    WORD usVStart = 0;
    WORD usVEnd = 0;
    WORD usPage = 0x0000;


    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H, 2, &pData[0], _AUTOINC);
    usRefHStart = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
    ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H, 2, &pData[0], _AUTOINC);
    usRefVStart = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

    switch(enumSelRegion)
    {
        case _1P_NORMAL_DEMO_OUTSIDE:
        case _PIP_DEMO_OUTSIDE:
        case _PBP_LR_DEMO_OUTSIDE:
        case _PBP_TB_DEMO_OUTSIDE:
        case _4P_DEMO_OUTSIDE:
        case _1P_NORMAL_DEMO_INSIDE:
        case _PIP_DEMO_INSIDE:
        case _PBP_LR_DEMO_INSIDE:
        case _PBP_TB_DEMO_INSIDE:
        case _4P_DEMO_INSIDE:
        case _NON_REGION:

            return;

        case _1P_NORMAL_FULL_REGION:
        case _1P_ROTATION_FULL_REGION:
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H, 2, &pData[0], _AUTOINC);
            usHEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H, 2, &pData[0], _AUTOINC);
            usVEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

            usHStart = 0;
            usHEnd = usHEnd - usRefHStart;
            usVStart = 0;
            usVEnd = usVEnd - usRefVStart;

            break;

        case _PIP_FULL_REGION:
        case _PBP_LR_FULL_REGION:
        case _PBP_TB_FULL_REGION:
        case _4P_FULL_REGION:

            // get Main1 Background size
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H, 2, &pData[0], _AUTOINC);
            usHEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H, 2, &pData[0], _AUTOINC);
            usVEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

            usHStart = usHEnd - usRefHStart;
            usHEnd = usHEnd - usRefHStart + 1;
            usVStart = 0;
            usVEnd = usVEnd - usRefVStart;

            break;

        case _PIP_MAIN:
        case _PIP_SUB:
        case _PBP_LR_L:
        case _PBP_LR_R:

            // get Sub1 Background size
            usPage = _REG_SUB1_PAGE;
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT + usPage, _P0_2B_PT_03_DISPLAY_HOR_BG_STA_H, 2, &pData[0], _AUTOINC);
            usHStart = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT + usPage, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H, 2, &pData[0], _AUTOINC);
            usHEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT + usPage, _P0_2B_PT_0E_DISPLAY_VER_BG_STA_H, 2, &pData[0], _AUTOINC);
            usVStart = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT + usPage, _P0_2B_PT_14_DISPLAY_VER_BG_END_H, 2, &pData[0], _AUTOINC);
            usVEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

            usHStart = usHStart - usRefHStart;
            usHEnd = usHEnd - usRefHStart;
            usVStart = usVStart - usRefVStart;
            usVEnd = usVEnd - usRefVStart;

            break;

        case _PBP_TB_T:
        case _PBP_TB_B:

            // get Main1 Background the lower half part
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H, 2, &pData[0], _AUTOINC);
            usHEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H, 2, &pData[0], _AUTOINC);
            usVEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

            usHStart = 0;
            usHEnd = usHEnd - usRefHStart;
            usVStart = ((usVEnd - usRefVStart) >> 1);
            usVEnd = usVEnd - usRefVStart;

            break;

        case _4P_LT:
        case _4P_LT_OUTSIDE:

            // get Main1 Background upper left part
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H, 2, &pData[0], _AUTOINC);
            usHEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H, 2, &pData[0], _AUTOINC);
            usVEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

            usHStart = 0;
            usHEnd = ((usHEnd - usRefHStart) >> 1);
            usVStart = 0;
            usVEnd = ((usVEnd - usRefVStart) >> 1);

            break;

        case _4P_LB:
        case _4P_LB_OUTSIDE:

            // get Main1 Background bottom left part
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H, 2, &pData[0], _AUTOINC);
            usHEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H, 2, &pData[0], _AUTOINC);
            usVEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

            usHStart = 0;
            usHEnd = ((usHEnd - usRefHStart) >> 1);
            usVStart = ((usVEnd - usRefVStart) >> 1);
            usVEnd = (usVEnd - usRefVStart);

            break;

        case _4P_RT:
        case _4P_RT_OUTSIDE:

            // get Main1 Background upper right part  (Sub1 Background the upper half part)
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H, 2, &pData[0], _AUTOINC);
            usHEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H, 2, &pData[0], _AUTOINC);
            usVEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

            usHStart = ((usHEnd - usRefHStart) >> 1);
            usHEnd = (usHEnd - usRefHStart);
            usVStart = 0;
            usVEnd = ((usVEnd - usRefVStart) >> 1);

            break;

        case _4P_RB:
        case _4P_RB_OUTSIDE:

            // get Main1 Background bottom right size  (Sub1 Background the lower half part)
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H, 2, &pData[0], _AUTOINC);
            usHEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H, 2, &pData[0], _AUTOINC);
            usVEnd = ((WORD)(pData[0] & 0x1F) << 8) | (WORD)(pData[1] & 0xFF);

            usHStart = ((usHEnd - usRefHStart) >> 1);
            usHEnd = (usHEnd - usRefHStart);
            usVStart = ((usVEnd - usRefVStart) >> 1);
            usVEnd = (usVEnd - usRefVStart);

            break;

        default:
            break;
    }

    // write position
    ScalerColorHLWDDomainAdjust(usHStart, usHEnd - usHStart, usVStart, usVEnd - usVStart);
    ScalerColorHLWBorderAdjust(0, 255, 0, 0, _DB_APPLY_NONE);
    ScalerColorHLWBorderEnable(_OFF, _OFF, _OFF, _OFF, _DB_APPLY_NONE);
    ScalerColorHLWDDomainEnable(_FUNCTION_ON);

#if(_ULTRA_VIVID_SUPPORT == _ON)
    ScalerColorHLWIDLTILSREnable(_FUNCTION_OFF);

    // Not 1P Mode or 1P interlace Mode
    if((GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_1P) || (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE))
    {
        ScalerGlobalIDomainDBApply(_INPUT_PATH_ALL, enumDBApply);
        ScalerGlobalDDomainDBApply(enumDBApply);
    }
    else
    {
        ScalerGlobalIDDomainDBApply(_INPUT_PATH_ALL, enumDBApply);
    }
#else
    ScalerGlobalDDomainDBApply(enumDBApply);
#endif
}
#endif // #if(_HIGHLIGHT_WINDOW_SUPPORT == _ON)

#if(_I_DITHER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust IDither Setting
// Input Value  :
//              enumIDitherConvType :  Conv Type
//              pucDitherTable : Dither Table Pointer
//              pucSeqTable : Seq Table Pointer
//              pucTempoTable : Temporal Table Pointer
//              ucBankAddress : Bank Address
// Output Value : None
//--------------------------------------------------
void ScalerColorIDitherAdjust(EnumIDitherConvType enumIDitherConvType, BYTE code *pucDitherTable, BYTE code *pucSeqTable, BYTE code *pucTempoTable, BYTE ucBankAddress)
{
    WORD usPage = 0x0000;
    WORD usAdjustOption = 0x0000;

    if(enumIDitherConvType == _IDITHER_12_TO_8)
    {
        usPage = _REG_MAIN1_PAGE;
    }
    else
    {
        usPage = _REG_SUB1_PAGE;
    }

    ScalerColorIDitherLoadDitherTable(usPage, pucDitherTable, ucBankAddress);

#if(((_I_DITHER_MULTI_SEQ_ENABLE == _DISABLE) && (_I_DITHER_SERIES_SEQ_ENABLE == _DISABLE)) || (_IDITHER_TYPE == _IDITHER_GEN_0_1_SEQ_TRUNCATE_2_0_BIT))
    ScalerColorIDitherLoadSeqTable(usPage, pucSeqTable, 24, ucBankAddress);
#else
    ScalerColorIDitherLoadSeqTable(usPage, pucSeqTable, 96, ucBankAddress);
#endif

    ScalerColorIDitherLoadTemporalTable(usPage, pucTempoTable, ucBankAddress);

    if(enumIDitherConvType == _IDITHER_12_TO_8)
    {
        usAdjustOption = (_I_DITHER_TEMP << 4) |
                         (_I_DITHER_VALUE_SIGN << 3) |
                         (_I_DITHER_V_FRAME_MOD << 1) |
                         (_I_DITHER_H_FRAME_MOD << 0) |
                         (_I_DITHER_SEQ_INV_ENABLE << 14) |
                         (_I_DITHER_SEQ_INV_MODE << 13) |
                         (_I_DITHER_SERIES_SEQ_ENABLE << 12) |
                         (_I_DITHER_SHARE_SEQ_ENABLE << 11) |
                         (_I_DITHER_MULTI_SEQ_ENABLE << 10);
    }
    else
    {
        usAdjustOption = (_I_DITHER_12_TO_10_TEMP << 4) |
                         (_I_DITHER_12_TO_10_VALUE_SIGN << 3) |
                         (_I_DITHER_12_TO_10_V_FRAME_MOD << 1) |
                         (_I_DITHER_12_TO_10_H_FRAME_MOD << 0) |
                         (_I_DITHER_12_TO_10_SEQ_INV_ENABLE << 14) |
                         (_I_DITHER_12_TO_10_SEQ_INV_MODE << 13) |
                         (_I_DITHER_12_TO_10_SERIES_SEQ_ENABLE << 12) |
                         (_I_DITHER_12_TO_10_SHARE_SEQ_ENABLE << 11) |
                         (_I_DITHER_12_TO_10_MULTI_SEQ_ENABLE << 10);
    }

    ScalerColorIDitherLoadSetting(usPage, usAdjustOption);
}
#endif // #if(_I_DITHER_SUPPORT == _ON)


#if((_DCR_SUPPORT == _ON) || (_IAPS_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set DCR Source
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorDCRSetSource(void)
{
    ScalerSetBit(P7_DA_DCR_CTRL, ~_BIT0, _DCR_SOURCE);
}
#endif

#if(_ICM_SUPPORT == _ON)
//--------------------------------------------------
// Description   : Fill ICM UVOffset/Brightness table
// Input Value   : pICMTable: ICM Table
//                 ucBankNum: Bank Number
//                 ucCMSel: ICM Select
// Output Value  : None
//--------------------------------------------------
void ScalerColorICMLoadTable(EnumSelRegion enumSelRegion, BYTE code *pucICMTable, BYTE ucBankNum)
{
    BYTE pucTemp[2] = {0};
    WORD usPage = ScalerRegionGetRegisterPage(_REG_DDOMAIN_AFTER_BLENDING, enumSelRegion);

    if(pucICMTable != NULL)
    {
        ScalerFlashRead(ucBankNum, (WORD)(&pucICMTable[1]), 2, pucTemp);
        ScalerColorICMAdjust(enumSelRegion, pucTemp[0], pucTemp[1]);

        ScalerColorICMUVOffsetLoadTable(usPage, pucICMTable, ucBankNum);

#if(_ICM_BRI_SUPPORT == _ON)
        ScalerColorICMBRILoadTable(usPage, pucICMTable, ucBankNum);
#endif
    }
    else
    {
        ScalerColorICMAdjust(enumSelRegion, 0x00, 0x00);
    }
}
#endif

#if(_SIX_COLOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable ICM function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorInitial(EnumSelRegion enumSelRegion)
{
#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_NORMAL_MODE)
    ScalerColorSixColorInitialNormal(enumSelRegion);
#elif(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_DELL_MODE)
    ScalerColorSixColorInitialDell(enumSelRegion);
#endif
}

//--------------------------------------------------
// Description  : 6 Color ICM adjust
// Input Value  : ucColorIndex --> Color Adjusted Now
//                ucHuePosition --> Hue position after mapping
//                ucSatPosition --> Sat position after mapping
// Output Value : None
//--------------------------------------------------
void ScalerColorSixColorAdjust(EnumSelRegion enumSelRegion, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition)
{
#if(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_NORMAL_MODE)
    ScalerColorSixColorAdjustNormal(enumSelRegion, ucColorIndex, ucHuePosition, ucSatPosition);
#elif(_SIX_COLOR_ICM_TYPE == _SIX_COLOR_ICM_DELL_MODE)
    ScalerColorSixColorAdjustDell(enumSelRegion, ucColorIndex, ucHuePosition, ucSatPosition);
#endif
}
#endif // #if(_SIX_COLOR_SUPPORT == _ON)

#if(_PCM_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Set Global Hue/SAT OSD Value For PCM Setting
// Input Value  : Global Hue Sat OSD Value
// Output Value : None
//--------------------------------------------------
void ScalerColorPCMSetHueSat(WORD usOSDHue, WORD usOSDInverHue, WORD usOSDSat, WORD usOSDInverseSat)
{
    g_usRegSelHUEOSD = usOSDHue;
    g_usInverseRegSelHUEOSD = usOSDInverHue;
    g_usRegSelSATOSD = usOSDSat;
    g_usInverseRegSelSATOSD = usOSDInverseSat;
}
#endif
