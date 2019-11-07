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
// ID Code      : ScalerFRC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __SCALER_FRC__

#include "ScalerFunctionInclude.h"
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _FRC_IVS2DVSDELAY_MARGIN                    (30)  // (IVStart + IDEN) period > (DVStart + DDEN) period
#if(_FREESYNC_SUPPORT == _ON)
#define _FRC_IVS2DVSDELAY_MARGIN_FREESYNC           (4)
#define _FRC_IVS2DVSDELAY_LINE_BUFFER_MARGIN        (4)
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
#if(_FRC_SUPPORT == _ON)
WORD g_usFRCPageSelect;
BYTE g_ucFRCPathCount = 1;
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
BYTE g_ucDispLatecnyRatio;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
DWORD ScalerFRCRegPageSelection(EnumInputDataPath enumInputPath);
void ScalerFRCPowerOnInitial(void);
void ScalerFRCEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath enumInputPath, bit bEn);
#endif

#if(_FRC_SUPPORT == _ON)
WORD ScalerFRCCalculatePreReadLine(WORD usFRCVerSize);
void ScalerFRCAdjustIVS2DVSDelay(WORD usFRCVerSize);
void ScalerFRCCompareIHFandDHF(WORD usVerSize);
WORD ScalerFRCSetOneFrameDVTotal(void);
void ScalerFRCSetPreRead(EnumInputDataPath enumInputPath, WORD usPreReadLine);
void ScalerFRCOneFrameCtrl(DWORD ulIHF, DWORD ulDHF);
void ScalerFRCWaitWriteFrameBufFinish(void);
BYTE ScalerFRCIVS2DVSDelayMargin(void);
#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
WORD ScalerFRCGetIVS2DVSDelayMax(WORD usFRCVerSize);
#endif
#endif

void ScalerFRCSetDDomainSourceSelect(EnumInputDataPath enumInputPath, EnumDDomainSourceSelect enumSourceSelect);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

#if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)
//--------------------------------------------------
// Description  : Select FRC Setting Path Address
// Input Value  : None
// Output Value : Path Address
//--------------------------------------------------
DWORD ScalerFRCRegPageSelection(EnumInputDataPath enumInputPath)
{
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIndex = 0x00;

    switch(enumInputPath)
    {
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M2:
        case _INPUT_PATH_S1:
        case _INPUT_PATH_S2:
            for(ucIndex = 0; ucIndex < 4; ++ucIndex)
            {
                if((enumInputPath & ((BYTE)_BIT0 << ucIndex)) == ((BYTE)_BIT0 << ucIndex))
                {
                    break;
                }
            }
            ucPathCount = 1;
            usPageSelect = ((DWORD)0x4000 * ucIndex);
            break;

        case _INPUT_PATH_S1_S2:
            ucPathCount = 2;
            usPageSelect = _REG_SUB1_PAGE;
            break;

        case _INPUT_PATH_ALL:
            ucPathCount = 4;
            usPageSelect = _REG_MAIN1_PAGE;
            break;

        default:
        case _INPUT_PATH_M1_M2:
            ucPathCount = 2;
            usPageSelect = _REG_MAIN1_PAGE;
            break;
    }

    return (((DWORD)usPageSelect << 8) | ucPathCount);
}

//--------------------------------------------------
// Description  : FRC Power on initial
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCPowerOnInitial(void)
{
    WORD usPageSelect = _REG_MAIN1_PAGE;
    BYTE ucPathIdx = 0x00;

    for(ucPathIdx = 0; ucPathIdx < 4; ucPathIdx++)
    {
        // Set Number
        ScalerSetByte(P5_A8_DISP_M1_READ_NUM_H + usPageSelect, 0x00);
        ScalerSetByte(P5_A9_DISP_M1_READ_NUM_L + usPageSelect, 0x01);

        // Set Length, Remain
        ScalerSetByte(P5_AA_DISP_M1_READ_LEN + usPageSelect, _FRC_ACCESS_READ_LENGTH);
        ScalerSetByte(P5_AB_DISP_M1_READ_REMAIN + usPageSelect, _FRC_ACCESS_READ_LENGTH);

        // Enable Display double buffer
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~_BIT4, _BIT4);

        usPageSelect += _REG_PAGE_OFFSET;
    }

    ScalerFRCEn(_FRC_ALL_ONOFF, _INPUT_PATH_ALL, _DISABLE);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    ScalerRotationSetFRCEn(_FRC_ALL_ONOFF, _DISABLE);
#endif
}

