#pragma once

#include "consts.h"

struct tagHora {
	int hora;
	int minuto;
	int segundo;
};

struct tagData {
	int ano;
	int mes;
	int dia;
};

struct tagDataHora {
	struct tagData data;
	struct tagHora horario;
};

struct tagMensagem {
	char userOrigem[50 + 1];	//Nome de user que enviou mensagem
	char userDestino[50 + 1];	//Nome de quem irá receber a mensagem
	struct tagDataHora dataHora;	//Contem ano mes dia hora minuto
	char assunto[70];	//Assunto da mensagem
	char corpoMensagem[300];	//Corpo da mensagem
	int lida;	//Se mensagem está lida ou nao
};

struct tagUser {
	char username[50 + 1];	//Nome do user para outros users
	char nome[50 + 1];	//Nome real do utilizador
	char password[50 + 1];	//Password da conta
	int msgNaoLidas;	//Quantidade de mensagens nao lidas
};
