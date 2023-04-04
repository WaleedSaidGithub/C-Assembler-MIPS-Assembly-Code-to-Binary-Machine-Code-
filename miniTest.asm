main:
    addi $t0, $0, 100
    addi $t1, $0, 0
    addi $s0, $0, 0
loopstart:
    slt $t2, $t1, $t0
    beq $t2, $0, loopend
    mult $t1, $t1
    mflo $t3
    add $s0, $s0, $t3
    addi $t1, $t1, 1
    j loopstart
loopend:
end:
    j end
