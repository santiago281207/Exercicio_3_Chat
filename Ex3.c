#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "consts.h"
#include "funcs.h"
#include "accountFuncs.h"

int main()
{
	struct tagUser users[MAX_USERS] = { "sa","System Administrator","sa" };	//User admin guardado na posicao 0
	int qtdUsers = 1;	//Começa a 1 pois já existe o user admin
	struct tagMensagem mensagens[MAX_MSG];
	int qtdMensagem = 0;
	/*Variaveis de Menu*/
	int bootTask = -1;
	int adminTask = 0;
	int userTask = 0;

	/**/
	char usernameLogin[50 + 1], passwordLogin[50 + 1];
	int loginIndex = 0, loggedIn = 0;

	while (1)
	{
		do
		{
			bootTask = BootMenu();
			getchar();	//Remover \n

			if (EntreAB(bootTask, 0, 1) == 0)
			{
				puts("Selecione uma opcao valida!");
				system("pause");
				system("cls");
			}
		} while (EntreAB(bootTask, 0, 1) == 0);

		if (bootTask == 0)	//Terminar programa
		{
			break;
		}
		else if (bootTask == 1)	//Login
		{
			printf("Indique o username: ");
			scanf("%s", usernameLogin);
			getchar();

			loginIndex = SearchUser(users, qtdUsers, usernameLogin);

			if (loginIndex == -1)	//Nao encontrou user
			{
				puts("Username nao existe!");
			}
			else	//Encontrou user
			{
				do
				{
					puts("Digite 'quit' para sair!");
					printf("Indique a password de %s: ", usernameLogin);
					scanf("%s", passwordLogin);

					if (strcmp("quit", passwordLogin) == 0)	//User digitou quit para sair da acao de login
					{
						puts("Saindo..");
						loggedIn = 0;
						break;
					}
					else if (PasswordCheck(passwordLogin, users[loginIndex].password) == 0)	//Password incorreta
					{
						puts("Password incorreta!");
						system("pause");
						system("cls");
					}
					else if (PasswordCheck(passwordLogin, users[loginIndex].password) == 1)	//Password está correta
					{
						loggedIn = 1;	//Sinalizador de que o user está "logado" na conta neste momento
					}
				} while (PasswordCheck(passwordLogin, users[loginIndex].password) == 0 && strcmp("quit",passwordLogin) != 0);

			}
		}	//Login task

		if (loggedIn == 1)	//User conseguiu entrar na conta
		{
			printf("Voce tem %d mensagens nao lidas!\n", users[loginIndex].msgNaoLidas);
			if (loginIndex == 0)	//System administrator
			{
				do	//Ciclo menu do admin
				{
					adminTask = AdminMenu();
					switch (adminTask)
					{
					case 1:	//Criar user
						break;
					case 2:	//Apagar User
						break;
					case 3:	//Ler mensagens
						break;
					case 4:	//Apagar mensagens
						break;
					case 5:	//Enviar mensagens
						break;
					case 0:	//Sair
						puts("Saindo...");
						break;
					default:
						printf("Introduza uma opcao valida!\n");
					}
					system("pause");
					system("cls");
				} while (adminTask != 0);

			}
			else	//Outro user
			{
				do	//Ciclo de um user normal
				{
					userTask = CommonUserMenu(users[loginIndex].username);

					switch (userTask)
					{

					}

				} while (EntreAB(userTask,0,3) == 0);

			}

		}

		system("pause");	//STACK OVERFLOW
		system("cls");

	}	//Ciclo infinito

	puts("Saindo...");
	return 0;
} //main
