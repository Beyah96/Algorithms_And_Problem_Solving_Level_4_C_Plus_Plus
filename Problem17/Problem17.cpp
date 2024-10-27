#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <vector>

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

short GetNumberOfDaysPerMonth(sDay Date) {
	short MonthsArray[12] = { 31, 28, 31, 30, 31, 30, 31, 31 ,30, 31, 30, 31 };
	if (Date.Month > 12 || Date.Month < 1)
		return 0;
	return (Date.Month == 2) ? ((isLeapYear(Date.Year)) ? 29 : 28) : MonthsArray[Date.Month - 1];
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

void PrintMonthCalender(sDay Date) {
	short DayOrder = GetDayOrder(1, Date.Month, Date.Year);
	short NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(Date);
	PrintMonthCalenderHeader(Date.Month);
	PrintMonthCalenderContent(NumberOfDaysPerMonth, DayOrder);
}
// TODo : I have to fixe the problem in the function bellow, if i pour Month <= in the for loop it makes mistakes and the same if i don't put it
short CountDaysFromFirstJanuary(sDay Date) {

	short NumberOfDaysFromFirstJanuary = 0;
	for (int Month = 1; Month < Date.Month; Month++) {
		Date.Month = Month;
		NumberOfDaysFromFirstJanuary += GetNumberOfDaysPerMonth(Date);
	}
	return NumberOfDaysFromFirstJanuary + Date.Day;
}


void PrintYearCalender(sDay Date) {
	for (short Month = 1; Month <= 12; Month++) {
		Date.Month = Month;
		PrintMonthCalender(Date);
	}
}

sDay FindDate(short DayOrderInYear, sDay Date) {
	sDay stSearchedDate;
	short RemainingDays = DayOrderInYear;
	short NumberOfDays;
	short Month = 1;
	while (true) {
		NumberOfDays = GetNumberOfDaysPerMonth(Date);
		if (NumberOfDays < RemainingDays) {
			Month++;
			RemainingDays -= NumberOfDays;
		}
		else {
			stSearchedDate.Month = Month;
			stSearchedDate.Year = Date.Year;
			stSearchedDate.Day = RemainingDays;
			break;
		}
	}
	return stSearchedDate;
}

void ConvertBackDate(sDay Date, short DayOrerInYear) {
	sDay stSearchedDate = FindDate(DayOrerInYear, Date);
	printf("Date for [%d] is :  %d/%d/%d", DayOrerInYear, stSearchedDate.Day, stSearchedDate.Month, Date.Year);
}

short GetNumberOfDaysPerYear(sDay Date) {
	return (isLeapYear(Date.Year)) ? 366 : 365;
}
sDay GetDate(sDay NewDate, short NewDays) {
	short NumberOfDaysPerYear;
	short DayOrderInYear = CountDaysFromFirstJanuary(NewDate);
	short RemainingDays = NewDays + DayOrderInYear;
	short NumberOfDaysPerMonth;
	NewDate.Month = 1;
	while (true) {
		NumberOfDaysPerYear = GetNumberOfDaysPerYear(NewDate);
		if (NumberOfDaysPerYear < RemainingDays) {
			NewDate.Year++;
			RemainingDays -= NumberOfDaysPerYear;
		}
		else {
			NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(NewDate);
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
	return (DateOne.Year > DateTwo.Year) ? true : (DateOne.Year < DateTwo.Year) ? false : (DateOne.Month > DateTwo.Month) ? true : (DateOne.Month < DateTwo.Month) ? false : (DateOne.Day > DateTwo.Day);
}

bool isDateOneEqualDateTwo(sDay DateOne, sDay DateTwo) {
	return (DateOne.Year != DateTwo.Year) ? false : (DateOne.Month != DateTwo.Month) ? false : (DateOne.Day == DateTwo.Day);
}

bool isTheLastDayInTheMonth(sDay Date) {
	return (Date.Day == GetNumberOfDaysPerMonth(Date));
}

bool isTheLastMonthOfTheYear(sDay Date) {
	return (Date.Month == 12);
}

sDay IncreaseDateByOne(sDay Date) {
	if (isTheLastDayInTheMonth(Date)) {
		Date.Day = 1;
		if (isTheLastMonthOfTheYear(Date)) {
			Date.Month = 1;
			Date.Year++;
		}
		else {
			Date.Month++;
		}
	}
	else
		Date.Day++;
	return Date;

}

short CalculateDifferenceSameYear(sDay DateOne, sDay DateTwo) {
	short Temp = 0;
	sDay stTemp;
	if (DateOne.Year == DateTwo.Year)
		Temp = CountDaysFromFirstJanuary(DateOne) - CountDaysFromFirstJanuary(DateTwo);
	else {
		for (int i = DateTwo.Year + 1; i < DateOne.Year; i++){
			stTemp.Day = 31;
			stTemp.Month = 12;
			stTemp.Year = i;
			Temp += GetNumberOfDaysPerYear(stTemp);
		}
		Temp += GetNumberOfDaysPerYear(DateOne) - CountDaysFromFirstJanuary(DateTwo) + GetNumberOfDaysPerMonth(DateOne);
	}
	return Temp;
}

short DifferenceBetweenDateOneAndDateTwo(sDay DateOne, sDay DateTwo) {
	if (isDateOneBeforeDateTwo(DateOne, DateTwo))
		return CalculateDifferenceSameYear(DateOne, DateTwo);
	else
		return CalculateDifferenceSameYear(DateTwo, DateOne);
}

int main() {
	sDay DateOne = ReadFullDate();
	/*sDay DateTwo = ReadFullDate();
	cout << "Difference is  : " << DifferenceBetweenDateOneAndDateTwo(DateOne, DateTwo) - 1<< "day (s)";
	cout << "Difference (including the end day) is  : " << DifferenceBetweenDateOneAndDateTwo(DateOne, DateTwo) << "day (s)";
	*/
	cout << CountDaysFromFirstJanuary(DateOne);
	return 0;
}