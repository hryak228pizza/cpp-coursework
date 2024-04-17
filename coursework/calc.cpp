#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <random>
#include <math.h>
#include "calc.h"
using namespace std;

//БАЗОВЫЙ КЛАСС


//ПОТОМКИ
CCalculator::CCalculator() {};
void CCalculator::calculate() const {};
void CCalculator::push(double x) {
	arr.push_back(x);
}
void CCalculator::pop() {
	if (!arr.empty()) {
		arr.pop_back();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << "Последний элемент удален." << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Ваше текущее множество: "; display();
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "Множество пустое" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
}
void CCalculator::display() {
	//Проверка на пустое множество
	if (arr.size() == 0) cout << "{ }" << endl;
	else {
		cout << "{";
		for (int i = 0;i < arr.size() - 1;i++) {
			cout << arr[i] << ", ";
		}
		cout << arr[arr.size() - 1] << "}" << endl;
	}	
}
bool CCalculator::isEmpty() {
	return arr.empty();
}
bool CCalculator::isEmpty() {
	return arr.empty();
}
bool CCalculator::isEmpty() {
	return arr.empty();
}
double CCalculator::minimum() {
	const vector<double>& arr = getData();
	double minVal = arr[0];
	for (const double& elem : arr) {
		if (elem < minVal) {
			minVal = elem;
		}
	}
	return minVal;
}
double CCalculator::maximum() {
	const vector<double>& arr = getData();
	double maxVal = arr[0];
	for (const double& elem : arr) {
		if (elem > maxVal) {
			maxVal = elem;
		}
	}
	return maxVal;
}
double CCalculator::sum() {
	const vector<double>& arr = getData();
	double sm = 0;
	for (double num : arr) sm += num;
	return sm;
}
void CCalculator::sortPrint() {
	const vector<double>& arr = getData();
	//Копия массива, который будет отсортирован
	vector<double> sortedNums = arr;
	//Сортировка
	sort(sortedNums.begin(), sortedNums.end());

	cout << "{";
	for (int i = 0;i < sortedNums.size() - 1;i++) {
		cout << sortedNums[i] << ", ";
	}
	cout << sortedNums[sortedNums.size() - 1] << "}" << endl;
}
double CCalculator::Q1() {
	const vector<double>& arr = getData();
	//Копия массива, который будет отсортирован
	vector<double> sortedNums = arr;
	//Сортировка
	sort(sortedNums.begin(), sortedNums.end());

	vector<double> tempArr;
	int size = sortedNums.size();

	//Отсечение первой половины множества до второго квантиля (не включая его)
	for (int i = 0; i < size / 2; i++)
		tempArr.push_back(sortedNums[i]);
	
	//Расчет середины первой половины массива
	size = tempArr.size();
	if (size % 2 == 0) return ((tempArr[size / 2 - 1] + tempArr[size / 2]) / 2.0);
	else return tempArr[size / 2];
}
double CCalculator::Q3() {
	const vector<double>& arr = getData();
	//Копия массива, который будет отсортирован
	vector<double> sortedNums = arr;
	//Сортировка
	sort(sortedNums.begin(), sortedNums.end());

	vector<double> tempArr;
	int size = sortedNums.size();

	//Отсечение второй половины множества после второго квантиля (не включая его)
	if (size % 2 == 0) {
		for (int i = size / 2; i < size; i++)
			tempArr.push_back(sortedNums[i]);
	}
	else {
		for (int i = size / 2 + 1; i < size; i++)
			tempArr.push_back(sortedNums[i]);
	}	

	//Расчет середины второй половины массива
	size = tempArr.size();
	if (size % 2 == 0) return ((tempArr[size / 2 - 1] + tempArr[size / 2]) / 2.0);
	else return tempArr[size / 2];
}


void CModeCalculator::calculate() const {
	const vector<double>& arr = CCalculator::getData();
	//Список мод множества
	vector<double> modeVec;
	//Словарь частотного распределения
	map<double, int> frequencyMap;
	int maxFrequency = 0;

	//Подсчет частоты каждого элемента в множестве
	for (double num : arr) frequencyMap[num]++;

	//Нахождение максимальной частоты
	for (const auto& entry : frequencyMap) {
		int frequency = entry.second;
		if (frequency > maxFrequency) {
			maxFrequency = frequency;
		}
	}

	//Добавление всех элементов с максимальной частотой в результирующий вектор
	for (const auto& entry : frequencyMap) {
		double num = entry.first;
		int frequency = entry.second;
		if (frequency == maxFrequency) {
			modeVec.push_back(num);
		}
	}

	if (modeVec.size() == 1) cout << "Мода: " << modeVec[0] << endl;
	else if (modeVec.empty()) cout << "Моды в данном множестве не существует." << endl;
	else {
		cout << "Моды множества: ";
		for (double mode : modeVec) {
			cout << mode << " ";
		}
		cout << endl;
	}
}

double CMedianCalculator::getMedian() const {
	const vector<double>& arr = CCalculator::getData();
	//Копия массива, который будет отсортирован
	vector<double> sortedNums = arr;
	//Сортировка
	sort(sortedNums.begin(), sortedNums.end());

	//Расчет середины массива
	int size = sortedNums.size();
	if (size % 2 == 0) return ((sortedNums[size / 2 - 1] + sortedNums[size / 2]) / 2.0);
	else return sortedNums[size / 2];
}
void CMedianCalculator::calculate() const {
	double median = getMedian();
	cout << median;
}

double CMeanAlgCalculator::getMeanAlg() const {
	const vector<double>& arr = CCalculator::getData();
	double meanValue = 0;
	for (int i = 0;i < arr.size();i++) {
		meanValue += arr[i];
	}
	return meanValue / arr.size();
};
void CMeanAlgCalculator::calculate() const {
	cout << getMeanAlg() << endl;
};

double CMeanGeomCalculator::getMeanGeom() const {
	const vector<double>& arr = CCalculator::getData();
	double meanValue = 1;
	for (int i = 0;i < arr.size();i++) {
		meanValue *= arr[i];
	}
	return pow(meanValue, 1.0 / arr.size());
};
void CMeanGeomCalculator::calculate() const {
	cout << getMeanGeom() << endl;
};

double CDeviationCalculator::standartDeviation() {
	const vector<double>& arr = getData();
	double deviationValue = 0;
	double meanAlgValue = getMeanAlg();

	//Сумма квадратов отклонения от среднего для каждого элемента
	for (int i = 0;i < arr.size();i++) {
		deviationValue += pow((arr[i] - meanAlgValue), 2);
	}
	return pow(deviationValue / (arr.size() - 1), 0.5);
}
double CDeviationCalculator::dispersion() {
	return pow(standartDeviation(), 2);
}

template <typename T>
T CRandomCalculator::getRandomNumberFlatINT(T mn, T mx)
{
	//Генерация случайного числа
	static mt19937 generator(random_device{}());
	uniform_real_distribution<T> distribution(mn, mx);

	return distribution(generator);

}
double CRandomCalculator::getRandomNumberFlatDOUBLE(double mn, double mx)
{
	//Генерация случайного числа
	static mt19937 generator(random_device{}());
	uniform_real_distribution<double> distribution(mn, mx);

	return distribution(generator);

}
double CRandomCalculator::getRandomNumberGauss(double mn, double mx)
{
	//Стандартные значения среднего арифметического и стандартного отклонения
	//	для наиболее нормального распределения
	double mean = 0.0;
	double stDev = 1.0;

	static mt19937 generator(random_device{}());
	normal_distribution<double> distribution(mean, stDev);

	return distribution(generator);
}
bool CRandomCalculator::shapiroTest()
{
	const vector<double>& arr = CCalculator::getData();
	int n = static_cast<int>(arr.size());

	//Сортировка множества
	vector<double> sortedData = arr;
	sort(sortedData.begin(), sortedData.end());

	double mean = 0.0;
	double stDev = 1.0;
	double sumW = 0.0;

	for (int i = 0; i < n; ++i) {
		double diff = sortedData[i] - (i + 1.0) / n; //разница между каждым отсортированным значением
													// и ожидаемым значением для нормального распределения.
		sumW += diff * diff;	//суммирование квадратов разниц					
	}

	double W = 1.0 - sumW / (n * n); //вычисление статистики W
	double alpha = 0.05;  //уровень значимости (обычно 0.05)

	cout << W << endl;
	return W > alpha;
}
double CRandomCalculator::skewness() {
	const vector<double>& arr = CCalculator::getData();

	double mean = getMeanAlg();
	double stDev = standartDeviation();

	double sum = 0;
	for (double x : arr) {
		sum += pow((x - mean) / stDev, 3);
	}
	return sum / arr.size();
}
double CRandomCalculator::kurtosis() {
	const vector<double>& arr = CCalculator::getData();

	double mean = getMeanAlg();
	double stDev = standartDeviation();

	double sum = 0;
	for (double x : arr) {
		sum += pow((x - mean) / stDev, 4);
	}
	return sum / arr.size() - 3;
}
CRandomCalculator::CRandomCalculator() {};
