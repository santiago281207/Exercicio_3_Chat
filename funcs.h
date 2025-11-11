#pragma once
#include <stdio.h>
#include <string.h>
#include "structs.h"

int BootMenu(void);	//Menu de login e terminar
int EntreAB(int x,int min,int max);
int SearchUser(struct tagUser users[],int qtdUsers,char username[50+1]);
int PasswordCheck(char password[],char realPassword[]);

int SearchUser(struct tagUser users[],int qtdUsers,char username[50+1])
{
	int i = 0;

	for(i = 0;i < qtdUsers;i++)	//Percorrer todos os usernames
	{
		if(strupr(users[i].username) == strupr(username))	//Comparar case insensitive
		{
			return i;	//Retorna index do user no campo
		}
	}
	return -1;	//Nao encontrou user
}

int BootMenu(void)
{
	int task = 0;

	puts("=== JOIN CHAT ===");
	puts("1 - Login.");
	puts("0 - Sair.");
	puts("=================");
	scanf("%d",&task);

	return task;
}

int EntreAB(int x,int min,int max)
{
	return x >= min && x <= max;
}

int PasswordCheck(char password[],char realPassword[])
{
	if(strcmp(password,realPassword) == 0)	//Compara case sensitive
	{
		return 1;	//Password correta
	}
	return 0;	//Password nao esta correta
}
