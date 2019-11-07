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
// ID Code      : ScalerScaling.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_SCALING__

#include "ScalerFunctionInclude.h"


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _HSD_TABLE_SIZE                                   128
#define _VSD_TABLE_SIZE                                   64

#if(_SHARPNESS_SUPPORT == _OFF)
#define _HSU_TABLE_SIZE                                   128
#define _VSU_TABLE_SIZE                                   128
#endif

#define _HSD_MAX_RATIO                                    15

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// 128 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_H_COEF_128_TAPS[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};


//----------------------------------------------------------------------------------------------------
// 64 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_V_COEF_64_TAPS[] =
{
    0x82, 0x0F, 0x97, 0x0F, 0xA4, 0x0F, 0xCE, 0x0F, 0xE8, 0x0F, 0x1A, 0x00, 0x3B, 0x00, 0x73, 0x00,
    0x98, 0x00, 0xD2, 0x00, 0xF8, 0x00, 0x32, 0x01, 0x58, 0x01, 0x91, 0x01, 0xB5, 0x01, 0xEE, 0x01,
    0x7E, 0x04, 0x69, 0x04, 0x5C, 0x04, 0x32, 0x04, 0x18, 0x04, 0xE6, 0x03, 0xC5, 0x03, 0x8D, 0x03,
    0x68, 0x03, 0x2E, 0x03, 0x08, 0x03, 0xCE, 0x02, 0xA8, 0x02, 0x6F, 0x02, 0x4B, 0x02, 0x12, 0x02,
};

#if(_SHARPNESS_SUPPORT == _OFF)
//----------------------------------------------------------------------------------------------------
// 128 taps Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_SU_COEF_128_TAPS[] =
{
    0xFB, 0x0F, 0xFE, 0x0F, 0xFD, 0x0F, 0xFC, 0x0F, 0xFB, 0x0F, 0xFA, 0x0F, 0xF7, 0x0F, 0xF5, 0x0F,
    0xF1, 0x0F, 0xED, 0x0F, 0xE9, 0x0F, 0xE4, 0x0F, 0xDE, 0x0F, 0xD9, 0x0F, 0xD3, 0x0F, 0xCD, 0x0F,
    0xC7, 0x0F, 0xDB, 0x0F, 0xF0, 0x0F, 0x0C, 0x00, 0x27, 0x00, 0x49, 0x00, 0x6B, 0x00, 0x93, 0x00,
    0xBC, 0x00, 0xEA, 0x00, 0x16, 0x01, 0x49, 0x01, 0x7A, 0x01, 0xB0, 0x01, 0xE3, 0x01, 0x1C, 0x02,
    0x84, 0x04, 0x78, 0x04, 0x6C, 0x04, 0x57, 0x04, 0x42, 0x04, 0x23, 0x04, 0x04, 0x04, 0xDC, 0x03,
    0xB4, 0x03, 0x86, 0x03, 0x59, 0x03, 0x26, 0x03, 0xF4, 0x02, 0xBD, 0x02, 0x89, 0x02, 0x50, 0x02,
    0xBA, 0x0F, 0xAF, 0x0F, 0xA7, 0x0F, 0xA1, 0x0F, 0x9C, 0x0F, 0x9A, 0x0F, 0x9A, 0x0F, 0x9C, 0x0F,
    0x9F, 0x0F, 0xA3, 0x0F, 0xA8, 0x0F, 0xAD, 0x0F, 0xB4, 0x0F, 0xBA, 0x0F, 0xC1, 0x0F, 0xC7, 0x0F,
};
#endif

#if(_FREESYNC_SUPPORT == _ON)
//----------------------------------------------------------------------------------------------------
// 64 taps bypass Coefficient Table (Sharpness)
//----------------------------------------------------------------------------------------------------
BYTE code tSD_V_COEF_64_TAPS_BYPASS[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04,
    0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04,
};
#endif
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerScalingSetInitial(void);
void ScalerScalingSetScalingUp(const StructSDRAMDataInfo *pstFIFOScaling);
void ScalerScalingSetScalingDownCoef(void);
void ScalerScalingSetScalingDown(const StructSDRAMDataInfo *pstFIFOScaling);
bit ScalerScalingGetFIFOScalingSize(StructSDRAMDataInfo *pstData);

#if(_SHARPNESS_SUPPORT == _OFF)
void ScalerScalingSetScalingUpCoef(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Set scaling initial settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetInitial(void)
{
    // Disable H/V SU
    ScalerSetBit(P0_32_SCALE_CONTROL_REG, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(P80_32_SCALE_CONTROL_REG_S1, ~(_BIT1 | _BIT0), 0x00);

#if(_4P_DISPLAY_SUPPORT == _ON)
    ScalerSetBit(P40_32_SCALE_CONTROL_REG_M2, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit(PC0_32_SCALE_CONTROL_REG_S2, ~(_BIT1 | _BIT0), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Decide which scaling up function should be performed
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetScalingUp(const StructSDRAMDataInfo *pstFIFOScaling)
{
    WORD usRegPageSel = 0x00;

    switch(GET_MDOMAIN_OUTPUT_DATA_PATH())
    {
        case _DISPLAY_PATH_M1:

            usRegPageSel = _REG_MAIN1_PAGE;
            break;

        case _DISPLAY_PATH_M2:

            usRegPageSel = _REG_MAIN2_PAGE;
            break;

        case _DISPLAY_PATH_S1:

            usRegPageSel = _REG_SUB1_PAGE;
            break;

        case _DISPLAY_PATH_S2:

            usRegPageSel = _REG_SUB2_PAGE;
            break;

        case _DISPLAY_PATH_ALL:
            usRegPageSel = _REG_MAIN1_PAGE;
            break;

        default:
            break;
    }

    CLR_V_SCALE_UP();
    CLR_H_SCALE_UP();

    // Disable Scale Up
    ScalerSetBit(P0_32_SCALE_CONTROL_REG + usRegPageSel, ~(_BIT1 | _BIT0), 0x00);

#if(_SHARPNESS_SUPPORT == _OFF)
    // Disable Scale Up FixCoef
    ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE + usRegPageSel, ~(_BIT5 | _BIT4), 0x00);
#endif

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        ScalerSetBit(P0_32_SCALE_CONTROL_REG + 0x8000, ~(_BIT1 | _BIT0), 0x00);

#if(_SHARPNESS_SUPPORT == _OFF)
        // Disable Scale Up FixCoef
        ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE + 0x8000, ~(_BIT5 | _BIT4), 0x00);
#endif
    }
#endif
    //===============================
    // Decide V direction scaling up
    //===============================
    // Set V Scaling Up Factor
    if(pstFIFOScaling->usOutputVHeight < g_stMDomainOutputData.usVHeight)
    {
        SET_V_SCALE_UP();

        PDATA_DWORD(0) = (DWORD)pstFIFOScaling->usOutputVHeight << 20;
        PDATA_DWORD(0) = (PDATA_DWORD(0) / g_stMDomainOutputData.usVHeight) + (PDATA_DWORD(0) % 2);

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_03_VER_SCALE_FACTOR_H, ((PDATA_DWORD(0) >> 16) & 0x0F));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_04_VER_SCALE_FACTOR_M, ((PDATA_DWORD(0) >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_05_VER_SCALE_FACTOR_L, (PDATA_DWORD(0) & 0xFF));

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_03_VER_SCALE_FACTOR_H, ((PDATA_DWORD(0) >> 16) & 0x0F));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_04_VER_SCALE_FACTOR_M, ((PDATA_DWORD(0) >> 8) & 0xFF));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_05_VER_SCALE_FACTOR_L, (PDATA_DWORD(0) & 0xFF));
        }
