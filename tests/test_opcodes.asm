    *=$2000
LABEL_01: BRK
    ORA ($A7,X) 
    ORA $6C
    ASL $C1
    PHP
    ORA #$F5
    ASL A
    ORA $87A6
    ASL $467E
LABEL_02: BPL LABEL_02
    ORA ($52),Y
    ORA $07,X
    ASL $4D,X
    CLC
    ORA $E97E,Y
    ORA $50F5,X
    ASL $241E,X
LABEL_03: JSR $B1DA
    AND ($96,X)
    BIT $D0
    AND $D1
    ROL $D8
    PLP
    AND #$79
    ROL A
    BIT $BC10
    AND $97CD
    ROL $1678
LABEL_04: BMI LABEL_04
    AND ($66),Y
    AND $72,X
    ROL $FB,X
    SEC
    AND $9FBA,Y
    ORA $64AB,X
    ASL $5D20,X
LABEL_05: RTI
    EOR ($28,X)
    EOR $D7
    LSR $15
    PHA
    EOR #$A5
    LSR A
    JMP $F3FE
    EOR $6571
    LSR $286C
LABEL_06: BVC LABEL_06
    EOR ($B2),Y
    EOR $0C,X
    LSR $A4,X
    CLI
    EOR $2BB7,Y
    EOR $CD9D,X
    LSR $40B3,X
LABEL_07: RTS
    ADC ($5E,X)
    ADC $59
    ROR $A2
    PLA
    ADC #$48
    ROR A
    JMP ($E120)
    ADC $5334
    ROR $3D76
LABEL_08: BCS LABEL_08
    ADC ($DD),Y
    ADC $73,X
    ROR $A3,X
    SEI
    ADC $4001,Y
    ADC $6168,X
    ROR $50E3,X
LABEL_09: STA ($07,X)
    STY $C1
    STA $3C
    STX $82
    DEY
    TXA
    STY $D1A1
    STA $7DD2
    STX $51E3
LABEL_10: BCC LABEL_10
    STA ($3B),Y
    STY $03,X
    STA $21,X
    STX $0E,Y
    TYA
    STA $A2FF,Y
    TXS
    STA $0AFB,X
LABEL_11: LDY #$06
    LDA ($0A,X)
    LDX #$C6
    LDY $C8
    LDA $90
    LDX $CE
    TAY
    LDA #$33
    TAX
    LDY $DD3D
    LDA $CD98
    LDX $E51D
LABEL_12: BCS LABEL_12
    LDA ($F3),Y
    LDY $E0,X
    LDA $F7,X
    LDX $F1,Y
    CLV
    LDA $CEAA,Y
    TSX
    LDY $6EE1,X
    LDA $095C,X
    LDX $98EB,Y
LABEL_13: CPY #$DE
    CMP ($45,X)
    CPY $71
    CMP $E3
    DEC $B5
    INY
    CMP #$74
    DEX
    CPY $0E77
    CMP $C1FF
    DEC $12DD
LABEL_14: BNE LABEL_14
    CMP ($CA),Y
    CMP $41,X
    DEC $81,X
    CLD
    CMP $7063,Y
    CMP $999A,X
    DEC $55D2,X
LABEL_15: CPX #$E5
    SBC ($FD,X)
    CPX $C9
    SBC $70
    INC $83
    INX
    SBC #$C8
    NOP
    CPX $2EF5
    SBC $56CE
    INC $CF16
LABEL_16: BEQ LABEL_16
    SBC ($6E),Y
    SBC $DD,X
    INC $B7,X
    SED
    SBC $8429,Y
    SBC $2BE1,X
    INC $B023,X