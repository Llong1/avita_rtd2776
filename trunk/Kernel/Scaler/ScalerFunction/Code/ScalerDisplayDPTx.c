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
// ID Code      : ScalerDisplayDPTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DISPLAY_DP_TX__

#include "ScalerFunctionInclude.h"

#if(_PANEL_STYLE == _PANEL_DPTX)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
#define _DISPLAY_DP_TX1_TU_SIZE                          32
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
#define _DISPLAY_DP_TX2_TU_SIZE                          32
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
bit g_bDptxSscEn = 0;

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
StructDownStreamInfo g_stDisplayDPTx1Info;
StructDPTxLTInfo g_stDisplayDPTx1LTInfo;
StructTimingInfo g_stDisplayDPTx1TimingInfo;
StructDisplayDPTxInputInfo g_stDisplayDPTx1InputInfo;
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
StructDownStreamInfo g_stDisplayDPTx2Info;
StructDPTxLTInfo g_stDisplayDPTx2LTInfo;
StructTimingInfo g_stDisplayDPTx2TimingInfo;
StructDisplayDPTxInputInfo g_stDisplayDPTx2InputInfo;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
void ScalerDisplayDPTx1Initial(void);
bit ScalerDisplayDPTx1LinkConfig(void);
void ScalerDisplayDPTx1VideoStreamOutput(bit bOutput);
void ScalerDisplayDPTx1DisplayFormatSetting(void);
void ScalerDisplayDPTx1DisplayMSASetting(void);
void ScalerDisplayDPTx1LinkTraining(void);
void ScalerDisplayDPTx1TPInitialSet(void);
BYTE ScalerDisplayDPTx1TrainPattern1(void);
BYTE ScalerDisplayDPTx1TrainPattern2(void);
void ScalerDisplayDPTx1TrainPatternEnd(void);
bit ScalerDisplayDPTx1TP1Lane0Adjust(void);
bit ScalerDisplayDPTx1TP1Lane1Adjust(void);
bit ScalerDisplayDPTx1TP1Lane2Adjust(void);
bit ScalerDisplayDPTx1TP1Lane3Adjust(void);
void ScalerDisplayDPTx1TP2Lane0Adjust(void);
void ScalerDisplayDPTx1TP2Lane1Adjust(void);
void ScalerDisplayDPTx1TP2Lane2Adjust(void);
void ScalerDisplayDPTx1TP2Lane3Adjust(void);
void ScalerDisplayDPTx1LinkForceOutput(void);
void ScalerDisplayDPTx1SignalReset(void);
void ScalerDisplayDPTx1EnhanceFramingMode(bit bEnable);
bit ScalerDisplayDPTx1MeasureInputInfo(void);
void ScalerDisplayDPTx1MLPHYSet(void);
bit ScalerDisplayDPTx1NativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
bit ScalerDisplayDPTx1NativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
void ScalerDisplayDPTx2Initial(void);
bit ScalerDisplayDPTx2LinkConfig(void);
void ScalerDisplayDPTx2VideoStreamOutput(bit bOutput);
void ScalerDisplayDPTx2DisplayFormatSetting(void);
void ScalerDisplayDPTx2DisplayMSASetting(void);
void ScalerDisplayDPTx2LinkTraining(void);
void ScalerDisplayDPTx2TPInitialSet(void);
BYTE ScalerDisplayDPTx2TrainPattern1(void);
BYTE ScalerDisplayDPTx2TrainPattern2(void);
void ScalerDisplayDPTx2TrainPatternEnd(void);
bit ScalerDisplayDPTx2TP1Lane0Adjust(void);
bit ScalerDisplayDPTx2TP1Lane1Adjust(void);
bit ScalerDisplayDPTx2TP1Lane2Adjust(void);
bit ScalerDisplayDPTx2TP1Lane3Adjust(void);
void ScalerDisplayDPTx2TP2Lane0Adjust(void);
void ScalerDisplayDPTx2TP2Lane1Adjust(void);
void ScalerDisplayDPTx2TP2Lane2Adjust(void);
void ScalerDisplayDPTx2TP2Lane3Adjust(void);
void ScalerDisplayDPTx2LinkForceOutput(void);
void ScalerDisplayDPTx2SignalReset(void);
void ScalerDisplayDPTx2EnhanceFramingMode(bit bEnable);
bit ScalerDisplayDPTx2MeasureInputInfo(void);
void ScalerDisplayDPTx2MLPHYSet(void);
bit ScalerDisplayDPTx2NativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
bit ScalerDisplayDPTx2NativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx1Initial(void)
{
    ScalerDisplayDPTx1AuxInitial();

    ScalerDisplayDPTx1HpdInitial();

    // Enable DPTX1 Small FIFO ouput 10bits data for each lane of Analog PHY driver ciruit.
    ScalerSetBit(P9C_10_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

    // Enable Arbiter Stuffing and Framing
    ScalerSetBit(P9C_C9_ARBITER_CTRL, ~_BIT0, _BIT0);

    SET_DISPLAY_DP_TX1_INPUT_COLOR_DEPTH(_PANEL_DISP_BIT_MODE);
    SET_DISPLAY_DP_TX1_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
}

//--------------------------------------------------
// Description  : Dp Tx Read DPCD Rx Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx1LinkConfig(void)
{
    // Set Power Normal
    pData[0] = 0x01;
    if(ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x06, 0x00, 1, pData) == _FALSE)
    {
        return _FALSE;
    }

    ScalerTimerDelayXms(10);

    // Read Sink Power Status
    if(ScalerDisplayDPTx1NativeAuxRead(0x00, 0x06, 0x00, 1, pData) == _FALSE)
    {
        return _FALSE;
    }

    // Check if Power State is Normal
    if(pData[0] != 0x01)
    {
        return _FALSE;
    }

    // Read Sink Cabability
    if(ScalerDisplayDPTx1NativeAuxRead(0x00, 0x00, 0x00, 16, pData) == _FALSE)
    {
        return _FALSE;
    }

    // Get Dpcd Revision Number
    if((pData[0] != _DP_VERSION_1_0) && (pData[0] != _DP_VERSION_1_1) && (pData[0] != _DP_VERSION_1_2))
    {
        pData[0] = _DP_VERSION_1_1;
    }

    // Set Dpcd Revision Number
    SET_DISPLAY_DP_TX1_DPCD_REV(pData[0]);

    if(pData[0] == _DP_VERSION_1_2)
    {
        // Check TP3 support
        if((pData[2] & _BIT6) == _BIT6)
        {
            SET_DISPLAY_DP_TX1_TP3_SUPPORT();
        }
        else
        {
            CLR_DISPLAY_DP_TX1_TP3_SUPPORT();
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX1_TP3_SUPPORT();
    }

    if((pData[1] == _DP_LINK_RBR) || (pData[1] == _DP_LINK_HBR) || ((pData[0] == _DP_VERSION_1_2) && (pData[1] == _DP_LINK_HBR2)))
    {
        // Set Link Rate
        SET_DISPLAY_DP_TX1_MAX_LINK_RATE(pData[1]);
    }
    else
    {
        // Set the Slowest Link Rate
        SET_DISPLAY_DP_TX1_MAX_LINK_RATE(_DP_LINK_RBR);
    }

    // Set Lane Number
    SET_DISPLAY_DP_TX1_LANE_NUM((pData[2] & 0x1F));

    // Set Enhanceed Framing
    SET_DISPLAY_DP_TX1_ENHANCE_FRAMING((bit)(pData[2] & _BIT7));

    // Set Max Downspread
    SET_DISPLAY_DP_TX1_DOWN_SPREAD((bit)(pData[3] & _BIT0));

    // Set Framing Change for eDP
    SET_DISPLAY_DP_TX1_FRAMING_CHANGE_CAPABLE((bit)(pData[13] & _BIT1));

    // Set Alternate SR Capable for eDP
    SET_DISPLAY_DP_TX1_ALTERNATE_SR_CAPABLE((bit)(pData[13] & _BIT0));

    return _TRUE;
}

//--------------------------------------------------
// Description  : Handle Tx Output stream
// Input Value  : DP Tx Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx1VideoStreamOutput(bit bOutput)
{
    if(bOutput == _ENABLE)
    {
#if(_DISPLAY_DP_TX_FB_MODE == _ON)
        // Set Front-Back Mode
        ScalerSetBit(P9C_D9_DPTX_TOP_CTL, ~(_BIT3 | _BIT2), (((BYTE)_PANEL_DPTX_FB_SWAP << 3) | _BIT2));
#else
#if(_PANEL_DPTX_LANE_NUMBER == _PANEL_DPTX_LANE_NUMBER_8)
        // Set Progressive Mode for TX1(MAC0)
        ScalerSetBit(P9C_D9_DPTX_TOP_CTL, ~(_BIT3 | _BIT2), ((BYTE)_PANEL_DPTX_FB_SWAP << 3));
#else
        // Set Progressive Mode for TX1(MAC0)
        ScalerSetBit(P9C_D9_DPTX_TOP_CTL, ~(_BIT3 | _BIT2), 0x00);
#endif
#endif

        ScalerDisplayDPTx1MeasureInputInfo();

        PDATA_DWORD(0) = 0;
        PDATA_DWORD(1) = 0x8000;
        PDATA_DWORD(2) = 0;

        // Mvid = Stream clk x Nvid / Link clk
        PDATA_DWORD(0) = ((DWORD)GET_D_CLK_FREQ() / _PANEL_DPTX_DCLK_DIV / 100) * PDATA_DWORD(1);
        PDATA_DWORD(0) /= ((GET_DISPLAY_DP_TX_SSCG_CONFIG() == _TRUE) ? ((DWORD)270 * GET_DISPLAY_DP_TX1_LINK_RATE() * 9975 / 10000) : ((DWORD)270 * GET_DISPLAY_DP_TX1_LINK_RATE()));

        // Debounce 10 times
        pData[12] = 0x0A;

        do
        {
            // Select HW mode for Mvid
            ScalerSetBit(P9C_A8_MN_VID_AUTO_EN_1, ~_BIT7, _BIT7);

            ScalerTimerDelayXms(2);

            // Select HW mode for Mvid
            ScalerSetBit(P9C_A8_MN_VID_AUTO_EN_1, ~_BIT7, 0x00);

            // Get Mvid From HW Mode
            PDATA_DWORD(2) = (((DWORD)ScalerGetByte(P9C_AF_MVID_AUTO_H) << 16) | ((DWORD)ScalerGetByte(P9C_B0_MVID_AUTO_M) << 8) | ScalerGetByte(P9C_B1_MVID_AUTO_L));

            // For RLE0779A/RL6449A disable auto Mvid is zero
            if(PDATA_DWORD(2) == 0)
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                ScalerSetByte(P9C_A9_MN_M_VID_H, pData[1]);
                ScalerSetByte(P9C_AA_MN_M_VID_M, pData[2]);
                ScalerSetByte(P9C_AB_MN_M_VID_L, pData[3]);

                break;
            }

            if(abs(PDATA_DWORD(0) - PDATA_DWORD(2)) < (PDATA_DWORD(0) >> 1))
            {
                // Set Mvid for HW mode
                ScalerSetByte(P9C_A9_MN_M_VID_H, pData[9]);
                ScalerSetByte(P9C_AA_MN_M_VID_M, pData[10]);
                ScalerSetByte(P9C_AB_MN_M_VID_L, pData[11]);

                break;
            }

            pData[12]--;

            if(pData[12] == 0x00)
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                ScalerSetByte(P9C_A9_MN_M_VID_H, pData[1]);
                ScalerSetByte(P9C_AA_MN_M_VID_M, pData[2]);
                ScalerSetByte(P9C_AB_MN_M_VID_L, pData[3]);
            }
        }
        while(pData[12] != 0);

        // Set Nvid for FW mode
        ScalerSetByte(P9C_AC_MN_N_VID_H, pData[5]);
        ScalerSetByte(P9C_AD_MN_N_VID_M, pData[6]);
        ScalerSetByte(P9C_AE_MN_N_VID_L, pData[7]);

        // Set Mvid DB Direct Effective
        ScalerSetBit(P9C_B4_MSA_CTRL, ~_BIT6, 0x00);

        // Set Mvid DB for FW mode
        ScalerSetBit(P9C_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6), _BIT6);

        // For Mvid Auto New Mode, M/N mode Measure and Generate are Independant.
        // SET_DISPLAY_DP_TX1_MVID_FW_MODE -> FW Manually Set Mvid/Nvid
        SET_DISPLAY_DP_TX1_MVID_FW_MODE();

        // MSA fill
        ScalerDisplayDPTx1DisplayMSASetting();

        // DP Tx TU Setting
        ScalerDisplayDPTx1DisplayFormatSetting();

        // Clear FIFO Status
        ScalerSetByte(P9C_A4_PG_FIFO_CTRL, 0xFF);

        // Main Link Switch to VIDEO pattern
        ScalerSetBit(P9C_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

        // Double buffer only by Vsync
        ScalerSetBit(P9C_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Main Link Switch to IDLE pattern
        ScalerSetBit(P9C_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Double buffer only by Vsync
        ScalerSetBit(P9C_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);
    }
}

//--------------------------------------------------
// Description  : DP Tx Arbiter
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1DisplayFormatSetting(void)
{
    // Disable HW Auto Calculate H Delay
    ScalerSetBit(P9C_D3_LFIFO_WL_SET, ~_BIT7, 0x00);

    // Pixel Generation Block Reset
    ScalerSetBit(P9C_A1_DP_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(P9C_A1_DP_RESET_CTRL, ~_BIT7, 0x00);

    // Get Bit Per Chrome
    switch(GET_DISPLAY_DP_TX1_INPUT_COLOR_DEPTH())
    {
        case _PANEL_DISP_18_BIT:
            pData[0] = 6;
            break;

        case _PANEL_DISP_24_BIT:
            pData[0] = 8;
            break;

        case _PANEL_DISP_30_BIT:
            pData[0] = 10;
            break;

        case _PANEL_DISP_36_BIT:
            pData[0] = 12;
            break;

        case _PANEL_DISP_48_BIT:
            pData[0] = 16;
            break;

        default:

            pData[0] = 8;
            break;
    }

    // Calculate Vaild Symbol in TU
    // Average TU = TU Size x (Stream_Clk x Byte of 1 pixel / Lane Number) / Link Rate
    PDATA_WORD(1) = ((GET_DISPLAY_DP_TX_SSCG_CONFIG() == _TRUE) ? ((DWORD)270 * GET_DISPLAY_DP_TX1_LINK_RATE() * 9975 / 10000) : ((DWORD)270 * GET_DISPLAY_DP_TX1_LINK_RATE()));
    PDATA_WORD(1) = ((DWORD)_DISPLAY_DP_TX1_TU_SIZE * (((DWORD)GET_D_CLK_FREQ() / _PANEL_DPTX_DCLK_DIV / 100 * 3 * pData[0]) / GET_DISPLAY_DP_TX1_LANE_NUM())) / (PDATA_WORD(1));

    ScalerSetByte(P9C_CC_TU_SIZE, _DISPLAY_DP_TX1_TU_SIZE);
    ScalerSetByte(P9C_CD_TU_DATA_SIZE0, (PDATA_WORD(1) >> 3));
    ScalerSetByte(P9C_CE_TU_DATA_SIZE1, (PDATA_WORD(1) & 0x07));

    PDATA_WORD(1) = ((DWORD)g_stDisplayDPTx1TimingInfo.usHWidth * pData[0] * 3) / (GET_DISPLAY_DP_TX1_LANE_NUM() * 8);
    PDATA_WORD(1) += ((bit)(((DWORD)g_stDisplayDPTx1TimingInfo.usHWidth * pData[0] * 3) % (GET_DISPLAY_DP_TX1_LANE_NUM() * 8)) ? 1 : 0);

    ScalerSetByte(P9C_CA_V_DATA_PER_LINE0, pData[2]);
    ScalerSetByte(P9C_CB_V_DATA_PER_LINE1, pData[3]);

    // Enable HW Auto Calculate H Delay
    ScalerSetBit(P9C_D3_LFIFO_WL_SET, ~_BIT7, _BIT7);

    ScalerSetByte(P9C_D4_ARBITER_SEC_END_CNT_HB, 0x00);
    ScalerSetByte(P9C_D5_ARBITER_SEC_END_CNT_LB, 0x47);
}

//--------------------------------------------------
// Description  : DP Tx MSA Generation
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1DisplayMSASetting(void)
{
    // Reset MSA Generation Block and SEC Block
    ScalerSetBit(P9C_A1_DP_RESET_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(P9C_A1_DP_RESET_CTRL, ~_BIT6, 0x00);

    // Set Htotal
    ScalerSetByte(P9C_B7_MN_STRM_ATTR_HTT_M, HIBYTE(g_stDisplayDPTx1TimingInfo.usHTotal));
    ScalerSetByte(P9C_B8_MN_STRM_ATTR_HTT_L, LOBYTE(g_stDisplayDPTx1TimingInfo.usHTotal));

    // Set Hstart
    ScalerSetByte(P9C_B9_MN_STRM_ATTR_HST_M, HIBYTE(g_stDisplayDPTx1TimingInfo.usHStart));
    ScalerSetByte(P9C_BA_MN_STRM_ATTR_HST_L, LOBYTE(g_stDisplayDPTx1TimingInfo.usHStart));

    // Set Hwidth
    ScalerSetByte(P9C_BB_MN_STRM_ATTR_HWD_M, HIBYTE(g_stDisplayDPTx1TimingInfo.usHWidth));
    ScalerSetByte(P9C_BC_MN_STRM_ATTR_HWD_L, LOBYTE(g_stDisplayDPTx1TimingInfo.usHWidth));

    // Set Hsyc
    ScalerSetByte(P9C_BD_MN_STRM_ATTR_HSW_M, HIBYTE(g_stDisplayDPTx1TimingInfo.usHSWidth));
    ScalerSetByte(P9C_BE_MN_STRM_ATTR_HSW_L, LOBYTE(g_stDisplayDPTx1TimingInfo.usHSWidth));

    // Set Vtotal
    ScalerSetByte(P9C_BF_MN_STRM_ATTR_VTTE_M, HIBYTE(g_stDisplayDPTx1TimingInfo.usVTotal));
    ScalerSetByte(P9C_C0_MN_STRM_ATTR_VTTE_L, LOBYTE(g_stDisplayDPTx1TimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(P9C_C1_MN_STRM_ATTR_VST_M, HIBYTE(g_stDisplayDPTx1TimingInfo.usVStart));
    ScalerSetByte(P9C_C2_MN_STRM_ATTR_VST_L, LOBYTE(g_stDisplayDPTx1TimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(P9C_C3_MN_STRM_ATTR_VHT_M, HIBYTE(g_stDisplayDPTx1TimingInfo.usVHeight));
    ScalerSetByte(P9C_C4_MN_STRM_ATTR_VHT_L, LOBYTE(g_stDisplayDPTx1TimingInfo.usVHeight));

    // Set Vsync
    ScalerSetByte(P9C_C5_MN_STRM_ATTR_VSW_M, HIBYTE(g_stDisplayDPTx1TimingInfo.usVSWidth));
    ScalerSetByte(P9C_C6_MN_STRM_ATTR_VSW_L, LOBYTE(g_stDisplayDPTx1TimingInfo.usVSWidth));

    // Set Color Space
    ScalerSetBit(P9C_B5_MSA_MISC0, ~(_BIT2 | _BIT1), (GET_DISPLAY_DP_TX1_INPUT_COLOR_SPACE() << 1));

    // Set Color Depth
    ScalerSetBit(P9C_B5_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5), (GET_DISPLAY_DP_TX1_INPUT_COLOR_DEPTH() << 5));

    // Set MISC1
    ScalerSetByte(P9C_B6_MN_STRM_ATTR_MISC1, 0x00);

    // MSA_DB = 1 and Bouble Buffer at V Blanking
    ScalerSetBit(P9C_B4_MSA_CTRL, ~(_BIT7 | _BIT6), _BIT7);
}

//--------------------------------------------------
// Description  : DP Tx Link Training
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1LinkTraining(void)
{
    if(GET_DISPLAY_DP_TX1_LINK_CONFIG() == _TRUE)
    {
        ScalerDisplayDPTx1TPInitialSet();

        while((GET_DISPLAY_DP_TX1_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_PASS) && (GET_DISPLAY_DP_TX1_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_FAIL))
        {
            switch(GET_DISPLAY_DP_TX1_LT_STATE())
            {
                case _DISPLAY_DP_TX_TRAINING_PATTERN1:

                    SET_DISPLAY_DP_TX1_LT_RESULT(ScalerDisplayDPTx1TrainPattern1());

                    // CR OK
                    if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS)
                    {
                        SET_DISPLAY_DP_TX1_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN2);
                    }
                    else if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL) // Can not Adjust voltage swing
                    {
                        SET_DISPLAY_DP_TX1_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DISPLAY_DP_TX_TRAINING_PATTERN2:

                    SET_DISPLAY_DP_TX1_LT_RESULT(ScalerDisplayDPTx1TrainPattern2());

                    if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS)
                    {
                        SET_DISPLAY_DP_TX1_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }
                    else if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL)
                    {
                        SET_DISPLAY_DP_TX1_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DISPLAY_DP_TX_TRAINING_PATTERN_END:

                    if(GET_DISPLAY_DP_TX1_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS)
                    {
                        SET_DISPLAY_DP_TX1_LT_RESULT(_DISPLAY_DP_TX_TRAINING_FAIL);
                    }
                    else
                    {
                        SET_DISPLAY_DP_TX1_LT_RESULT(_DISPLAY_DP_TX_TRAINING_PASS);
                    }

                    ScalerDisplayDPTx1TrainPatternEnd();

                    break;

                default:

                    break;
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Inital Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1TPInitialSet(void)
{
    // Panel DPTx Power Sequence Check Point
    PCB_DPTX1_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_LINK_TRAINING);

    SET_DISPLAY_DP_TX1_LT_RESULT(_DISPLAY_DP_TX_TRAINING_NO_RESULT);
    SET_DISPLAY_DP_TX1_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN1);

    // Set Link Rate
    SET_DISPLAY_DP_TX1_LINK_RATE(_PANEL_DPTX_LINK_RATE);

    // Set Link Rate for DPCD table of the Sink
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x00, 1, &GET_DISPLAY_DP_TX1_MAX_LINK_RATE());

    // Set Link Rate
    ScalerDisplayDPTxSetLinkRate();

    if(GET_DISPLAY_DP_TX1_FRAMING_CHANGE_CAPABLE() == _TRUE)
    {
        // Set Link Count and Disable Enhance Framing for External DP Sink
        pData[0] = GET_DISPLAY_DP_TX1_LANE_NUM();
        ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x01, 1, pData);

        // Set Enhance Framing Mode for eDP
        pData[0] = ((BYTE)GET_DISPLAY_DP_TX1_FRAMING_CHANGE_CAPABLE() << 1);
        ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);

        ScalerDisplayDPTx1EnhanceFramingMode(_ENABLE);
    }
    else
    {
        // Set Link Count and Enhance Framing for DPCD table of the Sink
        pData[0] = ((BYTE)GET_DISPLAY_DP_TX1_ENHANCE_FRAMING() << 7) | GET_DISPLAY_DP_TX1_LANE_NUM();
        ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x01, 1, pData);

        ScalerDisplayDPTx1EnhanceFramingMode(GET_DISPLAY_DP_TX1_ENHANCE_FRAMING());
    }

    // Initialize Main Link Signal
    ScalerDisplayDPTx1SignalInitialSetting();

    ScalerDisplayDPTx1NativeAuxRead(0x00, 0x01, 0x07, 1, pData);

    // Set Down Spread for DPCD table of the Sink
    pData[0] = ((pData[0] & ~_BIT4) | ((BYTE)GET_DISPLAY_DP_TX_SSCG_CONFIG() << 4));
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x07, 1, pData);

    // Set DPTx Spread Spectrum
    ScalerDisplayDPTxSSCSet(GET_DISPLAY_DP_TX_SSCG_CONFIG());
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDisplayDPTx1TrainPattern1(void)
{
    // Start TP1 Process
    if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_NO_RESULT)
    {
        // Repeat Bist Pattern --> for Training Pattern
        ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Select TP1
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, _BIT5);

        pData[0] = (_DISPLAY_DP_TX_TP_1 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
        pData[1] = g_stDisplayDPTx1LTInfo.ucLane0Adjust;
        pData[2] = g_stDisplayDPTx1LTInfo.ucLane1Adjust;
        pData[3] = g_stDisplayDPTx1LTInfo.ucLane2Adjust;
        pData[4] = g_stDisplayDPTx1LTInfo.ucLane3Adjust;

        // Write DPCD 102h to Start TP1
        ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerDisplayDPTx1MLPHYSet();

        pData[0] = g_stDisplayDPTx1LTInfo.ucLane0Adjust;
        pData[1] = g_stDisplayDPTx1LTInfo.ucLane1Adjust;
        pData[2] = g_stDisplayDPTx1LTInfo.ucLane2Adjust;
        pData[3] = g_stDisplayDPTx1LTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h  (Voltage Swing and Pre-emphasis)
        ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x03, 4, pData);
    }

    // Delay 400us
    for(pData[0] = 0; pData[0] < 55; pData[0]++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Read Lane Status and Request Adjust Level
    ScalerDisplayDPTx1NativeAuxRead(0x00, 0x02, 0x02, 6, pData);
    g_stDisplayDPTx1LTInfo.ucLane01LTStatus = pData[0];
    g_stDisplayDPTx1LTInfo.ucLane23LTStatus = pData[1];
    g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 = pData[4];
    g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 = pData[5];

    if(((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX1_LANE3_CR_DONE() & GET_DISPLAY_DP_TX1_LANE2_CR_DONE() & GET_DISPLAY_DP_TX1_LANE1_CR_DONE() & GET_DISPLAY_DP_TX1_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX1_LANE1_CR_DONE() & GET_DISPLAY_DP_TX1_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX1_LANE0_CR_DONE() == _TRUE)))
    {
        return _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS;
    }

    switch(GET_DISPLAY_DP_TX1_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            if(ScalerDisplayDPTx1TP1Lane3Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDisplayDPTx1TP1Lane2Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDisplayDPTx1TP1Lane1Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDisplayDPTx1TP1Lane0Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_TWO_LANE:

            if(ScalerDisplayDPTx1TP1Lane1Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDisplayDPTx1TP1Lane0Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_ONE_LANE:
        default:

            if(ScalerDisplayDPTx1TP1Lane0Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;
    }

    return _DISPLAY_DP_TX_TRAINING_PATTERN1_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDisplayDPTx1TrainPattern2(void)
{
    // Start TP2 Process
    if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS)
    {
        // Repeat Bist Pattern --> for Training Pattern
        ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Disable De-Scambling
        ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, _BIT1);

        // Set TP2 Pattern Type
        pData[0] = ScalerDisplayDPTx1SetTp2PatternType() | _DISPLAY_DP_TX_SCRAMBLING_DISABLE;

        pData[1] = g_stDisplayDPTx1LTInfo.ucLane0Adjust;
        pData[2] = g_stDisplayDPTx1LTInfo.ucLane1Adjust;
        pData[3] = g_stDisplayDPTx1LTInfo.ucLane2Adjust;
        pData[4] = g_stDisplayDPTx1LTInfo.ucLane3Adjust;

        // Write DPCD 102h-107h to Start TP2
        ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerDisplayDPTx1MLPHYSet();

        pData[0] = g_stDisplayDPTx1LTInfo.ucLane0Adjust;
        pData[1] = g_stDisplayDPTx1LTInfo.ucLane1Adjust;
        pData[2] = g_stDisplayDPTx1LTInfo.ucLane2Adjust;
        pData[3] = g_stDisplayDPTx1LTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x03, 4, pData);
    }

    // Delay 400us
    for(pData[0] = 0; pData[0] < 55; pData[0]++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Read Lane Status and Request Adjust Level
    ScalerDisplayDPTx1NativeAuxRead(0x00, 0x02, 0x02, 6, pData);
    g_stDisplayDPTx1LTInfo.ucLane01LTStatus = pData[0];
    g_stDisplayDPTx1LTInfo.ucLane23LTStatus = pData[1];
    g_stDisplayDPTx1LTInfo.ucLaneAlignStatus = pData[2];
    g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 = pData[4];
    g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 = pData[5];

    // CDR unlock => Reduce bit rate and return to TP1
    if(((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX1_LANE3_CR_DONE() & GET_DISPLAY_DP_TX1_LANE2_CR_DONE() & GET_DISPLAY_DP_TX1_LANE1_CR_DONE() & GET_DISPLAY_DP_TX1_LANE0_CR_DONE()) != _TRUE)) ||
       ((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX1_LANE1_CR_DONE() & GET_DISPLAY_DP_TX1_LANE0_CR_DONE()) != _TRUE)) ||
       ((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX1_LANE0_CR_DONE() != _TRUE)))
    {
        CLR_DISPLAY_DP_TX1_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }

    if((((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX1_LANE3_EQ_DONE() & GET_DISPLAY_DP_TX1_LANE2_EQ_DONE() & GET_DISPLAY_DP_TX1_LANE1_EQ_DONE() & GET_DISPLAY_DP_TX1_LANE0_EQ_DONE()) == _TRUE)) ||
        ((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX1_LANE1_EQ_DONE() & GET_DISPLAY_DP_TX1_LANE0_EQ_DONE()) == _TRUE)) ||
        ((GET_DISPLAY_DP_TX1_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX1_LANE0_EQ_DONE() == _TRUE))) &&
       (GET_DISPLAY_DP_TX1_LANE_ALIGN_DONE() == _TRUE))
    {
        CLR_DISPLAY_DP_TX1_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS;
    }

    if(GET_DISPLAY_DP_TX1_TP2_CNT() == 5)
    {
        CLR_DISPLAY_DP_TX1_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }
    else
    {
        ADD_DISPLAY_DP_TX1_TP2_CNT();
    }

    switch(GET_DISPLAY_DP_TX1_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            ScalerDisplayDPTx1TP2Lane3Adjust();
            ScalerDisplayDPTx1TP2Lane2Adjust();
            ScalerDisplayDPTx1TP2Lane1Adjust();
            ScalerDisplayDPTx1TP2Lane0Adjust();
            break;

        case _DP_TWO_LANE:

            ScalerDisplayDPTx1TP2Lane1Adjust();
            ScalerDisplayDPTx1TP2Lane0Adjust();
            break;

        case _DP_ONE_LANE:
        default:

            ScalerDisplayDPTx1TP2Lane0Adjust();

            break;
    }

    return _DISPLAY_DP_TX_TRAINING_PATTERN2_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training Pattern End
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1TrainPatternEnd(void)
{
    // Write TRAINING_PATTERN_SET = 00
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);

    if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
    {
        if(GET_DISPLAY_DP_TX1_ALTERNATE_SR_CAPABLE() == _TRUE)
        {
            // Scambling Seed Select to 0xFFFE
            ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT4, 0x00);

            pData[0] = ((BYTE)GET_DISPLAY_DP_TX1_FRAMING_CHANGE_CAPABLE() << 1) | _BIT0;
            ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);
        }
        else
        {
            // Scambling Seed Select to 0xFFFF
            ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT4, _BIT4);
        }

        // Enable Scrambling
        ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, 0x00);

        // Enable BS replaced by SR
        ScalerSetBit(P9C_0D_DPTX_PHY_CTRL, ~_BIT4, _BIT4);

        // Main Link switch to IDLE Pattern
        ScalerDisplayDPTx1VideoStreamOutput(_DISABLE);

        // Panel DPTx Power Sequence Check Point
        PCB_DPTX1_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_IDLE_PATTERN);

        // Disable bist mode
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), 0x00);

        // Disable Bist Pattern --> for Video Data
        ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~_BIT7, 0x00);
    }
    else
    {
        ScalerDisplayDPTx1LanePowerOff();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx1TP1Lane0Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX1_LANE0_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE0_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX1_LANE0_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX1_LANE0_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX1_LANE0_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX1_LANE0_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx1TP1Lane1Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX1_LANE1_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE1_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX1_LANE1_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX1_LANE1_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX1_LANE1_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX1_LANE1_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx1TP1Lane2Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX1_LANE2_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE2_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX1_LANE2_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX1_LANE2_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX1_LANE2_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX1_LANE2_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx1TP1Lane3Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX1_LANE3_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE3_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX1_LANE3_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX1_LANE3_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX1_LANE3_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX1_LANE3_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1TP2Lane0Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX1_LANE0_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX1_LANE0_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX1_LANE0_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1TP2Lane1Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX1_LANE1_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX1_LANE1_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX1_LANE1_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1TP2Lane2Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX1_LANE2_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX1_LANE2_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX1_LANE2_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1TP2Lane3Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX1_LANE3_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX1_LANE3_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX1_LANE3_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link TSignal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1LinkForceOutput(void)
{
    ScalerDisplayDPTx1TPInitialSet();

    // Set Output Signal According to Request
    ScalerDisplayDPTx1MLPHYSet();

    // Training Pattern 1 For Link Training
    // Repeat Bist Pattern --> for Training Pattern
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Select TP1
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, _BIT5);

    pData[0] = (_DISPLAY_DP_TX_TP_1 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
    pData[1] = g_stDisplayDPTx1LTInfo.ucLane0Adjust;
    pData[2] = g_stDisplayDPTx1LTInfo.ucLane1Adjust;
    pData[3] = g_stDisplayDPTx1LTInfo.ucLane2Adjust;
    pData[4] = g_stDisplayDPTx1LTInfo.ucLane3Adjust;

    // Write DPCD 102h-107h to Start TP1
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 5, pData);

    // Delay 400us
    for(pData[0] = 0; pData[0] < 55; pData[0]++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Training Pattern 2 For Link Training
    // Repeat Bist Pattern --> for Training Pattern
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Disable De-Scambling
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, _BIT1);

    // Select TP2
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, 0x00);

    pData[0] = (_DISPLAY_DP_TX_TP_2 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
    pData[1] = g_stDisplayDPTx1LTInfo.ucLane0Adjust;
    pData[2] = g_stDisplayDPTx1LTInfo.ucLane1Adjust;
    pData[3] = g_stDisplayDPTx1LTInfo.ucLane2Adjust;
    pData[4] = g_stDisplayDPTx1LTInfo.ucLane3Adjust;

    // Write DPCD 102h-107h to Start TP2
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 5, pData);

    // Delay 400us
    for(pData[0] = 0; pData[0] < 55; pData[0]++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);

    if(GET_DISPLAY_DP_TX1_ALTERNATE_SR_CAPABLE() == _TRUE)
    {
        // Scambling Seed Select to 0xFFFE
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT4, 0x00);

        pData[0] = ((BYTE)GET_DISPLAY_DP_TX1_FRAMING_CHANGE_CAPABLE() << 1) | _BIT0;
        ScalerDisplayDPTx1NativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);
    }
    else
    {
        // Scambling Seed Select to 0xFFFF
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT4, _BIT4);
    }

    // Enable Scambling
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, 0x00);

    // Enable BS replaced by SR
    ScalerSetBit(P9C_0D_DPTX_PHY_CTRL, ~_BIT4, _BIT4);

    // Main Link switch to IDLE Pattern
    ScalerDisplayDPTx1VideoStreamOutput(_DISABLE);

    // Disable bist mode
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), 0x00);

    // Disable Bist Pattern --> for Video Data
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1SignalReset(void)
{
    // Set Voltage Swing and pre-emphasis Variable to level 0
    CLR_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT();

    SET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();

    // Clear TP2 Count
    CLR_DISPLAY_DP_TX1_TP2_CNT();

    // Set Output Signal According to Request
    ScalerDisplayDPTx1MLPHYSet();
}

