#test for when a2>a3 - branch taken
addi a1, a1, 100
addi a2, a2, -40
addi a3, a3, -10
sub a1, a2, a3
bge a3,a2, iamLoop
jal iamNOTLOOP
iamNOTLOOP:
addi a1, a1, 1
jal DONE
iamLoop:
addi a1, a1, 6
jal DONE
DONE:
jr ra
