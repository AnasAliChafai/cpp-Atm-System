//ATM System Porject
// Copyright (c) 2025 Anas Ali Chafai. All rights reserved.
// Contact: anaschafai04gmail.com


#include<iostream>
#include <cstdlib>
#include<iomanip>
#include<string>
#include<cctype>
#include<vector>
#include<fstream>

using namespace std;

const string ClientsFileName = "Bank.txt";
struct stAccount {
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	float accountBalance = 0;
	bool mark = false;
};
enum enAtm {
	eQuickWithdraw = 1, eNormalWithdraw = 2,
	eDeposit = 3, eCheckBalnce = 4, eLogout = 5
};
stAccount CurrentAcc;
void ATMscreen();
void QuickWithdrawScreen();
void NormalWithdrawScreen();
void Login();
string ReadString(string msg) {
	string s;
	cout << msg;
	getline(cin >> ws, s);
	return s;
}
short ReadNum(string msg) {
	short n;
	cout << msg;
	cin >> n;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
		cout << "please enter a validate num";
		cin >> n;
	}
	return n;
}
short GetChoice(short rangeFrom, short rangeTo) {
	short choice;

	cout << "Choose what to withdraw from [" << rangeFrom << "] to[" << rangeTo << "] ? ";
	cin >> choice;
	return choice;
}
vector <string> SplitString(string S, string delim)
{
	vector <string> vs;
	short pos;
	string word;
	while ((pos = S.find(delim)) != string::npos)
	{
		word = S.substr(0, pos);
		if (word != "")
		{
			vs.push_back(word);
		}
		S.erase(0, pos + delim.length());
	}
	if (S != "")
	{
		vs.push_back(S);
	}
	return vs;
}
stAccount ConvertLineToRecord(string Line, string sperator = "#//#")
{
	vector <string> StringDevided = SplitString(Line, sperator);
	stAccount Acc;
	Acc.accountNumber = StringDevided[0];
	Acc.pinCode = StringDevided[1];
	Acc.name = StringDevided[2];
	Acc.phone = StringDevided[3];
	Acc.accountBalance = stof(StringDevided[4]);
	return Acc;

}
string ConvertRecordToLine(stAccount Account, string sperator = "#//#")
{
	string s = Account.accountNumber + sperator +
		Account.pinCode + sperator + Account.name +
		sperator + Account.phone + sperator +
		to_string(Account.accountBalance);
	return s;
}
void LoadDataFromFile(string FileName, vector <stAccount>& vAcc)
{
	fstream f;
	string line;
	stAccount Acc;
	f.open(FileName, ios::in);
	if (f.is_open())
	{
		while (getline(f, line))
		{
			if (line != "")
			{
				Acc = ConvertLineToRecord(line);
				vAcc.push_back(Acc);
			}
		}
		f.close();
	}
}
void SaveVectorToFile(string FileName, vector <stAccount> vAcc)
{
	fstream f;
	string s;
	f.open(FileName, ios::out);
	if (f.is_open())
	{
		for (stAccount& Account : vAcc)
		{
			s = ConvertRecordToLine(Account);
			f << s << endl;
		}
		f.close();
	}
}
void SaveClientToFile(const stAccount& client)
{
	fstream File;
	File.open(ClientsFileName, ios::out | ios::app);
	if (File.is_open())
	{
		File << ConvertRecordToLine(client) << endl;
		File.close();
	}
}
bool CheckIfClientExist(vector < stAccount>& vAcc, string AccountNumber)
{
	bool R = false;
	for (stAccount& A : vAcc)
	{
		if (A.accountNumber == AccountNumber)
		{
			R = true;
			break;
		}
	}
	return R;
}
bool CheckIfClientExist2(vector < stAccount>& vAcc, string AccountNumber, string PinCode, stAccount& CurrentAcc)
{
	bool R = false;
	for (stAccount& A : vAcc)
	{
		if (A.accountNumber == AccountNumber && A.pinCode == PinCode)
		{
			R = true;
			CurrentAcc = A;
			break;
		}
	}
	return R;
}
bool CheckIfClientExist(vector < stAccount>& vAcc, string AccountNumber, stAccount& ACC)
{
	bool R = false;
	for (stAccount& A : vAcc)
	{
		if (A.accountNumber == AccountNumber)
		{
			A.mark = true;
			ACC = A;
			R = true;
			break;
		}
	}
	return R;
}
void GoBackToATM()
{
	cout << "\nPress any key to go back to ATM Menu...";
	system("pause>nul");
	ATMscreen();
}
void BackToQuickWithdrawScreen()
{
	cout << "\nPress any key to Continue...";
	system("pause>nul");
	QuickWithdrawScreen();
}
void QuickWith(int With)
{
	char y;
	vector <stAccount> vAcc;
	LoadDataFromFile(ClientsFileName, vAcc);
	if (With > CurrentAcc.accountBalance)
	{
		cout << "Amount Exceeds the balance, you can withdraw up to : " << CurrentAcc.accountBalance << endl;
		BackToQuickWithdrawScreen();
	}
	cout << "\n\nAre You Sure You Want To Do This Transaction ? [y/n] : ";
	cin >> y;
	if (tolower(y) == 'y')
	{
		for (stAccount& A : vAcc)
		{
			if (A.accountNumber == CurrentAcc.accountNumber)
			{
				A.accountBalance -= With;
				CurrentAcc.accountBalance = A.accountBalance;
			}
		}
		SaveVectorToFile(ClientsFileName, vAcc);
		cout << "\n\nDone Successfully New Balnce Is : " << CurrentAcc.accountBalance << "\n\n";
	}
}
void ShowQuickWithdrawScreen()
{
	system("cls");
	cout << "=====================================\n";
	cout << "          Quick Withdraw       \n";
	cout << "=====================================\n";
	cout << "[1] 20\t\t";
	cout << "[2] 50\n";
	cout << "[3] 100\t\t";
	cout << "[4] 200\n";
	cout << "[5] 400\t\t";
	cout << "[6] 600\n";
	cout << "[7] 800\t\t";
	cout << "[8] 1000\n";
	cout << "[9] exit\n";
	cout << "=====================================\n";
	cout << "Your Balnce Is " << CurrentAcc.accountBalance << endl;

}
void QuickWithdrawScreen()
{
	ShowQuickWithdrawScreen();
	short choice = GetChoice(1, 9);
	switch (choice)
	{
	case 1: QuickWith(20); break;
	case 2: QuickWith(50); break;
	case 3: QuickWith(100); break;
	case 4: QuickWith(200); break;
	case 5: QuickWith(400); break;
	case 6: QuickWith(600); break;
	case 7: QuickWith(800); break;
	case 8: QuickWith(1000); break;
	case 9: GoBackToATM(); break;
	default: cout << "Invalid choice.\n"; BackToQuickWithdrawScreen(); break;
	}
	GoBackToATM();
}
void GoBackToNormalWithdraw()
{
	cout << "\nPress any key to Continue...";
	system("pause>nul");
	NormalWithdrawScreen();
}
void NormalWith()
{
	int With;
	char y;
	stAccount Acc;
	vector <stAccount> vAcc;
	LoadDataFromFile(ClientsFileName, vAcc);
	do
	{
		cout << "Enter an amount multiple of 5's : ";
		cin >> With;
	} while (With % 5 != 0);
	while (With > CurrentAcc.accountBalance)
	{
		cout << "Amount Exceeds the balance, you can withdraw up to : " << CurrentAcc.accountBalance << endl;
		GoBackToNormalWithdraw();
	}
	cout << "\n\nAre You Sure You Want To Do This Transaction ? [y/n] : ";
	cin >> y;
	if (tolower(y) == 'y')
	{
		for (stAccount& A : vAcc)
		{
			if (A.accountNumber == CurrentAcc.accountNumber)
			{
				A.accountBalance -= With;
				CurrentAcc.accountBalance = A.accountBalance;
			}
		}
		SaveVectorToFile(ClientsFileName, vAcc);
		cout << "\n\nDone Successfully New Balnce Is : " << CurrentAcc.accountBalance << "\n";
	}
}
void NormalWithdrawScreen()
{
	system("cls");
	cout << "------------------------------------------\n"
		<< "\t\tNormal Withdraw Screen\n"
		<< "------------------------------------------\n";
	NormalWith();
	GoBackToATM();
}
void Deposit()
{
	float Dep;
	char y;
	stAccount Acc;
	vector <stAccount> vAcc;
	LoadDataFromFile(ClientsFileName, vAcc);
	cout << "\nPlease Enter Deposit Amount ?  ";
	cin >> Dep;
	cout << "\n\nAre You Sure You Want To Do This Transaction ? [y/n] : ";
	cin >> y;
	if (tolower(y) == 'y')
	{
		for (stAccount& A : vAcc)
		{
			if (A.accountNumber == CurrentAcc.accountNumber)
			{
				A.accountBalance += Dep;
				CurrentAcc.accountBalance = A.accountBalance;
			}
		}
		SaveVectorToFile(ClientsFileName, vAcc);
		cout << "\nDone Successfully New Balnce Is : " << CurrentAcc.accountBalance << "\n";
	}
}
void DepositScreen()
{
	system("cls");
	cout << "------------------------------------------\n"
		<< "\t\tDeposit Screen\n"
		<< "------------------------------------------\n";
	Deposit();
	GoBackToATM();
}
void BlanceCheckScreen()
{
	system("cls");
	cout << "=====================================\n";
	cout << "          Quick Withdraw       \n";
	cout << "=====================================\n";
	cout << "Your Balance Is : " << CurrentAcc.accountBalance;
	GoBackToATM();
}
void ShowATMscreen() {
	system("cls");

	cout << "=====================================\n";
	cout << "          ATM Main Menu Screen       \n";
	cout << "=====================================\n";
	cout << "[1] Quick Withdraw.\n";
	cout << "[2] Normal Withdraw.\n";
	cout << "[3] Deposit.\n";
	cout << "[4] Check Balance.\n";
	cout << "[5] Logout.\n";
	cout << "=====================================\n";
	cout << "Choose what do you want to do? [1 to 5]? ";
}
void ATMscreen()
{
	ShowATMscreen();
	short Select = ReadNum("");
	switch (Select)
	{
	case enAtm::eQuickWithdraw: QuickWithdrawScreen();
		break;
	case enAtm::eNormalWithdraw: NormalWithdrawScreen();
		break;
	case enAtm::eDeposit: DepositScreen();
		break;
	case enAtm::eCheckBalnce: BlanceCheckScreen();
		break;
	case enAtm::eLogout: Login();
		break;
	}
}

void ShowLoginScreen()
{
	system("cls");
	cout << "=====================================\n";
	cout << "           Login Screen              \n";
	cout << "=====================================\n";
}
void Login()
{
	ShowLoginScreen();
	vector <stAccount> vAcc;
	stAccount Acc;
	LoadDataFromFile(ClientsFileName, vAcc);
	string AccountNumber;
	string PinCode;
	do
	{
		AccountNumber = ReadString("Enter Account Number : ");
		PinCode = ReadString("Enter Pin Code : ");
		if (!CheckIfClientExist2(vAcc, AccountNumber, PinCode, CurrentAcc))
		{
			ShowLoginScreen();
			cout << "Invalid Username/Password!\n\n";
		}
	} while (!CheckIfClientExist2(vAcc, AccountNumber, PinCode, CurrentAcc));
	ATMscreen();
}
int main()
{
	Login();
}