/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2011>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6410_Series_MHL3Rx4Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) && (_D4_MHL_VERSION >= _MHL_VERSION_3_0))

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of eCBUS-S State Handler
//--------------------------------------------------
#define GET_MHL3_RX4_ECBUS_PROCESS_STATE()                          (g_stMhl3Rx4ECBUSProcess.b3Mhl3ECBUSProcessState)
#define SET_MHL3_RX4_ECBUS_PROCESS_STATE(x)                         (g_stMhl3Rx4ECBUSProcess.b3Mhl3ECBUSProcessState = (x))

//--------------------------------------------------
// Macro of oCBUS --> eCBUS-S Switch
//--------------------------------------------------
#define GET_MHL3_RX4_ECBUS_MODE()                                   (g_stMhl3Rx4ECBUSProcess.b1MHL3ECBUSMode)
#define SET_MHL3_RX4_ECBUS_MODE(x)                                  (g_stMhl3Rx4ECBUSProcess.b1MHL3ECBUSMode = (x))

#define GET_MHL3_RX4_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx4ECBUSProcess.b1MHL3SourceDevCapSupp)
#define SET_MHL3_RX4_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx4ECBUSProcess.b1MHL3SourceDevCapSupp = _TRUE)
#define CLR_MHL3_RX4_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx4ECBUSProcess.b1MHL3SourceDevCapSupp = _FALSE)

#define GET_MHL3_RX4_STATUS_VERSION_3_0()                           (g_stMhl3Rx4ECBUSProcess.b1MHL3StatusVersion30)
#define SET_MHL3_RX4_STATUS_VERSION_3_0()                           (g_stMhl3Rx4ECBUSProcess.b1MHL3StatusVersion30 = _TRUE)
#define CLR_MHL3_RX4_STATUS_VERSION_3_0()                           (g_stMhl3Rx4ECBUSProcess.b1MHL3StatusVersion30 = _FALSE)

#define GET_MHL3_RX4_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx4ECBUSProcess.b1MHL3MscFeatReqUnComplete)
#define SET_MHL3_RX4_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx4ECBUSProcess.b1MHL3MscFeatReqUnComplete = _TRUE)
#define CLR_MHL3_RX4_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx4ECBUSProcess.b1MHL3MscFeatReqUnComplete = _FALSE)

//--------------------------------------------------
// Macro of eCBUS-S Start Up and TDM Sync TMOUT
//--------------------------------------------------
#define GET_MHL3_RX4_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut)
#define SET_MHL3_RX4_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut = _TRUE)
#define CLR_MHL3_RX4_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut = _FALSE)

#define GET_MHL3_RX4_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion)
#define SET_MHL3_RX4_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion = _TRUE)
#define CLR_MHL3_RX4_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion = _FALSE)

#define GET_MHL3_RX4_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp)
#define SET_MHL3_RX4_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp = _TRUE)
#define CLR_MHL3_RX4_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp = _FALSE)

#define GET_MHL3_RX4_ECBUS_CLK_STABLE()                             (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSClkStable)
#define SET_MHL3_RX4_ECBUS_CLK_STABLE()                             (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSClkStable = _TRUE)
#define CLR_MHL3_RX4_ECBUS_CLK_STABLE()                             (g_stMhl3Rx4ECBUSProcess.b1Mhl3ECBUSClkStable = _FALSE)

//--------------------------------------------------
// Macro of eMSC Block Transaction
//--------------------------------------------------
#define GET_MHL3_RX4_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx4ECBUSBlkRcvInfoSent)
#define SET_MHL3_RX4_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx4ECBUSBlkRcvInfoSent = _TRUE)
#define CLR_MHL3_RX4_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx4ECBUSBlkRcvInfoSent = _FALSE)

//--------------------------------------------------
// Macro of MHL 3.0 AV Link
//--------------------------------------------------
#define GET_MHL3_RX4_AV_LINK_N_CODE()                               (g_ucMhl3Rx4AVLinkNCode)
#define SET_MHL3_RX4_AV_LINK_N_CODE(x)                              (g_ucMhl3Rx4AVLinkNCode = (x))

#define GET_MHL3_RX4_AV_LINK_RATE()                                 (g_ucMhl3Rx4AVLinkRate)
#define SET_MHL3_RX4_AV_LINK_RATE(x)                                (g_ucMhl3Rx4AVLinkRate = (x))

