#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
	char *camp, *valoare;
}pereche ;

//e_delim vericia daca un char este un caracter delimitator
int e_delim(char c)
{
	if (strchr("!:;.,?() \n" ,c) != NULL)
		return 1;

	return 0;
}

//delimiteaza sparge textul formularului in delimitatori si campuri 
void delimiteaza(char * formular, int *dim, char **vect)
{
	int i, start, stop, j = 0;
	char aux[2000];
	
	start = 0;
	stop = -1;
	/*cand gasesc un delimitator si caracterul urmator nu este
	merg pana la urmatorul delimitator*/
	for (i = 0; i < strlen(formular); i++) {
		if (e_delim(formular[i]) && !e_delim(formular[i+1]))
			start = i+1;

		if (!e_delim(formular[i]) && e_delim(formular[i+1]))
			stop = i;
		//gasit inceputul si sfarsitul campului il salvez in vect
		if (start != -1 && stop != -1)
		{
			strncpy(aux, formular+start, stop-start+1);
			aux[stop-start+1] = 0;
			vect[j] = strdup(aux);
			j++;

			start = -1;
			stop = -1;
		}
		//fiecare delimitator este pus si el in vect
		if(e_delim(formular[i]))
		{
			vect[j] = malloc(1 * sizeof(char));
			vect[j][0] = formular[i];
			vect[j][1] = 0;
			j++;
		}
	}

	*dim = j;
}


int main()
{

	int n, i, dim, j;
	pereche *v;
	char s[11000], c[11000], t[11000], rez[20000];
	char * vect_delim[1000], *formular;
	
	scanf("%d", &n);
	v = malloc( n * sizeof(pereche));
	//citire si alocare pentru vectorul de structuri
	for(i = 0; i < n; i++)
	{
		scanf("%s%s", s, c);
		v[i].camp = malloc ( strlen(s) * sizeof(char));
		v[i].valoare = malloc ( strlen(c) * sizeof(char));
		strcpy(v[i].camp, s);
		strcpy(v[i].valoare, c);
	}
	
	//pentru \n care ramane in bufferul de stdin,s-ar putea rezolva si cu fflush
	fgets(t, 10, stdin);
	fgets(t, 11000, stdin); 
	formular = strdup(t);

	delimiteaza(formular, &dim, vect_delim);
	/*compar fiecare camp din vectorul de structuri cu fiecare cuvant din vect
	si daca este intr-adevar camp il inlocuiesc cu valoarea corespunzatoare*/
	for (i = 0; i < dim; i++)
	{
		for(j = 0; j < n; j++)
			if (strcmp(v[j].camp, vect_delim[i]) == 0)
				vect_delim[i] = strdup(v[j].valoare);
	}
	
	/*concatenez fiecare string din vect pentru a ajungle la formularul dorit
	in care campurile sunt inlocuite cu valorile lor*/
	strcpy(rez, vect_delim[0]);
	for(i = 1; i < dim; i++)
		strcat(rez, vect_delim[i]);

	if (rez[strlen(rez)-1] == '\n' && formular[strlen(formular)-1] != '\n')
		rez[strlen(rez)-1] = 0;
	printf("%s", rez);

	return 0;
}
