#include <iostream>
#include <math.h>
using namespace std;

class vector{
private:
  int dim; // размерность вектора, то, скольки-мерное пространство. dim = dimencion
  double* v; // звездочка говорит о том, что это динамический массив, одномерный массив v (есть только кол-во эл-тов этого массива) данных типа double
  int number; // номер - нужно чтобы отличать один вектор от другого без распечатывания
  friend vector& operator-(vector& op, vector& vect);  // вычитание одного вектора из другого
  friend vector& operator*(double n, vector& vect);  // умножение вектора на число
//Дружественные функции - это функции, которые не являются членами класса, однако имеют доступ к его закрытым членам - переменным и функциям, которые имеют спецификатор private.
  friend class matr;
  friend void printSLU(class matr& A, vector& B);
  friend void jacobi(matr& A, vector& B);


public:
 static int count; // Место для статической переменной выделяется
    // только один раз, и оно используется в течение всей программы.
    // Как только переменная объявлена, она существует до завершения
    // работы программы
    // нам надо хранить количество созданных объектов. Такое количество относится классу, однако не зависит от конкретного объекта.
    vector(){
        count++; // каждый раз, когда мы обращаемся к конструктору - каунт
           // увеличивается.
        number = count; // менять приватную переменную можно из любой функции внутри
                  // класса. Через функцию
  //можно, напрямую нельзя
        cout << "Constructor vector() made vector #" << number << endl;
        dim = 0;
        v = new double[dim]; // Мы создали массив, длина которого dim
    }; // Конструктор без параметров - пустой массив, ВСЕГДА В НАШЕМ СЛУЧАЕ, МЫ ТАК РЕШИЛИ
    vector(int d, double* var){
      count++;
      number = count;
      cout << "Constructor vector(int d, double* var) made vector #" << number<< endl;
      dim = d;
      v = new double[d];
      for (int i = 0; i < d; i++) {
        v[i] = var[i];
      }
    }; //просто конструктор со всеми входными данными
    vector(vector& vect){
      // Передали вектор в конструктор, который создаёт ещё один ТАКОЙ ЖЕ
    count++;
    number = count;
    cout << "Constructor vector(vector& vect) made vector #" << number
    << "by coping vector #" << vect.number << endl;
    // vect.number - номер того вектора, который мы копируем
    dim = vect.dim; // Размерность взяли из копируемого вектора. Обратились через
                    // точку. По ссылке.
    v = new double[dim];
    for (int i = 0; i < dim; i++) { // теперь мы заполняем массив,
    //берём первый элемент другого вектора и приравниваем к нему наш первый
    //элемент нового вектора А = (х1,х2,х3). И эти значения мы перекладываем в
    //какое-то С, которое теперь тоже равно (x1,x2,x3).
      v[i] = vect.v[i];
      }
    }; //передали по ссылке какой-то вектор; конструктор копирования
    vector(int d){
        count++;
        number = count;
        cout << "Constructor vector(int d) made vector #" << number << endl;
        dim = d;
        v = new double[d];
        for (int i = 0; i < d; i++) {
          v[i] = 0;
        }
    };  // конструктор, принимающий размерность и заполняющий вектор нулями
    ~vector(){
      cout << "Destructor ~vector() delete vector #" << number << endl;
      delete[] v; //освобождаем выделенную под массив память
    };  //деструктор

    void print(){if (dim != 0) {
        cout << "Vector #" << number << " (";
        for (int i = 0; i < dim; i++) {
          if (i == dim - 1) {
            cout << v[i];
          } else {
            cout << v[i] << ",";
          }
        }
        cout << ")" << endl;
      } else {
        cout << "Vector #" << number << " with dim = 0" << endl;
      }
    };  // процедура распечатывания

    double operator*(vector& vect);  // умножение вектора на вектор
    double operator[](int i);  // извлечь определённую координату вектора
    vector& operator*(int n);  // умножение вектора на число
    vector& operator+(vector& vect);  // сложение двух векторов
    vector& operator-();  // отрицаниие всех координат вектора
    vector& operator=(vector& vect);  // vector& operator=(const vector& vect);
};

