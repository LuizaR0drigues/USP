'''
gerando interalos:
range(start, end, step )

range(10) -> de 0 atté 9

for i in collection: (collection é uma coleção de valores que será alterado)
    instruction 01
    instruction 02

while condition:
    instruction 01
    instruction 02 
'''
#list(range(10))

print(list(range(11,21)))

print(list(range(11,21,2)))

for i in range(0,10,2):
    print(f'i = {i}')
print('') 

print('Elementos pares pra uma dada sequencia')
for i in range(12,30,2):
    print(i)
print('')

i = 0
while i < 10:
    print(f'i = {i}')
    i+=1
