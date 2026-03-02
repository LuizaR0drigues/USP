#func sem retorno

def print_parametro(x):
    print('imprimindo a variavel x')
    print(x)
    print('')

a = 10
print('Func sem retorno')
print_parametro(a)
nome = 'Katniss Everdeeen'
print_parametro(nome)

#func com retorno

def soma(x, y):
    return x + y

a = 10
b = 88
c = soma(a, b)
print('Func com retorno')
print(c)