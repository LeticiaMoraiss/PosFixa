#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <locale.h>
using namespace std;
#define max  1000

//Estruturas para cria��o da pilha
typedef struct{
    char tipo;
}Item;

typedef struct{
    Item item[max];
    int topo;
}Pilha;

//Variaveis globais para auxilo na convers�o
char auxExp[max] = {}; //Vetor que armazena a express�o posfixa
int qtdAuxExp = 0; //contador para controle de posi��es do vetor posfixa
Item operadorDaPilha; //Armazena o elemento do topo da pilha

void PilhaVazia(Pilha *pilha){
    pilha->topo=0;
}

void Empilhar(Pilha *pilha,Item c){
    if(pilha->topo == max){
    	cout<<"\n Pilha Cheia!!!\n\n";
    }
    else{
        pilha->item[pilha->topo] = c;
        pilha->topo++;
    }
}

int VerificarVazia(Pilha pilha){
    return (pilha.topo == 0);
}

void Desempilhar(Pilha *pilha, Item *x){
    char c;
    if(VerificarVazia(*pilha)){
        //cout<<"\n Pilha Vazia!!!\n\n";
    }
    else{
    	
        *x = pilha->item[pilha->topo-1];
        pilha->topo--;
    }
}

void Imprimir(Pilha *pilha){
    if(pilha->topo == 0){
        cout<<"\n Pilha Vazia!!!\n\n";
        return;
    }
    else{
        for(int i=0;i<pilha->topo;i++){
            printf("%c ",pilha->item[i]);
            auxExp[qtdAuxExp] = pilha->item[i].tipo;
            qtdAuxExp++;
        }
    }
}

//Fun��o resposavel por definir a prioridade dos operadores dentro da express�o
int Prioridade(Item elemento){
	if(elemento.tipo == '^'){
		return 3;
	}
	else if(elemento.tipo == '*' || elemento.tipo == '/'){
		return 2;
	}
	else if(elemento.tipo == '+' || elemento.tipo == '-'){
		return 1;
	}
	else if(elemento.tipo == '('){
		return 4;
	}
}

