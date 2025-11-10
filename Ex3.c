#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "consts.h"
#include "funcs.h"

int main()
{
	struct tagUser users[MAX_USERS] = {"sa","System Administrator","sa"};
	int qtdUsers = 1;;
	struct tagMensagem mensagens[MAX_MSG];
	int qtdMensagem = 0;
	int firstTask = 0;

	while(1)
	{
		do
		{
			firstTask = BootMenu();

			if(EntreAB(firstTask,0,1) == 0)
			{
				puts("Selecione uma opcao valida!");
			}else if(firstTask == 1)	//Login
			{
				do
				{

				}while();
			}
		}while(EntreAB(firstTask,0,1) == 0);

		if(firstTask == 0)
		{
			break;
		}

		system("pause");
		system("cls");
	}

	puts("Saindo...");
	return 0;
}