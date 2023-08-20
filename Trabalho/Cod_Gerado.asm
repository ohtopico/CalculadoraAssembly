.data
error_msg: .asciiz "Não foi possivel calcular" 
num: .word 20,

.text 
 main:
la      $t0, num
jal    main_fibonacci
jal     exit

main_add:
lw      $s0, 0($t0)
lw      $s1, 4($t0)
add     $s2 $s0 $s1
j       end2

main_sub:
lw      $s0, 0($t0)
lw      $s1, 4($t0)
sub     $s2 $s0 $s1
j       end2

main_mult:
lw      $s0, 0($t0)
lw      $s1, 4($t0)
mul     $s2, $s0, $s1
j      end2

main_div:
lw      $s0, 0($t0)
lw      $s1, 4($t0)
beq     $s1, $zero, error 
div     $s2, $s0, $s1
j       end2

main_raiz:
lw       $s0, 0($t0)
li       $s2, 0
isqrt:
mul      $t2, $s2, 2
add      $t2, $t2, 1
sub      $s0, $s0, $t2
add      $s2, $s2, 1
beq      $s0, $zero, end
slt      $t2, $s0, $zero
beq      $t2, 1, error
j        isqrt

main_potencia:
lw      $s0, 0($t0)
lw      $s2, 0($t0)
lw      $s1, 4($t0)
li      $t2,1
while:
beq      $t2,$s1,end2
mul      $s2,$s2,$s0
add      $t2,$t2,1
j        while

main_fatorial:
lw	    $s2, 0($t0)
lw	    $t1, 0($t0)	
beqz    $s2, error
bltz    $s2, error
fact: 
subi    $t1, $t1, 1
beqz    $t1, end
mul     $s2, $s2, $t1 
sw      $s2, 0($t0)
j 	    fact 

main_fibonacci:
lw 	    $t2, 0($t0)
blez 	$t2, error
li	    $s3, 1
li 	    $s4, 1
sw 	$s4, 0($t0)
la      $s2, ($s4)
addi 	$t2, $t2, -2
blez 	$t2,  end3
j        Loop
Loop:
add 	    $s5 $s3 $s4
addi 	$t2, $t2, -1
sw 	    $s5, 0($t0)
la       $s2, ($s5)
blez 	$t2,  end3
add	    $s3, $s5, $s4
addi 	$t2, $t2, -1
sw	    $s3, 0($t0)
la       $s2, ($s3)
blez 	$t2,  end3
add	    $s4, $s5, $s3
addi 	$t2, $t2 -1
sw	    $s4, 0($t0)
la       $s2, ($s4)
blez 	$t2, end3
bgtz 	$t2, Loop

end:
sw      $s2,0($t0)
j end3
end2: 
sw      $s2, 4($t0)
addi    $t0 $t0 4
end3:
jr    	$ra

exit: 
la       $a0, ($s2)
li      $v0,1
syscall
li      $v0, 10
syscall

error:
la       $a0, error_msg
la       $v0, 4
syscall
