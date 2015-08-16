#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <QObject>

class ChessMove : public QObject
{
    Q_OBJECT
public:
    //ChessMove(){}
    explicit ChessMove(QObject *parent = 0) : QObject(parent) {
        clear();
    }

    Q_PROPERTY(int rowTo READ rowTo WRITE setRowTo NOTIFY rowToChanged)
    Q_PROPERTY(int columnTo READ columnTo WRITE setColumnTo NOTIFY columnToChanged)
    Q_PROPERTY(int rowFrom READ rowFrom WRITE setRowFrom NOTIFY rowFromChanged)
    Q_PROPERTY(int columnFrom READ columnFrom WRITE setColumnFrom NOTIFY columnFromChanged)
    Q_PROPERTY(int side READ side WRITE setSide NOTIFY figureChanged)
    Q_PROPERTY(int figure READ figure WRITE setFigure NOTIFY sideChanged)

signals:
    void rowToChanged();
    void columnToChanged();
    void rowFromChanged();
    void columnFromChanged();
    void figureChanged();
    void sideChanged();

public slots:
    int rowTo() {
        return m_rowTo;
    }

    int rowFrom() {
        return m_rowFrom;
    }

    int columnTo() {
        return m_columnTo;
    }

    int columnFrom() {
        return m_columnFrom;
    }

    int figure() {
        return m_figure;
    }

    int side() {
        return m_side;
    }

    void setRowTo(int rowTo) {
        m_rowTo = rowTo;
        emit rowToChanged();
    }

    void setRowFrom(int rowFrom) {
        m_rowFrom = rowFrom;
        emit rowFromChanged();
    }

    void setColumnTo(int columnTo) {
        m_columnTo = columnTo;
        emit columnToChanged();
    }

    void setColumnFrom(int columnFrom) {
        m_columnFrom = columnFrom;
        emit columnFromChanged();
    }

    void setFigure(int figure) {
        m_figure = figure;
        emit figureChanged();
    }

    void setSide(int side) {
        m_side = side;
        emit sideChanged();
    }

    bool invalid() {
        return (m_rowTo < 0 || m_columnTo < 0
           || m_rowFrom < 0 || m_columnFrom < 0);
    }

    void clear()
    {
        m_rowFrom = -1;
        m_rowTo = -1;
        m_columnFrom = -1;
        m_columnTo = -1;
        m_figure = -1;
        m_side = -1;
    }

private:
    int m_rowFrom;
    int m_columnFrom;
    int m_rowTo;
    int m_columnTo;
    int m_figure;
    int m_side;
};

//Q_DECLARE_METATYPE(ChessMove)

#endif // CHESSMOVE_H
