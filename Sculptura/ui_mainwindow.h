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
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_as;
    QAction *actionOpen_PointClouds;
    QWidget *centralWidget;
    QLabel *label_brightness;
    QLabel *label_contrast;
    QPushButton *advanced_scanning;
    QPushButton *get_3D_model;
    QGroupBox *Box_pointclouds;
    QLabel *list_pc;
    QListView *listView_2;
    QPushButton *selectall;
    QPushButton *deleteall;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *vtk;
    QProgressBar *progressBar;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_simple_scanning;
    QPushButton *start_preview;
    QPushButton *stop_scanning;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider_brightness;
    QSlider *horizontalSlider_contrast;
    QLabel *preview_window;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuPointClouds;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1084, 627);
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("QMainWindow\n"
"{\n"
"    background-color: #ecf0f5;\n"
"}"));
        label_brightness = new QLabel(centralWidget);
        label_brightness->setObjectName(QStringLiteral("label_brightness"));
        label_brightness->setGeometry(QRect(21, 391, 80, 20));
        QFont font;
        font.setFamily(QStringLiteral("Open Sans"));
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label_brightness->setFont(font);
        label_contrast = new QLabel(centralWidget);
        label_contrast->setObjectName(QStringLiteral("label_contrast"));
        label_contrast->setGeometry(QRect(20, 420, 66, 20));
        label_contrast->setFont(font);
        advanced_scanning = new QPushButton(centralWidget);
        advanced_scanning->setObjectName(QStringLiteral("advanced_scanning"));
        advanced_scanning->setEnabled(true);
        advanced_scanning->setGeometry(QRect(20, 520, 341, 31));
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
        get_3D_model = new QPushButton(centralWidget);
        get_3D_model->setObjectName(QStringLiteral("get_3D_model"));
        get_3D_model->setEnabled(true);
        get_3D_model->setGeometry(QRect(410, 390, 341, 31));
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
        Box_pointclouds = new QGroupBox(centralWidget);
        Box_pointclouds->setObjectName(QStringLiteral("Box_pointclouds"));
        Box_pointclouds->setGeometry(QRect(790, 10, 211, 361));
        list_pc = new QLabel(Box_pointclouds);
        list_pc->setObjectName(QStringLiteral("list_pc"));
        list_pc->setGeometry(QRect(10, 10, 171, 20));
        list_pc->setFont(font);
        listView_2 = new QListView(Box_pointclouds);
        listView_2->setObjectName(QStringLiteral("listView_2"));
        listView_2->setGeometry(QRect(10, 40, 191, 261));
        listView_2->setProperty("isWrapping", QVariant(false));
        listView_2->setUniformItemSizes(false);
        selectall = new QPushButton(Box_pointclouds);
        selectall->setObjectName(QStringLiteral("selectall"));
        selectall->setEnabled(true);
        selectall->setGeometry(QRect(10, 310, 81, 31));
        selectall->setCursor(QCursor(Qt::PointingHandCursor));
        selectall->setStyleSheet(QLatin1String("QPushButton {\n"
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
        deleteall = new QPushButton(Box_pointclouds);
        deleteall->setObjectName(QStringLiteral("deleteall"));
        deleteall->setEnabled(true);
        deleteall->setGeometry(QRect(110, 310, 81, 31));
        deleteall->setCursor(QCursor(Qt::PointingHandCursor));
        deleteall->setStyleSheet(QLatin1String("QPushButton {\n"
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
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(400, 10, 381, 361));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        vtk = new QWidget(layoutWidget);
        vtk->setObjectName(QStringLiteral("vtk"));
        vtk->setStyleSheet(QLatin1String("QWidget {\n"
"    border: 2px solid lightgray;\n"
"    background-color: white;\n"
"}"));
        progressBar = new QProgressBar(vtk);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(157, 332, 131, 21));
        QFont font1;
        font1.setFamily(QStringLiteral("Open Sans"));
        font1.setBold(true);
        font1.setWeight(75);
        progressBar->setFont(font1);
        progressBar->setStyleSheet(QLatin1String("QProgressBar::chunk {\n"
"    background-color: #05B8CC;\n"
"    width: 20px;\n"
"}"));
        progressBar->setValue(24);

        horizontalLayout_2->addWidget(vtk);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 470, 363, 35));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_simple_scanning = new QLabel(layoutWidget1);
        label_simple_scanning->setObjectName(QStringLiteral("label_simple_scanning"));
        label_simple_scanning->setFont(font);

        horizontalLayout->addWidget(label_simple_scanning);

        start_preview = new QPushButton(layoutWidget1);
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

        stop_scanning = new QPushButton(layoutWidget1);
        stop_scanning->setObjectName(QStringLiteral("stop_scanning"));
        stop_scanning->setEnabled(true);
        stop_scanning->setCursor(QCursor(Qt::PointingHandCursor));
        stop_scanning->setStyleSheet(QLatin1String("QPushButton {\n"
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

        horizontalLayout->addWidget(stop_scanning);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(108, 394, 281, 53));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_brightness = new QSlider(layoutWidget2);
        horizontalSlider_brightness->setObjectName(QStringLiteral("horizontalSlider_brightness"));
        horizontalSlider_brightness->setCursor(QCursor(Qt::PointingHandCursor));
        horizontalSlider_brightness->setStyleSheet(QLatin1String("QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 18px;\n"
"    margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 5px;\n"
"}"));
        horizontalSlider_brightness->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider_brightness);

        horizontalSlider_contrast = new QSlider(layoutWidget2);
        horizontalSlider_contrast->setObjectName(QStringLiteral("horizontalSlider_contrast"));
        horizontalSlider_contrast->setCursor(QCursor(Qt::PointingHandCursor));
        horizontalSlider_contrast->setStyleSheet(QLatin1String("QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 18px;\n"
"    margin: -2px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 5px;\n"
"}"));
        horizontalSlider_contrast->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider_contrast);

        preview_window = new QLabel(centralWidget);
        preview_window->setObjectName(QStringLiteral("preview_window"));
        preview_window->setGeometry(QRect(10, 10, 371, 361));
        preview_window->setStyleSheet(QLatin1String("QLabel {\n"
"    border: 2px solid lightgray;\n"
"    background-color: white;\n"
"}"));
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        label_brightness->raise();
        label_contrast->raise();
        advanced_scanning->raise();
        get_3D_model->raise();
        Box_pointclouds->raise();
        preview_window->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1084, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuPointClouds = new QMenu(menuBar);
        menuPointClouds->setObjectName(QStringLiteral("menuPointClouds"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuPointClouds->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_as);
        menuPointClouds->addAction(actionOpen_PointClouds);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Sculptura", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as", 0));
        actionOpen_PointClouds->setText(QApplication::translate("MainWindow", "Open PointClouds", 0));
        label_brightness->setText(QApplication::translate("MainWindow", "Brightness", 0));
        label_contrast->setText(QApplication::translate("MainWindow", "Contrast", 0));
        advanced_scanning->setText(QApplication::translate("MainWindow", "Advanced scanning", 0));
        get_3D_model->setText(QApplication::translate("MainWindow", "Get 3D model", 0));
        Box_pointclouds->setTitle(QString());
        list_pc->setText(QApplication::translate("MainWindow", "List of Point Clouds", 0));
        selectall->setText(QApplication::translate("MainWindow", "Select all", 0));
        deleteall->setText(QApplication::translate("MainWindow", "Delete all", 0));
        label_simple_scanning->setText(QApplication::translate("MainWindow", "Simple scanning", 0));
        start_preview->setText(QApplication::translate("MainWindow", "Start preview", 0));
        stop_scanning->setText(QApplication::translate("MainWindow", "Start scanning", 0));
        preview_window->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuPointClouds->setTitle(QApplication::translate("MainWindow", "PointClouds", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
