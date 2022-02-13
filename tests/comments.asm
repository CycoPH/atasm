* = $2000
BOOT_this:		; boot here "nice"
loop jmp loop		; Wait for ever

someLoc	.byte 0		; "game loop" counter

	.bank
	* = $2e0
	.word BOOT_THIS