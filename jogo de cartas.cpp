/*Nomes:Ana Luisa Bavati  e Frederico Bechara De Paola
RAs : 13022165 e 13099965
Opcionais funcionando : 1, 2 e 3
Valor do Projeto : 15 pontos
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>

struct no
{
	char info[3];
	struct no *prox;
};

enum DOS_COLORS {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
	LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
	LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE
};

void gotoxy(int coluna, int linha) // Usar funcao gotoxy onde x È a coluna e y a linha
{
	COORD point;
	point.X = coluna; point.Y = linha;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

//--------------------------------------------------- 

void textcolor(DOS_COLORS iColor) // usar  a funcao textcolor, cor do texto
{
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x00F0;
	SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= iColor);
}

// -------------------------------------------------------------------------

void backcolor(DOS_COLORS iColor) // funcao backcolor , cor de fundoc
{
	HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
	bufferInfo.wAttributes &= 0x000F;
	SetConsoleTextAttribute(hl, bufferInfo.wAttributes |= (iColor << 4));
}

void cores();

void desenhar_cartas_superior(char carta[], int posicao);

void desenhar_cartas_inferior(char carta[], int posicao);

void desenhar_baralho();

void pintar_carta_superior(int posicao);

void pintar_carta_inferior(int posicao);

void quadro_central();

void quadro(char jogador1[], char jogador2[]);

void limpar_quadro();

void baralho(struct no **fila);

int criar_baralho(struct no **fila, int i);

void imprimir_baralho(struct no *fila);

int comparar_cartas(char jogador1[], char jogador2[]);

void limpar_mesa(char jogador1[], char jogador2[]);

void imprimir(struct no *pi);

struct no *embaralhar(struct no *fila);

int imprimir_fila(struct no *pi);

int fila_jogador1(char valor[], struct no **inicio_jogado1, struct no **fim_jogado1);

int fila_jogador2(char valor[], struct no **inicio_jogado2, struct no **fim_jogado2);

int criar_fila(struct no *fila, struct no **inicio_jogado1, struct no **fim_jogado1, struct no **inicio_jogado2, struct no **fim_jogado2);

int batalhas(struct no **inicio_jogado1, struct no **inicio_jogado2, struct no **fim_jogado1, struct no **fim_jogado2, char jogador1[], char jogador2[]);

int adc_fila_aux1(char carta_jogador1[], char carta_jogador2[], struct no **inicio_jogador1_ganhou, struct no **fim_jogador1_ganhou);

int adc_fila_aux2(char carta_jogador1[], char carta_jogador2[], struct no **inicio_jogador2_ganhou, struct no **fim_jogador2_ganhou);

int adc_fila_jogador1(struct no **fila_jogador1_ganhou, struct no **inicio_jogador1, struct no **fim_jogador1);

int adc_fila_jogador2(struct no **fila_jogador2_ganhou, struct no **inicio_jogador2, struct no **fim_jogador2);

void quadro_comeco();

void imprimir(struct no *pi);
//Variaveis globais
int contar_operacoes = 0;
int vitorias_jogador1 = 0;
int vitorias_jogador2 = 0;
int empates = 0;

void main()
{
	int rodadas_para_media;
	int partidas_realizadas;
	int media;
	char jogador1[50];
	char jogador2[50];
	int jogar_dnv = 1;
	int res_batalha = 0;
	rodadas_para_media = 0;
	partidas_realizadas = 0;
	int batalhas0 = 0;

	clock_t tempo_inicio;
	clock_t	tempo_fim;
	float tempo_duracao;
	float tempo_total = 0;
	float tempo_menor = 9999999999999;
	float tempo_maior = 0;
	int    menor_rodada = 99999999999999;
	int   maior_rodada = 0;

	do{
		int posicao = 1;
		char carta = '1';
		int total_cartas1 = 0, total_cartas2 = 0;
		int jogadas = 0;
		contar_operacoes = 0;
		vitorias_jogador1 = 0;
		vitorias_jogador2 = 0;
		empates = 0;

		struct no *fila = NULL;

		int i = 1;

		int resposta_comparar_cartas;

		char carta_jogador1[3];

		char carta_jogador2[3];

		struct no *inicio_jogador1 = NULL;
		struct no *fim_jogador1 = NULL;

		struct no *inicio_jogador2 = NULL;
		struct no *fim_jogador2 = NULL;

		quadro_comeco();
		quadro_central();

		gotoxy(25, 26);

		printf("   A GUERRA DAS CARTAS   \n");

		gotoxy(15, 33);

		system("pause");

		limpar_quadro();

		if (partidas_realizadas == 0)
		{
			gotoxy(10, 26);
			printf("Digite o nome do primeiro jogador(a): \n");
			gotoxy(10, 27);
			fflush(stdin);
			gets(jogador1);
			gotoxy(10, 30);
			printf("Digite o nome do segundo jogador(a): \n");
			gotoxy(10, 31);
			fflush(stdin);
			gets(jogador2);
			limpar_quadro();
		}

		quadro(jogador1, jogador2);

		// Criar baralho
		baralho(&fila);
		// Embaralhar
		fila = embaralhar(fila);

		// Criar a fila de cada jogador
		criar_fila(fila, &inicio_jogador1, &fim_jogador1, &inicio_jogador2, &fim_jogador2);

		// Criar jogadas
		total_cartas1 = imprimir_fila(inicio_jogador1);
		total_cartas2 = imprimir_fila(inicio_jogador2);
		gotoxy(4, 56);
		printf("Jogador(a): %s Cartas: %d %c Jogador(a): %s Cartas: %d", jogador1, total_cartas1, 186, jogador2, total_cartas2);

		tempo_inicio = clock();
		do{
			total_cartas1 = imprimir_fila(inicio_jogador1);
			total_cartas2 = imprimir_fila(inicio_jogador2);
			gotoxy(4, 56);
			printf("Jogador(a): %s Cartas: %d %c Jogador(a): %s Cartas: %d", jogador1, total_cartas1, 186, jogador2, total_cartas2);
			res_batalha = batalhas(&inicio_jogador1, &inicio_jogador2, &fim_jogador1, &fim_jogador2, jogador1, jogador2);
			limpar_mesa(jogador1, jogador2);
			if (res_batalha == 0)
			{
				break;
			}

			total_cartas1 = imprimir_fila(inicio_jogador1);
			total_cartas2 = imprimir_fila(inicio_jogador2);
			gotoxy(4, 56);
			printf("Jogador(a): %s Cartas: %d %c Jogador(a): %s Cartas: %d", jogador1, total_cartas1, 186, jogador2, total_cartas2);

		} while (inicio_jogador1 != NULL || inicio_jogador2 != NULL);
		tempo_fim = clock();
		tempo_duracao = ((float)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC);

		gotoxy(8, 53);
		printf("O jogo teve a duracao de %.3f segundo(s).", tempo_duracao);

		if (tempo_maior < tempo_duracao){
			tempo_maior = tempo_duracao;
			maior_rodada = contar_operacoes;
		}
		if (tempo_menor>tempo_duracao){
			tempo_menor = tempo_duracao;
			menor_rodada = contar_operacoes;
		}
		tempo_total = tempo_total + tempo_duracao;

		limpar_quadro();

		gotoxy(25, 26);
		printf("  Deseja Jogar Novamente??  \n");
		gotoxy(20, 28);
		printf(" Digite 1 para SIM ou 2 para NAO  \n");
		gotoxy(25, 30);
		scanf("%d", &jogar_dnv);
		system("cls");
		partidas_realizadas++;
		rodadas_para_media = rodadas_para_media + contar_operacoes;
	} while (jogar_dnv != 2);

	media = rodadas_para_media / partidas_realizadas;
	tempo_total = tempo_total / partidas_realizadas;

	gotoxy(5, 10);
	printf("O numero de partidas realizadas foi %i", partidas_realizadas);
	gotoxy(5, 12);
	printf("e a media de rodadas por partida foi: %i rodadas", media);
	gotoxy(5, 16);
	printf("O tempo do jogo mais rapido foi %.2f segundos.", tempo_menor);
	gotoxy(5, 18);
	printf("E o numero de operacoes realizadas foram %d rodadas", menor_rodada);
	gotoxy(5, 22);
	printf("O tempo do jogo mais lento foi %.2f segundos. ", tempo_maior);
	gotoxy(5, 24);
	printf("E o numero de operacoes realizadas foram %d rodadas", maior_rodada);
	gotoxy(5, 28);
	printf("O tempo medio de execucao foi : %.2f segundos", tempo_total);

	gotoxy(14, 56);
	system("pause");
}
//---------------------------------------------------------------------------------------

int batalhas(struct no **inicio_jogado1, struct no **inicio_jogado2, struct no **fim_jogado1, struct no **fim_jogado2, char jogador1[], char jogador2[])
{
	struct no *inicio_jogador1_ganhou = NULL;
	struct no *fim_jogador1_ganhou = NULL;
	struct no *inicio_jogador2_ganhou = NULL;
	struct no *fim_jogador2_ganhou = NULL;
	char carta_jogador1[3];
	char carta_jogador2[3];
	char carta_jogador1_fechada[3];
	char carta_jogador2_fechada[3];
	int resposta;
	int return0;
	int posicao = 1;

	contar_operacoes++;

	// Pegando a primeira carta da fila do primiero jogador
	if ((*inicio_jogado1) == NULL)
	{
		limpar_quadro();
		gotoxy(10, 26);
		printf("O jogador 1 nao possui mais cartas!!");
		gotoxy(10, 28);
		printf("O Jogador 2 venceu o jogo!");
		gotoxy(10, 30);
		system("pause");
		return 0;
	}
	struct no *aux1 = *inicio_jogado1;
	strcpy(carta_jogador1, aux1->info);
	*inicio_jogado1 = (*inicio_jogado1)->prox;
	free(aux1);

	// Pegando a primeira carta da fila do segundo jogador
	if ((*inicio_jogado2) == NULL)
	{
		limpar_quadro();
		gotoxy(10, 26);
		printf("O jogador 2 nao possui mais cartas!!");
		gotoxy(10, 28);
		printf("O Jogador 1 venceu o jogo!");
		gotoxy(10, 30);
		system("pause");
		return 0;
	}
	struct no *aux2 = *inicio_jogado2;
	strcpy(carta_jogador2, aux2->info);
	*inicio_jogado2 = (*inicio_jogado2)->prox;
	free(aux2);

	adc_fila_aux1(carta_jogador1, carta_jogador2, &inicio_jogador1_ganhou, &fim_jogador1_ganhou);
	adc_fila_aux2(carta_jogador1, carta_jogador2, &inicio_jogador2_ganhou, &fim_jogador2_ganhou);

	desenhar_cartas_inferior(carta_jogador2, posicao);
	desenhar_cartas_superior(carta_jogador1, posicao);

	resposta = comparar_cartas(carta_jogador1, carta_jogador2);

	if (resposta == 1)
	{
		vitorias_jogador1++;
		adc_fila_jogador1(&inicio_jogador1_ganhou, inicio_jogado1, fim_jogado1);
		limpar_quadro();
		gotoxy(10, 28);
		printf("O jogador 1 Ganhou essa rodada!!");
		gotoxy(10, 30);
		system("pause");
	}

	if (resposta == 2)
	{
		adc_fila_jogador2(&inicio_jogador2_ganhou, inicio_jogado2, fim_jogado2);
		vitorias_jogador2++;
		limpar_quadro();
		gotoxy(10, 28);
		printf("O jogador 2 Ganhou essa rodada !!");
		gotoxy(10, 30);
		system("pause");
	}

	if (resposta == 3)
	{
		do{
			empates++;
			posicao++;
			if (posicao == 8 || posicao == 15)
			{
				limpar_mesa(jogador1, jogador2);
				posicao = 2;
			}
			// Pegando a primeira carta da fila do primiero jogador
			if ((*inicio_jogado1) == NULL)
			{
				limpar_quadro();
				gotoxy(10, 26);
				printf("O jogador 1 nao possui mais cartas!!");
				gotoxy(10, 28);
				printf("O Jogador 2 venceu o jogo!");
				gotoxy(10, 30);
				system("pause");
				return 0;
			}
			struct no *aux3 = *inicio_jogado1;
			strcpy(carta_jogador1_fechada, aux3->info);
			*inicio_jogado1 = (*inicio_jogado1)->prox;
			free(aux3);

			// Pegando a primeira carta da fila do segundo jogador
			if ((*inicio_jogado2) == NULL)
			{
				limpar_quadro();
				gotoxy(10, 26);
				printf("O jogador 2 nao possui mais cartas!!");
				gotoxy(10, 28);
				printf("O Jogador 1 venceu o jogo!");
				gotoxy(10, 30);
				system("pause");
				return 0;
			}
			struct no *aux4 = *inicio_jogado2;
			strcpy(carta_jogador2_fechada, aux4->info);
			*inicio_jogado2 = (*inicio_jogado2)->prox;
			free(aux4);

			adc_fila_aux1(carta_jogador1_fechada, carta_jogador2_fechada, &inicio_jogador1_ganhou, &fim_jogador1_ganhou);
			adc_fila_aux2(carta_jogador1_fechada, carta_jogador2_fechada, &inicio_jogador2_ganhou, &fim_jogador2_ganhou);

			pintar_carta_inferior(posicao);
			pintar_carta_superior(posicao);

			posicao++;
			// Pegando a primeira carta da fila do primiero jogador
			if ((*inicio_jogado1) == NULL)
			{
				limpar_quadro();
				gotoxy(10, 26);
				printf("O jogador 1 nao possui mais cartas!!");
				gotoxy(10, 28);
				printf("O Jogador 2 venceu o jogo!");
				gotoxy(10, 30);
				system("pause");
				return 0;
			}
			struct no *aux5 = *inicio_jogado1;
			strcpy(carta_jogador1, aux5->info);
			*inicio_jogado1 = (*inicio_jogado1)->prox;
			free(aux5);

			// Pegando a primeira carta da fila do segundo jogador
			if ((*inicio_jogado2) == NULL)
			{
				limpar_quadro();
				gotoxy(10, 26);
				printf("O jogador 2 nao possui mais cartas!!");
				gotoxy(10, 28);
				printf("O Jogador 1 venceu o jogo!");
				gotoxy(10, 30);
				system("pause");
				return 0;
			}
			struct no *aux6 = *inicio_jogado2;
			strcpy(carta_jogador2, aux6->info);
			*inicio_jogado2 = (*inicio_jogado2)->prox;
			free(aux6);

			adc_fila_aux1(carta_jogador1, carta_jogador2, &inicio_jogador1_ganhou, &fim_jogador1_ganhou);
			adc_fila_aux2(carta_jogador1, carta_jogador2, &inicio_jogador2_ganhou, &fim_jogador2_ganhou);

			desenhar_cartas_inferior(carta_jogador2, posicao);
			desenhar_cartas_superior(carta_jogador1, posicao);

			resposta = comparar_cartas(carta_jogador1, carta_jogador2);
			if (resposta == 1)
			{
				vitorias_jogador1++;
				adc_fila_jogador1(&inicio_jogador1_ganhou, inicio_jogado1, fim_jogado1);
				limpar_quadro();
				gotoxy(10, 28);
				printf("O jogador 1 Ganhou essa rodada!!");
				gotoxy(10, 30);
				system("pause");
			}

			if (resposta == 2)
			{
				adc_fila_jogador2(&inicio_jogador2_ganhou, inicio_jogado2, fim_jogado2);
				vitorias_jogador2++;
				limpar_quadro();
				gotoxy(10, 28);
				printf("O jogador 2 Ganhou essa rodada !!");
				gotoxy(10, 30);
				system("pause");
			}
		}
		while (resposta == 3);
	}
	return 1;
}

int adc_fila_jogador1(struct no **fila_jogador1_ganhou, struct no **inicio_jogador1, struct no **fim_jogador1)
{
	struct no *p;   /* variável auxiliar para percorrer a lista */
	struct no *q;   /* variável auxiliar para criar a nova lista */

	if (*inicio_jogador1 == NULL)
	{
		return 0;
	}

	p = *inicio_jogador1;
	do
	{
		q = p;
		p = p->prox;
	} while (p != NULL);

	q->prox = *fila_jogador1_ganhou;

	fila_jogador1_ganhou = NULL;
	return 1;

}
int adc_fila_jogador2(struct no **fila_jogador2_ganhou, struct no **inicio_jogador2, struct no **fim_jogador2)
{
	struct no *p;   /* variável auxiliar para percorrer a lista */
	struct no *q;   /* variável auxiliar para criar a nova lista */

	if (*inicio_jogador2 == NULL)
	{
		return 0;
	}
	p = *inicio_jogador2;
	do
	{
		q = p;
		p = p->prox;
	} while (p != NULL);

	q->prox = *fila_jogador2_ganhou;

	fila_jogador2_ganhou = NULL;
	return 1;
}

