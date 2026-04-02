#pragma once
#include"clsPerson.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"clsString.h"
#include"clsDate.h"

class clsBankClient :public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector<string>vClientData;
		vClientData = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string sperator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += Client.FirstName + sperator;
		stClientRecord += Client.LastName + sperator;
		stClientRecord += Client.Email + sperator;
		stClientRecord += Client.Phone + sperator;
		stClientRecord += Client.AccountNumber() + sperator;
		stClientRecord += Client.PinCode + sperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}

	static string _ConvertTransferDataToLine(clsBankClient Client1, clsBankClient Client2, double Amount, string sperator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += clsDate::GetSystemDateTimeString() + sperator;
		stClientRecord += Client1.AccountNumber() + sperator;
		stClientRecord += to_string(Client1.AccountBalance) + sperator;
		stClientRecord += Client2.AccountNumber() + sperator;
		stClientRecord += to_string(Client2.AccountBalance) + sperator;
		stClientRecord += to_string(Amount) + sperator;
		
		return stClientRecord;

	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient>vClient;
		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClient.push_back(Client);
			}

			MyFile.close();

		}

		return vClient;
	}

	static void _SaveClientDataToFile(vector<clsBankClient> vClient)
	{
		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::out);//overWrite

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient C : vClient)
			{
				if (C._MarkForDelete == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;

				}
			}
			MyFile.close();
		}

	}

	struct stTransfer;

	static stTransfer _ConvertLineToTransferRecord(string Line, string Separator = "#//#")
	{
		stTransfer Transfer;

		vector<string>vTransferData;
		vTransferData = clsString::Split(Line, Separator);

		Transfer.DateTime = vTransferData[0];
		Transfer.AccountNumberFrom = vTransferData[1];
		Transfer.AccountBalanceFrom = stod(vTransferData[2]);
		Transfer.AccountNumberTo = vTransferData[3];
		Transfer.AccountBalanceTo = stod(vTransferData[4]);
		Transfer.Amount = stod(vTransferData[5]);
		Transfer.UserName = vTransferData[6];

		return Transfer;

	}

	static vector<stTransfer> _LoadTransfersDataFromFile()
	{
		vector<stTransfer>vTransfer;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stTransfer Transfer;
			while (getline(MyFile, Line))
			{
				Transfer = _ConvertLineToTransferRecord(Line);
				vTransfer.push_back(Transfer);
			}

			MyFile.close();

		}

		return vTransfer;
	}
	static void _SaveTransferDataToFile(clsBankClient Client1, clsBankClient Client2, double Amount)
	{
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			string DataLine = _ConvertTransferDataToLine(Client1, Client2, Amount);
			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient>_vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientDataToFile(_vClients);

	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}

	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, double AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(put = SetPinCode, get = GetPinCode))string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(put = SetAccountBalance, get = GetAccountBalance))double AccountBalance;


	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient>vClient;

		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				vClient.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient>vClient;

		fstream MyFile;
		MyFile.open("Bank Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClient.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
				return enSaveResults::svFailedEmptyObject;
			break;
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFailedAccountNumberExists;
			}
			else
			{
				_AddNew();

				//we need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}

		}
		return enSaveResults::svSucceeded;

	}

	static clsBankClient GetNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient>_vClient;
		_vClient = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}

		}
		_SaveClientDataToFile(_vClient);

		*this = _GetEmptyClientObject();
		return true;

	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	void Withdraw(double Amount)
	{
		_AccountBalance -= Amount;
		Save();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient>vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients)
		{

			TotalBalances += Client.AccountBalance;

		}

		return TotalBalances;
	}

	bool Transfer(double Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}


		return true;

	}

	struct stTransfer
	{
		string DateTime;
		string AccountNumberFrom;
		string AccountNumberTo;
		double AccountBalanceFrom;
		double AccountBalanceTo;
		double Amount = 0;
		string UserName;
	};

	static void SaveClientDataToFile(vector<clsBankClient>vClient)
	{
		_SaveClientDataToFile(vClient);
	}

	static void SaveTransferDataToFile(clsBankClient Client1, clsBankClient Client2, double Amount)
	{
		_SaveTransferDataToFile(Client1, Client2, Amount);
	}

	static vector<stTransfer> GetTransfersList()
	{
		vector<stTransfer>vTransfer;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stTransfer Transfer;
			while (getline(MyFile, Line))
			{
				Transfer = _ConvertLineToTransferRecord(Line);
				vTransfer.push_back(Transfer);
			}

			MyFile.close();

		}

		return vTransfer;
	}



};

