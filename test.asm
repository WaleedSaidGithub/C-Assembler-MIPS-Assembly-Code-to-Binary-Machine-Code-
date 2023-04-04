main:
    addi $s0, $0, 0
    addi $t0, $0, 10
loop:
    add $s0, $t0, $s0
    addi $t0, $t0, -1
    bne $t0, $0, loop
end:
    j end