int adc_fila_aux1(char carta_jogador1[], char carta_jogador2[], struct no **inicio_jogador1_ganhou, struct no **fim_jogador1_ganhou)
{
	struct no *aux = (struct no *)malloc(sizeof(struct no));

	if (!aux) return 0;

	strcpy(aux->info, carta_jogador1);
	aux->prox = NULL;
	if ((*inicio_jogador1_ganhou) == NULL)
	{
		(*inicio_jogador1_ganhou) = (*fim_jogador1_ganhou) = aux;
	}
	else
	{
		(*fim_jogador1_ganhou)->prox = aux;
		(*fim_jogador1_ganhou) = aux;
	}

	aux = (struct no *)malloc(sizeof(struct no));

	strcpy(aux->info, carta_jogador2);
	aux->prox = NULL;
	if ((*inicio_jogador1_ganhou) == NULL)
	{
		(*inicio_jogador1_ganhou) = (*fim_jogador1_ganhou) = aux;
	}
	else
	{
		(*fim_jogador1_ganhou)->prox = aux;
		(*fim_jogador1_ganhou) = aux;
	}
	return 1;
}

int adc_fila_aux2(char carta_jogador1[], char carta_jogador2[], struct no **inicio_jogador2_ganhou, struct no **fim_jogador2_ganhou)
{
	struct no *aux = (struct no *)malloc(sizeof(struct no));

	if (!aux) return 0;

	strcpy(aux->info, carta_jogador2);
	aux->prox = NULL;
	if ((*inicio_jogador2_ganhou) == NULL)
	{
		(*inicio_jogador2_ganhou) = (*fim_jogador2_ganhou) = aux;
	}
	else
	{
		(*fim_jogador2_ganhou)->prox = aux;
		(*fim_jogador2_ganhou) = aux;
	}

	aux = (struct no *)malloc(sizeof(struct no));

	if (!aux) return 0;

	strcpy(aux->info, carta_jogador1);
	aux->prox = NULL;
	if ((*inicio_jogador2_ganhou) == NULL)
	{
		(*inicio_jogador2_ganhou) = (*fim_jogador2_ganhou) = aux;
	}
	else
	{
		(*fim_jogador2_ganhou)->prox = aux;
		(*fim_jogador2_ganhou) = aux;
	}
	return 1;
}



