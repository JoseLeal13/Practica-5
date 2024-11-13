#ifndef ARREGLOBOMBAS_H
#define ARREGLOBOMBAS_H
#include "mapa.h"
#include "bomba.h"
#include <QObject>

using namespace std;

class ArregloBombas : public QObject
{
    Q_OBJECT

public:
    ArregloBombas();
    ~ArregloBombas();
    void crearUnaBomba(int x, int y);

public slots:
    void bombaExplotada();

private:
    Bomba* bombaActiva; // Puntero para la bomba activa
    mapa* nuevoMapa;
};

#endif // ARREGLOBOMBAS_H
