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
// ID Code      : ScalerMemory.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MEMORY__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_SHARPNESS_SUPPORT == _ON)
#define _SHARPNESS_TABLE_SIZE                       (128)
#endif


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
#if(_SHARPNESS_SUPPORT == _ON)
void ScalerMemorySetScalingCoef(EnumSelRegion enumSelRegion, BYTE code *pucAddress1, BYTE code *pucAddress2, BYTE ucBankNum);
#endif

void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq);
void ScalerMemoryInitial(void);
WORD ScalerMemoryGetScaleUpDt(void);
void ScalerMemorySetFifoCapture(EnumInputDataPath enumInputDataPath, WORD usHWidth, WORD usVHeight);
void ScalerMemoryCompensateDtForLastLine(DWORD ulTargetLastLine, DWORD ulCurrentLastLine);
void ScalerMemorySetIVS2DVSLineDelay(WORD usIVS2DVSDelay);
void ScalerMemoryFineTuneIVS2DVSDelay(WORD usOldIVS2DVSDelay, WORD usNewIVS2DVSDelay, WORD usIVS2DVSChgLimit);

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
void ScalerMemoryReset(void);
void ScalerMemoryPowerControl(bit bOnOff);
void ScalerMemorySetFrameTrackingEnable(bit bEn);
#endif

