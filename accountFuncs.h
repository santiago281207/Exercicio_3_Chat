#pragma once
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "consts.h"

int SearchUser(struct tagUser users[], int qtdUsers, char username[]);
int PasswordCheck(char password[], char realPassword[]);
int StrongPass(char password[]);

int PasswordCheck(char password[], char realPassword[])
{
	if (strcmp(password, realPassword) == 0)	//Compara case sensitive
	{
		return 1;	//Password correta
	}
	return 0;	//Password nao esta correta
}

int SearchUser(struct tagUser users[], int qtdUsers, char username[50 + 1])
{
	int i = 0;
	char aux1[50 + 1],aux2[50+1];

	strcpy(aux2, username);
	_strupr(aux2);

	for (i = 0;i < qtdUsers;i++)	//Percorrer todos os usernames
	{
		strcpy(aux1, users[i].username);
		_strupr(aux1);

		if (strcmp(aux1,aux2) == 0)	//Comparar case insensitive
		{
			return i;	//Retorna index do user no campo
		}
	}
	return -1;	//Nao encontrou user
}

int StrongPass(char password[])
{
	int qtdChars = 0;
	int qtdSymbol = 0;
	int qtdNum = 0;
	int qtdUp = 0;
	int qtdLower = 0;

	for(qtdChars = 0;password[qtdChars] != '\0';qtdChars++)
	{
		if(password[qtdChars] <= 47 || password[qtdChars] >= 58 && password[qtdChars] <= 64 || password[qtdChars] >= 91 && password[qtdChars] <= 96)
		{
			qtdSymbol++;
		}else if(password[qtdChars] >= '0' && password[qtdChars] <= '9')
		{
			qtdNum++;
		}else if(password[qtdChars] >= 'a' && password[qtdChars] <= 'z')
		{
			qtdLower++;
		}else if(password[qtdChars] >= 'A' && password[qtdChars] <= 'Z')
		{
			qtdUp++;
		}
	}

	if(qtdChars >= 7 && qtdLower >= 2 && qtdNum >= 2 && qtdSymbol >= 2 && qtdUp >= 2)
		return 1;	//Password forte
	return 0;	//Password fraca
}