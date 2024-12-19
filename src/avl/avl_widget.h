#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class AvlWidget; }
QT_END_NAMESPACE

class AvlWidget : public QWidget
{
    //Q_OBJECT
public:
    AvlWidget(QWidget *parent = nullptr);
    ~AvlWidget();

private:
    Ui::AvlWidget *ui;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
