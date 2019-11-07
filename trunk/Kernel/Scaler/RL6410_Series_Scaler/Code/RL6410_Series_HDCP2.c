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
// ID Code      : RL6410_Series_HDCP2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_HDCP2__

#include "ScalerFunctionInclude.h"

#if(_HDCP_2_2_SUPPORT == _ON)

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
//----------------------------------------------------------------------------
// Rx Key = 1118 Bytes
//----------------------------------------------------------------------------
StructHdcp2DownLoadKeyType g_stRxHdcp2DownLoadKeyType;

//----------------------------------------------------------------------------
// Global Variables (XDATA) for All Interface Shared
//----------------------------------------------------------------------------
BYTE g_ucHdcp2AuthActive;

BYTE g_pucHdcp2SHA256Input[64];
BYTE g_pucHdcp2RsaOaepInput[128];
BYTE g_pucHdcp2HmacSha256Input[64];
BYTE g_pucHdcp2HmacSha256CipherInput[64];
BYTE g_pucHdcp2Sha256[32];

BYTE g_pucHdcp2BackUp[3];

BYTE g_pucHdcp2KpubKm[128];
BYTE g_pucHdcp2M[16];
BYTE g_pucHdcp2Kh[16];
BYTE g_pucHdcp2EkhKm[16];
BYTE g_pucHdcp2Ks[16];
BYTE g_pucHdcp2EDkeyKs[16];
BYTE g_pucHdcp2Riv[8];

BYTE g_pucHdcp2InputCipher[16];
BYTE g_pucHdcp2AesInput[16];
BYTE g_pucHdcp2AesCipherInput[16];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//----------------------------------------------------------------------------
// General Function
//----------------------------------------------------------------------------
void ScalerHdcp2Initial(void);
void ScalerHdcp2Handler(void);
void ScalerHdcp2IntHandler_EXINT0(void);
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID);
#endif

//----------------------------------------------------------------------------
// Common Function for All Interface
//----------------------------------------------------------------------------
void ScalerHdcp2DownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType);
void ScalerHdcp2RxDownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType);
BYTE ScalerHdcp2HPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);
BYTE ScalerHdcp2LPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn);
void ScalerHdcp2DkeyCalculate_EXINT0(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
bit ScalerHdcp2RxSha256Calculate(BYTE *pucInputArray, BYTE ucCalCount);
BYTE ScalerHdcp2RxSha256Calculate_EXINT0(BYTE *pucInputArray, BYTE ucCalCount);
void ScalerHdcp2RxAesOfflineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray);
bit ScalerHdcp2RxPairingCalculate(void);
BYTE ScalerHdcp2RxHmacSha256Calculate_EXINT0(BYTE *pucInputArray1, BYTE *pucInputArray2);
void ScalerHdcp2RxGetRrx_EXINT0(BYTE *pucHdcp2Rrx);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
BYTE ScalerHdcp2RxRsaCalculate_EXINT0(BYTE *pucEkpubKmArray);
BYTE ScalerHdcp2RxRsaOaepCalculate_EXINT0(BYTE *pucKmArray);
#endif

#if((_DP_HDCP_2_2_SUPPORT == _ON) || (_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON))
bit ScalerHdcp2RxRsaCalculate(BYTE *pucEkpubKmArray);
bit ScalerHdcp2RxRsaOaepCalculate(BYTE *pucKmArray);
bit ScalerHdcp2HPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps);
void ScalerHdcp2DkeyCalculate(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn);
void ScalerHdcp2RxAesOfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray);
bit ScalerHdcp2RxHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2);
#endif

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
bit ScalerHdcp2LPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 2.2 Initial Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2Initial(void)
{
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ///ScalerDPRx0Hdcp2Initial();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ///ScalerDPRx1Hdcp2Initial();
#endif
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    ScalerTMDSRx2Hdcp2Initial();
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
    ScalerTMDSRx3Hdcp2Initial();
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
    ScalerTMDSRx4Hdcp2Initial();
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
    ScalerTMDSRx5Hdcp2Initial();
#endif
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2Handler(void)
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerDpRx0Hdcp2Handler();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerDpRx1Hdcp2Handler();
#endif
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    ScalerTMDSRx2Hdcp2Handler();
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
    ScalerTMDSRx3Hdcp2Handler();
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
    ScalerTMDSRx4Hdcp2Handler();
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
    ScalerTMDSRx5Hdcp2Handler();
#endif
#endif
}

