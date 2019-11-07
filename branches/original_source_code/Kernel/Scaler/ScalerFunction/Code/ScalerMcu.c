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
// ID Code      : ScalerMcu.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MCU__

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions DDCCI Protocol Items
//--------------------------------------------------
#define _DCCCI_LENGTH                       1

//--------------------------------------------------
// Definitions PWM Frequency
//--------------------------------------------------
#define _PWM_FREQ_LOW_BOUND                 16
#define _PWM_FREQ_DVSRST_BOUND              1000
#define _PWM_FREQ_UPPER_BOUND               55000

//--------------------------------------------------
// Definitions of Hardware IIC Timings
//--------------------------------------------------
#if(_HW_IIC_SPEED == _HW_IIC_LOW_SPEED_100K)
#define _HW_IIC_SLPC_14318K                 0x26 // 38
#define _HW_IIC_SHPC_14318K                 0x22 // 34
#define _HW_IIC_SLPC_28000K                 0x2F // 47
#define _HW_IIC_SHPC_28000K                 0x2F // 47
#define _HW_IIC_STA_SUGPIO_C                0x36 // 54
#define _HW_IIC_TOR                         0x47 // 71
#else
#define _HW_IIC_SLPC_14318K                 0x0C // 12
#define _HW_IIC_SHPC_14318K                 0x04 // 4
#define _HW_IIC_SLPC_28000K                 0x0E // 14
#define _HW_IIC_SHPC_28000K                 0x06 // 6
#define _HW_IIC_STA_SUGPIO_C                0x09 // 9
#define _HW_IIC_TOR                         0x23 // 35
#endif

#define _HW_IIC_FTPC                        0x03 // 3
#define _HW_IIC_FD10_14318K                 0x01 // 1
#define _HW_IIC_FD10_28000K                 0x02 // 2

//--------------------------------------------------
// Definitions of Hardware IIC
//--------------------------------------------------
#define _HW_IIC_BUFFER_SIZE                 24
#define _HW_IIC_DELAY_TIME                  5

//--------------------------------------------------
// Definitions of Software IIC
//--------------------------------------------------
#define _IIC_POLLING_TIME                   50

#if((_INSTANT_TIMER_EVENT_1 == _ON) && (_UART_SUPPORT == _ON))
#error "Instant Timer1 cannot be used when UART is supported"
#endif

//--------------------------------------------------
// Definitions DDCCI Protocol Items
//--------------------------------------------------
#define _DDCCI_BUFFER_SIZE                  32

// If User Don't Want to Save Tx Buf Size, Reduce the Available DDCCI Buf Size
#if(_DDCCI_TXBUF_LENGTH < _DDCCI_BUFFER_SIZE)
#undef _DDCCI_BUFFER_SIZE
#define _DDCCI_BUFFER_SIZE                  _DDCCI_TXBUF_LENGTH
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
BYTE idata g_ucDdcciCountEXINT;

BYTE data g_ucDelay5usN = 1;
BYTE data g_ucDelay5usI = 1;
BYTE data g_ucDelay5usI_EXINT;

BYTE g_ucRunDdcciCommand;

BYTE g_pucDdcciRxBuf[_DDCCI0_RXBUF_LENGTH];
BYTE g_pucDdcciTxBuf[_DDCCI_TXBUF_LENGTH];

BYTE g_pucDdcciGroupRxBuf[_MULTI_DISPLAY_MAX][_DDCCI_RXBUF_LENGTH] =
{
    {0},
#if(_MULTI_DISPLAY_MAX >= 0x02)
    {0},
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
    {0},
    {0},
#endif
};

BYTE g_ucDDCCIHandlerInx;

#if(_SW_IIC_SUPPORT == _ON)
BYTE idata g_ucSwIICStatus;
#endif

#if(_FLASH_PARTITION_RELOCATABLE_SUPPORT == _ON)
BYTE data g_ucBankOffset                               _at_     0x30;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerMcuInitial(void);
void ScalerMcuDdcciInitial(void);
void ScalerMcuDdcciSendData(EnumDDCCIPort enumDdcciChannel, BYTE *pucWriteArray);
BYTE ScalerMcuDdcciGetInputPort(EnumDDCCIPort enumDdcciChannel);
void ScalerMcuDdcciSelectDdcChannel(EnumDDCCIPort enumDdcciChannel, BYTE ucInputPort);

void ScalerMcuDdcci0SendData(BYTE *pucWriteArray);
BYTE ScalerMcuDdcci0GetInputPort(void);
void ScalerMcuDdcci0SelectDdcChannel(BYTE ucInputPort);

#if(_MULTI_DISPLAY_MAX >= 0x02)
void ScalerMcuDdcci1SendData(BYTE *pucWriteArray);
BYTE ScalerMcuDdcci1GetInputPort(void);
void ScalerMcuDdcci1SelectDdcChannel(BYTE ucInputPort);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
void ScalerMcuDdcci2SendData(BYTE *pucWriteArray);
BYTE ScalerMcuDdcci2GetInputPort(void);
void ScalerMcuDdcci2SelectDdcChannel(BYTE ucInputPort);

void ScalerMcuDdcci3SendData(BYTE *pucWriteArray);
BYTE ScalerMcuDdcci3GetInputPort(void);
void ScalerMcuDdcci3SelectDdcChannel(BYTE ucInputPort);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
BYTE ScalerMcuDdcci0IntGetData_EXINT1(BYTE *pucReadArray, BYTE ucBufLength);

#if(_MULTI_DISPLAY_MAX >= 0x02)
BYTE ScalerMcuDdcci1IntGetData_EXINT1(BYTE *pucReadArray);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
BYTE ScalerMcuDdcci2IntGetData_EXINT1(BYTE *pucReadArray);
BYTE ScalerMcuDdcci3IntGetData_EXINT1(BYTE *pucReadArray);
#endif

#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
void ScalerMcuDdcciReleaseScl(EnumDDCCIPort enumDDCCIPort);
#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
void ScalerMcuDdcciHoldScl_EXINT1(EnumDDCCIPort enumDDCCIPort);
BYTE ScalerMcuDdcciGetDDCChannel_EXINT1(EnumDDCCIPort enumDDCCIPort);
#endif
BYTE ScalerMcuDdcciGetDDCChannel(EnumDDCCIPort enumDDCCIPort);
#endif

BYTE ScalerMcuDdcciGetBufferSize(void);

void ScalerMcuFlashClockDiv(EnumFlashClkDiv enumClkDiv);
void ScalerMcuClockDiv(EnumMcuClkDiv enumClkDiv);
void ScalerMcuClockSel(EnumClkSel enumClock);

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
void ScalerMcuSwitchFlashMcuFastSpeed(bit bEnable);
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
void ScalerMcuIntoIdle(void);
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
void ScalerMcuSarAdcClkSel(EnumClkSel enumClock);
#endif

#if(_PWM_FUNCTION_SUPPORT == _ON)
void ScalerMcuPwmClockSel(EnumClkSel enumClock);
void ScalerMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency);
#endif

void ScalerMcu5usDelayCalc(EnumClkSel enumClock);

#if(_SW_IIC_SUPPORT == _ON)
BYTE ScalerMcuIICStart(BYTE ucSlaveAddr);
void ScalerMcuIICStop(void);
BYTE ScalerMcuIICGetAck(void);
void ScalerMcuIICSendAck(void);
void ScalerMcuIICSendNoAck(void);
BYTE ScalerMcuIICGetByte(void);
BYTE ScalerMcuIICSendByte(BYTE ucValue);
bit ScalerMcuIICWriteStart(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
bit ScalerMcuIICWritePolling(BYTE ucSlaveAddr);
#endif
bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray);
bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray);
#endif

#if(_HW_IIC_SUPPORT == _ON)
void ScalerMcuHwIICInitial(void);
void ScalerMcuHwIICSetFreqDiv(EnumClkSel enumClock);
#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
bit ScalerMcuHwIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum);
#endif
bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum);
bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum);
#endif

#if(_UART_SUPPORT == _ON)
bit ScalerMcuUartWrite(BYTE ucValue);
#endif

