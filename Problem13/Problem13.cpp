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

short CountDaysFromFirstJanuary(sDay Date) {

	short NumberOfDaysFromFirstJanuary = 0;
	for (int Month = 1; Month < Date.Month; Month++)
		NumberOfDaysFromFirstJanuary += GetNumberOfDaysPerMonth(Month, Date.Year);
	return NumberOfDaysFromFirstJanuary + Date.Day;
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

short GetNumberOfDaysPerYear(short Year) {
	return (isLeapYear(Year)) ? 366 : 365;
}
sDay GetDate(sDay NewDate, short NewDays) {
	short NumberOfDaysPerYear;
	short DayOrderInYear = CountDaysFromFirstJanuary(NewDate);
	short RemainingDays = NewDays + DayOrderInYear;
	short NumberOfDaysPerMonth;
	NewDate.Month = 1;
	while (true) {
		NumberOfDaysPerYear = GetNumberOfDaysPerYear(NewDate.Year);
		if (NumberOfDaysPerYear < RemainingDays) {
			NewDate.Year++;
			RemainingDays -= NumberOfDaysPerYear;
		}
		else {
			NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(NewDate.Month, NewDate.Year);
			if (NumberOfDaysPerMonth < RemainingDays) {
				NewDate.Month++;
				RemainingDays -= NumberOfDaysPerMonth;
			}
			else {
				NewDate.Day = RemainingDays;
				break;
			}
		}
	}
	return NewDate;
}

void AddDays(sDay Date, short NewDays) {
	sDay stSearchedDate = GetDate(Date, NewDays);
	printf("Date for [%d] is :  %d/%d/%d", NewDays, stSearchedDate.Day, stSearchedDate.Month, stSearchedDate.Year);
}

short ReadDay() {
	short Day = ReadNumber("Please enter the day : ");
	return Day;
}


short ReadMonth() {
	short Month = ReadNumber("Please enter the Month: ");
	return Month;
}


short ReadYear() {
	short Year = ReadNumber("Please enter a yera : ");
	return Year;
}



sDay ReadFullDate() {
	sDay NewDate;
	NewDate.Day = ReadDay();
	NewDate.Month = ReadMonth();
	NewDate.Year = ReadYear();
	return NewDate;
}

bool isDateOneBeforeDateTwo(sDay DateOne, sDay DateTwo) {
	return (DateOne.Year > DateTwo.Year) ? true : (DateOne.Year < DateTwo.Year) ? false : (DateOne.Month > DateTwo.Month) ? true : (DateOne.Month < DateTwo.Month) ?  false : (DateOne.Day > DateTwo.Day);
}

int main() {
	sDay DateOne = ReadFullDate();
	sDay DateTwo = ReadFullDate();
	(isDateOneBeforeDateTwo(DateOne, DateTwo) ? (cout << "Date1 is grater than Date2.") : cout << "Date2 is grater than Date1.");
	return 0;
}