#endif
        // Set V Initial Phase
        // R = Input Height /Output Height
        // ideal initial phase: for 4line SU = (1+R)*16*8
        PDATA_DWORD(0) = (DWORD)(pstFIFOScaling->usOutputVHeight + g_stMDomainOutputData.usVHeight) * 16 * 8 / g_stMDomainOutputData.usVHeight;

        // 1080i->1080P  no video compensation
        if((GET_INTERLACED_MODE() == _FALSE) ||
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
           ((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270)) ||
#endif
           (ScalerFmtCnvGetSourceType(GET_MDOMAIN_INPUT_DATA_PATH()) == _FC_SOURCE_ADC) ||
           (BYPASS_VIDEO_COMPENSATION(pstFIFOScaling->usOutputVHeight, g_stMDomainOutputData.usVHeight) == _TRUE))
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_11_VER_FILTER_COEF_INI, pData[3]);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(ScalerFmtCnvFBGetStatus() == _TRUE)
            {
                ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_11_VER_FILTER_COEF_INI, pData[3]);
            }
#endif
        }
        else
        {
            if(pData[3] > 0xBF)
            {
                pData[3] = 0xFF;
            }
            else
            {
                pData[3] = pData[3] + 0x40;
            }

            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_11_VER_FILTER_COEF_INI, pData[3]);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(ScalerFmtCnvFBGetStatus() == _TRUE)
            {
                ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_11_VER_FILTER_COEF_INI, pData[3]);
            }
#endif
        }
    }
    else
    {
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_03_VER_SCALE_FACTOR_H, 0x0F);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_04_VER_SCALE_FACTOR_M, 0xFF);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_05_VER_SCALE_FACTOR_L, 0xFF);

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_11_VER_FILTER_COEF_INI, 0xFF);

#if(_SHARPNESS_SUPPORT == _OFF)
        // Enable V Scale Up FixCoef
        ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE + usRegPageSel, ~_BIT4, _BIT4);
#endif

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_03_VER_SCALE_FACTOR_H, 0x0F);
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_04_VER_SCALE_FACTOR_M, 0xFF);
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_05_VER_SCALE_FACTOR_L, 0xFF);

            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_11_VER_FILTER_COEF_INI, 0xFF);

#if(_SHARPNESS_SUPPORT == _OFF)
            // Enable V Scale Up FixCoef
            ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE + 0x8000, ~_BIT4, _BIT4);
#endif
        }
#endif
    }

    if(GET_V_SCALE_UP() == _TRUE)
    {
        // Enable V Scale Up
        ScalerSetBit(P0_32_SCALE_CONTROL_REG + usRegPageSel, ~_BIT1, _BIT1);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            ScalerSetBit(P0_32_SCALE_CONTROL_REG + 0x8000, ~_BIT1, _BIT1);
        }
#endif

        if(GET_INTERLACED_MODE() == _TRUE)
        {
            // VGA Input or Prefered Timing
            if((ScalerFmtCnvGetSourceType(GET_MDOMAIN_INPUT_DATA_PATH()) == _FC_SOURCE_ADC) ||
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
               ((GET_ROT_TYPE() == _ROT_CW90) || (GET_ROT_TYPE() == _ROT_CW270)) ||
#endif
               (BYPASS_VIDEO_COMPENSATION(pstFIFOScaling->usOutputVHeight, g_stMDomainOutputData.usVHeight) == _TRUE))
            {
                // Disable Video Compensation
                ScalerSetBit(P0_32_SCALE_CONTROL_REG + usRegPageSel, ~_BIT7, 0x00);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                if(ScalerFmtCnvFBGetStatus() == _TRUE)
                {
                    ScalerSetBit(P0_32_SCALE_CONTROL_REG + 0x8000, ~_BIT7, 0x00);
                }
#endif
            }
            else
            {
                // Enable Video Compensation According to Odd Field Delay One Line
                ScalerSetBit(P0_32_SCALE_CONTROL_REG + usRegPageSel, ~_BIT7, _BIT7);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                if(ScalerFmtCnvFBGetStatus() == _TRUE)
                {
                    ScalerSetBit(P0_32_SCALE_CONTROL_REG + 0x8000, ~_BIT7, _BIT7);
                }
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
                // Check video compensation polarity for rotation
                ScalerRotationCheckVideoCompensation();
#endif
            }
        }
        else
        {
            // Disable Video Compensation
            ScalerSetBit(P0_32_SCALE_CONTROL_REG + usRegPageSel, ~_BIT7, 0x00);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(ScalerFmtCnvFBGetStatus() == _TRUE)
            {
                ScalerSetBit(P0_32_SCALE_CONTROL_REG + 0x8000, ~_BIT7, 0x00);
            }
#endif
        }
    }
    else
    {
        // Disable Video Compensation
        ScalerSetBit(P0_32_SCALE_CONTROL_REG + usRegPageSel, ~_BIT7, 0x00);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            ScalerSetBit(P0_32_SCALE_CONTROL_REG + 0x8000, ~_BIT7, 0x00);
        }
