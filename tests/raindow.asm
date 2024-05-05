	* = $2000
COLPF2 = $d018
COLBK = $D01A
WSYNC = $d40a
VCOUNT = $d40b
RTCLOK = $14

boot
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
	
	.RUN boot 