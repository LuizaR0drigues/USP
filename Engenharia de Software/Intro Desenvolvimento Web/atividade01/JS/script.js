
class Refri {
    constructor(sabor, preco, imagem) {
        this.sabor = sabor
        this.preco = parseFloat(preco)
        this.imagem = imagem
    }

}
class Maquina {
    
        static saldoRef = 0;
        static saldoMoed = 0;
        static troco = 0;
        static refriSelect = null;
    
    //contabiliza os valores ao selecionar
    static selecionarRefri(objRefri) {

        this.refriSelect = objRefri;
        this.saldoRef = objRefri.preco;


        const p_total = document.querySelector('.total');
        if (p_total) { //atualiza o valor do visor
            p_total.innerText = `Total Refri: R$ ${this.saldoRef.toFixed(2)}`;
            this.Pagamento();
        }

    }


    static somaMoeda(valorButton) {
        const valor_num = parseFloat(valorButton);
        this.saldoMoed += valor_num;
        console.log(this.saldoMoed);

        const p_moeda = document.querySelector('.total_moeda');
        if (p_moeda) { //atualiza o valor do visor
            p_moeda.innerText = `Inserido: R$ ${this.saldoMoed.toFixed(2)}`;
        }

    }
    static Pagamento() {
        const p_status = document.querySelector('.total-refri');
        const div_entrega = document.querySelector('.refri');

        if (!p_status || !div_entrega || !this.refriSelect) return;

        if (this.saldoMoed < this.saldoRef) {
            p_status.innerText = 'Aguardando Moedas...';
            div_entrega.innerHTML = 'vazio'; // clear
        }
        else {
            //calcula o troco
            this.troco = this.saldoMoed - this.saldoRef;

            //Msg de aprovação
            p_status.innerHTML = `PAGAMENTO APROVADO! <br> ${this.troco > 0 ? `Troco: R$ ${this.troco.toFixed(2)}` : ''}`;

            //mostra a imagem do refri
            div_entrega.innerHTML = `<img src="${this.refriSelect.imagem}" alt="${this.refriSelect.sabor}" style="width: 50px; animation: slideDown 0.5s;">`;

            // Zera os saldos para a proxima compra
            this.saldoMoed = 0;
            this.saldoRef = 0;
            this.troco = 0;
            this.refriSelect = null;
        }
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
                Maquina.selecionarRefri(refri); //calculando os valor e mostra o valor
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
                if (valorMoeda) {
                    Maquina.somaMoeda(parseFloat(valorMoeda));
                    Maquina.Pagamento();
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

