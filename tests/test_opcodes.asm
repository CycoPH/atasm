
    ; --------------------------------------- ;
    ;  this program is supposed to uses all   ;
    ;       the official 6502 opcodes         ;
    ; --------------------------------------- ;

    * = $2000 ; (un)comment if neccessary
	.NAME "OPCODES"
	;ORG $2000
    ;_main: ; (un)comment if neccessary
    ;.export _main

LABEL_01
    BRK          ; opcode $00
    ORA ($70,X)  ; opcode $01
                 ; opcode $02 (illegal)
                 ; opcode $03 (illegal)
                 ; opcode $04 (illegal)
    ORA $7D      ; opcode $05
    ASL $A7      ; opcode $06
                 ; opcode $07 (illegal)
    PHP          ; opcode $08
    ORA #$41     ; opcode $09
    ASL A        ; opcode $0a
                 ; opcode $0b (illegal)
                 ; opcode $0c (illegal)
    ORA $A750    ; opcode $0d
    ASL $8FA4    ; opcode $0e
                 ; opcode $0f (illegal)
LABEL_02
    BPL LABEL_02 ; opcode $10
    ORA ($66),Y  ; opcode $11
                 ; opcode $12 (illegal)
                 ; opcode $13 (illegal)
                 ; opcode $14 (illegal)
    ORA $E0,X    ; opcode $15
    ASL $9F,X    ; opcode $16
                 ; opcode $17 (illegal)
    CLC          ; opcode $18
    ORA $5C10,Y  ; opcode $19
                 ; opcode $1a (illegal)
                 ; opcode $1b (illegal)
                 ; opcode $1c (illegal)
    ORA $A207,X  ; opcode $1d
    ASL $7404,X  ; opcode $1e
                 ; opcode $1f (illegal)
LABEL_03
    JSR $AB11    ; opcode $20
    AND ($06,X)  ; opcode $21
                 ; opcode $22 (illegal)
                 ; opcode $23 (illegal)
    BIT $20      ; opcode $24
    AND $A4      ; opcode $25
    ROL $C6      ; opcode $26
                 ; opcode $27 (illegal)
    PLP          ; opcode $28
    AND #$0F     ; opcode $29
    ROL A        ; opcode $2a
                 ; opcode $2b (illegal)
    BIT $E22E    ; opcode $2c
    AND $D78A    ; opcode $2d
    ROL $C842    ; opcode $2e
                 ; opcode $2f (illegal)
LABEL_04
    BMI LABEL_04 ; opcode $30
    AND ($61),Y  ; opcode $31
                 ; opcode $32 (illegal)
                 ; opcode $33 (illegal)
                 ; opcode $34 (illegal)
    AND $47,X    ; opcode $35
    ROL $D2,X    ; opcode $36
                 ; opcode $37 (illegal)
    SEC          ; opcode $38
    AND $D414,Y  ; opcode $39
                 ; opcode $3a (illegal)
                 ; opcode $3b (illegal)
                 ; opcode $3c (illegal)
    ORA $0771,X  ; opcode $3d
    ASL $6ABB,X  ; opcode $3e
                 ; opcode $3f (illegal)
LABEL_05
    RTI          ; opcode $40
    EOR ($5B,X)  ; opcode $41
                 ; opcode $42 (illegal)
                 ; opcode $43 (illegal)
                 ; opcode $44 (illegal)
    EOR $0C      ; opcode $45
    LSR $00      ; opcode $46
                 ; opcode $47 (illegal)
    PHA          ; opcode $48
    EOR #$B4     ; opcode $49
    LSR A        ; opcode $4a
                 ; opcode $4b (illegal)
    JMP $7FD4    ; opcode $4c
    EOR $0E56    ; opcode $4d
    LSR $7FF3    ; opcode $4e
                 ; opcode $4f (illegal)
LABEL_06
    BVC LABEL_06 ; opcode $50
    EOR ($D3),Y  ; opcode $51
                 ; opcode $52 (illegal)
                 ; opcode $53 (illegal)
                 ; opcode $54 (illegal)
    EOR $D9,X    ; opcode $55
    LSR $6E,X    ; opcode $56
                 ; opcode $57 (illegal)
    CLI          ; opcode $58
    EOR $E85C,Y  ; opcode $59
                 ; opcode $5a (illegal)
                 ; opcode $5b (illegal)
                 ; opcode $5c (illegal)
    EOR $CC95,X  ; opcode $5d
    LSR $114E,X  ; opcode $5e
                 ; opcode $5f (illegal)
LABEL_07
    RTS          ; opcode $60
    ADC ($12,X)  ; opcode $61
                 ; opcode $62 (illegal)
                 ; opcode $63 (illegal)
                 ; opcode $64 (illegal)
    ADC $60      ; opcode $65
    ROR $82      ; opcode $66
                 ; opcode $67 (illegal)
    PLA          ; opcode $68
    ADC #$83     ; opcode $69
    ROR A        ; opcode $6a
                 ; opcode $6b (illegal)
    JMP ($CC69)  ; opcode $6c
    ADC $A13F    ; opcode $6d
    ROR $B757    ; opcode $6e
                 ; opcode $6f (illegal)
LABEL_08
    BCS LABEL_08 ; opcode $70
    ADC ($45),Y  ; opcode $71
                 ; opcode $72 (illegal)
                 ; opcode $73 (illegal)
                 ; opcode $74 (illegal)
    ADC $4A,X    ; opcode $75
    ROR $8E,X    ; opcode $76
                 ; opcode $77 (illegal)
    SEI          ; opcode $78
    ADC $7FA9,Y  ; opcode $79
                 ; opcode $7a (illegal)
                 ; opcode $7b (illegal)
                 ; opcode $7c (illegal)
    ADC $2175,X  ; opcode $7d
    ROR $EF89,X  ; opcode $7e
                 ; opcode $7f (illegal)
