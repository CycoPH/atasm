;=================================================
; OS memory and vectors
; For atasm
; Ken Jennings
;=================================================

;=================================================
; Use the ANTIC/GTIA/POKEY/PIA files for shadow
; register declarations.
;=================================================

;=================================================
; Most of the first half of Page Zero is claimed
; by the OS.  The second half is for the cartridge
; ROM, with part used for the Floating point 
; package.
;
; If a cartridge is not inserted then the Page Zero
; space for the cartridge is available for any 
; machine language program.   
;
; Likewise, if the floating-point package will not 
; be used then the FP registers and working area 
; can be treated as free for use by a machine 
; language program.
;=================================================

;=================================================
; OS and Cartridge Page 0
;=================================================
LINZBS = $00 ; word

CASINI = $02 ; word, Cassette initialization vector (and trap RESET. See $09).
RAMLO =  $04 ; word, power up memory test.  Disk boot address.

CTAFLG = $06 ; nonzero value means Left/A cartridge present
CTBFLG = $07 ; nonzero value means Right/B  cartridge present

WARMST = $08 ; Warmstart flag. 0 = powerup in progress. $FF normal reset occurred.
BOOT =   $09 ; Boot status. 0 = no boot.  
	; 1 = disk boot OK.  do reset via DOSVEC
	; 2 = cassette boot OK. do reset via CASINI
	; 3 = both successful. (trap reset via CASINI).

DOSVEC = $0A ; word. Entry vector for DOS (actually to start DUP.SYS).
DOSINI = $0C ; word. Init address for DOS or Cassette RUN address. (also trap RESET with this).

APPMHI = $0E ; word. Application high memory in use.

; POKMSK = $10 in POKEY.asm

BRKKEY = $11 ; 0 = Break pressed.  

; Real Time Clock incremented during the vertical blank.
; This is three addresses $12, $13, and $14.
; The value of $14 is incremented every vertical blank.
; When the value of $14 reaches $FF on the next increment it rolls 
; over to $00 and then the value of $13 increments.
; $14 rollover/$13 increment occurs approximately every 4.27 seconds.
; Likewise, when the value if $13 reaches $FF and it rolls 
; over to $00,then the value of $12 increments.
; $13 rollover/$12 increment occurs approximately every 18.2 minutes.
; Jiffy count / 59.92334 for seconds.
RTCLOK =   $12 ; and $13, and $14.  
RTCLOK60 = $14 ; incremented every jiffy/frame.

BUFADR = $15 ; word.  temporary address of disk buffer
ICCOMT = $17 ; CIO command.
DSKFMS = $18 ; word. File Management System vector.
DSKUTL = $1A ; word. Disk Utilities pointer.

PTIMOT = $1C ; printer timeout.  approx 64 second per 60 values.
PBPNT =  $1D ; Printer buffer pointer.  index into buffer.
PBUFSZ = $1E ; Printer buffer size.
PTEMP =  $1F ; Temporary printer value used by print handler.

; Zero Page copy of CIO's IOCB
ICHIDZ = $20 ; Handler Index
ICDNOZ = $21 ; Device or drive number
ICCOMZ = $22 ; Command
ICSTAZ = $23 ; IOCB status result
ICBALZ = $24 ; Buffer address (lo byte)
ICBAHZ = $25 ; Buffer address (hi byte)
ICPTLZ = $26 ; Put Byte rouotine address (lo byte)
ICPTHZ = $27 ; Put Byte rouotine address (hi byte)
ICBLLZ = $28 ; Buffer length (lo byte)
ICBLHZ = $29 ; Buffer length (hi byte)
ICAX1Z = $2A ; Aux byte 1 (open parameters)
ICAX2Z = $2B ; Aux byte 2
ICAX3Z = $2C ; Aux byte 3 (BASIC Note/Point)
ICAX4Z = $2D ; Aux byte 4 (BASIC Note/Point)
ICAX5Z = $2E ; Aux byte 5
ICAX6Z = $2F ; Aux byte 6

STATUS = $30 ; SIO status
CHKSUM = $31 ; SIO data frame checksum.

BUFRLO = $32 ; SIO and DCB address of data to send or receive (lo byte)
BUFRHI = $33 ; SIO and DCB address of data to send or receive (hi byte)
BFENLO = $34 ; SIO and DCB address after BUFRLO/BUFRHI  (lo byte)
BFENHI = $35 ; SIO and DCB address after BUFRLO/BUFRHI  (hi byte)

