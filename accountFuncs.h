#pragma once
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "consts.h"

int SearchUser(struct tagUser users[], int qtdUsers, char username[50 + 1]);
int PasswordCheck(char password[], char realPassword[]);

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
