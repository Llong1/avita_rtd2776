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
// ID Code      : RL6410_Series_MHL3Rx5.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define __RL6410_SERIES_MHL3RX5__

#include "ScalerFunctionInclude.h"

#if((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// MHL 3.0 eCBUS eMSC Link Macros
//--------------------------------------------------
#define GET_MHL3_RX5_EMSC_SYNC_RETRY_TIME()                  (g_ucMhl3Rx5EmscLinkRetryTime)
#define ADD_MHL3_RX5_EMSC_SYNC_RETRY_TIME()                  (g_ucMhl3Rx5EmscLinkRetryTime = (g_ucMhl3Rx5EmscLinkRetryTime + 1))
#define CLR_MHL3_RX5_EMSC_SYNC_RETRY_TIME()                  (g_ucMhl3Rx5EmscLinkRetryTime = (0))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
//--------------------------------------------------
// MHL 3.0 ECBUS Start Up
//--------------------------------------------------
StructECBUSProcessInfo g_stMhl3Rx5ECBUSProcess;
BYTE g_ucMhl3Rx5EmscLinkRetryTime;

//--------------------------------------------------
// MHL 3.0 eMSC Block Transaction
//--------------------------------------------------
WORD g_usMhl3Rx5SourceRxBufferAvailSize = 256;
WORD g_usMhl3Rx5SinkRxBufferAvailSize = 256;
bit g_bMhl3Rx5ECBUSBlkRcvInfoSent = 0;

//--------------------------------------------------
// MHL 3.0 ECBUS Virtual Channel Assignment
//--------------------------------------------------
BYTE g_pucMhl3Rx5ECBUSVCAssignNumEnt[16];
BYTE g_pucMhl3Rx5ECBUSVCAssignWBLength[16];
BYTE g_ucMhl3Rx5ECBUSVCAssignVCCount;
BYTE g_pucMhl3Rx5ECBUSVCAssignVCNum[8];
BYTE g_pucMhl3Rx5ECBUSVCAssignVCID[8];
BYTE g_pucMhl3Rx5ECBUSVCAssignVCSize[8];
BYTE g_pucMhl3Rx5ECBUSVCAssignSlotVC[25];

//--------------------------------------------------
// MHL 3.0 BIST
//--------------------------------------------------
bit g_bMhl3Rx5BISTTesting = 0;
BYTE g_ucMhl3Rx5BISTTestingMode;
BYTE g_ucMhl3Rx5BISTECBUSDruation;
BYTE g_ucMhl3Rx5BISTImpedenceMode = 0xFF;
WORD g_usMhl3Rx5BISTAVLinkErrCnt;
WORD g_usMhl3Rx5BISTEcbusErrCnt;

//--------------------------------------------------
// MHL 3.0 HID Device
//--------------------------------------------------
bit g_bMhl3Rx5HidDeviceActive = 0;
BYTE g_ucMhl3Rx5HidDeviceDiscript;
BYTE g_ucMhl3Rx5HidHeaderHB;
BYTE g_ucMhl3Rx5HidHeaderLB;

//--------------------------------------------------
// MHL 3.0 AV Link
//--------------------------------------------------
BYTE g_ucMhl3Rx5AVLinkNCode = _ECBUS_N_CODE_NULL;
BYTE g_ucMhl3Rx5AVLinkRate = _ECBUS_LINK_RATE_NULL;

//--------------------------------------------------
// MHL 3.0 Video Measure
//--------------------------------------------------
BYTE g_ucMhl3Rx5MSAFailMacRsetCount;
BYTE g_ucMhl3Rx5ViewPixelFormat = 0xFF;
BYTE g_ucMhl3Rx5ViewPixelDivider = 0xFF;
WORD g_usMhl3Rx5HstartAvg;
WORD g_usMhl3Rx5HendAvg;
WORD g_usMhl3Rx5HactiveAvg;
WORD g_usMhl3Rx5HtotalAvg;
WORD g_usMhl3Rx5Vstart;
WORD g_usMhl3Rx5Vend;
WORD g_usMhl3Rx5Vactive;
WORD g_usMhl3Rx5Vtotal;
WORD g_usMhl3Rx5HactivePixelCount;
WORD g_usMhl3Rx5HTotalPixelCount;
DWORD g_ulMhl3Rx5PixelClkValue;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMHL3Rx5ECBUSInitialSetting(void);
void ScalerMHL3Rx5ECBUSVirtualChannelInitialAssign(void);
void ScalerMHL3Rx5ECBUSVirtualChannelInitialAssign_EXINT0(void);

void ScalerMHL3Rx5ECBUSConfigureSettings(void);
void ScalerMHL3Rx5EnableECBUSMode(bit bEnable);
void ScalerMHL3Rx5EnableECBUSMode_EXINT0(bit bEnable);

void ScalerMHL3Rx5ECBUSResetProc(void);
void ScalerMHL3Rx5ECBUSResetProc_EXINT0(void);

void ScalerMHL3Rx5ECBUSIntHandler_EXINT0(void);
bit ScalerMHL3Rx5ECBUSHandler(void);

void ScalerMHL3Rx5BISTHandler(void);
void ScalerMHL3Rx5BISTTestingDoneProc(void);

BYTE ScalerMHL3Rx5ECBUSGetEmscRxVolume(BYTE ucRxSramWritePointer, BYTE ucRxSramReadPointer);
BYTE ScalerMHL3Rx5ECBUSEMSCRxHandler(void);
BYTE ScalerMHL3Rx5ECBUSProcessEmscPayload(BYTE ucBurstIDHB, BYTE ucBurstIDLB, BYTE ucLengthRemain);

BYTE ScalerMHL3Rx5ECBUSEmscTxEncode(BYTE ucEmscBurstId, BYTE ucEmscSubMessageId, BYTE ucEmscSubMessageContent, BYTE ucEmscSubMessageLength);
bit ScalerMHL3Rx5ECBUSEMSCTxHandler(void);

bit ScalerMHL3Rx5ECBUSTdmReallocation(void);
void ScalerMHL3Rx5ECBUSTdmReallocationAlgorithmA(BYTE ucAN, BYTE ucAM, BYTE ucNM1);
void ScalerMHL3Rx5ECBUSTdmReallocationAlgorithmB(BYTE ucBN, BYTE ucBM, BYTE ucNM1, BYTE ucBth);
bit ScalerMHL3Rx5DataSignalDetect(void);

void ScalerMHL3Rx5MeasureReset(void);
bit ScalerMHL3Rx5MeasureCheck(void);
BYTE ScalerMHL3Rx5FormatDetect(void);
bit ScalerMHL3Rx5ViewPixelFormatCheck(void);
bit ScalerMHL3Rx5InterlaceCheck(void);

bit ScalerMHL3Rx5DisplayFormatSetting(void);
DWORD ScalerMHL3Rx5StreamClkRegenerate(void);

bit ScalerMHL3Rx5DisplayFormatGenFifoCheck(void);
void ScalerMHL3Rx5DisplatFormatGenAdjustHsyncDelay(DWORD ulPixelClkValue);
void ScalerMHL3Rx5DisplayFormatGenAdjustVsyncDelay(DWORD ulPixelClkValue);

bit ScalerMHL3Rx5FakePowerSavingCheck(void);
void ScalerMHL3Rx5TimerEventProc(EnumScalerTimerEventID enumEventID);

#if(_MHL3_TEST_FUNCTION_DEBUG_MODE == _ON)
void ScalerMHL3Rx5TestPinSetting(BYTE ucMode);
#endif

#if(_ECBUS_TX_TEST_FUNCTION == _ON)
void ScalerMHL3Rx5ECBUSTxTestSettingFunction(void);
#endif
#if(_ECBUS_RX_TEST_FUNCTION == _ON)
void ScalerMHL3Rx5ECBUSRxTestSettingFunction(void);
#endif

void ScalerMHL3Rx5WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initial Setting of D0 eCBUS-S
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSInitialSetting(void)
{
    // Clear eCBUS Start Up TMOUT Flags
    CLR_MHL3_RX5_ECBUS_START_UP_TMOUT();
    CLR_MHL3_RX5_WAIT_SRC_MHL_VERSION_TMOUT();
    CLR_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP_TMOUT();
    CLR_MHL3_RX5_ECBUS_CLK_STABLE();

    ScalerMHL3Rx5ECBUSVirtualChannelInitialAssign();

    // Clear eCBUS eMSC Flags
    CLR_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT();

    // Clear eCBUS AV Link Flags
    SET_MHL3_RX5_AV_LINK_RATE(_ECBUS_LINK_RATE_NULL);
    SET_MHL3_RX5_AV_LINK_N_CODE(_ECBUS_N_CODE_NULL);
    CLR_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT();
    SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(_MHL3_VIDEO_FORMAT_NULL);
    SET_MHL3_RX5_VIEW_PIXEL_DIVIDER(_MHL3_VIDEO_MODE_DIV_ERROR);

    SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_INITIAL);
}

