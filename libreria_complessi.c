/**********************************************************/
/* Inclusione delle librerie standard "stdio.h" e "math.h"*/
/**********************************************************/
#include <stdio.h>
#include <math.h>

/*****************************************/
/* Definizione delle costanti simboliche */
/*****************************************/
#define PI_GRECO 3.141592	  /* pigreco */
#define RAD_GRAD (180 / PI_GRECO) /*fatt. conversione rad/gradi*/
#define GRAD_RAD (PI_GRECO / 180) /*fatt. conversione gradi/rad*/

/************************/
/* Definizione dei tipi */
/************************/

/* Forma del numero complesso*/ 
typedef enum {forma_algebrica,			
	      forma_trigonometrica} forma_t;

/* Tipo forma algebrica */
typedef struct 
{
	double parte_reale,
	       parte_immag;
} f_algebrica_t;

/* Tipo forma trigonometrica */
typedef struct 
{ 
	double modulo,
	       argomento;
} f_trigonometrica_t;

/* Tipo numero complesso */
typedef struct 
{ 
	forma_t forma;
	struct 
	{
		f_algebrica_t f_algebrica;
		f_trigonometrica_t f_trigonometrica;
	} dati_forma;
} n_compl_t;

/********************************/
/* Dichiarazione delle funzioni */
/********************************/
/*-Funzioni da esportare--------*/

void cambia_forma(void);	 	  /* Cambia la forma in cui è visualizzato un numero complesso*/
	
void somma_n_compl(void);		  /* Calcola la somma di due numeri complessi */

void differenza_n_compl(void);		  /* Calcola la differenza di due numeri complessi */

void prodotto_n_compl(void);		  /* Calcola il prodotto di due numeri complessi */

void rapporto_n_compl(void);		  /* Calcola rapporto di due numeri complessi */

/*-Funzioni interne-------------*/

void leggi_complesso(n_compl_t *);	  /* Aquisisce il numero complesso*/

int prendi_forma(void);			  /*------------------------------*/

n_compl_t prendi_valore_alg(void);	  /*------------------------------*/

n_compl_t prendi_valore_trig(void);	  /*------------------------------*/

void stampa_complesso(n_compl_t );	  /* Stampa il risultato delle operazioni*/

void stampa_alg(n_compl_t );		  /*-------------------------------------*/

void stampa_trig(n_compl_t );		  /*-------------------------------------*/

void converti_alg_trig(n_compl_t *);	  /* Converte da f.alg a f.trig*/

void converti_trig_alg(n_compl_t *);	  /* Converte da f.trig a f.alg*/

n_compl_t somma_f_alg(n_compl_t n1,	  /* Somma in f.alg*/
		      n_compl_t n2 );

n_compl_t differenza_f_alg(n_compl_t n1,  /* Differenza in f.alg*/		
		           n_compl_t n2);

n_compl_t prodotto_f_alg(n_compl_t n1,	  /* Prodotto in f.alg*/
		         n_compl_t n2 );

n_compl_t prodotto_f_trig(n_compl_t n1,	  /* Prodotto in f.trig*/
			  n_compl_t n2);

n_compl_t rapporto_f_alg(n_compl_t n1,	  /* Rapporto in f.alg*/
			 n_compl_t n2);

n_compl_t rapporto_f_trig(n_compl_t n1,	  /* Prodotto in f.trig*/
			  n_compl_t n2);

/******************************/
/* Definizione delle funzioni */
/******************************/
/*-Funzioni da esportare------*/

