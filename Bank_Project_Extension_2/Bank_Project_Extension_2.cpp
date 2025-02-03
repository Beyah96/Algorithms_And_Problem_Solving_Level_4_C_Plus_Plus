#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>


using namespace std;
static string Delim = "###|||###";
static string FileName = "ClientFile.Text";
void PrintMainMenueScreen();
void GoBackToTransactionMenuScreen();

string TabFunction(short Number) {
	string Tab = "";
	for (short i = 0; i < Number; i++)
		Tab += "\t";
	return Tab;
}
struct stClient {
	string AccountNumber, PINCode, Name, PhoneNumber;
	double Balance;
	bool HasToBeDeleted = false;
};

vector <string> SplitString(string RecordLine) {
	vector <string> vRecord;
	string sWord = "";
	short Pos = 0;
	while ((Pos = RecordLine.find(Delim)) != string::npos) {
		sWord = RecordLine.substr(0, Pos);
		if (sWord != " ")
			vRecord.push_back(sWord);
		RecordLine.erase(0, Pos + Delim.length());
	}
	if (RecordLine != "")
		vRecord.push_back(RecordLine);
	return vRecord;
}


stClient ConvertLineToRecord(string RecordLine) {
	vector <string> vRecord = SplitString(RecordLine);
	stClient Client;
	Client.AccountNumber = vRecord[0];
	Client.PINCode = vRecord[1];
	Client.Name = vRecord[2];
	Client.PhoneNumber = vRecord[3];
	Client.Balance = stod(vRecord[4]);
	return Client;
}

enum enMainMenuOptions { eClientList = 1, eAddClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransaction = 6, eExit = 7 };
enum enTransactions { eDeposit = 1, eWithDraw = 2, eTotalBalances = 3, eMainMenue = 4 };

vector <stClient> LoadClientsFromFile(string FileName) {
	vector <stClient> vClients;
	string sLine;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open()) {
		while (getline(MyFile, sLine)) {
			vClients.push_back(ConvertLineToRecord(sLine));
		}
		MyFile.close();
	}
	return vClients;
};


void GoBackToMainMenuScreen() {
	cout << endl << endl << "Press any key to go to main menu screen!" << endl;
	system("pause>0");
	PrintMainMenueScreen();
};


void PrintClientRecordLine(stClient Client) {
	cout << "|" << left << setw(14) << Client.AccountNumber << "|" << left << setw(10) << Client.PINCode << "|" << left << setw(30) << Client.Name << "|" << left << setw(13) << Client.PhoneNumber << "|" << left << setw(10) << Client.Balance << "|" << endl;

}
void ShowAllClientsScreen() {

	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Showing All Clients Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl;
	vector <stClient> vClients = LoadClientsFromFile(FileName);
	cout << " --------------------------------------------------------------------------------" << endl;
	cout << "|" << left << setw(14) << "Account Number" << "|" << left << setw(10) << "PIN Code" << "|" << left << setw(30) << "Client Name " << "|" << left << setw(13) << "Phone Number" << "|" << left << setw(10) << "Balance" << "|" << endl;
	cout << " --------------------------------------------------------------------------------" << endl;
	if (vClients.size() == 0)
		cout << "No Client Available in the system!" << endl;
	else
		for (stClient Client : vClients)
			PrintClientRecordLine(Client);
};

bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {
	string sLine;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open()) {
		while (getline(MyFile, sLine))
			if (ConvertLineToRecord(sLine).AccountNumber == AccountNumber) {
				MyFile.close();
				return true;
			}
		MyFile.close();
	}
	return false;
}

stClient ReadNewClient() {
	stClient Client;
	cout << "Account Number : ";
	cin >> Client.AccountNumber;

	while (ClientExistsByAccountNumber(Client.AccountNumber, FileName)) {
		cout << "Client with Account number : [" << Client.AccountNumber << "] already exists enter another account Number : ";
		getline(cin >> ws, Client.AccountNumber);
	};

	cout << "PIN Code : ";
	cin >> Client.PINCode;
	cout << "Full Name : ";
	getline(cin >> ws, Client.Name);
	cout << "Phone Number : ";
	cin >> Client.PhoneNumber;
	cout << "Balance : ";
	cin >> Client.Balance;

	return Client;

}

string ConvertRecordToLine(stClient Client) {
	return Client.AccountNumber + Delim + Client.PINCode + Delim + Client.Name + Delim + Client.PhoneNumber + Delim + to_string(Client.Balance);
}

void AddDataLineToFile(string FileName, string Line) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << Line << endl;
		MyFile.close();
	}
}

void AddNewClient() {
	stClient Client = ReadNewClient();
	AddDataLineToFile(FileName, ConvertRecordToLine(Client));
}

