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
// ID Code      : RL6410_Series_MHL3Rx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) && (_D3_MHL_VERSION >= _MHL_VERSION_3_0))

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of eCBUS-S State Handler
//--------------------------------------------------
#define GET_MHL3_RX3_ECBUS_PROCESS_STATE()                          (g_stMhl3Rx3ECBUSProcess.b3Mhl3ECBUSProcessState)
#define SET_MHL3_RX3_ECBUS_PROCESS_STATE(x)                         (g_stMhl3Rx3ECBUSProcess.b3Mhl3ECBUSProcessState = (x))

//--------------------------------------------------
// Macro of oCBUS --> eCBUS-S Switch
//--------------------------------------------------
#define GET_MHL3_RX3_ECBUS_MODE()                                   (g_stMhl3Rx3ECBUSProcess.b1MHL3ECBUSMode)
#define SET_MHL3_RX3_ECBUS_MODE(x)                                  (g_stMhl3Rx3ECBUSProcess.b1MHL3ECBUSMode = (x))

#define GET_MHL3_RX3_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx3ECBUSProcess.b1MHL3SourceDevCapSupp)
#define SET_MHL3_RX3_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx3ECBUSProcess.b1MHL3SourceDevCapSupp = _TRUE)
#define CLR_MHL3_RX3_SOURCE_XDEVCAP_SUPP()                          (g_stMhl3Rx3ECBUSProcess.b1MHL3SourceDevCapSupp = _FALSE)

#define GET_MHL3_RX3_STATUS_VERSION_3_0()                           (g_stMhl3Rx3ECBUSProcess.b1MHL3StatusVersion30)
#define SET_MHL3_RX3_STATUS_VERSION_3_0()                           (g_stMhl3Rx3ECBUSProcess.b1MHL3StatusVersion30 = _TRUE)
#define CLR_MHL3_RX3_STATUS_VERSION_3_0()                           (g_stMhl3Rx3ECBUSProcess.b1MHL3StatusVersion30 = _FALSE)

#define GET_MHL3_RX3_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx3ECBUSProcess.b1MHL3MscFeatReqUnComplete)
#define SET_MHL3_RX3_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx3ECBUSProcess.b1MHL3MscFeatReqUnComplete = _TRUE)
#define CLR_MHL3_RX3_MSC_FEAT_REQ_UNCOMPLETE()                      (g_stMhl3Rx3ECBUSProcess.b1MHL3MscFeatReqUnComplete = _FALSE)

//--------------------------------------------------
// Macro of eCBUS-S Start Up and TDM Sync TMOUT
//--------------------------------------------------
#define GET_MHL3_RX3_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut)
#define SET_MHL3_RX3_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut = _TRUE)
#define CLR_MHL3_RX3_ECBUS_START_UP_TMOUT()                         (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSStartUpTimeOut = _FALSE)

#define GET_MHL3_RX3_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion)
#define SET_MHL3_RX3_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion = _TRUE)
#define CLR_MHL3_RX3_WAIT_SRC_MHL_VERSION_TMOUT()                   (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSWaitMHLVersion = _FALSE)

#define GET_MHL3_RX3_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp)
#define SET_MHL3_RX3_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp = _TRUE)
#define CLR_MHL3_RX3_WAIT_SRC_RAP_CBUS_UP_TMOUT()                   (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSWaitRAPCBUSUp = _FALSE)

#define GET_MHL3_RX3_ECBUS_CLK_STABLE()                             (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSClkStable)
#define SET_MHL3_RX3_ECBUS_CLK_STABLE()                             (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSClkStable = _TRUE)
#define CLR_MHL3_RX3_ECBUS_CLK_STABLE()                             (g_stMhl3Rx3ECBUSProcess.b1Mhl3ECBUSClkStable = _FALSE)

//--------------------------------------------------
// Macro of eMSC Block Transaction
//--------------------------------------------------
#define GET_MHL3_RX3_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx3ECBUSBlkRcvInfoSent)
#define SET_MHL3_RX3_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx3ECBUSBlkRcvInfoSent = _TRUE)
#define CLR_MHL3_RX3_ECBUS_BLK_RCV_BUFFER_INFO_SENT()               (g_bMhl3Rx3ECBUSBlkRcvInfoSent = _FALSE)

//--------------------------------------------------
// Macro of MHL 3.0 AV Link
//--------------------------------------------------
#define GET_MHL3_RX3_AV_LINK_N_CODE()                               (g_ucMhl3Rx3AVLinkNCode)
#define SET_MHL3_RX3_AV_LINK_N_CODE(x)                              (g_ucMhl3Rx3AVLinkNCode = (x))

