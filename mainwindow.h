#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include "jugador.h"
#include "mapa.h"
#include "bomba.h"
#include <QTimer>
#include "juego.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;

    //QGraphicsRectItem* rectangulo;
    QGraphicsPixmapItem* imagen;

    Jugador* jugador;

    mapa* mapajuego;

    QPushButton *botonStart;
    QGraphicsTextItem *bienvenidaTexto;

    Juego *juego;

private slots:
    void colocarBomba();
    void empezarJuego();

};
#endif // MAINWINDOW_H
