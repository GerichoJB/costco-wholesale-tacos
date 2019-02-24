.data
	prompt:     .asciiz     "Enter string to Compare:  "
	dot:        .asciiz     "."
	eqmsg:      .asciiz     "strings are equal\n"
	nemsg:      .asciiz     "strings are not equal\n"
	str1:       .space      80
	str2:       .space      80

.text
main:
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
    j       exit

# strings _are_ equal -- send message
cmpeq:
    la      $a0,eqmsg
    li      $v0,4
    syscall
    j       exit
    
getstr:
    # prompt the user
    la      $a0,prompt
    li      $v0,4
    syscall
    # read in the string
    move    $a0,$t2
    li      $a1,79
    li      $v0,8
    syscall             
    jr      $ra                         
# exit program
exit:
    li      $v0,10
    syscall