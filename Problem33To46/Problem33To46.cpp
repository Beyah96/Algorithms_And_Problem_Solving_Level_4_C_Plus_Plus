#pragma warning(disable : 4996)

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

void PrshortMonthCalenderHeader(short MonthIndex) {
	cout << endl << endl;
	cout << "--------------------------------- " << left << setw(10) << GetMonthName(MonthIndex) << "-------------------------------" << endl;
	cout << left << setw(11) << "Sunday" << left << setw(11) << "Monday" << left << setw(11) << "Tuesday" << left << setw(11) << "Wednesday" << left << setw(11) << "Thursday" << left << setw(11) << "Friday" << left << setw(11) << "Saturday" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
}

void PrshortMonthCalenderContent(short NumberOfDaysPerMonth, short DayOrder) {
	for (short i = 0; i < DayOrder + NumberOfDaysPerMonth; i++) {
		if (i % 7 == 0) cout << endl;
		(i < DayOrder) ? (cout << left << setw(11) << "") : (cout << left << setw(11) << i - DayOrder + 1);
	}
}

void PrshortMonthCalender(sDay Date) {
	short DayOrder = GetDayOrder(1, Date.Month, Date.Year);
	short NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(Date);
	PrshortMonthCalenderHeader(Date.Month);
	PrshortMonthCalenderContent(NumberOfDaysPerMonth, DayOrder);
}
short CountDaysFromFirstJanuary(sDay Date) {
	short NumberOfDaysFromFirstJanuary = 0;
	short TempMonth = Date.Month;
	for (short Month = 1; Month < TempMonth; Month++) {
		Date.Month = Month;
		NumberOfDaysFromFirstJanuary += GetNumberOfDaysPerMonth(Date);
	}
	return NumberOfDaysFromFirstJanuary + Date.Day;
}


