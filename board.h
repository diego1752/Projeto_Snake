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
    void vida(int);
    void start();
signals:
    void tela2(int,int,int);
    void end();
private:
    bool Iniciar,Tecla;
    int x,y,locomocao,move,length;
    int fx,fy,pontos,hs,fr,chnglen;
    int fase,barra,vidas;

    QBasicTimer timer;
    int timeoutTime()
    {
        return 1000 / (7*fase);
    }

    QVector<int> qvtemp;
    QVector<QVector<int> > qvtail;

    void maca();
    bool bate_cobra();
    void fim_jogo();
};

#endif // BOARD_H
