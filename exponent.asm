.data 		
 promptRe: .asciiz "Enter 1 to continue, or any other int to exit "		
 promptX: .asciiz "Enter a number for X: "
 promptY: .asciiz "Enter a number for Y: "
 newline: .asciiz "\n"
 
.text
main:
	li	$v0,	4		
	la	$a0,	promptX 	
	syscall 			
	li 	$v0,	5 		 
	syscall 			
	move 	$s0,	$v0 		
	li	$v0,	4		
	la	$a0,	promptY		
	syscall 			
	li 	$v0,	5 		
	syscall 			
	move 	$s1,	$v0 		
	move	$a0,	$s0	
	move	$a1,	$s1		
	jal	exponential		
	move	$a0,	$v0
	li	$v0,	1
	syscall 
	li	$v0,	4		
	la	$a0,	newline 	
	syscall 
	li	$v0,	4		
	la	$a0,	promptRe 	
	syscall 
	#check for value
        li $v0, 5
        syscall
        move $t0, $v0 #t0 has user input
        beq  $t0, 1, continue
        #exit
        li      $v0,10
        syscall
	#continue
	continue:
	j main	
		
exponential: 
	addi	$sp,	$sp,	-4
	sw	$t0,	4($sp)
	move	$t0,	$zero
	li	$v0,	1
loop: 
	beq	$t0,	$a1,	end	
	mul	$v0,	$v0,	$a0	
	addi	$t0,	$t0,	1	
	j	loop			
end:
	#restore $t0 and the stack
	lw	$t0,	4($sp)
	addi	$sp,	$sp,	4
	jr	$ra
