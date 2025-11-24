#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#include "structs.h"
#include "consts.h"
#include "funcs.h"
#include "accountFuncs.h"

struct tagUser users[MAX_USERS] = {"sa", "System Administrator", "sa"}; // User admin guardado na posicao 0
struct tagMensagem mensagens[MAX_MSG];

int main()
{
	time_t atual;
	struct tm *dados;
	int qtdUsers = 1;														// Começa a 1 pois já existe o user admin
	int qtdMensagem = 0;
	int userMessagesIndex[MAX_MSG];

	/*Variaveis de Menu*/
	int bootTask = -1;
	int adminTask = 0;
	int userTask = 0;
	int messagesKey = 0;

	/**/
	char usernameLogin[50 + 1], passwordLogin[50 + 1];
	char usernameApagar[50 + 1], usernameDestino[50 + 1];
	int loginIndex = 0, loggedIn = 0;
	int passCheck = 0, userCheck = 0;
	int quitCheckLogin = -1, quitCheckNew = -1;
	int passStrenght = -1,sentIndex;
	int delIndex = -1, destinoIndex = -1;
	int i = 0;
	int msgApagadasCount = 0;

	while (1)
	{
		do
		{
			bootTask = BootMenu(); // Menu incial
			getchar();			   // Remover \n

			if (EntreAB(bootTask, 0, 1) == 0) // Opcao invalida
			{
				puts("Selecione uma opcao valida!");
				system("pause");
				system("cls");
			}
		} while (EntreAB(bootTask, 0, 1) == 0);

		if (bootTask == 0) // Terminar programa apenas admin
		{
			printf("Indique o username: ");
			scanf("%s", usernameLogin);
			usernameLogin[50] = '\0';
			getchar();

			loginIndex = SearchUser(users, qtdUsers, usernameLogin); // Ter indice do user

			if (loginIndex == -1) // Nao encontrou user
			{
				puts("Username nao existe!");
			}
			else // User existe
			{
				do
				{
					puts("Digite 'quit' para sair!");
					printf("Indique a password de %s: ", usernameLogin);
					scanf("%s", passwordLogin);
					passwordLogin[50] = '\0';

					passCheck = PasswordCheck(passwordLogin, users[loginIndex].password); // Verifica se password está correta
					quitCheckLogin = strcmp("quit", passwordLogin);						  // Verifica se é para sair

					if (quitCheckLogin == 0) // User digitou quit para sair da acao de login
					{
						puts("Saindo..");
						break;
					}
					else if (passCheck == 0) // Password incorreta
					{
						puts("Password incorreta!");
						system("pause");
						system("cls");
					}
					else if (passCheck == 1) // Password está correta
					{
						loggedIn = 1; // Sinalizador de que o user está "logado" na conta neste momento
					}
				} while (passCheck == 0);
			}
			if (loggedIn == 1 && loginIndex == 0 && quitCheckLogin != 0) // User logado é o admin
			{
				puts("Terminando programa...");
				break;
			}
			else if (loggedIn == 1 && loginIndex != 0 && quitCheckLogin != 0) // Se user logado nao for Admin
			{
				puts("Apenas administrador pode terminar o programa!");
			}
		}
		else if (bootTask == 1) // Login
		{
			system("cls");
			printf("Indique o username: ");
			scanf("%s", usernameLogin);
			usernameLogin[50] = '\0';

			getchar();

			loginIndex = SearchUser(users, qtdUsers, usernameLogin); // Encontrar indice de user

			if (loginIndex == -1) // Nao encontrou user
			{
				puts("Username nao existe!");
			}
			else // Encontrou user
			{
				do
				{
					puts("Digite 'quit' para sair!");
					printf("Indique a password de %s: ", usernameLogin);
					scanf("%s", passwordLogin);
					passwordLogin[50] = '\0';

					passCheck = PasswordCheck(passwordLogin, users[loginIndex].password); // Verificar se password está correta

					if (strcmp("quit", passwordLogin) == 0) // User digitou quit para sair da acao de login
					{
						puts("Saindo..");
						break;
					}
					else if (passCheck == 0) // Password incorreta
					{
						puts("Password incorreta!");
						system("pause");
						system("cls");
					}
					else if (passCheck == 1) // Password está correta
					{
						loggedIn = 1; // Sinalizador de que o user está "logado" na conta neste momento
					}
				} while (passCheck == 0);
			}
		} // Login task

		if (loggedIn == 1) // User conseguiu entrar na conta
		{
			if (loginIndex == 0) // System administrator
			{
				system("cls");
				do // Ciclo menu do admin
				{
					printf("Voce tem %d mensagens nao lidas!\n", users[loginIndex].msgNaoLidas);
					adminTask = AdminMenu();
					switch (adminTask)
					{
					case 1:						   // Criar user
						if (qtdUsers == MAX_USERS) // Maximo de users
						{
							printf("Maxima quantidade de users atingidos!\n");
						}
						else
						{
							system("cls");
							do // Username de novo user
							{
								puts("Digite 'quit' para sair!");
								printf("Indique o username: ");
								scanf("%s", users[qtdUsers].username);
								users[qtdUsers].username[50] = '\0';
								getchar();

								userCheck = SearchUser(users, qtdUsers, users[qtdUsers].username); // Verificar se nome já existe
								quitCheckNew = strcmp("quit", users[qtdUsers].username);		   // Verificar se é para sair

								if (userCheck != -1)
								{
									puts("Username ja existe!");
								}
								else if (quitCheckNew == 0)
								{
									puts("Saindo...");
								}
							} while (userCheck != -1 && quitCheckNew != 0);

							// Nome de user
							if (quitCheckNew == 0) // Se user quiser sair
							{
								break;
							}
							else // User nao quer sair
							{
								printf("Indique nome user: ");
								gets(users[qtdUsers].nome);
								users[qtdUsers].nome[50] = '\0';
								puts("");
								// Password de user novo
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

									if (passStrenght != 1)
									{
										printf("Password muito fraca, tente novamente!\n");
									}
								} while (passStrenght != 1);

								printf("Conta de %s criada com sucesso!\n", users[qtdUsers].username);
							}
						
						
						if (qtdMensagem == MAX_MSG - 1)
						{
							puts("Limite maximo de mensagens atigindo!");
						}
						else
						{
							strcpy(mensagens[qtdMensagem].userOrigem,"Sistema");
							strcpy(mensagens[qtdMensagem].userDestino, users[qtdUsers].username); // Colcoar username destinatario

							strcpy(mensagens[qtdMensagem].assunto,"Boas vindas ao chat");
							strcpy(mensagens[qtdMensagem].corpoMensagem,"Seja bem vindo a este grupo chat de trabalho.\nAqui pode enviar mensagens para os seus colegas de trabalho em turnos diferentes.");
							mensagens[qtdMensagem].lida = 0;										  // Nao foi lida

							time(&atual);			   // Obter tempo em segundos
							dados = localtime(&atual); // Converter valor para dados organizados "struct tm"

							mensagens[qtdMensagem].dataHora.data.dia = dados->tm_mday;
							mensagens[qtdMensagem].dataHora.data.mes = dados->tm_mon + 1;	  // Mes de 0 a 11 por isso +1
							mensagens[qtdMensagem].dataHora.data.ano = dados->tm_year + 1900; // Da os anos desde 1900 por isso adiciona se 1900
							mensagens[qtdMensagem].dataHora.horario.hora = dados->tm_hour;
							mensagens[qtdMensagem].dataHora.horario.minuto = dados->tm_min;
							mensagens[qtdMensagem].dataHora.horario.segundo = dados->tm_sec;
							mensagens[qtdMensagem].msgAuto = 1;

							users[qtdUsers].qtdMsgTotal++;
							users[qtdUsers].qtdMsgAuto++;
							users[qtdUsers].msgNaoLidas++;
							qtdMensagem++;
						}
						
						
						}

						qtdUsers++; // Aumentar qtd de users pois foi criado um novo
						system("pause");
						system("cls");
						break; // Acabar de criar user
					case 2:				   // Apagar User
						if (qtdUsers == 1) // Apenas existe o administrador
						{
							puts("Nao existem utilizadores para apagar!");
						}
						else
						{
							system("cls");
							do
							{
								printf("Indique o username da conta que pretende apagar: ");
								scanf("%s", usernameApagar);
								usernameApagar[50] = '\0';
								delIndex = SearchUser(users, qtdUsers, usernameApagar); // Index do user a apagar

								if (delIndex == 0) // Indice do admin
								{
									puts("Nao pode apagar o administrador!");
									system("pause");
									system("cls");
								}
								else if (delIndex == -1)
								{
									puts("Username não existe!");
									system("pause");
									system("cls");
								}
							} while (delIndex == -1 || delIndex == 0);

							// Apaga as mensagens que esse user enviou retornando a quantidade de mensagens
							qtdMensagem = DelMessages(mensagens, qtdMensagem, users[delIndex].username);
							// Apagar user
							DelUser(users, qtdUsers, delIndex);

							qtdUsers--; // Diminuir quantiadade de users
						}
						system("pause");
						system("cls");
						break;
					case 3: // Ler mensagens
						if (users[loginIndex].qtdMsgTotal == 0)
						{
							puts("Nao existem mensagens para ler!");
						}
						else
						{
							system("cls");
							SearchMessages(mensagens, qtdMensagem, users[loginIndex].username, userMessagesIndex);
							for (i = 0; i < users[loginIndex].qtdMsgTotal;)
							{
								puts("=== LENDO MENSAGENS ===");
								puts("Digite 'q' para sair.");
								printf("Username do remetente: %s.\n", mensagens[userMessagesIndex[i]].userOrigem);
								printf("Username do destinatario: %s\n", mensagens[userMessagesIndex[i]].userDestino);
								printf("Data de envio: %d/%d/%d.\n", mensagens[userMessagesIndex[i]].dataHora.data.dia, mensagens[userMessagesIndex[i]].dataHora.data.mes, mensagens[userMessagesIndex[i]].dataHora.data.ano);
								printf("Hora de envio: %d:%d:%d.\n", mensagens[userMessagesIndex[i]].dataHora.horario.hora, mensagens[userMessagesIndex[i]].dataHora.horario.minuto, mensagens[userMessagesIndex[i]].dataHora.horario.segundo);
								printf("Assunto da mensagem: %s\n", mensagens[userMessagesIndex[i]].assunto);
								printf("Corpo da mensagem: %s\n", mensagens[userMessagesIndex[i]].corpoMensagem);
								printf("Mensagem lida: %s\n", mensagens[userMessagesIndex[i]].lida == 1 ? "sim" : "nao");
								printf("[%d/%d]\n", i+1, users[loginIndex].qtdMsgTotal);

								if (mensagens[userMessagesIndex[i]].lida == 0)
								{
									mensagens[userMessagesIndex[i]].lida = 1;
									users[loginIndex].msgNaoLidas--;

									if(qtdMensagem < 2000 && mensagens[userMessagesIndex[i]].msgAuto == 0)
									{
										sentIndex = SearchUser(users,qtdUsers,mensagens[userMessagesIndex[i]].userOrigem);
									
										strcpy(mensagens[qtdMensagem].userOrigem,"Sistema");
										strcpy(mensagens[qtdMensagem].userDestino, users[sentIndex].username); // Colcoar username destinatario
										strcpy(mensagens[qtdMensagem].assunto,"A seguinte mensagem foi lida.");
										strcpy(mensagens[qtdMensagem].corpoMensagem,mensagens[userMessagesIndex[i]].corpoMensagem);					
										mensagens[qtdMensagem].lida = 0;										  // Nao foi lida

										time(&atual);			   // Obter tempo em segundos
									
										dados = localtime(&atual); // Converter valor para dados organizados "struct tm"
										
									
										mensagens[qtdMensagem].dataHora.data.dia = dados->tm_mday;
										mensagens[qtdMensagem].dataHora.data.mes = dados->tm_mon + 1;	  // Mes de 0 a 11 por isso +1
										mensagens[qtdMensagem].dataHora.data.ano = dados->tm_year + 1900; // Da os anos desde 1900 por isso adiciona se 1900								
										mensagens[qtdMensagem].dataHora.horario.hora = dados->tm_hour;
										mensagens[qtdMensagem].dataHora.horario.minuto = dados->tm_min;
										mensagens[qtdMensagem].dataHora.horario.segundo = dados->tm_sec;
										mensagens[qtdMensagem].msgAuto = 1;

										users[sentIndex].qtdMsgTotal++;
										users[sentIndex].qtdMsgAuto++;
										users[sentIndex].msgNaoLidas++;
										qtdMensagem++;
									}
								}

								printf("Introduza '>' para ir para proxima mensagem ou '<' para ir para mensagem anterior...\n");
								messagesKey = getchar();

								if (tolower(messagesKey) == 'q')
								{
									puts("Saindo...");
									break;
								}
								else if (messagesKey == '>') // Proxima mensagem
								{
									if(i == users[loginIndex].qtdMsgTotal)
									{
										puts("Chegou ao fim das mensagens!");
									}else if(i >= 0)
										i++;
								}
								else if (messagesKey == '<') // Mensagem anterior
								{
									if(i == 0)
									{
										puts("Chegou ao inicio das mensagens!");
									}else if(i > 0)
										i--;
								}
								system("cls");
							}
						}
						system("pause");
						system("cls");
						break;
					case 4: // Apagar mensagens já lidas
						if (users[loginIndex].msgNaoLidas == users[loginIndex].qtdMsgTotal)
						{
							puts("Nao existem mensagens lidas!");
						}
						else
						{
							system("cls");
							SearchMessages(mensagens, qtdMensagem, users[loginIndex].username, userMessagesIndex);
							for (i = 0; i < users[loginIndex].qtdMsgTotal; i++)
							{
								if (mensagens[userMessagesIndex[i]].lida == 1)
								{
									DelMensagensLidas(mensagens, qtdMensagem, userMessagesIndex[i]);
									users[loginIndex].qtdMsgTotal--;
									if(strcmp(mensagens[userMessagesIndex[i]].userOrigem,"Sistema") == 0)
									{
										users[loginIndex].qtdMsgAuto--;
									}else
									{
										users[loginIndex].qtdMsgReal--;
									}
									
									i--;
									msgApagadasCount++;
								}
							}
							printf("Foram apagadas %d mensagens!\n",msgApagadasCount);
						}
						system("pause");
						system("cls");
						msgApagadasCount = 0;
						break;
					case 5: // Enviar mensagens

						if (qtdMensagem == MAX_MSG - 1)
						{
							puts("Limite maximo de mensagens atigindo!");
						}
						else
						{
							system("cls");
							// Introduzir username de destino
							do
							{
								printf("Indique o username do destinatario: ");
								scanf("%s", usernameDestino);
								usernameDestino[50] = '\0';
								getchar();

								destinoIndex = SearchUser(users, qtdUsers, usernameDestino);
								if (destinoIndex == -1)
								{
									puts("Username nao existe!");
									system("pause");
									system("cls");
								}
							} while (destinoIndex == -1);

							puts("Indique o assunto da mensagem:");
							gets(mensagens[qtdMensagem].assunto);
							mensagens[qtdMensagem].assunto[50] = '\0';

							puts("Corpo da mensagem:");
							gets(mensagens[qtdMensagem].corpoMensagem);

							strcpy(mensagens[qtdMensagem].userOrigem, users[loginIndex].username);	  // Colocar username remetente
							strcpy(mensagens[qtdMensagem].userDestino, users[destinoIndex].username); // Colcoar username destinatario
							mensagens[qtdMensagem].lida = 0;										  // Nao foi lida

							time(&atual);			   // Obter tempo em segundos
							dados = localtime(&atual); // Converter valor para dados organizados "struct tm"

							mensagens[qtdMensagem].dataHora.data.dia = dados->tm_mday;
							mensagens[qtdMensagem].dataHora.data.mes = dados->tm_mon + 1;	  // Mes de 0 a 11 por isso +1
							mensagens[qtdMensagem].dataHora.data.ano = dados->tm_year + 1900; // Da os anos desde 1900 por isso adiciona se 1900
							mensagens[qtdMensagem].dataHora.horario.hora = dados->tm_hour;
							mensagens[qtdMensagem].dataHora.horario.minuto = dados->tm_min;
							mensagens[qtdMensagem].dataHora.horario.segundo = dados->tm_sec;

							users[destinoIndex].qtdMsgTotal++;
							users[destinoIndex].qtdMsgReal++;
							users[destinoIndex].msgNaoLidas++;
							qtdMensagem++;

							if(users[destinoIndex].qtdMsgTotal >= 25 && qtdMensagem < 2000)
							{
								strcpy(mensagens[qtdMensagem].userOrigem,"Sistema");
								strcpy(mensagens[qtdMensagem].userDestino, users[qtdUsers].username); // Colcoar username destinatario

								strcpy(mensagens[qtdMensagem].assunto,"25 mensagens");
								strcpy(mensagens[qtdMensagem].corpoMensagem,"Ja tem mais de 25 mensagens acumuladas. Considere em apagar mensagens.");
								mensagens[qtdMensagem].lida = 0;										  // Nao foi lida

								time(&atual);			   // Obter tempo em segundos
								dados = localtime(&atual); // Converter valor para dados organizados "struct tm"

								mensagens[qtdMensagem].dataHora.data.dia = dados->tm_mday;
								mensagens[qtdMensagem].dataHora.data.mes = dados->tm_mon + 1;	  // Mes de 0 a 11 por isso +1
								mensagens[qtdMensagem].dataHora.data.ano = dados->tm_year + 1900; // Da os anos desde 1900 por isso adiciona se 1900
								mensagens[qtdMensagem].dataHora.horario.hora = dados->tm_hour;
								mensagens[qtdMensagem].dataHora.horario.minuto = dados->tm_min;
								mensagens[qtdMensagem].dataHora.horario.segundo = dados->tm_sec;
								mensagens[qtdMensagem].msgAuto = 1;

								users[destinoIndex].qtdMsgTotal++;
								users[destinoIndex].qtdMsgAuto++;
								users[destinoIndex].msgNaoLidas++;
								qtdMensagem++;
							}
						}
						printf("Mensagem enviada para %s com sucesso!\n",users[destinoIndex].username);
						system("pause");
						system("cls");
						break;
					case 0: // Sair
						puts("Saindo...");
						break;
					default:
						printf("Introduza uma opcao valida!\n");
						break;
					}
				} while (adminTask != 0);
			}
			else // Outro user
			{
				system("cls");
				do // Ciclo de um user normal
				{
					printf("Voce tem %d mensagens nao lidas!\n", users[loginIndex].msgNaoLidas);
					userTask = CommonUserMenu(users[loginIndex].username);

					switch (userTask)
					{
					case 1: // Ler mensagens
						if (users[loginIndex].qtdMsgTotal == 0)
						{
							puts("Nao existem mensagens para ler!");
						}
						else
						{
							system("cls");
							SearchMessages(mensagens, qtdMensagem, users[loginIndex].username, userMessagesIndex);

							for (i = 0; i < users[loginIndex].qtdMsgTotal;)
							{
								puts("=== LENDO MENSAGENS ===");
								puts("Digite 'q' para sair.");
								printf("Username do remetente: %s.\n", mensagens[userMessagesIndex[i]].userOrigem);
								printf("Username do destinatario: %s\n", mensagens[userMessagesIndex[i]].userDestino);
								printf("Data de envio: %d/%d/%d.\n", mensagens[userMessagesIndex[i]].dataHora.data.dia, mensagens[userMessagesIndex[i]].dataHora.data.mes, mensagens[userMessagesIndex[i]].dataHora.data.ano);
								printf("Hora de envio: %d:%d:%d.\n", mensagens[userMessagesIndex[i]].dataHora.horario.hora, mensagens[userMessagesIndex[i]].dataHora.horario.minuto, mensagens[userMessagesIndex[i]].dataHora.horario.segundo);
								printf("Assunto da mensagem: %s\n", mensagens[userMessagesIndex[i]].assunto);
								printf("Corpo da mensagem: %s\n", mensagens[userMessagesIndex[i]].corpoMensagem);
								printf("Mensagem lida: %s\n", mensagens[userMessagesIndex[i]].lida == 1 ? "sim" : "nao");
								printf("[%d/%d]\n", i+1, users[loginIndex].qtdMsgTotal);

								if (mensagens[userMessagesIndex[i]].lida == 0)
								{
									mensagens[userMessagesIndex[i]].lida = 1;
									users[loginIndex].msgNaoLidas--;

									if(qtdMensagem < 2000 && mensagens[userMessagesIndex[i]].msgAuto == 0)
									{
										sentIndex = SearchUser(users,qtdUsers,mensagens[userMessagesIndex[i]].userOrigem);
									
										strcpy(mensagens[qtdMensagem].userOrigem,"Sistema");
										strcpy(mensagens[qtdMensagem].userDestino, users[sentIndex].username); // Colcoar username destinatario
										strcpy(mensagens[qtdMensagem].assunto,"A seguinte mensagem foi lida.");
										strcpy(mensagens[qtdMensagem].corpoMensagem,mensagens[userMessagesIndex[i]].corpoMensagem);					
										mensagens[qtdMensagem].lida = 0;										  // Nao foi lida

										time(&atual);			   // Obter tempo em segundos
									
										dados = localtime(&atual); // Converter valor para dados organizados "struct tm"
										
									
										mensagens[qtdMensagem].dataHora.data.dia = dados->tm_mday;
										mensagens[qtdMensagem].dataHora.data.mes = dados->tm_mon + 1;	  // Mes de 0 a 11 por isso +1
										mensagens[qtdMensagem].dataHora.data.ano = dados->tm_year + 1900; // Da os anos desde 1900 por isso adiciona se 1900								
										mensagens[qtdMensagem].dataHora.horario.hora = dados->tm_hour;
										mensagens[qtdMensagem].dataHora.horario.minuto = dados->tm_min;
										mensagens[qtdMensagem].dataHora.horario.segundo = dados->tm_sec;
										mensagens[userMessagesIndex[i]].msgAuto = 1;

										users[sentIndex].qtdMsgTotal++;
										users[sentIndex].qtdMsgAuto++;
										users[sentIndex].msgNaoLidas++;
										qtdMensagem++;
									}
								}

								printf("Introduza '>' para ir para proxima mensagem ou '<' para ir para mensagem anterior...\n");
								messagesKey = getchar();

								if (tolower(messagesKey) == 'q')
								{
									puts("Saindo...");
									break;
								}
								else if (messagesKey == '>') // Proxima mensagem
								{
									if(i+1 == users[loginIndex].qtdMsgTotal)
									{
										puts("Chegou ao fim das mensagens!");
										system("pause");
									}else if(i >= 0)
										i++;
								}
								else if (messagesKey == '<') // Mensagem anterior
								{
									if(i == 0)
									{
										puts("Chegou ao inicio das mensagens!");
										system("pause");
									}else if(i > 0)
										i--;
								}
								system("cls");
							}
						}
						system("pause");
						system("cls");
						break;
					case 2: // Apagar mensagens ja lidas
						if (users[loginIndex].msgNaoLidas == users[loginIndex].qtdMsgTotal)
						{
							puts("Nao existem mensagens lidas!");
						}
						else
						{
							system("cls");
							SearchMessages(mensagens, qtdMensagem, users[loginIndex].username, userMessagesIndex);
							for (i = 0; i < users[loginIndex].qtdMsgTotal; i++)
							{
								if (mensagens[userMessagesIndex[i]].lida == 1)
								{
									DelMensagensLidas(mensagens, qtdMensagem, userMessagesIndex[i]);
									users[loginIndex].qtdMsgTotal--;
									if(strcmp(mensagens[userMessagesIndex[i]].userOrigem,"Sistema") == 0)
									{
										users[loginIndex].qtdMsgAuto--;
									}else
									{
										users[loginIndex].qtdMsgReal--;
									}
									
									i--;
									msgApagadasCount++;
								}
							}
							printf("Foram apagadas %d mensagens!\n",msgApagadasCount);
						}
						system("pause");
						system("cls");
						msgApagadasCount = 0;
						break;
					case 3: // Enviar mensagens

						if (qtdMensagem == MAX_MSG - 1)
						{
							puts("Limite maximo de mensagens atigindo!");
						}
						else
						{
							system("cls");
							// Introduzir username de destino
							do
							{
								printf("Indique o username do destinatario: ");
								scanf("%s", usernameDestino);
								usernameDestino[50] = '\0';
								getchar();

								destinoIndex = SearchUser(users, qtdUsers, usernameDestino);
								if (destinoIndex == -1)
								{
									puts("Username nao existe!");
									system("pause");
									system("cls");
								}
							} while (destinoIndex == -1);

							puts("Indique o assunto da mensagem:");
							gets(mensagens[qtdMensagem].assunto);
							mensagens[qtdMensagem].assunto[50] = '\0';

							puts("Corpo da mensagem:");
							gets(mensagens[qtdMensagem].corpoMensagem);

							strcpy(mensagens[qtdMensagem].userOrigem, users[loginIndex].username);	  // Colocar username remetente
							strcpy(mensagens[qtdMensagem].userDestino, users[destinoIndex].username); // Colcoar username destinatario
							mensagens[qtdMensagem].lida = 0;										  // Nao foi lida

							time(&atual);			   // Obter tempo em segundos
							dados = localtime(&atual); // Converter valor para dados organizados "struct tm"

							mensagens[qtdMensagem].dataHora.data.dia = dados->tm_mday;
							mensagens[qtdMensagem].dataHora.data.mes = dados->tm_mon + 1;	  // Mes de 0 a 11 por isso +1
							mensagens[qtdMensagem].dataHora.data.ano = dados->tm_year + 1900; // Da os anos desde 1900 por isso adiciona se 1900
							mensagens[qtdMensagem].dataHora.horario.hora = dados->tm_hour;
							mensagens[qtdMensagem].dataHora.horario.minuto = dados->tm_min;
							mensagens[qtdMensagem].dataHora.horario.segundo = dados->tm_sec;
							mensagens[qtdMensagem].msgAuto = 0;

							users[destinoIndex].qtdMsgTotal++;
							users[destinoIndex].qtdMsgReal++;
							users[destinoIndex].msgNaoLidas++;
							qtdMensagem++;

							if(users[destinoIndex].qtdMsgTotal >= 25 && qtdMensagem < 2000)
							{
								strcpy(mensagens[qtdMensagem].userOrigem,"Sistema");
								strcpy(mensagens[qtdMensagem].userDestino, users[qtdUsers].username); // Colcoar username destinatario

								strcpy(mensagens[qtdMensagem].assunto,"25 mensagens");
								strcpy(mensagens[qtdMensagem].corpoMensagem,"Ja tem mais de 25 mensagens acumuladas. Considere em apagar mensagens.");
								mensagens[qtdMensagem].lida = 0;										  // Nao foi lida

								time(&atual);			   // Obter tempo em segundos
								dados = localtime(&atual); // Converter valor para dados organizados "struct tm"

								mensagens[qtdMensagem].dataHora.data.dia = dados->tm_mday;
								mensagens[qtdMensagem].dataHora.data.mes = dados->tm_mon + 1;	  // Mes de 0 a 11 por isso +1
								mensagens[qtdMensagem].dataHora.data.ano = dados->tm_year + 1900; // Da os anos desde 1900 por isso adiciona se 1900
								mensagens[qtdMensagem].dataHora.horario.hora = dados->tm_hour;
								mensagens[qtdMensagem].dataHora.horario.minuto = dados->tm_min;
								mensagens[qtdMensagem].dataHora.horario.segundo = dados->tm_sec;
								mensagens[qtdMensagem].msgAuto = 1;

								users[destinoIndex].qtdMsgTotal++;
								users[destinoIndex].qtdMsgAuto++;
								users[destinoIndex].msgNaoLidas++;
								qtdMensagem++;
							}
						}
						printf("Mensagem enviada para %s com sucesso!\n",users[destinoIndex].username);
						system("pause");
						system("cls");
						break;
					}
				} while (userTask != 0);
			}
		}

		bootTask = -1;
		adminTask = 0;
		userTask = 0;
		loggedIn = 0;
		loginIndex = -1;
		i = 0;
		msgApagadasCount = 0;
		system("pause");
		system("cls");
	} // Ciclo infinito

	return 0;
} // main
