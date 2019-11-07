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
// ID Code      : RTD2014OsdFontProp.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RTD_OSDFONTPROP__

#include "UserCommonInclude.h"

#if(_OSD_TYPE == _REALTEK_2014_OSD)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
BYTE code tFONT_EUROPE[] =
{
    //========Address -- (00),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (01),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (02),
    0x00,0x00,0x00,
    0x03,0x00,0x00,
    0x37,0x00,0x00,
    0xfb,0x00,0x00,
    0x33,0x00,0x00,
    0x33,0x00,0x00,
    0x33,0x00,0x00,
    0x30,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (03),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xc0,0x66,0x00,
    0x01,0xcc,0x00,
    0x33,0x80,0x00,
    0x6f,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (04),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xc0,0x6e,0x00,
    0x33,0xcc,0x00,
    0x0c,0xe6,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (05),
    0x00,0x00,0x00,
    0x00,0x0c,0x00,
    0x11,0xcc,0x00,
    0x33,0xcc,0x00,
    0x66,0xcc,0x00,
    0xcf,0xce,0x00,
    0xf0,0xec,0x00,
    0x00,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (06),
    0x00,0x00,0x00,
    0x07,0x0e,0x00,
    0x76,0xe0,0x00,
    0x6f,0x08,0x00,
    0xfc,0xce,0x00,
    0x0c,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (07),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xcf,0x08,0x00,
    0xfe,0xce,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (08),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xf0,0xec,0x00,
    0x11,0x88,0x00,
    0x33,0x00,0x00,
    0x36,0x00,0x00,
    0x66,0x00,0x00,
    0x60,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (09),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xce,0x6e,0x00,
    0x77,0xcc,0x00,
    0xec,0xe6,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (0a),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x7e,0xce,0x00,
    0xcc,0x66,0x00,
    0xe7,0xee,0x00,
    0x30,0xe6,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (0b),
    0x00,0x00,0x00,
    0x01,0x0c,0x00,
    0x11,0xcc,0x00,
    0x33,0x66,0x00,
    0x36,0x63,0x00,
    0x77,0xff,0x00,
    0x6c,0x31,0x08,
    0xc0,0x10,0x80,
    0x00,0x00,0x00,

    //========Address -- (0c),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xf3,0x00,
    0xcc,0x33,0x00,
    0xff,0xee,0x00,
    0xcc,0x33,0x00,
    0xcf,0x3f,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (0d),
    0x00,0x00,0x00,
    0x01,0x0e,0x00,
    0x76,0xf3,0x08,
    0xcc,0x10,0x00,
    0xcc,0x00,0x00,
    0xcc,0x11,0x08,
    0x67,0x3f,0x80,
    0x10,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (0e),
    0x00,0x00,0x00,
    0x0f,0x0c,0x00,
    0xfc,0xe6,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xcf,0x6e,0x00,
    0xf0,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (0f),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xe0,0x00,
    0xcc,0x00,0x00,
    0xff,0xee,0x00,
    0xcc,0x00,0x00,
    0xcf,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (10),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xe0,0x00,
    0xcc,0x00,0x00,
    0xff,0xcc,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (11),
    0x00,0x00,0x00,
    0x01,0x0e,0x00,
    0x76,0xf3,0x08,
    0xcc,0x10,0x80,
    0xcc,0x07,0x08,
    0xcc,0x71,0x88,
    0x67,0x1f,0x88,
    0x10,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (12),
    0x00,0x00,0x00,
    0x0c,0x03,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xff,0xff,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xc0,0x30,0x00,
    0x00,0x00,0x00,

    //========Address -- (13),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (14),
    0x00,0x00,0x00,
    0x00,0x06,0x00,
    0x00,0x66,0x00,
    0x00,0x66,0x00,
    0x00,0x66,0x00,
    0x0c,0x66,0x00,
    0xc7,0x6c,0x00,
    0x70,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (15),
    0x00,0x00,0x00,
    0x0c,0x01,0x08,
    0xcc,0x36,0x00,
    0xcd,0xc8,0x00,
    0xfe,0x8c,0x00,
    0xcc,0x66,0x00,
    0xcc,0x31,0x08,
    0xc0,0x10,0x80,
    0x00,0x00,0x00,

    //========Address -- (16),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcf,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (17),
    0x00,0x00,0x00,
    0x0e,0x00,0x0e,
    0xef,0x01,0xee,
    0xff,0x11,0xee,
    0xdd,0xbb,0x66,
    0xdc,0xbe,0x66,
    0xcc,0xee,0x66,
    0xc0,0xe0,0x60,
    0x00,0x00,0x00,

    //========Address -- (18),
    0x00,0x00,0x00,
    0x0c,0x03,0x00,
    0xee,0x33,0x00,
    0xff,0x33,0x00,
    0xdd,0xbb,0x00,
    0xcc,0xff,0x00,
    0xcc,0x77,0x00,
    0xc0,0x30,0x00,
    0x00,0x00,0x00,

    //========Address -- (19),
    0x00,0x00,0x00,
    0x03,0x0e,0x00,
    0x76,0xf3,0x00,
    0xcc,0x11,0x88,
    0xcc,0x11,0x88,
    0xcc,0x11,0x88,
    0x67,0x3f,0x00,
    0x30,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (1a),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xf3,0x00,
    0xcc,0x33,0x00,
    0xff,0xfe,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (1b),
    0x00,0x00,0x00,
    0x03,0x0e,0x00,
    0x76,0xf3,0x00,
    0xcc,0x11,0x88,
    0xcc,0x11,0x88,
    0xcc,0x1d,0x88,
    0x67,0x7f,0x00,
    0x30,0xf0,0xc8,
    0x00,0x00,0x00,

    //========Address -- (1c),
    0x00,0x00,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xf3,0x00,
    0xcc,0x33,0x00,
    0xff,0xfe,0x00,
    0xcc,0x33,0x00,
    0xcc,0x11,0x88,
    0xc0,0x00,0xc0,
    0x00,0x00,0x00,

    //========Address -- (1d),
    0x00,0x00,0x00,
    0x03,0x0c,0x00,
    0x7c,0xe7,0x00,
    0xce,0x30,0x00,
    0x73,0xce,0x00,
    0x0c,0x73,0x00,
    0xe7,0x3e,0x00,
    0x30,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (1e),
    0x00,0x00,0x00,
    0x0f,0x0f,0x00,
    0xf1,0xf8,0x00,
    0x11,0x88,0x00,
    0x11,0x88,0x00,
    0x11,0x88,0x00,
    0x11,0x88,0x00,
    0x10,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (1f),
    0x00,0x00,0x00,
    0x0c,0x03,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xcc,0x33,0x00,
    0xe7,0x7e,0x00,
    0x30,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (20),
    0x00,0x00,0x00,
    0x0c,0x01,0x08,
    0xc6,0x13,0x80,
    0x66,0x33,0x00,
    0x33,0x66,0x00,
    0x33,0x66,0x00,
    0x11,0xcc,0x00,
    0x10,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (21),
    0x00,0x00,0x00,
    0x0c,0x0c,0x0c,
    0xcc,0xcc,0xcc,
    0xcc,0xcc,0xcc,
    0xdd,0xee,0xcc,
    0xd7,0x23,0xc8,
    0x77,0x33,0x88,
    0x70,0x30,0x80,
    0x00,0x00,0x00,

    //========Address -- (22),
    0x00,0x00,0x00,
    0x0c,0x00,0x0c,
    0xe7,0x13,0xc8,
    0x31,0x3e,0x00,
    0x00,0xcc,0x00,
    0x13,0xe3,0x00,
    0x7e,0x31,0x8c,
    0xc0,0x00,0xc0,
    0x00,0x00,0x00,

    //========Address -- (23),
    0x00,0x00,0x00,
    0x0c,0x03,0x00,
    0xc6,0x36,0x00,
    0x63,0x6c,0x00,
    0x31,0xc8,0x00,
    0x11,0x88,0x00,
    0x11,0x88,0x00,
    0x10,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (24),
    0x00,0x00,0x00,
    0x0f,0x0f,0x00,
    0xf0,0xf7,0x00,
    0x00,0x6c,0x00,
    0x13,0x88,0x00,
    0x36,0x00,0x00,
    0xcf,0x0f,0x00,
    0xf0,0xf0,0x00,
    0x00,0x00,0x00,

    //========Address -- (25),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x7c,0xcc,0x00,
    0xcf,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (26),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xdf,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xef,0xec,0x00,
    0xd0,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (27),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0xce,0x00,
    0xec,0x60,0x00,
    0xcc,0x00,0x00,
    0xe7,0x6e,0x00,
    0x30,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (28),
    0x00,0x00,0x00,
    0x00,0x06,0x00,
    0x00,0x66,0x00,
    0x37,0x6e,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xee,0x00,
    0x30,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (29),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0x8c,0x00,
    0xcf,0x6e,0x00,
    0xfc,0xe0,0x00,
    0xe7,0x6c,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (2a),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x76,0x80,0x00,
    0xff,0x88,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x60,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (2b),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0x6e,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xee,0x00,
    0x3c,0x66,0x00,
    0x73,0xc8,0x00,

    //========Address -- (2c),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xdf,0xce,0x00,
    0xec,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xc0,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (2d),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xc0,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (2e),
    0x00,0x00,0x00,
    0x06,0x00,0x00,
    0x60,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0xec,0x00,0x00,

    //========Address -- (2f),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xcd,0xc8,0x00,
    0xdf,0x80,0x00,
    0xfd,0x88,0x00,
    0xdc,0xcc,0x00,
    0xc0,0xc0,0x00,
    0x00,0x00,0x00,

    //========Address -- (30),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (31),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xdf,0x9f,0x8c,
    0xec,0xec,0xcc,
    0xcc,0xcc,0xcc,
    0xcc,0xcc,0xcc,
    0xc0,0xc0,0xc0,
    0x00,0x00,0x00,

    //========Address -- (32),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xdf,0xce,0x00,
    0xec,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xc0,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (33),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (34),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xdf,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xef,0xec,0x00,
    0xdc,0x80,0x00,
    0xcc,0x00,0x00,

    //========Address -- (35),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0x6e,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xee,0x00,
    0x30,0x66,0x00,
    0x00,0x66,0x00,

    //========Address -- (36),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xdf,0x88,0x00,
    0xec,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (37),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x7f,0x8c,0x00,
    0xce,0xc0,0x00,
    0x71,0x8c,0x00,
    0xcf,0xcc,0x00,
    0x70,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (38),
    0x00,0x00,0x00,
    0x02,0x00,0x00,
    0x66,0x00,0x00,
    0xff,0x88,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x67,0x08,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (39),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcf,0xee,0x00,
    0x70,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (3a),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0x66,0x00,
    0xc6,0x6c,0x00,
    0x66,0xcc,0x00,
    0x33,0x88,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (3b),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0xee,0x66,
    0x66,0xee,0xcc,
    0x67,0xab,0xcc,
    0x33,0x11,0x88,
    0x30,0x10,0x80,
    0x00,0x00,0x00,

    //========Address -- (3c),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xce,0x37,0x00,
    0x63,0x6c,0x00,
    0x33,0xcc,0x00,
    0x6e,0x67,0x00,
    0xc0,0x30,0x00,
    0x00,0x00,0x00,

    //========Address -- (3d),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0x33,0x00,
    0x66,0x66,0x00,
    0x63,0x6c,0x00,
    0x33,0xcc,0x00,
    0x11,0x88,0x00,
    0xfe,0x00,0x00,

    //========Address -- (3e),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xff,0xee,0x00,
    0x01,0xc8,0x00,
    0x33,0x00,0x00,
    0x6f,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (3f),
    0x33,0x66,0x00,
    0x01,0x0c,0x00,
    0x11,0xcc,0x00,
    0x33,0x66,0x00,
    0x36,0x63,0x00,
    0x77,0xff,0x00,
    0x6c,0x31,0x08,
    0xc0,0x10,0x80,
    0x00,0x00,0x00,

    //========Address -- (40),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x60,0xc0,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (41),
    0x00,0x00,0x00,
    0x07,0x04,0x00,
    0x50,0xc0,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (42),
    0x00,0x00,0x00,
    0x01,0x08,0x00,
    0x30,0x00,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (43),
    0x00,0x00,0x00,
    0x06,0x0c,0x00,
    0x60,0xc0,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (44),
    0x00,0x00,0x00,
    0x06,0x00,0x00,
    0x30,0x00,0x00,
    0x7f,0x8c,0x00,
    0xc1,0xcc,0x00,
    0x78,0xcc,0x00,
    0x8f,0xcc,0x00,
    0x60,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (45),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x37,0xce,0x00,
    0xec,0x60,0x00,
    0xcc,0x00,0x00,
    0xe7,0x6e,0x00,
    0x37,0xc0,0x00,
    0x1e,0x00,0x00,

    //========Address -- (46),
    0x36,0x8c,0x00,
    0x0f,0x0e,0x00,
    0xfc,0xe0,0x00,
    0xcc,0x00,0x00,
    0xff,0xee,0x00,
    0xcc,0x00,0x00,
    0xcf,0x0e,0x00,
    0xf0,0xe0,0x00,
    0x00,0x00,0x00,

    //========Address -- (47),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x60,0xc0,0x00,
    0x37,0x8c,0x00,
    0xcf,0x6e,0x00,
    0xfc,0xe0,0x00,
    0xe7,0x6c,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (48),
    0x00,0x00,0x00,
    0x01,0x08,0x00,
    0x30,0x00,0x00,
    0x37,0x8c,0x00,
    0xcf,0x6e,0x00,
    0xfc,0xe0,0x00,
    0xe7,0x6c,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (49),
    0x00,0x00,0x00,
    0x03,0x00,0x00,
    0x10,0x80,0x00,
    0x37,0x8c,0x00,
    0xcf,0x6e,0x00,
    0xfc,0xe0,0x00,
    0xe7,0x6c,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (4a),
    0x00,0x00,0x00,
    0x07,0x04,0x00,
    0x50,0xc0,0x00,
    0xdf,0xce,0x00,
    0xec,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xc0,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (4b),
    0x00,0x00,0x00,
    0x01,0x08,0x00,
    0x30,0x00,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcf,0xee,0x00,
    0x70,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (4c),
    0x00,0x00,0x00,
    0x06,0x0c,0x00,
    0x60,0xc0,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcf,0xee,0x00,
    0x70,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (4d),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x60,0xc0,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcc,0x66,0x00,
    0xcf,0xee,0x00,
    0x70,0x60,0x00,
    0x00,0x00,0x00,

    //========Address -- (4e),
    0x00,0x00,0x00,
    0x01,0x08,0x00,
    0x30,0x00,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (4f),
    0x00,0x00,0x00,
    0x07,0x04,0x00,
    0x50,0xc0,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (50),
    0x00,0x00,0x00,
    0x06,0x0c,0x00,
    0x60,0xc0,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (51),
    0x00,0x00,0x00,
    0x03,0x08,0x00,
    0x60,0xc0,0x00,
    0x37,0x8c,0x00,
    0xec,0xe6,0x00,
    0xcc,0x66,0x00,
    0xe7,0xec,0x00,
    0x30,0x80,0x00,
    0x00,0x00,0x00,

    //========Address -- (52),
    0x00,0x00,0x00,
    0x06,0x00,0x00,
    0xc0,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x60,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (53),
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (54),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (55),
    0x00,0x00,0x00,
    0x12,0x00,0x00,
    0x66,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0xcc,0x00,0x00,
    0x46,0x00,0x00,
    0x62,0x00,0x00,
    0x10,0x00,0x00,

    //========Address -- (56),
    0x00,0x00,0x00,
    0x84,0x00,0x00,
    0x66,0x00,0x00,
    0x33,0x00,0x00,
    0x33,0x00,0x00,
    0x33,0x00,0x00,
    0x26,0x00,0x00,
    0x64,0x00,0x00,
    0x80,0x00,0x00,

    //========Address -- (57),
    0x00,0x00,0x00,
    0x03,0x00,0x00,
    0x33,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0x66,0x00,0x00,
    0xcc,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (58),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x0c,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xcc,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (59),
    0x00,0x00,0x00,
    0x01,0xff,0x8c,
    0x36,0x00,0x66,
    0x66,0x7d,0x6e,
    0x66,0x99,0x66,
    0x66,0xbf,0x6e,
    0x67,0x60,0xc0,
    0x30,0xff,0xec,
    0x00,0x00,0x00,

    //========Address -- (5a),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x66,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5b),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xff,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5c),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x24,0x48,0x00,
    0x99,0x00,0x00,
    0x42,0x84,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5d),
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x94,0x08,0x00,
    0x22,0x44,0x00,
    0x49,0x80,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,

    //========Address -- (5e),
