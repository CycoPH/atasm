	* = $2000

.proc start
	lda #$00
	rts
.endp


.proc initData
	lda #0
	sta 128
	rts
.endp

 * = $4000

.ifdef CHECKSUM
	.error "Fail if defined"
.endif

.ifndef TEST
	BOB_IS_HERE = 123
.else
	.error "this needs to fail if TEST is defined"
.endif

/* test multi-line comments */

/* 
Multi-line comments
*/
 
normal = ~00001111
abc = %00001111


.byte %0, %1, %10, %11
.byte ~11111111, %11111111, ~00001111, %00001111

.MACRO bob
	lda #%1
	ldx #~1000000
	sta $2000
.ENDM
bob 1

COLPF2 = $d018
COLBK = $D01A
WSYNC = $d40a
VCOUNT = $d40b
RTCLOK = $14

loop
	lda RTCLOK
	tay
	clc
	adc VCOUNT
	tax

	tya
	asl
	sec
	sbc VCOUNT

	sta WSYNC

	sta COLBK
	stx COLPF2
	jmp loop

.run start
