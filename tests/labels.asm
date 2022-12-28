	* = $2000
boot
	lda #0
	sta here
?loop
	bne ?loop
	rts
	
	
here .byte 0
		