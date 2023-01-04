	*=$2000

	jsr func1
	rts

.IF .REF func1
func1
	lda #1
	sta $4000
	rts
.ENDIF	

.IF .REF func2
func2
	lda #1
	sta $4000
	rts
.ENDIF	