//--------------------------------------------------
// Description  : Handle Enhance Framing
// Input Value  : _ENABLE of _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx1EnhanceFramingMode(bit bEnable)
{
    // Disable Digital PHY Enhancement
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT3, 0x00);

    // Enable Enhancement
    ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~_BIT2, ((BYTE)bEnable << 2));
}

//--------------------------------------------------
// Description  : Measure function for DPTX SST D0
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDisplayDPTx1MeasureInputInfo(void)
{
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 2, &pData[0], _NON_AUTOINC);

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 3, &pData[3], _NON_AUTOINC);

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 2, &pData[6], _NON_AUTOINC);

    // Htotal
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        g_stDisplayDPTx1TimingInfo.usHTotal = ((PDATA_WORD(0) & 0x1FFF) + 8) / _PANEL_DPTX_DCLK_DIV;
    }
    else
#endif
    {
        g_stDisplayDPTx1TimingInfo.usHTotal = ((PDATA_WORD(0) & 0x1FFF) + 4) / _PANEL_DPTX_DCLK_DIV;
    }

    // Hstart
    g_stDisplayDPTx1TimingInfo.usHStart = (PDATA_WORD(2) & 0x1FFF) / _PANEL_DPTX_DCLK_DIV;

    // Hwidth
    g_stDisplayDPTx1TimingInfo.usHWidth = ((PDATA_WORD(3) & 0x1FFF) - (PDATA_WORD(2) & 0x1FFF)) / _PANEL_DPTX_DCLK_DIV;

    // Hsyc
    g_stDisplayDPTx1TimingInfo.usHSWidth = pData[3] / _PANEL_DPTX_DCLK_DIV;

    // Hsyc polarity
    g_stDisplayDPTx1TimingInfo.b1HSP = 1;

    if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT3) == _BIT3)
    {
        // M:N frame sync
        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, _BIT7) == _BIT7)
        {
            BYTE ucTemp = 0;

            // Get DVtotal of frame sync frame in M:N case
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, _BIT5);
            ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

            // Get N+1 frame
            ucTemp = (ScalerMemoryGetMNRatio() & 0x00FF) + 1;

            // Wait N+1 dvs for get correct data
            do
            {
                ucTemp--;
                ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_OUTPUT_DATA_PATH());
            }
            while(ucTemp > 0);

            GET_DVTOTAL_LASTLINE(PDATA_WORD(0));
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);

            GET_FREE_RUN_DVTOTAL(PDATA_WORD(1));

            // Compare DVtotal of frame sync frame and DVtotal of free run frame
            if(PDATA_WORD(1) < PDATA_WORD(0))
            {
                PDATA_WORD(0) = PDATA_WORD(1);
            }
        }
        else
        {
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
            ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_OUTPUT_DATA_PATH());
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_OUTPUT_DATA_PATH());
            GET_DVTOTAL_LASTLINE(PDATA_WORD(0));
        }
    }
    else
    {
        GET_FREE_RUN_DVTOTAL(PDATA_WORD(0));
    }

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0D_DISPLAY_VER_SYNC_END);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 3, &pData[3], _NON_AUTOINC);

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 2, &pData[6], _NON_AUTOINC);

    // Vtotal
    g_stDisplayDPTx1TimingInfo.usVTotal = ((PDATA_WORD(0) + 1) & 0x1FFF);

    // VStart
    g_stDisplayDPTx1TimingInfo.usVStart = (PDATA_WORD(2) & 0x1FFF);

    // VHeight
    g_stDisplayDPTx1TimingInfo.usVHeight = (PDATA_WORD(3) & 0x1FFF) - (PDATA_WORD(2) & 0x1FFF);

    // Vsync
    g_stDisplayDPTx1TimingInfo.usVSWidth = (pData[3]);

    // Vsyc polarity
    g_stDisplayDPTx1TimingInfo.b1VSP = 1;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3     //Linqian
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1MLPHYSet(void)
{
    switch(GET_DISPLAY_DP_TX1_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            // Adjust Lane3 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx1SetSignalLevel(_DISPLAY_DP_TX_LANE_3, GET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS());

            // Adjust Lane2 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx1SetSignalLevel(_DISPLAY_DP_TX_LANE_2, GET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS());

            // Adjust Lane1 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx1SetSignalLevel(_DISPLAY_DP_TX_LANE_1, GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS());

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx1SetSignalLevel(_DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS());

            break;

        case _DP_TWO_LANE:

            // Adjust Lane1 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx1SetSignalLevel(_DISPLAY_DP_TX_LANE_1, GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS());

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx1SetSignalLevel(_DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS());

            break;

        case _DP_ONE_LANE:

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx1SetSignalLevel(_DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS());

            break;

        default:

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx1SetSignalLevel(_DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS());

            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Write
// Input Value  : ucCommand --> Native Aux Write Command
//                ucHighAddress --> High Byte of  Native Aux Write Address
//                ucMidAddress --> Middle Byte of  Native Aux Write Address
//                ucLowAddress --> Low Byte of  Native Aux Write Address
//                ucLength --> Native Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTx1NativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    if(ScalerDisplayDPTx1AuxWrite((0x80 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucWriteArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Read
// Input Value  : ucCommand --> Native Aux Read Command
//                ucHighAddress --> High Byte of  Native Aux Read Address
//                ucMidAddress --> Middle Byte of  Native Aux Read Address
//                ucLowAddress --> Low Byte of  Native Aux Read Address
//                ucLength --> Native Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Read
// Output Value : TRUE --> Native Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTx1NativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    if(ScalerDisplayDPTx1AuxRead((0x90 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucReadArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx2Initial(void)
{
    ScalerDisplayDPTx2AuxInitial();

    ScalerDisplayDPTx2HpdInitial();

    // Enable DPTX2 Small FIFO ouput 10bits data for each lane of Analog PHY driver ciruit.
    ScalerSetBit(P9E_10_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

    // Enable Arbiter Stuffing and Framing
    ScalerSetBit(P9E_C9_ARBITER_CTRL, ~_BIT0, _BIT0);

    SET_DISPLAY_DP_TX2_INPUT_COLOR_DEPTH(_PANEL_DISP_BIT_MODE);
    SET_DISPLAY_DP_TX2_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
}

//--------------------------------------------------
// Description  : Dp Tx Read DPCD Rx Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx2LinkConfig(void)
{
    // Set Power Normal
    pData[0] = 0x01;
    if(ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x06, 0x00, 1, pData) == _FALSE)
    {
        return _FALSE;
    }

    ScalerTimerDelayXms(10);

    // Read Sink Power Status
    if(ScalerDisplayDPTx2NativeAuxRead(0x00, 0x06, 0x00, 1, pData) == _FALSE)
    {
        return _FALSE;
    }

    // Check if Power State is Normal
    if(pData[0] != 0x01)
    {
        return _FALSE;
    }

    // Read Sink Cabability
    if(ScalerDisplayDPTx2NativeAuxRead(0x00, 0x00, 0x00, 16, pData) == _FALSE)
    {
        return _FALSE;
    }

    // Get DPCD revision number
    if((pData[0] != _DP_VERSION_1_0) && (pData[0] != _DP_VERSION_1_1) && (pData[0] != _DP_VERSION_1_2))
    {
        pData[0] = _DP_VERSION_1_1;
    }

    // Set DPCD revision nember
    SET_DISPLAY_DP_TX2_DPCD_REV(pData[0]);

    if(pData[0] == _DP_VERSION_1_2)
    {
        // Check TP3 support
        if((pData[2] & _BIT6) == _BIT6)
        {
            SET_DISPLAY_DP_TX2_TP3_SUPPORT();
        }
        else
        {
            CLR_DISPLAY_DP_TX2_TP3_SUPPORT();
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX2_TP3_SUPPORT();
    }

    if((pData[1] == _DP_LINK_RBR) || (pData[1] == _DP_LINK_HBR) || ((pData[0] == _DP_VERSION_1_2) && (pData[1] == _DP_LINK_HBR2)))
    {
        // Set Link Rate
        SET_DISPLAY_DP_TX2_MAX_LINK_RATE(pData[1]);
    }
    else
    {
        // Set the Slowest Link Rate
        SET_DISPLAY_DP_TX2_MAX_LINK_RATE(_DP_LINK_RBR);
    }

    // Set Lane Number
    SET_DISPLAY_DP_TX2_LANE_NUM((pData[2] & 0x1F));

    // Set Enhanceed Framing
    SET_DISPLAY_DP_TX2_ENHANCE_FRAMING((bit)(pData[2] & _BIT7));

    // Set Max Downspread
    SET_DISPLAY_DP_TX2_DOWN_SPREAD((bit)(pData[3] & _BIT0));

    // Set Framing Change for eDP
    SET_DISPLAY_DP_TX2_FRAMING_CHANGE_CAPABLE((bit)(pData[13] & _BIT1));

    // Set Alternate SR Capable for eDP
    SET_DISPLAY_DP_TX2_ALTERNATE_SR_CAPABLE((bit)(pData[13] & _BIT0));

    return _TRUE;
}

//--------------------------------------------------
// Description  : Handle Tx2 Output stream
// Input Value  : DP Tx Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx2VideoStreamOutput(bit bOutput)
{
    if(bOutput == _ENABLE)
    {
#if((_DISPLAY_DP_TX_FB_MODE == _OFF) && (_DISPLAY_DP_TX_PORT_1 == _OFF))
        // Set Progressive Mode for TX2(MAC1)
        ScalerSetBit(P9C_D9_DPTX_TOP_CTL, ~(_BIT3 | _BIT2), _BIT3);
#endif

        ScalerDisplayDPTx2MeasureInputInfo();

        PDATA_DWORD(0) = 0;
        PDATA_DWORD(1) = 0x8000;
        PDATA_DWORD(2) = 0;

        // Mvid = Stream clk x Nvid / Link clk
        PDATA_DWORD(0) = ((DWORD)GET_D_CLK_FREQ() / _PANEL_DPTX_DCLK_DIV / 100) * PDATA_DWORD(1);
        PDATA_DWORD(0) /= ((GET_DISPLAY_DP_TX_SSCG_CONFIG() == _TRUE) ? ((DWORD)270 * GET_DISPLAY_DP_TX2_LINK_RATE() * 9975 / 10000) : ((DWORD)270 * GET_DISPLAY_DP_TX2_LINK_RATE()));

        // Debounce 10 times
        pData[12] = 0x0A;

        do
        {
            // Select HW mode for Mvid
            ScalerSetBit(P9E_A8_MN_VID_AUTO_EN_1, ~_BIT7, _BIT7);

            ScalerTimerDelayXms(2);

            // Select HW mode for Mvid
            ScalerSetBit(P9E_A8_MN_VID_AUTO_EN_1, ~_BIT7, 0x00);

            // Get Mvid From HW Mode
            PDATA_DWORD(2) = (((DWORD)ScalerGetByte(P9E_AF_MVID_AUTO_H) << 16) | ((DWORD)ScalerGetByte(P9E_B0_MVID_AUTO_M) << 8) | ScalerGetByte(P9E_B1_MVID_AUTO_L));

            // For RLE0779A/RL6449A disable auto Mvid is zero
            if(PDATA_DWORD(2) == 0)
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                ScalerSetByte(P9E_A9_MN_M_VID_H, pData[1]);
                ScalerSetByte(P9E_AA_MN_M_VID_M, pData[2]);
                ScalerSetByte(P9E_AB_MN_M_VID_L, pData[3]);

                break;
            }

            if(abs(PDATA_DWORD(0) - PDATA_DWORD(2)) < (PDATA_DWORD(0) >> 1))
            {
                // Set Mvid for HW mode
                ScalerSetByte(P9E_A9_MN_M_VID_H, pData[9]);
                ScalerSetByte(P9E_AA_MN_M_VID_M, pData[10]);
                ScalerSetByte(P9E_AB_MN_M_VID_L, pData[11]);

                break;
            }

            pData[12]--;

            if(pData[12] == 0x00)
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                ScalerSetByte(P9E_A9_MN_M_VID_H, pData[1]);
                ScalerSetByte(P9E_AA_MN_M_VID_M, pData[2]);
                ScalerSetByte(P9E_AB_MN_M_VID_L, pData[3]);
            }
        }
        while(pData[12] != 0);

        // Set Nvid for FW mode
        ScalerSetByte(P9E_AC_MN_N_VID_H, pData[5]);
        ScalerSetByte(P9E_AD_MN_N_VID_M, pData[6]);
        ScalerSetByte(P9E_AE_MN_N_VID_L, pData[7]);

        // Set Mvid DB Direct Effective
        ScalerSetBit(P9E_B4_MSA_CTRL, ~_BIT6, 0x00);

        // Set Mvid DB for FW mode
        ScalerSetBit(P9E_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6), _BIT6);

        // For Mvid Auto New Mode, M/N mode Measure and Generate are Independant.
        // SET_DISPLAY_DP_TX2_MVID_FW_MODE -> FW Manually Set Mvid/Nvid
        SET_DISPLAY_DP_TX2_MVID_FW_MODE();

        // MSA fill
        ScalerDisplayDPTx2DisplayMSASetting();

        // DP Tx TU Setting
        ScalerDisplayDPTx2DisplayFormatSetting();

        // Clear FIFO Status
        ScalerSetByte(P9E_A4_PG_FIFO_CTRL, 0xFF);

        // Main Link Switch to VIDEO pattern
        ScalerSetBit(P9E_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT6);

        // Double buffer only by Vsync
        ScalerSetBit(P9E_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Main Link Switch to IDLE pattern
        ScalerSetBit(P9E_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // Double buffer only by Vsync
        ScalerSetBit(P9E_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);
    }
}

//--------------------------------------------------
// Description  : DP Tx Arbiter
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2DisplayFormatSetting(void)
{
    // Disable HW Auto Calculate H Delay
    ScalerSetBit(P9E_D3_LFIFO_WL_SET, ~_BIT7, 0x00);

    // Pixel Generation Block Reset
    ScalerSetBit(P9E_A1_DP_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(P9E_A1_DP_RESET_CTRL, ~_BIT7, 0x00);

    // Get Bit Per Chrome
    switch(GET_DISPLAY_DP_TX2_INPUT_COLOR_DEPTH())
    {
        case 0x00:
            pData[0] = 6;
            break;

        case 0x01:
            pData[0] = 8;
            break;

        case 0x02:
            pData[0] = 10;
            break;

        case 0x03:
            pData[0] = 12;
            break;

        case 0x04:
            pData[0] = 16;
            break;

        default:

            pData[0] = 8;
            break;
    }

    // Calculate Vaild Symbol in TU
    // Average TU = TU Size x (Stream_Clk x Byte of 1 pixel / Lane Number) / Link Rate
    PDATA_WORD(1) = ((GET_DISPLAY_DP_TX_SSCG_CONFIG() == _TRUE) ? ((DWORD)270 * GET_DISPLAY_DP_TX2_LINK_RATE() * 9975 / 10000) : ((DWORD)270 * GET_DISPLAY_DP_TX2_LINK_RATE()));
    PDATA_WORD(1) = ((DWORD)_DISPLAY_DP_TX2_TU_SIZE * (((DWORD)GET_D_CLK_FREQ() / _PANEL_DPTX_DCLK_DIV / 100 * 3 * pData[0]) / GET_DISPLAY_DP_TX2_LANE_NUM())) / (PDATA_WORD(1));

    ScalerSetByte(P9E_CC_TU_SIZE, _DISPLAY_DP_TX2_TU_SIZE);
    ScalerSetByte(P9E_CD_TU_DATA_SIZE0, (PDATA_WORD(1) >> 3));
    ScalerSetByte(P9E_CE_TU_DATA_SIZE1, (PDATA_WORD(1) & 0x07));

    PDATA_WORD(1) = ((DWORD)g_stDisplayDPTx2TimingInfo.usHWidth * pData[0] * 3) / (GET_DISPLAY_DP_TX2_LANE_NUM() * 8);
    PDATA_WORD(1) += ((bit)(((DWORD)g_stDisplayDPTx2TimingInfo.usHWidth * pData[0] * 3) % (GET_DISPLAY_DP_TX2_LANE_NUM() * 8)) ? 1 : 0);

    ScalerSetByte(P9E_CA_V_DATA_PER_LINE0, pData[2]);
    ScalerSetByte(P9E_CB_V_DATA_PER_LINE1, pData[3]);

    // Enable HW Auto Calculate H Delay
    ScalerSetBit(P9E_D3_LFIFO_WL_SET, ~_BIT7, _BIT7);

    ScalerSetByte(P9E_D4_ARBITER_SEC_END_CNT_HB, 0x00);
    ScalerSetByte(P9E_D5_ARBITER_SEC_END_CNT_LB, 0x47);
}

//--------------------------------------------------
// Description  : DP Tx MSA Generation
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2DisplayMSASetting(void)
{
    // Reset MSA Generation Block and SEC Block
    ScalerSetBit(P9E_A1_DP_RESET_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(P9E_A1_DP_RESET_CTRL, ~_BIT6, 0x00);

    // Set Htotal
    ScalerSetByte(P9E_B7_MN_STRM_ATTR_HTT_M, HIBYTE(g_stDisplayDPTx2TimingInfo.usHTotal));
    ScalerSetByte(P9E_B8_MN_STRM_ATTR_HTT_L, LOBYTE(g_stDisplayDPTx2TimingInfo.usHTotal));

    // Set Hstart
    ScalerSetByte(P9E_B9_MN_STRM_ATTR_HST_M, HIBYTE(g_stDisplayDPTx2TimingInfo.usHStart));
    ScalerSetByte(P9E_BA_MN_STRM_ATTR_HST_L, LOBYTE(g_stDisplayDPTx2TimingInfo.usHStart));

    // Set Hwidth
    ScalerSetByte(P9E_BB_MN_STRM_ATTR_HWD_M, HIBYTE(g_stDisplayDPTx2TimingInfo.usHWidth));
    ScalerSetByte(P9E_BC_MN_STRM_ATTR_HWD_L, LOBYTE(g_stDisplayDPTx2TimingInfo.usHWidth));

    // Set Hsyc
    ScalerSetByte(P9E_BD_MN_STRM_ATTR_HSW_M, HIBYTE(g_stDisplayDPTx2TimingInfo.usHSWidth));
    ScalerSetByte(P9E_BE_MN_STRM_ATTR_HSW_L, LOBYTE(g_stDisplayDPTx2TimingInfo.usHSWidth));

    // Set Vtotal
    ScalerSetByte(P9E_BF_MN_STRM_ATTR_VTTE_M, HIBYTE(g_stDisplayDPTx2TimingInfo.usVTotal));
    ScalerSetByte(P9E_C0_MN_STRM_ATTR_VTTE_L, LOBYTE(g_stDisplayDPTx2TimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(P9E_C1_MN_STRM_ATTR_VST_M, HIBYTE(g_stDisplayDPTx2TimingInfo.usVStart));
    ScalerSetByte(P9E_C2_MN_STRM_ATTR_VST_L, LOBYTE(g_stDisplayDPTx2TimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(P9E_C3_MN_STRM_ATTR_VHT_M, HIBYTE(g_stDisplayDPTx2TimingInfo.usVHeight));
    ScalerSetByte(P9E_C4_MN_STRM_ATTR_VHT_L, LOBYTE(g_stDisplayDPTx2TimingInfo.usVHeight));

    // Set Vsync
    ScalerSetByte(P9E_C5_MN_STRM_ATTR_VSW_M, HIBYTE(g_stDisplayDPTx2TimingInfo.usVSWidth));
    ScalerSetByte(P9E_C6_MN_STRM_ATTR_VSW_L, LOBYTE(g_stDisplayDPTx2TimingInfo.usVSWidth));

    // Set Color Space
    ScalerSetBit(P9E_B5_MSA_MISC0, ~(_BIT2 | _BIT1), (GET_DISPLAY_DP_TX2_INPUT_COLOR_SPACE() << 1));

    // Set Color Depth
    ScalerSetBit(P9E_B5_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5), (GET_DISPLAY_DP_TX2_INPUT_COLOR_DEPTH() << 5));

    // Set MISC1
    ScalerSetByte(P9E_B6_MN_STRM_ATTR_MISC1, 0x00);

    // MSA_DB = 1 and Bouble Buffer at V Blanking
    ScalerSetBit(P9E_B4_MSA_CTRL, ~(_BIT7 | _BIT6), _BIT7);
}

//--------------------------------------------------
// Description  : DP Tx Link Training
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2LinkTraining(void)
{
    if(GET_DISPLAY_DP_TX2_LINK_CONFIG() == _TRUE)
    {
        ScalerDisplayDPTx2TPInitialSet();

        while((GET_DISPLAY_DP_TX2_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_PASS) && (GET_DISPLAY_DP_TX2_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_FAIL))
        {
            switch(GET_DISPLAY_DP_TX2_LT_STATE())
            {
                case _DISPLAY_DP_TX_TRAINING_PATTERN1:

                    SET_DISPLAY_DP_TX2_LT_RESULT(ScalerDisplayDPTx2TrainPattern1());

                    if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS)
                    {
                        SET_DISPLAY_DP_TX2_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN2);
                    }
                    else if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL)
                    {
                        SET_DISPLAY_DP_TX2_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DISPLAY_DP_TX_TRAINING_PATTERN2:

                    SET_DISPLAY_DP_TX2_LT_RESULT(ScalerDisplayDPTx2TrainPattern2());

                    if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS)
                    {
                        SET_DISPLAY_DP_TX2_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }
                    else if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL)
                    {
                        SET_DISPLAY_DP_TX2_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DISPLAY_DP_TX_TRAINING_PATTERN_END:

                    if(GET_DISPLAY_DP_TX2_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS)
                    {
                        SET_DISPLAY_DP_TX2_LT_RESULT(_DISPLAY_DP_TX_TRAINING_FAIL);
                    }
                    else
                    {
                        SET_DISPLAY_DP_TX2_LT_RESULT(_DISPLAY_DP_TX_TRAINING_PASS);
                    }

                    ScalerDisplayDPTx2TrainPatternEnd();

                    break;

                default:

                    break;
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Inital Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2TPInitialSet(void)
{
    PCB_DPTX2_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_LINK_TRAINING);

    SET_DISPLAY_DP_TX2_LT_RESULT(_DISPLAY_DP_TX_TRAINING_NO_RESULT);
    SET_DISPLAY_DP_TX2_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN1);

    // Set Link Rate
    SET_DISPLAY_DP_TX2_LINK_RATE(_PANEL_DPTX_LINK_RATE);

    // Set Link Rate for DPCD table of the Sink
    ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x00, 1, &GET_DISPLAY_DP_TX2_MAX_LINK_RATE());

    // Set Link Rate
    ScalerDisplayDPTxSetLinkRate();

    if(GET_DISPLAY_DP_TX2_FRAMING_CHANGE_CAPABLE() == _TRUE)
    {
        // Set Link Count and Disable Enhance Framing for External DP Sink
        pData[0] = GET_DISPLAY_DP_TX2_LANE_NUM();
        ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x01, 1, pData);

        // Set Enhance Framing Mode for eDP
        pData[0] = ((BYTE)GET_DISPLAY_DP_TX2_FRAMING_CHANGE_CAPABLE() << 1);
        ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);

        ScalerDisplayDPTx2EnhanceFramingMode(_ENABLE);
    }
    else
    {
        // Set Link Count and Enhance Framing for DPCD table of the Sink
        pData[0] = ((BYTE)GET_DISPLAY_DP_TX2_ENHANCE_FRAMING() << 7) | GET_DISPLAY_DP_TX2_LANE_NUM();
        ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x01, 1, pData);

        ScalerDisplayDPTx2EnhanceFramingMode(GET_DISPLAY_DP_TX2_ENHANCE_FRAMING());
    }

    // Initialize Main Link Signal for DPCD table of the Sink
    ScalerDisplayDPTx2SignalInitialSetting();

    ScalerDisplayDPTx2NativeAuxRead(0x00, 0x01, 0x07, 1, pData);

    // Set Down Spread for DPCD table of the Sink
    pData[0] = ((pData[0] & ~_BIT4) | ((BYTE)GET_DISPLAY_DP_TX_SSCG_CONFIG() << 4));
    ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x07, 1, pData);

    // Set DPTx Spread Spectrum
    ScalerDisplayDPTxSSCSet(GET_DISPLAY_DP_TX_SSCG_CONFIG());
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDisplayDPTx2TrainPattern1(void)
{
    // Start TP1 Process
    if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_NO_RESULT)
    {
        // Repeat Bist Pattern --> for Training Pattern
        ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Select TP1
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, _BIT5);

        pData[0] = (_DISPLAY_DP_TX_TP_1 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
        pData[1] = g_stDisplayDPTx2LTInfo.ucLane0Adjust;
        pData[2] = g_stDisplayDPTx2LTInfo.ucLane1Adjust;
        pData[3] = g_stDisplayDPTx2LTInfo.ucLane2Adjust;
        pData[4] = g_stDisplayDPTx2LTInfo.ucLane3Adjust;

        // Write DPCD 102h to Start TP1
        ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerDisplayDPTx2MLPHYSet();

        pData[0] = g_stDisplayDPTx2LTInfo.ucLane0Adjust;
        pData[1] = g_stDisplayDPTx2LTInfo.ucLane1Adjust;
        pData[2] = g_stDisplayDPTx2LTInfo.ucLane2Adjust;
        pData[3] = g_stDisplayDPTx2LTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h  (Voltage Swing and Pre-emphasis)
        ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x03, 4, pData);
    }

    // Delay 400us
    for(pData[0] = 0; pData[0] < 55; pData[0]++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Read Lane Status and Request Adjust Level
    ScalerDisplayDPTx2NativeAuxRead(0x00, 0x02, 0x02, 6, pData);
    g_stDisplayDPTx2LTInfo.ucLane01LTStatus = pData[0];
    g_stDisplayDPTx2LTInfo.ucLane23LTStatus = pData[1];
    g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 = pData[4];
    g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 = pData[5];

    if(((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX2_LANE3_CR_DONE() & GET_DISPLAY_DP_TX2_LANE2_CR_DONE() & GET_DISPLAY_DP_TX2_LANE1_CR_DONE() & GET_DISPLAY_DP_TX2_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX2_LANE1_CR_DONE() & GET_DISPLAY_DP_TX2_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX2_LANE0_CR_DONE() == _TRUE)))
    {
        return _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS;
    }

    switch(GET_DISPLAY_DP_TX2_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            if(ScalerDisplayDPTx2TP1Lane3Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDisplayDPTx2TP1Lane2Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

        case _DP_TWO_LANE:

            if(ScalerDisplayDPTx2TP1Lane1Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

        case _DP_ONE_LANE:
        default:

            if(ScalerDisplayDPTx2TP1Lane0Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;
    }

    return _DISPLAY_DP_TX_TRAINING_PATTERN1_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDisplayDPTx2TrainPattern2(void)
{
    // Start TP2 Process
    if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS)
    {
        // Repeat Bist Pattern --> for Training Pattern
        ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Disable De-Scambling
        ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, _BIT1);

        // Set TP2 Pattern Type
        pData[0] = ScalerDisplayDPTx2SetTp2PatternType() | _DISPLAY_DP_TX_SCRAMBLING_DISABLE;

        pData[1] = g_stDisplayDPTx2LTInfo.ucLane0Adjust;
        pData[2] = g_stDisplayDPTx2LTInfo.ucLane1Adjust;
        pData[3] = g_stDisplayDPTx2LTInfo.ucLane2Adjust;
        pData[4] = g_stDisplayDPTx2LTInfo.ucLane3Adjust;

        // Write DPCD 102h-107h to Start TP2
        ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerDisplayDPTx2MLPHYSet();

        pData[0] = g_stDisplayDPTx2LTInfo.ucLane0Adjust;
        pData[1] = g_stDisplayDPTx2LTInfo.ucLane1Adjust;
        pData[2] = g_stDisplayDPTx2LTInfo.ucLane2Adjust;
        pData[3] = g_stDisplayDPTx2LTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x03, 4, pData);
    }

    // Delay 400us
    for(pData[0] = 0; pData[0] < 55; pData[0]++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Read Lane Status and Request Adjust Level
    ScalerDisplayDPTx2NativeAuxRead(0x00, 0x02, 0x02, 6, pData);
    g_stDisplayDPTx2LTInfo.ucLane01LTStatus = pData[0];
    g_stDisplayDPTx2LTInfo.ucLane23LTStatus = pData[1];
    g_stDisplayDPTx2LTInfo.ucLaneAlignStatus = pData[2];
    g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 = pData[4];
    g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 = pData[5];

    // CDR unlock => Reduce bit rate and return to TP1
    if(((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX2_LANE3_CR_DONE() & GET_DISPLAY_DP_TX2_LANE2_CR_DONE() & GET_DISPLAY_DP_TX2_LANE1_CR_DONE() & GET_DISPLAY_DP_TX2_LANE0_CR_DONE()) != _TRUE)) ||
       ((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX2_LANE1_CR_DONE() & GET_DISPLAY_DP_TX2_LANE0_CR_DONE()) != _TRUE)) ||
       ((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX2_LANE0_CR_DONE() != _TRUE)))
    {
        CLR_DISPLAY_DP_TX2_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }

    if((((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX2_LANE3_EQ_DONE() & GET_DISPLAY_DP_TX2_LANE2_EQ_DONE() & GET_DISPLAY_DP_TX2_LANE1_EQ_DONE() & GET_DISPLAY_DP_TX2_LANE0_EQ_DONE()) == _TRUE)) ||
        ((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX2_LANE1_EQ_DONE() & GET_DISPLAY_DP_TX2_LANE0_EQ_DONE()) == _TRUE)) ||
        ((GET_DISPLAY_DP_TX2_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX2_LANE0_EQ_DONE() == _TRUE))) &&
       (GET_DISPLAY_DP_TX2_LANE_ALIGN_DONE() == _TRUE))
    {
        CLR_DISPLAY_DP_TX2_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS;
    }

    if(GET_DISPLAY_DP_TX2_TP2_CNT() == 5)
    {
        CLR_DISPLAY_DP_TX2_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }
    else
    {
        ADD_DISPLAY_DP_TX2_TP2_CNT();
    }

    switch(GET_DISPLAY_DP_TX2_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            ScalerDisplayDPTx2TP2Lane3Adjust();
            ScalerDisplayDPTx2TP2Lane2Adjust();

        case _DP_TWO_LANE:

            ScalerDisplayDPTx2TP2Lane1Adjust();

        case _DP_ONE_LANE:
        default:

            ScalerDisplayDPTx2TP2Lane0Adjust();

            break;
    }

    return _DISPLAY_DP_TX_TRAINING_PATTERN2_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training Pattern End
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2TrainPatternEnd(void)
{
    // Write TRAINING_PATTERN_SET = 00
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);

    ScalerDisplayDPTx2SetTps3PatternMux(_OFF);

    if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
    {
        if(GET_DISPLAY_DP_TX2_ALTERNATE_SR_CAPABLE() == _TRUE)
        {
            // Scambling Seed Select to 0xFFFE
            ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT4, 0x00);

            pData[0] = ((BYTE)GET_DISPLAY_DP_TX2_FRAMING_CHANGE_CAPABLE() << 1) | _BIT0;
            ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);
        }
        else
        {
            // Scambling Seed Select to 0xFFFF
            ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT4, _BIT4);
        }

        // Enable Scrambling
        ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, 0x00);

        // Enable BS replaced by SR
        ScalerSetBit(P9E_0D_DPTX_PHY_CTRL, ~_BIT4, _BIT4);

        // Main Link switch to IDLE Pattern
        ScalerDisplayDPTx2VideoStreamOutput(_DISABLE);

        // Panel DPTx Power Sequence Check Point
        PCB_DPTX2_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_IDLE_PATTERN);

        // Disable bist mode
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), 0x00);

        // Disable Bist Pattern --> for Video Data
        ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~_BIT7, 0x00);
    }
    else
    {
        ScalerDisplayDPTx2LanePowerOff();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx2TP1Lane0Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX2_LANE0_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE0_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX2_LANE0_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX2_LANE0_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX2_LANE0_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX2_LANE0_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx2TP1Lane1Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX2_LANE1_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE1_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX2_LANE1_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX2_LANE1_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT();
    }


    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX2_LANE1_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX2_LANE1_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx2TP1Lane2Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX2_LANE2_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE2_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX2_LANE2_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX2_LANE2_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX2_LANE2_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX2_LANE2_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTx2TP1Lane3Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX2_LANE3_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE3_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX2_LANE3_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX2_LANE3_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX2_LANE3_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX2_LANE3_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2TP2Lane0Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX2_LANE0_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX2_LANE0_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX2_LANE0_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2TP2Lane1Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX2_LANE1_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX2_LANE1_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX2_LANE1_ADJUST_VOL_SWING());
    }


    if(GET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2TP2Lane2Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX2_LANE2_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX2_LANE2_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX2_LANE2_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2TP2Lane3Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX2_LANE3_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX2_LANE3_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX2_LANE3_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link TSignal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2LinkForceOutput(void)
{
    ScalerDisplayDPTx2TPInitialSet();

    // Set Output Signal According to Request
    ScalerDisplayDPTx2MLPHYSet();

    // Training Pattern 1 For Link Training
    // Repeat Bist Pattern --> for Training Pattern
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Select TP1
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, _BIT5);

    pData[0] = _DISPLAY_DP_TX_TP_1 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE;
    pData[1] = g_stDisplayDPTx2LTInfo.ucLane0Adjust;
    pData[2] = g_stDisplayDPTx2LTInfo.ucLane1Adjust;
    pData[3] = g_stDisplayDPTx2LTInfo.ucLane2Adjust;
    pData[4] = g_stDisplayDPTx2LTInfo.ucLane3Adjust;

    // Write DPCD 102h-107h to Start TP1
    ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x02, 5, pData);

    // Delay 400us
    for(pData[0] = 0; pData[0] < 55; pData[0]++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Training Pattern 2 For Link Training
    // Repeat Bist Pattern --> for Training Pattern
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Disable De-Scambling
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, _BIT1);

    // Select TP2
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, 0x00);

    pData[0] = _DISPLAY_DP_TX_TP_2 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE;
    pData[1] = g_stDisplayDPTx2LTInfo.ucLane0Adjust;
    pData[2] = g_stDisplayDPTx2LTInfo.ucLane1Adjust;
    pData[3] = g_stDisplayDPTx2LTInfo.ucLane2Adjust;
    pData[4] = g_stDisplayDPTx2LTInfo.ucLane3Adjust;

    // Write DPCD 102h-107h to Start TP2
    ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x02, 5, pData);

    // Delay 400us
    for(pData[0] = 0; pData[0] < 55; pData[0]++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x02, 1, pData);

    if(GET_DISPLAY_DP_TX2_ALTERNATE_SR_CAPABLE() == _TRUE)
    {
        // Scambling Seed Select to 0xFFFE
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT4, 0x00);

        pData[0] = ((BYTE)GET_DISPLAY_DP_TX2_FRAMING_CHANGE_CAPABLE() << 1) | _BIT0;
        ScalerDisplayDPTx2NativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);
    }
    else
    {
        // Scambling Seed Select to 0xFFFF
        ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT4, _BIT4);
    }

    // Enable Scambling
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, 0x00);

    // Enable BS replaced by SR
    ScalerSetBit(P9E_0D_DPTX_PHY_CTRL, ~_BIT4, _BIT4);

    // Main Link switch to IDLE Pattern
    ScalerDisplayDPTx2VideoStreamOutput(_DISABLE);

    // Disable bist mode
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), 0x00);

    // Disable Bist Pattern --> for Video Data
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2SignalReset(void)
{
    // Set Voltage Swing and pre-emphasis Variable to level 0
    CLR_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT();

    SET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();

    // Clear TP2 Count
    CLR_DISPLAY_DP_TX2_TP2_CNT();

    ScalerDisplayDPTx2MLPHYSet();
}

