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
// ID Code      : RL6410_PCB_EXAMPLE.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_PCB_TYPE == _RL6410_PCB_EXAMPLE)


///////////////////
// External Xtal //
///////////////////

//--------------------------------------------------
// External Xtal Define
//--------------------------------------------------
#define _EXT_XTAL                               _XTAL14318K


///////////////
// Debug DDC //
///////////////

//--------------------------------------------------
// Debug DDC Channel
//--------------------------------------------------
#define _PCB_DEBUG_DDC                          _VGA_DDC


///////////////////////
// Input Port Config //
///////////////////////

//--------------------------------------------------
// A0 Input Port
//--------------------------------------------------
#define _A0_INPUT_PORT_TYPE                     _A0_NO_PORT
#define _A0_EMBEDDED_DDCRAM_SIZE                _EDID_SIZE_NONE
#define _A0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D0 Input Port
//--------------------------------------------------
#define _D0_INPUT_PORT_TYPE                     _D0_NO_PORT
#define _D0_DDC_CHANNEL_SEL                     _NO_DDC
#define _D0_EMBEDDED_DDCRAM_SIZE                _EDID_SIZE_NONE
#define _D0_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

// For DP
#define _D0_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D0_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D0_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

// For DP Type-C
#define _D0_DP_TYPE_C_PORT_CONTROLLER_TYPE      _RTS_5400
#define _D0_DP_TYPE_C_USB_HUB_TYPE              _RTS_5411
#define _D0_DP_TYPE_C_RTS5400_SLAVE_ADDRESS     0xD4
#define _D0_DP_TYPE_C_RTS5411_SLAVE_ADDRESS     0xD2
#define _D0_DP_SMBUS_IIC                        _NO_IIC_PIN

//--------------------------------------------------
// D1 Input Port
//--------------------------------------------------
#define _D1_INPUT_PORT_TYPE                     _D1_NO_PORT
#define _D1_DDC_CHANNEL_SEL                     _NO_DDC
#define _D1_EMBEDDED_DDCRAM_SIZE                _EDID_SIZE_NONE
#define _D1_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

// For DP
#define _D1_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D1_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D1_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE

// For DP Type-C
#define _D1_DP_TYPE_C_PORT_CONTROLLER_TYPE      _RTS_5400
#define _D1_DP_TYPE_C_USB_HUB_TYPE              _RTS_5411
#define _D1_DP_TYPE_C_RTS5400_SLAVE_ADDRESS     0xD4
#define _D1_DP_TYPE_C_RTS5411_SLAVE_ADDRESS     0xD2
#define _D1_DP_SMBUS_IIC                        _NO_IIC_PIN

//--------------------------------------------------
// D2 Input Port
//--------------------------------------------------
#define _D2_INPUT_PORT_TYPE                     _D2_NO_PORT
#define _D2_DDC_CHANNEL_SEL                     _NO_DDC
#define _D2_EMBEDDED_DDCRAM_SIZE                _EDID_SIZE_NONE
#define _D2_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

// For HDMI MultiEdid
#define _D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0   _EDID_NOT_EXIST
#define _D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1   _EDID_NOT_EXIST
#define _D2_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2   _EDID_NOT_EXIST

// For MHL
#define _D2_MHL_VERSION                         _MHL_VERSION_NULL
#define _D2_CBUS_CHANNEL_SEL                    _NO_CBUS
#define _D2_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_NONE
#define _D2_MHL_EMBEDDED_DDCRAM_LOCATION        _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D3 Input Port
//--------------------------------------------------
#define _D3_INPUT_PORT_TYPE                     _D3_NO_PORT
#define _D3_DDC_CHANNEL_SEL                     _NO_DDC
#define _D3_EMBEDDED_DDCRAM_SIZE                _EDID_SIZE_NONE
#define _D3_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

// For HDMI MultiEdid
#define _D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0   _EDID_NOT_EXIST
#define _D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1   _EDID_NOT_EXIST
#define _D3_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2   _EDID_NOT_EXIST

// For MHL
#define _D3_MHL_VERSION                         _MHL_VERSION_NULL
#define _D3_CBUS_CHANNEL_SEL                    _NO_CBUS
#define _D3_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_NONE
#define _D3_MHL_EMBEDDED_DDCRAM_LOCATION        _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D4 Input Port
//--------------------------------------------------
#define _D4_INPUT_PORT_TYPE                     _D4_NO_PORT
#define _D4_DDC_CHANNEL_SEL                     _NO_DDC
#define _D4_EMBEDDED_DDCRAM_SIZE                _EDID_SIZE_NONE
#define _D4_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

// For HDMI MultiEdid
#define _D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0   _EDID_NOT_EXIST
#define _D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1   _EDID_NOT_EXIST
#define _D4_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2   _EDID_NOT_EXIST

// For MHL
#define _D4_MHL_VERSION                         _MHL_VERSION_NULL
#define _D4_CBUS_CHANNEL_SEL                    _NO_CBUS
#define _D4_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_NONE
#define _D4_MHL_EMBEDDED_DDCRAM_LOCATION        _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D5 Input Port
//--------------------------------------------------
#define _D5_INPUT_PORT_TYPE                     _D5_NO_PORT
#define _D5_DDC_CHANNEL_SEL                     _NO_DDC
#define _D5_EMBEDDED_DDCRAM_SIZE                _EDID_SIZE_NONE
#define _D5_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

// For HDMI MultiEdid
#define _D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_0   _EDID_NOT_EXIST
#define _D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_1   _EDID_NOT_EXIST
#define _D5_EMBEDDED_DDCRAM_SIZE_MULTI_EDID_2   _EDID_NOT_EXIST

// For MHL
#define _D5_MHL_VERSION                         _MHL_VERSION_NULL
#define _D5_CBUS_CHANNEL_SEL                    _NO_CBUS
#define _D5_MHL_EMBEDDED_DDCRAM_SIZE            _EDID_SIZE_NONE
#define _D5_MHL_EMBEDDED_DDCRAM_LOCATION        _EDID_TABLE_LOCATION_CODE

//--------------------------------------------------
// D6 Input Port
//--------------------------------------------------
#define _D6_INPUT_PORT_TYPE                     _D6_NO_PORT
#define _D6_EMBEDDED_DDCRAM_SIZE                _EDID_SIZE_NONE
#define _D6_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE

// For DP
#define _D6_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_NORMAL
#define _D6_DP_LINK_CLK_RATE                    _DP_HIGH_SPEED2_540MHZ
#define _D6_DP_MAIN_LINK_LANES                  _DP_FOUR_LANE
#define _D6_INPUT_PORT_SWITCH_FROM              _SWITCH_NONE

// For DP Type-C
#define _D6_DP_TYPE_C_PORT_CONTROLLER_TYPE      _RTS_5400
#define _D6_DP_TYPE_C_USB_HUB_TYPE              _RTS_5411
#define _D6_DP_TYPE_C_RTS5400_SLAVE_ADDRESS     0xD4
#define _D6_DP_TYPE_C_RTS5411_SLAVE_ADDRESS     0xD2
#define _D6_DP_SMBUS_IIC                        _NO_IIC_PIN

//--------------------------------------------------
// D7 Input Port
//--------------------------------------------------
#define _D7_INPUT_PORT_TYPE                     _D7_NO_PORT
#define _D7_D0_EMBEDDED_DDCRAM_SIZE             _EDID_SIZE_256
#define _D7_D1_EMBEDDED_DDCRAM_SIZE             _EDID_SIZE_384
#define _D7_EMBEDDED_DDCRAM_LOCATION            _EDID_TABLE_LOCATION_CODE
#define _D7_DP_CONNECTOR_TYPE                   _DP_CONNECTOR_DUAL_DP


/////////////////////////////
// Search Group & Priority //
/////////////////////////////

//--------------------------------------------------
// Input Port Search Group Define
//--------------------------------------------------
#define _A0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D0_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D1_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D2_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D3_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D4_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D5_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D6_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE
#define _D7_INPUT_PORT_GROUP                    _INPUT_PORT_GROUP_NONE

//--------------------------------------------------
// Input Port Search Priority Define (Must Start From Valid Port)
//--------------------------------------------------
#define _INPUT_PORT_SEARCH_PRI_0                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_1                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_2                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_3                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_4                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_5                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_6                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_7                _NO_INPUT_PORT
#define _INPUT_PORT_SEARCH_PRI_8                _NO_INPUT_PORT


//////////////
// VGA Port //
//////////////

//--------------------------------------------------
// Analog Signal Swap Options
//--------------------------------------------------
#define _VGA_INPUT_SWAP_RG                      _OFF
#define _VGA_INPUT_SWAP_RB                      _OFF
#define _VGA_INPUT_SWAP_GB                      _OFF

//--------------------------------------------------
// Analog Hsync Schmitt Trigger Control
//--------------------------------------------------
#define _VGA_HS_SCHMITT_TRIGGER_POLARITY_SEL    _POSITIVE
#define _VGA_HS_SCHMITT_TRIGGER_VTH_FINE_TUNE   _DISABLE
#define _VGA_HS_SCHMITT_TRIGGER_POSITIVE_VTH    _HS_SCHMITT_TRIGGER_LEVEL_10
#define _VGA_HS_SCHMITT_TRIGGER_NEGATIVE_VTH    _HS_SCHMITT_TRIGGER_LEVEL_01


///////////////
// TMDS Port //
///////////////