// статическую переменную нельзя задавать значением внтури класса, так что:
int vector::count = 0;  // начинаем с 0 нумерацию векторов

//ТУТ ИДУТ ОПЕРАТОРЫ ИЗ КЛАССА ВЕКТОР, У НИХ УКАЗАНО, ЧТО ОНИ ИЗ КЛАССА ВЕКТОР
//ИМЕННО ИЗ КЛАССА ВЕКТОР, ОНИ НЕ ЯВЛЯЮТСЯ ДРУЖЕСТВЕННЫМИ
vector& vector::operator=(vector& vect) {  // присваивание одного вектора другому
    cout << "Equating vector #" << number << " to vector #" << vect.number << endl;
    for (int i = 0; i < vect.dim; i++) {
        this->v[i] = vect.v[i];
    }
    return *this; //Ключевое слово this представляет указатель на текущий объект данного класса. Соответственно через this мы можем обращаться внутри класса к любым его членам. С его помощью можно возвращать текущий объект класса. С помощью указателя this возвращаем ссылку на объект текущего класса
}
double vector::operator*(vector& vect) {
  if (dim != vect.dim){
    cout << "Error: размерности векторы не равны" << endl;
  }
  else {
    cout << "Scalar Multiplication (vector #" << number << ", vector #" << vect.number << ") " << endl;
    static double tmp = 0;
    for (int i = 0; i < dim; i++) {
        tmp += v[i] * vect.v[i];
    }
    return tmp;}
}
double vector::operator[](int i) {

    cout << "Getting element " << i << " from vector #" << number << endl;
    return v[i];

}
vector& vector::operator*(int n) {  // умножение вектора на число (не friend)
    cout << "Multiplication vector #" << number << " with number " << n << endl;
    static vector tmp(dim);  // создаём вектор размерности dim, заполненный нулями
     //это было для нового вектора
    for (int i = 0; i < dim; i++) {
      tmp.v[i] = n * v[i];
    }
    //tmp.print();
    return tmp;
  //амперсанд означает, что мы вернём ссылку на объект в качестве результата
  //если его убрать, мы будем возвращать просто объект класса
}
vector& vector::operator+(vector& vect) {
    if (dim != vect.dim){
    cout << "Error: размерности векторы не равны" << endl;
  }
  else{
    cout << "Summarizing vector #" << number << ", vector#" << vect.number << endl;
    static vector tmp(dim);
    for (int i = 0; i < dim; i++) {
    tmp.v[i] = (v[i] + vect.v[i]);
    }
    // tmp.print();
    return tmp;}
}
vector& vector::operator-() {
    cout << "Negation vector #" << number << endl;
    static vector tmp(dim);
    for (int i = 0; i < dim; i++) {
        tmp.v[i] = -v[i];
    }
    //tmp.print();
    return tmp;


} //отрицание вектора

//А ТУТ ДРУЖЕСТВЕННЫЕ, ОНИ НЕОБЯЗАТЕЛЬНО ПРИНАДЛЕЖАТ КЛАССУ ВЕКТОР
vector &operator-(vector &op, vector &vect) {
    if (op.dim != vect.dim){
    cout << "Error: размерности векторы не равны" << endl;
  }
  else{
  cout << "Substraction vector #" << op.number << " from vector #"
       << vect.number << endl;
  static vector tmp(op.dim);
  for (int i = 0; i < op.dim; i++) {
    tmp.v[i] = op.v[i] - vect.v[i];
  }
  // tmp.print();
  return tmp;}
}
vector &operator*(double n, vector &vect) {
  cout << "Multiplication vector #" << vect.number << " with number " << n << endl;
  static vector tmp(vect.dim);
  for (int i = 0; i < vect.dim; i++) {
    tmp.v[i] = vect.v[i] * n;
  }
  return tmp;
}

//МАТРИЦЫЫЫЫЫЫЫЫЫЫ

