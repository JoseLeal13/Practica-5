#include "controlador.h"

Controlador::Controlador() {

    oMapa = new mapa(15, 17);
}

Controlador::~Controlador(){

    delete oMapa;
}
void Controlador::CambiarNivel(){

    oMapa->generarMatriz();
}
void Controlador::dibujar(QGraphicsScene* scene, const QPixmap& Solido, const QPixmap& Destruible){

    oMapa->dibujarMatriz(scene, Solido, Destruible);
}
