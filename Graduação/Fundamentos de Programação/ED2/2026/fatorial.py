
def fatorial_base(numero):
    ##usando o laço for
    for n in range(numero,0,-1):
        if numero != 0:
            acc = acc * n
        print(acc)

    return acc

def fatorial_recursive(numero):
    #caso base 
    if numero == 0:
        return 1

    print("Fatorial de ", numero - 1)
    return numero * fatorial_recursive(numero - 1)

in_f = int(input("Digite um valor: "))
fatorial = fatorial_recursive(in_f)
print(f"Fatorial de {in_f} = ", fatorial)