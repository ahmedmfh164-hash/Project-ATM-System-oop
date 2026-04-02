#pragma once
#include<iostream>
#include<iomanip>
#include"clsDate.h"
#include"Global.h"
#include"clsUtil.h"

using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		clsUtil::SetColor(3);
		cout << setw(29) << left << "" << "==================================================================\n";
		cout << "\n\t\t\t\t\t       " << Title;
		if (SubTitle != "")
		{
			cout << "\n\t\t\t\t\t  " << SubTitle;
		}
		cout << "\n" << setw(29) << left << "" << "==================================================================\n\n";

		clsDate Date;
		clsUtil::SetColor(11);
		cout << setw(31) << left << "" << "Account Name  : " << CurrentClient.FullName() << "\n";
		cout << setw(31) << left << "" << "Date Today : " << Date.DayShortName(Date.Day, Date.Month, Date.Year)
			<< ", " << Date.MonthShortName(Date.Month) << ", "
			<< Date.DateToString(Date.GetSystemDate()) << "\n\n";


	}

	


};

