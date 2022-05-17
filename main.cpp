#include <iostream>
#include "Tablero.h"
#include "list"


using namespace std;

bool MovimientoValido(char LetraO, int ColumnaO, char LetraD, int ColumnaD ,char color, Tablero actual)
{
    if (actual.Color(LetraO,ColumnaO)!=color)
        return false;

    int i=LetraO-64;//la A es el 1
    int j=LetraD-64;

    if ((i>10)||(ColumnaO>10)||(j<1)||(ColumnaD<1)||(i<1)||(ColumnaO<1)||(j>10)||(ColumnaD>10))
        return false;

    char aux;

    if((i!=j)&&(ColumnaO!=ColumnaD))//verifica que sea un movimiento valido reina
        {
            if((i<j)&&(ColumnaO<ColumnaD)&&((i-j)!=(ColumnaO-ColumnaD)))//verificar todas las diagonales
                return false;
            if((i<j)&&(ColumnaO>ColumnaD)&&((i-j)!=(ColumnaD-ColumnaO)))
                return false;
            if((i>j)&&(ColumnaO<ColumnaD)&&((j-i)!=(ColumnaO-ColumnaD)))
                return false;
            if((i>j)&&(ColumnaO>ColumnaD)&&((i-j)!=(ColumnaO-ColumnaD)))
                return false;
        }

    if(LetraO<LetraD)
    {
        if(ColumnaO<ColumnaD)
            for(int k=i+1;k<=j;k++)//diagonal 14
            {
                aux=k+64;
                if (actual.Color(aux,ColumnaO+k-i)!='-')
                    return false;
            }
        else
            if(ColumnaD<ColumnaO)//Diagonal 32
                for(int k=i+1;k<=j;k++)
                {
                    aux=k+64;
                    if (actual.Color(aux,ColumnaO-k+i)!='-')
                        return false;
                }
            else
                for(int k=i+1;k<=j;k++)//solo hacia la derecha
                {
                    aux=k+64;
                    if (actual.Color(aux,ColumnaO)!='-')
                        return false;
                }
    }
    else
    {

        if(LetraD<LetraO)
            if(ColumnaO<ColumnaD)
                for(int k=i-1;k>=j;k--)//diagonal 23
                {
                    aux=k+64;
                    if (actual.Color(aux,ColumnaO-k+i)!='-')
                        return false;
                }
            else
                if(ColumnaD<ColumnaO)
                    for(int k=i-1;k>=j;k--)//Diagonal 41
                    {
                        aux=k+64;
                        if (actual.Color(aux,ColumnaO+k-i)!='-')
                            return false;
                    }
                else
                    for(int k=i-1;k>=j;k--)//solo hacia la izquierda
                    {
                        aux=k+64;
                        if (actual.Color(aux,ColumnaO)!='-')
                            return false;
                    }
        else
            if(ColumnaO<ColumnaD)//hacia abajo
                for(int k=ColumnaO+1;k<=ColumnaD;k++)
                {
                    aux=i+64;
                    if(actual.Color(aux,k)!='-')
                        return false;
                }
            else
                if(ColumnaD<ColumnaO)//hacia arriba
                    for(int k=ColumnaO-1;k>=ColumnaD;k--)
                    {
                        aux=i+64;
                        if(actual.Color(aux,k)!='-')
                            return false;
                    }
                else
                    return false;
    }

    return true;
}

void MostrarTablero(Tablero objeto)
{
    cout <<' '<<' '<<' '<<'A'<<' '<<'B'<<' '<<'C'<<' '<<'D'<<' '<<'E'<<' '<<'F'<<' '<<'G'<<' '<<'H'<<' '<<'I'<<' '<<'J'<<endl;
    int i;
    for( i=1 ; i<11;i++)
    {
        if (i==10)
            cout <<i<<' ';
        else
            cout<<' ' <<i<<' ';
        for (int j=0;j<10;j++)
        {
            char aux=j+65;
            cout <<objeto.Color(aux , i )<<' ';
        }
        cout<<endl;
    }

}

