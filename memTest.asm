main:
    addi $t0, $0, 0
    addi $t1, $0, 4
    addi $t2, $0, 8
    addi $t3, $0, 100
    addi $t4, $0, 200
    addi $t5, $0, 300
    sw $t3, 0($t0)
    sw $t4, 4($t0)
    sw $t5, 8($t0)
    lw $s0, 4($t1)
    lw $s1, 0($t1)
    lw $s2, 0($t0)
end:
    j end
