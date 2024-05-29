#include <cmath>
#include <iostream>
using namespace std;

// Определение класса Point для представления точек на плоскости
class Point {
public:
    double x, y; // Координаты точки

    // Конструктор для инициализации точки с заданными координатами или значениями по умолчанию (0, 0)
    Point(double x = 0, double y = 0);

    // Метод для перемещения точки на заданные значения по оси x и y
    void move(double dx, double dy);
};

// Определение интерфейса для базовой фигуры
class IBaseShape {
public:
    // Виртуальные методы для отрисовки, стирания, перемещения и вращения фигуры
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;

    // Виртуальный деструктор для правильного удаления объектов классов-наследников
    virtual ~IBaseShape() {}
};

// Определение класса Line, наследующего интерфейс базовой фигуры
class Line : public IBaseShape {
protected:
    Point points[2]; // Массив из двух точек, определяющих линию

public:
    // Конструктор для инициализации линии с двумя точками
    Line(Point p1, Point p2);

    // Переопределение виртуальных методов базового класса
    void erase() override;
    void draw() override;
    void move(double dx, double dy) override;
    void rotate(double angle) override;
};

// Определение класса Square, наследующего интерфейс базовой фигуры
class Square : public IBaseShape {
public:
    Point points[4]; // Массив из четырех точек, определяющих квадрат

    // Конструктор для инициализации квадрата с четырьмя точками
    Square(Point p1, Point p2, Point p3, Point p4);

    // Переопределение виртуальных методов базового класса
    void draw() override;
    void erase() override;
    void move(double dx, double dy) override;
    void rotate(double angle);
};

class Rectangle : public IBaseShape {
public:
    Point points[4]; // Массив для хранения четырех точек
public:
    Rectangle(Point p1, Point p2, Point p3, Point p4);

    void erase() override; // Метод для стирания
    void draw() override; // Метод для отрисовки
    void move(double dx, double dy) override; // Метод для перемещения
    void rotate(double angle) override; // Метод для поворота
};
class Parallelogram : public IBaseShape {
public:
    Point points[4];
public:
    Parallelogram(Point p1, Point p2, Point p3, Point p4);

    void erase() override;

    void draw() override;

    void move(double dx, double dy) override;

    void rotate(double angle) override;
};

class Rhombus : public IBaseShape {
public:
    Point points[4];
public:
    Rhombus(Point p1, Point p2, Point p3, Point p4);

    void erase() override;

    void draw() override;

    void move(double dx, double dy) override;

    void rotate(double angle) override;
};

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;  // Инициализация координат точки
}

void Point::move(double dx, double dy) {
    x += dx;
    y += dy; // Изменение координат точки при перемещении
}

Line::Line(Point p1, Point p2) {
    points[0] = p1;    points[1] = p2; // Установка начальной и конечной точек линии
}

void Line::draw() {
    cout << "Line was drew" << endl; // Вывод сообщения о рисовании
}

void Line::erase() {
    cout << "Line was erased" << endl; // Вывод сообщения об стирании
}

void Line::move(double dx, double dy) {
    for (auto &point: points) {        point.move(dx, dy);    } // Перемещение каждой точки линии
}

const double M_PI = 3.14; // Значение числа Пи

void Line::rotate(double angle) {
    double angleR = angle * M_PI / 180; // Перевод угла в радианы
    double centerX, centerY; // Координаты центра вращения
    for (auto &point: points) {        centerX += point.x;        centerY += point.y;    } // Вычисление центра вращения
    centerX /= 2;    centerY /= 2; // Нахождение средних координат
    for (auto &point: points) {
        double oldX = point.x;        point.x = (point.x - centerX) * cos(angleR) - (point.y - centerY) * sin(angleR) + centerX;
        point.y = (oldX - centerX) * sin(angleR) + (point.y - centerY) * cos(angleR) + centerY;    } // Поворот каждой точки линии и вывод координат
}

Square::Square(Point p1, Point p2, Point p3, Point p4) {
    points[0] = p1;    points[1] = p2;
    points[2] = p3;    points[3] = p4; // Установка четырех точек квадрата
}
void Square::draw() {
    cout << "The square is drew" << endl; // Вывод сообщения о рисовании квадрата
}

void Square::erase() {
    cout << "The square is erased" << endl; // Вывод сообщения об стирании квадрата
}

void Square::move(double dx, double dy) {
    for (auto &point: points) {        point.move(dx, dy);        cout << "(" << point.x << ", " << point.y << ")" << endl;    } // Перемещение каждой точки квадрата и вывод координат
}

