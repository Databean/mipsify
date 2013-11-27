printInt:
	li $v0, 1
	lw $a0, 0($a0)
	syscall
	jr $ra

printString:
	li $v0, 4
	lw $a0, 0($a0)
	syscall
	jr $ra
	
readInt:
	li $v0, 5
	syscall
	jr $ra

sbrk:
	li $v0, 9
	lw $a0, 0($a0)
	syscall
	jr $ra

exit:
	li $v0, 10
	lw $a0, 0($a0)
	syscall
	jr $ra

exit2:
	li $v0, 17
	lw $a0, 0($a0)
	syscall
	jr $ra