void imprimir(struct no *pi)
{
	if (pi == NULL)
	{
		printf("Fila vazia!\n");
	}
	else
	{
		while (pi != NULL)
		{
			printf("%s\n", pi->info);
			pi = pi->prox;
		}
	}
}


int criar_fila(struct no *fila, struct no **inicio_jogado1, struct no **fim_jogado1, struct no **inicio_jogado2, struct no **fim_jogado2)
{
	char valor[3];
	int i = 1;
	struct no *aux = fila;

	for (i = 1; i < 53; i++)
	{
		strcpy(valor, aux->info);
		if (i <= 26)
		{
			fila_jogador1(valor, inicio_jogado1, fim_jogado1);
		}

		if (i > 26)
		{
			fila_jogador2(valor, inicio_jogado2, fim_jogado2);
		}
		aux = aux->prox;
	}
	return 1;
}

int fila_jogador1(char valor[], struct no **inicio_jogado1, struct no **fim_jogado1)
{
	struct no *aux = NULL;
	aux = (struct no *)malloc(sizeof(struct no));
	
	strcpy(aux->info, valor);
	aux->prox = NULL;
	
	if ((*inicio_jogado1) == NULL)
	{
		(*inicio_jogado1) = (*fim_jogado1) = aux;
	}
	else
	{
		(*fim_jogado1)->prox = aux;
		(*fim_jogado1) = aux;
	}
	return 1;
}


