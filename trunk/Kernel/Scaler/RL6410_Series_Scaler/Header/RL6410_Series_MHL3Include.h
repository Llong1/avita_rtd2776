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
// ID Code      : RL6410_Series_MHL3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_MHL_SUPPORT == _ON)

#if(_MHL_3_0_SUPPORT == _ON)

//--------------------------------------------------
// Definitions of MHL3 Debug Message Option
//--------------------------------------------------
#define _MHL3_ECBUS_STARTUP_DEBUG_MESSAGE                       _OFF
#define _MHL3_ECBUS_AVLINK_DEBUG_MESSAGE                        _OFF
#define _MHL3_ECBUS_WRITEBURST_DEBUG_MESSAGE                    _OFF
#define _MHL3_BIST_FUNCTION_DEBUG_MESSAGE                       _OFF
#define _MHL3_ECBUS_EMSC_DEBUG_MESSAGE                          _OFF

#define _MHL3_TEST_FUNCTION_DEBUG_MODE                          _OFF
#define _ECBUS_TX_TEST_FUNCTION                                 _OFF
#define _ECBUS_RX_TEST_FUNCTION                                 _OFF


//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of MHL3 Project Option
//--------------------------------------------------
#define _MHL3_ECBUS_AVLINK_CDR_MODE                             _ACDR_MODE
#define _MHL3_RBP_SUPPORT                                       _OFF
#define _MHL3_XVYCC_SUPPORT                                     _OFF
#define _MHL3_AUD_HBR                                           _MHL3_AUD_HBR_OFF
#define _MHL3_ECBUS_SYNC_LOST_SOLUTION                          _ECBUS_SYNC_LOST_REINIT

//--------------------------------------------------
// Definitions of MHL3 Audio Channel
//--------------------------------------------------
#define _MHL3_AUD_HBR_OFF                                       0x00
#define _MHL3_AUD_HBR_ON                                        0x04

//--------------------------------------------------
// Definitions of MHL3 CDR Mode
//--------------------------------------------------
#define _ACDR_MODE                                              0
#define _DCDR_MODE                                              1

//--------------------------------------------------
// Definitions _MHL3_TEST_FUNCTION_DEBUG_MODE
//--------------------------------------------------
#define _ECBUS_APHY                                             0
#define _ECBUS_DPHY                                             1
#define _ECBUS_MAC                                              2
#define _MHL3_MAC                                               3

//--------------------------------------------------
// MHL 3.0 Video Info
//--------------------------------------------------
#define _MHL3_VSYNC_TO_VSYNC_DELAY                              0x00FFFF

//--------------------------------------------------
// Definitions of eCBUS-S Status
//--------------------------------------------------
#define _MHL3_ECBUS_STATE_INITIAL                               0
#define _MHL3_ECBUS_STATE_START_UP_DONE                         1
#define _MHL3_ECBUS_STATE_TDM_SYNC_DONE                         2
#define _MHL3_ECBUS_STATE_EMSC_SYNC_DONE                        3
#define _MHL3_ECBUS_STATE_BIST_TESTING                          4
#define _MHL3_ECBUS_STATE_ECBUS_DONE                            5

//--------------------------------------------------
// Definitions of eCBUS-S BIST Mode
//--------------------------------------------------
#define _MHL3_ECBUS_BIST_MODE_NULL                              0x00
#define _MHL3_ECBUS_BIST_MODE_ECBUS_TX                          0x01
#define _MHL3_ECBUS_BIST_MODE_ECBUS_RX                          0x02
#define _MHL3_ECBUS_BIST_MODE_IMPEDENCE                         0x40
#define _MHL3_ECBUS_BIST_MODE_AVLINK_RX                         0x20

//--------------------------------------------------
// Definitions of MHL 3.0 Video Mode
//--------------------------------------------------
#define _MHL3_VIDEO_MODE_DIV_ERROR                              0xFF
#define _MHL3_VIDEO_24BIT_MODE_DIV                              0x03
#define _MHL3_VIDEO_16BIT_MODE_DIV                              0x02

