#test for branch if not equal
addi a1, a1, 100
addi a2, a2, 70
addi a3, a3, 40
sub a1, a2, a3
bne a2,a3, iamLoop
jal iamNOTLOOP
iamNOTLOOP:
addi a1, a1, 1
jal DONE
iamLoop:
addi a1, a1, 6
jal DONE
DONE:
jr ra