#endif
    }

    //===============================
    // Decide H direction scaling up
    //===============================
    // Set H Scaling Up Factor
    SET_H_SCALE_UP();

    if(pstFIFOScaling->usOutputHWidth < g_stMDomainOutputData.usHWidth)
    {
        SET_H_SCALE_UP();

        PDATA_DWORD(0) = (DWORD)pstFIFOScaling->usOutputHWidth << (20 - 1);
        PDATA_DWORD(0) = (PDATA_DWORD(0) / (g_stMDomainOutputData.usHWidth >> 1)) + (PDATA_DWORD(0) % 2);
        PDATA_DWORD(2) = PDATA_DWORD(0);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_00_HOR_SCALE_FACTOR_H, ((PDATA_DWORD(0) >> 16) & 0x0F));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_01_HOR_SCALE_FACTOR_M, ((PDATA_DWORD(0) >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_02_HOR_SCALE_FACTOR_L, (PDATA_DWORD(0) & 0xFF));

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_00_HOR_SCALE_FACTOR_H, ((PDATA_DWORD(0) >> 16) & 0x0F));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_01_HOR_SCALE_FACTOR_M, ((PDATA_DWORD(0) >> 8) & 0xFF));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_02_HOR_SCALE_FACTOR_L, (PDATA_DWORD(0) & 0xFF));
        }
#endif
        // Set H Initial Phase
        // R = Input width /Output width
        // ideal initial phase = (1+R)*16*8
        PDATA_DWORD(0) = (DWORD)(pstFIFOScaling->usOutputHWidth + g_stMDomainOutputData.usHWidth) * 16 * 8 / g_stMDomainOutputData.usHWidth;

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_10_HOR_FILTER_COEF_INI, pData[3]);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // max I domain extension
            // (DHTotal_reg + 8)/2  = DHStart_reg/4 + DHWith_reg/2 + FrontPorch_main
            PDATA_DWORD(1) = (DWORD)(g_stMDomainOutputData.usHTotal + 8 - g_stMDomainOutputData.usHStart / 2 - g_stMDomainOutputData.usHWidth) / 2;

            // Check minimum H front porch
            // FrontPorch_main >= Extension_reg + 56
            if(PDATA_DWORD(1) > 56)
            {
                PDATA_DWORD(1) -= 56;

#if(_ULTRA_VIVID_SUPPORT == _ON)
                // DSHP LineBuffer upper bound = 2560 + 31 (1 line buffer for back initial phase)
                if(PDATA_DWORD(1) + (g_stMDomainOutputData.usHWidth >> 1) > 2591)
                {
                    PDATA_DWORD(1) = 2591 - (g_stMDomainOutputData.usHWidth >> 1);
                }
#endif
            }
            else
            {
                PDATA_DWORD(1) = 0;
            }

            PDATA_DWORD(1) = PDATA_DWORD(1) * pstFIFOScaling->usOutputHWidth / g_stMDomainOutputData.usHWidth;

            // Check maximun I domain extension lenth = 18
            if(PDATA_DWORD(1) > 18)
            {
                PDATA_DWORD(1) = 18;
            }

            // Drop Extension num
            // extension + FIFOWidth must be even number
            if(((pstFIFOScaling->usOutputHWidth >> 1) & 0x01) == 0x01)
            {
                if(GET_MDOMAIN_EXTENSION_LEN() > PDATA_DWORD(1))
                {
                    PDATA_DWORD(1) = (GET_MDOMAIN_EXTENSION_LEN() - (((PDATA_DWORD(1) + 1) & 0x1E) - 1));
                }
                else
                {
                    PDATA_DWORD(1) = (GET_MDOMAIN_EXTENSION_LEN() - (((GET_MDOMAIN_EXTENSION_LEN() + 1) & 0x1E) - 1));
                }
            }
            else
            {
                if(GET_MDOMAIN_EXTENSION_LEN() > PDATA_DWORD(1))
                {
                    PDATA_DWORD(1) = (GET_MDOMAIN_EXTENSION_LEN() - (PDATA_DWORD(1) & 0x1E));
                }
                else
                {
                    PDATA_DWORD(1) = (GET_MDOMAIN_EXTENSION_LEN() - (GET_MDOMAIN_EXTENSION_LEN() & 0x1E));
                }
            }
            SET_MDOMAIN_EXTENSION_LEN(GET_MDOMAIN_EXTENSION_LEN() - PDATA_DWORD(1));

            // Set Drop Extension
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, ~0x1F, ((BYTE)(PDATA_DWORD(1)) & 0x1F));
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, ~0x1F, ((BYTE)(PDATA_DWORD(1)) & 0x1F));
            ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, ~0x1F, ((BYTE)(PDATA_DWORD(1)) & 0x1F));
            ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, ~0x1F, ((BYTE)(PDATA_DWORD(1)) & 0x1F));

            // Drop Extension Enable
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, ~_BIT7, _BIT7);
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, ~_BIT7, _BIT7);
            ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, ~_BIT7, _BIT7);
            ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, ~_BIT7, _BIT7);

            // D-domain extension
            PDATA_DWORD(1) = ((((DWORD)g_stMDomainOutputData.usHWidth * GET_MDOMAIN_EXTENSION_LEN() << 1) / pstFIFOScaling->usOutputHWidth + 1) >> 1);

            if(PDATA_DWORD(1) > 0xFF)
            {
                PDATA_DWORD(1) = 0xFF;
            }

            SET_DDOMAIN_EXTENSION_LEN(PDATA_DWORD(1));

            // back initial phase = FrontInitialPhase + InExtension for each OutExtension*SDFactor
            PDATA_DWORD(0) = (PDATA_DWORD(0) << 12) +
                             ((DWORD)GET_MDOMAIN_EXTENSION_LEN() << 20) - (PDATA_DWORD(1) * PDATA_DWORD(2));

            if(PDATA_DWORD(0) > 0xFFFFF)
            {
                SET_DDOMAIN_EXTENSION_LEN(PDATA_DWORD(1) + 1);
                PDATA_DWORD(0) = PDATA_DWORD(0) - PDATA_DWORD(2);
            }

            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_10_HOR_FILTER_COEF_INI, ((PDATA_DWORD(0) >> 12) & 0xFF));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_14_HOR_FILTER_COEF_INI_M, ((PDATA_DWORD(0) >> 4) & 0xFF));
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_15_HOR_FILTER_COEF_INI_L, ((PDATA_DWORD(0) & 0x0F) << 4));
        }
#endif
    }
    else
    {
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_00_HOR_SCALE_FACTOR_H, 0x0F);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_01_HOR_SCALE_FACTOR_M, 0xFF);
        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_02_HOR_SCALE_FACTOR_L, 0xFF);

        ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + usRegPageSel, _P0_34_PT_10_HOR_FILTER_COEF_INI, 0xFF);

#if(_SHARPNESS_SUPPORT == _OFF)
        // Enable H Scale Up FixCoef
        ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE + usRegPageSel, ~_BIT5, _BIT5);
