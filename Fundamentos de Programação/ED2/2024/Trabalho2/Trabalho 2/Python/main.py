

#similar a struct
class Aluno:
    def __init__(self,nome, mediA, depe):
        self.nome  = nome
        self.medp = media
        self.dp = depe
        


 
#selection sort
#achar o auxelemento e por ele nas primeiras posições
def selection_sort(vetor,  tam):

    for i in range(len(vetor)):#segue a ordem
       aux = i
       for j in range(i+1, tam):#pega o proximo
            print("Vetor antes: ", vetor[j].nome, vetor[aux].nome)
            if vetor[j].medp < vetor[aux].medp and vetor[j].dp < vetor[aux].dp: 
                aux = j   
            elif vetor[j].medp >= vetor[aux].medp and vetor[j].dp  >= vetor[aux].dp: 
                if(vetor[j].nome > vetor[aux].nome):
                    aux = j
           
       temp = vetor[aux]
       vetor[aux ] = vetor[i]
       vetor[i] = temp
     

   



def merge_sortMedia(array):
   if len(array)>1:
       mid = int(len(array)/2)
       left = array[:mid] # dividindo o vetor em duas partes direita e esquerta
       right = array[mid:]
       
       #usando recursão para ordenar os dois subvetores
       merge_sortMedia(left)
       merge_sortMedia(right)

       i, j, k = 0,0,0
       while j< len(left) and i<len(right):
           #ordenando por medi2
           if right[i].medp > left[i].medp:
            array[k] = right[i]
            i+=1
           else:
               array[k] = left[j]
               j+=1
           k+=1
       
       while i< len(right):
           array[k] =right[i]
           i+=1
           k+=1
       while j<len(left):
           array[k] = left[j]
           j+=1
           k+=1
       return array 

#main
#Entrada de dados
T = int(input())
na, nbol = [int(x) for x in  input().split()]
aluno = []

#split() le como um vetor com 3 caixinhas
#leitura dos dados de entrada
for i in range(na):
    media, reprova, nome= input().split()
    aluno.append(Aluno(nome, float(media),int( reprova)))



if T == 1:
   selection_sort(aluno, na)
   print(nbol)

   for i in range(nbol): 
     print(aluno[i].nome)


elif T == 2:

    merge_sortMedia(aluno)
    print(nbol)
    for i in range(nbol):
     
     print(aluno[i].nome)
    
   