#if(_FRC_SUPPORT == _ON)
void ScalerMemoryFrameTracking(void);
WORD ScalerMemoryGetMNRatio(void);
DWORD ScalerMemoryAddressConversion(DWORD ulTotalSize);
void ScalerMemoryCalculateLineStepAndBlockStep(DWORD ulHorSize, WORD usVerSize, StructMemoryLineBlockStep *pstMemoryLineBlockStep);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_SHARPNESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Scale Up coef
// Input Value  : H/V coef table, length
// Output Value : none
//--------------------------------------------------
void ScalerMemorySetScalingCoef(EnumSelRegion enumSelRegion, BYTE code *pucAddress1, BYTE code *pucAddress2, BYTE ucBankNum)
{
    WORD usCoefWritePage = 0x00;
    WORD usCoefSelPage = 0x00;
    bit bTableHorUseSel = 0;
    bit bTableVerUseSel = 0;

    switch(enumSelRegion)
    {
        case _1P_NORMAL_FULL_REGION:
        case _1P_ROTATION_FULL_REGION:
        case _PIP_MAIN:
        case _PBP_LR_L:
        case _PBP_TB_T:

            usCoefWritePage = _REG_MAIN1_PAGE;
            usCoefSelPage = _REG_MAIN1_PAGE;
            bTableHorUseSel = 0;
            bTableVerUseSel = 1;
            // M2 coef table map to M1 or S1
            // default:0 map to S1 // 4p should be setted to 1, map to M1
            ScalerSetBit(P40_37_SCALE_UP_FOR_LINE_INTERLEAVE_M2, ~_BIT0, 0x00);
            break;

        case _PIP_SUB:
        case _PBP_LR_R:

            usCoefWritePage = _REG_SUB1_PAGE;
            usCoefSelPage = _REG_SUB1_PAGE;
            bTableHorUseSel = 0;
            bTableVerUseSel = 1;
            ScalerSetBit(P40_37_SCALE_UP_FOR_LINE_INTERLEAVE_M2, ~_BIT0, 0x00);
            break;

        case _PBP_TB_B:

            usCoefWritePage = _REG_SUB1_PAGE;
            usCoefSelPage = _REG_MAIN2_PAGE;
            bTableHorUseSel = 0;
            bTableVerUseSel = 1;
            ScalerSetBit(P40_37_SCALE_UP_FOR_LINE_INTERLEAVE_M2, ~_BIT0, 0x00);
            break;

        case _4P_LT:

            usCoefWritePage = _REG_MAIN1_PAGE;
            usCoefSelPage = _REG_MAIN1_PAGE;
            bTableHorUseSel = 0;
            bTableVerUseSel = 0;
            ScalerSetBit(P40_37_SCALE_UP_FOR_LINE_INTERLEAVE_M2, ~_BIT0, _BIT0);
            break;

        case _4P_LB:

            usCoefWritePage = _REG_MAIN1_PAGE;
            usCoefSelPage = _REG_MAIN2_PAGE;
            bTableHorUseSel = 1;
            bTableVerUseSel = 1;
            ScalerSetBit(P40_37_SCALE_UP_FOR_LINE_INTERLEAVE_M2, ~_BIT0, _BIT0);
            break;

        case _4P_RT:

            usCoefWritePage = _REG_SUB1_PAGE;
            usCoefSelPage = _REG_SUB1_PAGE;
            bTableHorUseSel = 0;
            bTableVerUseSel = 0;
            ScalerSetBit(P40_37_SCALE_UP_FOR_LINE_INTERLEAVE_M2, ~_BIT0, _BIT0);
            break;

        case _4P_RB:

            usCoefWritePage = _REG_SUB1_PAGE;
            usCoefSelPage = _REG_SUB2_PAGE;
            bTableHorUseSel = 1;
            bTableVerUseSel = 1;
            ScalerSetBit(P40_37_SCALE_UP_FOR_LINE_INTERLEAVE_M2, ~_BIT0, _BIT0);
            break;

        case _PIP_FULL_REGION:
        case _PBP_LR_FULL_REGION:
        case _PBP_TB_FULL_REGION:
        case _4P_FULL_REGION:
        case _4P_LT_OUTSIDE:
        case _4P_LB_OUTSIDE:
        case _4P_RT_OUTSIDE:
        case _4P_RB_OUTSIDE:
        case _1P_NORMAL_DEMO_INSIDE:
        case _1P_NORMAL_DEMO_OUTSIDE:
        case _PIP_DEMO_INSIDE:
        case _PIP_DEMO_OUTSIDE:
        case _PBP_LR_DEMO_INSIDE:
        case _PBP_LR_DEMO_OUTSIDE:
        case _PBP_TB_DEMO_INSIDE:
        case _PBP_TB_DEMO_OUTSIDE:
        case _4P_DEMO_INSIDE:
        case _4P_DEMO_OUTSIDE:
        default:
            break;
    }

    // Set Coefficient table 1
    ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage, ~(_BIT7 | _BIT6), (_BIT7 | ((BYTE)bTableHorUseSel << 6)));
    ScalerBurstWrite(pucAddress1, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT + usCoefWritePage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    if(bTableVerUseSel != bTableHorUseSel)
    {
        // Set Coefficient table 2
        ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage, ~(_BIT7 | _BIT6), (_BIT7 | ((BYTE)bTableVerUseSel << 6)));
        ScalerBurstWrite(pucAddress2, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT + usCoefWritePage, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    }

    // Disable Coefficient Access,
    ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

    // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
    ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefSelPage, ~(_BIT5 | _BIT4), (((BYTE)bTableHorUseSel << 5) | ((BYTE)bTableVerUseSel << 4)));

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(ScalerFmtCnvFBGetStatus() == _TRUE)
    {
        // Set Coefficient table 1
        ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage + 0x8000, ~(_BIT7 | _BIT6), (_BIT7 | ((BYTE)bTableHorUseSel << 6)));
        ScalerBurstWrite(pucAddress1, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT + usCoefWritePage + 0x8000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

        if(bTableVerUseSel != bTableHorUseSel)
        {
            // Set Coefficient table 2
            ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage + 0x8000, ~(_BIT7 | _BIT6), (_BIT7 | ((BYTE)bTableVerUseSel << 6)));
            ScalerBurstWrite(pucAddress2, _SHARPNESS_TABLE_SIZE, ucBankNum, P0_36_USER_DEF_FILTER_ACCESS_PORT + usCoefWritePage + 0x8000, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
        }

        // Disable Coefficient Access,
        ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefWritePage + 0x8000, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // Set HSU to use coefficient table 1 & set VSU to use coefficient table 2
        ScalerSetBit(P0_35_FILTER_CONTROL_REG + usCoefSelPage + 0x8000, ~(_BIT5 | _BIT4), (((BYTE)bTableHorUseSel << 5) | ((BYTE)bTableVerUseSel << 4)));
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Set FIFO Clock
// Input Value  : Target FIFO Clock
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFIFOFreq(EnumScalerFIFOFreq enumFIFOFreq)
{
    switch(enumFIFOFreq)
    {
        case _SCALER_FIFO_FREQ_M2PLL:
            ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            break;

        case _SCALER_FIFO_FREQ_MPLL:
            ScalerSetBit(P0_22_M1_FIFO_CLOCK_SELECT, ~(_BIT1 | _BIT0), 0x00);
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : M Domain Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryInitial(void)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
    //------------------------------
    // DDR Initial
    //------------------------------

#endif

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
    //------------------------------
    // FRC Initial
    //------------------------------
    ScalerFRCInitial();
#endif

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    //------------------------------
    // Rotation Initial
    //------------------------------
    ScalerRotationInitial();
#endif
}

//--------------------------------------------------
// Description  : Calculate Dt Value for Scale Up
// Input Value  : None
// Output Value : Calculated Dt in 0.01 Lines
//--------------------------------------------------
WORD ScalerMemoryGetScaleUpDt(void)
{
    BYTE ucMax = 0;
    BYTE ucMin = 100;
    BYTE ucCount = 0;
    BYTE ucPhase = 0;
    WORD usDtMin = 0;
    WORD usDtMax = 0;
    WORD usSUF = 0;
    WORD usFIFOHWidth = 0;
    WORD usDt = 0;
    DWORD ulVFCI = 0;

    //-------------------------------------------------
    // Get Ver filter coef initial value: 20 bit
    //-------------------------------------------------
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_11_VER_FILTER_COEF_INI, 1, &pData[0], _NON_AUTOINC);
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_16_VER_FILTER_COEF_INI_M, 1, &pData[1], _NON_AUTOINC);
    ScalerGetDataPortByte(P0_33_SF_ADDR_PORT, _P0_34_PT_17_VER_FILTER_COEF_INI_L, 1, &pData[2], _NON_AUTOINC);

    ulVFCI = ((((DWORD)pData[0] << 12) & 0xFF000) | (((DWORD)pData[1] << 4) & 0x00FF0) | ((pData[2] >> 4) & 0x0000F));

    // VFCI * 128
    ulVFCI = (ulVFCI >> 13);

    // Since MSB would be Eliminated by Mod, Only WORD is Required
    usSUF = (WORD)(((DWORD)g_stMDomainInputData.usVHeight << 13) / g_stMDomainOutputData.usVHeight);

    // Get Min and Max Value
    do
    {
        // (VFCI + n * VSF) mod 1
        ucPhase = (BYTE)(((WORD)ulVFCI + (((WORD)ucCount * usSUF) >> 6)) & 0x7F);

        if(ucPhase > ucMax)
        {
            ucMax = ucPhase;
        }

        if(ucPhase < ucMin)
        {
            ucMin = ucPhase;
        }

        ucCount++;
    }
    while(ucCount < 255);

    DebugMessageFS("Calculated Max", ucMax);
    DebugMessageFS("Calculated Min", ucMin);

    //-------------------------------------------------
    // Get FIFO Input Width: 13 bit
    //-------------------------------------------------
    ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_00_DISPLAY_READ_WID_BSU_H, 1, &pData[0], _NON_AUTOINC);
    ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_01_DISPLAY_READ_WID_BSU_L, 1, &pData[1], _NON_AUTOINC);
    ScalerGetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, _P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H, 1, &pData[2], _NON_AUTOINC);

    usFIFOHWidth = ((((WORD)pData[2] << 8) & 0x1000) | (((WORD)pData[0] << 4) & 0xF00) | pData[1]);

    // VFCI * 100
    ulVFCI = (ulVFCI * 100) >> 7;

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            usFIFOHWidth = usFIFOHWidth / 2;

            // DtMin = 1  +(VFCI-min)/2+ VSF/2 - VSF*DHActiveEnd/DHTotal/2
            usDtMin = 100 + (ulVFCI >> 1) - (((WORD)ucMin * 100) >> 8) + (DWORD)g_stMDomainInputData.usVHeight  * 50 / g_stMDomainOutputData.usVHeight - (DWORD)g_stMDomainInputData.usVHeight * (g_stMDomainOutputData.usHStart + g_stMDomainOutputData.usHWidth / 2) / g_stMDomainOutputData.usVHeight * 50 / (g_stMDomainOutputData.usHWidth / 2);
            usDtMin = usDtMin << 1;

            // DtMax = 1 + FIFODepth/FIFOHWidth each(max-VFCI)/2 each VSF*(DHActiveStart/DHTotal)
            usDtMax = 100 + (DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 100 / usFIFOHWidth + (ulVFCI >> 1) - ((WORD)ucMax * 100 >> 8) - (DWORD)g_stMDomainInputData.usVHeight * g_stMDomainOutputData.usHStart / g_stMDomainOutputData.usVHeight * 50 / (g_stMDomainOutputData.usHTotal / 2);
            usDtMax = usDtMax << 1;
        }
        else
