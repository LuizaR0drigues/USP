.data 
input1: .asciz "Primeiro numero: "
input2: .asciz "Segundo numero: "
resultado: .asciz "O resultado: "

.text
#lendo o primeiro numero
li a7,4  #referente ao print string de outras linguagens
la a0, input1 #passando ao registrador a0 a mensagem que queremos imprimir na tela
ecall

li a7, 5 #para ler um inteiro devemos passar o 5 como id para o registrador  a7
ecall # chama-se o ecall em seguida pq o readint não precisa de argumento de entrada

mv t0, a0 #mv; transferir / salvando no reg temporario o valor contido em a0

#lendo o segundo numero
li a7,4  #referente ao print string de outras linguagens
la a0, input2 #passando ao registrador a0 a mensagem que queremos imprimir na tela
ecall

li a7, 5 #para ler um inteiro devemos passar o 5 como id para o registrador  a7
ecall # chama-se o ecall em seguida pq o readint não precisa de argumento de entrada

mv t1, a0

#soma
add t2, t0, t1 # t2 = t0 + t1

li a7,4  #referente ao print string de outras linguagens
la a0, resultado #passando ao registrador a0 a mensagem que queremos imprimir na tela
ecall

li a7,1
mv a0, t2 #transferindo o que esta em t2 para a0
ecall