class matr{
  int dim; //размерность квадратной матрицы
  double **b; //двумерный массив
  int number; //порядковый номер матрицы

  friend matr& operator*(double n, matr& M);
  friend class vector;
  friend void printSLU(matr& A, vector& B);
  friend void jacobi(matr& A, vector& B);
public:
  static int countmatr;//
  matr(int d){
    countmatr++;
  number = countmatr;
  cout << "Constructor matr(int d) made matrix #" << number << endl;
  this->dim = d;
  this->b = new double *[dim];

  for (int i = 0; i < dim; i++) {
    this->b[i] = new double[dim];
    for (int j = 0; j < dim; j++) {
      this->b[i][j] = 0;
    }
  }
  }; // конструктор создает матрицу d*d и заполняет нулями
  matr(int d, double **x){
  countmatr++;
  number = countmatr;
  cout << "Constructor (int d, double** x) made matrix #" << number <<
 endl;
  this->dim = d;
  this->b = new double *[dim];

  for (int i = 0; i < dim; i++) {
    this->b[i] = new double[dim];
    for (int j = 0; j < dim; j++) {
      this->b[i][j] = x[i][j];
    }
  }

  }; // конструктор принимает матрицу размером d*d и размер
  matr(matr &m){
     countmatr++;
  number = countmatr;
  cout << "Constructor matr(matr& m) made matrix #" << number
       << "by coping matrix #" << m.number << endl;
  this->dim = m.dim;
  b = new double *[dim];
  for (int i = 0; i < dim; i++) {
    b[i] = new double[dim];
  }

  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      this->b[i][j] = m.b[i][j];
    }
  }
  }; // конструктор копирования
  matr(int d, int o){
    countmatr++;
    number = countmatr;
    cout << "Constructor matr(int, int) made matrix #" << number << endl;
    dim = d;
    b = new double*[dim];
    for (int i=0; i<dim; i++){
      b[i] = new double[dim];
    }
    for (int i=0; i<dim; i++){
      for (int j=0; j<dim; j++){
        cout << "Enter elem #(" << i << ", " << j << ") : ";
        cin >> b[i][j];
      }
    }
  }; // конструктор с вводом матрицы
  matr(){
      countmatr++;
      number = countmatr;
      cout << "Constructor matr() made matrix #" << number << " with dim = 0"
           << endl;
      dim = 0;
      b = new double *[dim];
      }; // пустой конструктор
  ~matr(){
    cout << "Destructor ~matr() delete matrix #" << number << endl;
    for(int i=0; i < dim; i++){
    delete[] b[i];
    }
    delete[] b;
  }; // деструктор матрицы без утечки памяти

  void print() const{
    cout << "Matrix #" << number << ": \n";
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (i == dim - 1 && j == dim - 1) {
        cout << b[i][j];
      } else {
        cout << b[i][j] << " ";
      }
    }
    cout << endl;
  }
  }; //печатаем матрицу
  matr& obrDiag(matr& m){
    for (int i = 0; i < dim; i++){
      if (m.b[i][i] == 0){
        cout << "ERROR: You can't divide by zero! You have zeros on the main diagonal. Therefore, I am returning your original matrix to you." << endl;
        return m;
      }
    }
    cout << "Obr Diag Matrix #" << m.number << ":\n";
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (i == j) {
                double n = m.b[i][j];
                m.b[i][j] = 1/n;
            }
            else{
                m.b[i][j] = 0;
            }
        }
    }
    return m;
}; // обратная диагональ
  /*matr& plusDiag(matr& m){
  double sum = 0;
  for (int i = 0; i < m.dim; i++)
    {
        for (int j = 0; j < m.dim; j++)
        {
            if (i != j)
            {
                sum += fabs(m.b[i][j]);
            }
        }
    }
    for (int i = 0; i < m.dim; i++){
      for (int j = 0; j < m.dim; j++){
            m.b[i][i] += sum + 1;
      }
    }

    return m;
}
*/

  matr operator+(matr &m);  //сложение  матриц
  matr &operator-(const matr &m); // вычитание матриц
  matr &operator-();  //отрицание матрицы
  matr operator*(const matr &m) const;  //перемножение матриц
  matr &operator=(const matr &m);    // перегрузка оператора присваивание
  matr &operator*(double c);   //умножение матрицы на число
  vector& operator*(const vector& vect) const;

};

