#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QObject>

class AbstractFigure : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
    Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)

public:
    AbstractFigure() {}

    AbstractFigure(int row, int column) {
        m_row = row;
        m_column = column;
    }

signals:
    void columnChanged();
    void rowChanged();

public slots:

    int row() {
        return m_row;
    }

    int column() {
        return m_column;
    }

    void setRow(int row) {
        m_row = row;
        emit rowChanged();
    }

    void setColumn(int column) {
       m_column = column;
       emit columnChanged();
    }

private:
    int m_side;
    int m_figure;
    int m_row;
    int m_column;
};

#endif // ABSTRACTFIGURE_H
