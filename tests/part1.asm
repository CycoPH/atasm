levelMap = levelData + $1000

* = $600
    lda levelMap+1,x
    lda level.Data
    rts

level.Data .byte 0	
	
	* = $2000

	lda #0
	sta Part1Var
	jsr Part2
	brk
	
Part1Var	.byte 1

	.include "part2.asm"