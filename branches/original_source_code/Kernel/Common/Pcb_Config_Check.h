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
// ID Code      : Pcb_Config_Check.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PCB_CONFIG_CHECK_H__
#define __PCB_CONFIG_CHECK_H__

///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// PCB DP Lane Swap Check
//--------------------------------------------------
#if(_HW_DP_LANE_SWAP_SUPPORT == _OFF)
#if((_D0_DP_PCB_LANE0_MAPPING != _DP_SCALER_LANE0) ||\
    (_D0_DP_PCB_LANE1_MAPPING != _DP_SCALER_LANE1) ||\
    (_D0_DP_PCB_LANE2_MAPPING != _DP_SCALER_LANE2) ||\
    (_D0_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3) ||\
    (_D1_DP_PCB_LANE0_MAPPING != _DP_SCALER_LANE0) ||\
    (_D1_DP_PCB_LANE1_MAPPING != _DP_SCALER_LANE1) ||\
    (_D1_DP_PCB_LANE2_MAPPING != _DP_SCALER_LANE2) ||\
    (_D1_DP_PCB_LANE3_MAPPING != _DP_SCALER_LANE3))
#warning "DP Lane Swap Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// PCB DP PN Swap Check
//--------------------------------------------------
#if(_HW_DP_PN_SWAP_SUPPORT == _OFF)
#if((_D0_DP_PCB_PN_SWAP == _ON) || (_D1_DP_PCB_PN_SWAP == _ON))
#warning "DP PN Swap Can Not Be Supported!!!"
#endif
#endif

//--------------------------------------------------
// DP D7 Port Check
//--------------------------------------------------
#if(_SCALER_TYPE == _RL6193_SERIES)
#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
#warning "_D7_DP_PORT Can Not Be Supported!!!"
#endif
#endif

#if(_D7_INPUT_PORT_TYPE == _D7_DP_PORT)
#if((_D0_INPUT_PORT_TYPE != _D0_DP_PORT) || (_D1_INPUT_PORT_TYPE != _D1_DP_PORT))
#warning "_D0_INPUT_PORT_TYPE & _D1_INPUT_PORT_TYPE Should Be DP Port!!!"
#endif
#endif

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D7_INPUT_PORT_TYPE == _D7_DP_PORT))
#warning "_D6_INPUT_PORT_TYPE & _D7_INPUT_PORT_TYPE Can Not Be Both Supported!!!"
#endif

//--------------------------------------------------
// DDC Mapping Check
//--------------------------------------------------
#if(_DDC_CHANNEL_SWITCH_SUPPORT == _OFF)
#if(((_D0_DDC_CHANNEL_SEL != _NO_DDC) && (_D0_DDC_CHANNEL_SEL != _DDC0)) ||\
    ((_D1_DDC_CHANNEL_SEL != _NO_DDC) && (_D1_DDC_CHANNEL_SEL != _DDC1)) ||\
    ((_D2_DDC_CHANNEL_SEL != _NO_DDC) && (_D2_DDC_CHANNEL_SEL != _DDC2)) ||\
    ((_D3_DDC_CHANNEL_SEL != _NO_DDC) && (_D3_DDC_CHANNEL_SEL != _DDC3)) ||\
    ((_D4_DDC_CHANNEL_SEL != _NO_DDC) && (_D4_DDC_CHANNEL_SEL != _DDC4)) ||\
    ((_D5_DDC_CHANNEL_SEL != _NO_DDC) && (_D5_DDC_CHANNEL_SEL != _DDC5)))
#warning "D0 or D1 or D2 or D3 or D4 or D5 Select Wrong DDC Channel!!!"
#endif
#endif

//--------------------------------------------------
// Input Port Type & DDC Channel Status Check
//--------------------------------------------------
#if(((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_D0_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_D1_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_D2_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_D3_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_D4_DDC_CHANNEL_SEL == _NO_DDC)) ||\
     ((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_D5_DDC_CHANNEL_SEL == _NO_DDC)))
#warning "When D0 or D1 or D2 or D3 or D4 or D5 Input Port Type Select not _NO_PORT, DDC Channel Can't be _NO_DDC!!!"
#endif

