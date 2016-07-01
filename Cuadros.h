#ifndef CUADROS_H_INCLUDED
#define CUADROS_H_INCLUDED

typedef struct _CUADROS
{

        float x, y, xMax, yMax;
        float ancho, alto;
        sf::String valor;
        sf::Sprite sprite;

        bool estaDentro(float xM, float yM)
        {
            return ((xM >= x && xM <= xMax) && (yM >= y && yM <= yMax));
        }

        void calcularCoord()
        {
            xMax = x + ancho;
            yMax = y + alto;
            sf::Vector2<float> valorC = valor.GetScale();
            valor.SetX(x + ((ancho/2) - (valorC.x / 2)));
            valor.SetY(y +((alto/2)  - (valorC.y / 2)));
        }
}Cuadros;

/*void Cuadros::setDatos(sf::Image& imagen, float x, float y, float& ancho, float& alto, sf::String texto)
{
    sprite.SetImage(imagen);
    Cuadros::x = x;
    Cuadros::y = y;
    Cuadros::ancho = ancho;
    Cuadros::alto = alto;
    //Cuadros::fuente.LoadFromFile("Arial.ttf", 50);
    Cuadros::valor = texto;
    //Cuadros::valor.SetFont(fuente);
    Cuadros::valor.SetSize(50);
    //Cuadros::valor.SetFont(fuente);
    Cuadros::valor.SetColor(sf::Color::White);
    Cuadros::xMax = x + ancho;
    Cuadros::yMax = y + alto;

    sf::Vector2<float> valorC = Cuadros::valor.GetScale();
    valor.SetX((ancho/2) - (valorC.x / 2));
    valor.SetY((alto/2)  - (valorC.y / 2));
}*/

/*bool Cuadros::estaDentro(float x, float y)
{
    return ((x >= Cuadros::x && x <= Cuadros::xMax) && (y >= Cuadros::y && y <= Cuadros::yMax));
}*/

#endif // CUADROS_H_INCLUDED
