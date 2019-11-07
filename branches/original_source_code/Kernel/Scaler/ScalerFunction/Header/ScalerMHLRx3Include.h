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
// ID Code      : ScalerMHLRx3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX3_ADOPTER_ID_DONE()                   (g_bMHLRx3AdopterIDDone)
#define SET_MHL_RX3_ADOPTER_ID_DONE()                   (g_bMHLRx3AdopterIDDone = _TRUE)
#define CLR_MHL_RX3_ADOPTER_ID_DONE()                   (g_bMHLRx3AdopterIDDone = _FALSE)

#define GET_MHL_RX3_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx3CbusResetForHTCDone)
#define SET_MHL_RX3_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx3CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX3_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx3CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX3_SENT_MSC_DCAP_RDY()                 (g_bMHLRx3SentMscDcapRdy)
#define SET_MHL_RX3_SENT_MSC_DCAP_RDY()                 (g_bMHLRx3SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX3_SENT_MSC_DCAP_RDY()                 (g_bMHLRx3SentMscDcapRdy = _FALSE)

#define GET_MHL_RX3_MHL_VERSION()                       (g_ucMHLRx3MhlVersion)
#define SET_MHL_RX3_MHL_VERSION(x)                      (g_ucMHLRx3MhlVersion = (x))
#define CLR_MHL_RX3_MHL_VERSION()                       (g_ucMHLRx3MhlVersion = 0x00)

#define GET_MHL_RX3_ADOPTER_ID_HBYTE()                  (g_ucMHLRx3AdopterIDH)
#define GET_MHL_RX3_ADOPTER_ID_LBYTE()                  (g_ucMHLRx3AdopterIDL)
#define CLR_MHL_RX3_ADOPTER_ID_HBYTE()                  (g_ucMHLRx3AdopterIDH = 0xFF)
#define CLR_MHL_RX3_ADOPTER_ID_LBYTE()                  (g_ucMHLRx3AdopterIDL = 0xFF)

#define GET_MHL_RX3_PROCESS_STATE()                     (g_stMHLRx3Process.b4MHLProcessState)
#define SET_MHL_RX3_PROCESS_STATE(x)                    (g_stMHLRx3Process.b4MHLProcessState = (x))

#define GET_MHL_RX3_READY_TO_TRANSMIT()                 (g_stMHLRx3Process.b1MHLTransmitStatus)
#define SET_MHL_RX3_READY_TO_TRANSMIT()                 (g_stMHLRx3Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX3_READY_TO_TRANSMIT()                 (g_stMHLRx3Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX3_READY_TO_RESEND()                   (g_stMHLRx3Process.b1MHLResendStatus)
#define SET_MHL_RX3_READY_TO_RESEND()                   (g_stMHLRx3Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX3_READY_TO_RESEND()                   (g_stMHLRx3Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx3Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx3Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx3Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

#define GET_MHL_RX3_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx3WriteBurstProcessDone)
#define SET_MHL_RX3_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx3WriteBurstProcessDone = _TRUE)
#define CLR_MHL_RX3_WRITE_BURST_PROCESS_DONE()          (g_bMHLRx3WriteBurstProcessDone = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx3MhlVersion;
extern BYTE g_ucMHLRx3AdopterIDH;
extern BYTE g_ucMHLRx3AdopterIDL;
extern bit g_bMHLRx3AdopterIDDone;
extern bit g_bMHLRx3CbusResetForHTCDone;
extern bit g_bMHLRx3SentMscDcapRdy;
extern bit g_bMHLRx3WriteBurstProcessDone;

extern StructMHLProcessInfo g_stMHLRx3Process;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerMHLRx3DetectClkMode(void);
extern BYTE ScalerMHLRx3DetectClkMode_EXINT0(void);
extern bit ScalerMHLRx3MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx3MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);

#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

