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
// ID Code      : RL6410_Series_MHL3Rx5Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0))

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of eCBUS-S State Handler
//--------------------------------------------------
#define GET_MHL3_RX5_ECBUS_PROCESS_STATE()                          (g_stMhl3Rx5ECBUSProcess.b3Mhl3ECBUSProcessState)
#define SET_MHL3_RX5_ECBUS_PROCESS_STATE(x)                         (g_stMhl3Rx5ECBUSProcess.b3Mhl3ECBUSProcessState = (x))

//--------------------------------------------------
// Macro of oCBUS --> eCBUS-S Switch
//--------------------------------------------------
#define GET_MHL3_RX5_ECBUS_MODE()                                   (g_stMhl3Rx5ECBUSProcess.b1MHL3ECBUSMode)
#define SET_MHL3_RX5_ECBUS_MODE(x)                                  (g_stMhl3Rx5ECBUSProcess.b1MHL3ECBUSMode = (x))

#define GET_MHL3_RX5_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx5ECBUSProcess.b1MHL3SourceDevCapSupp)
#define SET_MHL3_RX5_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx5ECBUSProcess.b1MHL3SourceDevCapSupp = _TRUE)
#define CLR_MHL3_RX5_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx5ECBUSProcess.b1MHL3SourceDevCapSupp = _FALSE)

#define GET_MHL3_RX5_STATUS_VERSION_3_0()                           (g_stMhl3Rx5ECBUSProcess.b1MHL3StatusVersion30)
#define SET_MHL3_RX5_STATUS_VERSION_3_0()                           (g_stMhl3Rx5ECBUSProcess.b1MHL3StatusVersion30 = _TRUE)
#define CLR_MHL3_RX5_STATUS_VERSION_3_0()                           (g_stMhl3Rx5ECBUSProcess.b1MHL3StatusVersion30 = _FALSE)

#define GET_MHL3_RX5_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx5ECBUSProcess.b1MHL3MscFeatReqUnComplete)
#define SET_MHL3_RX5_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx5ECBUSProcess.b1MHL3MscFeatReqUnComplete = _TRUE)
#define CLR_MHL3_RX5_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx5ECBUSProcess.b1MHL3MscFeatReqUnComplete = _FALSE)

//--------------------------------------------------
// Macro of eCBUS-S Start Up and TDM Sync TMOUT
//--------------------------------------------------
#define GET_MHL3_RX5_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut)
#define SET_MHL3_RX5_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut = _TRUE)
#define CLR_MHL3_RX5_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut = _FALSE)

#define GET_MHL3_RX5_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion)
#define SET_MHL3_RX5_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion = _TRUE)
#define CLR_MHL3_RX5_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion = _FALSE)

#define GET_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp)
#define SET_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp = _TRUE)
#define CLR_MHL3_RX5_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp = _FALSE)

#define GET_MHL3_RX5_ECBUS_CLK_STABLE()                             (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSClkStable)
#define SET_MHL3_RX5_ECBUS_CLK_STABLE()                             (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSClkStable = _TRUE)
#define CLR_MHL3_RX5_ECBUS_CLK_STABLE()                             (g_stMhl3Rx5ECBUSProcess.b1Mhl3ECBUSClkStable = _FALSE)

//--------------------------------------------------
// Macro of eMSC Block Transaction
//--------------------------------------------------
#define GET_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx5ECBUSBlkRcvInfoSent)
#define SET_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx5ECBUSBlkRcvInfoSent = _TRUE)
#define CLR_MHL3_RX5_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx5ECBUSBlkRcvInfoSent = _FALSE)

//--------------------------------------------------
// Macro of MHL 3.0 AV Link
//--------------------------------------------------
#define GET_MHL3_RX5_AV_LINK_N_CODE()                               (g_ucMhl3Rx5AVLinkNCode)
#define SET_MHL3_RX5_AV_LINK_N_CODE(x)                              (g_ucMhl3Rx5AVLinkNCode = (x))

#define GET_MHL3_RX5_AV_LINK_RATE()                                 (g_ucMhl3Rx5AVLinkRate)
#define SET_MHL3_RX5_AV_LINK_RATE(x)                                (g_ucMhl3Rx5AVLinkRate = (x))

