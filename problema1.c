#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functia valid verifica daca cheia cat si textul daca sunt invalide
int valid(char c[], char s[])
{
	int i;
	
	for(i = 0; i < strlen(c); i++)
	{
		if(!(( c[i] > 64 && c[i] < 91 ) || (c[i] > 96 && c[i] < 123)))
			return 0;
	}
	
	for(i = 0; i < strlen(s); i++)
	{
		if(!(( s[i] > 64 && s[i] < 91 ) || (s[i] > 96 && s[i] < 123)))
			return 0;
	}
	
	return 1;

}

// invers_lit primeste o litera si returneaza aceasta litera in case ul diferit
char invers_lit(char lit)
{
	if( lit > 96 && lit < 123) lit -= 32;
	else lit += 32;
	
	return lit;
}

// schimbarea primeste o litera si ii aplica criptarea corespunzatoare
void schimbare(char cheie, char *text)
{
	// in nr si val memorez valoarea caractelor din codul ASCII
	// sch repr distanta de la a cu care trebuie mutata litera pt criptare 
	int nr, val, sch;
	
	nr = (int) cheie;
	val = (int) *text;
	//obs ca in functie de case ul cheii litera text se va muta cu 26 sau
	//0 pozitii astfel cu invers_lit aducem litera text la case ul potrivit
	if(nr > 96 && nr < 123) sch = nr - 97;
	else
	{
	 	sch = nr - 65;
	 	val = invers_lit(val); 	
	}
	//litera care trebuie criptata esti mutata cu sch pozitii
	if(val > 96 && val < 123)
	{
		if( val + sch > 122 )
			*text = (char)(65 + (val + sch - 123));
		else 
			*text = (char)( val + sch );
	}
	else
	{
		if( val + sch > 90 )
			*text = (char)( 96 + (val + sch - 90));
		else
			*text = (char)( val + sch);
	}  
}

int main()
{
	char c[15000], s[15000];
	int i, j = 0;
	
	scanf("%s %s", c, s);
	//verificare validitate input
	if(valid(c,s))
	{
		for(i = 0; i < strlen(s); i++)
		{
			//aplicare criptare
			schimbare( c[j], &s[i]);
			j++;
			if(j%strlen(c)==0) j = 0;
		}
		printf("%s", s);
		printf("\n");
	}
	else 
		printf("INVALID\n");
	
	return 0;
}