#endif
        {
            // DtMin = 1  +(VFCI-min)/2+ VSF/2 - VSF*DHActiveEnd/DHTotal/2
            usDtMin = 100 + (ulVFCI >> 1) - (((WORD)ucMin * 100) >> 8) + (DWORD)g_stMDomainInputData.usVHeight  * 50 / g_stMDomainOutputData.usVHeight - (DWORD)g_stMDomainInputData.usVHeight * (g_stMDomainOutputData.usHStart + g_stMDomainOutputData.usHWidth) / g_stMDomainOutputData.usVHeight * 50 / g_stMDomainOutputData.usHWidth;
            usDtMin = usDtMin << 1;

            // DtMax = 1 + FIFODepth/FIFOHWidth each(max-VFCI)/2 each VSF*(DHActiveStart/DHTotal)
            usDtMax = 100 + (DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 100 / usFIFOHWidth + (ulVFCI >> 1) - (((WORD)ucMax * 100) >> 8) - (DWORD)g_stMDomainInputData.usVHeight * g_stMDomainOutputData.usHStart / g_stMDomainOutputData.usVHeight * 50 / g_stMDomainOutputData.usHTotal;
            usDtMax = usDtMax << 1;
        }
    }
    else
#endif
    {
        // Dt min = 2 + (VFCI - min - VSF * DHActiveEnd / DHTotal)
        usDtMin = 200 + ulVFCI - (((WORD)ucMin * 100) >> 7) - (DWORD)g_stMDomainInputData.usVHeight * (g_stMDomainOutputData.usHStart + g_stMDomainOutputData.usHWidth) / g_stMDomainOutputData.usVHeight * 100 / g_stMDomainOutputData.usHTotal;

        // Dt max = 2 + FIFODepth / FIFOWIDTH - max + VFCI - VSF * DHActiveSt / DHTotal
        usDtMax = 200 + (DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() * 100 / usFIFOHWidth - (((WORD)ucMax * 100) >> 7) + ulVFCI - (DWORD)g_stMDomainInputData.usVHeight * g_stMDomainOutputData.usHStart / g_stMDomainOutputData.usVHeight * 100 / g_stMDomainOutputData.usHTotal;
    }

    DebugMessageFS("2. DtMax", usDtMax);
    DebugMessageFS("2. DtMin", usDtMin);

    usDt = (usDtMax + usDtMin) / 2;
    DebugMessageFS("2. Target Dt Value", usDt);

    // Calculat (I porch - 2)
    PDATA_WORD(0) = (g_stMDomainInputData.usVTotal > (g_stMDomainInputData.usVHeight + 2)) ? (g_stMDomainInputData.usVTotal - (g_stMDomainInputData.usVHeight + 2)) : 0;

    // Dt must small than (I portch - 2)
    if(usDt >= (PDATA_WORD(0) * 100))
    {
        usDt = ((PDATA_WORD(0) * 100) + usDtMin) / 2;
        DebugMessageFS("2. Target Dt Value new", usDt);
    }

    return usDt;
}