#if(_FALSE_COLOR_SUPPORT == _ON)
    // %
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0xea,0x37,0x00,
    0xe0,0x6c,0x00,
    0x11,0xc8,0x00,
    0x33,0x80,0x00,
    0x6e,0x75,0x00,
    0xc0,0x70,0x00,
    0x00,0x00,0x00,
#else
    // ;
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x66,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
    0x66,0x00,0x00,
    0xc0,0x00,0x00,
    0x00,0x00,0x00,
#endif

    //========Address -- (5f),
    0x00,0x00,0x00,
    0x07,0x08,0x00,
    0xcc,0xcc,0x00,
    0x01,0xc8,0x00,
    0x13,0x80,0x00,
    0x30,0x00,0x00,
    0x33,0x00,0x00,
    0x00,0x00,0x00,
    0x00,0x00,0x00,
};

BYTE code tOSD_CHARWIDTH_EUROPE[][2] =
{
    {_,    4},

    {_0_, 8}, {_1_, 5}, {_2_, 8}, {_3_, 8}, {_4_, 8}, {_5_, 8}, {_6_, 8}, {_7_, 8}, {_8_, 8}, {_9_, 8},

    {_A_, 10}, {_B_,  9}, {_C_, 10}, {_D_,  9}, {_E_,  8}, {_F_,  8}, {_G_, 10}, {_H_,  9}, {_I_,  3}, {_J_,  8},
    {_K_, 10}, {_L_,  8}, {_M_, 12}, {_N_,  9}, {_O_, 10}, {_P_,  9}, {_Q_, 11}, {_R_, 10}, {_S_,  9}, {_T_,  9},
    {_U_,  9}, {_V_, 10}, {_W_, 11}, {_X_, 11}, {_Y_,  9}, {_Z_,  9},


    {_a_,  8}, {_b_,  8}, {_c_,  8}, {_d_,  8}, {_e_,  8}, {_f_,  6}, {_g_,  8}, {_h_,  8}, {_i_,  3}, {_j_,  4},

    {_k_,  7}, {_l_,  3}, {_m_, 11}, {_n_,  8}, {_o_,  8}, {_p_,  8}, {_q_,  8}, {_r_,  6}, {_s_,  7}, {_t_,  6},
    {_u_,  8}, {_v_,  8}, {_w_, 12}, {_x_,  9}, {_y_,  9}, {_z_,  8},

    {_A0_,11}, {_a0_, 8}, {_a1_, 8}, {_a2_, 8}, {_a3_, 8}, {_a4_, 8}, {_c0_, 8}, {_E0_, 8}, {_e0_, 8}, {_e1_, 8}, {_e2_, 8}, {_n0_, 8},
    {_u0_, 8}, {_u1_, 8}, {_u2_, 8}, {_o0_, 8}, {_o1_, 8}, {_o2_, 8}, {_o3_, 8}, {_i0_, 4},

    {_UPDOT_, 3}, {_DOT_,   3}, {_LEFT_BRACE_, 5}, {_RIGHT_BRACE_, 5}, {_AND_,      5}, {_COLON_,       3}, {_AT_0_,        12},
#if (_FALSE_COLOR_SUPPORT == _ON)
    // %_PERCENTAGE_
    {_COMMA_, 5}, {_SLINE_, 5}, {_SHIFT_LEFT_, 7}, {_SHIFT_RIGHT_, 7}, {_PERCENTAGE_, 9}, {_QUERY_,       7},
#else
    {_COMMA_, 5}, {_SLINE_, 5}, {_SHIFT_LEFT_, 7}, {_SHIFT_RIGHT_, 7}, {_SEPERATE_, 4}, {_QUERY_,       7},
#endif
    {_END_, _END_},
};

BYTE code tSTRING_DISPLAYMODE[] =
{
    _D_, _i_, _s_, _p_, _l_, _a_, _y_, ___, _M_, _o_, _d_, _e_, _END_,
};