void AddNewClients() {
	system("cls");
	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Show Adding Clients Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl;
	char AddMore = 'Y';
	do {
		AddNewClient();

		cout << "Do you want to add a new client? : ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void ShowAddClientsScreen() {
	AddNewClients();
};

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client) {
	if (ClientExistsByAccountNumber(AccountNumber, FileName)) {
		for (stClient TempClient : vClients)
			if (TempClient.AccountNumber == AccountNumber) {
				Client = TempClient;
				return true;
			}
	}
	return false;
}

void PrintClientCard(stClient Client) {
	system("cls");

	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Client Card : " << endl;
	cout << TabFunction(4) << "======================================" << endl;

	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin Code : " << Client.PINCode << endl;
	cout << "Full Name : " << Client.Name << endl;
	cout << "Phone Number : " << Client.PhoneNumber << endl;
	cout << "Account Balance: " << Client.Balance << endl;
}

void SaveClientsDataToFile(string FileName, vector <stClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stClient Client : vClients)
			if (!Client.HasToBeDeleted)
				MyFile << ConvertRecordToLine(Client) << endl;
		MyFile.close();
	}
}

void MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients) {
	for (stClient& Client : vClients)
		if (Client.AccountNumber == AccountNumber)
			Client.HasToBeDeleted = true;
}

void DeleteClientByAccountNumber(string AccountNumber, vector <stClient> vClients) {
	stClient Client;
	char Answer;
	vClients = LoadClientsFromFile(FileName);
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "\n\n Are you sure, you want to delete this client? : ";
		cin >> Answer;
		if (toupper(Answer) == 'Y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(FileName, vClients);
			cout << endl << endl << "Client Deleted Successfuly" << endl;
		}
	}
	else
		cout << "No client with [" << AccountNumber << "] as account number!" << endl;
}

string ReadClientAccountNumber() {
	string AccountNumber = "";
	cout << "Please enter the account number : ";
	cin >> AccountNumber;
	return AccountNumber;
}
void ShowDeleteClientScreen() {
	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Delete Client Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl;
	vector <stClient> vClients = LoadClientsFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
};

void ChangeClientRecord(stClient& Client) {
	system("cls");

	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Change Client record : " << endl;
	cout << TabFunction(4) << "======================================" << endl;

	cout << "PIN Code : ";
	cin >> Client.PINCode;
	cout << "Full Name : ";
	getline(cin >> ws, Client.Name);
	cout << "Phone Number : ";
	cin >> Client.PhoneNumber;
	cout << "Balance : ";
	cin >> Client.Balance;

}
void UpdateClientData(string AccountNumber, vector <stClient>& vClients) {
	stClient Client;
	char Answer;
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << endl << endl << "Are you sure you want to update this client? : " << endl;
		cin >> Answer;
		for (stClient& TempClient : vClients)
			if (toupper(Answer) == 'Y') {
				ChangeClientRecord(TempClient);
				break;
			}
		SaveClientsDataToFile(FileName, vClients);
		cout << endl << endl << "Client updated successfuly!!" << endl;
	}
}

void ShowUpdateClientScreen() {
	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Update Client Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl;
	vector <stClient> vClients = LoadClientsFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientData(AccountNumber, vClients);
};

void ShowFindClientScreen() {
	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Find Client Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl;
	vector <stClient> vClients = LoadClientsFromFile(FileName);
	string AccountNumber = ReadClientAccountNumber();
	stClient Client;
	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
	}
};

void ShowEndScreen() {
	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Program Ends : " << endl;
	cout << TabFunction(4) << "======================================" << endl;

};

void Deposit(string AccountNumber, vector <stClient>& vClients, double DepositAmount) {
	stClient Client;
	char ContinueTransaction = 'n';
	cout << "Are you sure you want to perform this transaction ? y/n : ";
	cin >> ContinueTransaction;
	if (toupper(ContinueTransaction) == 'Y') {
		for (stClient& Client : vClients)
			if (Client.AccountNumber == AccountNumber) {
				Client.Balance += DepositAmount;
				SaveClientsDataToFile(FileName, vClients);
				cout << "Done successfully. New Balance is: " << Client.Balance << endl;
			}
	}
}


void PrintTotalBalances(stClient Client) {

	cout << "|" << left << setw(14) << Client.AccountNumber << "|" << left << setw(30) << Client.Name << "|" << left << setw(10) << Client.Balance << "|" << endl;
	cout << " --------------------------------------------------------" << endl;
}

double ReadAmount(string Message) {
	double Amount;
	do {
		cout << Message;
		cin >> Amount;
	} while (Amount < 0);
	return Amount;
}

