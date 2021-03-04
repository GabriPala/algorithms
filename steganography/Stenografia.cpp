//Librerie
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


//Variabili globali
unsigned char caratteri[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9'};
unsigned char frase[]="iiiiii";			// frase/parola da inserire nell'immagine


// FUNZIONE PRINCIPALE
int main()
{
	// VARIABILI
	unsigned int width=0;							// righe
	unsigned int height=0;							// colonne
	unsigned int maximum = 0;						// maximum pixel value
	unsigned char pSix[2];							// indica che questa è una immagine PPM
	unsigned int posX;								// usata per trovare i pixel da modificare
	int x,y,z=1,i=0;								// contatori
	
	//Crea due oggetti
	ifstream in("test.ppm",ios::in);
	ofstream out("risultato.ppm",ios::out);
	//Prende meta-data dall'immagine originale	
	in >> pSix >> width >> height >> maximum;
	//Memorizzano i colori separatamente
	unsigned char Red[width][height];
	unsigned char Green[width][height];
	unsigned char Blue[width][height];
	
	// creazione della chiave
	srand((unsigned)time(NULL));
	unsigned int chiave=rand()%(width-1)+1;		// chiave numerica casuale
	
	
	//Inizializza le nuove immaggini con i meta-data dell'originale
	out <<'#'<<chiave<<endl<<"P6"<<' '<<width<<' '<<height<<' '<<maximum<<' ';
	
	
	//Separa i colori in tre matrici
	for(y=0; y<height; y++)			//COLONNE
	{
		for(x=0; x<width; x++)		//RIGHE
			in >> Red[x][y] >> Green[x][y] >> Blue[x][y];
	}
	

	
	//Utilizzando la chiave trova le posizioni dei pixel da modificare
	int a=0;
	for(y=0; y<height;y++)
	{
		for(x=0;x<width;x++)
		{
			if(chiave*z==x)									// punto da modificare
			{
				for(i>0;i<sizeof(caratteri);i++)				// valore del carattere (corrisponde a i)
				{
					if(frase[z]==caratteri[i])
					{
						if(i<sizeof(caratteri)/3)				// Modifica il rosso se è nel 1° terzo dei valori di carattere (1-11)
						{
							/*Red[x][y]=Red[x-1][y]-i;*/ Red[x][y]='!';
						}
						else
						{
							if(i<(sizeof(caratteri)/3)*2)		// Modifica il verde se è nel 2° terzo dei valori di carattere (12-22)
							{
							Green[x][y]=Green[x-1][y]-i-sizeof(caratteri)/3;
							}
							else								// Modifica il blu se è nel 3° terzo dei valori di carattere (23-35)
							{
							Blue[x][y]=Blue[x-1][y]-i-(sizeof(caratteri)/3)*2;
							}
						}
						z++;
					}
				}
			}
		}	
	}
	
	
	
	
	//Ricostruisce l'immagine apportando le modifiche
	for(y=0; y<height; y++)
	{
		for(x=0; x<width; x++)
		    out << Red[x][y] << Green[x][y] << Blue[x][y];
	}
	
	return 0;
}