int matr::countmatr = 0;

//ПЕРЕГРУЗКА ОПЕРАТОРОВ
matr matr::operator+(matr& m) { // сложение двух матриц поэлементно

    cout << "Summarizing matrix #" << number << " with matrix #" << m.number << endl;
    matr tmp(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = b[i][j] + m.b[i][j];
        }
    }
    return tmp;
} //сложение
matr& matr::operator-(const matr& m) { // вычитание двух матриц

    cout << "Subtraction matrix #" << m.number << " from matrix #" << number << endl;
    static matr tmp(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = b[i][j] - m.b[i][j];
        }
    }
    return tmp;
}//вычитание
matr& matr::operator-() { // отрицание всех элементов матрицы

    cout << "Negation matrix #" << number << endl;
    static matr tmp(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = -b[i][j];
        }
    }

    return tmp;
}//отрицание
matr matr::operator*(const matr& m) const { // умножение двух матриц

    cout << "Multiplicating matrix #" << number << " with matrix #" << m.number << endl;
    static matr tmp(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = 0;
            for (int k = 0; k < dim; k++) {
                tmp.b[i][j] += b[i][k] * m.b[k][j];
            }
        }
    }
    return tmp;
}//перемножение матриц
matr& matr::operator=(const matr& m) {  // оператор присваивания для матриц
    cout << "Equating matrix #" << number << " to matrix #" << m.number << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            b[i][j] = m.b[i][j];
        }
    }
    return *this;
}//присваивание
matr& matr::operator*(double c) { // умножение матрицы на число (не friend)
    cout << "Multiplicating matrix #" << number << " with number " << c << endl;
    static matr tmp(dim); // создали новую матрицу с 0, в которую вложим результаты
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            tmp.b[i][j] = b[i][j] * c;
        }
    }

    return tmp;
}//умножение матрицы на число

//ДРУЖЕСТВЕННЫЕ и умножение на вектор...
matr& operator*(double c, matr& m) {  // умножение на число
    cout << "Multiplicating matrix #" << m.number << " with number" << c << endl;
    static matr tmp(m.dim);
    for (int i = 0; i < m.dim; i++) {
        for (int j = 0; j < m.dim; j++) {
            tmp.b[i][j] = c * m.b[i][j];
        }
    }

    return tmp;
} //умножение матрицы на число
vector& matr::operator*(const vector& vect) const{

    cout << "Multiplicating matrix #" << number << " with vector #" << vect.number << endl;

    static vector tmp(dim);

    for (int i = 0; i < dim; i++){
        double n = 0;
        for (int j = 0; j < dim; j++){
            n += vect.v[j] * b[i][j];
        }
        tmp.v[i] = n;
    }

    return tmp;
} //матрица на вектор

//ПЕЧАТЬ МАТРИЦЫ И ВЕКТОРА ОТВЕТОВ
void printSLU(matr& A, vector& B) {
cout << "Coefficients & answers of SLU:" << endl;

    for (int i = 0; i < A.dim; i++) {
        for (int j = 0; j < A.dim; j++) {
            cout << A.b[i][j] << " ";
        }
        cout << "  |  " << B.v[i] << endl;
    }

    cout << endl;
    }

