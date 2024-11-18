#include "juego.h"
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QTimer>
#include <QGraphicsView>
#include <QApplication>
#include <QVBoxLayout>

Juego::Juego(QObject* parent)
    : QGraphicsScene(parent), puntuacion(0), tiempo(0), juegoIniciado(false) {
}

void Juego::pantallaBienvenida() {
    // Crear el texto de bienvenida
    bienvenidaTexto = new QGraphicsTextItem();
    bienvenidaTexto->setPlainText("Bienvenido al Juego");
    bienvenidaTexto->setDefaultTextColor(Qt::white);
    bienvenidaTexto->setFont(QFont("Arial", 24));
    bienvenidaTexto->setPos(200, 100); // Posición del mensaje
    addItem(bienvenidaTexto);

    // Crear el botón "Start"
    comenzar = new QPushButton("Start");
    comenzar->setGeometry(300, 400, 100, 40);  // Posición y tamaño del botón
    comenzar->show();
    connect(comenzar, &QPushButton::clicked, this, &Juego::empezarJuego);
}

void Juego::empezarJuego() {
    // Limpiar la pantalla de bienvenida
    removeItem(bienvenidaTexto);

    // Crear el objeto para mostrar la puntuación
    puntuacionTexto = new QGraphicsTextItem();
    puntuacionTexto->setPlainText("Puntuación: 0");
    puntuacionTexto->setDefaultTextColor(Qt::white);
    puntuacionTexto->setFont(QFont("Arial", 16));
    puntuacionTexto->setPos(10, 10);
    addItem(puntuacionTexto);

    // Crear el objeto para mostrar el tiempo
    tiempoTexto = new QGraphicsTextItem();
    tiempoTexto->setPlainText("Tiempo: 0");
    tiempoTexto->setDefaultTextColor(Qt::white);
    tiempoTexto->setFont(QFont("Arial", 16));
    tiempoTexto->setPos(10, 40);
    addItem(tiempoTexto);

    // Configurar el temporizador para actualizar el tiempo
    tiempo_partida = new QTimer(this);
    connect(tiempo_partida, &QTimer::timeout, this, &Juego::actualizarTiempo);
    tiempo_partida->start(1000);  // Actualizar cada segundo

    // Inicializar el puntaje y tiempo
    puntuacion = 0;
    tiempo = 0;
    juegoIniciado = true;
}

void Juego::setScene(QGraphicsScene* scene) {
    sceneActual = scene;
}

void Juego::iniciarJuego() {
    if (sceneActual) {
        oMapa->generarMatriz();
        oMapa->colocarPuertaAleatoria(sceneActual, pixmapPuerta);  // Colocar la puerta
        oMapa->dibujarMatriz(sceneActual, pixmapSolido, pixmapDestruible);  // Dibujar el mapa
    }
}

void Juego::actualizarTiempo() {
    if (juegoIniciado) {
        tiempo++;
        tiempoTexto->setPlainText("Tiempo: " + QString::number(tiempo));
    }
}
void Juego::CambiarNivel() {
    clear();
    tiempo = 0;
    puntuacion = 0;
    tiempoTexto->setPlainText("Tiempo: 0");
    puntuacionTexto->setPlainText("Puntuación: 0");

    oMapa->generarMatriz();
    oMapa->colocarPuertaAleatoria(sceneActual, pixmapPuerta);
    oMapa->dibujarMatriz(sceneActual, pixmapSolido, pixmapDestruible);
    QPixmap Base("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\base.jpg");
    QPixmap Puerta("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\puerta.png");
    oMapa->colocarPuertaAleatoria(sceneActual, Puerta);
    sceneActual->setBackgroundBrush(Base.scaled(sceneActual->sceneRect().width(), sceneActual->sceneRect().height()));
    tiempo_partida->start(1000);
}