//--------------------------------------------------
// TMDS Signal Swap Options
//--------------------------------------------------
#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_MHL_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
#define _D2_TMDS_BR_SWAP                        _ON
#define _D2_TMDS_PN_SWAP                        _ON
#else
#define _D2_TMDS_BR_SWAP                        _OFF
#define _D2_TMDS_PN_SWAP                        _OFF
#endif

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_MHL_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT) || (_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT))
#define _D3_TMDS_BR_SWAP                        _ON
#define _D3_TMDS_PN_SWAP                        _ON
#else
#define _D3_TMDS_BR_SWAP                        _OFF
#define _D3_TMDS_PN_SWAP                        _OFF
#endif

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT) || (_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT))
#define _D4_TMDS_BR_SWAP                        _ON
#define _D4_TMDS_PN_SWAP                        _ON
#else
#define _D4_TMDS_BR_SWAP                        _OFF
#define _D4_TMDS_PN_SWAP                        _OFF
#endif

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) || (_D5_INPUT_PORT_TYPE == _D5_MHL_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
#define _D5_TMDS_BR_SWAP                        _ON
#define _D5_TMDS_PN_SWAP                        _ON
#else
#define _D5_TMDS_BR_SWAP                        _OFF
#define _D5_TMDS_PN_SWAP                        _OFF
#endif


/////////////
// DP Port //
/////////////

//--------------------------------------------------
// DP Lane & PN Swap Option
//--------------------------------------------------
#define _D0_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE0
#define _D0_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE1
#define _D0_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE2
#define _D0_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE3
#define _D0_DP_PCB_PN_SWAP                      _OFF

#define _D1_DP_PCB_LANE0_MAPPING                _DP_SCALER_LANE0
#define _D1_DP_PCB_LANE1_MAPPING                _DP_SCALER_LANE1
#define _D1_DP_PCB_LANE2_MAPPING                _DP_SCALER_LANE2
#define _D1_DP_PCB_LANE3_MAPPING                _DP_SCALER_LANE3
#define _D1_DP_PCB_PN_SWAP                      _OFF


//////////////
// MHL Port //
//////////////

//--------------------------------------------------
// MHL CBUS Output High Voltage Level
//--------------------------------------------------
#define _MHL_CBUS_LDO_HIGH                      _DISABLE


////////////////////
// For LVDS Panel //
////////////////////

//--------------------------------------------------
// LVDS Port Config
//--------------------------------------------------
#define _LVDS_PORT_SEL                          _LVDS_2_PORT_AB
#define _LVDS_PORT_MIRROR                       _DISABLE
#define _LVDS_PORT_AB_SWAP                      _DISABLE
#define _LVDS_PORT_CD_SWAP                      _DISABLE
#define _LVDS_PORT_EF_SWAP                      _DISABLE
#define _LVDS_PORT_GH_SWAP                      _DISABLE
#define _LVDS_PN_SWAP                           _DISABLE
#define _LVDS_RB_SWAP                           _DISABLE
#define _LVDS_ML_SWAP                           _DISABLE
#define _LVDS_DVS_INVERT                        _DISABLE
#define _LVDS_DHS_INVERT                        _DISABLE
#define _LVDS_DEN_INVERT                        _DISABLE
#define _LVDS_PAIR_MIRROR                       _DISABLE

#define _LVDS_CLK_CHANNEL_SEL                   _NORMAL_MODE           /// Display CLK Pair Position Selection: TXK = A / B / C / D / E / F / G / H port
                                                                       /// Normal mode: TXKCK1 as CLK for 8bit / 10bit
                                                                       /// Mode1:       TXK1   as CLK for 8bit / 10bit
                                                                       /// Mode2:       TXK2   as CLK for 8bit / 10bit
                                                                       /// Mode3:       TXKCK1 as CLK for 8bit
                                                                       ///              TXK3   as CLK for        10bit

//--------------------------------------------------
// LVDS Port AB Phase Selection
//--------------------------------------------------
#define _LVDS_A0_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_A1_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_A2_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_AC_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_A3_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_A4_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B0_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B1_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B2_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_BC_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B3_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_B4_PHASE                          _LVDS_PI_PHASE_AB0
#define _LVDS_PI_PHASE_AB0_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB1_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB2_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_AB3_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used

//--------------------------------------------------
// LVDS Port CD Phase Selection
//--------------------------------------------------
#define _LVDS_C0_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_C1_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_C2_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_CC_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_C3_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_C4_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D0_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D1_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D2_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_DC_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D3_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_D4_PHASE                          _LVDS_PI_PHASE_CD0
#define _LVDS_PI_PHASE_CD0_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD1_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD2_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_CD3_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used

//--------------------------------------------------
// LVDS Port EF Phase Selection
//--------------------------------------------------
#define _LVDS_E0_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_E1_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_E2_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_EC_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_E3_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_E4_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_F0_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_F1_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_F2_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_FC_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_F3_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_F4_PHASE                          _LVDS_PI_PHASE_EF0
#define _LVDS_PI_PHASE_EF0_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_EF1_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_EF2_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_EF3_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used

//--------------------------------------------------
// LVDS Port GH Phase Selection
//--------------------------------------------------
#define _LVDS_G0_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_G1_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_G2_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_GC_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_G3_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_G4_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_H0_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_H1_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_H2_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_HC_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_H3_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_H4_PHASE                          _LVDS_PI_PHASE_GH0
#define _LVDS_PI_PHASE_GH0_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_GH1_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_GH2_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used
#define _LVDS_PI_PHASE_GH3_SEL                  _LVDS_PHASE0           // Only Phase 0 ~ 16 can be used

//--------------------------------------------------
// LVDS Driving Config
//--------------------------------------------------
#define _LVDS_DRIV_CONTROL                      _LVDS_DRIV_CONTROL_3_0
#define _LVDS_VCM_CONTROL                       _LVDS_VCM_NORMAL
#define _LVDS_SR_CONTROL                        _LVDS_SR_CONTROL_0
#define _LVDS_PRE_EMPHASIS_CONTROL              _LVDS_PRE_EMPHASIS_0
#define _LVDS_TERMINATION_CONTROL               _DISABLE
#define _LVDS_VCM_USER_LEVEL                    0x0C

//--------------------------------------------------
// LVDS SSC Config
//--------------------------------------------------
#define _LVDS_SPREAD_RANGE                      10                     // 0~15, 0 ~ disable, 15 ~ 7.50%
#define _LVDS_SPREAD_SPEED                      _SPEED_33K


/////////////////////////
// eDPTx 1.1 HBR Panel //
/////////////////////////

//--------------------------------------------------
// eDPTx 1.1 HBR Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_FB_SWAP                 _DISABLE               // Swap Picture Front and Back Swap for 8 Lane Panel
#define _PANEL_DPTX_1_1_LANE_SWAP               _DISABLE               // Lane Port Swap
#define _PANEL_DPTX_1_1_LANE_PN_SWAP            _DISABLE               // Lane PN Swap
#define _PANEL_DPTX_1_1_SWING_LEVEL             _DP_SWING_800_MV       // Swing Level = 400,600,800,1200mV
#define _PANEL_DPTX_1_1_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_0_DB   // Preemphasis Level = 0,3.5,6,9.5dB

//--------------------------------------------------
// eDPTx 1.1 HBR SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_1_SPREAD_RANGE            5                      // 0~15, 0 ~ disable, 15 ~ 0.98%
#define _PANEL_DPTX_1_1_SPREAD_SPEED            _SPEED_33K             // _SPEED_30K or _SPEED_33K


//////////////////////////
// eDPTx 1.2 HBR2 Panel //
//////////////////////////

//--------------------------------------------------
// eDPTx 1.2 HBR2 Main Link Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_SWING_LEVEL             _DP_SWING_800_MV       // Swing Level = 400,600,800,1200mV
#define _PANEL_DPTX_1_2_PREEMPHASIS_LEVEL       _DP_PREEMPHASIS_3_5_DB // Preemphasis Level = 0,3.5,6,9.5dB

//--------------------------------------------------
// eDPTx 1.2 HBR2 SSC Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_SPREAD_RANGE            12                     // 0~15, 0 ~ disable, 0.5 ~ 0.03%
#define _PANEL_DPTX_1_2_SPREAD_SPEED            _SPEED_33K             // _SPEED_30~33K

//--------------------------------------------------
// eDPTx 1.2 HBR2 FB/Lane Config
//--------------------------------------------------
#define _PANEL_DPTX_1_2_FB_SWAP                 _DISABLE               // Swap Picture Front and Back Swap for 8 Lane Panel
#define _PANEL_DPTX_1_2_LANE_SWAP               _DISABLE               // Lane Port Swap
#define _PANEL_DPTX_1_2_LANE_PN_SWAP            _DISABLE               // Lane PN Swap


////////////////////
// V by One Panel //
////////////////////

//--------------------------------------------------
// V by One Main Link Config
//--------------------------------------------------
#define _VBO_LANE_SWAP                          _DISABLE               // Display Data Lane Swap
#define _VBO_ML_SWAP                            _DISABLE               // Display Data Port MSB/LSB Data Swap
#define _VBO_PN_SWAP                            _DISABLE               // Display Data PN Swap
#define _VBO_LANE_DRIV_CONTROL                  _VBO_DRIV_CONTROL_3_0
#define _VBO_PRE_EMPHASIS_CONTROL               _VBO_PRE_EMPHASIS_0

//--------------------------------------------------
// V by One SSC Config
//--------------------------------------------------
#define _VBO_SPREAD_RANGE                       15                     // 0~15, 0 ~ disable, 15 ~ 0.98%
#define _VBO_SPREAD_SPEED                       _SPEED_30K


/////////////////
// Memory DDR3 //
/////////////////

//--------------------------------------------------
// Definitions of DDR3 Memory Size
//--------------------------------------------------
#define _EXTERNAL_MEMORY_SIZE_CONFIG            _1G_16BIT_DDR3_2PCS    // _1G_16BIT_DDR3_1PC
                                                                       // _1G_16BIT_DDR3_2PCS
                                                                       // _2G_16BIT_GDDR3_1PC
                                                                       // _2G_16BIT_GDDR3_2PCS
                                                                       // _4G_16BIT_GDDR3_1PC
                                                                       // _4G_16BIT_GDDR3_2PCS

//--------------------------------------------------
// Definitions of DDR3 PLL Phase
//--------------------------------------------------
#define _DDR3_PLL_INITIAL_PHASE_0               0x00000000
#define _DDR3_PLL_INITIAL_PHASE_1               0x00000000
#define _DDR3_READ_DQ_DLYN_TAP                  0x00000000

//--------------------------------------------------
// Definitions of DDR3 Multi-Phase
//--------------------------------------------------
#define _DDR3_MULTIPHASE_EXIST                  _OFF


/////////
// PWM //
/////////

//--------------------------------------------------
// PWM Setting
//--------------------------------------------------
#define _PWM_DUT_RESOLUTION                     _PWM_8BIT

#define _BACKLIGHT_PWM                          _NO_PWM
#define _BACKLIGHT_PWM_INVERSE                  _OFF

#define _PWM0_EN                                _OFF
#define _PWM1_EN                                _OFF
#define _PWM2_EN                                _OFF
#define _PWM3_EN                                _OFF
#define _PWM4_EN                                _OFF
#define _PWM5_EN                                _OFF

#define _PWM0_PSAV_EN                           _OFF
#define _PWM1_PSAV_EN                           _OFF
#define _PWM2_PSAV_EN                           _OFF
#define _PWM3_PSAV_EN                           _OFF
#define _PWM4_PSAV_EN                           _OFF
#define _PWM5_PSAV_EN                           _OFF

#define _PWM0_PDOW_EN                           _OFF
#define _PWM1_PDOW_EN                           _OFF
#define _PWM2_PDOW_EN                           _OFF
#define _PWM3_PDOW_EN                           _OFF
#define _PWM4_PDOW_EN                           _OFF
#define _PWM5_PDOW_EN                           _OFF

#define _PWM0_RST_BY_DVS                        _OFF
#define _PWM1_RST_BY_DVS                        _OFF
#define _PWM2_RST_BY_DVS                        _OFF
#define _PWM3_RST_BY_DVS                        _OFF
#define _PWM4_RST_BY_DVS                        _OFF
#define _PWM5_RST_BY_DVS                        _OFF
#define _PWM_RST_BY_TCON                        _OFF


/////////////////
// SW & HW IIC //
/////////////////

//--------------------------------------------------
// Sofware and Hardware IIC Option
//--------------------------------------------------
#define _SW_IIC_SUPPORT                         _OFF
#define _SW_IIC_CLK_DIV                         _DIV_1

#define _HW_IIC_SUPPORT                         _OFF
#define _HW_IIC_SPEED                           _HW_IIC_LOW_SPEED_100K


///////////////////
// System Eeprom //
///////////////////

//--------------------------------------------------
// Eeprom System Data Storage Option
//--------------------------------------------------
#define _EEPROM_TYPE                            _EEPROM_24LC16
#define _EEPROM_SLAVE_ADDRESS                   0xA0
#define _PCB_SYS_EEPROM_IIC                     _NO_IIC_PIN


//////////
// Misc //
//////////

//--------------------------------------------------
// AD Key Option
//--------------------------------------------------
#define _AD_KEY_SUPPORT                         _OFF

//--------------------------------------------------
// Low Speed ADC Option
//--------------------------------------------------
#define _LOW_SPEED_ADC_SUPPORT                  _OFF


/////////////////////////////
// RL6410 Series Pin Share //
/////////////////////////////

//--------------------------------------------------
//  RL6410 BGA Pin Share
//--------------------------------------------------
#define _PIN_Y6                                 (0 & 0x07) // Page 10-0x00[2:0]
// 0 ~ 4 (0: P1D0i<I>, 1: reserved, 2: P1D0o<OD>, 3: AUX_P1)

#define _PIN_Y5                                 (0 & 0x07) // Page 10-0x01[2:0]
// 0 ~ 4 (0: P1D1i<I>, 1: reserved, 2: P1D1o<OD>, 3: AUX_N1)

#define _PIN_AA6                                (0 & 0x07) // Page 10-0x02[2:0]
// 0 ~ 4 (0: P1D2i<I>, 1: reserved, 2: P1D2o<OD>, 3: AUX_P0)

#define _PIN_AA5                                (0 & 0x07) // Page 10-0x03[2:0]
// 0 ~ 4 (0: P1D3i<I>, 1: reserved, 2: P1D3o<OD>, 3: AUX_N0)

#define _PIN_L4                                 (0 & 0x07) // Page 10-0x04[2:0]
// 0 ~ 2 (0: P1D4i<I>, 1: P1D4o<PP>, 2: P1D4o<OD>)

#define _PIN_W6                                 (0 & 0x07) // Page 10-0x05[2:0]
// 0 ~ 2 (0: P1D5i<I>, 1: P1D5o<PP>, 2: P1D5o<OD>)

#define _PIN_F4                                 (0 & 0x07) // Page 10-0x06[2:0]
// 0 ~ 2 (0: P1D6i<I>, 1: P1D6o<PP>, 2: P1D6o<OD>)

#define _PIN_W5                                 (0 & 0x07) // Page 10-0x07[2:0]
// 0 ~ 2 (0: P1D7i<I>, 1: P1D7o<PP>, 2: P1D7o<OD>)

#define _PIN_AJ3                                (0 & 0x07) // Page 10-0x08[2:0]
// 0 ~ 6 (0: P3D0i<I>, 1: P3D0o<PP>, 2: P3D0o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AJ1                                (0 & 0x07) // Page 10-0x09[2:0]
// 0 ~ 6 (0: P3D1i<I>, 1: P3D1o<PP>, 2: P3D1o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AJ2                                (0 & 0x07) // Page 10-0x0A[2:0]
// 0 ~ 6 (0: P3D2i<I>, 1: P3D2o<PP>, 2: P3D2o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AK3                                (0 & 0x07) // Page 10-0x0B[2:0]
// 0 ~ 6 (0: P3D3i<I>, 1: P3D3o<PP>, 2: P3D3o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AK2                                (0 & 0x07) // Page 10-0x0C[2:0]
// 0 ~ 6 (0: P3D4i<I>, 1: P3D4o<PP>, 2: P3D4o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AL3                                (0 & 0x07) // Page 10-0x0D[2:0]
// 0 ~ 6 (0: P3D5i<I>, 1: P3D5o<PP>, 2: P3D5o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AL2                                (0 & 0x07) // Page 10-0x0E[2:0]
// 0 ~ 6 (0: P3D6i<I>, 1: P3D6o<PP>, 2: P3D6o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AL1                                (0 & 0x07) // Page 10-0x0F[2:0]
// 0 ~ 6 (0: P3D7i<I>, 1: P3D7o<PP>, 2: P3D7o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AM1                                (0 & 0x07) // Page 10-0x10[2:0]
// 0 ~ 6 (0: P4D0i<I>, 1: P4D0o<PP>, 2: P4D0o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_AH9                                (0 & 0x07) // Page 10-0x11[2:0]
// 0 ~ 4 (0: P4D1i<I>, 1: P4D1o<PP>, 2: P4D1o<OD>, 3: A-adc0_0, 4: Int0)

#define _PIN_AH8                                (0 & 0x07) // Page 10-0x12[2:0]
// 0 ~ 4 (0: P4D2i<I>, 1: P4D2o<PP>, 2: P4D2o<OD>, 3: A-adc1_0, 4: INT1)

#define _PIN_AJ9                                (0 & 0x07) // Page 10-0x13[2:0]
// 0 ~ 3 (0: P4D3i<I>, 1: P4D3o<PP>, 2: P4D3o<OD>, 3: A-adc2_0)

#define _PIN_AJ8                                (0 & 0x07) // Page 10-0x14[2:0]
// 0 ~ 3 (0: P4D4i<I>, 1: P4D4o<PP>, 2: P4D4o<OD>, 3: A-adc3_0)

#define _PIN_AL5                                (0 & 0x07) // Page 10-0x15[2:0]
// 0 ~ 3 (0: P4D5i<I>, 1: P4D5o<PP>, 2: P4D5o<OD>, 3: Ddcsclvga)

#define _PIN_AK5                                (0 & 0x07) // Page 10-0x16[2:0]
// 0 ~ 3 (0: P4D6i<I>, 1: P4D6o<PP>, 2: P4D6o<OD>, 3: Ddcsdavga)

#define _PIN_AJ5                                (0 & 0x07) // Page 10-0x17[2:0]
// 0 ~ 5 (0: P4D7i<I>, 1: P4D7o<PP>, 2: P4D7o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5: TCON[4])

#define _PIN_AK4                                (0 & 0x07) // Page 10-0x18[2:0]
// 0 ~ 6 (0: P5D0i<I>, 1: P5D0o<PP>, 2: P5D0o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[5], 6: INT0)

#define _PIN_AL4                                (0 & 0x07) // Page 10-0x19[2:0]
// 0 ~ 5 (0: P5D1i<I>, 1: P5D1o<PP>, 2: P5D1o<OD>, 3: PWM2<PP>, 4: PWM2<OD>,
//        5: TCON[7])

#define _PIN_AM4                                (0 & 0x07) // Page 10-0x1A[2:0]
// 0 ~ 5 (0: P5D2i<I>, 1: P5D2o<PP>, 2: P5D2o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[8])

#define _PIN_AM2                                (0 & 0x07) // Page 10-0x1B[2:0]
// 0 ~ 7 (0: P5D3i<I>, 1: P5D3o<PP>, 2: P5D3o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[10], 6: INT1, 7: PWM_IN)

#define _PIN_AM3                                (0 & 0x07) // Page 10-0x1C[2:0]
// 0 ~ 6 (0: P5D4i<I>, 1: P5D4o<PP>, 2: P5D4o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[12], 6: PWM_OUT)

#define _PIN_G7                                 (0 & 0x07) // Page 10-0x1D[2:0]
// 0 ~ 5 (0: P5D5i<I>, 1: P5D5o<PP>, 2: P5D5o<OD>, 3: PWM2<PP>, 4: PWM2<OD>,
//        5: TCON[3])

#define _PIN_J7                                 (0 & 0x07) // Page 10-0x1E[2:0]
// 0 ~ 6 (0: P5D6i<I>, 1: P5D6o<PP>, 2: P5D6o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5: TCON[1], 6: EEIICSCL)

#define _PIN_H6                                 (0 & 0x07) // Page 10-0x1F[2:0]
// 0 ~ 6 (0: P5D7i<I>, 1: P5D7o<PP>, 2: P5D7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[2], 6: EEIICSDA)

#define _PIN_AD28                               (0 & 0x0F) // Page 10-0x24[2:0]
// 0 ~ 8 (0: P6D4i<I>, 1: P6D4o<PP>, 2: P6D4o<OD>, 3: TCON[4], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3, 8: IICSCL1)

#define _PIN_AH27                               (0 & 0x0F) // Page 10-0x25[2:0]
// 0 ~ 8 (0: P6D5i<I>, 1: P6D5o<PP>, 2: P6D5o<OD>, 3: TCON[5], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3, 8: IICSDA1)

#define _PIN_N29                                (0 & 0x07) // Page 10-0x26[2:0]
// 0 ~ 6 (0: P6D6i<I>, 1: P6D6o<PP>, 2: P6D6o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5: TCON[6], 6: Dptx_aux_ch_p_1)

#define _PIN_N28                                (0 & 0x07) // Page 10-0x27[2:0]
// 0 ~ 6 (0: P6D7i<I>, 1: P6D7o<PP>, 2: P6D7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[7], 6: Dptx_aux_ch_n_1)

#define _PIN_M29                                (0 & 0x07) // Page 10-0x28[2:0]
// 0 ~ 6 (0: P7D0i<I>, 1: P7D0o<PP>, 2: P7D0o<OD>, 3: PWM2<PP>, 4: PWM3<OD>,
//        5: TCON[8], 6: Dptx_aux_ch_p_2)

#define _PIN_M28                                (0 & 0x07) // Page 10-0x29[2:0]
// 0 ~ 6 (0: P7D1i<I>, 1: P7D1o<PP>, 2: P7D1o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[9], 6: Dptx_aux_ch_n_2)

#define _PIN_J29                                (0 & 0x07) // Page 10-0x2A[2:0]
// 0 ~ 7 (0: P7D2i<I>, 1: P7D2o<PP>, 2: P7D2o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[10], 6: Disp_frame_start_in, 7: Disp_frame_start_out)

#define _PIN_AJ28                               (0 & 0x07) // Page 10-0x2B[2:0]
// 0 ~ 6 (0: P7D3i<I>, 1: P7D3o<PP>, 2: P7D3o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[11], 6: Cryclk)

#define _PIN_N27                                (0 & 0x07) // Page 10-0x2C[2:0]
// 0 ~ 6 (0: P7D4i<I>, 1: P7D4o<PP>, 2: P7D4o<OD>, 3: Ws, 4: TCON[12],
//        5: Test4b_out0, 6: Test4b_out1)

#define _PIN_K27                                (0 & 0x07) // Page 10-0x2D[2:0]
// 0 ~ 6 (0: P7D5i<I>, 1: P7D5o<PP>, 2: P7D5o<OD>, 3: Sck, 4: TCON[13],
//        5: Test4b_out2, 6: Test4b_out3)

#define _PIN_M27                                (0 & 0x07) // Page 10-0x2E[2:0]
// 0 ~ 7 (0: P7D6i<I>, 1: P7D6o<PP>, 2: P7D6o<OD>, 3: Mck, 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

#define _PIN_K29                                (0 & 0x07) // Page 10-0x2F[2:0]
// 0 ~ 6 (0: P7D7i<I>, 1: P7D7o<PP>, 2: P7D7o<OD>, 3: Spdif0, 4: Sd0,
//        5: Test4b_out0, 6: Test4b_out1, 7: TCON[0])

#define _PIN_J28                                (0 & 0x07) // Page 10-0x30[2:0]
// 0 ~ 6 (0: P8D0i<I>, 1: P8D0o<PP>, 2: P8D0o<OD>, 3: Spdif1, 4: Sd1,
//        5: Test4b_out2, 6: Test4b_out3,  7: TCON[1])

#define _PIN_J27                                (0 & 0x07) // Page 10-0x31[2:0]
// 0 ~ 6 (0: P8D1i<I>, 1: P8D1o<PP>, 2: P8D1o<OD>, 3: Spdif2, 4: Sd2,
//        5: Test4b_out0, 6: Test4b_out1,  7: TCON[2])

#define _PIN_K28                                (0 & 0x07) // Page 10-0x32[2:0]
// 0 ~ 6 (0: P8D2i<I>, 1: P8D2o<PP>, 2: P8D2o<OD>, 3: Spdif3, 4: Sd3,
//        5: Test4b_out2, 6: Test4b_out3,  7: TCON[3])

#define _PIN_AH21                               (0 & 0x07) // Page 10-0x33[2:0]
// 0 ~ 4 (0: P8D3i<I>, 1: P8D3o<PP>, 2: P8D3o<OD>, 3: CLKO, 4: Usb_spi_clk)

#define _PIN_AK21                               (0 & 0x07) // Page 10-0x34[2:0]
// 0 ~ 4 (0: P8D4i<I>, 1: P8D4o<PP>, 2: P8D4o<OD>, 3: INT0, 4: Usb_spi_si)

#define _PIN_AJ21                               (0 & 0x07) // Page 10-0x35[2:0]
// 0 ~ 4 (0: P8D5i<I>, 1: P8D5o<PP>, 2: P8D5o<OD>, 3: INT1, 4: Usb_spi_so)

#define _PIN_AJ20                               (0 & 0x07) // Page 10-0x36[2:0]
// 0 ~ 4 (0: P8D6i<I>, 1: P8D6o<PP>, 2: P8D6o<OD>, 3: IRQB, 4: Usb_spi_ceb0)

#define _PIN_AH20                               (0 & 0x07) // Page 10-0x37[2:0]
// 0 ~ 4 (0: P8D7i<I>, 1: P8D7o<PP>, 2: P8D7o<OD>, 3: T2ex , 4: Usb_spi_ceb1)

#define _PIN_AL21                               (0 & 0x07) // Page 10-0x38[2:0]
// 0 ~ 2 (0: P9D0i<I>, 1: P9D0o<PP>, 2: P9D0o<OD>)

#define _PIN_AA29                               (0 & 0x07) // Page 10-0x39[2:0]
// 0 ~ 4 (0: P9D1i<I>, 1: P9D1o<PP>, 2: P9D1o<OD>, 3: Vb1_lock_n, 4: Dptx_hpd2_org)

#define _PIN_AA28                               (0 & 0x07) // Page 10-0x3A[2:0]
// 0 ~ 4 (0: P9D2i<I>, 1: P9D2o<PP>, 2: P9D2o<OD>, 3: Vb1_htpd_n, 4: Dptx_hpd1_org)

#define _PIN_AG25                               (0 & 0x07) // Page 10-0x3B[2:0]
// 0 ~ 6 (0: P9D3i<I>, 1: P9D3o<PP>, 2: P9D3o<OD>, 3: PWM5<PP>, 4: PWM5<OD>,
//        5: TCON[7], 6:T0)

#define _PIN_AH26                               (0 & 0x07) // Page 10-0x3C[2:0]
// 0 ~ 6 (0: P9D4i<I>, 1: P9D4o<PP>, 2: P9D4o<OD>, 3: PWM4<PP>, 4: PWM4<OD>,
//        5: TCON[6], 6:T1)

#define _PIN_AG26                               (0 & 0x07) // Page 10-0x3D[2:0]
// 0 ~ 6 (0: P9D5i<I>, 1: P9D5o<PP>, 2: P9D5o<OD>, 3: PWM3<PP>, 4: PWM3<OD>,
//        5: TCON[5], 6:T2)

#define _PIN_AJ26                               (0 & 0x07) // Page 10-0x3E[2:0]
// 0 ~ 6 (0: P9D6i<I>, 1: P9D6o<PP>, 2: P9D6o<OD>, 3: PWM2<PP>, 4: PWM2<OD>,
//        5: TCON[4], 6:Irda_in)

#define _PIN_AF28                               (0 & 0x07) // Page 10-0x3F[2:0]
// 0 ~ 7 (0: P9D7i<I>, 1: P9D7o<PP>, 2: P9D7o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5: TCON[3], 6: Test4b_out2, 7: Test4b_out3)

#define _PIN_AG24                               (0 & 0x07) // Page 10-0x40[2:0]
// 0 ~ 7 (0: PAD0i<I>, 1: PAD0o<PP>, 2: PAD0o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5: TCON[2], 6: Test4b_out0, 7: Test4b_out1)

#define _PIN_AE28                               (0 & 0x0F) // Page 10-0x41[2:0]
// 0 ~ 8 (0: PAD1i<I>, 1: PAD1o<PP>, 2: PAD1o<OD>, 3: TCON[1], 4: reserved,
//        5: reserved, 6: Test4b_out2, 7: Test4b_out3, 8: RXD)

#define _PIN_AJ27                               (0 & 0x0F) // Page 10-0x42[2:0]
// 0 ~ 8 (0: PAD2i<I>, 1: PAD2o<PP>, 2: PAD2o<OD>, 3: TCON[0], 4: Test4b_out0,
//        5: Test4b_out1, 6:reserved, 7: reserved, 8: TXD)

#define _PIN_AG29                               (0 & 0x07) // Page 10-0x43[2:0]
// 0 ~ 7 (0: PAD3i<I>, 1: PAD3o<PP>, 2: PAD3o<OD>, 3: TCON[13], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

#define _PIN_AH25                               (0 & 0x07) // Page 10-0x44[2:0]
// 0 ~ 5 (0: PAD4i<I>, 1: PAD4o<PP>, 2: PAD4o<OD>, 3: TCON[12], 4: Sd3,
//        5: Spdif3)

#define _PIN_AF29                               (0 & 0x07) // Page 10-0x45[2:0]
// 0 ~ 5 (0: PAD5i<I>, 1: PAD5o<PP>, 2: PAD5o<OD>, 3: TCON[11], 4: Sd2,
//        5: Spdif2)

#define _PIN_AJ25                               (0 & 0x07) // Page 10-0x46[2:0]
// 0 ~ 5 (0: PAD6i<I>, 1: PAD6o<PP>, 2: PAD6o<OD>, 3: TCON[10], 4: Sd1,
//        5: Spdif1)

#define _PIN_AG28                               (0 & 0x07) // Page 10-0x47[2:0]
// 0 ~ 5 (0: PAD7i<I>, 1: PAD7o<PP>, 2: PAD7o<OD>, 3: TCON[9], 4: Sd0,
//        5: Spdif0)

#define _PIN_AH24                               (0 & 0x07) // Page 10-0x48[2:0]
// 0 ~ 7 (0: PBD0i<I>, 1: PBD0o<PP>, 2: PBD0o<OD>, 3: TCON[8], 4: Test4b_out0,
//        5: Test4b_out1, 6: Test4b_out2, 7: Test4b_out3)

#define _PIN_AF27                               (0 & 0x07) // Page 10-0x49[2:0]
// 0 ~ 7 (0: PBD1i<I>, 1: PBD1o<PP>, 2: PBD1o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3, 7: Mck)

#define _PIN_AJ24                               (0 & 0x07) // Page 10-0x4A[2:0]
// 0 ~ 7 (0: PBD2i<I>, 1: PBD2o<PP>, 2: PBD2o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3, 7: Sck)

#define _PIN_AG27                               (0 & 0x07) // Page 10-0x4B[2:0]
// 0 ~ 7 (0: PBD3i<I>, 1: PBD3o<PP>, 2: PBD3o<OD>, 3: Test4b_out0, 4: Test4b_out1,
//        5: Test4b_out2, 6: Test4b_out3, 7: Ws)

#define _PIN_AJ18                               (0 & 0x07) // Page 10-0x4C[2:0]
// 0 ~ 4 (0: PBD4i<I>, 1: PBD4o<PP>, 2: PBD4o<OD>, 3: Line_inl, 4: Ws)

#define _PIN_AK18                               (0 & 0x07) // Page 10-0x4D[2:0]
// 0 ~ 4 (0: PBD5i<I>, 1: PBD5o<PP>, 2: PBD5o<OD>, 3: Line_inr, 4: Sck)

#define _PIN_AE20                               (0 & 0x07) // Page 10-0x4E[2:0]
// 0 ~ 4 (0: PBD6i<I>, 1: PBD6o<PP>, 2: PBD6o<OD>, 3: Audio_ref, 4: Mck)

#define _PIN_AL18                               (0 & 0x07) // Page 10-0x4F[2:0]
// 0 ~ 5 (0: PBD7i<I>, 1: PBD7o<PP>, 2: PBD7o<OD>, 3: Audio_soutl, 4: Sdo,
//        5: Spdif0)

#define _PIN_AM18                               (0 & 0x07) // Page 10-0x50[2:0]
// 0 ~ 5 (0: PCD0i<I>, 1: PCD0o<PP>, 2: PCD0o<OD>, 3: Audio_soutr, 4: Sd1,
//        5: Spdif1)

#define _PIN_AL19                               (0 & 0x07) // Page 10-0x51[2:0]
// 0 ~ 5 (0: PCD1i<I>, 1: PCD1o<PP>, 2: PCD1o<OD>, 3: Audio_houtl, 4: Sd2,
//        5: Spdif2)

#define _PIN_AM19                               (0 & 0x07) // Page 10-0x52[2:0]
// 0 ~ 5 (0: PCD2i<I>, 1: PCD2o<PP>, 2: PCD2o<OD>, 3: Audio_houtr, 4: Sd3,
//        5: Spdif3)

#define _PIN_AJ11                               (0 & 0x07) // Page 10-0x53[2:0]
// 0 ~ 3 (0: PCD3i<I>, 1: PCD3o<PP>, 2: PCD3o<OD>, 3: Dptx_aux_ch_p)

#define _PIN_AJ12                               (0 & 0x07) // Page 10-0x54[2:0]
// 0 ~ 3 (0: PCD4i<I>, 1: PCD4o<PP>, 2: PCD4o<OD>, 3: Dptx_aux_ch_n)

#define _PIN_AG6                                (0 & 0x07) // Page 10-0x55[2:0]
// 0 ~ 3 (0: PCD5i<I>, 1: PCD5o<PP>, 2: PCD5o<OD>, 3: Dptx_hpd_org)

#define _PIN_AJ4                                (0 & 0x07) // Page 10-0x56[2:0]
// 0 ~ 2 (0: PCD6i<I>, 1: PCD6o<PP>, 2: PCD6o<OD>)

#define _PIN_AF7                                (0 & 0x07) // Page 10-0x57[2:0]
// 0 ~ 2 (0: PCD7i<I>, 1: PCD7o<PP>, 2: PCD7o<OD>)

#define _PIN_AF6                                (0 & 0x07) // Page 10-0x58[2:0]
// 0 ~ 2 (0: PDD0i<I>, 1: PDD0o<PP>, 2: PDD0o<OD>)

#define _PIN_AG7                                (0 & 0x07) // Page 10-0x59[2:0]
// 0 ~ 2 (0: PDD1i<I>, 1: PDD1o<PP>, 2: PDD1o<OD>)

#define _PIN_AH7                                (0 & 0x07) // Page 10-0x5A[2:0]
// 0 ~ 2 (0: PDD2i<I>, 1: PDD2o<PP>, 2: PDD2o<OD>)

#define _PIN_AH6                                (0 & 0x07) // Page 10-0x5B[2:0]
// 0 ~ 2 (0: PDD3i<I>, 1: PDD3o<PP>, 2: PDD3o<OD>)

#define _PIN_AH5                                (0 & 0x07) // Page 10-0x5C[2:0]
// 0 ~ 2 (0: PDD4i<I>, 1: PDD4o<PP>, 2: PDD4o<OD>)

#define _PIN_AG8                                (0 & 0x07) // Page 10-0x5D[2:0]
// 0 ~ 6 (0: PDD5i<I>, 1: PDD5o<PP>, 2: PDD5o<OD>, 3: PWM1<PP>, 4: PWM1<OD>,
//        5:TCON[7], 6:IICSCL2)

#define _PIN_AG9                                (0 & 0x07) // Page 10-0x5E[2:0]
// 0 ~ 6 (0: PDD6i<I>, 1: PDD6o<PP>, 2: PDD6o<OD>, 3: PWM0<PP>, 4: PWM0<OD>,
//        5:TCON[3], 6:IICSDA2)

#define _PIN_J6                                 (0 & 0x07) // Page 10-0x5F[2:0]
// 0 ~ 3 (0: PDD7i<I>, 1: reserved, 2: PDD7o<OD>, 3: DDCSCL5)

#define _PIN_J5                                 (0 & 0x07) // Page 10-0x60[2:0]
// 0 ~ 3 (0: PED0i<I>, 1: reserved, 2: PED0o<OD>, 3: DDCSDA5)

#define _PIN_K6                                 (0 & 0x07) // Page 10-0x61[2:0]
// 0 ~ 3 (0: PED1i<I>, 1: reserved, 2: PED1o<OD>, 3: DDCSCL4)

#define _PIN_K5                                 (0 & 0x07) // Page 10-0x62[2:0]
// 0 ~ 3 (0: PED2i<I>, 1: reserved, 2: PED2o<OD>, 3: DDCSDA4)

#define _PIN_L6                                 (0 & 0x07) // Page 10-0x63[2:0]
// 0 ~ 3 (0: PED3i<I>, 1: reserved, 2: PED3o<OD>, 3: DDCSCL3)

#define _PIN_L5                                 (0 & 0x07) // Page 10-0x64[2:0]
// 0 ~ 3 (0: PED4i<I>, 1: reserved, 2: PED4o<OD>, 3: DDCSDA3)

#define _PIN_M6                                 (0 & 0x07) // Page 10-0x65[2:0]
// 0 ~ 3 (0: PED5i<I>, 1: reserved, 2: PED5o<OD>, 3: DDCSCL2)

#define _PIN_M5                                 (0 & 0x07) // Page 10-0x66[2:0]
// 0 ~ 3 (0: PED6i<I>, 1: reserved, 2: PED6o<OD>, 3: DDCSDA2)

#define _PIN_H7                                 (0 & 0x07) // Page 10-0x67[2:0]
// 0 ~ 3 (0: PED7i<I>, 1: PED7o<PP>, 2: PED7o<OD>)

#define _PIN_K7                                 (0 & 0x07) // Page 10-0x68[2:0]
// 0     (0: PFD0i<I>)

#define _PIN_C8                                 (0 & 0x07) // Page 10-0x69[2:0]
// 0 ~ 2 (0: PFD1i<I>, 1: PFD1o<PP>, 2: PFD1o<OD>)

#define _PIN_N6                                 (0 & 0x07) // Page 10-0x6A[2:0]
// 0 ~ 2 (0: PFD2i<I>, 1: PFD2o<PP>, 2: PFD2o<OD>)

#define _PIN_C6                                 (0 & 0x07) // Page 10-0x6B[2:0]
// 0 ~ 2 (0: PFD3i<I>, 1: PFD3o<PP>, 2: PFD3o<OD>)

#define _PIN_N5                                 (0 & 0x07) // Page 10-0x6C[2:0]
// 0 ~ 2 (0: PFD4i<I>, 1: PFD4o<PP>, 2: PFD4o<OD>)


//////////////////////
// GPIO Power Macro //
//////////////////////

//-----------------------------------------------
// Macro of Pcb GPIO Inital Setting
//-----------------------------------------------
#define PCB_GPIO_ON_REGION_INITIAL_SETTING()    {\
                                                }

