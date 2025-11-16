#pragma once
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "consts.h"
/*PROTOTIPOS*/
/*User*/
void DelUser(struct tagUser users[],int qtdUsers,int indexUser);
int SearchUser(struct tagUser users[], int qtdUsers, char username[]);	//Retorna posicao do utilizador com nome igual a username. senao retorna -1

/*Password*/
int PasswordCheck(char password[], char realPassword[]);	//Verifica se password é igual
int StrongPass(char password[]);	//Verifica o quao forter password é

/*Mensagens*/
int DelMessages(struct tagMensagem mensagens[],int qtdMensagens,char username[]);	//Apaga todas as mensagens que teem username como origem
void AuxDelMessages(struct tagMensagem mensagens[],int qtdMensagens,int delIndex);	//Apaga a mensagem no delIndex
void SearchMessages(struct tagMensagem mensagens[],int qtdMensagens,char username[],int indexStorage[]);
void DelMensagensLidas(struct tagMensagem mensagens[],int qtdMensagens,int indexDel);
/*DEFINIÇÕES*/

/*Users*/
int SearchUser(struct tagUser users[], int qtdUsers, char username[])
{
	int i = 0;

	for (i = 0;i < qtdUsers;i++)	//Percorrer todos os usernames
	{
		if (StringCompareCI(users[i].username,username) == 0)	//Comparar case insensitive
		{
			return i;	//Retorna index do user no campo
		}
	}
	return -1;	//Nao encontrou user
}

void DelUser(struct tagUser users[],int qtdUsers,int indexUser)
{
	//Puxa todas as posicoes aseguir a indexUser uma posicao para tras
	int i = indexUser;

	for(;i < qtdUsers-1;i++)
	{
		users[i] = users[i+1];
	}
}

/*Password*/
int StrongPass(char password[])
{
	int qtdChars = 0;
	int qtdSymbol = 0;
	int qtdNum = 0;
	int qtdUp = 0;
	int qtdLower = 0;

	for(qtdChars = 0; password[qtdChars] != '\0'; qtdChars++)
	{
		if( (password[qtdChars] <= 47) || (password[qtdChars] >= 58 && password[qtdChars] <= 64) || (password[qtdChars] >= 91 && password[qtdChars] <= 96) || (password[qtdChars] >= 123))
		{
			qtdSymbol++;
		}
		else if(password[qtdChars] >= '0' && password[qtdChars] <= '9')
		{
			qtdNum++;
		}
		else if(password[qtdChars] >= 'a' && password[qtdChars] <= 'z')
		{
			qtdLower++;
		}
		else if(password[qtdChars] >= 'A' && password[qtdChars] <= 'Z')
		{
			qtdUp++;
		}
	}

	if(qtdChars >= 7 && qtdLower >= 2 && qtdNum >= 2 && qtdSymbol >= 2 && qtdUp >= 2)
		return 1;
	return 0;
}


int PasswordCheck(char password[], char realPassword[])
{
	if (strcmp(password, realPassword) == 0)	//Compara case sensitive
	{
		return 1;	//Password correta
	}
	return 0;	//Password nao esta correta
}

/*Mensagens*/
int DelMessages(struct tagMensagem mensagens[],int qtdMensagens,char username[])
{
	//Retorna nova quantidade de mensagens apos a remocao 
	int i = 0;

	for(i = 0;i < qtdMensagens;i++)
	{
		if(StringCompareCI(mensagens[i].userOrigem,username) == 0)
		{
			AuxDelMessages(mensagens,qtdMensagens,i);
			qtdMensagens--;
			i = 0;
		}
	}
	return qtdMensagens;
}

void AuxDelMessages(struct tagMensagem mensagens[],int qtdMensagens,int delIndex)
{
	int i = delIndex;

	for(;i < qtdMensagens - 1;i++)
	{
		mensagens[i] = mensagens[i+1];
	}
}

void SearchMessages(struct tagMensagem mensagens[],int qtdMensagens,char username[],int indexStorage[])
{
	//Encontra todas as mensagens enviadas para username e armazena o index delas no indexStorage
	int i = 0,j = 0;

	for(i = 0;i < qtdMensagens;i++)
	{
		if(StringCompareCI(mensagens[i].userDestino,username) == 0)
		{
			indexStorage[j++] = i;
		}
	}
}

void DelMensagensLidas(struct tagMensagem mensagens[],int qtdMensagens,int indexDel)
{
	int i = indexDel;

	for(;i < qtdMensagens-1;i++)
	{
		mensagens[i] = mensagens[i+1];
	}
}