CRETRY = $36 ; Command frame retries.  Usually $0D.
DRETRY = $37 ; Device retries.  Usually $01.

BUFRFL = $38 ; Flag buffer full. $FF is full.
RECVDN = $39 ; Flag receive done. $FF is done.
XMTDON = $3A ; Flag transmit done. $FF is done.
CHKSNT = $3B ; Flag checksum sent. $FF is sent. $00 is not sent.
NOCKSM = $3C ; Flag $00 = checksum follows data.  not zero = no checksum.

BPTR =   $3D ; Index to data in cassette buffer. 
FTYPE =  $3E ; Gap between cassette blocks. $01 to $7F = normal. $80 to $00 = short gaps.
FEOF =   $3F ; EOF for cassette. $00 = No EOF.  !$00 = EOF detected.
FREQ =   $40 ; Number of beeps for cassette start.  1 = Play.  2 = Record.
SOUNDR = $41 ; Play I/O sounds to speaker. 0 = silence.  !0 = I/O sound.

; Critical I/O flag.  
; Set to stop some automated timers and updates.
;  $00 = Normal behavior. 
; !$00 = Critical I/O mode.
; When CRITIC is set (non-zero) the following activities change:
; Stage 2/Deferred Vertical Blank Interrupt STOPS.
; (Stage 1/Immediate Vertical Blank Interrupt continues.)
; Software Timers 2, 3, 4, and 5 stop.
; Keyboard repeat disabled.
CRITIC = $42 ;  

FMZSPG = $43 ; 7 bytes up to $49. Disk FMS page 0 temporary registers (below)
ZBUFP =  $43 ; word.  Pointer to filename.
ZDRVA =  $45 ; word. Drive pointer/sector temporary value.
ZSBA =   $47 ; word. temporary sector pointer.
ERRNO =  $49 ; Disk I/O error.  FMS initializes to $9F.

CKEY =   $4A ; Cassette Cold Start to boot cassette.  Set by holding START key.
CASSBT = $4B ; Flag Cassette Boot. 0 = cassette boot unsuccessful.

DSTAT =  $4C ; status from S: handler. 

; Atari's "Attract" mode.
; After no keyboard input for several minutes the Atari OS cycles the 
; colors to prevent CRT image burn-in.  Reset this to 0 periodically
; to prevent the OS engaging the attract mode.
ATRACT = $4D

; Dark attract mask. Set to $FE/254 when attract mode is not active.
; Set to $F6/246 when attract mode is active.  This masks the 
; color lunminance bits to make screen colors stay below 50% 
; brighness. 
DRKMSK = $4E

; Color shift mask When attract mode is on the color registers are
; exclusive-OR's with the values in $4e and $4f  during the OS's 
; stage two vertical blank interrupt.  (see RTCLOK)
; When set to zero and value of DRKMSK is $f6/246, the luminance 
; is reduced 50%. COLRSH contains the value of RTCLOK+1 which is 
; incremented approximately each 4.27 seconds causing the colors
; to cycle at that period of time.       
COLRSH = $4F

TEMP =   $50 ; S: temporary value. (write character to screen)
HOLD1 =  $51 ; S: temporary value. (lines for Display List)

LMARGN = $52 ; E: left margin of GR.0 text mode and text windows
RMARGN = $53 ; E: right margin of GR.0 text mode and text windows
ROWCRS = $54 ; S: current cursor row (Y) 
COLCRS = $55 ; word.  S: current cursor column (X)

DINDEX = $57 ; S: current screen text/graphics mode
SAVMSC = $58 ; word. Address of first byte of screen memory.

OLDROW = $5A ; Previous cursor row from $54. Used for Drawto and Fill
OLDCOL = $5B ; word. Previous cursor column from $55/$56. Used for Drawto and Fill
OLDCHR = $5D ; Prior value of character at cursor
OLDADR = $5E ; word. memory location of cursor.

NEWROW = $60 ; Destination row for Drawto and Fill.
NEWCOL = $62 ; word. Destination column for Drawto and Fill.
LOGCOL = $64 ; Logical line cursor column.
ADRESS = $65 ; word. S: Temp address for Display List, copy of SAVMSC, etc.

MLTTMP = $66 ; word. Temp value for S: and in OPEN
SAVADR = $68 ; word. S: temporary value. 

RAMTOP = $6A ; First page after end of usable memory.

BUFCNT = $6B ; E: temp logical line size.
BUFSTR = $6C ; word. E: temp value

