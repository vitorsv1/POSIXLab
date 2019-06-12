# POSIXLab

## Insper - Sistemas Hardware-Software

### Vitor Satyro Vitturi

Comecei com a criação de processos filhos para rodar os tests. Em seguida adicionei os prints com os respectivos erros retornados do filho. Cria um arquivo temporário para salvar os resultados dos tests vindo dos processos filhos e mostrar em ordem no final. Assim não ha relação entre os tests.

Coloquei um alarm com 7 para os filhos. 
Os resultados estão sendo printados coloridos passam ou não.
Calculando o tempo por time (sem ms) dentro dos filhos.

Analisando signal caso o CRTL+C seja apertado o pai da um kill 0 para matar o grupo.

O terminal com os teste criados sai desta maneira:

Running 8 tests:
==============================================

testLoopInfinito : [FAIL] com sinal: Alarm clock

testMuitoTrab exit status = 0
testMuitoTrab: [PASS]
testMuitoTrab demorou 2 sec

testDivision0 : [FAIL] com sinal: Floating point exception

testFalhaPassa exit status = 255
testFalhaPassa: [FAIL] This always fails in test.c:36
testFalhaPassa demorou 0 sec

testLento exit status = 0
testLento: [PASS]
testLento demorou 5 sec

testPrints exit status = 0
testPrints: Print
testPrints: Print
testPrints: Print
testPrints: Print
testPrints: Print
testPrints: Print
testPrints: [PASS]
testPrints demorou 0 sec

testSegmentation : [FAIL] com sinal: Segmentation fault

testRapido exit status = 0
testRapido: [PASS]
testRapido demorou 0 sec

==============================================
4/8 tests passed



