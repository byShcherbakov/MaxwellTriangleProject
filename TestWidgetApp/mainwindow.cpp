#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mycustomwidget.h" // Подключаем заголовочный файл нашего виджета из библиотеки

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем объект нашего виджета, передавая текущее окно в качестве родителя
    MyCustomWidget *triangleWidget = new MyCustomWidget(this);

    // Устанавливаем его как центральный виджет главного окна, чтобы он растянулся на весь экран
    setCentralWidget(triangleWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