//--------------------------------------------------
// Description  : HDCP 2.2 Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2IntHandler_EXINT0(void) using 1
{
#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerDpRx0Hdcp2Handler_EXINT0();
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerDpRx1Hdcp2Handler_EXINT0();
#endif
#endif

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
    ScalerTMDSRx2Hdcp2IntHandler_EXINT0();
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
    ScalerTMDSRx3Hdcp2IntHandler_EXINT0();
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
    ScalerTMDSRx4Hdcp2IntHandler_EXINT0();
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
    ScalerTMDSRx5Hdcp2IntHandler_EXINT0();
#endif
#endif
}

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP2.2 Re-Auth Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2ReAuthEvent(EnumScalerTimerEventID enumEventID)
{
    switch(enumEventID)
    {
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH:

            ScalerTMDSRx2Hdcp2ReAuthEvent();

            break;
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX3_HDCP2_REAUTH:

            ScalerTMDSRx3Hdcp2ReAuthEvent();

            break;
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX4_HDCP2_REAUTH:

            ScalerTMDSRx4Hdcp2ReAuthEvent();

            break;
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT))
        case _SCALER_TIMER_EVENT_RX5_HDCP2_REAUTH:

            ScalerTMDSRx5Hdcp2ReAuthEvent();

            break;
#endif

        default:

            break;
    }
}
#endif

//--------------------------------------------------------------------------------------------------------------------------
// Description  : HDCP 2.2 Down Load RSA Key
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array, ucRSAType == > Key Type
// Output Value : None
//--------------------------------------------------------------------------------------------------------------------------
void ScalerHdcp2DownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType)
{
    ScalerHdcp2RxDownLoadCalculateKey(usSubAddr, usLength, pucReadArray, ucRSAType);
}

