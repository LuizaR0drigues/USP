#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "painter.h"
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void draw_lines(int x1, int y1, int x2, int y2);
    void draw_point(int x, int y);
    void on_draw_clicked();
protected:
    void mousePressEvent(QMouseEvent* event)override ;
private slots:
    void on_pushButton_clicked();
    void on_reset_clicked();
    void orange_clicked();
    void blue_clicked();
    void red_clicked();
    void green_clicked();
    void yellow_clicked();
    void black_clicked();
private:
    Ui::MainWindow *ui;
    Painter painter;
};
#endif // MAINWINDOW_H
