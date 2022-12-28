;
; atasm -Itests/includes -Itests -hv tests/dump_symbols.asm
; produces the "asm-symbol.json" VSCode data file without
; and overload of hardware specific constants being defined

	.OPT NO SYMDUMP		; Turn OFF constant symbol tracing
	.include "ANTIC.asm"
	.include "GTIA.asm"
	.include "OS.asm"
	.OPT SYMDUMP		; Turn ON constant symbol tracing
	; All constant defined in any of the above files will NOT make it into
	; the "asm-symbols.json" file.

DEF_THIS = 200

	* = $2000
BOOT_HERE:
?loop  
	lda RTCLOK ; some comment
    tay
    clc
    adc VCOUNT
    tax

    tya
    asl
    sec
    sbc VCOUNT

    sta WSYNC

    sta COLBK
    stx COLPF2
    jmp ?loop

	; Where will the file boot once it has been loaded into memory
	.bank
	* = $2e0
	.word BOOT_HERE