//--------------------------------------------------
// Dual Link DVI Check
//--------------------------------------------------
#if(_HW_DUAL_LINK_DVI_SUPPORT_PORT == _DUAL_LINK_DVI_NONE)
#if(_DUAL_DVI_SUPPORT == _ON)
#warning "Dual Link DVI Port Can't Use in This Project!!!"
#endif
#elif(_HW_DUAL_LINK_DVI_SUPPORT_PORT == _DUAL_LINK_DVI_D2)
#if((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
#warning "D3 or D4 Input Port Can't be Dual DVI Port!!!"
#endif
#elif(_HW_DUAL_LINK_DVI_SUPPORT_PORT == _DUAL_LINK_DVI_D4)
#if((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
#warning "D2 or D3 Input Port Can't be Dual DVI Port!!!"
#endif
#elif(_HW_DUAL_LINK_DVI_SUPPORT_PORT == _DUAL_LINK_DVI_D2_D3_D4)
#if(((_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT) && (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)) ||\
     ((_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) && (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)))
#warning "D2&D3 or D3&D4 Input Port Can't both be Dual DVI Port!!!"
#endif
#endif

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#warning "_D3_INPUT_PORT_TYPE Should Be _D3_NO_PORT!!!"
#endif

#if(_D3_DDC_CHANNEL_SEL == _NO_DDC)
#warning "When D2 Input Port Type is Dual Link DVI Port, D3 DDC Channel Can't be _NO_DDC!!!"
#endif

#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#warning "_D4_INPUT_PORT_TYPE Should Be _D4_NO_PORT!!!"
#endif

#if(_D4_DDC_CHANNEL_SEL == _NO_DDC)
#warning "When D3 Input Port Type is Dual Link DVI Port, D4 DDC Channel Can't be _NO_DDC!!!"
#endif

#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#warning "_D5_INPUT_PORT_TYPE Should Be _D5_NO_PORT!!!"
#endif

#if(_D5_DDC_CHANNEL_SEL == _NO_DDC)
#warning "When D4 Input Port Type is Dual Link DVI Port, D5 DDC Channel Can't be _NO_DDC!!!"
#endif

#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

//--------------------------------------------------
// Type-C && Port Controller Setting Check
//--------------------------------------------------
#if((_D0_DP_TYPE_C_SUPPORT == _ON) && (_D0_DP_TYPE_C_PORT_CONTROLLER_TYPE == _PORT_CONTOLLER_NONE))
#warning "'_D0_DP_TYPE_C_PORT_CONTROLLER_TYPE' can't select '_PORT_CONTOLLER_NONE' if '_D0_DP_CONNECTOR_TYPE' selected '_DP_CONNECTOR_TYPEC'!!!"
#endif

#if((_D1_DP_TYPE_C_SUPPORT == _ON) && (_D1_DP_TYPE_C_PORT_CONTROLLER_TYPE == _PORT_CONTOLLER_NONE))
#warning "'_D1_DP_TYPE_C_PORT_CONTROLLER_TYPE' can't select '_PORT_CONTOLLER_NONE' if '_D1_DP_CONNECTOR_TYPE' selected '_DP_CONNECTOR_TYPEC'!!!"
#endif

#if((_D6_DP_TYPE_C_SUPPORT == _ON) && (_D6_DP_TYPE_C_PORT_CONTROLLER_TYPE == _USB_HUB_USER))
#warning "'_D6_DP_TYPE_C_PORT_CONTROLLER_TYPE' can't select '_PORT_CONTOLLER_NONE' if '_D6_DP_CONNECTOR_TYPE' selected '_DP_CONNECTOR_TYPEC'!!!"
#endif

#if((_D0_DP_TYPE_C_SUPPORT == _OFF) && (_D0_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE))
#warning "'_D0_DP_TYPE_C_USB_HUB_TYPE' should be select '_USB_HUB_NONE' if '_D0_DP_CONNECTOR_TYPE' not selected '_DP_CONNECTOR_TYPEC'!!!"
#endif

#if((_D1_DP_TYPE_C_SUPPORT == _OFF) && (_D1_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE))
#warning "'_D1_DP_TYPE_C_USB_HUB_TYPE' should be select '_USB_HUB_NONE' if '_D1_DP_CONNECTOR_TYPE' not selected '_DP_CONNECTOR_TYPEC'!!!"
#endif

#if((_D6_DP_TYPE_C_SUPPORT == _OFF) && (_D6_DP_TYPE_C_USB_HUB_TYPE != _USB_HUB_NONE))
#warning "'_D6_DP_TYPE_C_USB_HUB_TYPE' should be select '_USB_HUB_NONE' if '_D6_DP_CONNECTOR_TYPE' not selected '_DP_CONNECTOR_TYPEC'!!!"
#endif

