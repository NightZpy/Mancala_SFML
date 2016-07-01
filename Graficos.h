#ifndef GRAFICOS_H
#define GRAFICOS_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Cuadros.h"

using namespace std;

class Graficos
{
    public:
        Graficos(float xSub, float ySub, float anchoSub, float altoSub);

        void cargarImagenes(float ancho, float altoDeposito, float altoMancala, sf::String texto);

        sf::Image fondoImg, depositoImg[2], mancalaImg[2];
        sf::Sprite fondo;
        Cuadros depositos[2][6], mancala[2];
        sf::Rect<float> subTablero;

};

Graficos::Graficos(float xSub, float ySub, float anchoSub, float altoSub)
{
    sf::Rect<float> rect(xSub, ySub, xSub+anchoSub, ySub+altoSub);
    Graficos::subTablero = rect;
}

void Graficos::cargarImagenes(float ancho, float altoDeposito, float altoMancala, sf::String texto)
{
    if(!fondoImg.LoadFromFile("imagenes/Fondo_Tablero.jpg"))
    {
            cout<<endl<<"No se pudo cargar el fondo.";
            //ventana->Close();
    }
    if(!depositoImg[0].LoadFromFile("imagenes/deposito0.jpg"))
    {
            cout<<endl<<"No se pudo cargar el deposito0.jpg.";
            //ventana->Close();
    }
    if(!depositoImg[1].LoadFromFile("imagenes/deposito1.jpg"))
    {
            cout<<endl<<"No se pudo cargar el deposito1.jpg.";
            //ventana->Close();
    }
    if(!mancalaImg[0].LoadFromFile("imagenes/mancala0.jpg"))
    {
            cout<<endl<<"No se pudo cargar el mancala0.jpg.";
            //ventana->Close();
    }
    if(!mancalaImg[1].LoadFromFile("imagenes/mancala1.jpg"))
    {
            cout<<endl<<"No se pudo cargar el mancala1.jpg.";
            //ventana->Close();
    }

    fondo.SetImage(fondoImg);

    mancala[0].sprite.SetImage(mancalaImg[1]);
    mancala[0].x = subTablero.Left + 5;
    mancala[0].y = subTablero.Top  + 10;
    mancala[0].ancho = ancho;
    mancala[0].alto = altoMancala;
    mancala[0].xMax = mancala[0].x + ancho;
    mancala[0].yMax =  mancala[0].y + altoMancala;
    mancala[0].valor = texto;
    mancala[0].valor.SetText("0");
    mancala[0].sprite.SetX(mancala[0].x);
    mancala[0].sprite.SetY(mancala[0].y);
    mancala[0].calcularCoord();

    mancala[1].sprite.SetImage(mancalaImg[0]);
    mancala[1].x = (subTablero.Left + subTablero.GetWidth()) - (ancho + 5);
    mancala[1].y = subTablero.Top + 10;
    mancala[1].ancho = ancho;
    mancala[1].alto = altoMancala;
    mancala[1].xMax = mancala[1].x + ancho;
    mancala[1].yMax =  mancala[1].y + altoMancala;
    mancala[1].valor = texto;
    mancala[1].valor.SetText("0");
    mancala[1].sprite.SetX(mancala[1].x);
    mancala[1].sprite.SetY(mancala[1].y);
    mancala[1].calcularCoord();

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(j==0 && i==0)
            {
                depositos[i][j].sprite.SetImage(depositoImg[i]);
                depositos[i][j].x = mancala[0].xMax + 5;
                depositos[i][j].y = mancala[0].y;
                depositos[i][j].ancho = ancho;
                depositos[i][j].alto = altoDeposito;
                depositos[i][j].xMax = depositos[i][j].x + ancho;
                depositos[i][j].yMax =  depositos[i][j].y + altoDeposito;
                depositos[i][j].valor = texto;
                depositos[i][j].valor.SetText("4");
                depositos[i][j].sprite.SetX(depositos[i][j].x);
                depositos[i][j].sprite.SetY(depositos[i][j].y);
                depositos[i][j].calcularCoord();
            }

            if(j==0 && i==1)
            {
                depositos[i][j].sprite.SetImage(depositoImg[i]);
                depositos[i][j].x = mancala[0].xMax + 5;
                depositos[i][j].y = depositos[0][0].yMax + 10;
                depositos[i][j].ancho = ancho;
                depositos[i][j].alto = altoDeposito;
                depositos[i][j].xMax = depositos[i][j].x + ancho;
                depositos[i][j].yMax =  depositos[i][j].y + altoDeposito;
                depositos[i][j].valor = texto;
                depositos[i][j].valor.SetText("4");
                depositos[i][j].sprite.SetX(depositos[i][j].x);
                depositos[i][j].sprite.SetY(depositos[i][j].y);
                depositos[i][j].calcularCoord();

            }

            if(j>0)
            {
                if(i==0)
                {
                    depositos[i][j].sprite.SetImage(depositoImg[i]);
                    depositos[i][j].x = depositos[i][j-1].xMax + 5;
                    depositos[i][j].y = mancala[0].y;
                    depositos[i][j].ancho = ancho;
                    depositos[i][j].alto = altoDeposito;
                    depositos[i][j].xMax = depositos[i][j].x + ancho;
                    depositos[i][j].yMax =  depositos[i][j].y + altoDeposito;
                    depositos[i][j].valor = texto;
                    depositos[i][j].valor.SetText("4");
                    depositos[i][j].sprite.SetX(depositos[i][j].x);
                    depositos[i][j].sprite.SetY(depositos[i][j].y);
                    depositos[i][j].calcularCoord();
                }
                else
                {
                    depositos[i][j].sprite.SetImage(depositoImg[i]);
                    depositos[i][j].x = depositos[i][j-1].xMax + 5;
                    depositos[i][j].y = depositos[0][0].yMax + 10;
                    depositos[i][j].ancho = ancho;
                    depositos[i][j].alto = altoDeposito;
                    depositos[i][j].xMax = depositos[i][j].x + ancho;
                    depositos[i][j].yMax =  depositos[i][j].y + altoDeposito;
                    depositos[i][j].valor = texto;
                    depositos[i][j].valor.SetText("4");
                    depositos[i][j].sprite.SetX(depositos[i][j].x);
                    depositos[i][j].sprite.SetY(depositos[i][j].y);
                    depositos[i][j].calcularCoord();
                }
            }
        }
    }
}
#endif // GRAFICOS_H