int PuntuoCasillero(Tablero actual,const char LetraO, const int FilaO )
{
    int valor=0;
    int i=LetraO-64;//A vale 1
    for(int k=i+1;(k<=10);k++)//solo hacia la derecha
        if (actual.Color(k+64,FilaO)=='-')
            valor++;
        else
            k=11;
    for(int k=i+1;(k<=10);k++)//diagonal 14
        if ((FilaO+k-i)<=10)
            if(actual.Color(k+64,FilaO+k-i)=='-')
                valor++;
            else
                k=11;
        else
            k=11;
    for(int k=FilaO+1;(k<=10);k++)//solo hacia abajo
        if (actual.Color(LetraO,k)=='-')
            valor++;
        else
            k=11;
    for(int k=FilaO+1;(k<=10);k++)//diagonal 23
        if ((i-k+FilaO)>0)
            if(actual.Color(i+64-k+FilaO,k)=='-')
                valor++;
            else
                k=11;
        else
            k=11;
    for(int k=i-1;(k>0);k--)//solo hacia la izquierda
        if (actual.Color(k+64,FilaO)=='-')
            valor++;
        else
            k=-1;
    for(int k=i-1;(k>0);k--)//diagonal 41
        if ((FilaO+k-i)>0)
            if(actual.Color(k+64,FilaO+k-i)=='-')
                valor++;
            else
                k=-1;
        else
            k=-1;
    for(int k=FilaO-1;(k>0);k--)//solo hacia la arriba
        if (actual.Color(LetraO,k)=='-')
            valor++;
        else
            k=-1;
    for(int k=FilaO-1;(k>0);k--)//diagonal 32
        if (FilaO-k+i<11)
            if(actual.Color(FilaO-k+i+64,k)=='-')
                valor++;
            else
                k=-1;
        else
            k=-1;
    return valor;
}

int PuntuoCasilleroProximidad(Tablero actual,const char LetraO, const int F )
{
    int valor = 0;
    int C=LetraO-64;
    struct indices
    {
        int x;
        int y;
    };
    indices *aux = new indices[24];
    aux[0].x = -1;
    aux[0].y = 0;
    aux[1].x = -1;
    aux[1].y = -1;
    aux[2].x = 0;
    aux[2].y = -1;
    aux[3].x = 1;
    aux[3].y = -1;
    aux[4].x = 1;
    aux[4].y = 0;
    aux[5].x = 1;
    aux[5].y = 1;
    aux[6].x = 0;
    aux[6].y = 1;
    aux[7].x = -1;
    aux[7].y = 1;
    aux[8].x = -2;
    aux[8].y = 1;
    aux[9].x = -2;
    aux[9].y = 0;
    aux[10].x = -2;
    aux[10].y = -1;
    aux[11].x = -2;
    aux[11].y = -2;
    aux[12].x = -1;
    aux[12].y = -2;
    aux[13].x = 0;
    aux[13].y = -2;
    aux[14].x = 1;
    aux[14].y = -2;
    aux[15].x = 2;
    aux[15].y = -2;
    aux[16].x = 2;
    aux[16].y = -1;
    aux[17].x = 2;
    aux[17].y = 0;
    aux[18].x = 2;
    aux[18].y = 1;
    aux[19].x = 2;
    aux[19].y = 2;
    aux[20].x = 1;
    aux[20].y = 2;
    aux[21].x = 0;
    aux[21].y = 2;
    aux[22].x = -1;
    aux[22].y = 2;
    aux[23].x = -2;
    aux[23].y = 2;
    for(int i=0;i<24;i++)
    {
        int nuevax = C+aux[i].x;
        int nuevay = F+aux[i].y;
        if(nuevax>0 && nuevax<11 && nuevay>0 && nuevay<11)
        {
            if (actual.Color(nuevax+64,nuevay)=='-')
                valor++;
            else
                if(actual.Color(nuevax+64,nuevay)=='X')
                    valor--;
                else
                    valor=valor-2;
        }
        else
            valor--;
    }
    return valor;
}