#define GET_MHL3_RX3_AV_LINK_RATE()                                 (g_ucMhl3Rx3AVLinkRate)
#define SET_MHL3_RX3_AV_LINK_RATE(x)                                (g_ucMhl3Rx3AVLinkRate = (x))

//--------------------------------------------------
// Macro of MHL 3.0 AV Link Measure
//--------------------------------------------------
#define GET_MHL3_RX3_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx3MSAFailMacRsetCount)
#define ADD_MHL3_RX3_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx3MSAFailMacRsetCount++)
#define CLR_MHL3_RX3_MEASURE_FAIL_MAC_RESET_COUNT()                 (g_ucMhl3Rx3MSAFailMacRsetCount = 0)

#define GET_MHL3_RX3_MEASURE_VIEW_PIXEL_FORMAT()                    (g_ucMhl3Rx3ViewPixelFormat)
#define SET_MHL3_RX3_MEASURE_VIEW_PIXEL_FORMAT(x)                   (g_ucMhl3Rx3ViewPixelFormat = (x))

#define GET_MHL3_RX3_VIEW_PIXEL_DIVIDER()                           (g_ucMhl3Rx3ViewPixelDivider)
#define SET_MHL3_RX3_VIEW_PIXEL_DIVIDER(x)                          (g_ucMhl3Rx3ViewPixelDivider = (x))

//--------------------------------------------------
// Macro of MHL 3.0 VC ReAllocation
//--------------------------------------------------
#define GET_MHL3_RX3_ECBUS_VC_ASSIGN_NUM_ENT(x)                     (g_pucMhl3Rx3ECBUSVCAssignNumEnt[x])
#define SET_MHL3_RX3_ECBUS_VC_ASSIGN_NUM_ENT(x, y)                  (g_pucMhl3Rx3ECBUSVCAssignNumEnt[x] = (y))

#define GET_MHL3_RX3_ECBUS_VC_ASSIGN_WB_LENGTH(x)                   (g_pucMhl3Rx3ECBUSVCAssignWBLength[x])
#define SET_MHL3_RX3_ECBUS_VC_ASSIGN_WB_LENGTH(x, y)                (g_pucMhl3Rx3ECBUSVCAssignWBLength[x] = (y))

#define GET_MHL3_RX3_ECBUS_VC_ASSIGN_VC_COUNT()                     (g_ucMhl3Rx3ECBUSVCAssignVCCount)
#define SET_MHL3_RX3_ECBUS_VC_ASSIGN_VC_COUNT(x)                    (g_ucMhl3Rx3ECBUSVCAssignVCCount = (x))

#define GET_MHL3_RX3_ECBUS_VC_ASSIGN_VC_NUM(x)                      (g_pucMhl3Rx3ECBUSVCAssignVCNum[x])
#define SET_MHL3_RX3_ECBUS_VC_ASSIGN_VC_NUM(x, y)                   (g_pucMhl3Rx3ECBUSVCAssignVCNum[x] = (y))

#define GET_MHL3_RX3_ECBUS_VC_ASSIGN_VC_ID(x)                       (g_pucMhl3Rx3ECBUSVCAssignVCID[x])
#define SET_MHL3_RX3_ECBUS_VC_ASSIGN_VC_ID(x, y)                    (g_pucMhl3Rx3ECBUSVCAssignVCID[x] = (y))

#define GET_MHL3_RX3_ECBUS_VC_ASSIGN_VC_SIZE(x)                     (g_pucMhl3Rx3ECBUSVCAssignVCSize[x])
#define SET_MHL3_RX3_ECBUS_VC_ASSIGN_VC_SIZE(x, y)                  (g_pucMhl3Rx3ECBUSVCAssignVCSize[x] = (y))

#define GET_MHL3_RX3_ECBUS_VC_ASSIGN_SLOT_VC(x)                     (g_pucMhl3Rx3ECBUSVCAssignSlotVC[x])
#define SET_MHL3_RX3_ECBUS_VC_ASSIGN_SLOT_VC(x, y)                  (g_pucMhl3Rx3ECBUSVCAssignSlotVC[x] = (y))

//--------------------------------------------------
// Macro of MHL 3.0 BIST
//--------------------------------------------------
#define GET_MHL3_RX3_BIST_TESTING()                                 (g_bMhl3Rx3BISTTesting)
#define SET_MHL3_RX3_BIST_TESTING(x)                                (g_bMhl3Rx3BISTTesting = (x))

#define GET_MHL3_RX3_BIST_TESTING_MODE()                            (g_ucMhl3Rx3BISTTestingMode)
#define SET_MHL3_RX3_BIST_TESTING_MODE(x)                           (g_ucMhl3Rx3BISTTestingMode = (x))

