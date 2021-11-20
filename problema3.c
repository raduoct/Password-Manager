#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aleator genereaza sirul aleator pe baza unui seed si a unei lungimi(len)
char* aleator(int seed, int len)
{
	int i;
	char* sir;
	
	srand(seed);
	sir = malloc((len+1) * sizeof(char));
	for(i = 0;i < len; i++)
	{
		sir[i]= (char)(rand()%94 + 32);
	}
	sir[len] = 0;
	return sir;
}

//codificarea 1 in care verific aparitia unui caracter
char* codif1(char c)
{
	static int aparitii[126];
	char* cod;
	
	cod = malloc (5 * sizeof(char));
	sprintf(cod,"%c%d",c,aparitii[ (int)c]);
	aparitii[ (int) c] ++;
	return cod;
}

//codificarea 2 in care aplic transformariile pe biti cerute
char* codif2(char c)
{
	char* cod, mask = 1 << 5;
	int nr = 0, i, bit3, bit6;

	bit6 = (c >> 6) & 1;
	bit3 = (c >> 3) & 1;
	if( bit6 )
	{
		c = c & ~( 1 << 6); 	
	}
	else
	{
		c = c | ( 1 << 6);
	}
	if( bit3 )
	{
		c = c & ~( 1 << 3);
	}
	else
	{
		c = c | ( 1 << 3);
	}
	for(i = 0;i < 8; i++)
	{
		if( (1<<i) & c ) nr++;
	}
	c = c | mask;
	c = c & ~ 1;
	cod = malloc ( 4 * sizeof(char));
	sprintf(cod,"%c%d",c,nr);
	
	return cod;	
}

//codificarea 3 in care daca c este litera mica aplic uppercase literei
char* codif3(char c)
{
	char* cod;

	cod = malloc ( 3 * sizeof(char));
	if( c > 96 && c < 123 ) 
		cod[0] = (char)( (int)c - 32);
	else 
		cod[0] = c;
	cod[1] = 0;
	
	return cod;

}

//functia in care se aplica aleator fiecare codificare
char* transformare(char* sir, char* (*vect[])(char x) )
{
	int i;
	char* aux;
	
	aux = (char* )malloc ( (5*strlen(sir))*sizeof(char) );
	for(i = 0; i < strlen(sir) ; i++)
	{
		strcat(aux, vect[rand()%3](sir[i]));
	}
	
	//in aux se afla sirul aleator codificat tot aleator
	return aux;
}

int main()
{	
	int seed, n;
	char* p,* rez;
	char* (*vect[3])(char) = {codif1, codif2, codif3};
	
	
	scanf("%d%d", &seed, &n);
	srand(seed);
	p = aleator(seed, n);
	rez = transformare( p, vect);
	
	printf("%s", rez);
	printf("\n");
	
	return 0;
}