//-----------------------------------------------
// Power OFF Region GPIO Initial Setting
// N28,N29,M28,M29,J29,N27,K27,M27,K29,J28
// J27,K28
//-----------------------------------------------
#define PCB_GPIO_OFF_REGION_INITIAL_SETTING()   {\
                                                }

#define PCB_GPIO_SETTING_POWER_AC_ON()          {\
                                                }

#define PCB_GPIO_SETTING_POWER_NORMAL()         {\
                                                }

#define PCB_GPIO_SETTING_POWER_SAVING()         {\
                                                }

#define PCB_GPIO_SETTING_POWER_DOWN()           {\
                                                }


/////////////////////
// PCB Power Macro //
/////////////////////

//-----------------------------------------------
// Macro of VCCK_OFF Power Control
//-----------------------------------------------
#define bVCCKOFFPOWER                           (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _VCCK_OFF_POWER_ON                      1
#define _VCCK_OFF_POWER_OFF                     0
#define _VCCK_OFF_TIME_POLLING_POWER_ON         20 // ms

#define PCB_VCCK_OFF_POWER(x)                   {\
                                                    bVCCKOFFPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of DDR Poewr Control
//-----------------------------------------------
#define bDDRPOWER                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _DDR_POWER_ON                           1
#define _DDR_POWER_OFF                          0

