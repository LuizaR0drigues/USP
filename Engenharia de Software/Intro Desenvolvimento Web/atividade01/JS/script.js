class Refri{
    constructor(sabor, preco, imagem){
        this.sabor =  sabor
        this.preco = preco
        this.imagem = imagem
    }

}

fetch(
    'https://api.jsonbin.io/v3/b/69d64173aaba882197d7779a')
    .then(response => {
        if (!response.ok) {
            //apresenta o codigo do erro
        throw new Error('Erro na requisição: '+ response.status)
        }
        //verifica erros
        return response.json()
    })
    .then(data => {
        //pega os dados da api
        const dados = data.record.bebidas;
        
        //transformando os items em objetos Refri
        const listaRefris = dados.map(item => {
            
            return new Refri(item.sabor, item.preco, item.imagem);
        });

        ////imprime a lista de REFRIS
        console.log("Dados recebidos: ", listaRefris);

        //percorre os  elem
        listaRefris.forEach(refri => {
            console.log(`Sabor: ${refri.sabor}, Preço: ${refri.preco}`);
        })

         const menu  =  document.querySelector('.tipos_refri');
         const visor  =  document.querySelector('.visor_refri');

         listaRefris.forEach(refri => {
            //card do visor
            const card = document.createElement('div')
            card.classList.add('card_refri')

            const opcao = document.createElement('li');

            const img = document.createElement('img')
            img.src = refri.imagem;
            img.alt = `Garrafa de ${refri.sabor}`;
            img.classList.add('img-refri');

            const titulo = document.createElement('h5')
            titulo.innerText = refri.sabor;

            const preco = document.createElement('p');
            preco.innerText = `R$ ${refri.preco.toFixed(2)}`;

            
            //cardapio
            opcao.innerText = `${refri.sabor} -> R$ ${refri.preco}`;
            
            //montando o card
            card.appendChild(titulo);
            card.appendChild(img);
            card.appendChild(preco)
            //add na estrutura
            menu.appendChild(opcao);
            visor.appendChild(card);
           
    })
    })
    .catch(err => {
        console.error("Algo deu errado: ", err.message);
        console.log(err);
    
    });

   