//--------------------------------------------------
// Description  : Set FIFO Capture
// Input Value  : Input/Output H/V Active Region
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFifoCapture(EnumInputDataPath enumInputDataPath, WORD usHWidth, WORD usVHeight)
{
    WORD usPageSelect = 0x0000;
    BYTE ucRegSelect = 0x00;
    BYTE ucIdx = 0x00;

#if(_FRC_SUPPORT == _ON)
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(ScalerRotationCheckStatus() == _TRUE)
    {
        // Enable display frame sync fifo for rotation
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_24_DISP_MAIN_FIFO_LEN_CTRL, ~_BIT2, 0x00);
    }
    else
#endif
#endif
    {
        ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_24_DISP_MAIN_FIFO_LEN_CTRL, ~_BIT2, _BIT2);
    }

    for(ucIdx = 0; ucIdx < 4; ucIdx++)
    {
        if((enumInputDataPath & ((BYTE)_INPUT_PATH_M1 << ucIdx)) == ((BYTE)_INPUT_PATH_M1 << ucIdx))
        {
            ucRegSelect = (ucIdx % 2) * 4;

            if((enumInputDataPath & ((BYTE)_INPUT_PATH_M1 | _INPUT_PATH_M2)) != 0)
            {
                // (Display mode != PBP_TB) || ((Display mode == PBP_TB) && M1)
                if((GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_PBP_TB) ||
                   ((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB) && (ucIdx == 0)))
                {
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_00_DISPLAY_READ_WID_BSU_H + ucRegSelect), (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_01_DISPLAY_READ_WID_BSU_L + ucRegSelect), LOBYTE(usHWidth));
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_02_DISPLAY_READ_LEN_BSU_L + ucRegSelect), LOBYTE(usVHeight));
                    ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_03_DISPLAY_READ_WID_LEN_BSU_H + ucRegSelect), ~(_BIT4 | _BIT0), (((usHWidth & 0x1000) >> 8) | ((usVHeight & 0x1000) >> 12)));
                }
            }

            if((enumInputDataPath & ((BYTE)_INPUT_PATH_S1 | _INPUT_PATH_S2)) != 0)
            {
                if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB)
                {
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_04_DISPLAY_READ_WID_BSU_H_M2), (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_05_DISPLAY_READ_WID_BSU_L_M2), LOBYTE(usHWidth));
                    ScalerSetDataPortByte(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_06_DISPLAY_READ_LEN_BSU_L_M2), LOBYTE(usVHeight));
                    ScalerSetDataPortBit(P0_30_FIFO_WINDOW_ADDR_PORT, (_P0_31_PT_07_DISPLAY_READ_WID_LEN_BSU_H_M2), ~(_BIT4 | _BIT0), (((usHWidth & 0x1000) >> 8) | ((usVHeight & 0x1000) >> 12)));
                }
                else
                {
                    ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_S, (_P80_31_PT_00_DISPLAY_READ_WID_BSU_H_S1 + ucRegSelect), (((HIBYTE(usHWidth) & 0x0F) << 4) | (HIBYTE(usVHeight) & 0x0F)));
                    ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_S, (_P80_31_PT_01_DISPLAY_READ_WID_BSU_L_S1 + ucRegSelect), LOBYTE(usHWidth));
                    ScalerSetDataPortByte(P80_30_FIFO_WINDOW_ADDR_PORT_S, (_P80_31_PT_02_DISPLAY_READ_LEN_BSU_L_S1 + ucRegSelect), LOBYTE(usVHeight));
                }
            }

            usPageSelect = ((WORD)ucIdx * 0x4000);

            if(GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER)
            {
                // Set Pre-Read line
                ScalerSetByte(P5_A6_DISP_M1_PRRD_VST_H + usPageSelect, HIBYTE(_PRE_READ_LINE_BUFFER));
                ScalerSetByte(P5_A7_DISP_M1_PRRD_VST_L + usPageSelect, LOBYTE(_PRE_READ_LINE_BUFFER));

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                if(ScalerFmtCnvFBGetStatus() == _TRUE)
                {
                    PDATA_WORD(0) = (usHWidth >> 1) + GET_MDOMAIN_EXTENSION_LEN();
                }
                else
#endif
                {
                    PDATA_WORD(0) = usHWidth;
                }

                // Set Capture Line Pixel Number
                ScalerSetByte(P5_1F_CAP_M1_PIXEL_NUM_H + usPageSelect, HIBYTE(PDATA_WORD(0)));
                ScalerSetByte(P5_20_CAP_M1_PIXEL_NUM_L + usPageSelect, LOBYTE(PDATA_WORD(0)));
                ScalerSetByte(P5_A2_DISP_M1_PXL_NUM_H + usPageSelect, HIBYTE(PDATA_WORD(0)));
                ScalerSetByte(P5_A3_DISP_M1_PXL_NUM_L + usPageSelect, LOBYTE(PDATA_WORD(0)));

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
                if(ScalerFmtCnvFtoPGetStatus(_INPUT_PATH_M1_M2) == _TRUE)
                {
                    // Set Display Line Number to half height
                    ScalerSetByte(P5_21_CAP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVHeight >> 1));
                    ScalerSetByte(P5_22_CAP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVHeight >> 1));
                    ScalerSetByte(P5_A4_DISP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVHeight >> 1));
                    ScalerSetByte(P5_A5_DISP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVHeight >> 1));
                }
                else