BYTE code tSTRING_DISPLAYFUNCTION[] =
{
    _D_, _i_, _s_, _p_, _l_, _a_, _y_, ___, _F_, _u_, _n_, _c_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_SELECTREGION[] =
{
    _S_, _e_, _l_, _e_, _c_, _t_, ___, _R_, _e_, _g_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_PICTURE[] =
{
    _P_, _i_, _c_, _t_, _u_, _r_, _e_, _END_,
};

BYTE code tSTRING_ANALOG[] =
{
    _A_, _n_, _a_, _l_, _o_, _g_, _END_,
};

BYTE code tSTRING_COLOR[] =
{
    _C_, _o_, _l_, _o_, _r_, _END_,
};

BYTE code tSTRING_ADVANCE[] =
{
    _A_, _d_, _v_, _a_, _n_, _c_, _e_, _END_,
};
BYTE code tSTRING_INPUT[] =
{
    _I_, _n_, _p_, _u_, _t_, _END_,
};

BYTE code tSTRING_AUDIO[] =
{
    _A_, _u_, _d_, _i_, _o_, _END_,
};

BYTE code tSTRING_OTHER[] =
{
    _O_, _t_, _h_, _e_, _r_, _END_,
};

BYTE code tSTRING_INFORMATION[] =
{
    _I_, _n_, _f_, _o_, _r_, _m_, _a_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_FACTORY[] =
{
    _F_, _a_, _c_, _t_, _o_, _r_, _y_, _END_,
};

// display mode
BYTE code tSTRING_1P[] =
{
    _1_, _P_, _END_,
};

BYTE code tSTRING_2P_LR[] =
{
    _2_, _P_, ___, _L_, _R_, _END_,
};

BYTE code tSTRING_2P_TB[] =
{
    _2_, _P_, ___, _T_, _B_, _END_,
};

BYTE code tSTRING_2P_PIP[] =
{
    _2_, _P_, ___, _P_, _I_, _P_, _END_,
};

BYTE code tSTRING_4P[] =
{
    _4_, _P_, _END_,
};

// display function
BYTE code tSTRING_DISP_ROTATE[] =
{
    _D_, _i_, _s_, _p_, ___ , _R_ , _o_ , _t_ , _a_ , _t_ , _e_, _END_,
};
BYTE code tSTRING_LATENCY[] =
{
    _D_ , _i_ , _s_ , _p_ , ___ , _L_ , _a_ , _t_ , _e_ , _n_ , _c_ , _y_, _END_,
};

BYTE code tSTRING_DISP_LR_RATIO[] =
{
    _L_, _R_, ___, _R_ , _a_ , _t_ , _i_ , _o_, _END_,
};

BYTE code tSTRING_PIP_POSITION[] =
{
    _P_, _I_, _P_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_PIP_USER_POSITION_H[] =
{
    _P_, _I_, _P_, ___, _H_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_PIP_USER_POSITION_V[] =
{
    _P_, _I_, _P_, ___, _V_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_PIP_TRANSPARENCY[] =
{
    _P_, _I_, _P_, ___, _T_, _r_, _a_, _n_, _s_, _p_, _a_, _r_, _e_, _n_, _c_, _y_ , _END_,
};

BYTE code tSTRING_PIP_SIZE[] =
{
    _P_, _I_, _P_, ___, _S_, _i_, _z_, _e_, _END_,
};

BYTE code tSTRING_INPUT_SWAP[] =
{
    _I_, _n_, _p_, _u_, _t_, ___, _S_, _w_, _a_, _p_, _END_,
};

// select region
BYTE code tSTRING_2P_LR_L[] =
{
    _L_, _e_, _f_, _t_, ___, _S_, _i_, _d_, _e_, _END_,
};

BYTE code tSTRING_2P_LR_R[] =
{
    _R_, _i_, _g_, _h_, _t_, ___, _S_, _i_, _d_, _e_, _END_,
};

BYTE code tSTRING_2P_LR_FULL[] =
{
    _F_, _u_, _l_, _l_, _END_,
};

BYTE code tSTRING_2P_TB_T[] =
{
    _T_, _o_, _p_, ___, _S_, _i_, _d_, _e_, _END_,
};

BYTE code tSTRING_2P_TB_B[] =
{
    _B_, _o_, _t_, _t_, _o_, _m_, ___, _S_, _i_, _d_, _e_, _END_,
};

BYTE code tSTRING_2P_TB_FULL[] =
{
    _F_, _u_, _l_, _l_, _END_,
};

BYTE code tSTRING_2P_PIP_MAIN[] =
{
    _M_, _a_, _i_, _n_, _END_,
};

BYTE code tSTRING_2P_PIP_SUB[] =
{
    _S_, _u_, _b_, _END_,
};

BYTE code tSTRING_2P_PIP_FULL[] =
{
    _F_, _u_, _l_, _l_, _END_,
};

BYTE code tSTRING_4P_LT_IN[] =
{
    _1_, _P_, ___, _I_, _n_, _END_,
};

BYTE code tSTRING_4P_LT_OUT[] =
{
    _1_, _P_, ___, _O_, _u_, _t_, _END_,
};

BYTE code tSTRING_4P_RT_IN[] =
{
    _2_, _P_, ___, _I_, _n_, _END_,
};

BYTE code tSTRING_4P_RT_OUT[] =
{
    _2_, _P_, ___, _O_, _u_, _t_, _END_,
};

BYTE code tSTRING_4P_LB_IN[] =
{
    _3_, _P_, ___, _I_, _n_, _END_,
};

BYTE code tSTRING_4P_LB_OUT[] =
{
    _3_, _P_, ___, _O_, _u_, _t_, _END_,
};

BYTE code tSTRING_4P_RB_IN[] =
{
    _4_, _P_, ___, _I_, _n_, _END_,
};

BYTE code tSTRING_4P_RB_OUT[] =
{
    _4_, _P_, ___, _O_, _u_, _t_, _END_,
};

BYTE code tSTRING_4P_FULL[] =
{
    _4_, _P_, ___, _F_, _u_, _l_, _l_, _END_,
};

BYTE code tSTRING_BACKLIGHT[] =
{
    _B_, _a_, _c_, _k_, _l_, _i_, _g_, _h_, _t_, _END_,
};

BYTE code tSTRING_BRIGHTNESS[] =
{
    _B_, _r_, _i_, _g_, _h_, _t_, _n_, _e_, _s_, _s_, _END_,
};

BYTE code tSTRING_CONTRAST[] =
{
    _C_, _o_, _n_, _t_, _r_, _a_, _s_, _t_, _END_,
};

BYTE code tSTRING_SHARPNESS[] =
{
    _S_, _h_, _a_, _r_, _p_, _n_, _e_, _s_, _s_, _END_,
};

BYTE code tSTRING_AUTO_ADJUST[] =
{
    _A_, _u_, _t_, _o_, ___, _A_, _d_, _j_, _u_, _s_, _t_, _END_,
};

BYTE code tSTRING_HPOS[] =
{
    _H_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_VPOS[] =
{
    _V_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_CLOCK[] =
{
    _C_, _l_, _o_, _c_, _k_, _END_,
};

BYTE code tSTRING_PHASE[] =
{
    _P_, _h_, _a_, _s_, _e_, _END_,
};

BYTE code tSTRING_PANEL_UNIFORMITY[] =
{
    _P_, _a_, _n_, _e_, _l_ , ___ , _U_ , _n_ , _i_ , _f_ , _o_ , _r_ , _m_ , _i_ , _t_ , _y_, _END_,
};

BYTE code tSTRING_GAMMA[] =
{
    _G_, _a_, _m_, _m_, _a_, _END_,
};

BYTE code tSTRING_COLOR_TEMP[] =
{
    // _C_, _o_, _l_, _o_, _r_, ___, _T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_, _END_,
    _T_, _e_, _m_, _p_, _e_, _r_, _a_, _t_, _u_, _r_, _e_, _END_,
};

BYTE code tSTRING_COLOR_EFFECT[] =
{
    _C_, _o_, _l_, _o_, _r_, ___, _E_, _f_, _f_, _e_, _c_, _t_, _END_,
};

BYTE code tSTRING_DEMO[] =
{
    _D_, _e_, _m_, _o_, _END_,
};

BYTE code tSTRING_COLOR_FORMAT[] =
{
    _C_, _o_, _l_, _o_, _r_, ___, _F_, _o_, _r_, _m_, _a_, _t_, _END_,
};

BYTE code tSTRING_PCM[] =
{
    _P_, _C_, _M_, _END_,
};

BYTE code tSTRING_HUE[] =
{
    _H_, _u_, _e_, _END_,
};

BYTE code tSTRING_SATURATION[] =
{
    _S_, _a_, _t_, _u_, _r_, _a_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_ASPECT_RATIO[] =
{
    _A_, _s_, _p_, _e_, _c_, _t_, ___, _R_, _a_, _t_, _i_, _o_, _END_,
};

BYTE code tSTRING_OVER_SCAN[] =
{
    _O_, _v_, _e_, _r_, ___, _S_, _c_, _a_, _n_, _END_,
};

BYTE code tSTRING_OVER_DRIVE[] =
{
    _O_, _v_, _e_, _r_, ___, _D_, _r_, _i_, _v_, _e_, _END_,
};

BYTE code tSTRING_ENERGY_STAR[] =
{
    _E_, _n_, _e_, _r_, _g_, _y_, ___, _S_, _t_, _a_, _r_, _END_,
};

BYTE code tSTRING_DDCCI[] =
{
    _D_, _D_, _C_, _C_, _I_, _END_,
};

BYTE code tSTRING_ULTRA_VIVID[] =
{
    _U_, _l_, _t_, _r_, _a_, ___, _V_, _i_, _v_, _i_, _d_, _END_,
};


BYTE code tSTRING_DCR[] =
{
    _D_, _C_, _R_, _END_,
};

BYTE code tSTRING_DP_OPTION[] =
{
    _D_, _P_, ___, _O_, _p_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_DP_MST[] =
{
    _D_, _P_, ___, _M_, _S_, _T_, _END_,
};
#if(_EDID_SWITCH_BY_PORT_ITEM == _ON)
BYTE code tSTRING_DP_EDID[] =
{
    _E_, _D_, _I_, _D_, _END_,
};

#else
BYTE code tSTRING_DP_EDID[] =
{
    _D_, _P_, ___, _E_, _D_, _I_, _D_, _END_,
};
#endif

BYTE code tSTRING_CLONE[] =
{
    _C_, _l_, _o_, _n_, _e_,  ___, _M_, _o_ , _d_ , _e_, _END_,
};

BYTE code tSTRING_FREESYNC[] =
{
    _F_, _r_, _e_, _e_, ___, _S_, _y_ , _n_ , _c_, _END_,
};
BYTE code tSTRING_FREEZE[] =
{
    _F_, _r_, _e_, _e_, _z_, _e_, _END_,
};
BYTE code tSTRING_SINGLE_DP_EDID[] =
{
    _S_ , _i_ , _n_ , _g_ , _l_, _e_ , ___ , _D_, _P_, ___, _E_, _D_, _I_, _D_, _END_,
};

BYTE code tSTRING_DUAL_DP_EDID[] =
{
    _D_ , _u_ , _a_ , _l_, ___ , _D_, _P_, ___, _E_, _D_, _I_, _D_, _END_,
};

BYTE code tSTRING_DP_LANE_COUNT[] =
{
    // _D_, _P_, ___, _L_, _a_, _n_ , _e_ , _s_, _END_,
    _T_, _y_, _p_, _e_, _C_, ___, _C_, _o_, _n_, _f_, _i_, _g_, _END_,
};

#if(_ULTRA_HDR_SUPPORT == _ON)
BYTE code tSTRING_HDR[] =
{
    _U_, _l_, _t_, _r_, _a_ , ___ , _H_ , _D_ , _R_ , _END_,
};
#endif

#if (_FALSE_COLOR_SUPPORT == _ON)
BYTE code tSTRING_FALSE_COLOR[] =
{
    _F_, _a_, _l_, _s_, _e_, ___ , _C_ , _o_ , _l_ , _o_ , _r_, _END_,
};
#endif

BYTE code tSTRING_AUTO_SELECT[] =
{
    _A_ , _u_ , _t_ , _o_ , ___ , _S_ , _e_ , _l_ , _e_ , _c_ , _t_ , _END_,
};

BYTE code tSTRING_VOLUME[] =
{
    _V_, _o_, _l_, _u_, _m_, _e_, _END_,
};

BYTE code tSTRING_MUTE[] =
{
    _M_, _u_, _t_, _e_, _END_,
};

BYTE code tSTRING_STAND_ALONG[] =
{
    _S_, _t_, _a_, _n_, _d_, ___, _A_, _l_, _o_, _n_, _g_, _END_,
};

BYTE code tSTRING_AUDIO_SOURCE[] =
{
    _A_, _u_, _d_, _i_, _o_, ___, _S_, _o_, _u_, _r_, _c_, _e_, _END_,
};

BYTE code tSTRING_SOUND_MODE[] =
{
    _S_, _o_, _u_, _n_, _d_, ___, _M_, _o_, _d_, _e_, _END_,
};

BYTE code tSTRING_RESET[] =
{
    _R_, _e_, _s_, _e_, _t_, _END_,
};

BYTE code tSTRING_MENU_TIME[] =
{
    _M_, _e_, _n_, _u_, ___, _T_, _i_, _m_, _e_, _END_,
};

BYTE code tSTRING_OSD_HPOS[] =
{
    _O_, _S_, _D_, ___, _H_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_OSD_VPOS[] =
{
    _O_, _S_, _D_, ___, _V_, ___, _P_, _o_, _s_, _i_, _t_, _i_, _o_, _n_, _END_,
};

BYTE code tSTRING_LANGUAGE[] =
{
    _L_, _a_, _n_, _g_, _u_, _a_, _g_, _e_, _END_,
};

BYTE code tSTRING_TRANSPARENCY[] =
{
    _T_, _r_, _a_, _n_, _s_, _p_, _a_, _r_, _e_, _n_, _c_, _y_, _END_,
};

BYTE code tSTRING_ROTATE[] =
{
    _R_, _o_, _t_, _a_, _t_, _e_, _END_,
};

BYTE code tSTRING_BORDER_WIDTH[] =
{
    _B_, _o_, _r_, _d_, _e_, _r_, ___, _W_, _i_, _d_, _t_, _h_, _END_,
};

BYTE code tSTRING_BORDER_COLOR[] =
{
    _B_, _o_, _r_, _d_, _e_, _r_, ___, _C_, _o_, _l_, _o_, _r_, _END_,
};

BYTE code tSTRING_OSD_MODE_UER[] =
{
    _U_ , _s_ , _e_ , _r_ , _,_M_ , _o_ , _d_ , _e_ , _COLON_ , _END_,
};

BYTE code tSTRING_OSD_MODE_PERSET[] =
{
    _P_ , _r_ , _e_ , _s_ , _e_ , _t_ , _,_M_ , _o_ , _d_ , _e_ , _COLON_ , _END_,
};

BYTE code tSTRING_InputSource_1P[] =
{
    _1_ , _P_ , _END_,
};

BYTE code tSTRING_InputSource_2P[] =
{
    _2_ , _P_ , _END_,
};

BYTE code tSTRING_InputSource_3P[] =
{
    _3_ , _P_ , _END_,
};

BYTE code tSTRING_InputSource_4P[] =
{
    _4_ , _P_ , _END_,
};

BYTE code tSTRING_PLEASE_WAIT_MSG[] =
{
    _P_ , _l_ , _e_ , _a_ , _s_ , _e_ , ___ , ___ , _W_ , _a_ , _i_ , _t_ , _END_
};

BYTE code tSTRING_NO_CABLE[] =
{
    _N_ , _o_ , _,_C_ , _a_ , _b_ , _l_ , _e_ , _END_,
};

BYTE code tSTRING_NO_SIGNAL[] =
{
    _N_ , _o_ , _,_S_ , _i_ , _g_ , _n_ , _a_ , _l_ , _END_,
};

BYTE code tSTRING_NO_SUPPORT[] =
{
    _N_ , _o_ , _,_S_ , _u_ , _p_ , _p_ , _o_ , _r_ , _t_ , _END_,
};

BYTE code tSTRING_AUTO_COLOR[] =
{
    _A_ , _u_ , _t_ , _o_ , _,_C_ , _o_ , _l_ , _o_ , _r_ , _END_,
};

BYTE code tSTRING_GO_TO_POWER_SAVING_MODE[] =
{
    _G_ , _o_ , _T_ , _o_ , _,_P_ , _o_ , _w_ , _e_ , _r_ , _,_S_ , _a_ , _v_ , _i_ , _n_ , _g_ , _,_M_ , _o_ , _d_ , _e_ , _END_,
};

BYTE code tSTRING_PASS[] =
{
    _P_ , _a_ , _s_ , _s_ , _END_,
};

BYTE code tSTRING_FAIL[] =
{
    _F_ , _a_ , _i_ , _l_ , _END_,
};

BYTE code tSTRING_2P[] =
{
    _2_, _P_, _END_,
};
BYTE code tSTRING_3P[] =
{
    _3_, _P_, _END_,
};

BYTE code tSTRING_AUTOSELECT[] =
{
    _A_ , _u_ , _t_ , _o_ , ___ , _S_ , _e_ , _l_ , _e_ , _c_ , _t_ , _END_,
};

WORD code tSTRING_RESOLUTION_TABLE[][6]=
{
    {   _,   _,   _,   _,   _,   _},
    { 240, _4_, _8_, _0_, _i_,   _},
    { 480, _4_, _8_, _0_, _p_,   _},
    { 288, _5_, _7_, _6_, _i_,   _},
    { 576, _5_, _7_, _6_, _p_,   _},
    { 720, _7_, _2_, _0_, _p_,   _},
    { 540, _1_, _0_, _8_, _0_, _i_},
    {1080, _1_, _0_, _8_, _0_, _p_},
};
#if (_FALSE_COLOR_SUPPORT == _ON)
BYTE code tSTRING_FALSE_COLOR_CURSOR_1[] =
{
    _Y_ , _COLON_ , _,_0_ , _PERCENTAGE_ , _END_,
};

BYTE code tSTRING_FALSE_COLOR_CURSOR_2[] =
{
    _1_ , _0_ , _0_ , _PERCENTAGE_ , _END_,
};

#endif


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE *g_pucShowNumberAddress;
BYTE g_pucModeInfoData[28];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************

//***************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
BYTE *OsdPropGetShowInputPortStringAddress(BYTE ucInputPort);
BYTE *OsdPropGetShowVFreqStringAddress(void);
BYTE *OsdPropGetShowHFreqPClkStringAddress(void);

#if(_DIGITAL_PORT_SUPPORT == _ON)
BYTE *OsdPropGetShowHDCPEnable(bit bEn);
#endif

BYTE *OsdPropGetShowResolutionStringAddress(void);

#if(_FREESYNC_SUPPORT == _ON)
BYTE *OsdPropGetShowFreeSyncVFreqRangeStringAddress(void);
#endif

BYTE OsdPropGetFontPointer(BYTE ucPointerSelect);
BYTE OsdPropVideoResolution(void);
BYTE OsdPropSetFontPointer(BYTE ucPointerSelect, BYTE ucPointer);
void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage);
void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor);
BYTE *OsdPropGetStringTableAddress(BYTE ucString);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetShowInputPortStringAddress(BYTE ucInputPort)
{
    BYTE ucI = 0;

    if(ucInputPort == _A0_INPUT_PORT)
    {
        g_pucModeInfoData[0] = _A_;
        g_pucModeInfoData[1] = _0_;
    }
#ifndef _D7_INPUT_PORT_TYPE
    else if(ucInputPort == (_D6_INPUT_PORT + 1))
    {
        g_pucModeInfoData[0] = _D_;
        g_pucModeInfoData[1] = _7_;
    }
#endif
    else
    {
        g_pucModeInfoData[0] = _D_;
        g_pucModeInfoData[1] = (ucInputPort - _D0_INPUT_PORT) + _0_;
    }

    switch(ucInputPort)
    {
        case _A0_INPUT_PORT:
            ucI = _A0_INPUT_TYPE;
            break;
        case _D0_INPUT_PORT:
            ucI = _D0_INPUT_TYPE;
            break;
        case _D1_INPUT_PORT:
            ucI = _D1_INPUT_TYPE;
            break;
        case _D2_INPUT_PORT:
            ucI = _D2_INPUT_TYPE;
            break;
        case _D3_INPUT_PORT:
            ucI = _D3_INPUT_TYPE;
            break;
        case _D4_INPUT_PORT:
            ucI = _D4_INPUT_TYPE;
            break;
        case _D5_INPUT_PORT:
            ucI = _D5_INPUT_TYPE;
            break;
        case _D6_INPUT_PORT:
            ucI = _D6_INPUT_TYPE;
            break;
        case _D7_INPUT_PORT:
            ucI = _D7_INPUT_TYPE;
            break;
        default:
            ucI = _ICON_INPUT_NO_PORT;
            break;
    }

    g_pucModeInfoData[2] = _COLON_;

    switch(ucI)
    {
        case _ICON_INPUT_VGA:
            g_pucModeInfoData[3] = ___;
            g_pucModeInfoData[4] = _V_;
            g_pucModeInfoData[5] = _G_;
            g_pucModeInfoData[6] = _A_;
            g_pucModeInfoData[7] = _END_;
            break;


        case _ICON_INPUT_DVI:
            g_pucModeInfoData[3] = ___;
            g_pucModeInfoData[4] = _D_;
            g_pucModeInfoData[5] = _V_;
            g_pucModeInfoData[6] = _I_;
            g_pucModeInfoData[7] = _END_;
            break;


        case _ICON_INPUT_HDMI:
            g_pucModeInfoData[3] = ___;
            g_pucModeInfoData[4] = _H_;
            g_pucModeInfoData[5] = _D_;
            g_pucModeInfoData[6] = _M_;
            g_pucModeInfoData[7] = _I_;
            g_pucModeInfoData[8] = _END_;
            break;

        case _ICON_INPUT_DP:
            g_pucModeInfoData[3] = ___;
            g_pucModeInfoData[4] = _D_;
            g_pucModeInfoData[5] = _P_;
            g_pucModeInfoData[6] = ___;
            g_pucModeInfoData[7] = _END_;
            break;

        case _ICON_INPUT_MHL:
            g_pucModeInfoData[3] = ___;
            g_pucModeInfoData[4] = _M_;
            g_pucModeInfoData[5] = _H_;
            g_pucModeInfoData[6] = _L_;
            g_pucModeInfoData[7] = _END_;
            break;

        case _ICON_INPUT_HDMI20:
            g_pucModeInfoData[3] = ___;
            g_pucModeInfoData[4] = _H_;
            g_pucModeInfoData[5] = _D_;
            g_pucModeInfoData[6] = _M_;
            g_pucModeInfoData[7] = _I_;
            g_pucModeInfoData[8] = _2_;
            g_pucModeInfoData[9] = _DOT_;
            g_pucModeInfoData[10] = _0_;
            g_pucModeInfoData[11] = _END_;
            break;

        case _ICON_INPUT_DUAL_DVI:
            g_pucModeInfoData[3] = ___;
            g_pucModeInfoData[4] = _D_;
            g_pucModeInfoData[5] = _u_;
            g_pucModeInfoData[6] = _a_;
            g_pucModeInfoData[7] = _l_;
            g_pucModeInfoData[8] = ___;
            g_pucModeInfoData[9] = _D_;
            g_pucModeInfoData[10] = _V_;
            g_pucModeInfoData[11] = _I_;
            g_pucModeInfoData[12] = _END_;

            break;

        case _ICON_INPUT_NO_PORT:
            g_pucModeInfoData[3] = ___;
            g_pucModeInfoData[4] = _N_;
            g_pucModeInfoData[5] = _O_;
            g_pucModeInfoData[6] = _N_;
            g_pucModeInfoData[7] = _E_;
            g_pucModeInfoData[8] = _END_;
            break;

        default:
            break;
    }

    return g_pucModeInfoData;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
/*
BYTE* OsdPropGetShowPixelClockStringAddress(void)
{
    BYTE ucI = 0;
    WORD usFreq = ScalerSyncGetInputPixelClk();

    g_pucModeInfoData[0] = _P_;
    g_pucModeInfoData[1] = _C_;
    g_pucModeInfoData[2] = _L_;
    g_pucModeInfoData[3] = _K_;
    g_pucModeInfoData[4] = _COLON_;
    g_pucModeInfoData[5] = ___;
    g_pucModeInfoData[6] = ___;

    ucI = 10;

    while(1)
    {
        if(ucI == 9)
        {
            g_pucModeInfoData[ucI] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usFreq % 10 + _0_;
            usFreq /= 10;
        }

        if(usFreq <= 0)
        {
            break;
        }
        ucI--;
    }

    g_pucModeInfoData[11] = _M_;
    g_pucModeInfoData[12] = _H_;
    g_pucModeInfoData[13] = _z_;
    g_pucModeInfoData[14] = _END_;

    return g_pucModeInfoData;
}
*/
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetShowVFreqStringAddress(void)
{
    WORD usTemp = 0;
    BYTE ucI = 0;

    usTemp = GET_INPUT_TIMING_VFREQ();

    g_pucModeInfoData[0] = _V_;
    g_pucModeInfoData[1] = _COLON_;
    g_pucModeInfoData[2] = ___;

    ucI = 6;

    while(_TRUE)
    {
        if(ucI == 5)
        {
            g_pucModeInfoData[5] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;
        }

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }
    g_pucModeInfoData[7] = _H_;
    g_pucModeInfoData[8] = _z_;
    g_pucModeInfoData[9] = _END_;

    return g_pucModeInfoData;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetShowHFreqPClkStringAddress(void)
{
    WORD usTemp = 0;
    BYTE ucI = 0;
    BYTE ucJ = 0;
    WORD usFreq = ScalerSyncGetInputPixelClk(SysRegionGetPortType(SysRegionGetMeasureResultPointerRegion()));

    usTemp = GET_INPUT_TIMING_HFREQ();

    g_pucModeInfoData[0] = _H_;
    g_pucModeInfoData[1] = _COLON_;
    g_pucModeInfoData[2] = ___;

    ucI = 6;

    while(_TRUE)
    {
        if(ucI == 5)
        {
            g_pucModeInfoData[5] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;
        }

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }

    g_pucModeInfoData[7] = _K_;
    g_pucModeInfoData[8] = _H_;
    g_pucModeInfoData[9] = _z_;

    g_pucModeInfoData[10] = ___;
    g_pucModeInfoData[11] = ___;
    g_pucModeInfoData[12] = ___;

    g_pucModeInfoData[13] = _P_;
    g_pucModeInfoData[14] = _C_;
    g_pucModeInfoData[15] = _L_;
    g_pucModeInfoData[16] = _K_;
    g_pucModeInfoData[17] = _COLON_;
    g_pucModeInfoData[18] = ___;
    g_pucModeInfoData[19] = ___;

    ucJ = 23;

    while(_TRUE)
    {
        if(ucJ == 22)
        {
            g_pucModeInfoData[ucJ] = _DOT_;
        }
        else
        {
            g_pucModeInfoData[ucJ] = usFreq % 10 + _0_;
            usFreq /= 10;
        }

        if(usFreq <= 0)
        {
            break;
        }
        ucJ--;
    }

    g_pucModeInfoData[24] = _M_;
    g_pucModeInfoData[25] = _H_;
    g_pucModeInfoData[26] = _z_;
    g_pucModeInfoData[27] = _END_;



    return g_pucModeInfoData;
}

#if(_DIGITAL_PORT_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetShowHDCPEnable(bit bEn)
{
    g_pucModeInfoData[0] = _H_;
    g_pucModeInfoData[1] = _D_;
    g_pucModeInfoData[2] = _C_;
    g_pucModeInfoData[3] = _P_;
    g_pucModeInfoData[4] = ___;

    if(bEn == _TRUE)
    {
        g_pucModeInfoData[5] = _E_;
        g_pucModeInfoData[6] = _n_;
        g_pucModeInfoData[7] = _a_;
        g_pucModeInfoData[8] = _b_;
        g_pucModeInfoData[9] = _l_;
        g_pucModeInfoData[10] = _e_;
        g_pucModeInfoData[11] = _d_;
        g_pucModeInfoData[12] = _END_;
    }
    else
    {
        g_pucModeInfoData[5] = _D_;
        g_pucModeInfoData[6] = _i_;
        g_pucModeInfoData[7] = _s_;
        g_pucModeInfoData[8] = _a_;
        g_pucModeInfoData[9] = _b_;
        g_pucModeInfoData[10] = _l_;
        g_pucModeInfoData[11] = _e_;
        g_pucModeInfoData[12] = _d_;
        g_pucModeInfoData[13] = _END_;
    }

    return g_pucModeInfoData;
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetShowResolutionStringAddress(void)
{
    WORD usTemp = 0;
    BYTE ucI = OsdPropVideoResolution();

    if(ucI != 0)
    {
        g_pucModeInfoData[0] = tSTRING_RESOLUTION_TABLE[ucI][1];
        g_pucModeInfoData[1] = tSTRING_RESOLUTION_TABLE[ucI][2];
        g_pucModeInfoData[2] = tSTRING_RESOLUTION_TABLE[ucI][3];
        g_pucModeInfoData[3] = tSTRING_RESOLUTION_TABLE[ucI][4];
        g_pucModeInfoData[4] = tSTRING_RESOLUTION_TABLE[ucI][5];
        // g_pucModeInfoData[5] = _END_;

        g_pucModeInfoData[5] = _AT_0_;

        usTemp = GET_INPUT_TIMING_VFREQ();

        ucI = 7;
        g_pucModeInfoData[8] = _DOT_;
        g_pucModeInfoData[9] = usTemp % 10 + _0_;
        g_pucModeInfoData[10] = _H_;
        g_pucModeInfoData[11] = _z_;
        g_pucModeInfoData[12] = _END_;

        usTemp /= 10;

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }
    }
    else
    {
        if(GET_INPUT_TIMING_HWIDTH() >= 1000)
        {
            ucI = 3;
        }
        else
        {
            ucI = 2;
        }

        usTemp = GET_INPUT_TIMING_HWIDTH();
        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }

        if(GET_INPUT_TIMING_HWIDTH() >= 1000)
        {
            g_pucModeInfoData[4] = _x_;
        }
        else
        {
            g_pucModeInfoData[3] = _x_;
        }

        usTemp = GET_INPUT_TIMING_VHEIGHT();

        if((GET_INPUT_TIMING_HWIDTH() >= 1000) && (GET_INPUT_TIMING_VHEIGHT() >= 1000))
        {
            ucI = 8;
            g_pucModeInfoData[9] = _AT_0_;
        }
        else if((GET_INPUT_TIMING_HWIDTH() < 1000) && (GET_INPUT_TIMING_VHEIGHT() < 1000))
        {
            ucI = 6;
            g_pucModeInfoData[7] = _AT_0_;
        }
        else
        {
            ucI = 7;
            g_pucModeInfoData[8] = _AT_0_;
        }

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }

        usTemp = GET_INPUT_TIMING_VFREQ();

        if((GET_INPUT_TIMING_HWIDTH() >= 1000) && (GET_INPUT_TIMING_VHEIGHT() >= 1000))
        {
            ucI = 11;
        }
        else if((GET_INPUT_TIMING_HWIDTH() < 1000) && (GET_INPUT_TIMING_VHEIGHT() < 1000))
        {
            ucI = 9;
        }
        else
        {
            ucI = 10;
        }

        // Modify V freq. string position for V freq. > 100Hz
        if(usTemp >= 1000)
        {
            ++ucI;
        }

        g_pucModeInfoData[ucI + 1] = _DOT_;
        g_pucModeInfoData[ucI + 2] = (usTemp % 10) + _0_;
        g_pucModeInfoData[ucI + 3] = _H_;
        g_pucModeInfoData[ucI + 4] = _z_;
        g_pucModeInfoData[ucI + 5] = _END_;

        usTemp /= 10;

        while(_TRUE)
        {
            g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
            usTemp /= 10;

            if(usTemp <= 0)
            {
                break;
            }
            ucI--;
        }
    }

    return g_pucModeInfoData;
}
#if(_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetShowFreeSyncVFreqRangeStringAddress(void)
{
    WORD usTemp = 0;
    BYTE ucI = 0;

    usTemp = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
    {
        usTemp = ScalerDpGetAmdSpdInfo(_SPD_INFO_FREESYNC_MIN_VFREQ, SysRegionGetPortType(SysModeGetDisplayTarget()));
    }
#endif
#if(_HDMI_FREESYNC_SUPPORT == _ON)
    if((GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_HDMI) ||
       (GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_HDMI20) ||
       (GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_MHL))
    {
        usTemp = ScalerTMDSHdmiGetAmdSpdInfo(_SPD_INFO_FREESYNC_MIN_VFREQ, SysRegionGetPortType(SysModeGetDisplayTarget()));
    }
#endif

    g_pucModeInfoData[0] = _V_;
    g_pucModeInfoData[1] = _m_;
    g_pucModeInfoData[2] = _i_;
    g_pucModeInfoData[3] = _n_;
    g_pucModeInfoData[4] = _COLON_;
    g_pucModeInfoData[5] = ___;
    g_pucModeInfoData[6] = ___; // clear
    g_pucModeInfoData[7] = ___; // clear
    g_pucModeInfoData[8] = ___; // clear

    ucI = 8;

    while(_TRUE)
    {
        g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
        usTemp /= 10;

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }
    g_pucModeInfoData[9] = _H_;
    g_pucModeInfoData[10] = _z_;
    g_pucModeInfoData[11] = ___;
    g_pucModeInfoData[12] = ___;

    usTemp = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_DP)
    {
        usTemp = ScalerDpGetAmdSpdInfo(_SPD_INFO_FREESYNC_MAX_VFREQ, SysRegionGetPortType(SysModeGetDisplayTarget()));
    }
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    if((GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_HDMI) ||
       (GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_HDMI20) ||
       (GET_PORT_TYPE(SysSourceGetInputPortType(SysSourceGetInputPort())) == _PORT_MHL))
    {
        usTemp = ScalerTMDSHdmiGetAmdSpdInfo(_SPD_INFO_FREESYNC_MAX_VFREQ, SysRegionGetPortType(SysModeGetDisplayTarget()));
    }
#endif

    g_pucModeInfoData[13] = _V_;
    g_pucModeInfoData[14] = _m_;
    g_pucModeInfoData[15] = _a_;
    g_pucModeInfoData[16] = _x_;
    g_pucModeInfoData[17] = _COLON_;
    g_pucModeInfoData[18] = ___;
    g_pucModeInfoData[19] = ___; // clear
    g_pucModeInfoData[20] = ___; // clear
    g_pucModeInfoData[21] = ___; // clear

    ucI = 21;

    while(_TRUE)
    {
        g_pucModeInfoData[ucI] = usTemp % 10 + _0_;
        usTemp /= 10;

        if(usTemp <= 0)
        {
            break;
        }
        ucI--;
    }
    g_pucModeInfoData[22] = _H_;
    g_pucModeInfoData[23] = _z_;
    g_pucModeInfoData[24] = _END_;

    return g_pucModeInfoData;
}
#endif

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropGetFontPointer(BYTE ucPointerSelect)
{
    BYTE ucPointer = 0;

    if(ucPointerSelect == _PFONT_PAGE_0)
    {
        ucPointer = g_ucFontPointer0;
    }
    else if(ucPointerSelect == _PFONT_PAGE_1)
    {
        ucPointer = g_ucFontPointer1;
    }
    else if(ucPointerSelect == _PFONT_PAGE_2)
    {
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_1)
    {
        g_ucFontPointer2 = _SUB_PAGE_ITEM_1;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_2)
    {
        g_ucFontPointer2 = _SUB_PAGE_ITEM_2;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_3)
    {
        g_ucFontPointer2 = _SUB_PAGE_ITEM_3;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_4)
    {
        g_ucFontPointer2 = _SUB_PAGE_ITEM_4;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_5)
    {
        g_ucFontPointer2 = _SUB_PAGE_ITEM_5;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_6)
    {
        g_ucFontPointer2 = _SUB_PAGE_ITEM_6;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_7)
    {
        g_ucFontPointer2 = _SUB_PAGE_ITEM_7;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_8)
    {
        g_ucFontPointer2 = _SUB_PAGE_ITEM_8;
        ucPointer = g_ucFontPointer2;
    }
    else if(ucPointerSelect == _PFONT_PAGE_INFORMATION)
    {
        ucPointer = g_ucFontPointer1;
    }

    return ucPointer;
}


//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropVideoResolution(void)
{
    bit bVideoTiming = _FALSE;
    BYTE ucI = 0;
    EnumDisplayRegion enumRegion = SysRegionGetMeasureResultPointerRegion();
    EnumSourceTypeDef enumSourceTypeDef = SysRegionGetSourceType(enumRegion);
    EnumSourceSearchPort enumSourceSearchPort = SysRegionGetPortType(enumRegion);

    if(GET_INPUT_TIMING_VFREQ() > 620)
    {
        return _FALSE;
    }

    if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
    {
        bVideoTiming = _TRUE;
    }
#if(_VGA_SUPPORT == _ON)
    else if(enumSourceTypeDef == _SOURCE_VGA)
    {
        if(GET_VGA_COLOR_FORMAT_STATUS() == _COLOR_SPACE_YPBPR)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif
#if(_DVI_SUPPORT == _ON)
    else if(enumSourceTypeDef == _SOURCE_DVI)
    {
#if(_DIGITAL_PORT_SUPPORT == _ON)
        bVideoTiming = ScalerSyncHdcpCheckEnabled(enumSourceSearchPort);
#endif
    }
#endif
#if(_HDMI_SUPPORT == _ON)
    else if(enumSourceTypeDef == _SOURCE_HDMI)
    {
        if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace(enumSourceSearchPort)) == _FALSE)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif
#if(_DP_SUPPORT == _ON)
    else if(enumSourceTypeDef == _SOURCE_DP)
    {
        if(ScalerColorGetColorSpaceRGB(ScalerColorGetColorSpace(enumSourceSearchPort)) == _FALSE)
        {
            bVideoTiming = _TRUE;
        }
    }
#endif

    if(bVideoTiming == _TRUE)
    {
        for(ucI = 1; ucI < 8; ucI++)
        {
            if(GET_INPUT_TIMING_VHEIGHT() == tSTRING_RESOLUTION_TABLE[ucI][0])
            {
                if((tSTRING_RESOLUTION_TABLE[ucI][0] == 480) && (GET_INPUT_TIMING_HWIDTH() == 848))
                {
                    return _FALSE;
                }

                if(((tSTRING_RESOLUTION_TABLE[ucI][0] == 240) || (tSTRING_RESOLUTION_TABLE[ucI][0] == 288) || (tSTRING_RESOLUTION_TABLE[ucI][0] == 540)) &&
                   (GET_INPUT_TIMING_INTERLACE_FLG() == _FALSE))
                {
                    return _FALSE;
                }

                return ucI;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPropSetFontPointer(BYTE ucPointerSelect, BYTE ucPointer)
{
    ucPointer++;

    if(ucPointerSelect == _PFONT_PAGE_0)
    {
        if(ucPointer >= _OSD_PAGE_0_END)
        {
            ucPointer = _OSD_PAGE_0_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_1)
    {
        if(ucPointer >= _OSD_PAGE_1_END)
        {
            ucPointer = _OSD_PAGE_1_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_2)
    {
        if(ucPointer >= _OSD_PAGE_2_END)
        {
            ucPointer = _OSD_PAGE_2_START;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_1)
    {
        if(ucPointer >= _SUB_PAGE_ITEM_1_END)
        {
            ucPointer = _SUB_PAGE_ITEM_1;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_2)
    {
        if(ucPointer >= _SUB_PAGE_ITEM_2_END)
        {
            ucPointer = _SUB_PAGE_ITEM_2;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_3)
    {
        if(ucPointer >= _SUB_PAGE_ITEM_3_END)
        {
            ucPointer = _SUB_PAGE_ITEM_3;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_4)
    {
        if(ucPointer >= _SUB_PAGE_ITEM_4_END)
        {
            ucPointer = _SUB_PAGE_ITEM_4;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_5)
    {
        if(ucPointer >= _SUB_PAGE_ITEM_5_END)
        {
            ucPointer = _SUB_PAGE_ITEM_5;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_6)
    {
        if(ucPointer >= _SUB_PAGE_ITEM_6_END)
        {
            ucPointer = _SUB_PAGE_ITEM_6;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_7)
    {
        if(ucPointer >= _SUB_PAGE_ITEM_7_END)
        {
            ucPointer = _SUB_PAGE_ITEM_7;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_ITEM_8)
    {
        if(ucPointer >= _SUB_PAGE_ITEM_8_END)
        {
            ucPointer = _SUB_PAGE_ITEM_8;
        }
    }
    else if(ucPointerSelect == _PFONT_PAGE_INFORMATION)
    {
        if(ucPointer >= _OSD_PAGE_INFORMATION_END)
        {
            ucPointer = _OSD_PAGE_INFORMATION_START;
        }
    }

    return ucPointer;
}

void OsdPropPutString(BYTE ucRow, BYTE ucCol, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage)
{
    bit bEndFlag = 0;
    BYTE pucTemp[27] = {0};
    BYTE *pucFontTable = 0;
    BYTE *pucArray = 0;
    BYTE ucByte0 = 0x6C;    // palette index 0, 1bit 256 ~ 511
    BYTE ucFontBRealRaw = 0;
    BYTE pucDataTemp[16] = {0};// replace pdata

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucByte0 = 0x6E;
    }
#endif

    pucArray = OsdPropGetStringTableAddress(ucString);

    // if(ucLanguage == _CHINESE_T)
    // {
    // pucFontTable = tFONT_CHINESE;
    // }
    // else
    // {
    pucFontTable = tFONT_EUROPE;
    // }

    pucDataTemp[0] = ucLanguage;

    while(pucDataTemp[0] != _ENGLISH)
    {
        if(*pucArray == _END_)
        {
            pucDataTemp[0]--;
        }
        pucArray++;
    }

    pucDataTemp[1] = OsdPropGetFontPointer(ucFptsSelect);

    // reorder
    SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT6);
    SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~(_BIT7 | _BIT5)));

    pucDataTemp[2] = 0;
    pucDataTemp[3] = 0;
    pucDataTemp[4] = 0;
    pucDataTemp[5] = 0;
    pucDataTemp[9] = 0;

    while(*(pucArray + pucDataTemp[2]) != _END_)
    {
        switch(*(pucArray + pucDataTemp[2]))
        {
            case _END_:
                bEndFlag = 1;
                break;

            default:
                pucDataTemp[3] = *(pucArray + pucDataTemp[2]);

                if(ucLanguage == _ENGLISH)
                {
                    pucDataTemp[4] = tOSD_CHARWIDTH_EUROPE[pucDataTemp[3]][1];
                }
                else if(ucLanguage == _CHINESE_T)
                {
//                    pucDataTemp[4] = tOSD_CHARWIDTH_CHINESE[pucDataTemp[3]][1];
                }
                else
                {
                    pucDataTemp[4] = 12;
                }
                pucDataTemp[2]++;
                break;
        }

        if(pucDataTemp[5] == 0)
        {
            pucDataTemp[5] = pucDataTemp[4];
        }

        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT3);    // first bits shift direction: left shift
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~_BIT2)); // left bits shift direction: rigth shift
        SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(((pucDataTemp[4] - pucDataTemp[5]) << 4) | pucDataTemp[5]); // first bits shift and second bits shift

        pucDataTemp[6] = pucDataTemp[2];
        pucDataTemp[7] = pucDataTemp[5];

        for(pucDataTemp[0] = 0; pucDataTemp[0] < 9; pucDataTemp[0]++)
        {
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT0); // restart from last three bytes

            PDATA_WORD(7) = pucDataTemp[3] * 27 + pucDataTemp[0] * 3;

            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7)));
            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 1));
            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 2));

            pucDataTemp[2] = pucDataTemp[6];
            pucDataTemp[5] = pucDataTemp[7];

            if((pucDataTemp[5] == 12) || (*(pucArray + pucDataTemp[2]) == _END_))
            {
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
            }
            else
            {
                pucDataTemp[8] = *(pucArray + pucDataTemp[2]);

                if(ucLanguage == _CHINESE_T)
                {
//                    pucDataTemp[4] = tOSD_CHARWIDTH_CHINESE[pucDataTemp[8]][1];
                }
                else
                {
                    pucDataTemp[4] = tOSD_CHARWIDTH_EUROPE[pucDataTemp[8]][1];
                }

                pucDataTemp[2] ++;

                PDATA_WORD(7) = pucDataTemp[8] * 27 + pucDataTemp[0] * 3;

                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7)));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 1));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 2));

                pucDataTemp[5] += pucDataTemp[4];
            }

            while((pucDataTemp[5] < 12) && (*(pucArray + pucDataTemp[2]) != _END_))
            {
                SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET((pucDataTemp[5] << 4) | pucDataTemp[5]); // third bits shift and left bits shift

                switch(*(pucArray + pucDataTemp[2]))
                {
                    case _END_:
                        bEndFlag = 1;
                        break;

                    default:
                        pucDataTemp[8] = *(pucArray + pucDataTemp[2]);

                        if(ucLanguage == _ENGLISH)
                        {
                            pucDataTemp[4] = tOSD_CHARWIDTH_EUROPE[pucDataTemp[8]][1];
                        }
                        else if(ucLanguage == _CHINESE_T)
                        {
//                            pucDataTemp[4] = tOSD_CHARWIDTH_CHINESE[pucDataTemp[8]][1];
                        }
                        else
                        {
                            pucDataTemp[4] = 12;
                        }
                        pucDataTemp[2] ++;
                        break;
                }

                pucDataTemp[5] += pucDataTemp[4];

                PDATA_WORD(7) = pucDataTemp[8] * 27 + pucDataTemp[0] * 3;

                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7)));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 1));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 2));
            }

            pucTemp[pucDataTemp[0] * 3 + 2] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            pucTemp[pucDataTemp[0] * 3 + 1] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            pucTemp[pucDataTemp[0] * 3] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
        }

        if(pucDataTemp[5] <= 12)
        {
            pucDataTemp[5] = 0;
        }
        else
        {
            pucDataTemp[5] = pucDataTemp[5] - 12;
            pucDataTemp[2]--;
        }

        // Write the pro font data to sram
        // COsdFxLoadFontDataAddrCal(ucBankupFontPointer);

        // PDATA_WORD(7) = (WORD)pucDataTemp[1] * 9;
        PDATA_WORD(7) = ((WORD)pucDataTemp[1] + 0x100) * 9;
        PDATA_WORD(7) += g_usFontTableStart;

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
        if(GET_OSD_ROTATE_STATUS() != _OSD_ROTATE_DEGREE_0)
        {
            ScalerOsdFontRotateCtrl(GET_OSD_ROTATE_STATUS(), _ENABLE, _ENABLE);
            ScalerOsdCompressionCtrl(_OSD_DECODE_NON_COMPRESSED, _OSD_COMPRESSION_ENABLE);
        }
        else
