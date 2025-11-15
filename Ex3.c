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
	int passCheck = 0,userCheck = 0;
	int quitCheckLogin = -1,quitCheckNew = -1;
	int passStrenght = -1;
	char usernameApagar[50+1];
	int delIndex = -1;

	while (1)
	{
		do
		{
			bootTask = BootMenu();	//Menu incial
			getchar();	//Remover \n

			if (EntreAB(bootTask, 0, 1) == 0)	//Opcao invalida
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

			loginIndex = SearchUser(users, qtdUsers, usernameLogin);	//Ter indice do user

			if (loginIndex == -1)	//Nao encontrou user
			{
				puts("Username nao existe!");
			}
			else	//User existe
			{
				do
				{
					puts("Digite 'quit' para sair!");
					printf("Indique a password de %s: ", usernameLogin);
					scanf("%s", passwordLogin);
					passwordLogin[50] = '\0';

					passCheck = PasswordCheck(passwordLogin, users[loginIndex].password);	//Verifica se password está correta
					quitCheckLogin = strcmp("quit", passwordLogin);	//Verifica se é para sair

					if (quitCheckLogin == 0)	//User digitou quit para sair da acao de login
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
				} while (passCheck == 0);
			}
			if (loggedIn == 1 && loginIndex == 0 && quitCheckLogin != 0)	//User logado é o admin
			{
				puts("Terminando programa...");
				break;
			}
			else if(loggedIn == 1 && loginIndex != 0 && quitCheckLogin != 0)	//Se user logado nao for Admin
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

			loginIndex = SearchUser(users, qtdUsers, usernameLogin);	//Encontrar indice de user

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

					passCheck = PasswordCheck(passwordLogin, users[loginIndex].password);	//Verificar se password está correta

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
				} while (passCheck == 0);

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
						if(qtdUsers == MAX_USERS)	//Maximo de users
						{
							printf("Maxima quantidade de users atingidos!\n");
						}else
						{
							do	//Username de novo user
							{
								puts("Digite 'quit' para sair!");
								printf("Indique o username: ");
								scanf("%s",users[qtdUsers].username);
								users[qtdUsers].username[50] = '\0';
								getchar();

								userCheck = SearchUser(users,qtdUsers,users[qtdUsers].username);	//Verificar se nome já existe
								quitCheckNew = strcmp("quit",users[qtdUsers].username);	//Verificar se é para sair

								if(userCheck != -1)
								{
									puts("Username ja existe!");
								}else if(quitCheckNew == 0)
								{
									puts("Saindo...");
								}
							}while(userCheck != -1 && quitCheckNew != 0);

							//Nome de user
							if(quitCheckNew == 0)	//Se user quiser sair
							{
								break;
							}else	//User nao quer sair
							{
								printf("Indique nome user: ");
								gets(users[qtdUsers].nome);
								users[qtdUsers].nome[50] = '\0';

								//Password de user novo
							 	do	
							 	{
									puts("Password precisa ter pelo menos 7 caracteres;");
									puts("---------------------------------------------");
									puts("Password precisa ter pelo menos 2 simbolos;");
									puts("---------------------------------------------");
									puts("Password precisa ter pelo menos 2 maisuculas;");
									puts("---------------------------------------------");
									puts("Password precisa ter pelo menos 2 minusculas;");
									puts("---------------------------------------------");
									puts("Password precisa ter pelo menos 2 numeros;");
									puts("---------------------------------------------");
									printf("Indique a sua password: ");
									gets(users[qtdUsers].password);
									users[qtdUsers].password[50] = '\0';
	
									passStrenght = StrongPass(users[qtdUsers].password);

									if(passStrenght != 1)
									{
										printf("Password muito fraca, tente novamente!\n");
									}
								}while(passStrenght != 1);

								printf("Conta de %s criada com sucesso!\n",users[qtdUsers].username);
							}
						}
						qtdUsers++;	//Aumentar qtd de users pois foi criado um novo
						system("pause");
						system("cls");
						break;	//Acabar de criar user

					case 2:	//Apagar User
						if(qtdUsers == 1)	//Apenas existe o administrador
						{
							puts("Nao existem utilizadores para apagar!");
						}else
						{
							do
							{
								printf("Indique o username da conta que pretende apagar: ");
								scanf("%s",usernameApagar);
								usernameApagar[50] = '\0';
								delIndex = SearchUser(users,qtdUsers,usernameApagar);	//Index do user a apagar

								if(delIndex == 0)	//Indice do admin
								{
									puts("Nao pode apagar o administrador!");
									system("pause");
									system("cls");
								}else if(delIndex == -1)
								{
									puts("Username não existe!");
									system("pause");
									system("cls");
								}
							} while (delIndex == -1 || delIndex == 0);

							//Apaga as mensagens que esse user enviou retornando a quantidade de mensagens
							qtdMensagem = DelMensagens(mensagens,qtdMensagem,users[delIndex].username);
							//Apagar user
							DelUser(users,qtdUsers,delIndex);

							qtdUsers--;	//Diminuir quantiadade de users
						}
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

