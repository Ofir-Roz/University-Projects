; file ps.as

.entry LENGTH, LOOP
.extern W ,END
MAIN:   mov r11 ,LENGTH
LOOP:   jmp L1(#-1,r6)
        prn -5
        bne W(r4,r5)
        sub r1, r4
        bne L3
L1:     inc K, r4
.entry LOOP
        bne LOOP(K,W)
END:    stop
STR:    .string "abcdef" abcdef
LENGTH: .data   6,-9,15
K:      .data   22
.extern L3