int fila_jogador2(char valor[], struct no **inicio_jogado2, struct no **fim_jogado2)
{
	struct no *aux2 = NULL;
	aux2 = (struct no *)malloc(sizeof(struct no));
	
	strcpy(aux2->info, valor);
	aux2->prox = NULL;
	
	if ((*inicio_jogado2) == NULL)
	{
		(*inicio_jogado2) = (*fim_jogado2) = aux2;
	}
	else
	{
		(*fim_jogado2)->prox = aux2;
		(*fim_jogado2) = aux2;
	}
	return 1;
}


int imprimir_fila(struct no *pi)
{
	int cont = 0;

	if (pi == NULL)
	{
		return 0;
	}
	else
	{
		while (pi != NULL)
		{
			pi = pi->prox;
			cont++;
		}
		return (cont);
	}
}


struct no *embaralhar(struct no *fila)
{
	struct no *baralho;
	struct no *aux;
	struct no *aux2;
	struct no *posicao_fila;
	struct no *posicao_baralho;
	struct no *inicio_baralho;
	int cont = 1;
	int k = 1;
	int numero, i;
	char valor[3];
	int a = 1;
	int colocou_carta;

	srand(time(NULL));
	aux = NULL;
	struct no *x;
	baralho = NULL;

	for (i = 1; i < 53; i++)
	{
		aux = (struct no *)malloc(sizeof(struct no));
		if (!aux)
		{
			printf("nao criou baralho\n");
			system("pause");
			return 0;
		}
		strcpy(aux->info, "99");
		aux->prox = baralho;
		baralho = aux;
	}

