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
// ID Code      : RL6410_Series_Sync.c No.0000
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
            return GET_D0_INPUT_PIXEL_CLK();
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
        case _D1_INPUT_PORT:

            return GET_D1_INPUT_PIXEL_CLK();
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
        case _D2_INPUT_PORT:

#if(_D2_HDMI_2_0_SUPPORT == _ON)
            // Check 420 status
            if(ScalerGetBit(P31_32_YUV420_TO_YUV422_D2, _BIT7) == _BIT7)
            {
                return (GET_D2_INPUT_PIXEL_CLK() << 1);
            }
            else
#endif
            {
                return GET_D2_INPUT_PIXEL_CLK();
            }
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
        case _D3_INPUT_PORT:

#if(_D3_HDMI_2_0_SUPPORT == _ON)
            // Check 420 status
            if(ScalerGetBit(P31_33_YUV420_TO_YUV422_D3, _BIT7) == _BIT7)
            {
                return (GET_D3_INPUT_PIXEL_CLK() << 1);
            }
            else
#endif
            {
                return GET_D3_INPUT_PIXEL_CLK();
            }
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
        case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(ScalerTMDSRx4GetDualDVIMode() == _TRUE)
            {
                return (GET_D4_INPUT_PIXEL_CLK() << 1);
            }
#endif
            return GET_D4_INPUT_PIXEL_CLK();
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)


#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
        case _D5_INPUT_PORT:

            return GET_D5_INPUT_PIXEL_CLK();
#endif

#if(_D7_INPUT_PORT_TYPE != _D7_NO_PORT)
        case _D7_INPUT_PORT:

            switch(GET_D7_SWITCH_SELECT())
            {
                case _D0_INPUT_PORT:
                    return GET_D0_INPUT_PIXEL_CLK();

                case _D1_INPUT_PORT:
                    return GET_D1_INPUT_PIXEL_CLK();

                default:
                    // dual DP
                    return GET_D0_INPUT_PIXEL_CLK() * 2;
            }
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
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        // Enable HDCP Block and Key download port
        ScalerSetBit(PB_17_DP_HDCP_CONTROL, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Set Km Clock to Xtal Clock
        ScalerSetBit(PB_1A_HDCP_IRQ, ~_BIT3, 0x00);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        // Enable HDCP Block and Key download port
        ScalerSetBit(PB0_17_DP_HDCP_CONTROL, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

        // Set Km Clock to Xtal Clock
        ScalerSetBit(PB0_1A_HDCP_IRQ, ~_BIT3, 0x00);
#endif

#if(_D2_TMDS_SUPPORT == _ON)

        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P71_C3_HDCP_AP, _P71_C4_PT_40_PORT_PAGE71_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P71_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P71_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block Clk
        ScalerSetBit(P71_C2_HDCP_PCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P71_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Disable HDCP 2.2 Function
        ScalerSetBit(P2D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P2D_36_HDCP_I2C_CTRL_8, ~_BIT0, _BIT0);
        ScalerSetBit(P2D_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);
#endif

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P71_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_D3_TMDS_SUPPORT == _ON)

        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P72_C3_HDCP_AP, _P72_C4_PT_40_PORT_PAGE72_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P72_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P72_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block Clk
        ScalerSetBit(P72_C2_HDCP_PCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P72_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Disable HDCP 2.2 Function
        ScalerSetBit(P2E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P2E_36_HDCP_I2C_CTRL_8, ~_BIT0, _BIT0);
        ScalerSetBit(P2E_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);
#endif

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P72_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_D4_TMDS_SUPPORT == _ON)

        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P73_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P73_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block Clk
        ScalerSetBit(P73_C2_HDCP_PCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P73_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Disable HDCP 2.2 Function
        ScalerSetBit(P6D_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P6D_36_HDCP_I2C_CTRL_8, ~_BIT0, _BIT0);
        ScalerSetBit(P6D_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);
#endif

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P73_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif

#if(_D5_TMDS_SUPPORT == _ON)

        // Disable HDMI Repeater Function
        ScalerSetDataPortBit(P74_C3_HDCP_AP, _P74_C4_PT_40_PORT_PAGE74_BCAPS, ~_BIT6, 0x00);

        // Suspend Key Calculation before load key
        ScalerSetBit(P74_AE_TMDS_RPS, ~(_BIT1 | _BIT0), _BIT0);

        // Manual Select Key SRAM Access Right
        ScalerSetBit(P74_A9_TMDS_ABC0, ~_BIT4, 0x00);

        // Enable HDCP Block Clk
        ScalerSetBit(P74_C2_HDCP_PCR, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Enable HDCP Block, and Key download port
        ScalerSetBit(P74_C0_HDCP_CR, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
        // Disable HDCP 2.2 Function
        ScalerSetBit(P6E_26_HDCP_I2C_CTRL_0, ~_BIT7, 0x00);

        // Enable HDCP 2.2 IRQ
        ScalerSetBit(P6E_36_HDCP_I2C_CTRL_8, ~_BIT0, _BIT0);
        ScalerSetBit(P6E_35_HDCP_I2C_CTRL_7, ~_BIT0, _BIT0);
#endif

        // Set Km Clock to EMCU Clock
        ScalerSetBit(P74_AC_TMDS_Z0CC2, ~_BIT4, 0x00);
#endif
    }
    else if(bEnable == _DISABLE)
    {
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        // Disable Key download port
        ScalerSetBit(PB_17_DP_HDCP_CONTROL, ~_BIT0, 0x00);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        // Disable Key download port
        ScalerSetBit(PB0_17_DP_HDCP_CONTROL, ~_BIT0, 0x00);
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
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    ScalerWrite(PB_18_DP_HDCP_DOWNLOAD_PORT, usLength, pucReadArray, _NON_AUTOINC);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    ScalerWrite(PB0_18_DP_HDCP_DOWNLOAD_PORT, usLength, pucReadArray, _NON_AUTOINC);
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