void TodosLosMovimiento(Tablero actual,const char LetraO, const int FilaO ,list < pair <char, int> > & aux  )
{
    int i=LetraO-64;//A vale 1
    for(int k=i+1;(k<=10);k++)//solo hacia la derecha
        if (actual.Color(k+64,FilaO)=='-')
            {
                pair <char, int> par;
                par=make_pair(k+64,FilaO);
                aux.push_back(par);
            }
        else
            k=11;
    for(int k=i+1;(k<=10);k++)//diagonal 14
        if ((FilaO+k-i)<=10)
            if(actual.Color(k+64,FilaO+k-i)=='-')
            {
                pair <char, int> par;
                par=make_pair(k+64,FilaO+k-i);
                aux.push_back(par);
            }
            else
                k=11;
        else
            k=11;
    for(int k=FilaO+1;(k<=10);k++)//solo hacia abajo
        if (actual.Color(LetraO,k)=='-')
        {
            pair <char, int> par;
            par=make_pair(LetraO,k);
            aux.push_back(par);
        }
        else
            k=11;
    for(int k=FilaO+1;(k<=10);k++)//diagonal 23
        if ((i-k+FilaO)>0)
            if(actual.Color(i+64-k+FilaO,k)=='-')
            {
                pair <char, int> par;
                par=make_pair(i+64-k+FilaO,k);
                aux.push_back(par);
            }
            else
                k=11;
        else
            k=11;
    for(int k=i-1;(k>0);k--)//solo hacia la izquierda
        if (actual.Color(k+64,FilaO)=='-')
        {
            pair <char, int> par;
            par=make_pair(k+64,FilaO);
            aux.push_back(par);
        }
        else
            k=-1;
    for(int k=i-1;(k>0);k--)//diagonal 41
        if ((FilaO+k-i)>0)
            if(actual.Color(k+64,FilaO+k-i)=='-')
            {
                pair <char, int> par;
                par=make_pair(k+64,FilaO+k-i);
                aux.push_back(par);
            }
            else
                k=-1;
        else
            k=-1;
    for(int k=FilaO-1;(k>0);k--)//solo hacia la arriba
        if (actual.Color(LetraO,k)=='-')
        {
            pair <char, int> par;
            par=make_pair(LetraO,k);
            aux.push_back(par);
        }
        else
            k=-1;
    for(int k=FilaO-1;(k>0);k--)//diagonal 32
        if(FilaO-k+i<11)
            if(actual.Color(FilaO-k+i+64,k)=='-')
            {
                pair <char, int> par;
                par=make_pair(FilaO-k+i+64,k);
                aux.push_back(par);
            }
            else
                k=-1;
        else
            k=-1;
}

int ValuacionPC(Tablero actual,char jugador)
{
    int valor=0;
    for (int i=0; i<4;i++)
    {
        char aux1;
        int aux2;
        actual.DameFicha(aux1,aux2,jugador,i);
        valor=valor+PuntuoCasillero(actual,aux1,aux2);
    }
    return valor;
}

int ValuacionPCP(Tablero actual,char jugador)
{
    int valor=0;
    for (int i=0; i<4;i++)
    {
        char aux1;
        int aux2;
        actual.DameFicha(aux1,aux2,jugador,i);
        valor=valor+PuntuoCasilleroProximidad(actual,aux1,aux2);
    }
    return valor;
}


int NegaMax(Tablero actual, int profundidad,int profundidadMAX, int alpha, int beta, char jugador,int& mejorFR, char& mejorCR,int& mejorFD, char& mejorCD,int& reina,int heuristica)
{
    if ((profundidad==0)||(actual.GameOver(jugador)==true))
        if (heuristica==1)
            if(jugador=='R')
                return (ValuacionPC(actual,'R')-(ValuacionPC(actual,'A')));
            else
                return (ValuacionPC(actual,'A')-(ValuacionPC(actual,'R')));
        else
            if(jugador=='R')
                return (ValuacionPCP(actual,'R')-(ValuacionPCP(actual,'A')));
            else
                return (ValuacionPCP(actual,'A')-(ValuacionPCP(actual,'R')));
    else
    {
        int maximo=INT_MIN;
        list < pair <char, int> > ListaF;
        list < pair <char, int> > ListaD;
        for (int i=0; i<4;i++)
        {
            char aux1;
            int aux2;
            actual.DameFicha(aux1,aux2,jugador,i);
            TodosLosMovimiento(actual,aux1,aux2,ListaF);
            list< pair <char, int> >::const_iterator itF=ListaF.begin();
            while(itF!=ListaF.end())
            {
                    actual.MoverFicha(aux1,aux2,itF->first,itF->second);
                    TodosLosMovimiento(actual,itF->first,itF->second,ListaD);
                    list< pair <char, int> >::const_iterator itD=ListaD.begin();
                    while(itD!=ListaD.end())
                    {
                        actual.Disparo(itD->first,itD->second);
                        char ficha;
                        if (jugador=='R')
                            ficha='A';
                        else
                            ficha='R';
                        int valor=-NegaMax(actual,profundidad-1,profundidadMAX,beta*-1,alpha*-1,ficha,mejorFR ,mejorCR ,mejorFD ,mejorCD,reina, heuristica);
                        if (valor>maximo)
                        {
                            if (profundidad==profundidadMAX)
                            {
                                mejorCR=itF->first;
                                mejorFR=itF->second;
                                mejorFD=itD->second;
                                mejorCD=itD->first;
                                reina=i;
                            }
                            maximo=valor;
                        }
                        if (valor>alpha)
                            alpha=valor;
                        if (alpha>=beta)
                        {
                            actual.QuitarDisparo(itD->first,itD->second);
                            actual.MoverFicha(itF->first,itF->second,aux1,aux2);
                            ListaD.clear();
                            ListaF.clear();
                            return alpha;
                        }
                        actual.QuitarDisparo(itD->first,itD->second);
                        itD++;
                    }
                    ListaD.clear();
                    actual.MoverFicha(itF->first,itF->second,aux1,aux2);
                    itF++;
            }
            ListaF.clear();
        }
    }
    return alpha;
}

