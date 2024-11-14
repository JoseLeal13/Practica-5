#ifndef MAPA_H
#define MAPA_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "control.h"

class mapa {
public:
    mapa(int filas, int columnas);
    ~mapa();

    void generarMatriz();
    void dibujarMatriz(QGraphicsScene* scene, const QPixmap& Solido, const QPixmap& Destruible);
    bool esEspacioLibre(int x, int y);
    int **getmatriz();

    void explosionBomba(int x, int y, QGraphicsScene* scene, const QPixmap& Destruible);
    void colocarPuertaAleatoria(QGraphicsScene* scene, const QPixmap& pixmapPuerta);

private:
    int filas;
    int columnas;
    int** matriz;


};

#endif // MAPA_H
