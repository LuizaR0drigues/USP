% Aula referente ao comando Corte
% backtracking: processo pelo qual tds as alternativas são  tentadas exaustivamente
% com o CORTE (!), é possível controlar esse retrocesso
% sintaxe: ! fica ao lado direito de uma regra


% exemplo utilizando uma função
% ele ira testar todas as possibilidades sem o corte
% Ao adicionar o corte, dizemos ao compilador que ao achar a solução, ele não deve testar as demais opções
f(X, 0) :- X < 3, !. % X < 3 -> f = 0
f(X, 2) :- X < 6, !. % 3 =< X < 6 -> f = 2
f(X, 4).             % x >= 6 -> f = 4