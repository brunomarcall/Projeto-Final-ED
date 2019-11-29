#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10


//criando a struct//
 typedef struct{
   int id;
   char nome[50];
   char autor[50];
   float valor;
 }Livros;
typedef struct{
  int qtd;
  Livros dados[TAM];
}Biblioteca;

//variavel global//
Biblioteca fil;


//-----------------------PROTOTIPOS DAS FUNÇÕES-----------------------------------------------
int inserirLivro( int , char[], char[], float);

int pesquisarLivro(int);

int removerLivro(int);

int editarLivro(int, char[], char[],float);

int testid(int);

void mostrarLivros();

void mostrarLivro(int);

void menu();

void mostrarescolha(int);

void listInOrder();


//-----------------------FUNÇÃO PRINCIPAL-----------------------------------------------
void main(){
		menu();
 }


//fun��o para saber se o cadastro est� cheio//
int isFull(){
  return (fil.qtd >= TAM);
}
//fun��o para saber se o cadastro est� vazio//
int isEmpty(){
  return (fil.qtd == 0);
}
//fun��o para ver se o id digitado ja existe//
int testid(int id){
  if(isFull())
    return 0;
 
  int i;
  for(i=0;i<TAM; i++){
    if(id==fil.dados[i].id){
   return 0;
    }
  }
  return 1;
}
//fun��o para cadastrar os Livros//
int inserirLivro( int id, char nome[],char autor[],float valor){
  if(isFull())
    return 0;
  
  Livros livro={id};
  	strcpy(livro.nome, nome);
	strcpy(livro.autor, autor);
	livro.valor = valor;
  fil.dados[fil.qtd]=livro;
  fil.qtd++;
  
  return 1;
}
//fun��o para editar os Livros//
int editarLivro(int id, char nome[],char autor[], float valor){
  int i= pesquisarLivro(id);
  if(i == -1)
    return 0;
   int k;
  for (k=i; k<=i;k++){
  Livros livro={id};
  strcpy(livro.nome, nome);
	strcpy(livro.autor, autor);
	livro.valor = valor;
  fil.dados[k]=livro;
    
  }
  return 1;
}
//fun��o para contar a quantidade de Livros cadastrados//
void mostrarLivros(){
  if(isEmpty())
    return;
  int i;
  for (i=0;i< fil.qtd; i++){
    mostrarLivro(i);
  }
  printf("QTD %d\n",fil.qtd);
}
//fun��o para pesquisar o Livro pelo id//
int pesquisarLivro(int id){
  if(isEmpty())
    return -1;
  int i;
  for(i=0;i<fil.qtd; i++)
    if(id==fil.dados[i].id)
      return i;
  
  return -1;
}
//fun��o para exibir a Biblioteca de Livros//
void mostrarLivro(int i){
  i = (i < 0)?-i:i;
  if(i >= fil.qtd)
    return;
  
  printf("\nid: %d\n", fil.dados[i].id);
  printf("Nome: %s\n", fil.dados[i].nome);
	printf("autor: %s\n", fil.dados[i].autor);
	printf("Valor: %0.2f\n", fil.dados[i].valor);
  
}
//fun��o para remover os Livros//
int removerLivro(int id){
  int i= pesquisarLivro(id);
  if(i == -1)
    return 0;
  int k;
  for (k=i; k<=fil.qtd;k++){
    fil.dados[k] = fil.dados[k+1];
  }
  fil.qtd--;
  return 1;
}
//Função para escolher 1 livro especifico
void mostrarescolha(int id){
  	  int i= pesquisarLivro(id);
  if(i == -1)
    return;
   int k;
  for (k=i; k<=i;k++){
	printf("\nid: %d\n", fil.dados[k].id);
  printf("Nome: %s\n", fil.dados[k].nome);
		printf("autor: %s\n", fil.dados[k].autor);
	printf("valor: %0.2f\n", fil.dados[k].valor);

	}
	
}

//Esta função lista e imprimie todas as ocorrências de livros em ordem e sem repetições
void listInOrder(){
	int i,j,k=0;
	Livros aux;

	//Este laço é responsável por ordenar os números de ids com seus dados inclusos (nome, autor e valor).
	for(i=0; i<fil.qtd; i++)
		for(j=i+1;j<fil.qtd;j++)
			if(fil.dados[i].id>fil.dados[j].id){
				aux = fil.dados[i];
				fil.dados[i] = fil.dados[j];
				fil.dados[j]=aux;
			}

	 //Ao entrar nesse for, são impressos os livros sem repetições, graças ao laço while.
	for(i=0;i<fil.qtd; i++){
		k++;
		printf("\nId: %d\n",fil.dados[i].id);
		printf("Nome:    %s\n",fil.dados[i].nome);
		printf("Autor:  %s\n",fil.dados[i].autor);
		printf("Valor %f\n",fil.dados[i].valor);

		/**
		 * Entramos nesse while para que o "i" seja iterado até que ele encontre um numero de ID diferente
		 * do atual utilizado no início do laço for.
		 */
		while(fil.dados[i].id == fil.dados[i+1].id)
			i++;
	}
	printf("\nTotal de Livros: %d\n",k );
}