void ScalerMcuIspInitial(void);
void ScalerMcuPwmControl(EnumPowerStatus enumPowStatus);

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
void ScalerMcuBootInitial(void);
#endif
void ScalerMcuCacheInitial(void);
void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode);

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
void ScalerMcuDdcRamEDIDAddrSelect(EnumD0D1DDCRAMSelect enumDdcRamSel, EnumDDCAddrType enumDdcAddr);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : MCU Initial Settings
//
// MCU initial function, must be called at first
// Since code banking can not work correctly before this function is called,
// this function should stay in bank0.
//
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuInitial(void)
{
    BYTE ucFlashDivTemp = 0;

    // Clear Watchdog & Set CNT1 to Max
    MCU_FFEA_WATCHDOG_TIMER |= _BIT6 | _BIT2 | _BIT1 | _BIT0;

    // First Mux(epll/m2pll) Select M2pll
    MCU_FFE9_MCU_CLK_CONTROL_1 &= ~_BIT4;

    // Select Flash Clock Divider 1
    ucFlashDivTemp = ((_FLASH_CLK_IN_DIV & 0x0F) << 2);
    ucFlashDivTemp |= (MCU_FFED_MCU_CONTROL & 0xC3);
    MCU_FFED_MCU_CONTROL = ucFlashDivTemp;

    // Select Flash Clock Divider 2
    ucFlashDivTemp = (_FLASH_2_CLK_IN_DIV & 0x0F);
    ucFlashDivTemp |= (MCU_FFE9_MCU_CLK_CONTROL_1 & 0xF0);
    MCU_FFE9_MCU_CLK_CONTROL_1 = ucFlashDivTemp;

    ScalerMcuClockDiv(_MCU_CLK_DIV);
    ScalerMcu5usDelayCalc(_EXT_XTAL_CLK);


    ////////////////////////
    // Bankswitch Settings//
    ////////////////////////

    // Enable address remapping to XDATA, enable global XRAM and XFR
    // Use Pbank_switch, enable bankswitching function
    MCU_FFFC_BANK_SWICH_CONTROL |= _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0;

    // Select XDATA BANK Start
    MCU_FFFD_XDATA_BANK_START = 0x00;

    // Select first bank number for XDATA access
    MCU_FFFE_XDATA_BANK_SEL = 0x00; // Xdata_bank_sel: Bank0


    //////////////////
    //Cache Initial///
    //////////////////

    ScalerMcuCacheInitial();


    //////////////////
    //TIMER SETTINGS//
    //////////////////

    // Clock Control, Timer divide by 12 clock, MOVX duration = 2 machine cycles
    CKCON &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

    // Disable all interrupts
    IE = 0x00;

    // Stop Timer0 and Clear Flag
    TR0 = _OFF;
    TF0 = _OFF;

    // Stop Timer1 and Clear Flag
    TR1 = _OFF;
    TF1 = _OFF;

    // Stop Timer2 and Clear Flag
    TR2 = _OFF;
    TF2 = _OFF;
    TCLK = 0;
    RCLK = 0;

#if(_UART_SUPPORT == _ON)
    // Set Timer0 to Mode1 (16bit Counter)
    // Set Timer1 to Mode2 (8bit Counter with Auto-Reload)
    TMOD = 0x21;
#else
    // Set Timer0/1 to Mode1 (16bit counter)
    TMOD = 0x11;
#endif

    // Enable Timer2 AutoReload Mode
    T2CON &= ~_BIT0;

    // Set Interrupt Priority for Timer2
    PT0 = 0;
    PT1 = 0;
    PT2 = 1;

    // Enable Global Interrupt
    EA = _ENABLE;

    // Load Timer2 Count Value
    ScalerTimerSetTimerCount(_TIMER_OPERATION_INITIAL_MODE);

    // Start Watchdog
    MCU_FFEA_WATCHDOG_TIMER |= _BIT7;

#if(_UART_SUPPORT == _ON)

    /////////////////
    //UART Settings//
    /////////////////

    // Set Serial Port to Mode 1
    SM0 = 0;
    SM1 = 1;

    // SMOD0 Set to 1
    PCON |= _BIT7;

    // RI will be only activated if a valid stop is received
    SM2 = 1;

    // Set Serial Port Receive Enable
    REN = _ENABLE;

    // Clear Transmit and Receive Flags
    TI = 0;
    RI = 0;

    // Enable Serial Port IRQ
    ES = _ENABLE;
#endif


    /////////////////////////
    //GPIO Control Settings//
    /////////////////////////

    ScalerMcuGpioInitial();


    ////////////////
    //ISP Settings//
    ////////////////

    ScalerMcuIspInitial();


    ///////////////////
    // Flash Settings//
    ///////////////////

    // Set Flash fast read mode and latch Flash SO data in falling edge
    MCU_FF6C_READ_INSTRUCTION |= _BIT6 | _BIT5;


    ////////////////
    //PWM Settings//
    ////////////////

#if(_PWM_DUT_RESOLUTION == _PWM_8BIT)
    // Select 8 bit duty width type
    MCU_FF53_PWM_DUT_TYPE |= (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
#else
    // Select 12 bit duty width type
    MCU_FF53_PWM_DUT_TYPE &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

    // Enable double buffer mode
    MCU_FF48_PWM_EN |= _BIT7;
#endif

    // Enable PWM reset by DVS
    MCU_FF47_PWM_VS_CTRL = (((BYTE)_PWM5_RST_BY_DVS << 5) | ((BYTE)_PWM4_RST_BY_DVS << 4) | ((BYTE)_PWM3_RST_BY_DVS << 3) |
                            ((BYTE)_PWM2_RST_BY_DVS << 2) | ((BYTE)_PWM1_RST_BY_DVS << 1) | ((BYTE)_PWM0_RST_BY_DVS));


    ////////////////
    //DDC Settings//
    ////////////////

    ScalerMcuDdcInitial();


    ///////////////////
    //DDC-CI Settings//
    ///////////////////

    ScalerMcuDdcciInitial();


    ////////////////
    //IIC Settings//
    ////////////////

#if(_HW_IIC_SUPPORT == _ON)
    ScalerMcuHwIICInitial();
#endif


    ///////////////////
    //SARADC Settings//
    ///////////////////

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
    // Set Threshold for Auto Mode
    MCU_FF0F_ADC0_THRESHOLD_H = 0x00;
    MCU_FF10_ADC0_THRESHOLD_L = 0xFF;
    MCU_FF11_ADC1_THRESHOLD_H = 0x00;
    MCU_FF12_ADC1_THRESHOLD_L = 0xFF;
    MCU_FF13_ADC2_THRESHOLD_H = 0x00;
    MCU_FF14_ADC2_THRESHOLD_L = 0xFF;
    MCU_FF15_ADC3_THRESHOLD_H = 0x00;
    MCU_FF16_ADC3_THRESHOLD_L = 0xFF;

    // Set Auto Mode
    MCU_FF08_ADC_ACONTROL |= _BIT5;

    // Set Wait Time between measure
    MCU_FF17_CTRL0_WAIT_TIME_VALUE = 0x00;

    // Set ADC bias current to 5uA
    MCU_FF08_ADC_ACONTROL &= ~(_BIT2 | _BIT1);

    // ADC Start Scan
    MCU_FF08_ADC_ACONTROL |= _BIT7;
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
    ScalerTimerWDInitial();
#endif
}

//--------------------------------------------------
// Description  : DDC-CI Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciInitial(void)
{
    // Set slave address for debug tool
    MCU_FF23_IIC_SET_SLAVE = 0x6A;

    // Disable DDCCI 1,2,3
    MCU_FE87_IIC_1_SET_SLAVE = 0x3C;
    MCU_FE95_IIC_2_SET_SLAVE = 0x3C;
    MCU_FEA4_IIC_3_SET_SLAVE = 0x3C;

    MCU_FE86_IIC_1_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
    MCU_FE94_IIC_2_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
    MCU_FEA3_IIC_3_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC5)
    // DDC from DDC5 channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
    MCU_FF22_IIC_CH_SEL |= (_BIT2 | _BIT1);
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC4)
    // DDC from DDC4 channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
    MCU_FF22_IIC_CH_SEL |= (_BIT2 | _BIT0);
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC3)
    // DDC from DDC3 channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
    MCU_FF22_IIC_CH_SEL |= _BIT2;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC2)
    // DDC from DDC2 channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
    MCU_FF22_IIC_CH_SEL |= (_BIT1 | _BIT0);
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
    // DDC from DDC1 channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
    MCU_FF22_IIC_CH_SEL |= _BIT1;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
    // DDC from DDC0 channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
    MCU_FF22_IIC_CH_SEL |= _BIT0;
#else
    // DDC from VGA_DDC channel
    MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
#endif
    // Assign DDC-CI interrupts to int1 (IRQ2)
    MCU_FFC4_IRQ_PRIORITY_3 &= ~(_BIT2 | _BIT1 | _BIT0);
    MCU_FFC4_IRQ_PRIORITY_3 |= _BIT0;

    //////////////////
    //DDC-CI 0 reset//
    //////////////////

    // Enable DDC-CI buffer auto reset
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FF27_IIC_STATUS = 0x00;
    pData[0] = MCU_FF25_IIC_DATA_IN;
    MCU_FF26_IIC_DATA_OUT = 0x00;
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

    //////////////////
    //DDC-CI 1 reset//
    //////////////////

    // Enable DDC-CI buffer auto reset
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FE8B_IIC_1_STATUS = 0x00;
    pData[0] = MCU_FE89_IIC_1_DATA_IN;
    MCU_FE8A_IIC_1_DATA_OUT = 0x00;
    MCU_FE8D_IIC_1_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

    //////////////////
    //DDC-CI 2 reset//
    //////////////////

    // Enable DDC-CI buffer auto reset
    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FE99_IIC_2_STATUS = 0x00;
    pData[0] = MCU_FE97_IIC_2_DATA_IN;
    MCU_FE98_IIC_2_DATA_OUT = 0x00;
    MCU_FE9B_IIC_2_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;

    //////////////////
    //DDC-CI 3 reset//
    //////////////////

    // Enable DDC-CI buffer auto reset
    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT7;

    // Clear DDCCI status
    MCU_FEA8_IIC_3_STATUS = 0x00;
    pData[0] = MCU_FEA6_IIC_3_DATA_IN;
    MCU_FEA7_IIC_3_DATA_OUT = 0x00;
    MCU_FEAA_IIC_3_STATUS2 &= ~(_BIT5 | _BIT4);

    // Reset IIC Buffer
    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;

    // Enable INT1
    EX1 = 1;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FF28_IIC_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;

    DebugMessageSystem("######    F/W START    ######", _OFF);
}

