    // Start modulation length
    0x1B,                           // P23_A0_IR_PSR0

    // "0"/"1" modulation length
    0x1B,                           // P23_A1_IR_PSR1

    // "0" silence length
    0x1B,                           // P23_A2_IR_PSR2

    // "1" silence length
    0x37,                           // P23_A3_IR_PSR3

    // Reserved------------
    0x00,                           // P23_A4_IR_PER0

    // Debounce
    0x03,                           // P23_A5_IR_PER1

    // Repeat silence Default 0x00
    0x00,                           // P23_A6_IR_PER2

    // Start silence length
    0x06,                           // P23_A7_IR_PER3

    // Idle time
    0xFF,                           // P23_A8_IR_SF0

    // One command time
    0x41,                           // P23_A9_IR_SF1

    //----------------------------------------------

    // Time between 2 commands
    0x14,                           // P23_AE_IR_DPIR2
    0x1E,                           // P23_AF_IR_DPIR3

    // _BIT7 IR soft reset
    0x00,                           // P23_B0_IR_CR0

    // _BIT7 Panasonic 48bit enable; _BIT5~_BIT0 48bit Extended data number
    0x00,                           // P23_B1_IR_CR1

    // _BIT3 Modulation Length Adjustable Enable; _BIT1 IR RX Endian Select; Ohters Raw mode settings(default 0x00)
    (_BIT3),                        // P23_B2_IR_CR2

    // _BTI7 Length mode; _BIT6 Enable burst; _BIT4~_BIT0 data bits
    (_BIT7 | _BIT6 | 0x0B),         // P23_B3_IR_CR3

    //----------------------------------------------

    // Start modulation up level
    0x25,                           // P23_D0_IR_PSR_UP0

    // "0"/"1" modulation length up level
    0x32,                           // P23_D1_IR_PSR_UP1

    // "0" silence length up level
    0x32,                           // P23_D2_IR_PSR_UP2

    // "1" silence length up level
    0x4B,                           // P23_D3_IR_PSR_UP3

    // Reserved------------
    0x00,                           // P23_D4_IR_PER_UP0

    // Reserved------------
    0x00,                           // P23_D5_IR_PER_UP1

    // Repeat length up level Default 0xFF
    0xFF,                           // P23_D6_IR_PER_UP2

    // Start silence length up level
    0x0C,                           // P23_D7_IR_PER_UP3

    //----------------------------------------------

    // BIT1 Toshiba_en; BIT0 Philip RC6_en
    0x00,                           // P23_DA_IR_CTRL_RC62

    // RC6 mode Trailer Bit Length
    0x00,                           // P23_DB_IR_CTRL_RC63
