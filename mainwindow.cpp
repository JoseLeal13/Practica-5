#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Definir dimensiones del mapa
    int filas = 15;
    int columnas = 17;
    int tileSize = 50;  // Tamaño de cada celda en píxeles

    // Inicializar QGraphicsView y QGraphicsScene
    this->view = new QGraphicsView(this);
    this->scene = new QGraphicsScene(this);

    // Configurar el tamaño de la escena en función del mapa
    int sceneWidth = columnas * tileSize;
    int sceneHeight = filas * tileSize;
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    view->setScene(scene);
    view->setGeometry(50, 50, sceneWidth, sceneHeight); // Ajustar tamaño de la vista

    // Cargar las imágenes
    QPixmap Solido("C:\\Users\\Lenovo\\Pictures\\bmpSolido.jpg");
    QPixmap Destruible("C:\\Users\\Lenovo\\Downloads\\bmpDestruible.png");
    QPixmap Base("C:\\Users\\Lenovo\\Pictures\\base.jpeg"); // Imagen para la base del mapa

    scene->setBackgroundBrush(Base.scaled(sceneWidth, sceneHeight));

    // Inicializar el mapa con las dimensiones especificadas
    mapajuego = new mapa(filas, columnas);  // Inicializar mapa con filas y columnas
    mapajuego->generarMatriz();             // Generar la matriz del mapa
    mapajuego->dibujarMatriz(scene, Solido, Destruible); // Dibujar el mapa en la escena

    // Configuración del jugador
    QPixmap pixmap("C:\\Users\\Lenovo\\Pictures\\bomberman.png");
    QPixmap scaledPixmap = pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    jugador = new Jugador(1 * tileSize, 1 * tileSize);
    jugador->setPixmap(scaledPixmap);
    scene->addItem(jugador);

    connect(jugador, &Jugador::colocarBomba, this, &MainWindow::colocarBomba);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, jugador, &Jugador::update);
    timer->start(16);

    // Ajustar el tamaño de la vista en función de la escena
    view->setFixedSize(sceneWidth + 2, sceneHeight + 2); // Añadir un pequeño borde

    jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    jugador->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mapajuego; // Limpieza del objeto mapa
    delete jugador;   // Limpieza del jugador
}
void MainWindow::colocarBomba() {
    int jugadorX = jugador->getX();
    int jugadorY = jugador->getY();
    /*
    // Verificar si el espacio está libre antes de colocar la bomba
    if (mapajuego->esEspacioLibre(jugadorX, jugadorY)) {
    Bomba* bomba = new Bomba(jugadorX, jugadorY, nullptr);
    scene->addItem(bomba);
    }
*/
    Bomba* bomba = new Bomba(jugadorX, jugadorY, mapajuego, nullptr);
    scene->addItem(bomba);
}
