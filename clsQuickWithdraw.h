#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsATMClient.h"
#include"clsInputValidate.h"
#include"Global.h"
#include<vector>
using namespace std;

class clsQuickWithdraw:protected clsScreen
{
private:

    enum enQuickWithdraw {
        eFirstChoice = 1, eSecondChoice = 2, eThirdChoice = 3, eForthChoice = 4,
        eFifthChoice = 5, eSixthChoice = 6, eSevenChoice = 7, eEightChoice = 8, eExit = 9
    };

    static short _ReadQuickWithdrawOption()
    {
        clsUtil::SetColor(2);
        cout << setw(30) << left << "" << "Choose what do you want to do [1 to 9] ? ";
        clsUtil::SetColor(3);
        short Choose = clsInputValidate::ReadShortNumberBetween(1, 9, "Choose what do you want to do [1 to 9] ? ");
        return Choose;
    }

    static void _WithdrawFixedAmount(int Amount)
    {
        vector<clsBankClient>vClient = clsBankClient::GetClientsList();
        
        char Answer = 'Y';

        while (Amount > CurrentClient.AccountBalance)
        {
            clsUtil::SetColor(2);
            cout << "\nAmount exceeds balance, you can withdraw up to: "
                << CurrentClient.AccountBalance;
            cout << "\nPlease enter another amount ? ";
            clsUtil::SetColor(3);
            cin >> Amount;
        }
        clsUtil::SetColor(2);
        cout << "\nAre you sure want perform this transaction ? y/n ? ";
        clsUtil::SetColor(3);
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            for (clsBankClient &C : vClient)
            {
                if (CurrentClient.AccountNumber () == C.AccountNumber())
                {
                   C.Withdraw(Amount);
                   CurrentClient = C;
                    break;
                }
            }
            clsBankClient::SaveClientDataToFile(vClient);
            clsUtil::SetColor(2);
            cout << "\nDone Successfully. \nNew Balance is : " <<
                fixed << setprecision(0) << CurrentClient.AccountBalance << endl;

        }

    }

    static void _PerformQuickWithdrawMenue(enQuickWithdraw QuickWithdraw)
    {

        switch (QuickWithdraw)
        {

        case enQuickWithdraw::eFirstChoice:

            _WithdrawFixedAmount(50);
            break;

        case enQuickWithdraw::eSecondChoice:
            _WithdrawFixedAmount(100);
            break;

        case enQuickWithdraw::eThirdChoice:
            _WithdrawFixedAmount(200);
            break;

        case enQuickWithdraw::eForthChoice:
            _WithdrawFixedAmount(400);
            break;

        case enQuickWithdraw::eFifthChoice:
            _WithdrawFixedAmount(500);
            break;

        case enQuickWithdraw::eSixthChoice:
            _WithdrawFixedAmount(600);
            break;

        case enQuickWithdraw::eSevenChoice:
            _WithdrawFixedAmount(800);
            break;

        case enQuickWithdraw::eEightChoice:
            _WithdrawFixedAmount(1000);
            break;

        case enQuickWithdraw::eExit:
            
            break;
        }


    }

public:

	static void ShowQuickWithdrawScreen()
	{
		_DrawScreenHeader("\t***Quick WithDraw Screen***");


            cout << setw(33) << left << "" << "=======================================================\n";
            cout << setw(33) << left << "" << "\t\t   Quick Withdraw \n";
            cout << setw(33) << left << "" << "=======================================================\n";
            cout << setw(36) << left << "" << "  [1] 50 \t\t\t[2] 100\n";
            cout << setw(36) << left << "" << "  [3] 200\t\t\t[4] 400\n";
            cout << setw(36) << left << "" << "  [5] 500\t\t\t[6] 600\n";
            cout << setw(36) << left << "" << "  [7] 800\t\t\t[8] 1000\n";
            cout << setw(36) << left << "" << "  [9] Exit\n";
            cout << setw(33) << left << "" << "=======================================================\n";
            cout << setw(33) << left << "" << "Your Balance is : " << fixed << setprecision(0) << CurrentClient.AccountBalance << endl;

            _PerformQuickWithdrawMenue((enQuickWithdraw)_ReadQuickWithdrawOption());
        

	}


};

