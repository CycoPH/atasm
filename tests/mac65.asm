	* = $2000
	r .= 0
	.rept 1024
		.byte r
		r .= r+1
	.endr

	.INIT $2000

	* = $4000
	r .= 0
	.rept 1024
		.byte r
		r .= r+1
	.endr

	* = $600
Boot:	
	lda #1
	sta $2000
	rts

	.RUN Boot