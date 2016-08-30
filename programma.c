/*****************************/
/* Inclusione delle librerie */
/*****************************/

/*inclusione della libreria standard "stdio.h"*/
#include <stdio.h>

/*inclusione della libreria non standard "libreria_complessi.h"*/
#include "libreria_complessi.h"

/******************************/
/* Definizione delle funzioni */
/******************************/
void riesegui_operazione(void);

void scelta_operazione(void);

/****************/
/* Funzione main*/
/****************/
int main(void)
{
	riesegui_operazione();
	return(0);
}

/***********************/
/* Funzione principale */
/***********************/
void riesegui_operazione(void)
{
	char altre_op;
	int esito;
	char carattere;
	
		scelta_operazione();
		
		do
		{
			printf("Eseguire altre operazioni? [y/n]\n");
			esito = scanf(" %c", 
				      &altre_op);
			if ((esito != 1) || 
			    (altre_op != 'y' && 
      			     altre_op != 'Y' && 
			     altre_op != 'n' && 
			     altre_op != 'N' ))
			{
				printf("Digitare 'y' oppure 'n'\n");
				do
					carattere = getchar();
				while (carattere != '\n');
			}
		}
		while ((esito != 1) || 
		       (altre_op != 'y' && 
      		        altre_op != 'Y' && 
		        altre_op != 'n' && 
		        altre_op != 'N' ));
		do
		carattere = getchar();
	while (carattere != '\n');

	if (altre_op == 'y' || 
	    altre_op == 'Y')
		riesegui_operazione();
}

/****************************************************/
/* Funzione per scegliere quale operazione eseguire */
/****************************************************/
void scelta_operazione(void)
{
	int risposta;	   /*input: quale operazione eseguire*/
	int esito_lettura; /*var. di lavoro: esito delle scanf*/
	char carattere;    /*var. di lavoro: caratteri nel buffer della tastiera*/
			   /*var. di lavoro: array di stringhe*/
	char scelta[5][36] = {"1)Cambio di forma",
			      "2)Somma tra numeri complessi",
			      "3)Differenza tra numeri complessi",
			      "4)Prodotto tra numeri complessi",
			      "5)Rapporto tra numeri complessi"};

	/*scelta di operazione da effettuare*/
	do
	{
		/*scelta di una operazione*/	
		printf("Quale operazione eseguire? [1-2-3-4-5]\n\n");
		printf("\t%s\n",
		       scelta[0]);
		printf("\t%s\n",
		       scelta[1]);
		printf("\t%s\n",
		       scelta[2]);
		printf("\t%s\n",
		       scelta[3]);
		printf("\t%s\n",
		       scelta[4]);

		esito_lettura = scanf("%d", 
				      &risposta);
		
		/*validazione stretta dell'input*/
		if ((esito_lettura != 1) ||
		    ((risposta != 1) &&
		     (risposta != 2) &&
		     (risposta != 3) &&
		     (risposta != 4) &&
		     (risposta != 5))) 
		{
			printf("Assicurarsi di avere inserito ");
			printf("un valore da 1 a 5 e riprovare\n");
			
			do
				carattere = getchar();
			while (carattere != '\n');
		}
	}
	while ((esito_lettura != 1) ||
	       ((risposta != 1) &&
	        (risposta != 2) &&
	        (risposta != 3) &&
	        (risposta != 4) &&
	        (risposta != 5)));

	/*si esegue una specifica funzione della libreria*/
	/*"libreria_complessi" a seconda della risposta*/
	switch (risposta)
	{
		case 1:	/*invoca la funz. cambio di forma*/

			printf("Esecuzione operazione %s\n",
			       scelta[risposta-1]);
			cambia_forma();	
			break;

		case 2:	/*invoca la funz. per sommare*/

			printf("Esecuzione operazione %s\n",
			       scelta[risposta-1]);
			somma_n_compl();
			break;

		case 3:/*invoca la funz. per sottrarre*/

			printf("Esecuzione operazione %s\n",
			       scelta[risposta-1]);
			differenza_n_compl();
			break;

		case 4:/*invoca la funz. per moltiplicare*/

			printf("Esecuzione operazione %s\n",
			       scelta[risposta-1]);
			prodotto_n_compl();
			break;

		case 5:/*invoca la funz. per dividere*/

			printf("Esecuzione operazione %s\n",
			       scelta[risposta-1]);
			rapporto_n_compl();
			break;
	}
}
