#pragma once

#include <QWidget>
#include <QGraphicsScene>

namespace Ui { class RbtWidget; }

class RbtWidget : public QWidget {
public:
    RbtWidget(QWidget *parent = nullptr);
    ~RbtWidget();
private:
    Ui::RbtWidget *ui;
    QGraphicsScene *scene;
};