#endif
        {
            ScalerOsdFontRotateCtrl(GET_OSD_ROTATE_STATUS(), _DISABLE, _DISABLE);
            ScalerOsdCompressionCtrl(_OSD_DECODE_COMPRESSED, _OSD_COMPRESSION_DISABLE);
        }

        if(PDATA_WORD(7) > 4095)
        {
            ScalerOsdScrambleLoadFontAddrHsbSet();
        }
        else
        {
            ScalerOsdScrambleLoadFontAddrHsbClr();
        }

        ScalerOsdAddrSet(_OSD_SRAM, _OSD_BYTEALL, PDATA_WORD(7), _DISABLE);
        ScalerOsdBurstWriteDataPort(pucTemp, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

        // OSD HW needs time to process it and then write decompressed data into SRAM.
        // The value 1ms is enough at all.
        ScalerTimerDelayXms(1);

        ScalerOsdCompressionCtrl(_OSD_DECODE_COMPRESSED, _OSD_COMPRESSION_DISABLE);

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
        if(GET_OSD_ROTATE_STATUS() != _OSD_ROTATE_DEGREE_0)
        {
            ScalerOsdFontRotateCtrl(GET_OSD_ROTATE_STATUS(), _DISABLE, _ENABLE);
        }
#endif
        ScalerOsdScrambleLoadFontAddrHsbClr();

        if(ucRow >= _OSD_MAP_B_ROW_OFFSET)
        {
            ucFontBRealRaw = ucRow - _OSD_MAP_B_ROW_OFFSET;
        }
        else
        {
            ucFontBRealRaw = ucRow;
        }

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
        {
            PDATA_WORD(7) = (WORD)((g_ucOsdWidth - ucFontBRealRaw - 1) + g_ucOsdWidth * (ucCol + pucDataTemp[9]));
        }
        else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
        {
            PDATA_WORD(7) = (WORD)(g_ucOsdHeight - 1 - ucCol - pucDataTemp[9]) * g_ucOsdWidth + ucFontBRealRaw;
        }
        else
#endif
        {
            PDATA_WORD(7) = (WORD)ucFontBRealRaw * g_ucOsdWidth + ucCol + pucDataTemp[9];
        }

        if(ucRow >= _OSD_MAP_B_ROW_OFFSET)
        {
            ScalerOsdCommandAllByte(PDATA_WORD(7) + (((ScalerGetByte(P3A_1B_FRAME_CTRL_1B) & 0x0F) << 8) | ScalerGetByte(P3A_1D_FRAME_CTRL_1D)), ucByte0, pucDataTemp[1], ucColor);
        }
        else
        {
            // ScalerOsdCommandByte(PDATA_WORD(7) + g_usFontSelectStart, _OSD_BYTE1, pucDataTemp[1]);
            ScalerOsdCommandAllByte(PDATA_WORD(7) + g_usFontSelectStart, ucByte0, pucDataTemp[1], ucColor);
        }

        pucDataTemp[9]++; // Record the length of prop string

        // Increase the sram address pointer
        pucDataTemp[1] = OsdPropSetFontPointer(ucFptsSelect, pucDataTemp[1]);

    }// End of while(*(pucArray + stringcnt) != _END_)

    if(ucFptsSelect == _PFONT_PAGE_0)
    {
        g_ucFontPointer0 = pucDataTemp[1];
    }
    else if(ucFptsSelect == _PFONT_PAGE_1)
    {
        g_ucFontPointer1 = pucDataTemp[1];
    }
    else if((ucFptsSelect == _PFONT_PAGE_2) || ((ucFptsSelect >= _PFONT_PAGE_ITEM_1) && (ucFptsSelect <= _PFONT_PAGE_ITEM_8)))
    {
        g_ucFontPointer2 = pucDataTemp[1];
    }
    else if(ucFptsSelect == _PFONT_PAGE_INFORMATION)
    {
        g_ucFontPointer1 = pucDataTemp[1];
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropPutStringCenter(BYTE ucRow, BYTE ucCol, BYTE ucWidth, BYTE ucFptsSelect, BYTE ucString, BYTE ucColor, BYTE ucLanguage)
{
    bit bEndFlag = 0;
    BYTE pucTemp[27] = {0};
    bit bMode = _CENTER;
    BYTE *pucFontTable = 0;
    BYTE *pucArray = 0;
    BYTE ucByte0 = 0x6C;    // palette index 0, 1bit 256 ~ 511
    BYTE ucFontBRealRaw=0;
    BYTE pucDataTemp[16] = {0};// replace pdata

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
    if((GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90) ||
       (GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270))
    {
        ucByte0 = 0x6E;
    }
#endif
    pucArray = OsdPropGetStringTableAddress(ucString);

    if(ucLanguage == _CHINESE_T)
    {
//        pucFontTable = tFONT_CHINESE;
    }
    else
    {
        pucFontTable = tFONT_EUROPE;
    }

    pucDataTemp[0] = ucLanguage;

    while(pucDataTemp[0] != _ENGLISH)
    {
        if(*pucArray == _END_)
        {
            pucDataTemp[0]--;
        }
        pucArray++;
    }

    pucDataTemp[1] = OsdPropGetFontPointer(ucFptsSelect);

    // reorder
    SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT6);
    SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~(_BIT7 | _BIT5)));

    pucDataTemp[2] = 0;
    pucDataTemp[3] = 0;
    pucDataTemp[4] = 0;
    pucDataTemp[7] = 0;
    pucDataTemp[10] = 0;

    while(*(pucArray + pucDataTemp[2]) != _END_)
    {
        switch(*(pucArray + pucDataTemp[2]))
        {
            case _END_:

                break;

            default:

                pucDataTemp[3] = *(pucArray + pucDataTemp[2]);

                if(ucLanguage == _ENGLISH)
                {
                    pucDataTemp[4] = pucDataTemp[4] + tOSD_CHARWIDTH_EUROPE[pucDataTemp[3]][1];
                }
                else if(ucLanguage == _CHINESE_T)
                {
//                    pucDataTemp[4] = pucDataTemp[4] + tOSD_CHARWIDTH_CHINESE[pucDataTemp[3]][1];
                }
                else
                {
                    pucDataTemp[4] = pucDataTemp[4] + 12;
                }
                pucDataTemp[2] ++;
                break;
        }
    }
    pucDataTemp[5] = ucCol + (((((WORD)((ucWidth) * 12) - pucDataTemp[4]) / 2)) / 12);
    pucDataTemp[0] = ((((WORD)((ucWidth) * 12) - pucDataTemp[4]) / 2)) % 12;

