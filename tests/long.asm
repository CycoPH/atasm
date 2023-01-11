	*=$2000
start
	; some code to get away from the start label
	lda #0
	sta temp
	jmp skip

; This is a known label that the long jumps can short jump to
known	
	lda #$FF
	sta temp
	lda #$fe
	sta temp
	rts

; Lets branch to a known location
; These should all be reported as potential long jump optimizations
skip
	jeq known
	jne known
	jpl known
	jmi known
	jcc known
	jcs known
	jvc known
	jcs known

	lda #1
	; These are forward references that could become b.. opcodes
	jeq forward
	jne forward
	jpl forward
	jmi forward
	jcc forward
	jcs forward
	jvc forward
	jcs forward

	; These will be real long jumps
	jeq bob
	jne bob
	jpl bob
	jmi bob
	jcc bob
	jcs bob
	jvc bob
	jcs bob

	lda #1
	brk
forward	
	.dc 200 0
bob
	lda #2
	brk

temp .byte 0

	.bank
	* = $2e0
	.word start	