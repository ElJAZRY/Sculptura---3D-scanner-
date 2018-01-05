/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_as;
    QAction *actionOpen_PointClouds;
    QAction *actionOpen_Mesh;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *scanningGroupBox;
    QVBoxLayout *verticalLayout;
    QLabel *preview_window;
    QLabel *label_simple_scanning;
    QHBoxLayout *horizontalLayout;
    QPushButton *start_preview;
    QPushButton *start_scanning;
    QPushButton *advanced_scanning;
    QSpacerItem *verticalSpacer;
    QGroupBox *reconstructionGroupBox;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVTKWidget *vtkWindow;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QProgressBar *progressBar;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *get_3D_model;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *tabPointClouds;
    QGroupBox *ListGroupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *list_pc;
    QListView *listPointClouds;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *deleteAllPointClouds;
    QPushButton *deletePointCloud;
    QSpacerItem *verticalSpacer_2;
    QWidget *tabMeshes;
    QGroupBox *ListGroupBox_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *list_mesh;
    QListView *listMeshes;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *deleteAllMeshes;
    QPushButton *deleteMesh;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1174, 731);
        MainWindow->setStyleSheet(QLatin1String("QMainWindow\n"
"{\n"
"    background-color: #ecf0f5;\n"
"}"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/sheet.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/Folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/diskette.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon2);
        actionOpen_PointClouds = new QAction(MainWindow);
        actionOpen_PointClouds->setObjectName(QStringLiteral("actionOpen_PointClouds"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/cloud.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_PointClouds->setIcon(icon3);
        actionOpen_Mesh = new QAction(MainWindow);
        actionOpen_Mesh->setObjectName(QStringLiteral("actionOpen_Mesh"));
        actionOpen_Mesh->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("QMainWindow\n"
"{\n"
"    background-color: #ecf0f5;\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        scanningGroupBox = new QGroupBox(centralWidget);
        scanningGroupBox->setObjectName(QStringLiteral("scanningGroupBox"));
        scanningGroupBox->setMinimumSize(QSize(500, 0));
        scanningGroupBox->setMaximumSize(QSize(500, 16777215));
        verticalLayout = new QVBoxLayout(scanningGroupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        preview_window = new QLabel(scanningGroupBox);
        preview_window->setObjectName(QStringLiteral("preview_window"));
        preview_window->setMinimumSize(QSize(480, 360));
        preview_window->setMaximumSize(QSize(480, 360));
        preview_window->setStyleSheet(QLatin1String("QLabel {\n"
"    border: 2px solid lightgray;\n"
"    background-color: white;\n"
"}"));

        verticalLayout->addWidget(preview_window);

        label_simple_scanning = new QLabel(scanningGroupBox);
        label_simple_scanning->setObjectName(QStringLiteral("label_simple_scanning"));
        QFont font;
        font.setFamily(QStringLiteral("Open Sans"));
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label_simple_scanning->setFont(font);

        verticalLayout->addWidget(label_simple_scanning);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        start_preview = new QPushButton(scanningGroupBox);
        start_preview->setObjectName(QStringLiteral("start_preview"));
        start_preview->setEnabled(true);
        start_preview->setCursor(QCursor(Qt::PointingHandCursor));
        start_preview->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #c0cbd3;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: #748896;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #748896;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout->addWidget(start_preview);

        start_scanning = new QPushButton(scanningGroupBox);
        start_scanning->setObjectName(QStringLiteral("start_scanning"));
        start_scanning->setEnabled(true);
        start_scanning->setCursor(QCursor(Qt::PointingHandCursor));
        start_scanning->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #c0cbd3;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: #748896;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #748896;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout->addWidget(start_scanning);


        verticalLayout->addLayout(horizontalLayout);

        advanced_scanning = new QPushButton(scanningGroupBox);
        advanced_scanning->setObjectName(QStringLiteral("advanced_scanning"));
        advanced_scanning->setEnabled(true);
        advanced_scanning->setCursor(QCursor(Qt::PointingHandCursor));
        advanced_scanning->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #c0cbd3;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: #748896;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #748896;\n"
"    border-style: inset;\n"
"}"));

        verticalLayout->addWidget(advanced_scanning);

        verticalSpacer = new QSpacerItem(20, 141, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_3->addWidget(scanningGroupBox);

        reconstructionGroupBox = new QGroupBox(centralWidget);
        reconstructionGroupBox->setObjectName(QStringLiteral("reconstructionGroupBox"));
        verticalLayout_2 = new QVBoxLayout(reconstructionGroupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(reconstructionGroupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(430, 430));
        widget->setStyleSheet(QLatin1String("QWidget {\n"
"    border: 2px solid lightgray;\n"
"    background-color: white;\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        vtkWindow = new QVTKWidget(widget);
        vtkWindow->setObjectName(QStringLiteral("vtkWindow"));
        vtkWindow->setMinimumSize(QSize(320, 320));
        vtkWindow->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(vtkWindow, 0, 0, 1, 1);


        verticalLayout_2->addWidget(widget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        progressBar = new QProgressBar(reconstructionGroupBox);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        QFont font1;
        font1.setFamily(QStringLiteral("Open Sans"));
        font1.setBold(true);
        font1.setWeight(75);
        progressBar->setFont(font1);
        progressBar->setStyleSheet(QLatin1String("QProgressBar::chunk {\n"
"    background-color: #05B8CC;\n"
"    width: 20px;\n"
"}"));
        progressBar->setValue(0);

        horizontalLayout_4->addWidget(progressBar);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        get_3D_model = new QPushButton(reconstructionGroupBox);
        get_3D_model->setObjectName(QStringLiteral("get_3D_model"));
        get_3D_model->setEnabled(true);
        get_3D_model->setCursor(QCursor(Qt::PointingHandCursor));
        get_3D_model->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #c0cbd3;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: #748896;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #748896;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout_6->addWidget(get_3D_model);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout_3->addWidget(reconstructionGroupBox);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 470));
        tabWidget->setMaximumSize(QSize(180, 470));
        tabPointClouds = new QWidget();
        tabPointClouds->setObjectName(QStringLiteral("tabPointClouds"));
        tabPointClouds->setStyleSheet(QLatin1String("QWidget {\n"
"background-color: white;\n"
"}"));
        ListGroupBox = new QGroupBox(tabPointClouds);
        ListGroupBox->setObjectName(QStringLiteral("ListGroupBox"));
        ListGroupBox->setGeometry(QRect(0, 0, 180, 521));
        ListGroupBox->setMinimumSize(QSize(150, 400));
        ListGroupBox->setMaximumSize(QSize(180, 16777215));
        verticalLayout_4 = new QVBoxLayout(ListGroupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        list_pc = new QLabel(ListGroupBox);
        list_pc->setObjectName(QStringLiteral("list_pc"));
        list_pc->setFont(font);

        verticalLayout_4->addWidget(list_pc);

        listPointClouds = new QListView(ListGroupBox);
        listPointClouds->setObjectName(QStringLiteral("listPointClouds"));
        listPointClouds->setMinimumSize(QSize(150, 350));
        listPointClouds->setMaximumSize(QSize(170, 16777215));
        listPointClouds->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listPointClouds->setProperty("isWrapping", QVariant(false));
        listPointClouds->setUniformItemSizes(false);
        listPointClouds->setWordWrap(false);

        verticalLayout_4->addWidget(listPointClouds);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        deleteAllPointClouds = new QPushButton(ListGroupBox);
        deleteAllPointClouds->setObjectName(QStringLiteral("deleteAllPointClouds"));
        deleteAllPointClouds->setEnabled(true);
        deleteAllPointClouds->setCursor(QCursor(Qt::PointingHandCursor));
        deleteAllPointClouds->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #c0cbd3;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: #748896;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #748896;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout_2->addWidget(deleteAllPointClouds);

        deletePointCloud = new QPushButton(ListGroupBox);
        deletePointCloud->setObjectName(QStringLiteral("deletePointCloud"));
        deletePointCloud->setEnabled(true);
        deletePointCloud->setCursor(QCursor(Qt::PointingHandCursor));
        deletePointCloud->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #c0cbd3;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: #748896;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #748896;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout_2->addWidget(deletePointCloud);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        tabWidget->addTab(tabPointClouds, QString());
        tabMeshes = new QWidget();
        tabMeshes->setObjectName(QStringLiteral("tabMeshes"));
        ListGroupBox_2 = new QGroupBox(tabMeshes);
        ListGroupBox_2->setObjectName(QStringLiteral("ListGroupBox_2"));
        ListGroupBox_2->setGeometry(QRect(0, 0, 180, 511));
        ListGroupBox_2->setMinimumSize(QSize(150, 0));
        ListGroupBox_2->setMaximumSize(QSize(180, 16777215));
        verticalLayout_3 = new QVBoxLayout(ListGroupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        list_mesh = new QLabel(ListGroupBox_2);
        list_mesh->setObjectName(QStringLiteral("list_mesh"));
        list_mesh->setFont(font);

        verticalLayout_3->addWidget(list_mesh);

        listMeshes = new QListView(ListGroupBox_2);
        listMeshes->setObjectName(QStringLiteral("listMeshes"));
        listMeshes->setMinimumSize(QSize(150, 350));
        listMeshes->setMaximumSize(QSize(170, 16777215));
        listMeshes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listMeshes->setProperty("isWrapping", QVariant(false));
        listMeshes->setUniformItemSizes(false);
        listMeshes->setWordWrap(false);

        verticalLayout_3->addWidget(listMeshes);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        deleteAllMeshes = new QPushButton(ListGroupBox_2);
        deleteAllMeshes->setObjectName(QStringLiteral("deleteAllMeshes"));
        deleteAllMeshes->setEnabled(true);
        deleteAllMeshes->setCursor(QCursor(Qt::PointingHandCursor));
        deleteAllMeshes->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #c0cbd3;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: #748896;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #748896;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout_5->addWidget(deleteAllMeshes);

        deleteMesh = new QPushButton(ListGroupBox_2);
        deleteMesh->setObjectName(QStringLiteral("deleteMesh"));
        deleteMesh->setEnabled(true);
        deleteMesh->setCursor(QCursor(Qt::PointingHandCursor));
        deleteMesh->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #c0cbd3;\n"
"    border-style: outset;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    border-color: #748896;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #748896;\n"
"    border-style: inset;\n"
"}"));

        horizontalLayout_5->addWidget(deleteMesh);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 58, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        tabWidget->addTab(tabMeshes, QString());

        verticalLayout_5->addWidget(tabWidget);

        verticalSpacer_4 = new QSpacerItem(20, 148, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);


        horizontalLayout_3->addLayout(verticalLayout_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1174, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen_PointClouds);
        menuFile->addAction(actionOpen_Mesh);
        menuFile->addAction(actionSave_as);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Sculptura", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save Mesh as", 0));
        actionOpen_PointClouds->setText(QApplication::translate("MainWindow", "Open PointClouds", 0));
        actionOpen_Mesh->setText(QApplication::translate("MainWindow", "Open Mesh", 0));
        scanningGroupBox->setTitle(QString());
        preview_window->setText(QString());
        label_simple_scanning->setText(QApplication::translate("MainWindow", "Simple scanning", 0));
        start_preview->setText(QApplication::translate("MainWindow", "Start preview", 0));
        start_scanning->setText(QApplication::translate("MainWindow", "Start scanning", 0));
        advanced_scanning->setText(QApplication::translate("MainWindow", "Advanced scanning", 0));
        reconstructionGroupBox->setTitle(QString());
        get_3D_model->setText(QApplication::translate("MainWindow", "Get 3D model", 0));
        ListGroupBox->setTitle(QString());
        list_pc->setText(QApplication::translate("MainWindow", "List of Point Clouds", 0));
        deleteAllPointClouds->setText(QApplication::translate("MainWindow", "Delete all", 0));
        deletePointCloud->setText(QApplication::translate("MainWindow", "Delete", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabPointClouds), QApplication::translate("MainWindow", "PC", 0));
        ListGroupBox_2->setTitle(QString());
        list_mesh->setText(QApplication::translate("MainWindow", "List of Meshes", 0));
        deleteAllMeshes->setText(QApplication::translate("MainWindow", "Delete all", 0));
        deleteMesh->setText(QApplication::translate("MainWindow", "Delete", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabMeshes), QApplication::translate("MainWindow", "MESH", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
