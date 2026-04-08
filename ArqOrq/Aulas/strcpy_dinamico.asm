.data
.align 0                      # Alinha a memória para bytes (char)

str_src: .asciz "Margaret Hamilton"   # String de origem (terminada em '\0')

.align 2                      # Alinha para palavra (4 bytes)
ptr_dst: .word 0              # Variável que vai guardar o ponteiro para a heap


.text
.align 2                      # Alinha instruções em palavras
.globl main

main:
    # ===== 1. CALCULAR TAMANHO DA STRING =====
    # t0 → percorre a string
    # t3 → contador de caracteres

    la t0, str_src            # t0 recebe o endereço da string
    addi t3, zero, 0          # t3 = 0 (contador começa em zero)

loop_tam:
    lb s0, 0(t0)              # s0 recebe o byte apontado por t0

    addi t0, t0, 1            # avança para o próximo caractere
    addi t3, t3, 1            # incrementa o contador

    bne s0, zero, loop_tam    # se NÃO for '\0', continua o loop

    # Aqui t3 contém o tamanho da string (incluindo o '\0')


    # ===== 2. ALOCAR MEMÓRIA NA HEAP =====
    addi a7, zero, 9          # serviço 9: alocação dinâmica (malloc)
    add a0, zero, t3          # a0 recebe o tamanho a ser alocado
    ecall                     # retorna em a0 o endereço alocado

    # ===== 3. GUARDAR O PONTEIRO =====
    la t1, ptr_dst            # t1 recebe o endereço da variável ponteiro
    sw a0, 0(t1)              # ptr_dst recebe o endereço da heap


    # ===== 4. COPIAR STRING PARA HEAP =====
    la t0, str_src            # t0 ← início da string origem
    lw t2, 0(t1)              # t2 ← endereço da área alocada (destino)

loop_cpy:
    lb s0, 0(t0)              # s0 recebe 1 byte da origem
    sb s0, 0(t2)              # destino recebe esse byte

    addi t0, t0, 1            # avança origem
    addi t2, t2, 1            # avança destino

    bne s0, zero, loop_cpy    # continua até copiar o '\0'


    # ===== 5. IMPRIMIR STRING COPIADA =====
    addi a7, zero, 4          # serviço 4: imprimir string
    la t1, ptr_dst            # t1 aponta para o ponteiro
    lw a0, 0(t1)              # a0 recebe o endereço da string na heap
    ecall                     # imprime a string


    # ===== 6. FINALIZAR PROGRAMA =====
    addi a7, zero, 10         # serviço 10: encerrar
    ecall