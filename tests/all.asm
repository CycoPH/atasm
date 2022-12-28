	; Test all atasm features
	; Some equates
zpVariables = $90
BallXPosition		= zpVariables	;.byte BALL_START_X
BallYPosition		= zpVariables+1	;.byte BALL_START_Y
BallFrameCounter	= zpVariables+2
BallDirection		= zpVariables+3
NextBallDirection	= zpVariables+4

	* = $6000
	lda #1
	sta $6000

	.include "test_opcodes.asm"

	* = $3000 "BOOT"
BOOT_THIS:
	; Test LSB/MSB
	lda #<BOOT_THIS
	lda #>BOOT_THIS

	; Hex constant
	lda #>$601
	.BYTE $02,$04,$08,$10

	; Binary constant
	lda #~11110000
	.BYTE ~00011000,~00111100,~01111110

	; Character constant
	lda #'a+$10
	.BYTE 'a,'B
	; Strings in "
	.BYTE "This is a tes",'t+$80

	; Decimal constant
	lda #12+8*[3+4]
	sta BOOT_THIS

	; Make space for 32 bytes
	.ds 32

	; Define constant storage, fill mem
	.dc 16 123

	.BYTE +$80,$10,20,"Testing",'a ; 90 94 D4 E5 F3 F4 E9 EE E7 E1

	.SBYTE +$80,$10,20,"Testing",'a	; 90 94 D4 B4 F3 F4 E9 EE E7 E1

	.CBYTE +$80,$10,20,"Testing",'a	; 90 94 D4 E5 F3 F4 E9 EE E7 61

	; Store words in MSB/LSB
	.DBYTE $1234,-1,1 	; 12 34 FF FF 00 01

	; Store words in LSB/MSB
	.WORD $1234,-1,1	; 34 12 FF FF 01 00

	; Stores a 6 byte BCD floating point number in the format used in the Atari OS ROM.
	.FLOAT 3.14156295,-2.718281828	; 40 03 14 15 62 95 C0 27 18 28 18 28

SOME: 	
	lda #0
	sta StoreHere

StoreHere	.byte 0

	.local
?loop
	jmp ?loop

	.local
?loop
	jmp ?loop

.MACRO VDLI
	.IF %0<>1
		.ERROR "VDLI: Wrong number of parameters"
	.ELSE
		ldy # <%1
		ldx # >%1
		lda #$C0
		sty $0200
		stx $0201
		sta $D40E
	.ENDIF
.ENDM
	VDLI $1234

.MACRO ADD_WORD		; Add_word(x,y[z]) - Add two 16-bit values and store in y or (if set) in z
	.IF %0<2 .OR %0>3
		.ERROR "ADD_WORD: Wrong number of parameters"
	.ELSE
		lda %1
		clc
		adc %2
		.IF %0=3
			sta %3
		.ELSE
			sta %2
		.ENDIF
		lda %1+1
		adc %2+1
		.IF %0=3
			sta %3+1
		.ELSE
			sta %2+1
		.ENDIF
	;.ENDIF
.ENDM
	
	ADD_WORD 1234,5678
	ADD_WORD addr1,addr2,addr3

addr1	.byte 1
addr2	.byte 2
addr3	.byte 3

	; Repeat asl 4x
	.rept 4
		asl a
	.endr

table 	.rept 192
			.word [*-table]/2*40
		.endr

shapes
	r .= 0
	.rept 8
		.dbyte shape1+r*16
		r .= r+1
	.endr
shape1
	r .= 1
	.rept 8
		.dbyte ~1111000000000000/r
		.dbyte ~1100000000000000/r
		.dbyte ~1010000000000000/r
		.dbyte ~1001000000000000/r
		.dbyte ~0000100000000000/r
		.dbyte ~0000010000000000/r
		.dbyte ~0000001000000000/r
		.dbyte ~0000000100000000/r
		r .= r * 2
	.endr

	; V 1.14
	; Labels may contain '.'
	* = $4000
	.NAME DATA
	lda #255
	sta data.cmd
	lda data.len
	sta data.tmp

data.cmd	.byte 0
data.len	.byte 0
data.tmp	.byte 0

	;##TRACE "this is an altirra test %d" @a
	
	; New modulus %% operator
	; Alternative if for some reason %% does not assemble
	; .MOD
	BOB = 16

	.byte 14%%10
	.byte 128%%10
	
	r .= 0
	.rept 5%%255
	.byte [r*13].MODBOB
	.byte [r*13]%%BOB
	r .= r + 1
	.endr

Modulus10Table .rept 10
	.byte [*-Modulus10Table]%%10
	.endr

	; New shift operators << >>
	lda #$100>>1
	lda #$100>>2
	lda #$100>>3
	lda #$100>>4
	lda #$100>>5
	lda #$100>>6
	lda #$100>>7
	lda #1<<0
	lda #1<<1
	lda #1<<2
	lda #1<<3
	lda #1<<4
	lda #1<<5
	lda #1<<6
	lda #1<<7

	.bank
	* = $2e0
	.word BOOT_THIS
