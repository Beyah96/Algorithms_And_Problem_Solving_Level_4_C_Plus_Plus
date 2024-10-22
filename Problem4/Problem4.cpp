#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip> 

using namespace std;
enum enLeapYearStatus { NotLeapYear = 0, LeapYear = 1 };

struct stYearsDetails {
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
enLeapYearStatus CheckIfLeapYear(short Year) {
	bool isLeap = false;
	if ((Year % 400 == 0) || ((Year % 4 == 0) && (Year % 100 != 0)))
		isLeap = true;
	return (enLeapYearStatus)isLeap;
}

stYearsDetails GetYearsDetails(enLeapYearStatus YearStatus) {
	stYearsDetails MyYear;
	(YearStatus == enLeapYearStatus::LeapYear) ? MyYear.NumberOfDays = 366 : MyYear.NumberOfDays = 365;

	MyYear.NumberOfHours = 24 * MyYear.NumberOfDays;
	MyYear.NumberOfMinutes = 60 * MyYear.NumberOfHours; 
	MyYear.NumberOfSeconds = 60 * MyYear.NumberOfMinutes;
	return MyYear;
}

void PrintYearsDetails() {
	short Year = ReadYear("Please enter a year to check:");
	stYearsDetails MyYear = GetYearsDetails(CheckIfLeapYear(Year));

	cout << left << setw(18) << "Number of days" <<   "in [" << Year << "] is " << MyYear.NumberOfDays << endl;
	cout << left << setw(18) << "Number of hours" <<   "in [" << Year << "] is " <<MyYear.NumberOfHours << endl;
	cout << left << setw(18) << "Number of minutes" << "in [" << Year << "] is " << MyYear.NumberOfMinutes << endl;
	cout << left << setw(18) << "Number of seconds" << "in [" << Year << "] is " << MyYear.NumberOfSeconds << endl;
}


int main() {
	PrintYearsDetails();
	system("pause>0");
	return 0;
}