/*//for Right mode
    ucCol = (ucColEnd - (ucCharWidth/12) -1);
    ucBlinking = 12 - (ucCharWidth % 12);
*/

    pucDataTemp[4] = 0;
    pucDataTemp[2] = 0;


    if(pucDataTemp[0] == 0)
    {
        bMode = _NORMAL;
    }
    else
    {
        bMode = _CENTER;
    }

    while(*(pucArray + pucDataTemp[2]) != _END_)
    {
        switch(*(pucArray + pucDataTemp[2]))
        {
            case _END_:
                bEndFlag = 1;
                break;

            default:

                if(bMode == _CENTER)
                {
                    pucDataTemp[6] = _;
                }
                else
                {
                    pucDataTemp[6] = *(pucArray + pucDataTemp[2]);
                }

                if(ucLanguage == _ENGLISH)
                {
                    if(bMode == _CENTER)
                    {
                        pucDataTemp[4] = pucDataTemp[0];
                    }
                    else
                    {
                        pucDataTemp[4] = tOSD_CHARWIDTH_EUROPE[pucDataTemp[6]][1];
                    }
                }
                else if(ucLanguage == _CHINESE_T)
                {
                    if(bMode == _CENTER)
                    {
                        pucDataTemp[4] = pucDataTemp[0];
                    }
                    else
                    {
//                        pucDataTemp[4] = tOSD_CHARWIDTH_CHINESE[pucDataTemp[6]][1];
                    }
                }
                else
                {
                    pucDataTemp[4] = 12;
                }
                pucDataTemp[2] ++;
                break;
        }

        if(pucDataTemp[7] == 0)
        {
            pucDataTemp[7] = pucDataTemp[4];
        }

        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT3);    // first bits shift direction: left shift
        SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() & (~_BIT2)); // left bits shift direction: rigth shift
        SCALEROSD_FONT_ROTATE_1_2_BITS_SHIFT_SET(((pucDataTemp[4] - pucDataTemp[7]) << 4) | pucDataTemp[7]); // first bits shift and second bits shift

        pucDataTemp[8] = pucDataTemp[2];
        pucDataTemp[9] = pucDataTemp[7];

        if(bMode == _CENTER)
        {
            pucDataTemp[8] = 0;
            pucDataTemp[6] =0;
            pucDataTemp[2] = 0;
            bMode = _NORMAL;
        }

        for(pucDataTemp[0] = 0; pucDataTemp[0] < 9; pucDataTemp[0]++)
        {
            SCALEROSD_FONT_ROTATE_SETTING_SET(SCALEROSD_FONT_ROTATE_SETTING_GET() | _BIT0);  // restart from last three bytes
            PDATA_WORD(7)= pucDataTemp[6] * 27 + pucDataTemp[0] * 3;

            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7)));
            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 1));
            SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 2));

            pucDataTemp[2] = pucDataTemp[8];
            pucDataTemp[7] = pucDataTemp[9];


            if((pucDataTemp[7] == 12) || (*(pucArray + pucDataTemp[2]) == _END_))
            {
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
                SCALEROSD_FONT_ROTATE_INPUT_SET(0x00);
            }
            else
            {
                pucDataTemp[3] = *(pucArray + pucDataTemp[2]);
                if(ucLanguage == _CHINESE_T)
                {
//                    pucDataTemp[4] = tOSD_CHARWIDTH_CHINESE[pucDataTemp[3]][1];
                }
                else
                {
                    pucDataTemp[4] = tOSD_CHARWIDTH_EUROPE[pucDataTemp[3]][1];
                }
                pucDataTemp[2] ++;

                PDATA_WORD(7) = pucDataTemp[3] * 27 + pucDataTemp[0] * 3;

                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7)));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 1));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 2));

                pucDataTemp[7] += pucDataTemp[4];
            }

            while((pucDataTemp[7] < 12) && (*(pucArray + pucDataTemp[2]) != _END_))
            {
                SCALEROSD_FONT_ROTATE_3_L_BITS_SHIFT_SET((pucDataTemp[7] << 4) | pucDataTemp[7]); // third bits shift and left bits shift

                switch(*(pucArray + pucDataTemp[2]))
                {
                    case _END_:
                        bEndFlag = 1;
                        break;

                    default:
                        pucDataTemp[3] = *(pucArray + pucDataTemp[2]);

                        if(ucLanguage == _ENGLISH)
                        {
                            pucDataTemp[4] = tOSD_CHARWIDTH_EUROPE[pucDataTemp[3]][1];
                        }
                        else if(ucLanguage == _CHINESE_T)
                        {
//                            pucDataTemp[4] = tOSD_CHARWIDTH_CHINESE[pucDataTemp[3]][1];
                        }
                        else
                        {
                            pucDataTemp[4] = 12;
                        }
                        pucDataTemp[2] ++;
                        break;
                }

                pucDataTemp[7] += pucDataTemp[4];

                PDATA_WORD(7) = pucDataTemp[3] * 27 + pucDataTemp[0] * 3;

                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7)));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 1));
                SCALEROSD_FONT_ROTATE_INPUT_SET(*(pucFontTable + PDATA_WORD(7) + 2));
            }

            pucTemp[pucDataTemp[0] * 3 + 2] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            pucTemp[pucDataTemp[0] * 3 + 1] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
            pucTemp[pucDataTemp[0] * 3] = SCALEROSD_FONT_ROTATE_ONPUT_GET();
        }

        if(pucDataTemp[7] <= 12)
        {
            pucDataTemp[7] = 0;
        }
        else
        {
            pucDataTemp[7] = pucDataTemp[7] - 12;
            pucDataTemp[2] --;
        }

        // Write the pro font data to sram
        // COsdFxLoadFontDataAddrCal(ucBankupFontPointer);