//--------------------------------------------------
// Description  : Initial Assign eCBUS Virtual Channel
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSVirtualChannelInitialAssign(void)
{
    // Reset eCBUS eMSC Allocation Mapping
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(0, _MHL3_ECBUS_VC_CBUS1_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(1, _MHL3_ECBUS_VC_EMSC_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(2, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(3, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(4, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(5, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(6, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(7, _MHL3_ECBUS_VC_EMSC_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(8, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(9, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(10, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(11, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(12, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(13, _MHL3_ECBUS_VC_EMSC_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(14, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(15, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(16, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(17, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(18, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(19, _MHL3_ECBUS_VC_EMSC_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(20, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(21, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(22, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(23, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(24, _MHL3_ECBUS_VC_UN_ASSIGN);
}

//--------------------------------------------------
// Description  : Initial Assign eCBUS Virtual Channel (EXINT Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSVirtualChannelInitialAssign_EXINT0(void) using 1
{
    // Reset eCBUS eMSC Allocation Mapping
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(0, _MHL3_ECBUS_VC_CBUS1_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(1, _MHL3_ECBUS_VC_EMSC_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(2, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(3, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(4, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(5, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(6, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(7, _MHL3_ECBUS_VC_EMSC_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(8, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(9, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(10, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(11, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(12, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(13, _MHL3_ECBUS_VC_EMSC_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(14, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(15, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(16, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(17, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(18, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(19, _MHL3_ECBUS_VC_EMSC_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(20, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(21, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(22, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(23, _MHL3_ECBUS_VC_UN_ASSIGN);
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(24, _MHL3_ECBUS_VC_UN_ASSIGN);
}

//--------------------------------------------------
// Description  : Configure Setting of D0 eCBUS-S
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSConfigureSettings(void)
{
    ////////////////////////////////////
    /////// Analog PHY Configure ///////
    ////////////////////////////////////

    // Set Calibration Step to 00 = Work
    ScalerSetBit(P5E_01_ECBUS_STEP_CTRL, ~(_BIT1 | _BIT0), 0x00);

    // Manual Setting APHY Feedback R/C ---> 6K / 50f
    ScalerSetByte(P5E_03_ECBUS_FEEDBACK_CTRL, 0x32);

    // Set Vref of Compater after OP -> 101 = 715mV
    ScalerSetBit(P5E_04_EBUS_VREF_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Set BWD Tx Driving Strength ---> 0x48 for eCBUS Electrical CTS
    // 0x48 Demo Board:
    // Swing = 300 (250~400mV), P2P = 460 (<500mV), Rising/Falling = 800/800 (500~1000ps)
    // 0x47: Demo Board:
    // Swing = 270 (250~400mV), P2P = 400 (<500mV), Rising/Falling = 770/760 (500~1000ps)
    ScalerSetByte(P5E_05_EBUS_VREF_CTRL_1, 0x48);

    // Manual Set Z0 to Code 8 (50 phm)
    ScalerSetBit(P5E_06_ECBUS_Z0_CTRL_0, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
    ScalerSetByte(P5E_07_ECBUS_Z0_CTRL_1, 0x88);

    // Disable FWD Clk De-Glitch
    ScalerSetBit(P5E_08_ECBUS_DATA_CTRL, ~_BIT1, 0x00);

    // Set APHY to AC-Coupling Mode
    ScalerSetBit(P5E_0A_ECBUS_RESERVED_1, ~_BIT5, _BIT5);

    // Set eCBUS APHY Slew Rate to Max Slot(Min Timing) ---> 000
    ScalerSetBit(P5E_09_ECBUS_RESERVED_0, ~(_BIT3 | _BIT2), 0x00);
    ScalerSetBit(P5E_08_ECBUS_DATA_CTRL, ~_BIT4, 0x00);


    ////////////////////////////////////
    /////// Digital PHY Configure //////
    ////////////////////////////////////

    // Set Bubble Remove Stage ---> Stage 2
    ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~(_BIT4 | _BIT3), _BIT4);

    // Enable Stage Circuit Safe debounce Mode ---> Debounce 4 COMMA2 Symbol for Stat_Ok
    ScalerSetBit(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT4, _BIT4);

    // Set Stage Circuit Timeout ---> 40ms
    ScalerSetByte(P6C_A4_ECBUS_DPHY_STAT_CONFIG_1, 0xC8);

    // Set Stage Circuit Difference Threshold ---> 4 (of x40 Samples)
    ScalerSetByte(P6C_A5_ECBUS_DPHY_STAT_CONFIG_2, 0x04);

    // Set Nth Calibration Done ---> Stop Nth Adaption When TMOUT [0x2BB9]
    ScalerSetBit(P6C_A9_ECBUS_DPHY_CALIB_CTRL, ~_BIT3, _BIT3);

    // Set ini Circuit Timeout ---> 480 Tbit
    ScalerSetByte(P6C_AA_ECBUS_DPHY_INI_CONFIG_1, 0x10);

    // Set ini Circuit Wait Time ---> 4 Tbit
    ScalerSetByte(P6C_AB_ECBUS_DPHY_INI_CONFIG_2, 0x04);

    // Set Nth initial Value ---> 20.5 (of x40 Samples)
    ScalerSetByte(P6C_AC_ECBUS_DPHY_INI_CONFIG_3, 0x14);

    // Set ini Circuit Count ---> 120 Tbis
    ScalerSetBit(P6C_AD_ECBUS_DPHY_INI_CONFIG_4, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Set Nth_0/Nth_1 Equal Tolerance ---> 0 (Tbit Count)
    ScalerSetBit(P6C_AD_ECBUS_DPHY_INI_CONFIG_4, ~_BIT0, 0x00);
    ScalerSetByte(P6C_AE_ECBUS_DPHY_INI_CONFIG_5, 0x00);

    // Set D-PHY Tx Data Delay ---> 8 Tbit (As Co-Sim Result)
    ScalerSetBit(P6C_B3_ECBUS_DPHY_TX_PHASE_CONFIG_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x08);

    // Set D-PHY Tx Phase Initial Value for No Calibration ---> (FW Setting Depends on Experiment)
    ScalerSetByte(P6C_B4_ECBUS_DPHY_TX_PHASE_CONFIG_2, 0x04);

    // Set Nth Adaption Mode ---> (One_Avg & Zero_Avg) Mode
    ScalerSetByte(P6C_B8_ECBUS_DPHY_ADAPT_CTRL, 0x00);

    // Set Adapt_timer ---> 200us (0x2BA9 Enable)
    ScalerSetByte(P6C_B9_ECBUS_DPHY_ADAPT_CONFIG_1, 0x01);

    // Set D-PHY Rx Comma2 Timeout ---> 50ms
    ScalerSetByte(P6C_C0_ECBUS_DPHY_CONFIG, 0xFA);


    ////////////////////////////////////
    /////// ECBUS-S MAC Setting ////////
    ////////////////////////////////////

    //-------- Default Value Modify --------//

    // CBUS1/eMSC In-Out Swap Set to LSB First
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Comma Pattern MSB / LSB Swap
    ScalerSetBit(P6C_01_ECBUS_STARTUP_CONFIG, ~_BIT6, _BIT6);

    // COMMA Pattern Disparity Check --> Not Check
    ScalerSetBit(P6C_02_ECBUS_STARTUP_DET, ~(_BIT4 | _BIT3 | _BIT1), 0x00);

    // Enable eCBUS-S TDM IDLE Slot Detection
    ScalerSetBit(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT3, 0x00);

    // Enable COM1-IDLE Check when Sync Loss
    ScalerSetBit(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT4 | _BIT3 | _BIT1), _BIT4);

    // CRC Result Sending Swap Set to LSB First
    ScalerSetBit(P6C_3E_ECBUS_GLOBAL_CTRL, ~_BIT4, 0x00);


    //-------- COMMA Start Up Configuration --------//

    // FW Set BWD Data Type to Sent BWD "0" (0x00 IDLE).
    ScalerSetBit(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

    // Set FWD COMMA2 Detection Debounce Level --> Max 8 State
    ScalerSetBit(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Set FWD COMMA2_LOST Detection Threshold Level --> Max 8 State
    ScalerSetBit(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));


    //-------- TDM Slot Sync Configuration --------//

    // Set FWD COM1 Detection Debounce Level ---> 8 Symbols
    ScalerSetBit(P6C_05_ECBUS_TDM_SYNC_CONFIG_1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Set FWD COM1_Miss Detection Threshold Level for HW Use Only
    ScalerSetBit(P6C_05_ECBUS_TDM_SYNC_CONFIG_1, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // Set FWD IDLE Error Detection Threshold Level
    ScalerSetBit(P6C_05_ECBUS_TDM_SYNC_CONFIG_1, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Set FWD COM2 Detection Debounce Level --> 8 Stages
    ScalerSetBit(P6C_05_ECBUS_TDM_SYNC_CONFIG_1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set TDM Sync Loss Threshold Level ---> 2 Non-COM2
    ScalerSetByte(P2C_06_ECBUS_TDM_SYNC_CONFIG_2, 0x02);

    // Set TDM Slot Tx Offset ---> M+3 Slots + N Cycles (Z2 Margin = 11-0 ~ 12-3)
    ScalerSetByte(P6C_09_ECBUS_TDM_SYNC_TX_OFFSET, 0x85);

    // Set TDM Slot Rx Offset Start Point ---> M Slots + N Cycles
    ScalerSetByte(P6C_0A_ECBUS_TDM_SYNC_RX_OFFSET, 0xA0);

    // Set TDM Slot Rx Offset Check Range ---> 8 Slots
    ScalerSetBit(P6C_0B_ECBUS_TDM_SYNC_RESERVE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable Mark2 Accapt Option
    ScalerSetBit(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT0, _BIT0);


    //-------- eMSC Link Training Configuration --------//

    // Set Rx Received Sync Symbols Detection Debounce Level ---> 4 Symbols
    ScalerSetBit(P6C_0D_ECBUS_EMSC_SYNC_CONFIG_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Set Rx Received Sync Symbols Error Detection Threshold Level ---> 1 Symbols (No Debounde)
    ScalerSetBit(P6C_0D_ECBUS_EMSC_SYNC_CONFIG_1, ~(_BIT4 | _BIT3), 0x00);

    // Set Rx Received Sync Symbols Loss Debounce Level ---> 4 Symbols
    ScalerSetBit(P6C_0D_ECBUS_EMSC_SYNC_CONFIG_1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Set Rx Received Sync Symbols Threshold Level ---> 260 Sync
    ScalerSetBit(P6C_0E_ECBUS_EMSC_SYNC_CONFIG_2, ~(_BIT3 | _BIT2), 0x00);

    // Set Tx Transmitted Sync Symbols Threshold Level ---> 290 Sync
    ScalerSetBit(P6C_0E_ECBUS_EMSC_SYNC_CONFIG_2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));


    //-------- eMSC Block Transaction Configuration --------//

    // Set Rx Ignore Bytes When Rx Wait ---> 260 Bytes
    ScalerSetBit(P6C_23_ECBUS_EMSC_TRANS_CONFIG_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // Set Timeout of Waiting ACK ---> 2.0ms
    ScalerSetBit(P6C_24_ECBUS_EMSC_TRANS_CONFIG_2, ~(_BIT7 | _BIT6), 0x00);

    // Set Number of Tx Retry ---> 4 Times
    ScalerSetBit(P6C_24_ECBUS_EMSC_TRANS_CONFIG_2, ~(_BIT5 | _BIT4), _BIT5);

    // Set Tx Retry Wait Time ---> 2.0ms
    ScalerSetBit(P6C_24_ECBUS_EMSC_TRANS_CONFIG_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);


    //-------- eCBUS BIST Configuration --------//

    // Set eCBUS Rx BIST Receiving Debounce Level ---> 1 Symbols (No Debounde)
    ScalerSetBit(P6C_24_ECBUS_EMSC_TRANS_CONFIG_2, ~(_BIT5 | _BIT4), 0x00);
}


//--------------------------------------------------
// Description : oCBUS-ECBUS-S Change Mode Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5EnableECBUSMode(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        ////////////////////////////////////
        //////// Analog PHY Setting ////////
        ////////////////////////////////////

        // Enable 25 ohm and 50 ohm Resister
        ScalerSetBit(P5E_06_ECBUS_Z0_CTRL_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

        // Enable eCBUS-S APHY
        ScalerSetBit(P5E_00_ECBUS_EN, ~_BIT7, _BIT7);


        ////////////////////////////////////
        //////// Digital PHY Setting ///////
        ////////////////////////////////////

        // Hold ecbus_dphy_rstn Low
        ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT7, 0x00);

        // Enable eCBUS-S Mac Circuit
        ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT6, _BIT6);


        ////////////////////////////////////
        ////// Clk Detection Setting ///////
        ////////////////////////////////////

        CLR_TMDS_RX5_PHY_SET();

        // Disable Freq. Detection
        ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        // Choose Measure Clk to ECBUS Clk
        ScalerSetBit(P7E_1B_CMU_01, ~_BIT1, _BIT1);

        // Set CMU Reference Clk Source from ECBUS, Disable MHL 2.0 OP for MHL 3.0
        ScalerSetBit(P7E_1B_CMU_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

        // Measure Clk = TMDS Clk
        // Freq. Reference Counter = 1000
        // TMDS Offset = 1/128
        // Stable Time = 0x7F = about 5ms

        // Set Upper Bound (75M x 1.04)
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

        // Set MHL 3.0 ECBUS CLK Lower bound (75M x 0.96)
        ScalerSetByte(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_MHL3_ECBUS_FREQ_NORMAL_LOWER_BOUND));
        ScalerSetByte(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_MHL3_ECBUS_FREQ_NORMAL_LOWER_BOUND));

        // Disable Freq. Unstable IRQ
        ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), _BIT2);

        // Enable Freq. Stable IRQ
        ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Clear IRQ Pending Flag
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_60_PORT_PAGE74_HDMI_INTCR, ~_BIT7, _BIT7);

        // Start Freq. Detection
        ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);


        ////////////////////////////////////
        /////// ECBUS-S MAC Setting ////////
        ////////////////////////////////////

        // Hold ecbus_reset High
        ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);

        // Enable eCBUS-S Mac Circuit
        ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT3, _BIT3);

        // Reset CBUS / CBUS1 Command Frquest, Clear FW0
        ScalerSetBit(P6A_DE_CBUS_CTRL_3E, ~(_BIT7 | _BIT6), _BIT6);

        // Toggle oCBUS Mac Circuit Reset
        ScalerSetBit(P6A_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit(P6A_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Reset MHL DevCap Registor Values After oCBUS Mac Reset
        ScalerMHLRx5SetDevCapReg();

        // Enable CBUS 3.0-CBUS1 Mac Circuit
        ScalerSetBit(P6A_00_OCBUS_CTRL_00, ~_BIT6, _BIT6);

        EX0 = 1;

        // Record eCBUS Mode Up
        ScalerSetBit(P6C_50_ECBUS_HW_FSM_5, ~_BIT2, _BIT2);
    }
    else
    {
        ////////////////////////////////////
        //////// Analog PHY Setting ////////
        ////////////////////////////////////

        // Disable 25 ohm and 50 ohm Resister
        ScalerSetBit(P5E_06_ECBUS_Z0_CTRL_0, ~(_BIT3 | _BIT2), 0x00);

        // Disable eCBUS-S APHY
        ScalerSetBit(P5E_00_ECBUS_EN, ~_BIT7, 0x00);


        ////////////////////////////////////
        //////// Digital PHY Setting ///////
        ////////////////////////////////////

        // Hold ecbus_dphy_rstn Low
        ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT7, 0x00);

        // Disable eCBUS-S Mac Circuit
        ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT6, 0x00);


        ////////////////////////////////////
        ////// Clk Detection Setting ///////
        ////////////////////////////////////

        CLR_TMDS_RX5_PHY_SET();

        // Disable Freq. Detection
        ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        // Choose Measure Clk to ECBUS Clk
        ScalerSetBit(P7E_1B_CMU_01, ~_BIT1, 0x00);

        // Set CMU Reference Clk Source from ECBUS, Disable MHL 2.0 OP for MHL 3.0
        ScalerSetBit(P7E_1B_CMU_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

        // Measure Clk = TMDS Clk
        // Freq. Reference Counter = 1000
        // TMDS Offset = 1/128
        // Stable Time = 0x7F = about 5ms

        // Set Upper Bound (75M x 1.04)
        ScalerSetByte(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
        ScalerSetByte(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

        // Set TMDS Clk Lower bound (25M x 0.96)
        ScalerSetByte(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
        ScalerSetByte(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

        // Disable Freq. Unstable IRQ
        ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), _BIT2);

        // Enable Freq. Stable IRQ
        ScalerSetBit(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Clear IRQ Pending Flag
        ScalerSetDataPortBit(P74_C9_HDMI_AP, _P74_CA_PT_60_PORT_PAGE74_HDMI_INTCR, ~_BIT7, _BIT7);

        // Start Freq. Detection
        ScalerSetBit(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);


        ////////////////////////////////////
        /////// ECBUS-S MAC Setting ////////
        ////////////////////////////////////

        // Reset eCBUS-S Mac Circuit (Hold ECBUS Reset -> Disable eCBUS Power)
        ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT3, 0x00);

        // Reset CBUS / CBUS1 Command Frquest
        ScalerSetBit(P6A_DE_CBUS_CTRL_3E, ~_BIT7, 0x00);

        // Disable CBUS1 Mac Circuit
        ScalerSetBit(P6A_00_OCBUS_CTRL_00, ~(_BIT7 | _BIT6), 0x00);

        // Record eCBUS Mode Down
        ScalerSetBit(P6C_50_ECBUS_HW_FSM_5, ~_BIT3, _BIT3);
    }
}

//--------------------------------------------------
// Description  : MHL eCBUS-S Reset Proc for D0 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5EnableECBUSMode_EXINT0(bit bEnable) using 1
{
    if(bEnable == _ENABLE)
    {
        ////////////////////////////////////
        //////// Analog PHY Setting ////////
        ////////////////////////////////////

        // Enable 25 ohm and 50 ohm Resister
        ScalerSetBit_EXINT(P5E_06_ECBUS_Z0_CTRL_0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

        // Enable eCBUS-S APHY
        ScalerSetBit_EXINT(P5E_00_ECBUS_EN, ~_BIT7, _BIT7);


        ////////////////////////////////////
        //////// Digital PHY Setting ///////
        ////////////////////////////////////

        // Hold ecbus_dphy_rstn Low
        ScalerSetBit_EXINT(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT7, 0x00);

        // Enable eCBUS-S Mac Circuit
        ScalerSetBit_EXINT(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT6, _BIT6);


        ////////////////////////////////////
        ////// Clk Detection Setting ///////
        ////////////////////////////////////

        CLR_TMDS_RX5_PHY_SET();

        // Disable Freq. Detection
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        // Choose Measure Clk to ECBUS Clk
        ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT1, _BIT1);

        // Set CMU Reference Clk Source from ECBUS, Disable MHL 2.0 OP for MHL 3.0
        ScalerSetBit_EXINT(P7E_1B_CMU_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

        // Measure Clk = TMDS Clk
        // Freq. Reference Counter = 1000
        // TMDS Offset = 1/128
        // Stable Time = 0x7F = about 5ms

        // Set Upper Bound (75M x 1.04)
        ScalerSetByte_EXINT(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
        ScalerSetByte_EXINT(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

        // Set MHL 3.0 ECBUS CLK Lower bound (75M x 0.96)
        ScalerSetByte_EXINT(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_MHL3_ECBUS_FREQ_NORMAL_LOWER_BOUND));
        ScalerSetByte_EXINT(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_MHL3_ECBUS_FREQ_NORMAL_LOWER_BOUND));

        // Disable Freq. Unstable IRQ
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), _BIT2);

        // Enable Freq. Stable IRQ
        ScalerSetBit_EXINT(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Back Up C9_CA Port Auto Increase
        pData_EXINT[0] = ScalerGetByte_EXINT(P74_C8_HDMI_APC);

        // Clear IRQ Pending Flag
        ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_60_PORT_PAGE74_HDMI_INTCR);
        ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT7, _BIT7);

        // Recovery Up C9_CA Port Auto Increase
        ScalerSetByte_EXINT(P74_C8_HDMI_APC, pData_EXINT[0]);

        // Start Freq. Detection
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);


        ////////////////////////////////////
        /////// ECBUS-S MAC Setting ////////
        ////////////////////////////////////

        // Hold ecbus_reset High
        ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);

        // Enable eCBUS-S Mac Circuit
        ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT3, _BIT3);

        // Reset CBUS / CBUS1 Command Frquest, Clear FW0
        ScalerSetBit_EXINT(P6A_DE_CBUS_CTRL_3E, ~(_BIT7 | _BIT6), _BIT6);

        // Toggle oCBUS Mac Circuit Reset
        ScalerSetBit_EXINT(P6A_A0_CBUS_CTRL_00, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P6A_A0_CBUS_CTRL_00, ~_BIT7, 0x00);

        // Enable CBUS 3.0 Mac Circuit
        ScalerSetBit_EXINT(P6A_00_OCBUS_CTRL_00, ~_BIT6, _BIT6);

        EX0 = 1;

        // Record eCBUS Mode Up
        ScalerSetBit_EXINT(P6C_50_ECBUS_HW_FSM_5, ~_BIT4, _BIT4);
    }
    else
    {
        ////////////////////////////////////
        //////// Analog PHY Setting ////////
        ////////////////////////////////////

        // Disable 25 ohm and 50 ohm Resister
        ScalerSetBit_EXINT(P5E_06_ECBUS_Z0_CTRL_0, ~(_BIT3 | _BIT2), 0x00);

        // Disable eCBUS-S APHY
        ScalerSetBit_EXINT(P5E_00_ECBUS_EN, ~_BIT7, 0x00);


        ////////////////////////////////////
        //////// Digital PHY Setting ///////
        ////////////////////////////////////

        // Hold ecbus_dphy_rstn Low
        ScalerSetBit_EXINT(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT7, 0x00);

        // Disable eCBUS-S Mac Circuit
        ScalerSetBit_EXINT(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT6, 0x00);


        ////////////////////////////////////
        ////// Clk Detection Setting ///////
        ////////////////////////////////////

        CLR_TMDS_RX5_PHY_SET();

        // Disable Freq. Detection
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        // Choose Measure Clk to ECBUS Clk
        ScalerSetBit_EXINT(P7E_1B_CMU_01, ~_BIT1, 0x00);

        // Set CMU Reference Clk Source from ECBUS, Disable MHL 2.0 OP for MHL 3.0
        ScalerSetBit_EXINT(P7E_1B_CMU_01, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5));

        // Measure Clk = TMDS Clk
        // Freq. Reference Counter = 1000
        // TMDS Offset = 1/128
        // Stable Time = 0x7F = about 5ms

        // Set Upper Bound (75M x 1.04)
        ScalerSetByte_EXINT(P74_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
        ScalerSetByte_EXINT(P74_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

        // Set TMDS Clk Lower bound (25M x 0.96)
        ScalerSetByte_EXINT(P74_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
        ScalerSetByte_EXINT(P74_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

        // Disable Freq. Unstable IRQ
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), _BIT2);

        // Enable Freq. Stable IRQ
        ScalerSetBit_EXINT(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Back Up C9_CA Port Auto Increase
        pData_EXINT[0] = ScalerGetByte_EXINT(P74_C8_HDMI_APC);

        // Clear IRQ Pending Flag
        ScalerSetByte_EXINT(P74_C9_HDMI_AP, _P74_CA_PT_60_PORT_PAGE74_HDMI_INTCR);
        ScalerSetBit_EXINT(P74_CA_HDMI_DP, ~_BIT7, _BIT7);

        // Recovery Up C9_CA Port Auto Increase
        ScalerSetByte_EXINT(P74_C8_HDMI_APC, pData_EXINT[0]);

        // Start Freq. Detection
        ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);


        ////////////////////////////////////
        /////// ECBUS-S MAC Setting ////////
        ////////////////////////////////////

        // Reset eCBUS-S Mac Circuit (Hold ECBUS Reset -> Disable eCBUS Power)
        ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);
        ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT3, 0x00);

        // Reset CBUS / CBUS1 Command Frquest
        ScalerSetBit_EXINT(P6A_DE_CBUS_CTRL_3E, ~_BIT7, 0x00);

        // Disable CBUS1 Mac Circuit
        ScalerSetBit_EXINT(P6A_00_OCBUS_CTRL_00, ~(_BIT7 | _BIT6), 0x00);

        // Record eCBUS Mode Donw
        ScalerSetBit_EXINT(P6C_50_ECBUS_HW_FSM_5, ~_BIT5, _BIT5);
    }
}


//--------------------------------------------------
// Description  : MHL eCBUS-S Reset Proc for D5 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSResetProc(void)
{
    ///////////////////////////////////
    //////// Analog PHY Setting ///////
    ///////////////////////////////////

    // Reset APHY to Default State
    ScalerSetByte(P5E_01_ECBUS_STEP_CTRL, 0x0A);


    //////////////////////////////////
    //////// Digital PHY Reset ///////
    //////////////////////////////////

    // Disable FWD Rx Rising Auto K
    ScalerSetBit(P6C_A1_ECBUS_DPHY_EDGE_CTRL, ~_BIT0, 0x00);

    // Disable FWD Edge Rising K / Edge Manual
    ScalerSetByte(P6C_A3_ECBUS_DPHY_STAT_CTRL, 0x00);

    // Disable Tx k / Nth Adaption / Nth Manual Mode / Adaption End / rxvalid_reload
    ScalerSetByte(P6C_A9_ECBUS_DPHY_CALIB_CTRL, 0x80);


    //////////////////////////////////
    //////// Digital Mac Reset ///////
    //////////////////////////////////

    // Reset eCBUS-S Mac Circuit (Hold ECBUS Reset -> Disable eCBUS Power)
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT6, 0x00);

    // Disable Comma2 Detection Circuit
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT0, 0x00);

    // Disable Respond Com2 Auto
    // Deavtice TDM Active Mode
    // Disable Com1 Detection Circuit
    ScalerSetBit(P6C_04_ECBUS_TDM_SYNC_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), _BIT3);

    // Disable chk_wneh_loss
    // Reset TDM IRQs
    ScalerSetBit(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // Enable eMSC Reset Bit ---> Clear Tx/Rx SRAM / Hang eMSC Circuit FSM
    ScalerSetBit(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, _BIT4);

    // Reset eMSC IRQ Flags
    ScalerSetBit(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

    //////////////////////////////////
    ///////// eCBUS BIST Reset ///////
    //////////////////////////////////

    // Disable eCBUS BIST Function
    ScalerSetBit(P6C_34_ECBUS_BIST_CTRL, ~(_BIT4 | _BIT3), 0x00);

    // Force PRBS BIST Mode For eCBUS Electrical CTS - Disable Mac Force Test Out
    ScalerSetBit(P6C_52_ECBUS_TEST_FORCE_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ///////////////////////////////
    /////// Video Mac Reset ///////
    ///////////////////////////////

    // Disable MHL 3.0 Video Mac
    ScalerSetBit(P79_00_MHL_EN, ~_BIT7, 0x00);

    // Disable MHL 3.0 S2P Fifo
    // Disable Audio Accumulation
    ScalerSetBit(P79_01_MHL_FIFO_CTRL, ~(_BIT7 | _BIT3), 0x00);

    // Disable RR Align Auto Mode
    ScalerSetBit(P79_07_MHL_DATA_ALIGN_CTRL, ~_BIT3, 0x00);

    // Disable MHL 3.0 Measure
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, 0x00);

    // Clear MHL Mode Error Flag
    ScalerSetBit(P79_38_MHL_MEASURE_24, ~_BIT6, _BIT6);


    /////////////////////////////////
    /// Reset FW Timer / WD_Timer ///
    /////////////////////////////////

    // Cancel ECBUS WD TimerEvents
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_SEND_BWD_COMMA1);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA1);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA2);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COMMA2_TMOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_TDM_SYNC_TMOUT);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_RESET_HOLD_IDLE);
    ScalerTimerWDCancelTimerEvent(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COM1);

    // Cancel ECBUS Scaler TimerEvents
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_MHL_VERSION);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_FWD_CLK);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_BIST_DURATION);


    /////////////////////////////////////
    /////////// Reset FW Flags //////////
    /////////////////////////////////////

    // Clear eCBUS Start Up TMOUT Flags
    CLR_MHL3_RX5_ECBUS_START_UP_TMOUT();
    CLR_MHL3_RX5_WAIT_SRC_MHL_VERSION_TMOUT();
    CLR_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP_TMOUT();
    CLR_MHL3_RX5_ECBUS_CLK_STABLE();

    // Clear eCBUS eMSC Flags
    CLR_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT();

    // Reset VC Count
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_COUNT(0);

    ScalerMHL3Rx5ECBUSVirtualChannelInitialAssign();

    // Clear eCBUS AV Link Flags
    SET_MHL3_RX5_AV_LINK_RATE(_ECBUS_LINK_RATE_NULL);
    SET_MHL3_RX5_AV_LINK_N_CODE(_ECBUS_N_CODE_NULL);
    CLR_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT();
    SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(_MHL3_VIDEO_FORMAT_NULL);
    SET_MHL3_RX5_VIEW_PIXEL_DIVIDER(_MHL3_VIDEO_MODE_DIV_ERROR);

    SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_INITIAL);


    /////////////////////////////////////
    /// Reset FW Recorded State / Info //
    /////////////////////////////////////

    // Reset(Clear) eCBUS_INT Flow Recorded State
    ScalerSetByte(P6C_5F_ECBUS_RESERVE_2, 0x00);
    ScalerSetBit(P6C_60_ECBUS_DPHY_CAP0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Reset Recorded "_WAIT_COMMA2_END_TIME"
    ScalerSetByte(P6C_5D_ECBUS_RESERVE_0, 0x00);

    // Reset Recorded "_WAIT_ACTIVE_END_TIME"
    ScalerSetByte(P6C_5E_ECBUS_RESERVE_1, 0x00);
}

//--------------------------------------------------
// Description  : MHL eCBUS-S Reset Proc for D0 Port (INT Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSResetProc_EXINT0(void) using 1
{
    ///////////////////////////////////
    //////// Analog PHY Setting ///////
    ///////////////////////////////////

    // Reset APHY to Default State
    ScalerSetByte_EXINT(P5E_01_ECBUS_STEP_CTRL, 0x0A);


    //////////////////////////////////
    //////// Digital PHY Reset ///////
    //////////////////////////////////

    // Disable FWD Rx Rising Auto K
    ScalerSetBit_EXINT(P6C_A1_ECBUS_DPHY_EDGE_CTRL, ~_BIT0, 0x00);

    // Disable FWD Edge Rising K / Edge Manual
    ScalerSetByte_EXINT(P6C_A3_ECBUS_DPHY_STAT_CTRL, 0x00);

    // Disable Tx k / Nth Adaption / Nth Manual Mode / Adaption End / rxvalid_reload
    ScalerSetByte_EXINT(P6C_A9_ECBUS_DPHY_CALIB_CTRL, 0x80);


    //////////////////////////////////
    //////// Digital Mac Reset ///////
    //////////////////////////////////

    // Reset eCBUS-S Mac Circuit (Hold ECBUS Reset -> Disable eCBUS Power)
    ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT6, 0x00);

    // Disable Comma2 Detection Circuit
    ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT0, 0x00);

    // Disable Respond Com2 Auto
    // Deavtice TDM Active Mode
    // Disable Com1 Detection Circuit
    ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~(_BIT7 | _BIT5 | _BIT4 | _BIT3), _BIT3);

    // Disable chk_wneh_loss
    // Reset TDM IRQs
    ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

    // Enable eMSC Reset Bit ---> Clear Tx/Rx SRAM / Hang eMSC Circuit FSM
    ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, _BIT4);

    // Reset eMSC IRQs
    ScalerSetBit_EXINT(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

    //////////////////////////////////
    ///////// eCBUS BIST Reset ///////
    //////////////////////////////////

    // Disable eCBUS BIST Function
    ScalerSetBit_EXINT(P6C_34_ECBUS_BIST_CTRL, ~(_BIT4 | _BIT3), 0x00);

    // Force PRBS BIST Mode For eCBUS Electrical CTS - Disable Mac Force Test Out
    ScalerSetBit_EXINT(P6C_52_ECBUS_TEST_FORCE_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ///////////////////////////////
    /////// Video Mac Reset ///////
    ///////////////////////////////

    // Disable MHL 3.0 Video Mac
    ScalerSetBit_EXINT(P79_00_MHL_EN, ~_BIT7, 0x00);

    // Disable MHL 3.0 S2P Fifo
    // Disable Audio Accumulation
    ScalerSetBit_EXINT(P79_01_MHL_FIFO_CTRL, ~(_BIT7 | _BIT3), 0x00);

    // Disable RR Align Auto Mode
    ScalerSetBit_EXINT(P79_07_MHL_DATA_ALIGN_CTRL, ~_BIT3, 0x00);

    // Disable MHL 3.0 Measure
    ScalerSetBit_EXINT(P79_20_MHL_MEASURE_0, ~_BIT7, 0x00);

    // Clear MHL Mode Error Flag
    ScalerSetBit_EXINT(P79_38_MHL_MEASURE_24, ~_BIT6, _BIT6);


    /////////////////////////////////
    /// Reset FW Timer / WD_Timer ///
    /////////////////////////////////

    // Cancel ECBUS WD TimerEvents
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_SEND_BWD_COMMA1);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA1);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA2);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COMMA2_TMOUT);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_TDM_SYNC_TMOUT);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_RESET_HOLD_IDLE);
    ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COM1);

    // Cancel ECBUS Scaler TimerEvents
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_MHL_VERSION);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_FWD_CLK);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP);
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_BIST_DURATION);


    /////////////////////////////////////
    /////////// Reset FW Flags //////////
    /////////////////////////////////////

    // Clear eCBUS Start Up TMOUT Flags
    CLR_MHL3_RX5_ECBUS_START_UP_TMOUT();
    CLR_MHL3_RX5_WAIT_SRC_MHL_VERSION_TMOUT();
    CLR_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP_TMOUT();
    CLR_MHL3_RX5_ECBUS_CLK_STABLE();

    // Clear eCBUS eMSC Flags
    CLR_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT();

    // Reset VC Count
    SET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_COUNT(0);

    ScalerMHL3Rx5ECBUSVirtualChannelInitialAssign_EXINT0();

    // Clear eCBUS AV Link Flags
    SET_MHL3_RX5_AV_LINK_RATE(_ECBUS_LINK_RATE_NULL);
    SET_MHL3_RX5_AV_LINK_N_CODE(_ECBUS_N_CODE_NULL);
    CLR_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT();
    SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(_MHL3_VIDEO_FORMAT_NULL);
    SET_MHL3_RX5_VIEW_PIXEL_DIVIDER(_MHL3_VIDEO_MODE_DIV_ERROR);

    SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_INITIAL);


    /////////////////////////////////////
    /// Reset FW Recorded State / Info //
    /////////////////////////////////////

    // Reset(Clear) eCBUS_INT Flow Recorded State
    ScalerSetByte_EXINT(P6C_5F_ECBUS_RESERVE_2, 0x00);
    ScalerSetBit_EXINT(P6C_60_ECBUS_DPHY_CAP0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Reset Recorded "_WAIT_COMMA2_END_TIME"
    ScalerSetByte_EXINT(P6C_5D_ECBUS_RESERVE_0, 0x00);

    // Reset Recorded "_WAIT_ACTIVE_END_TIME"
    ScalerSetByte_EXINT(P6C_5E_ECBUS_RESERVE_1, 0x00);
}

//--------------------------------------------------
// Description : Int Process for eCBUS for D0 Port
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSIntHandler_EXINT0(void) using 1
{
    // Check eCBUS DPHY State Circuit Ok
    if(((ScalerGetByte_EXINT(P6C_C4_ECBUS_DPHY_IRQ) & 0x03) == 0x03) &&
       ((GET_MHL3_RX5_ECBUS_MODE() == _ON) || (GET_MHL3_RX5_BIST_TESTING() == _ON)))
    {
        // Disable eCBUS-S FWD Stat_ok IRQ and Clear eCBUS-S FWD Stat_ok IRQ Flag
        ScalerSetBit_EXINT(P6C_C4_ECBUS_DPHY_IRQ, ~(_BIT4 | _BIT1), 0x00);
        ScalerSetBit_EXINT(P6C_C4_ECBUS_DPHY_IRQ, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);

        // ----- Manual Set Nth, For Initial Unstable 0/1 Change -----//
        ScalerSetByte_EXINT(P6C_BA_ECBUS_DPHY_ADAPT_CONFIG_2, 0x13);
        ScalerSetByte_EXINT(P6C_BB_ECBUS_DPHY_ADAPT_CONFIG_3, 0x13);
        ScalerSetBit_EXINT(P6C_A9_ECBUS_DPHY_CALIB_CTRL, ~_BIT4, _BIT4);

        // Enable NTH Adaption (Option)
        // ScalerSetBit_EXINT(P6C_A9_ECBUS_DPHY_CALIB_CTRL, ~_BIT5, _BIT5);

        // Enable eCBUS-S FWD COMMA2 Detection Circuit
        ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT0, _BIT0);

        // Enable eCBUS-S FWD COMMA2 IRQ and Clear eCBUS-S FWD COMMA2 IRQ Flag
        ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT1), _BIT3);
        ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

        // Record eCBUS_INT Flow State-4 (FWD State_ok Interrupt)
        ScalerSetBit_EXINT(P6C_5F_ECBUS_RESERVE_2, ~_BIT3, _BIT3);
    }

    // If eCBUS Mac IRQ Happen (eCBUS Global IRQ Flag)
    if((ScalerGetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, _BIT2) == _BIT2) &&
       ((GET_MHL3_RX5_ECBUS_MODE() == _ON) || (GET_MHL3_RX5_BIST_TESTING() == _ON)))
    {
        // Check FWD COMMA2 (IRQ_Flag & IRQ_EN)
        if((ScalerGetByte_EXINT(P6C_02_ECBUS_STARTUP_DET) & (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // Disable eCBUS-S FWD COMMA2 IRQ
            ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

            // Toggle eCBUS D-PHY Stat_en to Re-start detecting FWD_Clk -> FWD_COMMA2 on eCBUS
            ScalerSetBit_EXINT(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT7, _BIT7);

            // Record State Max/Min of Source FWD Clk Period
            pData_EXINT[0] = ScalerGetByte_EXINT(P6C_A6_ECBUS_DPHY_STAT_RESULT_1);
            pData_EXINT[1] = ScalerGetByte_EXINT(P6C_A7_ECBUS_DPHY_STAT_RESULT_2);

            // ----- Manual Update Nth 0/1 Values After Comma2 Received ----- //
            ScalerSetByte_EXINT(P6C_BA_ECBUS_DPHY_ADAPT_CONFIG_2, (pData_EXINT[0] + pData_EXINT[1] + 1) / 2);
            ScalerSetByte_EXINT(P6C_BB_ECBUS_DPHY_ADAPT_CONFIG_3, (pData_EXINT[0] + pData_EXINT[1] + 1) / 2);

            // Enable NTH Adaption After COMMA2 Received (Option)
            // ScalerSetBit_EXINT(P6C_A9_ECBUS_DPHY_CALIB_CTRL, ~_BIT5, _BIT5);

            // Disable Manual Nth After Enable NTH Adaption (Option)
            // ScalerSetBit_EXINT(P6C_A9_ECBUS_DPHY_CALIB_CTRL, ~_BIT4, 0x00);

            // Record Time Point of "_WAIT_COMMA2_END_TIME"
            pData_EXINT[2] = ScalerTimerGetRecordTimer_EXINT0();

            // Cancel WD TimerEvent When Receive COMMA2
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COMMA2_TMOUT);

#if(_MHL3_ECBUS_STARTUP_DEBUG_MESSAGE == _ON)
            // If DebugMessage on --> Skip Receive FWD COMMA2 TMOUT Check
            if(_FALSE)
#else
            // Sink Receive FWD COMMA2 TMOUT --> Reset eCBUS-S Start Up
            if((pData_EXINT[2] < _MHL3_SOURCE_ECBUS_FWD_COMMA2_TMOUT_MIN) ||
               (pData_EXINT[2] > _MHL3_SOURCE_ECBUS_FWD_COMMA2_TMOUT_MAX))
#endif
            {
                // Record "_WAIT_COMMA2_END_TIME"
                ScalerSetByte_EXINT(P6C_5D_ECBUS_RESERVE_0, 0xFF);

                // Enable eCBUS-S Function Reset
                ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);

                // FW Set BWD Data Type to Sent BWD "0" (0x00 IDLE).
                ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

                // Set WD TimerEvent to Disable eCBUS-S Function Reset 200ms Later, Hold BWD 0x00(IDLE) 200ms
                ScalerTimerWDActivateTimerEvent_EXINT0(200, _SCALER_WD_TIMER_EVENT_RX5_ECBUS_RESET_HOLD_IDLE);

                // eCBUS Link Build Error #2
                ScalerSetByte_EXINT(P6C_5F_ECBUS_RESERVE_2, 0xE2);
            }
            // Sink Receive FWD COMMA2 Without TMOUT --> Keep Sent BWD COMMA1 15ms
            else
            {
                // Record "_WAIT_COMMA2_END_TIME"
                ScalerSetByte_EXINT(P6C_5D_ECBUS_RESERVE_0, pData_EXINT[2]);

                // Enable eCBUS-S FWD COMMA2_LOST IRQ and Clear eCBUS-S FWD COMMA2_LOST IRQ Flag
                ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT1), _BIT1);
                ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT1 | _BIT0), _BIT0);

                // Set WD TimerEvent to Keep eCBUS-S BWD Sending COMMA1
                ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA1);

                // Record eCBUS_INT Flow State-5 (DMac Comma2 Receive Interrupt)
                ScalerSetBit_EXINT(P6C_5F_ECBUS_RESERVE_2, ~_BIT4, _BIT4);
            }
        }

        // Check FWD COMMA2 LOST (IRQ_Flag & IRQ_EN)
        if((ScalerGetByte_EXINT(P6C_02_ECBUS_STARTUP_DET) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // Disable eCBUS-S FWD COMMA2_LOST IRQ and Clear eCBUS-S FWD COMMA2_LOST IRQ Flag
            ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT1), _BIT1);

            // If Already respond BWD COMMA2 => COMMA2_LOST_INT = SRC Enter Active State
            if(ScalerGetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, (_BIT5 | _BIT4)) == _BIT5)
            {
                // Record Timer Point of "_WAIT_ACTIVE_END_TIME"
                pData_EXINT[2] = ScalerTimerGetRecordTimer_EXINT0();

#if(_MHL3_ECBUS_STARTUP_DEBUG_MESSAGE == _ON)
                // If DebugMessage on --> Skip Receive FWD ACTIVE TMOUT Check
                if(_FALSE)
#else
                // Sink Receive FWD ACTIVE TMOUT --> Reset eCBUS-S Start Up
                if((pData_EXINT[2] < _MHL3_SOURCE_ECBUS_FWD_AVTIVE_TMOUT_MIN) ||
                   (pData_EXINT[2] > _MHL3_SOURCE_ECBUS_FWD_AVTIVE_TMOUT_MAX))
#endif
                {
                    // Record "_WAIT_ACTIVE_END_TIME"
                    ScalerSetByte_EXINT(P6C_5E_ECBUS_RESERVE_1, 0xFF);

                    // Enable eCBUS-S Function Reset
                    ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);

                    // FW Set BWD Data Type to Sent BWD "0" (0x00 IDLE).
                    ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

                    // Set WD TimerEvent to Disable eCBUS-S Function Reset 200ms Later, Hold BWD 0x00(IDLE) 200ms
                    ScalerTimerWDActivateTimerEvent_EXINT0(200, _SCALER_WD_TIMER_EVENT_RX5_ECBUS_RESET_HOLD_IDLE);

                    // eCBUS Link Build Error #3
                    ScalerSetByte_EXINT(P6C_5F_ECBUS_RESERVE_2, 0xE3);
                }
                // Sink Receive FWD ACTIVE Without TMOUT
                else
                {
                    // Record "_WAIT_ACTIVE_END_TIME"
                    ScalerSetByte_EXINT(P6C_5E_ECBUS_RESERVE_1, pData_EXINT[2]);

                    if(GET_MHL3_RX5_ECBUS_MODE() == _ON)
                    {
                        // Set WD TimerEvent to Keep eCBUS-S BWD Sending COMMA2
                        ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA2);
                    }
                    else if(GET_MHL3_RX5_BIST_TESTING() == _ON)
                    {
                        if((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_IMPEDENCE) == _MHL3_ECBUS_BIST_MODE_IMPEDENCE)
                        {
                            // TODO:
                        }

                        if((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_AVLINK_RX) == _MHL3_ECBUS_BIST_MODE_AVLINK_RX)
                        {
                            // TODO:
                        }

                        if((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_ECBUS_TX) == _MHL3_ECBUS_BIST_MODE_ECBUS_TX)
                        {
                            // Enable eCBUS BIST
                            ScalerSetBit_EXINT(P6C_34_ECBUS_BIST_CTRL, ~(_BIT4 | _BIT1), _BIT4);

                            // FW Set Enter TDM Active (HW Enter TDM_SYNC_INITIAL State)
                            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT5, _BIT5);
                        }

                        if((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_ECBUS_RX) == _MHL3_ECBUS_BIST_MODE_ECBUS_RX)
                        {
                            // Enable eCBUS BIST
                            ScalerSetBit_EXINT(P6C_34_ECBUS_BIST_CTRL, ~(_BIT4 | _BIT1), _BIT4);

                            // FW Set Enter TDM Active (HW Enter TDM_SYNC_INITIAL State)
                            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT5, _BIT5);
                        }

                        // FW Set BWD Data Type to Sent BWD 0 (IDLE)
                        ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

                        SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_START_UP_DONE);
                    }

                    // Record eCBUS_INT Flow State-7 (FWD Comma2 Loss Interrupt)
                    ScalerSetBit_EXINT(P6C_5F_ECBUS_RESERVE_2, ~_BIT6, _BIT6);
                }
            }
            // If Haven't respond BWD COMMA2 => COMMA2_LOST_INT = SRC FWD COMMA2 Lost(Error)
            else
            {
                // Enable eCBUS-S FWD COMMA2 IRQ and Clear eCBUS-S FWD COMMA2 IRQ Flag
                ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));

                // Cancel WD TimerEvent to Keep eCBUS-S BWD Sending COMMA1
                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA1);

                // Reset Recorded "_WAIT_ACTIVE_END_TIME"
                ScalerSetByte_EXINT(P6C_5E_ECBUS_RESERVE_1, 0x00);

                // Enable eCBUS-S Function Reset
                ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);

                // FW Set BWD Data Type to Sent BWD "0" (0x00 IDLE).
                ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

                // Set WD TimerEvent to Disable eCBUS-S Function Reset 200ms Later, Hold BWD 0x00(IDLE) 200ms
                ScalerTimerWDActivateTimerEvent_EXINT0(200, _SCALER_WD_TIMER_EVENT_RX5_ECBUS_RESET_HOLD_IDLE);

                // eCBUS Link Build Error #5
                ScalerSetByte_EXINT(P6C_5F_ECBUS_RESERVE_2, 0xE5);
            }
        }

        // Check FWD TDM Sync COM1 (IRQ_Flag & IRQ_EN)
        if((ScalerGetByte_EXINT(P6C_07_ECBUS_TDM_SYNC_DET_1) & (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // Disable eCBUS-S FWD COMMA2_LOST IRQ and Clear eCBUS-S FWD COMMA2_LOST IRQ Flag
            ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, ~(_BIT3 | _BIT1), _BIT1);

            // Disable eCBUS-S FWD TDM COM1 IRQ but not Clear eCBUS-S FWD TDM COM1 IRQ Flag
            ScalerSetBit_EXINT(P6C_07_ECBUS_TDM_SYNC_DET_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Process eCBUS TDM Sync Procedure, when Normal MHL3 Mode, Rather Tnen BIST Mode
            if(GET_MHL3_RX5_ECBUS_MODE() == _ON)
            {
                // Enable eCBUS-S FWD TDM_SYNC_DONE IRQ and Clear eCBUS-S FWD TDM_SYNC_DONE IRQ Flag
                ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT1), _BIT3);
                ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

                // Enable eMSC Reset Bit ---> Clear Tx/Rx SRAM / Hang eMSC Circuit FSM
                ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, _BIT4);

                // FW Set Enter TDM Active (HW Enter TDM_SYNC_INITIAL State)
                ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT5, _BIT5);

                // FW Set BWD Data Type to Sent BWD 0 (IDLE)
                ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA2);

                ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COM1);

                ScalerTimerWDActivateTimerEvent_EXINT0(60, _SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_TDM_SYNC_TMOUT);

                SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_START_UP_DONE);
            }

            // Record eCBUS_INT Flow State-8 (FWD TDM COM1 Receive Interrupt)
            ScalerSetBit_EXINT(P6C_5F_ECBUS_RESERVE_2, ~_BIT7, _BIT7);
        }

        // Check TDM SYNC DONE (IRQ_Flag & IRQ_EN)
        if((ScalerGetByte_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2) & (_BIT3 | _BIT2)) == (_BIT3 | _BIT2))
        {
            // Disable eCBUS-S FWD TDM_SYNC_DONE IRQ
            ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT2 | _BIT1), 0x00);

            // Clear eCBUS-S FWD TDM COM1 IRQ Flag
            ScalerSetBit_EXINT(P6C_07_ECBUS_TDM_SYNC_DET_1, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT3);

            // Cancel WD TimerEvent When TDM Sync Done
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_TDM_SYNC_TMOUT);

            // Enable eCBUS-S FWD TDM_SYNC_LOST IRQ and Clear eCBUS-S FWD TDM_SYNC_LOST IRQ Flag
            ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT1), _BIT1);
            ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT1 | _BIT0), _BIT0);

            // Clear All eMSC Flags
            ScalerSetBit_EXINT(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

            // Release eMSC Reset Bit ---> Release eMSC Circuit FSM
            ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, 0x00);

            // Start Sending eMSC Link Training Sync Symbols (Write 1 auto Clear)
            ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT2, _BIT2);

            SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_TDM_SYNC_DONE);

            // Record eCBUS_INT Flow State-9 (TDM SYNC DONE Interrupt)
            ScalerSetBit_EXINT(P6C_60_ECBUS_DPHY_CAP0, ~_BIT4, _BIT4);
        }

        // Check SYNC LOST (IRQ_Flag & IRQ_EN)
        if((ScalerGetByte_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // Disable eCBUS-S FWD TDM_SYNC_LOST IRQ
            ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT1 | _BIT0), 0x00);

            // Enable eMSC Reset Bit
            ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, _BIT4);

