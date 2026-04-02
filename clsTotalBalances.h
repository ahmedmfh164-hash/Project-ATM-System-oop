#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsATMClient.h"
#include"Global.h"

class clsTotalBalances:protected clsScreen
{
private:

    static void _PrintBalanceRecord(clsBankClient &Client)
    {
        clsUtil::SetColor(1);
        cout << setw(34) << left << "" << "\tBalances : " << fixed << setprecision(0)<< Client.AccountBalance;
        cout << endl;
    }

public:

    static void ShowYourBalances()
    {
        _DrawScreenHeader("\t  Show Balances Screen ");

        cout << setw(33) << left << "" << "========================================================\n\n";
        cout << setw(33) << left << "" << "\t\t      Your Balances \n\n";
        cout << setw(33) << left << "" << "========================================================\n";
        _PrintBalanceRecord(CurrentClient);
        cout << setw(33) << left << "" << "========================================================\n";

        cout << "\n";

    }




};

