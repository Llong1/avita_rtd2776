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
// ID Code      : RL6410_Series_MHL3Rx2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) && (_D2_MHL_VERSION >= _MHL_VERSION_3_0))

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of eCBUS-S State Handler
//--------------------------------------------------
#define GET_MHL3_RX2_ECBUS_PROCESS_STATE()                          (g_stMhl3Rx2ECBUSProcess.b3Mhl3ECBUSProcessState)
#define SET_MHL3_RX2_ECBUS_PROCESS_STATE(x)                         (g_stMhl3Rx2ECBUSProcess.b3Mhl3ECBUSProcessState = (x))

//--------------------------------------------------
// Macro of oCBUS --> eCBUS-S Switch
//--------------------------------------------------
#define GET_MHL3_RX2_ECBUS_MODE()                                   (g_stMhl3Rx2ECBUSProcess.b1MHL3ECBUSMode)
#define SET_MHL3_RX2_ECBUS_MODE(x)                                  (g_stMhl3Rx2ECBUSProcess.b1MHL3ECBUSMode = (x))

#define GET_MHL3_RX2_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx2ECBUSProcess.b1MHL3SourceDevCapSupp)
#define SET_MHL3_RX2_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx2ECBUSProcess.b1MHL3SourceDevCapSupp = _TRUE)
#define CLR_MHL3_RX2_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx2ECBUSProcess.b1MHL3SourceDevCapSupp = _FALSE)

#define GET_MHL3_RX2_STATUS_VERSION_3_0()                           (g_stMhl3Rx2ECBUSProcess.b1MHL3StatusVersion30)
#define SET_MHL3_RX2_STATUS_VERSION_3_0()                           (g_stMhl3Rx2ECBUSProcess.b1MHL3StatusVersion30 = _TRUE)
#define CLR_MHL3_RX2_STATUS_VERSION_3_0()                           (g_stMhl3Rx2ECBUSProcess.b1MHL3StatusVersion30 = _FALSE)

#define GET_MHL3_RX2_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx2ECBUSProcess.b1MHL3MscFeatReqUnComplete)
#define SET_MHL3_RX2_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx2ECBUSProcess.b1MHL3MscFeatReqUnComplete = _TRUE)
#define CLR_MHL3_RX2_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx2ECBUSProcess.b1MHL3MscFeatReqUnComplete = _FALSE)

//--------------------------------------------------
// Macro of eCBUS-S Start Up and TDM Sync TMOUT
//--------------------------------------------------
#define GET_MHL3_RX2_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut)
#define SET_MHL3_RX2_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut = _TRUE)
#define CLR_MHL3_RX2_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut = _FALSE)

#define GET_MHL3_RX2_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion)
#define SET_MHL3_RX2_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion = _TRUE)
#define CLR_MHL3_RX2_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion = _FALSE)

#define GET_MHL3_RX2_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp)
#define SET_MHL3_RX2_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp = _TRUE)
#define CLR_MHL3_RX2_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp = _FALSE)

#define GET_MHL3_RX2_ECBUS_CLK_STABLE()                             (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSClkStable)
#define SET_MHL3_RX2_ECBUS_CLK_STABLE()                             (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSClkStable = _TRUE)
#define CLR_MHL3_RX2_ECBUS_CLK_STABLE()                             (g_stMhl3Rx2ECBUSProcess.b1Mhl3ECBUSClkStable = _FALSE)

//--------------------------------------------------
// Macro of eMSC Block Transaction
//--------------------------------------------------
#define GET_MHL3_RX2_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx2ECBUSBlkRcvInfoSent)
#define SET_MHL3_RX2_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx2ECBUSBlkRcvInfoSent = _TRUE)
#define CLR_MHL3_RX2_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx2ECBUSBlkRcvInfoSent = _FALSE)

//--------------------------------------------------
// Macro of MHL 3.0 AV Link
//--------------------------------------------------
#define GET_MHL3_RX2_AV_LINK_N_CODE()                               (g_ucMhl3Rx2AVLinkNCode)
#define SET_MHL3_RX2_AV_LINK_N_CODE(x)                              (g_ucMhl3Rx2AVLinkNCode = (x))

#define GET_MHL3_RX2_AV_LINK_RATE()                                 (g_ucMhl3Rx2AVLinkRate)
#define SET_MHL3_RX2_AV_LINK_RATE(x)                                (g_ucMhl3Rx2AVLinkRate = (x))


