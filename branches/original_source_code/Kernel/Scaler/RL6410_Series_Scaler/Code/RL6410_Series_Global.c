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
// ID Code      : RL6410_Series_Global.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __6193_SCALER_GLOBAL__

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
void ScalerGlobalPathWatchDog(EnumInputDataPath enumInputDataPath, bit bEnable);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
void ScalerGlobalSetDBSyncMode(void);
#endif

void ScalerGlobalIDDomainDBApply(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Enabel Global Watch Dog by Path
// Input Value  : enumInputDataPath --> input data path
//                bEnable -->_ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerGlobalPathWatchDog(EnumInputDataPath enumInputDataPath, bit bEnable)
{
    BYTE ucPathIndex = 0x00;
    WORD usOffset = 0x0000;

    if(bEnable == _ENABLE)
    {
        // Clear Display Vsync Timeout Flag
        ScalerSetBit(P0_0C_WATCH_DOG_CTRL0, ~_BIT0, _BIT0);

        if(GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER)
        {
            // Set Free Run DVTotal = WD-Triggering DVTotal + 1 to Prevent DVTotal Too Long
            ScalerGetDataPortByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0B_DISPLAY_VER_TOTAL_H, 2, pData, _AUTOINC);
            PDATA_WORD(0) += 1;

            ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_30_FIXED_DVTOTAL_MSB);
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, (pData[0] & 0x3F));
            ScalerSetByte(P0_2B_DISPLAY_FORMAT_DATA_PORT, pData[1]);
        }
    }

    // Enable M1 & S1 WD only for even/odd mode
    if(enumInputDataPath == _INPUT_PATH_ALL)
    {
        if(bEnable == _ENABLE)
        {
            enumInputDataPath = _INPUT_PATH_M1;
        }
    }
    else if(enumInputDataPath == _INPUT_PATH_M1_M2)
    {
        enumInputDataPath = _INPUT_PATH_M1;
    }
    else if(enumInputDataPath == _INPUT_PATH_S1_S2)
    {
        enumInputDataPath = _INPUT_PATH_S1;
    }

    for(ucPathIndex = _INPUT_PATH_M1; ucPathIndex < _INPUT_PATH_ALL; ucPathIndex = (ucPathIndex << 1))
    {
        if((enumInputDataPath & ucPathIndex) == ucPathIndex)
        {
            if(bEnable == _ENABLE)
            {
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)

                // Clear Buffer Status and Input HVsync error flag
                ScalerSetByte(usOffset + P0_02_STATUS0, 0xFF);

                // Internal IRQ Enable (Global)
                ScalerGlobalIRQControl(_ENABLE);

                // Enable Input HVsync error IRQ
                ScalerSetBit(usOffset + P0_04_IRQ_CTRL0, ~_BIT5, _BIT5);

                EX0 = 1;
#else
                // Disable WD First
                ScalerSetByte(usOffset + P0_0C_WATCH_DOG_CTRL0, 0x00);
                ScalerSetBit(usOffset + P16_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(usOffset + P16_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), 0x00);
                ScalerSetBit(usOffset + P16_1C_M1_MEASURE_DUMMY0, ~_BIT7, 0x00);

                // Clear flag
                ScalerSetByte(usOffset + P0_02_STATUS0, 0xFF);
                ScalerSetBit(usOffset + P16_16_MEAS_HS_VS_DELTA_IRQ, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
                ScalerSetByte(usOffset + P16_03_MEAS_ERROR_FLG0, 0xFF);

                // Enable Input H/V Error WD & WD Action
                ScalerSetBit(usOffset + P0_0C_WATCH_DOG_CTRL0, ~(_BIT7 | _BIT5 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT5 | _BIT2 | _BIT1));

                // Enable measure overrange WD
#if(_VGA_SUPPORT == _ON)
                if(ScalerFmtCnvGetSourceType(enumInputDataPath) != _FC_SOURCE_ADC)
#endif
                {
                    ScalerSetBit(usOffset + P16_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
                }

                // Enable Input H/Vsync overflow WD (analog)
                ScalerSetBit(usOffset + P16_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

                // Enable Input Vsync timeout WD
                ScalerSetBit(usOffset + P16_1C_M1_MEASURE_DUMMY0, ~_BIT7, _BIT7);
#endif
            }
            else
            {
#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_BACKLIGHT)
                // Disable Input HVsync error IRQ
                ScalerSetBit(usOffset + P0_04_IRQ_CTRL0, ~_BIT5, 0x00);
#else
                // Disable Input H/V Error WD & Enable Frame Sync WD & Input H/Vsync overflow WD
                ScalerSetByte(usOffset + P0_0C_WATCH_DOG_CTRL0, 0x00);
                ScalerSetBit(usOffset + P16_17_MEAS_HS_VS_DELTA_WD, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
                ScalerSetBit(usOffset + P16_18_MEAS_HS_VS_ERROR_WD, ~(_BIT5 | _BIT4), 0x00);
                ScalerSetBit(usOffset + P16_1C_M1_MEASURE_DUMMY0, ~_BIT7, 0x00);
#endif
            }
        }

        // Update page offset
        usOffset += 0x4000;
    }

    // Disable "WD disable overlay" in multi-display mode
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT7, 0x00);
    }
    else
    {
        ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT7, _BIT7);
    }
}

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
//--------------------------------------------------
// Description  : Set I and D domain double buffer sync mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGlobalSetDBSyncMode(void)
{
#if(_MULTI_DISPLAY_MAX > 0X01)
    if(GET_MDOMAIN_DISPLAY_MODE() != _DISPLAY_MODE_1P)
    {
        ScalerSetBit(P31_A2_I_DB_CTRL2, ~_BIT0, 0x00);
    }
    else
#endif
    {
        // Set DB main/sub sync mode
        if(ScalerGetBit(P31_A1_I_DB_CTRL1, _BIT3) == 0x00)
        {
            // I_main_sub_sync select sub reference main: M1 IVS in 4 path mode
            ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), _BIT2);
        }
        else
        {
            // I_main_sub_sync select main reference sub: S2 IEN stop in 4 path mode
            ScalerSetBit(P31_A2_I_DB_CTRL2, ~(_BIT2 | _BIT1), _BIT1);
        }

        ScalerSetBit(P31_A2_I_DB_CTRL2, ~_BIT0, _BIT0);
    }
}
#endif

