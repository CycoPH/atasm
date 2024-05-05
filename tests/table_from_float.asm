* = $2000

	; Calc a perspective table as bytes
	d .= $100
	oz .= $80
	Z .= -128
	.REPT 256
		.float2u8 $FF*d/(d+oz+Z)+0.5
		Z .= Z + 1
	.ENDR

	; Calc a perspective table in LSB/MSB format
	d .= $100
	oz .= $80
	Z .= -128
	.REPT 256
		.FLOAT2U16LH $FF*d/(d+oz+Z)+0.5
		Z .= Z + 1
	.ENDR

	; Calc a perspective table in MSB/LSB format
	d .= $100
	oz .= $80
	Z .= -128
	.REPT 256
		.FLOAT2U16LH $FF*d/(d+oz+Z)+0.5
		Z .= Z + 1
	.ENDR

	; Val = X * 0.666666 in Low High format
	x .= 0
	.REPT 10
		.FLOAT2U16LH x*0.666666
		x .= x + 1
	.ENDR

	; Val = X * 0.666666 in High Low format
	x .= 0
	.REPT 10
		.FLOAT2U16HL x*0.666666
		x .= x + 1
	.ENDR

	; Val = X * 0.666666 in 8-bit format
	x .= 0
	.REPT 10
		.FLOAT2U8 x*0.666666
		x .= x + 1
	.ENDR
