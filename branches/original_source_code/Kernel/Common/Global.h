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
// ID Code      : Global.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "reg52_RTD.h"
#include "intrins.h"
#include "string.h"
#include "math.h"

//****************************************************************************
// Data Type Redefine
//****************************************************************************
typedef unsigned char BYTE;
typedef char          SBYTE;
typedef unsigned int  WORD;
typedef int           SWORD;
typedef unsigned long DWORD;
typedef long          SDWORD;

typedef unsigned char uint8_t;
typedef char          int8_t;
typedef unsigned int  uint16_t;
typedef int           int16_t;
typedef long		  int32_t;
typedef unsigned long uint32_t;

//****************************************************************************
// Extern pData for All Layer Temporary Use
//****************************************************************************
extern BYTE data pData[16];
extern BYTE g_ucPcbGpioDefault;

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _INPUT_PATH_NONE = 0,
    _INPUT_PATH_M1 = 0x01,
    _INPUT_PATH_M2 = 0x02,
    _INPUT_PATH_M1_M2 = 0x03,
    _INPUT_PATH_S1 = 0x04,
    _INPUT_PATH_S2 = 0x08,
    _INPUT_PATH_S1_S2 = 0x0C,
    _INPUT_PATH_ALL = 0x0F,
} EnumInputDataPath;

typedef enum
{
    _DISPLAY_PATH_NONE = 0,
    _DISPLAY_PATH_M1 = 0x01,
    _DISPLAY_PATH_M2 = 0x02,
    _DISPLAY_PATH_M1_M2 = 0x03,
    _DISPLAY_PATH_S1 = 0x04,
    _DISPLAY_PATH_S2 = 0x08,
    _DISPLAY_PATH_S1_S2 = 0x0C,
    _DISPLAY_PATH_ALL = 0x0F,
} EnumDisplayDataPath;

typedef enum
{
    _MAPPING_DISPLAY_PATH_M1 = 0x00,
    _MAPPING_DISPLAY_PATH_M2 = 0x01,
    _MAPPING_DISPLAY_PATH_S1 = 0x02,
    _MAPPING_DISPLAY_PATH_S2 = 0x03,
} EnumInputDisplayMapping;

typedef struct
{
    WORD usHStart;
    WORD usHWidth;
    WORD usVStart;
    WORD usVHeight;
}StructTimingFormat;

// Struct for all Timing Info
typedef struct
{
    EnumInputDataPath enumInputDataPath : 4;        // Input data path (M1 ~ S2)
    BYTE b1HSP : 1;             // HSP
    BYTE b1VSP : 1;             // VSP
    BYTE b1Interlace : 1;       // Interlace
    BYTE b1VideoField : 1;      // Field for video compensation
    WORD usHFreq;               // Horizontal Freq. (unit: 0.1kHz)
    WORD usHTotal;              // Horizontal Total length (unit: Pixel)
    WORD usHWidth;              // Horizontal Active Width (unit: Pixel)
    WORD usHStart;              // Horizontal Start (unit: Pixel)
    WORD usHSWidth;             // Horizontal Sync Pulse Count (unit: SyncProc Clock)

    WORD usVFreq;               // Vertical Freq. (unit: 0.1Hz)
    WORD usVTotal;              // Vertical Total length (unit: HSync)
    WORD usVHeight;             // Vertical Active Height (unit: HSync)
    WORD usVStart;              // Vertical Start (unit: HSync)
    WORD usVSWidth;             // Vertical Sync Width    (unit: HSync)
}StructTimingInfo;

typedef struct
{
    BYTE b4MeasurePort : 4;  // Measure port
    BYTE b1HSP : 1;
    BYTE b1VSP : 1;
    WORD usHSPeriod;
    WORD usHSWidth;
    WORD usVSPeriod;
    WORD usVSWidth;
    WORD usHTotal;
    WORD usHWidth;
    WORD usVHeight;
}StructMeasureSyncData;

typedef struct
{
    WORD usVActiveStart;
    WORD usVActiveEnd;
    WORD usHActiveStart;
    WORD usHActiveEnd;
}StructAutoActiveData;

typedef struct
{
    StructTimingInfo stTimingInfo;
    StructMeasureSyncData stMeasureSyncData;
    StructAutoActiveData stAutoActiveData;
}StructRegionTimingInfo;

// Struct for Display Timing Info
typedef struct
{
    EnumDisplayDataPath enumDisplayDataPath; // Display data path
    WORD usHTotal;                // Horizontal Total length (unit: Pixel)
    WORD usHStart;                // Horizontal Start Position
    WORD usHWidth;                // Horizontal Active Width (unit: Pixel)
    WORD usHBackStart;            // Horizontal Back Ground Start Position
    WORD usHBackWidth;            // Horizontal Back Ground Active Width (unit: Pixel)

    WORD usVTotal;                // Vertical Total length (unit: HSync)
    WORD usVStart;                // Vertical Start Position
    WORD usVHeight;               // Vertical Active Height (unit: HSync)
    WORD usVBackStart;            // Vertical Back Ground Start Position
    WORD usVBackHeight;           // Vertical Back Ground Active Height (unit: HSync)
}StructDisplayInfo;

typedef struct
{
    WORD usMaxFreq;
    WORD usTypFreq;
    WORD usMinFreq;
} StructDVCustomizedFreq;

typedef enum
{
    _DDOMAIN_SRC_FRAM_FRC,
    _DDOMAIN_SRC_FRAM_FRAME_SYNC_MODE,
} EnumDDomainSourceSelect;

typedef enum
{
    _DISPLAY_MODE_1P = 0x00,
    _DISPLAY_MODE_PIP = 0x10,
    _DISPLAY_MODE_PBP_LR = 0x20,
    _DISPLAY_MODE_PBP_TB = 0x30,
    _DISPLAY_MODE_4P = 0x40,
    _DISPLAY_MODE_NONE = 0xF0,
} EnumDisplayMode;

typedef enum
{
    _REGION_INDEX_0 = 0x00,
    _REGION_INDEX_1 = 0x01,
    _REGION_INDEX_2 = 0x02,
    _REGION_INDEX_3 = 0x03,
    _REGION_INDEX_NONE = 0x0F,
} EnumRegionIndex;

typedef enum
{
    _DISPLAY_RGN_1P = _DISPLAY_MODE_1P,

    _DISPLAY_RGN_MAIN = (_DISPLAY_MODE_PIP | _REGION_INDEX_0),
    _DISPLAY_RGN_SUB = (_DISPLAY_MODE_PIP | _REGION_INDEX_1),

    _DISPLAY_RGN_LEFT = (_DISPLAY_MODE_PBP_LR | _REGION_INDEX_0),
    _DISPLAY_RGN_RIGHT = (_DISPLAY_MODE_PBP_LR | _REGION_INDEX_1),

    _DISPLAY_RGN_TOP = (_DISPLAY_MODE_PBP_TB | _REGION_INDEX_0),
    _DISPLAY_RGN_BOTTOM = (_DISPLAY_MODE_PBP_TB | _REGION_INDEX_1),

    _DISPLAY_RGN_LT = (_DISPLAY_MODE_4P | _REGION_INDEX_0),
    _DISPLAY_RGN_LB = (_DISPLAY_MODE_4P | _REGION_INDEX_1),
    _DISPLAY_RGN_RT = (_DISPLAY_MODE_4P | _REGION_INDEX_2),
    _DISPLAY_RGN_RB = (_DISPLAY_MODE_4P | _REGION_INDEX_3),

    _DISPLAY_RGN_NONE = (_DISPLAY_MODE_NONE | _REGION_INDEX_NONE),
} EnumDisplayRegion;

typedef enum
{
    _1P_NORMAL_FULL_REGION = _DISPLAY_RGN_1P,
    _1P_ROTATION_FULL_REGION,
    _1P_NORMAL_DEMO_INSIDE,
    _1P_NORMAL_DEMO_OUTSIDE,

    _PIP_MAIN = _DISPLAY_RGN_MAIN,
    _PIP_SUB = _DISPLAY_RGN_SUB,
    _PIP_FULL_REGION,
    _PIP_DEMO_INSIDE,
    _PIP_DEMO_OUTSIDE,

    _PBP_LR_L = _DISPLAY_RGN_LEFT,
    _PBP_LR_R = _DISPLAY_RGN_RIGHT,
    _PBP_LR_FULL_REGION,
    _PBP_LR_DEMO_INSIDE,
    _PBP_LR_DEMO_OUTSIDE,

    _PBP_TB_T = _DISPLAY_RGN_TOP,
    _PBP_TB_B = _DISPLAY_RGN_BOTTOM,
    _PBP_TB_FULL_REGION,
    _PBP_TB_DEMO_INSIDE,
    _PBP_TB_DEMO_OUTSIDE,

    _4P_LT = _DISPLAY_RGN_LT,
    _4P_LB = _DISPLAY_RGN_LB,
    _4P_RT = _DISPLAY_RGN_RT,
    _4P_RB = _DISPLAY_RGN_RB,
    _4P_LT_OUTSIDE,
    _4P_LB_OUTSIDE,
    _4P_RT_OUTSIDE,
    _4P_RB_OUTSIDE,
    _4P_FULL_REGION,
    _4P_DEMO_INSIDE,
    _4P_DEMO_OUTSIDE,

    _NON_REGION = _DISPLAY_RGN_NONE,
} EnumSelRegion;

typedef struct
{
    EnumDisplayMode enumDisplayMode;
    BYTE b3MemorySelect : 3;
    BYTE b3DVFSelect : 3;
    BYTE b2MemoryConf : 2;
    BYTE b5DataBit : 5;
    BYTE b1HSU : 1;
    BYTE b1HSD : 1;
    BYTE b1VSU : 1;
    BYTE b1VSD : 1;
    BYTE b2MemoryFrameBuf : 2;
} StructMDomainInfo;

typedef struct
{
    BYTE ucAdcPGA;
    BYTE pucAdcGainMSB[3];
    BYTE pucAdcGainLSB[3];
    BYTE pucAdcOffsetMSB[3];
    BYTE pucAdcOffsetLSB[3];
} StructAdcDataType;

typedef struct
{
    WORD usInputHWidth;
    WORD usInputVHeight;
    WORD usOutputHWidth;
    WORD usOutputVHeight;
} StructSDRAMDataInfo;

//--------------------------------------------------
// Definitions of SDRAM Calibration Status
//--------------------------------------------------
typedef struct
{
    BYTE b1FirstAutoKStatus : 1;
    BYTE b1CasChangeStatus : 1;
    BYTE b1DCOnOnLineStatus : 1;
}StructSDRAMCalControl;

//--------------------------------------------------
// Definitions of DDR3 MultiPhase Info
//--------------------------------------------------
typedef struct
{
    DWORD ulDdrPllInitialPhase0;
    DWORD ulDdrPllInitialPhase1;
    DWORD ulDdrReadDqDelayTap;
} StructDDR3PhaseInfo;

//--------------------------------------------------
// Definitions for DP Margin Link
//--------------------------------------------------
typedef struct
{
    BYTE b1D0MarginLinkHBRRBR : 1;
    BYTE b1D0Lane0MarginLinkHBRRBR : 1;
    BYTE b1D0Lane1MarginLinkHBRRBR : 1;
    BYTE b1D0Lane2MarginLinkHBRRBR : 1;
    BYTE b1D0Lane3MarginLinkHBRRBR : 1;
    BYTE b1D1MarginLinkHBRRBR : 1;
    BYTE b1D1Lane0MarginLinkHBRRBR : 1;
    BYTE b1D1Lane1MarginLinkHBRRBR : 1;
    BYTE b1D1Lane2MarginLinkHBRRBR : 1;
    BYTE b1D1Lane3MarginLinkHBRRBR : 1;
    BYTE b1D6MarginLinkHBRRBR : 1;
} StructDPMarginLinkInfo;

//--------------------------------------------------
// Struct for Type-C SMBus Command
//--------------------------------------------------
typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDataByte0;
} StructSMBusWRGetICStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucFWMainVer;
    BYTE ucFWSubVer1;
    BYTE ucFWSubVer2;
    BYTE ucByte6;
    BYTE ucByte7;
    BYTE ucPDTypeCStatus;
    BYTE ucByte9;
    BYTE ucByte10;
    BYTE ucByte11;
    BYTE ucByte12;
    BYTE ucSMBusReadyStatus;
    BYTE ucByte14;
    BYTE ucByte15;
    BYTE ucByte16;
    BYTE ucByte17;
    BYTE ucByte18;
    BYTE ucByte19;
} StructSMBusRDGetICStatus;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
    BYTE ucDPCapVDOByte3;
} StructSMBusWRSetDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
} StructSMBusWRReadDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucPortNum;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
} StructSMBusRDReadDPLanes;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDPCfgVDOByte0;
    BYTE ucDPCfgPinConfig;
    BYTE ucDPCfgVDOByte2;
    BYTE ucDPCfgVDOByte3;
} StructSMBusRDReadDPLanesCfg;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
    BYTE ucDPCapVDOByte0;
    BYTE ucDPCapVDOByte1;
    BYTE ucDPCapVDOByte2;
    BYTE ucDPCapVDOByte3;
} StructSMBusWRSetDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucSubCommandCode;
    BYTE ucPortNum;
    BYTE ucVDOOrigin;
    BYTE ucVDOType;
} StructSMBusWRReadDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDPStatusVDOByte0;
    BYTE ucDPStatusVDOByte1;
    BYTE ucDPStatusVDOByte2;
    BYTE ucDPStatusVDOByte3;
} StructSMBusRDReadDPMultiFunction;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucPortNum;
    BYTE ucByte2;
} StructSMBusWRReconnect;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
} StructSMBusWrSetSSMode;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucByte0;
    BYTE ucByte1;
    BYTE ucByte2;
    BYTE ucByte3;
} StructSMBusWRDetectDSPSSMode;

