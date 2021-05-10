levelMap = levelData + $1000

* = $600
    lda levelMap+1,x
    lda levelData
    rts

levelData .byte 0