void PrintYearCalender(sDay Date) {
	for (short Month = 1; Month <= 12; Month++) {
		Date.Month = Month;
		PrshortMonthCalender(Date);
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
	Date = FindDate(DayOrerInYear, Date);
	printf("Date for [%d] is :  %d/%d/%d", DayOrerInYear, Date.Day, Date.Month, Date.Year);
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

bool isTheFirstDayInTheMonth(sDay Date) {
	return (Date.Day == 1);
}


bool isTheFirstMonthOfTheYear(sDay Date) {
	return (Date.Month == 1);
}


sDay DecreaseDateByOne(sDay Date) {
	short NumberOfDaysIntheMonth;
	if (isTheFirstDayInTheMonth(Date)) {
		if (isTheFirstMonthOfTheYear(Date)) {
			Date.Month = 12;
			Date.Year--;
			Date.Day = 31;
		}
		else {
			Date.Month--;
			NumberOfDaysIntheMonth = GetNumberOfDaysPerMonth(Date);
			Date.Day = NumberOfDaysIntheMonth;
		}
	}
	else
		Date.Day--;
	return Date;

}

short CalculateDifferenceSameYear(sDay DateOne, sDay DateTwo) {
	short Temp = 0;
	sDay stTemp;
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

short DifferenceBetweenDateOneAndDateTwo(sDay DateOne, sDay DateTwo, bool IncludeEndDay = false) {
	short Difference = (isDateOneBeforeDateTwo(DateOne, DateTwo)) ? CalculateDifferenceSameYear(DateOne, DateTwo) : CalculateDifferenceSameYear(DateTwo, DateOne);
	short result = (isDateOneBeforeDateTwo(DateOne, DateTwo)) ? 1 : -1;
	result *= (Difference + (short)IncludeEndDay);
	return result;
}

sDay DecreaseDateByXDays(short Days, sDay Date) {
	for (short Day = 1; Day <= Days; Day++)
		Date = DecreaseDateByOne(Date);
	return Date;
}

sDay DecreaseDateByOneWeek(sDay Date) {
	return DecreaseDateByXDays(7, Date);
}

sDay DecreaseDateByXWeeks(short Weeks, sDay Date) {
	for (short Week = 1; Week <= Weeks; Week++)
		Date = DecreaseDateByOneWeek(Date);
	return Date;
}

sDay DecreaseDateByOneMonth(sDay Date) {
	if (Date.Month == 1) {
		Date.Month = 12;
		Date.Year--;
	}
	else
		Date.Month--;
	return Date;
}

//sDay DecreaseDateByXMonth(short Months, sDay Date) {
//	for (short Month = 1; Month <= Months; Month++)
//		Date = DecreaseDateByOneMonth(Date);
//	return Date;
//}

sDay DecreaseDateByXMonths(short Months, sDay Date) {
	for (short Month = 1; Month <= Months; Month++)
		Date = DecreaseDateByOneMonth(Date);
	return Date;
}


sDay DecreaseDateByOneYear(sDay Date) {
	Date.Year--;
	return Date;
}

sDay DecreaseDateByXYears(short Years, sDay Date) {
	for (short Year = 1; Year <= Years; Year++)
		Date = DecreaseDateByOneYear(Date);
	return Date;
}

sDay DecreaseDateByXYearsFaster(short Years, sDay Date) {
	Date.Year -= Years;
	return Date;
}

sDay DecreaseDateByOneDecade(sDay Date) {
	return DecreaseDateByXYears(10, Date);
}

sDay DecreaseDateByOneDecadeFaster(sDay Date) {
	Date.Year -= 10;
	return Date;
}

sDay DecreaseDateByXDecades(short Decades, sDay Date) {
	for (short Decade = 1; Decade <= Decades; Decade++)
		Date = DecreaseDateByOneDecade(Date);
	return Date;
}

sDay DecreaseDateByXDecadesFaster(short Decades, sDay Date) {
	Date.Year -= Decades * 10;
	return Date;
}

sDay DecreaseDateByOneCentury(sDay Date) {
	Date.Year -= 100;
	return  Date;
}

sDay DecreaseDateByOneMillennium(sDay Date) {
	for (short Century = 1; Century <= 10; Century++)
		Date = DecreaseDateByOneCentury(Date);
	return Date;
}

void PrintDate(sDay Date, string Message) {
	cout << Message << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
}

int main() {
	sDay DateOne = ReadFullDate();
	DateOne = DecreaseDateByOne(DateOne);
	PrintDate(DateOne, "01 - Subtracting one day is : ");
	DateOne = DecreaseDateByXDays(10, DateOne);
	PrintDate(DateOne, "02 - Subtracting 10 days is : ");
	DateOne = DecreaseDateByOneWeek(DateOne);
	PrintDate(DateOne, "03 - Subtracting one week is : ");
	DateOne = DecreaseDateByXWeeks(10, DateOne);
	PrintDate(DateOne, "04 - Subtracting 10 weeks is : ");
	DateOne = DateOne = DecreaseDateByOneMonth(DateOne);
	PrintDate(DateOne, "05 - Subtracting one month is : ");
	DateOne = DecreaseDateByXMonths(5, DateOne);
	PrintDate(DateOne, "06 - Subtracting 5 months is : ");
	DateOne = DecreaseDateByOneYear(DateOne);
	PrintDate(DateOne, "07 - Subtracting one year is : ");
	DateOne = DecreaseDateByXYears(10, DateOne);
	PrintDate(DateOne, "08 - Subtracting 10 years is : ");
	DateOne = DecreaseDateByXYearsFaster(10, DateOne);
	PrintDate(DateOne, "09 - Subtracting 10 years (faster) is : ");
	DateOne = DecreaseDateByOneDecade(DateOne);
	PrintDate(DateOne, "10 - Subtracting one decade is : ");
	DateOne = DecreaseDateByXDecades(10, DateOne);
	PrintDate(DateOne, "11 - Subtracting 10 decades is : ");
	DateOne = DecreaseDateByXDecadesFaster(10, DateOne);
	PrintDate(DateOne, "12 - Subtracting 10 decades (faster) is : ");
	DateOne = DecreaseDateByOneCentury(DateOne);
	PrintDate(DateOne, "13 - Subtracting one century is : ");
	DateOne = DecreaseDateByOneMillennium(DateOne);
	PrintDate(DateOne, "14 - Subtracting one millennium is : ");
	return 0;
}