//--------------------------------------------------
// Description  : Set I and D domain double buffer apply
//
// The actual I_DB-applied path will be determined
// by both selected path and display mode.
//
// * In 1P Mode:
//      I_DB apply on M1 & M2, regardless of selected path.
//
// * In PIP, PBP_LR and PBP_TB Mode:
//      I_DB apply on M1 & M2 as long as at least one of them is selected.
//      I_DB apply on S1 & S2 as long as at least one of them is selected.
//
// * In 4P Mode:
//      I_DB apply on each selected path.
//
// Input Value  : DB path select, DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerGlobalIDDomainDBApply(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply)
{
    StructDBDataPathGroup structDataPathGroupInfo;
    BYTE ucDBctrl = 0x00;
    WORD usFirstPathPage = 0x0000;
    WORD usSecondPathPage = 0x0000;
    BYTE ucGroupIndex = 0x00;
    BYTE ucDataPathIndex = 0x00;
    BYTE ucPathCount = 0x00;
    EnumInputDataPath enumDataPath = 0x00;
    memset(&structDataPathGroupInfo, 0, sizeof(StructDBDataPathGroup));

    ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT5, _BIT5);

    if(enumDBApply == _DB_APPLY_POLLING)
    {
#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if((ScalerRotationCheckStatus() == _TRUE) ||
           (GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER) ||
           ((GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) && (GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)))
#else
        if((GET_MEMORY_SELECT() == _FRAME_SYNC_LINE_BUFFER) ||
           ((GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) && (GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)))
#endif
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_START, enumSelectedDataPath);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            // Set I M1/M2 apply bit (M1/M2/S1/S2)
            ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
#else
            // Set I M1/M2 apply bit (M1/M2)
            ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
