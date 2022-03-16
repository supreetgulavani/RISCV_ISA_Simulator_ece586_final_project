#test for bracnh if greater than or equal to
addi a1, a1, 100
addi a2, a2, 90
addi a3, a3, 90
sub a4, a2, a3
bge a2,a3, iamLoop
jal iamNOTLOOP
iamNOTLOOP:
addi a1, a1, 1
jal DONE
iamLoop:
addi a1, a1, 6
jal DONE
DONE:
jr ra





