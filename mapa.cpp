#include "mapa.h"
#include <ctime>
#include <cstdlib>

mapa::mapa(int filas, int columnas) : filas(filas), columnas(columnas) {
    matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }
}

mapa::~mapa() {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void mapa::generarMatriz() {
    srand(time(nullptr));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1) {
                matriz[i][j] = 1;
            } else if (i % 2 == 0 && j % 2 == 0) {
                matriz[i][j] = 1;
            } else if ((i == 1 && (j == 1 || j == 2)) ||
                       (j == 1 && i == 2) ||
                       (i == filas - 2 && (j == columnas - 3 || j == columnas - 2)) ||
                       (i == filas - 3 && j == columnas - 2)) {
                matriz[i][j] = 0;
            } else {
                matriz[i][j] = rand() % 2 + 2; // 2 o 3 (libre o destruible)
            }
        }
    }
}

void mapa::dibujarMatriz(QGraphicsScene* scene, const QPixmap& Solido, const QPixmap& Destruible) {
    int tileSize = 50;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int x = j * tileSize;
            int y = i * tileSize;

            if (matriz[i][j] == 1) {
                scene->addPixmap(Solido.scaled(tileSize, tileSize))->setPos(x, y);
            } else if (matriz[i][j] == 3) {
                scene->addPixmap(Destruible.scaled(tileSize, tileSize))->setPos(x, y);
            }
        }
    }
}
bool mapa::esEspacioLibre(int x, int y) {

    int i = y / 50;
    int j = x / 50;

    if (i < 0 || i >= filas || j < 0 || j >= columnas) {
        return false;
    }

    return matriz[i][j] == 0;
}