//--------------------------------------------------
// Description  : Send DDC Data
// Input Value  : enDdcciChannel --> DDCCI Channel Index
//                pWriteArray --> Data to be sent
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSendData(EnumDDCCIPort enumDdcciChannel, BYTE *pucWriteArray)
{
    switch(enumDdcciChannel)
    {
        case _DDCCI0:
            ScalerMcuDdcci0SendData(pucWriteArray);
            break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
        case _DDCCI1:
            ScalerMcuDdcci1SendData(pucWriteArray);
            break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        case _DDCCI2:
            ScalerMcuDdcci2SendData(pucWriteArray);
            break;

        case _DDCCI3:
            ScalerMcuDdcci3SendData(pucWriteArray);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : enDdcciChannel --> DDCCI Channel Index
// Output Value : InputPort
//--------------------------------------------------
BYTE ScalerMcuDdcciGetInputPort(EnumDDCCIPort enumDdcciChannel)
{
    switch(enumDdcciChannel)
    {
        case _DDCCI0:
            return ScalerMcuDdcci0GetInputPort();
            break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
        case _DDCCI1:
            return ScalerMcuDdcci1GetInputPort();
            break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        case _DDCCI2:
            return ScalerMcuDdcci2GetInputPort();
            break;

        case _DDCCI3:
            return ScalerMcuDdcci3GetInputPort();
            break;
#endif

        default:
            return _NO_INPUT_PORT;
            break;
    }

    return _NO_INPUT_PORT;
}

//--------------------------------------------------
// Description  : Select which DDCCI Connect to which DDC
// Input Value  : enDdcciChannel --> DDCCI Channel Index
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSelectDdcChannel(EnumDDCCIPort enumDdcciChannel, BYTE ucInputPort)
{
    switch(enumDdcciChannel)
    {
        case _DDCCI0:
            ScalerMcuDdcci0SelectDdcChannel(ucInputPort);
            break;

#if(_MULTI_DISPLAY_MAX >= 0x02)
        case _DDCCI1:
            ScalerMcuDdcci1SelectDdcChannel(ucInputPort);
            break;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        case _DDCCI2:
            ScalerMcuDdcci2SelectDdcChannel(ucInputPort);
            break;

        case _DDCCI3:
            ScalerMcuDdcci3SelectDdcChannel(ucInputPort);
            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DDCCI0 Channel Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
//                usTimeOutCnt --> Timeout
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci0SendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    // Enable mcu write
    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FF29_IIC_STATUS2 & _BIT2) == 0)
        {
            MCU_FF26_IIC_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
BYTE ScalerMcuDdcci0GetInputPort(void)
{
    switch(MCU_FF22_IIC_CH_SEL & (_BIT2 | _BIT1 | _BIT0))
    {
        case _VGA_DDC:
            pData[0] = _A0_INPUT_PORT;
            break;

        case _DDC0:
            pData[0] = _D0_INPUT_PORT;
            break;

        case _DDC1:
            pData[0] = _D1_INPUT_PORT;
            break;

        case _DDC2:
            pData[0] = _D2_INPUT_PORT;
            break;

        case _DDC3:
            pData[0] = _D3_INPUT_PORT;
            break;

        case _DDC4:
            pData[0] = _D4_INPUT_PORT;
            break;

        case _DDC5:
            pData[0] = _D5_INPUT_PORT;
            break;

        default:
            pData[0] = _NO_INPUT_PORT;
            break;
    }

    return pData[0];
}

//--------------------------------------------------
// Description  : Select Which DDC Connect to DDCCI0
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci0SelectDdcChannel(BYTE ucInputPort)
{
#if(_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)
    if(ucInputPort == _D6_INPUT_PORT)
    {
        ucInputPort = _D0_INPUT_PORT;
    }
#endif

    if(ucInputPort == _NO_INPUT_PORT)
    {
        MCU_FF22_IIC_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
    }
    else
    {
        MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= ucInputPort;
    }
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : DDCCI1 Channel Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
//                usTimeOutCnt --> Timeout
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci1SendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    // Enable mcu write
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FE8D_IIC_1_STATUS2 & _BIT2) == 0)
        {
            MCU_FE8A_IIC_1_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
BYTE ScalerMcuDdcci1GetInputPort(void)
{
    switch(MCU_FE86_IIC_1_CH_SEL & (_BIT2 | _BIT1 | _BIT0))
    {
        case _VGA_DDC:
            pData[0] = _A0_INPUT_PORT;
            break;

        case _DDC0:
            pData[0] = _D0_INPUT_PORT;
            break;

        case _DDC1:
            pData[0] = _D1_INPUT_PORT;
            break;

        case _DDC2:
            pData[0] = _D2_INPUT_PORT;
            break;

        case _DDC3:
            pData[0] = _D3_INPUT_PORT;
            break;

        case _DDC4:
            pData[0] = _D4_INPUT_PORT;
            break;

        case _DDC5:
            pData[0] = _D5_INPUT_PORT;
            break;

        default:
            pData[0] = _NO_INPUT_PORT;
            break;
    }

    return pData[0];
}

//--------------------------------------------------
// Description  : Select Which DDC Connect to DDCCI1
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci1SelectDdcChannel(BYTE ucInputPort)
{
#if(_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)
    if(ucInputPort == _D6_INPUT_PORT)
    {
        ucInputPort = _D0_INPUT_PORT;
    }
#endif

    if(ucInputPort == _NO_INPUT_PORT)
    {
        MCU_FE86_IIC_1_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
    }
    else
    {
        MCU_FE86_IIC_1_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FE86_IIC_1_CH_SEL |= ucInputPort;
    }
}
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Description  : DDCCI2 Channel Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci2SendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    // Enable mcu write
    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FE9B_IIC_2_STATUS2 & _BIT2) == 0)
        {
            MCU_FE98_IIC_2_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
BYTE ScalerMcuDdcci2GetInputPort(void)
{
    switch(MCU_FE94_IIC_2_CH_SEL & (_BIT2 | _BIT1 | _BIT0))
    {
        case _VGA_DDC:
            pData[0] = _A0_INPUT_PORT;
            break;

        case _DDC0:
            pData[0] = _D0_INPUT_PORT;
            break;

        case _DDC1:
            pData[0] = _D1_INPUT_PORT;
            break;

        case _DDC2:
            pData[0] = _D2_INPUT_PORT;
            break;

        case _DDC3:
            pData[0] = _D3_INPUT_PORT;
            break;

        case _DDC4:
            pData[0] = _D4_INPUT_PORT;
            break;

        case _DDC5:
            pData[0] = _D5_INPUT_PORT;
            break;

        default:
            pData[0] = _NO_INPUT_PORT;
            break;
    }

    return pData[0];
}

//--------------------------------------------------
// Description  : Select Which DDC Connect to DDCCI2
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci2SelectDdcChannel(BYTE ucInputPort)
{
#if(_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)
    if(ucInputPort == _D6_INPUT_PORT)
    {
        ucInputPort = _D0_INPUT_PORT;
    }
#endif

    if(ucInputPort == _NO_INPUT_PORT)
    {
        MCU_FE94_IIC_2_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
    }
    else
    {
        MCU_FE94_IIC_2_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FE94_IIC_2_CH_SEL |= ucInputPort;
    }
}

//--------------------------------------------------
// Description  : DDCCI3 Channel Send DDC Data
// Input Value  : pWriteArray --> Data to be sent
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci3SendData(BYTE *pucWriteArray)
{
    WORD usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
    BYTE ucDdcciCount = 0;

    // Enable mcu write
    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucDdcciCount < ((pucWriteArray[_DCCCI_LENGTH] & 0x7F) + 3))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FEAA_IIC_3_STATUS2 & _BIT2) == 0)
        {
            MCU_FEA7_IIC_3_DATA_OUT = pucWriteArray[ucDdcciCount++];

            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            ScalerTimerDelayXms(2);

            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    // Disable mcu write
    MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Get InputPort by checking Active DDC Channel for Ddccci
// Input Value  : None
// Output Value : InputPort
//--------------------------------------------------
BYTE ScalerMcuDdcci3GetInputPort(void)
{
    switch(MCU_FEA3_IIC_3_CH_SEL & (_BIT2 | _BIT1 | _BIT0))
    {
        case _VGA_DDC:
            pData[0] = _A0_INPUT_PORT;
            break;

        case _DDC0:
            pData[0] = _D0_INPUT_PORT;
            break;

        case _DDC1:
            pData[0] = _D1_INPUT_PORT;
            break;

        case _DDC2:
            pData[0] = _D2_INPUT_PORT;
            break;

        case _DDC3:
            pData[0] = _D3_INPUT_PORT;
            break;

        case _DDC4:
            pData[0] = _D4_INPUT_PORT;
            break;

        case _DDC5:
            pData[0] = _D5_INPUT_PORT;
            break;

        default:
            pData[0] = _NO_INPUT_PORT;
            break;
    }

    return pData[0];
}

//--------------------------------------------------
// Description  : Select Which DDC Connect to DDCCI3
// Input Value  : InputPort
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcci3SelectDdcChannel(BYTE ucInputPort)
{
#if(_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0)
    if(ucInputPort == _D6_INPUT_PORT)
    {
        ucInputPort = _D0_INPUT_PORT;
    }
#endif

    if(ucInputPort == _NO_INPUT_PORT)
    {
        MCU_FEA3_IIC_3_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
    }
    else
    {
        MCU_FEA3_IIC_3_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FEA3_IIC_3_CH_SEL |= ucInputPort;
    }
}
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Get DDC-CI Data in Interrupt Process
// Input Value  : pReadArray --> Data received
//                 ucBufLength --> DDC-DI 0 Rx Buffer Length
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcci0IntGetData_EXINT1(BYTE *pucReadArray, BYTE ucBufLength) using 2
{
    // Get DDC-CI Source Address
    if((MCU_FF27_IIC_STATUS & _BIT1) == _BIT1)
    {
        g_ucDdcciCountEXINT = 0;

        // Save Address
        pucReadArray[g_ucDdcciCountEXINT++] = MCU_FF24_IIC_SUB_IN;

        // Clear Flag
        MCU_FF27_IIC_STATUS &= ~_BIT1;
    }

    if((MCU_FF27_IIC_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FF29_IIC_STATUS2 & _BIT1) == 0)
        {
            if(g_ucDdcciCountEXINT >= ucBufLength)
            {
                // Reset data buffer
                MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

                g_ucDdcciCountEXINT = 0;

                break;
            }

            pucReadArray[g_ucDdcciCountEXINT++] = MCU_FF25_IIC_DATA_IN;

            // Reset data buffer and Enable mcu write
            if(((pucReadArray[_DCCCI_LENGTH] & 0x7F) + 3) == g_ucDdcciCountEXINT)
            {
                // Reset data buffer
                MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucDdcciCountEXINT = 0;

                for(pData_EXINT[0] = 32; pData_EXINT[0] > 0; pData_EXINT[0] --)
                {
                    MCU_FF26_IIC_DATA_OUT = 0;
                }

                // Disable mcu write
                MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;

                // Reset data buffer
                MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl_EXINT1(_DDCCI0);
                }
#endif
                return _SUCCESS;
            }
        }
    }

    return _FAIL;
}

#if(_MULTI_DISPLAY_MAX >= 0x02)
//--------------------------------------------------
// Description  : Get DDC-CI1 Data in Interrupt Process
// Input Value  : pReadArray --> Data received
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcci1IntGetData_EXINT1(BYTE *pucReadArray) using 2
{
    // Get DDC-CI Source Address
    if((MCU_FE8B_IIC_1_STATUS & _BIT1) == _BIT1)
    {
        g_ucDdcciCountEXINT = 0;

        // Save Address
        pucReadArray[g_ucDdcciCountEXINT++] = MCU_FE88_IIC_1_SUB_IN;

        // Clear Flag
        MCU_FE8B_IIC_1_STATUS &= ~_BIT1;
    }

    if((MCU_FE8B_IIC_1_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FE8D_IIC_1_STATUS2 & _BIT1) == 0)
        {
            if(g_ucDdcciCountEXINT >= _DDCCI_RXBUF_LENGTH)
            {
                // Reset data buffer
                MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

                g_ucDdcciCountEXINT = 0;

                break;
            }

            pucReadArray[g_ucDdcciCountEXINT++] = MCU_FE89_IIC_1_DATA_IN;

            // All data are received
            if(((pucReadArray[_DCCCI_LENGTH] & 0x7F) + 3) == g_ucDdcciCountEXINT)
            {
                // Reset data buffer and Enable mcu write
                MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucDdcciCountEXINT = 0;

                for(pData_EXINT[0] = 32; pData_EXINT[0] > 0; pData_EXINT[0] --)
                {
                    MCU_FE8A_IIC_1_DATA_OUT = 0;
                }

                // Disable mcu write
                MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;

                // Reset data buffer
                MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl_EXINT1(_DDCCI1);
                }
#endif
                return _SUCCESS;
            }
        }
    }

    return _FAIL;
}
#endif // End of #if(_MULTI_DISPLAY_MAX >= 0x02)

#if(_MULTI_DISPLAY_MAX >= 0x04)
//--------------------------------------------------
// Description  : Get DDC-CI2 Data in Interrupt Process
// Input Value  : pReadArray --> Data received
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcci2IntGetData_EXINT1(BYTE *pucReadArray) using 2
{
    // Get DDC-CI Source Address
    if((MCU_FE99_IIC_2_STATUS & _BIT1) == _BIT1)
    {
        g_ucDdcciCountEXINT = 0;

        // Save Address
        pucReadArray[g_ucDdcciCountEXINT++] = MCU_FE96_IIC_2_SUB_IN;

        // Clear Flag
        MCU_FE99_IIC_2_STATUS &= ~_BIT1;
    }

    if((MCU_FE99_IIC_2_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FE9B_IIC_2_STATUS2 & _BIT1) == 0)
        {
            if(g_ucDdcciCountEXINT >= _DDCCI_RXBUF_LENGTH)
            {
                // Reset data buffer
                MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;

                g_ucDdcciCountEXINT = 0;

                break;
            }

            pucReadArray[g_ucDdcciCountEXINT++] = MCU_FE97_IIC_2_DATA_IN;

            // All data are received
            if(((pucReadArray[_DCCCI_LENGTH] & 0x7F) + 3) == g_ucDdcciCountEXINT)
            {
                // Reset data buffer and Enable mcu write
                MCU_FE9C_IIC_2_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucDdcciCountEXINT = 0;

                for(pData_EXINT[0] = 32; pData_EXINT[0] > 0; pData_EXINT[0] --)
                {
                    MCU_FE98_IIC_2_DATA_OUT = 0;
                }

                // Disable mcu write
                MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;

                // Reset data buffer
                MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl_EXINT1(_DDCCI2);
                }
#endif
                return _SUCCESS;
            }
        }
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Get DDC-CI3 Data in Interrupt Process
// Input Value  : pReadArray --> Data received
// Output Value : _SUCCESS or _FAIL
//--------------------------------------------------
BYTE ScalerMcuDdcci3IntGetData_EXINT1(BYTE *pucReadArray) using 2
{
    // Get DDC-CI Source Address
    if((MCU_FEA8_IIC_3_STATUS & _BIT1) == _BIT1)
    {
        g_ucDdcciCountEXINT = 0;

        // Save Address
        pucReadArray[g_ucDdcciCountEXINT++] = MCU_FEA5_IIC_3_SUB_IN;

        // Clear Flag
        MCU_FEA8_IIC_3_STATUS &= ~_BIT1;
    }

    if((MCU_FEA8_IIC_3_STATUS & _BIT2) == _BIT2)
    {
        // Save received data until buffer empty
        while((MCU_FEAA_IIC_3_STATUS2 & _BIT1) == 0)
        {
            if(g_ucDdcciCountEXINT >= _DDCCI_RXBUF_LENGTH)
            {
                // Reset data buffer
                MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;

                g_ucDdcciCountEXINT = 0;

                break;
            }

            pucReadArray[g_ucDdcciCountEXINT++] = MCU_FEA6_IIC_3_DATA_IN;

            // All data are received
            if(((pucReadArray[_DCCCI_LENGTH] & 0x7F) + 3) == g_ucDdcciCountEXINT)
            {
                // Reset data buffer and Enable mcu write
                MCU_FEAB_IIC_3_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

                g_ucDdcciCountEXINT = 0;

                for(pData_EXINT[0] = 32; pData_EXINT[0] > 0; pData_EXINT[0] --)
                {
                    MCU_FEA7_IIC_3_DATA_OUT = 0;
                }

                // Disable mcu write
                MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;

                // Reset data buffer
                MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
                if((pucReadArray[3] == _DDCCI_OPCODE_VCP_DISP_CALIBRATION) && (pucReadArray[2] == 0x03))
                {
                    // Hold Scl for Display Calibration Process
                    ScalerMcuDdcciHoldScl_EXINT1(_DDCCI3);
                }
#endif
                return _SUCCESS;
            }
        }
    }

    return _FAIL;
}
#endif
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)