#endif

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // max I domain extension
            PDATA_DWORD(1) = (DWORD)(g_stMDomainOutputData.usHTotal + 8 - g_stMDomainOutputData.usHStart / 2 - g_stMDomainOutputData.usHWidth) / 2;
            // DExtension < FrontPorch_main - N
            // Check minimum H front porch
            // FrontPorch_main >= Extension_reg + 56
            if(PDATA_DWORD(1) > 56)
            {
                PDATA_DWORD(1) = PDATA_DWORD(1) - 56;

#if(_ULTRA_VIVID_SUPPORT == _ON)
                // DSHP LineBuffer = 2560+32
                if(PDATA_DWORD(1) + (g_stMDomainOutputData.usHWidth >> 1) > 2592)
                {
                    PDATA_DWORD(1) = 2592 - (g_stMDomainOutputData.usHWidth >> 1);
                }
#endif
            }
            else
            {
                PDATA_DWORD(1) = 0;
            }

            // Check maximun I domain extension lenth = 18
            if(PDATA_DWORD(1) > 18)
            {
                PDATA_DWORD(1) = 18;
            }

            if(((pstFIFOScaling->usOutputHWidth >> 1) & 0x01) == 0x01)
            {
                if(GET_MDOMAIN_EXTENSION_LEN() > PDATA_DWORD(1))
                {
                    PDATA_DWORD(1) = (GET_MDOMAIN_EXTENSION_LEN() - (((PDATA_DWORD(1) + 1) & 0x1E) - 1));
                }
                else
                {
                    PDATA_DWORD(1) = (GET_MDOMAIN_EXTENSION_LEN() - (((GET_MDOMAIN_EXTENSION_LEN() + 1) & 0x1E) - 1));
                }
            }
            else
            {
                if(GET_MDOMAIN_EXTENSION_LEN() > PDATA_DWORD(1))
                {
                    PDATA_DWORD(1) = (GET_MDOMAIN_EXTENSION_LEN() - (PDATA_DWORD(1) & 0x1E));
                }
                else
                {
                    PDATA_DWORD(1) = (GET_MDOMAIN_EXTENSION_LEN() - (GET_MDOMAIN_EXTENSION_LEN() & 0x1E));
                }
            }

            // Set M-domain Extension == D-domain Extension
            SET_MDOMAIN_EXTENSION_LEN(GET_MDOMAIN_EXTENSION_LEN() - PDATA_DWORD(1));
            SET_DDOMAIN_EXTENSION_LEN(GET_MDOMAIN_EXTENSION_LEN());

            // Set Drop Extension
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, ~0x1F, ((BYTE)(PDATA_DWORD(1)) & 0x1F));
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, ~0x1F, ((BYTE)(PDATA_DWORD(1)) & 0x1F));
            ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, ~0x1F, ((BYTE)(PDATA_DWORD(1)) & 0x1F));
            ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, ~0x1F, ((BYTE)(PDATA_DWORD(1)) & 0x1F));

            // Drop Extension Enable
            ScalerSetDataPortBit(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, ~_BIT7, _BIT7);
            ScalerSetDataPortBit(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, ~_BIT7, _BIT7);
            ScalerSetDataPortBit(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, ~_BIT7, _BIT7);
            ScalerSetDataPortBit(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, ~_BIT7, _BIT7);

            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_00_HOR_SCALE_FACTOR_H, 0x0F);
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_01_HOR_SCALE_FACTOR_M, 0xFF);
            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_02_HOR_SCALE_FACTOR_L, 0xFF);

            ScalerSetDataPortByte(P0_33_SF_ADDR_PORT + 0x8000, _P0_34_PT_10_HOR_FILTER_COEF_INI, 0xFF);

#if(_SHARPNESS_SUPPORT == _OFF)
            // Enable H Scale Up FixCoef
            ScalerSetBit(P0_37_SCALE_UP_FOR_LINE_INTERLEAVE + 0x8000, ~_BIT5, _BIT5);
#endif
        }
#endif
    }
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        // FIFOWin Extension
        ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_08_DISPLAY_READ_EXTENSION_MAIN, ~0x1F, ((BYTE)(GET_MDOMAIN_EXTENSION_LEN()) & 0x1F));
        ScalerSetDataPortBit(P80_30_FIFO_WINDOW_ADDR_PORT_S, _P80_31_PT_08_DISPLAY_READ_EXTENSION_SUB, ~0x1F, ((BYTE)(GET_MDOMAIN_EXTENSION_LEN()) & 0x1F));

        // Display Extension
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_MAIN, ~0xFF, ((BYTE)(GET_DDOMAIN_EXTENSION_LEN()) & 0xFF));
        ScalerSetDataPortBit(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_1F_DISPLAY_EXTENSION_FB_SUB, ~0xFF, ((BYTE)(GET_DDOMAIN_EXTENSION_LEN()) & 0xFF));

        ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);

        // Display Conversion Extension
        ScalerSetByte(P39_1E_DSPC_TIMING_CTRL0, GET_DDOMAIN_EXTENSION_LEN());  // ????? jeyu

#if(_OSD_POSITION_OFFSET_CORRECTION == _ON)
        ScalerOsdPositionOffsetCorrection();
#endif
    }
#endif
    //===============================
    // Set H direction scaling up
    //===============================
    if(GET_H_SCALE_UP() == _TRUE)
    {
        // Enable H Scale Up
        ScalerSetBit(P0_32_SCALE_CONTROL_REG + usRegPageSel, ~_BIT0, _BIT0);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            ScalerSetBit(P0_32_SCALE_CONTROL_REG + 0x8000, ~_BIT0, _BIT0);
        }
#endif
    }
}

//--------------------------------------------------
// Description  : Set Scale Down Coef
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerScalingSetScalingDownCoef(void)
{
    // M1
    // Set Coefficient table 1
    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tSD_H_COEF_128_TAPS, _HSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // M2
    // Set Coefficient table 1
    ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tSD_H_COEF_128_TAPS, _HSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // S1
    // Set Coefficient table 1
    ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tSD_H_COEF_128_TAPS, _HSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P80_27_SD_USER_FILTER_ACCESS_PORT_S1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(P80_26_SD_FILTER_CONTROL_REG_S1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P80_27_SD_USER_FILTER_ACCESS_PORT_S1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // S2
    // Set Coefficient table 1
    ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tSD_H_COEF_128_TAPS, _HSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), PC0_27_SD_USER_FILTER_ACCESS_PORT_S2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(PC0_26_SD_FILTER_CONTROL_REG_S2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), PC0_27_SD_USER_FILTER_ACCESS_PORT_S2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
}

