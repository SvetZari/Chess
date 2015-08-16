#include "logiccontroller.h"

int LogicController::index(const int row, const int column) {
    return column + (row * MAX_COLUMNS);
}

int LogicController::findChessMan(const int row, const int column) {
    foreach (QObject* figure, m_chessman) {
        AbstractFigure *abstractFigure = qobject_cast<AbstractFigure*>(figure);
        if(abstractFigure != 0) {
            if(abstractFigure->row() == row && abstractFigure->column() == column)
                return m_chessman.indexOf(figure);
        }
    }
    return -1;
}

void LogicController::moveChessMan()
{
    auto from = findChessMan(m_currentmove->rowFrom(), m_currentmove->columnFrom());
    qDebug() << "from" << from;

    auto to = findChessMan(m_currentmove->rowTo(), m_currentmove->columnTo());
    qDebug() << "to" << to;

    if(from == to)
        return;

    AbstractFigure *abstractFigure = qobject_cast<AbstractFigure*>(m_chessman[from]);
    if(abstractFigure != 0) {
        abstractFigure->setRow(m_currentmove->rowTo());
        abstractFigure->setColumn(m_currentmove->columnTo());
        m_chessman[to] = abstractFigure;
        m_chessman[from] = new AbstractFigure(m_currentmove->rowFrom(), m_currentmove->columnFrom());
    }
}