#if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Release SCL
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcciReleaseScl(EnumDDCCIPort enumDDCCIPort)
{
    switch(ScalerMcuDdcciGetDDCChannel(enumDDCCIPort) & (_BIT2 | _BIT1 | _BIT0))
    {
        case _DDC5:
            MCU_FE81_DDC5_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _DDC4:
            MCU_FE78_DDC4_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _DDC3:
            MCU_FE6F_DDC3_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _DDC2:
            MCU_FE66_DDC2_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _DDC1:
            MCU_FF2E_DDC1_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _DDC0:
            MCU_FF20_DDC0_DDC_CONTROL_2 &= ~_BIT0;
            break;

        case _VGA_DDC:
            MCU_FF1D_ADC_DDC_CONTROL_2 &= ~_BIT0;
            break;

        default:

            break;
    }
}

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : hold SCL
// Input Value  : NONE
// Output Value : NONE
//--------------------------------------------------
void ScalerMcuDdcciHoldScl_EXINT1(EnumDDCCIPort enumDDCCIPort) using 2
{
    switch(ScalerMcuDdcciGetDDCChannel_EXINT1(enumDDCCIPort) & (_BIT2 | _BIT1 | _BIT0))
    {
        case _DDC5:
            MCU_FE81_DDC5_DDC_CONTROL_2 |= _BIT0;
            break;

        case _DDC4:
            MCU_FE78_DDC4_DDC_CONTROL_2 |= _BIT0;
            break;

        case _DDC3:
            MCU_FE6F_DDC3_DDC_CONTROL_2 |= _BIT0;
            break;

        case _DDC2:
            MCU_FE66_DDC2_DDC_CONTROL_2 |= _BIT0;
            break;

        case _DDC1:
            MCU_FF2E_DDC1_DDC_CONTROL_2 |= _BIT0;
            break;

        case _DDC0:
            MCU_FF20_DDC0_DDC_CONTROL_2 |= _BIT0;
            break;

        case _VGA_DDC:
            MCU_FF1D_ADC_DDC_CONTROL_2 |= _BIT0;
            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Get DDC Channel for intterrupt
// Input Value  : enDDCCIPort --> DDC CI Port
// Output Value : DDC Channel no
//--------------------------------------------------
BYTE ScalerMcuDdcciGetDDCChannel_EXINT1(EnumDDCCIPort enumDDCCIPort) using 2
{
    BYTE ucDDCNo = _NO_DDC;

    switch(enumDDCCIPort)
    {
        case _DDCCI0:

            ucDDCNo = (MCU_FF22_IIC_CH_SEL & (_BIT2 | _BIT1 | _BIT0));

            break;

        case _DDCCI1:

            ucDDCNo = (MCU_FE86_IIC_1_CH_SEL & (_BIT2 | _BIT1 | _BIT0));

            break;

        case _DDCCI2:

            ucDDCNo = (MCU_FE94_IIC_2_CH_SEL & (_BIT2 | _BIT1 | _BIT0));

            break;

        case _DDCCI3:

            ucDDCNo = (MCU_FEA3_IIC_3_CH_SEL & (_BIT2 | _BIT1 | _BIT0));

            break;

        default:
            break;
    }

    return ucDDCNo;
}
#endif

//--------------------------------------------------
// Description  : Get DDC Channel for normal
// Input Value  : enDDCCIPort --> DDC CI Port
// Output Value : DDC Channel no
//--------------------------------------------------
BYTE ScalerMcuDdcciGetDDCChannel(EnumDDCCIPort enumDDCCIPort)
{
    BYTE ucDDCNo = _NO_DDC;

    switch(enumDDCCIPort)
    {
        case _DDCCI0:

            ucDDCNo = (MCU_FF22_IIC_CH_SEL & (_BIT2 | _BIT1 | _BIT0));

            break;

        case _DDCCI1:

            ucDDCNo = (MCU_FE86_IIC_1_CH_SEL & (_BIT2 | _BIT1 | _BIT0));

            break;

        case _DDCCI2:

            ucDDCNo = (MCU_FE94_IIC_2_CH_SEL & (_BIT2 | _BIT1 | _BIT0));

            break;

        case _DDCCI3:

            ucDDCNo = (MCU_FEA3_IIC_3_CH_SEL & (_BIT2 | _BIT1 | _BIT0));

            break;

        default:
            break;
    }

    return ucDDCNo;
}
#endif  // End of #if((_OGC_SUPPORT == _ON) || (_OCC_SUPPORT == _ON) || (_OGC_DICOM_SUPPORT == _ON))

//--------------------------------------------------
// Description  : Get DDC Buffer Size
// Input Value  : None
// Output Value : DDCCI Buffer Size
//--------------------------------------------------
BYTE ScalerMcuDdcciGetBufferSize(void)
{
    return _DDCCI_BUFFER_SIZE;
}

//--------------------------------------------------
// Description  : Set Flash Clock Divider.
// Input Value  : ClkDiv --> Flash Clock Divider
// Output Value : None
//--------------------------------------------------
void ScalerMcuFlashClockDiv(EnumFlashClkDiv enumClkDiv)
{
    BYTE ucFlashDiv2 = 0;

    enumClkDiv &= 0x0F;
    enumClkDiv = (enumClkDiv << 2);
    enumClkDiv |= (MCU_FFED_MCU_CONTROL & 0xC3);
    MCU_FFED_MCU_CONTROL = enumClkDiv;

    ucFlashDiv2 = (_FLASH_2_CLK_DIV & 0x0F);
    ucFlashDiv2 |= (MCU_FFE9_MCU_CLK_CONTROL_1 & 0xF0);
    MCU_FFE9_MCU_CLK_CONTROL_1 = ucFlashDiv2;
}

//--------------------------------------------------
// Description  : Set Mcu Clock Divider.
// Input Value  : ClkDiv --> MCU Clock Divider
// Output Value : None
//--------------------------------------------------
void ScalerMcuClockDiv(EnumMcuClkDiv enumClkDiv)
{
    enumClkDiv &= 0x0F;
    enumClkDiv = (enumClkDiv << 2);
    enumClkDiv |= (MCU_FFEE_MCU_CLOCK_CONTROL & 0xC3);
    MCU_FFEE_MCU_CLOCK_CONTROL = enumClkDiv;
}

//--------------------------------------------------
// Description  : CPU Clock Select.
// Input Value  : Clock --> _M2PLL_CLK/_EXT_XTAL_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuClockSel(EnumClkSel enumClock)
{
    if(enumClock == _M2PLL_CLK)
    {
        // Bit1 : 1 --> CPU CLK Source Select to M2PLL
        MCU_FFED_MCU_CONTROL |= _BIT1;
    }
    else
    {
        // Bit1 : 0 --> CPU CLK Source Select to Xtal
        MCU_FFED_MCU_CONTROL &= ~_BIT1;
    }
}

#if(_FLASH_CLK_SPEED == _FLASH_LOW_SPEED)
//--------------------------------------------------
// Description  : Set Flash & Mcu Divider when OSD is running.
// Input Value  : Fast or Low Speed
// Output Value : None
//--------------------------------------------------
void ScalerMcuSwitchFlashMcuFastSpeed(bit bEnable)
{
    // Only Take Effect when Flash Clk is From M2PLL
    if((MCU_FFED_MCU_CONTROL & _BIT1) == _BIT1)
    {
        if(bEnable == _ENABLE)
        {
            // Don't Switch Again If It's Already Using Fast Div
            if(((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) != _FLASH_CLK_FAST_DIV)
            {
                // Switch Flash and MCU Clock to high speed
                ScalerMcuFlashClockDiv(_FLASH_CLK_FAST_DIV);

                // Reload Timer Count
                ScalerTimerSetTimerCount(_TIMER_OPERATION_OSD_MODE);
            }
        }
        else if(bEnable == _DISABLE)
        {
            // Don't Switch Again If It's Already Using Normal Div
            if(((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) != _FLASH_CLK_DIV)
            {
                // Switch Flash and MCU Clock to low speed
                ScalerMcuFlashClockDiv(_FLASH_CLK_DIV);

                // Reload Timer Count
                ScalerTimerSetTimerCount(_TIMER_OPERATION_POWER_NORMAL_MODE);
            }
        }
    }
}
#endif

#if(_SYSTEM_LOW_POWER_IDLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable MCU Into Idle Mode
// Input Value  : None.
// Output Value : None
//--------------------------------------------------
void ScalerMcuIntoIdle(void)
{
    // Enable MCU into idle mode.
    PCON |= _BIT0;
}
#endif

#if(_LOW_SPEED_ADC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : SARADC Clock Select.
// Input Value  : enumClock --> _M2PLL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuSarAdcClkSel(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // ADC clk from external Xtal and div by 4 to obtain clk target 3MHz
        MCU_FF0D_ADC_CLK_DIV = 0x04;
    }
    else
    {
        // ADC clk from IOSC(27M) and div by 9 to obtain clk target 3MHz
        MCU_FF0D_ADC_CLK_DIV = 0x09;
    }
}

#endif  // End of #if(_LOW_SPEED_ADC_SUPPORT == _ON)

#if(_PWM_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PWM Clock Switch.
// Input Value  : Clock --> _M2PLL_CLK/_EXT_XTAL_CLK(_IOSC_CLK)
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmClockSel(EnumClkSel enumClock)
{
    WORD usCLKDiv = 0;
    WORD usFrequency = 0;

    ////////////////////////////////
    // Adjust PWMx divider: M & N //
    ////////////////////////////////

#if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))

    // Get PWM0 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF3E_PWM0_N_LSB) + 1)
    usCLKDiv = (0x01 << (MCU_FF3B_PWM03_M & (_BIT1 | _BIT0))) * (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF3E_PWM0_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT0) == _BIT0)
    {
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _IOSC_CLK)
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT0;
    }
    else
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT0;
    }

    ScalerMcuPwmAdjustFrequency(_PWM0, usFrequency);

