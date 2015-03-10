### Solution for SPOJ "HASHADIQ" problem

http://br.spoj.com/problems/HASHADIQ/

#### Warning:
I didn't care about wrong input since the system only provides valid input


(Will translate soon)

### Original Problem Description (portuguese)

Problema: HASHADIQ

Autor: Tiago Falcão

Neste problema, pede-se para armazenar, gerenciar e buscar por indivíduos definidos por um identificador único (inteiro) e pelas seguintes informações: Primeiro e último nome, data de nascimento e telefone. 

Entrada 
A entrada será feita por 4 comandos: add, del, info e query. A execução é encerrada com EOF.

O comando ''add'' recebe e armazena todos dados do individuo, e retorna erro se já existir individuo com mesmo identificador.


add <id> <first_name> <last_name> <birtday> <phone_number>

O comando ''del'' remove todos dados relacionados a um determinado identificador, e retorna erro se não existir individuo com o identificador fornecido.


del <id>

O comando ''info'' imprime todos dados de um determinado identificador, e retorna erro se não existir individuo com o identificador fornecido.


info <id>

O comando ''query'' realiza uma busca nos indivíduos cadastrados. Conforme as seguintes tags de busca:

fn: Primeiro nome
ln: Ultimo nome
bd: Data de nascimento
pn: Telefone
 

query (<tag>:<valor>)+

Saída 

O comando ''add'' somente imprime na saída quando ocorre erro na inserção de um individuo, ocorrida na inserção de individuo com identificador duplicado.

O comando ''del'' somente imprime na saída quando o identificador solicitado não existe.

O comando ''info'' imprime todos dados de um determinado identificador, ou imprime erro se não existir individuo com o identificador fornecido.

O comando ''query'' retorna os identificadores que respeitem os critérios da busca na ordem crescente separados por espaços. Em caso de não existir nenhum individuo que respeite a busca, uma linha vazia deve ser impressa.

Exemplo
Entrada:
add 123 Roberto Nascimento 01/01/1960 +55-21-0190-0190
add 123 Joao Souza 11/10/2000 103-99
add 09 Andre Matias 01/01/1970 +55-21-0190-0190
add 222 Diogo Fraga 01/06/1967 +55-21-0190-0190
add 99 Seu Barbosa 01/01/1960 +55-21-0190-0190
add 100 Seu Beirada 01/01/1960 +55-21-9999-9999
add 155 Andre Fortunato 02/01/1962 +55-21-0190-0190
query bd:01/01/1960
query bd:01/01/1960 fn:Seu
query bd:01/01/1960 fn:Seu pn:+55-21-9999-9999
info 100
del 99
query fn:XXX
query bd:01/01/1960 fn:Seu
info 99
del 99

Saída:
ID 123 ja cadastrado.
99 100 123
99 100
100
Seu Beirada 01/01/1960 +55-21-9999-9999

100
ID 99 nao existente.
ID 99 nao existente.