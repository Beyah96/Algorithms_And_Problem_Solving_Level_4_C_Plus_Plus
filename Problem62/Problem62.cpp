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

string ReadStringDate() {
	string Date;
	cout << "Please enter the date : " ;
	getline(cin >> ws, Date);
	return Date;
}

vector <string> SplitString(string Text, string Delim) {
	vector <string> vString;
	short Pos;
	string sWord;
	while ((Pos = Text.find(Delim)) != string::npos) {
		sWord = Text.substr(0, Pos);
		if (sWord != " ") {
			vString.push_back(sWord);
		}
		Text.erase(0, Pos + Delim.length());
	}
	if (Text != "")
		vString.push_back(Text);
	return vString;
}

sDate StringToDate(string DateString) {
	sDate Date;
	Date.Day = stoi(DateString.substr(0, DateString.find('/')));
	DateString.erase(0, DateString.find('/') + 1);
	Date.Month = stoi(DateString.substr(0, DateString.find('/')));
	DateString.erase(0, DateString.find('/') + 1);
	Date.Year = stoi(DateString);
	return Date;
}

sDate StringToDateSecondVersion(string DateString) {
	sDate Date;
	vector <string> vString = SplitString(DateString, "/");
	Date.Day = stoi(vString[0]);
	Date.Month = stoi(vString[1]);
	Date.Year = stoi(vString[2]);
	return Date;
}

string DateToString(sDate Date) {
	return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
}

string ReplaceWordInString(string Text, string ReplacedWord, string WordToReplace) {
	short Pos;
	string sWord;
	while ((Pos = Text.find(ReplacedWord)) != string::npos)
		Text = Text.replace(Pos, ReplacedWord.length(), WordToReplace);
	return Text;
}

string FormatDate(sDate Date, string DateFormat = "dd/mm/yyyy") {
	string FormattedDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
	FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(Date.Month));
	FormattedDateString = ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date.Year));
	return FormattedDateString;
}

int main() {
	cout << endl << "Period one : " << endl;
	sDate Date = StringToDateSecondVersion(ReadStringDate());
	cout << endl << FormatDate(Date, "dd-mm-yyyy") << endl;
	cout << endl << FormatDate(Date, "dd/mm/yyyy") << endl;
	cout << endl << FormatDate(Date, "mm-dd-yyyy") << endl;
	cout << endl << FormatDate(Date, "mm/dd/yyyy") << endl;
	cout << endl << FormatDate(Date, "mm-yyyy-dd") << endl;
	cout << endl << FormatDate(Date, "mm/yyyy/dd") << endl;
	cout << endl << FormatDate(Date, "Day : dd, Month : mm, Year : yyyy") << endl;

	return 0;
}