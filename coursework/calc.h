
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <random>
#include <cmath>
using namespace std;

//БАЗОВЫЙ КЛАСС
class CStaticMath {
public:
	virtual void calculate() const = 0;
};
//ПОТОМКИ
//Промежуточный + Стандартные простые функции
class CCalculator : public CStaticMath {
private:
	vector<double> arr;
public:
	CCalculator();
	CCalculator(const vector<double>& data) : arr(data) {}
	const vector<double>& getData() const { return arr; }

	void push(double x);
	void push(double x);
	void push(double x);
	void push(double x);
	void pop();
	void display();
	bool isEmpty();

	double minimum();
	double maximum();
	double sum();
	void sortPrint(); //вывод отсортированного массива

	//Квантили
	double Q1();
	double Q3();

	//Реализация виртуальной функции
	void calculate() const override;
};
//Мода
class CModeCalculator : public CCalculator {
public:
	CModeCalculator(const vector<double>& data) : CCalculator(data) {}
	CModeCalculator() {};
		
	void calculate() const override;
};
//Медиана
class CMedianCalculator : public CCalculator {
public:
	CMedianCalculator(const vector<double>& data) : CCalculator(data) {}
	CMedianCalculator() {};

	double getMedian() const;
	void calculate() const override;
};
//Среднее арифметическое
class CMeanAlgCalculator : public CCalculator {
public:
	CMeanAlgCalculator(const vector<double>& data) : CCalculator(data) {}
	CMeanAlgCalculator() {};

	double getMeanAlg() const;
	void calculate() const override;
};
//Среднее геометрическое
class CMeanGeomCalculator : public CCalculator {
public:
	CMeanGeomCalculator(const vector<double>& data) : CCalculator(data) {}
	CMeanGeomCalculator() {};

	double getMeanGeom() const;
	void calculate() const;
};
//Стандартное отклонение + дисперсия
class CDeviationCalculator : public CMeanAlgCalculator {
public:
	CDeviationCalculator(const vector<double>& data) : CMeanAlgCalculator(data) {}
	CDeviationCalculator() {};

	double standartDeviation();
	double dispersion();
};
//Реализация генерации рандомных чисел и проверки этой выборки
class CRandomCalculator : public CDeviationCalculator {
public:
	CRandomCalculator(const vector<double>& data) : CDeviationCalculator(data) {}
	CRandomCalculator();

	template <typename T>
	T getRandomNumberFlatINT(T mn, T mx);
	double getRandomNumberFlatDOUBLE(double mn, double mx);
	double getRandomNumberGauss(double mn, double mx);

	double skewness();  //вычисление коэффициента асимметрии
	double kurtosis();  //вычисление коэффициента эксцесса

	bool shapiroTest();	
};
