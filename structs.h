#pragma once

struct tagHora{
	int hora;
	int minuto;
	int segundo;
};

struct tagData{
	int ano;
	int mes;
	int dia;
};

struct tagDataHora{
	struct tagData data;
	struct tagHora horario;
};

struct tagUser{
	char username[50+1];
	char nome[50+1];
	char password[50+1];
};

struct tagMensagem{
	char userOrigem[50+1];
	char userDestino[50+1];
	struct tagDataHora dataHora;
	char assunto[50+1];
	char corpoMensagem[50+1];
};

