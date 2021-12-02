	* = $2000
FEAT_FILTER = 0
FEAT_BASS16 = 1

	.IF FEAT_FILTER .OR FEAT_BASS16
trackn_command		.byte 1
	.ENDIF


data.cmd	.byte 0
data.len	.byte 1

	lda #255
	sta data.cmd