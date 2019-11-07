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
// ID Code      : RL6410_Series_HDCP2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDCP_2_2_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#define GET_HDCP_2_2_AUTHENTICATION_ACTIVE()                          (bit)(g_ucHdcp2AuthActive)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//----------------------------------------------------------------------------
// Rx Key = 1118 Bytes
//----------------------------------------------------------------------------
extern StructHdcp2DownLoadKeyType g_stRxHdcp2DownLoadKeyType;

//----------------------------------------------------------------------------
// Global Variables (XDATA) for All Interface Shared
//----------------------------------------------------------------------------
extern BYTE g_ucHdcp2AuthActive;

extern BYTE g_pucHdcp2HmacSha256Input[64];
extern BYTE g_pucHdcp2HmacSha256CipherInput[64];

extern BYTE g_pucHdcp2Sha256[32];

extern BYTE g_pucHdcp2BackUp[3];

extern BYTE g_pucHdcp2KpubKm[128];
extern BYTE g_pucHdcp2M[16];
extern BYTE g_pucHdcp2Kh[16];
extern BYTE g_pucHdcp2EkhKm[16];
extern BYTE g_pucHdcp2Ks[16];
extern BYTE g_pucHdcp2EDkeyKs[16];
extern BYTE g_pucHdcp2Riv[8];

extern BYTE g_pucHdcp2InputCipher[16];


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerHdcp2Initial(void);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
extern void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID);
#endif

extern BYTE ScalerHdcp2HPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);
extern BYTE ScalerHdcp2LPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn);
extern void ScalerHdcp2DkeyCalculate_EXINT0(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
extern bit ScalerHdcp2RxSha256Calculate(BYTE *pucInputArray, BYTE ucCalCount);
#endif

extern BYTE ScalerHdcp2RxSha256Calculate_EXINT0(BYTE *pucInputArray, BYTE ucCalCount);
extern void ScalerHdcp2RxAesOfflineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray);
extern BYTE ScalerHdcp2RxHmacSha256Calculate_EXINT0(BYTE *pucInputArray1, BYTE *pucInputArray2);
extern void ScalerHdcp2RxGetRrx_EXINT0(BYTE *pucHdcp2Rrx);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
BYTE ScalerHdcp2RxRsaCalculate_EXINT0(BYTE *pucEkpubKmArray);
BYTE ScalerHdcp2RxRsaOaepCalculate_EXINT0(BYTE *pucKmArray);
#endif

#if((_DP_HDCP_2_2_SUPPORT == _ON) || (_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON))
extern bit ScalerHdcp2RxRsaCalculate(BYTE *pucEkpubKmArray);
extern bit ScalerHdcp2RxRsaOaepCalculate(BYTE *pucKmArray);
extern bit ScalerHdcp2HPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);
extern void ScalerHdcp2DkeyCalculate(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
extern void ScalerHdcp2RxAesOfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray);
extern bit ScalerHdcp2RxHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2);
#endif

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
extern bit ScalerHdcp2LPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn);
#endif
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)