#if(_MHL3_ECBUS_SYNC_LOST_SOLUTION == _ECBUS_SYNC_LOST_REINIT)

            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT5, 0X00);
            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT5, _BIT5);

            // FW Set Re-Initial TDM Sync (HW Enter TDM_SYNC_INITIAL State)
            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT0, _BIT0);

            // Enable eCBUS-S FWD TDM_SYNC_DONE IRQ and Clear eCBUS-S FWD TDM_SYNC_DONE IRQ Flag
            ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT1), _BIT3);
            ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

            // Cancel WD TimerEvent to to Wait FWD COM1 Sync (No Mather it Still Exist or not)
            ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COM1);

            // Re-Set WD TimerEvent to Wait FWD COM1 Sync
            ScalerTimerWDActivateTimerEvent_EXINT0(15, _SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COM1);

#elif(_MHL3_ECBUS_SYNC_LOST_SOLUTION == _ECBUS_SYNC_LOST_RETRY)

            // FW Set Re-Try TDM Sync (HW Enter TDM_SYNC_TX_COM1 State)
            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT1, _BIT1);

            // Enable eCBUS-S FWD TDM_SYNC_DONE IRQ and Clear eCBUS-S FWD TDM_SYNC_DONE IRQ Flag
            ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT1), _BIT3);
            ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

#endif
            // Record eCBUS_INT Flow State-10 (TDM SYNC Loss Interrupt)
            ScalerSetBit_EXINT(P6C_60_ECBUS_DPHY_CAP0, ~_BIT5, _BIT5);
        }

        // Check eMSC MARK LOST (IRQ_Flag & IRQ_EN)
        if((ScalerGetByte_EXINT(P6C_0F_ECBUS_EMSC_SYNC_DET) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            // Disable eMSC MARK Loss IRQ and Clear Flag
            ScalerSetBit_EXINT(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            // Switch Back to _MHL3_ECBUS_STATE_TDM_SYNC_DONE to Re-Start eMSC Link
            SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_TDM_SYNC_DONE);

            // Enable eMSC Reset Bit ---> Clear Tx/Rx SRAM / Hang eMSC Circuit FSM
            ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, _BIT4);

            // Clear All eMSC Flags
            ScalerSetBit_EXINT(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));

            // Release eMSC Reset Bit ---> Release eMSC Circuit FSM
            ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, 0x00);

            // Start Sending eMSC Link Training Sync Symbols (Write 1 auto Clear)
            ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT2, _BIT2);

            // Record eCBUS_INT Flow State-12 (eMSC Mark Loss Interrupt)
            ScalerSetBit_EXINT(P6C_60_ECBUS_DPHY_CAP0, ~_BIT7, _BIT7);
        }

        // Clear eCBUS Global IRQ Flag
        ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT2, _BIT2);
    }
}


//--------------------------------------------------
// Description  : ECBUS Handler for D0 Port
// Input Value  : ucActivePort --> Current Active Port
//                ucModeState --> Current Mode State
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHL3Rx5ECBUSHandler(void)
{
    DWORD ulSlotMapAssign = 0;

    // Check if Discovery State is done and send HPD & Device Capabilities Ready
    switch(GET_MHL3_RX5_ECBUS_PROCESS_STATE())
    {
        case _MHL3_ECBUS_STATE_INITIAL:

            // Clear MHL 3.0 Video Flags
            CLR_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT();

#if(_MHL3_ECBUS_STARTUP_DEBUG_MESSAGE == _ON)
            if(ScalerGetBit(P6C_5F_ECBUS_RESERVE_2, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5))
            {
                DebugMessageMHL("eCBUS Build Up Error #", ScalerGetByte(P6C_5F_ECBUS_RESERVE_2));
            }
#endif
            return _FALSE;
            break;

        case _MHL3_ECBUS_STATE_START_UP_DONE:

            if(GET_MHL3_RX5_BIST_TESTING() == _ON)
            {
                // Cancel 1S Timeout Event of oCBUS-eCBUS Start Up
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP);

                if((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_IMPEDENCE) == _MHL3_ECBUS_BIST_MODE_IMPEDENCE)
                {
                    // TODO:
                }

                if((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_AVLINK_RX) == _MHL3_ECBUS_BIST_MODE_AVLINK_RX)
                {
                    // TODO:
                }

                if(((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_ECBUS_TX) == _MHL3_ECBUS_BIST_MODE_ECBUS_TX) ||
                   ((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_ECBUS_RX) == _MHL3_ECBUS_BIST_MODE_ECBUS_RX))
                {
                    // TODO:
                }

                SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_BIST_TESTING);

#if(_MHL3_BIST_FUNCTION_DEBUG_MESSAGE == _ON)
                DebugMessageMHL("4 eCBUS BIST Testing", 0x00);
#endif
            }

            return _FALSE;
            break;

        case _MHL3_ECBUS_STATE_TDM_SYNC_DONE:

            if(GET_MHL3_RX5_ECBUS_MODE() == _ON)
            {
                // Cancel 5S Timeout Event of oCBUS-eCBUS Start Up
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP);

                // Assign TDM Slots Allocations
                for(pData[0] = 1; pData[0] < 25; pData[0]++)
                {
                    // Record Slot Mappong Pattern Bytes
                    ulSlotMapAssign = ulSlotMapAssign | ((DWORD)(GET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(pData[0]) == _MHL3_ECBUS_VC_EMSC_ASSIGN) << (pData[0] - 1));
                }

                // Set Tmds Slot Mapping Pattern, Double Buffer Write Trigger by Last Mapping Byte "P6C_12_ECBUS_EMSC_SLOT_MAP_3"
                ScalerSetByte(P6C_10_ECBUS_EMSC_SLOT_MAP_1, (BYTE)(ulSlotMapAssign >> 16));
                ScalerSetByte(P6C_11_ECBUS_EMSC_SLOT_MAP_2, (BYTE)(ulSlotMapAssign >> 8));
                ScalerSetByte(P6C_12_ECBUS_EMSC_SLOT_MAP_3, (BYTE)ulSlotMapAssign);

                // Check TDM Sync FSM
                if(ScalerGetByte(P6C_4C_ECBUS_HW_FSM_1) != 0x80)
                {
                    // FW Set Re-Initial TDM Sync (HW Enter TDM_SYNC_INITIAL State)
                    ScalerSetBit(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT0, _BIT0);

#if(_MHL3_ECBUS_STARTUP_DEBUG_MESSAGE == _ON)
                    DebugMessageMHL("0-- eCBUS TDM Sync Re-Initial", ScalerGetByte(P6C_4C_ECBUS_HW_FSM_1));
#endif
                }
                else
                {
                    // Enable CBUS1 Get Invalid Command Check
                    ScalerSetBit(P6A_01_OCBUS_CTRL_01, ~_BIT3, _BIT3);

                    // eMSC Link Build Retry Limit = 10, .... Polling emsc_link_done bit for 10ms (0x2B0F from 0xBC --> 0xB5)
                    if((GET_MHL3_RX5_EMSC_SYNC_RETRY_TIME() > 10) || (ScalerTimerPollingFlagProc(10, P6C_0F_ECBUS_EMSC_SYNC_DET, _BIT3, _TRUE) == _TRUE))
                    {
                        CLR_MHL3_RX5_EMSC_SYNC_RETRY_TIME();

                        // Clear emsc_link_done Flag (OR All Other Flags to 0x00, In Case of Mis-Clear)
                        ScalerSetBit(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

                        // Enable eMSC MARK Loss IRQ and Clear Flag (OR All Other Flags to 0x00, In Case of Mis-Clear)
                        ScalerSetBit(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);
                        ScalerSetBit(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

                        SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_EMSC_SYNC_DONE);

#if(_MHL3_ECBUS_STARTUP_DEBUG_MESSAGE == _ON)
                        DebugMessageMHL("1-- eCBUS TDM Sync Done", ScalerGetByte(P6A_DE_CBUS_CTRL_3E));
#endif
                    }
                    else // (0x2B0F == 0xA4)
                    {
                        ADD_MHL3_RX5_EMSC_SYNC_RETRY_TIME();

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
                        DebugMessageMHL("-Sync: emsc_link_done Un Done Reset eMSC Module", ScalerGetByte(P6C_0F_ECBUS_EMSC_SYNC_DET));
#endif
                        // Toggle eMSC Reset Bit
                        ScalerSetBit(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, _BIT4);
                        ScalerSetBit(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT4, 0x00);

                        // Start Sending eMSC Link Training Sync Symbols (Write 1 auto Clear)
                        ScalerSetBit(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT2, _BIT2);
                    }
                }
            }

            return _FALSE;
            break;

        case _MHL3_ECBUS_STATE_EMSC_SYNC_DONE:

            // Check Source FWD Sync Meet or Mark Received / Source Slot Allocation Detect Result
            if((ScalerGetBit(P6C_0F_ECBUS_EMSC_SYNC_DET, (_BIT5 | _BIT4 | _BIT2)) == (_BIT5 | _BIT4 | _BIT2)))
            {
                // Record eCBUS_INT Flow State-11 (eMSC Sync)
                ScalerSetBit(P6C_60_ECBUS_DPHY_CAP0, ~_BIT6, _BIT6);

                pData[0] = ScalerGetByte(P6C_13_ECBUS_EMSC_SOURCE_SLOT_DET_1);
                pData[1] = ScalerGetByte(P6C_14_ECBUS_EMSC_SOURCE_SLOT_DET_2);
                pData[2] = ScalerGetByte(P6C_15_ECBUS_EMSC_SOURCE_SLOT_DET_3);

                // If Detected Slot Allocation != Desired Allocation ---> Re-Sync eMSC
                if(((DWORD)pData[0] << 16 | (DWORD)pData[1] << 8 | (DWORD)pData[2]) !=
                   ((DWORD)ScalerGetByte(P6C_10_ECBUS_EMSC_SLOT_MAP_1) << 16 |
                    (DWORD)ScalerGetByte(P6C_11_ECBUS_EMSC_SLOT_MAP_2) << 8 |
                    (DWORD)ScalerGetByte(P6C_12_ECBUS_EMSC_SLOT_MAP_3)))
                {
                    // Clear slot_det_done Flag (OR All Other Flags to 0x00, In Case of Mis-Clear)
                    ScalerSetBit(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

                    ScalerSetByte(P6C_10_ECBUS_EMSC_SLOT_MAP_1, pData[0]);
                    ScalerSetByte(P6C_11_ECBUS_EMSC_SLOT_MAP_2, pData[1]);
                    ScalerSetByte(P6C_12_ECBUS_EMSC_SLOT_MAP_3, pData[2]);

                    // Switch Back to _MHL3_ECBUS_STATE_TDM_SYNC_DONE to Re-Start eMSC Link
                    SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_TDM_SYNC_DONE);

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
                    DebugMessageMHL("-Sync: Slot Allocation Detect Miss Match", 0x00);
#endif
                }
                else
                {
                    // Clear slot_det_done Flag (OR All Other Flags to 0x00, In Case of Mis-Clear)
                    ScalerSetBit(P6C_0F_ECBUS_EMSC_SYNC_DET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

#if(_MHL3_ECBUS_STARTUP_DEBUG_MESSAGE == _ON)
                    DebugMessageMHL("2-- eCBUS eMSC Sync Done", ScalerGetByte(P6A_DE_CBUS_CTRL_3E));
#endif
                    SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_ECBUS_DONE);
                }
            }

            return _FALSE;
            break;

        case _MHL3_ECBUS_STATE_BIST_TESTING:

            // Check if AV Link Rx BIST Testing Done
            if(((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_AVLINK_RX) == _MHL3_ECBUS_BIST_MODE_AVLINK_RX) &&
               (ScalerGetBit(P79_01_MHL_FIFO_CTRL, _BIT0) == _BIT0))
            {
#if(_MHL3_BIST_FUNCTION_DEBUG_MESSAGE == _ON)
                DebugMessageMHL("Frame Cnt Done", ScalerGetBit(P79_01_MHL_FIFO_CTRL, _BIT0));
#endif

                ScalerMHL3Rx5BISTTestingDoneProc();

                SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_ECBUS_DONE);
            }

            return _FALSE;
            break;

        case _MHL3_ECBUS_STATE_ECBUS_DONE:

            if((GET_MHL_RX5_PROCESS_STATE()) >= _MHL_STATE_PATH_EN_DONE)
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }

            break;

        default:
            break;
    }
}