//--------------------------------------------------
// Description  : Decide which scaling down function should be performed
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetScalingDown(const StructSDRAMDataInfo *pstFIFOScaling)
{
    WORD usRegPageSel = 0x0000;
    bit bEvenOdd = _FALSE;

    switch(GET_MDOMAIN_INPUT_DATA_PATH())
    {
        case _INPUT_PATH_M1:

            usRegPageSel = _REG_MAIN1_PAGE;
            break;

        case _INPUT_PATH_M2:

            usRegPageSel = _REG_MAIN2_PAGE;
            break;

        case _INPUT_PATH_M1_M2:

            usRegPageSel = _REG_MAIN1_PAGE;
            bEvenOdd = _TRUE;
            break;

        case _INPUT_PATH_S1:

            usRegPageSel = _REG_SUB1_PAGE;
            break;

        case _INPUT_PATH_S2:

            usRegPageSel = _REG_SUB2_PAGE;
            break;

        case _INPUT_PATH_S1_S2:

            usRegPageSel = _REG_SUB1_PAGE;
            bEvenOdd = _TRUE;
            break;

        case _INPUT_PATH_ALL:

            usRegPageSel = _REG_MAIN1_PAGE;
            bEvenOdd = _TRUE;
            break;

        default:
            break;
    }

    CLR_V_SCALE_DOWN();
    CLR_H_SCALE_DOWN();

    // Disable Scale Down
    // M1
#if(_FREESYNC_SUPPORT == _ON)
    if((GET_FREESYNC_ENABLED() == _ENABLE) && (ScalerGlobalGetDBStatus() == _FALSE))
    {
        // Keep VSD enabled under free-sync
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

        if(bEvenOdd == _TRUE)
        {
            // M2 or S2
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel + 0x4000, ~(_BIT3 | _BIT2 | _BIT1), 0x00);
        }
    }
    else
#endif
    {
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        if(bEvenOdd == _TRUE)
        {
            // M2 or S2
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel + 0x4000, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }
    }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        // S1
        ScalerSetBit(P80_23_SCALE_DOWN_CTRL_S1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        // S2
        ScalerSetBit(PC0_23_SCALE_DOWN_CTRL_S2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

    if(GET_MDOMAIN_INPUT_DATA_PATH() != _INPUT_PATH_ALL)
    {
        // Reset M/D extension
        SET_MDOMAIN_EXTENSION_LEN(0);
        SET_DDOMAIN_EXTENSION_LEN(0);

        // HSD extension = 0
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_3A_SD_OUT_EXTENSION_M1, 0x00);
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_3A_SD_OUT_EXTENSION_M2, 0x00);
        ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_3A_SD_OUT_EXTENSION_S1, 0x00);
        ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_3A_SD_OUT_EXTENSION_S2, 0x00);

        // Drop Extension disable
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_60_DROP_EXTENSION_M1, 0x00);
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_60_DROP_EXTENSION_M2, 0x00);
        ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_60_DROP_EXTENSION_S1, 0x00);
        ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_60_DROP_EXTENSION_S2, 0x00);

        // FIFOWin Extension
        ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_08_DISPLAY_READ_EXTENSION_MAIN, ~0x1F, 0x00);
        ScalerSetDataPortBit(P80_30_FIFO_WINDOW_ADDR_PORT_S, _P80_31_PT_08_DISPLAY_READ_EXTENSION_SUB, ~0x1F, 0x00);

        // Display Extension
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_1F_DISPLAY_EXTENSION_FB_MAIN, ~0xFF, 0x00);
        ScalerSetDataPortBit(P80_2A_DISPLAY_FORMAT_ADDR_PORT_S, _P80_2B_PT_1F_DISPLAY_EXTENSION_FB_SUB, ~0xFF, 0x00);

        // Display Conversion Extension
        ScalerSetByte(P39_1E_DSPC_TIMING_CTRL0, 0x00);
    }
#endif

    //===============================
    // Decide H direction scaling down
    //===============================
    // Set H Scaling Down Factor
    if(g_stMDomainInputData.usHWidth > pstFIFOScaling->usInputHWidth)
    {
        SET_H_SCALE_DOWN();

        // Calculate Scaling Factor
        // (4096 << 20) == 1<<32 DWORD  -> (IHwidth<<20)/(DHwidth) == (IHwidth<<19)/(DHwidth>>1)
        PDATA_DWORD(0) = (DWORD)g_stMDomainInputData.usHWidth << (20 - 1);
        PDATA_DWORD(0) = (PDATA_DWORD(0) / (pstFIFOScaling->usInputHWidth >> 1)) + (PDATA_DWORD(0) % 2);
        PDATA_DWORD(2) = PDATA_DWORD(0);
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_05_H_SD_FACTOR_H_M1, ((PDATA_DWORD(0) >> 16) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_06_H_SD_FACTOR_M_M1, ((PDATA_DWORD(0) >> 8) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_07_H_SD_FACTOR_L_M1, (PDATA_DWORD(0) & 0xFF));

        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_05_H_SD_FACTOR_H_M1, ((PDATA_DWORD(0) >> 16) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_06_H_SD_FACTOR_M_M1, ((PDATA_DWORD(0) >> 8) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_07_H_SD_FACTOR_L_M1, (PDATA_DWORD(0) & 0xFF));
        }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_05_H_SD_FACTOR_H_M1, ((PDATA_DWORD(0) >> 16) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_06_H_SD_FACTOR_M_M1, ((PDATA_DWORD(0) >> 8) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_07_H_SD_FACTOR_L_M1, (PDATA_DWORD(0) & 0xFF));

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_05_H_SD_FACTOR_H_M2, ((PDATA_DWORD(0) >> 16) & 0xFF));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_06_H_SD_FACTOR_M_M2, ((PDATA_DWORD(0) >> 8) & 0xFF));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_07_H_SD_FACTOR_L_M2, (PDATA_DWORD(0) & 0xFF));
        }