#define PCB_DDR_POWER(x)                        {\
                                                    bDDRPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of Power Board Low Power Pin High/Low
//-----------------------------------------------
#define bPOWERBOARDPOWER                        (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _LOW_POWER_ON                           1
#define _LOW_POWER_OFF                          0

#define PCB_POWERBOARD_LOWPOWER(x)              {\
                                                    bPOWERBOARDPOWER = (x);\
                                                }

//-----------------------------------------------
// Macro of 12V to 5V Regulator for MyDP or MHL
//-----------------------------------------------
#define bREGULATOR_5V                           (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _REGULATOR_5V_ON                        0
#define _REGULATOR_5V_OFF                       1

#define PCB_REGULATOR_5V_OUT(x)                 {\
                                                    bREGULATOR_5V = (x);\
                                                }


////////////////////
// DP Power Macro //
////////////////////

//-----------------------------------------------
// Macro of MyDP Power Control
//-----------------------------------------------
#define bD0_MYDP_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_MYDP_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_MYDP_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _MYDP_5V_POWER_ON                       1
#define _MYDP_5V_POWER_OFF                      0

#define PCB_D0_MYDP_POWER(x)                    {\
                                                    bD0_MYDP_POWER = (x);\
                                                }

#define PCB_D1_MYDP_POWER(x)                    {\
                                                    bD1_MYDP_POWER = (x);\
                                                }

