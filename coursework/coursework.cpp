#include <iostream>
#include <fstream>
#include <Windows.h>
#include "calc.cpp"
#include "calc.h"
#include "calc.h"
using namespace std;

#include <list>
#include <string>

void InputError();


int main()
{
    setlocale(LC_ALL, "ru-RU");

    char ans;
    //пример
    //vector<int> dataSet = { 2, 4, 4, 4, 5, 5, 7, 9 };
    //vector<int> dataSet = { 3, 5, 6, 9, 7, 5, 4, 0, 2 };
    //vector<int> dataSet = { 1, 3, 3, 4, 5, 6, 6, 7, 8, 8 };
    vector<double> dataSet = { 10, 11, 13 };
    vector<double> oldDataSet;
    CCalculator* Calculator = new CCalculator(dataSet);
    //CCalculator* Calculator = new CCalculator();

    ofstream outstream;
    ifstream instream;
    string path = "history.txt";


    do {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 8);
        cout << "Выберите функцию:" << endl;
        cout << "\ta - добавить элемент" << endl;
        cout << "\to - создать новое множество" << endl;
        cout << "\tl - восстановить последнее множество" << endl;
        cout << "\tu - создать случайное новое множество (Равномерное распределение)" << endl;
        cout << "\ty - создать случайное новое множество (Нормальное распределение)" << endl;
        cout << "\tb - удаление последнего элемента" << endl;
        cout << "\ts - вывести все элементы множества на экран" << endl;
        cout << "\tx - вывести все результаты измерений калькулятора на экран" << endl;
        cout << "\te - выход" << endl;
        SetConsoleTextAttribute(hConsole, 15);

        cin >> ans;
        if (cin.fail()) {
            InputError();
            break;
        }

        int n;
        double digit;
        bool flag;
        CCalculator* tempCalculator;

        switch (ans)
        {
        case 'a':
        {
            cout << "Введите количество элементов, сколько нужно добавить в множество:" << endl;
            cin >> n;
            if (cin.fail()) {
                InputError();
                break;
            }
            //Проверка на неотрицательность
            if (n <= 0) {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Недействительное количество элементов." << endl;
                InputError();
                break;
            }
            for (int i = 0;i < n;i++) {
                cout << "Введите число:" << endl;
                cin >> digit;
                if (cin.fail()) {
                    InputError();
                    break;
                }
                Calculator->push(digit);
            }
            break;
        }

        case 'o':
        {
            //записываем в файл предыдущее множество, если оно есть
            if (Calculator->getData().size() > 0) {
                outstream.open(path, ios::binary); //открыть новый пустой файл для двоичной записи
                if (!outstream.is_open()) {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Ошибка открытия файла..." << endl;
                }
                else {
                    //запись всех элементов в файл
                    outstream.write(reinterpret_cast<const char*>(Calculator->getData().data()), 
                        Calculator->getData().size() * sizeof(double));
                }
                outstream.close();
            }

            flag = true;
            CCalculator* tempCalculator = new CCalculator();
            cout << "Введите количество элементов, сколько нужно добавить в множество:" << endl;
            cin >> n;
            if (cin.fail()) {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Новое множество не создано из-за ошибки!" << endl;
                InputError();
                flag = false;
                break;
            }
            //Проверка на неотрицательность
            if (n <= 0) {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Недействительное количество элементов." << endl;
                InputError();
                break;
            }
            for (int i = 0;i < n;i++) {
                cout << "Введите число:" << endl;
                cin >> digit;
                if (cin.fail()) {
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << "Новое множество не создано из-за ошибки!" << endl;
                    InputError();
                    flag = false;
                    break;
                }
                tempCalculator->push(digit);
            }
            if (flag) {
                Calculator = tempCalculator;                
            }
            break;
        }

        case 'u':
        {
            //записываем в файл предыдущее множество, если оно есть
            if (Calculator->getData().size() > 0) {
                outstream.open(path, ios::binary); //открыть новый пустой файл для двоичной записи
                if (!outstream.is_open()) {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Ошибка открытия файла..." << endl;
                }
                else {
                    //запись всех элементов в файл
                    outstream.write(reinterpret_cast<const char*>(Calculator->getData().data()),
                        Calculator->getData().size() * sizeof(double));
                }
                outstream.close();
            }


            bool flag = true;
            CCalculator* tempCalculator = new CCalculator();
            //переменная для генерации случайного числа
            CRandomCalculator* randNum = new CRandomCalculator();

            cout << "Введите количество элементов, сколько нужно добавить в множество:" << endl;
            cin >> n;
            if (cin.fail()) {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Новое множество не создано из-за ошибки!" << endl;
                InputError();
                flag = false;
                break;
            }
            //Проверка на неотрицательность
            if (n <= 0) {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Недействительное количество элементов." << endl;
                InputError();
                break;
            }            

            cout << "Укажите предпочитаемый формат данных: " << endl;
            cout << "   1 - int " << endl;
            cout << "   2 - double " << endl;
            int tempAns;
            cin >> tempAns;
            if (cin.fail()) {
                SetConsoleTextAttribute(hConsole, 6);
                //cout << "Неверный ввод. Множество не создано." << endl;
                InputError();
                flag = false;
                break;
            }

            if (tempAns == 1) {
                for (int i = 0;i < n;i++) {
                    tempCalculator->push(randNum->getRandomNumberFlatINT(-1000, 1000));
                }
                if (flag) {
                    Calculator = tempCalculator;
                }
            }
            else if (tempAns == 2) {
                for (int i = 0;i < n;i++) {
                    tempCalculator->push(randNum->getRandomNumberFlatDOUBLE(-1000, 1000));
                }
                if (flag) {
                    Calculator = tempCalculator;
                }
            }
            else {
                SetConsoleTextAttribute(hConsole, 6);
                //cout << "Неверный ввод. Множество не создано." << endl;
                InputError();
            }            
            break;
        }

        case 'y':
        {
            //записываем в файл предыдущее множество, если оно есть
            if (Calculator->getData().size() > 0) {
                outstream.open(path, ios::binary); //открыть новый пустой файл для двоичной записи
                if (!outstream.is_open()) {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "Ошибка открытия файла..." << endl;
                }
                else {
                    //запись всех элементов в файл
                    outstream.write(reinterpret_cast<const char*>(Calculator->getData().data()),
                        Calculator->getData().size() * sizeof(double));
                }
                outstream.close();
            }


            bool flag = true;
            CCalculator* tempCalculator = new CCalculator();
            //переменная для генерации случайного числа
            CRandomCalculator* randNum = new CRandomCalculator();

            cout << "Введите количество элементов, сколько нужно добавить в множество:" << endl;
            cin >> n;
            if (cin.fail()) {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Новое множество не создано из-за ошибки!" << endl;
                InputError();
                flag = false;
                break;
            }
            //Проверка на неотрицательность
            if (n <= 0) {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Недействительное количество элементов." << endl;
                InputError();
                break;
            }
            for (int i = 0;i < n;i++) {
                tempCalculator->push(randNum->getRandomNumberGauss(-1000, 1000));
            }
            if (flag) {
                Calculator = tempCalculator;
            }
            break;
        }

        case 'b':
        {
            Calculator->pop();
            break;
        }

        case 'x':
            if (!Calculator->isEmpty()) {
                bool quantileFlag = true;
                double quantileVal;

                //доп переменные разных классов
                const vector<double>& data = Calculator->getData();
                CModeCalculator* modeVal = new CModeCalculator(data);
                CMedianCalculator* medianVal = new CMedianCalculator(data);
                CMeanAlgCalculator* meanAlgVal = new CMeanAlgCalculator(data);
                CMeanGeomCalculator* meanGeomVal = new CMeanGeomCalculator(data);
                CDeviationCalculator* SKval = new CDeviationCalculator(data);
                CRandomCalculator* randVal = new CRandomCalculator(data);

                cout << "Множество X: "; Calculator->display(); cout << endl;
                cout << "Минимум: " << Calculator->minimum() << endl;
                cout << "Максимум: " << Calculator->maximum() << endl;
                cout << "Сумма: " << Calculator->sum() << endl;
                cout << "Отсортированное множество: "; Calculator->sortPrint();
                /*Мода*/modeVal->calculate();
                cout << "Медиана: "; medianVal->calculate(); cout << endl;
                cout << "Среднее арифметическое значение: "; meanAlgVal->calculate();
                cout << "Среднее геометрическое значение: "; meanGeomVal->calculate();
                cout << "Среднеквадратическое отклонение: " << SKval->standartDeviation() << endl;
                cout << "Дисперсия: " << SKval->dispersion() << endl;
                cout << "Квартили: " << endl;

                if (data.size() < 2) {
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << "   Введите минимум 2 числа в множестве." << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else {
                    cout << "   Q1: " << Calculator->Q1() << endl;
                    cout << "   Q2: "; medianVal->calculate(); cout << endl;
                    cout << "   Q3: " << Calculator->Q3() << endl;
                }
                cout << "Коэффициент ассиметрии: " << randVal->skewness() << endl;
                cout << "Коэффициент эксцесса: " << randVal->kurtosis() << endl;

                cout << "Тест на нормальность: ";
                if (randVal->shapiroTest()) {
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << "   Данные подчиняются нормальному распределению." << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else {
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << "   Данные не подчиняются нормальному распределению." << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                }
            }
            else {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Сначала создайте множество." << endl;
            }
            break;

        case 's':
            if (!Calculator->isEmpty()) {
                cout << "Ваше текущее множество: ";
                Calculator->display();
            }
            else {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "Сначала создайте множество." << endl;
            }
            break;

        case 'l':
        {
            //записываем в переменную предыдущее множество, если оно есть
            if (Calculator->getData().size() > 0) {
                oldDataSet.clear();
                for (double n : Calculator->getData()) {
                    oldDataSet.push_back(n);
                }                
            }
            //открываем файл для записи в двоичном коде
            instream.open(path, ios::binary);
            bool flag = true;
            vector<double> tempDataSet;

            //проверка на существование такого файла
            if (!instream.is_open()) {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "Ошибка открытия файла... (Такой файл не существует)" << endl;
            }
            else {
                //проверка на пустоту файла
                if (instream.peek() == ifstream::traits_type::eof()) {
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << "Файл пуст, чтение завершено." << endl;
                }
                else {
                    //дополнительная переменная для записи результата при вызове функции instream.read
                    double num;
                    //instream.read которая вызывается в while  
                    while (instream.read(reinterpret_cast<char*>(&num), sizeof(double))) {
                        tempDataSet.push_back(num);
                    }
                    //перезапись старого множества из файла
                    Calculator = new CCalculator(tempDataSet);
                    cout << "Ваше новое множежство: ";
                    Calculator->display();
                    instream.close();
                    SetConsoleTextAttribute(hConsole, 15);


                    //перезапись старого множества в файл
                    outstream.open(path, ios::binary);
                    if (!outstream.is_open()) {
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "Ошибка открытия файла..." << endl;
                    }
                    else {
                        //запись всех элементов старого множества в файл
                        outstream.write(reinterpret_cast<const char*>(oldDataSet.data()),
                            oldDataSet.size() * sizeof(double));
                    }
                    outstream.close();
                }
            }
            break;
        }

        case 'e':
            cout << "Завершение работы..." << endl;
            return 0;

        default:
            InputError();
            break;
        }



    } while (true);


}

void InputError() {
    cin.clear();
    //cin.ignore();
    cin.ignore(100, '\n');

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "Неверный ввод\n" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}