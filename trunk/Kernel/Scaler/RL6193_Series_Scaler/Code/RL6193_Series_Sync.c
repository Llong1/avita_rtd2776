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
// ID Code      : RL6193_Series_Sync.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

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

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
WORD ScalerSyncGetInputPixelClk(EnumSourceSearchPort enumSourceSearchPort);

#if(_DIGITAL_PORT_SUPPORT == _ON)
void ScalerSyncHdcpEnableDownLoadKey(bit bEnable);
void ScalerSyncHdcpDownLoadBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray);
void ScalerSyncHdcpDownLoadKey(WORD usLength, BYTE *pucReadArray);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Let Upper Layer Get I-domain Pixel Clk
// Input Value  : enumSourceSearchPort --> target port
// Output Value : Input Pixel Clk (in 0.1MHz)
//--------------------------------------------------
WORD ScalerSyncGetInputPixelClk(EnumSourceSearchPort enumSourceSearchPort)
{
    switch(enumSourceSearchPort)
    {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
        case _A0_INPUT_PORT:
            return GET_A0_INPUT_PIXEL_CLK();
#endif


#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
        case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        case _D6_INPUT_PORT:
#endif

#if(_D0_HDMI_2_0_SUPPORT == _ON)
            // Check 420 status
            if(ScalerGetBit(P31_20_YUV420_TO_YUV422_D0, _BIT7) == _BIT7)
            {
                return (GET_D0_INPUT_PIXEL_CLK() << 1);
            }
            else
#endif
            {
                return GET_D0_INPUT_PIXEL_CLK();
            }
#endif


#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

#if(_D1_HDMI_2_0_SUPPORT == _ON)
            // Check 420 status
            if(ScalerGetBit(P31_21_YUV420_TO_YUV422_D1, _BIT7) == _BIT7)
            {
                return (GET_D1_INPUT_PIXEL_CLK() << 1);
            }
            else
#endif
            {
                return GET_D1_INPUT_PIXEL_CLK();
            }
#endif


#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            if(ScalerTMDSRx2GetDualDVIMode() == _TRUE)
            {
                return (GET_D2_INPUT_PIXEL_CLK() << 1);
            }
#endif
            return GET_D2_INPUT_PIXEL_CLK();
#endif


#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
        case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            if(ScalerTMDSRx3GetDualDVIMode() == _TRUE)
            {
                return (GET_D3_INPUT_PIXEL_CLK() << 1);
            }
#endif
            return GET_D3_INPUT_PIXEL_CLK();
#endif // End of #if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))


#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(ScalerTMDSRx4GetDualDVIMode() == _TRUE)
            {
                return (GET_D4_INPUT_PIXEL_CLK() << 1);
            }
#endif
            return GET_D4_INPUT_PIXEL_CLK();
#endif // End of #if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))


#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
        case _D5_INPUT_PORT:

            return GET_D5_INPUT_PIXEL_CLK();
#endif

        default:
            break;
    }

    return ~0;
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable/Disable DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpEnableDownLoadKey(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
#if((_D0_TMDS_SUPPORT == _ON) || (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
        // Suspend Key Calculation before load key
        ScalerSetBit(P2_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P2_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Switch MAC to Hdmi
        ScalerSetBit(PB_00_HD_DP_SEL, ~_BIT0, _BIT0);

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P2_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P2_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if((_D1_TMDS_SUPPORT == _ON) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
        // Suspend Key Calculation before load key
        ScalerSetBit(P70_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P70_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Switch MAC to Hdmi
        ScalerSetBit(PB0_00_HD_DP_SEL, ~_BIT0, _BIT0);

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P70_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P70_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        // Suspend Key Calculation before load key
        ScalerSetBit(P71_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P71_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P71_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P71_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        // Suspend Key Calculation before load key
        ScalerSetBit(P72_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P72_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P72_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P72_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_D4_TMDS_SUPPORT == _ON)
        // Suspend Key Calculation before load key
        ScalerSetBit(P73_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P73_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P73_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P73_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_D5_TMDS_SUPPORT == _ON)
        // Suspend Key Calculation before load key
        ScalerSetBit(P74_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P74_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P74_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P74_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif
    }
    else if(bEnable == _DISABLE)
    {
#if((_D0_TMDS_SUPPORT == _ON) || (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))

        // Disable Key download port
        ScalerSetBit(P2_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P2_C0_HDCP_CR, ~_BIT7, _BIT7);

        // Release Key Calculation
        ScalerSetBit(P2_AE_TMDS_RPS, ~_BIT1, _BIT1);
#endif

#if((_D1_TMDS_SUPPORT == _ON) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))

        // Disable Key download port
        ScalerSetBit(P70_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P70_C0_HDCP_CR, ~_BIT7, _BIT7);

        // Release Key Calculation
        ScalerSetBit(P70_AE_TMDS_RPS, ~_BIT1, _BIT1);
#endif

#if(_D2_TMDS_SUPPORT == _ON)

        // Disable Key download port
        ScalerSetBit(P71_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P71_C0_HDCP_CR, ~_BIT7, _BIT7);

        // Release Key Calculation
        ScalerSetBit(P71_AE_TMDS_RPS, ~_BIT1, _BIT1);
#endif

#if(_D3_TMDS_SUPPORT == _ON)

        // Disable Key download port
        ScalerSetBit(P72_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P72_C0_HDCP_CR, ~_BIT7, _BIT7);

        // Release Key Calculation
        ScalerSetBit(P72_AE_TMDS_RPS, ~_BIT1, _BIT1);
#endif

#if(_D4_TMDS_SUPPORT == _ON)

        // Disable Key download port
        ScalerSetBit(P73_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P73_C0_HDCP_CR, ~_BIT7, _BIT7);

        // Release Key Calculation
        ScalerSetBit(P73_AE_TMDS_RPS, ~_BIT1, _BIT1);
#endif

#if(_D5_TMDS_SUPPORT == _ON)

        // Disable Key download port
        ScalerSetBit(P74_C0_HDCP_CR, ~_BIT1, 0x00);

        // New Cipher Mode
        ScalerSetBit(P74_C0_HDCP_CR, ~_BIT7, _BIT7);

        // Release Key Calculation
        ScalerSetBit(P74_AE_TMDS_RPS, ~_BIT1, _BIT1);
#endif
    }
}

//--------------------------------------------------
// Description  : DownLoad HDCP BKsv
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadBKsv(BYTE ucSubAddr, BYTE ucLength, BYTE *pucReadArray)
{
    for(pData[0] = ucSubAddr; pData[0] < ucLength; pData[0]++)
    {
#if(_D0_TMDS_SUPPORT == _ON)
        ScalerSetDataPortByte(P2_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_D1_TMDS_SUPPORT == _ON)
        ScalerSetDataPortByte(P70_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_D2_TMDS_SUPPORT == _ON)
        ScalerSetDataPortByte(P71_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_D3_TMDS_SUPPORT == _ON)
        ScalerSetDataPortByte(P72_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_D4_TMDS_SUPPORT == _ON)
        ScalerSetDataPortByte(P73_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_D5_TMDS_SUPPORT == _ON)
        ScalerSetDataPortByte(P74_C3_HDCP_AP, pData[0], pucReadArray[pData[0]]);
#endif

#if(_DP_SUPPORT == _ON)
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        ScalerDpRx0SetDpcdValue(0x06, 0x80, (0x00 | pData[0]), pucReadArray[pData[0]]);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        ScalerDpRx1SetDpcdValue(0x06, 0x80, (0x00 | pData[0]), pucReadArray[pData[0]]);
#endif

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        // Enable DP Link Integrity Enable
        ScalerSetBit(PB_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        // Enable DP Link Integrity Enable
        ScalerSetBit(PB0_1B_HDCP_INTGT_VRF, ~_BIT7, _BIT7);
#endif
#endif
        g_pucHdcpBksvBackup[pData[0]] = pucReadArray[pData[0]];
    }

    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[0]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[1]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[2]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[3]);
    DebugMessageDigital("8. HDCP Bksv Backup", g_pucHdcpBksvBackup[4]);
}

//--------------------------------------------------
// Description  : DownLoad HDCP Key
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerSyncHdcpDownLoadKey(WORD usLength, BYTE *pucReadArray)
{
#if((_D0_TMDS_SUPPORT == _ON) || (_D0_INPUT_PORT_TYPE == _D0_DP_PORT))
    ScalerWrite(P2_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if((_D1_TMDS_SUPPORT == _ON) || (_D1_INPUT_PORT_TYPE == _D1_DP_PORT))
    ScalerWrite(P70_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if(_D2_TMDS_SUPPORT == _ON)
    ScalerWrite(P71_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if(_D3_TMDS_SUPPORT == _ON)
    ScalerWrite(P72_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if(_D4_TMDS_SUPPORT == _ON)
    ScalerWrite(P73_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if(_D5_TMDS_SUPPORT == _ON)
    ScalerWrite(P74_C1_HDCP_DKAP, usLength, pucReadArray, _NON_AUTOINC);
#endif
}
#endif