#endif
        // Calculate Initial Phase
        // (factor - 1) / 2  // 1.6
        PDATA_DWORD(0) = (PDATA_DWORD(0) >> 15) - 32;

        if(PDATA_DWORD(0) > 0x7F)
        {
            PDATA_DWORD(0) = 0x7F;
        }

        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_04_H_SD_INIT_M1, PDATA_DWORD(0));

        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_04_H_SD_INIT_M1, PDATA_DWORD(0));
        }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // extension
            PDATA_DWORD(1) = (DWORD)pstFIFOScaling->usInputHWidth * GET_FMTCNV_EXTENSION_LEN() / g_stMDomainInputData.usHWidth;

            if(PDATA_DWORD(1) > 0x1F)
            {
                PDATA_DWORD(1) = 0x1F;
            }

            if(PDATA_DWORD(1) > 0)
            {
                // extension + FIFOWidth must be even number
                if(((pstFIFOScaling->usInputHWidth >> 1) & 0x01) == 0x01)
                {
                    if((PDATA_DWORD(1) & 0x01) == 0x00)
                    {
                        PDATA_DWORD(1) = PDATA_DWORD(1) - 1;
                    }
                }
                else
                {
                    PDATA_DWORD(1) = (PDATA_DWORD(1) & 0xFFFE);
                }
            }

            SET_MDOMAIN_EXTENSION_LEN(PDATA_DWORD(1));
            SET_DDOMAIN_EXTENSION_LEN(PDATA_DWORD(1));

            // back initial phase = FrontInitialPhase + InExtension for each OutExtension*SDFactor
            PDATA_DWORD(0) = (PDATA_DWORD(0) << 14) + ((DWORD)GET_FMTCNV_EXTENSION_LEN() << 20) - (PDATA_DWORD(1) * PDATA_DWORD(2));

            // S1  initialphase
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_45_H_SD_INIT_H_M1, (PDATA_DWORD(0) >> 22) & 0x03);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_04_H_SD_INIT_M1, (PDATA_DWORD(0) >> 14) & 0xFF);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_43_H_SD_INIT_M_M1, (PDATA_DWORD(0) >> 6) & 0xFF);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_44_H_SD_INIT_L_M_M1, ((PDATA_DWORD(0) & 0x3F) << 2));

            // S2 initialphase
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_45_H_SD_INIT_H_M2, (PDATA_DWORD(0) >> 22) & 0x03);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_04_H_SD_INIT_M2, (PDATA_DWORD(0) >> 14) & 0xFF);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_43_H_SD_INIT_M_M2, (PDATA_DWORD(0) >> 6) & 0xFF);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_44_H_SD_INIT_L_M2, ((PDATA_DWORD(0) & 0x3F) << 2));

            // HSD extension
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_3A_SD_OUT_EXTENSION_M1, GET_MDOMAIN_EXTENSION_LEN());
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_3A_SD_OUT_EXTENSION_M2, GET_MDOMAIN_EXTENSION_LEN());
            ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_3A_SD_OUT_EXTENSION_S1, GET_MDOMAIN_EXTENSION_LEN());
            ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_3A_SD_OUT_EXTENSION_S2, GET_MDOMAIN_EXTENSION_LEN());
        }
#endif
    }
    else
    {
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_04_H_SD_INIT_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_05_H_SD_FACTOR_H_M1, 0x10);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_06_H_SD_FACTOR_M_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_07_H_SD_FACTOR_L_M1, 0x00);

        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_04_H_SD_INIT_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_05_H_SD_FACTOR_H_M1, 0x10);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_06_H_SD_FACTOR_M_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_07_H_SD_FACTOR_L_M1, 0x00);
        }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // extension
            PDATA_DWORD(1) = GET_FMTCNV_EXTENSION_LEN();

            if(PDATA_DWORD(1) > 0x1F)
            {
                PDATA_DWORD(1) = 0x1F;
            }

            if(PDATA_DWORD(1) > 0)
            {
                // extension + FIFOWidth must be even number
                if(((pstFIFOScaling->usInputHWidth >> 1) & 0x01) == 0x01)
                {
                    if((PDATA_DWORD(1) & 0x01) == 0x00)
                    {
                        PDATA_DWORD(1) = PDATA_DWORD(1) - 1;
                    }
                }
                else
                {
                    PDATA_DWORD(1) = (PDATA_DWORD(1) & 0xFFFE);
                }
            }
            SET_MDOMAIN_EXTENSION_LEN(PDATA_DWORD(1));
            SET_DDOMAIN_EXTENSION_LEN(PDATA_DWORD(1));

            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_04_H_SD_INIT_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_05_H_SD_FACTOR_H_M1, 0x10);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_06_H_SD_FACTOR_M_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_07_H_SD_FACTOR_L_M1, 0x00);

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_04_H_SD_INIT_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_05_H_SD_FACTOR_H_M2, 0x10);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_06_H_SD_FACTOR_M_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_07_H_SD_FACTOR_L_M2, 0x00);

            // HSD extension
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1, _P0_25_PT_3A_SD_OUT_EXTENSION_M1, GET_MDOMAIN_EXTENSION_LEN());
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2, _P40_25_PT_3A_SD_OUT_EXTENSION_M2, GET_MDOMAIN_EXTENSION_LEN());
            ScalerSetDataPortByte(P80_24_SD_ADDRESS_PORT_S1, _P80_25_PT_3A_SD_OUT_EXTENSION_S1, GET_MDOMAIN_EXTENSION_LEN());
            ScalerSetDataPortByte(PC0_24_SD_ADDRESS_PORT_S2, _PC0_25_PT_3A_SD_OUT_EXTENSION_S2, GET_MDOMAIN_EXTENSION_LEN());
        }
#endif
    }

    if(GET_H_SCALE_DOWN() == _TRUE)
    {
        // Enable H Scale Down
        // M1
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~(_BIT3 | _BIT1), _BIT1);

        if(bEvenOdd == _TRUE)
        {
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel + 0x4000, ~(_BIT3 | _BIT1), _BIT1);
        }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // S1
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0x8000, ~(_BIT3 | _BIT1), _BIT1);
            // S2
            ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2 + 0x8000, ~(_BIT3 | _BIT1), _BIT1);
        }