	inicio_baralho = baralho;

	while (fila != NULL)
	{
		strcpy(valor, fila->info);
		colocou_carta = FALSE;
		while (!colocou_carta)
		{
			numero = rand() % 52 + 1;
			for (aux2 = baralho, a = 1; aux2 != NULL; aux2 = aux2->prox, a++)
			{
				if (a == numero)
				{
					break;
				}
			}

			if (strcmp(aux2->info, "99") == 0)
			{
				strcpy(aux2->info, valor);
				colocou_carta = TRUE;

			}
		}
		fila = fila->prox;
	}
	return (baralho);
}

void baralho(struct no **fila)
{
	for (int j = 1; j < 5; j++){
		for (int i = 1; i < 14; i++)
		{
			criar_baralho(fila, i);
		}
	}
}


int criar_baralho(struct no **fila, int n)
{
	struct no *aux, *aux2;

	aux = (struct no *)malloc(sizeof(struct no));

	int i = n;

	if (!aux)
	{
		printf("Erro!- Aux nao alocado \n\n");
		system("pause");
		return 0;
	}
	if (i == 1)
	{
		strcpy(aux->info, "2");
	}
	if (i == 2)
	{
		strcpy(aux->info, "3");
	}
	if (i == 3)
	{
		strcpy(aux->info, "4");
	}
	if (i == 4)
	{
		strcpy(aux->info, "5");
	}
	if (i == 5)
	{
		strcpy(aux->info, "6");
	}
	if (i == 6)
	{
		strcpy(aux->info, "7");
	}
	if (i == 7)
	{
		strcpy(aux->info, "8");
	}
	if (i == 8)
	{
		strcpy(aux->info, "9");

	}
	if (i == 9)
	{
		strcpy(aux->info, "10");
	}
	if (i == 10)
	{
		strcpy(aux->info, "J");
	}
	if (i == 11)
	{
		strcpy(aux->info, "Q");
	}
	if (i == 12)
	{
		strcpy(aux->info, "K");
	}
	if (i == 13)
	{
		strcpy(aux->info, "A");
	}
	aux->prox = *fila;
	*fila = aux;
	return 1;
}


