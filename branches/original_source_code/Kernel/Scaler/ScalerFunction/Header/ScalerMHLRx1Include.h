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
// ID Code      : ScalerMHLRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX1_ADOPTER_ID_DONE()                   (g_bMHLRx1AdopterIDDone)
#define SET_MHL_RX1_ADOPTER_ID_DONE()                   (g_bMHLRx1AdopterIDDone = _TRUE)
#define CLR_MHL_RX1_ADOPTER_ID_DONE()                   (g_bMHLRx1AdopterIDDone = _FALSE)

#define GET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx1CbusResetForHTCDone)
#define SET_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx1CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX1_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx1CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX1_SENT_MSC_DCAP_RDY()                 (g_bMHLRx1SentMscDcapRdy)
#define SET_MHL_RX1_SENT_MSC_DCAP_RDY()                 (g_bMHLRx1SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX1_SENT_MSC_DCAP_RDY()                 (g_bMHLRx1SentMscDcapRdy = _FALSE)

#define GET_MHL_RX1_MHL_VERSION()                       (g_ucMHLRx1MhlVersion)
#define SET_MHL_RX1_MHL_VERSION(x)                      (g_ucMHLRx1MhlVersion = (x))
#define CLR_MHL_RX1_MHL_VERSION()                       (g_ucMHLRx1MhlVersion = 0x00)

#define GET_MHL_RX1_ADOPTER_ID_HBYTE()                  (g_ucMHLRx1AdopterIDH)
#define GET_MHL_RX1_ADOPTER_ID_LBYTE()                  (g_ucMHLRx1AdopterIDL)
#define CLR_MHL_RX1_ADOPTER_ID_HBYTE()                  (g_ucMHLRx1AdopterIDH = 0xFF)
#define CLR_MHL_RX1_ADOPTER_ID_LBYTE()                  (g_ucMHLRx1AdopterIDL = 0xFF)

#define GET_MHL_RX1_PROCESS_STATE()                     (g_stMHLRx1Process.b4MHLProcessState)
#define SET_MHL_RX1_PROCESS_STATE(x)                    (g_stMHLRx1Process.b4MHLProcessState = (x))

#define GET_MHL_RX1_READY_TO_TRANSMIT()                 (g_stMHLRx1Process.b1MHLTransmitStatus)
#define SET_MHL_RX1_READY_TO_TRANSMIT()                 (g_stMHLRx1Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX1_READY_TO_TRANSMIT()                 (g_stMHLRx1Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX1_READY_TO_RESEND()                   (g_stMHLRx1Process.b1MHLResendStatus)
#define SET_MHL_RX1_READY_TO_RESEND()                   (g_stMHLRx1Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX1_READY_TO_RESEND()                   (g_stMHLRx1Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx1Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx1Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX1_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx1Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx1MhlVersion;
extern BYTE g_ucMHLRx1AdopterIDH;
extern BYTE g_ucMHLRx1AdopterIDL;
extern bit g_bMHLRx1AdopterIDDone;
extern bit g_bMHLRx1CbusResetForHTCDone;
extern bit g_bMHLRx1SentMscDcapRdy;
extern StructMHLProcessInfo g_stMHLRx1Process;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerMHLRx1DetectClkMode(void);
extern BYTE ScalerMHLRx1DetectClkMode_EXINT0(void);
extern bit ScalerMHLRx1MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx1MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