//--------------------------------------------------
// Description  : FRC function enable/disable
// Input Value  : ucSettingPath: path
// Input Value  : bEn: enable/disable
// Output Value : None
//--------------------------------------------------
void ScalerFRCEn(EnumFRCOnOff enumCapDispOnOff, EnumInputDataPath enumInputPath, bit bEn)
{
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIndex = 0x00;

    // Calculate Register Page Number
    PDATA_DWORD(0) = ScalerFRCRegPageSelection(enumInputPath);
    ucPathCount = (PDATA_DWORD(0) & 0xFF);
    usPageSelect = (PDATA_DWORD(0) >> 8);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if((bEn == _DISABLE) && (enumInputPath == _INPUT_PATH_ALL))
    {
        for(ucIndex = 0; ucIndex < 4; ++ucIndex)
        {
            // Set 4 Channel Mode disable
            ScalerSetBit(P5_43_CAP_M1_4CH_CTRL1 + usPageSelect, ~_BIT1, 0x00);
            ScalerSetBit(P5_DC_DISP_M1_4CH_CTRL1 + usPageSelect, ~_BIT1, 0x00);

            // Set 4 channel manual mode
            ScalerSetBit(P5_44_CAP_M1_4CH_CTRL2 + usPageSelect, ~_BIT7, 0x00);
            ScalerSetBit(P5_DD_DISP_M1_4CH_CTRL2 + usPageSelect, ~_BIT7, 0x00);

            // Enable FRC M1 Display double buffer
            ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~_BIT4, _BIT4);

            usPageSelect += _REG_PAGE_OFFSET;
        }

        if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0x00)
        {
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, _DISPLAY_PATH_ALL);
        }
    }
#endif

    for(ucIndex = 0; ucIndex < ucPathCount; ++ucIndex)
    {
        if(bEn == _DISABLE)
        {
            if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
            {
                // Wait _EVENT_IEN_STOP before FRC Capture Disable
                if((ScalerGetBit(P31_A0_I_DB_CTRL0, _BIT7) == 0x00) && (ScalerGetBit(P0_10_M1_VGIP_CTRL + usPageSelect, _BIT0) == _BIT0))
                {
                    if(enumInputPath == _INPUT_PATH_ALL)
                    {
                        switch(usPageSelect)
                        {
                            default:
                            case _REG_MAIN1_PAGE:
                                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M1);
                                break;

                            case _REG_MAIN2_PAGE:
                                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_M2);
                                break;

                            case _REG_SUB1_PAGE:
                                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_S1);
                                break;

                            case _REG_SUB2_PAGE:
                                ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, _INPUT_PATH_S2);
                                break;
                        }
                    }
                    else
                    {
                        ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, enumInputPath);
                    }
                }

                // Disable Capture Block
                ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT7), 0x00);
            }

            if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF)
            {
                // Disable Display Block
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT0), 0x00);
            }
        }
        else
        {
            if((enumCapDispOnOff & _FRC_CAPTURE_ONOFF) == _FRC_CAPTURE_ONOFF)
            {
                if(ScalerGetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, _BIT7) == 0x00)
                {
                    // Enable Capture Block
                    ScalerSetBit(P5_27_CAP_M1_DDR_CTRL1 + usPageSelect, ~(_BIT7), _BIT7);
                }
            }

            if((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) == _FRC_DISPLAY_ONOFF)
            {
                if(ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, _BIT0) == 0x00)
                {
                    // Enable Display block
                    ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT0), _BIT0);
                }
            }
        } // End of if(bEn == _DISABLE)

        // Enable Double buffer
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~(_BIT4), _BIT4);

        usPageSelect += _REG_PAGE_OFFSET;
    }

    if(((enumCapDispOnOff & _FRC_DISPLAY_ONOFF) != 0) && (ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0))
    {
        // Wait double buffer
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, enumInputPath);
    }
}
#endif // End of #if(_MEMORY_TYPE_CONFIG != _NO_MEMORY)

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Calculate FRC Pre-read Line
// Input Value  : usFRCVerSize --> FRC Outpur Vertical Size
// Output Value : None
//--------------------------------------------------
WORD ScalerFRCCalculatePreReadLine(WORD usFRCVerSize)
{
    // preread = den_start - _PRE_READ_MEMORY x VSU factor - 1
    // VSU >= 1
    usFRCVerSize = (((DWORD)g_stMDomainOutputData.usVHeight * 10) / usFRCVerSize) * _PRE_READ_MEMORY + 1;
    usFRCVerSize = ((usFRCVerSize % 10) ? (usFRCVerSize / 10 + 1) : (usFRCVerSize / 10));

    return ((g_stMDomainOutputData.usVStart > usFRCVerSize) ? ((g_stMDomainOutputData.usVStart - usFRCVerSize)) : (0));
}

