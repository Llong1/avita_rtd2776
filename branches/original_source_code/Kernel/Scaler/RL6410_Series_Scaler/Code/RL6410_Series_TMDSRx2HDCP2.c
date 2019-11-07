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
// ID Code      : RL6410_Series_TMDSRx2HDCP2.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6410_SERIES_TMDS_RX2_HDCP2__

#include "ScalerFunctionInclude.h"

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
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
// Global Variables (XDATA) for Each Interface = 77 Bytes
//----------------------------------------------------------------------------
StructHdcp2HDCPAuthInfo g_stTmdsRx2Hdcp2AuthInfo;
BYTE g_ucTmdsRx2Hdcp2Ctrl;

BYTE g_pucTmdsRx2Hdcp2dKey0[16];
BYTE g_pucTmdsRx2Hdcp2dKey1[16];

BYTE g_pucTmdsRx2Hdcp2Km[16];

BYTE g_pucTmdsRx2Hdcp2Rtx[8];
BYTE g_pucTmdsRx2Hdcp2TxCaps[3];
BYTE g_pucTmdsRx2Hdcp2Rn[8];
BYTE g_pucTmdsRx2Hdcp2Rrx[8];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTMDSRx2Hdcp2Enable_EXINT0(void);
void ScalerTMDSRx2Hdcp2Initial(void);
void ScalerTMDSRx2Hdcp2ReAuthEvent(void);

void ScalerTMDSRx2Hdcp2Handler(void);
void ScalerTMDSRx2Hdcp2IntHandler_EXINT0(void);

void ScalerTMDSRx2Hdcp2ResetProc(void);
void ScalerTMDSRx2Hdcp2ResetProc_EXINT0(void);

void ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
void ScalerTMDSRx2Hdcp2AesOnlineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray);
void ScalerTMDSRx2Hdcp2SetRdMsgValue(WORD usAddress, BYTE *pucReadArray, WORD usLength);
void ScalerTMDSRx2Hdcp2SetRdMsgIDCode(BYTE ucValue);
bit ScalerTMDSRx2Hdcp2CaptureKpubKm(void);
void ScalerTMDSRx2Hdcp2CalculateKmKh(void);
#endif

