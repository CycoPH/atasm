; Generate an altirra.lst and altirra.lab file with
; atasm -oaltirra.xex -laltirra.lab -galtirra.lst altirra.asm
	*=$2000		; Start @ $2000
BOOT_THIS	
	lda #0
	sta storehere
	;##TRACE "Display list address = $%04X" dw(vdslst)
loop
	jmp loop
	
storehere .byte 1
	
	.bank
	* = $2e0
	.word BOOT_THIS
	
	