//--------------------------------------------------
// Description  : Adjust IVS2DVS Delay for Aspect Ratio Function
// Input Value  : usFRCVerSize : FRC Veritcal Size
// Output Value : None
//--------------------------------------------------
void ScalerFRCAdjustIVS2DVSDelay(WORD usFRCVerSize)
{
    BYTE ucFBshift = 0;
    DWORD ulIVStoDVSPixels = 0;

    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        BYTE ucMargin = ScalerFRCIVS2DVSDelayMargin();
        WORD usPreReadLine = ScalerFRCCalculatePreReadLine(usFRCVerSize);

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
        WORD usDelayMax = ScalerFRCGetIVS2DVSDelayMax(usFRCVerSize);
#endif

        // Measure Input Active Region after I-double buffer apply
        ScalerMeasureSetInputRegionCount(GET_MDOMAIN_INPUT_DATA_PATH(), _ACTIVE_REGION_TYPE);
        g_ulInputActiveRegionBackUp = ScalerMeasureGetInputRegionCountResult(_WAIT);

        // IHFreq, unit: 0.01kHz
        // IHF = Measure_clk * (IHtotal * IVheight' + IHwidth) / (IHtotal * Active_count)
        // IHF = (Measure_clk * IHtotal * IVheight'/ (IHtotal * Active_count)) + (Measure_clk * (IHtotal - IHporch) / (IHtotal * Active_count))
        // IHF = (Measure_clk * IVheight'/ Active_count) + (Measure_clk / Active_count) - (Measure_clk * (IHtotal - IHwidth) / (IHtotal * Active_count))
        if(GET_V_SCALE_DOWN() == _TRUE)
        {
            PDATA_WORD(2) = (g_stMDomainInputData.usVHeight);
        }
        else
        {
            PDATA_WORD(2) = (g_stMDomainInputData.usVHeight - 1);
        }

        PDATA_WORD(3) = ((DWORD)_MEASURE_CLK * 10 * PDATA_WORD(2) / g_ulInputActiveRegionBackUp * 10) +
                        (((DWORD)_MEASURE_CLK * 10 * PDATA_WORD(2)) % g_ulInputActiveRegionBackUp * 10 / g_ulInputActiveRegionBackUp) +
                        ((DWORD)_MEASURE_CLK * 100 / g_ulInputActiveRegionBackUp) -
                        ((DWORD)_MEASURE_CLK * 10 * (g_stMDomainInputData.usHTotal - g_stMDomainInputData.usHWidth) / g_ulInputActiveRegionBackUp / g_stMDomainInputData.usHTotal * 10);

        // DHFreq, unit: 0.01kHz
        PDATA_WORD(2) = ((DWORD)GET_D_CLK_FREQ() * 100 / g_stMDomainOutputData.usHTotal);

        switch(GET_MEMORY_SELECT())
        {
            case _FRAME_SYNC_MEMORY:

                // IVS2DVS line skip disable
                ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT3, _BIT3);

                // Consider IDEN period and (DDEN + pre-read) period
                if(g_stMDomainInputData.usVHeight >= ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight - usPreReadLine) * PDATA_WORD(3) / PDATA_WORD(2)))
                {
                    // (IVStart + IDEN) Period
                    PDATA_WORD(0) = (g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight);

                    // (DVStart + DDEN) Period
                    PDATA_WORD(1) = ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * PDATA_WORD(3) / PDATA_WORD(2));
                }
                else
                {
                    // IVStart Period
                    PDATA_WORD(0) = g_stMDomainInputData.usVStart;

                    // FRC_Display pre-read Period
                    PDATA_WORD(1) = (DWORD)usPreReadLine * PDATA_WORD(3) / PDATA_WORD(2);
                }

                if(PDATA_WORD(0) > PDATA_WORD(1))
                {
                    PDATA_WORD(0) = PDATA_WORD(0) - PDATA_WORD(1) + ucMargin;
                }
                else
                {
                    PDATA_WORD(0) = ucMargin;
                }

                PDATA_WORD(1) = ((g_stMDomainInputData.usVStart + ucMargin) > ((DWORD)usPreReadLine * PDATA_WORD(3) / PDATA_WORD(2))) ? ((g_stMDomainInputData.usVStart + ucMargin) - ((DWORD)usPreReadLine * PDATA_WORD(3) / PDATA_WORD(2))) : 0;

                if(PDATA_WORD(1) > PDATA_WORD(0))
                {
                    PDATA_WORD(0) = PDATA_WORD(1);
                }

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
                PDATA_WORD(1) = ((DWORD)usDelayMax - PDATA_WORD(0)) * GET_DISP_LATENCY_RATIO() / 100;
                PDATA_WORD(0) += PDATA_WORD(1);
#endif

                break;

            case _FREE_RUN_MEMORY:

                PDATA_WORD(0) = (g_stMDomainInputData.usVTotal + g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight);
                PDATA_WORD(0) -= ((DWORD)(g_stMDomainOutputData.usVStart + g_stMDomainOutputData.usVHeight) * PDATA_WORD(3) / PDATA_WORD(2));

                if(PDATA_WORD(0) > 255)
                {
                    PDATA_WORD(0) = 0xFE - 32;
                }
                else
                {
                    PDATA_WORD(0) -= 32;
                }

                break;

            default:
            case _MN_FRAME_SYNC_MEMORY:

                PDATA_WORD(0) = 0x01;

                break;
        }

        if((PDATA_WORD(0) > 0xF00) || (PDATA_WORD(0) == 0))
        {
            PDATA_WORD(0) = 0x01;
        }
    }
    else
    {
        // Multi-P ??
        PDATA_WORD(0) = 0x01;
    }

    // Disable Frame Sync Fine Tune
    ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT1, 0x00);

    ulIVStoDVSPixels = (DWORD)PDATA_WORD(0) * g_stMDomainInputData.usHTotal;

    if(GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)
    {
        if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT3) == _BIT3)
        {
            // Convert DVline limit to IVline
            WORD usIVS2DVSChgLimit = ((DWORD)_PANEL_DV_LINE_CHG_LIMIT * g_stMDomainOutputData.usHTotal / GET_D_CLK_FREQ() * g_stMDomainInputData.usHFreq / 10) +
                                     ((DWORD)_PANEL_DV_LINE_CHG_LIMIT * g_stMDomainOutputData.usHTotal % GET_D_CLK_FREQ() * g_stMDomainInputData.usHFreq / 10 / GET_D_CLK_FREQ());

            // Get Old IVS2DVS + IVSdelay (I line)
            PDATA_WORD(0) = (ScalerMemoryGetIVS2DVSDelayPixel() / g_stMDomainInputData.usHTotal);

            ScalerMemoryFineTuneIVS2DVSDelay(PDATA_WORD(0), (ulIVStoDVSPixels / g_stMDomainInputData.usHTotal), usIVS2DVSChgLimit);
        }

        if(ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE)
        {
            ulIVStoDVSPixels = (ulIVStoDVSPixels >> 1);

#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
            if(ScalerFmtCnvFBGetStatus() == _TRUE)
            {
                ucFBshift = 1;
            }
#endif
        }

        PDATA_WORD(2) = ulIVStoDVSPixels / g_stMDomainInputData.usHTotal;
        PDATA_WORD(3) = (ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2))) >> (4 + ucFBshift);
        PDATA_WORD(4) = 0x0000;
        pData[10] = (ulIVStoDVSPixels - ((DWORD)g_stMDomainInputData.usHTotal * PDATA_WORD(2)) - (PDATA_WORD(3) << (4 + ucFBshift))) >> ucFBshift;
        pData[11] = 0x00;

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
    else
    {
        ScalerMemorySetIVS2DVSLineDelay((ulIVStoDVSPixels / g_stMDomainInputData.usHTotal));

        // Set Frame Sync Mode Delay Fine Tune = 0
        SET_IVS2DVS_DELAY_16ICLK1(0x0000);
        SET_IVS2DVS_DELAY_16ICLK2(0x0000);
    }
}

