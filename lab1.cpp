#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

class CustomException : public exception {
private:
	string errorMessage;
	double errorValue;
	int errorCode;
public:
	CustomException(const string& message, double value, int code)
		:errorMessage(message), errorValue(value), errorCode(code) {}

	const char* what() const noexcept override {
		return errorMessage.c_str();
	}

	double getErrorValue() const {
		return errorValue;
	}

	int getErrorCode() const {
		return errorCode;
	}
};

double calculateZ1(double& m) {
	if (m == 0) throw CustomException("Деление на 0 Z1", m, 1);

	double lol1 = (m + 2) / sqrt(2 * m);
	double lol2 = 2 / (m - sqrt(2 * m));
	double lol3 = m / (sqrt(2 * m) + 2);
	double lol4 = (sqrt(m) - sqrt(2)) / (m + 2);

	double z1 = (lol1 + lol2 - lol3) * lol4;

	if (isnan(z1)) {
		throw CustomException("NaN Z1", z1, 3);
	}

	return z1;
}

double calculateZ2(double& m) {
	double z2 = 1 / (sqrt(m) + sqrt(2));

	if (isnan(z2)) {
		throw CustomException("NaN Z2", z2, 3);
	}
	return z2;
}

int main() {
	setlocale(LC_ALL, "Russian");
	double m;

	cout << "Введите значение m: ";
	cin >> m;

	try {
		double z1 = calculateZ1(m);
		double z2 = calculateZ2(m);

		cout << "Z1 = " << z1 << endl;
		cout << "Z2 = " << z2 << endl;

		if (z1 == z2) {
			cout << "Значения Z1 и Z2 равны." << endl;
		}
		else {
			cout << "Значения Z1 и Z2 различаются." << endl;
		}
	}
	catch (const CustomException& ex) {
		cerr << "Произошла ошибка: " << ex.what() << endl;
		cerr << "Значение, вызвавшее ошибку: " << ex.getErrorValue() << endl;
		cerr << "Код ошибки: " << ex.getErrorCode() << endl;
	}

	return 0;
}
