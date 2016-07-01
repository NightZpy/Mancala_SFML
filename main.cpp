#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Graficos.h"

using namespace std;

typedef struct _JUGADOR
{
    //Identificador de la fila que usa el jugador
    int id;
    int fichas;
    char nombre[30];
}Jugador;

int tablero[8][8];
Cuadros botones[4];

void jugarHumanos(Jugador* jugador, sf::RenderWindow* ventana);
void jugarConsola(Jugador* jugador);
void mostrarTablero();

void iniciarTablero();
int movimientoBasico(int x, int y);
bool finJuego();
int ganador();
void crearMenu(Cuadros* botonera);
void dibujarTablero(sf::RenderWindow* ventana, Graficos* tablero);
void dibujarMenu(sf::RenderWindow* ventana, Cuadros* cuadros);

int main()
{
    Jugador jugador[2];
    //jugarConsola(jugador);
    sf::String texto;
    texto.SetText("algo");
    texto.SetColor(sf::Color::Black);
    sf::RenderWindow ventana(sf::VideoMode(700, 300, 32), "Mancala");
    sf::Image imagen;
    crearMenu(botones);

    bool activo = true;
    while(ventana.IsOpened() && activo)
    {
        //ventana.Clear();
        dibujarMenu(&ventana, botones);
        ventana.Display();
        sf::Event eventos;
        while (ventana.GetEvent(eventos))
        {

            if(eventos.Type == sf::Event::Closed)
            {
                activo = false;
                ventana.Close();
            }

            if((eventos.Type == sf::Event::KeyPressed) && (eventos.Key.Code == sf::Key::Escape))
            {
                activo = false;
                ventana.Close();
            }
        }

        if(ventana.GetInput().IsMouseButtonDown(sf::Mouse::Left))
        {
            if(botones[0].estaDentro(eventos.MouseMove.X, eventos.MouseMove.Y))
            {
                jugarHumanos(jugador, &ventana);
            }
            if(botones[1].estaDentro(eventos.MouseMove.X, eventos.MouseMove.Y))
            {
                //jugarMaquina();
            }
            if(botones[2].estaDentro(eventos.MouseMove.X, eventos.MouseMove.Y))
            {
                //Nivel
            }
            if(botones[3].estaDentro(eventos.MouseMove.X, eventos.MouseMove.Y))
            {
                ventana.Close();
                exit(0);
            }
        }
        ventana.Clear();
        dibujarMenu(&ventana, botones);
        ventana.Display();
    }


    return 0;
}

void jugarHumanos(Jugador* jugador, sf::RenderWindow* ventana)
{
    sf::Clock Clock;
    sf::String texto;
    texto.SetText("algo");
    Graficos tab((float)50, (float)25, (float)600, (float)250);
    tab.cargarImagenes(70, 110, 220, texto);

    iniciarTablero();
    int jugadorTurno=0;

    jugador[0].id = 0;
    jugador[1].id = 1;

    int jugada=-1;
    bool finJ=false;
    bool activo = true;
    float tiempo;
    while(ventana->IsOpened() && activo)
    {
        tiempo += Clock.GetElapsedTime();
        //cout<<"Tiempo: "<<tiempo;
        sf::Event eventos;
        int x=jugadorTurno, y=-1;
        while (ventana->GetEvent(eventos))
        {
            if(eventos.MouseButton.Button == sf::Mouse::Left)
            {
            }

            if(eventos.Type == sf::Event::Closed)
            {
                activo = false;
                ventana->Close();
            }

            if((eventos.Type == sf::Event::KeyPressed) && (eventos.Key.Code == sf::Key::Escape))
            {
                activo = false;
                ventana->Close();
            }
        }

        if(tiempo>=5)
        {
            if(jugadorTurno==0)
            {
                Clock.Reset();
                tiempo=0;
                float x=eventos.MouseMove.X, y=eventos.MouseMove.Y;
                if(ventana->GetInput().IsMouseButtonDown(sf::Mouse::Left))
                {
                    //for(int i=0; i<2; i++)
                    //{
                        for(int j=0; j<6; j++)
                        {
                            if(tab.depositos[0][j].estaDentro(x, y))
                            {

                                    char str[3];
                                    jugada = movimientoBasico(0, j+1);
                                    tab.mancala[0].valor.SetText(itoa(tablero[0][0], str, 10));
                                    tab.mancala[1].valor.SetText(itoa(tablero[1][7], str, 10));
                                    for(int i=0; i<2; i++)
                                    {
                                        for(int k=0; k<6; k++)
                                        {
                                            tab.depositos[i][k].valor.SetText(itoa(tablero[i][k+1], str, 10));
                                        }
                                    }
                                    j=6;
                            }
                        }
                    //}
                }
                if(jugada==0)
                {
                    jugadorTurno=1;
                }

            }
            else
            if(jugadorTurno==1)
            {
                Clock.Reset();
                tiempo=0;
                cout<<endl<<"TURNO 1";
                float x=eventos.MouseMove.X, y=eventos.MouseMove.Y;
                if(ventana->GetInput().IsMouseButtonDown(sf::Mouse::Left))
                {
                    cout<<endl<<"IZQUIERDO";
                        for(int j=0; j<6; j++)
                        {
                            if(tab.depositos[1][j].estaDentro(x, y))
                            {

                                    char str[3];
                                    jugada = movimientoBasico(1, j+1);
                                    tab.mancala[0].valor.SetText(itoa(tablero[0][0], str, 10));
                                    tab.mancala[1].valor.SetText(itoa(tablero[1][7], str, 10));
                                    for(int i=0; i<2; i++)
                                    {
                                        for(int k=0; k<6; k++)
                                        {
                                            tab.depositos[i][k].valor.SetText(itoa(tablero[i][k+1], str, 10));
                                        }
                                    }
                                    j=6;
                            }
                        }
                }
                cout<<"jugada: "<<jugada;
                if(jugada==0)
                {
                    jugadorTurno=0;
                }
            }
        }
        if(finJuego()) activo = false;
        ventana->Clear();
        dibujarTablero(ventana, &tab);
        ventana->Display();
    }
    ventana->Clear();
    cout<<endl<<"El ganador es: "<<ganador()+1;
}

