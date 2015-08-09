#ifndef ENUMS
#define ENUMS

#include <QObject>

class ChessFigure : public QObject
{
    Q_OBJECT
public:

    Q_ENUMS(Figure)
    enum Figure {
        King,
        Queen,
        Rook,
        Bishop,
        Knight,
        Pawn,
    };
};


class ChessSide : public QObject
{
    Q_OBJECT
public:

    Q_ENUMS(Side)
    enum Side {
        White = 0,
        Black = 1
    };
};



#endif // ENUMS

