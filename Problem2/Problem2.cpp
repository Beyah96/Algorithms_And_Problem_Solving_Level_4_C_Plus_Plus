#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
enum enLeapYearStatus { NotLeapYear = 0, LeapYear = 1 };

short ReadYear(string Message) {
	short Number;
	do {
		cout << Message;
		cin >> Number;
	} while (Number < 0);
	return Number;
}
enLeapYearStatus CheckIfLeapYear(short Year) {
	bool isLeap;
	if (Year % 400 == 0)
		isLeap = true;
	else if (Year % 100 == 0)
		isLeap = false;
	else if (Year % 4 == 0)
		isLeap = true;
	else
		isLeap = false;
	return (enLeapYearStatus)isLeap;
}


int main() {
	short Number = ReadYear("Please enter the year: ");
	if (CheckIfLeapYear(Number) == enLeapYearStatus::LeapYear)
		printf("Yes, %d is a leap year", Number);
	else
		printf("No, %d is not a leap year", Number);
	system("pause>0");
	return 0;
}