//--------------------------------------------------
// Description  : Compare which one of IHF and DHF is bigger, and see if they are too similar
// Input Value  : ucSettingPath --> Path
//                stFIFOSize    --> FIFO size
// Output Value : output is true when they are too similar
//--------------------------------------------------
void ScalerFRCCompareIHFandDHF(WORD usVerSize)
{
    WORD usPageSelect = 0x0000;
    WORD usPreRead = 0;
    BYTE ucIndex = 0x00;

    // Calculate Register Page Number
    usPageSelect = g_usFRCPageSelect;

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
    if(usPageSelect == 0x2000)
    {
        usPageSelect = 0x1B00;  // 0x2000 - 0x500 = 0x1B00
    }
#endif

    // Set Previous FRC Style
    SET_MDOMAIN_FRC_STYLE(GET_MDOMAIN_INPUT_DATA_PATH(), (bit)((ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, _BIT3) == _BIT3) ? (_FRC_INPUT_FASTER) : (_FRC_INPUT_SLOWER)));

    // Get Pre-read line
    usPreRead = ScalerFRCCalculatePreReadLine(usVerSize);
    usPreRead = (usPreRead == 0) ? (g_stMDomainOutputData.usVStart) : (g_stMDomainOutputData.usVStart - usPreRead);

    if(g_stMDomainOutputData.usVHeight > g_stMDomainInputData.usVHeight)
    {
        // IHF'
        PDATA_DWORD(1) = (DWORD)g_stMDomainInputData.usHFreq;
        // DHF'
        PDATA_DWORD(2) = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal * g_stMDomainInputData.usVHeight / g_stMDomainOutputData.usVHeight);
    }
    else
    {
        // IHF'
        PDATA_DWORD(1) = (DWORD)g_stMDomainInputData.usHFreq * g_stMDomainOutputData.usVHeight / g_stMDomainInputData.usVHeight;
        // DHF'
        PDATA_DWORD(2) = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal);
    }

    // IDEN Period = IVH / IHF
    PDATA_WORD(0) = ((DWORD)GET_INPUT_TIMING_VHEIGHT() * 100 / g_stMDomainInputData.usHFreq);

    // DDEN Period = (DVH + Pre-read line) / DHF
    PDATA_WORD(1) = ((DWORD)(g_stMDomainOutputData.usVHeight + usPreRead) * 100 / ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal));

    for(ucIndex = 0; ucIndex < g_ucFRCPathCount; ++ucIndex)
    {
        if(GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY)
        {
            // Set Input Slower Than Display
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~_BIT3, 0x00);
        }
        else
        {
            // Set FRC Style
            if(PDATA_WORD(1) < PDATA_WORD(0)) // If IDEN period = DDEN period, then set input faster.
            {
                // Set Input Slower Than Display
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~_BIT3, 0x00);
            }
            else
            {
                // Set Input Fast Than Display
                ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~_BIT3, _BIT3);

#if(_D_DOMAIN_PATH != _D_DOMAIN_4_PATH)
                if((GET_MDOMAIN_INPUT_DATA_PATH() == _INPUT_PATH_S1_S2) &&
                   ((GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PIP) || (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_PBP_LR)))
                {
                    // (This Register Is Only for S2)
                    ScalerSetBit(P5_29_CAP_M1_DDR_CTRL3 + usPageSelect, ~(_BIT7), _BIT7);
                }
