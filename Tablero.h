#ifndef TABLERO_H
#define TABLERO_H


class Tablero
{
    public:
        Tablero();
        virtual ~Tablero();
        void MoverFicha(char LetraO, int ColumnaO, char LetraD, int ColumnaD);
        char Color(char LetraO, int ColumnaO);
        void Disparo(char LetraD, int ColumnaD);
        void PonerFicha(char LetraD, int ColumnaD, char Reina);
        bool GameOver(char color);
        void DameFicha(char & Letra, int & Fila,char color, int numero);
        void QuitarDisparo(char LetraD, int ColumnaD);


    private:
        char ** Matriz;
        int Dimension;
        struct posreina
        {
            int x;
            int y;
        };
        posreina *Reinaazul;
        posreina *Reinaroja;

};

#endif // TABLERO_H