#ifdef __USER_COMMON_INTERFACE__

//--------------------------------------------------
// A0 EDID Location Check
//--------------------------------------------------
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
#if((_A0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_A0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check A0 EDID table location!!!"
#endif
#endif

//--------------------------------------------------
// D0 EDID Location Check
//--------------------------------------------------
#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
#if((_D0_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D0_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D0 EDID table location!!!"
#endif
#if((_D0_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D0_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D0 MHL EDID table location!!!"
#endif

// D0 Multi Edid Check
#if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)

#if(((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 > _D0_EMBEDDED_DDCRAM_SIZE) && (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST)) ||\
    ((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 > _D0_EMBEDDED_DDCRAM_SIZE) && (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST)) ||\
    ((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 > _D0_EMBEDDED_DDCRAM_SIZE) && (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST)))
#warning "Please check _D0_EMBEDDED_DDCRAM_SIZE!!!"
#endif

#if(((_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) + (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) + (_D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)) >= 2)
#warning "Please check _D0_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_x (at least 2 edid exist) !!!"
#endif

#endif // End of #if(_D0_HDMI_MULTI_EDID_SUPPORT == _ON)

#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)


//--------------------------------------------------
// D1 EDID Location Check
//--------------------------------------------------
#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
#if((_D1_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D1_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D1 EDID table location!!!"
#endif
#if((_D1_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D1_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D1 MHL EDID table location!!!"
#endif

// D1 Multi Edid Check
#if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)

#if(((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 > _D1_EMBEDDED_DDCRAM_SIZE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST)) ||\
    ((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 > _D1_EMBEDDED_DDCRAM_SIZE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST)) ||\
    ((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 > _D1_EMBEDDED_DDCRAM_SIZE) && (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST)))
#warning "Please check _D1_EMBEDDED_DDCRAM_SIZE!!!"
#endif

#if(((_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) + (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) + (_D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)) >= 2)
#warning "Please check _D1_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_x (at least 2 edid exist) !!!"
#endif

#endif // End of #if(_D1_HDMI_MULTI_EDID_SUPPORT == _ON)

#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

//--------------------------------------------------
// D2 EDID Location Check
//--------------------------------------------------
#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
#if((_D2_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D2_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D2 EDID table location!!!"
#endif
#if((_D2_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D2_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D2 MHL EDID table location!!!"
#endif

// D2 Multi Edid Check
#if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)

#if(((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 > _D2_EMBEDDED_DDCRAM_SIZE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST)) ||\
    ((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 > _D2_EMBEDDED_DDCRAM_SIZE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST)) ||\
    ((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 > _D2_EMBEDDED_DDCRAM_SIZE) && (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST)))
#warning "Please check _D2_EMBEDDED_DDCRAM_SIZE!!!"
#endif

#if(((_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) + (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) + (_D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)) >= 2)
#warning "Please check _D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_x (at least 2 edid exist) !!!"
#endif

#endif // End of #if(_D2_HDMI_MULTI_EDID_SUPPORT == _ON)

#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

//--------------------------------------------------
// D3 EDID Location Check
//--------------------------------------------------
#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
#if((_D3_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D3_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D3 EDID table location!!!"
#endif
#if((_D3_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D3_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D3 MHL EDID table location!!!"
#endif

// D3 Multi Edid Check
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)

#if(((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 > _D3_EMBEDDED_DDCRAM_SIZE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST)) ||\
    ((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 > _D3_EMBEDDED_DDCRAM_SIZE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST)) ||\
    ((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 > _D3_EMBEDDED_DDCRAM_SIZE) && (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST)))
#warning "Please check _D3_EMBEDDED_DDCRAM_SIZE!!!"
#endif

#if(((_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) + (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) + (_D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)) >= 2)
#warning "Please check _D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_x (at least 2 edid exist) !!!"
#endif

#endif // End of #if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)

#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

//--------------------------------------------------
// D4 EDID Location Check
//--------------------------------------------------
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
#if((_D4_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D4_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D4 EDID table location!!!"
#endif
#if((_D4_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D4_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D4 MHL EDID table location!!!"
#endif

// D4 Multi Edid Check
#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)

#if(((_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 > _D4_EMBEDDED_DDCRAM_SIZE) && (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST)) ||\
    ((_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 > _D4_EMBEDDED_DDCRAM_SIZE) && (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST)) ||\
    ((_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 > _D4_EMBEDDED_DDCRAM_SIZE) && (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST)))
