#ifndef ARREGLOBOMBAS_H
#define ARREGLOBOMBAS_H
#include <vector>
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
    //void bombaExplotada();

private:
    vector<Bomba*> ArrBombas;
    int totalBombas;
};

#endif // ARREGLOBOMBAS_H