void Square::rotate(double angle) {
    double angleR = angle * M_PI / 180;    double centerX, centerY;
    centerX = (points[0].x + points[2].x) / 2;    centerY = (points[0].y + points[2].y) / 2; // Вычисление центра квадрата
    double sinA = sin(angleR);    double cosA = cos(angleR); // Синус и косинус угла
    for (auto &point: points) {
        double oldX = point.x;        double oldY = point.y; // Сохранение старых координат
        point.x = (oldX - centerX) * cosA - (oldY - centerY) * sinA + centerX; // Поворот точки вокруг центра
        point.y = (oldX - centerX) * sinA + (oldY - centerY) * cosA + centerY;        cout << "(" << point.x << ", " << point.y << ")" << endl;
    } // Поворот каждой точки квадрата и вывод координат
}
Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4) {
    points[0] = p1;    points[1] = p2;
    points[2] = p3;    points[3] = p4; // Установка четырех точек прямоугольника
}

void Rectangle::draw() {
    cout << "Rectangle was drew" << endl; // Вывод сообщения о рисовании прямоугольника
}

void Rectangle::erase() {
    cout << "Rectangle was erased" << endl; // Вывод сообщения об стирании прямоугольника
}

void Rectangle::move(double dx, double dy) {
    for (auto &point: points) {        point.move(dx, dy);        cout << "(" << point.x << ", " << point.y << ")" << endl;    } // Перемещение каждой точки прямоугольника и вывод координат
}

// Определение метода для поворота прямоугольника на заданный угол
// Пересчет координат точек прямоугольника после поворота вокруг центра
// Вывод новых координат точек и центра прямоугольника
void Rectangle::rotate(double angle) {
    double angleR = angle * M_PI / 180;
    double centerX, centerY;
    centerX = (points[0].x + points[2].x) / 2;
    centerY = (points[0].y + points[2].y) / 2;
    double sinA = sin(angleR);
    double cosA = cos(angleR);
    for (auto &point: points) {
        double oldX = point.x;
        double oldY = point.y;
        point.x = (oldX - centerX) * cosA - (oldY - centerY) * sinA + centerX;
        point.y = (oldX - centerX) * sinA + (oldY - centerY) * cosA + centerY;
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
    cout << centerX << endl;
    cout << centerY;
}

// Определение конструктора для параллелограмма на основе четырех точек
Parallelogram::Parallelogram(Point p1, Point p2, Point p3, Point p4) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}

// Вывод сообщения о нарисованном параллелограмме
void Parallelogram::draw() {
    cout << "Parallelogram was drew" << endl;
}

// Вывод сообщения об удаленном параллелограмме
void Parallelogram::erase() {
    cout << "Parallelogram was erased" << endl;
}

// Определение метода для перемещения параллелограмма на вектор (dx, dy)
// И вывод новых координат точек
void Parallelogram::move(double dx, double dy) {
    for (auto &point: points) {
        point.move(dx, dy);
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
}

// Определение метода для поворота ромба на заданный угол
// Аналогично реализации поворота прямоугольника
void Rhombus::rotate(double angle) {
    double angleR = angle * M_PI / 180;
    double centerX, centerY;
    centerX = (points[0].x + points[2].x) / 2;
    centerY = (points[0].y + points[2].y) / 2;
    double sinA = sin(angleR);
    double cosA = cos(angleR);
    for (auto &point: points) {
        double oldX = point.x;
        double oldY = point.y;
        point.x = (oldX - centerX) * cosA - (oldY - centerY) * sinA + centerX;
        point.y = (oldX - centerX) * sinA + (oldY - centerY) * cosA + centerY;
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
}

// Определение конструктора для ромба на основе четырех точек
Rhombus::Rhombus(Point p1, Point p2, Point p3, Point p4) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}

// Вывод сообщения о нарисованном ромбе
void Rhombus::draw() {
    cout << "Parallelogram was drew" << endl;
}

// Вывод сообщения об удаленном ромбе
void Rhombus::erase() {
    cout << "Parallelogram was erased" << endl;
}

// Метод для перемещения ромба на вектор (dx, dy)
// И вывод новых координат точек
void Rhombus::move(double dx, double dy) {
    for (auto &point: points) {
        point.move(dx, dy);
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
}


int main() {
    //Square square(Point(0, 0), Point(40, 0), Point(40, 40), Point(0, 40));
    //square.move(2,2);
    //square.rotate(90);
    //square.erase();

    //Rectangle rectangle(Point(5, 5), Point(25, 5), Point(25, 15), Point(5, 15));
    //rectangle.move(2,2);
    //rectangle.rotate(180);

    //Parallelogram parallelogram(Point(5, 5), Point(25, 5), Point(30, 15), Point(10, 15));
    //parallelogram.move(2,2);
    //parallelogram.rotate(90);

    //Rhombus Rhombus(Point(20, 10), Point(10, 30), Point(20, 50), Point(30, 30));
    //Rhombus.move(2,2);
    //Rhombus.rotate(90);

}

