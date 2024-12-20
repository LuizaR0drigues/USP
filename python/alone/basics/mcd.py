num1 = int(input("Digite o primeiro número: "))
num2 = int(input("Digite o segundo número: "))

while num2 != 0:  # Enquanto num2 não for zero
    print("Entradas: ", num1, num2)
    resto = num1 % num2
    num1 = num2
    num2 = resto
    print("Resto = ", resto)

print("MDC =", num1)  # Quando num2 for zero, num1 contém o MDC
