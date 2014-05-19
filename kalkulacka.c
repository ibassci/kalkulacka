#include <stdio.h>
#include <stdlib.h>

typedef struct uzel {
	int q_num;
	double n;
	char c;
	struct uzel *left;
	struct uzel *right;	
} UZEL;

double solve(UZEL *p){
	if (p==NULL) {printf("ERROR: Prazdny koren."); return;}
	
	int a, b;
	
	if (p->q_num>0) return p->n;
	else if (p->c=='+') return solve(p->left) + solve(p->right);
	else if (p->c=='-') return solve(p->left) - solve(p->right);
	else if (p->c=='/') return solve(p->left) / solve(p->right);
	else if (p->c=='*') return solve(p->left) * solve(p->right);
}

void delet(UZEL *p){
	if (p==NULL) return;
	
	delet(p->left);
	delet(p->right);
	
	free(p);
}

void opis(UZEL *p){
	if (p==NULL) return;
	
	if (p->q_num==-9) printf("(");
	opis(p->left);
	
	if (p->q_num<0)	{
		switch (p->c) {
			case '+': printf(" %c ", p->c); break;
			case '-': printf(" %c ", p->c); break;
			case '/': printf("%c", p->c); break;
			case '*': printf("%c", p->c); break;
		}
	} else printf("%0.1f", p->n);
	opis(p->right);
	if (p->q_num==-9) printf(")");
}

void zarad(UZEL *p, char **pole){
	
	do {																// do while ...prejede bile znaky
		switch (**pole) {
			case '+': p->c='+'; p->q_num=-1; (*pole)++; return;			// q_num je < 0 , takze jde o znakovy uzel
			case '-': p->c='-'; p->q_num=-1; (*pole)++; return;
			case '*': p->c='*'; p->q_num=-1; (*pole)++; return;
			case '/': p->c='/'; p->q_num=-1; (*pole)++; return;
			case '(': p->q_num=-7; (*pole)++; return;
			case ')': p->q_num=-8; (*pole)++; return;
			case '\0': p->q_num=-9; return;
		}
		if (**pole >= '0' && **pole <= '9') {
			int i;
			char *help;
			help=(char *)malloc(sizeof(char));
			
			for (i=0; **pole >= '0' && **pole <= '9' || **pole=='.'; i++, (*pole)++) {
				help[i]=**pole;
			} help[i]='\0';
			
			p->n=atof(help);											// ulozeni retezce help (cisla) do struktury do n
			p->q_num=1;
			while (**pole==' ') (*pole)++;
			free(help);
			return;
		}
		(*pole)++;
	} while (**pole==' ');
}

int prior(char uzel, char next){
	if (uzel==NULL) return 1;
	int pr_uzel, pr_next;
	
	switch (uzel) {										// seznam podle priority
		case '+': pr_uzel=0; break;
		case '-': pr_uzel=0; break;
		case '/': pr_uzel=1; break;
		case '*': pr_uzel=1; break;
	} switch (next) {
		case '+': pr_next=0; break;
		case '-': pr_next=0; break;
		case '/': pr_next=1; break;
		case '*': pr_next=1; break;
	} if (pr_uzel>=pr_next) return 0;					// nulta pozice (prvni znak) ma vetsi prioritu
	else return 1;										// POZN muze byt i: '>=' --> '>', DUSLEDEK  jiny komutativni strom
}

UZEL *pridej(UZEL *uzel, char **pole){
	UZEL *p, *cislo, *pomoc;							// ukazatel *pomoc potrebuji k zamene dvou ukazatelu
	
	CISLO:
	p=(UZEL *)malloc(sizeof(UZEL));
	
	zarad(p, pole);
	
	p->left=NULL;
	p->right=NULL;
	
	if (p->q_num==-7) {
		p->q_num=NULL;									// vycistim alokovanou pamet
		p=NULL;
		cislo=pridej(p, pole);
		cislo->q_num=-9;
		if (**pole==')') return cislo;
		goto CISLO;
	} else if (p->q_num==-8) {
		uzel->right=cislo;
		return NULL;
	}
	
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
				
				SKOK:
				
				pomoc=pridej(p, pole);
				
				// konec tvoreni stromu
				if (pomoc!=NULL && pomoc->q_num==-3) {return pomoc;}
				else if (uzel!=NULL && pomoc==NULL) {uzel->q_num=-3; return uzel;}
				else if (uzel==NULL && pomoc==NULL) {p->q_num=-3; return p;}
				
				
				if (uzel!=NULL && prior(uzel->c, pomoc->c) == 0) {
					pomoc->left=uzel;
					p=pomoc;
					uzel=pomoc;
					goto SKOK;
				} else if (prior(p->c, pomoc->c) == 0) {
					pomoc->left=p;
					if (uzel!=NULL) uzel->right=pomoc;
					p=pomoc;
					goto SKOK;
				}
			}
		}
	} else {
		if (uzel!=NULL) uzel->right=p;
		else if (uzel!=NULL && p->q_num==-9) uzel->right=cislo;
		else if (uzel==NULL) return cislo;
		return NULL;
	}
}

int main(){
	int i;
	UZEL *koren;
	char *ppole, **pp;
	char pole[100];
	
	gets(pole);
	
	ppole=pole;
	pp=&ppole;
	koren==NULL;
	koren=pridej(koren, pp);
	
	opis(koren);
	printf("\n\nVysledek: %0.1f\n\n", solve(koren));
	delet(koren);
}



/*	TESTOVACI MAIN
	==============

int main(){
	int i;
			char pole[]="2*3/1/2/3";
	//		char pole[]="12*2/3*2/4";
	//		char pole[]="(((((2*3)))))";
	//		char pole[]=" 2   -      8              *              7    ";
	//		char pole[]="2-8*7/8+1";
	//		char pole[]="((2+3)*4)+5";
	
	char *ppole, **pp;
	ppole=pole;
	pp=&ppole;

	UZEL *koren;
	koren=pridej(koren, pp);
	opis(koren);
	printf("\n\nVysledek: %f\n", solve(koren));
	
	delet(koren);
}

*/
