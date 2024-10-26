#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip>

using namespace std;
struct sDay {
	short Day, Month, Year;
};
short ReadNumber(string Message) {
	short Number;
	do {
		cout << Message;
		cin >> Number;
	} while (Number < 0);
	return Number;
}

bool isLeapYear(short Year) {
	return (((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0));
}

short GetNumberOfDaysPerMonth(short Month, short Year) {
	short MonthsArray[12] = { 31, 28, 31, 30, 31, 30, 31, 31 ,30, 31, 30, 31 };
	if (Month > 12 || Month < 1)
		return 0;
	return (Month == 2) ? ((isLeapYear(Year)) ? 29 : 28) : MonthsArray[Month - 1];
}

string GetDayName(short DayIndex) {
	string Days[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	return Days[DayIndex];
}

string GetMonthName(short MonthIndex) {
	string Months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return Months[MonthIndex - 1];
}

short GetDayOrder(short Day, short Month, short Year) {
	short a = (14 - Month) / 12;
	short y = Year - a;
	short m = Month + 12 * a - 2;
	return (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
}

void PrintMonthCalenderHeader(short MonthIndex) {
	cout << endl << endl;
	cout << "--------------------------------- " << left << setw(10) << GetMonthName(MonthIndex) << "-------------------------------" << endl;
	cout << left << setw(11) << "Sunday" << left << setw(11) << "Monday" << left << setw(11) << "Tuesday" << left << setw(11) << "Wednesday" << left << setw(11) << "Thursday" << left << setw(11) << "Friday" << left << setw(11) << "Saturday" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
}

void PrintMonthCalenderContent(short NumberOfDaysPerMonth, short DayOrder) {
	for (short i = 0; i < DayOrder + NumberOfDaysPerMonth; i++) {
		if (i % 7 == 0) cout << endl;
		(i < DayOrder) ? (cout << left << setw(11) << "") : (cout << left << setw(11) << i - DayOrder + 1);
	}
}

void PrintMonthCalender(short Month, short Year) {
	short DayOrder = GetDayOrder(1, Month, Year);
	short NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(Month, Year);
	PrintMonthCalenderHeader(Month);
	PrintMonthCalenderContent(NumberOfDaysPerMonth, DayOrder);
}

short CountDaysFromFirstJanuary(short CurrentDay, short CurrentMonth, short Year) {

	short NumberOfDaysFromFirstJanuary = 0;
	for (int Month = 1; Month < CurrentMonth; Month++)
		NumberOfDaysFromFirstJanuary += GetNumberOfDaysPerMonth(Month, Year);
	return NumberOfDaysFromFirstJanuary + CurrentDay;
}


void PrintYearCalender(short Year) {
	for (short Month = 1; Month <= 12; Month++)
		PrintMonthCalender(Month, Year);
}

sDay FindDate(short DayOrderInYear, short Year) {
	sDay stSearchedDate;
	short RemainingDays = DayOrderInYear;
	short NumberOfDays;
	short Month = 1;
	while (true) {
		NumberOfDays = GetNumberOfDaysPerMonth(Month, Year);
		if (NumberOfDays < RemainingDays) {
			Month++;
			RemainingDays -= NumberOfDays;
		}
		else {
			stSearchedDate.Month = Month;
			stSearchedDate.Year = Year;
			stSearchedDate.Day = RemainingDays;
			break;
		}
	}
	return stSearchedDate;
}

void ConvertBackDate(short Year, short DayOrerInYear) {
	sDay stSearchedDate = FindDate(DayOrerInYear, Year);
	printf("Date for [%d] is :  %d/%d/%d", DayOrerInYear, stSearchedDate.Day, stSearchedDate.Month, Year);
}

int main() {
	short Day = ReadNumber("Please enter the day : ");
	short Month = ReadNumber("Please enter the month : ");
	short Year = ReadNumber("Please enter a yera : ");

	short DayOrderInYear = CountDaysFromFirstJanuary(Day, Month, Year);

	cout << "Number of days from the begining of the year is : " << DayOrderInYear << endl;
	ConvertBackDate(Year, DayOrderInYear);
	return 0;
}