#endif
                {
                    // Set Display Line Number
                    ScalerSetByte(P5_21_CAP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVHeight));
                    ScalerSetByte(P5_22_CAP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVHeight));
                    ScalerSetByte(P5_A4_DISP_M1_LINE_NUM_H + usPageSelect, HIBYTE(usVHeight));
                    ScalerSetByte(P5_A5_DISP_M1_LINE_NUM_L + usPageSelect, LOBYTE(usVHeight));
                }
            }

            // Set Input Format 30 Bit
            if(GET_MEMORY_DATA_BIT() == (_COLOR_DEPTH_10_BITS * 3))
            {
                ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2 + usPageSelect, ~_BIT7, _BIT7);
            }
            else
            {
                ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2 + usPageSelect, ~_BIT7, 0x00);
            }

            // FRC display double buffer apply
            ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~_BIT4, _BIT4);
        }
    }
}

//--------------------------------------------------
// Description  : Compensate Last Line Fine Tune
// Input Value  : Target Last Line, Current Last Line
// Output Value : None
//--------------------------------------------------
void ScalerMemoryCompensateDtForLastLine(DWORD ulTargetLastLine, DWORD ulCurrentLastLine)
{
    DWORD ulCompsIVS2DVSpixel = 0;
    BYTE ucEOshift = 0;
    BYTE ucFBshift = 0;

    // Get Initial Dt Fine Tune Value
    PDATA_DWORD(0) = ScalerMemoryGetIVS2DVSDelayPixel();

    DebugMessageFS("Original Dt", PDATA_DWORD(0));

    // Compensate Dt = Original Dt + ((Target Last Line - Current Last Line) * DVHeight / DVTotal * IVHeight / DVHeight * IHTotal / DHTotal) / 2
    ulCompsIVS2DVSpixel = (SDWORD)PDATA_DWORD(0) + ((((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine) * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVTotal * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal) >> 1);

    DebugMessageFS("Last Line Difference", ((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine));
    DebugMessageFS("Dt Compensate Value", (((SDWORD)ulTargetLastLine - (SDWORD)ulCurrentLastLine) * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVTotal * g_stMDomainInputData.usHTotal / g_stMDomainOutputData.usHTotal) >> 1);

    DebugMessageFS("Compensated Dt", ulCompsIVS2DVSpixel);

#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        ucEOshift = 1;

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
        if(ScalerFmtCnvFBGetStatus() == _TRUE)
        {
            ucFBshift = 1;
        }
#endif
    }
#endif

    ulCompsIVS2DVSpixel = ulCompsIVS2DVSpixel >> ucEOshift;

    if((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P) &&
       (ScalerGetBit(P0_43_FS_DELAY_FINE_TUNE, _BIT1) == _BIT1) &&
       (ulCompsIVS2DVSpixel >= (((g_stMDomainInputData.usHTotal >> 1) + 64) >> ucEOshift)))
    {
        // Preserve 0.5 lines + 64 pixel in Fine Tune Byte
        PDATA_WORD(2) = (ulCompsIVS2DVSpixel - (((g_stMDomainInputData.usHTotal >> 1) + 64) >> ucEOshift)) / g_stMDomainInputData.usHTotal;
        PDATA_WORD(3) = (ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
        PDATA_WORD(4) = (ulCompsIVS2DVSpixel - (g_stMDomainInputData.usHTotal >> (1 + ucEOshift)) - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
        pData[10] = (ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << (4 + ucFBshift))) >> ucFBshift;
        pData[11] = (ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(4) << (4 + ucFBshift))) >> ucFBshift;
    }
    else
    {
        PDATA_WORD(2) = ulCompsIVS2DVSpixel / g_stMDomainInputData.usHTotal;
        PDATA_WORD(3) = ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) >> (4 + ucFBshift);
        PDATA_WORD(4) = 0x0000;
        pData[10] = (ulCompsIVS2DVSpixel - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << (4 + ucFBshift))) >> ucFBshift;
        pData[11] = 0x00;
    }

    //-------------------------------------------------
    // Apply updated Delay
    //-------------------------------------------------
    // IVS2DVS line delay, unit: line
    ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (pData[4] & 0x1F));
    ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, pData[5]);

    // IVS2DVS 16iclk1 delay, unit: 16 pixel
    PDATA_WORD(3) -= (PDATA_WORD(3) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK1(PDATA_WORD(3));

    // IVS2DVS 16iclk2 delay, unit: 16 pixel
    PDATA_WORD(4) -= (PDATA_WORD(4) >= 1) ? 1 : 0;
    SET_IVS2DVS_DELAY_16ICLK2(PDATA_WORD(4));

    // IVS2DVS iclk1 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0xF0, ((pData[10] & 0x0F) << 4));

    // IVS2DVS iclk2 delay, unit: 1 pixel
    ScalerSetBit(P0_3D_IV_DV_DELAY_CLK_FINE, ~0x0F, (pData[11] & 0x0F));
}

//--------------------------------------------------
// Description  : Set IVS2DVS Delay (line)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetIVS2DVSLineDelay(WORD usIVS2DVSDelay)
{
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
    if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
    {
        usIVS2DVSDelay = (usIVS2DVSDelay >> 1);
    }
#endif

    // IVS2DVS delay setting min=0x01
    if(usIVS2DVSDelay == 0)
    {
        usIVS2DVSDelay = 0x01;
    }

    ScalerSetByte(P0_3E_IVS2DVS_DLY_LINE_H, (HIBYTE(usIVS2DVSDelay) & 0x1F));
    ScalerSetByte(P0_40_IVS2DVS_DLY_LINE_L, LOBYTE(usIVS2DVSDelay));
}

