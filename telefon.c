#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char *s1, *s2;
} pereche;

void codificare(char text[], char a[][5], char textcod[], int* nr_caract) {
	int k, i, j, t;
	int tasta = 0;
	int nr = 0;
	for (k = 0; k < strlen(text); k++) {
		if (text[k] == ' ') {	
			textcod[nr++] = '0';
			tasta = 0;
		}
		for (i = 2; i <= 9; i++)
			if (i == 7 || i == 9)
				for (j = 1; j <= 4; j++) {
					if (text[k] == a[i][j]-32) {
						tasta = i;
						textcod[nr++] = '1'; // litera mare
						for (t = 1; t <= j; t++)
							textcod[nr++] = i + '0';
					}
					if (text[k] == a[i][j]) {
						if (i == tasta)
							textcod[nr++] = '#';
						for (t = 1; t <= j; t++)
							textcod[nr++] = i + '0';
						tasta = i;
					}

				}
			else
				for (j = 1; j <= 3; j++) {
					if (text[k] == a[i][j]-32) {
						tasta = i;
						textcod[nr++] = '1'; // litera mare
						for (t = 1; t <= j; t++)
							textcod[nr++] = i + '0';
					}
					if (text[k] == a[i][j]) {
						if (i == tasta)
							textcod[nr++] = '#';
						for (t = 1; t <= j; t++)
							textcod[nr++] = i + '0';
						tasta = i;
					}
				}
	}
	*nr_caract = nr;
}

void decodificare (char sir[], char a[][5]) {
	int i; 
	int l_secv = 0;
	int CapsLk = 0; // CapsLk={0->litera mica, 1->litera mare}
	int x;

	
	if (sir[0] >= '2' && sir[0] <= '9')
			l_secv = 1;
	else
		 if (sir[0] == '1')
				CapsLk = 1;
	for (i = 1; i < strlen(sir); i++) {
		if ( sir[i] == sir [i-1]) 
			l_secv++;
		else {
			if (sir[i] >= '2' && sir[i] <= '9') {
				if (l_secv > 0) {
					x = sir[i-1] - '0'; // transform caracterul s[i] in nr corespunzator
					if (CapsLk == 0)
						printf ("%c", a[x][l_secv]);
					else 
						printf ("%c", a[x][l_secv]-32);
				}
				l_secv = 1;
				if (sir[i-1] != '1')
					CapsLk = 0;
			}
			if (sir[i] == '#') {
				if (l_secv > 0) {
					x = sir[i-1] - '0'; // transform caracterul s[i] in nr corespunzator
					if (CapsLk == 0)
						printf ("%c", a[x][l_secv]);
					else 
						printf ("%c", a[x][l_secv]-32);
				}
				l_secv = 0;
			}
			if (sir[i] == '1') {
				if (l_secv > 0) {
					x = sir[i-1] - '0'; // transform caracterul s[i] in nr corespunzator
					if (CapsLk == 0)
						printf ("%c", a[x][l_secv]);
					else
						printf ("%c", a[x][l_secv]-32);
				}
				l_secv = 0;
				CapsLk = 1;
			}
			if (sir[i] == '0') {
				if (l_secv > 0 ) {
					x = sir[i-1] - '0'; // transform caracterul s[i] in nr corespunzator
					if (CapsLk == 0)
						printf ("%c", a[x][l_secv]);
					else printf ("%c", a[x][l_secv]-32);
				}
				printf(" ");
				l_secv = 0 ;
			}
			}
	}
	if (l_secv > 0) {
		x = sir[i-1] - '0';
		if (CapsLk == 0)
			printf ("%c", a[x][l_secv]);
		else printf ("%c", a[x][l_secv]-32);
	}
	printf("\n");
}