#define GET_MHL3_RX3_BIST_ECBUS_DURATION()                          (g_ucMhl3Rx3BISTECBUSDruation)
#define SET_MHL3_RX3_BIST_ECBUS_DURATION(x)                         (g_ucMhl3Rx3BISTECBUSDruation = (x))

#define GET_MHL3_RX3_BIST_IMPEDENCE_MODE()                          (g_ucMhl3Rx3BISTImpedenceMode)
#define SET_MHL3_RX3_BIST_IMPEDENCE_MODE(x)                         (g_ucMhl3Rx3BISTImpedenceMode = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//--------------------------------------------------
// MHL 3.0 eCBUS Info
//--------------------------------------------------
extern StructECBUSProcessInfo g_stMhl3Rx3ECBUSProcess;

//--------------------------------------------------
// MHL 3.0 Video Measure
//--------------------------------------------------
extern BYTE g_ucMhl3Rx3ViewPixelFormat;

//--------------------------------------------------
// MHL 3.0 ECBUS Virtual Channel
//--------------------------------------------------
extern BYTE g_pucMhl3Rx3ECBUSVCAssignNumEnt[16];
extern BYTE g_pucMhl3Rx3ECBUSVCAssignWBLength[16];
extern BYTE g_ucMhl3Rx3ECBUSVCAssignVCCount;
extern BYTE g_pucMhl3Rx3ECBUSVCAssignVCNum[8];
extern BYTE g_pucMhl3Rx3ECBUSVCAssignVCID[8];
extern BYTE g_pucMhl3Rx3ECBUSVCAssignVCSize[8];
extern BYTE g_pucMhl3Rx3ECBUSVCAssignSlotVC[25];

//--------------------------------------------------
// MHL 3.0 BIST
//--------------------------------------------------
extern bit g_bMhl3Rx3BISTTesting;
extern BYTE g_ucMhl3Rx3BISTTestingMode;
extern BYTE g_ucMhl3Rx3BISTECBUSDruation;
extern BYTE g_ucMhl3Rx3BISTImpedenceMode;

//--------------------------------------------------
// MHL 3.0 HID Device
//--------------------------------------------------
extern bit g_bMhl3Rx3HidDeviceActive;
extern BYTE g_ucMhl3Rx3HidDeviceDiscript;

//--------------------------------------------------
// MHL 3.0 AV Link
//--------------------------------------------------
extern BYTE g_ucMhl3Rx3AVLinkNCode;
extern BYTE g_ucMhl3Rx3AVLinkRate;
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerMHL3Rx3ECBUSInitialSetting(void);

extern void ScalerMHL3Rx3ECBUSConfigureSettings(void);
extern void ScalerMHL3Rx3EnableECBUSMode(bit bEnable);
extern void ScalerMHL3Rx3EnableECBUSMode_EXINT0(bit bEnable);

extern void ScalerMHL3Rx3ECBUSResetProc(void);
extern void ScalerMHL3Rx3ECBUSResetProc_EXINT0(void);

extern bit ScalerMHL3Rx3ECBUSTdmReallocation(void);
extern bit ScalerMHL3Rx3DataSignalDetect(void);
extern void ScalerMHL3Rx3MeasureReset(void);
extern bit ScalerMHL3Rx3MeasureCheck(void);
extern BYTE ScalerMHL3Rx3FormatDetect(void);
extern bit ScalerMHL3Rx3ViewPixelFormatCheck(void);
extern bit ScalerMHL3Rx3DisplayFormatSetting(void);
extern DWORD ScalerMHL3Rx3StreamClkRegenerate(void);

extern bit ScalerMHL3Rx3DisplayFormatGenFifoCheck(void);
extern void ScalerMHL3Rx3DisplatFormatGenAdjustHsyncDelay(DWORD ulPixelClkValue);
extern void ScalerMHL3Rx3DisplayFormatGenAdjustVsyncDelay(DWORD ulPixelClkValue);

extern void ScalerMHL3Rx3TimerEventProc(EnumScalerTimerEventID enumEventID);

extern void ScalerMHL3Rx3TestPinSetting(BYTE ucMode);

#if(_ECBUS_TX_TEST_FUNCTION == _ON)
extern void ScalerMHL3Rx3ECBUSTxTestSettingFunction(void);
#endif
#if(_ECBUS_RX_TEST_FUNCTION == _ON)
extern void ScalerMHL3Rx3ECBUSRxTestSettingFunction(void);
#endif

extern void ScalerMHL3Rx3WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);

#endif // End of #if((_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) && (_D3_MHL_VERSION >= _MHL_VERSION_3_0))