#endif
    }

    //===============================
    // Decide V direction scaling down
    //===============================
    // Set V Scaling Down Factor
    if((g_stMDomainInputData.usVHeight) > pstFIFOScaling->usInputVHeight)
    {
        SET_V_SCALE_DOWN();

        // Calculate Scaling Factor
        PDATA_DWORD(0) = ((DWORD)(g_stMDomainInputData.usVHeight) << 20);
        PDATA_DWORD(0) = (PDATA_DWORD(0) / pstFIFOScaling->usInputVHeight) + (PDATA_DWORD(0) % 2);
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_01_V_SD_FACTOR_H_M1, ((PDATA_DWORD(0) >> 19) & 0x0F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_02_V_SD_FACTOR_M_M1, ((PDATA_DWORD(0) >> 11) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_03_V_SD_FACTOR_L_M1, ((PDATA_DWORD(0) >> 3) & 0xFF));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_42_V_SD_FACTOR_L1_M1, (((PDATA_DWORD(0) & 0x07) << 5) & 0xE0));

        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_01_V_SD_FACTOR_H_M1, ((PDATA_DWORD(0) >> 19) & 0x0F));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_02_V_SD_FACTOR_M_M1, ((PDATA_DWORD(0) >> 11) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_03_V_SD_FACTOR_L_M1, ((PDATA_DWORD(0) >> 3) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_42_V_SD_FACTOR_L1_M1, (((PDATA_DWORD(0) & 0x07) << 5) & 0xE0));
        }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_01_V_SD_FACTOR_H_M1, ((PDATA_DWORD(0) >> 19) & 0x0F));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_02_V_SD_FACTOR_M_M1, ((PDATA_DWORD(0) >> 11) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_03_V_SD_FACTOR_L_M1, ((PDATA_DWORD(0) >> 3) & 0xFF));
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_42_V_SD_FACTOR_L1_M1, (((PDATA_DWORD(0) & 0x07) << 5) & 0xE0));

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_01_V_SD_FACTOR_H_M2, ((PDATA_DWORD(0) >> 19) & 0x0F));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_02_V_SD_FACTOR_M_M2, ((PDATA_DWORD(0) >> 11) & 0xFF));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_03_V_SD_FACTOR_L_M2, ((PDATA_DWORD(0) >> 3) & 0xFF));
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_42_V_SD_FACTOR_L1_M2, (((PDATA_DWORD(0) & 0x07) << 5) & 0xE0));
        }
#endif

        // Calculate Initial Phase
        PDATA_DWORD(0) = (PDATA_DWORD(0) >> 15) - 32;

        if(PDATA_DWORD(0) > 0x7F)
        {
            PDATA_DWORD(0) = 0x7F;
        }
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_00_V_SD_INIT_M1, PDATA_DWORD(0));

        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_00_V_SD_INIT_M1, PDATA_DWORD(0));
        }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_00_V_SD_INIT_M1, PDATA_DWORD(0));

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_00_V_SD_INIT_M2, PDATA_DWORD(0));
        }
#endif
    }
    else
    {
        // M1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_00_V_SD_INIT_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_01_V_SD_FACTOR_H_M1, 0x02);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_02_V_SD_FACTOR_M_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_03_V_SD_FACTOR_L_M1, 0x00);
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 0x00);

        if(bEvenOdd == _TRUE)
        {
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_00_V_SD_INIT_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_01_V_SD_FACTOR_H_M1, 0x02);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_02_V_SD_FACTOR_M_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_03_V_SD_FACTOR_L_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 0x00);
        }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // S1
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_00_V_SD_INIT_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_01_V_SD_FACTOR_H_M1, 0x02);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_02_V_SD_FACTOR_M_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_03_V_SD_FACTOR_L_M1, 0x00);
            ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_42_V_SD_FACTOR_L1_M1, 0x00);

            // S2
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_00_V_SD_INIT_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_01_V_SD_FACTOR_H_M2, 0x02);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_02_V_SD_FACTOR_M_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_03_V_SD_FACTOR_L_M2, 0x00);
            ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_42_V_SD_FACTOR_L1_M2, 0x00);
        }
#endif
    }

    if(GET_V_SCALE_DOWN() == _TRUE)
    {
        // Enable V Scale Down
        // M1
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~_BIT0, _BIT0);

        if(bEvenOdd == _TRUE)
        {
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel + 0x4000, ~_BIT0, _BIT0);
        }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // S1
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0x8000, ~_BIT0, _BIT0);
            // S2
            ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2 + 0x8000, ~_BIT0, _BIT0);
        }
#endif
    }

    PDATA_WORD(0) = pstFIFOScaling->usInputVHeight;

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    // Interlaced mode, Idomain Single Mode
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
#endif
    {
        PDATA_WORD(0) = PDATA_WORD(0) >> (WORD)bEvenOdd;
    }

    PDATA_WORD(1) = pstFIFOScaling->usInputHWidth;

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        PDATA_WORD(1) = pstFIFOScaling->usInputHWidth >> 1;
    }
#endif

    // Enable SD Out Window Set
    // M1
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_36_SD_OUT_WID_M_M1, (pData[2] & 0x0F));
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_37_SD_OUT_WID_L_M1, pData[3]);

    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_38_SD_OUT_LEN_M_M1, (pData[0] & 0x0F));
    ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel, _P0_25_PT_39_SD_OUT_LEN_L_M1, pData[1]);

    ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel, ~_BIT3, 0x00);

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Enable Scale Down
        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1, ~_BIT0, _BIT0);
        ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2, ~_BIT0, _BIT0);

        // Enable Scale Down FREESYNC Mode
        ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~_BIT1, _BIT1);
        ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~_BIT1, _BIT1);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            // Enable Scale Down
            ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0x8000, ~_BIT0, _BIT0);
            ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2 + 0x8000, ~_BIT0, _BIT0);

            // Enable Scale Down FREESYNC Mode
            ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1 + 0x8000, ~_BIT1, _BIT1);
            ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2 + 0x8000, ~_BIT1, _BIT1);
        }