void auto_correct(char text[], int n, char a[][5]) {
	int i;
	char cuvant[100];
	// aloc memorie pentru structura + componentele ei
	pereche* v = (pereche *)malloc(n*sizeof(pereche));
	for (i = 0; i < n; i++) {
		scanf("%s ", cuvant);
		v[i].s1 = malloc ( (strlen(cuvant)+1) * sizeof(char));
		strcpy(v[i].s1, cuvant);
		scanf("%s\n", cuvant);
		v[i].s2 = malloc ( (strlen(cuvant)+1) *sizeof(char));
		strcpy(v[i].s2, cuvant);
	}

	char *p, aux1[100], aux2[100];
	aux1[0] = '\0';
	aux2[0] = '\0';
	char textcodif[300];
	int nr_crct = 0;
	char aux[100];
	aux[0] = '\0';
	strcpy(aux, text);
	//corectarea textului dat
	for (i = 0; i < n; i++) 
	{
		if (strstr(aux, v[i].s1) != NULL) // ca sa evit corectarea unui cuvant de doua ori
		{
			p = strstr(text, v[i].s1);
			while (p!=NULL) 
			{
				int ok = 1; //presupun ca p pointeaza la un cuvant propriu-zis
				if (strlen(text) != strlen(p))
					if ( text[ strlen(text) - strlen(p) - 1 ] != ' ') 
						ok = 0; //nu e cuvant propriu-zis => nu se corecteaza
				if ( ok == 1)
				{
					strncpy(aux1, text, p-text);
					aux1[p-text]='\0';
					strcpy(aux2, p + strlen(v[i].s1));
					strcat(aux1, v[i].s2);
					strcat(aux1, aux2); 
					strcpy(text, aux1);
				}
				p = strstr (p + strlen(v[i].s2), v[i].s1);
			}
		}	
	}
	//criptarea textului corectat
	codificare(aux1, a, textcodif, &nr_crct);
	textcodif[nr_crct] = '\0';
	printf("%s\n", textcodif);


	// eliberez memoria pentru structura + componentele ei
	for (i = 0; i < n ; i++) {
		free(v[i].s1);
		free(v[i].s2);
	}
	free(v);
}

// functie care calculeaza cel mai mic divizor comun dintre doua numere 
long long cmmdc(long long x, long long y) {
	long long R;
	R = x % y;
	while (R) {
		x = y;
		y = R;
		R = x % y;
	}
	return y;
}

int nr_componente(char text[])
{
	int i;
	int nr_comp = 1;
	for (i = 0 ; i < strlen(text) ; i++)
		if (text[i] == ' ')
			nr_comp++;
	return nr_comp;
}

// verifica daca mesajul este prim
void verifica_prim (long long componente[], int n) {
	int ok,i,j;
	ok = 1; // presupun ca mesajul este prim
	for (i = 1 ; (i <= n-1) && (ok == 1); i++)
		for (j = i+1; (j <= n) & (ok == 1); j++)
			if (cmmdc( componente[i], componente[j]) != 1) 
				ok = 0;
	printf ("%d\n", ok); // ok=1 - mesaj prim, ok=0 - mesajul nu e prim
}

void vector_componente(char text[], char a[][5]) {
	int i, cifra;
	long long x = 0;
	int nr_crct_codif = 0;
	char textcodif[300];

	// formez vectorul de componente
	codificare(text, a, textcodif, &nr_crct_codif);
	textcodif[nr_crct_codif] = '\0';
	int nr_comp = nr_componente(text);
	long long *componente = malloc((nr_comp + 1)*sizeof(long long));
	int nr_crt = 1; // numarul curent al componententelor din vector 
	for (i = 0; i < nr_crct_codif; i++) {
		if (textcodif[i] != '#' && textcodif[i] != '0') {
			cifra = textcodif[i] - '0';
			x = x * 10 + cifra;
		}
		if (textcodif[i] == '0') {
			componente[nr_crt] = x;
			x = 0;
			nr_crt++;
		}
	}
	componente[nr_crt] = x;

	// afisez numarul de componente din vectorul de componente
	printf("%d\n", nr_comp);

	// afisez vectorul de componente
	for (i = 1; i <= nr_comp; i++) {
		if (i == nr_comp)
			printf("%lld", componente[i]); //pt a nu af spatiu dupa ultima comp
		else
			printf("%lld ", componente[i]);
	}
	printf ("\n");

	// caut componenta maxima+pozitia ei in vectorul de componente si le afisez
	long long Max;
	Max = 0;
	int poz_max;
	for (i = 1; i <= nr_comp; i++)
		if (componente[i] > Max) {
			Max = componente[i];
			poz_max = i;
		}
	printf ("%lld %d\n", Max, poz_max);

	// verific daca mesajul este prim
	verifica_prim(componente, nr_comp);
	free(componente);
}