typedef struct
{
    BYTE ucCommandCode;
    BYTE ucDataLength;
    BYTE ucDSP0;
    BYTE ucDSP1;
    BYTE ucDSP2;
    BYTE ucDSP3;
} StructSMBusRDDetectDSPSSMode;

typedef struct
{
    BYTE ucCommandStatus;
    BYTE ucDataLength;
} StructSMBusRDCommandReadyStatus;

union UnionSMBusWRCommandStrct
{
    StructSMBusWRGetICStatus stWrGetICStatus;
    StructSMBusWRSetDPMultiFunction stWrSetDPMultiFunction;
    StructSMBusWRReadDPMultiFunction stWrReadDPMultiFunction;
    StructSMBusWRSetDPLanes stWrSetDPLanes;
    StructSMBusWRReadDPLanes stWrReadDPLanes;
    StructSMBusWRReconnect stWrReconnect;
    StructSMBusWrSetSSMode stWrSetSSMode;
    StructSMBusWRDetectDSPSSMode stWrSetDetectDspSSMode;
};

union UnionSMBusRDCommandStrct
{
    StructSMBusRDCommandReadyStatus stRdCommandReadyStatus;
    StructSMBusRDGetICStatus stRdGetICStatus;
    StructSMBusRDReadDPMultiFunction stRdDPMultiFunction;
    StructSMBusRDReadDPLanes stRdDPlanes;
    StructSMBusRDReadDPLanesCfg stRdDPlanesCfg;
    StructSMBusRDDetectDSPSSMode stRdDetectDspSSMode;
};

typedef struct
{
    BYTE b1CableDetectFlag : 1;
    BYTE b1AltModeStatusLastCheck : 1;
    BYTE b4Lanes : 4;
} StructPortController;

typedef struct
{
    BYTE b7USBHubModeState : 7;
    BYTE b1SSDeviceDetecting : 1;
    BYTE b4UsbHubStatus : 4;
    BYTE b1UsbHubDeviceChangeFlg : 1;
} StructUsbHubInfo;

typedef struct
{
    BYTE b4AudioSamplingFreq : 4;
    BYTE b1AudioDetected : 1;
    BYTE b1AudioICodeReloaded : 1;
    BYTE b2AudioDigitalSource : 2;
} StructAudioDigitalInfo;

typedef enum
{
    _SMBUS_CMD_STATUS_NOTPROCEED = 0x00,
    _SMBUS_CMD_STATUS_COMPLETE = 0x01,
    _SMBUS_CMD_STATUS_DEFER = 0x02,
} EnumSMBusCmdStatus;

//--------------------------------------------------
// Enumerations of USB SS Device Mode State
//--------------------------------------------------
typedef enum
{
    _USB_MODE_STATUS_INITIAL = 0x00,
    _USB_MODE_STATUS_DETECT_SS_STATE = 0x01,
    _USB_MODE_STATUS_SS_STATE = 0x02,
    _USB_MODE_STATUS_PS_STATE = 0x03,
    _USB_MODE_STATUS_PD_STATE = 0x04,
    _USB_MODE_STATUS_NONE = 0xFF,
} EnumUsbModeStatus;

//--------------------------------------------------
// Structure of DP Lanes Mapping
//--------------------------------------------------
typedef struct
{
    BYTE b2Lane0Mapping : 2;
    BYTE b2Lane1Mapping : 2;
    BYTE b2Lane2Mapping : 2;
    BYTE b2Lane3Mapping : 2;
    BYTE b1PNSwap : 1;
} StructDpLanesMapping;

//****************************************************************************
// General Definitions
//****************************************************************************
//--------------------------------------------------
// Definitions of Physical Boolean
//--------------------------------------------------
#define _TRUE                                   1
#define _FALSE                                  0
#define _LOW_FOR_MST                            2
#define _HIGH                                   1
#define _LOW                                    0
#define _ENABLE                                 1
#define _DISABLE                                0
#define _READ                                   1
#define _WRITE                                  0
#define _ON                                     1
#define _OFF                                    0
#define _SUCCESS                                1
#define _FAIL                                   0
#define _STABLE                                 1
#define _UNSTABLE                               0
#define _POSITIVE                               1
#define _NEGATIVE                               0
#define _NEWMODE                                1
#define _OLDMODE                                0
#define _ODD                                    1
#define _EVEN                                   0
#define _WAIT                                   1
#define _NOT_WAIT                               0
#define _RIGHT                                  1
#define _LEFT                                   0
#define _EDID_SWITCH_MODE                       1
#define _MCCS_SWITCH_MODE                       0

//--------------------------------------------------
// Definitions of Page
//--------------------------------------------------
#define _PAGE0                                  0
#define _PAGE1                                  1
#define _PAGE2                                  2
#define _PAGE3                                  3
#define _PAGE4                                  4
#define _PAGE5                                  5
#define _PAGE6                                  6
#define _PAGE7                                  7
#define _PAGE8                                  8
#define _PAGE9                                  9
#define _PAGEA                                  10
#define _PAGEB                                  11
#define _PAGEC                                  12
#define _PAGED                                  13
#define _PAGEE                                  14
#define _PAGEF                                  15
#define _PAGE10                                 16

#define _PAGE_COMMON                            255

//--------------------------------------------------
// Definitions of Bits
//--------------------------------------------------
#define _BIT0                                   0x0001U
#define _BIT1                                   0x0002U
#define _BIT2                                   0x0004U
#define _BIT3                                   0x0008U
#define _BIT4                                   0x0010U
#define _BIT5                                   0x0020U
#define _BIT6                                   0x0040U
#define _BIT7                                   0x0080U
#define _BIT8                                   0x0100U
#define _BIT9                                   0x0200U
#define _BIT10                                  0x0400U
#define _BIT11                                  0x0800U
#define _BIT12                                  0x1000U
#define _BIT13                                  0x2000U
#define _BIT14                                  0x4000U
#define _BIT15                                  0x8000U
#define _BIT16                                  0x10000U

//--------------------------------------------------
// Definitions of Clock Divider Number
//--------------------------------------------------
#define _DIV_1                                  1
#define _DIV_2                                  2
#define _DIV_3                                  3
#define _DIV_4                                  4
#define _DIV_5                                  5
#define _DIV_6                                  6
#define _DIV_7                                  7
#define _DIV_8                                  8
#define _DIV_9                                  9
#define _DIV_10                                 10
#define _DIV_11                                 11
#define _DIV_12                                 12
#define _DIV_13                                 13

//--------------------------------------------------
// Definations of Scaler Write/Read Type
//--------------------------------------------------
#define _NON_AUTOINC                            1
#define _AUTOINC                                0
#define _BURST                                  2
#define _END                                    0

//--------------------------------------------------
// Definitions of Null Pointer
//--------------------------------------------------
#define _NULL_POINTER                           ((BYTE code *)0xFFFF)

//--------------------------------------------------
// Definitions of Page Register
//--------------------------------------------------
#define _REG_MAIN1_PAGE                         0x0000U
#define _REG_MAIN2_PAGE                         0x4000U
#define _REG_SUB1_PAGE                          0x8000U
#define _REG_SUB2_PAGE                          0xC000U

#define _REG_PAGE_OFFSET                        (_REG_MAIN2_PAGE - _REG_MAIN1_PAGE)

//--------------------------------------------------
// Definitions of Checker
//--------------------------------------------------
#define _ERROR_PRONE_CODE                       (_TRUE)

//****************************************************************************
// Definitions of TMDS
//****************************************************************************
//--------------------------------------------------
// Definitions of TMDS HPD Type
//--------------------------------------------------
#define _TMDS_HPD_NONE                          0
#define _TMDS_HPD_NORMAL                        1
#define _TMDS_HPD_HDCP_2_2                      2
#define _TMDS_HPD_ACER                          3

//****************************************************************************
// Definitions of Audio
//****************************************************************************
//--------------------------------------------------
// Definitions of Audio Volume Resolution
//--------------------------------------------------
#define _AUDIO_VOLUME_8BIT                      0
#define _AUDIO_VOLUME_14BIT                     1    // DVC  Support Only

//--------------------------------------------------
// Definitions of Analog Audio Input Type
//--------------------------------------------------
#define _AUDIO_FROM_AIN                         0
#define _AUDIO_FROM_DAC                         1

//****************************************************************************
// Definitions of Auto
//****************************************************************************
//--------------------------------------------------
// Definitions of Auto Function Channel
//--------------------------------------------------
#define _AUTO_RED_CHANNEL                       0
#define _AUTO_GREEN_CHANNEL                     1
#define _AUTO_BLUE_CHANNEL                      2
#define _AUTO_RGB_CHANNEL                       3


//****************************************************************************
// Definitions of CBUS
//****************************************************************************
#define _CBUS0                                  0
#define _CBUS1                                  1
#define _CBUS2                                  2
#define _CBUS3                                  3
#define _NO_CBUS                                4

//****************************************************************************
// Definitions of Digital Functions
//****************************************************************************
//--------------------------------------------------
// Definitions of DCR Source Option
//--------------------------------------------------
#define _DCR_BEFORE_DCC                         0
#define _DCR_BEFORE_IAPSGAIN                    1

//--------------------------------------------------
// Definitions of Highlight Window Option
//--------------------------------------------------
#define _HLW_BORDER_BOTTOM                      _BIT4
#define _HLW_BORDER_TOP                         _BIT5
#define _HLW_BORDER_RIGHT                       _BIT6
#define _HLW_BORDER_LEFT                        _BIT7

//--------------------------------------------------
// Definitions of ICM Adjust Option
//--------------------------------------------------
#define _CM0_ENABLE                             _BIT0
#define _CM1_ENABLE                             _BIT1
#define _CM2_ENABLE                             _BIT2
#define _CM3_ENABLE                             _BIT3
#define _CM4_ENABLE                             _BIT4
#define _CM5_ENABLE                             _BIT5
#define _Y_CORRECTION_MODE                      _BIT6
#define _UV_DELTA_RANGE                         _BIT7
#define _UV_DELTA_RANGE_EXTEND                  _BIT0

#define _SCM0_BLOCK0_ENABLE                     _BIT0
#define _SCM0_BLOCK1_ENABLE                     _BIT1
#define _SCM1_BLOCK0_ENABLE                     _BIT2
#define _SCM1_BLOCK1_ENABLE                     _BIT3
#define _SCM2_BLOCK0_ENABLE                     _BIT4
#define _SCM2_BLOCK1_ENABLE                     _BIT5
#define _SCM3_BLOCK0_ENABLE                     _BIT6
#define _SCM3_BLOCK1_ENABLE                     _BIT7
#define _SCMN_SHARE_REG                         _BIT0

//--------------------------------------------------
// Definitions of OD Table Mode
//--------------------------------------------------
#define _OD_8BIT_LUT                            0
#define _OD_10BIT_LUT                           1

//--------------------------------------------------
// Definitions of Panel Uniformity Level Correction Selection
//--------------------------------------------------
#define _UNIFORMITY_1LEVEL                      1
#define _UNIFORMITY_2LEVEL                      2
#define _UNIFORMITY_4LEVEL                      4

//****************************************************************************
// Definitions of EMCU
//****************************************************************************
//--------------------------------------------------
// Definations of DDC Channel
//--------------------------------------------------
#define _VGA_DDC                                0
#define _DDC0                                   1
#define _DDC1                                   2
#define _DDC2                                   3
#define _DDC3                                   4
#define _DDC4                                   5
#define _DDC5                                   6
#define _NO_DDC                                 7

//--------------------------------------------------
// Define for HW burst write
//--------------------------------------------------
#define _BURSTWRITE_FROM_FLASH                  0
#define _BURSTWRITE_FROM_XRAM                   1

#define _BURSTWRITE_COMMAND                     0
#define _BURSTWRITE_DATA_COMMON                 1
#define _BURSTWRITE_DATA_COMMON_AUTO_INC        2
#define _BURSTWRITE_DATA_OSD                    3

//--------------------------------------------------
// Reserved for pin define
//--------------------------------------------------
#define MCU_EMPTY_PIN_ASSIGN_ADDRESS            g_ucPcbGpioDefault


//****************************************************************************
// Definitions of IOSC
//****************************************************************************
//--------------------------------------------------
// Definitions of IOSC Clock Divider Number
//--------------------------------------------------
#define _IOSC_DIV_1                             0
#define _IOSC_DIV_2                             1
#define _IOSC_DIV_4                             2
#define _IOSC_DIV_8                             3

#define _IOSC_DIV                               _IOSC_DIV_1

//--------------------------------------------------
// Definitions of IOSC Frequency
//--------------------------------------------------
#define _IOSC27000K                             27000UL
#define _IOSC28000K                             28000UL

//****************************************************************************
// Definitions of Memory
//****************************************************************************
//--------------------------------------------------
// Definitions for Memory
//--------------------------------------------------
#define _FRAME_SYNC_LINE_BUFFER                 0
#define _FRAME_SYNC_MEMORY                      1
#define _FREE_RUN_MEMORY                        2
#define _MN_FRAME_SYNC_MEMORY                   3
#define _FREE_RUN_NO_INPUT                      4