#define PCB_D6_MYDP_POWER(x)                    {\
                                                    bD6_MYDP_POWER = (x);\
                                                }

//-----------------------------------------------
// Macro of DP1.2 Power Control
//-----------------------------------------------
#define bD0_DP12_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_DP12_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_DP12_POWER                          (MCU_EMPTY_PIN_ASSIGN_ADDRESS)


#define _DP12_33V_POWER_ON                      1
#define _DP12_33V_POWER_OFF                     0

#define PCB_D0_DP12_POWER(x)                    {\
                                                    bD0_DP12_POWER = (x);\
                                                }

#define PCB_D1_DP12_POWER(x)                    {\
                                                    bD1_DP12_POWER = (x);\
                                                }

#define PCB_D6_DP12_POWER(x)                    {\
                                                    bD6_DP12_POWER = (x);\
                                                }

//-----------------------------------------------
// Macro of MyDP & DP1.2 Power Select
//-----------------------------------------------
#define bD0_D12_MYDP_SEL                        (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_D12_MYDP_SEL                        (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_D12_MYDP_SEL                        (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _DP12_33V_POWER                         0
#define _MYDP_5V_POWER                          1

#define PCB_D0_DP12_MYDP_POWER_SELECT(x)        {\
                                                    bD0_D12_MYDP_SEL = (x);\
                                                }