BITMSK = $6E ; S: bit mapping value
SHFAMT = $6F ; S: pixel shift amount per graphics mode
ROWAC =  $70 ; word. S: temporary row value
COLAC =  $72 ; word. S: temporary column value

ENDPT =  $74 ; word.  S: end point for Drawto.  Copy of DELTAR or DELTAC

DELTAR = $76 ; S: ABS( NEWROW - ROWCRS )
DELTAC = $77 ; word.  S: ABS( NEWCOL - COLCRS )
ROWINC = $79 ; S: Row +/- (+1 or -1) 0 is down.  $FF is up.
COLINC = $7A ; S: Column +/- (+1 or -1) 0 is right, $FF is left.

SWPFLG = $7B ; S: text window swap control. 0 = graphics. $FF = text window.
HOLDCH = $7C ; S: byte value for shifting.
INSDAT = $7D ; S: temporary character value
COUNTR = $7E ; word. S: Loop control for line drawing. Value of DELTAR or DELTAC.

;=================================================
; Cartridge-specific Page 0 - $7F to $D1
;=================================================

;=================================================
; Atari BASIC/OSS BASIC XL values Page 0
;=================================================
LOMEM  = $80 ; word. BASIC start of memory.

VNTP   = $82 ; word. BASIC Variable Name Table Pointer.
VNTD   = $84 ; word. BASIC Variable Name Table End address (Dummy) 
VVTP   = $86 ; word. BASIC Variable Value Table Pointer.

STMTAB = $88 ; word. BASIC Start of Statements/user's BASIC program.
STMCUR = $8A ; word. BASIC pointer to current statement.

STARP  = $8C ; word. BASIC String and Array table pointer.
RUNSTK = $8E ; word. BASIC Pointer to GOSUB/FOR-NEXT stack.

MEMTP =  $90 ; word. BASIC pointer to end of user BASIC program.

STOPLN = $92 ; word. BASIC line number where execution stopped due to Break key or error.
PROMPT = $C2 ; Input prompt character.

ERSAVE = $C3 ; BASIC error code for Stop or Trap.
COLOR =  $C8 ; color for Plot or Drawto. (copied to $2F)

PTABW =  $C9 ; BASIC tab width - number of columns between tab stops.

;=================================================
; OS Floating Point Library
;=================================================
FR0 =    $D4 ; float.  Floating point register and USR return value to BASIC.
FRE =    $DA ; float.  Floating point register (extra).
FR1 =    $E0 ; float.  Floating point register 1.
FR2 =    $E6 ; float.  Floating point register 2.
FRX =    $EC ; Floating Point spare value
EEXP =   $ED ; Floating Point Exponent
NSIGN =  $EE ; Floating Point Sign.
ESIGN =  $EF ; Floating Point Sign of exponent.
FCHRFL = $F0 ; Flag for first character
DIGRT =  $F1 ; Digits to the right of the decimal.
CIX =    $F2 ; current character input index. Offset into INBUFF
INBUFF = $F3 ; word. input for text to BCD conversion.  output at LBUFF
ZTEMP1 = $F5 ; word. Floating point temporary register.
ZTEMP4 = $F7 ; word. Floating point temporary register.
ZTEMP3 = $F9 ; word. Floating point temporary register.
RADFLG = $FB ; or DEGFLG.  0 = radians.  6 = degrees.
FLPTR =  $FC ; word. Pointer to first Floating Point number for operation..
FPTR2 =  $FE ; word. Pointer to Floating Point number for operation.


;=================================================
; OS Page 2 
;=================================================
VDSLST = $0200 ; word. Display List interrupt address.

VPRCED = $0202 ; word. Peripheral proceed line vector.
VINTER = $0204 ; word. Peripheral interrupt vector.
VBREAK = $0206 ; word. BRK instruction vector.

VKEYBD = $0208 ; word. POKEY keyboard interrupt vector.
VSERIN = $020A ; word. POKEY serial I/O receive data ready interrupt vector
VSEROR = $020C ; word. POKEY serial I/O transmit data ready interrupt vector
VSEROC = $020E ; word. POKEY serial bus transmit complete interrupt vector.

