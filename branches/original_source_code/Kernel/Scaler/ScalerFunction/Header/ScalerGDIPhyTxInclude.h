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
// ID Code      : ScalerGDIPhyTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef struct
{
    BYTE ucDPCDRev;
    BYTE ucLinkRate;
    BYTE ucMaxLinkRate;
//------------------------------------------
    BYTE b3PeerDeviceType : 3;
    BYTE b3LaneNum : 3;
    BYTE b1MSGCapStatus : 1;
    BYTE b1DPPlugStatus : 1;
//------------------------------------------
    BYTE b5MaxLaneNum : 5;
    BYTE b1DPPlugChange : 1;
    BYTE b1LegacyPlugStatus : 1;
    BYTE b1EnhanceFraming : 1;
//------------------------------------------
    BYTE b5MaxLaneNumTemp : 5;
    BYTE b1AlternateSrCapable : 1;
    BYTE b1FramingChangeCapable : 1;
    BYTE b1SSCSupport : 1;
//------------------------------------------
    BYTE b1TP3Support : 1;
    BYTE b1NumberOfSDP : 1;
    BYTE b1NumberOfSDPSink : 1;
    BYTE b1DownStreamInfoReady : 1;
    BYTE b1UpRequestCap : 1;
} StructDownStreamInfo;

typedef struct
{
    BYTE b3TP1Lane0SameVolCnt : 3;
    BYTE b3TP1Lane1SameVolCnt : 3;
    BYTE b2LinkTrainingState : 2;
//------------------------------------------
    BYTE b4LinkTrainingResult : 4;
    BYTE b3TP1Lane2SameVolCnt : 3;
    BYTE b3TP1Lane3SameVolCnt : 3;
    BYTE b3TP2count : 3;
    BYTE ucLinkPBNPerTimeSlot;
    BYTE ucLane0Adjust;
    BYTE ucLane1Adjust;
    BYTE ucLane2Adjust;
    BYTE ucLane3Adjust;
    BYTE ucLane01LTStatus;
    BYTE ucLane23LTStatus;
    BYTE ucLaneAlignStatus;
    BYTE ucAdjustReqLane01;
    BYTE ucAdjustReqLane23;
} StructDPTxLTInfo;

#if(_DP_TX_SUPPORT == _ON)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of DP Tx Downstream Infomation
//--------------------------------------------------
#define GET_DP_TX_LANE0_CURRENT_VOL_SWING()                 (g_stTxLTInfo.ucLane0Adjust & 0x03)
#define SET_DP_TX_LANE0_CURRENT_VOL_SWING(x)                (g_stTxLTInfo.ucLane0Adjust = ((g_stTxLTInfo.ucLane0Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane0Adjust |= _BIT2)
#define CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane0Adjust &= ~_BIT2)

#define GET_DP_TX_LANE1_CURRENT_VOL_SWING()                 (g_stTxLTInfo.ucLane1Adjust & 0x03)
#define SET_DP_TX_LANE1_CURRENT_VOL_SWING(x)                (g_stTxLTInfo.ucLane1Adjust = ((g_stTxLTInfo.ucLane1Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane1Adjust |= _BIT2)
#define CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane1Adjust &= ~_BIT2)

#define GET_DP_TX_LANE2_CURRENT_VOL_SWING()                 (g_stTxLTInfo.ucLane2Adjust & 0x03)
#define SET_DP_TX_LANE2_CURRENT_VOL_SWING(x)                (g_stTxLTInfo.ucLane2Adjust = ((g_stTxLTInfo.ucLane2Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane2Adjust |= _BIT2)
#define CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane2Adjust &= ~_BIT2)

#define GET_DP_TX_LANE3_CURRENT_VOL_SWING()                 (g_stTxLTInfo.ucLane3Adjust & 0x03)
#define SET_DP_TX_LANE3_CURRENT_VOL_SWING(x)                (g_stTxLTInfo.ucLane3Adjust = ((g_stTxLTInfo.ucLane3Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane3Adjust |= _BIT2)
#define CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane3Adjust &= ~_BIT2)

#define GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()              ((g_stTxLTInfo.ucLane0Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(x)             (g_stTxLTInfo.ucLane0Adjust = ((g_stTxLTInfo.ucLane0Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane0Adjust |= _BIT5)
#define CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane0Adjust &= ~_BIT5)

#define GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()              ((g_stTxLTInfo.ucLane1Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(x)             (g_stTxLTInfo.ucLane1Adjust = ((g_stTxLTInfo.ucLane1Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane1Adjust |= _BIT5)
#define CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane1Adjust &= ~_BIT5)

#define GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()              ((g_stTxLTInfo.ucLane2Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(x)             (g_stTxLTInfo.ucLane2Adjust = ((g_stTxLTInfo.ucLane2Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane2Adjust |= _BIT5)
#define CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane2Adjust &= ~_BIT5)

#define GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()              ((g_stTxLTInfo.ucLane3Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(x)             (g_stTxLTInfo.ucLane3Adjust = ((g_stTxLTInfo.ucLane3Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane3Adjust |= _BIT5)
#define CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane3Adjust &= ~_BIT5)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _DP_TX_LANE_0 = 0x00,
    _DP_TX_LANE_1,
    _DP_TX_LANE_2,
    _DP_TX_LANE_3,
} EnumDpTxLane;

//--------------------------------------------------
// Definitions of DP Link Rate
//--------------------------------------------------


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDownStreamInfo g_stDownStreamInfo;
extern StructDPTxLTInfo g_stTxLTInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerGDIPhyTxMLPowerOff(void);
extern void ScalerGDIPhyTxCMUPowerOn(void);
extern void ScalerGDIPhyTxCMUPowerOff(void);
extern void ScalerGDIPhyTxCMUPowerDownMode(void);
extern void ScalerGDIPhyTxMLPHYSet(void);
extern void ScalerGDIPhyTxSetSignalLevel(BYTE ucLinkRate, EnumDpTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
#endif // End of #if(_DP_TX_SUPPORT == _ON)
