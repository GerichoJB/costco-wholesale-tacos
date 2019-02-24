.data
	menu:       .asciiz     "Press 1 for Compare, 2 for Concatenation, 3 for length, 4 for reverse or 5 for exit\n"
	#strComp---------------------------------------------------------------------------------------------------------
	promptComp: .asciiz     "Enter string to Compare:  "
	eqmsg:      .asciiz     "strings are equal\n"
	nemsg:      .asciiz     "strings are not equal\n"
	str1:       .space      80
	str2:       .space      80
	#strConcat--------------------------------------------------------------------------------------------------------
	first:      .asciiz     "First string: "
	last:       .asciiz     "Second string: "
	full:       .asciiz     "Full string: "
	newline:    .asciiz     "\n"
	string1:    .space      256             # buffer for first string
	string2:    .space      256             # buffer for second string
	string3:    .space      512             # combined output buffer
	#strLen-----------------------------------------------------------------------------------------------------------
	promptLen:
	 .asciiz "Enter a string of characters: "
	str:
	.space	1024     # Allocate 1024 bytes for the input string
	r1:	 .asciiz "The string \""
	r2:	 .asciiz "\" has "
	r3:	 .asciiz " characters."
	#strReverse--------------------------------------------------------------------------------------------------------
	promptRev: .asciiz "Enter String to be reversed: "
	input:	.space	256
	output:	.space	256


.text
main:
#-----------------------------------------------------------------------------------------------------------------------------------
    # Menu
    la      $a0,menu
    li      $v0,4
    syscall
    #get value from user
    li $v0, 5
    syscall
    move $t0, $v0 #t0 has user input
    # 1 for compare
    beq $t0, 1, strComp
    # 2 for concat
    beq $t0, 2, strConcat
    # 3 for length
    beq $t0, 3, strLen
    # 4 for reverse
    beq $t0, 4, strReverse
    # 5 for exit
    beq $t0, 5, exit
#------------------------------------------------------------------------------------------------------------------------------------

strComp:    
    # get first string
    la      $s2,str1
    move    $t2,$s2
    jal     getstr
    # get second string
    la      $s3,str2
    move    $t2,$s3
    jal     getstr
# string compare loop (just like strcmp)
cmploop:
    lb      $t2,($s2)                   
    lb      $t3,($s3)                   
    bne     $t2,$t3,cmpne               
    beq     $t2,$zero,cmpeq             
    addi    $s2,$s2,1                   
    addi    $s3,$s3,1                   
    j       cmploop

# strings are _not_ equal -- send message
cmpne:
    la      $a0,nemsg
    li      $v0,4
    syscall
    j       main

# strings _are_ equal -- send message
cmpeq:
    la      $a0,eqmsg
    li      $v0,4
    syscall
    j       main
    
getstr:
    # prompt the user
    la      $a0,promptComp
    li      $v0,4
    syscall
    # read in the string
    move    $a0,$t2
    li      $a1,79
    li      $v0,8
    syscall             
    jr      $ra

#string Concat----------------------------------------------------------------------------------------------------------------------        
strConcat:
    # prompt and read first string
    la      $a0,first               
    la      $a1,string1            
    jal     prompt
    move    $s0,$v0                 

    # prompt and read second string
    la      $a0,last                
    la      $a1,string2             
    jal     prompt
    move    $s1,$v0                 

    # point to combined string buffer
    la      $a0,string3
    la      $a1,string1
    jal     strcat
    la      $a1,string2
    jal     strcat
    j       print_full

# show results
print_full:
    # output the prefix message for the full string
    li      $v0,4
    la      $a0,full
    syscall
    # output the combined string
    li      $v0,4
    la      $a0,string3
    syscall
    # finish the line
    li      $v0,4
    la      $a0,newline
    syscall
    j       main
    
prompt:
    # output the prompt
    li      $v0,4                   
    syscall
    # get string from user
    li      $v0,8                   
    move    $a0,$a1                 
    li      $a1,256                
    syscall
    li      $v1,0x0A                
    move    $a1,$a0                 

# strip newline and get string length
prompt_nltrim:
    lb      $v0,0($a0)              
    addi    $a0,$a0,1               
    beq     $v0,$v1,prompt_nldone    
    bnez    $v0,prompt_nltrim      

prompt_nldone:
    subi    $a0,$a0,1               
    sb      $zero,0($a0)           
    sub     $v0,$a0,$a1             
    jr      $ra                    

strcat:
    lb      $v0,0($a1)              
    beqz    $v0,strcat_done        

    sb      $v0,0($a0)              

    addi    $a0,$a0,1               
    addi    $a1,$a1,1               
    j       strcat

strcat_done:
    sb      $zero,0($a0)           
    jr	    $ra                    
                                
#strLen-----------------------------------------------------------------------------------------------------------------------------------                                                          
strLen:
# Get the string from user
	li	$v0, 4		
	la	$a0, promptLen	
	syscall			
	la	$a0, promptLen	
	li	$v0, 8		
	la	$a0, str	
	li	$a1, 1024	
	syscall			
# Compute string length
	la	$s0, str	
	add	$s2, $0, $0	
	addi	$s3, $0, '\n'	
loop:
	lb	$s1, 0($s0)	
	beq	$s1, $s3, end	
	addi	$s2, $s2, 1	
	addi	$s0, $s0, 1	
	j	loop
end:
	sb	$0, 0($s0)	
# Output
	li	$v0, 4		
	la	$a0, r1		
	syscall			
	li	$v0, 4		
	la	$a0, str	
	syscall			
	li	$v0, 4		
	la	$a0, r2		
	syscall			
	li	$v0, 1		
	add	$a0, $s2, $0	
	syscall			
	li	$v0, 4		
	la	$a0, r3		
	syscall	
	li	$v0, 4		
	la	$a0, newline	
	syscall				
# to main
	j       main
	
#-----------------------------------------------------------------------------------------------------------------------------------------
strReverse:
	la      $a0,promptRev
        li      $v0,4
        syscall
	li	$v0, 8			
	la	$a0, input		
	li	$a1, 256		
	syscall
	jal	strlen			
	add	$t1, $zero, $v0		
	add	$t2, $zero, $a0		
	add	$a0, $zero, $v0		
	
reverse:
	li	$t0, 0			
	li	$t3, 0			
	reverse_loop:
	add	$t3, $t2, $t0		
	lb	$t4, 0($t3)		
	beqz	$t4, exitRev		
	sb	$t4, output($t1)		
	subi	$t1, $t1, 1		
	addi	$t0, $t0, 1		
	j	reverse_loop		
	
exitRev:
	li	$v0, 4			
	la	$a0, output		
	syscall	
	li	$v0, 4			
	la	$a0, newline		
	syscall
	j       main

strlen:
	li	$t0, 0
	li	$t2, 0
	strlen_loop:
	add	$t2, $a0, $t0
	lb	$t1, 0($t2)
	beqz	$t1, strlen_exit
	addiu	$t0, $t0, 1
	j	strlen_loop	
	strlen_exit:
	subi	$t0, $t0, 1
	add	$v0, $zero, $t0
	add	$t0, $zero, $zero
	jr	$ra
	                                                                                                              
# exit program----------------------------------------------------------------------------------------------------------------------------
exit:
    li      $v0,10
    syscall