//        PDATA_WORD(7) = (WORD)pucDataTemp[1] * 9;
        PDATA_WORD(7) = ((WORD)pucDataTemp[1] + 0x100) * 9;
        PDATA_WORD(7) += g_usFontTableStart;

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
        if(GET_OSD_ROTATE_STATUS() != _OSD_ROTATE_DEGREE_0)
        {
            ScalerOsdFontRotateCtrl(GET_OSD_ROTATE_STATUS(), _ENABLE, _ENABLE);
            ScalerOsdCompressionCtrl(_OSD_DECODE_NON_COMPRESSED, _OSD_COMPRESSION_ENABLE);
        }
        else
#endif
        {
            ScalerOsdFontRotateCtrl(GET_OSD_ROTATE_STATUS(), _DISABLE, _DISABLE);
            ScalerOsdCompressionCtrl(_OSD_DECODE_COMPRESSED, _OSD_COMPRESSION_DISABLE);
        }

        if(PDATA_WORD(7) > 4095)
        {
            ScalerOsdScrambleLoadFontAddrHsbSet();
        }
        else
        {
            ScalerOsdScrambleLoadFontAddrHsbClr();
        }

        ScalerOsdAddrSet(_OSD_SRAM, _OSD_BYTEALL, PDATA_WORD(7), _DISABLE);

        ScalerOsdBurstWriteDataPort(pucTemp, 27, GET_CURRENT_BANK_NUMBER(), _BURSTWRITE_DATA_OSD, _BURSTWRITE_FROM_XRAM);

        // OSD HW needs time to process it and then write decompressed data into SRAM.
        // The value 1ms is enough at all.
        ScalerTimerDelayXms(1);

        ScalerOsdCompressionCtrl(_OSD_DECODE_COMPRESSED, _OSD_COMPRESSION_DISABLE);

