#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsATMClient.h"
#include"clsInputValidate.h"
#include"clsQuickWithdraw.h"
#include"clsTotalBalances.h"
#include"clsNormalWithdraw.h"
#include"clsDeposit.h"
#include"Global.h"

using namespace std;


class clsMainMenue:protected clsScreen
{
private:

    enum enATMMainMenue {
        eQuickWthdraw = 1, eNormalWthdraw = 2, eDeposit = 3,
        eCheckBalances = 4, eLogout = 5
    };


    static short _ReadATMMainMenueOption()
    {
        clsUtil::SetColor(2);
        cout << setw(30) << left << "" << "Please Enter Number From 1 To 5 : ";
        clsUtil::SetColor(3);
        short Choose=clsInputValidate::ReadShortNumberBetween(1,5,"Please Enter Number From 1 To 5 : ");
        return Choose;
    }

    static void _GoBackToATMMainMenue()
    {
        clsUtil::SetColor(6);
        cout << "\n\nPress any Key go back to ATM Main menue ...";
        system("pause>0");
        system("cls");
        ShowATMMainMenueScreen();

    }

    static void _ShowQuickWithdraw()
    {
        clsQuickWithdraw::ShowQuickWithdrawScreen();
    }

    static void _ShowNormalWithdrawScreen()
    {
        clsNormalWithdraw::ShowNormalWithdrawScreen();

    }

    static void _ShowDepositScreen()
    {
        clsDeposit::ShowDepositScreen();
    }

    static void _ShowYourBalances()
    {
        clsTotalBalances::ShowYourBalances();

    }

    static void _Logout()
    {
            CurrentClient = clsBankClient::Find("", "");
        
    }

    static void _PerformATMMainMenueOption(enATMMainMenue ATMMainMenue)
    {

        switch (ATMMainMenue)
        {

        case enATMMainMenue::eQuickWthdraw:
            system("cls");
            _ShowQuickWithdraw();
            _GoBackToATMMainMenue();
            break;

        case enATMMainMenue::eNormalWthdraw:
            system("cls");
            _ShowNormalWithdrawScreen();
            _GoBackToATMMainMenue();
            break;

        case enATMMainMenue::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToATMMainMenue();
            break;

        case enATMMainMenue::eCheckBalances:
            system("cls");
            _ShowYourBalances();
            _GoBackToATMMainMenue();
            break;

        case enATMMainMenue::eLogout:
            system("cls");
            _Logout();

        }
    }

public:

    static void ShowATMMainMenueScreen()
    {
        _DrawScreenHeader("\t   ATM Main Menue Screen");

        cout << setw(30) << left << "" << "================================================================\n\n";
        cout << setw(30) << left << "" << "\t\t\t   **** Main Menue ****\n\n";
        cout << setw(30) << left << "" << "================================================================\n\n";
        clsUtil::SetColor(1);
        cout << setw(30) << left << "" << "\t\t\t[1] Quick Withdraw.\n";
        cout << setw(30) << left << "" << "\t\t\t[2] Normal Withdraw.\n";
        cout << setw(30) << left << "" << "\t\t\t[3] Deposit.\n";
        cout << setw(30) << left << "" << "\t\t\t[4] Check Balances.\n";
        cout << setw(30) << left << "" << "\t\t\t[5] Logout.\n\n";
        clsUtil::SetColor(11);
        cout << setw(30) << left << "" << "================================================================\n\n";


        _PerformATMMainMenueOption((enATMMainMenue)_ReadATMMainMenueOption());

    }


};

