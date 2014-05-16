#include <stdio.h>
#include <stdlib.h>

// program MAKE
/*
LEMON parser tutorial
*/
typedef struct uzel {
	int n;
	char c;
	struct uzel *left;
	struct uzel *right;	
} UZEL;


// funkce na vyhodnoceni stromu
/*
int solve(UZEL *koren){
	
	int a, b;
	
	if (koren->left->n!=NULL) {
		a=koren->left->n;
	} else {
	
	solve(koren->left)
	
	
}
*/

// funkce na smazani stromu

// funkce na priority (dostane dva argumenty a podle uzivatelskeho poradi posle ten s vyssi prioritou

// funkce na vyhodnoceni uzlu (bude pouzivana funkci pro vyhodnoceni stromu), ktera dostane dva argumenty (cisla) a provede operaci podle uzivatelskeho prani

void zarad(UZEL *p, char *pole){
	char help[5];														// ulozeni mozneho cisla
	int i;
	do {																// do while ...prejede bile znaky
		switch (*pole) {
			case '+': p->c='+'; p->n=NULL; return;									// smmazal jsem za casem p->n=NULL; ->nefungovalo
			case '-': p->c='-'; return;
			case '*': p->c='*'; return;
			case '/': p->c='/'; return;
		}
		if (*pole >= '0' && *pole <= '9') {
			
			for (i=0; *pole >= '0' && *pole <= '9'; i++, pole++) {
				help[i]=*pole;
			} help[i]='\0';
			p->n=atoi(help);
														// ulozeni retezce help (cisla) do struktury do n
			return;
		} else {
			printf("ani znak ani cislo ani mezera: OSETRI to");
			return;
		}
	} while (*pole==' ');
}

int prior(char uzel, char next){
	int pr_uzel, pr_next;
	switch (uzel) {										// senznam podle priority
		case '+': pr_uzel=0; break;
		case '-': pr_uzel=0; break;
		case '*': pr_uzel=1; break;
		case '/': pr_uzel=1; break;
	}
	switch (next) {
		case '+': pr_next=0; break;
		case '-': pr_next=0; break;
		case '*': pr_next=1; break;
		case '/': pr_next=1; break;
	}
	if (pr_uzel>pr_next) return 0;
	else return 1;
}

	// funkce pridej by mela vracet koren stromu

void pridej(UZEL *uzel, char *pole){
	UZEL *p, *pomoc;									// ukazatel *pomoc potrebuji k zamene dvou ukazatelu
	
	SKOK:
	
	p=(UZEL *)malloc(sizeof(UZEL));
	
	zarad(p, pole);
	p->left=NULL;
	p->right=NULL;
	
	if (uzel==NULL) {
		uzel=p;
		pridej(uzel, pole);								// ukazatel *pole se uz posunul ve funkci zarad(), takze neni treba posunovat
	} else {
		if (p->n!=(int)NULL) {
			uzel->right=p;								// p je cislo a ulozim jej do stromu, skocim a na p priradim dalsi uzel, ktery nebude cislo
			goto SKOK;									// a tedy muzu porovnat predchozi operaci s dalsi a podle toho upravit strom
		} else if (p->c!=(int)NULL) {
			if (prior(uzel->c, p->c) == 0) {			// prvni operace ma vetsi prioritu
				p->left=uzel;
				
			} else {									// druha ma vetsi prioritu -> musim upravit strom
				pomoc=uzel->right;
				uzel->right=p;
				p->left=pomoc;
			}
		} else printf("nova struktura *p nema ani cislo ani znak - osetri to");
		
	}
	
	

}






int main(){
	
	char pole[]="1*2+3";
	char *ppole;
	ppole=pole;

	UZEL *uzel;
	
	uzel=(UZEL *)malloc(sizeof(UZEL));
	
	zarad(uzel, ppole);
	
	
	
	
}