//--------------------------------------------------
// Description  : MHL3 BIST Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5BISTHandler(void)
{
    BYTE ucTmp = 0;

    /********************************************************/
    /************* Get MSC Command BIST_TRIGGER *************/
    /********************************************************/

    if((bit)ScalerGetBit(P6A_13_OCBUS_CTRL_13, _BIT3) == _TRUE)
    {
        //-------- Disable Stuck Low IRQ and Clear Stuck Low Flags --------//
        // ---------------- When Receive BIST_TRIGGER ---------------------//
        ScalerSetBit(P6A_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

#if(_MHL3_TEST_FUNCTION_DEBUG_MODE == _ON)
        // James Test Function Setting Call
        ScalerMHL3Rx5TestPinSetting(_MHL3_MAC);
#endif

#if(_MHL3_BIST_FUNCTION_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("3 BIST_TRIGGER", ScalerGetByte(P6A_22_OCBUS_CTRL_22));
#endif
        // Reset(Clear) eCBUS_INT Flow Recorded State
        ScalerSetBit(P6C_60_ECBUS_DPHY_CAP0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetByte(P6C_5F_ECBUS_RESERVE_2, 0x00);

        // Reset(Clear) eCBUS Reset Hold flag / Mode Up_Down Flad
        ScalerSetBit(P6C_50_ECBUS_HW_FSM_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

        // Reset Recorded "_WAIT_COMMA2_END_TIME"
        ScalerSetByte(P6C_5D_ECBUS_RESERVE_0, 0x00);

        // Reset Recorded "_WAIT_ACTIVE_END_TIME"
        ScalerSetByte(P6C_5E_ECBUS_RESERVE_1, 0x00);

        // Impedance Test (0x40)
        if((bit)ScalerGetBit(P6A_22_OCBUS_CTRL_22, _BIT6) == _TRUE)
        {
            switch(GET_MHL3_RX5_BIST_IMPEDENCE_MODE())
            {
                case _ECBUS_S_TX_LOW:

                    // Enable BWD eCBUS Driving Low
                    ScalerSetBit(P5E_0C_ECBUS_PHY_BIST, ~(_BIT2 | _BIT1), _BIT1);

                    break;

                case _ECBUS_S_TX_HIGH:

                    // Enable BWD eCBUS Driving High
                    ScalerSetBit(P5E_0C_ECBUS_PHY_BIST, ~(_BIT2 | _BIT1), _BIT2);

                    break;

                case _ECBUS_S_RX:

                    // Enable BWD eCBUS Driving All 0
                    ScalerSetBit(P6C_52_ECBUS_TEST_FORCE_OUT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

                    break;

                default:
                    break;
            }

            SET_MHL3_RX5_BIST_TESTING(_ON);
            SET_MHL3_RX5_BIST_TESTING_MODE(GET_MHL3_RX5_BIST_TESTING_MODE() | _MHL3_ECBUS_BIST_MODE_IMPEDENCE);

            switch(GET_MHL3_RX5_BIST_ECBUS_DURATION())
            {
                // eCBUS Electrical CTS Test (Tektrinix)
                case 0x20:

                    // James Electrical CTS Debug <20150520> (Duration + 10 Second)
                    ScalerTimerActiveTimerEvent(SEC(GET_MHL3_RX5_BIST_ECBUS_DURATION() + 10), _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_BIST_DURATION);
                    break;

                // eCBUS TDR CTS Test (Tektrinix)
                case 0x3C:

                    ScalerTimerActiveTimerEvent(SEC(GET_MHL3_RX5_BIST_ECBUS_DURATION()), _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_BIST_DURATION);
                    break;

                default:
                    break;
            }

            // Set to BIST TESTING State, For Source no Start Up Flow Under BIST (Tektrinix),
            SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_BIST_TESTING);

            ScalerMHL3Rx5ECBUSConfigureSettings();

            ScalerMHL3Rx5EnableECBUSMode(_ENABLE);

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP);

            CLR_MHL3_RX5_ECBUS_START_UP_TMOUT();

            ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP);
        }

        // AV Link Rx BIST (0x20)
        if((bit)ScalerGetBit(P6A_22_OCBUS_CTRL_22, _BIT5) == _TRUE)
        {
            ScalerTimerActiveTimerEvent(300, _SCALER_TIMER_EVENT_MHL3_RX5_WAIT_FWD_CLK);

            // Set Av Link Rx Bist Error Counted by Bit Unit
            ScalerSetBit(P79_02_MHL_BIST_CTRL, ~_BIT1, _BIT1);

            g_usMhl3Rx5BISTEcbusErrCnt = 0x00;
            g_usMhl3Rx5BISTAVLinkErrCnt = 0x00;

            SET_MHL3_RX5_BIST_TESTING(_ON);
            SET_MHL3_RX5_BIST_TESTING_MODE(GET_MHL3_RX5_BIST_TESTING_MODE() | _MHL3_ECBUS_BIST_MODE_AVLINK_RX);

            // Active Timer Event for Wait to Set BIST PHY
            ScalerTimerActiveTimerEvent(150, _SCALER_TIMER_EVENT_MHL3_RX5_AV_LINK_BIST_SET_PHY);

            // Direct Set to BIST TESTING State, Electrical CTS Source no Start Up Flow Under BIST
            SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_BIST_TESTING);

            ScalerMHL3Rx5ECBUSConfigureSettings();

            ScalerMHL3Rx5EnableECBUSMode(_ENABLE);

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP);

            CLR_MHL3_RX5_ECBUS_START_UP_TMOUT();

            ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP);
        }

        // ECBUS Rx BIST (0x02)
        if((bit)ScalerGetBit(P6A_22_OCBUS_CTRL_22, _BIT1) == _TRUE)
        {
            ScalerTimerActiveTimerEvent(300, _SCALER_TIMER_EVENT_MHL3_RX5_WAIT_FWD_CLK);

            // Write 1 to Reset eCBUS BIST Error Counter
            ScalerSetBit(P6C_34_ECBUS_BIST_CTRL, ~(_BIT3 | _BIT1), _BIT3);

            // Perform Rx BIST Configure
            ScalerSetBit(P6C_35_ECBUS_BIST_CONFIG, ~_BIT6, _BIT6);

            SET_MHL3_RX5_BIST_TESTING(_ON);
            SET_MHL3_RX5_BIST_TESTING_MODE(GET_MHL3_RX5_BIST_TESTING_MODE() | _MHL3_ECBUS_BIST_MODE_ECBUS_RX);

            // Timer Event = Get BIST Duration + 10 Sec For Electrical CTS
            ScalerTimerActiveTimerEvent(SEC(GET_MHL3_RX5_BIST_ECBUS_DURATION() + 10), _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_BIST_DURATION);

            // Direct Set to BIST TESTING State, Electrical CTS Source no Start Up Flow Under BIST
            SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_BIST_TESTING);

            ScalerMHL3Rx5ECBUSConfigureSettings();

            ScalerMHL3Rx5EnableECBUSMode(_ENABLE);

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP);

            CLR_MHL3_RX5_ECBUS_START_UP_TMOUT();

            ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP);
        }

        // ECBUS Tx BIST (0x01)
        if((bit)ScalerGetBit(P6A_22_OCBUS_CTRL_22, _BIT0) == _TRUE)
        {
            ScalerTimerActiveTimerEvent(300, _SCALER_TIMER_EVENT_MHL3_RX5_WAIT_FWD_CLK);

            // Write 1 to Reset PRBS Tx Pattern Generation
            ScalerSetBit(P6C_34_ECBUS_BIST_CTRL, ~(_BIT2 | _BIT1), _BIT2);

            // Perform Tx BIST Configure
            ScalerSetBit(P6C_35_ECBUS_BIST_CONFIG, ~_BIT7, _BIT7);

            SET_MHL3_RX5_BIST_TESTING(_ON);
            SET_MHL3_RX5_BIST_TESTING_MODE(GET_MHL3_RX5_BIST_TESTING_MODE() | _MHL3_ECBUS_BIST_MODE_ECBUS_TX);

            // Timer Event = Get BIST Duration + 10 Sec For Electrical CTS
            ScalerTimerActiveTimerEvent(SEC(GET_MHL3_RX5_BIST_ECBUS_DURATION() + 10), _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_BIST_DURATION);

            // Direct Set to BIST TESTING State, Electrical CTS Source no Start Up Flow Under BIST
            SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_BIST_TESTING);

            ScalerMHL3Rx5ECBUSConfigureSettings();

            ScalerMHL3Rx5EnableECBUSMode(_ENABLE);

            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP);

            CLR_MHL3_RX5_ECBUS_START_UP_TMOUT();

            ScalerTimerActiveTimerEvent(SEC(5), _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP);
        }

        SET_MHL_RX5_PROCESS_STATE(_MHL_STATE_BIST_TESTING);

        // Clear Flags
        ScalerSetBit(P6A_22_OCBUS_CTRL_22, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
        ScalerSetBit(P6A_13_OCBUS_CTRL_13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);
    }


    /********************************************************/
    /************* Get MSC Command BIST_STOP ****************/
    /********************************************************/

    if((bit)ScalerGetBit(P6A_13_OCBUS_CTRL_13, _BIT0) == _TRUE)
    {
        if((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_AVLINK_RX) == _MHL3_ECBUS_BIST_MODE_AVLINK_RX)
        {
#if(_MHL3_BIST_FUNCTION_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("5 BIST_STOP", 0x00);
#endif
            // Stop Av Link Rx Bist Duration
            ScalerSetBit(P79_02_MHL_BIST_CTRL, ~_BIT3, _BIT3);

            // Clear Flags
            ScalerSetBit(P6A_13_OCBUS_CTRL_13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        }
    }


    /********************************************************/
    /************* Get MSC Command BIST_REQUEST_STAT ********/
    /********************************************************/

    if((bit)ScalerGetBit(P6A_13_OCBUS_CTRL_13, _BIT2) == _TRUE)
    {
#if(_MHL3_BIST_FUNCTION_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("6 BIST_REQUEST_STAT", 0x00);
#endif
        // Encode BIST_RETURN_STAT and Sent Write_Burst
        pData[0] = _MHL_WRITE_BURST_ECBUS_BIST_RETURN_STAT_HBYTE;
        pData[1] = _MHL_WRITE_BURST_ECBUS_BIST_RETURN_STAT_LBYTE;

        for(ucTmp = 3; ucTmp < 12; ucTmp++)
        {
            pData[ucTmp] = 0x00;
        }

        // ECBUS BIST Error Counter
        pData[12] = g_usMhl3Rx5BISTEcbusErrCnt >> 8;
        pData[13] = g_usMhl3Rx5BISTEcbusErrCnt | 0x00FF;

        pData[12] = 0x00;
        pData[13] = 0x00;

        // AVLINK BIST Error Counter
        pData[14] = g_usMhl3Rx5BISTAVLinkErrCnt >> 8;
        pData[15] = g_usMhl3Rx5BISTAVLinkErrCnt | 0x00FF;

        pData[14] = 0x00;
        pData[15] = 0x00;

        pData[2] = 256 - (pData[0] + pData[1] + pData[12] + pData[13] + pData[14] + pData[15]);

        if(ScalerMHLRx5MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT) == _SUCCESS)
        {
            ucTmp = 100;

            while((ucTmp-- > 0) && ((bit)ScalerGetDataPortBit(P6A_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT) != _TRUE))
            {
                ScalerTimerDelayXms(5);
            }

            if(ScalerMHLRx5MscSendWriteBurst(0x40, 16, pData, _MHL_WRITE_BURST_WITH_REQ) == _SUCCESS)////
            {
                // Clear Flags
                ScalerSetBit(P6A_13_OCBUS_CTRL_13, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

#if(_MHL3_BIST_FUNCTION_DEBUG_MESSAGE == _ON)
                DebugMessageMHL("7 BIST RETURN ECBUS", g_usMhl3Rx5BISTEcbusErrCnt);
                DebugMessageMHL("7 BIST RETURN AVLINK", g_usMhl3Rx5BISTAVLinkErrCnt);
#endif
            }
        }
    }
}


//--------------------------------------------------
// Description  : MHL3.0 BIST Testing Done Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5BISTTestingDoneProc(void)
{
    g_usMhl3Rx5BISTEcbusErrCnt = (ScalerGetByte(P6C_39_ECBUS_BIST_ERR_CNT_H) << 8) | ScalerGetByte(P6C_3A_ECBUS_BIST_ERR_CNT_L);
    g_usMhl3Rx5BISTAVLinkErrCnt = (ScalerGetByte(P79_05_MHL_BIST_ERR_CNT_H) << 8) | ScalerGetByte(P79_06_MHL_BIST_ERR_CNT_L);

    if((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_IMPEDENCE) == _MHL3_ECBUS_BIST_MODE_IMPEDENCE)
    {
        // Disable ECBUS BIST Force Driving
        ScalerSetBit(P5E_0C_ECBUS_PHY_BIST, ~(_BIT3 | _BIT2), 0x00);
    }

    if(((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_ECBUS_TX) == _MHL3_ECBUS_BIST_MODE_ECBUS_TX) ||
       ((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_ECBUS_RX) == _MHL3_ECBUS_BIST_MODE_ECBUS_RX))
    {
        // Write 1 to Stop eCBUS BIST
        ScalerSetBit(P6C_34_ECBUS_BIST_CTRL, ~(_BIT1 | _BIT0), _BIT0);

        // Disable eCBUS BIST After TDM Slot Sync Done
        ScalerSetBit(P6C_34_ECBUS_BIST_CTRL, ~(_BIT4 | _BIT1), 0x00);
    }
}


//--------------------------------------------------
// Description  : Get the Length of Content Already Exist in Rx SRAM
// Input Value  : Rx SRAM Write Pointer, Rx SRAM Read Pointer
// Output Value : eMSC Rx SRAM Space Volume
//--------------------------------------------------
BYTE ScalerMHL3Rx5ECBUSGetEmscRxVolume(BYTE ucRxSramWritePointer, BYTE ucRxSramReadPointer)
{
    if(ucRxSramWritePointer > ucRxSramReadPointer)
    {
        return (ucRxSramWritePointer - ucRxSramReadPointer);
    }
    else if(ucRxSramReadPointer > ucRxSramWritePointer)
    {
        return (256 - ucRxSramWritePointer + ucRxSramReadPointer);
    }
    else
    {
#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("eMSC Rx SRAM Pointer Error", 0x00);
#endif
        return 0x00;
    }
}

//--------------------------------------------------
// Description  : eMSC Block Transaction Rx Handler
// Input Value  : None
// Output Value : SUCCESS or FAIL
//--------------------------------------------------
BYTE ScalerMHL3Rx5ECBUSEMSCRxHandler(void)
{
    BYTE ucEmscTransactionMacxPrcessTime = 5;

    BYTE ucRxEMSCTransactionCnt = 0;
    BYTE ucRxSramWritePointer = 0;
    BYTE ucRxTransactionByteCnt = 0;

    BYTE ucRxUnloadAck = 0;
    BYTE ucLengthRemaining = 0;

    BYTE ucBurstIDHB = 0;
    BYTE ucBurstIDLB = 0;

    // Get Received eMSC Transaction Count
    ucRxEMSCTransactionCnt = ScalerGetByte(P6C_1E_ECBUS_EMSC_RX_BLK_CNT);

    // Get eMSC Rx SRAM Write Pointer (HW Pointer+1)
    ucRxSramWritePointer = ScalerGetByte(P6C_1F_ECBUS_EMSC_RX_WRT_PNT);

    // Get (Byte Count-1) of the Received eMSC Transaction
    ucRxTransactionByteCnt = ScalerGetByte(P6C_21_ECBUS_EMSC_RX_REQ_CNT);

    if((ucRxEMSCTransactionCnt > 1) ||
       ((ucRxEMSCTransactionCnt == 1) &&
        (ScalerMHL3Rx5ECBUSGetEmscRxVolume(ucRxSramWritePointer, ScalerGetByte(P6C_17_ECBUS_EMSC_RX_ADDR)) > ucRxTransactionByteCnt)))
    {
#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("-1- . ucRxEMSCTransactionCnt = ", ucRxEMSCTransactionCnt);
        DebugMessageMHL("-1- . ucRxSramWritePointer = ", ucRxSramWritePointer);
        DebugMessageMHL("-1- . ucRxTransactionByteCnt = ", ucRxTransactionByteCnt);
#endif
        // Reload Rx Read Port Data at the First Address of New Received Transaction
        ScalerSetByte(P6C_17_ECBUS_EMSC_RX_ADDR, ScalerGetByte(P6C_17_ECBUS_EMSC_RX_ADDR));

        ucRxUnloadAck = ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);
        ucLengthRemaining = ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);

        if(ucLengthRemaining != ScalerGetByte(P6C_2A_ECBUS_EMSC_TRANS_RESERVE))
        {
#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("-Rx: SRAM FW Remain != HW Remain", ucLengthRemaining);
#endif
        }

        if(ucRxUnloadAck > 0x00)
        {
            // Update Source Peer Blank Rx Buffer Available Size
            g_usMhl3Rx5SourceRxBufferAvailSize = g_usMhl3Rx5SourceRxBufferAvailSize + ucRxUnloadAck;

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("-Rx: Source Rx SRAM Un-Load Bytes = ", ucRxUnloadAck);
#endif
        }

        // Set Sink Tx UnloadAck
        ucRxUnloadAck = ucLengthRemaining + 2;

        while((ucEmscTransactionMacxPrcessTime-- > 0) && (ucLengthRemaining > 0))
        {
            ucBurstIDHB = ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);
            ucBurstIDLB = ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);
            ucLengthRemaining -= 2;

            ucLengthRemaining = ScalerMHL3Rx5ECBUSProcessEmscPayload(ucBurstIDHB, ucBurstIDLB, ucLengthRemaining);
        }

        if(ScalerMHL3Rx5ECBUSEmscTxEncode(_MHL_ECBUS_EMSC_STANDARD_TRANSPORT_HEADER, 0x00, ucRxUnloadAck, 0x00) == _MHL3_EMSC_TX_ACK_SUCCESS)
        {
            ucRxEMSCTransactionCnt--;

            // FW Process An eMSC Transaction Done
            ScalerSetBit(P6C_1D_ECBUS_EMSC_TRANS_CTRL, ~_BIT2, _BIT2);

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("-2- . ucRxEMSCTransactionCnt = ", ucRxEMSCTransactionCnt);
            DebugMessageMHL("-3- . P6C_1E_ECBUS_EMSC_RX_BLK_CNT = ", ScalerGetByte(P6C_1E_ECBUS_EMSC_RX_BLK_CNT));
#endif
            if((ucRxEMSCTransactionCnt == ScalerGetByte(P6C_1E_ECBUS_EMSC_RX_BLK_CNT)) && (ucRxEMSCTransactionCnt == 0x00))
            {
#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
                DebugMessageMHL("-Rx: Decoding Done!!", ucRxEMSCTransactionCnt);
#endif
                return _MHL3_EMSC_RX_DECODE_SUCCESS;
            }
        }
        else
        {
            return _MHL3_EMSC_RX_DECODE_FAIL;
        }
    }

    return _MHL3_EMSC_RX_DECODE_FAIL;
}

//--------------------------------------------------
// Description  : Process Received eMSC Block Transaction Sub-Payload
// Input Value  : Sub-Payload Burst ID, Transaction Length Remaining
// Output Value : Transaction Length Remaining
//--------------------------------------------------
BYTE ScalerMHL3Rx5ECBUSProcessEmscPayload(BYTE ucBurstIDHB, BYTE ucBurstIDLB, BYTE ucLengthRemain)
{
    BYTE ucAttCode = 0;
    BYTE ucViewPixelFormat = 0;
    BYTE ucEMSCHidPayloadLength = 0;
    BYTE ucHidMessageId = 0;
    BYTE ucHidChkSumHB = 0;
    BYTE ucHidChkSumLB = 0;
    BYTE ucTmp = 0;

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
    DebugMessageMHL("-Rx: Processing Transaction Block ID = ", ucBurstIDLB);
#endif

    switch((ucBurstIDHB << 8 | ucBurstIDLB))
    {
        case (_MHL_WRITE_BURST_ECBUS_BLK_RCV_BUFFER_INFO_HBYTE << 8 | _MHL_WRITE_BURST_ECBUS_BLK_RCV_BUFFER_INFO_LBYTE):

            // Update Peer Blank Rx Buffer Available Size
            g_usMhl3Rx5SourceRxBufferAvailSize = (((WORD)ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA) |
                                                   (WORD)ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA) << 8)
                                                  - ((WORD)256 - g_usMhl3Rx5SourceRxBufferAvailSize) - 1);

            ucLengthRemain -= 2;

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("-Rx: Source ECBUS_BLK_RCV_BUFFER_INFO Payload = ", g_usMhl3Rx5SourceRxBufferAvailSize);
#endif
            return ucLengthRemain;
            break;

        case (_MHL_WRITE_BURST_ECBUS_BITS_PER_PIXEL_FMT_HBYTE << 8 | _MHL_WRITE_BURST_ECBUS_BITS_PER_PIXEL_FMT_LBYTE):

            // Get Check_Sum/ Tot_Ent/ Seq/ Num_Ent, 4 BYTE
            ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);
            ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);
            ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);
            ucTmp = ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);

            ucLengthRemain -= 4;

            // Decode View Pixel Format Descrtptors Num_Ent Times
            while(ucTmp > 0)
            {
                ucAttCode = ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);
                ucViewPixelFormat = ScalerGetByte(P6C_18_ECBUS_EMSC_RX_DATA);

                if(GET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT() == _MHL3_VIDEO_FORMAT_NULL)
                {
#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
                    DebugMessageMHL("-Rx: Get eMSC Bits Format INFO Before Measure", ucViewPixelFormat);
#endif
                    SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(ucViewPixelFormat);
                }
                else if(ucViewPixelFormat != GET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT())
                {
#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
                    DebugMessageMHL("-Rx: eMSC Bits Format / Format Measure 'Mismatch'", ucViewPixelFormat);
#endif
                    SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(ucViewPixelFormat);
                }

                ucTmp -= 1;
                ucLengthRemain -= 2;
            }

            return ucLengthRemain;
            break;

        default:

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("-Rx: Un Support Sub-Payload Received, Re-read Burst ID", ucBurstIDLB);
#endif
            ScalerSetByte(P6C_17_ECBUS_EMSC_RX_ADDR, ScalerGetByte(P6C_17_ECBUS_EMSC_RX_ADDR) - 2);

            return (ucLengthRemain + 2);
            break;
    }
}

//--------------------------------------------------
// Description  : eMSC Tx Transaction Encoder
// Input Value  : eMSC Burst ID, eMSC Sub-Message ID, Message Contents, Message Length
// Output Value : SUCCESS / FAIL Code
//--------------------------------------------------
BYTE ScalerMHL3Rx5ECBUSEmscTxEncode(BYTE ucEmscBurstId, BYTE ucEmscSubMessageId, BYTE ucEmscSubMessageContent, BYTE ucEmscSubMessageLength)
{
    WORD usTmp = 0;
    BYTE ucDataPos = 0;
    BYTE ucDataLength = 0;
    WORD usHIDReportSize = 0;
    BYTE ucProductNameSize = 0;
    BYTE ucManufacturerNameSize = 0;
    BYTE ucSerialNumberSize = 0;

    ucEmscSubMessageId = ucEmscSubMessageId;

    /**************************************************************
    ***** if Set Tx SRAM Empyt --> Encode a New Transaction *******
    **************************************************************/
    if(ScalerGetBit(P6C_26_ECBUS_EMSC_TRANS_DET_2, (_BIT7 | _BIT6)) == _BIT6)
    {
        // Reset Tx SRAM FW Write Address
        ScalerSetByte(P6C_19_ECBUS_EMSC_TX_ADDR, 0x00);

        //-----------------------------------------------------------------------//
        //--- Encode Standard Transport Header of the Transmitted Transaction ---//
        //-----------------------------------------------------------------------//
        if(ucEmscBurstId == _MHL_ECBUS_EMSC_STANDARD_TRANSPORT_HEADER)
        {
            // Set Rx Unload Ack Value of Standard Transport Header
            ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, ucEmscSubMessageContent);

            // Set Length Remaining of Transmitted Transaction
            if(GET_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT() == _FALSE)
            {
                // Set eMSC Tx Request Command Byte Count
                ScalerSetByte(P6C_22_ECBUS_EMSC_TX_REQ_CNT, ucEmscSubMessageLength + _MHL_ECBUS_BLK_RCV_BUFFER_INFO_LENGTH + _MHL_ECBUS_REQ_COMMAND_LENGTH - 1);

                // Set eMSC Tx Transaction Lengh Remaining
                ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, ucEmscSubMessageLength + _MHL_ECBUS_BLK_RCV_BUFFER_INFO_LENGTH);

                // Update Source Peer Blank Rx Buffer Available Size
                g_usMhl3Rx5SourceRxBufferAvailSize = g_usMhl3Rx5SourceRxBufferAvailSize - (ucEmscSubMessageLength + _MHL_ECBUS_BLK_RCV_BUFFER_INFO_LENGTH + _MHL_ECBUS_REQ_COMMAND_LENGTH);
            }
            else
            {
                // Set eMSC Tx Request Command Byte Count
                ScalerSetByte(P6C_22_ECBUS_EMSC_TX_REQ_CNT, ucEmscSubMessageLength + _MHL_ECBUS_REQ_COMMAND_LENGTH - 1);

                // Set eMSC Tx Transaction Lengh Remaining
                ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, ucEmscSubMessageLength);

                // Update Source Peer Blank Rx Buffer Available Size
                g_usMhl3Rx5SourceRxBufferAvailSize = g_usMhl3Rx5SourceRxBufferAvailSize - (ucEmscSubMessageLength + _MHL_ECBUS_REQ_COMMAND_LENGTH);
            }

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("-Tx: Sink Rx SRAM Un-Load Bytes = ", ucEmscSubMessageContent);
#endif
        }
        else
        {
            // Set Rx Unload Ack Value of Standard Transport Header
            ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, 0x00);

            // Set Length Remaining of Transmitted Transaction
            if(GET_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT() == _FALSE)
            {
                // Set eMSC Tx Request Command Byte Count
                ScalerSetByte(P6C_22_ECBUS_EMSC_TX_REQ_CNT, ucEmscSubMessageLength + _MHL_ECBUS_BLK_RCV_BUFFER_INFO_LENGTH + _MHL_ECBUS_REQ_COMMAND_LENGTH - 1);

                // Set eMSC Tx Transaction Lengh Remaining
                ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, ucEmscSubMessageLength + _MHL_ECBUS_BLK_RCV_BUFFER_INFO_LENGTH);

                // Update Source Peer Blank Rx Buffer Available Size
                g_usMhl3Rx5SourceRxBufferAvailSize = g_usMhl3Rx5SourceRxBufferAvailSize - (ucEmscSubMessageLength + _MHL_ECBUS_BLK_RCV_BUFFER_INFO_LENGTH + _MHL_ECBUS_REQ_COMMAND_LENGTH);
            }
            else
            {
                // Set eMSC Tx Request Command Byte Count
                ScalerSetByte(P6C_22_ECBUS_EMSC_TX_REQ_CNT, ucEmscSubMessageLength + _MHL_ECBUS_REQ_COMMAND_LENGTH - 1);

                // Set eMSC Tx Transaction Lengh Remaining
                ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, ucEmscSubMessageLength);

                // Update Source Peer Blank Rx Buffer Available Size
                g_usMhl3Rx5SourceRxBufferAvailSize = g_usMhl3Rx5SourceRxBufferAvailSize - (ucEmscSubMessageLength + _MHL_ECBUS_REQ_COMMAND_LENGTH);
            }
        }

        //----------------------------------------------------------------//
        //--- Encode Sink Rx BLK RCV Buffer Info for First Transaction ---//
        //----------------------------------------------------------------//
        if(GET_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT() == _FALSE)
        {
            ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, _MHL_WRITE_BURST_ECBUS_BLK_RCV_BUFFER_INFO_HBYTE);
            ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, _MHL_WRITE_BURST_ECBUS_BLK_RCV_BUFFER_INFO_LBYTE);

            // Set Sink Rx BLK RCV Buffer Info LB --> HB
            ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, g_usMhl3Rx5SinkRxBufferAvailSize);
            ScalerSetByte(P6C_1A_ECBUS_EMSC_TX_DATA, g_usMhl3Rx5SinkRxBufferAvailSize >> 8);

            SET_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT();

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("-Tx: ECBUS_BLK_RCV_BUFFER_INFO Encoded", g_usMhl3Rx5SinkRxBufferAvailSize);
#endif
        }

        // Check if Tx SRAM is Overflowed When Encoding
        if(ScalerGetBit(P6C_26_ECBUS_EMSC_TRANS_DET_2, _BIT3) == _BIT3)
        {
            // Clear Tx SRAM, Reset Tx SRAM HW Pointer
            ScalerSetBit(P6C_26_ECBUS_EMSC_TRANS_DET_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT5);

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("-Tx: eMSC Tx SRAM Overflow", 0x00);
#endif
            return _MHL3_EMSC_TX_SRAM_OVERFLOW_FAIL;
        }

        // Write 1 to Send Commends in eMSC Transmitting SRAM Space
        ScalerSetBit(P6C_1D_ECBUS_EMSC_TRANS_CTRL, ~_BIT1, _BIT1);

        // Set eMSC Tx Transmittion Max Processing Times
        usTmp = 8;

        // Wait Until Source eMSC ACK IRQ Flag or Retry Exceed Limit Flag
        while((usTmp-- > 0) && (ScalerGetBit(P6C_27_ECBUS_EMSC_TRANS_DET_3, _BIT1) != _BIT1))
        {
            // Check if Source eMSC ACK IRQ Flag
            if(ScalerGetBit(P6C_27_ECBUS_EMSC_TRANS_DET_3, _BIT3) == _BIT3)
            {
                // Clear Tx Transmit Done IRQ Flag
                ScalerSetBit(P6C_27_ECBUS_EMSC_TRANS_DET_3, ~(_BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT3);

                // Clear Tx SRAM, Reset Tx SRAM HW Pointer
                ScalerSetBit(P6C_26_ECBUS_EMSC_TRANS_DET_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT5);

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
                DebugMessageMHL("-Tx: Tx Transaction Get ACK Reply", 0x00);
#endif
                return _MHL3_EMSC_TX_ACK_SUCCESS;
            }
            else // Wait Another Tx Timeout (2ms) Period
            {
                ScalerTimerDelayXms(2);
            }
        }

        // Clear Tx Transmit Retry Exceed Limit IRQ Flag
        ScalerSetBit(P6C_27_ECBUS_EMSC_TRANS_DET_3, ~(_BIT6 | _BIT5 | _BIT3 | _BIT1), _BIT1);

        // Clear Tx SRAM, Reset Tx SRAM HW Pointer
        ScalerSetBit(P6C_26_ECBUS_EMSC_TRANS_DET_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT1), _BIT5);

