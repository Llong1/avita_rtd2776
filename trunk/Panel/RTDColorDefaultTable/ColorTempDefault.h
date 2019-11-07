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
// ID Code      : ColorTempDefaultNo.0000
// Update Note  :
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// COLOR TEMP DEFAULT DATA
//****************************************************************************
#if(_CTS_TYPE == _CTS_GEN_1_12BIT)
#if(_PANEL_TYPE == _AU_LVDS_21_5_WUXGA)  ///YLI55161_Samsung55
#define _CT9300_RED                                (0x80 << 4)/// (0x62 << 4)
#define _CT9300_GREEN                            (0x80 << 4)///   (0x68 << 4)
#define _CT9300_BLUE                               (0x80 << 4)/// (0x6F << 4)
#define _CT7500_RED                                 (0x80 << 4)/// (0x68 << 4)
#define _CT7500_GREEN                             (0x74 << 4)///  (0x69 << 4)
#define _CT7500_BLUE                                (0x6F << 4)/// (0x6B << 4)
#define _CT6500_RED                                 (0x80 << 4)/// (0x71 << 4)
#define _CT6500_GREEN                             (0x6E << 4)///  (0x70 << 4)
#define _CT6500_BLUE                                (0x62 << 4)/// (0x68 << 4)
#define _CT5800_RED                                 (0x80 << 4)
#define _CT5800_GREEN                               (0x69 << 4)
#define _CT5800_BLUE                                (0x59 << 4)
#define _CTSRGB_RED                                 (0x80 << 4)
#define _CTSRGB_GREEN                               (0x69 << 4)
#define _CTSRGB_BLUE                                (0x59 << 4)
#define _CTUSER_RED                                 (0x80 << 4)
#define _CTUSER_GREEN                               (0x80 << 4)
#define _CTUSER_BLUE                                (0x80 << 4)

#elif(_PANEL_TYPE == _AU_LVDS_24_WUXGA)  ///YLI55162_LG55
#define _CT9300_RED                                (0x74 << 4)/// (0x62 << 4)
#define _CT9300_GREEN                            (0x77 << 4)///   (0x68 << 4)
#define _CT9300_BLUE                               (0x80 << 4)/// (0x6F << 4)
#define _CT7500_RED                                 (0x80 << 4)/// (0x68 << 4)
#define _CT7500_GREEN                             (0x80 << 4)///  (0x69 << 4)
#define _CT7500_BLUE                                (0x7F << 4)/// (0x6B << 4)
#define _CT6500_RED                                 (0x80 << 4)/// (0x71 << 4)
#define _CT6500_GREEN                             (0x80 << 4)///  (0x70 << 4)
#define _CT6500_BLUE                                (0x75 << 4)/// (0x68 << 4)
#define _CT5800_RED                                 (0x80 << 4)/// (0x7F << 4)
#define _CT5800_GREEN                              (0x7E << 4)/// (0x6A << 4)
#define _CT5800_BLUE                                (0x6C << 4)/// (0x5C << 4)
#define _CTSRGB_RED                                 (0x78 << 4)/// (0x7F << 4)
#define _CTSRGB_GREEN                              (0x78 << 4)///  (0x6A << 4)
#define _CTSRGB_BLUE                                (0x78 << 4)/// (0x5C << 4)
#define _CTUSER_RED                                 (0x80 << 4)/// (0x80 << 4)
#define _CTUSER_GREEN                               (0x80 << 4)/// (0x80 << 4)
#define _CTUSER_BLUE                                (0x80 << 4)/// (0x80 << 4)

#elif(_PANEL_TYPE == _AU_LVDS_23_WUXGA) ///KUI32171_AUO32
#define _CT9300_RED                                (0x80 << 4)/// (0x62 << 4)
#define _CT9300_GREEN                            (0x7E << 4)///   (0x68 << 4)
#define _CT9300_BLUE                               (0x7B << 4)/// (0x6F << 4)
#define _CT7500_RED                                 (0x80 << 4)/// (0x68 << 4)
#define _CT7500_GREEN                             (0x72 << 4)///  (0x69 << 4)
#define _CT7500_BLUE                                (0x69 << 4)/// (0x6B << 4)
#define _CT6500_RED                                 (0x80 << 4)/// (0x71 << 4)
#define _CT6500_GREEN                             (0x6B << 4)///  (0x70 << 4)
#define _CT6500_BLUE                                (0x5D << 4)/// (0x68 << 4)
#define _CT5800_RED                                 (0x80 << 4)/// (0x7F << 4)
#define _CT5800_GREEN                              (0x66 << 4)/// (0x6A << 4)
#define _CT5800_BLUE                                (0x55 << 4)/// (0x5C << 4)
#define _CTSRGB_RED                                 (0x80 << 4)/// (0x7F << 4)
#define _CTSRGB_GREEN                              (0x66 << 4)///  (0x6A << 4)
#define _CTSRGB_BLUE                                (0x55 << 4)/// (0x5C << 4)
#define _CTUSER_RED                                 (0x80 << 4)/// (0x80 << 4)
#define _CTUSER_GREEN                               (0x80 << 4)/// (0x80 << 4)
#define _CTUSER_BLUE                                (0x80 << 4)/// (0x80 << 4)

#else
#define _CT9300_RED                                (0x62 << 4)
#define _CT9300_GREEN                            (0x68 << 4)
#define _CT9300_BLUE                               (0x6F << 4)
#define _CT7500_RED                                 (0x68 << 4)
#define _CT7500_GREEN                             (0x69 << 4)
#define _CT7500_BLUE                                (0x6B << 4)
#define _CT6500_RED                                  (0x71 << 4)
#define _CT6500_GREEN                              (0x70 << 4)
#define _CT6500_BLUE                                (0x68 << 4)
#define _CT5800_RED                                 (0x7F << 4)
#define _CT5800_GREEN                              (0x6A << 4)
#define _CT5800_BLUE                                (0x5C << 4)
#define _CTSRGB_RED                                 (0x7F << 4)
#define _CTSRGB_GREEN                              (0x6A << 4)
#define _CTSRGB_BLUE                                (0x5C << 4)
#define _CTUSER_RED                                 (0x80 << 4)
#define _CTUSER_GREEN                              (0x80 << 4)
#define _CTUSER_BLUE                                (0x80 << 4)

#endif ///End _MODEL_TYPE


#else
#define _CT9300_RED                                 0x80///  0x62
#define _CT9300_GREEN                             0x74///  0x68
#define _CT9300_BLUE                                0x70/// 0x6F
#define _CT7500_RED                                 0x80///  0x68
#define _CT7500_GREEN                             0x6F///  0x69
#define _CT7500_BLUE                                0x64/// 0x6B
#define _CT6500_RED                                 0x80///  0x71
#define _CT6500_GREEN                             0x6B///  0x70
#define _CT6500_BLUE                                0x5C/// 0x68
#define _CT5800_RED                                 0x7A
#define _CT5800_GREEN                               0x77
#define _CT5800_BLUE                                0x69
#define _CTSRGB_RED                                 0x80
#define _CTSRGB_GREEN                               0x80
#define _CTSRGB_BLUE                                0x80
#define _CTUSER_RED                                 0x80
#define _CTUSER_GREEN                               0x80
#define _CTUSER_BLUE                                0x80
#endif

