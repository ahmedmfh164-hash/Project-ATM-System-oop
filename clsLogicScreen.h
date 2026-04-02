#pragma once
#include"clsScreen.h"
#include"clsATMClient.h"
#include<iostream>
#include"clsMainMenue.h"
#include"Global.h"

class clsLoginScreen :protected clsScreen
{
private:

    static bool _Login()
    {
        bool LoginFailed = false;
        short TrialsFailed = 3;

        string AccountNumber, Password;
        do
        {
            clsUtil::SetColor(2);
            if (LoginFailed)
            {
                TrialsFailed--;
                cout << "\nInvalid Account Number/Password!\n";
                cout << "You Have " << TrialsFailed << " Trials To Logic .\n";
                if (TrialsFailed == 0)
                {
                    cout << "\nYour are Locked after 3 failed trails.\n";
                    return false;
                }
            }
            cout << "\nEnter Account Number ? ";
            clsUtil::SetColor(3);
            cin >> AccountNumber;
            clsUtil::SetColor(2);
            cout << "\nEnter Password ? ";
            clsUtil::SetColor(3);
            cin >> Password;

            CurrentClient = clsBankClient::Find(AccountNumber, Password);

            LoginFailed = CurrentClient.IsEmpty();
        } while (LoginFailed);

        system("cls");
        clsMainMenue::ShowATMMainMenueScreen();
        return true;
    }

public:

    static bool ShowLoginScreen()
    {

        system("cls");
        _DrawScreenHeader("\t\tLogic Screen");
        return _Login();

    }




};