//--------------------------------------------------
// Definitions of DVF type
//--------------------------------------------------
#define _1_IVF                                  0
#define _2_IVF                                  1
#define _3_IVF                                  2
#define _PANEL_TYP_FRAME_RATE_FREE_RUN          3
#define _2_5_IVF                                4
#define _5_4_IVF                                5
#define _6_5_IVF                                6

//--------------------------------------------------
// Definitions of Memory arrangement
//--------------------------------------------------
#define _LINE_MODE                              0
#define _FRAME_MODE                             1

//--------------------------------------------------
// Definitions of DDR Phase Calibration
//--------------------------------------------------
#define _MEMORY_PHASE_CALIBRATION_MCU_MODE      0
#define _MEMORY_PHASE_CALIBRATION_FRC_MODE      1
#define _MEMORY_PHASE_CALIBRATION_MODE_NONE     2

//****************************************************************************
// Definitions of MHL Packets
//****************************************************************************
//--------------------------------------------------
// Macros of MHL Reply List
//--------------------------------------------------
#define _MHL_SUCCESS                            0
#define _MHL_FAIL                               1
#define _MHL_ABORT_FAIL                         2
#define _MHL_PROTOCOL_ERROR                     3

//--------------------------------------------------
// Definitions of HDCP 2.2 RSA input parameter
//--------------------------------------------------
#define _HDCP_2_2_RSA_CIPHER_TEXT               0
#define _HDCP_2_2_RSA_RRMODN_KEY                1
#define _HDCP_2_2_RSA_D_KEY                     2
#define _HDCP_2_2_RSA_KPRIV_KEY                 3
#define _HDCP_2_2_RSA_N_PINV                    4
#define _HDCP_2_2_RSA_D_KEY_ENC                 5
#define _HDCP_2_2_CERT_RX                       6
#define _HDCP_2_2_LC                            7
#define _HDCP_2_2_KPUB_KM                       8
#define _HDCP_2_2_RRX                           9
#define _HDCP_2_2_RX_H_PRIME                    10
#define _HDCP_2_2_RX_PAIRING_INFO               11
#define _HDCP_2_2_RX_L_PRIME                    12
#define _HDCP_2_2_RX_M_PRIME                    13
#define _HDCP_2_2_RX_V_PRIME                    14

//****************************************************************************
// Definitions of Mode Search
//****************************************************************************
#define _USER_MODE_TYPE                         0
#define _PRESET_MODE_TYPE                       1

//****************************************************************************
// Definitions of NVRam
//****************************************************************************
#define _FLASH_PAGE_SIZE                        4096U

//****************************************************************************
// Definitions of M2PLL Freq
//****************************************************************************
#define _M2PLL_FREQ_243M                        0
#define _M2PLL_FREQ_351M                        1

//****************************************************************************
// Definitions of OSD
//****************************************************************************
typedef enum
{
    _OSD_WIN_CONTROL = 0,
    _OSD_SRAM = _BIT3,
} EnumOsdAddrIndicateType;

typedef enum
{
    _OSD_WITHOUT_DB = 0,
    _OSD_WITH_DB = _BIT7,
} EnumOsdDBufType;

typedef enum
{
    _OSD_BYTE0 = _BIT5,
    _OSD_BYTE1 = _BIT6,
    _OSD_BYTE2 = _BIT7,
    _OSD_BYTE0_BYTE1 = (_BIT6 | _BIT5),
    _OSD_BYTE0_BYTE2 = (_BIT7 | _BIT5),
    _OSD_BYTE1_BYTE2 = (_BIT7 | _BIT6),
    _OSD_BYTEALL = (_BIT7 | _BIT6 | _BIT5),
} EnumOsdWriteType;


//****************************************************************************
// Definitions of Panel
//****************************************************************************
//--------------------------------------------------
// Definitions of Panel Power Status
//--------------------------------------------------
#define _PANEL_POWER_OFF_STATE                  0
#define _WAITING_FOR_BACKLIGHT                  1
#define _READY_FOR_BACKLIGHT                    2
#define _BACKLIGHT_ON_ALREADY                   3
#define _PANEL_BACKLIGHT_OFF                    4


//--------------------------------------------------
// Definitions of Panel Power Action
//--------------------------------------------------
#define _PANEL_ON                               0
#define _PANEL_OFF                              1
#define _BACKLIGHT_ON                           2
#define _BACKLIGHT_OFF                          3


//****************************************************************************
// Definitions of Sync
//****************************************************************************
//--------------------------------------------------
// Definitions Of Two frame times
//--------------------------------------------------
#define _WAIT_TWO_FRAME_TIME                    90 // Reference 24 Hz, (1/24) * 2 = 83ms, give 7ms tolerance

//--------------------------------------------------
// Definitions of Input Sync Type State
//--------------------------------------------------
#define _NO_SYNC_STATE                          0
#define _SS_STATE                               1
#define _CS_STATE                               2
#define _SOG_STATE                              3
#define _SOY_STATE                              4
#define _DSS_STATE                              5
#define _NOT_SUPPORT_STATE                      0


//****************************************************************************
// Definitions of Source
//****************************************************************************
//--------------------------------------------------
// Definitions of Source Switch Type
//--------------------------------------------------
#define _SOURCE_SWITCH_FIXED_PORT               0
#define _SOURCE_SWITCH_AUTO_IN_GROUP            1
#define _SOURCE_SWITCH_DELL_HOTKEY_AUTO         2
#define _SOURCE_SWITCH_DELL_HOTKEY_FIXED        3

//--------------------------------------------------
// Definitions of Source Search Delay Mode
//--------------------------------------------------
#define _SOURCE_SEARCH_POLLING_MODE             0
#define _SOURCE_SEARCH_DELAY_DEFAULT_MODE       1
#define _SOURCE_SEARCH_DELAY_REACTIVE_MODE      2
#define _SOURCE_SEARCH_DELAY_NVRAM_PORT_MODE    3

//****************************************************************************
// Definitions of 3D
//****************************************************************************
//--------------------------------------------------
// Definitions of Chroma Weight for Depth Calculation
//--------------------------------------------------
#define _LUMINANCE                              0
#define _CHROMINANCE_1                          1
#define _CHROMINANCE_1_2                        2
#define _CHROMINANCE_1_4                        3

//--------------------------------------------------
// Definitions of LPF Weight Option
//--------------------------------------------------
#define _LPF_BLUR_STRONG                        0
#define _LPF_BLUR_MEDIUM                        1
#define _LPF_BLUR_WEAK                          2

//--------------------------------------------------
// Definitions of Hole Filling Mode
//--------------------------------------------------
#define _INTEGER_LEFT                           0
#define _INTEGER_INTERPOLATE                    1
#define _FRACTION_LEFT                          2
#define _FRACTION_INTERPOLATE                   3

//--------------------------------------------------
// Definitions of Dither Options
//--------------------------------------------------
#define _DDITHER_KEEP_1_FRAME                   0
#define _DDITHER_KEEP_2_FRAME                   1
#define _DDITHER_KEEP_4_FRAME                   2
#define _DDITHER_KEEP_8_FRAME                   3
#define _DDITHER_KEEP_16_FRAME                  4

#define _DDITHER_SUPER_PIXEL_2X2                0
#define _DDITHER_SUPER_PIXEL_2X4                1
#define _DDITHER_SUPER_PIXEL_4X2                2
#define _DDITHER_SUPER_PIXEL_4X4                3
#define _DDITHER_SUPER_PIXEL_4X8                4
#define _DDITHER_SUPER_PIXEL_8X4                5
#define _DDITHER_SUPER_PIXEL_8X8                6

//--------------------------------------------------
// Definitions of Color Depth
//--------------------------------------------------
#define _COLOR_DEPTH_6_BITS                     6
#define _COLOR_DEPTH_7_BITS                     7
#define _COLOR_DEPTH_8_BITS                     8
#define _COLOR_DEPTH_10_BITS                    10
#define _COLOR_DEPTH_12_BITS                    12
#define _COLOR_DEPTH_14_BITS                    14
#define _COLOR_DEPTH_16_BITS                    16

//--------------------------------------------------
// Macro of Instant Timer0/1 Counter Options
//--------------------------------------------------
#define _TIMER_OFF                              0

//****************************************************************************
// Definitions of Tcon
//****************************************************************************
//--------------------------------------------------
// Definitions of Tcon
//--------------------------------------------------
#define _TCON0                                  0
#define _TCON1                                  1
#define _TCON2                                  2
#define _TCON3                                  3
#define _TCON4                                  4
#define _TCON5                                  5
#define _TCON6                                  6
#define _TCON7                                  7
#define _TCON8                                  8
#define _TCON9                                  9
#define _TCON10                                 10
#define _TCON11                                 11
#define _TCON12                                 12
#define _TCON13                                 13

//****************************************************************************
// Global Macros
//****************************************************************************
#define LOBYTE(w)                               ((BYTE)(w))
#define HIBYTE(w)                               ((BYTE)(((WORD)(w) >> 8) & 0x00FF))
#define LOWORD(dw)                              ((WORD)(dw))
#define HIWORD(dw)                              ((WORD)((dw) >> 16))
#define SEC(x)                                  ((WORD)(1000U * (x)))

#define MAXOF(a, b)                             (((a) > (b)) ? (a) : (b))
#define MINOF(a, b)                             (((a) < (b)) ? (a) : (b))

#define SHL(x, y)                               ((x) << (y))
#define SHR(x, y)                               ((x) >> (y))
#define AND(n1, n2)                             ((n1) & (n2))

#define ABSDWORD(x, y)                          (((x) > (y)) ? ((x) - (y)) : ((y) - (x)))

#define GET_CURRENT_BANK_NUMBER()               (MCU_FFFF_PBANK_SWITCH)

//--------------------------------------------------
// Macro of Get Data bit
//--------------------------------------------------
#define GET_DATA_BIT7(x)                        ((bit)((x) & _BIT7))
#define GET_DATA_BIT6(x)                        ((bit)((x) & _BIT6))
#define GET_DATA_BIT5(x)                        ((bit)((x) & _BIT5))
#define GET_DATA_BIT4(x)                        ((bit)((x) & _BIT4))
#define GET_DATA_BIT3(x)                        ((bit)((x) & _BIT3))
#define GET_DATA_BIT2(x)                        ((bit)((x) & _BIT2))
#define GET_DATA_BIT1(x)                        ((bit)((x) & _BIT1))
#define GET_DATA_BIT0(x)                        ((bit)((x) & _BIT0))

//--------------------------------------------------
// Macro of WORD/DWORD pData
//--------------------------------------------------
#define PDATA_WORD(x)                           (((WORD *)pData)[x])
#define PDATA_WORD_EXINT(x)                     (((WORD *)pData_EXINT)[x])
#define PDATA_DWORD(x)                          (((DWORD *)pData)[x])
#define PDATA_DWORD_EXINT(x)                    (((DWORD *)pData_EXINT)[x])

//--------------------------------------------------
// Macro of Get Input Port and Port Type (x is Input Port Type)
//--------------------------------------------------
#define GET_INPUT_PORT(x)                       ((x) >> 4)
#define GET_PORT_TYPE(x)                        ((x) & 0x0F)

//--------------------------------------------------
// Macro of Cable Detect Flag
//--------------------------------------------------
#define GET_A0_CABLE_STATUS()                   (g_stPortCableStatus.b1A0CableDetect)
#define SET_A0_CABLE_STATUS(x)                  (g_stPortCableStatus.b1A0CableDetect = (x))

#define GET_D0_CABLE_STATUS()                   (g_stPortCableStatus.b1D0CableDetect)
#define SET_D0_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D0CableDetect = (x))

#define GET_D1_CABLE_STATUS()                   (g_stPortCableStatus.b1D1CableDetect)
#define SET_D1_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D1CableDetect = (x))

#define GET_D2_CABLE_STATUS()                   (g_stPortCableStatus.b1D2CableDetect)
#define SET_D2_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D2CableDetect = (x))

#define GET_D3_CABLE_STATUS()                   (g_stPortCableStatus.b1D3CableDetect)
#define SET_D3_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D3CableDetect = (x))

#define GET_D4_CABLE_STATUS()                   (g_stPortCableStatus.b1D4CableDetect)
#define SET_D4_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D4CableDetect = (x))

#define GET_D5_CABLE_STATUS()                   (g_stPortCableStatus.b1D5CableDetect)
#define SET_D5_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D5CableDetect = (x))

#define GET_D6_CABLE_STATUS()                   (g_stPortCableStatus.b1D6CableDetect)
#define SET_D6_CABLE_STATUS(x)                  (g_stPortCableStatus.b1D6CableDetect = (x))

#define GET_D0_TMDS_MODE()                      (g_stPortCableStatus.b1D0MHLCableDetect)
#define SET_D0_TMDS_MODE(x)                     (g_stPortCableStatus.b1D0MHLCableDetect = (x))

#define GET_D1_TMDS_MODE()                      (g_stPortCableStatus.b1D1MHLCableDetect)
#define SET_D1_TMDS_MODE(x)                     (g_stPortCableStatus.b1D1MHLCableDetect = (x))

#define GET_D2_TMDS_MODE()                      (g_stPortCableStatus.b1D2MHLCableDetect)
#define SET_D2_TMDS_MODE(x)                     (g_stPortCableStatus.b1D2MHLCableDetect = (x))

