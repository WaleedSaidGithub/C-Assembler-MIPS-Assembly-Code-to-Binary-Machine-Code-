          .data #memoized DP calculation of f(x) = f(x-1) + f(x//2) + x^2
          .text #f(0) = 0
          .align 2
          .globl main
main:
  addi $a0, $zero, 10 #a0 = n
  add $a0, $zero, $t1
  sub $sp, $sp, $t0 #create an array of size n+1
  mult $s0, $s1
  beq $t2, $zero, firstcalldone
  div $s1, $s0
  mflo $v0
firstcalldone:
  mfhi $t0
  sll $t1, $t0, 2
  srl $t0, $s0, 1
  sw $t0, 0($t1)
  lw $s1, 0($t1)
  sw $ra, 12($sp)
  slt $t2, $s1, $zero
  beq $t2, $zero, firstcalldone
  j main
  jal firstcalldone
  jr $ra
  jalr $t3, $ra
