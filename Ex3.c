#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "consts.h"
#include "funcs.h"
#include "accountFuncs.h"

int main()
{
	static struct tagUser users[MAX_USERS] = { "sa","System Administrator","sa" };	//User admin guardado na posicao 0
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
	int passCheck = 0;

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

		if (bootTask == 0)	//Terminar programa apenas admin
		{
			printf("Indique o username: ");
			scanf("%s", usernameLogin);
			usernameLogin[50] = '\0';
			getchar();
			loginIndex = SearchUser(users, qtdUsers, usernameLogin);

			if (loginIndex == -1)	//Nao encontrou user
			{
				puts("Username nao existe!");
			}
			else
			{
				do
				{
					puts("Digite 'quit' para sair!");
					printf("Indique a password de %s: ", usernameLogin);
					scanf("%s", passwordLogin);
					passwordLogin[50] = '\0';

					passCheck = PasswordCheck(passwordLogin, users[loginIndex].password);

					if (strcmp("quit", passwordLogin) == 0)	//User digitou quit para sair da acao de login
					{
						puts("Saindo..");
						break;
					}
					else if (passCheck == 0)	//Password incorreta
					{
						puts("Password incorreta!");
						system("pause");
						system("cls");
					}
					else if (passCheck == 1)	//Password está correta
					{
						loggedIn = 1;	//Sinalizador de que o user está "logado" na conta neste momento
					}
				} while (passCheck != 0);
			}
			if (loggedIn == 1 && loginIndex == 0 && strcmp("quit", passwordLogin) != 0)
			{
				puts("Terminando programa...");
				break;
			}
			else if(loggedIn == 1 && loginIndex != 0 && strcmp("quit", passwordLogin) != 0)
			{
				puts("Apenas administrador pode terminar o programa!");
			}
		}
		else if (bootTask == 1)	//Login
		{
			printf("Indique o username: ");
			scanf("%s", usernameLogin);
			usernameLogin[50] = '\0';

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
					passwordLogin[50] = '\0';

					passCheck = PasswordCheck(passwordLogin, users[loginIndex].password);

					if (strcmp("quit", passwordLogin) == 0)	//User digitou quit para sair da acao de login
					{
						puts("Saindo..");
						break;
					}
					else if (passCheck == 0)	//Password incorreta
					{
						puts("Password incorreta!");
						system("pause");
						system("cls");
					}
					else if (passCheck == 1)	//Password está correta
					{
						loggedIn = 1;	//Sinalizador de que o user está "logado" na conta neste momento
					}
				} while (passCheck != 0);

			}
		}	//Login task

		if (loggedIn == 1)	//User conseguiu entrar na conta
		{
			if (loginIndex == 0)	//System administrator
			{
				do	//Ciclo menu do admin
				{
					printf("Voce tem %d mensagens nao lidas!\n", users[loginIndex].msgNaoLidas);
					adminTask = AdminMenu();
					switch (adminTask)
					{
					case 1:	//Criar user
						system("pause");
						system("cls");
						break;
					case 2:	//Apagar User
						system("pause");
						system("cls");
						break;
					case 3:	//Ler mensagens
						system("pause");
						system("cls");
						break;
					case 4:	//Apagar mensagens
						system("pause");
						system("cls");
						break;
					case 5:	//Enviar mensagens
						system("pause");
						system("cls");
						break;
					case 0:	//Sair
						puts("Saindo...");
						break;
					default:
						printf("Introduza uma opcao valida!\n");
						break;
					}
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

				} while (userTask != 0);

			}

		}

		bootTask = -1;
		adminTask = 0;
		userTask = 0;
		loggedIn = 0;
		loginIndex = -1;
		system("pause");
		system("cls");
	}	//Ciclo infinito

	return 0;
} //main
