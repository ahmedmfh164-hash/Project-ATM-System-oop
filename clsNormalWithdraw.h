#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsATMClient.h"
#include"Global.h"
#include<vector>

class clsNormalWithdraw:protected clsScreen
{
private:

    static double _ReadAmount()
    {
        clsUtil::SetColor(2);
        cout << "\n\nPlease enter withdraw amount ? ";
        clsUtil::SetColor(3);
        double Amount=clsInputValidate::ReadDblNumber();

        while (Amount > CurrentClient.AccountBalance)
        {
            clsUtil::SetColor(2);
            cout << "\nAmount exceeds balance, you can withdraw up to: "
            << CurrentClient.AccountBalance;
            clsUtil::SetColor(2);
            cout << "\nPlease enter another amount ? ";
            clsUtil::SetColor(3);
            cin >> Amount;
        }

        return Amount;

    }

    static void NormalWithdraw()
    {

        vector<clsBankClient> vClient = clsBankClient::GetClientsList();

        char Answer = 'Y';

        double Amount = _ReadAmount();
        clsUtil::SetColor(2);
        cout << "\n\nAre you sure you want to perform this transaction ? y/n ? ";
        clsUtil::SetColor(3);
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            for (clsBankClient& C : vClient)
            {
                if (CurrentClient.AccountNumber()==C.AccountNumber())
                {
                    C.Withdraw(Amount);
                    CurrentClient = C;
                    break;
                }
            }

            clsBankClient::SaveClientDataToFile(vClient);
            clsUtil::SetColor(2);
            cout << "\nDone Successfully. \nNew Balance is : " << fixed << setprecision(0)
                << CurrentClient.AccountBalance << endl;
  
        }
     
    }

public:

    static void ShowNormalWithdrawScreen()
    {
        _DrawScreenHeader("\t  Normal Withdraw Screen");
        clsUtil::SetColor(2);
        cout << setw(30) << left << "" << "Your Balance is : " << fixed << setprecision(0) << CurrentClient.AccountBalance << endl;

        NormalWithdraw();

    }


};