#if((_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE) || (_OSD_ROTATE_FUNCTION == _OSD_ROTATE_HARDWARE))
        if(GET_OSD_ROTATE_STATUS() != _OSD_ROTATE_DEGREE_0)
        {
            ScalerOsdFontRotateCtrl(GET_OSD_ROTATE_STATUS(), _DISABLE, _ENABLE);
        }
#endif
        ScalerOsdScrambleLoadFontAddrHsbClr();

        if(ucRow >= _OSD_MAP_B_ROW_OFFSET)
        {
            ucFontBRealRaw = ucRow - _OSD_MAP_B_ROW_OFFSET;
        }
        else
        {
            ucFontBRealRaw = ucRow;
        }

#if(_OSD_ROTATE_FUNCTION == _OSD_ROTATE_SOFTWARE)
        if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_90)
        {
            PDATA_WORD(7) = (WORD)((g_ucOsdWidth - ucFontBRealRaw - 1) + g_ucOsdWidth * (pucDataTemp[5] + pucDataTemp[10]));
        }
        else if(GET_OSD_ROTATE_STATUS() == _OSD_ROTATE_DEGREE_270)
        {
            PDATA_WORD(7) = (WORD)(g_ucOsdHeight - 1 - pucDataTemp[5] - pucDataTemp[10]) * g_ucOsdWidth + ucFontBRealRaw;
        }
        else