void mostrarTablero()
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<8; j++)
        {
            cout<<" "<<tablero[i][j]<<" ";
        }
        cout<<endl;
    }
}

void iniciarTablero()
{
	tablero[0][0]=0;
	tablero[0][7]=0;

	for(int i=0; i<2; i++)
	{
		for(int j=1; j<7; j++)
		{
			tablero[i][j]=4;
		}
	}
}

bool finJuego()
{
    if(tablero[0][0]>24 || tablero[1][7]>24)
        return true;

    int cVacios=0;//Contador para saber cuando todas las celdas de un jugador estan vacias
    //Recorremos al jugador de arriba para verificar si tiene todas sus celdas vacias
    //cout<<endl<<"HACIENDO EL CONTEO PARA EL JUGADOR DE ARRIBA";
    for(int j=1; j<7; j++)
    {
        if(tablero[0][j]==0)
        {
            cVacios++;
        }
    }
    //cout<<endl<<"JUGADOR DE ARRIBA TIENE VACIOS: "<<cVacios;

    //Verificamos que las 6 celdas esten vacias
    if(cVacios==6)
    {
        //Pasamos entonces las fichas que le queden al otro jugados a su propio mancala
        for(int j=1; j<7; j++)
        {
            tablero[1][0]+=tablero[1][j];
        }
        //Retornamos verdadero=true ya que el juego si finalizo
        return true;
    }
    //Como el jugador de arriba no tenia vacias todas sus celdas verificamos el de abajo
    else
    {
        cVacios=0;
        for(int j=1; j<7; j++)
        {
            if(tablero[1][j]==0)
            {
                cVacios++;
            }
        }

        if(cVacios==6)
        {
            for(int j=1; j<7; j++)
            {
                tablero[0][0]+=tablero[0][j];
            }
            return true;
        }
    }

    //Retornamos falso=false porque el juego no finalizo
    return false;
}

int ganador()
{
    if(tablero[0][0]>tablero[1][7])
        return 0;
    else
        return 1;
}