void ScalerTMDSRx2Hdcp2AesOnlineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray);
void ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(WORD usAddress, BYTE *pucReadArray, WORD usLength);
void ScalerTMDSRx2Hdcp2SetRdMsgIDCode_EXINT0(BYTE ucValue);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : HDCP 1.4 Switch to HDCP 2.2 (Can't change the enable/disable procedure)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2Enable_EXINT0(void) using 1
{
    MCU_FE69_DDC2_EDID_IRQ |= _BIT2;

    // set a check duration = 2ms for cover max time(=500us)of Tx read RxStatus (offset address = 0x70)
    // each loop time = 40us
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 50; pData_EXINT[0]++)
    {
        pData_EXINT[1] = 0x03;
        while(--pData_EXINT[1] != 0)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        if((MCU_FE69_DDC2_EDID_IRQ & _BIT2) == _BIT2)
        {
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
        }
        else
        {
            break;
        }
    }

    // Detectd DDC non-Toggle or Timeout to Enable HDCP 2.2 Function
    // Enable HDCP 2.2 Module
    ScalerSetBit_EXINT(P2D_26_HDCP_I2C_CTRL_0, ~_BIT7, _BIT7);

    // Disable HDCP 1.4 Module
    ScalerSetBit_EXINT(P71_C0_HDCP_CR, ~_BIT0, 0x00);

    // Clear HDCP 1.4 IRQ Flag
    ScalerSetBit_EXINT(P71_A9_TMDS_ABC0, ~(_BIT7 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Enable HDCP 1.4 IRQ
    ScalerSetBit_EXINT(P71_AA_TMDS_ABC1, ~(_BIT4 | _BIT2), (_BIT4 | _BIT2));
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2Initial(void)
{
    // Enable HDCP 2 Write SRAM Auto Increase Function
    ScalerSetBit(P2D_20_HDCP_MSG_CTRL, ~_BIT0, _BIT0);

    // Enable HDCP 2 Read SRAM Auto Increase Function
    ScalerSetBit(P2D_23_HDCP_MSGRAP_H, ~_BIT2, _BIT2);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Re-Auth Timer Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2ReAuthEvent(void)
{
    if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        SET_TMDS_RX2_HPD_TRIGGER_EVENT(_TMDS_HPD_HDCP_2_2);

        DebugMessageHDCP2("[D2]BCH ERR FOR HPD EVENT", 0);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Handler Process for TMDS Rx2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2Handler(void)
{
    // Receiver Has Received AKE_INIT
    if(GET_TMDS_RX2_HDCP2_AKE_INIT_RECEIVED() == _TRUE)
    {
        CLR_TMDS_RX2_HDCP2_AKE_INIT_RECEIVED();

        DebugMessageHDCP2("[D2]AKE_INIT", 0);

#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)

        // Reset HDCP Cipher
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, 0x00);
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT3, _BIT3);

        g_pucTmdsRx2Hdcp2Rtx[0] = 0x18;
        g_pucTmdsRx2Hdcp2Rtx[1] = 0xfa;
        g_pucTmdsRx2Hdcp2Rtx[2] = 0xe4;
        g_pucTmdsRx2Hdcp2Rtx[3] = 0x20;
        g_pucTmdsRx2Hdcp2Rtx[4] = 0x6a;
        g_pucTmdsRx2Hdcp2Rtx[5] = 0xfb;
        g_pucTmdsRx2Hdcp2Rtx[6] = 0x51;
        g_pucTmdsRx2Hdcp2Rtx[7] = 0x49;

        g_pucTmdsRx2Hdcp2Rrx[0] = 0x3b;
        g_pucTmdsRx2Hdcp2Rrx[1] = 0xa0;
        g_pucTmdsRx2Hdcp2Rrx[2] = 0xbe;
        g_pucTmdsRx2Hdcp2Rrx[3] = 0xde;
        g_pucTmdsRx2Hdcp2Rrx[4] = 0x0c;
        g_pucTmdsRx2Hdcp2Rrx[5] = 0x46;
        g_pucTmdsRx2Hdcp2Rrx[6] = 0xa9;
        g_pucTmdsRx2Hdcp2Rrx[7] = 0x91;

        g_pucTmdsRx2Hdcp2TxCaps[0] = 0x02;
        g_pucTmdsRx2Hdcp2TxCaps[1] = 0x00;
        g_pucTmdsRx2Hdcp2TxCaps[2] = 0x00;

        g_pucTmdsRx2Caps[0] = 0x02;
        g_pucTmdsRx2Caps[1] = 0x00;
        g_pucTmdsRx2Caps[2] = 0x01;

        // Load Certrx to Read SRAM
        ScalerTMDSRx2Hdcp2SetRdMsgValue(0x01, g_stRxHdcp2DownLoadKeyType.pucHdcp2Certrx, 522);

#endif
    }

    // Receiver Has received AKE_NO_STORED_KM
    if(GET_TMDS_RX2_HDCP2_AKE_NO_STORED_KM_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        if(ScalerTMDSRx2Hdcp2CaptureKpubKm() == _TRUE)
        {
            // Decrypt Km by FW to Get 128 bit Km
            if(ScalerHdcp2RxRsaOaepCalculate(g_pucTmdsRx2Hdcp2Km) == _TRUE)
            {
                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_0, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Km, g_pucTmdsRx2Hdcp2Rn);

                memcpy(g_pucTmdsRx2Hdcp2dKey0, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_1, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Km, g_pucTmdsRx2Hdcp2Rn);

                memcpy(g_pucTmdsRx2Hdcp2dKey1, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                {
                    DebugMessageHDCP2("[D2]Dkey0", g_pucTmdsRx2Hdcp2dKey0[pData[0]]);
                }

                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                {
                    DebugMessageHDCP2("[D2]Dkey1", g_pucTmdsRx2Hdcp2dKey1[pData[0]]);
                }

                if(ScalerHdcp2HPrimeCalculate(g_pucTmdsRx2Hdcp2dKey0, g_pucTmdsRx2Hdcp2dKey1, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2TxCaps, g_pucTmdsRx2Caps) == _TRUE)
                {
                    ScalerTMDSRx2Hdcp2CalculateKmKh();
                }
            }
        }
#endif

        CLR_TMDS_RX2_HDCP2_AKE_NO_STORED_KM_RECEIVED();
        CLR_TMDS_RX2_HDCP2_AUTHENTICATION_ACTIVE();

        DebugMessageHDCP2("[D2]AKE_NO_STORED_KM", 0);
    }

    if(GET_TMDS_RX2_HDCP2_AKE_STORED_KM_RECEIVED() == _TRUE)
    {
        CLR_TMDS_RX2_HDCP2_AKE_STORED_KM_RECEIVED();

        DebugMessageHDCP2("[D2]AKE_STORED_KM", 0);
    }

    if(GET_TMDS_RX2_HDCP2_LC_INIT_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)

        BYTE pucSHA256[32];
        memset(pucSHA256, 0, sizeof(pucSHA256));

        g_pucTmdsRx2Hdcp2Rn[0] = 0x32;
        g_pucTmdsRx2Hdcp2Rn[1] = 0x75;
        g_pucTmdsRx2Hdcp2Rn[2] = 0x3e;
        g_pucTmdsRx2Hdcp2Rn[3] = 0xa8;
        g_pucTmdsRx2Hdcp2Rn[4] = 0x78;
        g_pucTmdsRx2Hdcp2Rn[5] = 0xa6;
        g_pucTmdsRx2Hdcp2Rn[6] = 0x38;
        g_pucTmdsRx2Hdcp2Rn[7] = 0x1c;

        if(ScalerHdcp2LPrimeCalculate(g_pucTmdsRx2Hdcp2dKey0, g_pucTmdsRx2Hdcp2dKey1, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Rn) == _TRUE)
        {
            // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 10
            ScalerTMDSRx2Hdcp2SetRdMsgIDCode(_HDCP_2_2_LC_SEND_L_PRIME);

            memcpy(pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

            ScalerTMDSRx2Hdcp2SetRdMsgValue(0x01, pucSHA256, 32);

            for(pData[0] = 0; pData[0] < 32; pData[0]++)
            {
                DebugMessageHDCP2("[D2]L_Prime", pucSHA256[pData[0]]);
            }

            // Set Message Size = 0x21
            ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
            ScalerSetByte(P71_C3_HDCP_AP, 0x70);
            ScalerSetByte(P71_C4_HDCP_DP, 0x21);
            ScalerSetByte(P71_C3_HDCP_AP, 0x71);
            ScalerSetByte(P71_C4_HDCP_DP, 0x00);
            ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);
        }
#endif

        CLR_TMDS_RX2_HDCP2_LC_INIT_RECEIVED();

        DebugMessageHDCP2("[D2]LC_INIT", 0);
    }

    if(GET_TMDS_RX2_HDCP2_SKE_SEND_EKS_RECEIVED() == _TRUE)
    {
#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
        BYTE pucEDkeyKs[16];
        BYTE pucInputCipher[16];
        BYTE pucRiv[8];
        BYTE pucKs[16];

        memset(pucInputCipher, 0, sizeof(pucInputCipher));
        memset(pucKs, 0, sizeof(pucKs));

        // Calculate Dkey 2
        ScalerHdcp2DkeyCalculate(_HDCP_2_2_DKEY_2, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Km, g_pucTmdsRx2Hdcp2Rn);

        pucEDkeyKs[0] = 0x4c;
        pucEDkeyKs[1] = 0x32;
        pucEDkeyKs[2] = 0x47;
        pucEDkeyKs[3] = 0x12;
        pucEDkeyKs[4] = 0xc4;
        pucEDkeyKs[5] = 0xbe;
        pucEDkeyKs[6] = 0xc6;
        pucEDkeyKs[7] = 0x69;
        pucEDkeyKs[8] = 0x0a;
        pucEDkeyKs[9] = 0xc2;
        pucEDkeyKs[10] = 0x19;
        pucEDkeyKs[11] = 0x64;
        pucEDkeyKs[12] = 0xde;
        pucEDkeyKs[13] = 0x91;
        pucEDkeyKs[14] = 0xf1;
        pucEDkeyKs[15] = 0x83;

        pucRiv[0] = 0x40;
        pucRiv[1] = 0x2b;
        pucRiv[2] = 0x6b;
        pucRiv[3] = 0x43;
        pucRiv[4] = 0xc5;
        pucRiv[5] = 0xe8;
        pucRiv[6] = 0x86;
        pucRiv[7] = 0xd8;

        // Decode Ks
        for(pData[0] = 0; pData[0] < 8; ++pData[0])
        {
            pucKs[pData[0]] = pucEDkeyKs[pData[0]] ^ ScalerGetByte((P63_81_HDCP_AES_OUT_15 + pData[0]));
        }

        for(pData[0] = 8; pData[0] < 16; ++pData[0])
        {
            pucKs[pData[0]] = pucEDkeyKs[pData[0]] ^ (ScalerGetByte((P63_81_HDCP_AES_OUT_15 + pData[0])) ^ g_pucTmdsRx2Hdcp2Rrx[pData[0] - 8]);
        }


        for(pData[0] = 0; pData[0] < 16; pData[0]++)
        {
            DebugMessageHDCP2("[D2]Ks", pucKs[pData[0]]);
        }

        SET_TMDS_RX2_HDCP2_AUTHENTICATION_DONE();

        // Enable HDMI Link Integrity Check
        ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        SET_TMDS_RX2_HDCP2_AUTH_STATE(_HDCP_2_2_STATE_AUTHENTICATED);

        // Enable Decryption
        for(pData[0] = 0; pData[0] < 16; ++pData[0])
        {
            pucInputCipher[pData[0]] = pucKs[pData[0]] ^ g_stRxHdcp2DownLoadKeyType.pucHdcp2Lc[pData[0]];
        }

        // Enable AES Decryption Cipher
        ScalerTMDSRx2Hdcp2AesOnlineCtrl(pucRiv, pucInputCipher);
#endif

        CLR_TMDS_RX2_HDCP2_SKE_SEND_EKS_RECEIVED();

        DebugMessageHDCP2("[D2]SKE_SEND_EKS", 0);
    }

    if(GET_TMDS_RX2_HDCP2_AUTHENTICATION_DONE() == _TRUE)
    {
        // Check BCH Error or Not
        if(ScalerGetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear BCH Error Flag
            ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1, ~_BIT6, _BIT6);

            // Clear Authentication Done Flag
            CLR_TMDS_RX2_HDCP2_AUTHENTICATION_DONE();

            DebugMessageHDCP2("[D2]REAUTH_REQ", 0);

            // Set HDCP 2.2 Authentication State = UnAuthenticated
            SET_TMDS_RX2_HDCP2_AUTH_STATE(_HDCP_2_2_STATE_UNAUTHENTICATED);

            // Set RxStatus REAUTH_REQ
            ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
            ScalerSetDataPortBit(P71_C3_HDCP_AP, _P71_C4_PT_71_PORT_PAGE71_HDCP2_STATUS2, ~_BIT3, _BIT3);
            ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

            // Active HDCP 2.2 Re-Auth Timer Event for HPD Trigger Event Usage
            ScalerTimerActiveTimerEvent(SEC(2), _SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);
        }
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Int Handler Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2IntHandler_EXINT0(void) using 1
{
    // Detect HDCP 2.2 Write Message Done IRQ
    if((ScalerGetBit_EXINT(P2D_35_HDCP_I2C_CTRL_7, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P2D_36_HDCP_I2C_CTRL_8, _BIT0) == _BIT0))
    {
        // Clear HDCP 2.2 Write Message Done Flag
        ScalerSetBit_EXINT(P2D_36_HDCP_I2C_CTRL_8, ~_BIT0, _BIT0);

        // Judge HDCP Switch to 2.2 Mode or not
        if((ScalerGetBit_EXINT(P2D_26_HDCP_I2C_CTRL_0, _BIT7) == 0x00) && (ScalerGetBit_EXINT(P71_C0_HDCP_CR, _BIT0) == _BIT0))
        {
            ScalerTMDSRx2Hdcp2Enable_EXINT0();
        }

        g_pucHdcp2BackUp[0] = ScalerGetByte_EXINT(P2D_21_HDCP_MSGWAP);

        ScalerSetByte_EXINT(P2D_21_HDCP_MSGWAP, 0x00);

        // Detect HDCP 2.2 Transmitter Write AKE_Init Message, Message ID = 2
        switch(ScalerGetByte_EXINT(P2D_22_HDCP_MSGWDP))
        {
            case _HDCP_2_2_AKE_INIT:

                // HDCP2 Reset Proc
                ScalerTMDSRx2Hdcp2ResetProc_EXINT0();

                // Save Transmitter Rtx to FW
                ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(0x01, 8, g_pucTmdsRx2Hdcp2Rtx);

                // Save TxCaps to FW
                ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(0x09, 3, g_pucTmdsRx2Hdcp2TxCaps);

                // Rrx Gen
                // Enable AES Random Gen
                ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), (_BIT5));

                // AES Trigger
                ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~_BIT6, _BIT6);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < (TL2 >> 2); pData_EXINT[0]++)
                {
                    Delay5us_EXINT(g_ucDelay5usN);
                }

                // Wait Finish for AES Random Gen
                pData_EXINT[0] = 0x0A;
                while((ScalerGetBit_EXINT(P63_60_HDCP_AES_CTRL, _BIT6) == _BIT6) && (--pData_EXINT[0] != 0))
                {
                    Delay5us_EXINT(g_ucDelay5usN);
                }

                // Disable AES Random Gen
                ScalerSetBit_EXINT(P63_60_HDCP_AES_CTRL, ~(_BIT6 | _BIT5), 0x00);

                // Get Rrx from HW
                ScalerHdcp2RxGetRrx_EXINT0(g_pucTmdsRx2Hdcp2Rrx);

                g_pucHdcp2BackUp[1] = ScalerGetByte_EXINT(P2D_23_HDCP_MSGRAP_H);
                g_pucHdcp2BackUp[2] = ScalerGetByte_EXINT(P2D_24_HDCP_MSGRAP_L);

                // Load Certrx to Read SRAM
                ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(0x01, g_stRxHdcp2DownLoadKeyType.pucHdcp2Certrx, 522);

                // Load Rrx to Read SRAM
                ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(0x020B, g_pucTmdsRx2Hdcp2Rrx, 8);

                // Load RxCaps HDCP 2.2 Support to Read SRAM
                ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(0x0213, g_pucTmdsRx2Caps, 3);

                // Load Message ID = 3
                ScalerTMDSRx2Hdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_AKE_SEND_CERT);

                // Set AKE_SEND_CERT Message Size = 534
                ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x70);
                ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x16);
                ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x71);
                ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x02);
                ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

                ScalerSetByte_EXINT(P2D_23_HDCP_MSGRAP_H, g_pucHdcp2BackUp[1]);
                ScalerSetByte_EXINT(P2D_24_HDCP_MSGRAP_L, g_pucHdcp2BackUp[2]);

                SET_TMDS_RX2_HDCP2_AKE_INIT_RECEIVED();

                break;

            case _HDCP_2_2_AKE_NO_STORED_KM:

                SET_TMDS_RX2_HDCP2_AKE_NO_STORED_KM_RECEIVED();
                SET_TMDS_RX2_HDCP2_AUTHENTICATION_ACTIVE();

                // Save Transmitter Ekpub[km] to FW
                ScalerSetByte_EXINT(P2D_21_HDCP_MSGWAP, 0x01);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 128; ++pData_EXINT[0])
                {
                    g_pucHdcp2KpubKm[pData_EXINT[0]] = ScalerGetByte_EXINT(P2D_22_HDCP_MSGWDP);
                }

                // Decrypt Ekpub[km]
                if(ScalerHdcp2RxRsaCalculate_EXINT0(g_pucHdcp2KpubKm) == _TRUE)
                {
                    // Decrypt Km by FW to Get 128 bit Km
                    if(ScalerHdcp2RxRsaOaepCalculate_EXINT0(g_pucTmdsRx2Hdcp2Km) == _TRUE)
                    {
                        ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_0, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Km, g_pucTmdsRx2Hdcp2Rn);

                        memcpy(g_pucTmdsRx2Hdcp2dKey0, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                        ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_1, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Km, g_pucTmdsRx2Hdcp2Rn);

                        memcpy(g_pucTmdsRx2Hdcp2dKey1, (volatile BYTE xdata *)P63_81_HDCP_AES_OUT_15, 16);

                        if(ScalerHdcp2HPrimeCalculate_EXINT0(g_pucTmdsRx2Hdcp2dKey0, g_pucTmdsRx2Hdcp2dKey1, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2TxCaps, g_pucTmdsRx2Caps) == _TRUE)
                        {
                            memset(g_pucHdcp2Sha256, 0, sizeof(g_pucHdcp2Sha256));

                            // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 0x07
                            ScalerTMDSRx2Hdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_AKE_SEND_H_PRIME);

                            memcpy(g_pucHdcp2Sha256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

                            // Load Km to Read SRAM
                            ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(0x01, g_pucHdcp2Sha256, 32);

                            // Set Message Size = 0x21
                            ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                            ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x70);
                            ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x21);
                            ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x71);
                            ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x00);
                            ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

                            // Enable HDCP2 Source Read Done IRQ
                            ScalerSetBit_EXINT(P2D_36_HDCP_I2C_CTRL_8, ~_BIT1, _BIT1);
                            ScalerSetBit_EXINT(P2D_35_HDCP_I2C_CTRL_7, ~_BIT1, _BIT1);
                        }
                    }
                }

                // Set HDCP 2.2 State to Compute Km
                SET_TMDS_RX2_HDCP2_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_KM);

                break;

            case _HDCP_2_2_AKE_STORED_KM:

                // Save Ekh[km] From Transmitter to FW
                ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(0x01, 16, g_pucTmdsRx2Hdcp2Km);

                // Save m From Transmitter to FW
                ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(0x11, 16, g_pucHdcp2M);

                // Calculate Km use AES Cipher, Input Value = m, Input Cipher = Kh
                ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, g_pucHdcp2Kh);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 0x10; ++pData_EXINT[0])
                {
                    g_pucTmdsRx2Hdcp2Km[pData_EXINT[0]] = g_pucTmdsRx2Hdcp2Km[pData_EXINT[0]] ^ ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate DKey0
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_0, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Km, g_pucTmdsRx2Hdcp2Rn);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucTmdsRx2Hdcp2dKey0[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate Dkey1
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_1, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Km, g_pucTmdsRx2Hdcp2Rn);

                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
                {
                    g_pucTmdsRx2Hdcp2dKey1[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]);
                }

                // Calculate H'
                if(ScalerHdcp2HPrimeCalculate_EXINT0(g_pucTmdsRx2Hdcp2dKey0, g_pucTmdsRx2Hdcp2dKey1, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2TxCaps, g_pucTmdsRx2Caps) == _TRUE)
                {
                    // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 0x07
                    ScalerTMDSRx2Hdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_AKE_SEND_H_PRIME);

                    for(pData_EXINT[2] = 0; pData_EXINT[2] < 32; pData_EXINT[2]++)
                    {
                        g_pucHdcp2Sha256[pData_EXINT[2]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[2]);
                    }

                    ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(0x01, g_pucHdcp2Sha256, 32);

                    // Set Message Size = 0x21
                    ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                    ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x70);
                    ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x21);
                    ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x71);
                    ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x00);
                    ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);
                }

                SET_TMDS_RX2_HDCP2_AKE_STORED_KM_RECEIVED();

                // Set HDCP 2.2 State to Compute Km
                SET_TMDS_RX2_HDCP2_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_KM);

                break;

            case _HDCP_2_2_LC_INIT:

                // Save Transmitter Rn to FW
                ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(0x01, 8, g_pucTmdsRx2Hdcp2Rn);

                if(ScalerHdcp2LPrimeCalculate_EXINT0(g_pucTmdsRx2Hdcp2dKey0, g_pucTmdsRx2Hdcp2dKey1, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Rn) == _TRUE)
                {
                    // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 10
                    ScalerTMDSRx2Hdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_LC_SEND_L_PRIME);

                    for(pData_EXINT[0] = 0; pData_EXINT[0] < 32; pData_EXINT[0]++)
                    {
                        g_pucHdcp2Sha256[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_35_HDCP_SHA_0 + pData_EXINT[0]);
                    }

                    ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(0x01, g_pucHdcp2Sha256, 32);

                    // Set Message Size = 0x21
                    ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
                    ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x70);
                    ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x21);
                    ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x71);
                    ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x00);
                    ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);
                }

                SET_TMDS_RX2_HDCP2_LC_INIT_RECEIVED();

                // Set HDCP 2.2 State to Compute L'
                SET_TMDS_RX2_HDCP2_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_L_PRIME);

                break;

            case _HDCP_2_2_SKE_SEND_EKS:

                // Calculate Dkey 2
                ScalerHdcp2DkeyCalculate_EXINT0(_HDCP_2_2_DKEY_2, g_pucTmdsRx2Hdcp2Rtx, g_pucTmdsRx2Hdcp2Rrx, g_pucTmdsRx2Hdcp2Km, g_pucTmdsRx2Hdcp2Rn);

                // Save EDkeyKs from Write SRAM to FW
                ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(0x01, 16, g_pucHdcp2EDkeyKs);

                // Save Riv from Write SRAM to FW
                ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(0x11, 8, g_pucHdcp2Riv);

                // Decode Ks
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; ++pData_EXINT[0])
                {
                    g_pucHdcp2Ks[pData_EXINT[0]] = g_pucHdcp2EDkeyKs[pData_EXINT[0]] ^ ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]));
                }

                for(pData_EXINT[0] = 8; pData_EXINT[0] < 16; ++pData_EXINT[0])
                {
                    g_pucHdcp2Ks[pData_EXINT[0]] = g_pucHdcp2EDkeyKs[pData_EXINT[0]] ^ (ScalerGetByte_EXINT((P63_81_HDCP_AES_OUT_15 + pData_EXINT[0])) ^ g_pucTmdsRx2Hdcp2Rrx[pData_EXINT[0] - 8]);
                }

                SET_TMDS_RX2_HDCP2_AUTHENTICATION_DONE();

                // Enable HDMI Link Integrity Check & Clear BCH Error Flag
                ScalerSetByte_EXINT(P71_C9_HDMI_AP, _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1);
                pData_EXINT[0] = ((ScalerGetByte_EXINT(P71_CA_HDMI_DP) & (~_BIT7)) | _BIT7 | _BIT6);
                ScalerSetByte_EXINT(P71_C9_HDMI_AP, _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1);
                ScalerSetByte_EXINT(P71_CA_HDMI_DP, pData_EXINT[0]);

                SET_TMDS_RX2_HDCP2_AUTH_STATE(_HDCP_2_2_STATE_AUTHENTICATED);

                // Enable Decryption
                for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; ++pData_EXINT[0])
                {
                    g_pucHdcp2InputCipher[pData_EXINT[0]] = g_pucHdcp2Ks[pData_EXINT[0]] ^ g_stRxHdcp2DownLoadKeyType.pucHdcp2Lc[pData_EXINT[0]];
                }

                // Enable AES Decryption Cipher
                ScalerTMDSRx2Hdcp2AesOnlineCtrl_EXINT0(g_pucHdcp2Riv, g_pucHdcp2InputCipher);

                SET_TMDS_RX2_HDCP2_SKE_SEND_EKS_RECEIVED();

                // Set HDCP 2.2 State to Compute L'
                SET_TMDS_RX2_HDCP2_AUTH_STATE(_HDCP_2_2_STATE_COMPUTE_KS);

                break;

            default:
                break;
        }

        ScalerSetByte_EXINT(P2D_21_HDCP_MSGWAP, g_pucHdcp2BackUp[0]);
    }

    // Source Has Read Msg Done IRQ
    if((ScalerGetBit_EXINT(P2D_35_HDCP_I2C_CTRL_7, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P2D_36_HDCP_I2C_CTRL_8, _BIT1) == _BIT1))
    {
        // Clear Read Msg Done Flag
        ScalerSetBit_EXINT(P2D_36_HDCP_I2C_CTRL_8, ~_BIT1, _BIT1);

        // Disable Read Msg Done IRQ
        ScalerSetBit_EXINT(P2D_35_HDCP_I2C_CTRL_7, ~_BIT1, 0x00);

        // Start Pairing AES Calculate
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; ++pData_EXINT[0])
        {
            if(pData_EXINT[0] < 8)
            {
                g_pucHdcp2M[pData_EXINT[0]] = g_pucTmdsRx2Hdcp2Rtx[pData_EXINT[0]];
            }
            else
            {
                g_pucHdcp2M[pData_EXINT[0]] = g_pucTmdsRx2Hdcp2Rrx[pData_EXINT[0] - 8];
            }
        }

        // AES Cipher Calculate Ekh[km]
        ScalerHdcp2RxAesOfflineCtrl_EXINT0(g_pucHdcp2M, g_pucHdcp2Kh);

        // Calculate Ekh[km] = kh AES m XOR Km
        for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; ++pData_EXINT[0])
        {
            g_pucHdcp2EkhKm[pData_EXINT[0]] = ScalerGetByte_EXINT(P63_81_HDCP_AES_OUT_15 + pData_EXINT[0]) ^ g_pucTmdsRx2Hdcp2Km[pData_EXINT[0]];
        }

        ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(0x01, g_pucHdcp2EkhKm, 16);

        // Load AKE Send Pairing Info
        ScalerTMDSRx2Hdcp2SetRdMsgIDCode_EXINT0(_HDCP_2_2_AKE_SEND_PAIRING_INFO);

        // Set Message Size = 0x11
        ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
        ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x70);
        ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x11);
        ScalerSetByte_EXINT(P71_C3_HDCP_AP, 0x71);
        ScalerSetByte_EXINT(P71_C4_HDCP_DP, 0x00);
        ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2ResetProc(void)
{
    // Disable Read Msg Done IRQ
    ScalerSetBit(P2D_35_HDCP_I2C_CTRL_7, ~_BIT1, 0x00);

    // Clear RxStatus REAUTH_REQ
    ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
    ScalerSetDataPortBit(P71_C3_HDCP_AP, _P71_C4_PT_70_PORT_PAGE71_HDCP2_STATUS1, ~_BIT3, 0x00);
    ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

    // Disable Link Interity Check
    ScalerSetDataPortBit(P71_C9_HDMI_AP, _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1, ~(_BIT7 | _BIT6), 0x00);

    // Reset Authenticated FSM
    ScalerSetByte(P2D_28_HDCP_I2C_CTRL_2, 0x00);
    ScalerSetBit(P2D_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

    // Cancel HDCP 2.2 Re-Auth Timer Event
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);

    CLR_TMDS_RX2_HDCP2_AUTHENTICATION_DONE();
    CLR_TMDS_RX2_HDCP2_AKE_INIT_RECEIVED();
    CLR_TMDS_RX2_HDCP2_AKE_NO_STORED_KM_RECEIVED();
    CLR_TMDS_RX2_HDCP2_AKE_STORED_KM_RECEIVED();
    CLR_TMDS_RX2_HDCP2_LC_INIT_RECEIVED();
    CLR_TMDS_RX2_HDCP2_SKE_SEND_EKS_RECEIVED();
}