#endif
        {
            PDATA_WORD(7) = (WORD)ucFontBRealRaw * g_ucOsdWidth + pucDataTemp[5] + pucDataTemp[10];
        }

        if(ucRow >= _OSD_MAP_B_ROW_OFFSET)
        {
            ScalerOsdCommandAllByte(PDATA_WORD(7) + (((ScalerGetByte(P3A_1B_FRAME_CTRL_1B) & 0x0F) << 8) | ScalerGetByte(P3A_1D_FRAME_CTRL_1D)), ucByte0, pucDataTemp[1], ucColor);
        }
        else
        {
            // ScalerOsdCommandByte(PDATA_WORD(7) + g_usFontSelectStart, _OSD_BYTE1, pucDataTemp[1]);
            ScalerOsdCommandAllByte(PDATA_WORD(7) + g_usFontSelectStart, ucByte0, pucDataTemp[1], ucColor);
        }
        pucDataTemp[10] ++; // Record the length of prop string

        // Increase the sram address pointer
        pucDataTemp[1] = OsdPropSetFontPointer(ucFptsSelect, pucDataTemp[1]);

    }// End of while(*(pucArray + stringcnt) != _END_)

    if(ucFptsSelect == _PFONT_PAGE_0)
    {
        g_ucFontPointer0 = pucDataTemp[1];
    }
    else if(ucFptsSelect == _PFONT_PAGE_1)
    {
        g_ucFontPointer1 = pucDataTemp[1];
    }
    else if((ucFptsSelect == _PFONT_PAGE_2) || ((ucFptsSelect >= _PFONT_PAGE_ITEM_1) && (ucFptsSelect <= _PFONT_PAGE_ITEM_8)))
    {
        g_ucFontPointer2 = pucDataTemp[1];
    }
    else if(ucFptsSelect == _PFONT_PAGE_INFORMATION)
    {
        g_ucFontPointer1 = pucDataTemp[1];
    }
}

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void OsdPropShowNumber(BYTE ucRow, BYTE ucCol, DWORD ulValue, BYTE ucPar, BYTE ucFontPoint, BYTE ucColor)
{
    BYTE ucIndex = 0;
    BYTE ucTemp = 0;
    BYTE ucI = 0;
    BYTE pucDataSN[16] = {0};

    pucDataSN[5] = (_0_ + (ulValue / 100000));
    pucDataSN[4] = (_0_ + (ulValue % 100000 / 10000));
    pucDataSN[3] = (_0_ + (ulValue % 10000) / 1000);
    pucDataSN[2] = (_0_ + (ulValue % 1000) / 100);
    pucDataSN[1] = (_0_ + (ulValue % 100) / 10);
    pucDataSN[0] = (_0_ + (ulValue % 10));

    for(ucIndex = 0; ucIndex < 6; ucIndex++)
    {
        if(pucDataSN[5 - ucIndex] != ((bit)(ucPar & _BIT1) ? 0x00 : _0_))
        {
            ucIndex = 5 - ucIndex;
            break;
        }
    }

    if((ulValue == 0) && ((bit)(ucPar & 0x02) == 0))
    {
        ucIndex = 0;
    }

    if((bit)(ucPar & _BIT1) != 0)
    {
        ucTemp = (ucPar & 0x70) >> 4;
        ucIndex = (ucPar & 0x70) >> 4;
    }
    else
    {
        ucTemp = (ucPar & 0x70) >> 4;

        if(ucTemp < ucIndex)
        {
            ucTemp = ucIndex;
        }
    }

    for(ucI = 0; ucI <= ucTemp; ucI++)
    {
        if(ucIndex >= ucTemp)
        {
            pucDataSN[ucI + 8] = pucDataSN[ucIndex - ucI];
        }
        else
        {
            if(ucI < (ucTemp - ucIndex))
            {
                pucDataSN[ucI + 8] = 0x00;
            }
            else
            {
                pucDataSN[ucI + 8] = pucDataSN[ucIndex - (ucI - (ucTemp - ucIndex))];
            }
        }
    }
    if((ucPar & 0x01) == _ALIGN_LEFT) // Align Right
    {
        pucDataSN[8 + ucTemp + 1] = 0x00; // clear
        pucDataSN[8 + ucTemp + 2] = 0x00; // clear
        pucDataSN[8 + ucTemp + 3] = _END_;
    }
    else
    {
        pucDataSN[8 + ucTemp + 1] = _END_;
    }
    g_pucShowNumberAddress = &pucDataSN[8];

    if((ucPar & 0x01) == _ALIGN_RIGHT)        // Align Right
    {
        OsdPropPutString(ucRow, ROW(ucCol - ucTemp), ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
    else
    {
        OsdPropPutString(ucRow, ucCol, ucFontPoint, _STRING_SHOW_NUMBER, ucColor, _ENGLISH);
    }
}


//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *OsdPropGetStringTableAddress(BYTE ucString)
{
    BYTE *pucArray = 0;

    switch(ucString)
    {
        case _STRING_DISPLAYMODE:
            pucArray = tSTRING_DISPLAYMODE;
            break;
        case _STRING_DISPLAYFUNCTION:
            pucArray = tSTRING_DISPLAYFUNCTION;
            break;
        case _STRING_SELECTREGION:
            pucArray = tSTRING_SELECTREGION;
            break;
        case _STRING_PICTURE:
            pucArray = tSTRING_PICTURE;
            break;
        case _STRING_ANALOG:
            pucArray = tSTRING_ANALOG;
            break;
        case _STRING_COLOR:
            pucArray = tSTRING_COLOR;
            break;
        case _STRING_ADVANCE:
            pucArray = tSTRING_ADVANCE;
            break;
        case _STRING_INPUT:
            pucArray = tSTRING_INPUT;
            break;
        case _STRING_AUDIO:
            pucArray = tSTRING_AUDIO;
            break;
        case _STRING_OTHER:
            pucArray = tSTRING_OTHER;
            break;
        case _STRING_INFORMATION:
            pucArray = tSTRING_INFORMATION;
            break;
        case _STRING_FACTORY:
            pucArray = tSTRING_FACTORY;
            break;

        // display mode
        case _STRING_1P:
            pucArray = tSTRING_1P;
            break;
        case _STRING_2P_LR:
            pucArray = tSTRING_2P_LR;
            break;
        case _STRING_2P_TB:
            pucArray = tSTRING_2P_TB;
            break;
        case _STRING_2P_PIP:
            pucArray = tSTRING_2P_PIP;
            break;
        case _STRING_4P:
            pucArray = tSTRING_4P;
            break;

        // display function
        case _STRING_DISP_ROTATE:
            pucArray = tSTRING_DISP_ROTATE;
            break;
        case _STRING_DISP_LATENCY:
            pucArray = tSTRING_LATENCY;
            break;
        case _STRING_DISP_LR_RATIO:
            pucArray = tSTRING_DISP_LR_RATIO;
            break;
        case _STRING_PIP_POSITION:
            pucArray = tSTRING_PIP_POSITION;
            break;
        case _STRING_PIP_USER_POSITION_H:
            pucArray = tSTRING_PIP_USER_POSITION_H;
            break;
        case _STRING_PIP_USER_POSITION_V:
            pucArray = tSTRING_PIP_USER_POSITION_V;
            break;
        case _STRING_PIP_TRANSPARENCY:
            pucArray = tSTRING_PIP_TRANSPARENCY;
            break;
        case _STRING_PIP_SIZE:
            pucArray = tSTRING_PIP_SIZE;
            break;

        case _STRING_INPUT_SWAP:
            pucArray = tSTRING_INPUT_SWAP;
            break;

        // select region
        case _STRING_2P_LR_L:
            pucArray = tSTRING_2P_LR_L;
            break;
        case _STRING_2P_LR_R:
            pucArray = tSTRING_2P_LR_R;
            break;
        case _STRING_2P_LR_FULL:
            pucArray = tSTRING_2P_LR_FULL;
            break;
        case _STRING_2P_TB_T:
            pucArray = tSTRING_2P_TB_T;
            break;
        case _STRING_2P_TB_B:
            pucArray = tSTRING_2P_TB_B;
            break;
        case _STRING_2P_TB_FULL:
            pucArray = tSTRING_2P_TB_FULL;
            break;
        case _STRING_2P_PIP_MAIN:
            pucArray = tSTRING_2P_PIP_MAIN;
            break;
        case _STRING_2P_PIP_SUB:
            pucArray = tSTRING_2P_PIP_SUB;
            break;
        case _STRING_2P_PIP_FULL:
            pucArray = tSTRING_2P_PIP_FULL;
            break;
        case _STRING_4P_LT_IN:
            pucArray = tSTRING_4P_LT_IN;
            break;
        case _STRING_4P_LT_OUT:
            pucArray = tSTRING_4P_LT_OUT;
            break;
        case _STRING_4P_RT_IN:
            pucArray = tSTRING_4P_RT_IN;
            break;
        case _STRING_4P_RT_OUT:
            pucArray = tSTRING_4P_RT_OUT;
            break;
        case _STRING_4P_LB_IN:
            pucArray = tSTRING_4P_LB_IN;
            break;
        case _STRING_4P_LB_OUT:
            pucArray = tSTRING_4P_LB_OUT;
            break;
        case _STRING_4P_RB_IN:
            pucArray = tSTRING_4P_RB_IN;
            break;
        case _STRING_4P_RB_OUT:
            pucArray = tSTRING_4P_RB_OUT;
            break;
        case _STRING_4P_FULL:
            pucArray = tSTRING_4P_FULL;
            break;

        // picture
        case _STRING_BACKLIGHT:
            pucArray = tSTRING_BACKLIGHT;
            break;
        case _STRING_BRIGHTNESS:
            pucArray = tSTRING_BRIGHTNESS;
            break;
        case _STRING_CONTRAST:
            pucArray = tSTRING_CONTRAST;
            break;
        case _STRING_SHARPNESS:
            pucArray = tSTRING_SHARPNESS;
            break;

        // display
        case _STRING_AUTO_ADJUST:
            pucArray = tSTRING_AUTO_ADJUST;
            break;
        case _STRING_HPOS:
            pucArray = tSTRING_HPOS;
            break;
        case _STRING_VPOS:
            pucArray = tSTRING_VPOS;
            break;
        case _STRING_CLOCK:
            pucArray = tSTRING_CLOCK;
            break;
        case _STRING_PHASE:
            pucArray = tSTRING_PHASE;
            break;

        // color
        case _STRING_PANEL_UNIFORMITY:
            pucArray = tSTRING_PANEL_UNIFORMITY;
            break;

        case _STRING_GAMMA:
            pucArray = tSTRING_GAMMA;
            break;
        case _STRING_COLOR_TEMP:
            pucArray = tSTRING_COLOR_TEMP;
            break;
        case _STRING_COLOR_EFFECT:
            pucArray = tSTRING_COLOR_EFFECT;
            break;
        case _STRING_DEMO:
            pucArray = tSTRING_DEMO;
            break;
        case _STRING_COLOR_FORMAT:
            pucArray = tSTRING_COLOR_FORMAT;
            break;
        case _STRING_PCM:
            pucArray = tSTRING_PCM;
            break;
        case _STRING_HUE:
            pucArray = tSTRING_HUE;
            break;
        case _STRING_SATURATION:
            pucArray = tSTRING_SATURATION;
            break;
        // advance
        case _STRING_ASPECT_RATIO:
            pucArray = tSTRING_ASPECT_RATIO;
            break;
        case _STRING_OVER_SCAN:
            pucArray = tSTRING_OVER_SCAN;
            break;
        case _STRING_OVER_DRIVE:
            pucArray = tSTRING_OVER_DRIVE;
            break;
        case _STRING_DDCCI:
            pucArray = tSTRING_DDCCI;
            break;
        case _STRING_ULTRA_VIVID:
            pucArray = tSTRING_ULTRA_VIVID;
            break;
        case _STRING_DCR:
            pucArray = tSTRING_DCR;
            break;
        case _STRING_DP_OPTION:
            pucArray = tSTRING_DP_OPTION;
            break;
        case _STRING_DP_MST:
            pucArray = tSTRING_DP_MST;
            break;
        case _STRING_DP_EDID:
            pucArray = tSTRING_DP_EDID;
            break;
        case _STRING_CLONE:
            pucArray = tSTRING_CLONE;
            break;
        case _STRING_FREESYNC:
            pucArray = tSTRING_FREESYNC;
            break;
        case _STRING_FREEZE:
            pucArray = tSTRING_FREEZE;
            break;

        case _STRING_DP_LANE_COUNT:
            pucArray = tSTRING_DP_LANE_COUNT;
            break;

#if(_ULTRA_HDR_SUPPORT == _ON)
        case _STRING_HDR:
            pucArray = tSTRING_HDR;
            break;
#endif

#if (_FALSE_COLOR_SUPPORT == _ON)
        case _STRING_FALSE_COLOR:
            pucArray = tSTRING_FALSE_COLOR;
            break;
#endif
        case _STRING_SINGLE_DP_EDID:
            pucArray = tSTRING_SINGLE_DP_EDID;
            break;
        case _STRING_DUAL_DP_EDID:
            pucArray = tSTRING_DUAL_DP_EDID;
            break;


        // audio
        case _STRING_VOLUME:
            pucArray = tSTRING_VOLUME;
            break;
        case _STRING_MUTE:
            pucArray = tSTRING_MUTE;
            break;
        case _STRING_STAND_ALONG:
            pucArray = tSTRING_STAND_ALONG;
            break;
        case _STRING_AUDIO_SOURCE:
            pucArray = tSTRING_AUDIO_SOURCE;
            break;
        case _STRING_SOUND_MODE:
            pucArray = tSTRING_SOUND_MODE;
            break;
        // other
        case _STRING_RESET:
            pucArray = tSTRING_RESET;
            break;
        case _STRING_MENU_TIME:
            pucArray = tSTRING_MENU_TIME;
            break;
        case _STRING_OSD_HPOS:
            pucArray = tSTRING_OSD_HPOS;
            break;
        case _STRING_OSD_VPOS:
            pucArray = tSTRING_OSD_VPOS;
            break;
        case _STRING_LANGUAGE:
            pucArray = tSTRING_LANGUAGE;
            break;
        case _STRING_TRANSPARENCY:
            pucArray = tSTRING_TRANSPARENCY;
            break;
        case _STRING_ROTATE:
            pucArray = tSTRING_ROTATE;
            break;
        case _STRING_SHOW_NUMBER:
            pucArray = g_pucShowNumberAddress;
            break;
        case _STRING_BORDER_WIDTH:
            pucArray = tSTRING_BORDER_WIDTH;
            break;
        case _STRING_BORDER_COLOR:
            pucArray = tSTRING_BORDER_COLOR;
            break;

        // information
        case _STRING_HFREQPCLK:
            pucArray = OsdPropGetShowHFreqPClkStringAddress();
            break;
        case _STRING_VFREQUENCY:
            pucArray = OsdPropGetShowVFreqStringAddress();
            break;
        case _STRING_VGA_USER_MODE:
            pucArray = tSTRING_OSD_MODE_UER;
            break;
        case _STRING_VGA_PRESET_MODE:
            pucArray = tSTRING_OSD_MODE_PERSET;
            break;
        case _STRING_HDCP_MODE:
#if(_DIGITAL_PORT_SUPPORT == _ON)
            pucArray = OsdPropGetShowHDCPEnable(ScalerSyncHdcpCheckEnabled(SysRegionGetPortType(SysRegionGetMeasureResultPointerRegion())));
#endif
            break;

        // Input Source
        case _STRING_InputSource_1P:
            pucArray = tSTRING_InputSource_1P;
            break;
        case _STRING_InputSource_2P:
            pucArray = tSTRING_InputSource_2P;
            break;
        case _STRING_InputSource_3P:
            pucArray = tSTRING_InputSource_3P;
            break;
        case _STRING_InputSource_4P:
            pucArray = tSTRING_InputSource_4P;
            break;

        // Adjust message
        case _STRING_PLEASE_WAIT:
            pucArray = tSTRING_PLEASE_WAIT_MSG;
            break;

        case _STRING_NO_SIGNAL:
            pucArray = tSTRING_NO_SIGNAL;
            break;

        case _STRING_NO_CABLE:
            pucArray = tSTRING_NO_CABLE;
            break;

        case _STRING_NO_SUPPORT:
            pucArray = tSTRING_NO_SUPPORT;
            break;

        case _STRING_GO_TO_POWER_SAVING_MODE:
            pucArray = tSTRING_GO_TO_POWER_SAVING_MODE;
            break;

        case _STRING_NOW_RESOLUTION:
            pucArray = OsdPropGetShowResolutionStringAddress();
            break;

        case _STRING_AUTO_COLOR:
            pucArray = tSTRING_AUTO_COLOR;
            break;

        case _STRING_AUTO_SELECT:
            pucArray = tSTRING_AUTO_SELECT;
            break;

        case _STRING_PASS:
            pucArray = tSTRING_PASS;
            break;

        case _STRING_FAIL:
            pucArray = tSTRING_FAIL;
            break;

        case _STRING_2P:
            pucArray = tSTRING_2P;
            break;

        case _STRING_3P:
            pucArray = tSTRING_3P;
            break;


        case _STRING_A0_PORT:
        case _STRING_D0_PORT:
        case _STRING_D1_PORT:
        case _STRING_D2_PORT:
        case _STRING_D3_PORT:
        case _STRING_D4_PORT:
        case _STRING_D5_PORT:
        case _STRING_D6_PORT:
        case _STRING_D7_PORT:
            pucArray = OsdPropGetShowInputPortStringAddress(ucString - _STRIN_END);
            break;

        case _STRING_AUTOSELECT_PORT:
            pucArray = tSTRING_AUTOSELECT;
            break;
#if(_FREESYNC_SUPPORT == _ON)
        case _STRING_FREESYNC_SUPPORT_V_RANGE:
            pucArray = OsdPropGetShowFreeSyncVFreqRangeStringAddress();
            break;
#endif
#if (_FALSE_COLOR_SUPPORT == _ON)
        case _STRING_FALSE_COLOR_CURSOR_1:
            pucArray = tSTRING_FALSE_COLOR_CURSOR_1;
            break;
        case _STRING_FALSE_COLOR_CURSOR_2:
            pucArray = tSTRING_FALSE_COLOR_CURSOR_2;
            break;
#endif

        default:
            break;
    }

    return pucArray;
}
#endif//#if(_OSD_TYPE == _REALTEK_2014_OSD)