; HIGH FREQUENCY POKEY TIMERS: 
; Per Mapping The Atari  
; (Timer 1/Channel 1 as example)
; 
; Store frequency base in AUDCTL/$D208/53768: 
;    $00 = 64 kilohertz, 
;    $01 = 15 kilohertz, 
;    $60 = 1.79 megahertz).
; Next, set the channel control register (AUDC1/$D201/53761). 
; Store address of interrupt routine into VTIMR1 ($210/$211). 
; Store 0 to STIMER/$D209/53769. 
; Enable the interrupt:
;    Store in POKMSK/$10 the value of POKMSK OR the interrupt number:
;       1 = timer 1 interrupt, 
;       2 = timer 2 interrupt, 
;       4 = timer 4 interrupt -- no timer 3!). 
;    Store the same value in IRQEN/$D20E/53774.
;
; An interrupt occurs when the timer counts down to zero. 
; The timer is reloaded with the original value stored there, 
; and the process begins all over again.
;
; The OS pushes the A register onto the stack before jumping 
; through the vector address. 
; X and Y are not saved. Push them on the stack if they will be used. 
; Before RTI/return from the interrupt:
;    PLA the X and Y from the stack if used
;    PLA the Accumulator, and 
;    Clear the interrupt with CLI.
VTIMR1 = $0210 ; word. POKEY timer 1 interrupt vector.
VTIMR2 = $0212 ; word. POKEY timer 2 interrupt vector.
VTIMR4 = $0214 ; word. POKEY timer 4 interrupt vector.

VIMIRQ = $0216 ; word. IRQ immediate vector.


;=================================================
; COUNTDOWN TIMERS
;===============================================================
;  TIMER    | CDTMV1  | CDTMV2  | CDTMV3   | CDTMV4  | CDTMV5  |
;---------------------------------------------------------------
; Decrement | stage 1 | stage 2 | stage 2  | stage 2 | stage 2 |
; in VBI?   |         |         |          |         |         |
;---------------------------------------------------------------
; Interrupt | CDTMA1  | CDTMA2  |          |         |         |
; Vector?   |         |         |          |         |         |
;---------------------------------------------------------------
; Countdown |         |         | CDTMF3   | CDTMF4  | CDTMF5  |
; Flag?     |         |         |          |         |         |
;---------------------------------------------------------------
; OS use?   | I/O     |  no     | cassette |  no     |  no     |
;           | timing  |         | I/O      |         |         |
;===============================================================
CDTMV1 = $0218 ; word. Countdown Timer Value 1.
CDTMV2 = $021A ; word. Countdown Timer Value 2.
CDTMV3 = $021C ; word. Countdown Timer Value 3.
CDTMV4 = $021E ; word. Countdown Timer Value 4.
CDTMV5 = $0220 ; word. Countdown Timer Value 5.

VVBLKI = $0222 ; word. VBLANK immediate interrupt vector. 
VVBLKD = $0224 ; word. VBLANK deferred interrupt vector.

CDTMA1 = $0226 ; word. System Timer 1 vector address.
CDTMA2 = $0228 ; word. System Timer 2 vector address.
CDTMF3 = $022A ; Set when CDTMV3 counts down to 0.
SRTIMR = $022B ; keyboard software repeat timer.
CDTMF4 = $022C ; Set when CDTMV4 counts down to 0.
INTEMP = $022D ; Temp value used by SETVBL.
CDTMF5 = $022E ; Set when CDTMV5 counts down to 0.

; SDMCTL = $022F in ANTIC.asm
; SDLSTL = $0230 in ANTIC.asm
; SSKCTL = $0232 in POKEY.asm
; LPENH  = $0234 in ANTIC.asm
; LPENV  = $0235 in ANTIC.asm

BRKKY =  $0236 ; Break key interrupt vector

; SIO Command Frame:
CDEVIC = $023A ; SIO Bus ID number
CCOMND = $023B ; SIO Bus command code
CAUX1 =  $023C ; Command auxiliary byte 1
CAUX2 =  $023D ; Command auxiliary byte 2

TMPSIO = $023E ; SIO temporary byte
ERRFLG = $023F ; SIO error flag (except timeout)
DFLAGS = $0240 ; Disk flags from first byte of boot sector.
DBSECT = $0241 ; Number of Boot sectors read.
BOOTAD = $0242 ; word. Address of the boot loader.

COLDST = $0244 ; Coldstart Flag. 0 = reset is warmstart.  1 = reset is coldstart.

DSKTIM = $0246 ; Disk I/O timeout countdown.

LINBUF = $0247 ; 40 characters. temporary buffer for screen data.