#define PCB_D1_DP12_MYDP_POWER_SELECT(x)        {\
                                                    bD1_D12_MYDP_SEL = (x);\
                                                }

#define PCB_D6_DP12_MYDP_POWER_SELECT(x)        {\
                                                    bD6_D12_MYDP_SEL = (x);\
                                                }


///////////////////////
// Panel Power Macro //
///////////////////////

//--------------------------------------------------
// Macro of Panel Power Up/Down
//--------------------------------------------------
#define bPANELPOWER                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _PANEL_CONTROL_ON                       0
#define _PANEL_CONTROL_OFF                      1

#define PCB_PANEL_POWER(x)                      {\
                                                    bPANELPOWER = (x);\
                                                }

#define PCB_PANEL_POWER_DETECT()                (bPANELPOWER)

//--------------------------------------------------
// Macro of Light Power Up/Down
//--------------------------------------------------
#define bBACKLIGHTPOWER                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _LIGHT_CONTROL_ON                       0
#define _LIGHT_CONTROL_OFF                      1

#define PCB_BACKLIGHT_POWER_PIN(x)              {\
                                                    bBACKLIGHTPOWER = (x);\
                                                }

#define PCB_BACKLIGHT_POWER(x)                  {\
                                                    if((x) == _LIGHT_CONTROL_ON)\
                                                    {\
                                                        ScalerTimerActiveTimerEvent(SEC(60), _USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                        ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, (((DWORD)_PANEL_TYP_FRAME_RATE * 60) / 100));\
                                                    }\
                                                    else\
                                                    {\
                                                        ScalerTimerCancelTimerEvent(_USER_TIMER_EVENT_PANEL_USED_TIMER);\
                                                    }\
                                                    PCB_BACKLIGHT_POWER_PIN(x)\
                                                }


//////////////////////////////////////
// eDPTx Panel Power Sequence Macro //
//////////////////////////////////////

//--------------------------------------------------
// eDPTx 1.1 Panel Power Sequence Macro
//--------------------------------------------------
#define PCB_DPTX1_POWER_SEQUENCE(x)             {\
                                                }

#define PCB_DPTX2_POWER_SEQUENCE(x)             {\
                                                }

//--------------------------------------------------
// eDPTx 1.2 Panel Power Sequence Macro
//--------------------------------------------------
#define PCB_DPTX_POWER_SEQUENCE(x)              {\
                                                }

//--------------------------------------------------
// Definitions of eDP Panel Power Sequence
//
// Panel On Sequence
//       _________       ________      ________
//       |       |       |      |      |      |
// ______|       |_______|      |______|      |______
//
//   Panel_On  HPD_ON    LT    IDLE   VIDEO  BL_ON
//
// Panel Off Sequence
//
//       _________
//       |       |
// ______|       |_______
//
//    BL_OFF    IDLE
//--------------------------------------------------
#define _DPTX_POWER_SEQUENCE_PANEL_ON           _HIGH
#define _DPTX_POWER_SEQUENCE_HPD_ON             _LOW
#define _DPTX_POWER_SEQUENCE_LINK_TRAINING      _HIGH
#define _DPTX_POWER_SEQUENCE_IDLE_PATTERN       _LOW
#define _DPTX_POWER_SEQUENCE_VIDEO_PATTERN      _HIGH
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_ON       _LOW
#define _DPTX_POWER_SEQUENCE_BACKLIGHT_OFF      _HIGH


/////////////////////////
// Write Protect Macro //
/////////////////////////

//-----------------------------------------------
// Macro of Flash write protect pin
//-----------------------------------------------
#define bFLASH_WRITE_PROTECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _FLASH_WRITE_PROTECT_ENABLE             0
#define _FLASH_WRITE_PROTECT_DISABLE            1

