*=$2000

SINCOS_SCALE = 253 << 5 ; = $1fa0, but can be 255 << 5 ($1fe0) as a maximum, given current range of input coordinates
; SM: could be calculated as the largest number that can support full range of 8-bit vertex coordinates without overflow 

	angle .= 0
    .REPT $140
		.sin <,angle,256,SINCOS_SCALE
		angle .= angle + 1
    .endr
	angle .= 0
    .REPT $140
		.sin >,angle,256,SINCOS_SCALE
		angle .= angle + 1
    .ENDR
trigtable_end:


perspective:
	d .= $100
    oz .= $80
	Z .= -128
	.REPT 256
		.float2u8 $FF*d/(d+oz+Z)+0.5
		Z .= Z + 1
	.ENDR  