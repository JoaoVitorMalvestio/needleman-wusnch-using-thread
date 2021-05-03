O sistema operacional utilizado para realizar as implementações foi o ubuntu 20.04.
A entrada do programa será a leitura de um arquivo chamado input1.txt e input2.txt na raiz do projeto, onde o primeiro arquivo irá conter a primeira sequência e o segundo arquivo a segunda sequência.

Nossa quantidade de thread é fixa e não parametrizável.

Para executar e compilar o programa deve-se ter instalado em sua máquina o compilador GCC ou Clang. No caso de uso de Linux o GCC já vem instalado por padrão, caso você queira usar o Clang basta usar esse tutorial de instalação e de como usar, acessando este site: https://clang.llvm.org/get_started.html

Nós utilizamos para buildar o nosso programa sequencial o comando do GCC:
   	gcc -g -c -std=c99 NeedlemanWunschSequecial.c
   	gcc -g -o NeedlemanWunschSequecial.o

Nós utilizamos para buildar o nosso programa com threads o comando do GCC:
	gcc -g -c -std=c99 NeedlemanWunschWithThread.c
   	gcc -g -o NeedlemanWunschWithThread.o