#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("-Tx: Previous Tx Transaction Retry Exceded Limit", 0x00);
#endif
        return _MHL3_EMSC_TX_RETRY_EXCEED_LIMIT_FAIL;
    }
    else
    {
#if(_MHL3_ECBUS_EMSC_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("-Tx: Tx SRAM Not Ready for Transmit", 0x00);
#endif
        return _MHL3_EMSC_TX_NOT_READY_FAIL;
    }
}

//--------------------------------------------------
// Description  : eMSC Block Transaction Tx Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerMHL3Rx5ECBUSEMSCTxHandler(void)
{
    // Manually Use _MHL_ECBUS_EMSC_STANDARD_TRANSPORT_HEADER to Send Sink Rx BLK RCV Buffer Info for First Transaction
    if(GET_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT() == _FALSE)
    {
        ScalerMHL3Rx5ECBUSEmscTxEncode(_MHL_ECBUS_EMSC_STANDARD_TRANSPORT_HEADER, 0x00, 0x00, 0x00);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : MHL 3.0 Re-Allocation Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerMHL3Rx5ECBUSTdmReallocation(void)
{
    BYTE ucTmp = 0;
    BYTE ucAN = 0;
    BYTE ucAM = 0;
    BYTE ucBN = 0;
    BYTE ucBM = 0;
    BYTE ucNM1 = 0;
    BYTE ucVCCount = 0;
    BYTE ucBth = 0;

    ucVCCount = GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_COUNT();

    // Compute AN, AM and ANM1
    for(ucTmp = 1; ucTmp < ucVCCount; ucTmp++)
    {
        ucAN = ucAN + GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_SIZE(ucTmp);
    }
    ucAM = GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_SIZE(ucVCCount);
    ucNM1 = GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_SIZE(ucVCCount - 1);

    // Algorithm A
    ScalerMHL3Rx5ECBUSTdmReallocationAlgorithmA(ucAN, ucAM, ucNM1);

    for(ucBth = 1; ucBth < (ucVCCount - 1); ucVCCount++)
    {
        ucBN = 0;

        // Compute BN and BM
        for(ucTmp = 1; ucTmp < (ucVCCount - ucBth); ucTmp++)
        {
            ucBN = ucBN + GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_SIZE(ucTmp);
        }

        ucBM = GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_SIZE(ucVCCount - ucBth);
        ucNM1 = GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_SIZE(ucVCCount - ucBth - 1);

        // Algorithm B
        ScalerMHL3Rx5ECBUSTdmReallocationAlgorithmB(ucBN, ucBM, ucNM1, ucBth);
    }

    for(ucTmp = 1; ucTmp < 25; ucTmp++)
    {
        if(GET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(0) == _MHL3_ECBUS_VC_UN_ASSIGN)
        {
            SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(ucTmp, _MHL3_ECBUS_VC_UN_ASSIGN);

            return _FAIL;
        }
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : MHL 3.0 Re-Allocation Algorithm A
// Input Value  : ucAN --> N of Algorithm A
//                ucAM --> M of Algorithm A
//                ucNM1 --> N_(M-1) of Algorithm A
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSTdmReallocationAlgorithmA(BYTE ucAN, BYTE ucAM, BYTE ucNM1)
{
    BYTE ucSlotNum = 0;
    BYTE ucCnt = 0;
    BYTE ucVCNum = 0;

    ucVCNum = GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_COUNT();

    for(ucSlotNum = 0; ucSlotNum < 25; ucSlotNum++)
    {
        if(ucSlotNum == 0)
        {
            SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(ucSlotNum, _MHL3_ECBUS_VC_CBUS1_ASSIGN);
            ucCnt = 0;
        }
        else
        {
            if(ucCnt < ucAN)
            {
                if(ucAN == ucNM1)
                {
                    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(ucSlotNum, (ucVCNum - 1));
                }
            }
            else
            {
                SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(ucSlotNum, ucVCNum);
            }

            ucCnt = (ucCnt + ucAN) % (ucAN + ucAM);
        }
    }
}

//--------------------------------------------------
// Description  : MHL 3.0 Re-Allocation Algorithm B
// Input Value  : ucAN --> N of Algorithm B
//                ucAM --> M of Algorithm B
//                ucNM1 --> N_(M-1) of Algorithm B
//                ucBth --> Nth of Algorithm B
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSTdmReallocationAlgorithmB(BYTE ucBN, BYTE ucBM, BYTE ucNM1, BYTE ucBth)
{
    BYTE ucSlotNum = 0;
    BYTE ucCnt = 0;
    BYTE ucVCNum = 0;

    ucVCNum = GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_COUNT() - ucBth;

    for(ucSlotNum = 1; ucSlotNum < 25; ucSlotNum++)
    {
        if(ucCnt == 0)
        {
            if(ucCnt < ucBN)
            {
                if(ucBN == ucNM1)
                {
                    SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(ucSlotNum, (ucVCNum - 1));
                }
            }
            else
            {
                SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(ucSlotNum, ucVCNum);
            }

            ucCnt = (ucCnt + ucBN) % (ucBN + ucBM);
        }
    }
}

//--------------------------------------------------
// Description  : MHL3.0 Data Lane Signal Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerMHL3Rx5DataSignalDetect(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : Reset MHL3 Video Mac
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
void ScalerMHL3Rx5MeasureReset(void)
{
    // Rsset MHL 3.0 Video Mac
    ScalerSetBit(P79_00_MHL_EN, ~_BIT7, 0x00);
    ScalerSetBit(P79_00_MHL_EN, ~_BIT7, _BIT7);

    // Reset MHL 3.0 S2P Fifo
    // Reset Audio Accumulation
    ScalerSetBit(P79_01_MHL_FIFO_CTRL, ~(_BIT7 | _BIT3), 0x00);
    ScalerSetBit(P79_01_MHL_FIFO_CTRL, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));

    // Disable RR Align Auto Mode
    ScalerSetBit(P79_07_MHL_DATA_ALIGN_CTRL, ~_BIT3, 0x00);
    ScalerSetBit(P79_07_MHL_DATA_ALIGN_CTRL, ~_BIT3, _BIT3);

    // Disable MHL 3.0 Measure
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, 0x00);
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, _BIT7);

    // Clear MHL Mode Error Flag
    ScalerSetBit(P79_38_MHL_MEASURE_24, ~_BIT6, _BIT6);
}



//--------------------------------------------------
// Description  : Check MHL3 Video Measure Results
// Input Value  : None
// Output Value : True --> Get Video Stream
//--------------------------------------------------
bit ScalerMHL3Rx5MeasureCheck(void)
{
    WORD usHstartAvgNonInv = 0;
    WORD usHstartAvgInv = 0;
    WORD usVstartAvgNonInv = 0;
    WORD usVstartAvgInv = 0;
    BYTE ucPixelModeDiv = 0;
    WORD usHactiveAvg1 = 0;
    WORD usHactiveAvg2 = 0;
    WORD usHactiveDiff = 0;
    WORD usHtotalDiff = 0;
    WORD usVtotalDiff = 0;

    // Reset MHL 3.0 Measure Enable
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, 0x00);

    // Get MHL Clk Mode (24 Bits or 16 Bits)
    ucPixelModeDiv = GET_MHL3_RX5_VIEW_PIXEL_DIVIDER();


    /////////////////////////////////////
    //////// First Time Measure /////////
    /////////////////////////////////////

    // Select Hactive Region Measure
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT2, 0x00);

    // Disable HS / VS Invert
    ScalerSetBit(P79_33_MHL_MEASURE_19, ~(_BIT5 | _BIT4), 0x00);

    // Trigger MHL 3.0 Measure
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, _BIT7);

    ScalerTimerPollingFlagProc(100, P79_20_MHL_MEASURE_0, _BIT7, _FALSE);

    // Get Hstart 1
    ScalerRead(P79_21_MHL_MEASURE_1, 2, &pData[0], _AUTOINC);

    // Get Hstart 2
    ScalerRead(P79_23_MHL_MEASURE_3, 2, &pData[2], _AUTOINC);

    // Calculate Hstart Average
    usHstartAvgNonInv = ((((WORD)pData[0] << 8) | ((WORD)pData[1] << 0)) + (((WORD)pData[2] << 8) | ((WORD)pData[3] << 0))) / 2;

    // Get Vstart
    ScalerRead(P79_2F_MHL_MEASURE_15, 2, &pData[10], _AUTOINC);
    usVstartAvgNonInv = PDATA_WORD(5);

    // Get Symbol Number
    ScalerRead(P79_2D_MHL_MEASURE_13, 2, &pData[0], _AUTOINC);
    g_usMhl3Rx5HactivePixelCount = PDATA_WORD(0);

    // Check if HDMI Format --> g_usMhl3HactivePixelCount = (g_usMhl3HactivePixelCount - 2 * ucPixelModeDiv) / ucPixelModeDiv
    if(ScalerMHL3Rx5FormatDetect() == _SOURCE_HDMI)
    {
        g_usMhl3Rx5HactivePixelCount = (g_usMhl3Rx5HactivePixelCount - 2 * ucPixelModeDiv) / ucPixelModeDiv;
    }
    else if(ScalerMHL3Rx5FormatDetect() == _SOURCE_DVI) // Check if DVI Format --> g_usMhl3HactivePixelCount = g_usMhl3HactivePixelCount / ucPixelModeDiv
    {
        g_usMhl3Rx5HactivePixelCount = g_usMhl3Rx5HactivePixelCount / ucPixelModeDiv;
    }


    /////////////////////////////////////
    //////// Second Time Measure ////////
    /////////////////////////////////////

    // Configure to Measure Htotal Pixel Count
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT2, _BIT2);

    // Enable HS / VS Invert
    ScalerSetBit(P79_33_MHL_MEASURE_19, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // Re-Trigger MHL 3.0 Measure
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, _BIT7);

    ScalerTimerPollingFlagProc(100, P79_20_MHL_MEASURE_0, _BIT7, _FALSE);

    // Get Hstart 1
    ScalerRead(P79_21_MHL_MEASURE_1, 2, &pData[0], _AUTOINC);

    // Get Hstart 2
    ScalerRead(P79_23_MHL_MEASURE_3, 2, &pData[2], _AUTOINC);

    // Calculate Hstart Average
    usHstartAvgInv = ((((WORD)pData[0] << 8) | ((WORD)pData[1] << 0)) + (((WORD)pData[2] << 8) | ((WORD)pData[3] << 0))) / 2;

    // Get Vstart
    ScalerRead(P79_2F_MHL_MEASURE_15, 2, &pData[10], _AUTOINC);
    usVstartAvgInv = PDATA_WORD(5);

    // Get Symbol Number
    ScalerRead(P79_2D_MHL_MEASURE_13, 2, &pData[0], _AUTOINC);
    g_usMhl3Rx5HTotalPixelCount = PDATA_WORD(0);

    // Check if HDMI Format --> g_usMhl3HactivePixelCount = (g_usMhl3HactivePixelCount - 2 * ucPixelModeDiv) / ucPixelModeDiv
    if(ScalerMHL3Rx5FormatDetect() == _SOURCE_HDMI)
    {
        g_usMhl3Rx5HTotalPixelCount = g_usMhl3Rx5HactivePixelCount + (g_usMhl3Rx5HTotalPixelCount - ((g_usMhl3Rx5HactivePixelCount + 2) * ucPixelModeDiv)) / 2;
    }
    else if(ScalerMHL3Rx5FormatDetect() == _SOURCE_DVI) // Check if DVI Format --> g_usMhl3HactivePixelCount = g_usMhl3HactivePixelCount / ucPixelModeDiv
    {
        g_usMhl3Rx5HTotalPixelCount = g_usMhl3Rx5HactivePixelCount + (g_usMhl3Rx5HTotalPixelCount - (g_usMhl3Rx5HactivePixelCount * ucPixelModeDiv)) / 2;
    }


    ///////////////////////////////////////////
    //////// HS / VS Polarity Decesion ////////
    ///////////////////////////////////////////

    // James RL6369-B / RL6369-C Bug
    if(usHstartAvgInv > usHstartAvgNonInv)
    // if((usHstartAvgInv > usHstartAvgNonInv) && (ScalerGetBit(P26_33_MHL_MEASURE_19, _BIT7) == _BIT7))
    {
        // Enable HS Invert
        ScalerSetBit(P79_33_MHL_MEASURE_19, ~_BIT5, _BIT5);
    }
    else if(usHstartAvgInv < usHstartAvgNonInv)
    // else if((usHstartAvgInv < usHstartAvgNonInv) && (ScalerGetBit(P26_33_MHL_MEASURE_19, _BIT7) == 0x00))
    {
        // Disable HS Invert
        ScalerSetBit(P79_33_MHL_MEASURE_19, ~_BIT5, 0x00);
    }
    else
    {
#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("HS Polarity Check Fail", (usHstartAvgInv == usHstartAvgNonInv));
#endif
        return _FALSE;
    }

    if(usVstartAvgInv > usVstartAvgNonInv)
    // if((usVstartAvgInv > usVstartAvgNonInv) && (ScalerGetBit(P26_33_MHL_MEASURE_19, _BIT6) == _BIT6))
    {
        // Enable VS Invert
        ScalerSetBit(P79_33_MHL_MEASURE_19, ~_BIT4, _BIT4);
    }
    else if(usVstartAvgInv < usVstartAvgNonInv)
    // else if((usVstartAvgInv < usVstartAvgNonInv) && (ScalerGetBit(P26_33_MHL_MEASURE_19, _BIT6) == 0x00))
    {
        // Disable HS Invert
        ScalerSetBit(P79_33_MHL_MEASURE_19, ~_BIT4, 0x00);
    }
    else
    {
#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("VS Polarity Check Fail", (usVstartAvgInv == usVstartAvgNonInv));
#endif
        return _FALSE;
    }

    // Re-Trigger MHL 3.0 Measure After HS / VS Must Postive_Polarity
    ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, _BIT7);

    ScalerTimerPollingFlagProc(100, P79_20_MHL_MEASURE_0, _BIT7, _FALSE);


    //////////////////////////
    //// Horizontal Check ////
    //////////////////////////

    // Get Hstart 1
    ScalerRead(P79_21_MHL_MEASURE_1, 2, &pData[0], _AUTOINC);

    // Get Hstart 2
    ScalerRead(P79_23_MHL_MEASURE_3, 2, &pData[2], _AUTOINC);

    // Calculate Hstart Average
    g_usMhl3Rx5HstartAvg = ((((WORD)pData[0] << 8) | ((WORD)pData[1] << 0)) + (((WORD)pData[2] << 8) | ((WORD)pData[3] << 0))) / 2;

    // Get Hend 1
    ScalerRead(P79_25_MHL_MEASURE_5, 2, &pData[4], _AUTOINC);

    // Get Hend 2
    ScalerRead(P79_27_MHL_MEASURE_7, 2, &pData[6], _AUTOINC);

    // Calculate Hend Average
    g_usMhl3Rx5HendAvg = ((((WORD)pData[4] << 8) | ((WORD)pData[5] << 0)) + (((WORD)pData[6] << 8) | ((WORD)pData[7] << 0))) / 2;


    // Calculate Hactives
    usHactiveAvg1 = abs((((WORD)pData[4] << 8) | ((WORD)pData[5] << 0)) - (((WORD)pData[0] << 8) | ((WORD)pData[1] << 0)));

    usHactiveAvg2 = abs((((WORD)pData[6] << 8) | ((WORD)pData[7] << 0)) - (((WORD)pData[2] << 8) | ((WORD)pData[3] << 0)));

    // Calculate Hstart Difference
    usHactiveDiff = abs(usHactiveAvg1 - usHactiveAvg2);

    // Calculate Hactive Average
    g_usMhl3Rx5HactiveAvg = g_usMhl3Rx5HendAvg - g_usMhl3Rx5HstartAvg;

    // Get Htotal 1
    ScalerRead(P79_29_MHL_MEASURE_9, 2, &pData[6], _AUTOINC);

    // Get Htotal 2
    ScalerRead(P79_2B_MHL_MEASURE_11, 2, &pData[8], _AUTOINC);

    // Calculate Htotal Difference
    usHtotalDiff = abs((((WORD)pData[6] << 8) | ((WORD)pData[7] << 0)) - (((WORD)pData[8] << 8) | ((WORD)pData[9] << 0)));

    // Calculate Htotal
    g_usMhl3Rx5HtotalAvg = ((((WORD)pData[6] << 8) | ((WORD)pData[7] << 0)) + (((WORD)pData[8] << 8) | ((WORD)pData[9] << 0))) / 2;


    //////////////////////////
    ///// Vertical Check /////
    //////////////////////////

    // Get Vtotal 1
    ScalerRead(P79_34_MHL_MEASURE_20, 2, &pData[8], _AUTOINC);

    // Get Vtotal 2
    ScalerRead(P79_36_MHL_MEASURE_22, 2, &pData[10], _AUTOINC);

    // Calculate Vtotal
    usVtotalDiff = abs((((WORD)pData[8] << 8) | ((WORD)pData[9] << 0)) - (((WORD)pData[10] << 8) | ((WORD)pData[11] << 0)));

    // Calculate Vtotal
    g_usMhl3Rx5Vtotal = ((((WORD)pData[8] << 8) | ((WORD)pData[9] << 0)) + (((WORD)pData[10] << 8) | ((WORD)pData[11] << 0))) / 2;

    // Get Vstart
    ScalerRead(P79_2F_MHL_MEASURE_15, 2, &pData[10], _AUTOINC);
    g_usMhl3Rx5Vstart = PDATA_WORD(5);

    // Get Vend
    ScalerRead(P79_31_MHL_MEASURE_17, 2, &pData[12], _AUTOINC);
    g_usMhl3Rx5Vend = PDATA_WORD(6);

    // Calculate Vactive
    g_usMhl3Rx5Vactive = g_usMhl3Rx5Vend - g_usMhl3Rx5Vstart;

#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
    //--------------------- Debug Message ---------------------//
    DebugMessageMHL("- g_usMhl3HstartAvg = ", g_usMhl3Rx5HstartAvg);
    DebugMessageMHL("- g_usMhl3HendAvg = ", g_usMhl3Rx5HendAvg);
    DebugMessageMHL("- g_usMhl3HactiveAvg = ", g_usMhl3Rx5HactiveAvg);
    DebugMessageMHL("- g_usMhl3HtotalAvg = ", g_usMhl3Rx5HtotalAvg);
    DebugMessageMHL("- g_usMhl3Vstart = ", g_usMhl3Rx5Vstart);
    DebugMessageMHL("- g_usMhl3Vend = ", g_usMhl3Rx5Vend);
    DebugMessageMHL("- g_usMhl3Vactive = ", g_usMhl3Rx5Vactive);
    DebugMessageMHL("- g_usMhl3Vtotal = ", g_usMhl3Rx5Vtotal);
    DebugMessageMHL("- g_usMhl3HactivePixelCount = ", g_usMhl3Rx5HactivePixelCount);
    DebugMessageMHL("- g_usMhl3HTotalPixelCount = ", g_usMhl3Rx5HTotalPixelCount);
    DebugMessageMHL("--- usHactiveDiff = ", usHactiveDiff);
    DebugMessageMHL("--- usHtotalDiff = ", usHtotalDiff);
    DebugMessageMHL("--- usVtotalDiff = ", usVtotalDiff);
    //---------------------------------------------------------//
#endif

    //--------------- Check Measure Result Fail / Error -----------------//
    /* When RR Symbol Hit Vsync Duration -> Measure Result Will be Wrong */
    //-------------------------------------------------------------------//
    if((g_usMhl3Rx5HstartAvg == 0x0000) || (g_usMhl3Rx5HendAvg == 0x0000) || (g_usMhl3Rx5HactiveAvg == 0x0000) || (g_usMhl3Rx5HtotalAvg == 0x0000) ||
       (g_usMhl3Rx5Vstart == 0x0000) || (g_usMhl3Rx5Vend == 0x0000) || (g_usMhl3Rx5Vactive == 0x0000) || (g_usMhl3Rx5Vtotal == 0x0000) || (g_usMhl3Rx5HactivePixelCount == 0x0000) ||
       (usHactiveDiff >= (g_usMhl3Rx5Vactive >> 2)) || (usHtotalDiff >= (g_usMhl3Rx5HtotalAvg >> 2)) || (usVtotalDiff >= (g_usMhl3Rx5Vtotal >> 2)))
    {
        if((ScalerTMDSRx5HdcpEnabled() == _TRUE) && (GET_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT() < 10))
        {
            ADD_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT();
        }
        else
        {
            CLR_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT();

            // Digital Phy Block Reset
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
            ScalerTimerDelayXms(30);
            ScalerSetBit(PB_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);
        }

        return _FALSE;
    }

    CLR_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT();

    return _TRUE;
}


//--------------------------------------------------
// Description  : MHL 3.0 Detect Clk Bits Mode / Video Format
// Input Value  : None
// Output Value : Bit Mode for Divider
//--------------------------------------------------
BYTE ScalerMHL3Rx5FormatDetect(void)
{
    if(ScalerGetBit(P79_38_MHL_MEASURE_24, _BIT5) == _BIT5) // DVI Format
    {
        ScalerSetBit(P79_0B_MHL_S2P, ~_BIT0, _BIT0);

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
        ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, ~_BIT1, 0x00);
#endif

        return _SOURCE_DVI;
    }
    else // MHL 3.0 HDMI Format
    {
        ScalerSetBit(P79_0B_MHL_S2P, ~_BIT0, 0x00);

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
        ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, ~_BIT1, _BIT1);