#define GET_D3_TMDS_MODE()                      (g_stPortCableStatus.b1D3MHLCableDetect)
#define SET_D3_TMDS_MODE(x)                     (g_stPortCableStatus.b1D3MHLCableDetect = (x))

#define GET_D4_TMDS_MODE()                      (g_stPortCableStatus.b1D4MHLCableDetect)
#define SET_D4_TMDS_MODE(x)                     (g_stPortCableStatus.b1D4MHLCableDetect = (x))

#define GET_D5_TMDS_MODE()                      (g_stPortCableStatus.b1D5MHLCableDetect)
#define SET_D5_TMDS_MODE(x)                     (g_stPortCableStatus.b1D5MHLCableDetect = (x))

#define GET_D6_SWITCH_SELECT()                  (g_ucD6SwitchSelect)
#define SET_D6_SWITCH_SELECT(x)                 (g_ucD6SwitchSelect = (x))

#define GET_D6_SWITCH_POWER_STATUS()            (g_bD6SwitchPowerStatus)
#define SET_D6_SWITCH_POWER_STATUS(x)           (g_bD6SwitchPowerStatus = (x))

#define GET_DP_AUTO_SEARCH_SWITCH()             (g_bDpAutoSearchSwitch)
#define SET_DP_AUTO_SEARCH_SWITCH()             (g_bDpAutoSearchSwitch = _TRUE)
#define CLR_DP_AUTO_SEARCH_SWITCH()             (g_bDpAutoSearchSwitch = _FALSE)

#define GET_D7_SWITCH_SELECT()                  (g_ucD7SwitchSelect)
#define SET_D7_SWITCH_SELECT(x)                 (g_ucD7SwitchSelect = (x))


//****************************************************************************
// General Enumerations
//****************************************************************************

//--------------------------------------------------
// Enumerations of DDCRAM Addr Select
//--------------------------------------------------
typedef enum
{
    _DDCRAM_TOP_ADDR,
    _DDCRAM_BOTTOM_ADDR,
} EnumDDCAddrType;

//--------------------------------------------------
// Enumerations of DDC0/1 Select
//--------------------------------------------------
typedef enum
{
    _D0_DDCRAM,
    _D1_DDCRAM,
} EnumD0D1DDCRAMSelect;

//--------------------------------------------------
// Enumerations of DDCCI or Debug Mode
//--------------------------------------------------
typedef enum
{
    _DEBUG_MODE,
    _DDCCI_MODE,
} EnumDDCCIDebugMode;

//--------------------------------------------------
// Enumerations IRQ Type
//--------------------------------------------------
typedef enum
{
    _IRQ_IVS = 0x00,
    _IRQ_DVS,
    _IRQ_DEN,
    _IRQ_IHS_TIMEOUT,
} EnumIRQ;

//--------------------------------------------------
// Enumerations of LED indication
//--------------------------------------------------
typedef enum
{
    _LED_POWER_ON = 0x00,
    _LED_POWER_SEARCH,
    _LED_POWER_ACTIVE,
    _LED_POWER_SAVING,
    _LED_POWER_NOSUPPORT,
    _LED_POWER_NOSUPPORT_SAVING,
    _LED_POWER_OFF,
    _LED_TYPE_1,
    _LED_TYPE_2,
    _LED_TYPE_3,
    _LED_TYPE_4,
    _LED_TYPE_5,
    _LED_TYPE_FLASH,
    _LED_SYSTEM_END,
} EnumLedIndication;

//--------------------------------------------------
// Enumerations of System Clock
//--------------------------------------------------
typedef enum
{
    _EXT_XTAL_CLK,
    _IOSC_CLK,
    _M2PLL_CLK,
    _ECBUS_CLK
} EnumClkSel;

//--------------------------------------------------
// Enumerations of System Data Info
//--------------------------------------------------
typedef enum
{
    _MONITOR_POWER_STATUS,
    _DP_HOT_PLUG_DC_OFF_HIGH,
    _HDMI_HOT_PLUG_SUPPORT_TIME,
    _HDMI_HOT_PLUG_SUPPORT,
    _AUTO_SEARCH_TARGET,
    _SOURCE_SCAN_TYPE,
    _SEARCH_PORT_0,
    _SEARCH_PORT_1,
    _SEARCH_PORT_2,
    _SEARCH_PORT_3,
    _DISPLAY_MODE,
    _MODE_SLOT_INDEX,
    _SSC,
    _DP_EDID_SELECT,
    _DUAL_DP_EDID_SELECT,
    _DP_D0_LANES,
    _DP_D1_LANES,
    _DP_D2_LANES,
    _DP_D6_LANES,
    _DIGITAL_COLOR_INFO_CHANGE_RESET,
    _EDID_D0_SELECT,
    _EDID_D1_SELECT,
    _EDID_D2_SELECT,
    _EDID_D3_SELECT,
    _EDID_D4_SELECT,
    _EDID_D5_SELECT,
    _EDID_D6_SELECT,
} EnumSystemDataItemDataType;

//--------------------------------------------------
// Enumerations of Waiting Events (CR_03)
//--------------------------------------------------
typedef enum
{
    _EVENT_IVS = _BIT0,
    _EVENT_IEN_START = _BIT1,
    _EVENT_IEN_STOP = _BIT2,
    _EVENT_DVS = _BIT3,
    _EVENT_DEN_START = _BIT4,
    _EVENT_DEN_STOP = _BIT5,
    _EVENT_UNDERFLOW = _BIT6,
    _EVENT_OVERFLOW = _BIT7,
    _EVENT_ALL = 0xFF,
} EnumWaitEventType;

//--------------------------------------------------
// Enumerations of DB trigger event
//--------------------------------------------------
typedef enum
{
    _DB_TRIGGER_EVENT_IVS,
    _DB_TRIGGER_EVENT_IEN_STOP,
} EnumDBIDomainTriggerEvent;


//****************************************************************************
// Enumerations of Auto Color
//****************************************************************************
//--------------------------------------------------
// Enumerations of ADC Gain/Offset
//--------------------------------------------------
typedef enum
{
    _ADC_GAIN = 0x00,
    _ADC_OFFSET,
} EnumADCGainOffset;

//--------------------------------------------------
// Enumerations of S/H Gain Operation Mode
//--------------------------------------------------
typedef enum
{
    _SHA_GAIN_CHECK_MODE = 0x00,
    _SHA_GAIN_WRITE_MODE,
} EnumShaGainOptions;

//--------------------------------------------------
// Enumerations of auto-color types
//--------------------------------------------------
typedef enum
{
    _AUTO_TUNE_RGB,
    _AUTO_TUNE_RGB_KNOWNWHITE,
    _AUTO_TUNE_YPBPR,
    _AUTO_CALIBRATE_RGB,
    _AUTO_TUNE_RGB_GAIN_ONLY,
    _AUTO_TUNE_YPBPR_GAIN_ONLY,
} EnumAutoColorType;


//****************************************************************************
// Enumerations of Auto Phase
//****************************************************************************
//--------------------------------------------------
// Enumerations of Hardware Phase Search SOD Method
//--------------------------------------------------
typedef enum
{
    _PHASE_SEARCH_SOD = 0x00,
    _PHASE_SEARCH_WSOD = 0x01,
} EnumAutoPhaseSearchSODMethod;

//--------------------------------------------------
// Enumerations of Hardware Phase Search Step
//--------------------------------------------------
typedef enum
{
    _PHASE_SEARCH_STEP_1 = 0x00,
    _PHASE_SEARCH_STEP_2 = 0x01,
    _PHASE_SEARCH_STEP_4 = 0x02,
    _PHASE_SEARCH_STEP_8 = 0x03,
    _PHASE_SEARCH_STEP_16 = 0x04,
} EnumAutoPhaseSearchStep;

//--------------------------------------------------
// Enumerations of image auto-function measure result status
//--------------------------------------------------
typedef enum
{
    _AUTO_FAIL = _FAIL,
    _AUTO_SUCCESS = _SUCCESS,
    _AUTO_ABORT,
} EnumAutoResult;


//****************************************************************************
// Enumerations of Digital Functions
//****************************************************************************
//--------------------------------------------------
// Enumerations of Digital Functions On/Off/Clock Gated
//--------------------------------------------------
typedef enum
{
    _FUNCTION_OFF,
    _FUNCTION_ON,
    _FUNCTION_CLOCK_GATED,
} EnumFunctionOnOFF;

//--------------------------------------------------
// Enumerations of Digital Functions Double Buffer
//--------------------------------------------------
typedef enum
{
    _DB_APPLY_NONE,
    _DB_APPLY_NO_POLLING,
    _DB_APPLY_POLLING,
} EnumDBApply;

//--------------------------------------------------
// Enumerations of Brightness/Contrast Coefficient Sets
//--------------------------------------------------
typedef enum
{
    _BRIGHTNESS_COEF_A,
    _BRIGHTNESS_COEF_B,
    _CONTRAST_COEF_A,
    _CONTRAST_COEF_B,
    _CONTRAST_COEF_A_2,
    _CONTRAST_COEF_B_2,
} EnumBriConCoefType;

//--------------------------------------------------
// Enumerations of Color Space
//--------------------------------------------------
typedef enum
{
    _COLOR_SPACE_RGB,
    _COLOR_SPACE_YCBCR422,
    _COLOR_SPACE_YCBCR444,
    _COLOR_SPACE_YCBCR420,
    _COLOR_SPACE_YPBPR,
    _COLOR_SPACE_Y_ONLY,
    _COLOR_SPACE_RAW,
} EnumColorSpace;

//****************************************************************************
// Enumerations of Colorimetry
//****************************************************************************
typedef enum
{
    _COLORIMETRY_RGB_SRGB,
    _COLORIMETRY_RGB_ADOBERGB,
    _COLORIMETRY_RGB_XRRGB,
    _COLORIMETRY_RGB_SCRGB,
    _COLORIMETRY_RGB_DCI_P3,
    _COLORIMETRY_RGB_COLOR_PROFILE,
    _COLORIMETRY_YCC_SMPTE_170M,
    _COLORIMETRY_YCC_ITUR_BT601,
    _COLORIMETRY_YCC_ITUR_BT709,
    _COLORIMETRY_YCC_XVYCC601,
    _COLORIMETRY_YCC_XVYCC709,
    _COLORIMETRY_Y_ONLY,
    _COLORIMETRY_RAW,
    _COLORIMETRY_EXT,
    _COLORMETRY_RESERVED,
}EnumColorimetry;

typedef enum
{
    _COLORIMETRY_EXT_RGB_SRGB,
    _COLORIMETRY_EXT_RGB_XRRGB,
    _COLORIMETRY_EXT_RGB_SCRGB,
    _COLORIMETRY_EXT_RGB_ADOBERGB,
    _COLORIMETRY_EXT_RGB_DCI_P3,
    _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE,
    _COLORIMETRY_EXT_RGB_ITUR_BT2020,
    _COLORIMETRY_EXT_YCC_ITUR_BT601,
    _COLORIMETRY_EXT_YCC_ITUR_BT709,
    _COLORIMETRY_EXT_YCC_XVYCC601,
    _COLORIMETRY_EXT_YCC_XVYCC709,
    _COLORIMETRY_EXT_YCC_SYCC601,
    _COLORIMETRY_EXT_YCC_ADOBEYCC601,
    _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL,
    _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL,
    _COLORIMETRY_EXT_Y_ONLY_DICOM_PART14,
    _COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE,
    _COLORIMETRY_EXT_RESERVED,
}EnumColorimetryExt;

//--------------------------------------------------
// Enumerations of YUV2RGB Types
//--------------------------------------------------
typedef enum
{
    _COLOR_CONV_YUV2RGB_ITU601,
    _COLOR_CONV_YUV2RGB_ITU709,
    _COLOR_CONV_YUV2RGB_ITU709_RGBLIMIT,
    _COLOR_CONV_YUV2RGB_ITU601_YUVFULL,
    _COLOR_CONV_YUV2RGB_ITU709_YUVFULL,
    _COLOR_CONV_YUV2RGB_ITU601_8BIT,
    _COLOR_CONV_YUV2RGB_ITU709_8BIT,
    _COLOR_CONV_YUV2RGB_ITU709_RGBLIMIT_8BIT,
    _COLOR_CONV_YUV2RGB_ITU_BT2020_1,
    _COLOR_CONV_YUV2RGB_ITU_BT2020_2,
} EnumColorConvYuv2RgbType;

//--------------------------------------------------
// Enumerations of DCC Table Index
//--------------------------------------------------
typedef enum
{
    _DCC_CONTROL,
    _DCC_TABLE,
    _DCC_END,
} EnumDCCTableIndex;

//--------------------------------------------------
// Enumerations of DCR Measure Select
//--------------------------------------------------
typedef enum
{
    _MEASURE_AVERAGE,      // R+G+B
    _MEASURE_R,            // R
    _MEASURE_G,            // G
    _MEASURE_B,            // B
    _MEASURE_Y,            // 2R+5G+B
} EnumDCRMeasureSel;