#endif // End of #if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))

#if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON))

    // Get PWM1 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT3 | _BIT2)))
    // N = (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 8) | MCU_FF3F_PWM1_N_LSB) + 1)
    usCLKDiv = (0x01 << ((MCU_FF3B_PWM03_M & (_BIT3 | _BIT2)) >> 2)) * (((WORD)((MCU_FF3D_PWM01_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF3F_PWM1_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT1) == _BIT1)
    {
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _IOSC_CLK)
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT1;
    }
    else
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT1;
    }

    ScalerMcuPwmAdjustFrequency(_PWM1, usFrequency);

#endif // End of #if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON))

#if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON))

    // Get PWM2 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT5 | _BIT4)))
    // N = (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF41_PWM2_N_LSB) + 1)
    usCLKDiv = (0x01 << ((MCU_FF3B_PWM03_M & (_BIT5 | _BIT4)) >> 4)) * (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF41_PWM2_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT2) == _BIT2)
    {
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _IOSC_CLK)
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT2;
    }
    else
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT2;
    }

    ScalerMcuPwmAdjustFrequency(_PWM2, usFrequency);

#endif // End of #if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON))

#if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON))

    // Get PWM3 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3B_PWM03_M & (_BIT7 | _BIT6)))
    // N = (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF42_PWM3_N_LSB) + 1)
    usCLKDiv = (0x01 << ((MCU_FF3B_PWM03_M & (_BIT7 | _BIT6)) >> 6)) * (((WORD)((MCU_FF40_PWM23_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF42_PWM3_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT3) == _BIT3)
    {
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _IOSC_CLK)
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT3;
    }
    else
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT3;
    }

    ScalerMcuPwmAdjustFrequency(_PWM3, usFrequency);

#endif // End of #if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON))

#if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON))

    // Get PWM4 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3C_PWM45_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 8) | MCU_FF44_PWM4_N_LSB) + 1)
    usCLKDiv = (0x01 << (MCU_FF3C_PWM45_M & (_BIT1 | _BIT0))) * (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | MCU_FF44_PWM4_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT4) == _BIT4)
    {
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _IOSC_CLK)
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT4;
    }
    else
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT4;
    }

    ScalerMcuPwmAdjustFrequency(_PWM4, usFrequency);

#endif // End of #if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON))

