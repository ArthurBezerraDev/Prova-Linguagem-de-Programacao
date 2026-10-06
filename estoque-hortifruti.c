#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nó: nome[20], quantidade e ponteiro para o próximo nó
typedef struct No{
	
	char nome[20];	
	int quant;
	struct No *prox;

}No;

// Nó cabeça: ponteiro para o primeiro nó da lista
typedef struct Cabeça{
	
	No *inicio;
	
}Cabeça;

// ---------- Função Auxiliar ----------

//Retorna 1 se o produto já existir na lista.
int No_existe(Cabeça *lista, char *nome){

	No *aux = lista->inicio;
	
	while (aux){
		if (strcmp(aux->nome, nome) == 0){
			return 1;
		}
		aux = aux->prox;
	}
	return 0;
}

//Remove o '\n' e bota '\0' no lugar
void Remove_barran(char *str){
	str[strcspn(str, "\n")] = '\0';
}


// ---------- Cadastro do Produto ---------- 
void Cadastrar_produto(Cabeça *lista){
	
	char nome[20];		
	int quantidade;
	
	printf("Quantidade a cadastrar: ");
	scanf(" %d", &quantidade);
	getchar();	
	
	if (quantidade <= 0){
		printf("\n\nERRO, quantidade inválida!\n\n");
		return;
	}
	printf("Nome do produto a ser cadastrado: ");
	fgets(nome, sizeof(nome), stdin);
	Remove_barran(nome);
	
	// Caso o produto seja novo no estoque
	if (No_existe(lista, nome) == 0){
	
		No *novo = malloc(sizeof(No));
		if (!(novo)){
			printf("\n\nERRO, alocação de memória!\n\n");
			return;
		}
		
		novo->quant = quantidade;
		strcpy(novo->nome, nome);
		novo->prox = lista->inicio;
		
		lista->inicio = novo;
		printf("Produto Cadastrado!\n");
		return;
	}
	
	// Caso o produto já esteja no estoque
	No *aux = lista->inicio;
	while (aux){
		if (strcmp(aux->nome, nome) == 0){
			aux->quant = aux->quant + quantidade;
			printf("Quantidade acrescentado (produto já existia na lista)!\n");
			return;
		}
		aux = aux->prox;
	}
}

// ---------- Realizar Venda ----------
void Vender(Cabeça *lista){
	
	if (!(lista->inicio)){
		printf("\n\nERRO, Estoque vazia!\n\n");
		return;
	}
	char nome[20];
	int quantidade;
	
	No *aux = lista->inicio;
	
	printf("Produto a ser vendido: ");
	fgets(nome, sizeof(nome), stdin);
	Remove_barran(nome);
	
	printf("Quantidade a ser vendida: ");
	scanf(" %d", &quantidade);
	
	// Se for o primeiro elemento da lista
	if (strcmp(aux->nome, nome) == 0){
		int diff = ((aux->quant) - (quantidade));
		
		// Estoque menor do que o requisitado
		if (diff < 0){
			printf("\n\nERRO, Quantidade indisponível!\n\n");
			return;
		}
		
		// Estoque igual ao requisitado
		if (diff == 0){
			lista->inicio = aux->prox;
			free(aux);
			printf("Produto completamente vendido!\n");
			return;
		}
		
		// Estoque maior ao requisitado
		if (diff > 0){
			aux->quant = diff;
			printf("Quantidade %d vendida, quantidade restante: %d\n", quantidade, diff);
			return;
		}
	}
	
	No *ant = NULL;
	
	// Caso o No esteja mais a diante da lista
	while (aux){
		

		
		// Encontrou
		if (strcmp(aux->nome, nome) == 0){
			int diff = aux->quant - quantidade;	
			
			if (diff < 0){
				printf("\n\nERRO, Quantidade indisponível!\n\n");
				return;
			}
			if (diff == 0){
				ant->prox = aux->prox;
				free(aux);
				printf("Produto completamente vendido!\n");
				return;
			}
			if (diff > 0){
				aux->quant = diff;
				printf("Quantidade %d vendida, quantidade restante: %d\n", quantidade, diff);
				return;
			}
		
		}
		ant = aux;
		aux = aux->prox;
	}
	printf("\n\nERRO, Produto não encontrado!\n\n");
	 
}

// ------------- Mostrar Estoque ------------
void Imprimir(Cabeça *lista){

	No *aux = lista->inicio;
	
	if (!(lista->inicio)){
		printf("\n\nERRO, Estoque vazio!\n\n");
		return;
	}
	
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
	
	while (aux){
		printf("\t %s: %d unidades\n", aux->nome, aux->quant);
		aux = aux->prox;
	}
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

// ------------- Encerrar Programa -------------
void Encerramento(Cabeça *lista){
	
	if (!(lista->inicio)){
		free(lista);
		printf("Memória Liberada!");
		return;
	}
	
	No *aux = lista->inicio;
	No *pos;
	
	while (aux){
		pos = aux->prox;
		free(aux);
		aux = pos;
	} 
	free(lista);
	printf("Memória Finalizada!");
}

 
int main(){

	Cabeça *estoque = malloc(sizeof(Cabeça));
	estoque->inicio = NULL;
	
	int escolha;
	
	
	printf("----------------------------------\n");
	printf("	Estoque Hortifruti\n");
	while (1){
		printf("----------------------------------\n");
		printf("(1) Cadastrar Produto\n");
		printf("(2) Realizar Venda\n");
		printf("(3) Mostrar Estoque\n");
		printf("(0) Encerrar Programa\n");
		printf(": ");
		scanf(" %d", &escolha);
		getchar();
		
		// Cadastrar Produto
		if (escolha == 1){
			printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			Cadastrar_produto(estoque);
			printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			printf("\n");
			continue;
			
		}
		
		// Realizar Venda
		else if (escolha == 2){
			printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			Vender(estoque);
			printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
			printf("\n");
			continue;
			
		}
		
		// Mostrar Estoque
		else if (escolha == 3){
			Imprimir(estoque);
			printf("\n");
			continue;
			
		}
		
		// Encerrar Programa
		else if (escolha == 0){
			Encerramento(estoque);
			printf("\n");
			break;
			
		}
		
		else{
			printf("ERRO, digite novamente!\n");
			printf("\n");
			continue;
		
		}
	
	}
printf("\nObrigado por executar o programa\n");
}
