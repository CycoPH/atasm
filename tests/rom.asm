* = $c000
main
    brk

    * = $fffa ; nmi vector
    .word $1234

    * = $fffc ; run vector
    .word main

    * = $fffe ; irq vector
    .word $5678