#if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))

    // Get PWM5 M and N Value
    // PWM CLK divider = 2^M * (N + 1)
    // M = (0x01 <<(MCU_FF3C_PWM45_M & (_BIT1 | _BIT0)))
    // N = (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF44_PWM4_N_LSB) + 1)
    usCLKDiv = (0x01 << ((MCU_FF3C_PWM45_M & (_BIT3 | _BIT2)) >> 2)) * (((WORD)((MCU_FF43_PWM45_N_MSB & (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | MCU_FF45_PWM5_N_LSB) + 1);

    if((MCU_FF3A_PWM_CK_SEL & _BIT5) == _BIT5)
    {
        usFrequency = ((DWORD)_M2PLL_CLK_KHZ * 1000) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }
    else
    {
        usFrequency = (((DWORD)_INTERNAL_OSC_XTAL * 1000) / (0x01 << _IOSC_DIV)) / usCLKDiv / _PWM_DUT_RESOLUTION;
    }

    if(enumClock == _IOSC_CLK)
    {
        // Switch Clock To IOSC
        MCU_FF3A_PWM_CK_SEL &= ~_BIT5;
    }
    else
    {
        // Switch Clock To M2PLL
        MCU_FF3A_PWM_CK_SEL |= _BIT5;
    }

    ScalerMcuPwmAdjustFrequency(_PWM5, usFrequency);

#endif // End of #if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))
}

//--------------------------------------------------
// Description  : PWM Clock Switch.
// Input Value  : ucPwmType --> _BACKLIGHT_PWM/_AUDIO_VOLUME...
//                ucFrequency --> Frequency
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmAdjustFrequency(BYTE ucPwmType, WORD usFrequency)
{
    BYTE ucPWM_M = 0;
    WORD usPWM_N = 0;

    // Set limit for Pwm frequency
    if(usFrequency < _PWM_FREQ_LOW_BOUND)
    {
        usFrequency = _PWM_FREQ_LOW_BOUND;
    }
    else if(usFrequency > _PWM_FREQ_UPPER_BOUND)
    {
        usFrequency = _PWM_FREQ_UPPER_BOUND;
    }

    if(usFrequency >= _PWM_FREQ_DVSRST_BOUND)
    {
        // Disable PWM reset by DVS
#if(_BACKLIGHT_PWM == _PWM0)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT0;

#elif(_BACKLIGHT_PWM == _PWM1)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT1;

#elif(_BACKLIGHT_PWM == _PWM2)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT2;

#elif(_BACKLIGHT_PWM == _PWM3)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT3;

#elif(_BACKLIGHT_PWM == _PWM4)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT4;

#elif(_BACKLIGHT_PWM == _PWM5)
        MCU_FF47_PWM_VS_CTRL &= ~_BIT5;
#endif
    }
    else
    {
        // Enable PWM reset by DVS
#if(_BACKLIGHT_PWM == _PWM0)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM0_RST_BY_DVS);

#elif(_BACKLIGHT_PWM == _PWM1)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM1_RST_BY_DVS << 1);

#elif(_BACKLIGHT_PWM == _PWM2)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM2_RST_BY_DVS << 2);

#elif(_BACKLIGHT_PWM == _PWM3)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM3_RST_BY_DVS << 3);

#elif(_BACKLIGHT_PWM == _PWM4)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM4_RST_BY_DVS << 4);

#elif(_BACKLIGHT_PWM == _PWM5)
        MCU_FF47_PWM_VS_CTRL |= ((BYTE)_PWM5_RST_BY_DVS << 5);
#endif
    }

    // Check if PWM clk is M2PLL or IOSC
    if((MCU_FF3A_PWM_CK_SEL & ucPwmType) == ucPwmType)
    {
        for(ucPWM_M = 0; ucPWM_M < 4; ucPWM_M++)
        {
            // Calculate N Divider for M2PLL
            usPWM_N = ((DWORD)(((((DWORD)_M2PLL_CLK_KHZ * 1000 * 2) / ((DWORD)usFrequency * (0x01 << ucPWM_M) * _PWM_DUT_RESOLUTION)) + 1) / 2) - 1);

            if(usPWM_N < 4096)
            {
                break;
            }
        }
    }
    else
    {
        for(ucPWM_M = 0; ucPWM_M < 4; ucPWM_M++)
        {
            // Calculate N Divider for IOSC 27MHz
            usPWM_N = ((DWORD)(((((DWORD)_INTERNAL_OSC_XTAL * 1000 * 2) / ((DWORD)usFrequency * (0x01 << ucPWM_M) * _PWM_DUT_RESOLUTION)) + 1) / 2) - 1);

            if(usPWM_N < 4096)
            {
                break;
            }
        }
    }

    // Load M/N divider to corresponding register
    switch(ucPwmType)
    {
#if((_PWM0_EN == _ON) || (_PWM0_PSAV_EN == _ON) || (_PWM0_PDOW_EN == _ON))
        case _PWM0:

            MCU_FF3B_PWM03_M = (MCU_FF3B_PWM03_M & ~(_BIT1 | _BIT0)) | (ucPWM_M);
            MCU_FF3D_PWM01_N_MSB &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
            MCU_FF3D_PWM01_N_MSB |= (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            MCU_FF3E_PWM0_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT0;

            break;
#endif

#if((_PWM1_EN == _ON) || (_PWM1_PSAV_EN == _ON) || (_PWM1_PDOW_EN == _ON))
        case _PWM1:

            MCU_FF3B_PWM03_M = (MCU_FF3B_PWM03_M & ~(_BIT3 | _BIT2)) | (ucPWM_M << 2);
            MCU_FF3D_PWM01_N_MSB &= ~(_BIT7 | _BIT6 | _BIT5 | _BIT4);
            MCU_FF3D_PWM01_N_MSB |= (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            MCU_FF3F_PWM1_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT1;

            break;
#endif

#if((_PWM2_EN == _ON) || (_PWM2_PSAV_EN == _ON) || (_PWM2_PDOW_EN == _ON))
        case _PWM2:

            MCU_FF3B_PWM03_M = (MCU_FF3B_PWM03_M & ~(_BIT5 | _BIT4)) | (ucPWM_M << 4);
            MCU_FF40_PWM23_N_MSB &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
            MCU_FF40_PWM23_N_MSB |= (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            MCU_FF41_PWM2_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT2;

            break;
#endif

#if((_PWM3_EN == _ON) || (_PWM3_PSAV_EN == _ON) || (_PWM3_PDOW_EN == _ON))
        case _PWM3:

            MCU_FF3B_PWM03_M = (MCU_FF3B_PWM03_M & ~(_BIT7 | _BIT6)) | (ucPWM_M << 6);
            MCU_FF40_PWM23_N_MSB &= ~(_BIT7 | _BIT6 | _BIT5 | _BIT4);
            MCU_FF40_PWM23_N_MSB |= (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            MCU_FF42_PWM3_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT3;

            break;
#endif

#if((_PWM4_EN == _ON) || (_PWM4_PSAV_EN == _ON) || (_PWM4_PDOW_EN == _ON))
        case _PWM4:

            MCU_FF3C_PWM45_M = (MCU_FF3C_PWM45_M & ~(_BIT1 | _BIT0)) | (ucPWM_M);
            MCU_FF43_PWM45_N_MSB &= ~(_BIT7 | _BIT6 | _BIT5 | _BIT4);
            MCU_FF43_PWM45_N_MSB |= (BYTE)((usPWM_N >> 4) & (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            MCU_FF44_PWM4_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT4;

            break;
#endif

#if((_PWM5_EN == _ON) || (_PWM5_PSAV_EN == _ON) || (_PWM5_PDOW_EN == _ON))
        case _PWM5:

            MCU_FF3C_PWM45_M = (MCU_FF3C_PWM45_M & ~(_BIT3 | _BIT2)) | (ucPWM_M << 2);
            MCU_FF43_PWM45_N_MSB &= ~(_BIT3 | _BIT2 | _BIT1 | _BIT0);
            MCU_FF43_PWM45_N_MSB |= (BYTE)((usPWM_N >> 8) & (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            MCU_FF45_PWM5_N_LSB = (BYTE)usPWM_N;
            MCU_FF49_PWM_CK |= _BIT5;

            break;
#endif
        default:

            break;
    }
}
#endif // End of #if(_PWM_FUNCTION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : 5us Delay Calculation
// Input Value  : Clock --> _M2PLL_CLK/_IOSC_CLK
// Output Value : ucValue --> N = (DelayTime * FlashClock + 24)/80
//--------------------------------------------------
void ScalerMcu5usDelayCalc(EnumClkSel enumClock)
{
    BYTE ucMcuDiv = 0;

    ucMcuDiv = ((MCU_FFED_MCU_CONTROL & 0x3C) >> 2) * ((MCU_FFEE_MCU_CLOCK_CONTROL & 0x3C) >> 2);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Chart :                                                                                                      //
    //                                                                                                              //
    //  INOSC                                                                                                       //
    //    14.318MHz ---|   |      |IOSC|            |   |                                                           //
    //                 |Mux|------|DIV | -----------|   |                                                           //
    //    27MHz     ---|   |      |    |            |   |  EMCU Crystal |   |                                       //
    //                CR0B[0]   Page6 CRA0[1:0]     |Mux|---------------|   |                                       //
    //                                              |   |               |   |                                       //
    //                   external-crystal-----------|   |               |   |       |Flash|      |MCU|              //
    //                                              |   |               |Mux|-------|DIV  |------|DIV|------8051    //
    //                                             CR09[3]              |   |       |     |   |  |   |              //
    //                                                                  |   |     0xFFED[5:2] | 0xFFEE[5:2]         //
    //                                                M2PLL-------------|   |                 |                     //
    //                                                                  |   |                 |--|Flash|            //
    //                                                                0xFFED[1]                  |DIV2 |-----Flash  //
    //                                                                                          0xFFE9[3:0]         //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(enumClock == _M2PLL_CLK)
    {
        g_ucDelay5usN = (BYTE)(((DWORD)_M2PLL_CLK_MHZ / ucMcuDiv) & 0x000000FF);
    }
    else if(enumClock == _IOSC_CLK)
    {
        g_ucDelay5usN = (BYTE)(((DWORD)_INTERNAL_OSC_XTAL / ucMcuDiv / 1000) & 0x000000FF);
    }
    else // For Xtal
    {
        g_ucDelay5usN = (BYTE)(((DWORD)_EXT_XTAL / ucMcuDiv / 1000) & 0x000000FF);
    }

    /////////////////////////////////////////////
    // #define Delay5us(N)\                    //
    //         g_ucDelay5usI = N;\             //
    //         while(--g_ucDelay5usI)          //
    //                                         //
    // Formula (when Cache is disabled):       //
    //                                         //
    //              (24 + 32 + 80 * (N-1))     //
    //  DelayTime = ----------------------     //
    //                   Mcu Clk * 2           //
    //                                         //
    //       DelayTime * Mcu Clk * 2 + 24      //
    //  N =  ----------------------------      //
    //                   80                    //
    //                                         //
    // Formula (when Cache is enabled):        //
    //                                         //
    //              (52 + 12 * (N-1))          //
    //  DelayTime = ------------------         //
    //                 Mcu Clk                 //
    //                                         //
    //       DelayTime * Mcu Clk - 40          //
    //  N =  ------------------------          //
    //                12                       //
    /////////////////////////////////////////////

    // For Cache Disable Formula
    /*
    g_ucDelay5usN = ((WORD)(_HW_IIC_DELAY_TIME * g_ucDelay5usN * 2 + 24) / 8);
    g_ucDelay5usN = (g_ucDelay5usN + 5) / 10;

    if(g_ucDelay5usN == 0)
    {
        g_ucDelay5usN = 1;
    }
    */

    // For Cache Enable Formula
    if((WORD)_HW_IIC_DELAY_TIME * g_ucDelay5usN > 40)
    {
        g_ucDelay5usN = (((WORD)(_HW_IIC_DELAY_TIME * g_ucDelay5usN - 40) + 6) / 12);
    }
    else
    {
        g_ucDelay5usN = 2;
    }

    if(g_ucDelay5usN == 0)
    {
        g_ucDelay5usN = 2;
    }
}

#if(_SW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Software IIC Start
// Input Value  : ucSlaveAddr --> Slave Address
// Output Value : None
//--------------------------------------------------
BYTE ScalerMcuIICStart(BYTE ucSlaveAddr)
{
    BYTE ucTemp = 0;
    WORD usTimeOut = 6;

    PCB_SW_IIC_SCL_SET();
    PCB_SW_IIC_SDA_SET();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

    PCB_SW_IIC_SCL_CHK(ucTemp);

    while(ucTemp == _LOW)
    {
        if(usTimeOut > 0)
        {
            usTimeOut--;
            Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);
        }
        else
        {
            return _FAIL;
        }

        PCB_SW_IIC_SCL_CHK(ucTemp);
    }

    PCB_SW_IIC_SDA_CLR();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

    PCB_SW_IIC_SCL_CLR();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

    return ScalerMcuIICSendByte(ucSlaveAddr);
}

//--------------------------------------------------
// Description  : Software IIC Stop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICStop(void)
{
    PCB_SW_IIC_SDA_CLR();
    PCB_SW_IIC_SCL_SET();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

    PCB_SW_IIC_SDA_SET();
}

//--------------------------------------------------
// Description  : Software IIC Get Acknowledge
// Input Value  : None
// Output Value : ucAck --> 0: Ack / 1: Nack
//--------------------------------------------------
BYTE ScalerMcuIICGetAck(void)
{
    BYTE ucAck = 0;

    PCB_SW_IIC_SDA_SET();
    PCB_SW_IIC_SCL_SET();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

    PCB_SW_IIC_SDA_CHK(ucAck);

    PCB_SW_IIC_SCL_CLR();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

    PCB_SW_IIC_SDA_SET();

    return ucAck;
}

//--------------------------------------------------
// Description  : Software IIC Send Acknowledge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICSendAck(void)
{
    PCB_SW_IIC_SDA_CLR();
    PCB_SW_IIC_SCL_SET();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

    PCB_SW_IIC_SCL_CLR();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);
}

//--------------------------------------------------
// Description  : Software IIC Send No-Acknowledge
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIICSendNoAck(void)
{
    PCB_SW_IIC_SDA_SET();
    PCB_SW_IIC_SCL_SET();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

    PCB_SW_IIC_SCL_CLR();

    Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);
}

//--------------------------------------------------
// Description  : Software IIC Read 1 Byte
// Input Value  : None
// Output Value : ucValue --> Received Byte
//--------------------------------------------------
#pragma save
#pragma OT(8)
BYTE ScalerMcuIICGetByte(void)
{
    BYTE ucTemp = 0;
    BYTE ucCnt = 0;
    BYTE ucValue = 0;

    PCB_SW_IIC_SDA_SET();

    for(ucCnt = 0; ucCnt < 8; ucCnt++)
    {
        PCB_SW_IIC_SCL_SET();

        Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

        PCB_SW_IIC_SDA_CHK(ucTemp);

        ucValue = (ucValue << 1) | ucTemp;

        PCB_SW_IIC_SCL_CLR();

        Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);
    }

    return ucValue;
}
uint8_t i2c_receive_bytes(WORD usLength,uint8_t *pReadArray)
{
    // Save received data
    while(--usLength)
    {
        *pReadArray++ = ScalerMcuIICGetByte();

        ScalerMcuIICSendAck();
    }

    *pReadArray++ = ScalerMcuIICGetByte();

    ScalerMcuIICSendNoAck();

    ScalerMcuIICStop();

    return _SUCCESS;

}

#pragma restore

//--------------------------------------------------
// Description  : SoftWare IIC Write 1 Byte
// Input Value  : ucValue --> Data to be transmitted
// Output Value : None
//--------------------------------------------------
#pragma save
#pragma OT(8)
BYTE ScalerMcuIICSendByte(BYTE ucValue)
{
    BYTE ucCnt = 0;

    for(ucCnt = 0; ucCnt < 8; ucCnt++)
    {
        if((bit)(ucValue & _BIT7) == _HIGH)
        {
            PCB_SW_IIC_SDA_SET();
        }
        else
        {
            PCB_SW_IIC_SDA_CLR();
        }

        PCB_SW_IIC_SCL_SET();

        Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);

        PCB_SW_IIC_SCL_CLR();

        if((MCU_FFED_MCU_CONTROL & _BIT1) == _BIT1)
        {
            Delay5us(g_ucDelay5usN * _SW_IIC_CLK_DIV);
        }

        ucValue = ucValue << 1;
    }

    if(ScalerMcuIICGetAck() == _HIGH)
    {
        ScalerMcuIICStop();

        return _FAIL;
    }

    return _SUCCESS;
}
#pragma restore

//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICWriteStart(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr)
{
    if(ScalerMcuIICStart(ucSlaveAddr | _WRITE) == _FAIL)
    {
        return _FAIL;
    }

    switch(ucSubAddrLength)
    {
        case 1:

            if(ScalerMcuIICSendByte((BYTE)(usSubAddr)) == _FAIL)
            {
                return _FAIL;
            }

            break;

        case 2:

            if(ScalerMcuIICSendByte((BYTE)((usSubAddr & 0xFF00) >> 8)) == _FAIL)
            {
                return _FAIL;
            }
            else
            {
                if(ScalerMcuIICSendByte((BYTE)(usSubAddr)) == _FAIL)
                {
                    return _FAIL;
                }
            }

            break;

        default:

            break;
    }
    return _SUCCESS;
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICWritePolling(BYTE ucSlaveAddr)
{
    if(ScalerMcuIICStart(ucSlaveAddr | _WRITE) == _FAIL)
    {
        return _FAIL;
    }

    ScalerMcuIICStop();

    return _SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Read data from the selected device by Software IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucReadArray)
{
    if(usLength == 0)
    {
        return _FAIL;
    }

    // Write Slave address and Sub-address
    if(ScalerMcuIICWriteStart(ucSlaveAddr, ucSubAddrLength, usSubAddr) == _FAIL)
    {
        return _FAIL;
    }

    // Write Slave address to read
    if(ScalerMcuIICStart(ucSlaveAddr | _READ) == _FAIL)
    {
        return _FAIL;
    }

    // Save received data
    while(--usLength)
    {
        *pucReadArray++ = ScalerMcuIICGetByte();

        ScalerMcuIICSendAck();
    }

    *pucReadArray++ = ScalerMcuIICGetByte();

    ScalerMcuIICSendNoAck();

    ScalerMcuIICStop();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by Software IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit ScalerMcuIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, WORD usLength, BYTE *pucWriteArray)
{
    if(usLength == 0)
    {
        return _FAIL;
    }

    // Write Slave address and Sub-address
    if(ScalerMcuIICWriteStart(ucSlaveAddr, ucSubAddrLength, usSubAddr) == _FAIL)
    {
        return _FAIL;
    }

    // Send data
    while(usLength--)
    {
        if(ScalerMcuIICSendByte(*pucWriteArray++) == _FAIL)
        {
            return _FAIL;
        }
    }

    ScalerMcuIICStop();

    return _SUCCESS;
}
#pragma restore

#endif    // End of #if(_SW_IIC_SUPPORT == _ON)

#if(_HW_IIC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Hardware IIC Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIICInitial(void)
{
    // Reset IIC module
    MCU_FF55_I2CM_CR0 &= ~_BIT7;

    // Enable IIC module and disable TOR
    MCU_FF55_I2CM_CR0 |= _BIT7;
    MCU_FF55_I2CM_CR0 &= ~_BIT0;

    // Set TOR: time-out = TOR x 2 x ((FD10+1)/input clk)
    MCU_FF56_I2CM_CR1 = _HW_IIC_TOR;

    // Disable burst mode
    MCU_FF57_I2CM_CR2 = 0x00;

    // Clear interrupts
    MCU_FF58_I2CM_CR3 = 0x00;

    // Set fall time period count
    MCU_FF59_I2CM_STR0 = _HW_IIC_FTPC;

    // Set STA setup time period count
    MCU_FF5A_I2CM_STR1 = _HW_IIC_STA_SUGPIO_C;

    // Set SCL high period count
    MCU_FF5B_I2CM_STR2 = _HW_IIC_SHPC_14318K;

    // Set SCL low period count
    MCU_FF5C_I2CM_STR3 = _HW_IIC_SLPC_14318K;

    // Set frequency divisor: ref = xtal/(FD10+1)
    MCU_FF5F_I2CM_CCR = _HW_IIC_FD10_14318K;
}

//--------------------------------------------------
// Description  : Hardware IIC Clock Select
// Input Value  : Clock --> _EXT_XTAL_CLK/_IOSC_CLK
// Output Value : None
//--------------------------------------------------
void ScalerMcuHwIICSetFreqDiv(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // Set freq. divisor: ref = XTAL/(FD10+1) = 7.16M(ref should be approx 10MHz)
        MCU_FF5F_I2CM_CCR = _HW_IIC_FD10_14318K;

        // Set STA setup time period count
        MCU_FF5A_I2CM_STR1 = _HW_IIC_STA_SUGPIO_C;

        // Set SCL high period count
        MCU_FF5B_I2CM_STR2 = _HW_IIC_SHPC_14318K;

        // Set SCL low period count
        MCU_FF5C_I2CM_STR3 = _HW_IIC_SLPC_14318K;
    }
    else
    {
        // Set freq. divisor: ref = IOSC/(FD10+1) = 9M(ref should be approx 10MHz)
        MCU_FF5F_I2CM_CCR = _HW_IIC_FD10_28000K;

        // Set STA setup time period count
        MCU_FF5A_I2CM_STR1 = _HW_IIC_STA_SUGPIO_C;

        // Set SCL high period count
        MCU_FF5B_I2CM_STR2 = _HW_IIC_SHPC_28000K;

        // Set SCL low period count
        MCU_FF5C_I2CM_STR3 = _HW_IIC_SLPC_28000K;
    }
}

#if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Polling internal write cycle finish
// Input Value  : ucSlaveAddr  --> Slave address
// Output Value : Polling result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIICWritePolling(BYTE ucSlaveAddr, BYTE ucSubAddrLength, BYTE ucHwIICPinNum)
{
    BYTE ucSubAddress = 0x00;
    BYTE ucLength = 0;
    BYTE ucTimeOutCnt = _IIC_POLLING_TIME;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Set 1 byte for FRSIB
    MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);

    // Set no repeat start
    MCU_FF58_I2CM_CR3 &= ~(_BIT4 | _BIT3);

    // Load Slave Address to IIC Buffer
    MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

    MCU_FF55_I2CM_CR0 &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);

    switch(ucSubAddrLength)
    {
        case 0:

            break;

        case 1:

            // Set data length
            MCU_FF55_I2CM_CR0 |= ucLength << 1;

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(ucSubAddress);

            break;

        case 2:

            // Set data length
            MCU_FF55_I2CM_CR0 |= (ucLength + 1) << 1;

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSubAddress;

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSubAddress;

            break;

        default:

            break;
    }

    // IIC command Start
    MCU_FF55_I2CM_CR0 |= _BIT6;

    // Wait until Master Transmit Complete
    while((MCU_FF5D_I2CM_SR & 0x01) != 0x01)
    {
        ucTimeOutCnt--;

        Delay5us(g_ucDelay5usN);

        if(ucTimeOutCnt == 0x00)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
    }

    // Clear all flags
    MCU_FF5D_I2CM_SR |= 0x07;

    return _SUCCESS;
}
#endif // End of #if(_EEPROM_ACCESS_FUNCTION_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Read data from the selected device by IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                ucSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Reading result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    WORD usTimeOutCnt = 600;

    // Return fail if Data to be received is greater than IIC buffer size
    if(ucDataLength > _HW_IIC_BUFFER_SIZE)
    {
        return _FAIL;
    }

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    switch(ucSubAddrLength)
    {
        case 0:

            // Set 1 byte for FRSIB
            MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);

            // Set no repeat start
            MCU_FF58_I2CM_CR3 &= ~(_BIT4 | _BIT3);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        case 1:

            // Set 2 bytes for FRSIB
            MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);
            MCU_FF57_I2CM_CR2 |= _BIT0;

            // Set one repeat start
            MCU_FF58_I2CM_CR3 &= ~_BIT4;
            MCU_FF58_I2CM_CR3 |= _BIT3;

            // Load Slave Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        case 2:

            // Set 3 bytes for FRSIB
            MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);
            MCU_FF57_I2CM_CR2 |= _BIT1;

            // Set one repeat start
            MCU_FF58_I2CM_CR3 &= ~_BIT4;
            MCU_FF58_I2CM_CR3 |= _BIT3;

            // Load Slave Address to IIC Buffer
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)((usSubAddr & 0xFF00) >> 8);

            // Load Second Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Load Slave Address to receive data
            MCU_FF5E_I2CM_TD = ucSlaveAddr | _READ;

            break;

        default:

            break;
    }

    // Set data length
    MCU_FF55_I2CM_CR0 &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);
    MCU_FF55_I2CM_CR0 |= (ucDataLength - 1) << 1;

    // IIC command Start
    MCU_FF55_I2CM_CR0 |= _BIT6;

    // Wait until Master Receive Complete
    while((MCU_FF5D_I2CM_SR & 0x02) != 0x02)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            Delay5us(g_ucDelay5usN);
        }
    }

    // Save received data
    for(ucI = 0; ucI < ucDataLength; ucI++)
    {
        *pucReadArray = MCU_FF5E_I2CM_TD;
        pucReadArray++;
    }

    // Clear all flags
    MCU_FF5D_I2CM_SR |= 0x07;

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Write data to the selected device by IIC
// Input Value  : ucSlaveAddr  --> Slave address
//                usSubAddr    --> Start address of selected device
//                usLength     --> Numbers of data we want to read
//                pReadArray   --> Result array
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
#pragma save
#pragma OT(8)
bit ScalerMcuHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray, BYTE ucHwIICPinNum)
{
    BYTE ucI = 0;
    WORD usTimeOutCnt = 600;
    BYTE ucTempLength = 0;

    ScalerPinshareHwIICPin(ucHwIICPinNum);

    // Set 1 byte for FRSIB
    MCU_FF57_I2CM_CR2 &= ~(_BIT1 | _BIT0);

    // Set no repeat start
    MCU_FF58_I2CM_CR3 &= ~(_BIT4 | _BIT3);

    // Wait I2C Fifo Clk Switch to Mcu Clk
    while((MCU_FF5D_I2CM_SR & _BIT5) != _BIT5)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            Delay5us(g_ucDelay5usN);
        }
    }

    // Load Slave Address to IIC Buffer
    MCU_FF5E_I2CM_TD = ucSlaveAddr | _WRITE;

    MCU_FF55_I2CM_CR0 &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);

    if(ucDataLength > 16)
    {
        pData[0] = 16;
    }
    else
    {
        pData[0] = ucDataLength;
    }

    switch(ucSubAddrLength)
    {
        case 0:

            // Set data length
            ucTempLength = ((pData[0] - 1) << 1);

            break;

        case 1:

            // Load Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Set data length
            ucTempLength = (pData[0] << 1);

            break;

        case 2:

            // Load First Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)((usSubAddr & 0xFF00) >> 8);

            // Load Second Sub-Address to IIC Buffer
            MCU_FF5E_I2CM_TD = (BYTE)(usSubAddr);

            // Set data length
            ucTempLength = ((pData[0] + 1) << 1);

            break;

        default:

            break;
    }

    if(ucDataLength <= 16)
    {
        // Load data to IIC buffer for transmission
        for(ucI = 0; ucI < pData[0]; ucI++)
        {
            MCU_FF5E_I2CM_TD = *pucWriteArray;
            pucWriteArray++;
        }

        // Send IIC command Start
        MCU_FF55_I2CM_CR0 = 0xC0 + ucTempLength;
    }
    else
    {
        // Disable HW TOR
        MCU_FF55_I2CM_CR0 &= ~_BIT0;

        // Enable Burst Mode
        MCU_FF57_I2CM_CR2 |= _BIT6;

        // Calcualte Burst Command
        pData[1] = (ucDataLength / 16) + ((ucDataLength % 16) ? 1 : 0);

        for(pData[2] = 0; pData[2] < pData[1]; pData[2]++)
        {
            usTimeOutCnt = 600;

            // Wait I2C Fifo Clk Switch to Mcu Clk
            while((MCU_FF5D_I2CM_SR & _BIT5) != _BIT5)
            {
                if(usTimeOutCnt == 0)
                {
                    // Reset(Block) IIC module
                    MCU_FF55_I2CM_CR0 &= ~_BIT7;

                    // Enable IIC module
                    MCU_FF55_I2CM_CR0 |= _BIT7;

                    return _FAIL;
                }
                else
                {
                    usTimeOutCnt--;

                    Delay5us(g_ucDelay5usN);
                }
            }

            // Load data to IIC buffer for transmission
            for(ucI = 0; ucI < pData[0]; ucI++)
            {
                MCU_FF5E_I2CM_TD = *pucWriteArray;
                pucWriteArray++;
            }

            if(pData[2] != 0)
            {
                // Set data length
                ucTempLength = ((pData[0] - 1) << 1) & (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1);
            }

            // Set Length and First Burst Command Start, Must Keep FF55[6] = 1 until Burst Mode end
            MCU_FF55_I2CM_CR0 = 0xC0 + ucTempLength;

            // Update Remaider Data Length
            ucDataLength = ucDataLength - pData[0];

            if(ucDataLength > 16)
            {
                pData[0] = 16;
            }
            else
            {
                pData[0] = ucDataLength;
            }

            if(pData[2] == (pData[1] - 1))
            {
                // Disable Burst Write
                MCU_FF57_I2CM_CR2 &= ~_BIT6;

                // Burst write again
                MCU_FF5D_I2CM_SR |= (_BIT4 | _BIT3);

                break;
            }
            else if(pData[2] != 0)
            {
                // Burst write again
                MCU_FF5D_I2CM_SR |= (_BIT4 | _BIT3);
            }

            usTimeOutCnt = 600;

            // Wait into Burst Wait State
            while((MCU_FF5D_I2CM_SR & _BIT3) != _BIT3)
            {
                if(usTimeOutCnt == 0)
                {
                    // Reset(Block) IIC module
                    MCU_FF55_I2CM_CR0 &= ~_BIT7;

                    // Enable IIC module
                    MCU_FF55_I2CM_CR0 |= _BIT7;

                    return _FAIL;
                }
                else
                {
                    usTimeOutCnt--;

                    Delay5us(g_ucDelay5usN);
                }
            }
        }
    }

    usTimeOutCnt = 600;

    // Wait until Master Transmit Complete
    while((MCU_FF5D_I2CM_SR & 0x01) != 0x01)
    {
        if(usTimeOutCnt == 0)
        {
            // Reset(Block) IIC module
            MCU_FF55_I2CM_CR0 &= ~_BIT7;

            // Enable IIC module
            MCU_FF55_I2CM_CR0 |= _BIT7;

            return _FAIL;
        }
        else
        {
            usTimeOutCnt--;

            Delay5us(g_ucDelay5usN);
        }
    }

    // Clear all flags
    MCU_FF5D_I2CM_SR |= 0x07;

    return _SUCCESS;
}
#pragma restore

