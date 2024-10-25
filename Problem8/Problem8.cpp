#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip> 
#include <vector>

using namespace std;

short ReadNumber(string Message) {
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

short GetNumberOfDaysPerMonth(short Year, short Month) {
	short MonthsArr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (Month > 12 || Month < 1)
		return 0;

	return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : MonthsArr[Month - 1];
}

string GetDayName(short DayIndex) {
	string Days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thurday", "Friday", "Saturday" };
	return Days[DayIndex];
}

string GetMonthName(short MonthIndex) {
	string Months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	return Months[MonthIndex-1];
}

short GetDayOrder(short Day, short Month, short Year) {
	short a = (14 - Month) / 12;
	short y = Year - a;
	short m = Month + 12 * a - 2;
	return (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
}

void PrintMonthCalenderHeader(short MonthIndex) {
	cout << "--------------------------------- "<< left << setw(10) << GetMonthName(MonthIndex) <<"-------------------------------" << endl;
	cout << left << setw(11) << "Sunday" << left << setw(11) << "Monday" << left << setw(11) << "Tuesday" << left << setw(11) << "Wednesday" << left << setw(11) << "Thurday" << left << setw(11) << "Friday" << left << setw(11) << "Saturday" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
}

void GetMonthCalenderContent(short NumberOfDaysPerMonth, short DayOrder, string arrDays[35]) {
	for (int i = 0; i < 35; i++) arrDays[i] = " ";
	while (NumberOfDaysPerMonth != 0) {
		arrDays[DayOrder + NumberOfDaysPerMonth] = to_string(NumberOfDaysPerMonth);
		NumberOfDaysPerMonth--;
	}
}

void PrintMonthCalenderContent(short NumberOfDaysPerMonth, short DayOrder) {
	string arrDays[35];
	GetMonthCalenderContent(NumberOfDaysPerMonth, DayOrder, arrDays);
	short Counter = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++)
			cout << left << setw(11) << arrDays[++Counter];
		cout << endl;
	}
}

void PrintMonthCalender() {

	short Day = 1;
	short Month = ReadNumber("Please enter the month : ");
	short Year = ReadNumber("Please enter the year : ");
	cout << endl;
	short DayOrder = GetDayOrder(Day, Month, Year);
	cout << "Day order : " << DayOrder << endl;
	short NmuberOfDaysPerMonth = GetNumberOfDaysPerMonth(Year, Month);
	PrintMonthCalenderHeader(Month);
	PrintMonthCalenderContent(NmuberOfDaysPerMonth, DayOrder);
}


int main() {
	PrintMonthCalender();
	system("pause>0");
	return 0;
}