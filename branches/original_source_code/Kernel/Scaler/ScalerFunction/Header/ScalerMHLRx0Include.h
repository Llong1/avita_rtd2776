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
// ID Code      : ScalerMHLRx0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Adopter ID
//--------------------------------------------------
#define GET_MHL_RX0_ADOPTER_ID_DONE()                   (g_bMHLRx0AdopterIDDone)
#define SET_MHL_RX0_ADOPTER_ID_DONE()                   (g_bMHLRx0AdopterIDDone = _TRUE)
#define CLR_MHL_RX0_ADOPTER_ID_DONE()                   (g_bMHLRx0AdopterIDDone = _FALSE)

#define GET_MHL_RX0_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx0CbusResetForHTCDone)
#define SET_MHL_RX0_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx0CbusResetForHTCDone = _TRUE)
#define CLR_MHL_RX0_CBUS_RESET_FOR_HTC_DONE()           (g_bMHLRx0CbusResetForHTCDone = _FALSE)

#define GET_MHL_RX0_SENT_MSC_DCAP_RDY()                 (g_bMHLRx0SentMscDcapRdy)
#define SET_MHL_RX0_SENT_MSC_DCAP_RDY()                 (g_bMHLRx0SentMscDcapRdy = _TRUE)
#define CLR_MHL_RX0_SENT_MSC_DCAP_RDY()                 (g_bMHLRx0SentMscDcapRdy = _FALSE)

#define GET_MHL_RX0_MHL_VERSION()                       (g_ucMHLRx0MhlVersion)
#define SET_MHL_RX0_MHL_VERSION(x)                      (g_ucMHLRx0MhlVersion = (x))
#define CLR_MHL_RX0_MHL_VERSION()                       (g_ucMHLRx0MhlVersion = 0x00)

#define GET_MHL_RX0_ADOPTER_ID_HBYTE()                  (g_ucMHLRx0AdopterIDH)
#define GET_MHL_RX0_ADOPTER_ID_LBYTE()                  (g_ucMHLRx0AdopterIDL)
#define CLR_MHL_RX0_ADOPTER_ID_HBYTE()                  (g_ucMHLRx0AdopterIDH = 0xFF)
#define CLR_MHL_RX0_ADOPTER_ID_LBYTE()                  (g_ucMHLRx0AdopterIDL = 0xFF)

#define GET_MHL_RX0_PROCESS_STATE()                     (g_stMHLRx0Process.b4MHLProcessState)
#define SET_MHL_RX0_PROCESS_STATE(x)                    (g_stMHLRx0Process.b4MHLProcessState = (x))

#define GET_MHL_RX0_READY_TO_TRANSMIT()                 (g_stMHLRx0Process.b1MHLTransmitStatus)
#define SET_MHL_RX0_READY_TO_TRANSMIT()                 (g_stMHLRx0Process.b1MHLTransmitStatus = _TRUE)
#define CLR_MHL_RX0_READY_TO_TRANSMIT()                 (g_stMHLRx0Process.b1MHLTransmitStatus = _FALSE)

#define GET_MHL_RX0_READY_TO_RESEND()                   (g_stMHLRx0Process.b1MHLResendStatus)
#define SET_MHL_RX0_READY_TO_RESEND()                   (g_stMHLRx0Process.b1MHLResendStatus = _TRUE)
#define CLR_MHL_RX0_READY_TO_RESEND()                   (g_stMHLRx0Process.b1MHLResendStatus = _FALSE)

#define GET_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx0Process.b1MHLSwitchPortDiscoveryDoneStatus)
#define SET_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx0Process.b1MHLSwitchPortDiscoveryDoneStatus = _TRUE)
#define CLR_MHL_RX0_SWITCH_PORT_DISCOVERY_DONE()        (g_stMHLRx0Process.b1MHLSwitchPortDiscoveryDoneStatus = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucMHLRx0MhlVersion;
extern BYTE g_ucMHLRx0AdopterIDH;
extern BYTE g_ucMHLRx0AdopterIDL;
extern bit g_bMHLRx0AdopterIDDone;
extern bit g_bMHLRx0CbusResetForHTCDone;
extern bit g_bMHLRx0SentMscDcapRdy;
extern StructMHLProcessInfo g_stMHLRx0Process;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit ScalerMHLRx0DetectClkMode(void);
extern BYTE ScalerMHLRx0DetectClkMode_EXINT0(void);
extern bit ScalerMHLRx0MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
extern bit ScalerMHLRx0MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);


#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
