#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controlador.h"  // Asegúrate de incluir el archivo del controlador

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicialización de la vista y la escena
    int filas = 15;
    int columnas = 17;
    int tileSize = 50;  // Tamaño de cada celda en píxeles
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    int sceneWidth = columnas * tileSize;
    int sceneHeight = filas * tileSize;
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    view->setScene(scene);
    view->setGeometry(50, 50, sceneWidth, sceneHeight); // Ajuste de la vista

    // Establecer una imagen de fondo para el menú de bienvenida
    QPixmap fondoMenu("C:\\Users\\Lenovo\\Pictures\\bombermanFondo.jpg");
    scene->setBackgroundBrush(fondoMenu.scaled(sceneWidth, sceneHeight));

    // Crear y mostrar pantalla de bienvenida con texto
    bienvenidaTexto = new QGraphicsTextItem();
    bienvenidaTexto->setPlainText("Bienvenido al Juego");
    bienvenidaTexto->setDefaultTextColor(Qt::white);
    bienvenidaTexto->setFont(QFont("Arial", 24));
    bienvenidaTexto->setPos(sceneWidth / 2 - bienvenidaTexto->boundingRect().width() / 2, 100); // Centrado horizontalmente
    scene->addItem(bienvenidaTexto);

    // Crear y configurar el botón de inicio
    botonStart = new QPushButton("Iniciar", this);
    int botonWidth = 150;
    int botonHeight = 50;
    botonStart->setGeometry(sceneWidth / 2 - botonWidth / 2, sceneHeight / 2 + 100, botonWidth, botonHeight);  // Centrado horizontalmente
    botonStart->show();

    // Conectar la señal del botón con la función empezarJuego
    connect(botonStart, &QPushButton::clicked, this, &MainWindow::empezarJuego);

    // Inicializar controlador
    controlador = new Controlador();  // Asegúrate de instanciar el controlador

    // Conectar la señal de fin de juego a la función de menú de fin de juego
    connect(controlador, &Controlador::juegoPerdido, this, &MainWindow::mostrarMenuPerdiste);

    // Temporizador (si es necesario)
    QTimer *timer = new QTimer(this);
    timer->start(16);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mapajuego; // Limpieza del objeto mapa
    delete jugador;   // Limpieza del jugador
    delete botonStart; // Limpieza del botón de inicio
    delete bienvenidaTexto; // Limpieza del texto de bienvenida
    delete juego; // Limpieza de la instancia de Juego
    delete controlador; // Limpieza del controlador
}

void MainWindow::empezarJuego() {
    // Limpiar la pantalla de bienvenida
    scene->removeItem(bienvenidaTexto);

    // Eliminar el fondo de la bienvenida (hacerlo transparente)
    scene->setBackgroundBrush(Qt::transparent);

    // Ocultar el botón de inicio en lugar de removerlo de la escena
    botonStart->setVisible(false);

    // Iniciar el juego
    controlador->dibujar(scene, QPixmap("solido.png"), QPixmap("destruible.png"));
}

void MainWindow::mostrarMenuPerdiste() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Perdiste");
    msgBox.setText("Has perdido todas tus vidas. ¿Quieres volver a intentarlo?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int resultado = msgBox.exec();
    if (resultado == QMessageBox::Yes) {
        controlador->reiniciarJuego();  // Reinicia el juego si el jugador quiere volver a intentarlo
    } else {
        // Aquí puedes cerrar el juego o volver al menú principal
    }
}
