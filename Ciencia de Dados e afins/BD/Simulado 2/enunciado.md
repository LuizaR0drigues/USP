# Simulado para a Avaliação Individual — SCC0540 / SCC0640 (Bases de Dados)

> **Contexto:** Baseado no modelo relacional, triggers e consultas do projeto **"Sistema de
Gestão de Eventos e Espaços"** (Grupo: *Quase-Eng-Compers-Relacionais*).
> **Instruções:** Resolva as 5 questões independentes considerando o esquema relacional
original do projeto apresentado no arquivo `Projeto.txt`.
---
## Esquema de Referência (Resumo dos Elementos Relevantes)
- **evento** (`EventoId`, `Nome`, `Inicio`, `Fim`, `Descricao`)
- **promotor** (`PromotorId`, `Email`, `Telefone`, `Nome`, `CEP`, `Numero_endereco`)
- **pessoa_promotor** (`PessoaPId`, `CPF`)
- **organizacao** (`OrganizacaoId`, `CNPJ`)
- **patrocinio** (`EventoId`, `PromotorId`, `Valor`, `Data_patrocinio`)
- **atividade** (`AtividadeId`, `EventoId`, `Nome`, `Descricao`)
- **espaco** (`EspacoId`, `Nome`, `LimitePessoas`, `CEP`, `Numero`, `Rua`, `Bairro`,
`Cidade`, `Estado`)
- **sessao** (`AtividadeId`, `NumeroSessao`, `EspacoId`, `Nome`, `DataHoraInicio`,
`Duracao`, `Vagas`, `Valor`, `DataHoraFim`)
*(PK: `AtividadeId`, `NumeroSessao`)*
- **recursos** (`RecursoId`, `Nome`, `Descricao`)
- **estoque** (`EstoqueId`, `EspacoId`, `RecursoId`, `Quantidade`)
- **recursos_sessao** (`RecursoSessaoId`, `AtividadeId`, `NumeroSessao`, `RecursoId`,
`QtdNecessaria`)
- **participante** (`ParticipanteId`, `CPF`, `Nome`, `DataNascimento`)
- **credenciamento** (`CredenciamentoId`, `ParticipanteId`, `EventoId`, `Organizacao`)
- **inscricao** (`InscricaoId`, `CredenciamentoId`, `AtividadeId`, `NumeroSessao`,
`DataHora`, `Papel`)
---
## Questão 1 — Evolução do Esquema (DDL)
No esquema atual, cada patrocínio (`patrocinio`) associa diretamente um evento a um
promotor através de uma chave primária composta `(EventoId, PromotorId)`. Isso restringe
que um mesmo promotor patrocine um evento em mais de uma cota ou data diferente.
Surgiu um novo requisito: **um promotor poderá realizar múltiplos patrocínios
independentes para o mesmo evento** (por exemplo, cotas adicionais ou repasses em
datas diferentes). Cada patrocínio deverá ter um identificador próprio numérico
(`PatrocinioId`), mantendo os atributos `EventoId`, `PromotorId`, `Valor` e `Data_patrocinio`.
Modifique o esquema para atender a este requisito. Os patrocínios existentes antes da
alteração deverão ser preservados.
*Resposta: apresente apenas o DDL necessário.*
---
## Questão 2 — Trigger (PL/pgSQL)
No sistema, um participante que se credenciou como organizador de um evento
(`credenciamento.Organizacao = TRUE`) **não pode se inscrever como 'ouvinte'** em
nenhuma sessão das atividades daquele evento (organizadores só podem atuar como
`'instrutor'` ou `'palestrante'`).
Implemente a função e o trigger necessários sobre a tabela `inscricao`:
1. Ao inserir ou atualizar uma linha em `inscricao`, verificar se o participante associado
àquele `CredenciamentoId` possui `Organizacao = TRUE`.
2. Se possuir e o papel (`NEW.Papel`) for `'ouvinte'`, a operação deve ser rejeitada com
`RAISE EXCEPTION`.
3. Garanta consistência evitando leituras inconsistentes no momento da validação.
*Resposta: apresente apenas o SQL necessário.*
---
## Questão 3 — Consulta Relacional Complexa (Divisão Relacional)
Considere o evento cujo identificador é `EventoId = 42`.
Deseja-se premiar os participantes mais engajados desse evento.
Escreva uma consulta SQL que retorne o `ParticipanteId`, o `Nome` e o `CPF` de todos os
participantes que satisfazem **simultaneamente** as seguintes condições:
1. Estão credenciados no evento `EventoId = 42`;
2. Estão inscritos com papel `'ouvinte'` em **todas** as sessões de **todas** as atividades
vinculadas a esse evento.
> *Nota:* Considere que o evento possui pelo menos uma sessão cadastrada. Participantes
inscritos em apenas parte das sessões não devem ser retornados.
*Resposta: apresente apenas o SQL.*
---
## Questão 4 — Consulta Analítica (Window Functions / Ranking)
A comissão organizadora deseja ranquear o desempenho de público das atividades dentro
de cada evento.
Para cada evento, liste as **duas atividades com o maior número total de inscritos como
ouvintes** somando todas as suas sessões.
O resultado deverá apresentar:
- `EventoId`;
- Nome do Evento (`nome_evento`);
- `AtividadeId`;
- Nome da Atividade (`nome_atividade`);
- Quantidade total de inscrições como ouvinte (`total_ouvintes`);
- Posição no ranking dentro do respectivo evento (`posicao_ranking`).
**Regras:**
- O ranking deve reiniciar a cada evento.
- Em caso de empate na contagem de ouvintes, a atividade de menor `AtividadeId` deve
figurar primeiro.
- Devem aparecer somente as duas primeiras atividades ranqueadas de cada evento
(atividades sem nenhum ouvinte devem constar com 0 ouvintes).
*Resposta: apresente apenas o SQL.*
---
## Questão 5 — Diagnóstico e Correção
Deseja-se listar o `EspacoId` e o `Nome` dos espaços cadastrados que já receberam
sessões e **onde todas as sessões alocadas tiveram duração estritamente menor ou igual a
120 minutos (2 horas)**.
Um desenvolvedor propôs a seguinte consulta:
```sql
SELECT esp.EspacoId, esp.Nome
FROM espaco esp
WHERE EXISTS (
SELECT 1
FROM sessao s
WHERE s.EspacoId = esp.EspacoId
AND s.Duracao <= 120
);
Determine se a consulta atende ao requisito. Sua resposta deverá possuir exatamente duas
partes:
● DIAGNÓSTICO: Explique o problema da consulta proposta em no máximo 60
palavras.
● CORREÇÃO: Apresente o SQL corrigido. Não são necessárias explicações
adicionais nessa parte.