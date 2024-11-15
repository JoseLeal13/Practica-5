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

void mapa::explosionBomba(int x, int y, QGraphicsScene* scene) {
    int posiciones[] = {-1, 1, 0, 0}; // Arriba, Abajo, Izquierda, Derecha
    int posicionesY[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = x + posiciones[i];
        int ny = y + posicionesY[i];

        if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas) {
            if (matriz[nx][ny] == 3) {  // Si el bloque es destruible
                matriz[nx][ny] = 0;

                QList<QGraphicsItem*> items = scene->items(QRectF(ny * 50, nx * 50, 50, 50));
                for (QGraphicsItem* item : items) {
                    if (item->scene() == scene && item->type() == QGraphicsPixmapItem::Type) {
                        scene->removeItem(item);
                        delete item;
                    }
                }
            }
        }
    }
}



int** mapa::getmatriz(){

    return matriz;
}

Puerta* mapa::colocarPuertaAleatoria(QGraphicsScene* scene, const QPixmap& pixmapPuerta) {
    srand(time(nullptr));

    int i, j;
    do {
        i = rand() % filas;
        j = rand() % columnas;
    } while (matriz[i][j] != 3);  // Encuentra un bloque destruible al azar

    // Crear la puerta con tamaño de 45x45
    Puerta* puerta = new Puerta(pixmapPuerta.scaled(45, 45)); // Redimensiona la puerta a 45x45
    // Colocarla debajo del bloque destruible (ajustar la posición en el eje Y)
    puerta->setPos(j * 50, i * 50 + 5); // 5 píxeles más abajo para que quede debajo

    scene->addItem(puerta);

    return puerta; // Devuelve la puerta para que otro código maneje la conexión
}



/*
bool mapa::esEspacioLibre(int x, int y) {

    int i = y / 50;
    int j = x / 50;

    if (i < 0 || i >= filas || j < 0 || j >= columnas) {
        return false;
    }

    return matriz[i][j] == 0;
}
*/
