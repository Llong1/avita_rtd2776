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
// ID Code      : RL6193_Series_DisplayDPTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_PANEL_STYLE == _PANEL_DPTX)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

#define _DISPLAY_DP_TX_SKEW_LANE0                   0
#define _DISPLAY_DP_TX_SKEW_LANE1                   2
#define _DISPLAY_DP_TX_SKEW_LANE2                   4
#define _DISPLAY_DP_TX_SKEW_LANE3                   6

//--------------------------------------------------
// Definations of DP1.1 DPLL VCO Target
//--------------------------------------------------
#define _DP_DPLL_TARGET_FREQ                        216000 // kHz

//--------------------------------------------------
// Definations of DPTX DPLL Range
//--------------------------------------------------
#define _DP_DPLL_BOUNDRY_0                          600000
#define _DP_DPLL_BOUNDRY_1                          1200000
#define _DP_DPLL_BOUNDRY_2                          2400000

#else

#define _DISPLAY_DP_TX_TU_SIZE                      32

#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
BYTE code tVBY1_DRV_TABLE[32] =
{
    // Pre-emphasis->      0                    1                    2                   3
    // VoltageSwing
    /*    0    */      0x04, 0x02,          0x04, 0x06,         0x04, 0x07,         0x04, 0x07,
    /*    1    */      0x09, 0x00,          0x09, 0x07,         0x09, 0x07,         0x09, 0x07,
    /*    2    */      0x0F, 0x01,          0x0F, 0x01,         0x0F, 0x01,         0x0F, 0x01,
    /*    3    */      0x0F, 0x01,          0x0F, 0x01,         0x0F, 0x01,         0x0F, 0x01,
};
#else
BYTE code tDISPLAY_DPTX_DRV_RBR_HBR_TABLE[48] =
{
    // Pre-emphasis->        0                    1                    2                    3
    // VoltageSwing
    /*    0    */      0x00, 0x04, 0x40,    0x03, 0x06, 0x42,    0x85, 0x0A, 0x36,    0x0F, 0x0F, 0xF5,
    /*    1    */      0x00, 0x06, 0x42,    0x21, 0x0E, 0x24,    0x1C, 0x0F, 0xFF,    0x1C, 0x0F, 0xFF,
    /*    2    */      0x0C, 0x0D, 0xB3,    0x1C, 0x0F, 0xFA,    0x1C, 0x0F, 0xFA,    0x1C, 0x0F, 0xFA,
    /*    3    */      0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,
};