//--------------------------------------------------
// Macro of MHL 3.0 AV Link Measure
//--------------------------------------------------
#define GET_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx5MSAFailMacRsetCount)
#define ADD_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx5MSAFailMacRsetCount++)
#define CLR_MHL3_RX5_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx5MSAFailMacRsetCount = 0)

#define GET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT()                    (g_ucMhl3Rx5ViewPixelFormat)
#define SET_MHL3_RX5_MEASURE_VIEW_PIXEL_FORMAT(x)                   (g_ucMhl3Rx5ViewPixelFormat = (x))

#define GET_MHL3_RX5_VIEW_PIXEL_DIVIDER()                           (g_ucMhl3Rx5ViewPixelDivider)
#define SET_MHL3_RX5_VIEW_PIXEL_DIVIDER(x)                          (g_ucMhl3Rx5ViewPixelDivider = (x))

//--------------------------------------------------
// Macro of MHL 3.0 VC ReAllocation
//--------------------------------------------------
#define GET_MHL3_RX5_ECBUS_VC_ASSIGN_NUM_ENT(x)                     (g_pucMhl3Rx5ECBUSVCAssignNumEnt[x])
#define SET_MHL3_RX5_ECBUS_VC_ASSIGN_NUM_ENT(x, y)                  (g_pucMhl3Rx5ECBUSVCAssignNumEnt[x] = (y))

#define GET_MHL3_RX5_ECBUS_VC_ASSIGN_WB_LENGTH(x)                   (g_pucMhl3Rx5ECBUSVCAssignWBLength[x])
#define SET_MHL3_RX5_ECBUS_VC_ASSIGN_WB_LENGTH(x, y)                (g_pucMhl3Rx5ECBUSVCAssignWBLength[x] = (y))

#define GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_COUNT()                     (g_ucMhl3Rx5ECBUSVCAssignVCCount)
#define SET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_COUNT(x)                    (g_ucMhl3Rx5ECBUSVCAssignVCCount = (x))

#define GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_NUM(x)                      (g_pucMhl3Rx5ECBUSVCAssignVCNum[x])
#define SET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_NUM(x, y)                   (g_pucMhl3Rx5ECBUSVCAssignVCNum[x] = (y))

#define GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_ID(x)                       (g_pucMhl3Rx5ECBUSVCAssignVCID[x])
#define SET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_ID(x, y)                    (g_pucMhl3Rx5ECBUSVCAssignVCID[x] = (y))

#define GET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_SIZE(x)                     (g_pucMhl3Rx5ECBUSVCAssignVCSize[x])
#define SET_MHL3_RX5_ECBUS_VC_ASSIGN_VC_SIZE(x, y)                  (g_pucMhl3Rx5ECBUSVCAssignVCSize[x] = (y))

#define GET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(x)                     (g_pucMhl3Rx5ECBUSVCAssignSlotVC[x])
#define SET_MHL3_RX5_ECBUS_VC_ASSIGN_SLOT_VC(x, y)                  (g_pucMhl3Rx5ECBUSVCAssignSlotVC[x] = (y))

//--------------------------------------------------
// Macro of MHL 3.0 BIST
//--------------------------------------------------
#define GET_MHL3_RX5_BIST_TESTING()                                 (g_bMhl3Rx5BISTTesting)
#define SET_MHL3_RX5_BIST_TESTING(x)                                (g_bMhl3Rx5BISTTesting = (x))

#define GET_MHL3_RX5_BIST_TESTING_MODE()                            (g_ucMhl3Rx5BISTTestingMode)
#define SET_MHL3_RX5_BIST_TESTING_MODE(x)                           (g_ucMhl3Rx5BISTTestingMode = (x))

#define GET_MHL3_RX5_BIST_ECBUS_DURATION()                          (g_ucMhl3Rx5BISTECBUSDruation)
#define SET_MHL3_RX5_BIST_ECBUS_DURATION(x)                         (g_ucMhl3Rx5BISTECBUSDruation = (x))