#endif  // End of #if(_HW_IIC_SUPPORT == _ON)

#if(_UART_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Write data to the selected device by UART
// Input Value  : ucValue --> Data to be send
// Output Value : Write result (Fail/Success)
//--------------------------------------------------
bit ScalerMcuUartWrite(BYTE ucValue)
{
    WORD usTimeOut = 1800;

    // Disable Serial Port IRQ
    ES = _DISABLE;

    // Clear Flag
    TI = 0;

    // Load Data to Serial Port Buffer
    SBUF = ucValue;

    do
    {
        Delay5us(g_ucDelay5usN);
    }
    while((TI == 0) && (--usTimeOut != 0));

    // Enable Serial Port IRQ
    ES = _ENABLE;

    return ((TI != 0) && (usTimeOut != 0)) ? _TRUE : _FALSE;
}
#endif

//--------------------------------------------------
// Description  : ISP Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuIspInitial(void)
{
    // Keep mcu peripheral(timer) running while mcu stopped by spi flash access
    MCU_FFEE_MCU_CLOCK_CONTROL |= _BIT6;
}

//--------------------------------------------------
// Description  : Low Power Consumption Setting For Mcu Module.
// Input Value  : enumPowAction
// Output Value : None
//--------------------------------------------------
void ScalerMcuPwmControl(EnumPowerStatus enumPowStatus)
{
    if(enumPowStatus == _POWER_STATUS_NORMAL)
    {
        // PWM output clock stop disable
        MCU_FFF2_PWM_I2C_CLOCK_STOP |= (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FFF2_PWM_I2C_CLOCK_STOP &= ~(((BYTE)_PWM5_EN << 5) | ((BYTE)_PWM4_EN << 4) | ((BYTE)_PWM3_EN << 3) | ((BYTE)_PWM2_EN << 2) | ((BYTE)_PWM1_EN << 1) | ((BYTE)_PWM0_EN));

        // PWM Output Enable
        MCU_FF48_PWM_EN &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FF48_PWM_EN |= (((BYTE)_PWM5_EN << 5) | ((BYTE)_PWM4_EN << 4) | ((BYTE)_PWM3_EN << 3) | ((BYTE)_PWM2_EN << 2) | ((BYTE)_PWM1_EN << 1) | ((BYTE)_PWM0_EN));

#if(_PWM_RST_BY_TCON == _ON)
        // Enable TCON
        ScalerTconEnable(_ON);

        // Enable PWM reset by TCON
        MCU_FF47_PWM_VS_CTRL |= _BIT6;
#endif
    }
    else if(enumPowStatus == _POWER_STATUS_SAVING)
    {
        // PWM Output Enable
        MCU_FF48_PWM_EN &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FF48_PWM_EN |= (((BYTE)_PWM5_PSAV_EN << 5) | ((BYTE)_PWM4_PSAV_EN << 4) | ((BYTE)_PWM3_PSAV_EN << 3) | ((BYTE)_PWM2_PSAV_EN << 2) | ((BYTE)_PWM1_PSAV_EN << 1) | ((BYTE)_PWM0_PSAV_EN));

        // PWM output clock stop disable
        MCU_FFF2_PWM_I2C_CLOCK_STOP |= (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FFF2_PWM_I2C_CLOCK_STOP &= ~(((BYTE)_PWM5_PSAV_EN << 5) | ((BYTE)_PWM4_PSAV_EN << 4) | ((BYTE)_PWM3_PSAV_EN << 3) |
                                         ((BYTE)_PWM2_PSAV_EN << 2) | ((BYTE)_PWM1_PSAV_EN << 1) | ((BYTE)_PWM0_PSAV_EN));
    }
    else if(enumPowStatus == _POWER_STATUS_OFF)
    {
        // PWM Output Disable when Power Down(or enable by define)
        MCU_FF48_PWM_EN &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FF48_PWM_EN |= (((BYTE)_PWM5_PDOW_EN << 5) | ((BYTE)_PWM4_PDOW_EN << 4) | ((BYTE)_PWM3_PDOW_EN << 3) | ((BYTE)_PWM2_PDOW_EN << 2) | ((BYTE)_PWM1_PDOW_EN << 1) | ((BYTE)_PWM0_PDOW_EN));

        // PWM Output Clock Stop Enable when Power Down(or enable by define)
        MCU_FFF2_PWM_I2C_CLOCK_STOP |= (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FFF2_PWM_I2C_CLOCK_STOP &= ~(((BYTE)_PWM5_PDOW_EN << 5) | ((BYTE)_PWM4_PDOW_EN << 4) | ((BYTE)_PWM3_PDOW_EN << 3) |
                                         ((BYTE)_PWM2_PDOW_EN << 2) | ((BYTE)_PWM1_PDOW_EN << 1) | ((BYTE)_PWM0_PDOW_EN));
    }
    else
    {
        // PWM Output Disable
        MCU_FF48_PWM_EN &= ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

        // PWM Output Clock Stop Enable
        MCU_FFF2_PWM_I2C_CLOCK_STOP |= (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
    }
}

#if(_FLASH_PARTITION_TYPE == _FLASH_PARTITION_BOOT)
//--------------------------------------------------
// Description  : MCU boot code initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuBootInitial(void)
{
    // Disable watchdog timer
    MCU_FFEA_WATCHDOG_TIMER &= ~(_BIT7);

    // Enable global XRAM and XFR, use Pbank_switch, enable bankswitching function
    MCU_FFFC_BANK_SWICH_CONTROL |= (_BIT3 | _BIT2 | _BIT1 | _BIT0);

    // Flash clock divider and mcu clock divider
    ScalerMcuFlashClockDiv(_FLASH_CLK_IN_DIV);
    ScalerMcuClockDiv(_MCU_CLK_DIV);

    // Disable all interrupts
    IE = 0x00;
}
#endif

//--------------------------------------------------
// Description  : Cache Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerMcuCacheInitial(void)
{
    // Reset Cache
    MCU_FDA1_CACHE_OPTION |= _BIT0;
    MCU_FDA1_CACHE_OPTION &= ~_BIT0;

    // Disable Common Bank Function
    MCU_FDA1_CACHE_OPTION &= ~_BIT1;

    // Enable Cache
    MCU_FDA0_CACHE_FUNCTION |= _BIT0;
}

//--------------------------------------------------
// Description  : DDCCI switch DDC Port
// Input Value  : enumMode --> Debug or DDCCI Mode
//                ucInputPort --> Input Port Type
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcciSwitchPort(EnumDDCCIDebugMode enumMode)
{
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
    // Force to debug mode when debug message is enable
    enumMode = _DEBUG_MODE;
#endif

    ScalerDebugSelectDDCCIDebugMode(enumMode);

    if(enumMode == _DDCCI_MODE)
    {
        // Set slave address for DDCCI
        MCU_FF23_IIC_SET_SLAVE = 0x6E;

        // Disable STOP_I, Enable D_IN_I, SUB_I interrupts
        MCU_FF28_IIC_IRQ_CONTROL &= ~_BIT4;
        MCU_FF28_IIC_IRQ_CONTROL |= _BIT2 | _BIT1;

#if(_MULTI_DISPLAY_MAX >= 0x02)
        // Set slave address for DDCCI
        MCU_FE87_IIC_1_SET_SLAVE = 0x6E;

        // Enable D_IN_I, SUB_I interrupts
        MCU_FE8C_IIC_1_IRQ_CONTROL |= _BIT2 | _BIT1;
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
        // Set slave address for DDCCI
        MCU_FE95_IIC_2_SET_SLAVE = 0x6E;

        // Enable D_IN_I, SUB_I interrupts
        MCU_FE9A_IIC_2_IRQ_CONTROL |= _BIT2 | _BIT1;

        // Set slave address for DDCCI
        MCU_FEA4_IIC_3_SET_SLAVE = 0x6E;

        // Enable D_IN_I, SUB_I interrupts
        MCU_FEA9_IIC_3_IRQ_CONTROL |= _BIT2 | _BIT1;
#endif
    }
    else
    {
        // Set slave address for debug tool
        MCU_FF23_IIC_SET_SLAVE = 0x6A;

        // Disable STOP_I, D_IN_I, SUB_I interrupts
        MCU_FF28_IIC_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        // Enable STOP_I, D_IN_I, SUB_I interrupts
        MCU_FF28_IIC_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;

#if(_DEBUG_DDC_CHANNEL_SEL == _DDC5)
        // DDC from DDC5 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= (_BIT2 | _BIT1);
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC4)
        // DDC from DDC4 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= (_BIT2 | _BIT0);
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC3)
        // DDC from DDC3 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= _BIT2;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC2)
        // DDC from DDC2 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= (_BIT1 | _BIT0);
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC1)
        // DDC from DDC1 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= _BIT1;
#elif(_DEBUG_DDC_CHANNEL_SEL == _DDC0)
        // DDC from DDC0 channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
        MCU_FF22_IIC_CH_SEL |= _BIT0;
#else
        // DDC from VGA_DDC channel
        MCU_FF22_IIC_CH_SEL &= ~(_BIT2 | _BIT1 | _BIT0);
#endif

        //////////////////////////////////////////////////////////////////
        /////////////////////Disable DDCCI 1~3 ///////////////////////////
        //////////////////////////////////////////////////////////////////
        // Config ddc-ci address to no used addaress
        MCU_FE87_IIC_1_SET_SLAVE = 0x3C;
        MCU_FE95_IIC_2_SET_SLAVE = 0x3C;
        MCU_FEA4_IIC_3_SET_SLAVE = 0x3C;

        // Disable all ddc interrupt
        MCU_FE8C_IIC_1_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FE9A_IIC_2_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
        MCU_FEA9_IIC_3_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);

        // Config none ddc port
        MCU_FE86_IIC_1_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
        MCU_FE94_IIC_2_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
        MCU_FEA3_IIC_3_CH_SEL |= (_BIT2 | _BIT1 | _BIT0);
    }
}

#if(_D6_INPUT_PORT_TYPE != _D6_NO_PORT)
//--------------------------------------------------
// Description  : D0/D1 DDC RAM layout selected
// Input Value  : enumDdcRamSel --> D0 or D1 DDCRAM; enumDdcAddr --> Point to Top or bottom address
// Output Value : None
//--------------------------------------------------
void ScalerMcuDdcRamEDIDAddrSelect(EnumD0D1DDCRAMSelect enumDdcRamSel, EnumDDCAddrType enumDdcAddr)
{
    switch(enumDdcRamSel)
    {
        case _D0_DDCRAM:

            if(enumDdcAddr == _DDCRAM_TOP_ADDR)
            {
                MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT0;
            }
            else
            {
                MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT0;
            }

            break;

        case _D1_DDCRAM:

            if(enumDdcAddr == _DDCRAM_TOP_ADDR)
            {
                MCU_FEB1_DDCRAM_ST_ADDRESS &= ~_BIT1;
            }
            else
            {
                MCU_FEB1_DDCRAM_ST_ADDRESS |= _BIT1;
            }

            break;

        default:
            break;
    }
}
#endif
