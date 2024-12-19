/********************************************************************************
** Form generated from reading UI file 'avl_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVL_WIDGET_H
#define UI_AVL_WIDGET_H

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

class Ui_AvlWidget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *initBtn;
    QSpinBox *inputKey;
    QPushButton *addBtn;
    QPushButton *delBtn;
    QPushButton *searchBtn;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *AvlWidget)
    {
        if (AvlWidget->objectName().isEmpty())
            AvlWidget->setObjectName(QString::fromUtf8("AvlWidget"));
        AvlWidget->resize(455, 302);
        gridLayout_2 = new QGridLayout(AvlWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        initBtn = new QPushButton(AvlWidget);
        initBtn->setObjectName(QString::fromUtf8("initBtn"));

        horizontalLayout->addWidget(initBtn);

        inputKey = new QSpinBox(AvlWidget);
        inputKey->setObjectName(QString::fromUtf8("inputKey"));

        horizontalLayout->addWidget(inputKey);

        addBtn = new QPushButton(AvlWidget);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));

        horizontalLayout->addWidget(addBtn);

        delBtn = new QPushButton(AvlWidget);
        delBtn->setObjectName(QString::fromUtf8("delBtn"));

        horizontalLayout->addWidget(delBtn);

        searchBtn = new QPushButton(AvlWidget);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));

        horizontalLayout->addWidget(searchBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        graphicsView = new QGraphicsView(AvlWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(AvlWidget);

        QMetaObject::connectSlotsByName(AvlWidget);
    } // setupUi

    void retranslateUi(QWidget *AvlWidget)
    {
        AvlWidget->setWindowTitle(QCoreApplication::translate("AvlWidget", "Form", nullptr));
        initBtn->setText(QCoreApplication::translate("AvlWidget", "init_avl", nullptr));
        addBtn->setText(QCoreApplication::translate("AvlWidget", "add", nullptr));
        delBtn->setText(QCoreApplication::translate("AvlWidget", "remove", nullptr));
        searchBtn->setText(QCoreApplication::translate("AvlWidget", "search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AvlWidget: public Ui_AvlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVL_WIDGET_H
