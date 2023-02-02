#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <time.h>

using namespace std;

class Ucak
{

public:

	char ucakParcasi[5];
	int Y;

	Ucak()
	{
		Y = 10;
		ucakParcasi[0] = 178;
		ucakParcasi[1] = 178;
		ucakParcasi[2] = 178;
		ucakParcasi[3] = 178;
		ucakParcasi[4] = 178;
	}

};

class Dusman
{
public:
	
	int X = 87;
	int Y;
	char parca[9] = { char(176), char(176), char(176), char(176), char(178), char(176), char(176), char(176), char(176) };

};

class Ates
{
	public:

		int X;
		int Y;
		char mermi=223;

		Ates()
		{
			int Y = 10;
		}

};


Ucak ucak;

Dusman dusman[100];

Ates ates[1000];

int aktifDusmanSayisi = 0;

int pasifDusmanSayisi = 0;

int aktifAtesSayisi = 0;

int pasifAtesSayisi = 0;


const int	sahneGenisligi = 89;

const int	sahneYuksekligi = 20;

char		sahne[sahneGenisligi][sahneYuksekligi];

char		tuslar[256];



void gotoxy(int x,int y)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}



void sahneyiCiz()
{
	for (int y = 0; y < sahneYuksekligi; y++) 
	{
		for (int x = 0; x < sahneGenisligi; x++)
		{

			cout << sahne[x][y];
		}
		cout << endl;
	}
}

void sinirlariOlustur()
{
	for (int x = 0; x < sahneGenisligi; x++)
	{
		sahne[x][0] = 178;
		sahne[x][sahneYuksekligi-1]=178;
	}
	for (int y = 0; y < sahneYuksekligi; y++)
	{
		sahne[0][y] = 178;
		sahne[sahneGenisligi-1][y] = 178;
	}

}

void sahneyiTemizle()
{
	for(int y=0 ;y<sahneYuksekligi;y++)
	{
		for(int x=0 ;x<sahneGenisligi;x++)
		{
			sahne[x][y]=' ';
		}
	}
}



void ucakYerlestir(Ucak ucak)
{
	sahne[1][ucak.Y-2]=ucak.ucakParcasi[0];
	sahne[2][ucak.Y-1]=ucak.ucakParcasi[1];
	sahne[3][ucak.Y  ]=ucak.ucakParcasi[2];
	sahne[2][ucak.Y+1]=ucak.ucakParcasi[3];
	sahne[1][ucak.Y+2]=ucak.ucakParcasi[4];

}


//																	DUSMAN FOKSIYONLARI


void dusmanlariCiz()
{

	for (int i = pasifDusmanSayisi; i < aktifDusmanSayisi+1; i++)
	{
		sahne[dusman[i].X+2][dusman[i].Y + 1] = dusman[i].parca[0];
		sahne[dusman[i].X+1][dusman[i].Y + 1] = dusman[i].parca[1];
		sahne[dusman[i].X  ][dusman[i].Y + 1] = dusman[i].parca[2];
		sahne[dusman[i].X+2][dusman[i].Y + 2] = dusman[i].parca[3];
		sahne[dusman[i].X+1][dusman[i].Y + 2] = dusman[i].parca[4];
		sahne[dusman[i].X  ][dusman[i].Y + 2] = dusman[i].parca[5];
		sahne[dusman[i].X+2][dusman[i].Y + 3] = dusman[i].parca[6];
		sahne[dusman[i].X+1][dusman[i].Y + 3] = dusman[i].parca[7];
		sahne[dusman[i].X  ][dusman[i].Y + 3] = dusman[i].parca[8];
	}	
}

void ekrandanCikanDusmanlar()
{
	for (int i = pasifDusmanSayisi; i < aktifDusmanSayisi; i++)
	{
		if (dusman[i].X > 88)
			pasifDusmanSayisi++;
	}
}

void dusmanSayisiKontrol()
{
	if (dusman[aktifDusmanSayisi].X<62) 
	{
		aktifDusmanSayisi++;


		dusman[aktifDusmanSayisi].Y = rand() % 13 + 3;

	}
}

void dusmanIlerlet()
{

	for (int i = pasifDusmanSayisi; i < aktifDusmanSayisi+1; i++)
		dusman[i].X--;

}


//																	ATES FONKIYONLARI


void atesleriCiz()
{
	for (int i = pasifAtesSayisi; i < aktifAtesSayisi ; i++)
	{
		sahne[ates[i].X][ates[i].Y] = ates[i].mermi;
	
	}
}

void ekrandanCikanAtesler()
{

	for (int i = pasifAtesSayisi; i < aktifAtesSayisi; i++)
	{
		if (ates[i].X > 88)
			pasifAtesSayisi++;
	}
}

void atesIlerlet()
{
	for (int i = pasifAtesSayisi; i < aktifAtesSayisi + 1; i++)
		ates[i].X++;

}

void atesDusmaniVurdu()
{	
	
		for(int i=pasifAtesSayisi;i<aktifAtesSayisi;i++)
			for(int j=pasifDusmanSayisi;j<aktifDusmanSayisi;j++)
			{
				if (ates[i].X >= (dusman[j].X + 2) && ates[i].Y == dusman[j].Y+1 )
				{
					ates[i] = ates[pasifAtesSayisi + 1];
					dusman[j] = dusman[pasifDusmanSayisi + 1];
					pasifAtesSayisi++;
					pasifDusmanSayisi++;
				}
				if (ates[i].X >= (dusman[j].X + 2) && ates[i].Y == dusman[j].Y+2 )
				{
					ates[i] = ates[pasifAtesSayisi + 1];
					dusman[j] = dusman[pasifDusmanSayisi + 1];
					pasifAtesSayisi++;
					pasifDusmanSayisi++;
				}
				if (ates[i].X >= (dusman[j].X + 2) && ates[i].Y == dusman[j].Y+3 )
				{
					ates[i] = ates[pasifAtesSayisi + 1];
					dusman[j] = dusman[pasifDusmanSayisi + 1];
					pasifAtesSayisi++;
					pasifDusmanSayisi++;
				}
			}
	
}


void klavyeOku(char tuslar[])
{
	for (int x = 0; x < 256; x++)
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
}

void klavyeKontrol()
{
	klavyeOku(tuslar);

	/*if (tuslar['W'] != 0)
	{
		ucak.Y--;
	}
	if (tuslar['S'] != 0)
	{
		ucak.Y++;
	}*/

}



int main()
{
	
	srand(time(NULL));
	

	while (true) 
	{
		if (tuslar['W'] != 0)
		{
			ucak.Y--;
		}

		if (tuslar['S'] != 0)
		{
			ucak.Y++;
		}

		if (tuslar['F'] != 0)
		{
			aktifAtesSayisi++;
			ates[aktifAtesSayisi-1].Y = ucak.Y;
			ates[aktifAtesSayisi - 1].X = 4;
		}

		sahneyiTemizle();
		sinirlariOlustur();
		klavyeKontrol();

		ucakYerlestir(ucak);


		dusmanlariCiz();
		dusmanSayisiKontrol();
		ekrandanCikanDusmanlar();
		dusmanIlerlet();


		atesleriCiz();
		atesIlerlet();
		ekrandanCikanAtesler();
		atesDusmaniVurdu();
		
		
		gotoxy(0, 0);
		kursoruGizle();
		sahneyiCiz();
	}
	

	system("pause");
	return 0;
}
