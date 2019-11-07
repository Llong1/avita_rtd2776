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
// ID Code      : ScalerDPRx1HDCP2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_HDCP_2_2_SUPPORT == _ON)
#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HDCP 2.2 Authentication State
//--------------------------------------------------
#define GET_DP_RX1_HDCP2_AKE_INIT_RECEIVED()                      (bit)(g_ucDPRx1Hdcp2Ctrl & _BIT7)
#define SET_DP_RX1_HDCP2_AKE_INIT_RECEIVED()                      (g_ucDPRx1Hdcp2Ctrl |= _BIT7)
#define CLR_DP_RX1_HDCP2_AKE_INIT_RECEIVED()                      (g_ucDPRx1Hdcp2Ctrl &= ~_BIT7)

#define GET_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (bit)(g_ucDPRx1Hdcp2Ctrl & _BIT6)
#define SET_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (g_ucDPRx1Hdcp2Ctrl |= _BIT6)
#define CLR_DP_RX1_HDCP2_AKE_NO_STORED_KM_RECEIVED()              (g_ucDPRx1Hdcp2Ctrl &= ~_BIT6)

#define GET_DP_RX1_HDCP2_AKE_STORED_KM_RECEIVED()                 (bit)(g_ucDPRx1Hdcp2Ctrl & _BIT5)
#define SET_DP_RX1_HDCP2_AKE_STORED_KM_RECEIVED()                 (g_ucDPRx1Hdcp2Ctrl |= _BIT5)
#define CLR_DP_RX1_HDCP2_AKE_STORED_KM_RECEIVED()                 (g_ucDPRx1Hdcp2Ctrl &= ~_BIT5)

#define GET_DP_RX1_HDCP2_LC_INIT_RECEIVED()                       (bit)(g_ucDPRx1Hdcp2Ctrl & _BIT4)
#define SET_DP_RX1_HDCP2_LC_INIT_RECEIVED()                       (g_ucDPRx1Hdcp2Ctrl |= _BIT4)
#define CLR_DP_RX1_HDCP2_LC_INIT_RECEIVED()                       (g_ucDPRx1Hdcp2Ctrl &= ~_BIT4)

#define GET_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED()                  (bit)(g_ucDPRx1Hdcp2Ctrl & _BIT3)
#define SET_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED()                  (g_ucDPRx1Hdcp2Ctrl |= _BIT3)
#define CLR_DP_RX1_HDCP2_SKE_SEND_EKS_RECEIVED()                  (g_ucDPRx1Hdcp2Ctrl &= ~_BIT3)

#define GET_DP_RX1_HDCP2_STREAM_MANAGE_RECEIVED()                 (bit)(g_ucDPRx1Hdcp2Ctrl & _BIT2)
#define SET_DP_RX1_HDCP2_STREAM_MANAGE_RECEIVED()                 (g_ucDPRx1Hdcp2Ctrl |= _BIT2)
#define CLR_DP_RX1_HDCP2_STREAM_MANAGE_RECEIVED()                 (g_ucDPRx1Hdcp2Ctrl &= ~_BIT2)

#define GET_DP_RX1_HDCP2_AUTHENTICATION_DONE()                    (bit)(g_ucDPRx1Hdcp2Ctrl & _BIT1)
#define SET_DP_RX1_HDCP2_AUTHENTICATION_DONE()                    (g_ucDPRx1Hdcp2Ctrl |= _BIT1)
#define CLR_DP_RX1_HDCP2_AUTHENTICATION_DONE()                    (g_ucDPRx1Hdcp2Ctrl &= ~_BIT1)

#define GET_DP_RX1_HDCP2_PARING_CALCULATE()                       (bit)(g_ucDPRx1Hdcp2Ctrl & _BIT0)
#define SET_DP_RX1_HDCP2_PARING_CALCULATE()                       (g_ucDPRx1Hdcp2Ctrl |= _BIT0)
#define CLR_DP_RX1_HDCP2_PARING_CALCULATE()                       (g_ucDPRx1Hdcp2Ctrl &= ~_BIT0)

#define SET_DP_RX1_HDCP2_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive |= _BIT1)
#define CLR_DP_RX1_HDCP2_AUTHENTICATION_ACTIVE()                  (g_ucHdcp2AuthActive &= ~_BIT1)

#define GET_DP_RX1_HDCP2_MODE()                                   (ScalerGetBit(PB0_1A_HDCP_IRQ, _BIT1) == _BIT1)
#define GET_DP_RX1_HDCP2_REPEATER_CAPABLE()                       (ScalerDpRx1GetDpcdInfo_EXINT0(0x06, 0x92, 0x1F) == (_BIT1 | _BIT0))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDPRx1Hdcp2Ctrl;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx1Hdcp2Handler(void);
extern void ScalerDpRx1Hdcp2Handler_EXINT0(void);
extern void ScalerDpRx1Hdcp2LoadCertRrxKey(void);
extern void ScalerDpRx1Hdcp2ResetProc(void);

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
#endif // End of #if(_DP_HDCP_2_2_SUPPORT == _ON)

