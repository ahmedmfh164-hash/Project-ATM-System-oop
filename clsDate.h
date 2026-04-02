#pragma warning(disable:4996)
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "clsString.h"
#include<windows.h>
#include<iomanip>
#include<sstream>

class clsDate
{
private:

	short _Day = 1;
	short _Month=1;	
	short _Year=1900;

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon+1;
		_Year = now->tm_year + 1900;

	}

	clsDate(string sDate)
	{
		vector<string>vDate;
		vDate = clsString::Split(sDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day,short Month,short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DateOrderInYear, short Year)
	{
		clsDate Date1 = GetDateFromDayOrderInYear( Year, DateOrderInYear);
		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year = Date1.Year;

	}

	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay))short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth))short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear))short Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	static clsDate GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;


		return clsDate(Day, Month, Year);
	}

	 static string GetSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		stringstream S;

		S << setw(2) << setfill('0') << Day << "/" << setw(2) << setfill('0') << Month
			<< "/" << setw(2) << setfill('0') << Year
			<< "  " << setw(2) << setfill('0') << now->tm_hour << ":"
			<< setw(2) << setfill('0') << now->tm_min <<
			":" << setw(2) << setfill('0') << now->tm_sec;

		return S.str();
	}

	static bool IsValidDate( clsDate Date)
	{
		if (Date.Day < 1 || Date.Day>31)
			return false;
		
		if (Date.Month < 1 || Date.Month>12)
			return false;

		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				if (Date.Day > 29)
					return false;
			}
			else
				if (Date.Day > 28)
					return false;
		}

		short DaysIsMonth = NumberOfDaysInMonth(Date.Year,Date.Month);

		if (Date.Day > DaysIsMonth)
			return false;

		return true;

	}

	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static string DateToString(clsDate Date)
	{
		stringstream S;

		S << setw(2) << setfill('0') << Date.Day << "/" << setw(2) << setfill('0') << Date.Month
			<< "/" << setw(2) << setfill('0') << Date.Year;

		return S.str();
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDaysInMonth(short Year, short Month)
	{

		if (Month < 1 || Month>12)
			return 0;

		short arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? IsLeapYear(Year) ? 29 : 28 : arr[Month - 1];
	

	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Year, _Month);
	}

	static short NumberOfDaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(_Year);
	}

	static short NumberOfHoursInMonth(short Year, short Month)
	{
		return NumberOfDaysInMonth(Year, Month) * 24;
	}

	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(_Year,_Month);
	}

	static int NumberOfMinutesInMonth(short Year, short Month)
	{
		return NumberOfHoursInMonth(Year, Month) * 60;
	}

	int NumberOfMinutesInMonth()
	{
		return NumberOfMinutesInMonth(_Year, _Month);
	}

	static int NumberOfSecondsInMonth(short Year, short Month)
	{
		return NumberOfMinutesInMonth(Year, Month) * 60;

	}

	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(_Year, _Month);
	}

	static short NumberOfHoursInYear(short Year)
	{
		return NumberOfDaysInYear(Year) * 24;
	}

	short NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(_Year);
	}

	static int NumberOfMinutesInYear(short Year)
	{
		return NumberOfHoursInYear(Year) * 60;
	}

	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(_Year);
	}

	static int NumberOfSecondsInYear(short Year)
	{
		return NumberOfMinutesInYear(Year) * 60;

	}

	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(_Year);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a = (14 - Month) / 12;

		short y = Year - a;

		short m = Month + 12 * a - 2;

		//san=0,mon=1,..etc
		short d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

		return d;
		
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day,_Month,_Year);
	}

	static string DayShortName(short DayOrder)
	{
		string DayName[] = { "Sunday", "Monday", "Tuesday",
			"Wednesday", "Thursday", "Friday","Saturday" };

		return DayName[DayOrder];

	}

	static string DayShortName(short Day,short Month,short Year)
	{
		string DayName[] = { "Sunday", "Monday", "Tuesday",
			"Wednesday", "Thursday", "Friday","Saturday" };

		return DayName[DayOfWeekOrder(Day,Month,Year)];
	}

	string DayShortName()
	{
		return DayShortName(_Day, _Month, _Year);
	}

	static void PrintDayName(short DayOfWeekOrder)
	{
		string DayName[] = { "Sunday", "Monday", "Tuesday","Wednesday", "Thursday", "Friday", "Saturday" };

		cout<<DayName[DayOfWeekOrder];
	}

	void PrintDayName()
	{
		return PrintDayName(DayOfWeekOrder());
	}

	static string MonthShortName(short Month)
	{
		string MonthName[12] = { "January" ,"February", "March", "April","May",
			"June","July", "August","September","October","November","December" };

		return MonthName[Month - 1];

	}

	string PrintMonthName()
	{
		return MonthShortName(_Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays;
		string DayName[7] = { "Sunday", "Monday", "Tuesday","Wednesday", "Thursday", "Friday", "Saturday" };

		//Index of the day from 0to 6
		int current = DayOfWeekOrder(1, Month, Year);

		NumberOfDays = NumberOfDaysInMonth(Year, Month);

		//Print the current month name
		printf("\n__________________%s__________________\n", MonthShortName(Month).c_str());

		//Print the columns
		cout << "  ";
		for (int i = 0;i < 7;i++)
			printf(" %s ", DayName[i].c_str());

		printf("\n_______________________________________\n");

		//Print appropriate spaces
		int i;
		for (i = 0;i < current;i++)
			printf("     ");

		for (int a = 1;a <= NumberOfDays;a++)
		{
			printf("%5d", a);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}

		}				  
		printf("\n_______________________________________\n");

	}

	void PrintMonthCalendar()
	{
		return PrintMonthCalendar(_Month,_Year);
	}

	static void PrintYearCalendar(short Month, short Year)
	{

		printf("\n-------------------------\n\n");
		printf("\n       Calendar - %d\n", Year);
		printf("\n-------------------------\n\n");

		for (short a = 1;a <= 12;a++)
		{
			PrintMonthCalendar( a, Year);

		}


	}

	void PrintYearCalendar()
	{

		printf("\n-------------------------\n\n");
		printf("\n       Calendar - %d\n", _Year);
		printf("\n-------------------------\n\n");

		for (short a = 1;a <= 12;a++)
		{
			PrintMonthCalendar(a, Year);

		}
	}

	static short NumberOfDaysFromBeginingOfYear(short Year, short Month, short Day)
	{
		short TotalDays = 0;

		for (int a = 1;a <= Month - 1;a++)
		{
			TotalDays += NumberOfDaysInMonth(Year, a);

		}
		TotalDays += Day;

		return TotalDays;
	}

	short NumberOfDaysFromBeginingOfYear()
	{
		return NumberOfDaysFromBeginingOfYear(_Year,_Month,_Day);
	}

	static clsDate GetDateFromDayOrderInYear(short Year, short DateOrderInYear)
	{
		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Year, Date.Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}

		}

		return Date;

	}

	void AddDays( short Days)
	{

		short RemainingDays = Days + NumberOfDaysFromBeginingOfYear(_Year,_Month,_Day);
		short MonthDays = 0;

		_Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(_Year, _Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				_Month++;
				if (_Month > 12)
				{
					_Month = 1;
					_Year++;
				}
			}
			else
			{
				_Day = RemainingDays;
				break;
			}

		}

	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);

	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{

		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ?
			(Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ?
				Date1.Day < Date2.Day : false)) : false);

	}

	bool IsDate1BeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this,Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return ((Date1.Year == Date2.Year) ? (Date1.Month == Date2.Month) ? Date1.Day == Date2.Day : false : false);
	}

	bool IsDate1EqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{

		return (!IsDate1BeforeDate2(Date1,Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsWeekEnd(clsDate& Date)
	{
		short DayIndex = DayOfWeekOrder(Date.Day,Date.Month,Date.Year);
		return  (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate &Date)
	{
		return  !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static clsDate AddOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year ++;
			}
			else
			{
				Date.Day = 1;
				Date.Month ++;
			}
		}
		else
			Date.Day++;

		return Date;

	}

	static void SwapDate(clsDate& Date1, clsDate& Date2)
	{
		clsDate TemDate;

		TemDate.Year = Date1.Year;
		TemDate.Month = Date1.Month;
		TemDate.Day = Date1.Day;

		Date1.Year = Date2.Year;
		Date1.Month = Date2.Month;
		Date1.Day = Date2.Day;

		Date2.Year = TemDate.Year;
		Date2.Month = TemDate.Month;
		Date2.Day = TemDate.Day;

	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		int SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDate(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);

		}

		return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;

	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static clsDate IncreaseDateByOneDay(clsDate &Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else

			Date.Day++;

		return Date;
	}

	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate &Date, short Days)
	{
		for (int a = 1;a <= Days;a++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate &Date)
	{
		for (int a = 1;a <= 7;a++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}

	void  IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate Date, short Weeks)
	{
		for (int a = 1;a <= Weeks;a++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate &Date)
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		if (Date.Day > NumberOfDaysInMonth(Date.Year, Date.Month))
		{
			Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
		}

		return Date;

	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate &Date, short Months)
	{
		for (int a = 1;a <= Months;a++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;

	}

	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(*this, Months);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate &Date, short Years)
	{
		for (int a = 1;a <= Years;a++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;

	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(*this, Years);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate &Date, short Years)
	{
		Date.Year += Years;
		return Date;
	}

	void  IncreaseDateByXYearsFaster(short Years)
	{
		IncreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate &Date)
	{
		Date.Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate &Date, short Decades)
	{
		for (int a = 1;a <= Decades;a++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}
		return Date;

	}

	void IncreaseDateByXDecades(short Decades)
	{
		IncreaseDateByXDecades(*this, Decades);
	}

	static clsDate IncreaseDateByXDecadesFaster(short Decade, clsDate &Date)
	{
		Date.Year += Decade * 10;
		return Date;
	}

	void IncreaseDateByXDecadesFaster(short Decade)
	{
		IncreaseDateByXDecadesFaster(Decade, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate &Date)
	{
		Date.Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate &Date)
	{
		Date.Year += 1000;
		return Date;
	}

	clsDate IncreaseDateByOneMillennium()
	{
		return IncreaseDateByOneMillennium(*this);
	}

	static bool IsFirstDayInMonth(clsDate Date)
	{
		return (Date.Day == 1);
	}

	bool IsFirstDayInMonth()
	{
		return IsFirstDayInMonth(*this);
	}

	static bool IsFirstMonthInYear(short Month)
	{
		return (Month == 1);

	}

	bool IsFirstMonthInYear()
	{
		return IsFirstMonthInYear(_Month);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (IsFirstDayInMonth(Date))
		{
			if (IsFirstMonthInYear(Date.Month))
			{
				Date.Day = 31;
				Date.Month = 12;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
			}
		}
		else

			Date.Day--;

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short Days)
	{
		for (int a = 1;a <= Days;a++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (int a = 1;a <= 7;a++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void  DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, short Weeks)
	{
		for (int a = 1;a <= Weeks;a++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{

		if (IsFirstMonthInYear(Date.Month))
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
		}

		if (Date.Day > NumberOfDaysInMonth(Date.Year, Date.Month))
		{
			Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
		}

		return Date;

	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, short Months)
	{
		for (int a = 1;a <= Months;a++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;

	}

	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short Years)
	{
		for (int a = 1;a <= Years;a++)
		{
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;

	}

	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate& Date, short Years)
	{
		Date.Year -= Years;
		return Date;
	}

	void  DecreaseDateByXYearsFaster(short Years)
	{
		DecreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, short Decades)
	{
		for (int a = 1;a <= Decades;a++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}
		return Date;

	}

	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(*this, Decades);
	}

	static clsDate DecreaseDateByXDecadesFaster(short Decade, clsDate& Date)
	{
		Date.Year -= Decade * 10;
		return Date;
	}

	void DecreaseDateByXDecadesFaster(short Decade)
	{
		DecreaseDateByXDecadesFaster(Decade, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year -= 1000;
		return Date;
	}

	clsDate DecreaseDateByOneMillennium()
	{
		return DecreaseDateByOneMillennium(*this);
	}

	clsDate StringToDate(string DateString)
	{
		clsDate Date;
		vector<string>vDate;

		vDate = clsString::Split(DateString, "/");
		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);

		return Date;
	}

	string ReplaceWordInString(string S1, string StringToReplace, string sReplaceTo)
	{
		size_t pos = S1.find(StringToReplace);

		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(), sReplaceTo);
			pos = S1.find(StringToReplace);//find next
		}
		return S1;
	}

	string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = "";
		FormattedDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
		FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date.Year));

		return FormattedDateString;
	}

	static bool ValidateDate(clsDate Date)
	{
		if (Date.Month < 1 || Date.Month > 12)
			return false;

		if (Date.Day < 1 || Date.Day > NumberOfDaysInMonth(Date.Year, Date.Month))
			return false;

		return true;
	}

bool ValidateDate()
{
	return ValidateDate(*this);
}

static int CalculateMyAgeInDays(clsDate DateOfBirth)
{
	return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
}

static short DaysUntilTheEndOfWeek(clsDate Date)
{
	return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
}

short DaysUntilTheEndOfWeek()
{
	return DaysUntilTheEndOfWeek(*this);
}

static short DaysUntilTheEndOfMonth(clsDate Date)
{
	clsDate EndOfMonthDate;
	EndOfMonthDate.Day = NumberOfDaysInMonth(Date.Year,Date.Month);
	EndOfMonthDate.Month = Date.Month;
	EndOfMonthDate.Year = Date.Year;

	return GetDifferenceInDays(Date, EndOfMonthDate, true);
}

short DaysUntilTheEndOfMonth()
{
	return DaysUntilTheEndOfMonth(*this);
}

static short DaysUntilTheEndOfYear(clsDate Date)
{
	clsDate EndOfYearDate;
	EndOfYearDate.Day = 31;
	EndOfYearDate.Month = 12;
	EndOfYearDate.Year = Date.Year;

	return GetDifferenceInDays(Date, EndOfYearDate, true);
}

short DaysUntilTheEndOfYear()
{
	return DaysUntilTheEndOfYear(*this);
}

static short CalculateBusinessDays(clsDate DateFrom,clsDate DateTo)
{
	short Days = 0;
	while (IsDate1BeforeDate2(DateFrom, DateTo))
	{
		if (IsBusinessDay(DateFrom))
			Days++;

		DateFrom = AddOneDay(DateFrom);
	}

	return Days;
}

static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
{
	return CalculateBusinessDays(DateFrom, DateTo);
}

static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
{

	short WeekEndCounter = 0;

	while (IsWeekEnd(DateFrom))
	{
		DateFrom = IncreaseDateByOneDay(DateFrom);
	}

	for (int a = 1;a <= VacationDays + WeekEndCounter;a++)
	{
		if (IsWeekEnd(DateFrom))
		{
			WeekEndCounter++;
		}
		DateFrom = IncreaseDateByOneDay(DateFrom);
	}

	while (IsWeekEnd(DateFrom))
	{
		DateFrom = IncreaseDateByOneDay(DateFrom);
	}

	return DateFrom;

}

enum enDateCompare { Defore = -1, Equal = 0, After = 1 };

static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
{

	if (IsDate1BeforeDate2(Date1, Date2))
		return enDateCompare::Defore;

	if (IsDate1EqualDate2(Date1, Date2))
		return enDateCompare::Equal;


	return enDateCompare::After;

}

enDateCompare CompareDates(clsDate Date2)
{
	return CompareDates(*this, Date2);
}


};