//РЕШЕНИЕ МАТРИЦЫ
void jacobi(matr& A, vector& B){
    const double eps = 0.001;
    vector tmp(A.dim);
    vector X(A.dim);
    double norm; // норма, определяемая как наибольшая разность компонент столбца иксов соседних итераций.
  int c=0;

	do {
        for (int i = 0; i < A.dim; i++) {
            tmp.v[i] = B.v[i];
            for (int g = 0; g < A.dim; g++) {
                if (i != g)
                    tmp.v[i] -= A.b[i][g] * X.v[g];
            }
            tmp.v[i] /= A.b[i][i];
        }
        norm = fabs(X.v[0] - tmp.v[0]);
        for (int h = 0; h < A.dim; h++) {
            if (fabs(X.v[h] - tmp.v[h]) > norm)
                norm = fabs(X.v[h] - tmp.v[h]);
            X.v[h] = tmp.v[h];
        }
    c++;
  } while (norm > eps && c != 10000);
  if (c!=10000){
  cout << "The number of iterations for the Jacobi method: " << c << endl;
   X.print();
  }
  else{
    cout << "Error: Exceeded the number of iterations for the Jacobi method: " << c << endl;
    cout << "Here are the values obtained for this number of iterations: " << c << endl;
    X.print();
  }
}


//ОСНОВНОЙ КОД
int main() {
  /*
 matr matr_1;
  matr_1.print();

  int n = 3;

  double **M = new double *[n];
  for (int i = 0; i < n; i++)
    M[i] = new double[n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << "Введите элемент матрицы М[" << i << "][" << j << "]" << endl;
      cin >> M[i][j];
    }
  }

  matr matr_2(3);
  matr_2.print();

  matr matr_3(3, M);
  matr_3.print();

  matr matr_4(matr_3);
  matr_4.print();

  matr_4.obrDiag(matr_4);
  matr_4.print();

  cout << "\nПРОВЕРКА СЛОЖЕНИЯ ДВУХ МАТРИЦ" << endl;
  (matr_3+matr_3).print();

  cout << "\nПРОВЕРКА ВЫЧИТАНИЯ ДВУХ МАТРИЦ" << endl;
  (matr_3-matr_4).print();

  cout << "\nПРОВЕРКА ОТРИЦАНИЯ МАТРИЦЫ" << endl;
  (-matr_3).print();

  cout << "\nПРОВЕРКА ПЕРЕМНОЖЕНИЯ ДВУХ МАТРИЦ" << endl;
  matr matr_5(3, 123);
  matr_5.print();
  (matr_3*matr_5).print();

  cout << "\nПРОВЕРКА ОПЕРАТОРА ПРИСВАИВАНИЕ" << endl;
  matr matr_6 = matr_5;
  matr_6.print();

  cout << "\nПРОВЕРКА УМНОЖЕНИЯ НА ЧИСЛО" << endl;
  (3*matr_6).print();
  (matr_6*2).print();
*/
int d1 = 3;
   double* arr_d1 = new double[d1];
   for (int i = 0; i < d1; i++) {
       cout << "Enter element #" << i + 1 << " for array number 1: ";
       cin >> arr_d1[i];
   }
  vector res(d1, arr_d1);
  /*cout << "\nПРОВЕРКА УМНОЖЕНИЯ НА ВЕКТОР" << endl;
  (matr_3*res).print();

  matr matr_7(3, 4);
  matr_7.obrDiag(matr_7);
  matr_7.print();
*/
  matr slau(3, 4);
  //(slau.plusDiag(slau)).print();
  printSLU(slau, res);
  jacobi(slau, res);
}



/*
//Ограничение на большое число на диагонали

vect v1(3, 1);
matrix I(3);
I.makeDiag();
matrix m1(3, 1111);
m1.multiDiag();
v1 = m1 * v1;
vect v_ans(3);
printSLU(m1, v1);

*/
//Использование параметра const мне кажется логичным проектным решением, потому что вы хотите гарантировать, что другое значение не будет изменено.
//Ссылка const - это просто ссылка, которая является const . Это не изменяет постоянство фактического объекта, который вы передаете.
//Параметр является const во всей функции, использующей его, он не изменяет свою константу вне его.

//В этом случае вы хотите объявить аргумент const, чтобы ваш оператор присваивания принимал как неконстантные переменные, так и переменные const; последний случай, в частности, включает результат выражений, который является временной переменной const и который вы обычно хотите поддерживать в присваиваниях.