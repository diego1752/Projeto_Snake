#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QFrame>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QTimerEvent>
#include <QProgressBar>

class board : public QFrame
{
    Q_OBJECT
public:
    board(QWidget *parent=0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
public slots:
    void movex(int);
    void movey(int);
    void start();
signals:
    void tela2(int,int);
    void end();
private:
    int x,y,locomocao,move,fase,length,fx,fy,pontos,hs,fr,chnglen,barra,vidas;
    bool isStarted,isChanged;

    QBasicTimer timer;
    int timeoutTime()
    {
        return 1000 / (3 + 4*fase);
    }

    QVector<int> qvtemp;
    QVector<QVector<int> > qvtail;

    void genfood();
    bool check_snake();

    void end_game();
    int lowesthighscore();


    QVector<QVector<QString> > qvscores;
};

#endif // BOARD_H