int movimientoBasico(int x, int y)
{
    //Si el valor de retorno es: -1 (fallo), 0 (exitoso pero no repite turno), 1 (repite turno)
    int vRetorno=-1;
	//filtramos que la celda de movimiento sea válida
	if((x<0 || x>1) || (y<1 || y>6))
		return vRetorno;

    vRetorno=0;
	int i=x, j=y;//Variables para recorrer el arreglo
	int cPasos=tablero[x][y];//Variable para controlar los pasos que podemos dar
	tablero[x][y]=0;//lo pongo vacio (porque de él voy a sacar las fichas para jugarHumanos)
	cout<<endl<<"FICHAS A REPARTIR: "<<cPasos;
	do
	{
		//verifico esto para ver si me muevo hacia atrás o hacia adelante
		if(i==0)//me muevo hacia la izquierda o atras (porque es la fila de arriba
		{
		    cout<<endl<<"MOVIENDO IZQUIERDA";
			j--; //muevo la columna hacia la izquierda
			cout<<endl<<"PASO: "<<cPasos;

			cout<<endl<<"I: "<<i;
			cout<<endl<<"J: "<<j;
			if(j==0)//significa que llegue a el deposito y debo bajar a la parte del otro jugador
			{
			    cout<<endl<<"EN UN DEPOSITO";
			    //Verifico que el deposito (mancala) es el de ese jugador
			    if(x==i)
			    {
			        cout<<endl<<"ES MI DEPOSITO";
			        //Verificamos si queda 1 sola ficha (y será depositada en el mancala propio)
			        if(cPasos==1)
			        {
                        vRetorno=1;
                        cout<<endl<<"ULTIMA FICHA EN EL MANCALA PROPIO";
			        }
			        cout<<endl<<"SE DEPOSITO UNA FICHA EN MI MANCALA";
                    tablero[i][j]++; //aumento las fichas que hay en ese deposito en 1 porque pase por ahi
                    cout<<endl<<"AHORA LAS FICHAS EN MI MANCALA SON: "<<tablero[i][j];
			    }
			    i=1;//me ubico ahora en la parte del jugador de abajo (fila=1)
			    cout<<endl<<"ME MUEVO A LA FILA DE ABAJO";
			}
			else
			{
			    //Verificamos que no estamos en la misma celda de inicio
			    if(i!=x || j!=y)
			    {
			        cout<<endl<<"NO ES UN MANCALA Y NO ES LA CELDA DE INICIO";
			        //Verificamos que estamos en la fila del jugador de turno
			        if(x==i)
			        {
			            //cout<<endl<<"FILA DEL JUGADOR AL TURNO";
			            //Verificamos que la celda este vacia para la regla de tomar fichas del frente
                        if(tablero[i][j]==0 && cPasos==1)
                        {
                            cout<<endl<<"CELDA VACIA, SE TOMARAN LAS FICHAS DE LA CELDA DEL FRENTE";
                            //Tomamos las fichas del frente y la que se iba a poner, para ponerlas en el mancala propio
                            tablero[i][0] += tablero[i+1][j] + 1;
                            tablero[i+1][j] = 0;//Vaciamos la celda del frente
                        }
                        else
                        {
                            cout<<endl<<"AUMENTANDO LA CELDA EN 1";
                            tablero[i][j]++;//Sólo aumento, no hay más na que hacer
                        }

			        }
			        else
			        {
			            cout<<endl<<"AUMENTANDO LA CELDA EN 1";
                        tablero[i][j]++;//Sólo aumento, no hay más na que hacer
			        }
			    }
			}
		}
		else//hacia la derecha o adelante
		{
		    cout<<endl<<"MOVIENDO DERECHA";
			//aqui es lo mismo que arriba pero moviendose hacia la derecha (j++)
			j++;
			if(j==7)
			{
			    //Verifico que el deposito (mancala) es el de ese jugador
			    if(x==i)
			    {
			        //Verificamos si queda 1 sola ficha (y será depositada en el mancala propio)
                    if(cPasos==1)
                        vRetorno=1;
                    tablero[i][j]++; //aumento las fichas que hay en ese deposito en 1 porque pase por ahi
			    }
                i=0;//me ubico ahora en la parte del jugador de abajo (fila=1)
			}
			else
			{
			    //Verificamos que no estamos en la misma celda de inicio
			    if(i!=x || j!=y)
			    {
			        //Verificamos que estamos en la fila del jugador de turno
			        if(x==i)
			        {
			            //Verificamos que la celda este vacia para la regla de tomar fichas del frente
                        if(tablero[i][j]==0 && cPasos==1)
                        {
                            //Tomamos las fichas del frente y la que se iba a poner, para ponerlas en el mancala propio
                            tablero[i][7] += tablero[i-1][j] + 1;
                            tablero[i-1][j] = 0;//Vaciamos la celda del frente
                        }
                        else
                        {
                            cout<<endl<<"AUMENTANDO LA CELDA EN 1";
                            tablero[i][j]++;//Sólo aumento, no hay más na que hacer
                        }
			        }
			        else
			        {
                        tablero[i][j]++;//Sólo aumento, no hay más na que hacer
			        }
			    }
			}
		}
		cPasos--;//Como di un paso, pues lo resto de el contador de pasos
	}while(cPasos>0);//Se realizara el bucle cuando aún queden pasos por dar (fichas por meter)
	return vRetorno;
}