#endif
            }
        }

        usPageSelect += _REG_PAGE_OFFSET;
    }

    usPageSelect = g_usFRCPageSelect;
    for(ucIndex = 0; ucIndex < g_ucFRCPathCount; ++ucIndex)
    {
        // Write in double buffer
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~_BIT4, _BIT4);
        usPageSelect += _REG_PAGE_OFFSET;
    }

    pData[8] = (PDATA_DWORD(1) > PDATA_DWORD(2)) ? (_BIT3) : (0x00);
    if((ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, _BIT3) ^ pData[8]) != 0)
    {
        DebugMessageFRC("Error1-input faster/slower mis-match: IDEN", PDATA_WORD(0));
        DebugMessageFRC("Error2-input faster/slower mis-match: DDEN", PDATA_WORD(1));
        DebugMessageFRC("Error3-input faster/slower mis-match: IHF\'", PDATA_DWORD(1));
        DebugMessageFRC("Error4-input faster/slower mis-match: DHF\'", PDATA_DWORD(2));
    }

    if((GET_MEMORY_SELECT() == _FRAME_SYNC_MEMORY) || (GET_MEMORY_SELECT() == _MN_FRAME_SYNC_MEMORY))
    {
        ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, GET_MDOMAIN_OUTPUT_DATA_PATH());

        // Set Frame sync when FRC
        ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
    }
    else if(GET_MEMORY_SELECT() == _FREE_RUN_MEMORY)
    {
        if(GET_MEMORY_FRAME_BUFFER() == _MEMORY_1_FRAME_BUFFER)
        {
            ScalerFRCOneFrameCtrl(PDATA_DWORD(0), PDATA_DWORD(1));
        }
        else
        {
            // Set Free Run when FRC
            ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
        }
    }
}