/*********************************************************/
/* Funzione per cambiare la forma di un numero complesso */
/*********************************************************/
void cambia_forma(void)
{
	n_compl_t numero;	/*var. di lavoro: numero complesso da convertire*/

	/* aquisizione del numero */
	leggi_complesso(&numero); 	

	/*controllo forma del numero*/
	switch (numero.forma)
	{
		case 0:	/*se f.algebrica*/

			converti_alg_trig(&numero);
			break;

		case 1: /*se f.trigonometrica*/

			converti_trig_alg(&numero);
			break;
	}
	
	/*stampa il numero cambiato di forma*/
	stampa_complesso(numero);
}
/*********************************************/
/* Funzione per sommare due numeri complessi */
/*********************************************/
void somma_n_compl(void)
{
	n_compl_t numero1,	/*input: primo numero*/
		  numero2;	/*input: secondo numero*/
	n_compl_t risultato;	/*output: il risultato della somma*/

	leggi_complesso(&numero1);	/*aquisizione del primo numero*/

	leggi_complesso(&numero2);	/*aquisizione del secondo numero*/

	/*controllo forma primo numero*/
	switch (numero1.forma)	
	{	case 0:		/*se il num.1 è in f.algebrica*/
		
 			/*controllo forma secondo numero*/
			switch (numero2.forma)
			{
				case 0:	/*se il num.2 è in f.algebrica*/

					/*invoca la funzione per sommare*/
					risultato = somma_f_alg(numero1, 
								numero2);
					break;

				case 1:	/*se il num.2 è in f.trigonometrica*/

					/*cambio di forma trig-alg*/
					converti_trig_alg(&numero2);

					/*invoca la funzione per sommare*/	
					risultato = somma_f_alg(numero1, 
								numero2);
					break;
			}

			/*assegna al ris. la forma alg.*/
			risultato.forma = forma_algebrica; 

			break;

		case 1:		/*se il num. 1 è in f.trigonometrica*/

			/*assegna momentaneamente al ris. la forma alg.*/
			risultato.forma = forma_algebrica;

			/*converto in forma algebrica il primo numero*/
			converti_trig_alg(&numero1);

			/*controllo forma secondo numero*/
			switch (numero2.forma)
			{
				case 0:	/*se il num.2 è in f.algebrica*/

					/*invoca la funzione per sommare*/
					risultato = somma_f_alg(numero1,
								numero2);
					break;

				case 1:	/*se il num.2 è in f.trigonometrica*/

					/*cambio di forma trig-alg*/
					converti_trig_alg(&numero2);
					
					/*invoca la funzione per sommare*/
					risultato = somma_f_alg(numero1,
								numero2);
					break;
			}
			
			/*converto il risultato in f.trigonometrica*/
			converti_alg_trig(&risultato);
			break;
	}

	/*stampa il risultato della somma*/
	stampa_complesso(risultato);
}

/***********************************************/
/* Funzione per sottrarre due numeri complessi */
/***********************************************/
void differenza_n_compl(void)
{
	n_compl_t numero1,	/*input: primo numero*/
		  numero2;	/*input: secondo numero*/
	n_compl_t risultato;	/*output: il risultato della differenza*/

	leggi_complesso(&numero1);	/*aquisizione del primo numero*/

	leggi_complesso(&numero2);	/*aquisizione del secondo numero*/

	/*controllo forma primo numero*/
	switch (numero1.forma)	
	{	case 0:		/*se il num.1 è in f.algebrica*/

			/*controllo forma secondo numero*/
			switch (numero2.forma)
			{
				case 0:	/*se il num.2 è in f.algebrica*/
					/*invoca funz. per sottrarre*/
					risultato = differenza_f_alg(numero1,
								     numero2);
					break;

				case 1:	/*se il num.2 è in f.trigonometrica*/

					/*cambio di forma trig-alg*/
					converti_trig_alg(&numero2);	

					/*invoco funz. per sottrarre*/
					risultato = differenza_f_alg(numero1,
								     numero2);
					break;
			}

			/*assegna al ris. la forma alg.*/
			risultato.forma = forma_algebrica; 

			break;

		case 1:		/*se il num. 1 è in f.trigonometrica*/

			/*assegna momentaneamente al ris. la forma alg.*/
			risultato.forma = forma_algebrica;	

			/*converto in forma algebrica il primo numero*/
			converti_trig_alg(&numero1);

			/*controllo forma secondo numero*/
			switch (numero2.forma)
			{
				case 0:	/*se il num.2 è in f.algebrica*/
	
					/*invoca la funz. per sottrarre*/
					risultato = differenza_f_alg(numero1,
								     numero2);
					break;

				case 1:	/*se il num.2 è in f.trigonometrica*/

					converti_trig_alg(&numero2);	/*cambio di forma trig-alg*/

					/*invoco la funz. per sottrarre*/
					risultato = differenza_f_alg(numero1,
								     numero2);		
					break;
			}
			
			/*converto il risultato in f.trigonometrica*/
			converti_alg_trig(&risultato);
			break;
		}

	/*stampa il risultato della differenza*/
	stampa_complesso(risultato);
}

