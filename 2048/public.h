#ifndef PUBLIC_H
#define PUBLIC_H

#include <QApplication>
#include <QMainWindow>
#include <QPoint>
#include <QPointF>
#include <QColor>
#include <QtMath>
#include <QtGlobal>
#include <QTime>
#include <QVector>
#include <QPair>
#include <QPaintEvent>
#include <QPainter>
#include <QString>
#include <QFont>
#include <QTextOption>
#include <QRectF>
#include <QSizeF>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QTimer>

#define ALL_COLORS 12

#define LOG_BASE 2

#define GRID_HEIGHT 4
#define GRID_WIDTH 4

#define CELL_LENGTH 150

#define EMPTY 0

#define TIME_SCALR 10000

#define TWO 2

#define FONT_SIZE 70

#define LEFT -1
#define RIGHT 1
#define UP -1
#define DOWN 1

#define NOT_MOVEABLE -1

#define MOVE_TYPE_INIT -1
#define MOVE_TYPE_EMPTY 0
#define MOVE_TYPE_ADD 1
#define MOVE_TYPE_NOT_MOVEABLE 2

#define LEFT_UP_SPEED -20
#define RIGHT_DOWN_SPEED 20

#define TIME_INTERVAL 1

#define TO_LEFT 0
#define TO_RIGHT 1
#define TO_UP 2
#define TO_DOWN 3

#define ACTUAL_MOVE 0
#define TEST_MOVE 1

const QColor colors[ALL_COLORS] = {
    QColor("transparent"),
    QColor(230, 184, 175),
    QColor(244, 204, 204),
    QColor(252, 229, 205),
    QColor(255, 242, 204),
    QColor(217, 234, 211),
    QColor(208, 224, 227),
    QColor(201, 218, 248),
    QColor(207, 226, 243),
    QColor(217, 210, 233),
    QColor(234, 209, 220),
    QColor(234, 153, 153)};

#endif // PUBLIC_H