//-------------------------------------------------
// Description  : Calculate DVTotal for OneFrame FRC
// Input Value  : None
// Output Value : usDVTotal
//-------------------------------------------------
WORD ScalerFRCSetOneFrameDVTotal(void)
{
    DWORD ulFrameDiff = 0;
    DWORD ulActiveRegionDiff = 0;
    WORD usIHF = 0;
    WORD usDHF = 0;
    WORD usDVTotal = 0;

    if((DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDHF = (DWORD)g_usDVFreq * _PANEL_DV_TOTAL / 1000;
    }
    else
    {
        usDHF = (DWORD)g_usDVFreq * (DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 / 1000;
    }

    usIHF = (DWORD)g_stMDomainInputData.usVFreq * g_stMDomainInputData.usVTotal / 1000;
    ulFrameDiff = (DWORD)1000 * ((DWORD)1000 * g_stMDomainInputData.usVFreq - (DWORD)1000 * g_usDVFreq) / ((DWORD)g_stMDomainInputData.usVFreq * g_usDVFreq);
    ulActiveRegionDiff = (DWORD) 1000 * ((DWORD)g_stMDomainOutputData.usVHeight * usIHF - (DWORD)g_stMDomainInputData.usVHeight * usDHF) / ((DWORD)usIHF * usDHF);

    // If((Input frame ahead) < 0.8*(Conflict region)), Then DVT = DVH / ((Input Frame ahead)*0.8 + IVH/IHF) * (1/DVF).
    // Else if(DVH*1.66 < DVT), Then DVT = Panel_DVT.
    // Else DVT = DVH*1.66
    if((ulFrameDiff * 100 / ulActiveRegionDiff) < 125)
    {
        usDVTotal = (DWORD)1000 * g_stMDomainOutputData.usVHeight / ((ulFrameDiff * 100 / 125) + ((DWORD)1000 * g_stMDomainInputData.usVHeight / usIHF)) * 1000 / g_usDVFreq;
    }
    else if((DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000 < _PANEL_DV_TOTAL)
    {
        usDVTotal = _PANEL_DV_TOTAL;
    }
    else
    {
        usDVTotal = (DWORD)g_stMDomainOutputData.usVHeight * 1066 / 1000;
    }

    if(usDVTotal > _PANEL_DV_TOTAL_MAX)
    {
        usDVTotal = _PANEL_DV_TOTAL_MAX;
    }
    else if(usDVTotal < _PANEL_DV_TOTAL_MIN)
    {
        usDVTotal = _PANEL_DV_TOTAL_MIN;
    }

    return usDVTotal;
}

//-------------------------------------------------
// Description  : Set FRC Display Pre-Read Line
// Input Value  : enumInputDataPath : Input path
//                usPreReadLine : Pre-Read Line
// Output Value : None
//-------------------------------------------------
void ScalerFRCSetPreRead(EnumInputDataPath enumInputPath, WORD usPreReadLine)
{
    if((enumInputPath & _INPUT_PATH_M1) != 0)
    {
        ScalerSetByte(P5_A6_DISP_M1_PRRD_VST_H, HIBYTE(usPreReadLine));
        ScalerSetByte(P5_A7_DISP_M1_PRRD_VST_L, LOBYTE(usPreReadLine));
        ScalerSetBit(P5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    }

    if((enumInputPath & _INPUT_PATH_M2) != 0)
    {
        ScalerSetByte(P45_A6_DISP_M2_PRRD_VST_H, HIBYTE(usPreReadLine));
        ScalerSetByte(P45_A7_DISP_M2_PRRD_VST_L, LOBYTE(usPreReadLine));
        ScalerSetBit(P45_AD_DISP_STATUS, ~_BIT4, _BIT4);
    }

    if((enumInputPath & _INPUT_PATH_S1) != 0)
    {
        ScalerSetByte(P85_A6_DISP_S1_PRRD_VST_H, HIBYTE(usPreReadLine));
        ScalerSetByte(P85_A7_DISP_S1_PRRD_VST_L, LOBYTE(usPreReadLine));
        ScalerSetBit(P85_AD_DISP_STATUS, ~_BIT4, _BIT4);
    }

    if((enumInputPath & _INPUT_PATH_S2) != 0)
    {
        ScalerSetByte(PC5_A6_DISP_S2_PRRD_VST_H, HIBYTE(usPreReadLine));
        ScalerSetByte(PC5_A7_DISP_S2_PRRD_VST_L, LOBYTE(usPreReadLine));
        ScalerSetBit(PC5_AD_DISP_STATUS, ~_BIT4, _BIT4);
    }

    if(ScalerGetBit(P31_B0_D_DB_CTRL0, _BIT7) == 0)
    {
        // Wait double buffer
        ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_INPUT_DATA_PATH());
    }
}

//--------------------------------------------------
// Description  : Set OneFrame FRC
// Input Value  : IHF, DHF
// Output Value : None
//--------------------------------------------------
void ScalerFRCOneFrameCtrl(DWORD ulIHF, DWORD ulDHF)
{
    SWORD shMargin = 0;
    WORD usPreRead = 0;
    WORD usLeadingLine = 0;
    bit bAutoMode = _ENABLE; // 1:auto mode; 0:manual mode
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIndex = 0x00;
    WORD usLength = g_stMDomainInputData.usVHeight;

    // Calculate Register Page Number
    PDATA_DWORD(0) = ScalerFRCRegPageSelection(GET_MDOMAIN_INPUT_DATA_PATH());
    ucPathCount = pData[3];
    usPageSelect = (PDATA_DWORD(0) >> 8);

    /// 1. Only if meet the following check condition, Write data to Memory:
    /// (1) Input Faster :
    ///      1. When R-FIFO is working check:  (IHP' * Length) > (DHP' * (Remain + Line_Margin)) --> (DHF' * Length) > (IHF' * (Remain + LIne_Margin))
    ///      2. When R-FIFO is idle check:     [W-FIFO starts] before [R-FIFO starts + Margin]
    /// (2) Input Slower :
    ///      1. When R-FIFO is working:  ((IHP' !V DHP') * Length) < (DHP'* (Remain + LIne_Margin)) --> ((DHF' - IHF')* Length) < ((DHF' * (Remain + Line_Margin)))
    ///      2. When R-FIFO is idle: Porch > [(IHP' !V DHP') * Length ] / DHP'
    /// 2. Remain Value:
    /// (1) Input Faster :
    ///    if ( pre_read_trig | (pre_cnt > pre_read_margin) )
    ///       Remain = line_counter
    ///    else
    ///       Remain = 0
    /// (2) Input Slower :
    ///    if ( line_counter < (length-1) )
    ///       Remain = line_counter
    ///    else
    ///       Remain = 0

    // Input Faster Case
    if(ulIHF > ulDHF)
    {
        usPreRead = g_stMDomainOutputData.usVStart - _PRE_READ_MEMORY;

        // Assume IHF_M = 37.48KHz, if input faster, IHF_M set 38, else set 37.
        ulIHF = (ulIHF % 10) ? (ulIHF / 10 + 1) : (ulIHF / 10);

        /// Set Line Merge
        ///      Auto mode : margin to avoid frame tear, range from -2048 to 2047
        ///      Manual mode : decide whether write data to Memory or not
        shMargin = 0x02;

        // Input faster case : DHF * Length
        ulDHF = ulDHF * usLength / 10;
    }
    else
    {
        // Input Slower Case
        // forbidden lines (conflict region)
        usPreRead = ((DWORD)g_stMDomainOutputData.usVHeight * ulDHF / ulIHF - g_stMDomainOutputData.usVHeight);
        usPreRead = (usPreRead < 10) ? 10 : usPreRead;

        PDATA_WORD(0) = _PANEL_DV_TOTAL_MIN;
        // Input frame leading lines in display (Display Frame Ahead)(uint: display line)
        if(g_stMDomainInputData.usVFreq > _PANEL_MAX_FRAME_RATE)
        {
            usLeadingLine = (DWORD)(g_stMDomainInputData.usVFreq - g_usDVFreq) * PDATA_WORD(0) / g_stMDomainInputData.usVFreq;
        }
        else if(g_stMDomainInputData.usVFreq < _PANEL_MIN_FRAME_RATE)
        {
            usLeadingLine = (DWORD)(g_usDVFreq - g_stMDomainInputData.usVFreq) * PDATA_WORD(0) / g_stMDomainInputData.usVFreq;
        }

        if(usPreRead <= g_stMDomainOutputData.usVStart)
        {
            /// 1. Set OneFrameFRC control by Manual mode
            ///  --> Write data control by Manual mode:
            ///  * Only if meet the following check condition, Write data to Memory:
            ///      (1)Input Faster: Remain + Line-margin(CRE8, CRE9) < 0.
            ///      (2)Input Slower: Remain + Line-mergin(CRE8, CRE9) > 0.
            /// 2. Set Input Faster mode

            if((usPreRead * 15 / 10) < usLeadingLine)
            {
                if((usPreRead * 15 / 10) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0; // PRRD_Margin
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - usPreRead * 15 / 10;
                }
            }
            else if((usPreRead * 13 / 10) < usLeadingLine)
            {
                if((usLeadingLine - 1) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - (usLeadingLine - 1);
                }
            }
            else
            {
                if((usPreRead * 13 / 10) > g_stMDomainOutputData.usVStart)
                {
                    usPreRead = 0;
                }
                else
                {
                    usPreRead = g_stMDomainOutputData.usVStart - usPreRead * 13 / 10;
                }
            }

            ulIHF = (g_stMDomainInputData.usHFreq % 10) ? (g_stMDomainInputData.usHFreq / 10 + 1) : (g_stMDomainInputData.usHFreq / 10);
            shMargin = (SWORD)0 - (g_stMDomainOutputData.usVHeight - 1);

            // Input Slower Case : (DHF - IHF) * Length
            ulDHF = ulDHF * g_stMDomainInputData.usVHeight / 10;
            bAutoMode = _DISABLE;

            // Set Input Faster Mode
            ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1, ~_BIT3, _BIT3);
        }
        else
        {
            usPreRead = (DWORD)(PDATA_WORD(0) - g_stMDomainOutputData.usVHeight) * usLength / g_stMDomainOutputData.usVHeight - 3;
            shMargin = (usPreRead > 20) ? (usPreRead - 20) : 0;

            usPreRead = usLength;

            // Input Slower Case : (DHF - IHF) * Length
            ulDHF = (ulDHF - ulIHF) * usLength / 10;
            ulIHF = (DWORD)ulIHF / 10;
        }
    }

    // Set FRC M1/M2
    PDATA_WORD(0) = usPageSelect;
    for(ucIndex = 0; ucIndex < ucPathCount; ++ucIndex)
    {
        ScalerSetByte(P5_B1_DISP_M1_ONEF_DHF_H + usPageSelect, ((ulDHF >> 16) | ((BYTE)bAutoMode << 6) | (_BIT7)));
        ScalerSetByte(P5_B2_DISP_M1_ONEF_DHF_M + usPageSelect, (BYTE)(ulDHF >> 8));
        ScalerSetByte(P5_B3_DISP_M1_ONEF_DHF_L + usPageSelect, (BYTE)ulDHF);
        ScalerSetByte(P5_B4_DISP_M1_ONEF_IHF + usPageSelect, (BYTE)ulIHF);
        ScalerSetByte(P5_B5_DISP_M1_LINE_MAGN_L + usPageSelect, LOBYTE(shMargin));
        ScalerSetByte(P5_B6_DISP_M1_ONEF_MAGN_H + usPageSelect, (((HIBYTE(shMargin) << 4) & 0xF0) | (HIBYTE(usPreRead) & 0x0F)));
        ScalerSetByte(P5_B7_DISP_M1_ONEF_MAGN_L + usPageSelect, LOBYTE(usPreRead));

        ScalerSetByte(P45_B1_DISP_M2_ONEF_DHF_H + usPageSelect, ((ulDHF >> 16) | ((BYTE)bAutoMode << 6) | (_BIT7)));
        ScalerSetByte(P45_B2_DISP_M2_ONEF_DHF_M + usPageSelect, (BYTE)(ulDHF >> 8));
        ScalerSetByte(P45_B3_DISP_M2_ONEF_DHF_L + usPageSelect, (BYTE)ulDHF);
        ScalerSetByte(P45_B4_DISP_M2_ONEF_IHF + usPageSelect, (BYTE)ulIHF);
        ScalerSetByte(P45_B5_DISP_M2_LINE_MAGN_L + usPageSelect, LOBYTE(shMargin));
        ScalerSetByte(P45_B6_DISP_M2_ONEF_MAGN_H + usPageSelect, (((HIBYTE(shMargin) << 4) & 0xF0) | (HIBYTE(usPreRead) & 0x0F)));
        ScalerSetByte(P45_B7_DISP_M2_ONEF_MAGN_L + usPageSelect, LOBYTE(usPreRead));

        usPageSelect += _REG_PAGE_OFFSET;
    }

    usPageSelect = PDATA_WORD(0);
    for(ucIndex = 0; ucIndex < ucPathCount; ++ucIndex)
    {
        // Write in double buffer
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~(_BIT4), _BIT4);

        usPageSelect += _REG_PAGE_OFFSET;
    }

    // Disable Osd Overlay In Case of Garbage
    pData[0] = ScalerGetByte(P0_6C_OVERLAY_CTRL);
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, 0x00);

    // Set Frame sync
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

    ScalerTimerWaitForIDDomainEvent(_EVENT_DEN_STOP, GET_MDOMAIN_OUTPUT_DATA_PATH());

    // Set Free Run
    ScalerSetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~(_BIT7 | _BIT3 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

    // Enable Osd Overlay In Case of Garbage
    ScalerSetBit(P0_6C_OVERLAY_CTRL, ~_BIT0, (pData[0] & _BIT0));
}

//--------------------------------------------------
// Description  : Wait Capture Write Memory Block Finish
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFRCWaitWriteFrameBufFinish(void)
{
    WORD usPageSelect = 0x0000;

    if(GET_MEMORY_CONFIG() == _MEMORY_WORK_MODE)
    {
        // Calculate Register Page Number
        PDATA_DWORD(0) = ScalerFRCRegPageSelection(GET_MDOMAIN_INPUT_DATA_PATH());
        usPageSelect = (PDATA_DWORD(0) >> 8);

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
        if(ScalerRotationCheckStatus() == _TRUE)
        {
            usPageSelect = 0x1B00; // 0x2000 - 0x500 = 0x1B00
        }
#endif

        // Check Double Frame Buffer
        if((bit)(ScalerGetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, _BIT6)) == _TRUE)
        {
            // Get FRC Capture Block Index
            pData[0] = ScalerGetBit((P5_2A_CAP_M1_STATUS + usPageSelect), _BIT6);

            // Wait Write Data
            ScalerTimerPollingFlagProc(50, (P5_2A_CAP_M1_STATUS + usPageSelect), _BIT6, ((~pData[0]) & _BIT6));
            ScalerTimerPollingFlagProc(50, (P5_2A_CAP_M1_STATUS + usPageSelect), _BIT6, ((pData[0]) & _BIT6));

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
#if(_FORMAT_CONVERSION_SUPPORT == _ON)
            if((ScalerFmtCnvFtoPGetStatus(GET_MDOMAIN_INPUT_DATA_PATH()) == _TRUE) &&
               ((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)))
#else
            if((GET_ROT_TYPE() != _ROT_DISABLE) && (GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P))
#endif
            {
                ScalerTimerPollingFlagProc(50, (P5_2A_CAP_M1_STATUS + usPageSelect), _BIT6, ((~pData[0]) & _BIT6));
            }
#endif

            ScalerTimerWaitForIDDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
            ScalerTimerWaitForIDDomainEvent(_EVENT_IVS, GET_MDOMAIN_INPUT_DATA_PATH());
        }
    }
}

