/********************************************************************************
** Form generated from reading UI file 'rbt_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RBT_WIDGET_H
#define UI_RBT_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RbtWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *initBtn;
    QSpinBox *inputKey;
    QPushButton *addBtn;
    QPushButton *delBtn;
    QPushButton *clearBtn;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *RbtWidget)
    {
        if (RbtWidget->objectName().isEmpty())
            RbtWidget->setObjectName(QString::fromUtf8("RbtWidget"));
        RbtWidget->resize(403, 377);
        gridLayout = new QGridLayout(RbtWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        initBtn = new QPushButton(RbtWidget);
        initBtn->setObjectName(QString::fromUtf8("initBtn"));

        horizontalLayout->addWidget(initBtn);

        inputKey = new QSpinBox(RbtWidget);
        inputKey->setObjectName(QString::fromUtf8("inputKey"));

        horizontalLayout->addWidget(inputKey);

        addBtn = new QPushButton(RbtWidget);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));

        horizontalLayout->addWidget(addBtn);

        delBtn = new QPushButton(RbtWidget);
        delBtn->setObjectName(QString::fromUtf8("delBtn"));

        horizontalLayout->addWidget(delBtn);

        clearBtn = new QPushButton(RbtWidget);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        horizontalLayout->addWidget(clearBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        graphicsView = new QGraphicsView(RbtWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 1, 0, 1, 1);


        retranslateUi(RbtWidget);

        QMetaObject::connectSlotsByName(RbtWidget);
    } // setupUi

    void retranslateUi(QWidget *RbtWidget)
    {
        RbtWidget->setWindowTitle(QCoreApplication::translate("RbtWidget", "Form", nullptr));
        initBtn->setText(QCoreApplication::translate("RbtWidget", "init_rbt", nullptr));
        addBtn->setText(QCoreApplication::translate("RbtWidget", "add", nullptr));
        delBtn->setText(QCoreApplication::translate("RbtWidget", "remove", nullptr));
        clearBtn->setText(QCoreApplication::translate("RbtWidget", "clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RbtWidget: public Ui_RbtWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RBT_WIDGET_H