//--------------------------------------------------
// Macro of MHL 3.0 AV Link Measure
//--------------------------------------------------
#define GET_MHL3_RX2_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx2MSAFailMacRsetCount)
#define ADD_MHL3_RX2_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx2MSAFailMacRsetCount++)
#define CLR_MHL3_RX2_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx2MSAFailMacRsetCount = 0)

#define GET_MHL3_RX2_MEASURE_VIEW_PIXEL_FORMAT()                    (g_ucMhl3Rx2ViewPixelFormat)
#define SET_MHL3_RX2_MEASURE_VIEW_PIXEL_FORMAT(x)                   (g_ucMhl3Rx2ViewPixelFormat = (x))

#define GET_MHL3_RX2_VIEW_PIXEL_DIVIDER()                           (g_ucMhl3Rx2ViewPixelDivider)
#define SET_MHL3_RX2_VIEW_PIXEL_DIVIDER(x)                          (g_ucMhl3Rx2ViewPixelDivider = (x))

//--------------------------------------------------
// Macro of MHL 3.0 VC ReAllocation
//--------------------------------------------------
#define GET_MHL3_RX2_ECBUS_VC_ASSIGN_NUM_ENT(x)                     (g_pucMhl3Rx2ECBUSVCAssignNumEnt[x])
#define SET_MHL3_RX2_ECBUS_VC_ASSIGN_NUM_ENT(x, y)                  (g_pucMhl3Rx2ECBUSVCAssignNumEnt[x] = (y))

#define GET_MHL3_RX2_ECBUS_VC_ASSIGN_WB_LENGTH(x)                   (g_pucMhl3Rx2ECBUSVCAssignWBLength[x])
#define SET_MHL3_RX2_ECBUS_VC_ASSIGN_WB_LENGTH(x, y)                (g_pucMhl3Rx2ECBUSVCAssignWBLength[x] = (y))

#define GET_MHL3_RX2_ECBUS_VC_ASSIGN_VC_COUNT()                     (g_ucMhl3Rx2ECBUSVCAssignVCCount)
#define SET_MHL3_RX2_ECBUS_VC_ASSIGN_VC_COUNT(x)                    (g_ucMhl3Rx2ECBUSVCAssignVCCount = (x))

#define GET_MHL3_RX2_ECBUS_VC_ASSIGN_VC_NUM(x)                      (g_pucMhl3Rx2ECBUSVCAssignVCNum[x])
#define SET_MHL3_RX2_ECBUS_VC_ASSIGN_VC_NUM(x, y)                   (g_pucMhl3Rx2ECBUSVCAssignVCNum[x] = (y))

#define GET_MHL3_RX2_ECBUS_VC_ASSIGN_VC_ID(x)                       (g_pucMhl3Rx2ECBUSVCAssignVCID[x])
#define SET_MHL3_RX2_ECBUS_VC_ASSIGN_VC_ID(x, y)                    (g_pucMhl3Rx2ECBUSVCAssignVCID[x] = (y))

#define GET_MHL3_RX2_ECBUS_VC_ASSIGN_VC_SIZE(x)                     (g_pucMhl3Rx2ECBUSVCAssignVCSize[x])
#define SET_MHL3_RX2_ECBUS_VC_ASSIGN_VC_SIZE(x, y)                  (g_pucMhl3Rx2ECBUSVCAssignVCSize[x] = (y))

#define GET_MHL3_RX2_ECBUS_VC_ASSIGN_SLOT_VC(x)                     (g_pucMhl3Rx2ECBUSVCAssignSlotVC[x])
#define SET_MHL3_RX2_ECBUS_VC_ASSIGN_SLOT_VC(x, y)                  (g_pucMhl3Rx2ECBUSVCAssignSlotVC[x] = (y))

//--------------------------------------------------
// Macro of MHL 3.0 BIST
//--------------------------------------------------
#define GET_MHL3_RX2_BIST_TESTING()                                 (g_bMhl3Rx2BISTTesting)
#define SET_MHL3_RX2_BIST_TESTING(x)                                (g_bMhl3Rx2BISTTesting = (x))

#define GET_MHL3_RX2_BIST_TESTING_MODE()                            (g_ucMhl3Rx2BISTTestingMode)
#define SET_MHL3_RX2_BIST_TESTING_MODE(x)                           (g_ucMhl3Rx2BISTTestingMode = (x))

