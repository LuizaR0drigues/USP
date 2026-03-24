# strcpy estático (copia uma string para outra)

.data
.align 0              # Alinha a memória para dados do tipo char (byte)

str_src: .asciz "Ada Lovelace"   # String de origem (terminada em '\0')
str_dst: .space 15               # Reserva 15 bytes para a string destino

.text
.align 2              # Alinha para palavras (32 bits)
.globl main           # Define o ponto de entrada

main:
    # ===== Inicialização =====
    la t0, str_src    # t0 recebe endereço da string de origem
    la t1, str_dst    # t1 recebe endereço da string de destino

loop_cpy:
    # ===== Copia 1 caractere por vez =====
    lb s0, 0(t0)      # s0 recebe o conteudo da posicao 0(t0)  → lê 1 byte da origem
    sb s0, 0(t1)      # 0(t1) recebe o conteudo de s0  → escreve 1 byte no destino

    # ===== Avança para o próximo caractere =====
    addi t0, t0, 1    # t0 = t0 + 1 (próximo byte da origem)
    addi t1, t1, 1    # t1 = t1 + 1 (próximo byte do destino)

    # ===== Verifica fim da string =====
    bne s0, zero, loop_cpy  
    # Se o caractere NÃO for '\0' (zero), continua copiando
    # Quando for '\0', a cópia termina (fim da string)

    # ===== Impressão da string copiada =====
    addi a7, zero, 4  # Serviço 4: imprimir string
    la a0, str_dst    # a0 ← endereço da string destino
    ecall             # imprime "Ada Lovelace"

    # ===== Finalização =====
    addi a7, zero, 10 # Serviço 10: encerrar programa
    ecall