; GPRIOR = $026F in GTIA.asm
; PADDL0 = $0270 in POKEY.asm
; PADDL1 = $0271 in POKEY.asm
; PADDL2 = $0272 in POKEY.asm
; PADDL3 = $0273 in POKEY.asm
; PADDL4 = $0274 in POKEY.asm
; PADDL5 = $0275 in POKEY.asm
; PADDL6 = $0276 in POKEY.asm
; PADDL7 = $0277 in POKEY.asm
; STICK0 = $0278 in POKEY.asm
; STICK1 = $0279 in POKEY.asm
; STICK2 = $027A in POKEY.asm
; STICK3 = $027B in POKEY.asm
; PTRIG0 = $027C in POKEY.asm
; PTRIG1 = $027D in POKEY.asm
; PTRIG2 = $027E in POKEY.asm
; PTRIG3 = $027F in POKEY.asm
; PTRIG4 = $0280 in POKEY.asm
; PTRIG5 = $0281 in POKEY.asm
; PTRIG6 = $0282 in POKEY.asm
; PTRIG7 = $0283 in POKEY.asm
; STRIG0 = $0284 in POKEY.asm
; STRIG1 = $0285 in POKEY.asm
; STRIG2 = $0286 in POKEY.asm
; STRIG3 = $0287 in POKEY.asm

CSTAT =  $0288 ; Cassette status register.
WMODE =  $0289 ; Cassette Write mode.  0 = read. $80 = write
BLIM =   $028A ; Cassette Buffer Limit. character count in buffer: 0 to $80.

TXTROW = $0290 ; E: text window cursor row.
TXTCOL = $0291 ; word. E: text window cursor column.
TINDEX = $0293 ; Split-screen text window graphics mode.  
TXTMSC = $0294 ; word. Address of first byte of text window when split screen is active.
TXTOLD = $0296 ; 6 bytes -- split screen versions of OLDROW, OLDCOL (word), OLDCHR, OLDADR (word) 
TMPX1 =  $029C ; 4 bytes -- Temp values for disply handler.
DMASK =  $02A0 ; Pixel Mask per current graphics mode. 1s set for bits that correspond to pixels.
	; 11111111 -- OS Modes 0, 1, 2, 12, 13 - 1 pixel is 1 byte
	; 11110000 -- OS Modes 9, 10, 11 for GTIA - 2 pixels each byte
	; 00001111
	; 11000000 -- OS Modes 3, 5, 7, 15 - 4 pixels each byte
	; 00110000 
	; 00001100
	; 00000011
	; 10000000 -- OS modes 4, 6, 8, 14 - 8 pixels each byte
	; 01000000
	; ... up to 
	; 00000001

TMPLBT = $02A1 ; Temporary value for bit mask.
ESCFLG = $02A2 ; Set to $80 when ESC key pressed. Reset to 0 for other characters.
TABMAP = $02A3 ; 15 bytes (120 bits) One bit for each character in a logical line.  1 = tab set. 0 = no tab.
LOGMAP = $02B2 ; 4 bytes. Bits of the first 3 bytes indicate the correspoding line on screen begins a logical line. 1 = start of logical line.
INVFLG = $02B6 ; When set to $80, input from E: occurs in inverse video.
FILFLG = $02B7 ; If operation is Draw this is 0. If operation is Fill, this is !0.
TMPROW = $02B8 ; Temporary row from ROWCRS
TMPCOL = $02B9 ; word. Temporary column from COLCRS
SCRFLG = $02BB ; Count number of physical lines in a logical line removed from screen.
SHFLOK = $02BE ; $0 for lowercase. $40 for uppercase (shift). $80 for control (ctrl) 
BOTSCR = $02BF ; Number of rows available for printing. 24 for OS Mode 0.  4 for text windows.

; PCOLOR0 = $02C0 in GTIA.asm
; PCOLOR1 = $02C1 in GTIA.asm
; PCOLOR2 = $02C2 in GTIA.asm
; PCOLOR3 = $02C3 in GTIA.asm
; COLOR0 =  $02C4 in GTIA.asm
; COLOR1 =  $02C5 in GTIA.asm
; COLOR2 =  $02C6 in GTIA.asm
; COLOR3 =  $02C7 in GTIA.asm
; COLOR4 =  $02C8 in GTIA.asm

; RUNAD =   $02E0 in DOS.asm
; INITAD =  $02E2 in DOS.asm

