#include <QMessageBox>
#include "controlador.h"
#include "jugador.h"

Controlador::Controlador() {
    oMapa = new mapa(15, 17);
    oMapa->generarMatriz();  // Genera el contenido de la matriz
    jugador = new Jugador(0, 0); // Posición inicial del jugador

    connect(jugador, &Jugador::juegoPerdido, this, &Controlador::mostrarMenuPerdiste);
}

void Controlador::mostrarMenuPerdiste() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Perdiste");
    msgBox.setText("Has perdido todas tus vidas. ¿Quieres volver a intentarlo?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int resultado = msgBox.exec();
    if (resultado == QMessageBox::Yes) {
        reiniciarJuego();  // Reinicia el juego si el jugador quiere volver a intentarlo
    } else {
        // Aquí puedes cerrar el juego o volver al menú principal
    }
}

void Controlador::reiniciarJuego() {
    jugador->setVidas(3);
    CambiarNivel();
    dibujar(sceneActual, pixmapSolido, pixmapDestruible);
}
void Controlador::detectarColisiones() {
    if (puerta && jugador && puerta->collidesWithItem(jugador)) {
        emit puerta->jugadorGanado();
    }
}

void Controlador::mostrarMenuGanaste() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Ganaste");
    msgBox.setText("¡Has completado el juego! ¿Quieres volver a jugar?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int resultado = msgBox.exec();
    if (resultado == QMessageBox::Yes) {
        reiniciarJuego();
    } else {
        QApplication::quit();
    }
}
