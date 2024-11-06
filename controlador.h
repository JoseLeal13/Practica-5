#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include "mapa.h"

class Controlador
{
public:
    Controlador();
    ~Controlador();

    void dibujar(QGraphicsScene* scene, const QPixmap& Solido, const QPixmap& Destruible);
    void CambiarNivel();

private:
    mapa *oMapa;
};

#endif // CONTROLADOR_H
