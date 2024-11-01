#include <iostream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <vector>

using namespace std;
struct sDate {
	short Day, Month, Year;
};

struct sPeriod {
	sDate DateOne, DateTwo;
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

short GetNumberOfDaysPerMonth(sDate Date) {
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

short GetDayOrder(sDate Date) {
	return GetDayOrder(Date.Day, Date.Month, Date.Year);
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

void PrintMonthCalender(sDate Date) {
	short DayOrder = GetDayOrder(1, Date.Month, Date.Year);
	short NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(Date);
	PrintMonthCalenderHeader(Date.Month);
	PrintMonthCalenderContent(NumberOfDaysPerMonth, DayOrder);
}
short CountDaysFromFirstJanuary(sDate Date) {
	short NumberOfDaysFromFirstJanuary = 0;
	short TempMonth = Date.Month;
	for (short Month = 1; Month < TempMonth; Month++) {
		Date.Month = Month;
		NumberOfDaysFromFirstJanuary += GetNumberOfDaysPerMonth(Date);
	}
	return NumberOfDaysFromFirstJanuary + Date.Day;
}


void PrintYearCalender(sDate Date) {
	for (short Month = 1; Month <= 12; Month++) {
		Date.Month = Month;
		PrintMonthCalender(Date);
	}
}

sDate FindDate(short DayOrderInYear, sDate Date) {
	sDate stSearchedDate;
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

void ConvertBackDate(sDate Date, short DayOrerInYear) {
	Date = FindDate(DayOrerInYear, Date);
	printf("Date for [%d] is :  %d/%d/%d", DayOrerInYear, Date.Day, Date.Month, Date.Year);
}

short GetNumberOfDaysPerYear(sDate Date) {
	return (isLeapYear(Date.Year)) ? 366 : 365;
}
sDate GetDate(sDate NewDate, short NewDays) {
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

void AddDays(sDate Date, short NewDays) {
	sDate stSearchedDate = GetDate(Date, NewDays);
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



sDate ReadFullDate() {
	sDate NewDate;
	NewDate.Day = ReadDay();
	NewDate.Month = ReadMonth();
	NewDate.Year = ReadYear();
	return NewDate;
}

bool isDateOneBeforeDateTwo(sDate DateOne, sDate DateTwo) {
	return (DateOne.Year < DateTwo.Year) ? true : (DateOne.Year > DateTwo.Year) ? false : (DateOne.Month < DateTwo.Month) ? true : (DateOne.Month > DateTwo.Month) ? false : (DateOne.Day < DateTwo.Day);
}

bool isDateOneEqualDateTwo(sDate DateOne, sDate DateTwo) {
	return (DateOne.Year != DateTwo.Year) ? false : (DateOne.Month != DateTwo.Month) ? false : (DateOne.Day == DateTwo.Day);
}

bool isDateOneAfterDateTwo(sDate DateOne, sDate DateTwo) {
	return !(isDateOneBeforeDateTwo(DateOne, DateTwo) || isDateOneEqualDateTwo(DateOne, DateTwo));
}

bool isTheLastDayshortheMonth(sDate Date) {
	return (Date.Day == GetNumberOfDaysPerMonth(Date));
}

bool isTheLastMonthOfTheYear(sDate Date) {
	return (Date.Month == 12);
}

sDate IncreaseDateByOne(sDate Date) {
	if (isTheLastDayshortheMonth(Date)) {
		Date.Day = 1;
		if (isTheLastMonthOfTheYear(Date)) {
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;
	}
	else
		Date.Day++;
	return Date;

}

short CalculateDifferenceSameYear(sDate DateOne, sDate DateTwo) {
	short Temp = 0;
	sDate stTemp;
	if (DateOne.Year == DateTwo.Year)
		return CountDaysFromFirstJanuary(DateOne) - CountDaysFromFirstJanuary(DateTwo);
	else {
		for (short Year = DateTwo.Year + 1; Year < DateOne.Year; Year++) {
			stTemp.Year = Year;
			Temp += GetNumberOfDaysPerYear(stTemp);
		}
		return Temp + GetNumberOfDaysPerYear(DateTwo) + CountDaysFromFirstJanuary(DateOne) - CountDaysFromFirstJanuary(DateTwo);
	}
}

short DifferenceBetweenDateOneAndDateTwo(sDate DateOne, sDate DateTwo, bool IncludeEndDay = false) {
	short Difference = (isDateOneBeforeDateTwo(DateOne, DateTwo)) ? CalculateDifferenceSameYear(DateTwo, DateTwo) : CalculateDifferenceSameYear(DateOne, DateTwo);
	short result = (isDateOneBeforeDateTwo(DateOne, DateTwo)) ? -1 : 1;
	result *= (Difference + (short)IncludeEndDay);
	return result;
}

sDate IncreaseDateByXDays(short Days, sDate Date) {
	for (short Day = 1; Day <= Days; Day++)
		Date = IncreaseDateByOne(Date);
	return Date;
}

sDate IncreaseDateByOneWeek(sDate Date) {
	return IncreaseDateByXDays(7, Date);
}

sDate IncreaseDateByXWeeks(short Weeks, sDate Date) {
	for (short Week = 1; Week <= Weeks; Week++)
		Date = IncreaseDateByOneWeek(Date);
	return Date;
}

sDate IncreaseDateByOneMonth(sDate Date) {
	short NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(Date);
	for (short Day = 1; Day <= NumberOfDaysPerMonth; Day++)
		Date = IncreaseDateByOne(Date);
	return Date;
}


sDate IncreaseDateByXMonths(short Months, sDate Date) {
	for (short Month = 1; Month <= Months; Month++)
		Date = IncreaseDateByOneMonth(Date);
	return Date;
}


sDate IncreaseDateByOneYear(sDate Date) {
	Date.Year++;
	return Date;
}

sDate IncreaseDateByXYears(short Years, sDate Date) {
	for (short Year = 1; Year <= Years; Year++)
		Date = IncreaseDateByOneYear(Date);
	return Date;
}

sDate IncreaseDateByXYearsFaster(short Years, sDate Date) {
	Date.Year += Years;
	return Date;
}

sDate IncreaseDateByOneDecade(sDate Date) {
	return IncreaseDateByXYears(10, Date);
}

sDate IncreaseDateByOneDecadeFaster(sDate Date) {
	Date.Year += 10;
	return Date;
}

sDate IncreaseDateByXDecades(short Decades, sDate Date) {
	for (short Decade = 1; Decade <= Decades; Decade++)
		Date = IncreaseDateByOneDecade(Date);
	return Date;
}

sDate IncreaseDateByXDecadesFaster(short Decades, sDate Date) {
	Date.Year += Decades * 10;
	return Date;
}

sDate IncreaseDateByOneCentury(sDate Date) {
	Date.Year += 100;
	return  Date;
}

sDate IncreaseDateByOneMillennium(sDate Date) {
	for (short Century = 1; Century <= 10; Century++)
		Date = IncreaseDateByOneCentury(Date);
	return Date;
}

void PrintDate(sDate Date, string Message) {
	cout << Message << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
}

bool IsEndOfTheWeek(sDate Date) {
	return (GetDayOrder(Date) == 6);
}

bool IsWeekEnd(sDate Date) {
	return (GetDayOrder(Date) >= 5);
}

bool IsBusinessDay(sDate Date) {
	return !IsWeekEnd(Date);
}

short DaysUntilTheEndOfWeek(sDate Date) {
	return (6 - GetDayOrder(Date));
}
short DaysUntilTheEndOfMonth(sDate Date) {
	short NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(Date);
	sDate TempDate = Date;
	TempDate.Day = NumberOfDaysPerMonth;
	return DifferenceBetweenDateOneAndDateTwo(TempDate, Date, true);
}
short DaysUntilTheEndOfYear(sDate Date) {
	sDate TempDate;
	TempDate.Day = 31;
	TempDate.Month = 12;
	TempDate.Year = Date.Year;
	return DifferenceBetweenDateOneAndDateTwo(TempDate, Date, true);
}

short GetActualVacationDays(sDate DateFrom, sDate DateTo) {
	short Difference = DifferenceBetweenDateOneAndDateTwo(DateTo, DateFrom);
	short HowManyDaysUntilEndOfWeek = DaysUntilTheEndOfWeek(DateFrom) + 1;
	short NumberOfWeeks = (Difference - HowManyDaysUntilEndOfWeek) / 7;
	short Remainder = (NumberOfWeeks > 0) ? ((Difference - HowManyDaysUntilEndOfWeek) % 7) : 0;
	HowManyDaysUntilEndOfWeek = (HowManyDaysUntilEndOfWeek > 2) ? (HowManyDaysUntilEndOfWeek - 2) : 0;
	Remainder = (Remainder > 5) ? 5 : Remainder;
	return HowManyDaysUntilEndOfWeek + NumberOfWeeks * 5 + Remainder;
}


sDate GetVacationReturnDate(sDate DateFrom) {
	short ActualVacationDays = ReadNumber("Please enter vacation days : ");
	short WeekendCounter = 0;
	for (short i = 1; i <= ActualVacationDays + WeekendCounter; i++) {
		if (IsWeekEnd(DateFrom))
			WeekendCounter++;
		DateFrom = IncreaseDateByOne(DateFrom);
	}
	while (IsWeekEnd(DateFrom))
		DateFrom = IncreaseDateByOne(DateFrom);
	return DateFrom;
}

enum enDateCompare { After = -1, Same = 0, Before = 1 };

short CompareTwoDates(sDate DateOne, sDate DateTwo) {
	short result;
	(isDateOneAfterDateTwo(DateOne, DateTwo)) ? (result = 1) : (isDateOneEqualDateTwo(DateOne, DateTwo) ? result = 0 : result = -1);
	return result;
}

enDateCompare CompareTwoDatesWithEnums(sDate DateOne, sDate DateTwo) {
	enDateCompare result;
	(isDateOneAfterDateTwo(DateOne, DateTwo)) ? (result = enDateCompare::Before) : (isDateOneEqualDateTwo(DateOne, DateTwo) ? result = enDateCompare::Same : result = After);
	return result;
}

sPeriod ReadPeriod() {
	sPeriod Period;
	cout << endl << "Priod's Date One : " << endl;
	Period.DateOne = ReadFullDate();
	do {
		cout << endl << "Priod's Date Two : " << endl;
		Period.DateTwo = ReadFullDate();
	} while (isDateOneBeforeDateTwo(Period.DateTwo, Period.DateOne));
	return Period;
}


bool isPeriodsOverlap(sPeriod PeriodOne, sPeriod PeriodTwo) {
	return ((CompareTwoDates(PeriodOne.DateOne, PeriodTwo.DateTwo) != 1) && (CompareTwoDates(PeriodOne.DateTwo, PeriodTwo.DateOne) != -1));
}

bool isPeriodsOverlapSecondVersion(sPeriod PeriodOne, sPeriod PeriodTwo) {
	return ((CompareTwoDates(PeriodOne.DateOne, PeriodTwo.DateTwo) == enDateCompare::After) || (CompareTwoDates(PeriodOne.DateTwo, PeriodTwo.DateOne) == enDateCompare::Before));
}
int main() {
	cout << endl << "Period one : " << endl;
	sPeriod PeriodOne = ReadPeriod();
	cout << endl << "Period Two : " << endl;
	sPeriod PeriodTwo = ReadPeriod();
	(isPeriodsOverlapSecondVersion(PeriodOne, PeriodTwo)) ? (cout << "Yes, Periods overlap .") : (cout << "No, Periods do not overlap .");
	return 0;
}