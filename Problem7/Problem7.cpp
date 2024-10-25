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

string GetDayName(short DayIndex) {
	string Days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thurday", "Friday", "Saturday" };
	return Days[DayIndex];
}

short GetDayOrder(short Day, short Month, short Year) {
	short a = (14 - Month) / 12;
	short y = Year - a;
	short m = Month + 12 * a - 2;
	return (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
}

void PrintNameOfDay() {
	short Day = ReadNumber("Please enter the day : ");
	short Month = ReadNumber("Please enter the month : ");
	short Year = ReadNumber("Please enter the year : ");
	cout << endl;
	short DayOrder = GetDayOrder(Day, Month, Year);
	string DayName = GetDayName(DayOrder);
	printf("Date      : %d / %d / %d\n", Day, Month, Year);
	cout << "Day Order : " << DayOrder << endl;
	cout << "Day Name  : " << DayName;
}

int main() {
	PrintNameOfDay();
	system("pause>0");
	return 0;
}