int comparar_cartas(char jogador1[], char jogador2[])
{
	// retorna 1 - se a carta do jogador 1 for maior que a do jogador 2
	// retorna 2 - se a carta do jogador 2 for maior que a do jogador 1
	// retorna 3  - se as cartas forem iguais;
	
	int valor1 = 0;
	int valor2 = 0;

	if (strcmp(jogador1, "A") == 0)
	{
		valor1 = 14;
	}
	if (strcmp(jogador2, "A") == 0)
	{
		valor2 = 14;

	}
	if (strcmp(jogador1, "K") == 0)
	{
		valor1 = 13;
	}

	if (strcmp(jogador2, "K") == 0)
	{
		valor2 = 13;
	}
	if (strcmp(jogador1, "Q") == 0)
	{
		valor1 = 12;
	}
	if (strcmp(jogador2, "Q") == 0)
	{
		valor2 = 12;
	}
	if (strcmp(jogador1, "J") == 0)
	{
		valor1 = 11;
	}
	if (strcmp(jogador2, "J") == 0)
	{
		valor2 = 11;
	}
	if (strcmp(jogador1, "10") == 0)
	{
		valor1 = 10;

	}
	if (strcmp(jogador2, "10") == 0)
	{
		valor2 = 10;

	}
	if (strcmp(jogador1, "9") == 0)
	{
		valor1 = 9;
	}
	if (strcmp(jogador2, "9") == 0)
	{
		valor2 = 9;
	}
	if (strcmp(jogador1, "8") == 0)
	{
		valor1 = 8;
	}
	if (strcmp(jogador2, "8") == 0)
	{
		valor2 = 8;
	}
	if (strcmp(jogador1, "7") == 0)
	{
		valor1 = 7;
	}
	if (strcmp(jogador2, "7") == 0)
	{
		valor2 = 7;
	}
	if (strcmp(jogador1, "6") == 0)
	{
		valor1 = 6;
	}
	if (strcmp(jogador2, "6") == 0)
	{
		valor2 = 6;
	}
	if (strcmp(jogador1, "5") == 0)
	{
		valor1 = 5;
	}
	if (strcmp(jogador2, "5") == 0)
	{
		valor2 = 5;
	}
	if (strcmp(jogador1, "4") == 0)
	{
		valor1 = 4;
	}
	if (strcmp(jogador2, "4") == 0)
	{
		valor2 = 4;
	}
	if (strcmp(jogador1, "3") == 0)
	{
		valor1 = 3;
	}
	if (strcmp(jogador2, "3") == 0)
	{
		valor2 = 3;
	}
	if (strcmp(jogador1, "2") == 0)
	{
		valor1 = 2;
	}
	if (strcmp(jogador2, "2") == 0)
	{
		valor2 = 2;
	}
	if (strcmp(jogador1, "99") == 0)
	{
		valor1 = 99;
	}
	if (valor1 > valor2)
	{
		return 1;
	}
	if (valor1 < valor2)
	{
		return 2;
	}
	if (valor1 == valor2)
	{
		return 3;
	}
	else
	{
		printf("Erro - Comparar cartas");
		system("pause");
		return 0;
	}
	return 1;
}

void imprimir_baralho(struct no *fila){
	printf("\n");
	while (fila != NULL)
	{
		printf("%s", fila->info);
		printf("\n");
		fila = fila->prox;
	}
}


//*************************************************************************************************************************************************

void limpar_mesa(char jogador1[], char jogador2[])
{
	system("cls");
	quadro(jogador1, jogador2);
	quadro_central();
}

void limpar_quadro()
{
	int x1 = 6;
	int y1 = 23;
	for (int j = 0; j < 14; j++)
	{
		for (int i = 0; i < 67; i++)
		{
			gotoxy(x1, y1);
			printf(" ");
			x1++;
		}
		y1++;
		x1 = 6;
	}
	quadro_central();
	gotoxy(8, 36);
	printf("Rodadas: %d ", contar_operacoes);
	gotoxy(7, 37);
	printf("Vitorias do jogador1: %d | Vitorias do jogador2: %d | Empates: %d", vitorias_jogador1, vitorias_jogador2, empates);
}

void quadro_central()
{
	int x1 = 5;
	int y1 = 22;
	
	gotoxy(x1, y1);
	printf("%c", 201);
	y1++;
	
	for (int i = 0; i<15; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1++;
	}

	gotoxy(x1, y1);
	printf("%c", 200);
	x1++;

	for (int i = 0; i<68; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}
	
	gotoxy(x1, y1);
	printf("%c", 188);
	y1--;

	for (int i = 0; i<15; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1--;
	}

	gotoxy(x1, y1);
	printf("%c", 187);
	x1--;

	for (int i = 0; i<68; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1--;
	}
}

//----------------------------------------------------------------------------------------------------------------------------

void quadro_comeco()
{
	int x1 = 1;
	int y1 = 1;

	gotoxy(x1, y1);
	printf("%c", 201);
	y1++;

	for (int i = 0; i < 55; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1++;
	}

	gotoxy(x1, y1);
	printf("%c", 200);
	x1++;

	for (int i = 0; i < 76; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}

	gotoxy(x1, y1);
	printf("%c", 188);
	y1--;

	for (int i = 0; i < 55; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1--;
	}

	gotoxy(x1, y1);
	printf("%c", 187);
	x1--;

	for (int i = 0; i < 76; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1--;
	}


	x1 = 2;
	y1 = 5;

	gotoxy(x1, y1);

	for (int i = 0; i < 76; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}


	gotoxy(2, 3);
	printf("                        JOGO: A GUERRA DAS CARTAS                        ");
	x1 = 2;
	y1 = 54;
	gotoxy(x1, y1);

	for (int i = 0; i < 76; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}
}