//--------------------------------------------------
// Macro of MHL 3.0 AV Link Measure
//--------------------------------------------------
#define GET_MHL3_RX4_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx4MSAFailMacRsetCount)
#define ADD_MHL3_RX4_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx4MSAFailMacRsetCount++)
#define CLR_MHL3_RX4_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx4MSAFailMacRsetCount = 0)

#define GET_MHL3_RX4_MEASURE_VIEW_PIXEL_FORMAT()                    (g_ucMhl3Rx4ViewPixelFormat)
#define SET_MHL3_RX4_MEASURE_VIEW_PIXEL_FORMAT(x)                   (g_ucMhl3Rx4ViewPixelFormat = (x))

#define GET_MHL3_RX4_VIEW_PIXEL_DIVIDER()                           (g_ucMhl3Rx4ViewPixelDivider)
#define SET_MHL3_RX4_VIEW_PIXEL_DIVIDER(x)                          (g_ucMhl3Rx4ViewPixelDivider = (x))

//--------------------------------------------------
// Macro of MHL 3.0 VC ReAllocation
//--------------------------------------------------
#define GET_MHL3_RX4_ECBUS_VC_ASSIGN_NUM_ENT(x)                     (g_pucMhl3Rx4ECBUSVCAssignNumEnt[x])
#define SET_MHL3_RX4_ECBUS_VC_ASSIGN_NUM_ENT(x, y)                  (g_pucMhl3Rx4ECBUSVCAssignNumEnt[x] = (y))

#define GET_MHL3_RX4_ECBUS_VC_ASSIGN_WB_LENGTH(x)                   (g_pucMhl3Rx4ECBUSVCAssignWBLength[x])
#define SET_MHL3_RX4_ECBUS_VC_ASSIGN_WB_LENGTH(x, y)                (g_pucMhl3Rx4ECBUSVCAssignWBLength[x] = (y))

#define GET_MHL3_RX4_ECBUS_VC_ASSIGN_VC_COUNT()                     (g_ucMhl3Rx4ECBUSVCAssignVCCount)
#define SET_MHL3_RX4_ECBUS_VC_ASSIGN_VC_COUNT(x)                    (g_ucMhl3Rx4ECBUSVCAssignVCCount = (x))

#define GET_MHL3_RX4_ECBUS_VC_ASSIGN_VC_NUM(x)                      (g_pucMhl3Rx4ECBUSVCAssignVCNum[x])
#define SET_MHL3_RX4_ECBUS_VC_ASSIGN_VC_NUM(x, y)                   (g_pucMhl3Rx4ECBUSVCAssignVCNum[x] = (y))

#define GET_MHL3_RX4_ECBUS_VC_ASSIGN_VC_ID(x)                       (g_pucMhl3Rx4ECBUSVCAssignVCID[x])
#define SET_MHL3_RX4_ECBUS_VC_ASSIGN_VC_ID(x, y)                    (g_pucMhl3Rx4ECBUSVCAssignVCID[x] = (y))

#define GET_MHL3_RX4_ECBUS_VC_ASSIGN_VC_SIZE(x)                     (g_pucMhl3Rx4ECBUSVCAssignVCSize[x])
#define SET_MHL3_RX4_ECBUS_VC_ASSIGN_VC_SIZE(x, y)                  (g_pucMhl3Rx4ECBUSVCAssignVCSize[x] = (y))

#define GET_MHL3_RX4_ECBUS_VC_ASSIGN_SLOT_VC(x)                     (g_pucMhl3Rx4ECBUSVCAssignSlotVC[x])
#define SET_MHL3_RX4_ECBUS_VC_ASSIGN_SLOT_VC(x, y)                  (g_pucMhl3Rx4ECBUSVCAssignSlotVC[x] = (y))

//--------------------------------------------------
// Macro of MHL 3.0 BIST
//--------------------------------------------------
#define GET_MHL3_RX4_BIST_TESTING()                                 (g_bMhl3Rx4BISTTesting)
#define SET_MHL3_RX4_BIST_TESTING(x)                                (g_bMhl3Rx4BISTTesting = (x))

#define GET_MHL3_RX4_BIST_TESTING_MODE()                            (g_ucMhl3Rx4BISTTestingMode)
#define SET_MHL3_RX4_BIST_TESTING_MODE(x)                           (g_ucMhl3Rx4BISTTestingMode = (x))

#define GET_MHL3_RX4_BIST_ECBUS_DURATION()                          (g_ucMhl3Rx4BISTECBUSDruation)
#define SET_MHL3_RX4_BIST_ECBUS_DURATION(x)                         (g_ucMhl3Rx4BISTECBUSDruation = (x))