//--------------------------------------------------
// Enumerations of DCR Adjust Option
//--------------------------------------------------
typedef enum
{
    _DCR_ABOVE_TH1_NUM,
    _DCR_ABOVE_TH1_VAL,
    _DCR_ABOVE_TH2_NUM,
    _DCR_ABOVE_TH2_VAL,
    _DCR_HIGH_LV_NUM_R,
    _DCR_LOW_LV_NUM_R,
    _DCR_HIGH_LV_VAL_R,
    _DCR_LOW_LV_VAL_R,
    _DCR_HIGH_LV_NUM_G,
    _DCR_LOW_LV_NUM_G,
    _DCR_HIGH_LV_VAL_G,
    _DCR_LOW_LV_VAL_G,
    _DCR_HIGH_LV_NUM_B,
    _DCR_LOW_LV_NUM_B,
    _DCR_HIGH_LV_VAL_B,
    _DCR_LOW_LV_VAL_B,
    _DCR_Y_MAX_VAL,
    _DCR_Y_MIN_VAL,
    _DCR_ABOVE_TH1_VAL_HIGH,
    _DCR_ABOVE_TH2_VAL_HIGH,
} EnumDCRAdjOption;

//--------------------------------------------------
// Enumerations for DCR Get Average
//--------------------------------------------------
typedef enum
{
    _DCR_ABOVE_TH1_VAL_TOTAL,
    _DCR_ABOVE_TH2_VAL_TOTAL,
} EnumDCRAverageOption;

//--------------------------------------------------
// Enumerations of ICM Table Index
//--------------------------------------------------
typedef enum
{
    _ICM_CONTROL,
    _ICM_0,
    _ICM_1,
    _ICM_2,
    _ICM_3,
    _ICM_4,
    _ICM_5,
    _ICM_END = 0xff,
} EnumICMTableIndex;

typedef enum
{
    _SCM_CONTROL,
    _SCM_0,
    _SCM_1,
    _SCM_2,
    _SCM_3,
    _SCM_4,
    _SCM_5,
    _SCM_6,
    _SCM_7,
    _SCM_END = 0xff,
} EnumSCMTableIndex;

//--------------------------------------------------
// Enumerations of Gamma Channel
//--------------------------------------------------
typedef enum
{
    _GAMMA_RED_CHANNEL,
    _GAMMA_GREEN_CHANNEL,
    _GAMMA_BLUE_CHANNEL,
} EnumGammaChannel;

//--------------------------------------------------
// Enumerations of Highlight Window Type
//--------------------------------------------------
typedef enum
{
    _HLW_FULL_WINDOW,
    _HLW_INSIDE_WINDOW,
    _HLW_OUTSIDE_WINDOW,
    _HLW_ALL_BYPASS,
} EnumHLWType;

//--------------------------------------------------
// Enumerations of Highlight Window IP Selection
//--------------------------------------------------
typedef enum
{
    _IP_SRGB,
    _IP_DCR,
    _IP_SHP_MAIN,
    _IP_SHP_SUB,
    _IP_CONTRAST,
    _IP_GAMMA,
    _IP_3DGAMMA,
    _IP_DCC,
    _IP_UNIFORMITY,
    _IP_IAPSGAIN,
    _IP_ICM,
    _IP_LIVESHOWTM,
} EnumHLWIPSel;

//--------------------------------------------------
// Enumerations of Display calibration
//--------------------------------------------------
typedef enum
{
    _OGC_CAL,
    _OCC_CAL,
    _DICOM_CAL,
    _UNIFORMITY_CAL,
}EnumCaliType;

//--------------------------------------------------
// Enumerations of Highlight Window Set Selection
//--------------------------------------------------
typedef enum
{
    _HLW_ALLSETA,
    _HLW_INSIDEA_OUTSIDEB,
    _HLW_INSIDEB_OUTSIDEA,
    _HLW_ALLSETB,
} EnumHLWSetSel;

//--------------------------------------------------
// Enumerations of Highlight Window Active Select
//--------------------------------------------------
typedef enum
{
    _BRI_CON_A_ON_FULL_WINDOW,
    _BRI_CON_B_ON_INSIDE_WINDOW,
    _BRI_CON_A_ON_HLW_OUTSIDE_WINDOW,
    _BRI_CON_B_ON_INSIDE_A_ON_HLW_OUTSIDE_WINDOW,
} EnumBriConHLWType;

//--------------------------------------------------
// Enumerations of OCC Options
//--------------------------------------------------
typedef enum
{
    _PCM_SRGB,
    _PCM_ADOBE_RGB,
    _PCM_USER_DEFINE,
    _PCM_EBU_MODE,
    _PCM_SOFT_PROFT,
    _PCM_REC_709,
    _PCM_DCI_P3,
    _PCM_SMPTE_C,
    _PCM_HDR_2084,
    _TOTAL_COLORSPACE_NUM,
    _PCM_USER_MODE = _TOTAL_COLORSPACE_NUM,
} EnumPCMType;

//--------------------------------------------------
// Enumerations of IDither Conversion Type
//--------------------------------------------------
typedef enum
{
    _IDITHER_12_TO_8,
    _IDITHER_12_TO_10,
}EnumIDitherConvType;

//--------------------------------------------------
// Enumerations of Quantization Range (RGB)
//--------------------------------------------------
typedef enum
{
    _RGB_QUANTIZATION_FULL_RANGE = 0x00,
    _RGB_QUANTIZATION_LIMIT_RANGE = 0x01,
    _RGB_QUANTIZATION_DEFAULT_RANGE = 0x02,
    _RGB_QUANTIZATION_RESERVED = 0x03,
} EnumColorRGBQuantization;

typedef enum
{
    _AVI_RGB_QUANTIZATION_DEFAULT = 0x00,
    _AVI_RGB_QUANTIZATION_LIMITED = 0x01,
    _AVI_RGB_QUANTIZATION_FULL = 0x02,
    _AVI_RGB_QUANTIZATION_RESERVED = 0x03,
} EnumAviInfoRGBQuantization;

//--------------------------------------------------
// Enumerations of Quantization Range (YCC)
//--------------------------------------------------
typedef enum
{
    _YCC_QUANTIZATION_LIMIT_RANGE = 0x00,
    _YCC_QUANTIZATION_FULL_RANGE = 0x01,
} EnumColorYCCQuantization;

typedef enum
{
    _AVI_YCC_QUANTIZATION_LIMITED = 0x00,
    _AVI_YCC_QUANTIZATION_FULL = 0x01,
} EnumAviInfoYCCQuantization;

//--------------------------------------------------
// Enumerations of AVI Pixel Repetition
//--------------------------------------------------
typedef enum
{
    _AVI_PIXEL_REPETITION_0 = 0x00,
    _AVI_PIXEL_REPETITION_1 = 0x01,
    _AVI_PIXEL_REPETITION_2 = 0x02,
    _AVI_PIXEL_REPETITION_3 = 0x03,
    _AVI_PIXEL_REPETITION_4 = 0x04,
    _AVI_PIXEL_REPETITION_5 = 0x05,
}EnumAviInfoPixelRepetition;

//--------------------------------------------------
// Definitions of AVI Info Content Types
//--------------------------------------------------
typedef enum
{
    _AVI_COLOR_SPACE_RGB = 0x00,
    _AVI_COLOR_SPACE_YCC_422 = 0x01,
    _AVI_COLOR_SPACE_YCC_444 = 0x02,
    _AVI_COLOR_SPACE_YCC_420 = 0x03,
    _AVI_COLOR_SPACE_RESERVED = 0x04,
} EnumAviInfoColorSpace;

typedef enum
{
    _AVI_COLORIMETRY_NONE = 0x00,
    _AVI_COLORIMETRY_ITU601 = 0x01,
    _AVI_COLORIMETRY_ITU709 = 0x02,
    _AVI_COLORIMETRY_EXTENDED = 0x03,
} EnumAviInfoColorimetry;

typedef enum
{
    _AVI_COLORIMETRY_EXT_XVYCC601 = 0x00,
    _AVI_COLORIMETRY_EXT_XVYCC709 = 0x01,
    _AVI_COLORIMETRY_EXT_SYCC601 = 0x02,
    _AVI_COLORIMETRY_EXT_ADOBEYCC601 = 0x03,
    _AVI_COLORIMETRY_EXT_ADOBERGB = 0x04,
    _AVI_COLORIMETRY_EXT_ITUR_BT2020_1 = 0x05,
    _AVI_COLORIMETRY_EXT_ITUR_BT2020_2 = 0x06,
    _AVI_COLORIMETRY_EXT_RESERVED = 0x07,
} EnumAviInfoColorimetryExt;

typedef enum
{
    _AVI_SCAN_INFO_NONE = 0x00,
    _AVI_SCAN_INFO_OVERSCAN = 0x01,
    _AVI_SCAN_INFO_UNDERCAN = 0x02,
    _AVI_SCAN_INFO_RESERVED = 0x03,
} EnumAviInfoScanInfo;

typedef enum
{
    _AVI_IT_CONTENT_NONE = 0x00,
    _AVI_IT_CONTENT_TRUE = 0x01,
} EnumAviInfoITContent;

//--------------------------------------------------
// Enumerations of SRGB Options
//--------------------------------------------------
typedef enum
{
    _SRGB_NORMAL_MODE,
    _SRGB_LUT_MODE,
}EnumsRGBLut;

typedef enum
{
    _SRGB_1_BIT_SHIFT_LEFT,
    _SRGB_2_BIT_SHIFT_LEFT,
    _SRGB_3_BIT_SHIFT_LEFT,
    _SRGB_0_BIT_SHIFT_LEFT,
}EnumSrgbPrecision;

typedef enum
{
    _OGC_MODE = 0,
    _PCM_MODE,
} EnumPCMModeSelect;

//--------------------------------------------------
// Enumerations of Panel Uniformity
//--------------------------------------------------
typedef enum
{
    _UNIFORMITY_TYPE1 = 0,  // gamma 1.8
    _UNIFORMITY_TYPE2,      // gamma 2.0
    _UNIFORMITY_TYPE3,      // gamma 2.2
    _UNIFORMITY_TYPE4,      // gamma 2.4
    _UNIFORMITY_TYPE5,      // srgb
    _UNIFORMITY_TYPE6,      // adobe rgb
} EnumUniformityTypeSelect;

typedef enum
{
    _UNIFORMITY_OGC_MODE = 0,
    _UNIFORMITY_PCM_MODE,
} EnumUniformityModeSelect;

//****************************************************************************
// Enumerations of DP
//****************************************************************************
//--------------------------------------------------
// Enumerations of DP Link Training Type
//--------------------------------------------------
typedef enum
{
    _DP_NORMAL_LT = 0x00,
    _DP_FAKE_LT,
} EnumDpLinkTrainingType;

//--------------------------------------------------
// Enumerations of DP Fifo Check Condition
//--------------------------------------------------
typedef enum
{
    _DP_FIFO_DELAY_CHECK = 0x00,
    _DP_FIFO_POLLING_CHECK,
} EnumDpFifoCheckCondition;

//--------------------------------------------------
// Enumerations of DP HS Tracking Type
//--------------------------------------------------
typedef enum
{
    _DP_HS_TRACKING_HW_MODE = 0x00,
    _DP_HS_TRACKING_FW_MODE,
} EnumDpHSTrackingType;

//--------------------------------------------------
// Enumerations of DP Sink Reveive Port
//--------------------------------------------------
typedef enum
{
    _DP_SINK_REVEICE_PORT0 = 0x00,
    _DP_SINK_REVEICE_PORT1,
} EnumDpSinkReceivePort;

//--------------------------------------------------
// Enumerations of DP Sink Status
//--------------------------------------------------
typedef enum
{
    _DP_SINK_OUT_OF_SYNC = 0x00,
    _DP_SINK_IN_SYNC,
} EnumDpSinkStatus;

//--------------------------------------------------
// Enumerations of DP Hot Plug Assert Type
//--------------------------------------------------
typedef enum
{
    _DP_HPD_ASSERTED = 0x00,
    _DP_LONG_HPD_EVENT,
    _DP_HDCP_LONG_HPD_EVENT,
    _DP_MST_LONG_HPD_EVENT,
    _DP_HPD_LOW_RESET_AUX,
    _DP_HPD_LOW,
    _DP_HPD_NONE = 0xFF,
} EnumDpHotPlugAssertType;

//--------------------------------------------------
// Enumerations of DP Version Type
//--------------------------------------------------
typedef enum
{
    _DP_VERSION_1_0 = 0x10,
    _DP_VERSION_1_1 = 0x11,
    _DP_VERSION_1_2 = 0x12,
    _DP_VERSION_1_3 = 0x13,
    _DP_VERSION_1_4 = 0x14,
} EnumDpVersionType;

//--------------------------------------------------
// Definitions of DP Lane
//--------------------------------------------------
typedef enum
{
    _DP_LANE_0,
    _DP_LANE_1,
    _DP_LANE_2,
    _DP_LANE_3,
} EnumDpLane;

//--------------------------------------------------
// Definitions of DP Link Rate
//--------------------------------------------------
typedef enum
{
    _DP_LINK_RBR = 0x06,
    _DP_LINK_HBR = 0x0A,
    _DP_LINK_HBR2 = 0x14,
} EnumDpLinkRate;

//--------------------------------------------------
// Definitions of DP Lane Count
//--------------------------------------------------
typedef enum
{
    _DP_LINK_1_LANE = 0x01,
    _DP_LINK_2_LANE = 0x02,
    _DP_LINK_4_LANE = 0x04,
} EnumDpLaneCount;