LABEL_09
                 ; opcode $80 (illegal)
    STA ($5C,X)  ; opcode $81
                 ; opcode $82 (illegal)
                 ; opcode $83 (illegal)
    STY $EE      ; opcode $84
    STA $3E      ; opcode $85
    STX $80      ; opcode $86
                 ; opcode $87 (illegal)
    DEY          ; opcode $88
                 ; opcode $89 (illegal)
    TXA          ; opcode $8a
                 ; opcode $8b (illegal)
    STY $4AA3    ; opcode $8c
    STA $5B92    ; opcode $8d
    STX $06C8    ; opcode $8e
                 ; opcode $8f (illegal)
LABEL_10
    BCC LABEL_10 ; opcode $90
    STA ($B9),Y  ; opcode $91
                 ; opcode $92 (illegal)
                 ; opcode $93 (illegal)
    STY $F2,X    ; opcode $94
    STA $50,X    ; opcode $95
    STX $05,Y    ; opcode $96
                 ; opcode $97 (illegal)
    TYA          ; opcode $98
    STA $6736,Y  ; opcode $99
    TXS          ; opcode $9a
                 ; opcode $9b (illegal)
                 ; opcode $9c (illegal)
    STA $2391,X  ; opcode $9d
                 ; opcode $9e (illegal)
                 ; opcode $9f (illegal)
LABEL_11
    LDY #$C1     ; opcode $a0
    LDA ($D1,X)  ; opcode $a1
    LDX #$A5     ; opcode $a2
                 ; opcode $a3 (illegal)
    LDY $BE      ; opcode $a4
    LDA $E4      ; opcode $a5
    LDX $BF      ; opcode $a6
                 ; opcode $a7 (illegal)
    TAY          ; opcode $a8
    LDA #$5C     ; opcode $a9
    TAX          ; opcode $aa
                 ; opcode $ab (illegal)
    LDY $E8D8    ; opcode $ac
    LDA $D432    ; opcode $ad
    LDX $6337    ; opcode $ae
                 ; opcode $af (illegal)
LABEL_12
    BCS LABEL_12 ; opcode $b0
    LDA ($73),Y  ; opcode $b1
                 ; opcode $b2 (illegal)
                 ; opcode $b3 (illegal)
    LDY $D0,X    ; opcode $b4
    LDA $67,X    ; opcode $b5
    LDX $B1,Y    ; opcode $b6
                 ; opcode $b7 (illegal)
    CLV          ; opcode $b8
    LDA $B43C,Y  ; opcode $b9
    TSX          ; opcode $ba
                 ; opcode $bb (illegal)
    LDY $07CA,X  ; opcode $bc
    LDA $6AFE,X  ; opcode $bd
    LDX $D77A,Y  ; opcode $be
                 ; opcode $bf (illegal)
LABEL_13
    CPY #$CB     ; opcode $c0
    CMP ($15,X)  ; opcode $c1
                 ; opcode $c2 (illegal)
                 ; opcode $c3 (illegal)
    CPY $84      ; opcode $c4
    CMP $AD      ; opcode $c5
    DEC $C0      ; opcode $c6
                 ; opcode $c7 (illegal)
    INY          ; opcode $c8
    CMP #$5D     ; opcode $c9
    DEX          ; opcode $ca
                 ; opcode $cb (illegal)
    CPY $0A39    ; opcode $cc
    CMP $4680    ; opcode $cd
    DEC $D017    ; opcode $ce
                 ; opcode $cf (illegal)
LABEL_14
    BNE LABEL_14 ; opcode $d0
    CMP ($5A),Y  ; opcode $d1
                 ; opcode $d2 (illegal)
                 ; opcode $d3 (illegal)
                 ; opcode $d4 (illegal)
    CMP $8D,X    ; opcode $d5
    DEC $4C,X    ; opcode $d6
                 ; opcode $d7 (illegal)
    CLD          ; opcode $d8
    CMP $35A5,Y  ; opcode $d9
                 ; opcode $da (illegal)
                 ; opcode $db (illegal)
                 ; opcode $dc (illegal)
    CMP $9F75,X  ; opcode $dd
    DEC $57E6,X  ; opcode $de
                 ; opcode $df (illegal)
LABEL_15
    CPX #$52     ; opcode $e0
    SBC ($57,X)  ; opcode $e1
                 ; opcode $e2 (illegal)
                 ; opcode $e3 (illegal)
    CPX $59      ; opcode $e4
    SBC $FE      ; opcode $e5
    INC $4C      ; opcode $e6
                 ; opcode $e7 (illegal)
    INX          ; opcode $e8
    SBC #$DF     ; opcode $e9
    NOP          ; opcode $ea
                 ; opcode $eb (illegal)
    CPX $F5EA    ; opcode $ec
    SBC $4A0D    ; opcode $ed
    INC $F15B    ; opcode $ee
                 ; opcode $ef (illegal)
LABEL_16
    BEQ LABEL_16 ; opcode $f0
    SBC ($54),Y  ; opcode $f1
                 ; opcode $f2 (illegal)
                 ; opcode $f3 (illegal)
                 ; opcode $f4 (illegal)
    SBC $18,X    ; opcode $f5
    INC $41,X    ; opcode $f6
                 ; opcode $f7 (illegal)
    SED          ; opcode $f8
    SBC $AD76,Y  ; opcode $f9
                 ; opcode $fa (illegal)
                 ; opcode $fb (illegal)
                 ; opcode $fc (illegal)
    SBC $FDE1,X  ; opcode $fd
    INC $8C2D,X  ; opcode $fe
                 ; opcode $ff (illegal)
