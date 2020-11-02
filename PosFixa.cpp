#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

bool CompararNumero(char auxiliar);
void ImprimirPosfixa(char posfixa[]);
void PosFixa(char infixa[]);
void InformacaoInvalida();

int main(){
	char infixa[99];

	cout<<"Expressao infixa: ";
	gets(infixa);
	
	PosFixa(infixa);
	
	exit(0);
}

void PosFixa(char infixa[])
{
	/*
	 *	O switch vai controlar as manipulações da pilha com os operadores.
	 *	LISTA DE PRIORIDADE:
	 *	'('      -> prioridade 4
	 *	'+' '-'  -> prioridade 1
	 *	'*' '/'  -> prioridade 2
	 *	'^'      -> prioridade 3
	 *	')"      -> NA
	 */ 
	
	char posfixa[99], operadores[99], auxiliar;
	int contPosfixa=-1, contOperadores=-1;
	
	posfixa[0] = '\0';
	
	for(int cont=0; cont<strlen(infixa); cont++){
		if(CompararNumero(infixa[cont]))
		{ //Coloca os numeros/variaveis na posfixa ou faz tratamento com os operadores
			contPosfixa++;
			posfixa[contPosfixa] = infixa[cont];
		}
		else
		{			
			switch(infixa[cont]){
				case '(':
					contOperadores++;
					operadores[contOperadores] = infixa[cont];
					break;
				case ')':
					for(; operadores[contOperadores] != '('; contOperadores--, contPosfixa++)
					{
						posfixa[contPosfixa+1] = operadores[contOperadores];
					}
					contOperadores--;
					break;
				case '+':
				case '-':
					if(operadores[contOperadores] == '^' 
					  || operadores[contOperadores] == '*')
					{
						for(int x=0; x == 0; contOperadores--,contPosfixa++)
						{
							posfixa[contPosfixa+1] = operadores[contOperadores];
							if(operadores[contOperadores] == '+' 
							   || operadores[contOperadores] == '-' 
							   || operadores[contOperadores] == '(' 
							   || contOperadores-1 == -1)
							{
								x++;
							}
						}	
					}
					if(contOperadores != -1 
					   && operadores[contOperadores] != '(' )
					{
						contPosfixa++;
						posfixa[contPosfixa] = operadores[contOperadores];
						operadores[contOperadores] = infixa[cont];
					}
					else if(contOperadores == -1 
					       || operadores[contOperadores] == '(')
					{
						contOperadores++;
						operadores[contOperadores] = infixa[cont];
					}
					
					break;
				case '*':
				case '/':
					if(operadores[contOperadores] == '^')
					{
						for(int x=0; x == 0; contOperadores--,contPosfixa++)
						{
							posfixa[contPosfixa+1] = operadores[contOperadores];
							if(operadores[contOperadores] == '*' 
							   || operadores[contOperadores] == '/')
							{
								x++;	
							}							
						}	
					}
					if(contOperadores != -1 
					   && operadores[contOperadores] != '(' 
					   && (operadores[contOperadores] != '+' 
					       && operadores[contOperadores] != '-')
					  )
					{
						contPosfixa++;
						if(operadores[contOperadores] == '*' 
						  || operadores[contOperadores] == '/')
						{
							posfixa[contPosfixa] = operadores[contOperadores];
							operadores[contOperadores] = infixa[cont];
						}
						else
						{
							posfixa[contPosfixa] = infixa[cont];
						}
					}
					else if(contOperadores == -1 
					        || operadores[contOperadores] == '(' 
							|| operadores[contOperadores] == '+' 
							|| operadores[contOperadores] == '-')
					{
						contOperadores++;
						operadores[contOperadores] = infixa[cont];
					}
					break;
				case '^':
					if(operadores[contOperadores] == '^')
					{
						posfixa[contPosfixa] = infixa[cont];
					}						
					else
					{
						contOperadores++;
						operadores[contOperadores] = infixa[cont];
					}
					break;
				default: //simbolos inválidos
					InformacaoInvalida();
			}
		}
		if(strlen(infixa) == cont+1)
		{ //Tira os restos da pilha quando a infixa terminar
			for(int x=-1; x<contOperadores; contOperadores--,contPosfixa++)
			{
				posfixa[contPosfixa+1] = operadores[contOperadores];
			}
			posfixa[contPosfixa+1] = '\0';
		}
	}
	
	cout<<"Expressao posfixa: ";
	ImprimirPosfixa(posfixa);
}

bool CompararNumero(char auxiliar)
{ //Define se é um numero/variavel ou algum outro simbolo
	if((auxiliar >= '0' && auxiliar <= '9') 
	   ||(auxiliar >= 'a' && auxiliar <= 'z') 
	   ||(auxiliar >= 'A' && auxiliar <= 'Z'))
	{
		return true;
	} 
	else
	{		
		return false;
	}
}

void InformacaoInvalida()
{
	system("cls");
	cout<<"*****************************************";
	cout<<"\n**Caractere invalido!! - Fim do sistema**\n";
	cout<<"*****************************************";
	exit(0);
}

void ImprimirPosfixa(char posfixa[])
{
	for(int cont=0; posfixa[cont] != '\0'; cont++)
	{
		cout<<posfixa[cont];
	}
}