//--------------------------------------------------
// Description  : Calculate IVS2DVS delay margin
// Input Value  : N.A.
// Output Value : IVS2DVS delay margin
//--------------------------------------------------
BYTE ScalerFRCIVS2DVSDelayMargin(void)
{
#if(_FREESYNC_SUPPORT == _ON)
    if(GET_FREESYNC_ENABLED() == _TRUE)
    {
        // Margin need to consider Fifo margin, line buffer margin and setting margin
        // Fifo margin: FIFO size/ format/ IHwidth * 2
        pData[0] = ((DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() / g_stMDomainInputData.usHWidth);
        pData[0] += ((((DWORD)_M_DOMAMAIN_FIFO_BIT / GET_MEMORY_DATA_BIT() % g_stMDomainInputData.usHWidth) != 0x00) ? 1 : 0);

        pData[0] += (_FRC_IVS2DVSDELAY_LINE_BUFFER_MARGIN + _FRC_IVS2DVSDELAY_MARGIN_FREESYNC);
    }
    else
#endif
    {
        pData[0] = _FRC_IVS2DVSDELAY_MARGIN;
    }

    return pData[0];
}

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get IVS2DVSDelay Max Value in Frame Sync Mode
// Input Value  : usFRCVerSize : Input VHeight
// Output Value : IVS2DVSDelay Max Value
//--------------------------------------------------
WORD ScalerFRCGetIVS2DVSDelayMax(WORD usFRCVerSize)
{
    WORD usDHF = 0x00;
    WORD usIPeriod = 0x00;
    WORD usDStartPeriod = 0x00;

    if(ScalerMDomainMemorySelectConfirm() == _FRAME_SYNC_MEMORY)
    {
        // DHFreq
        usDHF = ((DWORD)GET_D_CLK_FREQ() * 10 / g_stMDomainOutputData.usHTotal);

        // (IVStart + IDEN) Period
        usIPeriod = (g_stMDomainInputData.usVStart + g_stMDomainInputData.usVHeight);

        // Pre-read Period
        usDStartPeriod = ((DWORD)ScalerFRCCalculatePreReadLine(usFRCVerSize) * g_stMDomainInputData.usHFreq / usDHF);

        return (usIPeriod - (usDStartPeriod + _FRC_IVS2DVSDELAY_MARGIN));
    }

    return 0;
}
#endif // End of #if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
#endif // End of #if(_FRC_SUPPORT == _ON)

//--------------------------------------------------
// Description  : D Domain Source Select
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerFRCSetDDomainSourceSelect(EnumInputDataPath enumInputPath, EnumDDomainSourceSelect enumSourceSelect)
{
    WORD usPageSelect = 0x0000;
    BYTE ucPathCount = 1;
    BYTE ucIndex = 0x00;

    // Calculate Register Page Number
    PDATA_DWORD(0) = ScalerFRCRegPageSelection(enumInputPath);
    ucPathCount = pData[3];
    usPageSelect = (PDATA_DWORD(0) >> 8);

    if(enumSourceSelect == _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE)
    {
        pData[0] = _BIT2;
    }
    else
    {
        pData[0] = 0x00;
    }

    for(ucIndex = 0; ucIndex < ucPathCount; ++ucIndex)
    {
        // Set Frame sync with line buffer mode
        ScalerSetBit(P5_AC_DISP_M1_DISP_CTRL1 + usPageSelect, ~(_BIT2 | _BIT1), pData[0]);

        // Enable Double buffer
        ScalerSetBit(P5_AD_DISP_STATUS + usPageSelect, ~(_BIT4), _BIT4);

        usPageSelect += _REG_PAGE_OFFSET;
    }
}

