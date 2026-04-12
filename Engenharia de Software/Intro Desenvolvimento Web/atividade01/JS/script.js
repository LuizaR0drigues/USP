
class Refri {
    constructor(sabor, preco, imagem) {
        this.sabor = sabor
        this.preco = parseFloat(preco)
        this.imagem = imagem
    }

}
let saldoRef = 0;
let saldoMoed = 0;
let troco = 0;
let refriSelect = null;

//contabiliza os valores ao selecionar
function selecionarRefri(objRefri) {
    
    refriSelect = objRefri;
    saldoRef = objRefri.preco;

  
    const p_total = document.querySelector('.total');
    if (p_total) { //atualiza o valor do visor
        p_total.innerText = `Total Refri: R$ ${saldoRef.toFixed(2)}`;
        Pagamento();
    }

}


function somaMoeda(valorButton) {
    const valor_num = parseFloat(valorButton);
    saldoMoed += valor_num;
    console.log(saldoMoed);

    const p_moeda =  document.querySelector('.total_moeda');
    if (p_moeda) { //atualiza o valor do visor
        p_moeda.innerText = `Inserido: R$ ${saldoMoed.toFixed(2)}`;
    }

}
function Pagamento() {
   const p_status = document.querySelector('.total-refri'); 
    const div_entrega = document.querySelector('.refri');   
    
    if (!p_status || !div_entrega || !refriSelect) return;

    if (saldoMoed < saldoRef) {
        p_status.innerText = 'Aguardando Moedas...';
        div_entrega.innerHTML = 'vazio'; // clear
    } 
    else {
        //calcula o troco
        troco = saldoMoed - saldoRef;

        //Msg de aprovação
        p_status.innerHTML = `PAGAMENTO APROVADO! <br> ${troco > 0 ? `Troco: R$ ${troco.toFixed(2)}` : ''}`;

        //mostra a imagem do refri
        div_entrega.innerHTML = `<img src="${refriSelect.imagem}" alt="${refriSelect.sabor}" style="width: 50px; animation: slideDown 0.5s;">`;
        
        // Zera os saldos 
        saldoMoed = 0;
         saldoRef = 0;
    }
}

//Recebe os itens da api 
//Transforma em objetos e mostra na tela
fetch(
    'https://api.jsonbin.io/v3/b/69d64173aaba882197d7779a')
    .then(response => {
        if (!response.ok) {
            //apresenta o codigo do erro
            throw new Error('Erro na requisição: ' + response.status)
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


        const visor_refri = document.querySelector('.visor_refri');

        listaRefris.forEach(refri => {
            //card do visor
            const card = document.createElement('button');
            card.classList.add('botao-refri-card');
            card.addEventListener('click', () => {
                selecionarRefri(refri); //calculando os valor e mostra o valor
            });


            const img = document.createElement('img')
            img.src = refri.imagem;
            img.alt = `Garrafa de ${refri.sabor}`;
            img.classList.add('img-refri');

            const titulo = document.createElement('h5')
            titulo.innerText = refri.sabor;

            const preco = document.createElement('p');
            preco.innerText = `R$ ${refri.preco.toFixed(2)}`;

            //montando o card
            card.appendChild(titulo);
            card.appendChild(img);
            card.appendChild(preco)
            //add na estrutura
            visor_refri.appendChild(card);
        })
        const moedas = document.querySelectorAll('.op_moedas');
        const visor_moedas = document.querySelectorAll('.coletor-moedas');

        for (let item of moedas) {
            item.draggable = true;
            item.addEventListener('dragstart', function (e) {
                e.dataTransfer.setData('valor', e.target.id);
                
            });
        }

        for (let zone of visor_moedas) {
            zone.addEventListener('dragover', function (e) {
                    e.preventDefault();
                });

            zone.addEventListener('drop', function (e) {
                e.preventDefault();

                const valorMoeda = e.dataTransfer.getData('valor');
                //const itemArrastado = document.getElementById(id);
            if(valorMoeda){
                somaMoeda(parseFloat(valorMoeda));
                Pagamento();
                console.log("Moeda inserida: R$ ", valorMoeda)
            }
                })
                
            }
        }
    )
    .catch(err => {
        console.error("Algo deu errado: ", err.message);
        console.log(err);

    });

