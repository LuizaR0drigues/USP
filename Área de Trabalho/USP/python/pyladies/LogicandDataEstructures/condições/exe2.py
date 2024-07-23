velocidade = int(input("Digite a velocidade do carro: \n"))
print(velocidade)
if velocidade > 80:
    multa = (velocidade - 80) * 7
    print(f'O valor da multa será: {multa}')
else:
    print('Parabens por respeitar as regras de trânsito :)')