/**************************************************/
/* Funzione per moltiplicare due numeri complessi */
/**************************************************/
void prodotto_n_compl(void)
{
	n_compl_t numero1,	/*input: primo numero*/
		  numero2;	/*input: secondo numero*/
	n_compl_t risultato;	/*output: il risultato del prodotto*/

	leggi_complesso(&numero1);	/*aquisizione del primo numero*/

	leggi_complesso(&numero2);	/*aquisizione del secondo numero*/

	/*controllo forma primo numero*/
	switch (numero1.forma)	
	{	case 0:		/*se il num.1 è in f.algebrica*/

 			/*controllo forma secondo numero*/
			switch (numero2.forma)
			{
				case 0:	/*se il num.2 è in f.algebrica*/

					/*invoco la funzione per moltiplicare*/
					risultato = prodotto_f_alg(numero1,
								   numero2);
					break;

				case 1:	/*se il num.2 è in f.trigonometrica*/

					/*cambio di forma trig-alg*/
					converti_trig_alg(&numero2);
	
					/*invoco la funzione per moltiplicare*/
					risultato = prodotto_f_alg(numero1,
								   numero2);
					break;
			}

			/*assegna al ris. la forma alg.*/
			risultato.forma = forma_algebrica;

			break;

		case 1:		/*se il num. 1 è in f.trigonometrica*/
		
			/*controllo forma secondo numero*/
			switch (numero2.forma)
			{
				case 0:	/*se il num.2 è in f.algebrica*/

					/*cambio di forma alg-trig*/
					converti_alg_trig(&numero2); 

					/*invoco la funz. per moltiplicare*/
					risultato = prodotto_f_trig(numero1,
								    numero2);
					break;

				case 1:	/*se il num.2 è in f.trigonometrica*/

					/*invoco la funz. per moltiplicare*/
					risultato = prodotto_f_trig(numero1,
								    numero2);
					break;
			}

			/*assegna al ris. la forma trig.*/
			risultato.forma = forma_trigonometrica;	

			break;
	}

	/*stampa il risultato del prodotto*/
	stampa_complesso(risultato);
}
/**********************************************/
/* Funzione per dividere due numeri complessi */
/**********************************************/
void rapporto_n_compl(void)
{
	n_compl_t numero1,	/*input: primo numero*/
		  numero2;	/*input: secondo numero*/
	n_compl_t risultato;	/*output: il risultato del rapporto*/

	leggi_complesso(&numero1);	/*aquisizione del primo numero*/

	leggi_complesso(&numero2);	/*aquisizione del secondo numero*/

	/*controllo forma primo numero*/
	switch (numero1.forma)	
	{	case 0:		/*se il num.1 è in f.algebrica*/
				
 			/*controllo forma secondo numero*/
			switch (numero2.forma)
			{
				case 0:	/*se il num.2 è in f.algebrica*/

					/*invoco la funz. per dividere*/
					risultato = rapporto_f_alg(numero1,
							  	   numero2);
					break;

				case 1:	/*se il num.2 è in f.trigonometrica*/

					/*cambio di forma trig-alg*/
					converti_trig_alg(&numero2);	
					
					/*invoco la funz.per dividere*/
					risultato = rapporto_f_alg(numero1,
								   numero2);
					break;
			}

			/*assegna al ris. la forma alg.*/
			risultato.forma = forma_algebrica; 

			break;

		case 1:		/*se il num. 1 è in f.trigonometrica*/

			/*controllo forma secondo numero*/
			switch (numero2.forma)
			{
				case 0:	/*se il num.2 è in f.algebrica*/

					/*cambio di forma alg-trig*/
					converti_alg_trig(&numero2); 

					/*invoco la funz. per dividere*/
					risultato = rapporto_f_trig(numero1,numero2);
					break;

				case 1:	/*se il num.2 è in f.trigonometrica*/

					/*invoco la funz. per dividere*/
					risultato = rapporto_f_trig(numero1,
								    numero2);
					break;
			}

			/*assegna al ris. la forma trig.*/
			risultato.forma = forma_trigonometrica;	

			break;
	}

	/*stampa il risultato della somma*/
	stampa_complesso(risultato);
}

