#include <stdio.h>
#include <stdlib.h>

typedef struct uzel {
	int q_num;
	int n;
	char c;
	struct uzel *left;
	struct uzel *right;	
} UZEL;

UZEL *koren;

int solve(UZEL *p){
	
	if (p==NULL) {printf("problem: "); return 0;}
	
	int a, b, c;
	
	if (p->q_num>0) return p->n;
	else if (p->c=='+') {
		c = solve(p->left) + solve(p->right);
		return c;
	} else if (p->c=='-') {
		c = solve(p->left) - solve(p->right);
		return c;
	} else if (p->c=='/') {
		c = solve(p->left) / solve(p->right);
		return c;
	} else if (p->c=='*') {
		c = solve(p->left) * solve(p->right);
		return c;
	}
}

void delet(UZEL *p){
	
	if (p==NULL) return;
	
	delet(p->left);
	delet(p->right);
	
	free(p);
}

void opis(int o, UZEL *p){
	
	if (p==NULL) return;
	
	opis(o-1, p->left);
	if (p->q_num<0)	printf("%c ", p->c);
	else printf("%i ", p->n);
	opis(o+1, p->right);
}

void zarad(UZEL *p, char **pole){
	char help[5];														// ulozeni mozneho cisla
	int i;
	do {																// do while ...prejede bile znaky
		switch (**pole) {
			case '+': p->c='+'; p->q_num=-1; (*pole)++; return;			// q_num je < 0 , takze jde o znakovy uzel
			case '-': p->c='-'; p->q_num=-1; (*pole)++; return;
			case '*': p->c='*'; p->q_num=-1; (*pole)++; return;
			case '/': p->c='/'; p->q_num=-1; (*pole)++; return;
			case '(': p->c='('; p->q_num=-2; (*pole)++; return;
			case ')': p->c=')'; p->q_num=-2; (*pole)++; return;
		}
		if (**pole >= '0' && **pole <= '9') {
			
			for (i=0; **pole >= '0' && **pole <= '9'; i++, (*pole)++) {
				help[i]=**pole;
			} help[i]='\0';
			p->n=atoi(help);											// ulozeni retezce help (cisla) do struktury do n
			p->q_num=1;
			return;
		} (*pole)++;
	} while (**pole!='\0' || **pole==' ');								// osetrit podminku
}

int prior(char uzel, char next){
	if (uzel==NULL) return 1;
	int pr_uzel, pr_next;
	switch (uzel) {										// seznam podle priority
		case '+': pr_uzel=0; break;
		case '-': pr_uzel=0; break;
		case '*': pr_uzel=2; break;
		case '/': pr_uzel=1; break;
	}
	switch (next) {
		case '+': pr_next=0; break;
		case '-': pr_next=0; break;
		case '*': pr_next=2; break;
		case '/': pr_next=1; break;
	}
	if (pr_uzel>=pr_next) return 0;						// nulta pozice (prvni znak) ma vetsi prioritu
	else return 1;										// POZN muze byt i: '>=' --> '>', DUSLEDEK  jiny komutativni strom
}

UZEL *pridej(UZEL *uzel, char **pole){
	UZEL *p, *cislo, *pomoc;							// ukazatel *pomoc potrebuji k zamene dvou ukazatelu
	
	CISLO:
	
	p=(UZEL *)malloc(sizeof(UZEL));
	
	zarad(p, pole);
	
	p->left=NULL;
	p->right=NULL;

	// osetreni zavorek ()
	// zavorkovy koren bude jako cislo
	if (p->q_num==-2) {
		
		
	}	
	// je treba aby pridej vracelo koren!!!	
	
	
	
	
	
	
	if (**pole!='\0') {
		if (p->q_num>0) {
			cislo=p;									// p je cislo a ulozim jej do stromu, skocim a na p priradim dalsi uzel, ktery nebude cislo
			goto CISLO;									// a tedy muzu porovnat predchozi operaci s dalsi a podle toho upravit strom
		} else if (p->q_num<0) {
			if (uzel!=NULL && prior(uzel->c, p->c) == 0) {			// prvni operace ma vetsi prioritu
				uzel->right=cislo;
				return p;								// vratim p rekurzi nahoru
			} else {									// druha ma vetsi prioritu -> musim upravit strom
				if (uzel!=NULL) uzel->right=p;			// pri prvnim pouziti funkce je uzel prazdny a toto neni treba
				p->left=cislo;
				if (uzel==NULL) {koren=p;
				}
				SKOK:
				
				pomoc=pridej(p, pole);
				
				// if (**pole=='\0' && koren==pomoc) return pomoc;
				// if (**pole=='\0' && level==3) {printf("koneeeeec %c\n", p->c); return p;}
				// if (**pole=='\0' && level<3) {printf("koneeeeec %c\n", pomoc->c); return pomoc;}
				if (pomoc==NULL) return NULL;			// konec tvoreni stromu
				
				if (uzel!=NULL && prior(uzel->c, pomoc->c) == 0) {
					pomoc->left=uzel;
					p=pomoc;
					uzel=pomoc;
					koren=pomoc;
					
					goto SKOK;
				} else if (prior(p->c, pomoc->c) == 0) {
					pomoc->left=p;
					if (uzel!=NULL) uzel->right=pomoc;
					p=pomoc;
					koren=uzel;
					if (uzel==NULL) koren=p;
					goto SKOK;
				}printf("konsssssssssssssssssssssssssssssssssssssssssssseeeeec");
			}
		}
	} else {
		uzel->right=p;
		return NULL;
	}
}

int main(){
	int i;
			char pole[]="3*2-1/1+1-2*3/1/2/3-1+2-2+1-3125/5/5/5/5+69";
	//		char pole[]="1+2";
	//		char pole[]="2*3";
	//		char pole[]="2-8*7";
	
	char *ppole, **pp;
	ppole=pole;
	pp=&ppole;

	UZEL *uzel;
	
	pridej(uzel, pp);
	
	printf("OD KORENE:\n");
	opis(0 ,koren);
	printf("\n");
	printf("vysledek: %i\n", solve(koren));
	
	delet(koren);
}
