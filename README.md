# POSIXLab

Comecei com a criação de processos filhos para rodar os tests. Em seguida adicionei os prints com os respectivos erros retornados do filho. Cria um arquivo temporário para salvar os resultados dos tests vindo dos processos filhos e mostrar em ordem no final. Assim não ha relação entre os tests.

Coloquei um alarm com 7 para os filhos. 
Os resultados estão sendo printados coloridos passam ou não.
Calculando o tempo por time (sem ms) dentro dos filhos.

Analisando signal caso o CRTL+C seja apertado o pai da um kill 0 para matar o grupo.


