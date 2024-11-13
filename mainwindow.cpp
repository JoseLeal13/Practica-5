#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    // Eliminar el fondo de la bienvenida (hacerlo transparente)
    scene->setBackgroundBrush(Qt::transparent);

    // Ocultar el botón de inicio en lugar de removerlo de la escena
    botonStart->setVisible(false);  // Esto lo hace invisible, pero no lo elimina de la escena

    // Crear una nueva instancia de Juego
    juego = new Juego();

    // Iniciar el juego (configuración inicial, como el mapa, jugador, etc.)
    juego->iniciarJuego(scene);

    // Crear las imágenes y elementos del mapa después de presionar "Start"
    QPixmap Solido("C:\\Users\\Lenovo\\Pictures\\bmpSolido.jpg");
    QPixmap Destruible("C:\\Users\\Lenovo\\Downloads\\bmpDestruible.png");
    QPixmap Base("C:\\Users\\Lenovo\\Pictures\\base.jpg");

    // Ajustar el fondo del juego
    scene->setBackgroundBrush(Base.scaled(scene->sceneRect().width(), scene->sceneRect().height(), Qt::KeepAspectRatioByExpanding));

    // Inicializar el mapa
    mapajuego = new mapa(15, 17);  // Inicializar mapa con filas y columnas
    mapajuego->generarMatriz();             // Generar la matriz del mapa
    mapajuego->dibujarMatriz(scene, Solido, Destruible); // Dibujar el mapa en la escena

    // Configuración del jugador
    QPixmap pixmap("C:\\Users\\Lenovo\\Pictures\\bomberman.png");
    QPixmap scaledPixmap = pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    jugador = new Jugador(1 * 50, 1 * 50);  // Ajusta la posición del jugador
    jugador->setPixmap(scaledPixmap);
    scene->addItem(jugador);

    connect(jugador, &Jugador::colocarBomba, this, &MainWindow::colocarBomba);

    // Temporizador
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, jugador, &Jugador::update);
    timer->start(16);

    // Ajustar el tamaño de la vista en función de la escena
    view->setFixedSize(scene->sceneRect().width() + 2, scene->sceneRect().height() + 2);

    // Hacer visible la vista para que se muestre el juego
    view->show();
}
