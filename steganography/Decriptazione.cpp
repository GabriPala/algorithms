#include <iostream>
#include <string>
#include <fstream>
using namespace std;


//prototipi
void CreaTabellaValori();
bool ListaVuota();


//FUNZIONE PRINCIPALE
int main()
{
	
	unsigned int width=0;		// righe
	unsigned int height=0;		// colonne
	unsigned int maximum = 0;	// maximum pixel value
	unsigned char pSix[10];		// indicates this is a PPM image
	
    char caratteri[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char parola[]="password";
	int parola_pos[7];
	
	int i,y,z=0;
	
	ifstream in("imgnorm.ppm",ios::in);  
	ofstream out("output.txt",ios::out); 
	
	//Prende meta-data dall'immagine originale
	in >> pSix >> width >> height >> maximum;
	
	//Memorizzano i colori separatamente
	unsigned char Red[width][height];
	unsigned char Green[width][height];
	unsigned char Blue[width][height];
	
	//Separa i colori
	for(i=0; i<height; i++)			//COLONNE
	{
		for(y=0; y<width; y++)		//RIGHE
			in >> Red[y][i] >> Green[y][i] >> Blue[y][i];
	}

	
	int newparola[10];
	
	int pos[]={15,15,35,35,25,55,45,65,5,75,25,85,35,95};
	int posizione=0;
	
	//Prendi parola
	for(i=0; i<height; i++)			//COLONNE
	{		
		for(y=0; y<width; y++)		//RIGHE
		{
			if(pos[posizione]==y && pos[posizione+1]==i)
			{
				posizione+=2;
				
				newparola[z]=Red[y][i]-Red[y-1][i];
				
				z++;
			}
		
		}
	}
	
	for(i=0; i<7; i++)			//COLONNE
	{		
		for(y=0; y<26; y++)		//RIGHE
		{
			if(newparola[i]==y)
			{
				out<<caratteri[y];
			}
		}
	}
	
	
	
	return 0;
}