#define _MHL3_VIDEO_FORMAT_NULL                                 0xFF
#define _MHL3_VIDEO_24BIT_FORMAT                                0x00
#define _MHL3_VIDEO_16BIT_FORMAT                                0x01

//--------------------------------------------------
// MSC Slot Channel Defune
//--------------------------------------------------
#define _MHL3_ECBUS_VC_UN_ASSIGN                                0xFF
#define _MHL3_ECBUS_VC_CBUS1_ASSIGN                             0
#define _MHL3_ECBUS_VC_EMSC_ASSIGN                              1

//--------------------------------------------------
// Macro of oCBUS --> eCBUS-S Switch
//--------------------------------------------------
#define GET_MHL3_ECBUS_MODE()                                   (GET_MHL3_RX2_ECBUS_MODE() | GET_MHL3_RX3_ECBUS_MODE() |\
                                                                 GET_MHL3_RX4_ECBUS_MODE() | GET_MHL3_RX5_ECBUS_MODE())

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// MHL 3.0 eCBUS eMSC Rx Decode Response
//--------------------------------------------------
typedef enum
{
    _MHL3_EMSC_RX_DECODE_SUCCESS = 0x00,
    _MHL3_EMSC_RX_LENGTH_RAMAIN_ERROR,
    _MHL3_EMSC_RX_DECODE_FAIL,
} EnumMHL3eMscRxDecodeRespond;

//--------------------------------------------------
// MHL 3.0 eCBUS eMSC Tx Encode Response
//--------------------------------------------------
typedef enum
{
    _MHL3_EMSC_TX_ACK_SUCCESS = 0x00,
    _MHL3_EMSC_TX_RETRY_EXCEED_LIMIT_FAIL,
    _MHL3_EMSC_TX_NOT_READY_FAIL,
    _MHL3_EMSC_TX_SRAM_OVERFLOW_FAIL,
} EnumMHL3eMscTxEncodeRespond;

//--------------------------------------------------
// Definitions of MHL 3.0 AV Link
//--------------------------------------------------
typedef enum
{
    _ECBUS_LINK_RATE_1_5,
    _ECBUS_LINK_RATE_3_0,
    _ECBUS_LINK_RATE_6_0,
    _ECBUS_LINK_RATE_NULL = 0xFF,
} EnumECBUSAVLinkRate;

typedef enum
{
    _ECBUS_N_CODE_NULL = 0x00,
    _ECBUS_N_CODE_1_5 = 0x02,
    _ECBUS_N_CODE_3_0 = 0x04,
    _ECBUS_N_CODE_6_0 = 0x08,
} EnumECBUSAVLinkNCode;

//--------------------------------------------------
// Definitions of MHL 3.0 Impedance BIST
//--------------------------------------------------
typedef enum
{
    _AV_LINK_RX = 0x02,
    _ECBUS_S_TX_LOW = 0x08,
    _ECBUS_S_TX_HIGH = 0x09,
    _ECBUS_S_RX = 0x0A,
} EnumECBUSImpedanceBIST;

//--------------------------------------------------
// Structure of MHL 3.0
//--------------------------------------------------
typedef struct
{
    BYTE b3Mhl3ECBUSProcessState : 3;
    BYTE b1Mhl3ECBUSStartUpTimeOut : 1;
    BYTE b1Mhl3ECBUSWaitMHLVersion : 1;
    BYTE b1Mhl3ECBUSWaitRAPCBUSUp : 1;
    BYTE b1MHL3ECBUSMode : 1;
    BYTE b1MHL3SourceDevCapSupp : 1;
    BYTE b1MHL3StatusVersion30 : 1;
    BYTE b1MHL3MscFeatReqUnComplete : 1;
    BYTE b1Mhl3ECBUSClkStable : 1;
} StructECBUSProcessInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************



//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif // End of #if(_MHL_3_0_SUPPORT == _ON)

#endif // End of #if(_MHL_SUPPORT == _ON)
