	.OPT ILL		; This will cause a warning
	* = $2000 "BOOT"
boot
	lda #0
	sta here
?loop
	bne ?loop
	rts
	
here .byte 0

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
	
	lda  #256 		; This will cause a warning
	lda	#~101112	; This will cause a warning
	.OPT ABCDEF		; This will cause a warning
	.WARN "Hello world" ; This will cause a warning
	sta ABC		; This will cause an error