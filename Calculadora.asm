.data
error_msg: .asciiz "Nao foi possivel calcular" 
num: .word 5, 2 #números a serem utilizados nas funções

.text 
 main:
la      $t0, num #carrega o endereço do vetor

# espaço para chamada de funções #
#exemplos
jal     main_fatorial
jal 	main_add
#encerramento do programa
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
	j      	end2


main_div:
	lw      $s0, 0($t0)
	lw      $s1, 4($t0)
	beq     $s1, $zero, error #caso o divisor seja zero, dá erro
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
	lw     	$s0, 0($t0)
	lw  	$s2, 0($t0)
	lw  	$s1, 4($t0)
	li      $t2,1
while:
	beq     $t2,$s1,end2
	mul     $s2,$s2,$s0
	add     $t2,$t2,1
	j       while


main_fatorial:
	lw	$s2, 0($t0)
	lw	$t1, 0($t0) #$t1 contém o número de vezes que precisamos multiplicar
	beqz    $s2, error #não pode calcular fatorial de zero
	bltz    $s2, error #não pode calcular fatorial de numero negativo
fact: 
	subi    $t1, $t1, 1 #decrementa
	beqz    $t1, end
	mul     $s2, $s2, $t1 #multiplica
	sw      $s2, 0($t0) #armazena
	j 	    fact #repete


main_fibonacci:
	lw 	$t2, 0($t0) #coloca em $t2 o numero de vezes que precisamos somar
	blez 	$t2, error #verifica se o número é maior que zero
	li	$s3, 1 #inicializa primeiro elemento
	li 	$s4, 1 #inicializa segundo elemento
	sw 	$s4, 0($t0) #guarda na lista
	la      $s2, ($s4) #guarda no registrador de saída
	addi 	$t2, $t2, -2 #$t2 = $t2 - 2
	blez 	$t2,  end3 # se $t2 <= 0, achamos o elemento e sai da função
	j       Loop #repete o processo
Loop:
	add 	$s5 $s3 $s4
	addi 	$t2, $t2, -1
	sw 	$s5, 0($t0)
	la      $s2, ($s5)
	blez 	$t2,  end3
	add	$s3, $s5, $s4
	addi 	$t2, $t2, -1
	sw	$s3, 0($t0)
	la      $s2, ($s3)
	blez 	$t2,  end3
	add	$s4, $s5, $s3
	addi 	$t2, $t2 -1
	sw	$s4, 0($t0)
	la      $s2, ($s4)
	blez 	$t2, end3
	bgtz 	$t2, Loop

#saída das funções
end:
	sw      $s2,0($t0) #apenas atualiza primeiro elemento da lista
	j end3
end2: 
	sw      $s2, 4($t0) #armazena no segundo elemento da lista 
	addi    $t0 $t0 4 #atualiza posição inicial da lista
end3:
	jr    	$ra #volta para o main

#encerramento de programa mostrando resultado
exit: 
	la       $a0, ($s2)
	li      $v0,1
	syscall 
	li      $v0, 10
	syscall

#encerramento de programa com mensagem de erro
error:
	la       $a0, error_msg
	la       $v0, 4
	syscall