/*-Funzioni interne-----------*/

/*--------------------------------------------*/
/* Funzione per acquisire un numero complesso */
/*--------------------------------------------*/
void leggi_complesso(n_compl_t *num_comp)
{
	int scelta_forma; /*var. di lavoro: scelta della forma*/
	
	/*aquisizione della forma del numero */
	scelta_forma = prendi_forma();

	/*aquisizione dei valori del numero*/
	switch (scelta_forma)
	{
		case 1:	/*se f.algebrica*/

			*num_comp = prendi_valore_alg();
			break;
		
		case 2:	/*se f.trigonometrica*/

			*num_comp = prendi_valore_trig();
			break;
	}
}

/*---------------------------------------------------*/
/* Funzione per scegliere la forma del nunero compl. */
/*---------------------------------------------------*/
int prendi_forma(void)
{
	int risposta,	    /*var. di lavoro: seleziona la forma del numero*/
	    esito_lettura;  /*var. di lavoro: esito della scanf*/
	char carattere;	    /*var. di lavoro: carattere nel buffer della tastiera*/

	/*Validazione stretta della scelta della forma*/
	do
	{	
		printf("Selezionare la forma del ");
		printf("numero complesso (1 o 2):\n\n");
		printf("\t1. Forma Algebrica\n\n");
		printf("\t2. Forma Trigonometrica\n");

		esito_lettura = scanf("%d",
		     		      &risposta);

		if ((esito_lettura != 1) ||
		    ((risposta != 1)&&
		     (risposta != 2)))
		    
		{
			printf("\nErrore! Input non accattabile! ");
			printf("[assicurarsi di avere inserito ");
			printf("1 oppure 2]\n");

			do
				carattere = getchar();

			while (carattere != '\n');
		}
	}
	while ((esito_lettura != 1) ||
	       ((risposta != 1) &&
	        (risposta != 2)));

	return(risposta);
}

/*------------------------------------------------------*/
/* Funzione per aquisire il valore in f.alg. del numero */
/*------------------------------------------------------*/
n_compl_t prendi_valore_alg(void)
{
	n_compl_t num;	   /*output: numero aquisito*/
	int esito_lettura; /*var. di lavoro: esito delle scanf*/
	char carattere;	   /*var. di lavoro: carattere nel buffer*/

	/*assegnazione della forma alg. al tipo n_compl_t*/
	num.forma = forma_algebrica; 

	/*Validazione stretta dell'input*/

	/*parte reale*/
	do
	{
		printf("Inserire il valore della parte reale: ");
		esito_lettura = scanf("%lf",
				      &num.dati_forma.f_algebrica.parte_reale);
		if (esito_lettura != 1)
		{
			printf("\nAttenzione! Assicurarsi di aver inserito ");
			printf("un numero reale e non un carattere\n");
			do
				carattere = getchar();
			while (carattere != '\n');
		}
	}
	while (esito_lettura != 1);

	/*parte immaginaria*/
	do
	{
		printf("Inserire il valore della parte immaginaria: ");
		esito_lettura = scanf("%lf",
				      &num.dati_forma.f_algebrica.parte_immag);
		if (esito_lettura != 1)
		{
			printf("\nAttenzione! Assicurarsi di aver inserito ");
			printf("un numero reale e non un carattere\n");
			do
	 			carattere = getchar();
			while (carattere != '\n');
		}
	}
	while (esito_lettura != 1);
	
	return(num);
}