RAMSIZ = $02E4 ; Highest usable Page number (high byte)
MEMTOP = $02E5 ; word. Pointer to last byte usable by application. OS display data follows.
MEMLO =  $02E7 ; word. Pointer to start of free mememory. ($0700 default, $1CFc with DOS 2, $23DC with 850 driver)

DVSTAT = $02EA ; 4 bytes. Status registers for serial device status. Different for Disk vs 850.

CBAUDL = $02EE ; low byte cassette bps rate.
CBAUDH = $02EF ; high byte cassette bps rate.

CRSINH = $02F0 ; Cursor Inhibit.  0 = cursor on.  1 = cursor off.
KEYDEL = $02F1 ; Key delay counter. Starts at 3, decremented each frame until 0.
CH1 =    $02F2 ; Keyboard character code previously in CH/$02FC.

; CHACT = $02F3 in ANTIC.asm
; CHBAS = $02F4 in ANTIC.asm

ATACHR = $02FA ; Last value read or written at graphics cursor.  Atascii in text modes. color number in others.  
; CH =     $02FC ; in POKEY.asm KBCODE - Internal keyboard code of last key pressed.  $FF is no key pressed.
FILDAT = $02FD ; Color for the fill region.
DSPFLG = $02FE ; E: config for cursor control characters. 0 = normal operation. !0 = Display cursor controls instead of acting on them.
SSFLAG = $02FF ; Scrolling stop/start control. 0 = normal scrolling.  $FF = stop scrolling.

;=================================================
; OS Page 3
;=================================================
DDEVIC = $0300 ; Serial bus device ID. Set by Handler.
DUNIT =  $0301 ; Device unit number. Set by user program.
DCOMND = $0302 ; Device command set by handler or the user program.
DSTATS = $0303 ; Status code for user program. Handler's data frame direction for SIO. 
DBUFLO = $0304 ; word. Data buffer address.
DBUFHI = $0305 
DTIMLO = $0306 ; Handler timeout in (approx) seconds.
DBYTLO = $0308 ; word. Number of bytes transferred to/from buffer.
DBYTHI = $0309 
DAUX1 =  $030A ; Information specific to device.  (sector number) 
DAUX2 =  $030B ; Information specific to device.  (sector number) 

TIMER1 = $030C ; Timer for BPS rate 
ADDCOR = $030E ; Math correction for calculating bps rate 
CASFLG = $030F ; SIO Cassette mode or not. 0 = standard SIO. !0 = cassette.
TIMER2 = $0310 ; word. End timer for bps rate.
TEMP1 =  $0312 ; word. Temporary value for SIO bps calculations.
TEMP2 =  $0314 ; Temporary value
TEMP3 =  $0315 ; Temporary value
SAVIO =  $0316 ; SIO flag for bit arrival.
TIMFLG = $0317 ; Timeout for bps rate correction.
STACKP = $0318 ; SIO stack pointer.
TSTAT =  $0319 ; Temporary status.

; Handler Address Table
; 12 entries, 3 bytes each:
; Atascii character for device.
; Handler address LSB/MSB.
HATABS = $031A ; 36 bytes of handler entries, 3 bytes each.

; CIO Block.  ** denotes commonly used fields **
IOCB =  $0340   ; Base IO Control Block
ICHID = IOCB+$00 ; Handler ID
ICDNO = IOCB+$01 ; Device number
ICCMD = IOCB+$02 ; ** CIO Command **
ICSTA = IOCB+$03 ; CIO Status
ICBAL = IOCB+$04 ; ** Buffer address (low) **
ICBAH = IOCB+$05 ; ** Buffer address (high) **
ICPTL = IOCB+$06 ; Put char routine (low)
ICPTH = IOCB+$07 ; Put char routine (high)
ICBLL = IOCB+$08 ; ** Buffer length (low) **
ICBLH = IOCB+$09 ; ** Buffer length (high) **
ICAX1 = IOCB+$0A ; ** Aux Byte 1 **
ICAX2 = IOCB+$0B ; ** Aux Byte 2 **
ICAX3 = IOCB+$0C ; Aux Byte 3  
ICAX4 = IOCB+$0D ; Aux Byte 4  
ICAX5 = IOCB+$0E ; Aux Byte 5  
ICAX6 = IOCB+$0F ; Aux Byte 6  

IOCB0 = IOCB  ; IOCB for channel 0
IOCB1 = $0350 ; IOCB for channel 1
IOCB2 = $0360 ; IOCB for channel 2
IOCB3 = $0370 ; IOCB for channel 3
IOCB4 = $0380 ; IOCB for channel 4
IOCB5 = $0390 ; IOCB for channel 5
IOCB6 = $03A0 ; IOCB for channel 6
IOCB7 = $03B0 ; IOCB for channel 7