//--------------------------------------------------------------------------------------------------------------------------
// Description  : HDCP 2.2 Down Load RSA Key for Rx Key
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array, ucRSAType == > Key Type
// Output Value : None
//--------------------------------------------------------------------------------------------------------------------------
void ScalerHdcp2RxDownLoadCalculateKey(WORD usSubAddr, WORD usLength, BYTE *pucReadArray, BYTE ucRSAType)
{
    switch(ucRSAType)
    {
        case _HDCP_2_2_RSA_D_KEY:

            memcpy(&g_stRxHdcp2DownLoadKeyType.pucHdcp2DKey[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_RSA_KPRIV_KEY:

            memcpy(&g_stRxHdcp2DownLoadKeyType.pucHdcp2KPriv[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_RSA_RRMODN_KEY:

            memcpy(&g_stRxHdcp2DownLoadKeyType.pucHdcp2Rrmodn[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_RSA_N_PINV:

            memcpy(&g_stRxHdcp2DownLoadKeyType.pucHdcp2Npinv[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_CERT_RX:

            memcpy(&g_stRxHdcp2DownLoadKeyType.pucHdcp2Certrx[usSubAddr], pucReadArray, usLength);

            break;

        case _HDCP_2_2_LC:

            memcpy(&g_stRxHdcp2DownLoadKeyType.pucHdcp2Lc[usSubAddr], pucReadArray, usLength);

            break;

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        case _HDCP_2_2_KPUB_KM:

            memcpy(&g_stRxHdcp2DownLoadKeyType.pucHdcp2KpubKm[usSubAddr], pucReadArray, usLength);

            break;
#endif

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Hprime Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2HPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps) using 1
{
    // H = HMAC-SHA256(rtx || RxCaps || TxCaps, kd)
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256CipherInput[pData_EXINT[0]] = *(pucHdcp2dKey0 + pData_EXINT[0]);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256CipherInput[16 + pData_EXINT[0]] = *(pucHdcp2dKey1 + pData_EXINT[0]);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[pData_EXINT[0]] = *(pucHdcp2Rtx + pData_EXINT[0]);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[8 + pData_EXINT[0]] = pucHdcp2RxCaps[pData_EXINT[0]];
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 3; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[11 + pData_EXINT[0]] = *(pucHdcp2TxCaps + pData_EXINT[0]);
    }

    g_pucHdcp2HmacSha256Input[14] = 0x80;

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 47; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256Input[15 + pData_EXINT[0]] = 0;
    }

    g_pucHdcp2HmacSha256Input[62] = 0x02;
    g_pucHdcp2HmacSha256Input[63] = 0x70;

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
    {
        g_pucHdcp2HmacSha256CipherInput[32 + pData_EXINT[0]] = 0;
    }

    if(ScalerHdcp2RxHmacSha256Calculate_EXINT0(g_pucHdcp2HmacSha256Input, g_pucHdcp2HmacSha256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Lprime Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2LPrimeCalculate_EXINT0(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn) using 1
{
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 64; pData_EXINT[0]++)
    {
        if(pData_EXINT[0] < 8)
        {
            g_pucHdcp2HmacSha256Input[pData_EXINT[0]] = *(pucHdcp2Rn + pData_EXINT[0]);
        }
        else
        {
            g_pucHdcp2HmacSha256Input[pData_EXINT[0]] = 0;
        }
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 64; pData_EXINT[0]++)
    {
        if(pData_EXINT[0] < 16)
        {
            g_pucHdcp2HmacSha256CipherInput[pData_EXINT[0]] = *(pucHdcp2dKey0 + pData_EXINT[0]);
        }
        else if(pData_EXINT[0] < 32)
        {
            g_pucHdcp2HmacSha256CipherInput[pData_EXINT[0]] = *(pucHdcp2dKey1 + pData_EXINT[0] - 16);

            if(pData_EXINT[0] > 23)
            {
                g_pucHdcp2HmacSha256CipherInput[pData_EXINT[0]] = g_pucHdcp2HmacSha256CipherInput[pData_EXINT[0]] ^ *(pucHdcp2Rrx + pData_EXINT[0] - 24);
            }
        }
        else
        {
            g_pucHdcp2HmacSha256CipherInput[pData_EXINT[0]] = 0;
        }
    }


    g_pucHdcp2HmacSha256Input[8] = 0x80;
    g_pucHdcp2HmacSha256Input[62] = 0x02;
    g_pucHdcp2HmacSha256Input[63] = 0x40;

    if((bit)ScalerHdcp2RxHmacSha256Calculate_EXINT0(g_pucHdcp2HmacSha256Input, g_pucHdcp2HmacSha256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Dkey Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2DkeyCalculate_EXINT0(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn) using 1
{
    switch(ucDkeyCount)
    {
        case _HDCP_2_2_DKEY_0:

            // Initial AES Input Value
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucHdcp2AesInput[pData_EXINT[0]] = *(pucHdcp2Rtx + pData_EXINT[0]);
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucHdcp2AesInput[8 + pData_EXINT[0]] = *(pucHdcp2Rrx + pData_EXINT[0]);
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                g_pucHdcp2AesCipherInput[pData_EXINT[0]] = *(pucHdcp2Km + pData_EXINT[0]);
            }

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

            break;

        case _HDCP_2_2_DKEY_1:

            // Initial AES Input Value
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucHdcp2AesInput[pData_EXINT[0]] = *(pucHdcp2Rtx + pData_EXINT[0]);
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 7; pData_EXINT[0]++)
            {
                g_pucHdcp2AesInput[8 + pData_EXINT[0]] = *(pucHdcp2Rrx + pData_EXINT[0]);
            }

            g_pucHdcp2AesInput[15] = *(pucHdcp2Rrx + 7) ^ 0x01;

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                g_pucHdcp2AesCipherInput[pData_EXINT[0]] = *(pucHdcp2Km + pData_EXINT[0]);
            }

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

            break;

        case _HDCP_2_2_DKEY_2:

            // Initial AES Input Value
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucHdcp2AesInput[pData_EXINT[0]] = *(pucHdcp2Rtx + pData_EXINT[0]);
            }

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 7; pData_EXINT[0]++)
            {
                g_pucHdcp2AesInput[8 + pData_EXINT[0]] = *(pucHdcp2Rrx + pData_EXINT[0]);
            }

            g_pucHdcp2AesInput[15] = *(pucHdcp2Rrx + 7) ^ 0x02;

            for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
            {
                g_pucHdcp2AesCipherInput[pData_EXINT[0]] = *(pucHdcp2Km + pData_EXINT[0]);
            }

            for(pData_EXINT[0] = 8; pData_EXINT[0] < 16; pData_EXINT[0]++)
            {
                g_pucHdcp2AesCipherInput[pData_EXINT[0]] = *(pucHdcp2Km + pData_EXINT[0]) ^ *(pucHdcp2Rn + pData_EXINT[0] - 8);
            }

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2AesInput, g_pucHdcp2AesCipherInput);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 SHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxSha256Calculate(BYTE *pucInputArray, BYTE ucCalCount)
{
    // Set 1, Then Set 0 for Reset SHA256 Module
    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT3, _BIT3);

    ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT3, 0x00);

    // Write SHA256 Input Data, Total 512 bits
    for(pData[1] = 0; pData[1] < 16; pData[1]++)
    {
        ScalerSetByte(P63_31_HDCP_SHA_DATA1, pucInputArray[pData[1] * 4]);
        ScalerSetByte(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + pData[1] * 4]);
        ScalerSetByte(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + pData[1] * 4]);
        ScalerSetByte(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + pData[1] * 4]);

        // Inform HW SHA data Has been set first 32 bit
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT0, _BIT0);
    }

    if(ucCalCount == 0)
    {
        // Set First Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1), _BIT1);

        // Enable SHA256 Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable First Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1), 0x00);

        // Enable SHA256 Calculate
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT2, _BIT2);
    }

    // Polling 10ms for HDCP Sha Done
    if(ScalerTimerPollingFlagProc(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 SHA 256 Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RxSha256Calculate_EXINT0(BYTE *pucInputArray, BYTE ucCalCount) using 1
{
    // Set 1, Then Set 0 for Reset SHA256 Module
    ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT3, _BIT3);

    ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT3, 0x00);

    // Write SHA256 Input Data, Total 512 bits
    for(pData_EXINT[1] = 0; pData_EXINT[1] < 16; pData_EXINT[1]++)
    {
        ScalerSetByte_EXINT(P63_31_HDCP_SHA_DATA1, pucInputArray[pData_EXINT[1] * 4]);
        ScalerSetByte_EXINT(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + pData_EXINT[1] * 4]);
        ScalerSetByte_EXINT(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + pData_EXINT[1] * 4]);
        ScalerSetByte_EXINT(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + pData_EXINT[1] * 4]);

        // Inform HW SHA data Has been set first 32 bit
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT0, _BIT0);
    }

    if(ucCalCount == 0)
    {
        // Set First Calculate
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1), _BIT1);

        // Enable SHA256 Calculate
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable First Calculate
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~(_BIT2 | _BIT1), 0x00);

        // Enable SHA256 Calculate
        ScalerSetBit_EXINT(P63_30_HDCP_SHA_CONTRL, ~_BIT2, _BIT2);
    }

    // Polling 10ms for HDCP Sha Done
    if(ScalerTimerPollingFlagProc_EXINT0(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Off-Line AES Ctrl in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxAesOfflineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray) using 1
{
    // HDCP 2.2 Reset
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

    // AES Random Disable
    ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    // Load Input Value
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetByte_EXINT((P63_61_HDCP_AES_DATA_IN_15 + pData_EXINT[0]), pucInputArray[pData_EXINT[0]]);

        ScalerSetByte_EXINT((P63_71_HDCP_AES_CIPHER_KEY_15 + pData_EXINT[0]), pucCipherArray[pData_EXINT[0]]);
    }

    // Start AES Calculation
    ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    // Wait Finish for AES
    pData_EXINT[0] = 0xFF;
    while((ScalerGetBit_EXINT(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && (--pData_EXINT[0] != 0))
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Pairing Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxPairingCalculate(void)
{
    BYTE pucSHA256Input[64];
    BYTE ucIndex = 0;

    memset(pucSHA256Input, 0, sizeof(pucSHA256Input));

    // Disable HDCP 2.2 Software Reset
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

    // Calculate Kh = SHA256(Kprivrx), Need 3 SHA256 Block
    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        if(ucIndex < 5)
        {
            memcpy(pucSHA256Input, &g_stRxHdcp2DownLoadKeyType.pucHdcp2KPriv[ucIndex << 6], 64);
        }

        else
        {
            pucSHA256Input[0] = 0x80;
            memset(&pucSHA256Input[1], 0, 63);
            pucSHA256Input[62] = 0x0A;
        }

        if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, ucIndex) == _TRUE)
        {
            if(ucIndex == 5)
            {
                memcpy(g_pucHdcp2Kh, (volatile BYTE xdata *)(P63_35_HDCP_SHA_0 + 16), 16);

                return _TRUE;
            }
        }
    }

    DebugMessageHDCP2("HDCP2 Pairing Fail", 0x00);

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 HMACSHA 256 Calculate IN INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RxHmacSha256Calculate_EXINT0(BYTE *pucInputArray1, BYTE *pucInputArray2) using 1
{
    for(pData_EXINT[1] = 0; pData_EXINT[1] < 64; pData_EXINT[1]++)
    {
        // K0 XOR ipad = 512 bit
        *(pucInputArray2 + pData_EXINT[1]) = *(pucInputArray2 + pData_EXINT[1]) ^ 0x36;
    }

    // Calculate SHA256((K0 XOR ipad) || text)
    if(ScalerHdcp2RxSha256Calculate_EXINT0(pucInputArray2, 0) == _TRUE)
    {
        if(ScalerHdcp2RxSha256Calculate_EXINT0(pucInputArray1, 1) == _TRUE)
        {
            // KO XOR opad
            for(pData_EXINT[1] = 0; pData_EXINT[1] < 64; pData_EXINT[1]++)
            {
                *(pucInputArray2 + pData_EXINT[1]) = (*(pucInputArray2 + pData_EXINT[1]) ^ 0x36) ^ 0x5C;
            }

            for(pData_EXINT[1] = 0; pData_EXINT[1] < 64; pData_EXINT[1]++)
            {
                if(pData_EXINT[1] < 32)
                {
                    *(pucInputArray1 + pData_EXINT[1]) = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[1]);
                }
                else
                {
                    *(pucInputArray1 + pData_EXINT[1]) = 0;
                }
            }

            *(pucInputArray1 + 32) = 0x80;
            *(pucInputArray1 + 62) = 0x03;

            // SHA256((KO XOR opad) || SHA256(KO XOR ipad) || text)
            if(ScalerHdcp2RxSha256Calculate_EXINT0(pucInputArray2, 0) == _TRUE)
            {
                if(ScalerHdcp2RxSha256Calculate_EXINT0(pucInputArray1, 1) == _TRUE)
                {
                    return _TRUE;
                }
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Rrx Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxGetRrx_EXINT0(BYTE *pucHdcp2Rrx) using 1
{
    // Load Rrx to Read SRAM
    pucHdcp2Rrx[0] = ScalerGetByte_EXINT(P63_89_HDCP_AES_OUT_7);
    pucHdcp2Rrx[1] = ScalerGetByte_EXINT(P63_8A_HDCP_AES_OUT_6);
    pucHdcp2Rrx[2] = ScalerGetByte_EXINT(P63_8B_HDCP_AES_OUT_5);
    pucHdcp2Rrx[3] = ScalerGetByte_EXINT(P63_8C_HDCP_AES_OUT_4);
    pucHdcp2Rrx[4] = ScalerGetByte_EXINT(P63_8D_HDCP_AES_OUT_3);
    pucHdcp2Rrx[5] = ScalerGetByte_EXINT(P63_8E_HDCP_AES_OUT_2);
    pucHdcp2Rrx[6] = ScalerGetByte_EXINT(P63_8F_HDCP_AES_OUT_1);
    pucHdcp2Rrx[7] = ScalerGetByte_EXINT(P63_90_HDCP_AES_OUT_0);
}

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RxRsaCalculate_EXINT0(BYTE *pucEkpubKmArray) using 1
{
    // Enable HDCP 2.2 RSA Module
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    // RSA Clock Select
    ScalerSetBit_EXINT(P63_92_HDCP_DUMMY1, ~_BIT7, _BIT7);

    // Select RSA Key Download Data Length
    ScalerSetBit_EXINT(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

    // Load Ekpub[km] to RSA Module as cipher text
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (15 - pData_EXINT[0]));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEkpubKmArray[pData_EXINT[0] << 3], 8);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load RRmodN
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - pData_EXINT[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcp2DownLoadKeyType.pucHdcp2Rrmodn[pData_EXINT[0] << 3], 8);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load N Key
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (15 - pData_EXINT[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcp2DownLoadKeyType.pucHdcp2Certrx[(pData_EXINT[0] << 3) + 5], 8);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load D Key
        ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (15 - pData_EXINT[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcp2DownLoadKeyType.pucHdcp2DKey[pData_EXINT[0] << 3], 8);
    }

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, &g_stRxHdcp2DownLoadKeyType.pucHdcp2Npinv, 4);

    // Set RSA Write key done
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

    // Enable RSA Calculate
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT4, 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc_EXINT0(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~_BIT7, 0x00);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Oaep Calculate in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerHdcp2RxRsaOaepCalculate_EXINT0(BYTE *pucKmArray) using 1
{
    // Read Out RSA Message
    ScalerSetBit_EXINT(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5), _BIT6);

    // Read Message From One of 2 Address
    if(ScalerGetBit_EXINT(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
        {
            ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, pData_EXINT[0]);
            memcpy(&g_pucHdcp2RsaOaepInput[(15 - pData_EXINT[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
        {
            ScalerSetByte_EXINT(P63_16_HDCP_RSA_DATA_ADDR, (0x30 | pData_EXINT[0]));
            memcpy(&g_pucHdcp2RsaOaepInput[(15 - pData_EXINT[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }

    // Calculate First Block 512 Bit SHA256 Calculate, Calculate MGF(maskDB, 32)
    if(ScalerHdcp2RxSha256Calculate_EXINT0(&g_pucHdcp2RsaOaepInput[33], 0) == _TRUE)
    {
        // Load Second Block 512 Bit Data
        memcpy(g_pucHdcp2SHA256Input, &g_pucHdcp2RsaOaepInput[97], 31);
        memset(&g_pucHdcp2SHA256Input[31], 0, 33);
        g_pucHdcp2SHA256Input[35] = 0x80;
        g_pucHdcp2SHA256Input[62] = 0x03;
        g_pucHdcp2SHA256Input[63] = 0x18;

        // Calculate Second Block 512 Bit Data
        if(ScalerHdcp2RxSha256Calculate_EXINT0(g_pucHdcp2SHA256Input, 1) == _TRUE)
        {
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
            {
                g_pucHdcp2SHA256Input[pData_EXINT[0]] = g_pucHdcp2RsaOaepInput[1 + pData_EXINT[0]] ^ ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + pData_EXINT[0]));
            }

            memset(&g_pucHdcp2SHA256Input[32], 0, 32);
            g_pucHdcp2SHA256Input[36] = 0x80;
            g_pucHdcp2SHA256Input[62] = 0x01;
            g_pucHdcp2SHA256Input[63] = 0x20;

            // Calculte MGF(Seed, 95), Seed = 32 byte SHA256 output + C 0x0000000x + 0x80 + Stream Length
            g_pucHdcp2SHA256Input[35] = 0;
            ScalerHdcp2RxSha256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0);
            g_pucHdcp2SHA256Input[35] = 1;
            ScalerHdcp2RxSha256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0);
            g_pucHdcp2SHA256Input[35] = 2;
            ScalerHdcp2RxSha256Calculate_EXINT0(g_pucHdcp2SHA256Input, 0);

            // DB maskDB XOR DBmask
            for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
            {
                g_pucHdcp2SHA256Input[pData_EXINT[0]] = g_pucHdcp2RsaOaepInput[33 + pData_EXINT[0] + 64] ^ ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + pData_EXINT[0]));
            }

            g_pucHdcp2SHA256Input[31] = ScalerGetByte_EXINT((P63_35_HDCP_SHA_0 + 31));

            if(g_pucHdcp2SHA256Input[14] == 0x01)
            {
                memcpy(pucKmArray, &g_pucHdcp2SHA256Input[15], 16);

                return _TRUE;
            }
        }
    }

    return _FALSE;
}
#endif

#if((_DP_HDCP_2_2_SUPPORT == _ON) || (_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON))
//--------------------------------------------------
// Description  : HDCP 2.2 RSA Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxRsaCalculate(BYTE *pucEkpubKmArray)
{
    // Enable HDCP 2.2 RSA Module
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

    // RSA Clock Select
    ScalerSetBit(P63_92_HDCP_DUMMY1, ~_BIT7, _BIT7);

    // Select RSA Key Download Data Length
    ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

    // Load Ekpub[km] to RSA Module as cipher text
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (15 - pData[0]));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pucEkpubKmArray[pData[0] << 3], 8);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load RRmodN
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcp2DownLoadKeyType.pucHdcp2Rrmodn[pData[0] << 3], 8);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcp2DownLoadKeyType.pucHdcp2Certrx[(pData[0] << 3) + 5], 8);
    }

    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load D Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + (15 - pData[0])));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &g_stRxHdcp2DownLoadKeyType.pucHdcp2DKey[pData[0] << 3], 8);
    }

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, &g_stRxHdcp2DownLoadKeyType.pucHdcp2Npinv, 4);

    // Set RSA Write key done
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT4, 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT7, 0x00);

        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 RSA Oaep Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxRsaOaepCalculate(BYTE *pucKmArray)
{
    BYTE pucSHA256Input[64];
    BYTE pucRsaOaepInput[128];

    // Read Out RSA Message
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5), _BIT6);

    // Read Message From One of 2 Address
    if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(pData[0] = 0; pData[0] < 16; pData[0]++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, pData[0]);
            memcpy(&pucRsaOaepInput[(15 - pData[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(pData[0] = 0; pData[0] < 16; pData[0]++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 | pData[0]));
            memcpy(&pucRsaOaepInput[(15 - pData[0]) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }

    // Calculate First Block 512 Bit SHA256 Calculate, Calculate MGF(maskDB, 32)
    if(ScalerHdcp2RxSha256Calculate(&pucRsaOaepInput[33], 0) == _TRUE)
    {
        // Load Second Block 512 Bit Data
        memcpy(pucSHA256Input, &pucRsaOaepInput[97], 31);
        memset(&pucSHA256Input[31], 0, 33);
        pucSHA256Input[35] = 0x80;
        pucSHA256Input[62] = 0x03;
        pucSHA256Input[63] = 0x18;

        // Calculate Second Block 512 Bit Data
        if(ScalerHdcp2RxSha256Calculate(pucSHA256Input, 1) == _TRUE)
        {
            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                pucSHA256Input[pData[0]] = pucRsaOaepInput[1 + pData[0]] ^ ScalerGetByte((P63_35_HDCP_SHA_0 + pData[0]));
            }

            memset(&pucSHA256Input[32], 0, 32);
            pucSHA256Input[36] = 0x80;
            pucSHA256Input[62] = 0x01;
            pucSHA256Input[63] = 0x20;

            // Calculte MGF(Seed, 95), Seed = 32 byte SHA256 output + C 0x0000000x + 0x80 + Stream Length
            pucSHA256Input[35] = 0;
            ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0);
            pucSHA256Input[35] = 1;
            ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0);
            pucSHA256Input[35] = 2;
            ScalerHdcp2RxSha256Calculate(pucSHA256Input, 0);

            // DB maskDB XOR DBmask
            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                pucSHA256Input[pData[0]] = pucRsaOaepInput[33 + pData[0] + 64] ^ ScalerGetByte((P63_35_HDCP_SHA_0 + pData[0]));
            }

            pucSHA256Input[31] = ScalerGetByte((P63_35_HDCP_SHA_0 + 31));

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
            for(pData[0] = 0; pData[0] < 16; pData[0]++)
            {
                DebugMessageHDCP2("Km", pucSHA256Input[pData[0] + 15]);
            }
#endif

            if(pucSHA256Input[14] == 0x01)
            {
                memcpy(pucKmArray, &pucSHA256Input[15], 16);

                return _TRUE;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Hprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2HPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2TxCaps, BYTE *pucHdcp2RxCaps)
{
    BYTE pucHMACSHA256Input[64];
    BYTE pucHMACSHA256CipherInput[64];

    memset(pucHMACSHA256Input, 0, sizeof(pucHMACSHA256Input));
    memset(pucHMACSHA256CipherInput, 0, sizeof(pucHMACSHA256CipherInput));

    // H = HMAC-SHA256(rtx || RxCaps || TxCaps, kd)
    // HMAC(text) = HMAC(K, text) = SHA256((K0 XOR opad) || SHA256((KO XOR ipad) || text))
    // Calculate SHA256((KO XOR ipad) || text)

    memcpy(pucHMACSHA256CipherInput, pucHdcp2dKey0, 16);
    memcpy(&pucHMACSHA256CipherInput[16], pucHdcp2dKey1, 16);
    memcpy(pucHMACSHA256Input, pucHdcp2Rtx, 8);
    memcpy(&pucHMACSHA256Input[8], pucHdcp2RxCaps, 3);
    memcpy(&pucHMACSHA256Input[11], pucHdcp2TxCaps, 3);
    pucHMACSHA256Input[14] = 0x80;
    memset(&pucHMACSHA256Input[15], 0, 47);
    pucHMACSHA256Input[62] = 0x02;
    pucHMACSHA256Input[63] = 0x70;

    memset(&pucHMACSHA256CipherInput[32], 0, 32);

    if(ScalerHdcp2RxHmacSha256Calculate(pucHMACSHA256Input, pucHMACSHA256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : HDCP 2.2 Dkey Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2DkeyCalculate(BYTE ucDkeyCount, BYTE *pucHdcp2Rtx, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Km, BYTE *pucHdcp2Rn)
{
    BYTE pucAESInput[16];
    BYTE pucAESCipherInput[16];

    memset(pucAESInput, 0, sizeof(pucAESInput));
    memset(pucAESCipherInput, 0, sizeof(pucAESCipherInput));

    switch(ucDkeyCount)
    {
        case _HDCP_2_2_DKEY_0:

            // Initial AES Input Value
            memcpy(pucAESInput, pucHdcp2Rtx, 8);
            memcpy(&pucAESInput[8], pucHdcp2Rrx, 8);
            memcpy(pucAESCipherInput, pucHdcp2Km, 16);

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl(pucAESInput, pucAESCipherInput);

            break;

        case _HDCP_2_2_DKEY_1:

            // Initial AES Input Value
            memcpy(pucAESInput, pucHdcp2Rtx, 8);
            memcpy(&pucAESInput[8], pucHdcp2Rrx, 7);
            pucAESInput[15] = *(pucHdcp2Rrx + 7) ^ 0x01;
            memcpy(pucAESCipherInput, pucHdcp2Km, 16);

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl(pucAESInput, pucAESCipherInput);

            break;

        case _HDCP_2_2_DKEY_2:

            // Initial AES Input Value
            memcpy(pucAESInput, pucHdcp2Rtx, 8);
            memcpy(&pucAESInput[8], pucHdcp2Rrx, 7);
            pucAESInput[15] = *(pucHdcp2Rrx + 7) ^ 0x02;

            memcpy(pucAESCipherInput, pucHdcp2Km, 8);

            for(pData[0] = 8; pData[0] < 16; pData[0]++)
            {
                pucAESCipherInput[pData[0]] = *(pucHdcp2Km + pData[0]) ^ *(pucHdcp2Rn + pData[0] - 8);
            }

            // AES Calculate
            ScalerHdcp2RxAesOfflineCtrl(pucAESInput, pucAESCipherInput);

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Off-Line AES Ctrl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerHdcp2RxAesOfflineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    BYTE ucDelayTemp = 0xFF;

    // HDCP 2.2 Reset
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

    // AES Random Disable
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

    // Load Input Value
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        ScalerSetByte((P63_61_HDCP_AES_DATA_IN_15 + pData[0]), pucInputArray[pData[0]]);

        ScalerSetByte((P63_71_HDCP_AES_CIPHER_KEY_15 + pData[0]), pucCipherArray[pData[0]]);
    }

    // Start AES Calculation
    ScalerSetBit(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

    // Wait Finish for AES
    while((ScalerGetBit(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && (--ucDelayTemp != 0))
    {
        Delay5us(g_ucDelay5usN);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 HMACSHA 256 Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2RxHmacSha256Calculate(BYTE *pucInputArray1, BYTE *pucInputArray2)
{
    for(pData[0] = 0; pData[0] < 64; pData[0]++)
    {
        // K0 XOR ipad = 512 bit
        // pInputArray2[pData[0]] = pInputArray2[pData[0]] ^ 0x36;
        *(pucInputArray2 + pData[0]) = *(pucInputArray2 + pData[0]) ^ 0x36;
    }

    // Calculate SHA256((K0 XOR ipad) || text)
    if(ScalerHdcp2RxSha256Calculate(pucInputArray2, 0) == _TRUE)
    {
        if(ScalerHdcp2RxSha256Calculate(pucInputArray1, 1) == _TRUE)
        {
            // KO XOR opad
            for(pData[0] = 0; pData[0] < 64; pData[0]++)
            {
                // pInputArray2[pData[0]] = (pInputArray2[pData[0]] ^ 0x36) ^ 0x5C;
                *(pucInputArray2 + pData[0]) = (*(pucInputArray2 + pData[0]) ^ 0x36) ^ 0x5C;
            }

            memcpy(pucInputArray1, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
            memset(pucInputArray1 + 32, 0, 32);
            *(pucInputArray1 + 32) = 0x80;
            *(pucInputArray1 + 62) = 0x03;

            // SHA256((KO XOR opad) || SHA256(KO XOR ipad) || text)
            if(ScalerHdcp2RxSha256Calculate(pucInputArray2, 0) == _TRUE)
            {
                if(ScalerHdcp2RxSha256Calculate(pucInputArray1, 1) == _TRUE)
                {
                    return _TRUE;
                }
            }
        }
    }

    return _FALSE;
}
#endif

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 Lprime Calculate
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerHdcp2LPrimeCalculate(BYTE *pucHdcp2dKey0, BYTE *pucHdcp2dKey1, BYTE *pucHdcp2Rrx, BYTE *pucHdcp2Rn)
{
    BYTE pucHMACSHA256Input[64];
    BYTE pucHMACSHA256CipherInput[64];

    memset(pucHMACSHA256Input, 0, sizeof(pucHMACSHA256Input));
    memset(pucHMACSHA256CipherInput, 0, sizeof(pucHMACSHA256CipherInput));

    memcpy(pucHMACSHA256CipherInput, pucHdcp2dKey0, 16);

    for(pData[0] = 16; pData[0] < 32; pData[0]++)
    {
        pucHMACSHA256CipherInput[pData[0]] = *(pucHdcp2dKey1 + pData[0] - 16);

        if(pData[0] > 23)
        {
            pucHMACSHA256CipherInput[pData[0]] = pucHMACSHA256CipherInput[pData[0]] ^ *(pucHdcp2Rrx + pData[0] - 24);
        }
    }

    memset(&pucHMACSHA256CipherInput[32], 0, 32);
    memcpy(pucHMACSHA256Input, pucHdcp2Rn, 8);
    pucHMACSHA256Input[8] = 0x80;
    memset(&pucHMACSHA256Input[9], 0, 53);
    pucHMACSHA256Input[62] = 0x02;
    pucHMACSHA256Input[63] = 0x40;

    if(ScalerHdcp2RxHmacSha256Calculate(pucHMACSHA256Input, pucHMACSHA256CipherInput) == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}
#endif
#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)