//--------------------------------------------------
// Definitions of DP Voltage Swing Level
//--------------------------------------------------
typedef enum
{
    _DP_LINK_VOLTAGE_SWING_LEVEL_0,
    _DP_LINK_VOLTAGE_SWING_LEVEL_1,
    _DP_LINK_VOLTAGE_SWING_LEVEL_2,
    _DP_LINK_VOLTAGE_SWING_LEVEL_3,
} EnumDpVoltageSwingLevel;

//--------------------------------------------------
// Definitions of DP Pre-emphasis Level
//--------------------------------------------------
typedef enum
{
    _DP_LINK_PREEMPHASIS_LEVEL_0,
    _DP_LINK_PREEMPHASIS_LEVEL_1,
    _DP_LINK_PREEMPHASIS_LEVEL_2,
    _DP_LINK_PREEMPHASIS_LEVEL_3,
} EnumDpPreEmphasisLevel;

//--------------------------------------------------
// Definitions of DP Lane Count
//--------------------------------------------------
typedef enum
{
    _DP_POWER_NORMAL = 0x00,
    _DP_POWER_DOWN,
    _DP_POWER_DOWN_WITH_AUX,
} EnumDpPowerState;

//--------------------------------------------------
// Enumerations of DP FREESYNC Capable Switch
//--------------------------------------------------
typedef enum
{
    _DP_FREESYNC_CAPABILITY_INITIAL = 0x00,
    _DP_FREESYNC_CAPABILITY_SWITCH,
} EnumDpFREESYNCCapabilitySwitch;

//--------------------------------------------------
// Enumerations of MST Rx Port
//--------------------------------------------------
typedef enum
{
    _DP_MST_NO_PORT,
    _DP_MST_RX0_PORT,
    _DP_MST_RX1_PORT,
    _DP_MST_RX6_PORT,
} EnumDPMSTPort;

//--------------------------------------------------
// Enumerations of MST Info Backup
//--------------------------------------------------
typedef enum
{
    _DP_MST_BACKUP_INFO,
    _DP_MST_BACKUP_INFO_RESET,
    _DP_MST_BACKUP_INFO_RESTORE,
} EnumDpMstBackup;

//--------------------------------------------------
// Enumerations of Display DP Tx
//--------------------------------------------------
typedef enum
{
    _DISPLAY_DP_TX_LEVEL_0 = 0x00,
    _DISPLAY_DP_TX_LEVEL_1,
    _DISPLAY_DP_TX_LEVEL_2,
    _DISPLAY_DP_TX_LEVEL_3,
} EnumDisplayDPTxSignalLevel;

//****************************************************************************
// Enumerations of Measure
//****************************************************************************

//--------------------------------------------------
// Enumerations of AutoFunction Measure Field Select
//--------------------------------------------------
typedef enum
{
    _EVEN_FIELD_MEASURE = 0x00,
    _ODD_FIELD_MEASURE = 0x01,
    _NORMAL_MEASURE = 0x02,
} EnumMeasureFieldSelect;

//--------------------------------------------------
// Enumerations of AutoFunction Measure Boundary Type
//--------------------------------------------------
typedef enum
{
    _FULL_BOUNDARY = 0x00,
    _OVERSCAN_BOUNDARY = 0x01,
} EnumMeasureBoundType;

//****************************************************************************
// Enumerations of Memory
//****************************************************************************
//--------------------------------------------------
// Enumerations of FRC on/off
//--------------------------------------------------
typedef enum
{
    _FRC_DISPLAY_ONOFF = _BIT0,
    _FRC_CAPTURE_ONOFF = _BIT2,
    _FRC_ALL_ONOFF = (_FRC_DISPLAY_ONOFF | _FRC_CAPTURE_ONOFF),
} EnumFRCOnOff;

//--------------------------------------------------
// Enumerations of Memory Work
//--------------------------------------------------
typedef enum
{
    _LINE_BUFFER_MODE = 0x00,
    _MEMORY_WORK_MODE,
} EnumMemoryWorkMode;

//--------------------------------------------------
// Enumerations of FIFO Frequency
//--------------------------------------------------
typedef enum
{
    _SCALER_FIFO_FREQ_M2PLL,
    _SCALER_FIFO_FREQ_MPLL,
} EnumScalerFIFOFreq;

//****************************************************************************
// Enumerations of MHL
//****************************************************************************
//--------------------------------------------------
// Definitions of MSC Native Commands
//--------------------------------------------------
typedef enum
{
    _MSC_SET_INT = 0x60,
    _MSC_WRITE_STAT = 0x60,
    _MSC_READ_DEVCAP = 0x61,
    _MSC_SET_HPD = 0x64,
    _MSC_CLR_HPD,
    _MSC_WRITE_BURST = 0x6C,
    _MSC_WRITE_XSTAT = 0x70,
    _MSC_READ_XDEVCAP = 0x71,
    _MSC_ABORT = 0x35,
    _MSC_MSG = 0x68,
} EnumMHLMscCommand;

//--------------------------------------------------
// Definitions of MSC Offset
//--------------------------------------------------
typedef enum
{
    _MSC_NULL_ADDRESS = 0x00,

    // Capability Register Required Fields
    _MSC_DEV_STATE_00 = 0x00,
    _MSC_MHL_VERSION_01,
    _MSC_DEV_CAT_02,
    _MSC_ADOPTER_ID_H_03,
    _MSC_ADOPTER_ID_L_04,
    _MSC_VID_LINK_MODE_05,
    _MSC_AUD_LINK_MODE_06,
    _MSC_VIDEO_TYPE_07,
    _MSC_LOG_DEV_MAP_08,
    _MSC_BANDWIDTH_09,
    _MSC_FEATURE_FLAG_0A,
    _MSC_DEVICE_ID_H_0B,
    _MSC_DEVICE_ID_L_0C,
    _MSC_SCRATCHPAD_SIZE_0D,
    _MSC_INT_STAT_SIZE_0E,

    // _MSC_SET_INT
    _MSC_RCHANGE_INT = 0x20,
    _MSC_DCHANGE_INT,

    // _MSC_WRITE_STAT
    _MSC_CONNECTED_RDY = 0x30,
    _MSC_LINK_MODE,
    _MSC_MHL_VERSION_STAT,

    // _MSC_MSG
    _MSC_MSGE = 0x02,
    _MSC_RCP = 0x10,
    _MSC_RCPK,
    _MSC_RCPE,
    _MSC_RAP = 0x20,
    _MSC_RAPK,
    _MSC_RBP,
    _MSC_RBPK,
    _MSC_RBPE,
    _MSC_UCP = 0x30,
    _MSC_UCPK,
    _MSC_UCPE,
    _MSC_RUSB = 0x40,
    _MSC_RUSBK,
    _MSC_RHID,
    _MSC_RHIDK,
    _MSC_ATT = 0x50,
    _MSC_ATTK,
    _MSC_BIST_TRIGGER = 0x60,
    _MSC_REQUEST_STAT,
    _MSC_BIST_READY,
    _MSC_BIST_STOP,

    // MHL 3.0 XDAVCAP
    _MSC_40_SCRATCHPAD_OFFSET = 0x40,
    _MSC_80_ECBUS_SPEEDS = 0x80,
    _MSC_81_TMDS_SPEEDS,
    _MSC_82_ECBUS_DEV_ROLES,
    _MSC_83_LOG_DEV_MAPX,
    _MSC_84_ACRFS_DIV_SUPPORT,
    _MSC_85_RESERVE,
    _MSC_86_RESERVE,
    _MSC_87_RESERVE,
    _MSC_88_RESERVE,
    _MSC_89_RESERVE,
    _MSC_8A_RESERVE,
    _MSC_8B_RESERVE,
    _MSC_8C_RESERVE,
    _MSC_8D_RESERVE,
    _MSC_8E_RESERVE,
    _MSC_8F_RESERVE,

    _MSC_90_CURR_ECBUS_MODE = 0x90,
    _MSC_91_AVLINK_MODE_STATUS,
    _MSC_92_AVLINK_MODE_CONTROL,
    _MSC_93_MULTI_SINK_STATUS,
} EnumMHLMscOffset;

//--------------------------------------------------
// Definitions of MSC Data
//--------------------------------------------------
typedef enum
{
    _MSC_NULL_VALUE,

    // _MSC_RCHANGE_INT = 0x20
    _MSC_DCAP_CHG = 0x01,
    _MSC_DSCR_CHG = 0x02,
    _MSC_REQ_WRT = 0x04,
    _MSC_GRT_WRT = 0x08,
    _MSC_3D_REQ = 0x10,
    _MSC_FEAT_REQ = 0x20,
    _MSC_FEAT_COMPLETE = 0x40,

    // _MSC_DCHANGE_INT = 0x21
    _MSC_EDID_CHG = 0x02,

    // _MSC_CONNECTED_RDY = 0x30
    _MSC_DCAP_RDY = 0x01,
    _MSC_XDEVCAP_SUPP = 0x02,
    _MSC_POW_STAT = 0x04,
    _MSC_PLIM_STAT = 0x38,

    // _MSC_LINK_MODE = 0x31
    _MSC_PATH_EN = 0x08,
    _MSC_MUTED = 0x10,

    // _MSC_MHL_VERSION_STAT = 0x32
    _MSC_MHL_VERSION_3_0 = 0x30,

    // _MSC_90_CURR_ECBUS_MODE = 0x90
    _MSC_ECBUS_S_MODE = 0x04,

    // _MSC_91_AVLINK_MODE_STATUS = 0x91
    _MSC_NO_SIGNAL = 0x00,
    _MSC_CRU_LOCKED = 0x01,
    _MSC_TMDS_NORMAL = 0x02,

    // _MSCE_OPCODE
    _MSCE_NO_ERR = 0x01,
    _MSCE_INVALID_SUB_CMD = 0x01,

    // _MSC_RAPK_OPCODE
    _MSC_RAPK_NO_ERROR = 0x00,
    _MSC_RAPK_UNRECOGNIZE_CODE,
    _MSC_RAPK_UNSUPPORT_CODE,
    _MSC_RAPK_RESPONDER_BUSY,

    // _MSC_RCPE_OPCODE
    _MSC_RCPE_NO_ERROR = 0x00,
    _MSC_RCPE_INEFFECTIVE_CODE,
    _MSC_RCPE_RESPONDER_BUSY,

    // _MSC_RHIDK_OPCODE
    _MSC_RHIDK_NO_ERROR = 0x00,
    _MSC_RHIDK_INVALID_CODE,
    _MSC_RHIDK_DENY,

} EnumMHLMscData;

//--------------------------------------------------
// Definitions of MHL RAP OpCode
//--------------------------------------------------
typedef enum
{
    _MSC_RAP_POLL = 0x00,
    _MSC_RAP_CONTENT_ON = 0x10,
    _MSC_RAP_CONTENT_OFF = 0x11,
    _MSC_RAP_CBUS_MODE_DOWN = 0x20,
    _MSC_RAP_CBUS_MODE_UP = 0x21,
} EnumMHLMscRAPSubComm;

//--------------------------------------------------
// Definitions of MHL RAP OpCode
//--------------------------------------------------
typedef enum
{
    _MSC_RHID_REQUEST_HOST = 0x00,
    _MSC_RHID_RELINQUISH_HOST,
} EnumMHLMscRHIDSubComm;

//--------------------------------------------------
// Definitions of MHL Write Burst Options
//--------------------------------------------------
typedef enum
{
    _MHL_WRITE_BURST_WITH_REQ,
    _MHL_WRITE_BURST_WITHOUT_REQ,
}EnumMHLWriteBurstMode;

//****************************************************************************
// Enumerations of Mode
//****************************************************************************
//--------------------------------------------------
// Enumerations of Mode State
//--------------------------------------------------
typedef enum
{
    _MODE_STATUS_INITIAL = 0x00,
    _MODE_STATUS_DISPLAY_INITIAL,
    _MODE_STATUS_DISPLAY_SETTING,
    _MODE_STATUS_DISPLAY_CHECK,
    _MODE_STATUS_POWER_SAVING,
    _MODE_STATUS_POWER_OFF,
    _MODE_STATUS_FACTORY,
    _MODE_STATUS_NONE = 0xFF,
} EnumModeStatus;


//****************************************************************************
// Enumerations of Power
//****************************************************************************
//--------------------------------------------------
// Enumerations of Power Status/Action
//--------------------------------------------------
typedef enum
{
    _POWER_STATUS_AC_ON = 0x00,
    _POWER_STATUS_OFF,
    _POWER_STATUS_NORMAL,
    _POWER_STATUS_SAVING,
    _POWER_STATUS_NOSUPPORT_SAVING,
    _POWER_STATUS_FAKE_SAVING,
    _POWER_STATUS_NONE = 0xFF,
} EnumPowerStatus;

//--------------------------------------------------
// Enumerations of Power Action
//--------------------------------------------------
typedef enum
{
    _POWER_ACTION_OFF_TO_NORMAL = 0x00,
    _POWER_ACTION_AC_ON_TO_NORMAL,
    _POWER_ACTION_AC_ON_TO_OFF,
    _POWER_ACTION_AC_ON_INITIAL,
    _POWER_ACTION_PS_TO_NORMAL,
    _POWER_ACTION_PS_TO_OFF,
    _POWER_ACTION_NORMAL_TO_PS,
    _POWER_ACTION_NORMAL_TO_OFF,
    _POWER_ACTION_NORMAL_TO_NOSUPPORT_PS,
    _POWER_ACTION_NORMAL_TO_FAKE_PS,
    _POWER_ACTION_NOSUPPORT_PS_TO_PS,
    _POWER_ACTION_NOSUPPORT_PS_TO_OFF,
    _POWER_ACTION_FAKE_PS_TO_NORMAL,
    _POWER_ACTION_FAKE_PS_TO_OFF,
    _POWER_ACTION_NONE = 0xFF,
} EnumPowerAction;

