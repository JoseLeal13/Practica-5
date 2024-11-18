#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int filas = 15;
    int columnas = 17;
    int tileSize = 50;

    // Inicialización de la vista y la escena
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    int sceneWidth = columnas * tileSize;
    int sceneHeight = filas * tileSize;
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    view->setScene(scene);
    view->setGeometry(50, 50, sceneWidth, sceneHeight);

    // Fondo del menú de bienvenida
    QPixmap fondoMenu("C:\\Users\\Lenovo\\Pictures\\bombermanFondo.jpg");
    scene->setBackgroundBrush(fondoMenu.scaled(sceneWidth, sceneHeight));

    // Texto de bienvenida
    bienvenidaTexto = new QGraphicsTextItem("Bienvenido al Juego");
    bienvenidaTexto->setDefaultTextColor(Qt::white);
    bienvenidaTexto->setFont(QFont("Arial", 24));
    bienvenidaTexto->setPos(sceneWidth / 2 - bienvenidaTexto->boundingRect().width() / 2, 100);
    scene->addItem(bienvenidaTexto);

    // Botón de inicio
    botonStart = new QPushButton("Iniciar", this);
    int botonWidth = 150;
    int botonHeight = 50;
    botonStart->setGeometry(sceneWidth / 2 - botonWidth / 2, sceneHeight / 2 + 100, botonWidth, botonHeight);
    botonStart->show();
    connect(botonStart, &QPushButton::clicked, this, &MainWindow::empezarJuego);
    connect(controlador, &Controlador::juegoPerdido, controlador, &Controlador::mostrarMenuPerdiste);
    // Inicialización del mapa y controlador
    mapajuego = new mapa(filas, columnas);  // Crear el objeto de mapa
    controlador = new Controlador();  // Pasar la escena y el mapa al controlador

    QTimer *timer = new QTimer(this);
    timer->start(16);
}

MainWindow::~MainWindow() {
    delete ui;
    delete mapajuego;
    delete controlador;
    delete botonStart;
    delete bienvenidaTexto;
    //delete juego;
}

void MainWindow::colocarBomba() {
    int jugadorX = jugador->getX();
    int jugadorY = jugador->getY();

    // Colocar la bomba
    Bomba* bomba = new Bomba(jugadorX, jugadorY, mapajuego, nullptr);
    scene->addItem(bomba);
}

void MainWindow::empezarJuego() {
    // Limpiar la pantalla de bienvenida
    scene->removeItem(bienvenidaTexto);
    botonStart->hide();  // Ocultar el botón

    // Configurar el mapa y los elementos del juego
    int filas = 15;
    int columnas = 17;
    int tileSize = 50;  // Tamaño de cada celda en píxeles

    QPixmap Solido = QPixmap("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\bmpSolido.jpg");
    QPixmap Destruible = QPixmap("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\bmpDestruible (1).png");
    QPixmap Puerta = QPixmap("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\puerta.png");

    QPixmap Base("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\base.jpg");
    scene->setBackgroundBrush(Base.scaled(scene->sceneRect().width(), scene->sceneRect().height()));

    // Inicializar QGraphicsView y QGraphicsScene
    mapajuego = new mapa(filas, columnas);  // Inicializar mapa con filas y columnas
    mapajuego->generarMatriz();             // Generar la matriz del mapa
    mapajuego->dibujarMatriz(scene, QPixmap(Solido), QPixmap(Destruible));
    mapajuego->colocarPuertaAleatoria(scene, Puerta);

    // Configuración del jugador
    QPixmap pixmap("C:\\Users\\Lenovo\\Documents\\Bomberman\\build\\bomberman.png");
    QPixmap scaledPixmap = pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    jugador = new Jugador(1 * tileSize, 1 * tileSize);
    jugador->setPixmap(scaledPixmap);
    scene->addItem(jugador);

    connect(jugador, &Jugador::colocarBomba, this, &MainWindow::colocarBomba);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, jugador, &Jugador::update);
    timer->start(16);

    // Ajustar el tamaño de la vista en función de la escena
    view->setFixedSize(columnas * tileSize + 2, filas * tileSize + 2); // Añadir un pequeño borde
    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    jugador->setFocus();
}