#define GET_MHL3_RX5_BIST_IMPEDENCE_MODE()                          (g_ucMhl3Rx5BISTImpedenceMode)
#define SET_MHL3_RX5_BIST_IMPEDENCE_MODE(x)                         (g_ucMhl3Rx5BISTImpedenceMode = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//--------------------------------------------------
// MHL 3.0 eCBUS Info
//--------------------------------------------------
extern StructECBUSProcessInfo g_stMhl3Rx5ECBUSProcess;

//--------------------------------------------------
// MHL 3.0 Video Measure
//--------------------------------------------------
extern BYTE g_ucMhl3Rx5ViewPixelFormat;

//--------------------------------------------------
// MHL 3.0 ECBUS Virtual Channel
//--------------------------------------------------
extern BYTE g_pucMhl3Rx5ECBUSVCAssignNumEnt[16];
extern BYTE g_pucMhl3Rx5ECBUSVCAssignWBLength[16];
extern BYTE g_ucMhl3Rx5ECBUSVCAssignVCCount;
extern BYTE g_pucMhl3Rx5ECBUSVCAssignVCNum[8];
extern BYTE g_pucMhl3Rx5ECBUSVCAssignVCID[8];
extern BYTE g_pucMhl3Rx5ECBUSVCAssignVCSize[8];
extern BYTE g_pucMhl3Rx5ECBUSVCAssignSlotVC[25];

//--------------------------------------------------
// MHL 3.0 BIST
//--------------------------------------------------
extern bit g_bMhl3Rx5BISTTesting;
extern BYTE g_ucMhl3Rx5BISTTestingMode;
extern BYTE g_ucMhl3Rx5BISTECBUSDruation;
extern BYTE g_ucMhl3Rx5BISTImpedenceMode;

//--------------------------------------------------
// MHL 3.0 HID Device
//--------------------------------------------------
extern bit g_bMhl3Rx5HidDeviceActive;
extern BYTE g_ucMhl3Rx5HidDeviceDiscript;

//--------------------------------------------------
// MHL 3.0 AV Link
//--------------------------------------------------
extern BYTE g_ucMhl3Rx5AVLinkNCode;
extern BYTE g_ucMhl3Rx5AVLinkRate;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHL3Rx5ECBUSInitialSetting(void);

extern void ScalerMHL3Rx5ECBUSConfigureSettings(void);
extern void ScalerMHL3Rx5EnableECBUSMode(bit bEnable);
extern void ScalerMHL3Rx5EnableECBUSMode_EXINT0(bit bEnable);

extern void ScalerMHL3Rx5ECBUSResetProc(void);
extern void ScalerMHL3Rx5ECBUSResetProc_EXINT0(void);

extern bit ScalerMHL3Rx5ECBUSTdmReallocation(void);
extern bit ScalerMHL3Rx5DataSignalDetect(void);
extern void ScalerMHL3Rx5MeasureReset(void);
extern bit ScalerMHL3Rx5MeasureCheck(void);
extern BYTE ScalerMHL3Rx5FormatDetect(void);
extern bit ScalerMHL3Rx5ViewPixelFormatCheck(void);
extern bit ScalerMHL3Rx5DisplayFormatSetting(void);
extern DWORD ScalerMHL3Rx5StreamClkRegenerate(void);

extern bit ScalerMHL3Rx5DisplayFormatGenFifoCheck(void);
extern void ScalerMHL3Rx5DisplatFormatGenAdjustHsyncDelay(DWORD ulPixelClkValue);
extern void ScalerMHL3Rx5DisplayFormatGenAdjustVsyncDelay(DWORD ulPixelClkValue);

extern void ScalerMHL3Rx5TimerEventProc(EnumScalerTimerEventID enumEventID);

extern void ScalerMHL3Rx5TestPinSetting(BYTE ucMode);

#if(_ECBUS_TX_TEST_FUNCTION == _ON)
extern void ScalerMHL3Rx5ECBUSTxTestSettingFunction(void);
#endif
#if(_ECBUS_RX_TEST_FUNCTION == _ON)
extern void ScalerMHL3Rx5ECBUSRxTestSettingFunction(void);
#endif
extern void ScalerMHL3Rx5WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

#endif // End of #if((_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) && (_D5_MHL_VERSION >= _MHL_VERSION_3_0))