// sorteaza un vector descrescator
void bubbleSort(int n, long long x[]) {
	int ok, i, aux;
	aux = 0;
	ok = 0; // presupunem ca vectorul x nu e sortat
	while (ok == 0) {
		ok = 1; // presupunem ca vectorul x e sortat
		for ( i = 0 ; i < n-1 ; i++)
			if (x[i] < x[i+1]) {
				ok = 0; // vectorul x nu e sortnr_crt]nr_crt]at
				aux = x[i];
				x[i] = x[i+1];
				x[i+1] = aux;
			}
	}
}

// verifica daca numarul este perfect
void verifica_perfect(char text[], char a[][5]) {
	int i, N, nr_crct_codif, cifra, sum, nrcif;
	N = 0; // numarul magic
	nr_crct_codif = 0; // numarul de caractere ale textului codificat
	sum = 0; // suma cifrelor textului codificat
	nrcif = 0; // nr de cifre din textul codificat
	char textcodif[300];
	codificare(text,a,textcodif,&nr_crct_codif);
	for (i = 0; i < nr_crct_codif; i++)
		if (textcodif[i] != '#') {	
			cifra = textcodif[i] - '0';
			sum += cifra;
			nrcif++;
		}
	N = sum % 9 ;
	if (N == 0 || nrcif % N != 0)
		printf("0");
	else {
		long long* grup = malloc( (nrcif/N) * sizeof(long long) );
		int count, nr_grupuri;
		count = 0; //numara cifrele in timp ce se formeaza un grup
		nr_grupuri = 0;
		long long componenta;
		componenta = 0;
		for (i = 0; i < nr_crct_codif; i++) {
			if (textcodif[i] != '#') {
				cifra = textcodif[i] - '0';
				componenta = componenta * 10 + (long long)cifra; 
				count++;
			}
			if (count == N) {	
				grup[nr_grupuri++] = componenta;
				count = 0;
				componenta = 0;
			}
		}
		bubbleSort(nr_grupuri, grup);
		for (i = 0; i < nr_grupuri; i++) {
			if (i == nr_grupuri -1)
				printf("%lld", grup[i]); //pt a nu-mi afisa spatiu dupa ultimul grup
			else
				printf("%lld ", grup[i]);
		}
		free(grup);
	}
}

int main() {
	//declaratii
	int n, i, j;
	char text1[100], text2[100], text3[100], sir[300];

	//formez matricea cu tastele
	char a[10][5], c = 'a';
	for (i=2; i<=9; i++)
		if (i==7 || i==9)
			for (j=1; j<=4; j++) {
				a[i][j]=c;
				c++;
			}
		else 
			for (j=1; j<=3; j++) {
				a[i][j]=c;
				c++;
			}
	// cerinta 1
	fgets(text1, 100, stdin);
	int nr_caract = 0;
	char textcod[300];
	codificare(text1, a, textcod, &nr_caract);
	textcod[nr_caract] = '\0';
	printf("%s\n", textcod);

	// cerinta 2
	scanf("%s\n", sir);
	decodificare(sir, a);

	// cerinta 3
	fgets(text2, 100, stdin);
	scanf("%d\n", &n);
	auto_correct(text2, n, a);
	
  	// cerinta 4
	fgets(text3, 100, stdin);
	vector_componente(text3, a);
	verifica_perfect(text3, a);

	return 0;
}