PRNBUF = $03C0 ; 40 bytes up to $3E7

; CIO Common Device Commands
CIO_OPEN =       $03
CIO_GET_RECORD = $05
CIO_GET_BYTES =  $07
CIO_PUT_RECORD = $09
CIO_PUT_BYTES =  $0B
CIO_CLOSE =      $0C
CIO_STATUS =     $0D
CIO_SPECIAL =    $0E

; CIO Device Commands for D:
CIO_D_RENAME =      $20 ; Rename a file
CIO_D_DELETE =      $21 ; Delete the named file
CIO_D_LOCK =        $23 ; Lock/protect the file
CIO_D_UNLOCK =      $24 ; unlock/unprotect the file

CIO_D_POINT =       $25 ; Move to sector/byte position
CIO_D_NOTE =        $26 ; Get current sector/byte position

CIO_D_FILELEN =     $27 ; Get file length
CIO_D_CD_MYDOS =    $29 ; MyDos cd (change directory)
CIO_D_MKDIR_MYDOS = $2A ; MyDos (and SpartaDos) mkdir (make directory)
CIO_D_RMDIR_SPDOS = $2B ; SpartaDos rmdir (remove directory)
CIO_D_CD_SPDOS    = $2C ; SpartaDos cd (change directory)
CIO_D_PWD_MYDOS   = $30 ; MyDos (and SpartaDos) print/get working directory 

CIO_D_FORMAT =      $FE ; Format Disk

; CIO Device Commands for S:
CIO_S_DRAWTO = $11
CIO_S_FILL =   $12

; ICAX1 Common Options (OPEN modes).
CIO_ICAX_READ      = $04
CIO_ICAX_WRITE     = $08 ; READ + WRITE starts I/O at first byte.

; ICAX1 Less Common Options (OPEN modes.)
CIO_ICAX_E_FORCED     = $01 ; E: FORCED input. Usually with READ + WRITE.
CIO_ICAX_D_APPEND     = $01 ; D: Write starts at end of file. Usually with READ + WRITE.
CIO_ICAX_D_DIRECTORY  = $02 ; D: DIRECTORY.  Use with READ. 

CIO_ICAX_S_TEXTWINDOW = $10 ; S: Open graphics mode with text window. Ignored for 0, 9, 10, 11.
CIO_ICAX_S_DONOTCLEAR = $20 ; S: Suppress clear screen for graphics mode. 

; Note: 
; The ICAX2 value for S: is the OS graphics mode number.
; If the mode is 0, 9, 10, or 11 the text Window option is ignored.

;=================================================
; OS Page 4, 5, 6   
;=================================================
CASBUF = $03FD ; 128 bytes up to $047F (ends in page 4)

; $0480 to $06FF are free if BASIC and FP are not used. 

; $057E to $05FF
; Various line/buffer values for FP package.

LBPR1 =  $057E ; LBUFF Prefix 1.
LBPR2 =  $057F ; LBUFF Prefix 2.
LBUFF =  $0580 ; up to $5FF. Text buffer for FP/ATASCII conversions.
PLYARG = $05E0 ; Polynomial arguments for FP package.
FPSCR =  $05E6 ; to $05EB -- FP temporary use
FPSCR1 = $05EC ; to $05FF -- FP temporary use

;=================================================
; Cartridge space 
; Pages $80 through $9F 
; Pages $A0 through $BF 
;=================================================
; CART B -- Atari 800 ONLY
CARTB =  $8000 ; Start of Cart B/Right Cart (8K)
CRBSTA = $9FFA ; word. Cart B/Right Start address.
CRBFLG = $9FFC ; Cart B/right present.  Copied to $7 CTBFLG
CRBBTF = $9FFD ; Cart B/right Boot Option bits. $1 = boot disk. $4 = Boot cart. $80 = diagnostic cart 
CRBINI = $9FFE ; word. Init address for Cart B/Right for cold boot/warm start

CARTA =  $A000 ; Start of Cart A/Left Cart (8K)
CRASTA = $BFFA ; word. Cart A/Left Start address.
CRAFLG = $BFFC ; Cart A/Left present.  Copied to $6 CTAFLG
CRABTF = $BFFD ; Cart A/Left Boot Option bits. $01 = boot disk. $04 = Boot cart. $80 = diagnostic cart 
CRAINI = $BFFE ; word. Init address for Cart A/Left for cold boot/warm start

