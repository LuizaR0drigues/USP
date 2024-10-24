import random

num = random.randint(0,5)
print("-=-" * 20)
print("Vou pensar num numero entre 0 e 5....")
print("-=-" *20)

flag = 1
while(flag):
    print("-=-" *20)
    jogador = int(input("Que número eu pensei?"))
    print(jogador)
    if jogador == num:
        print("Parabens")
        break
    else:
        print("Não foi dessa vez")