#endif

        return _SOURCE_HDMI;
    }
}


//--------------------------------------------------
// Description  : MHL 3.0 Detect Clk Bits Mode / Video Format
// Input Value  : None
// Output Value : Bit Mode for Divider
//--------------------------------------------------
bit ScalerMHL3Rx5ViewPixelFormatCheck(void)
{
    if(ScalerGetBit(P79_38_MHL_MEASURE_24, _BIT6) == 0x00) // Mode Detect Non-Error
    {
        if(ScalerGetBit(P79_38_MHL_MEASURE_24, _BIT7) == _BIT7) // 16 Bits Mode
        {
            ScalerSetBit(P79_00_MHL_EN, ~_BIT2, _BIT2);

            SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(_MHL3_VIDEO_16BIT_FORMAT);

            SET_MHL3_RX5_VIEW_PIXEL_DIVIDER(_MHL3_VIDEO_16BIT_MODE_DIV);

#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("16 Bit Mode", 0x00);
#endif
        }
        else // 24 Bits Mode
        {
            ScalerSetBit(P79_00_MHL_EN, ~_BIT2, 0x00);

            SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(_MHL3_VIDEO_24BIT_FORMAT);

            SET_MHL3_RX5_VIEW_PIXEL_DIVIDER(_MHL3_VIDEO_24BIT_MODE_DIV);

#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
            DebugMessageMHL("24 Bit Mode", 0x00);
#endif
        }

        return _TRUE;
    }
    else
    {
        SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(_MHL3_VIDEO_FORMAT_NULL);

        SET_MHL3_RX5_VIEW_PIXEL_DIVIDER(_MHL3_VIDEO_MODE_DIV_ERROR);

        return _FALSE;
    }
}


//--------------------------------------------------
// Description  : Check ECBUS Interlace by VBID or Measure
// Input Value  : None
// Output Value : True --> Interlace
//--------------------------------------------------
bit ScalerMHL3Rx5InterlaceCheck(void)
{
    if(ScalerGetBit(P79_33_MHL_MEASURE_19, _BIT2) == _BIT2)
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}


//--------------------------------------------------
// Description  : ECBUS-S Display Format Generator Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerMHL3Rx5DisplayFormatSetting(void)
{
    BYTE ucPixelModeDiv = _MHL3_VIDEO_MODE_DIV_ERROR;
    DWORD ulLinkClkValue = 0;
    WORD usFifoOffset = 512;
    DWORD ulMhl3VstoVsDelay = 0;

    ////////////////////////////////////////////////////
    /////// Calculate LinkClk-PixelClk Conversion //////
    ////////////////////////////////////////////////////

    // Compute Link Clk (Unit: kHz)
    ulLinkClkValue = (DWORD)GET_D5_INPUT_PIXEL_CLK() * GET_MHL3_RX5_AV_LINK_N_CODE() * 100;

    // Check MHL Clk Mode (24 Bits or 16 Bits)
    ucPixelModeDiv = GET_MHL3_RX5_VIEW_PIXEL_DIVIDER();

    // Compute Pixel Clock => PixelClk = (H Active PixelCount / HActive_CountByLinkClk) x LinkCount (Unit: kHz)
    g_ulMhl3Rx5PixelClkValue = (DWORD)(g_usMhl3Rx5HactivePixelCount) * ulLinkClkValue / (DWORD)g_usMhl3Rx5HactiveAvg;

    // James Reserved for RL6369-C
    // Compute Pixel Clock => PixelClk = (H Total PixelCount / HTotal_CountByLinkClk) x LinkCount (Unit: kHz)
    g_ulMhl3Rx5PixelClkValue = (DWORD)(g_usMhl3Rx5HTotalPixelCount) * ulLinkClkValue / (DWORD)g_usMhl3Rx5HtotalAvg;

    // If Pixel Clk > 300MHz, 1/2 SD at Format Conv.
    if(g_ulMhl3Rx5PixelClkValue > 300000)
    {
#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("Pixel Exceed 300MHz", 0x00);
#endif
    }


    /////////////////////////////////////
    /////// Display Format Setting //////
    /////////////////////////////////////

    // Disable Display Format Generation, Set Values
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT7, 0x00);

    // Calculate Hstart (in Pixel Clk)
    PDATA_WORD(0) = (WORD)((DWORD)g_usMhl3Rx5HstartAvg * g_ulMhl3Rx5PixelClkValue / ulLinkClkValue);

    //--- Set Hstart ---//
    ScalerSetByte(P79_4E_MN_DPF_HST_M, pData[0]);
    ScalerSetByte(P79_4F_MN_DPF_HST_L, pData[1]);

    // Calculate Hactive (in Pixel Clk)
    PDATA_WORD(1) = g_usMhl3Rx5HactivePixelCount;

    //--- Set Hactive ---//
    ScalerSetByte(P79_50_MN_DPF_HWD_M, pData[2]);
    ScalerSetByte(P79_51_MN_DPF_HWD_L, pData[3]);

    // Calculate Htotal (in Pixel Clk)
    PDATA_WORD(2) = (WORD)((DWORD)g_usMhl3Rx5HtotalAvg * g_ulMhl3Rx5PixelClkValue / ulLinkClkValue);

    //--- Set Htotal ---//
    ScalerSetByte(P79_4C_MN_DPF_HTT_M, pData[4]);
    ScalerSetByte(P79_4D_MN_DPF_HTT_L, pData[5]);

    //--- Set Vactive ---//
    ScalerSetByte(P79_58_MN_DPF_VHT_M, (BYTE)(g_usMhl3Rx5Vactive >> 8));
    ScalerSetByte(P79_59_MN_DPF_VHT_L, (BYTE)(g_usMhl3Rx5Vactive & 0x00FF));

    //--- Set Vtotal ---//
    ScalerSetByte(P79_54_MN_DPF_VTT_M, (BYTE)(g_usMhl3Rx5Vtotal >> 8));
    ScalerSetByte(P79_55_MN_DPF_VTT_L, (BYTE)(g_usMhl3Rx5Vtotal & 0x00FF));


    /**************************************************/
    /********* Vtotal - Vstart - Vactive < 2 **********/
    /**** --> Last Line Issue (Don't Care in MHL3) ****/
    /**************************************************/
    if((g_usMhl3Rx5Vend >= g_usMhl3Rx5Vstart + g_usMhl3Rx5Vactive) &&
       (g_usMhl3Rx5Vstart >= 3) && (g_usMhl3Rx5Vstart - 2 > 3) &&
       (g_usMhl3Rx5Vtotal - g_usMhl3Rx5Vstart - g_usMhl3Rx5Vactive < 2))
    {
        g_usMhl3Rx5Vstart = g_usMhl3Rx5Vstart - 2;
    }

    //--- Set Vstart ---//
    ScalerSetByte(P79_56_MN_DPF_VST_M, (BYTE)(g_usMhl3Rx5Vstart >> 8));
    ScalerSetByte(P79_57_MN_DPF_VST_L, (BYTE)(g_usMhl3Rx5Vstart & 0x00FF));

    //--- Set HSW --> Negative and 3 Lines width ---//
    ScalerSetByte(P79_52_MN_DPF_HSW_M, 0x00);
    ScalerSetByte(P79_53_MN_DPF_HSW_L, 0x0F);

    //--- Set VSW --> Negative and 3 Lines width ---//
    ScalerSetByte(P79_5A_MN_DPF_VSW_M, 0x00);
    ScalerSetByte(P79_5B_MN_DPF_VSW_L, 0x03);


    //////////////////////////////////////////////////////
    /////// Display Setting Depents on Video Format //////
    //////////////////////////////////////////////////////

    //------------------------------------------------//
    //--- Use VS to VS Delay (for Frame Sync Mode) ---//
    //------------------------------------------------//

    ulMhl3VstoVsDelay = (DWORD)_MHL3_VSYNC_TO_VSYNC_DELAY;

    if(ScalerMHL3Rx5InterlaceCheck() == _TRUE) // Interlace
    {
#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("MHL 3.0 : IIIIIIterLace", 0);
#endif
        // Get Vtotal 1
        ScalerRead(P79_34_MHL_MEASURE_20, 2, &pData[4], _AUTOINC);

        // Get Vtotal 2
        ScalerRead(P79_36_MHL_MEASURE_22, 2, &pData[6], _AUTOINC);

        if((((WORD)pData[4] << 8) | ((WORD)pData[5] << 0)) < (((WORD)pData[6] << 8) | ((WORD)pData[7] << 0)))
        {
            // Set Odd Field VS to VS Delay (Not used in De_Only Mode)
            ScalerSetByte(P79_46_OVBLK2VS_H, (LOBYTE(ulMhl3VstoVsDelay >> 16)));
            ScalerSetByte(P79_47_OVBLK2VS_M, (LOBYTE(ulMhl3VstoVsDelay >> 8)));
            ScalerSetByte(P79_48_OVBLK2VS_L, LOBYTE(ulMhl3VstoVsDelay));

            // BStoVSDelay = BStoVSDelay + 1;
            ulMhl3VstoVsDelay = ulMhl3VstoVsDelay + 1;

            // Set Even Field VS to VS Delay (Not used in De_Only Mode)
            ScalerSetByte(P79_43_EVBLK2VS_H, (LOBYTE(ulMhl3VstoVsDelay >> 16)));
            ScalerSetByte(P79_44_EVBLK2VS_M, (LOBYTE(ulMhl3VstoVsDelay >> 8)));
            ScalerSetByte(P79_45_EVBLK2VS_L, LOBYTE(ulMhl3VstoVsDelay));
        }
        else if((((WORD)pData[4] << 8) | ((WORD)pData[5] << 0)) > (((WORD)pData[6] << 8) | ((WORD)pData[7] << 0)))
        {
            // Set Even Field VS to VS Delay (Not used in De_Only Mode)
            ScalerSetByte(P79_43_EVBLK2VS_H, (LOBYTE(ulMhl3VstoVsDelay >> 16)));
            ScalerSetByte(P79_44_EVBLK2VS_M, (LOBYTE(ulMhl3VstoVsDelay >> 8)));
            ScalerSetByte(P79_45_EVBLK2VS_L, LOBYTE(ulMhl3VstoVsDelay));

            // BStoVSDelay = BStoVSDelay - 1;
            ulMhl3VstoVsDelay = ulMhl3VstoVsDelay - 1;

            // Set Odd Field VS to VS Delay (Not used in De_Only Mode)
            ScalerSetByte(P79_46_OVBLK2VS_H, (LOBYTE(ulMhl3VstoVsDelay >> 16)));
            ScalerSetByte(P79_47_OVBLK2VS_M, (LOBYTE(ulMhl3VstoVsDelay >> 8)));
            ScalerSetByte(P79_48_OVBLK2VS_L, LOBYTE(ulMhl3VstoVsDelay));
        }

        // Enable ECBUS Interlace
        ScalerSetBit(P79_5C_INTERLACE_MODE_CONFIG, ~_BIT7, _BIT7);
    }
    else // Progressive
    {
#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("MHL 3.0 : PPPPProgressive", 0);
#endif
        // Set Odd Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P79_46_OVBLK2VS_H, (LOBYTE(ulMhl3VstoVsDelay >> 16)));
        ScalerSetByte(P79_47_OVBLK2VS_M, (LOBYTE(ulMhl3VstoVsDelay >> 8)));
        ScalerSetByte(P79_48_OVBLK2VS_L, LOBYTE(ulMhl3VstoVsDelay));

        // Set Even Field VS to VS Delay (Not used in De_Only Mode)
        ScalerSetByte(P79_43_EVBLK2VS_H, (LOBYTE(ulMhl3VstoVsDelay >> 16)));
        ScalerSetByte(P79_44_EVBLK2VS_M, (LOBYTE(ulMhl3VstoVsDelay >> 8)));
        ScalerSetByte(P79_45_EVBLK2VS_L, LOBYTE(ulMhl3VstoVsDelay));

        // Disable ECBUS Interlace
        ScalerSetBit(P79_5C_INTERLACE_MODE_CONFIG, ~_BIT7, 0x00);
    }


    //------------------------------------------------------------//
    //---- Use HS to HS Delay (for DE_Only / Line_Sync Mode) -----//
    //------------------------------------------------------------//

    // Compute Fifo Offset PixelClk + Hstart
    // usFifoOffset = usFifoOffset * ucPixelModeDiv + g_usMhl3HstartAvg;

    // Set HS to HS Delay (for DE_Only Mode)
    ScalerSetByte(P79_49_BS2HS_0, (BYTE)(usFifoOffset >> 8));
    ScalerSetByte(P79_4A_BS2HS_1, (BYTE)(usFifoOffset & 0x00FF));

    // Set VS Front Porch (for DE_Only Mode)
    ScalerSetByte(P79_4B_VS_FRONT_PORCH, 0x04);

    // Enable DE_ONLY Mode (Line_Sync Mode)
    ScalerSetBit(P79_41_DPF_CTRL_0, ~(_BIT7 | _BIT5 | _BIT4), _BIT4);

    // Double Buffer to Apply Display Format Setting
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT6, _BIT6);

    return _TRUE;
}


/*
//--------------------------------------------------
// Description  : ECBUS BS to HS Delay Calculation (for DE_ONLY Mode)
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerMHL3GetBStoHSDelay(void)
{
    DWORD ulHFrontPorch = 0;
    DWORD usFifoOffset = 0;

    //--- Get Htotal ---//
    pData[0] = ScalerGetByte(P26_4C_MN_DPF_HTT_M);
    pData[1] = ScalerGetByte(P26_4D_MN_DPF_HTT_L);

    //--- Get Hstart ---//
    pData[2] = ScalerGetByte(P26_4E_MN_DPF_HST_M);
    pData[3] = ScalerGetByte(P26_4F_MN_DPF_HST_L);

    //--- Get Hactive ---//
    pData[4] = ScalerGetByte(P26_50_MN_DPF_HWD_M);
    pData[5] = ScalerGetByte(P26_51_MN_DPF_HWD_L);

    // HFrontPorch = (Htotal - Hend) * (Link Clk / Stream CLK)
    ulHFrontPorch = (DWORD)(PDATA_WORD(0) - PDATA_WORD(1) - PDATA_WORD(2));

    // Fifo size = 360 x 64bit
    // FifoOffset = (1/2 * (256 * 96) / (24bps or 16bps))
    usFifoOffset = 512;

    return ((ulHFrontPorch + usFifoOffset) / 2);

}


//--------------------------------------------------
// Description  : ECBUS BS to VS Delay Calculation (for Frame Sync Mode)
// Input Value  : None
// Output Value : BS to VS Delay
//--------------------------------------------------
DWORD ScalerMHL3GetBStoVSDelay(void)
{
    DWORD ulVFrontPorch = 0;
    DWORD ulHFrontPorch = 0;
    DWORD usFifoOffset = 0;

    // Get Vtotal 1
    ScalerRead(P26_34_MHL_MEASURE_20, 2, &pData[0], _AUTOINC);

    //--- Get Vtotal ---//
    pData[0] = ScalerGetByte(P26_54_MN_DPF_VTT_M);
    pData[1] = ScalerGetByte(P26_55_MN_DPF_VTT_L);

    //--- Get Vstart ---//
    pData[2] = ScalerGetByte(P26_56_MN_DPF_VST_M);
    pData[3] = ScalerGetByte(P26_57_MN_DPF_VST_L);

    //--- Get Vactive ---//
    pData[4] = ScalerGetByte(P26_58_MN_DPF_VHT_M);
    pData[5] = ScalerGetByte(P26_59_MN_DPF_VHT_L);

    // (Vtotal - Vstart - Vactive) < 2 --> Last Line Issue --> Vstart - 2
    if((PDATA_WORD(0) >= (PDATA_WORD(1) + PDATA_WORD(2))) &&
        (PDATA_WORD(1) >= 3) &&
        (PDATA_WORD(0) - (PDATA_WORD(1) + PDATA_WORD(2)) < 2) &&
        ((PDATA_WORD(1) - 2) > 3))
    {
        PDATA_WORD(1) = PDATA_WORD(1) - 2;
    }

    // VFrontPorch = (Vtotal - Vend) * Htotal * (Link Clk / Stream CLK)
    ulVFrontPorch = ((DWORD)(PDATA_WORD(3) - PDATA_WORD(2))) * (DWORD)PDATA_WORD(4);

    //--- Get Htotal ---//
    pData[0] = ScalerGetByte(P26_4C_MN_DPF_HTT_M);
    pData[1] = ScalerGetByte(P26_4D_MN_DPF_HTT_L);

    //--- Get Hstart ---//
    pData[2] = ScalerGetByte(P26_4E_MN_DPF_HST_M);
    pData[3] = ScalerGetByte(P26_4F_MN_DPF_HST_L);

    //--- Get Hactive ---//
    pData[4] = ScalerGetByte(P26_50_MN_DPF_HWD_M);
    pData[5] = ScalerGetByte(P26_51_MN_DPF_HWD_L);

    // HFrontPorch = (Htotal - Hend) * (Link Clk / Stream CLK)
    ulHFrontPorch = (DWORD)(PDATA_WORD(0) - PDATA_WORD(1) - PDATA_WORD(2));

    // Fifo size = 360 x 64bit
    // FifoOffset = (1/2 * (256 * 96) / (24bps or 16bps))
    usFifoOffset = 512;

    return ((ulVFrontPorch + ulHFrontPorch + usFifoOffset) / 2);

}
*/

//--------------------------------------------------
// Description  : MHL 3.0 Pixel Clk PLL Setting
// Input Value  : None
// Output Value : True --> Stream CLK Regen. ok
//--------------------------------------------------
DWORD ScalerMHL3Rx5StreamClkRegenerate(void)
{
    DWORD ulXtal_clk = 0;
    DWORD ulpllm = 0;
    BYTE ucplln = 0;
    BYTE ucpllo = 0;
    BYTE ucdivs = 0;
    BYTE ucdiv2 = 0;
    BYTE ucdiv_pllo = 0;
    BYTE ucdiv_divs = 0;
    BYTE ucBuf = 0;
    SDWORD lOffsetValue = 0;
    BYTE ucCPI = 0;
    WORD usHtotal = 0;
    WORD usVtotal = 0;

#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
    //--------------------- Debug Message ---------------------//
    DebugMessageMHL("Target Pixel Clk Compute by Measure", g_ulMhl3Rx5PixelClkValue);
    DebugMessageMHL("eCBUS Clk", GET_D5_INPUT_PIXEL_CLK());
    //---------------------------------------------------------//
#endif

    ///////////////////////////
    // Get Htotal and Vtotal //
    ///////////////////////////

    // Get Htotal (in Pixel Clk)
    pData[0] = ScalerGetByte(P79_4C_MN_DPF_HTT_M);
    pData[1] = ScalerGetByte(P79_4D_MN_DPF_HTT_L);

    usHtotal = ((((WORD)pData[0]) << 8) | ((WORD)pData[1]));

    // Get Vtotal (in Pixel Clk)
    pData[0] = ScalerGetByte(P79_54_MN_DPF_VTT_M);
    pData[1] = ScalerGetByte(P79_55_MN_DPF_VTT_L);

    usVtotal = ((((WORD)pData[0]) << 8) | ((WORD)pData[1]));


    /////////////////////////////////////
    // Set Pixel Clk for Link Training //
    /////////////////////////////////////

    // PLL Input Clock select to Xtal Clock, [7:6] = 00
    // PLL Output Clock Select to PLL Clock, [5] = 0
    // Trigger Double Buffer. [4] = 1
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT4);

    // Set Xtal Clk (Unit: KHz)
    ulXtal_clk = _GDI_CLK_KHZ;

    // Set N Code
    ucplln = 2;

    // Get DPLL parameter
    // If "600Mhz > g_ulMhl3PixelClkValue > 270Mhz"
    if((600000 > g_ulMhl3Rx5PixelClkValue) && (g_ulMhl3Rx5PixelClkValue >= 270000))
    {
        ucpllo = 0;
        ucdivs = 0;

        ucdiv_divs = 1;
        ucdiv_pllo = 1;

        ulpllm = ((((g_ulMhl3Rx5PixelClkValue) * ucdiv_divs * ucdiv_pllo) * ucplln * 256) / (ulXtal_clk * 256));

        if(ulpllm > 257)
        {
            return 0x00;
        }
    }
    // If "270MHz > g_ulMhl3PixelClkValue > 8.437Mhz"
    else if((g_ulMhl3Rx5PixelClkValue < 270000) && (g_ulMhl3Rx5PixelClkValue >= 8437))
    {
        ucpllo = 1;

        if((g_ulMhl3Rx5PixelClkValue < 270000) && (g_ulMhl3Rx5PixelClkValue >= 135000))
        {
            ucdivs = 0;
        }
        else if((g_ulMhl3Rx5PixelClkValue < 135000) && (g_ulMhl3Rx5PixelClkValue >= 67500))
        {
            ucdivs = 1;
        }
        else if((g_ulMhl3Rx5PixelClkValue < 67500) && (g_ulMhl3Rx5PixelClkValue >= 33750))
        {
            ucdivs = 2;
        }
        else if((g_ulMhl3Rx5PixelClkValue < 33750) && (g_ulMhl3Rx5PixelClkValue >= 16875))
        {
            ucdivs = 4;
        }
        else
        {
            ucdivs = 8;
        }

        // Because set 17 get minimum error for recovery Pixel clk , close to fact clk.
        if(ucdivs == 0)
        {
            ucdiv_divs = 1;
        }
        else
        {
            ucdiv_divs = 2 * ucdivs;
        }

        ucdiv_pllo = 1;

        if(ucpllo != 0)
        {
            ucdiv_pllo = 1;

            for(ucBuf = 0; ucBuf < ucpllo; ucBuf++)
            {
                ucdiv_pllo = 2 * ucdiv_pllo;
            }
        }

        // ulpllm = ((((g_ulMhl3PixelClkValue * 256)) * ucplln) / (ulXtal_clk * 256));
        ulpllm = ((((g_ulMhl3Rx5PixelClkValue * ucdiv_pllo * ucdiv_divs * 256)) * ucplln) / (ulXtal_clk * 256));

        if(ulpllm > 257)
        {
            return 0x00;
        }
    }
    else
    {
        return 0x00;
    }

    // offset = (m/n*f_ref - f)/(m/n*f_ref)*2^21
    // seperate *2^21 to *32*16384*4
    lOffsetValue = ((SDWORD)(g_ulMhl3Rx5PixelClkValue * ucdiv_pllo * ucdiv_divs) - (SDWORD)((ulXtal_clk / ucplln) * ulpllm)) * 16384 / ulpllm * ucplln / ulXtal_clk * 32 * 4;

    // DPPLL Power Down
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, _BIT7);

    // Disable HSync Tracking
    // Set HS/VS Mode -> Normal,
    // Set HS/VS Select -> HS Track
    // HS Tracking Select -> MHL HS
    ScalerSetBit(PB5_A7_MN_SCLKG_TRK_CTRL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT1), (_BIT4 | _BIT3 | _BIT1));

    // Set VCOMD, phase Swallow Circuit Clock Select, SCLKGSTOP
    ScalerSetBit(PB5_BF_MN_SCLKG_PLL_WD, ~(0x7F), 0x16);

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(PB5_A3_MN_SCLKG_DIVS, (((ucdiv2) << 7) | ((ucdivs) << 0)));

    // Set DPPLL Div_O.
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), ucpllo);

    // Offset Value Setting
    ScalerSetByte(PB5_A6_MN_SCLKG_OFFS_L, (BYTE)lOffsetValue);
    ScalerSetByte(PB5_A5_MN_SCLKG_OFFS_M, (BYTE)(lOffsetValue >> 8));
    ScalerSetBit(PB5_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 | _BIT0), ((BYTE)(lOffsetValue >> 16)) & (_BIT2 | _BIT1 | _BIT0));

    // Enable phase swallow
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set Tracking Region to Active Region
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT0, 0x00);

    // Set DPPLL M Code
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), (((ulpllm - 2) >> 8) & 0x03));
    ScalerSetByte(PB5_A1_MN_SCLKG_DIVM, ((ulpllm - 2) & 0xFF));

    // Set DPPLL N Code
    ScalerSetByte(PB5_A2_MN_SCLKG_DIVN, (ucplln - 2));

    // Load offset value
    ScalerSetBit(PB5_A4_MN_SCLKG_OFFS_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Double Buffer for M/N Tracking
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // DPLL Power On
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    ScalerTimerDelayXms(2);


    ////////////////////////////////
    // DPPLL VCO Band Calibration //
    ////////////////////////////////

    // Reg DPLL_CMPEN
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALLCH
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALSW
    ScalerSetBit(PB5_BD_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);

    // VCO Band : 10 ---> KVCO = 1880
    // VCO Band : 11 ---> KVCO = 2340
    // R : 13
    // Icp = 6.28 * 700 * M / KVCO / R
    // Icp   = 2.5u + D0[0] * 2.5u + D0[1] * 5u + D0[2] * 10u (A)
    // Icp = 2.5uA, 5uA, 7.5uA, 10uA......
    if(ScalerGetBit(PB5_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) == _BIT5)
    {
        ucCPI = 4396 * ulpllm / 1880 / 13;
    }
    else if(ScalerGetBit(PB5_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) == (_BIT5 | _BIT4))
    {
        ucCPI = 4396 * ulpllm / 2340 / 13;
    }

    ucCPI = ((20 * ucCPI) + 25) / 50;
    ucCPI -= (ucCPI == 0) ? 0 : 1;

    // Set PLL Charge Pump Current
    ScalerSetByte(PB5_BE_MN_SCLKG_PLL_CHP, (0x78 | (ucCPI & 0x07)));


    ////////////////////////////////////////
    // DPPLL HS Tracking Tracking Setting //
    ////////////////////////////////////////

    // Disable Tracking New Mode
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT1);

    // Set Initial I/P Code
    ScalerSetByte(PB5_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PB5_B3_MN_SCLKG_TRK_VS_P_H, 0x07);
    ScalerSetByte(PB5_B4_MN_SCLKG_TRK_VS_P_M, 0xFF);
    ScalerSetByte(PB5_B5_MN_SCLKG_TRK_VS_P_L, 0xFF);

    // Set Tracking Freq -> Every Line
    ScalerSetBit(PB5_A8_MN_SCLKG_TRK_MN_I_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

    // Set Tracking Lock PE
    ScalerSetByte(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, 0x7F);

    // Enable H Sync Tracking
    ScalerSetBit(PB5_A7_MN_SCLKG_TRK_CTRL, ~_BIT6, _BIT6);

    // Double Buffer for H Sync Tracking
    ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // Get Frame Period (Unit: ms)
    PDATA_WORD(7) = 1000 / (g_ulMhl3Rx5PixelClkValue / usHtotal / usVtotal) + 1;

    pData[0] = 0;
    // Waiting for Stream Clk Stable
    do
    {
        // Clear PE Flag
        ScalerSetBit(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, ~_BIT7, _BIT7);
        ScalerTimerDelayXms(PDATA_WORD(7));

        pData[0]++;
    }
    while((ScalerGetBit(PB5_B7_MN_SCLKG_TRK_VS_NLOCK, _BIT7) == _BIT7) && (pData[0] < 10));

    // Set Final I/P Code
    ScalerSetByte(PB5_B1_MN_SCLKG_TRK_VS_I_M, 0x00);
    ScalerSetByte(PB5_B2_MN_SCLKG_TRK_VS_I_L, 0x02);

    // Start Generate Display Format
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT7, _BIT7);

    // Enable Tracking New Mode
    ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~(_BIT2 | _BIT1), _BIT2);

    return g_ulMhl3Rx5PixelClkValue;
}


