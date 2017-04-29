#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "public.h"
#include "ui_mainwindow.h"
#include "gameEngine.h"
#include "cell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent*) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    ~MainWindow();

public slots:
    void place_stone_on_board();
    void timer_update();
    void move_update();

private:
    Ui::MainWindow *ui;
    void draw_lines(QPainter &);
    void draw_cells(QPainter &);
    GameEngine* ge;
    QTimer* blink_timer;
    QTimer* move_timer;
    bool on_off;
};

#endif // MAINWINDOW_H