#endif
            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));

            // Wait D double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);
        }
        else
        {
            // Divide input data path into several groups (e.g. (M1_M2, S1_S2) or (M2, M3, M4))
            ScalerGlobalIDDomainDBGetDataPathGroup(enumSelectedDataPath, &structDataPathGroupInfo);

            // Clear pending I/D domain DB ready bit
            ScalerGlobalIDDomainDBClearReadyBit(enumSelectedDataPath);

            // Set DB buffer start address
            ScalerGlobalIDDomainDBSetBufferAddress(&structDataPathGroupInfo);

            for(ucGroupIndex = 0; ucGroupIndex < (structDataPathGroupInfo.ucGroupNum); ucGroupIndex++)
            {
                switch(structDataPathGroupInfo.penumGroup[ucGroupIndex])
                {
                    case _INPUT_PATH_M1:
                        usFirstPathPage = _REG_MAIN1_PAGE;
                        ucPathCount = 1;
                        ucDBctrl = _BIT3;
                        break;

                    case _INPUT_PATH_M2:
                        usFirstPathPage = _REG_MAIN2_PAGE;
                        ucPathCount = 1;
                        ucDBctrl = _BIT2;
                        break;

                    case _INPUT_PATH_S1:
                        usFirstPathPage = _REG_SUB1_PAGE;
                        ucPathCount = 1;
                        ucDBctrl = _BIT1;
                        break;

                    case _INPUT_PATH_S2:
                        usFirstPathPage = _REG_SUB2_PAGE;
                        ucPathCount = 1;
                        ucDBctrl = _BIT0;
                        break;

                    case _INPUT_PATH_M1_M2:
                        usFirstPathPage = _REG_MAIN1_PAGE;
                        ucPathCount = 2;
                        ucDBctrl = (_BIT3 | _BIT2);
                        break;

                    case _INPUT_PATH_S1_S2:
                        usFirstPathPage = _REG_SUB1_PAGE;
                        ucPathCount = 2;
                        ucDBctrl = (_BIT1 | _BIT0);
                        break;

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                    case _INPUT_PATH_ALL:
                        usFirstPathPage = _REG_MAIN1_PAGE;
                        ucPathCount = 4;
                        ucDBctrl = (_BIT3 | _BIT2 | _BIT1 | _BIT0);
                        break;
#endif

                    default:
                        usFirstPathPage = _REG_MAIN1_PAGE;
                        ucPathCount = 0;
                        ucDBctrl = 0x00;
                        break;
                }

                usSecondPathPage = (ucPathCount == 2) ? (usFirstPathPage + _REG_PAGE_OFFSET) : usFirstPathPage;

                // Wait Iden_start event
                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_START, structDataPathGroupInfo.penumGroup[ucGroupIndex]);
                ScalerTimerDelayXms(2);

                // Set I apply bit
                ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucDBctrl);

                // Get FRC cap current block num, and set to FRC display freeze block num
                pData[0] = (ScalerGetBit(P5_2A_CAP_M1_STATUS + usFirstPathPage, _BIT6) >> 3);
                ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2 + usFirstPathPage, ~_BIT3, pData[0]);
                if(ucPathCount == 2)
                {
                    ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2 + usSecondPathPage, ~_BIT3, pData[0]);
                }
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                else if(ucPathCount == 4)
                {
                    ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT3, pData[0]);
                    ScalerSetBit(P85_AE_DISP_S1_DISP_CTRL2, ~_BIT3, pData[0]);
                    ScalerSetBit(PC5_AE_DISP_S2_DISP_CTRL2, ~_BIT3, pData[0]);
                }
#endif

                // if input fast than display
                if(GET_MDOMAIN_FRC_STYLE(structDataPathGroupInfo.penumGroup[ucGroupIndex]) == _FRC_INPUT_FASTER)
                {
                    // Enable FRC cap block free
                    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usFirstPathPage, ~_BIT4, _BIT4);
                    if(ucPathCount == 2)
                    {
                        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usSecondPathPage, ~_BIT4, _BIT4);
                    }
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                    else if(ucPathCount == 4)
                    {
                        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT4, _BIT4);
                        ScalerSetBit(P85_27_CAP_S1_DDR_CTRL1, ~_BIT4, _BIT4);
                        ScalerSetBit(PC5_27_CAP_S2_DDR_CTRL1, ~_BIT4, _BIT4);
                    }
#endif
                }

                // Wait I double buffer
                ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_A0_I_DB_CTRL0, ucDBctrl, 0);

                // Enable FRC display freeze mode
                ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2 + usFirstPathPage, ~_BIT2, _BIT2);
                ScalerSetBit(P5_AD_DISP_STATUS + usFirstPathPage, ~_BIT4, _BIT4);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                if(ucPathCount == 2)
#else
                if((ucPathCount == 2) &&
                   ((usSecondPathPage == _REG_MAIN2_PAGE) || ((usSecondPathPage == _REG_SUB2_PAGE) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_TB))))
