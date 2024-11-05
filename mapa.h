#ifndef MAPA_H
#define MAPA_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class mapa {
public:
    mapa(int filas, int columnas);
    ~mapa();

    void generarMatriz();
    void dibujarMatriz(QGraphicsScene* scene, const QPixmap& Solido, const QPixmap& Destruible);
    bool esEspacioLibre(int x, int y);

private:
    int filas;
    int columnas;
    int** matriz;
};

#endif // MAPA_H