#warning "Please check _D4_EMBEDDED_DDCRAM_SIZE!!!"
#endif

#if(((_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) + (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) + (_D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)) >= 2)
#warning "Please check _D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_x (at least 2 edid exist) !!!"
#endif

#endif // End of #if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)

#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

//--------------------------------------------------
// D5 EDID Location Check
//--------------------------------------------------
#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
#if((_D5_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D5_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D5 EDID table location!!!"
#endif
#if((_D5_MHL_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D5_MHL_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D5 MHL EDID table location!!!"
#endif

// D5 Multi Edid Check
#if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)

#if(((_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 > _D5_EMBEDDED_DDCRAM_SIZE) && (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 != _EDID_NOT_EXIST)) ||\
    ((_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 > _D5_EMBEDDED_DDCRAM_SIZE) && (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 != _EDID_NOT_EXIST)) ||\
    ((_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 > _D5_EMBEDDED_DDCRAM_SIZE) && (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 != _EDID_NOT_EXIST)))
#warning "Please check _D5_EMBEDDED_DDCRAM_SIZE!!!"
#endif

#if(((_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0 == _EDID_NOT_EXIST) + (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1 == _EDID_NOT_EXIST) + (_D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2 == _EDID_NOT_EXIST)) >= 2)
#warning "Please check _D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_x (at least 2 edid exist) !!!"
#endif

#endif // End of #if(_D5_HDMI_MULTI_EDID_SUPPORT == _ON)

#endif // End of #if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)


//--------------------------------------------------
// D6 EDID Location Check
//--------------------------------------------------
#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
#if((_D6_EMBEDDED_DDCRAM_SIZE != _EDID_SIZE_NONE) && (_D6_EMBEDDED_DDCRAM_LOCATION == _EDID_TABLE_LOCATION_CODE))
#warning "Please check D6 EDID table location!!!"
#endif
#endif

#endif // End of #ifdef __USER_COMMON_INTERFACE__


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Panel
//--------------------------------------------------
#if(_LVDS_VCM_USER_LEVEL > 0x1F)
#warning "LVDS VCM Selection Exceed The Maximum Value"
#endif


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Panel Config Check
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_DPTX)

#if((_PANEL_DPTX_1_1_SWING_LEVEL + _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL) > 2)
#warning "Panel DPTX 1.1 Swing and Pre-emphasis over Spec!!!"
#endif

#if(_PANEL_DPTX_1_1_SPREAD_SPEED == _SPEED_66K)
#warning "Panel DPTx Spread Spectrum Speed Should Be 30kHz~33kHz"
#endif


//////////////////////////
// eDPTx 1.2 HBR2 Panel //
//////////////////////////

//--------------------------------------------------
// eDPTx 1.2 HBR2 Panel Config Check
//--------------------------------------------------
#if((_PANEL_DPTX_1_2_SWING_LEVEL + _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL) > 3)
#warning "Panel DPTX 1.2 Swing and Pre-emphasis over Spec!!!"
#endif

#if(_PANEL_DPTX_1_2_SPREAD_SPEED == _SPEED_66K)
#warning "Panel DPTx Spread Spectrum Speed Should Be 30kHz~33kHz"
#endif

#endif


////////////////////
// V by One Panel //
////////////////////

//--------------------------------------------------
// V by One Panel Config Check
//--------------------------------------------------
#if(_PANEL_STYLE == _PANEL_VBO)
#if(_VBO_SPREAD_SPEED != _SPEED_30K)
#warning "Vbyone Spread Spectrum Speed Should Be 30kHz"
#endif
#endif


/////////////////
// Memory DDR3 //
/////////////////

//--------------------------------------------------
// DDR3 of Multi Phase For Different Vendor
//--------------------------------------------------
#if(_MEMORY_TYPE_CONFIG != _MEMORY_DDR3)
#if(_DDR3_MULTIPHASE_EXIST == _ON)
#warning "This Function Can Not Be _ON without DDR3"
#endif
#endif


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// SW & HW IIC
//--------------------------------------------------
#if (_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)
#if(_SW_IIC_SUPPORT == _OFF)
#warning "If using SW IIC _SW_IIC_SUPPORT Should Be ON"
#endif
#endif


//////////
// Misc //
//////////

#endif // End of #ifndef __PCB_CONFIG_CHECK_H__