void quadro(char jogador1[], char jogador2[])
{
	int x1 = 1;
	int y1 = 1;

	gotoxy(x1, y1);
	printf("%c", 201);
	y1++;

	for (int i = 0; i<55; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1++;
	}

	gotoxy(x1, y1);
	printf("%c", 200);
	x1++;

	for (int i = 0; i<76; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}

	gotoxy(x1, y1);
	printf("%c", 188);
	y1--;

	for (int i = 0; i<55; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1--;
	}

	gotoxy(x1, y1);
	printf("%c", 187);
	x1--;

	for (int i = 0; i<76; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1--;
	}


	x1 = 2;
	y1 = 5;
	gotoxy(x1, y1);

	for (int i = 0; i<76; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}

	gotoxy(2, 3);
	printf("                        JOGO: A GUERRA DAS CARTAS                        ");
	x1 = 2;
	y1 = 54;
	gotoxy(x1, y1);

	for (int i = 0; i<76; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}

	// Jogador 1
	gotoxy(3, 7);
	printf("Jogador(a) 1 : %s", jogador1);

	// Jogador 2
	gotoxy(3, 43);
	printf("Jogador(a) 2 : %s ", jogador2);
}

//----------------------------------------------------------------------------------------------------------------------------

void pintar_carta_superior(int posicao)
{

	int x = 0;
	int y = 0;
	int x1 = 5, y1 = 10;
	if (posicao == 1)
	{
		x1 = 5;
	}
	if (posicao == 2)
	{
		x1 = x1 + 10;
	}
	if (posicao == 3)
	{
		x1 = x1 + 20;
	}
	if (posicao == 4)
	{
		x1 = x1 + 30;
	}
	if (posicao == 5)
	{
		x1 = x1 + 40;
	}
	if (posicao == 6)
	{
		x1 = x1 + 50;
	}
	if (posicao == 7)
	{
		x1 = x1 + 60;
	}
	y = y1;
	x = x1;
	int cont = 1;
	do{
		for (int i = 1; i < 8; i++)
		{
			gotoxy(x1, y1);
			printf("%c", 176);
			x1++;
		}
		x1 = x;
		y1++;
		cont++;
	} while (cont != 8);
}

//----------------------------------------------------------------------------------------------------------------------------

void pintar_carta_inferior(int posicao)
{
	int x2 = 5, y2 = 45;

	if (posicao == 1)
	{
		x2 = 5;
	}
	if (posicao == 2)
	{
		x2 = x2 + 10;
	}
	if (posicao == 3)
	{
		x2 = x2 + 20;
	}
	if (posicao == 4)
	{
		x2 = x2 + 30;
	}
	if (posicao == 5)
	{
		x2 = x2 + 40;
	}
	if (posicao == 6)
	{
		x2 = x2 + 50;
	}
	if (posicao == 7)
	{
		x2 = x2 + 60;
	}
	int y = y2;
	int x = x2;
	int cont = 1;
	do{
		for (int i = 1; i < 8; i++)
		{
			gotoxy(x2, y2);
			printf("%c", 176);
			x2++;
		}
		x2 = x;
		y2++;
		cont++;
	} while (cont != 8);
}

//----------------------------------------------------------------------------------------------------------------------------

void desenhar_cartas_superior(char carta[], int posicao)
{
	int x1 = 5, y1 = 10;
	if (posicao == 1)
	{
		x1 = 5;
	}
	if (posicao == 2)
	{
		x1 = x1 + 10;
	}
	if (posicao == 3)
	{
		x1 = x1 + 20;
	}
	if (posicao == 4)
	{
		x1 = x1 + 30;
	}
	if (posicao == 5)
	{
		x1 = x1 + 40;
	}
	if (posicao == 6)
	{
		x1 = x1 + 50;
	}
	if (posicao == 7)
	{
		x1 = x1 + 60;
	}
	gotoxy(x1, y1);
	printf("%c", 201);
	y1++;
	for (int i = 0; i<5; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1++;
	}
	
	gotoxy(x1, y1);
	printf("%c", 200);
	x1++;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}

	gotoxy(x1, y1);
	printf("%c", 188);
	y1--;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1--;
	}

	gotoxy(x1, y1);
	printf("%c", 187);
	x1--;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1--;
	}

	y1 = y1 + 3;
	x1 = x1 + 3;
	gotoxy(x1, y1);
	printf("%s", carta);
}

//----------------------------------------------------------------------------------------------------------------------------

void desenhar_cartas_inferior(char carta[], int posicao)
{
	int x2 = 5, y2 = 45;

	if (posicao == 1)
	{
		x2 = 5;
	}
	if (posicao == 2)
	{
		x2 = x2 + 10;
	}
	if (posicao == 3)
	{
		x2 = x2 + 20;
	}
	if (posicao == 4)
	{
		x2 = x2 + 30;
	}
	if (posicao == 5)
	{
		x2 = x2 + 40;
	}
	if (posicao == 6)
	{
		x2 = x2 + 50;
	}
	if (posicao == 7)
	{
		x2 = x2 + 60;
	}

	gotoxy(x2, y2);
	printf("%c", 201);
	y2++;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x2, y2);
		printf("%c", 186);
		y2++;
	}

	gotoxy(x2, y2);
	printf("%c", 200);
	x2++;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x2, y2);
		printf("%c", 205);
		x2++;
	}

	gotoxy(x2, y2);
	printf("%c", 188);
	y2--;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x2, y2);
		printf("%c", 186);
		y2--;
	}

	gotoxy(x2, y2);
	printf("%c", 187);
	x2--;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x2, y2);
		printf("%c", 205);
		x2--;
	}

	y2 = y2 + 3;
	x2 = x2 + 3;
	gotoxy(x2, y2);
	printf("%s", carta);
}