#define PCB_FLASH_WRITE_PROTECT(x)              {\
                                                    bFLASH_WRITE_PROTECT = (x);\
                                                }

//-----------------------------------------------
// Macro of System Eeprom WP High/Low
//-----------------------------------------------
#define bEEPROM_WRITE_PROTECT                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _EEPROM_WP_ENABLE                       1
#define _EEPROM_WP_DISABLE                      0

#define PCB_EEPROM_WRITE_PROTECT(x)             {\
                                                    bEEPROM_WRITE_PROTECT = (x);\
                                                }

#define PCB_EEPROM_WRITE_PROTECT_DETECT()       (bEEPROM_WRITE_PROTECT)

//-----------------------------------------------
// Macro of EDID Eeprom WP High/Low
//-----------------------------------------------
#define bEDID_WRITE_PROTECT                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _EDID_EEPROM_WP_ENABLE                  1
#define _EDID_EEPROM_WP_DISABLE                 0

#define PCB_A0_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D2_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D3_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D4_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }

#define PCB_D5_EDID_EEPROM_WRITE_PROTECT(x)     {\
                                                    bEDID_WRITE_PROTECT = (x);\
                                                }


////////////////////////
// Cable Status Macro //
////////////////////////

//-----------------------------------------------
// Macro of Input Cable Connect
//-----------------------------------------------
#define bD0_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD0_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD0_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD1_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD6_DP_PIN15_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_DP_PIN16_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_DP_PIN17_CONNECT                    (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

// For DP Type-C
#define bD0_USB_TYPEC_AUXP_CONNECT              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD0_USB_TYPEC_AUXN_CONNECT              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD1_USB_TYPEC_AUXP_CONNECT              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_USB_TYPEC_AUXN_CONNECT              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define bD6_USB_TYPEC_AUXP_CONNECT              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_USB_TYPEC_AUXN_CONNECT              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)


#define bA0_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD0_CONNECT                             (((bit)bD0_DP_PIN15_CONNECT == _TRUE) && ((bit)bD0_DP_PIN16_CONNECT == _TRUE) && ((bit)bD0_DP_PIN17_CONNECT == _FALSE))
#define bD1_CONNECT                             (((bit)bD1_DP_PIN15_CONNECT == _TRUE) && ((bit)bD1_DP_PIN16_CONNECT == _TRUE) && ((bit)bD1_DP_PIN17_CONNECT == _FALSE))
#define bD2_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD4_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD5_CONNECT                             (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD6_CONNECT                             (((bit)bD6_DP_PIN15_CONNECT == _TRUE) && ((bit)bD6_DP_PIN16_CONNECT == _TRUE) && ((bit)bD6_DP_PIN17_CONNECT == _FALSE))

// For DP Type-C
#define bD0_CONNECT                             (((bit)bD0_USB_TYPEC_AUXP_CONNECT == _TRUE) && ((bit)bD0_USB_TYPEC_AUXN_CONNECT == _FALSE))
#define bD1_CONNECT                             (((bit)bD1_USB_TYPEC_AUXP_CONNECT == _TRUE) && ((bit)bD1_USB_TYPEC_AUXN_CONNECT == _FALSE))
#define bD6_CONNECT                             (((bit)bD6_USB_TYPEC_AUXP_CONNECT == _TRUE) && ((bit)bD6_USB_TYPEC_AUXN_CONNECT == _FALSE))

#define PCB_A0_PIN()                            (bA0_CONNECT)
#define PCB_D0_PIN()                            (bD0_CONNECT)
#define PCB_D1_PIN()                            (bD1_CONNECT)
#define PCB_D2_PIN()                            (bD2_CONNECT)
#define PCB_D3_PIN()                            (bD3_CONNECT)
#define PCB_D4_PIN()                            (bD4_CONNECT)
#define PCB_D5_PIN()                            (bD5_CONNECT)
#define PCB_D6_PIN()                            (bD6_CONNECT)

//-----------------------------------------------
// Macro of DP Source Power
//-----------------------------------------------
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_DP_PIN17_CONNECT)
#define GET_PCB_D1_DP_SOURCE_POWER()            (bD1_DP_PIN17_CONNECT)
#define GET_PCB_D6_DP_SOURCE_POWER()            (bD6_DP_PIN17_CONNECT)

// For DP Type-C
#define GET_PCB_D0_DP_SOURCE_POWER()            (bD0_USB_TYPEC_AUXN_CONNECT)
#define GET_PCB_D1_DP_SOURCE_POWER()            (bD1_USB_TYPEC_AUXN_CONNECT)
#define GET_PCB_D6_DP_SOURCE_POWER()            (bD6_USB_TYPEC_AUXN_CONNECT)

//-----------------------------------------------
// Macro of MHL Cable Connect
//-----------------------------------------------
#define bD2_MHL_CONNECT                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_MHL_CONNECT                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD4_MHL_CONNECT                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD5_MHL_CONNECT                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_D2_MHL_DETECT()                     (bD2_MHL_CONNECT)
#define PCB_D3_MHL_DETECT()                     (bD3_MHL_CONNECT)
#define PCB_D4_MHL_DETECT()                     (bD4_MHL_CONNECT)
#define PCB_D5_MHL_DETECT()                     (bD5_MHL_CONNECT)


////////////////////
// Hot Plug Macro //
////////////////////

//-----------------------------------------------
// Macro of Digital Hot Plug High/Low
//-----------------------------------------------
#define bD0_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD1_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD2_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD4_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD5_HPD                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _D0_HOT_PLUG_HIGH                       1
#define _D0_HOT_PLUG_LOW                        0

#define _D1_HOT_PLUG_HIGH                       1
#define _D1_HOT_PLUG_LOW                        0

#define _D2_HOT_PLUG_HIGH                       1
#define _D2_HOT_PLUG_LOW                        0

#define _D3_HOT_PLUG_HIGH                       1
#define _D3_HOT_PLUG_LOW                        0

#define _D4_HOT_PLUG_HIGH                       1
#define _D4_HOT_PLUG_LOW                        0

#define _D5_HOT_PLUG_HIGH                       1
#define _D5_HOT_PLUG_LOW                        0

#define PCB_D0_HOTPLUG(x)                       {\
                                                    bD0_HPD = (x);\
                                                }

#define PCB_D1_HOTPLUG(x)                       {\
                                                    bD1_HPD = (x);\
                                                }

#define PCB_D2_HOTPLUG(x)                       {\
                                                    bD2_HPD = (x);\
                                                }

#define PCB_D3_HOTPLUG(x)                       {\
                                                    bD3_HPD = (x);\
                                                }

#define PCB_D4_HOTPLUG(x)                       {\
                                                    bD4_HPD = (x);\
                                                }

#define PCB_D5_HOTPLUG(x)                       {\
                                                    bD5_HPD = (x);\
                                                }

#define PCB_D0_HOTPLUG_DETECT()                 (bD0_HPD)
#define PCB_D1_HOTPLUG_DETECT()                 (bD1_HPD)
#define PCB_D2_HOTPLUG_DETECT()                 (bD2_HPD)
#define PCB_D3_HOTPLUG_DETECT()                 (bD3_HPD)
#define PCB_D4_HOTPLUG_DETECT()                 (bD4_HPD)
#define PCB_D5_HOTPLUG_DETECT()                 (bD5_HPD)


//////////////////////////////////////
// DP D0 & D6 External Switch Macro //
//////////////////////////////////////

//-----------------------------------------------
// Macro of D6 Switch Power
//-----------------------------------------------
#define bDIGITAL_D6_SWITCH_POWER                (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _DIGITAL_D6_SWITCH_POWER_ON             1
#define _DIGITAL_D6_SWITCH_POWER_DOWN           0

#define PCB_DIGITAL_D6_SWITCH_POWER(x)          {\
                                                    bDIGITAL_D6_SWITCH_POWER = (x);\
                                                }

//-----------------------------------------------
// Macro of D6 Switch Lane & Aux_HPD Macro
//-----------------------------------------------
#define bDIGITAL_D6_SWITCH_LANE                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bDIGITAL_D6_SWITCH_AUX_HPD              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _DP_D0_D6_SWITCH_D0                     1
#define _DP_D0_D6_SWITCH_D6                     0

#define PCB_DIGITAL_D0_D6_SWITCH_LANE(x)        {\
                                                    bDIGITAL_D6_SWITCH_LANE = (x);\
                                                }

#define PCB_DIGITAL_D0_D6_SWITCH_AUX_HPD(x)     {\
                                                    bDIGITAL_D6_SWITCH_AUX_HPD = (x);\
                                                }


///////////////
// MHL Macro //
///////////////

//-----------------------------------------------
// Macro of HDMI/MHL Switch
//-----------------------------------------------
#define bD2_TMDS_SWITCH                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_TMDS_SWITCH                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD4_TMDS_SWITCH                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD5_TMDS_SWITCH                         (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _TMDS_SWITCH_MHL_CBUS                   0
#define _TMDS_SWITCH_HDMI_HPD                   1

#define PCB_D2_HDMI_MHL_SWITCH(x)               {\
                                                    bD2_TMDS_SWITCH = (x);\
                                                }

#define PCB_D3_HDMI_MHL_SWITCH(x)               {\
                                                    bD3_TMDS_SWITCH = (x);\
                                                }

#define PCB_D4_HDMI_MHL_SWITCH(x)               {\
                                                    bD4_TMDS_SWITCH = (x);\
                                                }

#define PCB_D5_HDMI_MHL_SWITCH(x)               {\
                                                    bD5_TMDS_SWITCH = (x);\
                                                }

