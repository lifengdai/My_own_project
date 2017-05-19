#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "public.h"
#include "ui_mainwindow.h"
#include "game_engine.h"
#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *) override;
    void keyReleaseEvent(QKeyEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    ~MainWindow();

public slots:
    void start_game();
    void timer_start();
    void new_game();

private:
    Ui::MainWindow *ui;
    gameEngine* ge;
    QTimer* timer;
    bool game_is_started;
};

#endif // MAINWINDOW_H
