#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "public.h"
#include "ui_mainwindow.h"
#include "game_engine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent*) override;
    virtual void keyReleaseEvent(QKeyEvent*) override;
    ~MainWindow();

public slots:
    void start_game();
    void move_timer_move();
    void new_game();

private:
    Ui::MainWindow *ui;
    gameEngine* ge;
    QTimer* move_timer;
    int key;
};

#endif // MAINWINDOW_H
