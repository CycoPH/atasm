	* = $2000

location	.byte 0
	.byte <location
	.byte >location

BOB = 16

	.byte 14%%10
	.byte 128%%10
	
table	
	r .= 0
	.rept 5%%255
	;.byte [r*13].MODBOB
	.byte [r*13]%%BOB
	r .= r + 1
	.endr
	

Modulus10Table .rept 10
	.byte [*-Modulus10Table]%%10
	.endr
