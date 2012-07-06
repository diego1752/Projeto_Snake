#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QFrame>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QTimerEvent>

class board : public QFrame
{
    Q_OBJECT
public:
    board(QWidget *parent=0);
protected:
    void paintEvent(QPaintEvent *event);
public slots:
    void start();
signals:
    void tela2(int,int);
    void end();
private:
    int x,y,move,fx,fy;
    bool iniciado,emMov;


};

#endif // BOARD_H