/*-------------------------------------------------------*/
/* Funzione per aquisire il valore in f.trig. del numero */
/*-------------------------------------------------------*/
n_compl_t prendi_valore_trig(void)
{
	n_compl_t num;	   /*output: numero aquisito*/
	int esito_lettura; /*var. di lavoro: esito delle scanf*/
	char carattere;	   /*var. di lavoro: carattere nel buffer*/

	/*Assegnazione della forma trig. al tipo n_compl_t*/
	num.forma = forma_trigonometrica;
		
	/*Validazione stretta dell'input*/

	/*modulo*/
	do
	{
		printf("Inserire il valore del modulo: ");
		esito_lettura = scanf("%lf",
				      &num.dati_forma.f_trigonometrica.modulo);
		if (esito_lettura != 1)
		{
			printf("\nAttenzione! Assicurarsi di aver inserito ");
			printf("un numero reale e non un carattere\n");
			do
				carattere = getchar();
			while (carattere != '\n');
		}
	}
	while (esito_lettura != 1);
		
	/*argomento*/
	do
	{
		printf("Inserire il valore dell'argomento (in gradi): ");
		esito_lettura = scanf("%lf",
			   	      &num.dati_forma.f_trigonometrica.argomento);
		if (esito_lettura != 1)
		{
			printf("\nAttenzione! Assicurarsi di aver inserito ");
			printf("un numero reale e non un carattere\n");
			do
				carattere = getchar();
			while (carattere != '\n');
		}
	}
	while (esito_lettura != 1);
	
	/*conversione dell'argomento da gradi a radianti*/
	num.dati_forma.f_trigonometrica.argomento = 
			(num.dati_forma.f_trigonometrica.argomento * 
			 GRAD_RAD);

	return(num);
}

/*------------------------------------------------------*/
/* Funzione per stampare il numero complesso risultante */
/*------------------------------------------------------*/
void stampa_complesso(n_compl_t n)
{	
	/*Controlla la forma del numero*/
	switch (n.forma)
	{	
		case 0:	/*se n è in f.algrbrica*/

			stampa_alg(n);		
			break;
	
		case 1:	/*se n è in f.trigonometrica*/
	
			stampa_trig(n);
			break;
	}
}

/*---------------------------------*/
/* Stampa il numero in f.algebrica */
/*---------------------------------*/
void stampa_alg(n_compl_t num)
{
	char sgn;   /*var. di lavoro: segno della p.immag*/

	/*se solo la parte reale è = 0*/
	if (num.dati_forma.f_algebrica.parte_reale == 0)
	{

		/*stampa il nun in forma ib*/
		printf("Il numero complesso risultante ");
		printf("in forma algebrica è: ");
		printf("%.2fi\n",
	     	       num.dati_forma.f_algebrica.parte_immag);
	}

	/*se solo la parte immaginaria è = 0*/
	else if (num.dati_forma.f_algebrica.parte_immag == 0)
	{

		/*stampa il num in forma a*/
		printf("Il numero complesso risultante ");
		printf("in forma algebrica è: ");
		printf("%.2f\n",
	       	       num.dati_forma.f_algebrica.parte_reale);
	}

	/*se sia la p.reale che la p.immag sono != 0*/
	else
	{
		
		/*mette un segno a seconda del segno della p.immag*/
		if (num.dati_forma.f_algebrica.parte_immag >= 0)
			sgn = '+';
		else
			sgn = '-';

		/*stampa il num in forma a+ib*/
		printf("Il numero complesso risultante ");
		printf("in forma algebrica è: ");
		printf("%.2f %c %.2fi\n",
		       num.dati_forma.f_algebrica.parte_reale,
		       sgn,
	  	       fabs(num.dati_forma.f_algebrica.parte_immag));
	}
}

/*--------------------------------------*/
/* Stampa il numero in f.trigonometrica */
/*--------------------------------------*/
void stampa_trig(n_compl_t num)
{
	printf("Il numero risultante ");
	printf("in forma trigonometrica è: ");
	printf("%.2f(cos%.2f° + i * sin%.2f°)\n",
	       num.dati_forma.f_trigonometrica.modulo,
	       (num.dati_forma.f_trigonometrica.argomento *
		RAD_GRAD),
	       (num.dati_forma.f_trigonometrica.argomento *
		RAD_GRAD));
}
	