//--------------------------------------------------
// Description  : Handle Enhance Framing
// Input Value  : _ENABLE of _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx2EnhanceFramingMode(bit bEnable)
{
    // Disable Digital PHY Enhancement
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT3, 0x00);

    // Enable Enhancement
    ScalerSetBit(P9E_A0_DP_MAC_CTRL, ~_BIT2, ((BYTE)bEnable << 2));
}

//--------------------------------------------------
// Description  : Measure function for DPTX SST D0
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDisplayDPTx2MeasureInputInfo(void)
{
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 2, &pData[0], _NON_AUTOINC);

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 3, &pData[3], _NON_AUTOINC);

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 2, &pData[6], _NON_AUTOINC);

    // Htotal
#if(_D_DOMAIN_PATH == _D_DOMAIN_4_PATH)
    if(GET_MDOMAIN_DISPLAY_MODE() == _DISPLAY_MODE_1P)
    {
        g_stDisplayDPTx2TimingInfo.usHTotal = ((PDATA_WORD(0) & 0x1FFF) + 8) / _PANEL_DPTX_DCLK_DIV;
    }
    else
#endif
    {
        g_stDisplayDPTx2TimingInfo.usHTotal = ((PDATA_WORD(0) & 0x1FFF) + 4) / _PANEL_DPTX_DCLK_DIV;
    }

    // Hstart
    g_stDisplayDPTx2TimingInfo.usHStart = (PDATA_WORD(2) & 0x1FFF) / _PANEL_DPTX_DCLK_DIV;

    // Hwidth
    g_stDisplayDPTx2TimingInfo.usHWidth = ((PDATA_WORD(3) & 0x1FFF) - (PDATA_WORD(2) & 0x1FFF)) / _PANEL_DPTX_DCLK_DIV;

    // Hsyc
    g_stDisplayDPTx2TimingInfo.usHSWidth = pData[3] / _PANEL_DPTX_DCLK_DIV;

    // Hsyc polarity
    g_stDisplayDPTx2TimingInfo.b1HSP = 1;

    if(ScalerGetBit(P0_28_VIDEO_DISPLAY_CONTROL_REG, _BIT3) == _BIT3)
    {
        // M:N frame sync
        if(ScalerGetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_25_MN_FRAME_RATE_EN, _BIT7) == _BIT7)
        {
            BYTE ucTemp = 0;

            // Get DVtotal of frame sync frame in M:N case
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, _BIT5);
            ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);

            // Get N+1 frame
            ucTemp = (ScalerMemoryGetMNRatio() & 0x00FF) + 1;

            // Wait N+1 dvs for get correct data
            do
            {
                ucTemp--;
                ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_OUTPUT_DATA_PATH());
            }
            while(ucTemp > 0);

            GET_DVTOTAL_LASTLINE(PDATA_WORD(0));
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);

            GET_FREE_RUN_DVTOTAL(PDATA_WORD(1));

            // Compare DVtotal of frame sync frame and DVtotal of free run frame
            if(PDATA_WORD(1) < PDATA_WORD(0))
            {
                PDATA_WORD(0) = PDATA_WORD(1);
            }
        }
        else
        {
            ScalerSetBit(P0_43_FS_DELAY_FINE_TUNE, ~_BIT5, 0x00);
            ScalerSetBit(P0_44_LAST_LINE_H, ~_BIT7, _BIT7);
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_OUTPUT_DATA_PATH());
            ScalerTimerWaitForIDDomainEvent(_EVENT_DVS, GET_MDOMAIN_OUTPUT_DATA_PATH());
            GET_DVTOTAL_LASTLINE(PDATA_WORD(0));
        }
    }
    else
    {
        GET_FREE_RUN_DVTOTAL(PDATA_WORD(0));
    }

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_0D_DISPLAY_VER_SYNC_END);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 3, &pData[3], _NON_AUTOINC);

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_14_DISPLAY_VER_BG_END_H);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 2, &pData[6], _NON_AUTOINC);

    // Vtotal
    g_stDisplayDPTx2TimingInfo.usVTotal = ((PDATA_WORD(0) + 1) & 0x1FFF);

    // VStart
    g_stDisplayDPTx2TimingInfo.usVStart = (PDATA_WORD(2) & 0x1FFF);

    // VHeight
    g_stDisplayDPTx2TimingInfo.usVHeight = (PDATA_WORD(3) & 0x1FFF) - (PDATA_WORD(2) & 0x1FFF);

    // Vsync
    g_stDisplayDPTx2TimingInfo.usVSWidth = (pData[3]);

    // Vsyc polarity
    g_stDisplayDPTx2TimingInfo.b1VSP = 1;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3     //Linqian
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2MLPHYSet(void)
{
    switch(GET_DISPLAY_DP_TX2_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            // Adjust Lane3 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx2SetSignalLevel(_DISPLAY_DP_TX_LANE_3, GET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS());

            // Adjust Lane2 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx2SetSignalLevel(_DISPLAY_DP_TX_LANE_2, GET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS());

        case _DP_TWO_LANE:

            // Adjust Lane1 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx2SetSignalLevel(_DISPLAY_DP_TX_LANE_1, GET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS());

        case _DP_ONE_LANE:

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx2SetSignalLevel(_DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS());

            break;

        default:

            // Adjust Lane0 PHY voltage swing level and Pre-emphasis
            ScalerDisplayDPTx2SetSignalLevel(_DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS());

            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Write
// Input Value  : ucCommand --> Native Aux Write Command
//                ucHighAddress --> High Byte of  Native Aux Write Address
//                ucMidAddress --> Middle Byte of  Native Aux Write Address
//                ucLowAddress --> Low Byte of  Native Aux Write Address
//                ucLength --> Native Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTx2NativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    if(ScalerDisplayDPTx2AuxWrite((0x80 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucWriteArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Read
// Input Value  : ucCommand --> Native Aux Read Command
//                ucHighAddress --> High Byte of  Native Aux Read Address
//                ucMidAddress --> Middle Byte of  Native Aux Read Address
//                ucLowAddress --> Low Byte of  Native Aux Read Address
//                ucLength --> Native Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Read
// Output Value : TRUE --> Native Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTx2NativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    if(ScalerDisplayDPTx2AuxRead((0x90 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucReadArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)
