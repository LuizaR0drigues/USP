palavra = []
vogais = []
conso = []

palavra = input()

for letras in palavra:
    if letras.lower() in 'aeiou':  # Verifica se a letra é uma vogal
        vogais.append(letras)
    else:
        conso.append(letras)
# Concatena as listas em strings
vogaiss = ''.join(vogais)
consos= ''.join(conso)
print(f'Vogais: {vogaiss}')
print(f'Consoantes: {consos}')  

