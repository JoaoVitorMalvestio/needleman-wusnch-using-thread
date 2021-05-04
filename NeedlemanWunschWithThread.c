// Marcos Vinicius Peres RA: 94594
// João Vitor Malvestio da Silva RA: 93089
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <pthread.h>
#define TAM_MAX 20000

void inicializacao(char primeiraSequencia[], char segundaSequencia[]);
void matrizDeScore(char primeiraSequencia[], char segundaSequencia[]);
void printMatriz(char primeiraSequencia[], char segundaSequencia[]);
int MAIOR(int a, int b);

struct inicializa_arg_struct {
    int tamanhoPrimeiraSequencia;
    int tamanhoSegundaSequencia;
};

struct calcula_score_arg_struct {
    char primeiraSequencia[TAM_MAX];
    char segundaSequencia[TAM_MAX];
    int posLinha;
    int posColuna;
};

int matriz[TAM_MAX][TAM_MAX];
int match = 1;
int missmatch = -1;
int gap = -1; 

int main(){	
	FILE *arq;
	char primeiraSequencia[TAM_MAX]; 
    char segundaSequencia[TAM_MAX];
    
	arq = fopen("./input1.txt", "rt");
	if (arq == NULL) {
		printf("Problemas na abertura do arquivo\n");
	 	return 0;
	}
	
	while (!feof(arq)){	  
  		fgets(primeiraSequencia, TAM_MAX, arq);
  		primeiraSequencia[strcspn(primeiraSequencia, "\n")] = 0;	  
	}
	
	fclose(arq);
	
	arq = fopen("./input2.txt", "rt");
	if (arq == NULL) {
		printf("Problemas na abertura do arquivo\n");
	 	return 0;
	}
	
	while (!feof(arq)){	  
  		fgets(segundaSequencia, TAM_MAX, arq);
	  	segundaSequencia[strcspn(segundaSequencia, "\n")] = 0;
	}
	
	fclose(arq);
	
	printf("Primeira Sequencia: %s \n", primeiraSequencia);
    
    printf("Segunda Sequencia: %s \n", segundaSequencia);
    	
    inicializacao(primeiraSequencia, segundaSequencia);
    matrizDeScore(primeiraSequencia, segundaSequencia);
    printMatriz(primeiraSequencia, segundaSequencia);
    
	return 0;
}

void* inicializaLinha (void *arguments) {
	struct inicializa_arg_struct *args = arguments;
	
	for (int i = 0; i < args -> tamanhoPrimeiraSequencia +  1; i++){		
        matriz[i][0] = i == 0 ? 0 : matriz[i-1][0] + (gap); 
    }

	return NULL;
}

void* inicializaColuna (void *arguments) {
	struct inicializa_arg_struct *args = arguments;
	
	for (int j = 0; j < args -> tamanhoSegundaSequencia + 1; j++){		
        matriz[0][j] = j == 0 ? 0 : matriz[0][j-1] + (gap);
    }
    
	return NULL;
}

void inicializacao (char primeiraSequencia[], char segundaSequencia[]) {
	struct inicializa_arg_struct args;
    pthread_t thread_linha;
    pthread_t thread_coluna;    
	
	args.tamanhoPrimeiraSequencia = strlen(primeiraSequencia);
    args.tamanhoSegundaSequencia = strlen(segundaSequencia);        
    
	matriz[0][0] = 0;
		
	pthread_create(&thread_linha, NULL, &inicializaLinha, (void *)&args);
	pthread_create(&thread_coluna, NULL, &inicializaColuna, (void *)&args);
	pthread_join(thread_linha, NULL);
	pthread_join(thread_coluna, NULL);
}

void* calculaScorePos (void *arguments) {	
	struct calcula_score_arg_struct *args = arguments;
	
	int posLinha = args -> posLinha;
	char primeiraSequencia[TAM_MAX];
	strcpy(primeiraSequencia, args -> primeiraSequencia);
	char segundaSequencia[TAM_MAX];
	strcpy(segundaSequencia, args -> segundaSequencia);
	int tamanhoSegundaSequencia = strlen(segundaSequencia);
	
	for (int posColuna = 1; posColuna < tamanhoSegundaSequencia + 1; posColuna++){
		int valorDiagonal = 0;
			
	    if (primeiraSequencia[posLinha - 1] == segundaSequencia[posColuna - 1]) {
			valorDiagonal = matriz[posLinha - 1][posColuna - 1] + match;
	    }else{
			valorDiagonal = matriz[posLinha - 1][posColuna - 1] + missmatch;
	    }
	    
	    int valorEsquerda = matriz[posLinha][posColuna - 1] + gap;
	    int valorCima =  matriz[posLinha - 1][posColuna] + gap;
	    int maximoScore = MAIOR(MAIOR(valorDiagonal, valorEsquerda), valorCima);
	            
	    matriz[posLinha][posColuna] = maximoScore;	        	
    }		
}

void matrizDeScore(char primeiraSequencia[], char segundaSequencia []){
    int tamanhoPrimeiraSequencia = strlen(primeiraSequencia);
    int tamanhoSegundaSequencia = strlen(segundaSequencia);
    pthread_t thread[tamanhoPrimeiraSequencia + 1];	        
    
    for (int i = 1; i < tamanhoPrimeiraSequencia + 1; i++) {
    	struct calcula_score_arg_struct args;
        strcpy(args.primeiraSequencia, primeiraSequencia);
        strcpy(args.segundaSequencia, segundaSequencia);
        args.posLinha = i;        	       	
        pthread_create(thread + i, NULL, calculaScorePos, (void *)&args);
        pthread_join(thread[i], NULL);
    }
    
    for (int i = 1; i < tamanhoPrimeiraSequencia + 1; i++){
        pthread_join(thread[i], NULL);
    }	
}

int MAIOR (int a, int b) {
	if (a > b) {
		return a;
	}
	
	return b;
}

void printMatriz(char primeiraSequencia[], char segundaSequencia []){
    int tamanhoPrimeiraSequencia = strlen(primeiraSequencia);
    int tamanhoSegundaSequencia = strlen(segundaSequencia);
    
    printf("\t\t");
    for (int i = 0; i < tamanhoSegundaSequencia; i++) {		    
		printf("%c\t", segundaSequencia[i]);
	}
    
    for (int i = 0; i < tamanhoPrimeiraSequencia + 1; i++){
        printf("\n");
        
        if (i > 0) {
        	printf("%c\t", primeiraSequencia[i - 1]);	
		} else {
			printf("\t");
		}
		
        for (int j = 0; j < tamanhoSegundaSequencia + 1; j++){
        	if (matriz[i][j] < 0) {
        		printf("%d\t",matriz[i][j]);	
			} else {
				printf(" %d\t",matriz[i][j]);
			}
            
        }

    }

}
