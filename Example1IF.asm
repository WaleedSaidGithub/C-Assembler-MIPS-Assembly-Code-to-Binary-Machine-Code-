          .text #everything after "text" is your actual code
	        .align 2 #directive that aligns all labels in memory, ignore this for now
	        .globl main #Speficies that "main" is the starting label for this program

main:
  addi $s0, $zero, 8  # a= 3
  addi $s1, $zero, 9  # b = 9
  addi $s2, $zero, 20  #c = 20



  addi $t0, $zero, 4 #(t0 = 4)
  slt $t0, $s0, $t0 # (t0 = (a < 4))
  beq $t0, $zero, endif
  add $s0, $zero, $s1 #(a = b)
  j endelse
endif:
  add $s0, $zero, $s2 #(a = c)
endelse:




  addi $v0, $zero, 10 #These two lines cause QTSPIM to not error when your program ends
  syscall #Don't worry about them now, we'll understand what they do later.
