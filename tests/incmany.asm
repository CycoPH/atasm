	* = $2000

	.bank
BOOT_THIS
	lda #0
	sta StoreIt
	.include "incpart1.asm"
	.include "incpart2.asm"
	.include "incpart3.asm"
	.include "incpart4.asm"
	.include "incpart5.asm"
	.include "incpart6.asm"
	.include "incpart7.asm"
	.include "incpart8.asm"
	.include "incpart9.asm"
	.include "incpart10.asm"

	jmp BOOT_THIS


StoreIt:
	.byte 0

	.bank
	* = $2e0
	.word BOOT_THIS