		*=$2000
		LDA #1
		STA $4000
		jmp align

		; Test if we can align the PC to the next page boundary
		*=(*+$FF) & $FF00
align	LDA #2
		STA $4001