/*----------------------------------------------------------*/
/* Funzione per convertire da f. algebrica a trigonometrica */
/*----------------------------------------------------------*/
void converti_alg_trig(n_compl_t *num)
{	
	/* assegnazione della forma trigonometrica */

	num->forma = forma_trigonometrica;	

	/* calcolo del modulo */

	num->dati_forma.f_trigonometrica.modulo = 
			sqrt (pow (num->dati_forma.f_algebrica.parte_reale, 2) +
			      pow (num->dati_forma.f_algebrica.parte_immag, 2));
	
	/* calcolo dell'argomento */

	if (num->dati_forma.f_algebrica.parte_reale == 0)	/*se a = 0 */
	{	
		if (num->dati_forma.f_algebrica.parte_immag == 0)	/* e b = 0 */

			num->dati_forma.f_trigonometrica.argomento = 0;

		else if (num->dati_forma.f_algebrica.parte_immag > 0)	/* e b < 0 */

			num->dati_forma.f_trigonometrica.argomento = 1.5708;

		else							/* e b > 0 */

			num->dati_forma.f_trigonometrica.argomento = -1.5708; 

	}

	else if (num->dati_forma.f_algebrica.parte_reale > 0)		/* se a > 0 e b qualsiasi*/
	{
		num->dati_forma.f_trigonometrica.argomento = 
						atan2 (num->dati_forma.f_algebrica.parte_immag,
						       num->dati_forma.f_algebrica.parte_reale); 
	}

	else	/* se a < 0 */	
	{
		if (num->dati_forma.f_algebrica.parte_immag >= 0)	/* e b >= 0 */

			num->dati_forma.f_trigonometrica.argomento = 
						atan2 (num->dati_forma.f_algebrica.parte_immag, 
						       num->dati_forma.f_algebrica.parte_reale) + PI_GRECO;

		else							/*e b < 0*/
			num->dati_forma.f_trigonometrica.argomento = 
						atan2 (num->dati_forma.f_algebrica.parte_immag, 
						       num->dati_forma.f_algebrica.parte_reale) - PI_GRECO;
	}
}

/*---------------------------------------------------------*/
/* Funzione per convertire da f.trigonometrica a algebrica */
/*---------------------------------------------------------*/
void converti_trig_alg(n_compl_t *num)
{
	/* assegnazione della forma algebrica */

	num->forma = forma_algebrica;

	/*calcolo della parte reale*/
	
	num->dati_forma.f_algebrica.parte_reale = 
		        (cos(num->dati_forma.f_trigonometrica.argomento) * 
		    	    (num->dati_forma.f_trigonometrica.modulo));
		
	/*calcolo della parte immaginaria*/
	
	num->dati_forma.f_algebrica.parte_immag = 
			(sin(num->dati_forma.f_trigonometrica.argomento) * 
			    (num->dati_forma.f_trigonometrica.modulo));		
}
	
/*-------------------------------------------*/
/* Funzione per fare la somma in f.algebrica */
/*-------------------------------------------*/
n_compl_t somma_f_alg(n_compl_t n1,
		      n_compl_t n2 )
{
	n_compl_t somma;
	
	/*calcolo p.reale*/
	somma.dati_forma.f_algebrica.parte_reale = 		
		n1.dati_forma.f_algebrica.parte_reale + 
		n2.dati_forma.f_algebrica.parte_reale;

	/*calcolo p.immaginaria*/
	somma.dati_forma.f_algebrica.parte_immag = 		
		n1.dati_forma.f_algebrica.parte_immag + 
		n2.dati_forma.f_algebrica.parte_immag;

	return(somma);
}

/*------------------------------------------------*/
/* Funzione per fare la differenza in f.algebrica */
/*------------------------------------------------*/
n_compl_t differenza_f_alg(n_compl_t n1,
		           n_compl_t n2 )
{
	n_compl_t differenza; /*output: sottrazione */
	
	/*calcolo p.reale*/
	differenza.dati_forma.f_algebrica.parte_reale = 		
		n1.dati_forma.f_algebrica.parte_reale - 
		n2.dati_forma.f_algebrica.parte_reale;

	/*calcolo p.immaginaria*/
	differenza.dati_forma.f_algebrica.parte_immag = 		
		n1.dati_forma.f_algebrica.parte_immag - 
		n2.dati_forma.f_algebrica.parte_immag;

	return(differenza);
}

