#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ge = new gameEngine(ui->mainframe->x(), ui->mainframe->y());
    move_timer = new QTimer(this);
    move_timer->setInterval(TIME_INTERVAL);
    connect(ui->btn_start, SIGNAL(clicked(bool)), this, SLOT(start_game()));
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move_timer_move()));
    connect(ui->btn_new, SIGNAL(clicked(bool)), this, SLOT(new_game()));
    key = 0;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    if(!ge->get_move_is_started())
    {
        for(int r = 0; r < GRID_HEIGHT; r++)
        {
            for(int c = 0; c < GRID_WIDTH; c++)
            {
                const QPointF& position = ge->get_grid().get_a_cell(r, c).get_position();
                const QColor& color = ge->get_grid().get_a_cell(r, c).get_color();
                int num = ge->get_grid().get_a_cell(r, c).get_number();

                if(num > EMPTY)
                {
                    painter.fillRect(position.x(), position.y(), CELL_LENGTH, CELL_LENGTH, color);
                    painter.setPen(QColor("white"));
                    QFont font = QFont("Monaco", FONT_SIZE, QFont::Bold);
                    painter.setFont(font);
                    QRectF rectf(position, QSizeF(CELL_LENGTH, CELL_LENGTH));
                    painter.drawText(rectf, QString::number(num), QTextOption(Qt::AlignHCenter|Qt::AlignVCenter));
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < ge->get_need_to_move().size(); i++)
        {
            cell& tmp = ge->get_need_to_move_cell(i);
            int num = tmp.get_number();
            const QPointF& position = tmp.get_position();
            painter.fillRect(position.x(), position.y(), CELL_LENGTH, CELL_LENGTH, tmp.get_color());
            painter.setPen(QColor("white"));
            QFont font = QFont("Monaco", FONT_SIZE, QFont::Bold);
            painter.setFont(font);
            QRectF rectf(position, QSizeF(CELL_LENGTH, CELL_LENGTH));
            painter.drawText(rectf, QString::number(num), QTextOption(Qt::AlignHCenter|Qt::AlignVCenter));
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    key = event->key();

    switch(key)
    {
    case Qt::Key_Left:
        ge->set_move_is_started(true);
        ge->left_fill();
        ge->asign_move_type_left();
        ge->test_move(TO_LEFT);
        break;

    case Qt::Key_Right:
        ge->set_move_is_started(true);
        ge->right_fill();
        ge->asign_move_type_right();
        ge->test_move(TO_RIGHT);
        break;

    case Qt::Key_Up:
        ge->set_move_is_started(true);
        ge->up_fill();
        ge->asign_move_type_up();
        ge->test_move(TO_UP);
        break;
    case Qt::Key_Down:
        ge->set_move_is_started(true);
        ge->down_fill();
        ge->asign_move_type_down();
        ge->test_move(TO_DOWN);
        break;
    }

    if(ge->get_move_is_started())
    {
        move_timer->start();
    }
    update();
}

void MainWindow::move_timer_move()
{
    if(!ge->get_move_is_started())
    {
        move_timer->stop();
        ge->place_on_grid();
    }
    else
    {
        switch(key)
        {
        case Qt::Key_Left:
            ge->move_left();
            break;

        case Qt::Key_Right:
            ge->move_right();
            break;

        case Qt::Key_Up:
            ge->move_up();
            break;

        case Qt::Key_Down:
            ge->move_down();
            break;
        }
    }
    update();
}

void MainWindow::start_game()
{
    ge->place_on_grid();
    ge->place_on_grid();
    update();
    ui->btn_start->setEnabled(false);
}

void MainWindow::new_game()
{
    move_timer->stop();

    delete ge;

    ge = new gameEngine(ui->mainframe->x(), ui->mainframe->y());

    update();

    ui->btn_start->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ge;

    ui = NULL;
    ge = NULL;
}