//--------------------------------------------------
// Description  : MHL 3.0 DPF Video Fifo Check
// Input Value  : Fifo Check Condition
// Output Value : True --> Fifo not over/underflow
//--------------------------------------------------
bit ScalerMHL3Rx5DisplayFormatGenFifoCheck(void)
{
    ScalerSetBit(P79_0C_MHL_FIFO_FLAG, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    ScalerTimerDelayXms(30);

    if((ScalerGetBit(P79_0C_MHL_FIFO_FLAG, _BIT1) == _BIT1) || (ScalerGetBit(P79_0C_MHL_FIFO_FLAG, _BIT0) == _BIT0))
    {
        return _FALSE;
    }

    return _TRUE;
}


//--------------------------------------------------
// Description  : MHL 3.0 Adjust Vsync Delay (For De-Only Mode)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5DisplatFormatGenAdjustHsyncDelay(DWORD ulPixelClkValue)
{
    DWORD ulHStoHSDelayDeltaOverflow = 0;
    DWORD ulHStoHSDelayDeltaUnderflow = 0;

    if(ScalerGetBit(P79_0C_MHL_FIFO_FLAG, (_BIT1 | _BIT0)) == 0x00) // Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(P79_0C_MHL_FIFO_FLAG, _BIT1) == _BIT1) // Fifo Overflow
    {
#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("7. MHL 3.0 : Fifo Ovfl", ScalerGetByte(PB5_A1_MN_SCLKG_DIVM));
#endif
        if(g_usMhl3Rx5HactivePixelCount == 0x280)
        {
            ScalerSetByte(PB5_A1_MN_SCLKG_DIVM, ScalerGetByte(PB5_A1_MN_SCLKG_DIVM) + 1);

            // Set Tracking Region to Whole Line (Active + Blanking)
            ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT0, _BIT0);

            ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);
        }
        else
        {
            // Get Htotal (in Pixel Clk)
            pData[0] = ScalerGetByte(P79_4C_MN_DPF_HTT_M);
            pData[1] = ScalerGetByte(P79_4D_MN_DPF_HTT_L);

            // ((Link Clk * 256)/ Pixel CLK) * Htotal / 256 --> 1 Line
            ulHStoHSDelayDeltaOverflow = ((DWORD)GET_D5_INPUT_PIXEL_CLK() * GET_MHL3_RX5_AV_LINK_N_CODE() * 100) / ulPixelClkValue * (DWORD)PDATA_WORD(0);
        }
    }
    else if(ScalerGetBit(P79_0C_MHL_FIFO_FLAG, _BIT0) == _BIT0) // Fifo Underflow
    {
#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("7. MHL 3.0 : Fifo Udfl", ScalerGetByte(PB5_A1_MN_SCLKG_DIVM));
#endif
        if(g_usMhl3Rx5HactivePixelCount == 0x280)
        {
            ScalerSetByte(PB5_A1_MN_SCLKG_DIVM, ScalerGetByte(PB5_A1_MN_SCLKG_DIVM) - 1);

            // Set Tracking Region to Whole Line (Active + Blanking)
            ScalerSetBit(PB5_B8_MN_SCLKG_SDM_CTRL, ~_BIT0, _BIT0);

            ScalerSetBit(PB5_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);
        }
        else
        {
            // Get Hactive (in Pixel Clk)
            pData[0] = ScalerGetByte(P79_50_MN_DPF_HWD_M);
            pData[1] = ScalerGetByte(P79_51_MN_DPF_HWD_L);

            if(PDATA_WORD(0) != 1366)
            {
                return;
            }

            PDATA_WORD(0) = PDATA_WORD(0) - 2;

            // Set Hactive
            ScalerSetByte(PB5_45_MN_DPF_HWD_M, pData[0]);
            ScalerSetByte(PB5_46_MN_DPF_HWD_L, pData[1]);

            // ((Link Clk * 2) / Pixel CLK) --> 2 pixels
            ulHStoHSDelayDeltaUnderflow = ((DWORD)GET_D5_INPUT_PIXEL_CLK() * GET_MHL3_RX5_AV_LINK_N_CODE() * 100 * 2) / ulPixelClkValue;
        }
    }

    // Get HS to HS Delay
    ScalerRead(P79_49_BS2HS_0, 2, &pData[2], _AUTOINC);

    pData[2] = pData[2] & 0x0F;

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    PDATA_DWORD(0) = (DWORD)PDATA_WORD(1) - ((ulHStoHSDelayDeltaOverflow + ulHStoHSDelayDeltaUnderflow) / 2);

    // Set HS to HS Delay (in Pixel Clk)
    ScalerSetByte(P79_49_BS2HS_0, pData[2]);
    ScalerSetByte(P79_4A_BS2HS_1, pData[3]);

    // Enable Double Buffer
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Reset Display Format Gen
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT7, _BIT7);

    ScalerTimerDelayXms(30);
}


//--------------------------------------------------
// Description  : MHL 3.0 Adjust Vsync Delay (For Frame-Sync Mode)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5DisplayFormatGenAdjustVsyncDelay(DWORD ulPixelClkValue)
{
    DWORD ulMhl3OddVstoVsDelay = 0;
    DWORD ulMhl3EvenVstoVsDelay = 0;
    DWORD ulVStoVSDelayDeltaOverflow = 0;
    DWORD ulVStoVSDelayDeltaUnderflow = 0;

    if(ScalerGetBit(P79_0C_MHL_FIFO_FLAG, (_BIT1 | _BIT0)) == 0x00) // Fifo Ok
    {
        return;
    }
    else if(ScalerGetBit(P79_0C_MHL_FIFO_FLAG, _BIT1) == _BIT1) // Fifo Overflow
    {
        // Get Htotal (in Pixel Clk)
        pData[0] = ScalerGetByte(P79_4C_MN_DPF_HTT_M);
        pData[1] = ScalerGetByte(P79_4D_MN_DPF_HTT_L);

        // ((Link Clk * 256)/ Pixel CLK) * Htotal / 256 --> 1 Line
        ulVStoVSDelayDeltaOverflow = ((DWORD)GET_D5_INPUT_PIXEL_CLK() * GET_MHL3_RX5_AV_LINK_N_CODE() * 100) / ulPixelClkValue * (DWORD)PDATA_WORD(0);

#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("7. MHL 3.0 Fifo Overflow", ulVStoVSDelayDeltaOverflow);
#endif
    }
    else if(ScalerGetBit(P79_0C_MHL_FIFO_FLAG, _BIT0) == _BIT0) // Fifo Underflow
    {
        // Get Hactive (in Pixel Clk)
        pData[0] = ScalerGetByte(P79_50_MN_DPF_HWD_M);
        pData[1] = ScalerGetByte(P79_51_MN_DPF_HWD_L);

        if(PDATA_WORD(0) != 1366)
        {
            return;
        }

        PDATA_WORD(0) = PDATA_WORD(0) - 2;

        // Set Hactive (in Pixel Clk)
        ScalerSetByte(PB5_45_MN_DPF_HWD_M, pData[0]);
        ScalerSetByte(PB5_46_MN_DPF_HWD_L, pData[1]);

        // ((Link Clk * 2) / Pixel CLK) --> 2 pixels
        ulVStoVSDelayDeltaUnderflow = ((DWORD)GET_D5_INPUT_PIXEL_CLK() * GET_MHL3_RX5_AV_LINK_N_CODE() * 100 * 2) / ulPixelClkValue;

#if(_MHL3_ECBUS_AVLINK_DEBUG_MESSAGE == _ON)
        DebugMessageMHL("7. MHL 3.0 Fifo Underflow", ulVStoVSDelayDeltaUnderflow);
#endif
    }

    // Get VStoVSDelay Even
    pData[0] = 0x00;
    ScalerRead(P79_43_EVBLK2VS_H, 3, &pData[1], _AUTOINC);
    ulMhl3EvenVstoVsDelay = PDATA_DWORD(0);

    // Get VStoVSDelay Odd
    pData[4] = 0x00;
    ScalerRead(P79_46_OVBLK2VS_H, 3, &pData[5], _AUTOINC);
    ulMhl3OddVstoVsDelay = PDATA_DWORD(1);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    ulMhl3EvenVstoVsDelay = ulMhl3EvenVstoVsDelay - ((ulVStoVSDelayDeltaOverflow + ulVStoVSDelayDeltaUnderflow) / 2);

    // BStoVSDelay = BStoVSDelay + (Nvid * 256 / Mvid) * ((DWORD)Htotal) / 256;
    ulMhl3OddVstoVsDelay = ulMhl3OddVstoVsDelay - ((ulVStoVSDelayDeltaOverflow + ulVStoVSDelayDeltaUnderflow) / 2);

    // Set Even Field VS to VS Delay
    ScalerSetByte(P79_43_EVBLK2VS_H, LOBYTE(ulMhl3EvenVstoVsDelay >> 16));
    ScalerSetByte(P79_44_EVBLK2VS_M, LOBYTE(ulMhl3EvenVstoVsDelay >> 8));
    ScalerSetByte(P79_45_EVBLK2VS_L, LOBYTE(ulMhl3EvenVstoVsDelay));

    // Set Odd Field VS to VS Delay
    ScalerSetByte(P79_46_OVBLK2VS_H, LOBYTE(ulMhl3OddVstoVsDelay >> 16));
    ScalerSetByte(P79_47_OVBLK2VS_M, LOBYTE(ulMhl3OddVstoVsDelay >> 8));
    ScalerSetByte(P79_48_OVBLK2VS_L, LOBYTE(ulMhl3OddVstoVsDelay));

    // Enable Double Buffer
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT6, _BIT6);

    // Reset Display Format Gen
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT7, 0x00);
    ScalerSetBit(P79_41_DPF_CTRL_0, ~_BIT7, _BIT7);

    ScalerTimerDelayXms(30);
}


//--------------------------------------------------
// Description  : Check MHL3 ECBUS Linking -> Fake PSM
// Input Value  : None
// Output Value : TRUE / FALSE
//--------------------------------------------------

bit ScalerMHL3Rx5FakePowerSavingCheck(void)
{
    if(((GET_MHL3_RX5_ECBUS_MODE() == _ON) || (GET_MHL3_RX5_BIST_TESTING() == _ON)) &&
       (GET_MHL3_RX5_ECBUS_PROCESS_STATE() >= _MHL3_ECBUS_STATE_TDM_SYNC_DONE))
    {
        DebugMessageMHL("SysPower MHL3 Fake Saving", 0x01);
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : Handle MHL Related Timer Event
// Input Value  : ucEventID
// Output Value : None
//--------------------------------------------------

void ScalerMHL3Rx5TimerEventProc(EnumScalerTimerEventID enumEventID)
{
    BYTE ucTmp = 0;
    WORD usVtotal1 = 0;
    WORD usVtotal2 = 0;

    switch(enumEventID)
    {
        case _SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_MHL_VERSION:

            // Check eCBUS Non Receive RAP_UP / BITS_START
            if((GET_MHL3_RX5_SOURCE_XDEVCAP_SUPP() == _FALSE) && (GET_MHL3_RX5_STATUS_VERSION_3_0() == _FALSE))
            {
                SET_MHL3_RX5_WAIT_SRC_MHL_VERSION_TMOUT();
            }

            break;

        case _SCALER_TIMER_EVENT_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP:

            // Check eCBUS Non Receive RAP_UP / BITS_START
            if((GET_MHL3_RX5_ECBUS_MODE() == _OFF) && (GET_MHL3_RX5_BIST_TESTING() == _OFF))
            {
                SET_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP_TMOUT();
            }

            break;

        case _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_START_UP:

            // Check eCBUS Non TDM Sync While StartUp TMOUT
            if(((GET_MHL3_RX5_ECBUS_MODE() == _ON) && (GET_MHL3_RX5_ECBUS_PROCESS_STATE() < _MHL3_ECBUS_STATE_TDM_SYNC_DONE)) ||
               ((GET_MHL3_RX5_BIST_TESTING() == _ON) && (GET_MHL3_RX5_ECBUS_PROCESS_STATE() < _MHL3_ECBUS_STATE_START_UP_DONE)))
            {
                SET_MHL3_RX5_ECBUS_START_UP_TMOUT();
            }

            break;

        case _SCALER_TIMER_EVENT_MHL3_RX5_ECBUS_BIST_DURATION:

            if(GET_MHL3_RX5_ECBUS_PROCESS_STATE() == _MHL3_ECBUS_STATE_BIST_TESTING)
            {
                ScalerMHL3Rx5BISTTestingDoneProc();

                SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_ECBUS_DONE);
            }

            break;

        case _SCALER_TIMER_EVENT_MHL3_RX5_WAIT_FWD_CLK:

            // Check eCBUS StartUp FWD Clk Non Received
            if(GET_MHL3_RX5_ECBUS_CLK_STABLE() == _FALSE)
            {
                ScalerMHLRx5CBUSResetProc();

#if(_MHL3_ECBUS_STARTUP_DEBUG_MESSAGE == _ON)
                DebugMessageMHL("eCBUS STUCKLOW_DISABLE - CLK TMOUT", 0x00);
#endif
            }

            break;

        case _SCALER_TIMER_EVENT_MHL3_RX5_AV_LINK_BIST_SET_PHY:

            if((GET_MHL3_RX5_AV_LINK_RATE() != _ECBUS_LINK_RATE_NULL) && (GET_MHL3_RX5_AV_LINK_N_CODE() != _ECBUS_N_CODE_NULL))
            {
                // Enable RR Align Auto Mode
                ScalerSetBit(P79_07_MHL_DATA_ALIGN_CTRL, ~_BIT3, _BIT3);

                // Enable MHL 3.0 Video Mac
                ScalerSetBit(P79_00_MHL_EN, ~_BIT7, _BIT7);

                ScalerTMDSRx5MHL3AcdrSetPhy();

                SET_TMDS_RX5_PHY_SET();

                // Enable MHL 3.0 Measure
                ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, _BIT7);

                ScalerTimerPollingFlagProc(130, P79_20_MHL_MEASURE_0, _BIT7, _FALSE);

                // Get Vtotal 1
                ScalerRead(P79_34_MHL_MEASURE_20, 2, &pData[0], _AUTOINC);
                usVtotal1 = PDATA_WORD(0);

                // Get Vtotal 2
                ScalerRead(P79_36_MHL_MEASURE_22, 2, &pData[2], _AUTOINC);
                usVtotal2 = PDATA_WORD(1);

                ucTmp = 0;

                while((usVtotal1 < 0x10) || (usVtotal2 < 0x10))
                {
                    if(ucTmp >= 100)
                    {
                        ScalerMHL3Rx5BISTTestingDoneProc();

                        SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_ECBUS_DONE);

#if(_MHL3_BIST_FUNCTION_DEBUG_MESSAGE == _ON)
                        // Set AV Link Video Mode
                        DebugMessageMHL("BIST Set PHY Fail", usVtotal1);
#endif
                        break;
                    }
                    else
                    {
                        ScalerTMDSRx5MHL3AcdrSetPhy();

                        // Enable MHL 3.0 Measure
                        ScalerSetBit(P79_20_MHL_MEASURE_0, ~_BIT7, _BIT7);

                        ScalerTimerPollingFlagProc(130, P79_20_MHL_MEASURE_0, _BIT7, _FALSE);

                        // Get Vtotal 1
                        ScalerRead(P79_34_MHL_MEASURE_20, 2, &pData[0], _AUTOINC);
                        usVtotal1 = PDATA_WORD(0);

                        // Get Vtotal 2
                        ScalerRead(P79_36_MHL_MEASURE_22, 2, &pData[2], _AUTOINC);
                        usVtotal2 = PDATA_WORD(1);

                        ucTmp++;
                    }
                }

                // Enable MHL 3.0 S2P Fifo
                // Enable Audio Accumulation
                ScalerSetBit(P79_01_MHL_FIFO_CTRL, ~(_BIT7 | _BIT3), (_BIT7 | _BIT3));

                // Clear MHL Mode Error Flag
                ScalerSetBit(P79_38_MHL_MEASURE_24, ~_BIT6, _BIT6);

                // Enable Av Link Rx Bist Error Detection
                // (Counter Will Start Counting when First PRBS Detected)
                ScalerSetBit(P79_02_MHL_BIST_CTRL, ~_BIT7, _BIT7);
            }

            break;

        default:
            break;
    }
}

#if(_MHL3_TEST_FUNCTION_DEBUG_MODE == _ON)
//--------------------------------------------------
// Description  : MHL3 RL6369 Test Function Pin Setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5TestPinSetting(BYTE ucMode)
{
//----------------------------------------------------------------------//
//-------------------- Page 00 8D/8E Test Out Enable -------------------//
//----------------------------------------------------------------------//
    ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x00);
    ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x0F);
    ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x01);
    ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x82);

//---------------------------------------------------------------------//
//------------------------- Page 6F Switch ----------------------------//
//---------------------------------------------------------------------//

    switch(ucMode)
    {
        case _ECBUS_APHY:

            //---------------------------------------------------------------------//
            //------------------------- Page 6F Switch ----------------------------//
            //---------------------------------------------------------------------//
            ScalerSetByte(P6F_03_MUX_TST_OUT, 0x0A);
            ScalerSetByte(P79_5E_MHL_TEST_OUT_SEL, 0x03);

            //--------------------------------------------------------------//
            //------------------- eCBUS A-PHY Sub Setting ------------------//
            //--------------------------------------------------------------//
            ScalerSetBit(P6A_A8_CBUS_CTRL_08, ~_BIT3, _BIT3);

            //-------------------- Test Out 0 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);

            //-------------------- Test Out 1 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x21);

            //-------------------- Test Out 2 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x22);

            // APHY Rx FWD Duty TestPin
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x5B);

            //-------------------- Test Out 3 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x23);

            // APHY Rx FWD Clk TestPin
            // ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x59);

            // APHY Tx BWD Data TestPin
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x5C);

            break;

        case _ECBUS_DPHY:

            //---------------------------------------------------------------------//
            //------------------------- Page 6F Switch ----------------------------//
            //---------------------------------------------------------------------//
            ScalerSetByte(P6F_03_MUX_TST_OUT, 0x0A);
            ScalerSetByte(P79_5E_MHL_TEST_OUT_SEL, 0x05);

            //--------------------------------------------------------------//
            //------------------- eCBUS D-PHY Sub Setting ------------------//
            //--------------------------------------------------------------//
            ScalerSetBit(P6C_C5_ECBUS_DPHY_DEBUG, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);


            //-------------------- Test Out 0 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);

            // DPHY Clk
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x40);

            //-------------------- Test Out 1 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x21);

            // DPHY Tx Data
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x51);

            //-------------------- Test Out 2 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x22);

            // DPHY Clk
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x40);


            //-------------------- Test Out 3 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x23);

            // DPHY Rx Data
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x52);

            break;

        case _ECBUS_MAC:


            //---------------------------------------------------------------------//
            //------------------------- Page 6F Switch ----------------------------//
            //---------------------------------------------------------------------//
            ScalerSetByte(P6F_03_MUX_TST_OUT, 0x0A);
            ScalerSetByte(P79_5E_MHL_TEST_OUT_SEL, 0x06);

            //--------------------------------------------------------------//
            //------------------- eCBUS Mac Sub Setting --------------------//
            //--------------------------------------------------------------//
            ScalerSetBit(P6C_52_ECBUS_TEST_FORCE_OUT, ~_BIT7, _BIT7);


            //-------------------- Test Out 0 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);


            //-------------------- Test Out 1 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x21);


            //-------------------- Test Out 2 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x22);


            //-------------------- Test Out 3 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x23);

            break;

        case _MHL3_MAC:


            //---------------------------------------------------------------------//
            //------------------------- Page 6F Switch ----------------------------//
            //---------------------------------------------------------------------//
            ScalerSetByte(P6F_03_MUX_TST_OUT, 0x0A);
            ScalerSetByte(P79_5E_MHL_TEST_OUT_SEL, 0x07);

            //--------------------------------------------------------------//
            //-------------------- MHL3 Mac Sub Setting --------------------//
            //--------------------------------------------------------------//
            ScalerSetBit(P79_00_MHL_EN, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P79_01_MHL_FIFO_CTRL, ~(_BIT1 | _BIT0), 0x00);

            //--------------------------------------------------------------//
            //-------------------- MHL3 Mac DPF Setting --------------------//
            //--------------------------------------------------------------//
            ScalerSetBit(P79_5D_TEST0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), _BIT5);


            //-------------------- Test Out 0 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);

            //-------------------- Test Out 1 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x21);

            //-------------------- Test Out 2 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x22);

            // Video Mac VS
            // ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x4B);

            // SOP
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0xDC);

            //-------------------- Test Out 3 Bit Select -------------------//
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x23);

            // Video Mac HS
            // ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x4D);

            // EOP
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0xDB);

            break;

        default:
            break;
    }
}
#endif // End of #if(_MHL3_TEST_FUNCTION_DEBUG_MODE == _ON)


