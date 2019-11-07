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
// ID Code      : ScalerHDCP2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDCP_2_2_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Write & Read Message ID
//--------------------------------------------------
#define _HDCP_2_2_NONE                                              0x00
#define _HDCP_2_2_AKE_INIT                                          0x02
#define _HDCP_2_2_AKE_SEND_CERT                                     0x03
#define _HDCP_2_2_AKE_NO_STORED_KM                                  0x04
#define _HDCP_2_2_AKE_STORED_KM                                     0x05
#define _HDCP_2_2_AKE_SEND_H_PRIME                                  0x07
#define _HDCP_2_2_AKE_SEND_PAIRING_INFO                             0x08
#define _HDCP_2_2_LC_INIT                                           0x09
#define _HDCP_2_2_LC_SEND_L_PRIME                                   0x0A
#define _HDCP_2_2_SKE_SEND_EKS                                      0x0B
#define _HDCP_2_2_REPEATERAUTH_SEND_RECID_LIST                      0x0C
#define _HDCP_2_2_REPEATERAUTH_SEND_ACK                             0x0F
#define _HDCP_2_2_REPEATERAUTH_STREAM_MANAGE                        0x10
#define _HDCP_2_2_REPEATERAUTH_STREAM_READY                         0x11
#define _HDCP_2_2_SKE_TYPE_VALUE                                    0x12

//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_STATE_UNAUTHENTICATED = 0,
    _HDCP_2_2_STATE_COMPUTE_KM,
    _HDCP_2_2_STATE_COMPUTE_L_PRIME,
    _HDCP_2_2_STATE_COMPUTE_KS,
    _HDCP_2_2_STATE_AUTHENTICATED,
    _HDCP_2_2_STATE_WAIT_FOR_DOWNSTREAM,
    _HDCP_2_2_STATE_ASS_RECEIVER_ID_LIST,
    _HDCP_2_2_STATE_VERIFY_RECEIVER_ID_LIST,
    _HDCP_2_2_STATE_CONTENT_STREAM_MANAGEMENT,
} EnumHdcp2AuthState;

//--------------------------------------------------
// Definitions of HDCP 2.2 D-KEY No.
//--------------------------------------------------
typedef enum
{
    _HDCP_2_2_DKEY_0 = 0,
    _HDCP_2_2_DKEY_1,
    _HDCP_2_2_DKEY_2,
} EnumHdcp2DKey;

//--------------------------------------------------
// Struct for RX HDCP Authentication
//--------------------------------------------------
typedef struct
{
    BYTE b4AuthState : 4;
} StructHdcp2HDCPAuthInfo;

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef struct
{
    BYTE pucHdcp2Certrx[522];
    BYTE pucHdcp2DKey[128];
    BYTE pucHdcp2KPriv[320];
    BYTE pucHdcp2Rrmodn[128];
    BYTE pucHdcp2Lc[16];
    BYTE pucHdcp2Npinv[4];
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
    BYTE pucHdcp2KpubKm[128];
#endif
} StructHdcp2DownLoadKeyType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif // End of #if(_HDCP_2_2_SUPPORT == _ON)