//Fun��o responsavel por fazer a convers�o de infixa para posfixa
void ConverterPosfixa(char expressao[], Pilha pilha){
	//Variaveis para armazenar o elemento da posi��o do vetor e elemento desempilhado
	Item elemento, desempilhado; 
	
	//Armazena a prioridade do operador que esta sendo lido na express�o				
	int prioridadeOperadorExp = 0; 
	
	//Armazena a prioridade do operador aue esta no topo da pilha							  
	int prioridadeOperadorPilha = 0; 
	
	for(int i = 0; i < strlen(expressao); i++){
		//Armazena o caracter correspondente a posi��o do vetor
		elemento.tipo = expressao[i]; 
		if(elemento.tipo == '-' || elemento.tipo == '+' || elemento.tipo == '/' 
			|| elemento.tipo == '^' || elemento.tipo == '*' )
		{ //Compara para saber se � operador
			
			//Se a pilha estiver vazia
			if(VerificarVazia(pilha)){ 
				//Empilha o operador
				Empilhar(&pilha, elemento); 
			}
			else{ //Se n�o
				//Armazena o operador do topo da pilha
				operadorDaPilha = pilha.item[pilha.topo-1]; 
												
				//Armazena a prioridade do operador da pilha										   
				prioridadeOperadorPilha = Prioridade(operadorDaPilha); 
				
				 //Armazena a prioridade do operador da express�o													  
				prioridadeOperadorExp = Prioridade(elemento);
				
				//Se a prioridade do operador da pilha for maior que a 
				//prioridade do operador da express�o											 
				if(prioridadeOperadorPilha >= prioridadeOperadorExp ){ 
				
				  //Se o operador que esta na pilha for 
				  //diferente de abre parenteses
				  if(operadorDaPilha.tipo != '('){ 
					
					//Se o operador da pilha for "elevado"
					if(operadorDaPilha.tipo == '^'){ 
						
					  //Desempilha o operador da pilha
					  Desempilhar(&pilha, &desempilhado); 
					
					  //Armazena no vetor posfixa								
					  auxExp[qtdAuxExp] = desempilhado.tipo; 
					
					  //Incrementa a posi��o do vetor posfixa									
		 	  		  qtdAuxExp++; 
						
					  //Armazena o novo operador que esta no topo   			
		 	  		  operadorDaPilha = pilha.item[pilha.topo-1];
						
					  //Armazena a prioridade do operador   								
					 prioridadeOperadorPilha = Prioridade(operadorDaPilha);
						
					 //Enquanto a prioridade do operador da pilha for maior 
					 //que a prioridade do operador da express�o
					 while(prioridadeOperadorPilha >= prioridadeOperadorExp){ 
						
					   //Verifica se o topo n�o contem um abre parenteses
					   if(operadorDaPilha.tipo != '('){ 
							
					    	//Desempilha o operador do topo	
							Desempilhar(&pilha, &desempilhado);
								
							//Armazena no vetor posfixa							
						    auxExp[qtdAuxExp] = desempilhado.tipo; 
								
							//Incrementa a posi��o do vetor posfixa							
		 	  			    qtdAuxExp++; 
								
							//Armazena o novo operador que esta no topo   
		 	  			    operadorDaPilha = pilha.item[pilha.topo-1];  
								
							//Armazena a prioridade do operador   								
							prioridadeOperadorPilha = Prioridade(operadorDaPilha);	
					   }
						else{ //Se for igual a abre parenteses
						 	//Finaliza o while
							prioridadeOperadorPilha = 0;
						}
		 	  					
					 }
					}
					else{ //Se n�o for um operador "elevado" 
					
						//Desempilha o operador da pilha
						Desempilhar(&pilha, &desempilhado); 
						
						//Arameza no vetor da posfixa							
						auxExp[qtdAuxExp] = desempilhado.tipo; 
						
						//Incrementa a posi��o do vetor posfixa								
						qtdAuxExp++; 
					}
				
				 }
				  //Empilha o perador da express�o		
				  Empilhar(&pilha, elemento); 
				}
				else{ //Se a prioridade do operador da pilha 
				//for menor que a prioridade do operador da express�o
				
				//Empilha o operador da express�o
					Empilhar(&pilha, elemento); 
				}
			}
		}
		//Se o operador da express�o for abre parenteses
		else if(elemento.tipo == '('){ 
			//Empilha ele na pilha				
			Empilhar(&pilha, elemento); 
		}
		//Se o operador for fecha parenteses
		else if(elemento.tipo == ')'){ 
			
			//Enquanto n�o encontrar o abre parenteses						
			while(desempilhado.tipo != '('){ 
				
				//Desempilha da pilha				
				Desempilhar(&pilha, &desempilhado); 
				
				//Verifica se n�o � abre parenteses
				if(desempilhado.tipo != '('){ 
					 
					//Armazena no vetor posfixa						
					auxExp[qtdAuxExp] = desempilhado.tipo;
					//Incrementa a posi��o posfixa
 	  				qtdAuxExp++;
				}			
			}
			//Armazena o item que ficou no topo da pilha
			Item aux = pilha.item[pilha.topo-1]; 
			
			//Se for abre parenteses			
			if(aux.tipo =='('){ 
				//Desempilha da pilha
				Desempilhar(&pilha, &desempilhado); 
			}		
		}
		else{ //Se for um operando
			auxExp[qtdAuxExp] = elemento.tipo; //Armazena no vetor posfixa
			qtdAuxExp++; //Incrementa a posi�ao do vetor posfixa
		}
	}
	
   while(pilha.topo > 0){ //Enquanto tiver operador na pilha
      Desempilhar(&pilha,&desempilhado); //Desempilho
      if(desempilhado.tipo != '(' ){ // Se for diferente de abre parenteses
      	auxExp[qtdAuxExp] = desempilhado.tipo; //Armazena no vetor posfixa
 	  	qtdAuxExp++; //Incrementa a posi��o do vetor posfixa
      }   
   }
   
   for(int i = 0; i < strlen(auxExp); i++){ //Percorre o vetor de posfixa 
   	   cout<<auxExp[i]; //Exibe na tela a express�o posfixa
   }
}
int main(){
	
	setlocale(LC_ALL,"Portuguese"); //Permite acentua��o
    
	Pilha pilha; //Variavel que recebe os operadores
	char expressao[max]; //Variavel que armazena a express�o infixa

	PilhaVazia(&pilha); //Cria a pilha vazia

	cout<<"\n Informe a express�o Infixa: ";
	gets(expressao); //L� a express�o infixa 
	
    cout<<"\n Express�o Posfixa: ";
	ConverterPosfixa(expressao, pilha); //Chama a fun��o responsavel pela convers�o
      
	cout<<"\n\n\n";
	system("pause");
	return 0;
}
