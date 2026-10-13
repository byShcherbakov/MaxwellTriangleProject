#ifndef MYCUSTOMWIDGET_H
#define MYCUSTOMWIDGET_H

#include <QWidget>
#include <QColor>
#include <QPointF>
#include "MyCustomWidget_global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MyCustomWidget; }
QT_END_NAMESPACE

class MYCUSTOMWIDGET_EXPORT MyCustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyCustomWidget(QWidget *parent = nullptr);
    ~MyCustomWidget();

signals:
    // Сигнал, который виджет будет испускать при клике
    void colorSelected(const QColor &color);

protected:
    // Переопределяем системные события
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MyCustomWidget *ui;

    // Вспомогательная функция для расчета RGB по координатам внутри треугольника
    QColor getColorAtPoint(const QPointF &p);

    // Вершины треугольника Максвелла (Красный, Зеленый, Синий)
    QPointF vertexR;
    QPointF vertexG;
    QPointF vertexB;
};

#endif // MYCUSTOMWIDGET_H