/*void jugarConsola(Jugador* jugador)
{
    int opc=0;
    do
    {
        cout<<endl<<"1.-Juego para 2 personas.";
        cout<<endl<<"2.-Juego contra la maquina.";
        cout<<endl<<"3.-Seleccionar nivel del juego.";
        cout<<endl<<"4.-Salir.";
        cin>>opc;

        switch(opc)
        {
            case 1:
                jugarHumanos(jugador);
            break;

            case 2:
                //jugarHumanosMaquina();
            break;

            case 3:
                //cambiarNivel();
            break;

            default:
                if(opc<1 || opc>4)
                    cout<<endl<<"Escoja una opcion valida...";
            break;
        }
    }while(opc!=4);
}*/

void crearMenu(Cuadros* botonera)
{
    sf::Image img;
    if(!img.LoadFromFile("imagenes/boton.jpg"))
    {
        cout<<endl<<"Error cargando boton.jpg";
        return;
    }

    sf::String textos[4];
    textos[0].SetText("Para 2");
    textos[1].SetText("Contra PC");
    textos[2].SetText("Nivel");
    textos[3].SetText("Salir");

    for(int i=0; i<4; i++)
    {
        textos[i].SetColor(sf::Color::Black);
    }

    botonera[0].sprite.SetImage(img);
    botonera[0].x = 50;
    botonera[0].y = 50;
    botonera[0].ancho = 120;
    botonera[0].alto = 90;
    botonera[0].valor = textos[0];
    botonera[0].calcularCoord();
    botonera[0].sprite.SetX(botonera[0].x);
    botonera[0].sprite.SetY(botonera[0].y);

    botonera[1].sprite.SetImage(img);
    botonera[1].x = 180;
    botonera[1].y = 50;
    botonera[1].ancho = 120;
    botonera[1].alto = 90;
    botonera[1].valor = textos[1];
    botonera[1].calcularCoord();
    botonera[1].sprite.SetX(botonera[1].x);
    botonera[1].sprite.SetY(botonera[1].y);

    botonera[2].sprite.SetImage(img);
    botonera[2].x = 50;
    botonera[2].y = 150;
    botonera[2].ancho = 120;
    botonera[2].alto = 90;
    botonera[2].valor = textos[2];
    botonera[2].calcularCoord();
    botonera[2].sprite.SetX(botonera[2].x);
    botonera[2].sprite.SetY(botonera[2].y);

    botonera[3].sprite.SetImage(img);
    botonera[3].x = 180;
    botonera[3].y = 150;
    botonera[3].ancho = 120;
    botonera[3].alto = 90;
    botonera[3].valor = textos[3];
    botonera[3].calcularCoord();
    botonera[3].sprite.SetX(botonera[3].x);
    botonera[3].sprite.SetY(botonera[3].y);
}

void dibujarMenu(sf::RenderWindow* ventana, Cuadros* cuadros)
{
    sf::Image imagen;
    if(!imagen.LoadFromFile("imagenes/Fondo_menu.jpg"))
    {
        cout<<endl<<"Error cargando Fondo_menu.jpg";
        return;
    }
    sf::Sprite fondo;
    fondo.SetImage(imagen);
    ventana->Draw(fondo);

    for(int i=0; i<4; i++)
        ventana->Draw(cuadros[i].sprite);
}

void dibujarTablero(sf::RenderWindow* ventana, Graficos* tablero)
{
        ventana->Draw(tablero->fondo);
        ventana->Draw(tablero->mancala[0].sprite);
        ventana->Draw(tablero->mancala[0].valor);
        ventana->Draw(tablero->mancala[1].sprite);
        ventana->Draw(tablero->mancala[1].valor);
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<6; j++)
            {
                ventana->Draw(tablero->depositos[i][j].sprite);
                ventana->Draw(tablero->depositos[i][j].valor);
            }
        }
}
