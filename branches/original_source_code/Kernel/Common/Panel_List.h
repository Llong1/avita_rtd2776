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
// ID Code      : Panel_List.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __PANEL_LIST_H__
#define __PANEL_LIST_H__

//--------------------------------------------------
// Definitions for Panel Manufacturer
//--------------------------------------------------
#define _PANEL_NONE_BRAND                       0
#define _PANEL_AUO                              1
#define _PANEL_CMO                              2
#define _PANEL_CPT                              3
#define _PANEL_HSD                              4
#define _PANEL_SAMSUNG                          5
#define _PANEL_LGD                              6
#define _PANEL_SVA                              7
#define _PANEL_BOE                              8
#define _PANEL_INNOLUX                          9
#define _PANEL_QISDA                            10

//--------------------------------------------------
// Definitions for Panel Settings
//--------------------------------------------------
#define _PANEL_NONE                             0
#define _PANEL_TTL                              1
#define _PANEL_LVDS                             2
#define _PANEL_RSDS                             3
#define _PANEL_VBO                              4
#define _PANEL_DPTX                             5

//--------------------------------------------------
// Definitions for Panel Bit Length
//--------------------------------------------------
#define _PANEL_DISP_18_BIT                      0
#define _PANEL_DISP_24_BIT                      1
#define _PANEL_DISP_30_BIT                      2
#define _PANEL_DISP_36_BIT                      3
#define _PANEL_DISP_48_BIT                      4

//--------------------------------------------------
// Definitions for LVDS Port Counts
//--------------------------------------------------
#define _LVDS_1_PORT                            0
#define _LVDS_2_PORT                            1
#define _LVDS_4_PORT                            2
#define _LVDS_8_PORT                            3

//--------------------------------------------------
// Definitions for LVDS Bit Map Table
//--------------------------------------------------
#define _LVDS_BIT_MAP_TABLE_1_3                 0
#define _LVDS_BIT_MAP_TABLE_2_4                 1

//--------------------------------------------------
// Definitions for LVDS Panel Type
//--------------------------------------------------
#define _LVDS_PANEL_1_SECTION                   0
#define _LVDS_PANEL_2_SECTION                   1
#define _LVDS_PANEL_4_SECTION                   2
#define _LVDS_PANEL_8_SECTION                   3

//--------------------------------------------------
// Definitions for TTL Port Counts
//--------------------------------------------------
#define _TTL_1_PORT                             0
#define _TTL_2_PORT                             1

//--------------------------------------------------
// Definitions for DPTX Panel Phy Rate
//--------------------------------------------------
#define _PANEL_DPTX_LINK_RBR                    0x06
#define _PANEL_DPTX_LINK_HBR                    0x0A
#define _PANEL_DPTX_LINK_HBR2                   0x14

//--------------------------------------------------
// Definitions for DPTX Panel Phy Rate
//--------------------------------------------------
#define _PANEL_DPTX_LANE_NUMBER_1               0
#define _PANEL_DPTX_LANE_NUMBER_2               1
#define _PANEL_DPTX_LANE_NUMBER_4               2
#define _PANEL_DPTX_LANE_NUMBER_8               3

//--------------------------------------------------
// Definitions for DPTX Panel Vendor Specific Type List
//--------------------------------------------------
#define _PANEL_DPTX_VENDOR_SPECIFIC_NONE        0
#define _PANEL_DPTX_VENDOR_SPECIFIC_004F1H      1

//--------------------------------------------------
// Definitions for Vby1 Bit Length
//--------------------------------------------------
#define _VBO_DISP_30_BIT                        1
#define _VBO_DISP_24_BIT                        2
#define _VBO_DISP_18_BIT                        3

//--------------------------------------------------
// Definitions for Vby1 Lane Count
//--------------------------------------------------
#define _VBO_1_DATA_LANE                        1
#define _VBO_2_DATA_LANE                        2
#define _VBO_4_DATA_LANE                        4
#define _VBO_8_DATA_LANE                        8

//--------------------------------------------------
// Definitions for Vby1 Panel Section
//--------------------------------------------------
#define _VBO_PANEL_1_SECTION                    1
#define _VBO_PANEL_2_SECTION                    2
#define _VBO_PANEL_4_SECTION                    4
#define _VBO_PANEL_8_SECTION                    8

//--------------------------------------------------
// Definitions for Vby1 Panel HS Control
//--------------------------------------------------
#define _VBO_HS_NORMAL                          0
#define _VBO_HS_ALWAYS_OFF                      1
#define _VBO_HS_ALWAYS_ON                       2

//--------------------------------------------------
// Definitions for Vby1 Panel VS Control
//--------------------------------------------------
#define _VBO_VS_NORMAL                          0
#define _VBO_VS_ALWAYS_OFF                      1
#define _VBO_VS_ALWAYS_ON                       2

//--------------------------------------------------
// Definitions for Vby1 Panel Video Pattern Transfer Type
//--------------------------------------------------
#define _VBO_VIDEO_TRANSFER_IN_HORIZONTAL_BLANK 0
#define _VBO_VIDEO_TRANSFER_IN_VERTICAL_BLANK   1

//--------------------------------------------------
// Definitions for Vby1 Byte Mode
//--------------------------------------------------
#define _VBO_DISP_3_BYTE_MODE                   3
#define _VBO_DISP_4_BYTE_MODE                   4
#define _VBO_DISP_5_BYTE_MODE                   5

//--------------------------------------------------
// Definitions for 2D / 3D panel type
//--------------------------------------------------
#define _PANEL_DISPLAY_NORMAL                   0
#define _PANEL_DISPLAY_SHUTTER_GLASSES          1
#define _PANEL_DISPLAY_PATTERN_RETARDER         2

//--------------------------------------------------
// Definitions for PR Panel Display Type
//--------------------------------------------------
#define _PANEL_PR_LR_DISPLAY                    0
#define _PANEL_PR_RL_DISPLAY                    1

//--------------------------------------------------
// Definitions for Panel Backlight
//--------------------------------------------------
#define _PANEL_BACKLIGHT_CCFL                   0
#define _PANEL_BACKLIGHT_LED                    1

//--------------------------------------------------
// Definitions for Panel Clk Unit
//--------------------------------------------------
#define _PANEL_CLOCK_MHZ                        0
#define _PANEL_CLOCK_KHZ                        1

//--------------------------------------------------
// Definitions for Panel Cable Type
//--------------------------------------------------
#define _LVDS_CABLE_TYPE_0                      0
#define _LVDS_CABLE_TYPE_1                      1

#endif // End of #ifndef __PANEL_LIST_H__
