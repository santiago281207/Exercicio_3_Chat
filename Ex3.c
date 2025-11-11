#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "consts.h"
#include "funcs.h"

int main()
{
	struct tagUser users[MAX_USERS] = {"sa","System Administrator","sa"};	//User admin guardado na posicao 0
	int qtdUsers = 1;;
	struct tagMensagem mensagens[MAX_MSG];
	int qtdMensagem = 0;

	/*Variaveis de Menu*/
	int firstTask = 0;

	/**/
	char usernameLogin[50+1],passwordLogin[50+1];
	int loginIndex = 0,loggedIn = 0;

	while(1)
	{
		do
		{
			firstTask = BootMenu();
			getchar();	//Remover \n

			if(EntreAB(firstTask,0,1) == 0)
			{
				puts("Selecione uma opcao valida!");
			}
		}while(EntreAB(firstTask,0,1) == 0);

		if(firstTask == 0)	//Terminar programa
		{
			break;
		}else if(firstTask == 1)	//Login
		{
			printf("Indique o username: ");
			scanf("%s",usernameLogin);
			getchar();

			loginIndex = SearchUser(users,qtdUsers,usernameLogin);

			if(loginIndex == -1)	//Nao encontrou user
			{
				puts("Username nao existe!");
			}else	//Encontrou user
			{
				do
				{
					puts("Digite 'quit' para sair!");
					printf("Indique a password de %s: ",usernameLogin);
					scanf("%s",passwordLogin);

					if(PasswordCheck(passwordLogin,users[loginIndex].password) == 0)
					{
						puts("Password incorreta!");
					}else if(strcmp("quit",passwordLogin) == 0)
					{
						puts("Saindo..");
						loggedIn = 0;
						break; 
					}else if(PasswordCheck(passwordLogin,users[loginIndex].password) == 1)
					{
						loggedIn = 1;
					}
				}while(PasswordCheck(passwordLogin,users[loginIndex].password) == 0);

			}
		}	//Login task

			if(loggedIn == 1)	//User conseguiu entrar na conta
			{
				if(loginIndex == 0)	//System administrator
				{
					do	//Ciclo menu do admin
					{

					}while();

				}else	//Outro user
				{
					do	//Ciclo de um user normal
					{

					}while();

				}

			}


		system("pause");
		system("cls");

		}	//Ciclo infinito

	puts("Saindo...");
	return 0;
} //main

