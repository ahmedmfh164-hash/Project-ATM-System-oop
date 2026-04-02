#pragma once
#include<iostream>
#include<vector>
#include"clsScreen.h"
#include"clsATMClient.h"
#include"Global.h"
#include"clsInputValidate.h"

class clsDeposit:protected clsScreen
{
private:

    static bool _Deposit()
    {
        vector<clsBankClient>vClient = clsBankClient::GetClientsList();

        char Answer = 'Y';

        clsUtil::SetColor(2);
        cout << "\n\nPlease enter deposit amount ? ";
        clsUtil::SetColor(3);
        double Amount = clsInputValidate::ReadDblNumber();

        clsUtil::SetColor(2);
        cout << "\n\nAre you sure you want to perform this transaction ? y/n ? ";
        clsUtil::SetColor(3);
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            for (clsBankClient& C : vClient)
            {
                if (C.AccountNumber() == CurrentClient.AccountNumber())
                {
                    C.AccountBalance += Amount;
                    CurrentClient = C;
                    break;
                }
            }

            clsBankClient::SaveClientDataToFile(vClient);
            clsUtil::SetColor(2);
            cout << "New Balance is : " << fixed << setprecision(0) << CurrentClient.AccountBalance << endl;

            return true;
        }
        else
            return false;


        return false;
    }

public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t      Deposit Screen");

        cout << setw(30) << left << "" << "Your Balance is : " << fixed << setprecision(0) << CurrentClient.AccountBalance << endl;

        _Deposit();


    }


};