#define GET_MHL3_RX4_BIST_IMPEDENCE_MODE()                          (g_ucMhl3Rx4BISTImpedenceMode)
#define SET_MHL3_RX4_BIST_IMPEDENCE_MODE(x)                         (g_ucMhl3Rx4BISTImpedenceMode = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//--------------------------------------------------
// MHL 3.0 eCBUS Info
//--------------------------------------------------
extern StructECBUSProcessInfo g_stMhl3Rx4ECBUSProcess;

//--------------------------------------------------
// MHL 3.0 Video Measure
//--------------------------------------------------
extern BYTE g_ucMhl3Rx4ViewPixelFormat;

//--------------------------------------------------
// MHL 3.0 ECBUS Virtual Channel
//--------------------------------------------------
extern BYTE g_pucMhl3Rx4ECBUSVCAssignNumEnt[16];
extern BYTE g_pucMhl3Rx4ECBUSVCAssignWBLength[16];
extern BYTE g_ucMhl3Rx4ECBUSVCAssignVCCount;
extern BYTE g_pucMhl3Rx4ECBUSVCAssignVCNum[8];
extern BYTE g_pucMhl3Rx4ECBUSVCAssignVCID[8];
extern BYTE g_pucMhl3Rx4ECBUSVCAssignVCSize[8];
extern BYTE g_pucMhl3Rx4ECBUSVCAssignSlotVC[25];

//--------------------------------------------------
// MHL 3.0 BIST
//--------------------------------------------------
extern bit g_bMhl3Rx4BISTTesting;
extern BYTE g_ucMhl3Rx4BISTTestingMode;
extern BYTE g_ucMhl3Rx4BISTECBUSDruation;
extern BYTE g_ucMhl3Rx4BISTImpedenceMode;

//--------------------------------------------------
// MHL 3.0 HID Device
//--------------------------------------------------
extern bit g_bMhl3Rx4HidDeviceActive;
extern BYTE g_ucMhl3Rx4HidDeviceDiscript;

//--------------------------------------------------
// MHL 3.0 AV Link
//--------------------------------------------------
extern BYTE g_ucMhl3Rx4AVLinkNCode;
extern BYTE g_ucMhl3Rx4AVLinkRate;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHL3Rx4ECBUSInitialSetting(void);

extern void ScalerMHL3Rx4ECBUSConfigureSettings(void);
extern void ScalerMHL3Rx4EnableECBUSMode(bit bEnable);
extern void ScalerMHL3Rx4EnableECBUSMode_EXINT0(bit bEnable);

extern void ScalerMHL3Rx4ECBUSResetProc(void);
extern void ScalerMHL3Rx4ECBUSResetProc_EXINT0(void);

extern bit ScalerMHL3Rx4ECBUSTdmReallocation(void);
extern bit ScalerMHL3Rx4DataSignalDetect(void);
extern void ScalerMHL3Rx4MeasureReset(void);
extern bit ScalerMHL3Rx4MeasureCheck(void);
extern BYTE ScalerMHL3Rx4FormatDetect(void);
extern bit ScalerMHL3Rx4ViewPixelFormatCheck(void);
extern bit ScalerMHL3Rx4DisplayFormatSetting(void);
extern DWORD ScalerMHL3Rx4StreamClkRegenerate(void);

extern bit ScalerMHL3Rx4DisplayFormatGenFifoCheck(void);
extern void ScalerMHL3Rx4DisplatFormatGenAdjustHsyncDelay(DWORD ulPixelClkValue);
extern void ScalerMHL3Rx4DisplayFormatGenAdjustVsyncDelay(DWORD ulPixelClkValue);

extern void ScalerMHL3Rx4TimerEventProc(EnumScalerTimerEventID enumEventID);

extern void ScalerMHL3Rx4TestPinSetting(BYTE ucMode);

#if(_ECBUS_TX_TEST_FUNCTION == _ON)
extern void ScalerMHL3Rx4ECBUSTxTestSettingFunction(void);
#endif
#if(_ECBUS_RX_TEST_FUNCTION == _ON)
extern void ScalerMHL3Rx4ECBUSRxTestSettingFunction(void);
#endif
extern void ScalerMHL3Rx4WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

#endif // End of #if((_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) && (_D4_MHL_VERSION >= _MHL_VERSION_3_0))