#define GET_MHL3_RX2_BIST_ECBUS_DURATION()                          (g_ucMhl3Rx2BISTECBUSDruation)
#define SET_MHL3_RX2_BIST_ECBUS_DURATION(x)                         (g_ucMhl3Rx2BISTECBUSDruation = (x))

#define GET_MHL3_RX2_BIST_IMPEDENCE_MODE()                          (g_ucMhl3Rx2BISTImpedenceMode)
#define SET_MHL3_RX2_BIST_IMPEDENCE_MODE(x)                         (g_ucMhl3Rx2BISTImpedenceMode = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//--------------------------------------------------
// MHL 3.0 eCBUS Info
//--------------------------------------------------
extern StructECBUSProcessInfo g_stMhl3Rx2ECBUSProcess;

//--------------------------------------------------
// MHL 3.0 Video Measure
//--------------------------------------------------
extern BYTE g_ucMhl3Rx2ViewPixelFormat;

//--------------------------------------------------
// MHL 3.0 ECBUS Virtual Channel
//--------------------------------------------------
extern BYTE g_pucMhl3Rx2ECBUSVCAssignNumEnt[16];
extern BYTE g_pucMhl3Rx2ECBUSVCAssignWBLength[16];
extern BYTE g_ucMhl3Rx2ECBUSVCAssignVCCount;
extern BYTE g_pucMhl3Rx2ECBUSVCAssignVCNum[8];
extern BYTE g_pucMhl3Rx2ECBUSVCAssignVCID[8];
extern BYTE g_pucMhl3Rx2ECBUSVCAssignVCSize[8];
extern BYTE g_pucMhl3Rx2ECBUSVCAssignSlotVC[25];

//--------------------------------------------------
// MHL 3.0 BIST
//--------------------------------------------------
extern bit g_bMhl3Rx2BISTTesting;
extern BYTE g_ucMhl3Rx2BISTTestingMode;
extern BYTE g_ucMhl3Rx2BISTECBUSDruation;
extern BYTE g_ucMhl3Rx2BISTImpedenceMode;

//--------------------------------------------------
// MHL 3.0 HID Device
//--------------------------------------------------
extern bit g_bMhl3Rx2HidDeviceActive;
extern BYTE g_ucMhl3Rx2HidDeviceDiscript;

//--------------------------------------------------
// MHL 3.0 AV Link
//--------------------------------------------------
extern BYTE g_ucMhl3Rx2AVLinkNCode;
extern BYTE g_ucMhl3Rx2AVLinkRate;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHL3Rx2ECBUSInitialSetting(void);

extern void ScalerMHL3Rx2ECBUSConfigureSettings(void);
extern void ScalerMHL3Rx2EnableECBUSMode(bit bEnable);
extern void ScalerMHL3Rx2EnableECBUSMode_EXINT0(bit bEnable);

extern void ScalerMHL3Rx2ECBUSResetProc(void);
extern void ScalerMHL3Rx2ECBUSResetProc_EXINT0(void);

extern bit ScalerMHL3Rx2ECBUSTdmReallocation(void);
extern bit ScalerMHL3Rx2DataSignalDetect(void);
extern void ScalerMHL3Rx2MeasureReset(void);
extern bit ScalerMHL3Rx2MeasureCheck(void);
extern BYTE ScalerMHL3Rx2FormatDetect(void);
extern bit ScalerMHL3Rx2ViewPixelFormatCheck(void);
extern bit ScalerMHL3Rx2DisplayFormatSetting(void);
extern DWORD ScalerMHL3Rx2StreamClkRegenerate(void);

extern bit ScalerMHL3Rx2DisplayFormatGenFifoCheck(void);
extern void ScalerMHL3Rx2DisplatFormatGenAdjustHsyncDelay(DWORD ulPixelClkValue);
extern void ScalerMHL3Rx2DisplayFormatGenAdjustVsyncDelay(DWORD ulPixelClkValue);

extern void ScalerMHL3Rx2TimerEventProc(EnumScalerTimerEventID enumEventID);

extern void ScalerMHL3Rx2TestPinSetting(BYTE ucMode);

#if(_ECBUS_TX_TEST_FUNCTION == _ON)
extern void ScalerMHL3Rx2ECBUSTxTestSettingFunction(void);
#endif
#if(_ECBUS_RX_TEST_FUNCTION == _ON)
extern void ScalerMHL3Rx2ECBUSRxTestSettingFunction(void);
#endif
extern void ScalerMHL3Rx2WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

#endif // End of #if((_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) && (_D2_MHL_VERSION >= _MHL_VERSION_3_0))