BYTE code tDISPLAY_DPTX_DRV_HBR2_TABLE[48] =
{
    // Pre-emphasis->        0                    1                    2                    3
    // VoltageSwing
    /*    0    */      0x00, 0x03, 0x22,    0x0F, 0x0B, 0x61,    0x0F, 0x0C, 0x5A,    0x63, 0x0F, 0xBE,
    /*    1    */      0x00, 0x05, 0x33,    0x23, 0x0E, 0x67,    0xE0, 0x0F, 0x7F,    0xE0, 0x0F, 0x7F,
    /*    2    */      0x00, 0x07, 0x55,    0xE0, 0x0B, 0xFF,    0xE0, 0x0B, 0xFF,    0xE0, 0x0B, 0xFF,
    /*    3    */      0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,
};
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
StructDisplayDPTxInputInfo g_stDisplayDPTxInputInfo;
StructTimingInfo g_stDisplayDPTxTimingInfo;
StructDownStreamInfo g_stDisplayDPTxInfo;
StructDPTxLTInfo g_stDisplayDPTxLTInfo;
#endif // End of #if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDisplayDPTxAnalogPhyConrol(bit bEnable);
void ScalerDisplayDPTxPollingHotPlug(WORD usNum);
bit ScalerDisplayDPTxLinkSequence(void);
void ScalerDisplayDPTxLinkConfigCheck(void);
void ScalerDisplayDPTxCheckSSC(void);
void ScalerDisplayDPTxStreamHanlder(bit bOutput);
void ScalerDisplayDPTxLinkSignalForceOutput(void);
void ScalerDisplayDPTxPowerSequenceProc(bit bLevel);
void ScalerDisplayDPTxPhyInitial(void);
void ScalerDisplayDPTxSSCSet(bit bSscEn);

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
void ScalerDisplayDPTxPhy(bit bOn);
void ScalerDisplayDPTxPLL(bit bOn);
void ScalerDisplayDPTxPLLPower(BYTE ucOn);
void ScalerDisplayDPTxSetPLLReset(void);
void ScalerDisplayDPTxSetPLLFreq(DWORD ulFreq);
void ScalerDisplayDPTxPower(bit bOn);
void ScalerDisplayDPTxSetLinkRate(void);
void ScalerDisplayDPTxSetZ0(void);

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
void ScalerDisplayDPTx1AuxInitial(void);
void ScalerDisplayDPTx1AuxPHYSet(BYTE ucMode);
bit ScalerDisplayDPTx1AuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
bit ScalerDisplayDPTx1AuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
void ScalerDisplayDPTx1HpdInitial(void);
void ScalerDisplayDPTx1SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
void ScalerDisplayDPTx1SignalInitialSetting(void);
void ScalerDisplayDPTx1LanePowerOff(void);
EnumDisplayDPTxTrainPattern ScalerDisplayDPTx1SetTp2PatternType(void);
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
void ScalerDisplayDPTx2AuxInitial(void);
void ScalerDisplayDPTx2AuxPHYSet(BYTE ucMode);
bit ScalerDisplayDPTx2AuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
bit ScalerDisplayDPTx2AuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
void ScalerDisplayDPTx2HpdInitial(void);
void ScalerDisplayDPTx2SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
void ScalerDisplayDPTx2SignalInitialSetting(void);
void ScalerDisplayDPTx2LanePowerOff(void);
EnumDisplayDPTxTrainPattern ScalerDisplayDPTx2SetTp2PatternType(void);
void ScalerDisplayDPTx2SetTps3PatternMux(bit bAphyMux);
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)
#else
void ScalerDisplayDPTxInitial(void);
bit ScalerDisplayDPTxLinkConfig(void);
void ScalerDisplayDPTxVideoStreamOutput(bit bOutput);
void ScalerDisplayDPTxDisplayFormatSetting(void);
void ScalerDisplayDPTxMSASetting(void);
void ScalerDisplayDPTxLinkTraining(void);
void ScalerDisplayDPTxTPInitialSet(void);
BYTE ScalerDisplayDPTxTrainPattern1(void);
bit ScalerDisplayDPTxTP1Lane0Adjust(void);
bit ScalerDisplayDPTxTP1Lane1Adjust(void);
bit ScalerDisplayDPTxTP1Lane2Adjust(void);
bit ScalerDisplayDPTxTP1Lane3Adjust(void);
BYTE ScalerDisplayDPTxTrainPattern2(void);
void ScalerDisplayDPTxTP2Lane0Adjust(void);
void ScalerDisplayDPTxTP2Lane1Adjust(void);
void ScalerDisplayDPTxTP2Lane2Adjust(void);
void ScalerDisplayDPTxTP2Lane3Adjust(void);
void ScalerDisplayDPTxTrainPatternEnd(void);
void ScalerDisplayDPTxSignalReset(void);
void ScalerDisplayDPTxAuxPHYSet(BYTE ucMode);
void ScalerDisplayDPTxSignalInitialSetting(void);
void ScalerDisplayDPTxMLPowerOff(void);
void ScalerDisplayDPTxCMUPowerOn(void);
void ScalerDisplayDPTxCMUPowerOff(void);
void ScalerDisplayDPTxMLPHYSet(void);
void ScalerDisplayDPTxSetSignalLevel(BYTE ucLinkRate, EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
bit ScalerDisplayDPTxAuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
bit ScalerDisplayDPTxAuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
bit ScalerDisplayDPTxNativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
bit ScalerDisplayDPTxNativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
bit ScalerDisplayDPTxMeasureInputInfo(void);
void ScalerDisplayDPTxLinkForceOutput(void);
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Control Vby1 Phy
// Input Value  : bit bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxAnalogPhyConrol(bit bEnable)
{
#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
    // Initial Vby1 Analog PHY for DPTx
    ScalerDisplayDPTxPower(bEnable);

    // Initial Vby1 PLL for DPTx
    ScalerDisplayDPTxPLL(bEnable);

    // Initial Vby1 Digital PHY for DPTx
    ScalerDisplayDPTxPhy(bEnable);
#else
    if(bEnable == _ENABLE)
    {
        ScalerDisplayDPTxCMUPowerOn();
    }
    else
    {
        // Power Down ML PHY
        ScalerDisplayDPTxMLPowerOff();

        // Power CMU PHY
        ScalerDisplayDPTxCMUPowerOff();
    }
#endif
}

//--------------------------------------------------
// Description  : Wait for Dp Tx Htpdn
// Input Value  : WORD usNum
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPollingHotPlug(WORD usNum)
{
#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

    WORD usTimeElapsed = 0;
    WORD usPreviousTime = 0;
    bit bHPCheck = _FALSE;
    usPreviousTime = g_usTimerCounter;

    do
    {
        bHPCheck = _SUCCESS;

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_2 == _ON)

        if(ScalerGetBit(P9C_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            // Panel DPTx Power Sequence Check Point
            PCB_DPTX2_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
            bHPCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

#if(_DISPLAY_DP_TX_PORT_1 == _ON)

        if(ScalerGetBit(P9E_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            // Panel DPTx Power Sequence Check Point
            PCB_DPTX1_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
            bHPCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)
#else
#if(_DISPLAY_DP_TX_PORT_1 == _ON)

        if(ScalerGetBit(P9E_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            // Panel DPTx Power Sequence Check Point
            PCB_DPTX1_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
            bHPCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)

        if(ScalerGetBit(P9C_70_HPD_CTRL, _BIT2) == _BIT2)
        {
            bHPCheck &= _SUCCESS;

            // Panel DPTx Power Sequence Check Point
            PCB_DPTX2_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);
        }
        else
        {
            bHPCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

        if(usPreviousTime != g_usTimerCounter)
        {
            usTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while((usTimeElapsed <= usNum) && (bHPCheck != _SUCCESS));

#else

    ScalerTimerPollingFlagProc(usNum, PBB_70_HPD_CTRL, _BIT2, _TRUE);

    // Panel DPTx Power Sequence Check Point
    PCB_DPTX_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_HPD_ON);

#endif // #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Link Sequence
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDisplayDPTxLinkSequence(void)
{
    bit bLTCheck = _SUCCESS;
    BYTE ucLTRetryNum = 0;

    do
    {
        bLTCheck = _SUCCESS;

        // Check DPTx Link Config
        ScalerDisplayDPTxLinkConfigCheck();

        // Check DPTx SSCG Status
        ScalerDisplayDPTxCheckSSC();

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_2 == _ON)

        // Set Dptx2 Link Training
        ScalerDisplayDPTx2LinkTraining();

        if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
        {
            bLTCheck &= _SUCCESS;
        }
        else
        {
            bLTCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

#if(_DISPLAY_DP_TX_PORT_1 == _ON)

        // Set Dptx1 Link Training
        ScalerDisplayDPTx1LinkTraining();

        if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
        {
            bLTCheck &= _SUCCESS;
        }
        else
        {
            bLTCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)
#else
#if(_DISPLAY_DP_TX_PORT_1 == _ON)

        // Set Dptx1 Link Training
        ScalerDisplayDPTx1LinkTraining();

        if(GET_DISPLAY_DP_TX1_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
        {
            bLTCheck &= _SUCCESS;
        }
        else
        {
            bLTCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)

        // Set Dptx2 Link Training
        ScalerDisplayDPTx2LinkTraining();

        if(GET_DISPLAY_DP_TX2_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
        {
            bLTCheck &= _SUCCESS;
        }
        else
        {
            bLTCheck &= _FALSE;
        }
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

#else

        // Set Dptx Link Training
        ScalerDisplayDPTxLinkTraining();

        if(GET_DISPLAY_DP_TX_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
        {
            bLTCheck &= _SUCCESS;
        }
        else
        {
            bLTCheck &= _FALSE;
        }
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

        ucLTRetryNum += 1;

        ScalerTimerDelayXms(5);
    }
    while((ucLTRetryNum < 5) && (bLTCheck != _SUCCESS));

    return bLTCheck;
}

//--------------------------------------------------
// Description  : Check for Dp Tx Link Config
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxLinkConfigCheck(void)
{
#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    SET_DISPLAY_DP_TX2_LINK_CONFIG(ScalerDisplayDPTx2LinkConfig());
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    SET_DISPLAY_DP_TX1_LINK_CONFIG(ScalerDisplayDPTx1LinkConfig());
#endif
#else
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    SET_DISPLAY_DP_TX1_LINK_CONFIG(ScalerDisplayDPTx1LinkConfig());
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    SET_DISPLAY_DP_TX2_LINK_CONFIG(ScalerDisplayDPTx2LinkConfig());
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

#else
    SET_DISPLAY_DP_TX_LINK_CONFIG(ScalerDisplayDPTxLinkConfig());
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
}

//--------------------------------------------------
// Description  : Setting for eDp Tx SSCG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxCheckSSC(void)
{
    bit bDpTxSscEn = _ENABLE;

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    bDpTxSscEn &= GET_DISPLAY_DP_TX2_DOWN_SPREAD();
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    bDpTxSscEn &= GET_DISPLAY_DP_TX1_DOWN_SPREAD();
#endif
#else
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    bDpTxSscEn &= GET_DISPLAY_DP_TX1_DOWN_SPREAD();
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    bDpTxSscEn &= GET_DISPLAY_DP_TX2_DOWN_SPREAD();
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

#else

    bDpTxSscEn &= GET_DISPLAY_DP_TX_DOWN_SPREAD();

#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

    bDpTxSscEn = (_PANEL_DPTX_SPREAD_RANGE != 0) ? bDpTxSscEn : _DISABLE;

    SET_DISPLAY_DP_TX_SSCG_CONFIG(bDpTxSscEn);
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Stream Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxStreamHanlder(bit bOutput)
{
#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    ScalerDisplayDPTx2VideoStreamOutput(bOutput);
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    ScalerDisplayDPTx1VideoStreamOutput(bOutput);
#endif
#else
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    ScalerDisplayDPTx1VideoStreamOutput(bOutput);
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    ScalerDisplayDPTx2VideoStreamOutput(bOutput);
#endif

#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#else
    ScalerDisplayDPTxVideoStreamOutput(bOutput);
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
}

//--------------------------------------------------
// Description  : DP Tx Link TSignal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxLinkSignalForceOutput(void)
{
#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    ScalerDisplayDPTx2LinkForceOutput();
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    ScalerDisplayDPTx1LinkForceOutput();
#endif
#else
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    ScalerDisplayDPTx1LinkForceOutput();
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    ScalerDisplayDPTx2LinkForceOutput();
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

#else
    ScalerDisplayDPTxLinkForceOutput();
#endif
}

//--------------------------------------------------
// Description  : DP Tx Power Sequence Process
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxPowerSequenceProc(bit bLevel)
{
    bLevel = bLevel;

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    PCB_DPTX2_POWER_SEQUENCE(bLevel);
#endif

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    PCB_DPTX1_POWER_SEQUENCE(bLevel);
#endif
#else
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    PCB_DPTX1_POWER_SEQUENCE(bLevel);
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    PCB_DPTX2_POWER_SEQUENCE(bLevel);
#endif
#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

#else
    PCB_DPTX_POWER_SEQUENCE(bLevel);
#endif
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPhyInitial(void)
{
    // Set DISP mode is Dp Tx
    ScalerSetBit(P39_00_LVDS_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
    // Set PLL phy input clk ref from Dp Tx
    ScalerSetBit(P38_17_CTS_FIFO_L, ~(_BIT6 | _BIT5), _BIT6);

    // Set Dp Tx Digital Phy Initial
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

    // Set eDP mode
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

    // Enable Vby1 Phy power
    ScalerDisplayDPTxAnalogPhyConrol(_ENABLE);

    // Pre-emphasis on
    ScalerSetByte(P38_A2_PHY0_APHY_02, 0xFF);

    // Initial Z0 for DPTx
    ScalerDisplayDPTxSetZ0();
#else
    ScalerDisplayDPTxAnalogPhyConrol(_DISABLE);
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

    // Waiting for PHY initial
    ScalerTimerDelayXms(10);
}

//--------------------------------------------------
// Description  : Dp Tx SSC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxSSCSet(bit bSscEn)
{
#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)

    if(bSscEn == _ENABLE)
    {
#if(_PANEL_DPTX_SPREAD_SPEED == _SPEED_30K)
        // The Numbers of Count for Spread Spectrum FMDIV: 30kHz
        ScalerSetByte(PBE_0D_DCLK_SSC_COUNT, 0x92);
#else
        // The Numbers of Count for Spread Spectrum FMDIV: 33kHz
        ScalerSetByte(PBE_0D_DCLK_SSC_COUNT, 0x94);
#endif
        // Enable DPclk Spread Range New Mode
        ScalerSetBit(PBE_07_DCLK_SPREAD_SPECTRUM, ~_BIT0, _BIT0);
        ScalerSetBit(PBE_07_DCLK_SPREAD_SPECTRUM, ~0xF0, ((_PANEL_DPTX_SPREAD_RANGE << 4) & 0xF0));

        ScalerSetBit(PBE_07_DCLK_SPREAD_SPECTRUM, ~_BIT3, ((_PANEL_DPTX_SPREAD_SPEED << 3) & _BIT3));
        ScalerSetBit(PBE_07_DCLK_SPREAD_SPECTRUM, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable DPclk Spread Range New Mode
        ScalerSetBit(PBE_07_DCLK_SPREAD_SPECTRUM, ~0xF0, 0x00);
        ScalerSetBit(PBE_07_DCLK_SPREAD_SPECTRUM, ~_BIT2, _BIT2);
    }

#else

    if(bSscEn == _ENABLE)
    {
        PDATA_WORD(0) = (WORD)((ScalerGetBit(PBC_DD_DPTX_CMU12, 0x1F) << 4) | (ScalerGetByte(PBC_DE_DPTX_CMU13) >> 4));
        PDATA_WORD(1) = (WORD)((ScalerGetBit(PBC_DE_DPTX_CMU13, 0x0F) << 8) | ScalerGetByte(PBC_DF_DPTX_CMU14));

        // Calculate SSC Frequency = 30~33k
        PDATA_WORD(3) = (((_EXT_XTAL / _DISPLAY_DP_TX_SSC_FREQ) + 2) & 0xFFFC);

        // Calculate SSC downspread
        PDATA_WORD(2) = ((((DWORD)PDATA_WORD(0) + 4) * 4096 + PDATA_WORD(1))) * 16 / 200 / PDATA_WORD(3) / 15 * _PANEL_DPTX_SPREAD_RANGE;

        // Set SSC Frequency = 30~33k
        ScalerSetByte(PBC_E1_DPTX_CMU16, (BYTE)(PDATA_WORD(3) >> 8));
        ScalerSetByte(PBC_E2_DPTX_CMU17, (BYTE)PDATA_WORD(3));

        // Set SSC downspread
        ScalerSetByte(PBC_E3_DPTX_CMU18, (BYTE)(PDATA_WORD(2) >> 8));
        ScalerSetByte(PBC_E4_DPTX_CMU19, (BYTE)PDATA_WORD(2));

        // [5] 1: Enable SSC, 0: disable
        // [4] 0: 1st Order SDM, 1:2nd Order SDM
        // [3] 0: Triangular wave, 1: Square wave
        ScalerSetBit(PBC_D5_DPTX_CMU5, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
    }
    else
    {
        // Disable SSC
        ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT5, 0x00);
    }
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
}

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
//--------------------------------------------------
// Description  : Settings for Dp Tx Digital Phy
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPhy(bit bOn)
{
    if(bOn == _ON)
    {
        // Set Dp Tx Digital Phy
        ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~_BIT4, _BIT4);

        // Enable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0xFF);
    }

    else
    {
        // Disable Digital Phy output
        ScalerSetByte(P38_8E_PHY0_TXBIST_02_H1, 0x00);

        // Reset Dp Tx Digital Phy
        ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~_BIT4, 0x00);
    }
}

//--------------------------------------------------
// Description  : Dp Tx PLL Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPLL(bit bOn)
{
    if(bOn == _ON)
    {
        // Enable Vby1 and DPTx Clock
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Power Up Dp Tx Vby1 PLL
        ScalerSetBit(P38_AD_PHY0_APHY_0D, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT3));

        // Set Dp DPLL Enable
        ScalerDisplayDPTxPLLPower(_ON);

        // Power Up Dp Tx PLL for LCLK
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT6, _BIT6);
    }

    else
    {
        // Power Down Dp Tx PLL for LCLK
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT6, 0x00);

        // Set Dp DPLL Disable
        ScalerDisplayDPTxPLLPower(_OFF);

        // Power Down Dp Tx Vby PLL
        ScalerSetBit(P38_AD_PHY0_APHY_0D, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

        // Disable Vby1 and DPTx Clock
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~(_BIT1 | _BIT0), 0x00);
    }
}

//--------------------------------------------------
// Description  : DP DPLL Power COntrol.
// Input Value  : ucOn    --> ON/OFF.
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPLLPower(BYTE ucOn)
{
    if(ucOn == _ON)
    {
        ScalerDisplayDPTxSetPLLFreq(_DP_DPLL_TARGET_FREQ);
    }
    else
    {
        // Power Off DP DPLL
        ScalerDisplayDPTxSetPLLReset();
    }
}

//--------------------------------------------------
// Description  : Reset DP DPLL Setting, Enable DP DPLL Spread Spectrum Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxSetPLLReset(void)
{
    // Power Down DP DPLL
    ScalerSetBit(PBE_03_DPLL_WD, ~_BIT0, _BIT0);

    // Reset DP DPLL M Code (LSB)
    ScalerSetByte(PBE_00_DPLL_M, 0x00);

    // Reset DP DPLL M, N Code(MSB)
    ScalerSetByte(PBE_10_DPLL_M_N_MSB, 0x00);

    // Reset DP DPLL N Code(LSB)
    ScalerSetBit(PBE_01_DPLL_N, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set DP DPLL BPN
    ScalerSetBit(PBE_01_DPLL_N, ~_BIT6, 0x00);

    // Reset DP DPLL Output Divier
    ScalerSetBit(PBE_01_DPLL_N, ~(_BIT5 | _BIT4), 0x00);

    // DP DPLL Bypass Calibration
    ScalerSetBit(PBE_04_DPLL_CAL, ~_BIT5, _BIT5);

    // Disable DP DPLL Calibration Mode
    ScalerSetBit(PBE_04_DPLL_CAL, ~(_BIT4 | _BIT3 | _BIT2), 0x00);

    // Disable DP DPLL WD Reset, DPLL WD Set Normal, DPLL Freq Tuning Enable
    ScalerSetBit(PBE_03_DPLL_WD, ~(_BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT3 | (_DPLL_VCORSTB_NORMAL_VALUE << 1));

    // Enable DDS Spread Spectrum Output
    ScalerSetBit(PBE_08_FIXED_LAST_LINE_CTRL, ~_BIT0, _BIT0);

    // Enable DP DPLL Phase Swallow, Set LDO
    ScalerSetBit(PBE_0E_DPLL_LDO, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
}

//--------------------------------------------------
// Description  : Set display clock (Dclk)/display port clk(DPclk) frequency in kHz
// Input Value  : ulFreq    --> Target Dclk/DPclk frequency
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxSetPLLFreq(DWORD ulFreq)
{
    BYTE ucTemp = 0;
    WORD usMcode = 0;

    // Enable DDS Spread Spectrum Output
    ScalerSetBit(PBE_08_FIXED_LAST_LINE_CTRL, ~_BIT0, _BIT0);

    // Because div 2 is delete (div2 of MPLL no control register), but initial output div we set div8
    usMcode = ulFreq * 8 * 2 * 16 / ((DWORD)_EXT_XTAL * 15);

    // MPLL_VCO_clk_now
    PDATA_DWORD(0) = ulFreq * 16 / 15;

    // ----------- Previous Select Band & Div Alg. -----------
    // pData[15]: [5:4]=DPLL_O[1:0],[1:0]=DPLL VCO band
    PDATA_DWORD(1) = PDATA_DWORD(0) * 8;

    if(PDATA_DWORD(1) <= _DP_DPLL_BOUNDRY_0)      // 600000
    {
        pData[15] = ((3 << 4) | (2));
    }
    else if(PDATA_DWORD(1) <= _DP_DPLL_BOUNDRY_1) // 1200000
    {
        pData[15] = ((2 << 4) | (2));
    }
    else if(PDATA_DWORD(1) <= _DP_DPLL_BOUNDRY_2) // 2400000
    {
        pData[15] = ((1 << 4) | (2));
    }
    else
    {
        pData[15] = ((0 << 4) | (2));
    }
    // ---------------------------------

    switch(((pData[15] & 0x30) >> 4))
    {
        case 0:

            pData[0] = 8;
            break;

        case 1:

            pData[0] = 4;
            break;

        case 2:

            pData[0] = 2;
            break;

        case 3:

            pData[0] = 1;
            break;

        default:

            break;
    }

    usMcode = (usMcode + (pData[0] / 2)) / pData[0];

    // Manual set MPLL VCO band
    ScalerSetBit(PBE_04_DPLL_CAL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((pData[15] & 0x03) << 6) | _BIT5);

    // Set M Code
    ScalerSetByte(PBE_00_DPLL_M, (usMcode - 2));

    // Set N Code & Output divider
    ScalerSetByte(PBE_01_DPLL_N, (pData[15] & 0x30));

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Old Formula : Icp * N_Code / M_Code = 0.5 * Fxtal / 27MHz (for xtal not 27MHz)               //
    // Icp set 2.5uA, 5uA, 7.5uA, 10uA......                                                        //
    // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
    // If VCO band = 'b00, Icp = (700 * M * 2 * pi) / (778 * 0x01C1[7:5]).                          //
    // If VCO band = 'b01, Icp = (700 * M * 2 * pi) / (1340 * 0x01C1[7:5]).                         //
    // If VCO band = 'b10, Icp = (700 * M * 2 * pi) / (1880 * 0x01C1[7:5]).                         //
    // If VCO band = 'b11, Icp = (700 * M * 2 * pi) / (2340 * 0x01C1[7:5]).                         //
    // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
    // Assume MPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
    // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
    //////////////////////////////////////////////////////////////////////////////////////////////////
    switch((pData[15] & 0x03))
    {
        case 0:

            PDATA_DWORD(0) = 778;
            break;

        case 1:

            PDATA_DWORD(0) = 1340;
            break;

        case 2:

            PDATA_DWORD(0) = 1880;
            break;

        case 3:

            PDATA_DWORD(0) = 2340;
            break;

        default:

            break;
    }
    PDATA_DWORD(0) = (DWORD)usMcode * 700 * 628 * 20 / PDATA_DWORD(0) / ((7 + (ScalerGetBit(PBE_02_DPLL_CRNT, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);
    pData[1] = (PDATA_DWORD(0) + 25) / 50;
    pData[1] -= (pData[1] == 0) ? 0 : 1;

    // Set Current Control
    ScalerSetByte(PBE_02_DPLL_CRNT, (0x78 | (pData[1] & 0x07)));

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PBE_03_DPLL_WD, ~_BIT1, (_DPLL_VCORSTB_NORMAL_VALUE << 1));

    // Power up DP DPLL
    ScalerSetBit(PBE_03_DPLL_WD, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT0), (_BIT4 | _BIT3));
    for(ucTemp = 0; ucTemp < 20; ucTemp++)
    {
        Delay5us(g_ucDelay5usN);
    }

    // Reset PFD, LPF
    ScalerSetBit(PBE_03_DPLL_WD, ~_BIT5, _BIT5);
    Delay5us(g_ucDelay5usN);
    ScalerSetBit(PBE_03_DPLL_WD, ~_BIT5, 0x00);

    // Calculate DP DPLL Output Freq. According to current Settings
    PDATA_DWORD(0) = (DWORD)_EXT_XTAL * 1000 / (1 << ((pData[15] & 0x30) >> 4)) * usMcode / 2;

    // Offset resolution (DPclk / 2^15) in Hz
    PDATA_DWORD(1) = (PDATA_DWORD(0) >> 15);

    // Target frequency of DPclk in Hz
    usMcode = (PDATA_DWORD(0) - (ulFreq * 1000)) / PDATA_DWORD(1);
    usMcode = usMcode & 0x0FFF;

    // Set DP Dpll Offset
    ScalerSetBit(PBE_05_DCLK_FINE_TUNE_OFFSET_MSB, ~0x0F, HIBYTE(usMcode) & 0x0F); // 0xF0
    ScalerSetByte(PBE_06_DCLK_FINE_TUNE_OFFSET_LSB, LOBYTE(usMcode));
}

//--------------------------------------------------
// Description  : Dp Tx Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxPower(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up Dp Tx Digital Block: reg_en
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT7, _BIT7);

        // Power Up Dp Tx Analog Block
        ScalerSetBit(P38_A0_PHY0_APHY_00, ~_BIT7, _BIT7);
    }

    else
    {
        // Power Down Dp Tx Analog Block
        ScalerSetByte(P38_A1_PHY0_APHY_01, 0x00);

        // Power Down Dp Tx Analog Block
        ScalerSetBit(P38_A0_PHY0_APHY_00, ~_BIT7, 0x00);

        // Power Down Dp Tx Digital Block
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Dp Tx VBy1 Link Rate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxSetLinkRate(void)
{
#if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)
#if(_DISPLAY_DP_TX_PORT_2 == _ON)
    pData[0] = GET_DISPLAY_DP_TX2_LINK_RATE();
#else
    pData[0] = GET_DISPLAY_DP_TX1_LINK_RATE();
#endif
#else
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
    pData[0] = GET_DISPLAY_DP_TX1_LINK_RATE();
#else
    pData[0] = GET_DISPLAY_DP_TX2_LINK_RATE();
#endif

#endif // End of #if(_PANEL_DPTX_LINK_SEQUENCE_SWAP == _OFF)

    switch(pData[0])
    {
        case _DP_LINK_HBR:

            // Set Vby1 M code and N code: M dependent on Dp Tx link rate, M = 5, N = 4, PLL Pre-divider = 1
            ScalerSetBit(P38_AF_PHY0_APHY_0F, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT2 | _BIT1));

            // Vbyone Analog TX Bandwidth
            ScalerSetBit(P38_AE_PHY0_APHY_0E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT0));

            // DPLL Bandwidth
            ScalerSetBit(PBE_02_DPLL_CRNT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1 | _BIT0));

            // PLL VCO LDO,1V regulator
            ScalerSetBit(P38_B0_PHY0_APHY_10, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3 | _BIT2));

            break;

        default:

            // Set Vby1 M code and N code: M dependent on Dp Tx link rate, M = 3, N = 4, PLL Pre-divider = 2
            ScalerSetBit(P38_AF_PHY0_APHY_0F, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT3 | _BIT1));

            // Vbyone Analog TX Bandwidth
            ScalerSetBit(P38_AE_PHY0_APHY_0E, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            // DPLL Bandwidth
            ScalerSetBit(PBE_02_DPLL_CRNT, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT3 | _BIT1));

            // PLL VCO LDO,1V regulator
            ScalerSetBit(P38_B0_PHY0_APHY_10, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT3 | _BIT2));

            break;
    }
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Z0 Tunning
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxSetZ0(void)
{
    // Auto tunning set
    ScalerSetBit(P38_AB_PHY0_APHY_0B, ~_BIT6, _BIT6);

    // Tunning power on
    ScalerSetBit(P38_AB_PHY0_APHY_0B, ~_BIT7, _BIT7);

    // Wait for auto trimming stop, time-consuming ~ 1ms
    ScalerTimerDelayXms(2);

    // Tunning power off
    ScalerSetBit(P38_AB_PHY0_APHY_0B, ~_BIT7, 0x00);
}

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
//--------------------------------------------------
// Description  : DP Tx AuxInitial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx1AuxInitial(void)
{
    // Power Down Aux CH
    ScalerSetBit(P9F_A0_AUX_TX_CTRL, ~_BIT0, 0x00);

    // Setting Aux
    ScalerDisplayDPTx1AuxPHYSet(_DISPLAY_DP_TX_AUX_DIFF_MODE);

    // Set Aux Timeout
    ScalerSetByte(P9F_A1_AUX_TIMEOUT, 0x95);

    // Sync end Pattern Error Handle Disable
    ScalerSetBit(P9F_F6_AUX_DIG_PHY8, ~_BIT1, _BIT1);

    // Power On Aux CH
    ScalerSetBit(P9F_A0_AUX_TX_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Dp Tx Aux PHY Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1AuxPHYSet(BYTE ucMode)
{
    if(ucMode == _DISPLAY_DP_TX_AUX_SINGLE_MODE)
    {
        // Set Aux Tx LDO = 1.05V
        ScalerSetBit(P9F_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Set ADJR P
        ScalerSetBit(P9F_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Single End Mode and Enlarge Z0-P
        ScalerSetBit(P9F_62_AUX_2, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

        // Enable Enlarge Z0-N and Set ADJR-N = 0
        ScalerSetBit(P9F_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Set TX ADJR-P and ADJR-N
        ScalerSetByte(P9F_67_DIG_TX_03, 0x00);
    }
    else
    {
        // Set Aux Tx LDO = 0.9V
        ScalerSetBit(P9F_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Set ADJR P
        ScalerSetBit(P9F_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        // Disable Single End Mode and Enlarge Z0-P
        ScalerSetBit(P9F_62_AUX_2, ~(_BIT5 | _BIT0), 0x00);

        // Disable Enlarge Z0-N and Set ADJR N
        ScalerSetBit(P9F_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        // TX Z0 hand mode setting
        ScalerSetByte(P9F_67_DIG_TX_03, 0x88);
    }
}

//--------------------------------------------------
// Description  : DP Tx Aux Write
// Input Value  : ucCommand --> Aux Write Command
//                ucHighAddress --> High Byte of  Aux Write Address
//                ucMidAddress --> Middle Byte of  Aux Write Address
//                ucLowAddress --> Low Byte of  Aux Write Address
//                ucLength --> Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of Aux Write
// Output Value : TRUE --> Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTx1AuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    BYTE ucDataCount = 0;
    BYTE ucWriteRetryNum = 0;

    // Enable Timeout Retry
    ScalerSetBit(P9F_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

    // Reset FIFO
    ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // CLR Flag
    ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

    // Disable Address only transaction
    ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(P9F_A4_AUXTX_REQ_CMD, ucCommandAddrH);
    ScalerSetByte(P9F_A5_AUXTX_REQ_ADDR_M, ucAddrM);
    ScalerSetByte(P9F_A6_AUXTX_REQ_ADDR_L, ucAddrL);

    // Check Length
    if(ucLength == 0)
    {
        ucLength = 1;
    }
    else if(ucLength > 16)
    {
        ucLength = 16;
    }

    // Setting AUX Write Length : TX_LEN = ucLength-1
    ScalerSetByte(P9F_A7_AUXTX_REQ_LEN, (ucLength - 1));

    // Write Data to Buffer
    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
    {
        ScalerSetByte(P9F_A8_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
    }

    // Reset AUX Start Bit
    ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

    // Enable Aux to Start Write
    ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

    while(ucWriteRetryNum < 7)
    {
        // Delay 400us
        for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
        {
            Delay5us(g_ucDelay5usN);
        }

        // Polling AUX Done Bit (Delay 25 Loop = 175us)
        for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
        {
            Delay5us(g_ucDelay5usN);

            if(ScalerGetBit(P9F_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
            {
                // Reply Error or Nack or Command is not ACK
                if((ScalerGetBit(P9F_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit(P9F_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                {
                    // CLR Flag
                    ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Write Data to Buffer
                    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
                    {
                        ScalerSetByte(P9F_A8_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
                    }

                    // Reset AUX Start Bit
                    ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                    // Enable Aux to Start Write
                    ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

                    break;
                }
                else
                {
                    // Disable Timeout Retry
                    ScalerSetBit(P9F_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    return _TRUE;
                }
            }
            else
            {
                // HW Retry Times Reaches RETRY_NUM
                if(ScalerGetBit(P9F_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                {
                    // Disable Timeout Retry
                    ScalerSetBit(P9F_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    return _FALSE;
                }
            }
        }

        // Increasing Retry Num
        ucWriteRetryNum += 1;
    }

    // Disable Timeout Retry
    ScalerSetBit(P9F_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset FIFO
    ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Aux Read
// Input Value  : ucCommand --> Aux Read Command
//                ucHighAddress --> High Byte of  Aux Read Address
//                ucMidAddress --> Middle Byte of  Aux Read Address
//                ucLowAddress --> Low Byte of  Aux Read Address
//                ucLength --> Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of Aux Read
// Output Value : TRUE --> Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTx1AuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucCheckLength = 0;
    BYTE ucOffsetLength = 0;

    // Enable AUX FW Handle Mode
    ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5), _BIT5);

    // Disable Address only transaction
    ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT7, 0x00);

    do
    {
        ucReadRetryNum = 0;

        // Enable Retry Mechanism
        ScalerSetBit(P9F_B0_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Timeout HW Retry
        ScalerSetBit(P9F_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Setting DPCD Read Address
        ScalerSetByte(P9F_A4_AUXTX_REQ_CMD, ucCommandAddrH);
        ScalerSetByte(P9F_A5_AUXTX_REQ_ADDR_M, ucAddrM);
        ScalerSetByte(P9F_A6_AUXTX_REQ_ADDR_L, (ucAddrL + ucOffsetLength));

        ucLength = ucLength - ucOffsetLength;

        if(ucLength == 0)
        {
            ucLength = 1;
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        // Set Read Length : TX_LEN = ucLength-1
        ScalerSetByte(P9F_A7_AUXTX_REQ_LEN, (ucLength - 1));

        // Reset AUX Start Bit
        ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        // Enable Aux to Start Read
        ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay 400us
            for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
            {
                Delay5us(g_ucDelay5usN);
            }

            // Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(P9F_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((ScalerGetBit(P9F_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit(P9F_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Reset AUX Start Bit
                        ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                        // Enable Aux to Start Read
                        ScalerSetBit(P9F_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ucCheckLength = ScalerGetBit(P9F_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        ucOffsetLength += ucCheckLength;

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = ScalerGetByte(P9F_AA_AUX_REPLY_DATA);
                            pucReadArray++;
                        }

                        if(ucCheckLength == ucLength)
                        {
                            // Disable Timeout Retry
                            ScalerSetBit(P9F_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            return _TRUE;
                        }
                    }

                    break;
                }
                else
                {
                    // HW Retry Times Reaches RETRY_NUM
                    if(ScalerGetBit(P9F_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        ScalerSetBit(P9F_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum += 1;
        }
        while((ucReadRetryNum < 7) && (ScalerGetBit(P9F_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00));
    }
    while((ucCheckLength != ucLength) && (ucReadRetryNum < 7));

    // Disable Timeout Retry
    ScalerSetBit(P9F_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte(P9F_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    ScalerSetBit(P9F_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Hpd Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx1HpdInitial(void)
{
    // Set HPD 1ms Timer to  2ms
    ScalerSetBit(P9E_73_HPD_TIMER1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
    ScalerSetByte(P9E_75_HPD_TIMER3, 0x2C);

    // Set HPD 10ms Timer to  2ms
    ScalerSetByte(P9E_78_HPD_TIMER6, 0x0D);
    ScalerSetByte(P9E_79_HPD_TIMER7, 0x2C);

    // Clear HPD IRQ Flag
    ScalerSetByte(P9E_71_HPD_IRQ, 0xFE);

    // Enable HPD Detection
    ScalerSetBit(P9E_70_HPD_CTRL, ~_BIT7, _BIT7);

    // Disable Short IRQ and Disable Long IRQ
    ScalerSetByte(P9E_72_HPD_IRQ_EN, 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis)
{
    BYTE ucIndex = 0x00;

    ucVoltageSwing = ucVoltageSwing;

    ucPreEmphasis = ucPreEmphasis;

    ucIndex = (_PANEL_DPTX_SWING_LEVEL * 4 + _PANEL_DPTX_PREEMPHASIS_LEVEL) * 2;

    switch(enumLaneX)
    {
        case _DISPLAY_DP_TX_LANE_0: // VTX_lane0

            if(ucIndex == 0)
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT7, 0x00);
            }
            else
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT7, _BIT7);
            }

            // Pre-emphasis
            ScalerSetBit(P38_A3_PHY0_APHY_03, ~(_BIT7 | _BIT6 | _BIT5), (tVBY1_DRV_TABLE[ucIndex + 1] << 5));

            // Driving current
            ScalerSetBit(P38_A7_PHY0_APHY_07, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (tVBY1_DRV_TABLE[ucIndex + 0] << 4));

            break;

        case _DISPLAY_DP_TX_LANE_1: // VTX_lane1

            if(ucIndex == 0)
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT6, 0x00);
            }
            else
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT6, _BIT6);
            }

            // Pre-emphasis
            ScalerSetBit(P38_A3_PHY0_APHY_03, ~(_BIT4 | _BIT3 | _BIT2), (tVBY1_DRV_TABLE[ucIndex + 1] << 2));

            // Driving current
            ScalerSetBit(P38_A7_PHY0_APHY_07, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (tVBY1_DRV_TABLE[ucIndex + 0]));

            break;

        case _DISPLAY_DP_TX_LANE_2: // VTX_lane2

            if(ucIndex == 0)
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT5, 0x00);
            }
            else
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT5, _BIT5);
            }

            // Pre-emphasis
            ScalerSetBit(P38_A4_PHY0_APHY_04, ~(_BIT7 | _BIT6 | _BIT5), (tVBY1_DRV_TABLE[ucIndex + 1] << 5));

            // Driving current
            ScalerSetBit(P38_A8_PHY0_APHY_08, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (tVBY1_DRV_TABLE[ucIndex + 0] << 4));

            break;

        case _DISPLAY_DP_TX_LANE_3: // VTX_lane3

            if(ucIndex == 0)
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT4, 0x00);
            }
            else
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT4, _BIT4);
            }

            // Pre-emphasis
            ScalerSetBit(P38_A4_PHY0_APHY_04, ~(_BIT4 | _BIT3 | _BIT2), (tVBY1_DRV_TABLE[ucIndex + 1] << 2));

            // Driving current
            ScalerSetBit(P38_A8_PHY0_APHY_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (tVBY1_DRV_TABLE[ucIndex + 0]));

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1SignalInitialSetting(void)
{
#if(_PANEL_DPTX_LANE_PN_SWAP == _ENABLE)
    // Set Swap For Lane PN
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT0, _BIT0);
#else
    // Set No Swap For Lane PN
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT0, 0x00);
#endif

#if (_PANEL_DPTX_LANE_SWAP == _ENABLE)
    // Set Lane Swap for MAC0
    ScalerSetByte(P9C_13_DPTX_SFIFO_LANE_SWAP1, 0xE4);

    // Lane 0/1/2/3 Skew Setting
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((_DISPLAY_DP_TX_SKEW_LANE3 << 3) | _DISPLAY_DP_TX_SKEW_LANE2));
    ScalerSetBit(P38_86_PHY0_TXBIST_00_H1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((_DISPLAY_DP_TX_SKEW_LANE1 << 5) | (_DISPLAY_DP_TX_SKEW_LANE0 << 2)));
#else
    // Set Lane Non-Swap for MAC0
    ScalerSetByte(P9C_13_DPTX_SFIFO_LANE_SWAP1, 0x1B);

    // Lane 0/1/2/3 Skew Setting
    ScalerSetBit(P38_85_PHY0_TXBIST_00_H2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((_DISPLAY_DP_TX_SKEW_LANE0 << 3) | _DISPLAY_DP_TX_SKEW_LANE1));
    ScalerSetBit(P38_86_PHY0_TXBIST_00_H1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), ((_DISPLAY_DP_TX_SKEW_LANE2 << 5) | (_DISPLAY_DP_TX_SKEW_LANE3 << 2)));
#endif // End of #if(_PANEL_DPTX_LANE_SWAP ==  _ENABLE)

    // Set Voltage Swing and Pre-emphasis Level 0
    ScalerDisplayDPTx1SignalReset();

    // Initial Bist Mode
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), _BIT2);

    // Disable Scrambling
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, _BIT1);

    // DPTX Power On TX Driver and Enable Output
    switch(GET_DISPLAY_DP_TX1_LANE_NUM())
    {
        case _DP_ONE_LANE:

            // Set Mac 1 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT0);

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

            // Lane:0 power on
            ScalerSetBit(P38_A1_PHY0_APHY_01, ~_BIT7, _BIT7);

            break;

        case _DP_TWO_LANE:

            // Set Mac 2 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT1);

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

            // Lane:0-1 power on
            ScalerSetBit(P38_A1_PHY0_APHY_01, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            break;

        case _DP_FOUR_LANE:

            // Set Mac 4 Lane
            ScalerSetBit(P9C_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Dig PHY Set
            ScalerSetBit(P9C_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Lane:0-3 power on
            ScalerSetBit(P38_A1_PHY0_APHY_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Power Off DPTX Lane
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx1LanePowerOff(void)
{
    // Lane:0-3 Power Down
    ScalerSetBit(P38_A1_PHY0_APHY_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
}

//--------------------------------------------------
// Description  : Set TP2 Pattern Type
// Input Value  : None
// Output Value : _DISPLAY_DP_TX_TP_2 or _DISPLAY_DP_TX_TP_3
//--------------------------------------------------
EnumDisplayDPTxTrainPattern ScalerDisplayDPTx1SetTp2PatternType(void)
{
    // Main Link Switch to TPS2 Pattern
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, 0x00);

    return _DISPLAY_DP_TX_TP_2;
}
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
//--------------------------------------------------
// Description  : DP Tx AuxInitial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx2AuxInitial(void)
{
    // Power Down Aux CH
    ScalerSetBit(P9D_A0_AUX_TX_CTRL, ~_BIT0, 0x00);

    // Setting Aux
    ScalerDisplayDPTx2AuxPHYSet(_DISPLAY_DP_TX_AUX_DIFF_MODE);

    // Set Aux Timeout
    ScalerSetByte(P9D_A1_AUX_TIMEOUT, 0x95);

    // Sync end Pattern Error Handle Disable
    ScalerSetBit(P9D_F6_AUX_DIG_PHY8, ~_BIT1, _BIT1);

    // Power On Aux Channel
    ScalerSetBit(P9D_A0_AUX_TX_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Dp Tx Aux PHY Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2AuxPHYSet(BYTE ucMode)
{
    if(ucMode == _DISPLAY_DP_TX_AUX_SINGLE_MODE)
    {
        // Set Aux Tx LDO = 1.05V
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Set ADJR P
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Single End Mode and Enlarge Z0-P
        ScalerSetBit(P9D_62_AUX_2, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

        // Enable Enlarge Z0-N and Set ADJR-N = 0
        ScalerSetBit(P9D_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);

        // Set TX ADJR-P and ADJR-N
        ScalerSetByte(P9D_67_DIG_TX_03, 0x00);
    }
    else
    {
        // Set Aux Tx LDO = 0.9V
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Set ADJR P
        ScalerSetBit(P9D_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        // Disable Single End Mode and Enlarge Z0-P
        ScalerSetBit(P9D_62_AUX_2, ~(_BIT5 | _BIT0), 0x00);

        // Disable Enlarge Z0-N and Set ADJR N
        ScalerSetBit(P9D_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

        // TX Z0 hand mode setting
        ScalerSetByte(P9D_67_DIG_TX_03, 0x88);
    }
}

//--------------------------------------------------
// Description  : DP Tx Aux Write
// Input Value  : ucCommand --> Aux Write Command
//                ucHighAddress --> High Byte of  Aux Write Address
//                ucMidAddress --> Middle Byte of  Aux Write Address
//                ucLowAddress --> Low Byte of  Aux Write Address
//                ucLength --> Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of Aux Write
// Output Value : TRUE --> Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTx2AuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    BYTE ucDataCount = 0;
    BYTE ucWriteRetryNum = 0;

    // Enable Timeout Retry
    ScalerSetBit(P9D_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

    // Reset FIFO
    ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // CLR Flag
    ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

    // Disable Address only transaction
    ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(P9D_A4_AUXTX_REQ_CMD, ucCommandAddrH);
    ScalerSetByte(P9D_A5_AUXTX_REQ_ADDR_M, ucAddrM);
    ScalerSetByte(P9D_A6_AUXTX_REQ_ADDR_L, ucAddrL);

    // Check Length
    if(ucLength == 0)
    {
        ucLength = 1;
    }
    else if(ucLength > 16)
    {
        ucLength = 16;
    }

    // Setting AUX Write Length : TX_LEN = ucLength-1
    ScalerSetByte(P9D_A7_AUXTX_REQ_LEN, (ucLength - 1));

    // Write Data to Buffer
    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
    {
        ScalerSetByte(P9D_A8_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
    }

    // Reset AUX Start Bit
    ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

    // Enable Aux to Start Write
    ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

    while(ucWriteRetryNum < 7)
    {
        // Delay 400us
        for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
        {
            Delay5us(g_ucDelay5usN);
        }

        // Polling AUX Done Bit (Delay 25 Loop = 175us)
        for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
        {
            Delay5us(g_ucDelay5usN);

            if(ScalerGetBit(P9D_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
            {
                // Reply Error or Nack or Command is not ACK
                if((ScalerGetBit(P9D_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit(P9D_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                {
                    // CLR Flag
                    ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Write Data to Buffer
                    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
                    {
                        ScalerSetByte(P9D_A8_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
                    }

                    // Reset AUX Start Bit
                    ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                    // Enable Aux to Start Write
                    ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

                    break;
                }
                else
                {
                    // Disable Timeout Retry
                    ScalerSetBit(P9D_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    return _TRUE;
                }
            }
            else
            {
                // HW Retry Times Reaches RETRY_NUM
                if(ScalerGetBit(P9D_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                {
                    // Disable Timeout Retry
                    ScalerSetBit(P9D_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    return _FALSE;
                }
            }
        }

        // Increasing Retry Num
        ucWriteRetryNum += 1;
    }

    // Disable Timeout Retry
    ScalerSetBit(P9D_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset FIFO
    ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Aux Read
// Input Value  : ucCommand --> Aux Read Command
//                ucHighAddress --> High Byte of  Aux Read Address
//                ucMidAddress --> Middle Byte of  Aux Read Address
//                ucLowAddress --> Low Byte of  Aux Read Address
//                ucLength --> Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of Aux Read
// Output Value : TRUE --> Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTx2AuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucCheckLength = 0;
    BYTE ucOffsetLength = 0;

    // Enable AUX FW Handle Mode
    ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5), _BIT5);

    // Disable Address only transaction
    ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT7, 0x00);

    do
    {
        ucReadRetryNum = 0;

        // Enable Retry Mechanism
        ScalerSetBit(P9D_B0_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Timeout HW Retry
        ScalerSetBit(P9D_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Setting DPCD Read Address
        ScalerSetByte(P9D_A4_AUXTX_REQ_CMD, ucCommandAddrH);
        ScalerSetByte(P9D_A5_AUXTX_REQ_ADDR_M, ucAddrM);
        ScalerSetByte(P9D_A6_AUXTX_REQ_ADDR_L, (ucAddrL + ucOffsetLength));

        ucLength = ucLength - ucOffsetLength;

        if(ucLength == 0)
        {
            ucLength = 1;
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        // Set Read Length : TX_LEN = ucLength-1
        ScalerSetByte(P9D_A7_AUXTX_REQ_LEN, (ucLength - 1));

        // Reset AUX Start Bit
        ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        // Enable Aux to Start Read
        ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay 400us
            for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
            {
                Delay5us(g_ucDelay5usN);
            }

            // Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(P9D_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((ScalerGetBit(P9D_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit(P9D_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Reset AUX Start Bit
                        ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                        // Enable Aux to Start Read
                        ScalerSetBit(P9D_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ucCheckLength = ScalerGetBit(P9D_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        ucOffsetLength += ucCheckLength;

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = ScalerGetByte(P9D_AA_AUX_REPLY_DATA);
                            pucReadArray++;
                        }

                        if(ucCheckLength == ucLength)
                        {
                            // Disable Timeout Retry
                            ScalerSetBit(P9D_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            return _TRUE;
                        }
                    }

                    break;
                }
                else
                {
                    // HW Retry Times Reaches RETRY_NUM
                    if(ScalerGetBit(P9D_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        ScalerSetBit(P9D_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum += 1;
        }
        while((ucReadRetryNum < 7) && (ScalerGetBit(P9D_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00));
    }
    while((ucCheckLength != ucLength) && (ucReadRetryNum < 7));

    // Disable Timeout Retry
    ScalerSetBit(P9D_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte(P9D_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    ScalerSetBit(P9D_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Hpd Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTx2HpdInitial(void)
{
    // Set HPD 1ms Timer to  2ms
    ScalerSetBit(P9C_73_HPD_TIMER1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
    ScalerSetByte(P9C_75_HPD_TIMER3, 0x2C);

    // Set HPD 10ms Timer to  2ms
    ScalerSetByte(P9C_78_HPD_TIMER6, 0x0D);
    ScalerSetByte(P9C_79_HPD_TIMER7, 0x2C);

    // Clear HPD IRQ Flag
    ScalerSetByte(P9C_71_HPD_IRQ, 0xFE);

    // Enable HPD Detection
    ScalerSetBit(P9C_70_HPD_CTRL, ~_BIT7, _BIT7);

    // Disable Short IRQ and Disable Long IRQ
    ScalerSetByte(P9C_72_HPD_IRQ_EN, 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis)
{
    BYTE ucIndex = 0x00;

    ucVoltageSwing = ucVoltageSwing;

    ucPreEmphasis = ucPreEmphasis;

    ucIndex = (_PANEL_DPTX_SWING_LEVEL * 4 + _PANEL_DPTX_PREEMPHASIS_LEVEL) * 2;

    switch(enumLaneX)
    {
        case _DISPLAY_DP_TX_LANE_0: // VTX_lane4

            if(ucIndex == 0)
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT3, 0x00);
            }
            else
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT3, _BIT3);
            }

            // Pre-emphasis
            ScalerSetBit(P38_A5_PHY0_APHY_05, ~(_BIT7 | _BIT6 | _BIT5), (tVBY1_DRV_TABLE[ucIndex + 1] << 5));

            // Driving current
            ScalerSetBit(P38_A9_PHY0_APHY_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (tVBY1_DRV_TABLE[ucIndex + 0] << 4));

            break;

        case _DISPLAY_DP_TX_LANE_1: // VTX_lane5

            if(ucIndex == 0)
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT2, 0x00);
            }
            else
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT2, _BIT2);
            }

            // Pre-emphasis
            ScalerSetBit(P38_A5_PHY0_APHY_05, ~(_BIT4 | _BIT3 | _BIT2), (tVBY1_DRV_TABLE[ucIndex + 1] << 2));

            // Driving current
            ScalerSetBit(P38_A9_PHY0_APHY_09, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (tVBY1_DRV_TABLE[ucIndex + 0]));

            break;

        case _DISPLAY_DP_TX_LANE_2: // VTX_lane6

            if(ucIndex == 0)
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT1, 0x00);
            }
            else
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT1, _BIT1);
            }

            // Pre-emphasis
            ScalerSetBit(P38_A6_PHY0_APHY_06, ~(_BIT7 | _BIT6 | _BIT5), (tVBY1_DRV_TABLE[ucIndex + 1] << 5));

            // Driving current
            ScalerSetBit(P38_AA_PHY0_APHY_0A, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (tVBY1_DRV_TABLE[ucIndex + 0] << 4));

            break;

        case _DISPLAY_DP_TX_LANE_3: // VTX_lane7

            if(ucIndex == 0)
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT0, 0x00);
            }
            else
            {
                ScalerSetBit(P38_B1_PHY0_APHY_11, ~_BIT0, _BIT0);
            }

            // Pre-emphasis
            ScalerSetBit(P38_A6_PHY0_APHY_06, ~(_BIT4 | _BIT3 | _BIT2), (tVBY1_DRV_TABLE[ucIndex + 1] << 2));

            // Driving current
            ScalerSetBit(P38_AA_PHY0_APHY_0A, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (tVBY1_DRV_TABLE[ucIndex + 0]));

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2SignalInitialSetting(void)
{
#if(_PANEL_DPTX_LANE_PN_SWAP == _ENABLE)
    // Set Swap For Lane PN
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT0, _BIT0);
#else
    // Set No Swap For Lane PN
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT0, 0x00);
#endif

#if (_PANEL_DPTX_LANE_SWAP == _ENABLE)
    // Set Lane Swap for MAC0
    ScalerSetByte(P9E_13_DPTX_SFIFO_LANE_SWAP1, 0xE4);

    // Lane 0/1/2/3 Skew Setting
    ScalerSetBit(P38_86_PHY0_TXBIST_00_H1, ~(_BIT1 | _BIT0), (_DISPLAY_DP_TX_SKEW_LANE3 >> 1));
    ScalerSetByte(P38_87_PHY0_TXBIST_00_L2, ((_DISPLAY_DP_TX_SKEW_LANE3 << 7) | (_DISPLAY_DP_TX_SKEW_LANE2 << 4) | (_DISPLAY_DP_TX_SKEW_LANE1 << 1) | (_DISPLAY_DP_TX_SKEW_LANE0 >> 2)));
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT7 | _BIT6), (_DISPLAY_DP_TX_SKEW_LANE0 << 6));
#else
    // Set Lane Non-Swap for MAC0
    ScalerSetByte(P9E_13_DPTX_SFIFO_LANE_SWAP1, 0x1B);

    // Lane 0/1/2/3 Skew Setting
    ScalerSetBit(P38_86_PHY0_TXBIST_00_H1, ~(_BIT1 | _BIT0), (_DISPLAY_DP_TX_SKEW_LANE0 >> 1));
    ScalerSetByte(P38_87_PHY0_TXBIST_00_L2, ((_DISPLAY_DP_TX_SKEW_LANE0 << 7) | (_DISPLAY_DP_TX_SKEW_LANE1 << 4) | (_DISPLAY_DP_TX_SKEW_LANE2 << 1) | (_DISPLAY_DP_TX_SKEW_LANE3 >> 2)));
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT7 | _BIT6), (_DISPLAY_DP_TX_SKEW_LANE3 << 6));
#endif // End of #if(_PANEL_DPTX_LANE_SWAP ==  _ENABLE)

    // Set Voltage Swing and Pre-emphasis Level 0
    ScalerDisplayDPTx2SignalReset();

    // Initial Bist Mode
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT3 | _BIT2), _BIT2);

    // Disable Scrambling
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~_BIT1, _BIT1);

    // DPTX Power On TX Driver and Enable Output
    switch(GET_DISPLAY_DP_TX2_LANE_NUM())
    {
        case _DP_ONE_LANE:

            // Set Mac 1 Lane
            ScalerSetBit(P9E_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT0);

            // Dig PHY Set
            ScalerSetBit(P9E_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

            // Lane:0 power on
            ScalerSetBit(P38_A1_PHY0_APHY_01, ~_BIT3, _BIT3);

            break;

        case _DP_TWO_LANE:

            // Set Mac 2 Lane
            ScalerSetBit(P9E_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT1);

            // Dig PHY Set
            ScalerSetBit(P9E_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT5 | _BIT4));

            // Lane:0-1 power on
            ScalerSetBit(P38_A1_PHY0_APHY_01, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));


            break;

        case _DP_FOUR_LANE:

            // Set Mac 4 Lane
            ScalerSetBit(P9E_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Dig PHY Set
            ScalerSetBit(P9E_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Lane:0-3 power on
            ScalerSetBit(P38_A1_PHY0_APHY_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Power Off DPTX Lane
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTx2LanePowerOff(void)
{
    // Lane:4-7 Power Down
    ScalerSetBit(P38_A1_PHY0_APHY_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Set TP2 Pattern Type
// Input Value  : None
// Output Value : _DISPLAY_DP_TX_TP_2 or _DISPLAY_DP_TX_TP_3
//--------------------------------------------------
EnumDisplayDPTxTrainPattern ScalerDisplayDPTx2SetTp2PatternType(void)
{
    // Main Link Switch to TPS2 Pattern
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~_BIT5, 0x00);

    return _DISPLAY_DP_TX_TP_2;
}

//--------------------------------------------------
// Description  : Set Analog Phy Mux for TPS3 Pattern
// Input Value  : None
// Output Value : _ON or _OFF
//--------------------------------------------------
void ScalerDisplayDPTx2SetTps3PatternMux(bit bAphyMux)
{
    bAphyMux = bAphyMux;
}
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

#else
//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxInitial(void)
{
    // Setting Aux
    ScalerDisplayDPTxAuxPHYSet(_DISPLAY_DP_TX_AUX_DIFF_MODE);

    // Set Aux Timeout
    ScalerSetByte(PBD_A1_AUX_TIMEOUT, 0x95);

    // Power Down Aux CH
    ScalerSetBit(PBD_A0_AUX_TX_CTRL, ~_BIT0, 0x00);

    // Sync end Pattern Error Handle Disable
    ScalerSetBit(PBD_F6_AUX_DIG_PHY8, ~_BIT1, _BIT1);

    // Disable HPD Int.
    ScalerSetByte(PBB_72_HPD_IRQ_EN, 0x00);

    // Set HPD 0.45ms Timer to 2ms
    ScalerSetByte(PBB_73_HPD_TIMER1, 0x2D);
    ScalerSetByte(PBB_74_HPD_TIMER2, 0xFC);
    ScalerSetByte(PBB_75_HPD_TIMER3, 0x2C);

    // Set HPD 10ms Timer to  2ms
    ScalerSetByte(PBB_78_HPD_TIMER6, 0x0D);
    ScalerSetByte(PBB_79_HPD_TIMER7, 0x2C);

    // Enable HPD Detection
    ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, _BIT7);

    // Clear HPD IRQ Flag
    ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

    // Disable Downstream Z0 Detection
    ScalerSetBit(PBC_A2_DPTX_RCV_DET0, ~_BIT6, 0x00);

    // Set DP TX CLK divider
    ScalerSetByte(PBB_E0_DPTX_CLK_GEN, 0x21);

    // Enable Arbiter Stuffing and Framing
    ScalerSetBit(PBB_C9_ARBITER_CTRL, ~_BIT0, _BIT0);

    SET_DISPLAY_DP_TX_INPUT_COLOR_DEPTH(_PANEL_DISP_BIT_MODE);
    SET_DISPLAY_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
}

//--------------------------------------------------
// Description  : Dp Tx Read DPCD Rx Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTxLinkConfig(void)
{
    // Power On Aux CH
    ScalerSetBit(PBD_A0_AUX_TX_CTRL, ~_BIT0, _BIT0);

    // Read Sink Capability
    if(ScalerDisplayDPTxNativeAuxRead(0x00, 0x00, 0x00, 16, pData) == _FALSE)
    {
        return _FALSE;
    }

    // Check Sink Version
    if((pData[0] != _DP_VERSION_1_0) && (pData[0] != _DP_VERSION_1_1) && (pData[0] != _DP_VERSION_1_2))
    {
        pData[0] = _DP_VERSION_1_1;
    }

    // Set Sink Version
    SET_DISPLAY_DP_TX_DPCD_REV(pData[0]);

    if(pData[0] == _DP_VERSION_1_2)
    {
        // Check TP3 support
        if((pData[2] & _BIT6) == _BIT6)
        {
            SET_DISPLAY_DP_TX_TP3_SUPPORT();
        }
        else
        {
            CLR_DISPLAY_DP_TX_TP3_SUPPORT();
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX_TP3_SUPPORT();
    }

    if((pData[1] == _DP_LINK_RBR) || (pData[1] == _DP_LINK_HBR) || ((pData[0] == _DP_VERSION_1_2) && (pData[1] == _DP_LINK_HBR2)))
    {
        // Set Link Rate
        SET_DISPLAY_DP_TX_MAX_LINK_RATE(pData[1]);
    }
    else
    {
        // Set the Slowest Link Rate
        SET_DISPLAY_DP_TX_MAX_LINK_RATE(_DP_LINK_RBR);
    }

    // Set Lane Number
    SET_DISPLAY_DP_TX_LANE_NUM((pData[2] & 0x1F));

    // Set Enhanceed Framing
    SET_DISPLAY_DP_TX_ENHANCE_FRAMING((bit)(pData[2] & _BIT7));

    // Set Max Downspread
    SET_DISPLAY_DP_TX_DOWN_SPREAD((bit)(pData[3] & _BIT0));

    // Set Framing Change for eDP
    SET_DISPLAY_DP_TX_FRAMING_CHANGE_CAPABLE((bit)(pData[13] & _BIT1));

    // Set Alternate SR Capable for eDP
    SET_DISPLAY_DP_TX_ALTERNATE_SR_CAPABLE((bit)(pData[13] & _BIT0));

    return _TRUE;
}

//--------------------------------------------------
// Description  : Settings for Dp Tx Z0 Tunning
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayDPTxVideoStreamOutput(bit bOutput)
{
    if(bOutput == _ENABLE)
    {
        ScalerDisplayDPTxMeasureInputInfo();

        PDATA_DWORD(0) = 0;
        PDATA_DWORD(1) = 0x8000;
        PDATA_DWORD(2) = 0;

        // Mvid = Stream clk x Nvid / Link clk
        PDATA_DWORD(0) = ((DWORD)GET_D_CLK_FREQ() / 100) * PDATA_DWORD(1);
        PDATA_DWORD(0) /= ((GET_DISPLAY_DP_TX_SSCG_CONFIG() == _TRUE) ? ((DWORD)270 * GET_DISPLAY_DP_TX_LINK_RATE() * 9975 / 10000) : ((DWORD)270 * GET_DISPLAY_DP_TX_LINK_RATE()));

        // Debounce 10 times
        pData[12] = 0x0A;

        do
        {
            // Select HW mode for Mvid
            ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~_BIT7, _BIT7);

            ScalerTimerDelayXms(2);

            // Select HW mode for Mvid
            ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~_BIT7, 0x00);

            // Get Mvid From HW Mode
            PDATA_DWORD(2) = (((DWORD)ScalerGetByte(PBB_AF_MVID_AUTO_H) << 16) | ((DWORD)ScalerGetByte(PBB_B0_MVID_AUTO_M) << 8) | ScalerGetByte(PBB_B1_MVID_AUTO_L));

            // For RLE0779A/RL6449A disable auto Mvid is zero
            if(PDATA_DWORD(2) == 0)
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                ScalerSetByte(PBB_A9_MN_M_VID_H, pData[1]);
                ScalerSetByte(PBB_AA_MN_M_VID_M, pData[2]);
                ScalerSetByte(PBB_AB_MN_M_VID_L, pData[3]);

                break;
            }

            if(abs(PDATA_DWORD(0) - PDATA_DWORD(2)) < (PDATA_DWORD(0) >> 1))
            {
                // Set Mvid for HW mode
                ScalerSetByte(PBB_A9_MN_M_VID_H, pData[9]);
                ScalerSetByte(PBB_AA_MN_M_VID_M, pData[10]);
                ScalerSetByte(PBB_AB_MN_M_VID_L, pData[11]);

                break;
            }

            pData[12]--;

            if(pData[12] == 0x00)
            {
                // HW Auto Mvid is wrong Set Mvid for FW mode
                ScalerSetByte(PBB_A9_MN_M_VID_H, pData[1]);
                ScalerSetByte(PBB_AA_MN_M_VID_M, pData[2]);
                ScalerSetByte(PBB_AB_MN_M_VID_L, pData[3]);
            }
        }
        while(pData[12] != 0);

        // Set Nvid for FW mode
        ScalerSetByte(PBB_AC_MN_N_VID_H, pData[5]);
        ScalerSetByte(PBB_AD_MN_N_VID_M, pData[6]);
        ScalerSetByte(PBB_AE_MN_N_VID_L, pData[7]);

        // Set Mvid DB Direct Effective
        ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT6, 0x00);

        // Set Mvid DB for FW mode
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6), _BIT6);

        // Set MSA
        ScalerDisplayDPTxMSASetting();

        // Set TU Setting
        ScalerDisplayDPTxDisplayFormatSetting();

        // Clear FIFO Status
        ScalerSetByte(PBB_A4_PG_FIFO_CTRL, 0xFF);

        // Set Secondary Data Size => Should be Modified by Input Sec
        // HBlanking - Max Audio Packet Size - Blanking Overhead
        pData[0] = ScalerGetBit(PBB_D1_AUTO_HDEALY0, (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        pData[1] = ScalerGetByte(PBB_D2_AUTO_HDEALY1);

        // sec_end_cnt = h_blanking - max_audio_packet (lane_num, max_long_packet_cnt) - safe_margin
        // max_audio_packet = SS_SE + HEADER_ECC_BYTES / lane_num + [(max_long_packet_cnt+1) * (minimum packet payload + 4)] / lane_num.
        PDATA_WORD(0) = PDATA_WORD(0) - 2 - ((8 + 20) / GET_DISPLAY_DP_TX_LANE_NUM());

        ScalerSetByte(PBB_D4_ARBITER_SEC_END_CNT_HB, pData[0]);
        ScalerSetByte(PBB_D5_ARBITER_SEC_END_CNT_LB, pData[1]);

        // Main Link switch to VIDEO pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_VIDEO_PATTERN << 4));

        // Double buffer only by Vsync
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);
    }
    else
    {
        // Main Link switch to IDLE pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_IDLE_PATTERN << 4));

        // Double buffer only by Vsync
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);
    }
}

//--------------------------------------------------
// Description  : DP Tx Arbiter
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxDisplayFormatSetting(void)
{
    // Disable HW Auto Calculate H Delay
    ScalerSetBit(PBB_D3_LFIFO_WL_SET, ~_BIT7, 0x00);

    // Pixel Generation Block Reset
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT7, 0x00);

    // Get Bit Per Chrome
    switch(GET_DISPLAY_DP_TX_INPUT_COLOR_DEPTH())
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

    // step1: Cal vaild symbol in TU
    // Average TU = TU Size x (Stream_Clk x Byte of 1 pixel / Lane Number) / Link Rate
    PDATA_WORD(1) = ((GET_DISPLAY_DP_TX_SSCG_CONFIG() == _TRUE) ? ((DWORD)270 * GET_DISPLAY_DP_TX_LINK_RATE() * 9975 / 10000) : ((DWORD)270 * GET_DISPLAY_DP_TX_LINK_RATE()));
    PDATA_WORD(1) = ((DWORD)_DISPLAY_DP_TX_TU_SIZE * (((DWORD)(GET_D_CLK_FREQ() / 100) * 3 * pData[0]) / GET_DISPLAY_DP_TX_LANE_NUM())) / (PDATA_WORD(1));

    ScalerSetByte(PBB_CC_TU_SIZE, _DISPLAY_DP_TX_TU_SIZE);
    ScalerSetByte(PBB_CD_TU_DATA_SIZE0, (PDATA_WORD(1) >> 3));
    ScalerSetByte(PBB_CE_TU_DATA_SIZE1, (PDATA_WORD(1) & 0x07));

    PDATA_WORD(1) = ((DWORD)g_stDisplayDPTxTimingInfo.usHWidth * pData[0] * 3) / (GET_DISPLAY_DP_TX_LANE_NUM() * 8);
    PDATA_WORD(1) += ((bit)(((DWORD)g_stDisplayDPTxTimingInfo.usHWidth * pData[0] * 3) % (GET_DISPLAY_DP_TX_LANE_NUM() * 8)) ? 1 : 0);

    ScalerSetByte(PBB_CA_V_DATA_PER_LINE0, pData[2]);
    ScalerSetByte(PBB_CB_V_DATA_PER_LINE1, pData[3]);

    // step 3: Enable HW Auto Calculate H Delay
    ScalerSetBit(PBB_D3_LFIFO_WL_SET, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : DP Tx MSA Generation
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxMSASetting(void)
{
    // Reset MSA Generation Block and SEC Block
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT6, 0x00);

    // Set Htotal
    ScalerSetByte(PBB_B7_MN_STRM_ATTR_HTT_M, HIBYTE(g_stDisplayDPTxTimingInfo.usHTotal));
    ScalerSetByte(PBB_B8_MN_STRM_ATTR_HTT_L, LOBYTE(g_stDisplayDPTxTimingInfo.usHTotal));

    // Set Hstart
    ScalerSetByte(PBB_B9_MN_STRM_ATTR_HST_M, HIBYTE(g_stDisplayDPTxTimingInfo.usHStart));
    ScalerSetByte(PBB_BA_MN_STRM_ATTR_HST_L, LOBYTE(g_stDisplayDPTxTimingInfo.usHStart));

    // Set Hwidth
    ScalerSetByte(PBB_BB_MN_STRM_ATTR_HWD_M, HIBYTE(g_stDisplayDPTxTimingInfo.usHWidth));
    ScalerSetByte(PBB_BC_MN_STRM_ATTR_HWD_L, LOBYTE(g_stDisplayDPTxTimingInfo.usHWidth));

    // Set Hsyc
    ScalerSetByte(PBB_BD_MN_STRM_ATTR_HSW_M, HIBYTE(g_stDisplayDPTxTimingInfo.usHSWidth));
    ScalerSetByte(PBB_BE_MN_STRM_ATTR_HSW_L, LOBYTE(g_stDisplayDPTxTimingInfo.usHSWidth));

    // Set Vtotal
    ScalerSetByte(PBB_BF_MN_STRM_ATTR_VTTE_M, HIBYTE(g_stDisplayDPTxTimingInfo.usVTotal));
    ScalerSetByte(PBB_C0_MN_STRM_ATTR_VTTE_L, LOBYTE(g_stDisplayDPTxTimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(PBB_C1_MN_STRM_ATTR_VST_M, HIBYTE(g_stDisplayDPTxTimingInfo.usVStart));
    ScalerSetByte(PBB_C2_MN_STRM_ATTR_VST_L, LOBYTE(g_stDisplayDPTxTimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(PBB_C3_MN_STRM_ATTR_VHT_M, HIBYTE(g_stDisplayDPTxTimingInfo.usVHeight));
    ScalerSetByte(PBB_C4_MN_STRM_ATTR_VHT_L, LOBYTE(g_stDisplayDPTxTimingInfo.usVHeight));

    // Set Vsync
    ScalerSetByte(PBB_C5_MN_STRM_ATTR_VSW_M, HIBYTE(g_stDisplayDPTxTimingInfo.usVSWidth));
    ScalerSetByte(PBB_C6_MN_STRM_ATTR_VSW_L, LOBYTE(g_stDisplayDPTxTimingInfo.usVSWidth));

    // Set Color Space
    ScalerSetBit(PBB_B5_MSA_MISC0, ~(_BIT2 | _BIT1), (GET_DISPLAY_DP_TX_INPUT_COLOR_SPACE() << 1));

    // Set Color Depth
    ScalerSetBit(PBB_B5_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5), (GET_DISPLAY_DP_TX_INPUT_COLOR_DEPTH() << 5));

    // Set MISC1
    ScalerSetByte(PBB_B6_MN_STRM_ATTR_MISC1, 0x00);

    // MSA_DB = 1 and Bouble Buffer at V Blanking
    ScalerSetBit(PBB_B4_MSA_CTRL, ~(_BIT7 | _BIT6), _BIT7);
}

//--------------------------------------------------
// Description  : DP Tx Link Training
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxLinkTraining(void)
{
    // Set Dptx Link Training
    if(GET_DISPLAY_DP_TX_LINK_CONFIG() == _TRUE)
    {
        ScalerDisplayDPTxTPInitialSet();

        while((GET_DISPLAY_DP_TX_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_PASS) && (GET_DISPLAY_DP_TX_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_FAIL))
        {
            switch(GET_DISPLAY_DP_TX_LT_STATE())
            {
                case _DISPLAY_DP_TX_TRAINING_PATTERN1:

                    SET_DISPLAY_DP_TX_LT_RESULT(ScalerDisplayDPTxTrainPattern1());

                    if(GET_DISPLAY_DP_TX_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS)
                    {
                        SET_DISPLAY_DP_TX_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN2);
                    }
                    else if(GET_DISPLAY_DP_TX_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL)
                    {
                        SET_DISPLAY_DP_TX_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DISPLAY_DP_TX_TRAINING_PATTERN2:

                    SET_DISPLAY_DP_TX_LT_RESULT(ScalerDisplayDPTxTrainPattern2());

                    if(GET_DISPLAY_DP_TX_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS)
                    {
                        SET_DISPLAY_DP_TX_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }
                    else if(GET_DISPLAY_DP_TX_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL)
                    {
                        SET_DISPLAY_DP_TX_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN_END);
                    }

                    break;

                case _DISPLAY_DP_TX_TRAINING_PATTERN_END:

                    if(GET_DISPLAY_DP_TX_LT_RESULT() != _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS)
                    {
                        SET_DISPLAY_DP_TX_LT_RESULT(_DISPLAY_DP_TX_TRAINING_FAIL);
                    }
                    else
                    {
                        SET_DISPLAY_DP_TX_LT_RESULT(_DISPLAY_DP_TX_TRAINING_PASS);
                    }

                    ScalerDisplayDPTxTrainPatternEnd();

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
void ScalerDisplayDPTxTPInitialSet(void)
{
    // Panel DPTx Power Sequence Check Point
    PCB_DPTX_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_LINK_TRAINING);

    SET_DISPLAY_DP_TX_LT_RESULT(_DISPLAY_DP_TX_TRAINING_NO_RESULT);
    SET_DISPLAY_DP_TX_LT_STATE(_DISPLAY_DP_TX_TRAINING_PATTERN1);

    // Set Link Rate
    SET_DISPLAY_DP_TX_LINK_RATE(_PANEL_DPTX_LINK_RATE);

    // Set Link Rate for DPCD table of the Sink
    ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x00, 1, &GET_DISPLAY_DP_TX_MAX_LINK_RATE());

    if(GET_DISPLAY_DP_TX_FRAMING_CHANGE_CAPABLE() == _TRUE)
    {
        // Set Link Count and Disable Enhance Framing for External DP Sink
        pData[0] = GET_DISPLAY_DP_TX_LANE_NUM();
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x01, 1, pData);

        // Set Enhance Framing Mode for eDP
        pData[0] = ((BYTE)GET_DISPLAY_DP_TX_FRAMING_CHANGE_CAPABLE() << 1);
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);

        // Set Enhance Framing Mode
        ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Set Link Count and Enhance Framing for DPCD table of the Sink
        pData[0] = ((BYTE)GET_DISPLAY_DP_TX_ENHANCE_FRAMING() << 7) | GET_DISPLAY_DP_TX_LANE_NUM();
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x01, 1, pData);

        // Set Enhance Framing Mode
        ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, ((BYTE)GET_DISPLAY_DP_TX_ENHANCE_FRAMING() << 2));
    }

    // Set Analog PHY CMU to gen Link Rate
    ScalerDisplayDPTxAnalogPhyConrol(_ENABLE);

    // Initialize Main Link Signal
    ScalerDisplayDPTxSignalInitialSetting();

    ScalerDisplayDPTxNativeAuxRead(0x00, 0x01, 0x07, 1, pData);

    // Set Down Spread
    pData[0] = ((pData[0] & ~_BIT4) | ((BYTE)GET_DISPLAY_DP_TX_SSCG_CONFIG() << 4));
    ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x07, 1, pData);

    // Set DPTx Spread Spectrum
    ScalerDisplayDPTxSSCSet(GET_DISPLAY_DP_TX_SSCG_CONFIG());
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDisplayDPTxTrainPattern1(void)
{
    // Start TP1 Process
    if(GET_DISPLAY_DP_TX_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_NO_RESULT)
    {
        // Main Link switch to TP1 Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_TPS1 << 4));
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        pData[0] = (_DISPLAY_DP_TX_TP_1 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
        pData[1] = g_stDisplayDPTxLTInfo.ucLane0Adjust;
        pData[2] = g_stDisplayDPTxLTInfo.ucLane1Adjust;
        pData[3] = g_stDisplayDPTxLTInfo.ucLane2Adjust;
        pData[4] = g_stDisplayDPTxLTInfo.ucLane3Adjust;

        // Write DPCD 102h to Start TP1
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerDisplayDPTxMLPHYSet();

        pData[0] = g_stDisplayDPTxLTInfo.ucLane0Adjust;
        pData[1] = g_stDisplayDPTxLTInfo.ucLane1Adjust;
        pData[2] = g_stDisplayDPTxLTInfo.ucLane2Adjust;
        pData[3] = g_stDisplayDPTxLTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x03, 4, pData);
    }

    if(GET_DISPLAY_DP_TX_DPCD_REV() >= 0x12)
    {
        // Read Training Aux Read Interval
        ScalerDisplayDPTxNativeAuxRead(0x00, 0x00, 0x0E, 1, pData);

        if(pData[0] > 0x04)
        {
            pData[0] = 0;
        }
    }
    else
    {
        pData[0] = 0;
    }

    if(pData[0] != 0x00)
    {
        // Delay 4*pData[0] ms
        ScalerTimerDelayXms(pData[0] << 2);
    }
    else
    {
        // Delay 400us
        for(pData[0] = 0; pData[0] < 55; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }
    }

    // Read Lane Status and Request Adjust Level
    ScalerDisplayDPTxNativeAuxRead(0x00, 0x02, 0x02, 6, pData);
    g_stDisplayDPTxLTInfo.ucLane01LTStatus = pData[0];
    g_stDisplayDPTxLTInfo.ucLane23LTStatus = pData[1];
    g_stDisplayDPTxLTInfo.ucAdjustReqLane01 = pData[4];
    g_stDisplayDPTxLTInfo.ucAdjustReqLane23 = pData[5];

    if(((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX_LANE3_CR_DONE() & GET_DISPLAY_DP_TX_LANE2_CR_DONE() & GET_DISPLAY_DP_TX_LANE1_CR_DONE() & GET_DISPLAY_DP_TX_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX_LANE1_CR_DONE() & GET_DISPLAY_DP_TX_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX_LANE0_CR_DONE() == _TRUE)))
    {
        return _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS;
    }

    switch(GET_DISPLAY_DP_TX_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            if(ScalerDisplayDPTxTP1Lane3Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDisplayDPTxTP1Lane2Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

        case _DP_TWO_LANE:

            if(ScalerDisplayDPTxTP1Lane1Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

        case _DP_ONE_LANE:
        default:

            if(ScalerDisplayDPTxTP1Lane0Adjust() == _FAIL)
            {
                return _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;
    }

    return _DISPLAY_DP_TX_TRAINING_PATTERN1_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTxTP1Lane0Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX_LANE0_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE0_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX_LANE0_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX_LANE0_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX_LANE0_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX_LANE0_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTxTP1Lane1Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX_LANE1_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE1_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX_LANE1_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX_LANE1_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX_LANE1_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX_LANE1_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTxTP1Lane2Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX_LANE2_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE2_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX_LANE2_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX_LANE2_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX_LANE2_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX_LANE2_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDisplayDPTxTP1Lane3Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DISPLAY_DP_TX_LANE3_ADJUST_VOL_SWING() + GET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE3_ADJUST_VOL_SWING((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING() == GET_DISPLAY_DP_TX_LANE3_ADJUST_VOL_SWING())
    {
        ADD_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT();

        if((GET_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT() == 5) || ((GET_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT() == 1) && (GET_DISPLAY_DP_TX_LANE3_ADJUST_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)))
        {
            CLR_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX_LANE3_ADJUST_VOL_SWING());
    SET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX_LANE3_ADJUST_PRE_EMPHASIS());

    if(GET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDisplayDPTxTrainPattern2(void)
{
    // Start TP2 Process
    if(GET_DISPLAY_DP_TX_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS)
    {
        // Check TP3 Supported
        if(GET_DISPLAY_DP_TX_TP3_SUPPORT() == _TRUE)
        {
            // Main Link Switch to TPS3 Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_TPS3 << 4));
            pData[0] = _DISPLAY_DP_TX_TP_3;
        }
        else
        {
            // Main Link Switch to TPS2 Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_TPS2 << 4));
            pData[0] = _DISPLAY_DP_TX_TP_2;
        }

        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // Disable Scrambling
        pData[0] |= _DISPLAY_DP_TX_SCRAMBLING_DISABLE;
        pData[1] = g_stDisplayDPTxLTInfo.ucLane0Adjust;
        pData[2] = g_stDisplayDPTxLTInfo.ucLane1Adjust;
        pData[3] = g_stDisplayDPTxLTInfo.ucLane2Adjust;
        pData[4] = g_stDisplayDPTxLTInfo.ucLane3Adjust;

        // Write DPCD 102h-107h to Start TP2
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerDisplayDPTxMLPHYSet();

        pData[0] = g_stDisplayDPTxLTInfo.ucLane0Adjust;
        pData[1] = g_stDisplayDPTxLTInfo.ucLane1Adjust;
        pData[2] = g_stDisplayDPTxLTInfo.ucLane2Adjust;
        pData[3] = g_stDisplayDPTxLTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x03, 4, pData);
    }

    if(GET_DISPLAY_DP_TX_DPCD_REV() >= 0x12)
    {
        pData[0] = (_DISPLAY_DP_TX_LANE0_MAX_POST_CURSOR2_REACHED | _DISPLAY_DP_TX_LANE1_MAX_POST_CURSOR2_REACHED);
        pData[1] = (_DISPLAY_DP_TX_LANE2_MAX_POST_CURSOR2_REACHED | _DISPLAY_DP_TX_LANE3_MAX_POST_CURSOR2_REACHED);
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x0F, 2, pData);

        // Read Training Aux Read Interval
        ScalerDisplayDPTxNativeAuxRead(0x00, 0x00, 0x0E, 1, pData);

        if(pData[0] > 0x04)
        {
            pData[0] = 0;
        }
    }
    else
    {
        pData[0] = 0;
    }

    if(pData[0] != 0x00)
    {
        // Delay 4*pData[0] ms
        ScalerTimerDelayXms(pData[0] << 2);
    }
    else
    {
        // Delay 400us
        for(pData[0] = 0; pData[0] < 55; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }
    }

    // Read Lane Status and Request Adjust Level
    ScalerDisplayDPTxNativeAuxRead(0x00, 0x02, 0x02, 6, pData);
    g_stDisplayDPTxLTInfo.ucLane01LTStatus = pData[0];
    g_stDisplayDPTxLTInfo.ucLane23LTStatus = pData[1];
    g_stDisplayDPTxLTInfo.ucLaneAlignStatus = pData[2];
    g_stDisplayDPTxLTInfo.ucAdjustReqLane01 = pData[4];
    g_stDisplayDPTxLTInfo.ucAdjustReqLane23 = pData[5];

    // CDR unlock => Reduce bit rate and return to TP1
    if(((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX_LANE3_CR_DONE() & GET_DISPLAY_DP_TX_LANE2_CR_DONE() & GET_DISPLAY_DP_TX_LANE1_CR_DONE() & GET_DISPLAY_DP_TX_LANE0_CR_DONE()) != _TRUE)) ||
       ((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX_LANE1_CR_DONE() & GET_DISPLAY_DP_TX_LANE0_CR_DONE()) != _TRUE)) ||
       ((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX_LANE0_CR_DONE() != _TRUE)))
    {
        CLR_DISPLAY_DP_TX_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }

    if((((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DISPLAY_DP_TX_LANE3_EQ_DONE() & GET_DISPLAY_DP_TX_LANE2_EQ_DONE() & GET_DISPLAY_DP_TX_LANE1_EQ_DONE() & GET_DISPLAY_DP_TX_LANE0_EQ_DONE()) == _TRUE)) ||
        ((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_TWO_LANE) && ((GET_DISPLAY_DP_TX_LANE1_EQ_DONE() & GET_DISPLAY_DP_TX_LANE0_EQ_DONE()) == _TRUE)) ||
        ((GET_DISPLAY_DP_TX_LANE_NUM() == _DP_ONE_LANE) && (GET_DISPLAY_DP_TX_LANE0_EQ_DONE() == _TRUE))) &&
       (GET_DISPLAY_DP_TX_LANE_ALIGN_DONE() == _TRUE))
    {
        CLR_DISPLAY_DP_TX_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS;
    }

    if(GET_DISPLAY_DP_TX_TP2_CNT() == 5)
    {
        CLR_DISPLAY_DP_TX_TP2_CNT();

        return _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }
    else
    {
        ADD_DISPLAY_DP_TX_TP2_CNT();
    }

    switch(GET_DISPLAY_DP_TX_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            ScalerDisplayDPTxTP2Lane3Adjust();
            ScalerDisplayDPTxTP2Lane2Adjust();

        case _DP_TWO_LANE:

            ScalerDisplayDPTxTP2Lane1Adjust();

        case _DP_ONE_LANE:
        default:

            ScalerDisplayDPTxTP2Lane0Adjust();

            break;
    }

    return _DISPLAY_DP_TX_TRAINING_PATTERN2_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxTP2Lane0Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX_LANE0_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX_LANE0_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX_LANE0_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxTP2Lane1Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX_LANE1_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX_LANE1_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX_LANE1_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxTP2Lane2Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX_LANE2_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX_LANE2_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX_LANE2_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxTP2Lane3Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING() + GET_DISPLAY_DP_TX_LANE3_ADJUST_PRE_EMPHASIS()) > _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS((_DISPLAY_DP_TX_LEVEL_3 - GET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(GET_DISPLAY_DP_TX_LANE3_ADJUST_PRE_EMPHASIS());
        SET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING(GET_DISPLAY_DP_TX_LANE3_ADJUST_VOL_SWING());
    }

    if(GET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS() == _DISPLAY_DP_TX_LEVEL_3)
    {
        SET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training Pattern End
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxTrainPatternEnd(void)
{
    // Write TRAINING_PATTERN_SET = 00
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x02, 1, pData);

    if(GET_DISPLAY_DP_TX_LT_RESULT() == _DISPLAY_DP_TX_TRAINING_PASS)
    {
        if(GET_DISPLAY_DP_TX_ALTERNATE_SR_CAPABLE() == _TRUE)
        {
            pData[0] = ((BYTE)GET_DISPLAY_DP_TX_FRAMING_CHANGE_CAPABLE() << 1) | _BIT0;
            ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);

            // Enable Sramble(Seed = 0xFFFE) and Enable BS replaced by SR
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT1 | _BIT0), (_BIT4 | _BIT1 | _BIT0));
        }
        else
        {
            // Enable Sramble(Seed = 0xFFFF) and Enable BS replaced by SR
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
        }

        // Main Link switch to IDLE Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_IDLE_PATTERN << 4));

        // Direct Apply Idle Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // Output switch to d-domain
        ScalerSetBit(PBB_D9_DPTX_TOP_CTL, ~_BIT1, _BIT1);

        // Panel DPTx Power Sequence Check Point
        PCB_DPTX_POWER_SEQUENCE(_DPTX_POWER_SEQUENCE_IDLE_PATTERN);
    }
    else
    {
        // Power Down ML PHY
        ScalerDisplayDPTxMLPowerOff();

        // Main Link switch to IDLE Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_IDLE_PATTERN << 4));

        // Direct Apply Idle Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxSignalReset(void)
{
    // Set Voltage Swing and pre-emphasis Variable to level 0
    CLR_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT();
    CLR_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT();

    SET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    SET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(_DISPLAY_DP_TX_LEVEL_0);
    CLR_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();

    // Clear TP2 Count
    CLR_DISPLAY_DP_TX_TP2_CNT();

    ScalerDisplayDPTxMLPHYSet();
}

//--------------------------------------------------
// Description  : Dp Tx Aux PHY Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxAuxPHYSet(BYTE ucMode)
{
    if(ucMode == _DISPLAY_DP_TX_AUX_SINGLE_MODE)
    {
        // Set Aux Tx LDO = 1.05V
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Set ADJR P
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Single End Mode and Enlarge Z0-P
        ScalerSetBit(PBD_62_AUX_2, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

        // Enable Enlarge Z0-N and Set ADJR-N = 0
        ScalerSetBit(PBD_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
        // Set Aux Tx LDO = 0.9V
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Set ADJR P
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Disable Single End Mode and Enlarge Z0-P
        ScalerSetBit(PBD_62_AUX_2, ~(_BIT5 | _BIT0), _BIT0);

        // Disable Enlarge Z0-N and Set ADJR N
        ScalerSetBit(PBD_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1 | _BIT0));
    }

    // Set TX ADJR-P and ADJR-N
    ScalerSetByte(PBD_67_DIG_TX_03, 0xFF);
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxSignalInitialSetting(void)
{
    // Set Voltage Swing and pre-emphasis level 0
    ScalerDisplayDPTxSignalReset();

    // Disable scramble
    ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, 0x00);

    // Set Z0 to 50 ohm
    ScalerSetByte(PBC_C2_DPTX_Z0_LANE3_2, 0x88);
    ScalerSetByte(PBC_C3_DPTX_Z0_LANE1_0, 0x88);

    // Set Lane Swap
    ScalerSetByte(PBC_AA_DPTX_SFIFO_LANE_SWAP1, 0x1B);

    // Enable DP Tx
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

    // DPTX power on TX driver and Enable output
    switch(GET_DISPLAY_DP_TX_LANE_NUM())
    {
        case _DP_ONE_LANE:

            // Set Mac 1 Lane
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT0);

            // Dig PHY Set
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

            // Disable Skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, 0x00);

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            ScalerSetBit(PBC_A1_DPTX_PHY_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
            ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            break;

        case _DP_TWO_LANE:

            // Set Mac 2 Lane
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT1);

            // Dig PHY Set
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3));

            // Enable Lane Skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            ScalerSetBit(PBC_A1_DPTX_PHY_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
            ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _DP_FOUR_LANE:

            // Set Mac 4 Lane
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Dig PHY Set
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable Lane Skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            ScalerSetBit(PBC_A1_DPTX_PHY_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power off
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxMLPowerOff(void)
{
    // Power Down 4 Lanes
    ScalerSetByte(PBC_A1_DPTX_PHY_CTRL1, 0x0F);

    // Disable DP TX Power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx CMU Power On
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxCMUPowerOn(void)
{
    WORD usNCode = 0;
    WORD usFCode = 0;
    DWORD ulCMUFreq = 5400000;

    // Enable Power of DPTX
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT7, _BIT7);

    // Enable CMU
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, _BIT4);

    // Wait for CMU Stable
    ScalerTimerDelayXms(2);

    // Disable SSC
    ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT5, 0x00);

    // Divider for Postdivider of CMU and Pre-divder of CMU
    ScalerSetByte(PBC_D2_DPTX_CMU2, 0x00);

    // LDO voltage Setting
    ScalerSetByte(PBC_D3_DPTX_CMU3, 0x55);

    // Set DP mode
    ScalerSetBit(PBC_A9_DPTX_SFIFO_LANE_SWAP0, ~(_BIT7 | _BIT3), _BIT7);

    // Set Small FIFO,half rate (1 bit mode)
    ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~(_BIT6 | _BIT5), 0x00);

    // CLKRD duty set to 4'b1111 @0638 as AMlee suggests.
    // Good Phase setting 4'b1111
    ScalerSetByte(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, 0xF0);

    if(GET_DISPLAY_DP_TX_LINK_RATE() == _DP_LINK_HBR2)
    {
        // 5.4G
        // HBR2 = 5.4GHz, VCO = 3~6 GHz
        ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), 0x00);

        // VCO = 3 ~ 6GHz,div = 1
        ulCMUFreq = 5400000;

        // [7] 0:CCO Mode¡B1:VCO Mode
        // [6] 0:Small Kvco¡B1:Big Kvco
        // [5] 0:3rd LPF¡B1:2nd LPF
        // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
        // [3] 0:Use PI¡B1:Bypass PI
        // [2:0] PI Current setting
        ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1)); // VCO 5G~6G

    }
    else if(GET_DISPLAY_DP_TX_LINK_RATE() == _DP_LINK_HBR)
    {
        // HBR = 2.7GHz, VCO = 1.5 ~ 3 GHz
        ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // VCO = 1.5 ~ 3GHz, div = 2, 2700000 * 2 = 5400000
        ulCMUFreq = 5400000;

        // [7] 0:CCO Mode¡B1:VCO Mode
        // [6] 0:Small Kvco¡B1:Big Kvco
        // [5] 0:3rd LPF¡B1:2nd LPF
        // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
        // [3] 0:Use PI¡B1:Bypass PI
        // [2:0] PI Current setting
        ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));  // VCO 3G~4G

    }
    else if(GET_DISPLAY_DP_TX_LINK_RATE() == _DP_LINK_RBR)
    {
        // RBR = 1.62GHz, VCO = 1.5 ~ 3 GHz
        ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // VCO = 1.5 ~ 3GHz, div = 2, 1620000 * 2 = 3240000
        ulCMUFreq = 3240000;

        // [7] 0:CCO Mode¡B1:VCO Mode
        // [6] 0:Small Kvco¡B1:Big Kvco
        // [5] 0:3rd LPF¡B1:2nd LPF
        // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
        // [3] 0:Use PI¡B1:Bypass PI
        // [2:0] PI Current setting
        ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));  // VCO 3G~4G
    }

    // Count N.F Code
    usNCode = ulCMUFreq / (_EXT_XTAL * 2) - 4;
    usFCode = ulCMUFreq % (_EXT_XTAL * 2);

    if(usFCode != 0)
    {
        ulCMUFreq = ((DWORD)usFCode << 12);
        usFCode = ulCMUFreq / (_EXT_XTAL * 2);
    }

    // N Code = 9 bit
    // F Code = 12 bit
    usNCode &= 0x1FF;
    usFCode &= 0xFFF;

    // Set N.f code
    // ScalerSetByte(PBC_DD_DPTX_CMU12, (BYTE)(usNCode >> 4));
    // ScalerSetByte(PBC_DE_DPTX_CMU13, ((BYTE)(usNCode << 4) | (BYTE)(usFCode >> 8)));
    // ScalerSetByte(PBC_DF_DPTX_CMU14, (BYTE)usFCode);

    // N.f double buffer
    // ScalerSetBit(PBC_DD_DPTX_CMU12, ~_BIT7, _BIT7);

    ScalerSetByte(PBC_DF_DPTX_CMU14, (BYTE)usFCode);
    ScalerSetByte(PBC_DE_DPTX_CMU13, ((BYTE)(usNCode << 4) | (BYTE)(usFCode >> 8)));
    ScalerSetByte(PBC_DD_DPTX_CMU12, (BYTE)(_BIT7 | (usNCode >> 4)));




    // toggle CMU power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, _BIT4);

    // CMU enable
    // Wait PLL stable
    ScalerTimerDelayXms(2);

    // Enable Watch Dog
    ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT7, _BIT7);    // Enable WD

    // Wait Watch Dog to check PLL is stable or not
    ScalerTimerDelayXms(2);

    // Check PLL is stable or not
    if(ScalerGetBit(PBC_D4_DPTX_CMU4, _BIT7) == 0x00)
    {
        // Disable WD & SSC
        ScalerSetByte(PBC_D5_DPTX_CMU5, 0x00);

        // Disable CMU Power
        ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);

        // Disable DP TX Power
        ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT7, 0x00);
    }

    // Disable WD & SSC
    ScalerSetByte(PBC_D5_DPTX_CMU5, 0x00);
}


//--------------------------------------------------
// Description  : Dp Tx CMU Power Off
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxCMUPowerOff(void)
{
    // Check SSC is enable or not
    if(ScalerGetBit(PBC_D5_DPTX_CMU5, _BIT5) != 0x00)
    {
        // Disable SSC
        ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT5, 0x00);

        // SSC Off stable
        ScalerTimerDelayXms(2);
    }

    // Disable CMU Power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);

    // Disabe DP TX Power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3     //Linqian
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxMLPHYSet(void)
{
    switch(GET_DISPLAY_DP_TX_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            // set Lane3 PHY voltage swing level
            ScalerDisplayDPTxSetSignalLevel(GET_DISPLAY_DP_TX_LINK_RATE(), _DISPLAY_DP_TX_LANE_3, GET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS());

            // set Lane2 PHY voltage swing level
            ScalerDisplayDPTxSetSignalLevel(GET_DISPLAY_DP_TX_LINK_RATE(), _DISPLAY_DP_TX_LANE_2, GET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS());

            // set Lane1 PHY voltage swing level
            ScalerDisplayDPTxSetSignalLevel(GET_DISPLAY_DP_TX_LINK_RATE(), _DISPLAY_DP_TX_LANE_1, GET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS());

            // set Lane0 PHY voltage swing level
            ScalerDisplayDPTxSetSignalLevel(GET_DISPLAY_DP_TX_LINK_RATE(), _DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());

        case _DP_TWO_LANE:

            // set Lane1 PHY voltage swing level
            ScalerDisplayDPTxSetSignalLevel(GET_DISPLAY_DP_TX_LINK_RATE(), _DISPLAY_DP_TX_LANE_1, GET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS());

            // set Lane0 PHY voltage swing level
            ScalerDisplayDPTxSetSignalLevel(GET_DISPLAY_DP_TX_LINK_RATE(), _DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());

        case _DP_ONE_LANE:

            // set Lane0 PHY voltage swing level
            ScalerDisplayDPTxSetSignalLevel(GET_DISPLAY_DP_TX_LINK_RATE(), _DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());

        default:

            // set Lane0 PHY voltage swing level
            ScalerDisplayDPTxSetSignalLevel(GET_DISPLAY_DP_TX_LINK_RATE(), _DISPLAY_DP_TX_LANE_0, GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxSetSignalLevel(BYTE ucLinkRate, EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis)
{
    BYTE ucIndex = 0x00;
    BYTE *pucTable = 0x00;

    ucLinkRate = ucLinkRate;

    ucVoltageSwing = ucVoltageSwing;

    ucPreEmphasis = ucPreEmphasis;

    ucIndex = (_PANEL_DPTX_SWING_LEVEL * 4 + _PANEL_DPTX_PREEMPHASIS_LEVEL) * 3;

    if(ucLinkRate == _DP_LINK_HBR2)
    {
        pucTable = tDISPLAY_DPTX_DRV_HBR2_TABLE;
    }
    else
    {
        pucTable = tDISPLAY_DPTX_DRV_RBR_HBR_TABLE;
    }

    switch(enumLaneX)
    {
        case _DISPLAY_DP_TX_LANE_0:

            // De-emphasis [9:8]
            ScalerSetBit(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, ~0x03, ((pucTable[ucIndex + 1] & 0xF0) >> 4));

            // De-emphasis [7:0]
            ScalerSetByte(PBC_B4_DPTX_DEEMP_EN_LANE0L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(PBC_B7_DPTX_DRV_DAC_DAT_LANE1_0, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

            // Post1 [3:0]
            ScalerSetBit(PBC_BB_DPTX_DRV_DAC_POST1_LANE1_0, ~0x0F, (pucTable[ucIndex + 2] >> 4));

            // Post0 [3:0]
            ScalerSetBit(PBC_B9_DPTX_DRV_DAC_POST0_LANE1_0, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

            break;

        case _DISPLAY_DP_TX_LANE_1:

            // De-emphasis [9:8]
            ScalerSetBit(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, ~0x0C, ((pucTable[ucIndex + 1] & 0xF0) >> 2));

            // De-emphasis [7:0]
            ScalerSetByte(PBC_B3_DPTX_DEEMP_EN_LANE1L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(PBC_B7_DPTX_DRV_DAC_DAT_LANE1_0, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));

            // Post1 [3:0]
            ScalerSetBit(PBC_BB_DPTX_DRV_DAC_POST1_LANE1_0, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));

            // Post0 [3:0]
            ScalerSetBit(PBC_B9_DPTX_DRV_DAC_POST0_LANE1_0, ~0xF0, (pucTable[ucIndex + 2] << 4));

            break;

        case _DISPLAY_DP_TX_LANE_2:

            // De-emphasis [9:8]
            ScalerSetBit(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, ~0x30, ((pucTable[ucIndex + 1] & 0xF0) >> 0));

            // De-emphasis [7:0]
            ScalerSetByte(PBC_B2_DPTX_DEEMP_EN_LANE2L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(PBC_B6_DPTX_DRV_DAC_DAT_LANE3_2, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

            // Post1 [3:0]
            ScalerSetBit(PBC_BA_DPTX_DRV_DAC_POST1_LANE3_2, ~0x0F, (pucTable[ucIndex + 2] >> 4));

            // Post0 [3:0]
            ScalerSetBit(PBC_B8_DPTX_DRV_DAC_POST0_LANE3_2, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

            break;

        case _DISPLAY_DP_TX_LANE_3:

            // De-emphasis [9:8]
            ScalerSetBit(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, ~0xC0, ((pucTable[ucIndex + 1] & 0xF0) << 2));

            // De-emphasis [7:0]
            ScalerSetByte(PBC_B1_DPTX_DEEMP_EN_LANE3L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(PBC_B6_DPTX_DRV_DAC_DAT_LANE3_2, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));

            // Post1 [3:0]
            ScalerSetBit(PBC_BA_DPTX_DRV_DAC_POST1_LANE3_2, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));

            // Post0 [3:0]
            ScalerSetBit(PBC_B8_DPTX_DRV_DAC_POST0_LANE3_2, ~0xF0, (pucTable[ucIndex + 2] << 4));

            break;

        default:

            // No data
            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Aux Write
// Input Value  : ucCommand --> Aux Write Command
//                ucHighAddress --> High Byte of  Aux Write Address
//                ucMidAddress --> Middle Byte of  Aux Write Address
//                ucLowAddress --> Low Byte of  Aux Write Address
//                ucLength --> Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of Aux Write
// Output Value : TRUE --> Aux Write Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTxAuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    BYTE ucDataCount = 0;
    BYTE ucWriteRetryNum = 0;

    // Enable Timeout Retry
    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

    // Reset FIFO
    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // CLR Flag
    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

    // Disable Address only transaction
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT7, 0x00);

    ScalerSetByte(PBD_A4_AUXTX_REQ_CMD, ucCommandAddrH);
    ScalerSetByte(PBD_A5_AUXTX_REQ_ADDR_M, ucAddrM);
    ScalerSetByte(PBD_A6_AUXTX_REQ_ADDR_L, ucAddrL);

    // Check Length
    if(ucLength == 0)
    {
        ucLength = 1;
    }
    else if(ucLength > 16)
    {
        ucLength = 16;
    }

    // Setting AUX Write Length : TX_LEN = ucLength-1
    ScalerSetByte(PBD_A7_AUXTX_REQ_LEN, (ucLength - 1));

    // Write Data to Buffer
    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
    {
        ScalerSetByte(PBD_A8_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
    }

    // Reset AUX Start Bit
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

    // Enable Aux to Start Write
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

    while(ucWriteRetryNum < 7)
    {
        // Delay 400us
        for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
        {
            Delay5us(g_ucDelay5usN);
        }

        // Polling AUX Done Bit (Delay 25 Loop = 175us)
        for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
        {
            Delay5us(g_ucDelay5usN);

            if(ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
            {
                // Reply Error or Nack or Command is not ACK
                if((ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit(PBD_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                {
                    // CLR Flag
                    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Write Data to Buffer
                    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
                    {
                        ScalerSetByte(PBD_A8_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
                    }

                    // Reset AUX Start Bit
                    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                    // Enable Aux to Start Write
                    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

                    break;
                }
                else
                {
                    // Disable Timeout Retry
                    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    return _TRUE;
                }
            }
            else
            {
                // HW Retry Times Reaches RETRY_NUM
                if(ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                {
                    // Disable Timeout Retry
                    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    return _FALSE;
                }
            }
        }

        // Increasing Retry Num
        ucWriteRetryNum += 1;
    }

    // Disable Timeout Retry
    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset FIFO
    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Aux Read
// Input Value  : ucCommand --> Aux Read Command
//                ucHighAddress --> High Byte of  Aux Read Address
//                ucMidAddress --> Middle Byte of  Aux Read Address
//                ucLowAddress --> Low Byte of  Aux Read Address
//                ucLength --> Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of Aux Read
// Output Value : TRUE --> Aux Read Sucessful
//--------------------------------------------------
bit ScalerDisplayDPTxAuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucCheckLength = 0;
    BYTE ucOffsetLength = 0;

    // Enable AUX FW Handle Mode
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5), _BIT5);

    // Disable Address only transaction
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT7, 0x00);

    do
    {
        ucReadRetryNum = 0;

        // Enable Retry Mechanism
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Timeout HW Retry
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Setting DPCD Read Address
        ScalerSetByte(PBD_A4_AUXTX_REQ_CMD, ucCommandAddrH);
        ScalerSetByte(PBD_A5_AUXTX_REQ_ADDR_M, ucAddrM);
        ScalerSetByte(PBD_A6_AUXTX_REQ_ADDR_L, (ucAddrL + ucOffsetLength));

        ucLength = ucLength - ucOffsetLength;

        if(ucLength == 0)
        {
            ucLength = 1;
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        // Set Read Length : TX_LEN = ucLength-1
        ScalerSetByte(PBD_A7_AUXTX_REQ_LEN, (ucLength - 1));

        // Reset AUX Start Bit
        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        // Enable Aux to Start Read
        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay 400us
            for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
            {
                Delay5us(g_ucDelay5usN);
            }

            // Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit(PBD_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Reset AUX Start Bit
                        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                        // Enable Aux to Start Read
                        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ucCheckLength = ScalerGetBit(PBD_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        ucOffsetLength += ucCheckLength;

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = ScalerGetByte(PBD_AA_AUX_REPLY_DATA);
                            pucReadArray++;
                        }

                        if(ucCheckLength == ucLength)
                        {
                            // Disable Timeout Retry
                            ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            return _TRUE;
                        }
                    }

                    break;
                }
                else
                {
                    // HW Retry Times Reaches RETRY_NUM
                    if(ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum += 1;
        }
        while((ucReadRetryNum < 7) && (ScalerGetBit(PBD_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00));
    }
    while((ucCheckLength != ucLength) && (ucReadRetryNum < 7));

    // Disable Timeout Retry
    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    return _FALSE;
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
bit ScalerDisplayDPTxNativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    if(ScalerDisplayDPTxAuxWrite((0x80 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucWriteArray) == _FALSE)
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
bit ScalerDisplayDPTxNativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    if(ScalerDisplayDPTxAuxRead((0x90 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucReadArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure function for DPTX SST D0
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDisplayDPTxMeasureInputInfo(void)
{
    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_00_DISPLAY_HOR_TOTAL_H);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 2, &pData[0], _NON_AUTOINC);

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_02_DISPLAY_HOR_SYNC_END);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 3, &pData[3], _NON_AUTOINC);

    ScalerSetByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_09_DISPLAY_HOR_BG_END_H);
    ScalerRead(P0_2B_DISPLAY_FORMAT_DATA_PORT, 2, &pData[6], _NON_AUTOINC);

    // Htotal
    g_stDisplayDPTxTimingInfo.usHTotal = (PDATA_WORD(0) & 0x1FFF) + 4;

    // Hstart
    g_stDisplayDPTxTimingInfo.usHStart = (PDATA_WORD(2) & 0x1FFF);

    // Hwidth
    g_stDisplayDPTxTimingInfo.usHWidth = (PDATA_WORD(3) & 0x1FFF) - (PDATA_WORD(2) & 0x1FFF);

    // Hsyc
    g_stDisplayDPTxTimingInfo.usHSWidth = (pData[3]);

    // Hsyc polarity
    g_stDisplayDPTxTimingInfo.b1HSP = 1;

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
    g_stDisplayDPTxTimingInfo.usVTotal = ((PDATA_WORD(0) + 1) & 0x1FFF);

    // VStart
    g_stDisplayDPTxTimingInfo.usVStart = (PDATA_WORD(2) & 0x1FFF);

    // VHeight
    g_stDisplayDPTxTimingInfo.usVHeight = (PDATA_WORD(3) & 0x1FFF) - (PDATA_WORD(2) & 0x1FFF);

    // Vsync
    g_stDisplayDPTxTimingInfo.usVSWidth = (pData[3]);

    // Vsyc polarity
    g_stDisplayDPTxTimingInfo.b1VSP = 1;

    g_stDisplayDPTxTimingInfo.usHFreq = GET_D_CLK_FREQ() * 10 / g_stDisplayDPTxTimingInfo.usHTotal;
    g_stDisplayDPTxTimingInfo.usVFreq = GET_D_CLK_FREQ() * 1000 / g_stDisplayDPTxTimingInfo.usHTotal * 10 / g_stDisplayDPTxTimingInfo.usVTotal;

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Link TSignal Force Output
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDisplayDPTxLinkForceOutput(void)
{
    ScalerDisplayDPTxTPInitialSet();

    // Set Output Signal According to Request
    ScalerDisplayDPTxMLPHYSet();

    // Training Pattern 1 For Link Training
    // Main Link switch to TP1 Pattern
    ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_TPS1 << 4));
    ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

    pData[0] = (_DISPLAY_DP_TX_TP_1 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
    pData[1] = g_stDisplayDPTxLTInfo.ucLane0Adjust;
    pData[2] = g_stDisplayDPTxLTInfo.ucLane1Adjust;
    pData[3] = g_stDisplayDPTxLTInfo.ucLane2Adjust;
    pData[4] = g_stDisplayDPTxLTInfo.ucLane3Adjust;

    // Write DPCD 102h-107h to Start TP1
    ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x02, 5, pData);

    if(GET_DISPLAY_DP_TX_DPCD_REV() >= 0x12)
    {
        // Read Training Aux Read Interval
        ScalerDisplayDPTxNativeAuxRead(0x00, 0x00, 0x0E, 1, pData);

        if(pData[0] > 0x04)
        {
            pData[0] = 0;
        }
    }
    else
    {
        pData[0] = 0;
    }

    if(pData[0] != 0x00)
    {
        // Delay 4*pData[0] ms
        ScalerTimerDelayXms(pData[0] << 2);
    }
    else
    {
        // Delay 400us
        for(pData[0] = 0; pData[0] < 55; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }
    }

    // Training Pattern 2 For Link Training
    // Main Link Switch to TP2 Pattern
    ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_TPS2 << 4));
    ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

    pData[0] = (_DISPLAY_DP_TX_TP_2 | _DISPLAY_DP_TX_SCRAMBLING_DISABLE);
    pData[1] = g_stDisplayDPTxLTInfo.ucLane0Adjust;
    pData[2] = g_stDisplayDPTxLTInfo.ucLane1Adjust;
    pData[3] = g_stDisplayDPTxLTInfo.ucLane2Adjust;
    pData[4] = g_stDisplayDPTxLTInfo.ucLane3Adjust;

    // Write DPCD 102h-107h to Start TP2
    ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x02, 5, pData);

    if(GET_DISPLAY_DP_TX_DPCD_REV() >= 0x12)
    {
        pData[0] = (_DISPLAY_DP_TX_LANE0_MAX_POST_CURSOR2_REACHED | _DISPLAY_DP_TX_LANE1_MAX_POST_CURSOR2_REACHED);
        pData[1] = (_DISPLAY_DP_TX_LANE2_MAX_POST_CURSOR2_REACHED | _DISPLAY_DP_TX_LANE3_MAX_POST_CURSOR2_REACHED);
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x0F, 2, pData);

        // Read Training Aux Read Interval
        ScalerDisplayDPTxNativeAuxRead(0x00, 0x00, 0x0E, 1, pData);

        if(pData[0] > 0x04)
        {
            pData[0] = 0;
        }
    }
    else
    {
        pData[0] = 0;
    }

    if(pData[0] != 0x00)
    {
        // Delay 4*pData[0] ms
        ScalerTimerDelayXms(pData[0] << 2);
    }
    else
    {
        // Delay 400us
        for(pData[0] = 0; pData[0] < 55; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }
    }

    // Training Pattern End For Link Training
    pData[0] = _DISPLAY_DP_TX_TP_NONE;
    ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x02, 1, pData);

    if(GET_DISPLAY_DP_TX_ALTERNATE_SR_CAPABLE() == _TRUE)
    {
        pData[0] = ((BYTE)GET_DISPLAY_DP_TX_FRAMING_CHANGE_CAPABLE() << 1) | _BIT0;
        ScalerDisplayDPTxNativeAuxWrite(0x00, 0x01, 0x0A, 1, pData);

        // Enable Sramble(Seed = 0xFFFE) and Enable BS replaced by SR
        ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT1 | _BIT0), (_BIT4 | _BIT1 | _BIT0));
    }
    else
    {
        // Enable Sramble(Seed = 0xFFFF) and Enable BS replaced by SR
        ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT1 | _BIT0), (_BIT4 | _BIT0));
    }

    // Main Link switch to IDLE Pattern
    ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DISPLAY_DP_TX_OUTPUT_IDLE_PATTERN << 4));
    ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

    // Output switch to d-domain
    ScalerSetBit(PBB_D9_DPTX_TOP_CTL, ~_BIT1, _BIT1);
}
#endif // End of #if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)


