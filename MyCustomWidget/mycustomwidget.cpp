#include "mycustomwidget.h"
#include "ui_mycustomwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPolygonF>
#include <cmath>

MyCustomWidget::MyCustomWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyCustomWidget)
{
    ui->setupUi(this);

    // Начальный текст для лейблов
    ui->labelR->setText("Red: 0");
    ui->labelG->setText("Green: 0");
    ui->labelB->setText("Blue: 0");
}

MyCustomWidget::~MyCustomWidget()
{
    delete ui;
}

// Отрисовка треугольника Максвелла
void MyCustomWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Рассчитываем вершины треугольника с отступами от краев виджета
    int margin = 20;
    vertexR = QPointF(width() / 2.0, margin);                  // Верхняя (Красный)
    vertexG = QPointF(margin, height() - margin);              // Левая нижняя (Зеленый)
    vertexB = QPointF(width() - margin, height() - margin);    // Правая нижняя (Синий)

    // Чтобы сделать честный градиент Максвелла на чистом Qt, проще всего
    // отрисовать треугольник попиксельно или использовать полигон с фоном.
    // Для демонстрации нарисуем контур треугольника и зальем его базовым градиентом.
    QPolygonF triangle;
    triangle << vertexR << vertexG << vertexB;

    // Ограничиваем область рисования только внутри треугольника
    painter.setClipRegion(QRegion(triangle.toPolygon()));


    // Попиксельно закрашиваем внутреннюю область (для плавного цветового треугольника)
    // Внимание: для очень больших виджетов это может слегка притормаживать, но дает точный цвет
    for (int y = margin; y < height() - margin; ++y) {
        for (int x = margin; x < width() - margin; ++x) {
            QPointF p(x, y);
            if (triangle.containsPoint(p, Qt::OddEvenFill)) {
                painter.setPen(getColorAtPoint(p));
                painter.drawPoint(x, y);
            }
        }
    }
}

// Обработка нажатия мыши
void MyCustomWidget::mousePressEvent(QMouseEvent *event)
{
    QPointF clickPos = event->position();
    QPolygonF triangle;
    triangle << vertexR << vertexG << vertexB;

    // Проверяем, что клик был именно внутри треугольника
    if (triangle.containsPoint(clickPos, Qt::OddEvenFill)) {
        QColor selectedColor = getColorAtPoint(clickPos);

        // Устанавливаем составляющие цвета в QLabel
        ui->labelR->setText(QString("Red: %1").arg(selectedColor.red()));
        ui->labelG->setText(QString("Green: %1").arg(selectedColor.green()));
        ui->labelB->setText(QString("Blue: %1").arg(selectedColor.blue()));

        // Испускаем сигнал наружу для глобального проекта
        emit colorSelected(selectedColor);

        // Обновляем виджет, если нужно что-то перерисовать (например, маркер клика)
        update();
    }
}

// Математика расчета цвета по барицентрическим координатам
QColor MyCustomWidget::getColorAtPoint(const QPointF &p)
{
    // Считаем определитель для барицентрических координат
    double det = (vertexG.y() - vertexB.y()) * (vertexR.x() - vertexB.x()) +
                 (vertexB.x() - vertexG.x()) * (vertexR.y() - vertexB.y());

    if (std::abs(det) < 0.0001) return QColor(Qt::black);

    // Вычисляем веса (коэффициенты близости к каждой из вершин)
    double wR = ((vertexG.y() - vertexB.y()) * (p.x() - vertexB.x()) +
                 (vertexB.x() - vertexG.x()) * (p.y() - vertexB.y())) / det;

    double wG = ((vertexB.y() - vertexR.y()) * (p.x() - vertexB.x()) +
                 (vertexR.x() - vertexB.x()) * (p.y() - vertexB.y())) / det;

    double wB = 1.0 - wR - wG;

    // Ограничиваем значения от 0.0 до 1.0 на случай погрешностей на границах
    wR = std::max(0.0, std::min(1.0, wR));
    wG = std::max(0.0, std::min(1.0, wG));
    wB = std::max(0.0, std::min(1.0, wB));

    // Превращаем веса в стандартные RGB компоненты (0-255)
    int r = static_cast<int>(wR * 255);
    int g = static_cast<int>(wG * 255);
    int b = static_cast<int>(wB * 255);

    return QColor(r, g, b);
}
