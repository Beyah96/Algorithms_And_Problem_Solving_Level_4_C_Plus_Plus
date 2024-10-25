#include <iostream>
#include <string>
#include <iomanip>

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
    return (Year % 400 == 0) || (Year % 100 != 0 && Year % 4 == 0);
}

short GetNumberOfDaysPerMonth(short Year, short Month) {
    short MonthsArr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (Month > 12 || Month < 1)
        return 0;

    return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : MonthsArr[Month - 1];
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
    cout << "--------------------------------- " << left << setw(10) << GetMonthName(MonthIndex) << "-------------------------------" << endl;
    cout << left << setw(11) << "Sunday" << left << setw(11) << "Monday" << left << setw(11) << "Tuesday" << left << setw(11) << "Wednesday" << left << setw(11) << "Thursday" << left << setw(11) << "Friday" << left << setw(11) << "Saturday" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
}

void PrintMonthCalenderContent(short NumberOfDaysPerMonth, short DayOrder) {
    for (int i = 0; i < DayOrder + NumberOfDaysPerMonth; i++){
        if(i % 7 == 0) (cout << endl);
        (i < DayOrder) ? (cout << left << setw(11) << "") : (cout << left << setw(11) << i - DayOrder + 1);
    }
}

void PrintMonthCalender(short Month, short Year) {
    short Day = 1;
    cout << endl;
    short DayOrder = GetDayOrder(Day, Month, Year);
    short NumberOfDaysPerMonth = GetNumberOfDaysPerMonth(Year, Month);
    PrintMonthCalenderHeader(Month);
    PrintMonthCalenderContent(NumberOfDaysPerMonth, DayOrder);
}

void PrintYearCalender() {
    short Year = ReadNumber("Please enter the year: ");
    cout << endl << endl;
    for (short Month = 1; Month <= 12; Month++) {
        PrintMonthCalender(Month, Year);
        cout << endl <<  "===========================================================================" << endl<<endl; // Ajout d'une séparation entre les mois
    }
}

int main() {
    PrintYearCalender();
    return 0;
}
