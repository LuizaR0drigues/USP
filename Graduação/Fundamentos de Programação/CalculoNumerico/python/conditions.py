'''Estrutura Básica de um IF
if condition 01:
    instruction 01
    instruction 02
    
else:
    instruction 03
    instruction 04

or
if condition 01:
    instruction 01
    instruction 02

elif(condition 02):
    instruction 03
    instruction 04
    
else:
    instruction 05
    instruction 06

é possivel de se usar a condição booleana;

and - &&
or - ||
not - !
'''

#utilizando o elif
idade = int(input("Digite a sua idade: "))
if idade < 18:
    print('Menor de idade')
elif 18<= idade < 60:
    print('Adulto')
else:
    print('Idoso')

# operador condicional/ternário
    
x = int(input("Digite um número: "))
print("Par" if x %2 ==0 else "Impar")