#if(_ECBUS_TX_TEST_FUNCTION == _ON)
//--------------------------------------------------
// Description  : MHL3 RL6410 eCBUS Tx Mode Testing Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSTxTestSettingFunction(void)
{
    SET_D5_TMDS_MODE(_TMDS_MHL_MODE);

    ScalerMHLRx5ModeMHLSetting();

    ScalerMHLRx5CBUSPhySwitch(_ON);

    ScalerTMDSRx5MHL3SetCmu(_EXT_XTAL_CLK);

    //////////////////////////////////////////////
    /////// Analog PHY Configure and Enable //////
    //////////////////////////////////////////////

    // APHY Set to Work State
    ScalerSetBit(P5E_01_ECBUS_STEP_CTRL, ~(_BIT1 | _BIT0), 0x00);

    // Disable FWD Clk De-Glitch
    ScalerSetBit(P5E_08_ECBUS_DATA_CTRL, ~_BIT1, 0x00);

    // Vref of Comparator
    ScalerSetBit(P5E_04_EBUS_VREF_CTRL_0, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Enable eCBUS-S APHY
    ScalerSetBit(P5E_00_ECBUS_EN, ~_BIT7, _BIT7);


    ////////////////////////////////////
    /////// Digital PHY Configure //////
    ////////////////////////////////////

    // Set Bubble Remove Stage ---> Stage 2
    ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~(_BIT4 | _BIT3), _BIT4);

    // Enable Stage Circuit Safe debounce Mode ---> Debounce 4 COMMA2 Symbol for Stat_Ok
    ScalerSetBit(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT4, _BIT4);

    // Set Stage Circuit Timeout ---> 40ms
    ScalerSetByte(P6C_A4_ECBUS_DPHY_STAT_CONFIG_1, 0xC8);

    // Set Stage Circuit Difference Threshold ---> 4 (of x40 Samples)
    ScalerSetByte(P6C_A5_ECBUS_DPHY_STAT_CONFIG_2, 0x04);

    // Set Nth Calibration Done
    ScalerSetBit(P6C_A9_ECBUS_DPHY_CALIB_CTRL, ~_BIT3, _BIT3);

    // Set ini Circuit Timeout ---> 240 Tbit
    ScalerSetByte(P6C_AA_ECBUS_DPHY_INI_CONFIG_1, 0x08);

    // Set ini Circuit Wait Time ---> 4 Tbit
    ScalerSetByte(P6C_AB_ECBUS_DPHY_INI_CONFIG_2, 0x04);

    // Set Nth initial Value ---> 20.5 (of x40 Samples)
    ScalerSetByte(P6C_AC_ECBUS_DPHY_INI_CONFIG_3, 0x14);

    // Set ini Circuit Count ---> 120 Tbis
    ScalerSetBit(P6C_AD_ECBUS_DPHY_INI_CONFIG_4, ~(_BIT3 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

    // Set Nth_0/Nth_1 Equal Tolerance ---> 0 (Tbit Count)
    ScalerSetBit(P6C_AD_ECBUS_DPHY_INI_CONFIG_4, ~_BIT0, 0x00);
    ScalerSetByte(P6C_AE_ECBUS_DPHY_INI_CONFIG_5, 0x00);

    // Set D-PHY Tx Data Delay ---> 3 Tbit (As Co-Sim Result)
    ScalerSetBit(P6C_B3_ECBUS_DPHY_TX_PHASE_CONFIG_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x03);

    // Set D-PHY Tx Phase Initial Value for No Calibration ---> (FW Setting Depends on Experiment)
    ScalerSetByte(P6C_B4_ECBUS_DPHY_TX_PHASE_CONFIG_2, 0x04);

    // Set D-PHY Tx Phase Upper Bound of Calibration ---> (FW Setting Depends on Experiment)
    ScalerSetByte(P6C_B5_ECBUS_DPHY_TX_PHASE_CONFIG_3, 0x0E);

    // Set D-PHY Tx Phase Lower Bound of Calibration ---> (FW Setting Depends on Experiment)
    ScalerSetByte(P6C_B6_ECBUS_DPHY_TX_PHASE_CONFIG_4, 0x02);

    // Set Nth Adaption Mode ---> One_Avg & Zero_Avg
    ScalerSetByte(P6C_B8_ECBUS_DPHY_ADAPT_CTRL, 0x00);

    // Set Adapt_timer
    ScalerSetByte(P6C_B9_ECBUS_DPHY_ADAPT_CONFIG_1, 0x30);

    // Set D-PHY Rx Comma2 Timeout ---> 50ms
    ScalerSetByte(P6C_C0_ECBUS_DPHY_CONFIG, 0xFA);


    ////////////////////////////////////
    /////// ECBUS-S MAC Setting ////////
    ////////////////////////////////////

    //-------- Default Value Modify --------//

    // CBUS1/eMSC In-Out Swap Set to LSB First
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Enable COM1-IDLE Check when Sync Loss
    ScalerSetBit(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT4 | _BIT3 | _BIT1), _BIT4);

    // CRC Result Sending Swap Set to LSB First
    ScalerSetBit(P6C_3E_ECBUS_GLOBAL_CTRL, ~_BIT4, 0x00);


    //-------- COMMA Start Up Configuration --------//

    // FW Set BWD Data Type to Sent BWD "0" (0x00 IDLE).
    ScalerSetBit(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

    // Set FWD COMMA2 Detection Debounce Level
    ScalerSetBit(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT3 | _BIT2), _BIT2);

    // Set FWD COMMA2_LOST Detection Threshold Level
    ScalerSetBit(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT1 | _BIT0), 0x01);


    //-------- TDM Slot Sync Configuration --------//

    // Set FWD COM1 Detection Debounce Level
    ScalerSetBit(P6C_05_ECBUS_TDM_SYNC_CONFIG_1, ~(_BIT7 | _BIT6), _BIT6);

    // Set FWD COM1_Miss Detection Threshold Level for HW Use Only
    ScalerSetBit(P6C_05_ECBUS_TDM_SYNC_CONFIG_1, ~(_BIT5 | _BIT4), _BIT4);

    // Set FWD IDLE Error Detection Threshold Level
    ScalerSetBit(P6C_05_ECBUS_TDM_SYNC_CONFIG_1, ~(_BIT3 | _BIT2), _BIT2);

    // Set FWD COM2 Detection Debounce Level
    ScalerSetBit(P6C_05_ECBUS_TDM_SYNC_CONFIG_1, ~(_BIT1 | _BIT0), 0x01);

    // Set TDM Sync Loss Threshold Level ---> 2 Non-COM2
    ScalerSetByte(P6C_06_ECBUS_TDM_SYNC_CONFIG_2, _BIT1);

    // Set TDM Slot Tx Offset ---> 10 Slots + 0 Cycles
    ScalerSetBit(P6C_09_ECBUS_TDM_SYNC_TX_OFFSET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4));

    // Set TDM Slot Rx Offset Start Point ---> 6 Slots + 0 Cycles
    ScalerSetBit(P6C_0A_ECBUS_TDM_SYNC_RX_OFFSET, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

    // Set TDM Slot Rx Offset Check Range ---> 8 Slots
    ScalerSetBit(P6C_0B_ECBUS_TDM_SYNC_RESERVE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));


    //-------- eMSC Link Training Configuration --------//

    // Set Rx Received Sync Symbols Detection Debounce Level ---> 4 Symbols
    ScalerSetBit(P6C_0D_ECBUS_EMSC_SYNC_CONFIG_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // Set Rx Received Sync Symbols Error Detection Threshold Level ---> 1 Symbols (No Debounde)
    ScalerSetBit(P6C_0D_ECBUS_EMSC_SYNC_CONFIG_1, ~(_BIT4 | _BIT3), 0x00);

    // Set Rx Received Sync Symbols Loss Debounce Level ---> 4 Symbols
    ScalerSetBit(P6C_0D_ECBUS_EMSC_SYNC_CONFIG_1, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

    // Set Rx Received Sync Symbols Threshold Level ---> 260 Sync
    ScalerSetBit(P6C_0E_ECBUS_EMSC_SYNC_CONFIG_2, ~(_BIT3 | _BIT2), 0x00);

    // Set Tx Transmitted Sync Symbols Threshold Level ---> 260 Sync
    ScalerSetBit(P6C_0E_ECBUS_EMSC_SYNC_CONFIG_2, ~(_BIT1 | _BIT0), 0x00);


    //-------- eMSC Block Transaction Configuration --------//

    // Set Rx Ignore Bytes When Rx Wait ---> 260 Bytes
    ScalerSetBit(P6C_23_ECBUS_EMSC_TRANS_CONFIG_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // Set Timeout of Waiting ACK ---> 2.0ms
    ScalerSetBit(P6C_24_ECBUS_EMSC_TRANS_CONFIG_2, ~(_BIT7 | _BIT6), 0x00);

    // Set Number of Tx Retry ---> 4 Times
    ScalerSetBit(P6C_24_ECBUS_EMSC_TRANS_CONFIG_2, ~(_BIT5 | _BIT4), _BIT5);

    // Set Tx Retry Wait Time ---> 2.0ms
    ScalerSetBit(P6C_24_ECBUS_EMSC_TRANS_CONFIG_2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);


    //-------- eCBUS BIST Configuration --------//

    // Set eCBUS Rx BIST Receiving Debounce Level ---> 1 Symbols (No Debounde)
    ScalerSetBit(P6C_24_ECBUS_EMSC_TRANS_CONFIG_2, ~(_BIT5 | _BIT4), 0x00);


    ////////////////////////////////////
    //////// Digital PHY Setting ///////
    ////////////////////////////////////

    // Hold ecbus_dphy_rstn Low
    ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT7, 0x00);

    // Enable eCBUS-S Mac Circuit
    ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT6, _BIT6);


    ////////////////////////////////////
    /////// ECBUS-S MAC Setting ////////
    ////////////////////////////////////

    // Enable CBUS 3.0 Mac Circuit
    ScalerSetBit(P6A_00_OCBUS_CTRL_00, ~_BIT6, _BIT6);

    // Disable Stuck Low IRQ and Clear Stuck Low Flags
    ScalerSetBit(P6A_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT1);

    // Clear eCBUS Global IRQ Flag
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~(_BIT2), 0x00);

    // Hold ecbus_reset High
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);

    // Enable eCBUS-S Mac Circuit
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT3, _BIT3);


    ////////////////////////////////////
    /////// ECBUS-S Clk INT_EN /////////
    ////////////////////////////////////

    //----------- D-PHY ------------//

    // Release ecbus_dphy_rstn
    ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT7, _BIT7);

    // Enable FWD Edge Calibration
    ScalerSetBit(P6C_A1_ECBUS_DPHY_EDGE_CTRL, ~_BIT0, _BIT0);

    // Enable eCBUS D-PHY Stat_en to start detecting FWD_Clk -> FWD_COMMA2 on eCBUS
    ScalerSetBit(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT7, _BIT7);


    //------------- MAC ------------//

    // Release ecbus_reset
    ScalerSetBit(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, 0x00);

    // Set ECBUS DPHY DUTY Mode
    ScalerSetBit(0x6CB3, ~_BIT4, _BIT4);


    //-----------------------------------------------//
    //------------------ Testing --------------------//
    //-----------------------------------------------//
    // BWD All 0
    ScalerSetBit(0x6C01, ~(_BIT5 | _BIT4), 0x00);

    while(_TRUE)
    {
        if(ScalerGetByte(0x0006) == 0x00) // DPHY Rx/Tx Testout
        {
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x00);
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x80);
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x01);
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x02);

            // DPHY Tx Data TestPin = GJ 99
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x51);

            // DPHY Rx Data TestPin = GJ 100
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x21);
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x52);

            ScalerSetByte(P6F_03_MUX_TST_OUT, 0x0A);
            ScalerSetByte(P79_5E_MHL_TEST_OUT_SEL, 0x05);
        }
        else if(ScalerGetByte(0x0006) == 0x01) // APHY Testout
        {
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x00);
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x80);
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x01);
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x02);

            // APHY Rx FWD Duty TestPin = GJ 99
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x5B);

            // APHY Rx FWD Clk TestPin = GJ 100
            ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x21);
            ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x59);

            ScalerSetByte(P6F_03_MUX_TST_OUT, 0x0A);
            ScalerSetByte(P79_5E_MHL_TEST_OUT_SEL, 0x03);
            ScalerSetBit(P6A_A8_CBUS_CTRL_08, ~_BIT3, _BIT3);
        }

        ScalerDebug();
    }
}
#endif // End of #if(_ECBUS_TX_TEST_FUNCTION == _ON)

#if(_ECBUS_RX_TEST_FUNCTION == _ON)
//--------------------------------------------------
// Description  : MHL3 RL6410 eCBUS Rx Mode Testing Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMHL3Rx5ECBUSRxTestSettingFunction(void)
{
    // Rx Ready Triggle
    if(ScalerGetBit(0x6CA0, _BIT0) == _BIT0)
    {
        ScalerMHL3Rx5ECBUSConfigureSettings();

        ScalerMHL3Rx5EnableECBUSMode(_ENABLE);

        while(_TRUE)
        {
            if(ScalerGetBit(0x6CA0, _BIT1) == _BIT1) // DPHY Rx/Tx Testout
            {
                ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x00);
                ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x80);
                ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x01);
                ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x02);

                // DPHY Tx Data TestPin = GJ 99
                ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);
                ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x51);

                // DPHY Rx Data TestPin = GJ 100
                ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x21);
                ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x52);

                ScalerSetByte(P6F_03_MUX_TST_OUT, 0x0A);

                // Clear Control Flag
                ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT1, 0x00);
            }
            else if(ScalerGetBit(0x6CA0, _BIT2) == _BIT2) // APHY Testout
            {
                ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x00);
                ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x80);
                ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x01);
                ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x02);

                // APHY Rx FWD Duty TestPin = GJ 99
                ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x20);
                ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x59);

                // APHY Rx FWD Clk TestPin = GJ 100
                ScalerSetByte(P0_8D_TEST_MODE_PORT_ADDR, 0x21);
                ScalerSetByte(P0_8E_TEST_MODE_PORT_DATA, 0x5B);

                ScalerSetByte(P6F_03_MUX_TST_OUT, 0x0A);

                ScalerSetBit(P6A_A8_CBUS_CTRL_08, ~_BIT3, _BIT3);

                // Clear Control Flag
                ScalerSetBit(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT2, 0x00);
            }

            ScalerDebug();
        }
    }
}
#endif // End of #if(_ECBUS_RX_TEST_FUNCTION == _ON)

//--------------------------------------------------
// Description  :
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerMHL3Rx5WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime) using 3
{
    switch(enumEventID)
    {
        // BWD COMMA1 WatchDogTimerEvent TMOUT --> Sent COMMA1
        case _SCALER_WD_TIMER_EVENT_RX5_ECBUS_SEND_BWD_COMMA1:

            // FW Set BWD Data Type to Sent BWD COMMA1
            ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), _BIT4);

            // Set Stage Circuit Difference Threshold ---> 8 (of x40 Samples)
            ScalerSetByte_EXINT(P6C_A5_ECBUS_DPHY_STAT_CONFIG_2, 0x08);

            ScalerSetBit_EXINT(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT3, _BIT3);

            // Clear State_ok Flag and Enable eCBUS-S DPHY State Interrupt
            ScalerSetBit_EXINT(P6C_C4_ECBUS_DPHY_IRQ, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(P6C_C4_ECBUS_DPHY_IRQ, ~(_BIT4 | _BIT1), _BIT1);

            // Toggle eCBUS D-PHY Stat_en to Re-start detecting FWD_Clk -> FWD_COMMA2 on eCBUS
            ScalerSetBit_EXINT(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT7, _BIT7);

            // Reset eCBUS If Haven't Receive COMMA2 Within 40ms
            *pucActiveWDID = _SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COMMA2_TMOUT;
            *pucActiveWDTime = 100;

            // Reset Recorded "_WAIT_COMMA2_END_TIME"
            ScalerSetByte_EXINT(P6C_5D_ECBUS_RESERVE_0, 0x00);

            // Record Time Point of "_WAIT_COMMA2_START_TIME"
            ScalerTimerResetRecordTimer_WDINT();

            // Record eCBUS_INT Flow State-3 (BWD Start Comma1 WD)
            ScalerSetBit_EXINT(P6C_5F_ECBUS_RESERVE_2, ~_BIT2, _BIT2);

            break;

        case _SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COMMA2_TMOUT:

            // Check Comma2 Receive Flag 0 (James)
            if(ScalerGetBit_EXINT(P6C_02_ECBUS_STARTUP_DET, _BIT3) == _BIT3)
            {
                // Enable eCBUS-S Function Reset
                ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);

                // FW Set BWD Data Type to Sent BWD "0" (0x00 IDLE).
                ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

                // Set WD TimerEvent to Disable eCBUS-S Function Reset 200ms Later, Hold BWD 0x00(IDLE) 200ms
                *pucActiveWDID = _SCALER_WD_TIMER_EVENT_RX5_ECBUS_RESET_HOLD_IDLE;
                *pucActiveWDTime = 200;

                // eCBUS Link Build Error #1
                ScalerSetByte_EXINT(P6C_5F_ECBUS_RESERVE_2, 0xE1);
            }

            break;

        // BWD Keep COMMA1 WatchDogTimerEvent TMOUT --> Sent BWD COMMA2
        case _SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA1:

            // FW Set BWD Data Type to Sent BWD COMMA2 (HW Enter Start Up Done Standby State)
            ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), _BIT5);

            // Enable eCBUS-S FWD TDM COM1 Detection Circuit
            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT4, _BIT4);

            // Enable eCBUS-S FWD TDM COM1 IRQ and Clear eCBUS-S FWD TDM COM1 IRQ Flag
            ScalerSetBit_EXINT(P6C_07_ECBUS_TDM_SYNC_DET_1, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), _BIT3);
            ScalerSetBit_EXINT(P6C_07_ECBUS_TDM_SYNC_DET_1, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT2);

            // Reset Recorded "_WAIT_ACTIVE_START_TIME"
            ScalerSetByte_EXINT(P6C_5E_ECBUS_RESERVE_1, 0x00);

            // Record Timer Point of "_WAIT_ACTIVE_START_TIME"
            ScalerTimerResetRecordTimer_WDINT();

            // Record eCBUS_INT Flow State-6 (BWD Keep Comma1 15ms WD)
            ScalerSetBit_EXINT(P6C_5F_ECBUS_RESERVE_2, ~_BIT5, _BIT5);

            break;

        // Check BWD Keep COMMA2 WatchDogTimerEvent TMOUT and Sent BWD ACTIVE
        /*** If COM1 INT Already Happen (HW Already Enter Active)--> This Block Functionless ***/
        case _SCALER_WD_TIMER_EVENT_RX5_ECBUS_BWD_KEEP_COMMA2:

            // If No-FWD COM1 Received ---> HW Enter Active with IDLE(0x00)
            if(ScalerGetBit_EXINT(P6C_07_ECBUS_TDM_SYNC_DET_1, _BIT3) == 0x00)
            {
                // FW Set BWD Data Type to Sent BWD 0 (IDLE)
                ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

                // If(Haven't Receive COM1) --> Set WD TimerEvent to Wait FWD COM1 Sync
                *pucActiveWDID = _SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COM1;
                *pucActiveWDTime = 15;
            }

            break;

        // Check Wait FWD COM1 WatchDogTimerEvent TMOUT
        /*** If COM1 INT Already Happen (HW Already Enter Active)--> This Block Functionless ***/
        case _SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_FWD_COM1:

            // If No-FWD COM1 Received --> Sink Initiative Sent BWD COM1 to Sync TDM
            if(ScalerGetBit_EXINT(P6C_07_ECBUS_TDM_SYNC_DET_1, _BIT3) == 0x00)
            {
                // Disable eCBUS-S FWD TDM_SYNC_LOST IRQ
                ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT1 | _BIT0), 0x00);

                // Enable eCBUS-S FWD TDM_SYNC_DONE IRQ and Clear eCBUS-S FWD TDM_SYNC_DONE IRQ Flag
                ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT1), _BIT3);
                ScalerSetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, ~(_BIT3 | _BIT2 | _BIT1), _BIT2);

                // FW Set Enter TDM Active (HW Enter TDM_SYNC_INITIAL State)
                ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT5, _BIT5);

                // FW Set TDM_COM1_SEND to Sent BWD COM1 Initiativly
                ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT2, _BIT2);

                // Reset eCBUS If Haven't TDM Sync Within 40ms
                *pucActiveWDID = _SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_TDM_SYNC_TMOUT;
                *pucActiveWDTime = 40;
            }

            break;

        case _SCALER_WD_TIMER_EVENT_RX5_ECBUS_WAIT_TDM_SYNC_TMOUT:

            // Check TDM Sync Done Flag 0 (James)
            if(ScalerGetBit_EXINT(P6C_08_ECBUS_TDM_SYNC_DET_2, _BIT3) == _BIT3)
            {
                // Enable eCBUS-S Function Reset
                ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, _BIT1);

                // FW Set BWD Data Type to Sent BWD "0" (0x00 IDLE).
                ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

                // Set WD TimerEvent to Disable eCBUS-S Function Reset 200ms Later, Hold BWD 0x00(IDLE) 200ms
                *pucActiveWDID = _SCALER_WD_TIMER_EVENT_RX5_ECBUS_RESET_HOLD_IDLE;
                *pucActiveWDTime = 200;

                // eCBUS Link Build Error #4
                ScalerSetByte_EXINT(P6C_5F_ECBUS_RESERVE_2, 0xE4);
            }

            break;

        case _SCALER_WD_TIMER_EVENT_RX5_ECBUS_CLK_UNSTABLE_TMOUT:

            if((GET_MHL3_RX5_BIST_TESTING() == _ON) && (GET_MHL3_RX5_BIST_ECBUS_DURATION() == 0x3C))
            {
                if((((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_IMPEDENCE) == _MHL3_ECBUS_BIST_MODE_IMPEDENCE) &&
                    ((GET_MHL3_RX5_BIST_IMPEDENCE_MODE() == _ECBUS_S_TX_HIGH) || (GET_MHL3_RX5_BIST_IMPEDENCE_MODE() == _ECBUS_S_TX_LOW))) ||
                   ((GET_MHL3_RX5_BIST_TESTING_MODE() & _MHL3_ECBUS_BIST_MODE_AVLINK_RX) == _MHL3_ECBUS_BIST_MODE_AVLINK_RX))
                {
                    break;
                }
            }

            if(((GET_MHL3_RX5_ECBUS_CLK_STABLE() == _FALSE) && (GET_MHL3_RX5_ECBUS_PROCESS_STATE() >= _MHL3_ECBUS_STATE_TDM_SYNC_DONE)) ||
               ((GET_MHL3_RX5_ECBUS_CLK_STABLE() == _FALSE) && (GET_MHL3_RX5_ECBUS_START_UP_TMOUT() == _TRUE)))
            {
                if(GET_MHL3_RX5_ECBUS_MODE() == _ON)
                {
                    // Enable Stuck Low IRQ
                    ScalerSetBit_EXINT(P6A_A4_CBUS_CTRL_04, ~(_BIT1 | _BIT0), _BIT0);

                    // Record eCBUS Clk Un-Stable Reset
                    ScalerSetBit_EXINT(P6C_50_ECBUS_HW_FSM_5, ~_BIT6, _BIT6);
                }
            }
            else
            {
                // State Reset to Re-Start eCBUS Link Training
                ScalerSetBit_EXINT(P6C_5F_ECBUS_RESERVE_2, ~_BIT0, 0x00);
            }

            break;

        // Check eCBUS Reset Hold Idle WatchDogTimerEvent TMOUT
        case _SCALER_WD_TIMER_EVENT_RX5_ECBUS_RESET_HOLD_IDLE:

            //----------- D-PHY ------------//

            // Disable FWD Edge Calibration
            ScalerSetBit_EXINT(P6C_A1_ECBUS_DPHY_EDGE_CTRL, ~_BIT0, 0x00);

            // Disable eCBUS D-PHY Stat_en to start detecting FWD_Clk -> FWD_COMMA2 on eCBUS
            ScalerSetBit_EXINT(P6C_A3_ECBUS_DPHY_STAT_CTRL, ~_BIT7, 0x00);

            // Hold ecbus_dphy_rstn
            ScalerSetBit_EXINT(P6C_A0_ECBUS_DPHY_CTRL, ~_BIT7, 0x00);


            //------------- MAC ------------//

            /*** Reset ECBUS Finctions Before Release StartUp_Reset ***/
            // Disable COMMA2 Detection Circuit
            ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT0, 0x00);

            // FW Set BWD Data Type to Sent BWD "0" (0x00 IDLE).
            ScalerSetBit_EXINT(P6C_01_ECBUS_STARTUP_CONFIG, ~(_BIT5 | _BIT4), 0x00);

            // Deactivate TDM State
            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT5, 0x00);

            // Disable COM1 Detection Circuit
            ScalerSetBit_EXINT(P6C_04_ECBUS_TDM_SYNC_CTRL, ~_BIT4, 0x00);

            // Disable eMSC Sync Symbol Transaction
            ScalerSetBit_EXINT(P6C_0C_ECBUS_EMSC_SYNC_CTRL, ~_BIT2, 0x00);

            // Disable eCBUS-S Function Reset
            ScalerSetBit_EXINT(P6C_00_ECBUS_STARTUP_CTRL, ~_BIT1, 0x00);

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P74_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable eCBUS-S FWD CLK IRQ and Clear eCBUS-S FWD CLK IRQ Flag
            ScalerSetBit_EXINT(P74_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            SET_MHL3_RX5_ECBUS_PROCESS_STATE(_MHL3_ECBUS_STATE_INITIAL);

            // Reset(Clear) eCBUS_INT Flow Recorded State
            ScalerSetBit_EXINT(P6C_60_ECBUS_DPHY_CAP0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
            ScalerSetByte_EXINT(P6C_5F_ECBUS_RESERVE_2, 0x00);

            // Record eCBUS Reset Hold Done
            ScalerSetBit_EXINT(P6C_50_ECBUS_HW_FSM_5, ~_BIT7, _BIT7);

            break;

        default:
            break;
    }
}

#endif // End of #if((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0))
