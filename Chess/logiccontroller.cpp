#include "logiccontroller.h"

bool LogicController::allowed(QObject *move) {
    ChessMove *chessmove = qobject_cast<ChessMove*>(move);
    if(chessmove != 0) {
        //qDebug() << "is allowed" << chessmove->rowFrom() << chessmove->columnFrom() << " - > "
        //         << chessmove->rowTo() << chessmove->columnTo() << chessmove->figure() << chessmove->side();
        return chessmove->allowed();
    }
}

void LogicController::initChessman()
{
    m_chessman.clear();
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int column = 0; column < MAX_COLUMNS; column++) {
            //QQmlEngine::setObjectOwnership(chessman, QQmlEngine::JavaScriptOwnership);
            m_chessman.append(new AbstractFigure(row,column,true));
        }
    }
}

QList<QObject *> LogicController::chessman() {
    //for (int var = 0; var < 64; ++var) {
    //    auto ret = (dynamic_cast<AbstractFigure*>(m_chessman[var]));
    //    qDebug() << ret->figure();
    //}
    return m_chessman;
}

QObject *LogicController::currentmove() {
    return m_currentmove;
}

void LogicController::setCurrentMove(QObject *move) {
    ChessMove *chessmove = qobject_cast<ChessMove*>(move);
    if(chessmove != 0) {
        m_currentmove = chessmove;
        //qDebug() << "new pos" << chessmove->rowTo() << chessmove->columnTo() << chessmove->figure() << chessmove->side();

        //
        qDebug() << m_chessmoves.count();
        m_chessmoves.append(chessmove);

        moveChessMan();

        emit currentmoveChanged();
        emit chessmanChanged();
    }
}

void LogicController::setCurrentMove(QObject *move) {
    ChessMove *chessmove = qobject_cast<ChessMove*>(move);
    if(chessmove != 0) {
        m_currentmove = chessmove;
        //qDebug() << "new pos" << chessmove->rowTo() << chessmove->columnTo() << chessmove->figure() << chessmove->side();

        //
        qDebug() << m_chessmoves.count();
        m_chessmoves.append(chessmove);

        moveChessMan();

        emit currentmoveChanged();
        emit chessmanChanged();
    }
}

void LogicController::clear() {
    m_chessman.clear();
    m_chessmoves.clear();
}

int LogicController::index(const int row, const int column) {
    return column + (row * MAX_COLUMNS);
}

int LogicController::findChessMan(const int row, const int column) {
    foreach (QObject* figure, m_chessman) {
        AbstractFigure *abstractFigure = qobject_cast<AbstractFigure*>(figure);
        if(abstractFigure != 0)
            if(abstractFigure->row() == row && abstractFigure->column() == column)
                return m_chessman.indexOf(figure);
    }
    return -1;
}

void LogicController::moveChessMan()
{
    auto from = findChessMan(m_currentmove->rowFrom(), m_currentmove->columnFrom());
    auto to = findChessMan(m_currentmove->rowTo(), m_currentmove->columnTo());
    if(from == to) return;

    AbstractFigure *figureTo = qobject_cast<AbstractFigure*>(m_chessman[to]);
    if(figureTo == 0) return;

    AbstractFigure *figureFrom = qobject_cast<AbstractFigure*>(m_chessman[from]);
    if(figureFrom == 0) return;

    if(figureFrom->side() == figureTo->side())
        return;

    figureFrom->setRow(m_currentmove->rowTo());
    figureFrom->setColumn(m_currentmove->columnTo());
    m_chessman[to] = figureFrom;
    m_chessman[from] = new AbstractFigure(m_currentmove->rowFrom(), m_currentmove->columnFrom());
}
