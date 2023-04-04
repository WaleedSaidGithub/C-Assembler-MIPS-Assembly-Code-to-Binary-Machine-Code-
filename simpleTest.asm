main:
    j begin
f:
    addi $v0, $a0, 10
    jr $ra
    addi $v0, $a0, 100
begin:
    addi $a0, $0, 20
    jal f
    addi $s0, $v0, 0
    addi $a0, $0, 40
    jal f
    addi $s1, $v0, 0
end:
    j end