//--------------------------------------------------
// Enumerations of Mode Action
//--------------------------------------------------
typedef enum
{
    _MODE_ACTION_NO_RESET_MODE = 0x00,
    _MODE_ACTION_RESET_TO_DISPLAY_INITIAL,
    _MODE_ACTION_RESET_TO_DISPLAY_SETTING,
    _MODE_ACTION_RESET_TO_DISPLAY_SETTING_WITHOUT_FORCETOBG,
    _MODE_ACTION_RESET_TO_DISPLAY_CHECK,
    _MODE_ACTION_RESET_TO_POWER_SAVING,
    _MODE_ACTION_RESET_TO_POWER_OFF,
    _MODE_ACTION_RESET_TO_FACTORY_MODE,
    _MODE_ACTION_NONE = 0xFF,
} EnumModeAction;

//--------------------------------------------------
// Enumerations of Display State Action
//--------------------------------------------------
typedef enum
{
    _DISPLAY_ACTION_NO_ACTION = 0x00,

    _DISPLAY_ACTION_RESET_TO_NONE,
    _DISPLAY_ACTION_NO_SIGNAL,
    _DISPLAY_ACTION_OOR,
    _DISPLAY_ACTION_DISPLAY_READY,
    _DISPLAY_ACTION_ACTIVE,
} EnumDisplayAction;


//****************************************************************************
// Enumerations of Scaling
//****************************************************************************
//--------------------------------------------------
// Enumerations of VSU Type
//--------------------------------------------------
typedef enum
{
    _VSU_2D_4LINE_COEF = 0x00,  // 2D 4line SU
    _VSU_2D_3LINE_COEF = 0x01,  // 2D 3line SU
    _VSU_3D_2LINE_COEF = 0x02,  // 3D 2line SU
    _VSU_3D_3LINE_COEF = 0x03,  // 3D 3line SU
    _VSU_3D_4LINE_COEF = 0x04,  // 3D 4line SU
} EnumVSUCoefType;


//****************************************************************************
// Enumerations of Source
//****************************************************************************
//--------------------------------------------------
// Enumerations of Input Source Type
//--------------------------------------------------
typedef enum
{
    _SOURCE_INPUT_TYPE_VGA = 0x00,
    _SOURCE_INPUT_TYPE_HDMI,
    _SOURCE_INPUT_TYPE_DVI,
    _SOURCE_INPUT_TYPE_DP,
} EnumSourceInputType;

//--------------------------------------------------
// Enumerations of Source State
//--------------------------------------------------
typedef enum
{
    _SOURCE_VGA,
    _SOURCE_VIDEO,
    _SOURCE_DVI,
    _SOURCE_HDMI,
    _SOURCE_DP,
    _SOURCE_NONE,
    _SOURCE_AMOUNT = _SOURCE_NONE,
} EnumSourceTypeDef;

//--------------------------------------------------
// Enumerations of Input Port List
//--------------------------------------------------
typedef enum
{
    _A0_INPUT_PORT = 0x00,
    _D0_INPUT_PORT,
    _D1_INPUT_PORT,
    _D2_INPUT_PORT,
    _D3_INPUT_PORT,
    _D4_INPUT_PORT,
    _D5_INPUT_PORT,
    _D6_INPUT_PORT,
    _D7_INPUT_PORT,
    _NO_INPUT_PORT,
}EnumSourceSearchPort;

#define _A0_INPUT_PORT                          0x00
#define _D0_INPUT_PORT                          0x01
#define _D1_INPUT_PORT                          0x02
#define _D2_INPUT_PORT                          0x03
#define _D3_INPUT_PORT                          0x04
#define _D4_INPUT_PORT                          0x05
#define _D5_INPUT_PORT                          0x06
#define _D6_INPUT_PORT                          0x07
#define _D7_INPUT_PORT                          0x08
#define _NO_INPUT_PORT                          0x09

typedef struct
{
    BYTE ucVersion;
    BYTE ucLength;

    BYTE ucEOTF;
    BYTE ucStaticMetadataID;

    WORD usDisplayPrimariesX0;
    WORD usDisplayPrimariesY0;

    WORD usDisplayPrimariesX1;
    WORD usDisplayPrimariesY1;

    WORD usDisplayPrimariesX2;
    WORD usDisplayPrimariesY2;

    WORD usWhitePointX;
    WORD usWhitePointY;

    WORD usMaxDisplayMasteringLv;
    WORD usMinDisplayMasteringLv;
    WORD usMaxCLL;
    WORD usMaxFALL;
} StructHDRStaticMetaData;

//--------------------------------------------------
// Enumerations Load EDID Port Selection
//--------------------------------------------------
typedef enum
{
    _A0_INPUT_PORT_EDID = _A0_INPUT_PORT,
    _D0_INPUT_PORT_EDID = _D0_INPUT_PORT,
    _D1_INPUT_PORT_EDID = _D1_INPUT_PORT,
    _D2_INPUT_PORT_EDID = _D2_INPUT_PORT,
    _D3_INPUT_PORT_EDID = _D3_INPUT_PORT,
    _D4_INPUT_PORT_EDID = _D4_INPUT_PORT,
    _D5_INPUT_PORT_EDID = _D5_INPUT_PORT,
    _D6_INPUT_PORT_EDID = _D6_INPUT_PORT,
    _D7_INPUT_PORT_EDID = _D7_INPUT_PORT,
    _D0_INPUT_PORT_MHL_EDID,
    _D1_INPUT_PORT_MHL_EDID,
    _D2_INPUT_PORT_MHL_EDID,
    _D3_INPUT_PORT_MHL_EDID,
    _D4_INPUT_PORT_MHL_EDID,
    _D5_INPUT_PORT_MHL_EDID,
} EnumInputPortEdid;

//--------------------------------------------------
// Enumerations of Input Port Priority
//--------------------------------------------------
typedef enum
{
    _INPUT_PORT_PRIORITY_0 = 0x00,
    _INPUT_PORT_PRIORITY_1,
    _INPUT_PORT_PRIORITY_2,
    _INPUT_PORT_PRIORITY_3,
    _INPUT_PORT_PRIORITY_4,
    _INPUT_PORT_PRIORITY_5,
    _INPUT_PORT_PRIORITY_6,
    _INPUT_PORT_PRIORITY_7,
    _INPUT_PORT_PRIORITY_8,
    _INPUT_PORT_PRIORITY_NONE,
}EnumSourceSearchPortPriority;

//--------------------------------------------------
// Enumerations of Input Port Search Group List
//--------------------------------------------------
typedef enum
{
    _INPUT_PORT_GROUP_0 = 0x00,
    _INPUT_PORT_GROUP_1,
    _INPUT_PORT_GROUP_2,
    _INPUT_PORT_GROUP_3,
    _INPUT_PORT_GROUP_4,
    _INPUT_PORT_GROUP_5,
    _INPUT_PORT_GROUP_6,
    _INPUT_PORT_GROUP_7,
    _INPUT_PORT_GROUP_8,
    _INPUT_PORT_GROUP_NONE,
}EnumSourceSearchGroup;

//--------------------------------------------------
// Enumerations of Port Type List
//--------------------------------------------------
typedef enum
{
    _PORT_NONE = 0x00,
    _PORT_VGA,
    _PORT_DVI,
    _PORT_HDMI,
    _PORT_DP,
    _PORT_MHL,
    _PORT_HDMI20,
    _PORT_DUAL_DVI,
}EnumInputPortType;

#define _PORT_NONE                              0x00
#define _PORT_VGA                               0x01
#define _PORT_DVI                               0x02
#define _PORT_HDMI                              0x03
#define _PORT_DP                                0x04
#define _PORT_MHL                               0x05
#define _PORT_HDMI20                            0x06
#define _PORT_DUAL_DVI                          0x07

//--------------------------------------------------
// Structure of Input Port Cable Status
//--------------------------------------------------
typedef struct
{
    BYTE b1A0CableDetect : 1;
    BYTE b1D0CableDetect : 1;
    BYTE b1D1CableDetect : 1;
    BYTE b1D2CableDetect : 1;
    BYTE b1D3CableDetect : 1;
    BYTE b1D4CableDetect : 1;
    BYTE b1D5CableDetect : 1;
    BYTE b1D6CableDetect : 1;
    BYTE b1D0MHLCableDetect : 1;
    BYTE b1D1MHLCableDetect : 1;
    BYTE b1D2MHLCableDetect : 1;
    BYTE b1D3MHLCableDetect : 1;
    BYTE b1D4MHLCableDetect : 1;
    BYTE b1D5MHLCableDetect : 1;
} StructPortCableStatus;

//****************************************************************************
// Enumerations of Timer
//****************************************************************************
//--------------------------------------------------
// Enumerations of Timer Operation
//--------------------------------------------------
typedef enum
{
    _TIMER_OPERATION_INITIAL_MODE,
    _TIMER_OPERATION_POWER_NORMAL_MODE,
    _TIMER_OPERATION_POWER_SAVING_MODE,
    _TIMER_OPERATION_POWER_SAVING_FAST_MODE,
    _TIMER_OPERATION_POWER_IDLE_MODE,
    _TIMER_OPERATION_OSD_MODE,
} EnumScalerTimerOperationMode;


//****************************************************************************
// Enumerations of Timing Info
//****************************************************************************
//--------------------------------------------------
// Enumerations of Timing Info
//--------------------------------------------------
typedef enum
{
    _HPOLARITY = 0x00,
    _VPOLARITY,
    _INTERLACE,
    _IHFREQ,
    _IHTOTAL,
    _IHWIDTH,
    _IHSTART,
    _IVFREQ,
    _IVTOTAL,
    _IVHEIGHT,
    _IVSTART,
    _IVSYNC_WIDTH,
    _MISC,
} EnumTimingInfoSelect;

//--------------------------------------------------
// Enumerations of Display Timing Data Info
//--------------------------------------------------
typedef enum
{
    _DISPLAY_TIMING_HTOTAL,
    _DISPLAY_TIMING_VTOTAL,
    _DISPLAY_TIMING_HSTART,
    _DISPLAY_TIMING_VSTART,
    _DISPLAY_TIMING_HWIDTH,
    _DISPLAY_TIMING_VHEIGHT,
} EnumDispTimingDataType;

//****************************************************************************
// Enumerations of Audio
//****************************************************************************
//--------------------------------------------------
// Enumerations of Audio State
//--------------------------------------------------
typedef enum
{
    _AUDIO_STATUS_POWER_OFF,
    _AUDIO_STATUS_PREPARING,
    _AUDIO_STATUS_PLAYBACK,
} EnumAudioState;

//--------------------------------------------------
// Enumerations of Audio DAC State
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OFF,
    _AUDIO_DAC_INITIAL,
    _AUDIO_DAC_CHARGE,
    _AUDIO_DAC_DEPOP,
    _AUDIO_DAC_READY,
} EnumAudioDACState;

//--------------------------------------------------
// Enumerations of Audio DAC Output
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUTPUT_NONE,
    _AUDIO_DAC_OUTPUT_SPEAKER,
    _AUDIO_DAC_OUTPUT_HEADPHONE,
    _AUDIO_DAC_OUTPUT_BOTH,
} EnumAudioDACOutput;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq Type
//--------------------------------------------------
typedef enum
{
    _AUDIO_FREQ_NO_AUDIO = 0x00,
    _AUDIO_FREQ_32K,
    _AUDIO_FREQ_44_1K,
    _AUDIO_FREQ_48K,
    _AUDIO_FREQ_64K,
    _AUDIO_FREQ_88_2K,
    _AUDIO_FREQ_96K,
    _AUDIO_FREQ_128K,
    _AUDIO_FREQ_176_4K,
    _AUDIO_FREQ_192K,
    _AUDIO_FREQ_256K,
    _AUDIO_FREQ_352_8K,
    _AUDIO_FREQ_384K,
    _AUDIO_FREQ_512K,
    _AUDIO_FREQ_705_6K,
    _AUDIO_FREQ_768K,
} EnumAudioSamplingFreqType;

//--------------------------------------------------
// Enumerations of Audio Sampling Freq Packet Number
//--------------------------------------------------
typedef enum
{
    _AUDIO_FREQ_PACKET_NO_AUDIO = 0,
    _AUDIO_FREQ_PACKET_32K = 32,
    _AUDIO_FREQ_PACKET_44_1K = 44,
    _AUDIO_FREQ_PACKET_48K = 48,
    _AUDIO_FREQ_PACKET_64K = 64,
    _AUDIO_FREQ_PACKET_88_2K = 88,
    _AUDIO_FREQ_PACKET_96K = 96,
    _AUDIO_FREQ_PACKET_128K = 128,
    _AUDIO_FREQ_PACKET_176_4K = 176,
    _AUDIO_FREQ_PACKET_192K = 192,
    _AUDIO_FREQ_PACKET_256K = 256,
    _AUDIO_FREQ_PACKET_352_8K = 352,
    _AUDIO_FREQ_PACKET_384K = 384,
    _AUDIO_FREQ_PACKET_512K = 512,
    _AUDIO_FREQ_PACKET_705_6K =705,
    _AUDIO_FREQ_PACKET_768K = 768,
} EnumAudioSamplingFreqPacket;

