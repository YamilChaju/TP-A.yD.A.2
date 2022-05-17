#include "Tablero.h"



Tablero::Tablero()//considerar que a donde dice columnasX debe decir Fila X
{
    Matriz = new char*[10];
    for(int i=0;i<10;i++)
    {
        Matriz[i] = new char [10];
        for (int j=0;j<10;j++)
            Matriz[i][j]='-';
    }
    this->PonerFicha('A',4,'R');
    this->PonerFicha('D',1,'R');
    this->PonerFicha('G',1,'R');
    this->PonerFicha('J',4,'R');
    this->PonerFicha('A',7,'A');
    this->PonerFicha('D',10,'A');
    this->PonerFicha('G',10,'A');
    this->PonerFicha('J',7,'A');

    Dimension=10;


    Reinaroja = new posreina[4];
    Reinaroja[0].x=0;
    Reinaroja[0].y=3;
    Reinaroja[1].x=3;
    Reinaroja[1].y=0;
    Reinaroja[2].x=6;
    Reinaroja[2].y=0;
    Reinaroja[3].x=9;
    Reinaroja[3].y=3;

    Reinaazul = new posreina[4];
    Reinaazul[0].x=0;
    Reinaazul[0].y=6;
    Reinaazul[1].x=3;
    Reinaazul[1].y=9;
    Reinaazul[2].x=6;
    Reinaazul[2].y=9;
    Reinaazul[3].x=9;
    Reinaazul[3].y=6;

}

Tablero::~Tablero()
{
    //dtor
}

char Tablero::Color(char LetraO, int ColumnaO)
{
    int n =(LetraO - 65);//para letras minusculas -97
    return Matriz[n][ColumnaO-1];
}

void Tablero::MoverFicha(char LetraO, int ColumnaO, char LetraD, int ColumnaD)//no contola que se caiga fuera del tablero
{
    int n =(LetraO - 65);
    char aux = this->Color(LetraO , ColumnaO);
    Matriz[n][ColumnaO-1]='-';

    int i=0;
    bool encotrada=false;
    while ((encotrada==false)&&(i<4))
    {
        if (aux=='R')
        {
            if ((Reinaroja[i].x==n)&&(Reinaroja[i].y==ColumnaO-1))
                encotrada=true;
            i++;
        }
        if (aux=='A')
        {
            if ((Reinaazul[i].x==n)&&(Reinaazul[i].y==ColumnaO-1))
                encotrada=true;
            i++;
        }
    }

    n =(LetraD - 65);
    Matriz[n][ColumnaD-1]=aux;

    if (aux=='A')
    {
        Reinaazul[i-1].x=n;
        Reinaazul[i-1].y=ColumnaD-1;
    }
    if (aux=='R')
    {
        Reinaroja[i-1].x=n;
        Reinaroja[i-1].y=ColumnaD-1;
    }

}

bool Tablero::GameOver(char color)
{
    int x,y;
    for(int i=0;i<4;i++)
    {
        if (color=='R')
        {
            x = Reinaroja[i].x;
            y = Reinaroja[i].y;
        }
        else
        {
            x = Reinaazul[i].x;
            y = Reinaazul[i].y;
        }
        if (((x-1)>=0) && (Matriz[x-1][y]=='-'))
            return false;
        if (((x+1)<=9) && (Matriz[x+1][y]=='-'))
            return false;
        if (((y-1)>=0) && (Matriz[x][y-1]=='-'))
            return false;
        if (((y+1)<=9) && (Matriz[x][y+1]=='-'))
            return false;
        if (((y+1)<=9) && ((x-1)>=0) && (Matriz[x-1][y+1]=='-'))
            return false;
        if (((y+1)<=9) && ((x+1)<=9) && (Matriz[x+1][y+1]=='-'))
            return false;
        if (((y-1)>=0) && ((x+1)<=9) && (Matriz[x+1][y-1]=='-'))
            return false;
        if (((y-1)>=0) && ((x-1)>=0) && (Matriz[x-1][y-1]=='-'))
            return false;
    }
    return true;
}

void Tablero::Disparo(char LetraD, int ColumnaD)
{
    int n =(LetraD - 65);
    Matriz[n][ColumnaD-1]='X';
}

void Tablero::PonerFicha(char LetraD, int ColumnaD, char Reina)
{
    int n =(LetraD - 65);
    Matriz[n][ColumnaD-1]=Reina;
}

void Tablero::DameFicha(char & Letra, int & Fila,char color, int numero)//solo hacepta de 0 a 3
{
    if ((numero>=0)&&(numero<4))
    {
        if (color=='R')
        {
            Letra=Reinaroja[numero].x+65;
            Fila=Reinaroja[numero].y+1;
        }
        else
        {
            Letra=Reinaazul[numero].x+65;
            Fila=Reinaazul[numero].y+1;
        }
    }
}

void Tablero::QuitarDisparo(char LetraD, int ColumnaD)
{
    int n =(LetraD - 65);
    Matriz[n][ColumnaD-1]='-';
}