//--------------------------------------------------
// Description  : IVS2DVS Delay Finetune
// Input Value  : Old IVS2DVS Delay/ New IVS2DVS Delay/ IVS2DVS Change limit
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFineTuneIVS2DVSDelay(WORD usOldIVS2DVSDelay, WORD usNewIVS2DVSDelay, WORD usIVS2DVSChgLimit)
{
    WORD usDVTotalFrameSync = 0;
    WORD usDVTotalFreeRun = 0;
    WORD usRemainIVS2DVSDelay = 0;
    BYTE ucTimeoutCounter = 255;
    bit bFreeRunEn = _FALSE;

    ScalerSetByte(P0_41_IVS2DVS_DLY_TUNE_ODD, 0x00);
    ScalerSetByte(P0_42_IVS2DVS_DLY_TUNE_EVEN, 0x00);

    if(ScalerVgipGetDigitalCaptureStatus() == _TRUE)
    {
        // Avoid (Current_IVStart + IVHeight) > IVToal + New_IVSDelay in digital capture
        PDATA_WORD(0) = (GET_INPUT_TIMING_VSTART() + ScalerVgipGetCaptureVStartPosition() + g_stMDomainInputData.usVHeight);
    }
    else
    {
        // Avoid (Current_IVSDelay + IVStart + IVHeight) > IVToal + New_IVSDelay in analog capture
        PDATA_WORD(0) = (ScalerVgipGetCaptureVDelay() + ScalerVgipGetCaptureVStartPosition() + g_stMDomainInputData.usVHeight);
    }

#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        bFreeRunEn = (PDATA_WORD(0) > ((DWORD)g_stMDomainInputData.usVHeight * 105 / 100)) ? (_TRUE) : (_FALSE);
    }
    else
#endif
    {
        bFreeRunEn = (PDATA_WORD(0) > g_stMDomainInputData.usVTotal) ? (_TRUE) : (_FALSE);
    }

    if(bFreeRunEn == _TRUE)
    {
        ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
        return;
    }

    // IVS2DVS delay from small to large
    if((usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay()) < (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()))
    {
        usRemainIVS2DVSDelay = (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()) - (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay());

        while(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
        {
            usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
            usOldIVS2DVSDelay += usIVS2DVSChgLimit;

            ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay);
            ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);

            if(ucTimeoutCounter == 0)
            {
                break;
            }

            ucTimeoutCounter--;
        }

        ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
    }
    else
    {
        // Get Frame Sync DVtotal
        ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
        ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
        GET_DVTOTAL_LASTLINE(usDVTotalFrameSync);

        // IVS2DVS  diff (D_line)
        usRemainIVS2DVSDelay = (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay()) - (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY());
        usRemainIVS2DVSDelay = (DWORD)usRemainIVS2DVSDelay * g_stMDomainOutputData.usVBackHeight / g_stMDomainInputData.usVHeight;

        // Select smaller between measure DVtotal & Calculate DVtotal
        PDATA_WORD(0) = (usDVTotalFrameSync < g_stMDomainOutputData.usVTotal) ? usDVTotalFrameSync : g_stMDomainOutputData.usVTotal;

        // Display front porch
        PDATA_WORD(1) = (PDATA_WORD(0) > (g_stMDomainOutputData.usVBackHeight + g_stMDomainOutputData.usVStart)) ? (PDATA_WORD(0) - (g_stMDomainOutputData.usVBackHeight + g_stMDomainOutputData.usVStart)) : 0;

        // (IVS2DVS diff >= Display front porch) or (transient DVtotal < DVtotal min)
        if((usRemainIVS2DVSDelay >= PDATA_WORD(1)) || ((PDATA_WORD(0) - usRemainIVS2DVSDelay) <= _PANEL_DV_TOTAL_MIN))
        {
            // IVS2DVS delay from large to small --> small_IVS2DVS + IVtotal - large_IVS2DVS
            usRemainIVS2DVSDelay = (usNewIVS2DVSDelay + GET_VGIP_INITIAL_VDELAY()) + g_stMDomainInputData.usVTotal - (usOldIVS2DVSDelay + ScalerVgipGetCaptureVDelay());

            while((usRemainIVS2DVSDelay > usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) < g_stMDomainInputData.usVTotal))
            {
                usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay);
                ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);

                if(ucTimeoutCounter == 0)
                {
                    break;
                }

                ucTimeoutCounter--;
            }

            // Back up Free run DVtotal
            GET_FREE_RUN_DVTOTAL(usDVTotalFreeRun);

            if((usRemainIVS2DVSDelay > usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) >= g_stMDomainInputData.usVTotal))
            {
                usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                usOldIVS2DVSDelay = usOldIVS2DVSDelay + usIVS2DVSChgLimit - g_stMDomainInputData.usVTotal;

                PDATA_WORD(7) = ((DWORD)g_stMDomainInputData.usVTotal + usIVS2DVSChgLimit) * usDVTotalFrameSync / g_stMDomainInputData.usVTotal + 1;

                ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, ~0x3FU, (pData[14] & 0x3F));
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_31_FIXED_DVTOTAL_LSB, pData[15]);

                ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);

                ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_INPUT_DATA_PATH());

                // Set to free-run mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                if(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
                {
                    usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                    usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                    ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                    ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay);
                    ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_NO_POLLING);

                    ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                    // Set to frame-sync mode
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);

                    while(usRemainIVS2DVSDelay > usIVS2DVSChgLimit)
                    {
                        usRemainIVS2DVSDelay -= usIVS2DVSChgLimit;
                        usOldIVS2DVSDelay += usIVS2DVSChgLimit;

                        ScalerMemorySetIVS2DVSLineDelay(usOldIVS2DVSDelay);
                        ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_POLLING);

                        if(ucTimeoutCounter == 0)
                        {
                            break;
                        }

                        ucTimeoutCounter--;
                    }

                    ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
                }
                else
                {
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                    ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
                    ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_NO_POLLING);

                    ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                    // Set to frame-sync mode
                    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
                }
            }
            else if((usRemainIVS2DVSDelay <= usIVS2DVSChgLimit) && ((usOldIVS2DVSDelay + usIVS2DVSChgLimit) >= g_stMDomainInputData.usVTotal))
            {
                PDATA_WORD(7) = ((DWORD)g_stMDomainInputData.usVTotal * 2 - usOldIVS2DVSDelay + usNewIVS2DVSDelay) * usDVTotalFrameSync / g_stMDomainInputData.usVTotal + 1;

                ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, ~0x3FU, (pData[14] & 0x3F));
                ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_31_FIXED_DVTOTAL_LSB, pData[15]);

                ScalerGlobalDDomainDBApply(_DB_APPLY_POLLING);

                ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_INPUT_DATA_PATH());

                // Set to free-run mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());

                ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
                ScalerGlobalIDomainDBApply(GET_MDOMAIN_INPUT_DATA_PATH(), _DB_APPLY_NO_POLLING);

                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, GET_MDOMAIN_INPUT_DATA_PATH());
                ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

                // Set to frame-sync mode
                ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, _BIT3);
            }
            else
            {
                ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
                DebugMessageFS("Error condition", 0);
            }

            ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB, ~0x3FU, ((HIBYTE(usDVTotalFreeRun)) & 0x3F));
            ScalerSetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_31_FIXED_DVTOTAL_LSB, (LOBYTE(usDVTotalFreeRun)));
        }
        else
        {
            ScalerMemorySetIVS2DVSLineDelay(usNewIVS2DVSDelay);
        }
    }

    DebugMessageFS("Timeout counter", ucTimeoutCounter);
}

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Description  : Memory Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryReset(void)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

    // DDR Reset