#endif

        if(GET_V_SCALE_DOWN() == _TRUE)
        {
            // Set Coefficient table 2
            ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Set Coefficient table 2
            ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(ScalerFmtCnvFBGetStatus() == _TRUE)
            {
                // Set Coefficient table 2
                ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1 + 0x8000, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1 + 0x8000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

                // Set Coefficient table 2
                ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2 + 0x8000, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2 + 0x8000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
            }
#endif
        }
        else
        {
            // Set Coefficient table 2
            ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerBurstWrite(tSD_V_COEF_64_TAPS_BYPASS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Set Coefficient table 2
            ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerBurstWrite(tSD_V_COEF_64_TAPS_BYPASS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(ScalerFmtCnvFBGetStatus() == _TRUE)
            {
                // Set Coefficient table 2
                ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1 + 0x8000, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                ScalerBurstWrite(tSD_V_COEF_64_TAPS_BYPASS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1 + 0x8000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

                // Set Coefficient table 2
                ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2 + 0x8000, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                ScalerBurstWrite(tSD_V_COEF_64_TAPS_BYPASS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2 + 0x8000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
            }
#endif
        }

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
        {
            // Set IVst = 2
            g_stMDomainInputData.usVStart = 2;
        }
        else
#endif
        {
            // Set IVst = 1
            g_stMDomainInputData.usVStart = 1;
        }
    }
    else
    {
        if(GET_V_SCALE_DOWN() == _TRUE)
        {
            // Set Coefficient table 2
            ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

            // Set Coefficient table 2
            ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(ScalerFmtCnvFBGetStatus() == _TRUE)
            {
                // Set Coefficient table 2
                ScalerSetBit(P0_26_SD_FILTER_CONTROL_REG_M1 + 0x8000, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_27_SD_USER_FILTER_ACCESS_PORT_M1 + 0x8000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

                // Set Coefficient table 2
                ScalerSetBit(P40_26_SD_FILTER_CONTROL_REG_M2 + 0x8000, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
                ScalerBurstWrite(tSD_V_COEF_64_TAPS, _VSD_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P40_27_SD_USER_FILTER_ACCESS_PORT_M2 + 0x8000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
            }
#endif
        }
    }
#endif

    if(bEvenOdd == _TRUE)
    {
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_36_SD_OUT_WID_M_M1, (pData[2] & 0x0F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_37_SD_OUT_WID_L_M1, pData[3]);

        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_38_SD_OUT_LEN_M_M1, (pData[0] & 0x0F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + usRegPageSel + 0x4000, _P0_25_PT_39_SD_OUT_LEN_L_M1, pData[1]);

        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + usRegPageSel + 0x4000, ~_BIT3, 0x00);
    }

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        // S1
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_36_SD_OUT_WID_M_M1, (pData[2] & 0x0F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_37_SD_OUT_WID_L_M1, pData[3]);

        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_38_SD_OUT_LEN_M_M1, (pData[0] & 0x0F));
        ScalerSetDataPortByte(P0_24_SD_ADDRESS_PORT_M1 + 0x8000, _P0_25_PT_39_SD_OUT_LEN_L_M1, pData[1]);

        ScalerSetBit(P0_23_SCALE_DOWN_CTRL_M1 + 0x8000, ~_BIT3, 0x00);

        // S2
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_36_SD_OUT_WID_M_M2, (pData[2] & 0x0F));
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_37_SD_OUT_WID_L_M2, pData[3]);

        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_38_SD_OUT_LEN_M_M2, (pData[0] & 0x0F));
        ScalerSetDataPortByte(P40_24_SD_ADDRESS_PORT_M2 + 0x8000, _P40_25_PT_39_SD_OUT_LEN_L_M2, pData[1]);

        ScalerSetBit(P40_23_SCALE_DOWN_CTRL_M2 + 0x8000, ~_BIT3, 0x00);
    }
#endif
}

//--------------------------------------------------
// Description  : Get fifo scaling size
// Input Value  : Input/Output H/V Active Region
// Output Value : _FAIL /_SUCCESS
//--------------------------------------------------
bit ScalerScalingGetFIFOScalingSize(StructSDRAMDataInfo *pstData)
{
    // Update fifo scaling size
    ScalerScalingUpdateFIFOScalingSize(pstData);

#if(_FRC_SUPPORT == _ON)
    // Check when SD/SU happened simultaneously due to BW/memory space limititation
    if((g_stMDomainInputData.usHWidth > pstData->usInputHWidth) &&
       (g_stMDomainOutputData.usHWidth > pstData->usInputHWidth))
    {
        if(GET_MEMORY_DATA_BIT() >= (_COLOR_DEPTH_10_BITS * 3))
        {
            DebugMessageFRC("4. FRC truncate color bit", GET_MEMORY_DATA_BIT());

            // Truncate color depth to 8 bit
            ScalerMDomainSetMemoryDataBit(_COLOR_DEPTH_8_BITS);

            // Update fifo scaling size
            ScalerScalingUpdateFIFOScalingSize(pstData);
        }
    }

    // Check HSD Ratio
    if((g_stMDomainInputData.usHWidth > pstData->usInputHWidth) &&
       (g_stMDomainOutputData.usHWidth > pstData->usInputHWidth))
    {
        if((g_stMDomainInputData.usHWidth / pstData->usInputHWidth) > _HSD_MAX_RATIO)
        {
            DebugMessageFRC("Fail : HSD > Max HSD Ratio", pstData->usInputHWidth);
            return _FAIL;
        }
    }
#endif

#if(_PBP_TB_DISPLAY_SUPPORT == _ON)
    // Check TB TOP display size
    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB) &&
       (GET_MDOMAIN_OUTPUT_DATA_PATH() == _DISPLAY_PATH_M1))
    {
        // Keep TOP dispaly V height when:
        // 1. Top VSU is disabled
        // 2. DVend_top(active) != DVend_top(background)
        // 3. (DHend_top - DHtotal_top / 2) < FIFO_IHWidth_top
        if(pstData->usOutputVHeight >= GET_MDOMAIN_OUTPUT_VHEIGHT())
        {
            return _SUCCESS;
        }
        else if((GET_MDOMAIN_OUTPUT_VSTART() + GET_MDOMAIN_OUTPUT_VHEIGHT()) !=
                (GET_MDOMAIN_OUTPUT_VBSTART() + _PANEL_DV_HEIGHT / 2))
        {
            return _SUCCESS;
        }
        else if((GET_MDOMAIN_OUTPUT_HSTART() + GET_MDOMAIN_OUTPUT_HWIDTH()) <
                (GET_MDOMAIN_OUTPUT_HTOTAL() / 2 + pstData->usInputHWidth))
        {
            return _SUCCESS;
        }
        else
        {
            // Shrink TOP display V height by 1 for M-domain
            g_stMDomainOutputData.usVHeight = (g_stMDomainOutputData.usVHeight - 1);
        }
    }
#endif

    return _SUCCESS;
}

#if(_SHARPNESS_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Set ScaleUp Coef
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerScalingSetScalingUpCoef(void)
{
    // M1
    // Set Coefficient table 1
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _HSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _VSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P0_36_USER_DEF_FILTER_ACCESS_PORT, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable Coefficient Access, Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetBit(P0_35_FILTER_CONTROL_REG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

    // M2
    // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetBit(P40_35_FILTER_CONTROL_REG_M2, ~(_BIT5 | _BIT4), _BIT4);


    // S1
    // Set Coefficient table 1
    ScalerSetBit(P80_35_FILTER_CONTROL_REG_S1, ~(_BIT7 | _BIT6), _BIT7);
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _HSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P80_36_USER_DEF_FILTER_ACCESS_PORT_S1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Set Coefficient table 2
    ScalerSetBit(P80_35_FILTER_CONTROL_REG_S1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite(tSD_SU_COEF_128_TAPS, _VSU_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), P80_36_USER_DEF_FILTER_ACCESS_PORT_S1, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable Coefficient Access, Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetBit(P80_35_FILTER_CONTROL_REG_S1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

    // S2
    // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetBit(PC0_35_FILTER_CONTROL_REG_S2, ~(_BIT5 | _BIT4), _BIT4);
}
#endif
