*=$2000 ; Locate data @ $2000
	SCALE.=4096
	angle .= 0
	.rept 256+64
		.sin angle,256,SCALE
		angle .= angle + 1
	.endr