#endif
}

//--------------------------------------------------
// Description  : Memory Power Control
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerMemoryPowerControl(bit bOnOff)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

    // DDR Power Control
    ScalerDDR3PowerControl(bOnOff);

#endif

    if(bOnOff == _ON)
    {
#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
        ScalerFRCPowerOnInitial();
#endif
    }
}

//--------------------------------------------------
// Description  : M:N frame tracking
// Input Value  : En: enable / disable
// Output Value : None
//--------------------------------------------------
void ScalerMemorySetFrameTrackingEnable(bit bEn)
{
    // Enable/Disable M:N frame tracking function
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, ~_BIT7, (BYTE)bEn << 7);
}
#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set M:N frame tracking
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMemoryFrameTracking(void)
{
    BYTE ucM = 1;
    BYTE ucN = 1;

    if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, _BIT7) == _BIT7)
    {
        return;
    }

    // Measure DVtotal in frame sync mode
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

    // Wait IVS for get correct data
    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
    ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());

    PDATA_WORD(0) = ScalerMemoryGetMNRatio();

    ucM = (PDATA_WORD(0) >> 8) & 0xFF;
    ucN = PDATA_WORD(0) & 0xFF;

    // Read DVTotal result
    GET_DVTOTAL_LASTLINE(PDATA_WORD(1));

    // Set to read last line result
    ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, 0x00);

    // Read Last line result
    GET_DVTOTAL_LASTLINE(PDATA_WORD(0));
    PDATA_WORD(0) = (PDATA_WORD(0) << _D_DOMAIN_PATH);

    // Calulate Display total pixel: DHtotal * DVtotal + last line
    PDATA_DWORD(1) = (DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * PDATA_WORD(1) + (PDATA_WORD(0));

#if(_MN_FINE_TUNE_LASTLINE_SUPPORT == _OFF)
    // Fine tune MN frame sync last line
    if(((PDATA_DWORD(1) * ucM) % GET_MDOMAIN_OUTPUT_HTOTAL()) > ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 90 / 100))
    {
        // Free run DVtotal
        PDATA_WORD(1) = (PDATA_DWORD(1) * ucM) / GET_MDOMAIN_OUTPUT_HTOTAL() / ucN + 1;

        // Free run Last line
        PDATA_WORD(0) = ((PDATA_DWORD(1) * ucM) % GET_MDOMAIN_OUTPUT_HTOTAL()) / ucN;
    }
    else if(((PDATA_DWORD(1) * ucM) % GET_MDOMAIN_OUTPUT_HTOTAL()) < ((DWORD)GET_MDOMAIN_OUTPUT_HTOTAL() * 10 / 100))
    {
        // Free run DVtotal
        PDATA_WORD(1) = ((PDATA_DWORD(1) * ucM) - GET_MDOMAIN_OUTPUT_HTOTAL()) / GET_MDOMAIN_OUTPUT_HTOTAL() / ucN + 1;

        // Free run Last line
        PDATA_WORD(0) = (((PDATA_DWORD(1) * ucM) % GET_MDOMAIN_OUTPUT_HTOTAL()) + GET_MDOMAIN_OUTPUT_HTOTAL()) / ucN;
    }
    else
