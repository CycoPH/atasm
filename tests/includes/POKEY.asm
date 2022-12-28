; POKEY register list
; For atasm
; Ken Jennings
;=================================================
; Hardware Registers
;
AUDF1 = $D200 ; Audio channel 1 Frequency
AUDF2 = $D202 ; Audio channel 2 Frequency
AUDF3 = $D204 ; Audio channel 3 Frequency
AUDF4 = $D206 ; Audio channel 4 Frequency
;
AUDC1 = $D201 ; Audio channel 1 Control
AUDC2 = $D203 ; Audio channel 2 Control
AUDC3 = $D205 ; Audio channel 3 Control
AUDC4 = $D207 ; Audio channel 4 Control
;
AUDCTL = $D208 ; Audio Control
;
POT0 = $D200 ; (Read) Potentiometer (paddle) 0 
POT1 = $D201 ; (Read) Potentiometer (paddle) 1 
POT2 = $D202 ; (Read) Potentiometer (paddle) 2 
POT3 = $D203 ; (Read) Potentiometer (paddle) 3 
POT4 = $D204 ; (Read) Potentiometer (paddle) 4 
POT5 = $D205 ; (Read) Potentiometer (paddle) 5 
POT6 = $D206 ; (Read) Potentiometer (paddle) 6 
POT7 = $D207 ; (Read) Potentiometer (paddle) 7 
;
ALLPOT = $D208 ; (Read) Read 8 line POT port state
POTGO =  $D20B ; Start the POT scan sequence
;
STIMER = $D209 ; Start timers
KBCODE = $D209 ; (Read) Keyboard code
RANDOM = $D20A ; (Read) Random number
;
SKREST = $D20A ; Reset Serial Status (SKSTAT)
SEROUT = $D20D ; Serial port data output
SERIN =  $D20D ; (Read) Serial port data input
SKCTL =  $D20F ; Serial Port Control
SKSTAT = $D20F ; (Read) Serial port status
;
IRQEN = $D20E ; Interrupt Request Enable
IRQST = $D20E ; (Read) IRQ Status
;=================================================
; Shadow Registers for Hardware Registers
;
PADDL0 = $0270 ; POT0
PADDL1 = $0270 ; POT1
PADDL2 = $0270 ; POT2
PADDL3 = $0270 ; POT3
PADDL4 = $0270 ; POT4
PADDL5 = $0270 ; POT5
PADDL6 = $0270 ; POT6
PADDL7 = $0270 ; POT7
;
CH = $02FC ; KBCODE
;
POKMSK = $10 ; IRQEN
;
SSKCTL = $0232 ; SKCTL
;=================================================
; Important Bit Positions
;
; AUDC 
MASK_AUD_NOISE  = ~00011111
MASK_AUD_FORCE  = ~11101111
MASK_AUD_VOLUME = ~11110000
;
AUD_NOISE =       ~11100000
AUD_FORCE =       ~00010000
AUD_VOLUME =      ~00001111
;
NOISE_5_BIT_17_BIT_POLY = ~00000000
NOISE_5_BIT_POLY =        ~00100000
NOISE_5_BIT_4_BIT_POLY =  ~01000000
NOISE_5_BIT_POLY_2 =      ~01100000 ; Duplicate of "5 bit poly"
NOISE_17_BIT_POLY =       ~10000000
NOISE_NO_POLY_PURE =      ~10100000
NOISE_4_BIT_POLY =        ~11000000
NOISE_NO_POLY_PURE_2 =    ~11100000 ; Duplicate of "No poly pure"
;
;AUDCTL
MASK_AUDCTL_POLY    =     ~01111111 ; 17 or 9 bit poly
MASK_AUDCTL_CH1_SYS =     ~10111111 ; Channel 1, 64KHz or system CPU clock (1.79Mhz NTSC)
MASK_AUDCTL_CH3_SYS =     ~11011111 ; Channel 3, 64KHz or system CPU clock (1.79Mhz NTSC)
MASK_AUDCTL_16_BIT_2_1 =  ~11101111 ; Tie channels 2 and 1 for 16-bit resolution
MASK_AUDCTL_16_BIT_4_3 =  ~11110111 ; Tie channels 4 and 3 for 16-bit resolution
MASK_AUDCTL_HIPASS_1_3 =  ~11111011 ; High pass filter channel 1 by channel 3
MASK_AUDCTL_HIPASS_2_4 =  ~11111101 ; High pass filter channel 2 by channel 4
MASK_AUDCTL_64_OR_15KHZ = ~11111110 ; Use Clock 64Khz or 15Khz
;
AUDCTL_POLY_17 =        ~00000000
AUDCTL_POLY_9  =        ~10000000
AUDCTL_CH1_64  =        ~00000000
AUDCTL_CH1_SYS =        ~01000000
AUDCTL_CH3_64  =        ~00000000
AUDCTL_CH3_SYS =        ~00100000
AUDCTL_16_BIT_2_1_OFF = ~00000000
AUDCTL_16_BIT_2_1_ON =  ~00010000
AUDCTL_16_BIT_4_3_OFF = ~00000000
AUDCTL_16_BIT_4_3_ON =  ~00001000
AUDCTL_HIPASS_1_3_OFF = ~00000000
AUDCTL_HIPASS_1_3_ON =  ~00000100
AUDCTL_HIPASS_2_4_OFF = ~00000000
AUDCTL_HIPASS_2_4_ON =  ~00000010
AUDCTL_CLOCK_64KHZ =    ~00000000
AUDCTL_CLOCK_15KHZ =    ~00000001
;
;ALLPOT
MASK_ALLPOT_PADDLE7 = ~01111111
MASK_ALLPOT_PADDLE6 = ~10111111
MASK_ALLPOT_PADDLE5 = ~11011111
MASK_ALLPOT_PADDLE4 = ~11101111
MASK_ALLPOT_PADDLE3 = ~11110111
MASK_ALLPOT_PADDLE2 = ~11111011
MASK_ALLPOT_PADDLE1 = ~11111101
MASK_ALLPOT_PADDLE0 = ~11111110
;
ALLPOT_PADDLE7 = ~10000000
ALLPOT_PADDLE6 = ~01000000
ALLPOT_PADDLE5 = ~00100000
ALLPOT_PADDLE4 = ~00010000
ALLPOT_PADDLE3 = ~00001000
ALLPOT_PADDLE2 = ~00000100
ALLPOT_PADDLE1 = ~00000010
ALLPOT_PADDLE0 = ~00000001
;
;SKCTL
MASK_SERIAL_BREAK =   ~01111111
MASK_SERIAL_MODE =    ~10001111
MASK_SERIAL_2TONE =   ~11110111
MASK_FAST_POT_SCAN =  ~11111011
MASK_ENABLE_KB_SCAN = ~11111101
MASK_KB_DEBOUNCE =    ~11111110
;
SERIAL_BREAK = ~10000000
SERIAL_MODE0 = ~00000000 ; Input Clock External.            Output Clock External.          Bidirectional Clock Input.
SERIAL_MODE1 = ~00010000 ; Input Clock Channel 3+4 (async). Output Clock External.          Bidirectional Clock Input.
SERIAL_MODE2 = ~00100000 ; Input Clock Channel 4.           Output Clock Channel 4.         Bidirectional Clock Output Channel 4.
SERIAL_MODE3 = ~00110000 ; Input Clock Channel 3+4 (async). Output Clock Channel 4 (async). Bidirectional Clock Input.
SERIAL_MODE4 = ~01000000 ; Input Clock External.            Output Clock Channel 4.         Bidirectional Clock Input.
SERIAL_MODE5 = ~01010000 ; Input Clock Channel 3+4 (async). Output Clock Channel 4 (async). Bidirectional Clock Input.
SERIAL_MODE6 = ~01100000 ; Input Clock Channel 4.           Output Clock Channel 2.         Bidirectional Clock Output Channel 4.
SERIAL_MODE7 = ~01110000 ; Input Clock Channel 3+4 (async). Output Clock Channel 2.         Bidirectional Clock Input.
;
SERIAL_2TONE = ~00001000 ; 1 and 0 bits are audio set by timers 1 and 2
;
FAST_POT_SCAN_OFF = ~00000000
FAST_POT_SCAN_ON =  ~00000100
DISABLE_KB_SCAN =   ~00000000
ENABLE_KB_SCAN =    ~00000010
KB_DEBOUNCE_OFF =   ~00000000
KB_DEBOUNCE_ON =    ~00000001
;
;SKSTAT
MASK_SERIAL_FRAME_ERROR =   ~01111111
MASK_SERIAL_INPUT_OVERRUN = ~10111111
MASK_KEYBOARD_OVERRUN =     ~11011111
MASK_SERIAL_DATA_READY =    ~11101111
MASK_SHIFT_KEY_PRESSED =    ~11110111
MASK_LAST_KEY_HELD =        ~11111011
MASK_SERIAL_INPUT_BUSY =    ~11111101
;
SERIAL_FRAME_NO_ERROR =   ~00000000
SERIAL_FRAME_ERROR =      ~10000000
SERIAL_NO_INPUT_OVERRUN = ~00000000
SERIAL_INPUT_OVERRUN =    ~01000000
KEYBOARD_NO_OVERRUN =     ~00000000
KEYBOARD_OVERRUN =        ~00100000
SERIAL_DATA_NOT_READY =   ~00000000
SERIAL_DATA_READY =       ~00010000
SHIFT_KEY_NOT_PRESSED =   ~00000000
SHIFT_KEY_PRESSED =       ~00001000
LAST_KEY_NOT_HELD =       ~00000000
LAST_KEY_HELD =           ~00000100
SERIAL_INPUT_NOT_BUSY =   ~00000000
SERIAL_INPUT_BUSY =       ~00000010
;
;IRQEN and IRQST
MASK_IRQ_TIMER1 =           ~11111110
MASK_IRQ_TIMER2 =           ~11111101
MASK_IRQ_TIMER4 =           ~11111011
MASK_IRQ_SERIAL_OUT_DONE =  ~11110111
MASK_IRQ_SERIAL_OUT_READY = ~11101111
MASK_IRQ_SERIAL_IN_READY =  ~11011111
MASK_IRQ_NORMAL_KEY_PRESS = ~10111111
MASK_IRQ_BREAK_PRESSED =    ~01111111
;
IRQ_TIMER1_OFF =           ~00000000
IRQ_TIMER1_ON =            ~00000001
IRQ_TIMER2_OFF =           ~00000000
IRQ_TIMER2_ON =            ~00000010
IRQ_TIMER4_OFF =           ~00000000
IRQ_TIMER4_ON =            ~00000100
IRQ_SERIAL_OUT_NOT_DONE =  ~00000000
IRQ_SERIAL_OUT_DONE =      ~00001000
IRQ_SERIAL_OUT_NOT_READY = ~00000000
IRQ_SERIAL_OUT_READY =     ~00010000
IRQ_SERIAL_IN_NOT_READY =  ~00000000
IRQ_SERIAL_IN_READY =      ~00100000
IRQ_NO_KEY_PRESS =         ~00000000
IRQ_NORMAL_KEY_PRESS =     ~01000000
IRQ_BREAK_NOT_PRESSED =    ~00000000
IRQ_BREAK_PRESSED =        ~10000000