void ShowDepositScreen() {
	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Deposit Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl;
	string AccountNumber = ReadClientAccountNumber();
	vector <stClient> vClients = LoadClientsFromFile(FileName);
	stClient Client;

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "Client with [" << AccountNumber << "] does not exist." << endl;
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double DepositAmount = ReadAmount("Please enter Deposit Amount : ");
	Deposit(AccountNumber, vClients, DepositAmount);
};


void ShowWithDrawScreen() {

	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Deposit Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl;
	string AccountNumber = ReadClientAccountNumber();
	vector <stClient> vClients = LoadClientsFromFile(FileName);
	stClient Client;

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "Client with [" << AccountNumber << "] does not exist." << endl;
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double DepositAmount = ReadAmount("Please enter Deposit Amount : ");
	while (DepositAmount > Client.Balance) {
		cout << "Amount exceeds the balance, you can withdraw up to : " << Client.Balance << endl;
		DepositAmount = ReadAmount("Please enter Deposit Amount : ");
	}

	Deposit(AccountNumber, vClients, DepositAmount * -1);

};

void ShowTotalBalancesScreen() {
	double TotalBalances = 0;
	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Balances List : " << endl;
	cout << TabFunction(4) << "======================================" << endl;
	vector <stClient> vClients = LoadClientsFromFile(FileName);
	cout << endl << endl << endl << " --------------------------------------------------------" << endl;
	cout << "|" << left << setw(14) << "Account Number" << "|" << left << setw(30) << "Client Name " << "|" << left << setw(10) << "Balance" << "|" << endl;
	cout << " --------------------------------------------------------" << endl;
	if (vClients.size() == 0)
		cout << "No Client Available in the system!" << endl;
	else
		for (stClient Client : vClients) {
			PrintTotalBalances(Client);
			TotalBalances += Client.Balance;
		}
	cout << "\t\t Total balances = " << TotalBalances << endl;
};


short ReadOption(short From, short To) {
	short Choice;
	do {
		cout << "Chose what do you want to do? [" << From << "to" << To << "] : ";
		cin >> Choice;
	} while (Choice < From || Choice > To);
	return Choice;
}

void PerformingTransactionMenueOption(enTransactions Transaction) {
	system("cls");
	switch (Transaction)
	{
	case eDeposit:
		ShowDepositScreen();
		break;
	case eWithDraw:
		ShowWithDrawScreen();
		break;
	case eTotalBalances:
		ShowTotalBalancesScreen();
		break;
	case eMainMenue:
		PrintMainMenueScreen();
		break;
	}

	if (Transaction != enTransactions::eMainMenue)
		GoBackToTransactionMenuScreen();
};

void ShowTransactionsScreen() {
	system("cls");
	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Transactions Menu Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl;

	cout << setw(3) << "[1] Deposit." << endl;
	cout << setw(3) << "[2] Withdraw." << endl;
	cout << setw(3) << "[3] Total Balances." << endl;
	cout << setw(3) << "[4] Main Menue." << endl;

	PerformingTransactionMenueOption((enTransactions)ReadOption(1, 4));
}

void GoBackToTransactionMenuScreen() {
	cout << "Press any key to go to transactions menu!";
	system("pause>0");
	ShowTransactionsScreen();
}

void PerformingMainMenueOption(enMainMenuOptions MainMenuOption) {
	system("cls");
	switch (MainMenuOption)
	{
	case eClientList:
		ShowAllClientsScreen();
		break;
	case eAddClient:
		AddNewClients();
		break;
	case eDeleteClient:
		ShowDeleteClientScreen();
		break;
	case eUpdateClient:
		ShowUpdateClientScreen();
		break;
	case eFindClient:
		ShowFindClientScreen();
		break;
	case eTransaction:
		ShowTransactionsScreen();
		break;
	case eExit:
		ShowEndScreen();
		break;
	default:
		break;
	}
	if (MainMenuOption != enMainMenuOptions::eExit)
		GoBackToMainMenuScreen();
}


void PrintMainMenueScreen() {
	system("cls");

	cout << TabFunction(4) << "======================================" << endl;
	cout << TabFunction(5) << "Main Menu Screen : " << endl;
	cout << TabFunction(4) << "======================================" << endl << endl << endl;

	cout << setw(3) << "[1] Show client list." << endl;
	cout << setw(3) << "[2] Add New client." << endl;
	cout << setw(3) << "[3] Delete client." << endl;
	cout << setw(3) << "[4] Update client info." << endl;
	cout << setw(3) << "[5] Find client." << endl;
	cout << setw(3) << "[6] Transactions." << endl;
	cout << setw(3) << "[7] Manage Users" << endl;
	cout << setw(3) << "[8] Logout." << endl;
	cout << "======================================" << endl << endl;

	PerformingMainMenueOption((enMainMenuOptions)ReadOption(1, 7));
}

int main() {
	PrintMainMenueScreen();
	system("pause>0");
	return 0;
}