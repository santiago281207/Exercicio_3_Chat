#pragma once
#include <stdio.h>
#include <string.h>
#include "structs.h"

int BootMenu(void);
int EntreAB(int x,int min,int max);
int SearchUser(struct tagUser users[],int qtdUsers,char username[50+1]);


int SearchUser(struct tagUser users[],int qtdUsers,char username[50+1])
{
	int i = 0;

	for(i = 0;i < qtdUsers;i++)
	{

	}
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