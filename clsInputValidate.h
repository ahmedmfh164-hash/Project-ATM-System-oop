#pragma once
#include<iostream>
#include"clsDate.h"
#include<string>
#include"clsString.h"
#include<limits>
class clsInputValidate
{
public:

	static bool IsNumberBetween(short Number, short From, short To)
	{
		if (Number >= From && Number <= To)
			return true;

		return false;

	}

	static bool IsNumberBetween(int Number, int From, int To)
	{
			if (Number >= From && Number <= To)
				return true;

		return false;
	}

	static bool IsNumberBetween(float Number, float From,float To)
	{
		if (Number >= From && Number <= To)
			return true;

		return false;

	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
			if (Number >= From && Number <= To)
				return true;
		
		return false;

	}

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
	{
		if (clsDate::IsDate1AfterDate2(Date, DateFrom)||clsDate::IsDate1EqualDate2(Date,DateFrom) &&
			(clsDate::IsDate1BeforeDate2(Date, DateTo)||clsDate::IsDate1EqualDate2(Date,DateTo))
			)
			return true;
		else  if (clsDate::IsDate1AfterDate2(Date, DateTo)|| clsDate::IsDate1EqualDate2(Date, DateTo) &&
			(clsDate::IsDate1BeforeDate2(Date, DateFrom)|| clsDate::IsDate1EqualDate2(Date, DateFrom))
			)
			return true;
		
		return false;
	}
	
	static short ReadShortNumber(string Message = " Invalid Number, Enter Again : ")
	{
		short Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore( '\n');
			cout << Message;
		}

		return Number;
	}

	static int ReadIntNumber(string Message = " Invalid Number, Enter Again : ")
	{
		int Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore( '\n');
			cout << Message;
		}

		return Number;
	}

	static float ReadFloatNumber(string Message = " Invalid Number, Enter Again : ")
	{
		float Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore( '\n');
			cout << Message;
		}

		return Number;
	}

	static short ReadShortNumberBetween(short NumFrom, short NumTo, string Message)
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, NumFrom, NumTo))
		{
			cout << Message;
			Number = ReadShortNumber();
		}

		return Number;
	}

	static int ReadIntNumberBetween(int NumFrom, int NumTo, string Message)
	{
		int Number = ReadIntNumber();

			while (!IsNumberBetween(Number,NumFrom,NumTo))
		{
			cout << Message;
			Number = ReadIntNumber();
		}
		
			return Number;
	}

	static double ReadDblNumber(string Message="Invalid Number, Enter Again :")
	{
		double Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore( '\n');
			cout << Message;
		}

		return Number;
	}

	static string ReadString(string Message = "Invalid String, Enter Again :")
	{
		string S1;

		while (!(cin >> S1))
		{
			cin.clear();
			cin.ignore( '\n');
			cout << Message;
		}

		return S1;
	}

	static double ReadDblNumberBetween(double NumFrom, double NumTo, string Message)
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, NumFrom, NumTo))
		{
			cout << Message;
			Number = ReadDblNumber();
		}

		return Number;
	}

	static bool IsValideDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}


};

