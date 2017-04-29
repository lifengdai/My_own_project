#ifndef PUBLIC
#define PUBLIC

#include <QPoint>
#include <QPen>
#include <QColor>
#include <QPainter>
#include <QMainWindow>
#include <QtGlobal>
#include <QVector>
#include <QTime>
#include <QMouseEvent>
#include <QTimer>
#include <QPair>
#include <QDebug>
#include <QtMath>
#include <QString>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10
#define CELL_GAP 10.0f

#define HALF 0.5f

#define NO_COLOR 0
#define RED 1
#define YELLOW 2
#define BLUE 3
#define GRAY 4
#define BLACK 5
#define PURPLE 6
#define ORANGE 7
#define TOTAL_COLOR 7
#define OFFSET 1

#define OFFSET_X 25.0f
#define OFFSET_Y 15.0f

#define TOTAL_CELLS 100
#define TIMES 3
#define SCALAR 1000

#define TIME_INTERVAL 400
#define MOVE_TIME_INTERVAL 100

#define FLT_MAX 10000.0f

#define TO_RIGHT 1
#define TO_LEFT -1
#define TO_UP -1
#define TO_DOWN 1

#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2

#define ALL_DIRECTIONS 8
#define HORIZANTAL 1
#define VERTICAL 2
#define LEFT_DIAGONAL 3
#define RIGHT_DIAGONAL 4
#define H_UP 0
#define H_DOWN 1
#define V_LEFT 2
#define V_RIGHT 3
#define LD_UP 4
#define LD_DOWN 5
#define RD_UP 6
#define RD_DOWN 7

#define DOUBLE  2
#define LINE_OFFSET 1
#define MIN_LINE 5

#define REMOVE 0
#define APPEND 1

#define NUM_OF_DIRECTIONS 4

#define SQUARE 2.0f

#define TIE_BROKER 50
#define TIE_BASE 10000000.0f

#endif // PUBLIC