//Esta função imprime para o usuário o menu com todas as funcionalidades do programa
void menu(){
  char nome[50];
	char autor[50];
  	float valor;
	char codigo[10];
  	int id,resp,saber=0,idRemove,op,voltar,print,i,flag;
     do{
        system("clear");
			printf("\n+------------------------------------------------------------------+");
		printf("\n|                             Menu                                 |");
		printf("\n+------------------------------------------------------------------+");
		printf("\n|    1 - Cadastrar                                                 |");
		printf("\n|    2 - Listar Todos os Livros                                    |");
		printf("\n|    3 - Pesquisar Livro pelo ID                                   |");
		printf("\n|    4 - Editar Livro                                              |");
		printf("\n|    5 - Remover Livro da Biblioteca                               |");
		printf("\n|    6 - Listar Livros ordenados pelo ID                           |");
		printf("\n|    0 - Sair                                                      |");
		printf("\n+------------------------------------------------------------------+");
		printf("\nDigite sua escolha >> ");
        scanf("%d", &op);
        switch(op){
        case 1:
            //Cadastrar
            if(isFull())
                break;
              do{ 
             							//testando se ira entrar so numeros no id//	
								while(1) {
							
									printf("O id deve conter apenas numeros. Digite o id do Livro: ");
									scanf("%s",codigo);
								
									flag = 1;
							
									for(i=0;codigo[i]!='\0';i++){
										
											if (codigo[i] != '0' && codigo[i] != '1' && codigo[i] != '2' && codigo[i] != '3' && codigo[i] != '4' &&
													codigo[i] != '5' &&	codigo[i] != '6' && codigo[i] != '7' && codigo[i] != '8' && codigo[i] != '9') {																	
													flag = 0;
													break;
											}
									}
									if(flag == 1)
										break;
									setbuf(stdin, NULL);
								}
							
								id = atoi(codigo);	
								testid(id);
								//Testando se o ID digitado ja existe//
								while(testid(id)==0){    
										printf("Id existente, Digite outro: ");
										scanf("%d",&id);
										testid(id);
								}; 
								printf("Digite o nome do Livro: ");
								//limpando o cache//
								setbuf(stdin, NULL);
								scanf("%[^\n]s",nome);
								printf("Digite o autor do Livro: ");
								setbuf(stdin, NULL);
								scanf("%[^\n]s",autor);
								printf("Digite a valor do Livro: ");
								setbuf(stdin, NULL);
								scanf("%f",&valor);
								inserirLivro(id,nome,autor,valor);
                printf("Deseja cadastrar outro Livro? [1]-SIM [2]-N�o: ");
                scanf("%d",&resp);
                if(saber == TAM -1 ){
                	printf("Desculpe, numero de Livros alcan�ados");
                	resp=0;
                }
                saber++;
								
                }while(resp==1);
						 		printf("voltar para o menu? [1]-SIM [2]-N�O: ");
            		scanf("%d",&voltar);
           			if (voltar==1)
             			 menu();
            		else
										exit(0);
              	break;
           
          case 2:
            //Listar todos
          	  mostrarLivros();
            	printf("voltar para o menu? [1]-SIM [2]-N�O: ");
            	scanf("%d",&voltar);
           		if (voltar==1)
              	menu();
           	  else
             		exit(0);
          case 3:
             //Pesquisar
          			if(isEmpty())
                  break;				
						while(1) {
							
								printf("O id deve conter apenas numeros. Digite o id do Livro: ");
								scanf("%s",codigo);
								
								flag = 1;
							
								for(i=0;codigo[i]!='\0';i++){
										
											if (codigo[i] != '0' && codigo[i] != '1' && codigo[i] != '2' && codigo[i] != '3' && codigo[i] != '4' &&
													codigo[i] != '5' &&	codigo[i] != '6' && codigo[i] != '7' && codigo[i] != '8' && codigo[i] != '9') {																	
													flag = 0;
													break;
											}
								}
								if(flag == 1)
										break;
								setbuf(stdin, NULL);
						}
							
						id = atoi(codigo);	
						testid(id);
				
						//Testando se o ID digitado ja existe//
						while(testid(id)==1){    
									printf("Por favor digite um ID existente: ");
									scanf("%d",&id);
									testid(id);
									if(testid(id)==1){
										printf("Id digitado n�o existe!!\n");
										printf("Deseja rever a Lista de Livros? [1]-SIM [2]-N�O: ");
										scanf("%d",&print);
										if(print == 1){
											mostrarLivros();
										}else
											exit(0);
										
									}
						}; 
        		mostrarescolha(id);
            printf("voltar para o menu? [1]-SIM [2]-N�O: ");
            scanf("%d",&voltar);
            if (voltar==1)
              menu();
            else
							exit(0);
              break;
           
          case 4:
            //Alterar
            if(isEmpty())
                break;
               do {
																	
									while(1) {
							
										printf("O id deve conter apenas numeros. Digite o id do Livro: ");
										scanf("%s",codigo);
								
										flag = 1;

										for(i=0;codigo[i]!='\0';i++){

													if (codigo[i] != '0' && codigo[i] != '1' && codigo[i] != '2' && codigo[i] != '3' && codigo[i] != '4' &&
															codigo[i] != '5' &&	codigo[i] != '6' && codigo[i] != '7' && codigo[i] != '8' && codigo[i] != '9') {																	
															flag = 0;
															break;
													}
										}
										if(flag == 1)
												break;
										setbuf(stdin, NULL);
								}

								id = atoi(codigo);	
								testid(id);
								//Testando se o ID digitado ja existe//
								while(testid(id)!=0){    
										printf("Id existente, Digite outro: ");
										scanf("%d",&id);
										testid(id);
								}; 
								printf("Digite o nome do Livro: ");
								setbuf(stdin, NULL);
								scanf("%[^\n]s",nome);
								printf("Digite o autor do Livro: ");
								setbuf(stdin, NULL);
								scanf("%[^\n]s",autor);
								printf("Digite a valor do Livro: ");
								setbuf(stdin, NULL);
								scanf("%f",&valor);
								editarLivro(id,nome,autor,valor);
                printf("Deseja modificar outro Livro? [1]-SIM [2]-N�o: ");
                scanf("%d",&resp);
            }while(resp==1);
						printf("voltar para o menu? [1]-SIM [2]-N�O: ");
            scanf("%d",&voltar);
            if (voltar==1)
              menu();
            else
							exit(0);
              break;
         
          case 5:
            //Remover
             do{
                							
								while(1) {

										printf("O id deve conter apenas numeros. Digite o id do Livro: ");
										scanf("%s",codigo);

										flag = 1;

										for(i=0;codigo[i]!='\0';i++){

													if (codigo[i] != '0' && codigo[i] != '1' && codigo[i] != '2' && codigo[i] != '3' && codigo[i] != '4' &&
															codigo[i] != '5' &&	codigo[i] != '6' && codigo[i] != '7' && codigo[i] != '8' && codigo[i] != '9') {																	
															flag = 0;
															break;
													}
										}
										if(flag == 1)
												break;
										setbuf(stdin, NULL);
								}

								idRemove = atoi(codigo);	
								testid(idRemove);
								//Testando se o ID digitado ja existe//
								while(testid(idRemove)==1){    
								printf("Id existente, Digite outro: ");
								scanf("%d",&idRemove);
								testid(idRemove);
								}; 
                removerLivro(idRemove);
                printf("Livro Removido com sucesso!!\n");
                printf("deseja remover mais algum Livro? [1]-SIM [2]-N�O: ");
                scanf("%d",&resp);
                saber--;
             }while(resp==1);
						 printf("voltar para o menu? [1]-SIM [2]-N�O: ");
            scanf("%d",&voltar);
            if (voltar==1)
              menu();
            else
							exit(0);
              break;
           case 6:
		   			if (isEmpty())
              break;
						listInOrder();
						printf("voltar para o menu? [1]-SIM [2]-N�O: ");
            			scanf("%d",&voltar);
            			if (voltar==1)
              				menu();
            			else
							exit(0);
		   	break;
          case 0:
            exit(0);
            break;
        default:
            printf("\nOpcao invalida");
						printf("voltar para o menu? [1]-SIM [2]-N�O: ");
            scanf("%d",&voltar);
            if (voltar==1)
              menu();
            else
              exit(0);
						
            break;
        }
}while(op!=0);
}