void Jugar(Tablero actual, int profundidad, int heuristica)
{
    char xo,xd;
    int yo,yd;
    bool valido;
    cout<<"El usuario es jugador AZUL"<<endl;
    while (!actual.GameOver('A') && !actual.GameOver('R'))
    {
        valido = false;
        cout << "TURNO JUGADOR" << endl;
        cout << endl;
        MostrarTablero(actual);
        while (!valido)//movimiento de reina
        {
            cout << "Ingrese las coordenadas de la reina que desee mover (primero letra mayuscula, luego numero):"<<endl;
            cin >> xo>>yo;
            cout << "Ingrese las coordenadas a donde desee mover la reina:"<<endl;
            cin >> xd>>yd;
            cout << endl;
            if (MovimientoValido(xo,yo,xd,yd,'A',actual))
                valido = true;
            else{
                cout << "Los datos ingresados son invalidos, intentalo nuevamente." << endl;
                cout << endl;
            }
        }
        actual.MoverFicha(xo,yo,xd,yd);
        MostrarTablero(actual);
        while (valido)//disparo
        {
            cout <<"Ingrese las coordenadas a donde desee disparar la flecha:"<<endl;
            cin >> xo>>yo;
            cout << endl;
            if (MovimientoValido(xd,yd,xo,yo,'A',actual))
                valido = false;
            else{
                cout <<"Los datos ingresados son invalidos, intentalo nuevamente."<< endl;
                cout << endl;
            }
        }
        actual.Disparo(xo,yo);
        MostrarTablero(actual);
        if (!actual.GameOver('A'))
            if(!actual.GameOver('R'))
            {
                cout << "TURNO COMPUTADORA"<< endl;
                int alpha=INT_MIN+1;
                int beta=INT_MAX-1;
                char mejorCR='a';
                int mejorFR=0;
                int mejorFD=0;
                char mejorCD='a';
                int reina=-1;
                int i=0;
                i=NegaMax(actual,profundidad,profundidad,alpha,beta,'R',mejorFR,mejorCR,mejorFD,mejorCD,reina,heuristica);
                int origenF=0;
                char origenC='a';
                actual.DameFicha(origenC,origenF,'R',reina);
                actual.MoverFicha(origenC,origenF,mejorCR,mejorFR);
                actual.Disparo(mejorCD,mejorFD);
                if (actual.GameOver('A')==true)
                {
                    cout <<"Has perdido." << endl;
                    MostrarTablero(actual);
                }
                if(actual.GameOver('R')==true)
                {
                    MostrarTablero(actual);
                    cout <<"¡Felicidades! Has ganado." << endl;
                }
            }
            else
            {
                MostrarTablero(actual);
                cout <<"¡Felicidades! Has ganado." << endl;
            }
        else
        {
            MostrarTablero(actual);
            cout <<"Has perdido." << endl;
        }
    }
}






int main()
{

    Tablero a;
    bool j=false;
    int i=0;
    while (j==false)
    {
        cout<<"ingrese la heuristica contra la que desea jugar (1 o 2):"<< endl;
        cin>>i;
        if (i!=1)
            if (i!=2)
                cout<<"ingrese un valor valido (1 o 2):"<< endl;
            else
                j=true;
        else
            j=true;
    }
    j=false;
    int k=0;
    while (j==false)
    {
        cout<<"ingrese la profundidad contra la que desea jugar:"<< endl;
        cin>>k;
        if (k<=0)
            cout<<"ingrese un valor valido (positivo):"<< endl;
        else
            j=true;
    }
    Jugar(a,k,i);
    return 0;
}