/*----------------------------------------------*/
/* Funzione per fare il prodotto in f.algebrica */
/*----------------------------------------------*/
n_compl_t prodotto_f_alg(n_compl_t n1,
		         n_compl_t n2 )
{
	n_compl_t prodotto;
	
	/*calcolo p.reale*/
	prodotto.dati_forma.f_algebrica.parte_reale = 		
		((n1.dati_forma.f_algebrica.parte_reale * 
		  n2.dati_forma.f_algebrica.parte_reale) -
		 (n1.dati_forma.f_algebrica.parte_immag * 
		  n2.dati_forma.f_algebrica.parte_immag));

	/*calcolo p.immaginaria*/
	prodotto.dati_forma.f_algebrica.parte_immag = 		
		((n1.dati_forma.f_algebrica.parte_reale *
		  n2.dati_forma.f_algebrica.parte_immag) +
		 (n2.dati_forma.f_algebrica.parte_reale * 
		  n1.dati_forma.f_algebrica.parte_immag));

	return(prodotto);
}

/*--------------------------------------------------*/
/* Funzione per fare il prodotto in f.trigonometica */
/*--------------------------------------------------*/
n_compl_t prodotto_f_trig(n_compl_t n1,
			  n_compl_t n2)
{
	n_compl_t prodotto_trig;

	/*calcolo modulo*/
	prodotto_trig.dati_forma.f_trigonometrica.modulo = 		
			n1.dati_forma.f_trigonometrica.modulo *
			n2.dati_forma.f_trigonometrica.modulo;

	/*calcolo argomeno*/
	prodotto_trig.dati_forma.f_trigonometrica.argomento = 							
			n1.dati_forma.f_trigonometrica.argomento + 
			n2.dati_forma.f_trigonometrica.argomento;

	return(prodotto_trig);
}

/*----------------------------------------------*/
/* Funzione per fare il rapporto in f.algebrica */
/*----------------------------------------------*/
n_compl_t rapporto_f_alg(n_compl_t n1,
			 n_compl_t n2)
{
	n_compl_t rapporto;
	
	/*calcolo p.reale*/
	rapporto.dati_forma.f_algebrica.parte_reale = 		
		 (((n1.dati_forma.f_algebrica.parte_reale * 
		    n2.dati_forma.f_algebrica.parte_reale) -
		   (n1.dati_forma.f_algebrica.parte_immag * 
		    n2.dati_forma.f_algebrica.parte_immag)) /
		  (pow (n2.dati_forma.f_algebrica.parte_reale, 2))+
		  (pow (n2.dati_forma.f_algebrica.parte_immag,2)));

	/*calcolo p.immaginaria*/
	rapporto.dati_forma.f_algebrica.parte_immag = 		
		 (((n1.dati_forma.f_algebrica.parte_reale *
		    n2.dati_forma.f_algebrica.parte_immag) +
		   (n2.dati_forma.f_algebrica.parte_reale * 
	 	    n1.dati_forma.f_algebrica.parte_immag)) /
		  (pow (n2.dati_forma.f_algebrica.parte_reale, 2))+
		  (pow (n2.dati_forma.f_algebrica.parte_immag,2)));

	return(rapporto);
}

/*---------------------------------------------------*/
/* Funzione per fare il rapporto in f.trigonometrica */
/*---------------------------------------------------*/
n_compl_t rapporto_f_trig(n_compl_t n1,
			  n_compl_t n2)
{
	n_compl_t rapporto_trig;

	/*calcolo modulo*/
	rapporto_trig.dati_forma.f_trigonometrica.modulo = 		
			n1.dati_forma.f_trigonometrica.modulo /
			n2.dati_forma.f_trigonometrica.modulo;

	/*calcolo argomeno*/
	rapporto_trig.dati_forma.f_trigonometrica.argomento = 							
			n1.dati_forma.f_trigonometrica.argomento - 
			n2.dati_forma.f_trigonometrica.argomento;

	return(rapporto_trig);
}
