
#semelhante ao tipo de dado em C
class LinkedList:
    def __init__(self):
        self.head = None #primeiro elemneto vazio
        self._size = 0

    def append(self, elem):
        if self.head:
        #inserção quando a lista ja possui elem9AO FINAL)
           pointer = self.head
        #percorrendo a lista em busca do ultimo elem
           while(pointer.prox):
              pointer = pointer.prox 
           pointer.prox = Node(elem)
        #inseridno o primerio elemneto da lista 
        else:
            self.head = Node(elem)
        
        self._size = self._size + 1
        #TAMANHO LISTA
    def __len__(self):
        return self._size
        
    #encontrando itens 
    def __getitem__(self, index):
            pointer = self.head #meu ponteiro é o primeiro elemd
            for i in range(index):
                if pointer:
                    pointer = pointer.prox
                else:
                    raise IndexError("List index out of range")
                
            if pointer:       
                return pointer.data
            else:
                raise IndexError("List out of range")

        #modificando item
    def __setitem__(self, index, elem):
            pointer = self.head #meu ponteiro é o primeiro elemd
            for i in range(index):
                if pointer:
                    pointer = pointer.prox
                else:
                    raise IndexError("List index out of range")
                
            if pointer:       
                pointer.data = elem
            else:
                raise IndexError("List out of range")
            
    #procurando um elemnto na tlista
    def index(self, elem):
        pointer = self.head
        i = 0
        while(pointer):
            if pointer.data == elem:
                return i 
            pointer = pointer.prox
            i += 1
            raise ValueError("{} is not in list".format(elem))

#funções hash
def hash()

##testes
tabela = LinkedList()

T = 