#endif
                {
                    ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2 + usSecondPathPage, ~_BIT2, _BIT2);
                    ScalerSetBit(P5_AD_DISP_STATUS + usSecondPathPage, ~_BIT4, _BIT4);
                }
                else if(ucPathCount == 4)
                {
                    ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT2, _BIT2);
                    ScalerSetBit(P85_AE_DISP_S1_DISP_CTRL2, ~_BIT2, _BIT2);
                    ScalerSetBit(PC5_AE_DISP_S2_DISP_CTRL2, ~_BIT2, _BIT2);
                    ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
                    ScalerSetBit(P85_AD_DISP_STATUS, ~_BIT4, _BIT4);
                    ScalerSetBit(PC5_AD_DISP_STATUS, ~_BIT4, _BIT4);
                }

                // Wait 2*IDEND at input fast case, wait 1*IDEND at input slow case
                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);

                // if input fast than display
                if(GET_MDOMAIN_FRC_STYLE(structDataPathGroupInfo.penumGroup[ucGroupIndex]) == _FRC_INPUT_FASTER)
                {
                    // Wait Iden_stop event
                    ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, structDataPathGroupInfo.penumGroup[ucGroupIndex]);

                    // Disable FRC cap block free
                    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usFirstPathPage, ~_BIT4, 0x00);
                    if(ucPathCount == 2)
                    {
                        ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usSecondPathPage, ~_BIT4, 0x00);
                    }
                    else if(ucPathCount == 4)
                    {
                        ScalerSetBit(P45_27_CAP_M2_DDR_CTRL1, ~_BIT4, 0x00);
                        ScalerSetBit(P85_27_CAP_S1_DDR_CTRL1, ~_BIT4, 0x00);
                        ScalerSetBit(PC5_27_CAP_S2_DDR_CTRL1, ~_BIT4, 0x00);
                    }
                }
            }

            // Set D apply bit
            ScalerSetBit(P31_B0_D_DB_CTRL0, ~_BIT6, _BIT6);

            // Wait D double buffer
            ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P31_B0_D_DB_CTRL0, _BIT6, 0);

            // Disable FRC display freeze mode
            ScalerSetBit(P5_AE_DISP_M1_DISP_CTRL2, ~_BIT2, 0x00);
            ScalerSetBit(P45_AE_DISP_M2_DISP_CTRL2, ~_BIT2, 0x00);
            ScalerSetBit(P85_AE_DISP_S1_DISP_CTRL2, ~_BIT2, 0x00);
            ScalerSetBit(PC5_AE_DISP_S2_DISP_CTRL2, ~_BIT2, 0x00);
            ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
            ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
            ScalerSetBit(P85_AD_DISP_STATUS, ~_BIT4, _BIT4);
            ScalerSetBit(PC5_AD_DISP_STATUS, ~_BIT4, _BIT4);
        }
    }
    else if(enumDBApply == _DB_APPLY_NO_POLLING)
    {
        switch(GET_MDOMAIN_DISPLAY_MODE())
        {
            case _DISPLAY_MODE_1P:
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
                ucDBctrl |= (_BIT3 | _BIT2 | _BIT1 | _BIT0);
#else
                ucDBctrl |= (_BIT3 | _BIT2);
#endif
                break;

            case _DISPLAY_MODE_PIP:
            case _DISPLAY_MODE_PBP_LR:
            case _DISPLAY_MODE_PBP_TB:
                if((enumSelectedDataPath & _INPUT_PATH_M1_M2) != 0x00)
                {
                    ucDBctrl |= (_BIT3 | _BIT2);
                }

                if((enumSelectedDataPath & _INPUT_PATH_S1_S2) != 0x00)
                {
                    ucDBctrl |= (_BIT1 | _BIT0);
                }
                break;

            case _DISPLAY_MODE_4P:
                for(ucDataPathIndex = 0; ucDataPathIndex < 4; ucDataPathIndex++)
                {
                    enumDataPath = ((BYTE)_BIT0 << ucDataPathIndex);

                    if((enumSelectedDataPath & enumDataPath) == enumDataPath)
                    {
                        ucDBctrl |= ((BYTE)_BIT3 >> ucDataPathIndex);
                    }
                }
                break;

            default:
                break;
        }

        // Set I apply bit
        ScalerSetBit(P31_A0_I_DB_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucDBctrl);

        // Set D apply bit
        ScalerSetBit(P31_B0_D_DB_CTRL0, ~(_BIT6), (_BIT6));
    }
}

