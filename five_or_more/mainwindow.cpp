#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lbl_Info->hide();
    ge = new GameEngine(ui->frame->height());
    on_off = false;

    connect(ui->btn_newGame, SIGNAL(clicked()), this, SLOT(place_stone_on_board()));
    blink_timer = new QTimer(this);
    move_timer = new QTimer(this);

    blink_timer->setInterval(TIME_INTERVAL);
    move_timer->setInterval(MOVE_TIME_INTERVAL);

    connect(blink_timer, SIGNAL(timeout()), this, SLOT(timer_update()));
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move_update()));

    ge->place_on_board();
    update();
}

void MainWindow::move_update()
{
    QVector<QPair<int, int>>& trail = ge->get_trail();
    QPair<int, int> pair = trail.takeLast();
    cell cells[TIMES] = {cell()};
    cell* place = NULL;

    if(!trail.isEmpty())
    {
        QPair<int, int> second_last = trail.last();
        int color = ge->get_bd().get_a_cell(pair.first, pair.second).get_color();
        ge->get_bd().get_a_cell(pair.first, pair.second).set_color(NO_COLOR);
        ge->get_bd().get_a_cell(second_last.first, second_last.second).set_color(color);
    }
    else
    {
        if(ge->get_dest() != NULL)
            ge->check_a_line(*(ge->get_dest()));
        move_timer->stop();
        place = cells;
        ge->place_on_board(place);
    }

    update();

    if(place != NULL)
    {
        for(int i = 0; i < TIMES; i++)
        {
            ge->check_a_line(cells[i]);
        }
    }

    ui->lbl_Score->setText(QString::number(ge->get_score()));
    update();
    place = NULL;
}

void MainWindow::timer_update()
{
    on_off = !on_off;
    int color = on_off ? ge->get_selected_cell()->get_real_color() : NO_COLOR;
    ge->get_selected_cell()->set_color(color);
    update();
}

void MainWindow::place_stone_on_board()
{
    delete ge;
    ge = new GameEngine(ui->frame->height());
    ge->place_on_board();
    ui->lbl_Info->hide();
    ui->lbl_Score->setText("0");
    move_timer->stop();
    blink_timer->stop();
    update();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    draw_lines(painter);
    draw_cells(painter);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    ui->lbl_Info->hide();

    if(!move_timer->isActive())
    {
        //Get mouse position
        int x = event->x();
        int y = event->y();

        //Get mouse position reletive to the frame
        x -= ui->frame->x();
        y -= ui->frame->y();

        //Calculate the position of the cell by the mouse clicked position
        int column  = x / cell::length;
        int row = y / cell::length;

        if(row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH && x >= 0 && y >= 0)
        {
            ge->set_selected_cell(row, column, *blink_timer);
            update();

            if(!blink_timer->isActive())
            {
                QVector<QPair<int, int>> trail = ge->get_trail();

                if(!trail.isEmpty())
                {
                    QPair<int, int> scr = trail.last();
                    QPair<int, int> des = trail.first();

                    cell& source = ge->get_bd().get_a_cell(scr.first, scr.second);
                    cell& destnation = ge->get_bd().get_a_cell(des.first, des.second);

                    int tmp = source.get_color();
                    source.set_real_color(destnation.get_real_color());
                    destnation.set_real_color(tmp);

                    ge->maintain_vaild_cells(APPEND, scr);
                    ge->maintain_vaild_cells(REMOVE, des);

                    move_timer->start();
                }
                else if(ge->Is_move())
                {
                    ui->lbl_Info->show();
                }
            }
        }
    }
}

//Draw each cell by its color
void MainWindow::draw_cells(QPainter& painter)
{
    for(int r = 0; r < BOARD_HEIGHT; r++)
    {
        for(int c = 0; c < BOARD_WIDTH; c++)
        {
            //Draw a rectangle in the cell
            cell acell = ge->get_bd().get_a_cell(r, c);
            QPointF point = acell.get_point();
            QSizeF sizef(cell::length - CELL_GAP, cell::length - CELL_GAP);
            QRectF rectf(point, sizef);
            QColor color = acell.draw_cell_color();
            painter.fillRect(rectf, color);
        }
    }
}

//Draw the grid of the board
void MainWindow::draw_lines(QPainter& painter)
{
    float a_y = ui->frame->y();
    float a_x = ui->frame->x();
    float b_y = 0.0f;
    float b_x = 0.0f;

    //Draw vertical lines
    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        a_x = a_x + cell::length;
        b_x = a_x;
        b_y = ui->frame->height() + a_y;
        QPointF a(a_x, a_y);
        QPointF b(b_x, b_y);

        painter.drawLine(a, b);
    }

    //Reset to its initial state
    b_x = 0.0f;
    b_y = 0.0f;
    a_y = ui->frame->y();
    a_x = ui->frame->x();

    //Draw horizontal lines
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        a_y = a_y + cell::length;
        b_y = a_y;
        b_x = ui->frame->width() + a_x;
        QPointF a(a_x, a_y);
        QPointF b(b_x, b_y);

        painter.drawLine(a, b);
    }
}

MainWindow::~MainWindow()
{
    delete ge;
    delete ui;
    delete blink_timer;
    delete move_timer;

    ge = NULL;
    ui = NULL;
    blink_timer = NULL;
    move_timer = NULL;
}
