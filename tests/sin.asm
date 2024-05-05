	* = $2000

SCALE = 4096; 

	; Some sample SIN test
	.sin 0, 256, $1000
	.sin 64, 256, $1000
	.sin 128, 256, $1000
	.sin 192, 256, $1000

	.sin 21, 256, $1000 ; 30 degrees 

	; Create a 16-bit SIN table. 256 steps, scale by 4096 ($1000)
	angle .= 0
	.rept 256
		.sin angle, 256, SCALE
		angle .= angle + 1
	.endr

	; Create a 16-bit SIN and COS table. 256 steps, scale by 4096 ($1000)
	; COS is offset from SIN by 90 degrees, so starts at 90/360 * 256 = 64
	angle .= 0
	.rept 256+64
		.sin angle,256,SCALE
		angle .= angle + 1
	.endr

	; Here is a sample for a combined SIN/COS table with Low (LSB) and High (MSB) split into their own tables.
	angle .= 0
	.rept 256+64
		.sin <,angle,256,SCALE
		angle .= angle + 1
	.endr
	angle .= 0
	.rept 256+64
		.sin >,angle,256,SCALE
		angle .= angle + 1
	.endr

	; 16-bit COS table
	angle .= 0
	.rept 256
		.cos angle, 256, SCALE
		angle .= angle + 1
	.endr
	
