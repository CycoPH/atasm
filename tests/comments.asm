* = $2000
.macro mDL_LMS  ; Mode, Screen memory address
	.if %0<>2
		.error "mDL_LMS: 2 arguments required."
	.else
		MDL_TEMP .= %1&$0F
		.if MDL_TEMP<DL_TEXT_2
			.error "mDL_LMS: Argument 1 must be ANTIC Mode from $2 to $F."
		.else 
			; Byte for Mode plus LMS option.  And then the screen memory address.
			.byte %1|DL_LMS
			.word %2   
		.endif
	.endif
.endm

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



BOOT_this:		; boot here "nice"
loop jmp loop		; Wait for ever

someLoc	.byte 0		; "game loop" counter


	ADD_WORD $80, $82

	.bank
	* = $2e0
	.word BOOT_THIS