#endif // End of #if(_MN_FINE_TUNE_LASTLINE_SUPPORT == _OFF)
    {
        // Free run DVtotal
        PDATA_WORD(1) = PDATA_DWORD(1) * ucM / GET_MDOMAIN_OUTPUT_HTOTAL() / ucN;

        // Free run Last line
        PDATA_WORD(0) = GET_MDOMAIN_OUTPUT_HTOTAL();
    }

    if(PDATA_WORD(1) < (g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight))
    {
        DebugMessageFRC("FrameTrack-DVT-Error", PDATA_WORD(1));
        PDATA_WORD(1) = _PANEL_DV_TOTAL;
    }

    // Set DVTotal
    SET_FREE_RUN_DVTOTAL(PDATA_WORD(1));

    // Set Frame Sync Watch Dog
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(1) + 64) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(1) + 64));

    PDATA_WORD(2) = PDATA_WORD(0) - (PDATA_WORD(0) % _DHTOTAL_MULTIPLE);

    // Set Last line
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_32_FIXED_LAST_LINE_MSB);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(2) - 8) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(2) - 8));
#else
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (HIBYTE(PDATA_WORD(2) - 4) & 0x1F));
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, LOBYTE(PDATA_WORD(2) - 4));
#endif

    // Set M:N frame tracking function
    // Set ivs skipped, M = register value +1
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_26_M_FOR_MN_FRAME_RATE);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (ucM - 1));
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_27_N_FOR_MN_FRAME_RATE);
    ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (ucN - 1));
}

//--------------------------------------------------
// Description  : Get M:N ratio
// Input Value  : None
// Output Value : M << 8 | N
//--------------------------------------------------
WORD ScalerMemoryGetMNRatio(void)
{
    BYTE ucM = 1;
    BYTE ucN = 1;

    switch(GET_MEMORY_DVF_SELECT())
    {
        case _2_IVF:

            ucM = 1;
            ucN = 2;

            break;

        case _3_IVF:

            ucM = 1;
            ucN = 3;

            break;

        case _2_5_IVF:

            ucM = 2;
            ucN = 5;

            break;

        default:

            break;
    }

    return ((ucM << 8) | (ucN));
}

//--------------------------------------------------
// Description  : Transfer the Memory Size to Address
// Input Value  : ulTotalSize --> Total Memory size
// Output Value : Line Step Address or Block Step Address
//--------------------------------------------------
DWORD ScalerMemoryAddressConversion(DWORD ulTotalSize)
{
#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)

    return (((ulTotalSize & 0x000100) << 1) | ((ulTotalSize & 0xFFFE00) << 2) | LOBYTE(ulTotalSize));

#else

    // _1G_16BIT_DDR3 or ...
    return ulTotalSize;

#endif
}

//--------------------------------------------------
// Description  : Calculate the Line Step and Block Step
// Input Value  : usHorSize --> Horizontal size (unit : 64 bits)
//                usVerSize --> Vertical size
// Output Value : Line Step and Block Step
//--------------------------------------------------
void ScalerMemoryCalculateLineStepAndBlockStep(DWORD ulHorSize, WORD usVerSize, StructMemoryLineBlockStep *pstMemoryLineBlockStep)
{
    pstMemoryLineBlockStep->ulLineStep = ulHorSize;

    if((pstMemoryLineBlockStep->ulLineStep & 0x03) != 0)
    {
        pstMemoryLineBlockStep->ulLineStep += (4 - (pstMemoryLineBlockStep->ulLineStep & 0x03));
    }

#if((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_2PCS)
    // 1024column x 32bit = 512 x 64bit. (64bit : FRC access unit)
    PDATA_WORD(0) = pstMemoryLineBlockStep->ulLineStep / 512;  // Row, Bank
    PDATA_WORD(1) = pstMemoryLineBlockStep->ulLineStep % 512;  // Column
    pstMemoryLineBlockStep->ulLineStep = (((DWORD)PDATA_WORD(0) << 9) | PDATA_WORD(1));
#elif((_MEMORY_SIZE_CONFIG & _MEMORY_NUM_MASK) == _MEMORY_1PC)
    // 1024column x 16bit = 256 x 64bit (64bit : FRC access unit)
    PDATA_WORD(0) = pstMemoryLineBlockStep->ulLineStep / 256;  // Row, Bank
    PDATA_WORD(1) = pstMemoryLineBlockStep->ulLineStep % 256;  // Column
    pstMemoryLineBlockStep->ulLineStep = (((DWORD)PDATA_WORD(0) << 8) | PDATA_WORD(1));
#else
    pstMemoryLineBlockStep->ulLineStep = pstMemoryLineBlockStep->ulLineStep * 64 / _MEMORY_BUS_WIDTH;
#endif

    pstMemoryLineBlockStep->ulBlockStep = (DWORD)usVerSize * pstMemoryLineBlockStep->ulLineStep;

    pstMemoryLineBlockStep->ulLineStep = ScalerMemoryAddressConversion(pstMemoryLineBlockStep->ulLineStep);
    pstMemoryLineBlockStep->ulBlockStep = ScalerMemoryAddressConversion(pstMemoryLineBlockStep->ulBlockStep);
}
#endif