;=================================================
; XL OS ROM CSET 2 Pages $CC - $CF
;=================================================
ROM_CSET_2 = $CC00

;=================================================
; OS Floating Point Package 
; Pages $D8 through $DF 
;=================================================
; FP Routines References:
;  Page 0 - $D4 to $DB  
;  Page 5 - $57E to $5FF
; In/out usually FR0, and LBUFF
;=================================================
AFP =    $D800 ; Convert ATASCII to FP
FASC =   $D8E6 ; Convert FP to ATASCII
IFP =    $D9AA ; Convert Integer to FP
FPI =    $D9D2 ; Convert FP to Integer
ZFRO =   $DA44 ; Zero FR0
ZFR1 =   $DA46 ; Zero FR1
FSUB =   $DA60 ; Subtracttion - FR0 minus FR1
FADD =   $DA66 ; Addition - FR0 plus FR1
FMUL =   $DADB ; Multiplication - FR0 times FR1
FDIV =   $DB28 ; Division - FR0 divided by FR1
PLYEVL = $DD40 ; Evaluate FP Polynomial 
FLD0R =  $DD89 ; Load FR0 from x, Y reg pointer
FLD0P =  $DD8D ; Load FR0 from FLPTR
FLD1R =  $DD98 ; Load FR1 from x, Y reg pointer
FLD1P =  $DD9C ; Load FR1 from FLPTR
FST0R =  $DDA7 ; Store FR0 to address in X, Y registers
FST0P =  $DDAB ; Store FR0 using FLPTR 
FMOVE =  $DDB6 ; Move FR0 contents to FR1
EXP =    $DDC0 ; Exponentiation - FP base E 
EXP10 =  $DDCC ; FP base 10 exponentiations
LOG =    $DECD ; FP natural log
LOG10 =  $DED1 ; FP base 10 log

;=================================================
; OS ROM CSET Pages $E0 - $E3 
;=================================================
ROM_CSET = $E000


;=================================================
; OS ROM VECTORs - Page $E4
;=================================================
; Device handler vectors specify:
; Open 
; Close 
; Get Byte 
; Put Byte 
; Get Special
; JMP to handler init routine
EDITRV = $E400 ; Screen editor vector table.
SCRENV = $E410 ; Screen editor vector table.
KEYBDV = $E420 ; Screen editor vector table.
PRINTV = $E430 ; Screen editor vector table.
CASETV = $E440 ; Screen editor vector table.

DISKIV = $E450 ; JMP vector for disk handler init
DSKINV = $E453 ; JMP vector for disk handler interface.

CIOV =   $E456 ; JSR vector for CIO. All CIO operations go through this address.
SIOV =   $E459 ; JMP vector for SIO.

; JSR to set Vertical Blank Interupt Vector/Timer values.
; Y register is the LSB of vector/routine or timer value.
; X register is the MSB of vector/routine or timer value.
; A register is the number of the Vertical Blank routine to change:
;    1 == CDTMV1 - decremented Immediate VBI Stage 1 -- JSR to CDTMA1 $0226
;    2 == CDTMV2 - decremented Immediate VBI Stage 2 -- JSR to CDTMA2 $0228
;    3 == CDTMV3 - decremented Immediate VBI Stage 2 -- Zero CDTMF3 $022A
;    4 == CDTMV4 - decremented Immediate VBI Stage 2 -- Zero CDTMF4 $022C
;    5 == CDTMV5 - decremented Immediate VBI Stage 2 -- Zero CDTMF5 $022E
;    6 == Immediate VBI
;    7 == deferred VBI
SETVBV = $E45C ; JSR Vector to set timers

; User Immediate VBI routine should end by a JMP to this address 
; to continue the OS Vertical Blank routine. 
SYSVBV = $E45F ; JMP to end user Immediate VBI

; User Deferred VBI routine should end by a JMP to this address 
; to continue the OS Vertical Blank routine. 
XITVBV = $E462 ; JMP Vector to end user Deferred VBI

WARMSV = $E474 ; Usr() here will warmstart.
COLDSV = $E477 ; Usr() here to cold boot the system.

; After this there is not much that a user program 
; should reference or call.  
; I/O should be done by CIO. 
; Vertical Blank timers should be set by calling SETVBV.
; Everything else is subject to change or reloaction 
; in a future operating system.
