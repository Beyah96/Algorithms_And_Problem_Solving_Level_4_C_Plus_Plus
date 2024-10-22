#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip> 
#include <vector>

using namespace std;

enum enLeapYearStatus { NotLeapYear = 0, LeapYear = 1 };

struct stDetails {
	short NumberOfDays, NumberOfHours;
	int NumberOfMinutes, NumberOfSeconds;
};

short ReadYear(string Message) {
	short Number;
	do {
		cout << Message;
		cin >> Number;
	} while (Number < 0);
	return Number;
}
bool isLeapYear(short Year) {
	return (((Year % 400 == 0) || ((Year % 4 == 0) && (Year % 100 != 0))) ? true : false);
}

stDetails GetYearsDetails(bool YearStatus) {
	stDetails MyYear;
	(YearStatus) ? MyYear.NumberOfDays = 366 : MyYear.NumberOfDays = 365;

	MyYear.NumberOfHours = 24 * MyYear.NumberOfDays;
	MyYear.NumberOfMinutes = 60 * MyYear.NumberOfHours;
	MyYear.NumberOfSeconds = 60 * MyYear.NumberOfMinutes;
	return MyYear;
}

short GetNumberOfDaysPerMonth(short Year, short Month) {
	short MonthsArr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (Month > 12 || Month < 1)
		return 0;
	
	return (Month == 2)?(isLeapYear(Year)? 28 : 29) : MonthsArr[Month - 1];
}



stDetails GetMonthDetails(short NumberOfDaysPerMonth) {
	stDetails MyMonth;
	MyMonth.NumberOfDays = NumberOfDaysPerMonth;
	MyMonth.NumberOfHours = 24 * MyMonth.NumberOfDays;
	MyMonth.NumberOfMinutes = 60 * MyMonth.NumberOfHours;
	MyMonth.NumberOfSeconds = 60 * MyMonth.NumberOfMinutes;
	return MyMonth;
}

void PrintMonthDetails() {
	short Year = ReadYear("Please enter a year to check:");
	short Month = ReadYear("Please enter month number : ");
	short NumberOfDayPerMonth = GetNumberOfDaysPerMonth(isLeapYear(Year), Month);
	stDetails MyMonth = GetMonthDetails(NumberOfDayPerMonth);
	cout << left << setw(18) << "Number of days" << "in [" << Month << "] is " << MyMonth.NumberOfDays << endl;
	cout << left << setw(18) << "Number of hours" << "in [" << Month << "] is " << MyMonth.NumberOfHours << endl;
	cout << left << setw(18) << "Number of minutes" << "in [" << Month << "] is " << MyMonth.NumberOfMinutes << endl;
	cout << left << setw(18) << "Number of seconds" << "in [" << Month << "] is " << MyMonth.NumberOfSeconds << endl;
}


int main() {
	PrintMonthDetails();
	system("pause>0");
	return 0;
}