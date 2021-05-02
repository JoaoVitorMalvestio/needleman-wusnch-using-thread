// Marcos Vinicius Pers RA: 94594
// JAO
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define MAIOR(a, b) (((a) > (b)) ? (a) : (b))


void inicializacao(char primeiraSequencia[], char segundaSequencia[]);
void matrizDeScore(char primeiraSequencia[], char segundaSequencia[]);
void printMatriz(char primeiraSequencia[], char segundaSequencia[]);

int matriz[100][100];
int match = 1;
int missmatch = -1;
int gap = -2; 

int main(){
	
	FILE *arq;
	char Linha[100];
	char primeiraSequencia[100]; 
    char segundaSequencia[100]; 
    
	arq = fopen("teste.txt", "rt");
	if (arq == NULL) {
		printf("Problemas na abertura do arquivo\n");
	 	return;
	}
	
	while (!feof(arq)){
	  if(strlen(primeiraSequencia) == 0 ){
  		fgets(primeiraSequencia, 100, arq);
	  }else{
	  	fgets(segundaSequencia, 100, arq);
	  }
	}
	
	fclose(arq);
	
	printf("Primeira Sequencia: %s \n", primeiraSequencia);
    
    printf("Segunda Sequencia: %s \n", segundaSequencia);
    	
    inicializacao(primeiraSequencia,segundaSequencia);
    matrizDeScore(primeiraSequencia,segundaSequencia);
    printMatriz(primeiraSequencia,segundaSequencia);
    
	return 0;
}

void inicializacao(char primeiraSequencia[],char segundaSequencia []){
    int tamanhoPrimeiraSequencia = strlen(primeiraSequencia);
    int tamanhoSegundaSequencia = strlen(segundaSequencia);
    
	matriz[0][0] = 0;
    
    for (int i = 0; i < tamanhoPrimeiraSequencia +  1; i++){
        matriz[i][0] = i == 0 ? 0 : matriz[i-1][0] + (gap); 
    }

    for (int j = 0; j < tamanhoSegundaSequencia + 1; j++){
        matriz[0][j] = j == 0 ? 0 : matriz[0][j-1] + (gap);
    }

}

void matrizDeScore(char primeiraSequencia[],char segundaSequencia []){
    int tamanhoPrimeiraSequencia = strlen(primeiraSequencia);
    int tamanhoSegundaSequencia = strlen(segundaSequencia);
    
    for (int i = 1; i < tamanhoPrimeiraSequencia + 1; i++) {
        for (int j = 1; j < tamanhoSegundaSequencia + 1; j++){
        
            int valorDiagolanal = 0;

            if (primeiraSequencia[j - 1] == segundaSequencia[i - 1]){
                valorDiagolanal = matriz[i - 1][j - 1] + match;
            }
            else{
                valorDiagolanal = matriz[i - 1][j - 1] + missmatch;
            }

            int valorEsquerda = matriz[i][j - 1] + gap;
            int valorCima =  matriz[i - 1][j] + gap;

            int maxScore = MAIOR(MAIOR(valorDiagolanal, valorEsquerda), valorCima);
            matriz[i][j] = maxScore;
        }
    }
}


void printMatriz(char primeiraSequencia[],char segundaSequencia []){
    int tamanhoPrimeiraSequencia = strlen(primeiraSequencia);
    int tamanhoSegundaSequencia = strlen(segundaSequencia);
    
    for (int i = 0; i < tamanhoPrimeiraSequencia + 1; i++){
        printf("\n");
        for (int j = 0; j < tamanhoSegundaSequencia + 1; j++){
            printf("%d\t",matriz[i][j]);
        }

    }

}
