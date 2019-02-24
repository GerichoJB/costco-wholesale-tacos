.data
prompt:
	 .asciiz "Enter a string of characters: "
str:
.space	1024     # Allocate 1024 bytes for the input string
r1:	 .asciiz "The string \""
r2:	 .asciiz "\" has "
r3:	 .asciiz " characters."
newline: .asciiz "\n"
	
.text
main:
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
# Exit Gracefully
	li	$v0, 10
	syscall