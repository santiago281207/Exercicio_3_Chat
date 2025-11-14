#pragma once
#include <stdio.h>
#include <string.h>
#include "structs.h"

int AdminMenu(void);
int CommonUserMenu(char username[]);
int BootMenu(void);	//Menu de login e terminar
int EntreAB(int x, int min, int max);

int BootMenu(void)
{
	int task = 0;

	puts("=== JOIN CHAT ===");
	puts("1 - Login.");
	puts("0 - Sair.");
	puts("=================");
	scanf("%d", &task);

	return task;
}

int AdminMenu(void)
{
	int task;
	printf("=== BEM VINDO ADMINISTRADOR ===\n");
	puts("1 - Criar User.");
	puts("2 - Apagar User.");
	puts("3 - Ler mensagens.");
	puts("4 - Apagar mensagens.");
	puts("5 - Enviar mensagem.");
	puts("0 - Sair.");

	scanf("%d", &task);
	return task;
}

int CommonUserMenu(char username[])
{
	int task;
	printf("=== BEM VINDO %s ===\n", username);
	puts("1 - Ler mensagens.");
	puts("2 - Apagar mensagens.");
	puts("3 - Enviar mensagem.");
	puts("0 - Sair.");

	scanf("%d", &task);
	return task;
}

int EntreAB(int x, int min, int max)
{
	return x >= min && x <= max;
}
