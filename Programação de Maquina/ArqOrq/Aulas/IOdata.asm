.data
.align 0              # Alinha a memória para dados do tipo char (byte a byte)

str_positivo: .asciz "Hello World! ++"   # String para número >= 0
str_negativo: .asciz "Hello World! --"   # String para número < 0


.text
.align 2              # Alinha a memória para palavras (32 bits)
.globl main           # Torna o rótulo 'main' visível (ponto de entrada)

main:
    # ===== Leitura de um inteiro =====
    addi a7, zero, 5  # Código 5: serviço de leitura de inteiro
    ecall             # Chama o sistema -> resultado vai para a0

    add s0, a0, zero  # Copia o valor lido (a0) para s0

    # ===== Comparação =====
    blt s0, zero, print_negativo  
    # Se s0 < 0, desvia para 'print_negativo'

    # ===== Caso número >= 0 =====
    addi a7, zero, 4  # Código 4: imprimir string
    la a0, str_positivo  # Carrega endereço da string positiva em a0
    ecall             # Imprime "Hello World! ++"

    j the_end         # Pula para o final do programa


print_negativo:
    # ===== Caso número < 0 =====
    addi a7, zero, 4  # Código 4: imprimir string
    la a0, str_negativo  # Carrega endereço da string negativa para a0
    ecall             # Imprime "Hello World! --"


the_end:
    # ===== Impressão do número digitado =====
    addi a7, zero, 1  # Código 1: imprimir inteiro
    add a0, zero, s0  # Move o valor de s0 para a0
    ecall             # Imprime o número

    # ===== Encerramento do programa =====
    addi a7, zero, 10 # Código 10: finalizar programa
    ecall