//--------------------------------------------------
// Description  : HDCP 2.2 Reset Proc in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2ResetProc_EXINT0(void) using 1
{
    // Disable Read Msg Done IRQ
    ScalerSetBit_EXINT(P2D_35_HDCP_I2C_CTRL_7, ~_BIT1, 0x00);

    // Clear RxStatus REAUTH_REQ
    ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
    ScalerSetByte_EXINT(P71_C3_HDCP_AP, _P71_C4_PT_70_PORT_PAGE71_HDCP2_STATUS1);
    ScalerSetBit_EXINT(P71_C4_HDCP_DP, ~_BIT3, 0x00);
    ScalerSetBit_EXINT(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

    // Disable Link Interity Check
    ScalerSetByte_EXINT(P71_C9_HDMI_AP, _P71_CA_PT_63_PORT_PAGE71_HDMI_PEAC1);
    ScalerSetBit_EXINT(P71_CA_HDMI_DP, ~(_BIT7 | _BIT6), 0x00);

    // Reset Authenticated FSM
    ScalerSetByte_EXINT(P2D_28_HDCP_I2C_CTRL_2, 0x00);
    ScalerSetBit_EXINT(P2D_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);

    // Cancel HDCP 2.2 Re-Auth Timer Event
    ScalerTimerCancelTimerEvent_EXINT0(_SCALER_TIMER_EVENT_RX2_HDCP2_REAUTH);

    CLR_TMDS_RX2_HDCP2_AUTHENTICATION_DONE();
    CLR_TMDS_RX2_HDCP2_AKE_INIT_RECEIVED();
    CLR_TMDS_RX2_HDCP2_AKE_NO_STORED_KM_RECEIVED();
    CLR_TMDS_RX2_HDCP2_AKE_STORED_KM_RECEIVED();
    CLR_TMDS_RX2_HDCP2_LC_INIT_RECEIVED();
    CLR_TMDS_RX2_HDCP2_SKE_SEND_EKS_RECEIVED();
}

//--------------------------------------------------
// Description  : HDCP 2.2 Down Load Value in INT
// Input Value  : usSubAddr == > start address, usLength == > key Length,
//                pReadArray == > Key Array
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2DownLoadWriteSRAMValue_EXINT0(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray) using 1
{
    ScalerSetByte_EXINT(P2D_21_HDCP_MSGWAP, ucSubAddr);

    // Load Value To FW
    for(pData_EXINT[0] = ucSubAddr; pData_EXINT[0] < (ucSubAddr + ucLength); pData_EXINT[0]++)
    {
        pucReadArray[pData_EXINT[0] - ucSubAddr] = ScalerGetByte_EXINT(P2D_22_HDCP_MSGWDP);
    }
}


#if(_HDCP_2_2_ERRATA_TEST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDCP 2.2 On-Line AES Ctrl for Rx2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2AesOnlineCtrl(BYTE *pucInputArray, BYTE *pucCipherArray)
{
    memcpy((volatile BYTE xdata *)P2D_00_HDCP_AES_CIPHER_KEY_15, pucCipherArray, 16);
    memcpy((volatile BYTE xdata *)P2D_2D_HDCP_I2C_CTRL_RIV7, pucInputArray, 8);

    // Riv from FW
    ScalerSetBit(P2D_29_HDCP_I2C_CTRL_3, ~_BIT7, _BIT7);

    // Set HW to Authenticated State
    ScalerSetByte(P2D_28_HDCP_I2C_CTRL_2, 0x10);
    ScalerSetBit(P2D_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message Value
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2SetRdMsgValue(WORD usAddress, BYTE *pucReadArray, WORD usLength)
{
    WORD usTemp = 0;

    ScalerSetBit(P2D_23_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), usAddress >> 8);
    ScalerSetByte(P2D_24_HDCP_MSGRAP_L, usAddress);

    // Set HDCP 2 Read SRAM Message Value, Disable HDCP 2 Read SRAM auto Increase
    for(usTemp = usAddress; usTemp < (usAddress + usLength); usTemp++)
    {
        ScalerSetByte(P2D_25_HDCP_MSGRDP, pucReadArray[usTemp - usAddress]);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message ID Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2SetRdMsgIDCode(BYTE ucValue)
{
    ScalerSetBit(P2D_23_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte(P2D_24_HDCP_MSGRAP_L, 0x00);
    ScalerSetByte(P2D_25_HDCP_MSGRDP, ucValue);
}

//--------------------------------------------------
// Description  : Capture Kpub/Km
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx2Hdcp2CaptureKpubKm(void)
{
    BYTE pucKpubKm[128];
    memset(pucKpubKm, 0, sizeof(pucKpubKm));

    // Save Transmitter Ekpub[km] to FW
    ScalerSetByte(P2D_21_HDCP_MSGWAP, 0x01);

    for(pData[0] = 0; pData[0] < 128; ++pData[0])
    {
        pucKpubKm[pData[0]] = g_stRxHdcp2DownLoadKeyType.pucHdcp2KpubKm[pData[0]];

        DebugMessageHDCP2("[D2]Ekpub(km)", pucKpubKm[pData[0]]);
    }

    // Decrypt Ekpub[km]
    return (ScalerHdcp2RxRsaCalculate(pucKpubKm) == _TRUE);
}

//--------------------------------------------------
// Description  : Calculate Km/Kh
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2CalculateKmKh(void)
{
    BYTE pucSHA256[32];
    memset(pucSHA256, 0, sizeof(pucSHA256));

    BYTE pucM[16];
    memset(pucM, 0, sizeof(pucM));

    // Load H prime to Read SRAM, AKE Send H PRIME Message ID = 0x07
    ScalerTMDSRx2Hdcp2SetRdMsgIDCode(_HDCP_2_2_AKE_SEND_H_PRIME);

    memcpy(pucSHA256, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);

    for(pData[0] = 0; pData[0] < 32; pData[0]++)
    {
        DebugMessageHDCP2("[D2]H_prime", pucSHA256[pData[0]]);
    }

    // Load Km to Read SRAM
    ScalerTMDSRx2Hdcp2SetRdMsgValue(0x01, pucSHA256, 32);

    // Set Message Size = 0x21
    ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, _BIT0);
    ScalerSetDataPortByte(P71_C3_HDCP_AP, _P71_C4_PT_70_PORT_PAGE71_HDCP2_STATUS1, 0x21);
    ScalerSetDataPortByte(P71_C3_HDCP_AP, _P71_C4_PT_71_PORT_PAGE71_HDCP2_STATUS2, 0x00);
    ScalerSetBit(P2D_3B_I2C_DUMMY_0, ~_BIT0, 0x00);

    // Enable HDCP2 Source Read Done IRQ
    ScalerSetBit(P2D_36_HDCP_I2C_CTRL_8, ~_BIT1, _BIT1);
    ScalerSetBit(P2D_35_HDCP_I2C_CTRL_7, ~_BIT1, _BIT1);

    // Start Pairing AES Calculate
    for(pData[0] = 0; pData[0] < 16; ++pData[0])
    {
        if(pData[0] < 8)
        {
            pucM[pData[0]] = g_pucTmdsRx2Hdcp2Rtx[pData[0]];
        }
        else
        {
            pucM[pData[0]] = g_pucTmdsRx2Hdcp2Rrx[pData[0] - 8];
        }
    }

    // AES Cipher Calculate Ekh[km]
    ScalerHdcp2RxAesOfflineCtrl(pucM, g_pucHdcp2Kh);

    // Calculate Ekh[km] = kh AES m XOR Km
    for(pData[0] = 0; pData[0] < 16; ++pData[0])
    {
        g_pucHdcp2Kh[pData[0]] = ScalerGetByte(P63_81_HDCP_AES_OUT_15 + pData[0]) ^ g_pucTmdsRx2Hdcp2Km[pData[0]];

        DebugMessageHDCP2("[D2]Ekh(km)", g_pucHdcp2Kh[pData[0]]);
    }
}
#endif

//--------------------------------------------------
// Description  : HDCP 2.2 On-Line AES Ctrl in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2AesOnlineCtrl_EXINT0(BYTE *pucInputArray, BYTE *pucCipherArray) using 1
{
    for(pData_EXINT[0] = 0; pData_EXINT[0] < 16; pData_EXINT[0]++)
    {
        ScalerSetByte_EXINT(P2D_00_HDCP_AES_CIPHER_KEY_15 + pData_EXINT[0], pucCipherArray[pData_EXINT[0]]);
    }

    for(pData_EXINT[0] = 0; pData_EXINT[0] < 8; pData_EXINT[0]++)
    {
        ScalerSetByte_EXINT(P2D_2D_HDCP_I2C_CTRL_RIV7 + pData_EXINT[0], pucInputArray[pData_EXINT[0]]);
    }

    // Riv from FW
    ScalerSetBit_EXINT(P2D_29_HDCP_I2C_CTRL_3, ~_BIT7, _BIT7);

    // Set HW to Authenticated State
    ScalerSetByte_EXINT(P2D_28_HDCP_I2C_CTRL_2, 0x10);
    ScalerSetBit_EXINT(P2D_29_HDCP_I2C_CTRL_3, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message Value in INT
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2SetRdMsgValue_EXINT0(WORD usAddress, BYTE *pucReadArray, WORD usLength) using 1
{
    WORD usTemp = 0;

    ScalerSetBit_EXINT(P2D_23_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), usAddress >> 8);
    ScalerSetByte_EXINT(P2D_24_HDCP_MSGRAP_L, usAddress);

    // Set HDCP 2 Read SRAM Message Value, Disable HDCP 2 Read SRAM auto Increase
    for(usTemp = usAddress; usTemp < (usAddress + usLength); usTemp++)
    {
        ScalerSetByte_EXINT(P2D_25_HDCP_MSGRDP, pucReadArray[usTemp - usAddress]);
    }
}

//--------------------------------------------------
// Description  : HDCP 2.2 Set Read Message ID Code
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx2Hdcp2SetRdMsgIDCode_EXINT0(BYTE ucValue) using 1
{
    ScalerSetBit_EXINT(P2D_23_HDCP_MSGRAP_H, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte_EXINT(P2D_24_HDCP_MSGRAP_L, 0x00);
    ScalerSetByte_EXINT(P2D_25_HDCP_MSGRDP, ucValue);
}
#endif // End of #if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT))
#endif // End of #if(_TMDS_HDCP_2_2_SUPPORT == _ON)