//-----------------------------------------------
// Macro of MHL VBus Switch
//-----------------------------------------------
#define bD2_MHL_VBUS_SWITCH                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_MHL_VBUS_SWITCH                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD4_MHL_VBUS_SWITCH                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD5_MHL_VBUS_SWITCH                     (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _MHL_VBUS_ON                            1
#define _MHL_VBUS_OFF                           0

#define PCB_D2_MHL_VBUS_SWITCH(x)               {\
                                                    bD2_MHL_VBUS_SWITCH = (x);\
                                                    PCB_MHL_VBUS_POWER(x);\
                                                }

#define PCB_D3_MHL_VBUS_SWITCH(x)               {\
                                                    bD3_MHL_VBUS_SWITCH = (x);\
                                                    PCB_MHL_VBUS_POWER(x);\
                                                }

#define PCB_D4_MHL_VBUS_SWITCH(x)               {\
                                                    bD4_MHL_VBUS_SWITCH = (x);\
                                                    PCB_MHL_VBUS_POWER(x);\
                                                }

#define PCB_D5_MHL_VBUS_SWITCH(x)               {\
                                                    bD5_MHL_VBUS_SWITCH = (x);\
                                                    PCB_MHL_VBUS_POWER(x);\
                                                }

#define PCB_GET_D2_MHL_VBUS_SWITCH()            (bD2_MHL_VBUS_SWITCH)
#define PCB_GET_D3_MHL_VBUS_SWITCH()            (bD3_MHL_VBUS_SWITCH)
#define PCB_GET_D4_MHL_VBUS_SWITCH()            (bD4_MHL_VBUS_SWITCH)
#define PCB_GET_D5_MHL_VBUS_SWITCH()            (bD5_MHL_VBUS_SWITCH)

//-----------------------------------------------
// Macro of MHL VBUS 5V Power Control
//-----------------------------------------------
#define PCB_MHL_VBUS_POWER(x)                   {\
                                                    if((x) == _MHL_VBUS_ON)\
                                                    {\
                                                        PCB_REGULATOR_5V_OUT(_REGULATOR_5V_ON);\
                                                    }\
                                                    else\
                                                    {\
                                                        if(ScalerSyncMHLVBusPowerExist() == _FALSE)\
                                                        {\
                                                            PCB_REGULATOR_5V_OUT(_REGULATOR_5V_OFF);\
                                                        }\
                                                    }\
                                                }


///////////////
// PWM Macro //
///////////////

//-----------------------------------------------
// Macro of Pcb PWM Inital Setting
//-----------------------------------------------
#define PCB_PWM_SETTING()                       {\
                                                    ScalerMcuPwmAdjustFrequency(_BACKLIGHT_PWM, 240);\
                                                }

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_8BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKLIGHT_PWM()                 (MCU_GET_8BIT_PWM_DUTY(_BACKLIGHT_PWM))

#elif(_PWM_DUT_RESOLUTION == _PWM_12BIT)

#define PCB_BACKLIGHT_PWM(x)                    {\
                                                    MCU_ADJUST_12BIT_PWM_DUTY(_BACKLIGHT_PWM, (x));\
                                                }

#define PCB_GET_BACKLIGHT_PWM()                 (MCU_GET_12BIT_PWM_DUTY(_BACKLIGHT_PWM))

#endif


//////////////////
// SW IIC Macro //
//////////////////

//--------------------------------------------------
// Macro of IIC : (_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
#define bSWIIC_SYS_EEPROM_SCL                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bSWIIC_SYS_EEPROM_SDA                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_SW_IIC_SDA_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SDA = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SDA_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SDA;\
                                                    }\
                                                }

#define PCB_SW_IIC_SCL_SET()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _TRUE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CLR()                    {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        bSWIIC_SYS_EEPROM_SCL = _FALSE;\
                                                    }\
                                                }
#define PCB_SW_IIC_SCL_CHK(x)                   {\
                                                    if(GET_SW_IIC_STATUS() == _IIC_SYS_EEPROM)\
                                                    {\
                                                        (x) = bSWIIC_SYS_EEPROM_SCL;\
                                                    }\
                                                }


///////////////
// LED Macro //
///////////////

//--------------------------------------------------
// Macro of LED On/Off
//--------------------------------------------------
#define bLED1                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLED2                                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _LED_ON                                 1
#define _LED_OFF                                0

#define PCB_LED_AC_ON_INITIAL()                 {\
                                                }

#define PCB_LED_ACTIVE()                        {\
                                                }

#define PCB_LED_IDLE()                          {\
                                                }

#define PCB_LED_POWER_SAVING()                  {\
                                                }

#define PCB_LED_ON()                            {\
                                                }

#define PCB_LED_OFF()                           {\
                                                }

#define PCB_LED_TYPE1()                         {\
                                                }

#define PCB_LED_TYPE2()                         {\
                                                }

#define PCB_LED_TYPE3()                         {\
                                                }

#define PCB_LED_TYPE4()                         {\
                                                }

#define PCB_LED_TYPE5()                         {\
                                                }

#define PCB_LED_TYPE_FLASH()                    {\
                                                }


//////////////////
// AD Key Macro //
//////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define AD_KEY0                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define AD_KEY1                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define AD_KEY2                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define AD_KEY3                                 (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_ADKEY0()                            (_FALSE)
#define PCB_ADKEY1()                            (_FALSE)
#define PCB_ADKEY2()                            (_FALSE)
#define PCB_ADKEY3()                            (_FALSE)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                }


////////////////////
// GPIO Key Macro //
////////////////////

//-----------------------------------------------
// Macro of Keypad Setting
//-----------------------------------------------
#define bPOWER_KEY                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bMENU_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bEXIT_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bLEFT_KEY                               (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bRIGHT_KEY                              (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define PCB_KEY_STATE(ucV0, ucV1,\
                      ucV2, ucV3, ucKeyState)   {\
                                                }


//////////////////
// EEPROM Macro //
//////////////////

//-----------------------------------------------
// Macro of HDMI External EDID Switch
//-----------------------------------------------
#define bD2_EXT_SWITCH_EDID_0                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD2_EXT_SWITCH_EDID_1                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD2_EXT_SWITCH_EDID_2                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_EXT_SWITCH_EDID_0                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_EXT_SWITCH_EDID_1                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD3_EXT_SWITCH_EDID_2                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD4_EXT_SWITCH_EDID_0                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD4_EXT_SWITCH_EDID_1                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD4_EXT_SWITCH_EDID_2                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD5_EXT_SWITCH_EDID_0                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD5_EXT_SWITCH_EDID_1                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)
#define bD5_EXT_SWITCH_EDID_2                   (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _EEPROM_EDID_ENABLE                     0
#define _EEPROM_EDID_DISABLE                    1

#define PCB_D2_EXT_EDID_0_SWITCH(x)             {\
                                                    bD2_EXT_SWITCH_EDID_0 = (x);\
                                                }

#define PCB_D2_EXT_EDID_1_SWITCH(x)             {\
                                                    bD2_EXT_SWITCH_EDID_1 = (x);\
                                                }

#define PCB_D2_EXT_EDID_2_SWITCH(x)             {\
                                                    bD2_EXT_SWITCH_EDID_2 = (x);\
                                                }

#define PCB_D3_EXT_EDID_0_SWITCH(x)             {\
                                                    bD3_EXT_SWITCH_EDID_0 = (x);\
                                                }

#define PCB_D3_EXT_EDID_1_SWITCH(x)             {\
                                                    bD3_EXT_SWITCH_EDID_1 = (x);\
                                                }

#define PCB_D3_EXT_EDID_2_SWITCH(x)             {\
                                                    bD3_EXT_SWITCH_EDID_2 = (x);\
                                                }

#define PCB_D4_EXT_EDID_0_SWITCH(x)             {\
                                                    bD4_EXT_SWITCH_EDID_0 = (x);\
                                                }

#define PCB_D4_EXT_EDID_1_SWITCH(x)             {\
                                                    bD4_EXT_SWITCH_EDID_1 = (x);\
                                                }

#define PCB_D4_EXT_EDID_2_SWITCH(x)             {\
                                                    bD4_EXT_SWITCH_EDID_2 = (x);\
                                                }

#define PCB_D5_EXT_EDID_0_SWITCH(x)             {\
                                                    bD5_EXT_SWITCH_EDID_0 = (x);\
                                                }

#define PCB_D5_EXT_EDID_1_SWITCH(x)             {\
                                                    bD5_EXT_SWITCH_EDID_1 = (x);\
                                                }

#define PCB_D5_EXT_EDID_2_SWITCH(x)             {\
                                                    bD5_EXT_SWITCH_EDID_2 = (x);\
                                                }


/////////////////
// Audio Macro //
/////////////////

//-----------------------------------------------
// Macro of PCB Audio Connect
//-----------------------------------------------
#define bAudioDetect                            (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _AUDIO_CONNECT                          0
#define _AUDIO_DISCONNECT                       1

#define PCB_AUDIO_DETECT()                      (bAudioDetect)

//-----------------------------------------------
// Macro of PCB Audio AMP Control
//-----------------------------------------------
#define bPCBAMPMUTECONTROL                      (MCU_EMPTY_PIN_ASSIGN_ADDRESS)

#define _AMP_MUTE_ON                            0
#define _AMP_MUTE_OFF                           1

#define PCB_AMP_MUTE(x)                         {\
                                                    bPCBAMPMUTECONTROL = (x);\
                                                }

#endif // End of #if(_PCB_TYPE == _RL6410_PCB_EXAMPLE)