//--------------------------------------------------
// Enumerations of Audio Sampling Frequency in SPDIF Format
//--------------------------------------------------
typedef enum
{
    _AUDIO_SPDIF_FS_22_05KHZ = _BIT2,
    _AUDIO_SPDIF_FS_24KHZ = (_BIT2 | _BIT1),
    _AUDIO_SPDIF_FS_32KHZ = (_BIT1 | _BIT0),
    _AUDIO_SPDIF_FS_44_1KHZ = 0x00,
    _AUDIO_SPDIF_FS_48KHZ = _BIT1,
    _AUDIO_SPDIF_FS_88_2KHZ = _BIT3,
    _AUDIO_SPDIF_FS_96KHZ = (_BIT3 | _BIT1),
    _AUDIO_SPDIF_FS_176_4KHZ = (_BIT3 | _BIT2),
    _AUDIO_SPDIF_FS_192KHZ = (_BIT3 | _BIT2 | _BIT1),
    _AUDIO_SPDIF_FS_NOT_INDICATED = _BIT0,
} EnumAudioSpdifSamplingFrequencyType;

//--------------------------------------------------
// Enumerations of Audio input Source
//--------------------------------------------------
typedef enum
{
    _LINE_IN_AUDIO,
    _DIGITAL_AUDIO,
    _NO_AUDIO_SOURCE = 0xFF,
} EnumAudioInputSource;

//--------------------------------------------------
// Enumerations of Digital Audio Source
//--------------------------------------------------
typedef enum
{
    _DIGITAL_AUDIO_SOURCE_NONE,
    _DIGITAL_AUDIO_SOURCE_HDMI,
    _DIGITAL_AUDIO_SOURCE_DP,
} EnumAudioDigitalSource;

//--------------------------------------------------
// Enumerations of Audio Input Port
//--------------------------------------------------
typedef enum
{
    _AUDIO_FROM_D0_PORT = 0x00,
    _AUDIO_FROM_D1_PORT,
    _AUDIO_FROM_D2_PORT,
    _AUDIO_FROM_D3_PORT,
    _AUDIO_FROM_D4_PORT,
    _AUDIO_FROM_D5_PORT,
    _AUDIO_FROM_ADC_PORT,
} EnumAudioInputPort;

//--------------------------------------------------
// Enumerations of Audio Output Port
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUT = 0x00,
    _AUDIO_I2S_OUT,
    _AUDIO_SPDIF_OUT,
    _AUDIO_DPTX_OUT,
} EnumAudioOutputType;

//--------------------------------------------------
// Enumerations of Audio DAC Output Gain
//--------------------------------------------------
typedef enum
{
    _AUDIO_DAC_OUTPUT_GAIN_0_DB = 0x00,
    _AUDIO_DAC_OUTPUT_GAIN_1_5_DB = 0x01,
    _AUDIO_DAC_OUTPUT_GAIN_3_DB = 0x02,
    _AUDIO_DAC_OUTPUT_GAIN_4_5_DB = 0x03,
    _AUDIO_DAC_OUTPUT_GAIN_6_DB = 0x04,
    _AUDIO_DAC_OUTPUT_GAIN_7_5_DB = 0x05,
    _AUDIO_DAC_OUTPUT_GAIN_9_DB = 0x06,
    _AUDIO_DAC_OUTPUT_GAIN_10_5_DB = 0x07,
} EnumAudioDacOutputGain;

//--------------------------------------------------
// Enumerations of Audio Channel Count
//--------------------------------------------------
typedef enum
{
    _AUDIO_CHANNEL_COUNT_MONO = 0x00,
    _AUDIO_CHANNEL_COUNT_2,
    _AUDIO_CHANNEL_COUNT_3,
    _AUDIO_CHANNEL_COUNT_4,
    _AUDIO_CHANNEL_COUNT_5,
    _AUDIO_CHANNEL_COUNT_6,
    _AUDIO_CHANNEL_COUNT_7,
    _AUDIO_CHANNEL_COUNT_8,
} EnumAudioChannelCount;

//--------------------------------------------------
// Definitions of Aspect Ratio Type Status
//--------------------------------------------------
typedef enum
{
    _ASPECT_RATIO_FULL,
    _ASPECT_RATIO_FIXED,
    _ASPECT_RATIO_USER,
    _ASPECT_RATIO_ORIGIN,
} EnumAspectRatioType;

//--------------------------------------------------
// Definitions of Rotation Type Status
//--------------------------------------------------
typedef enum
{
    _ROT_DISABLE = 0x00,
    _ROT_CW90,
    _ROT_CW180,
    _ROT_CW270,
    _ROT_HOR_MIRROR,
    _ROT_VER_MIRROR,
} EnumRotationType;

//--------------------------------------------------
// Definitions of Rotation Display Type Status
//--------------------------------------------------
typedef enum
{
    _ROT_FULL = 0x00,
    _ROT_PIXEL_BY_PIXEL,
    _ROT_KEEP_SRC_ASPECT_RATIO,
} EnumRotationDisplayType;

//------------------------------------------------------------
// Definitions of Pin Share Config type that user can adjust
//------------------------------------------------------------
typedef enum
{
    _GPI,
    _GPO_OD,
    _GPO_PP,
    _PWM0_OD,
    _PWM0_PP,
    _PWM1_OD,
    _PWM1_PP,
    _PWM2_OD,
    _PWM2_PP,
    _PWM3_OD,
    _PWM3_PP,
    _PWM4_OD,
    _PWM4_PP,
    _PWM5_OD,
    _PWM5_PP,
} EnumPinConfigType;

//------------------------------------------------------------
// Definitions of Flash Drive Config type that user can Pin
//------------------------------------------------------------
typedef enum
{
    _CONFIG_PIN_SPI_CLK,
    _CONFIG_PIN_SPI_SI_SO_CEB,
} EnumConfigSPIPinType;

//------------------------------------------------------------
// Definitions of Flash Drive Config type that user can Drive
//------------------------------------------------------------
typedef enum
{
    _SPI_DRIVE_3_0MA,
    _SPI_DRIVE_3_5MA,
    _SPI_DRIVE_4_0MA,
    _SPI_DRIVE_4_5MA,
    _SPI_DRIVE_5_0MA,
    _SPI_DRIVE_5_5MA,
} EnumFlashDriveConfigType;

//--------------------------------------------------
// Definitions of Rotation Status
//--------------------------------------------------
typedef struct
{
    EnumRotationType enumRotationType;
    EnumRotationDisplayType enumRotationDispSize;
} StructRotationStatus;

//--------------------------------------------------
// Definitions of AVI Info Frame Contents
//--------------------------------------------------
typedef enum
{
    _AVI_INFO_COLOR_SPACE,
    _AVI_INFO_COLORIMETRY,
    _AVI_INFO_EXTENDED_COLORIMETRY,
    _AVI_INFO_YCC_QUANTIZATION,
    _AVI_INFO_RGB_QUANTIZATION,
    _AVI_INFO_SCAN_INFO,
    _AVI_INFO_IT_CONTENT,
    _AVI_INFO_PIXEL_REPETITION,
    _AVI_INFO_AR,
    _AVI_INFO_VIC,
} EnumAviInfoContent;

typedef enum
{
    _DISPLAY_STATE_NONE,
    _DISPLAY_STATE_NO_SIGNAL,
    _DISPLAY_STATE_OOR,
    _DISPLAY_STATE_DISPLAY_READY,
    _DISPLAY_STATE_ACTIVE,

    _DISPLAY_STATE_MAX = 0x0F,
} EnumDisplayState;

typedef enum
{
    _DISPLAY_EVENT_TIMING_CONFIRMED = _BIT0,
    _DISPLAY_EVENT_TIMING_DOUBLE_CHECK = _BIT1,
    _DISPLAY_EVENT_MEASURE_CHECKING = _BIT3,
    _DISPLAY_EVENT_FIRST_ACTIVE = _BIT4,
    _DISPLAY_EVENT_STATE_CHANGE_USR = _BIT6,
    _DISPLAY_EVENT_STATE_CHANGE_SYS = _BIT7,
    _DISPLAY_EVENT_ALL = 0xFF,
} EnumDisplayEvent;

typedef enum
{
    _BORDER_WIN1,
    _BORDER_WIN2,
} EnumBorderWin;

typedef enum
{
    _REG_MAIN1,
    _REG_MAIN2,
    _REG_SUB1,
    _REG_SUB2,
} EnumRegSel;

typedef enum
{
    _REG_IDOMAIN,
    _REG_DDOMAIN_BEFORE_BLENDING,
    _REG_DDOMAIN_AFTER_BLENDING,
} EnumRegisterDataPosition;

typedef enum
{
    _CHECK_ADC_SAVE,
    _CHECK_ADC_LOAD,
    _CHECK_SYSTEM_DATA_SAVE,
    _CHECK_SYSTEM_DATA_LOAD,
    _CHECK_MODE_USER_DATA_SAVE,
    _CHECK_MODE_USER_DATA_LOAD,
    _CHECK_SYSTEM_ITEM_COUNT,
} EnumNvramCheckType;

//-------------------------------------------------
// Enum DDCCI Port
//-------------------------------------------------
typedef enum
{
    _DDCCI0 = 0,
    _DDCCI1,
    _DDCCI2,
    _DDCCI3,
    _DDCCIMAX,
}EnumDDCCIPort;

//-------------------------------------------------
// Enum Aspect return type
//-------------------------------------------------
typedef enum
{
    _ASPECT_RATIO_H,
    _ASPECT_RATIO_V,
}EnumAspectRatioValueType;


//-------------------------------------------------
// Enum Pip Position Value type
//-------------------------------------------------
typedef enum
{
    _PIP_POSITION_START_H,
    _PIP_POSITION_START_V,
}EnumPipPositionValueType;

//-------------------------------------------------
// Enum Pip Size Value type
//-------------------------------------------------
typedef enum
{
    _PIP_SIZE_H_WIDTH,
    _PIP_SIZE_V_HEIGHT,
}EnumPipSizeValueType;

//--------------------------------------------------
// Struct for RX HDCP Authentication
//--------------------------------------------------
typedef struct
{
    BYTE b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1AuthRepeaterProcTimeout : 1;
    BYTE b1AuthReadIrqTimeout : 1;
    BYTE ucAuthUpstreamEvent;
    BYTE b1AuthCpIrqTimer : 1;
}StructDPRxHDCPAuthInfo;

//--------------------------------------------------
//HDCP RX Authentication State
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP_STATE_IDLE = 0,
    _DP_RX_HDCP_STATE_AUTH_FAKE,
    _DP_RX_HDCP_STATE_AUTH_1,
    _DP_RX_HDCP_STATE_AUTH_2,
    _DP_RX_HDCP_STATE_AUTH_DONE,
} EnumDPRxHDCPAuthState;

//--------------------------------------------------
//HDCP RX Authentication Upstream Event
//--------------------------------------------------
typedef enum
{
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE = 0,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS,
    _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT,
} EnumDPRxHDCPUpstreamAuthStatus;

//--------------------------------------------------
// Structure of MHL State Definitions
//--------------------------------------------------
typedef struct
{
    BYTE b4MHLProcessState : 4;
    BYTE b1MHLTransmitStatus : 1;
    BYTE b1MHLResendStatus : 1;
    BYTE b1MHLSwitchPortDiscoveryDoneStatus : 1;
} StructMHLProcessInfo;

typedef enum
{
    _H_V_SU_128TAPS_NORMAL,
    _H_V_SU_96TAPS_NORMAL,
    _H_SU_128TAPS_1_TO_1,
    _H_SU_96TAPS_1_TO_1,
} EnumSUCoefType;

typedef enum
{
    _SPD_INFO_OUI,
    _SPD_INFO_FREESYNC_SUPPORT,
    _SPD_INFO_FREESYNC_ENABLE,
    _SPD_INFO_FREESYNC_ACTIVE,
    _SPD_INFO_FREESYNC_MIN_VFREQ,
    _SPD_INFO_FREESYNC_MAX_VFREQ,
} EnumAmdSpdInfoContent;

//--------------------------------------------------
// Definitions of HDR Max Mastering Lv Type
//--------------------------------------------------
typedef enum
{
    _HDR_MAX_MASTERING_LV_TYPE0, // 1200 nits
    _HDR_MAX_MASTERING_LV_TYPE1, // 4000 nits
    _HDR_MAX_MASTERING_LV_TYPE2, // 10000 nits
} EnumHDRMaxMasteringLvType;

//--------------------------------------------------
// Definitions of HDR Color Matrix
//--------------------------------------------------
typedef enum
{
    _HDR_COLOR_MATRIX_SRGB,
    _HDR_COLOR_MATRIX_ADOBE,
    _HDR_COLOR_MATRIX_DCIP3_D65,
    _HDR_COLOR_MATRIX_BT2020,
} EnumHDRColorMatrix;

//--------------------------------------------------
// Definitions of OSD Position Offset Type
//--------------------------------------------------
typedef enum
{
    _OSD_POSITION_OFFSET_GLOBAL,
    _OSD_POSITION_OFFSET_WINDOW,
} EnumOsdPositionOffsetType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructPortCableStatus g_stPortCableStatus;
extern BYTE g_ucD6SwitchSelect;
extern bit g_bD6SwitchPowerStatus;
extern bit g_bDpAutoSearchSwitch;
extern BYTE g_ucD7SwitchSelect;

#endif // End of #ifndef __GLOBAL_H__