//----------------------------------------------------------------------------------------------------------------------------

void desenhar_baralho()
{
	int x1 = 15;
	int y1 = 25;

	gotoxy(x1, y1);
	printf("%c", 201);
	y1++;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1++;
	}

	gotoxy(x1, y1);
	printf("%c", 200);
	x1++;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1++;
	}

	gotoxy(x1, y1);
	printf("%c", 188);
	y1--;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 186);
		y1--;
	}

	gotoxy(x1, y1);
	printf("%c", 187);
	x1--;

	for (int i = 0; i<5; i++)
	{
		gotoxy(x1, y1);
		printf("%c", 205);
		x1--;
	}
}

//----------------------------------------------------------------------------------------------------------------------------

void cores()
{

	char texto = 0;
	char fundo = 0;
	int op_menu;

	printf("Selecione qual das opcoes deseja alterar a cor:\n");
	printf("1 - Alterar a cor do texto\n2 - Alterar a cor de fundo\n");
	scanf("%d", &op_menu);

	if (op_menu == 1)
	{
		system("cls");
		printf("\n--------------- Alterar Cor do Texto --------------------\n\n");
		printf("0 = Preto            8 = Cinza Escuro\n");
		printf("1 = Azul             9 = Azul claro\n");
		printf("2 = Verde            A = Verde claro\n");
		printf("3 = Verde agua       B = Verde - agua claro\n");
		printf("4 = Vermelho         C = Vermelho claro\n");
		printf("5 = Roxo             D = Lilas\n");
		printf("6 = Marron           E = Amarelo claro\n");
		printf("7 = Cinza claro      F = Branco  \n");
		printf("\nSelecione a cor desejada:\n\nOpcao:");
		fflush(stdin);
		scanf("%c", &texto);

		if (texto == '0')
		{
			textcolor(BLACK);
		}
		if (texto == '1')
		{
			textcolor(BLUE);
		}
		if (texto == '2')
		{
			textcolor(GREEN);
		}
		if (texto == '3')
		{
			textcolor(CYAN);
		}
		if (texto == '4')
		{
			textcolor(RED);
		}
		if (texto == '5')
		{
			textcolor(MAGENTA);
		}
		if (texto == '6')
		{
			textcolor(BROWN);
		}
		if (texto == '7')
		{
			textcolor(LIGHT_GRAY);
		}
		if (texto == '8')
		{
			textcolor(DARK_GRAY);
		}
		if (texto == '9')
		{
			textcolor(LIGHT_BLUE);
		}
		if (texto == 'A')
		{
			textcolor(LIGHT_GREEN);
		}
		if (texto == 'B')
		{
			textcolor(LIGHT_CYAN);
		}
		if (texto == 'C')
		{
			textcolor(LIGHT_RED);
		}
		if (texto == 'D')
		{
			textcolor(LIGHT_MAGENTA);
		}
		if (texto == 'E')
		{
			textcolor(YELLOW);
		}
		if (texto == 'F')
		{
			textcolor(WHITE);
		}
	}

	if (op_menu == 2)
	{
		system("cls");
		printf("\n--------------- Alterar Cor de Fundo --------------------\n\n");
		printf("0 = Preto            8 = Cinza Escuro\n");
		printf("1 = Azul             9 = Azul claro\n");
		printf("2 = Verde            A = Verde claro\n");
		printf("3 = Verde agua       B = Verde - agua claro\n");
		printf("4 = Vermelho         C = Vermelho claro\n");
		printf("5 = Roxo             D = Lilas\n");
		printf("6 = Marron           E = Amarelo claro\n");
		printf("7 = Cinza claro      F = Branco  \n");
		printf("\nSelecione a cor desejada:\n\nOpcao:");
		fflush(stdin);
		scanf("%c", &texto);
		
		if (texto == '0')
		{
			backcolor(BLACK);
		}
		if (texto == '1')
		{
			backcolor(BLUE);
		}
		if (texto == '2')
		{
			backcolor(GREEN);
		}
		if (texto == '3')
		{
			backcolor(CYAN);
		}
		if (texto == '4')
		{
			backcolor(RED);
		}
		if (texto == '5')
		{
			backcolor(MAGENTA);
		}
		if (texto == '6')
		{
			backcolor(BROWN);
		}
		if (texto == '7')
		{
			backcolor(LIGHT_GRAY);
		}
		if (texto == '8')
		{
			backcolor(DARK_GRAY);
		}
		if (texto == '9')
		{
			backcolor(LIGHT_BLUE);
		}
		if (texto == 'A')
		{
			backcolor(LIGHT_GREEN);
		}
		if (texto == 'B')
		{
			backcolor(LIGHT_CYAN);
		}
		if (texto == 'C')
		{
			backcolor(LIGHT_RED);
		}
		if (texto == 'D')
		{
			backcolor(LIGHT_MAGENTA);
		}
		if (texto == 'E')
		{
			backcolor(YELLOW);
		}
		if (texto == 'F')
		{
			backcolor(WHITE);
		}
	}
	system("cls");
}
