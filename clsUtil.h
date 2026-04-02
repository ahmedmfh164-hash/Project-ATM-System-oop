#pragma once
#include <iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>
#include"clsString.h"
#include"clsDate.h"
#include<windows.h>
using namespace std;

class clsUtil
{

public:

    enum enCharType {

        SmallLetter = 1,
        CapitalLetter = 2,
        SpecialCharacter = 3,
        Digit = 4,
        MixChars=5
    };

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumbers(int From, int To)
    {
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static void FillArrayWithRandomNumbers(int arr[],  short arrLength)
    {
        for (int a = 0;a < arrLength;a++)
        {
                arr[a] = RandomNumbers(1, 100);
        }
    }

    static void FillArrayWithRandomWords(string arr[], enCharType CharType, short arrLength)
    {
        for (int a = 0;a < arrLength;a++)
        {
            arr[a] = GenerateWord(CharType,arrLength);
        }
    }

    static void FillArrayWithRandomKeys(string arr[], short arrLength, enCharType CharType,short Length)
    {
        for (int a = 0;a < arrLength;a++)
        {
            arr[a] = GenerateKey(Length,CharType);
        }
    }

    static char GetRandomCharacter(enCharType CharType)
    {
        //updated this method to accept mixchars
        if (CharType == enCharType::MixChars)
        {
            //Capital/small/Digit only
            CharType = (enCharType)RandomNumbers(1, 3);
        }

        switch (CharType)
        {
        case enCharType::SmallLetter:
        {
            return char(RandomNumbers(97, 122));
            break;
        }
        case enCharType::CapitalLetter:
        {
            return char(RandomNumbers(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumbers(33, 47));
            break;                 
        }
        case enCharType::Digit:
        {
            return char(RandomNumbers(48, 57));
            break;
        }
        default:
            return char(RandomNumbers(65, 90));
            break;
        }

    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word;

        for (int a = 1;a <= Length;a++)
        {
            Word = Word + GetRandomCharacter(CharType);
        }
        return Word;
    }

    static string GenerateKey(short Length,enCharType CharType)
    {
        string Key = "";

        Key = GenerateWord(CharType, Length) + "-";
        Key = Key + GenerateWord(CharType, Length) + "-";
        Key = Key + GenerateWord(CharType, Length) + "-";
        Key = Key + GenerateWord(CharType, Length);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {
        for (int i = 1;i <= NumberOfKeys;i++)
        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(4,CharType) << endl;
        }

    }

    static string NumberToText(int Number)
    {
        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "","One","Two","Three","Four","Five","Six","Seven","Eight"
                ,"Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen"
                ,"Seventeen","Eighteen","Nineteen" };

            return arr[Number] + " ";

        }

        else if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","","Tewnty","Thirty","Fourty","Fifty","Sexty","Seventy","Eighty","Ninety" };

            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        else if (Number >= 100 && Number <= 199)
        {
            return "One Hundred " + NumberToText(Number % 100);
        }

        else if (Number >= 200 && Number <= 999)
        {
            return NumberToText(Number / 100) + "Hundred " + NumberToText(Number % 100);
        }

        else if (Number >= 1000 && Number <= 1999)
        {
            return "One Thousand " + NumberToText(Number % 1000);
        }

        else if (Number >= 2000 && Number <= 999999)
        {
            return NumberToText(Number / 1000) + "Thousand " + NumberToText(Number % 1000);
        }

        else if (Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }

        else if (Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Million " + NumberToText(Number % 1000000);
        }

        else if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + NumberToText(Number % 1000000000);
        }
        else

            return NumberToText(Number / 1000000000) + "Billion " + NumberToText(Number % 1000000000);

    }

    static void PrintStringArray(string arr[100], int arrLength)
    {
        cout << "\nArray elements:\n\n";
        for (int a = 0;a < arrLength;a++)
        {
            cout << "Array[" << a << "] : ";
            cout << arr[a] << "\n";
        }
        cout << "\n";

    }

    static void Swap(int& A, int& B)
    {
        int Temp;
        Temp = A;
        A = B;
        B=Temp;
    }

    static void Swap(double& A, double& B)
    {
        double Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(bool& A, bool& B)
    {
        bool Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(char& A, char& B)
    {
        char Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(string& A, string& B)
    {
        string Temp;
        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(clsDate& A, clsDate& B)
    {
        clsDate::SwapDate(A, B);
    }

    static void ShuffleArray(int arr[100], int arrLength)
    {

        for (int a = 0;a < arrLength;a++)
        {
            Swap(arr[RandomNumbers(1, arrLength) - 1], arr[RandomNumbers(1, arrLength) - 1]);
        }

    }

    static void ShuffleArray(string arr[100], int arrLength)
    {

        for (int a = 0;a < arrLength;a++)
        {
            Swap(arr[RandomNumbers(1, arrLength) - 1], arr[RandomNumbers(1, arrLength) - 1]);
        }

    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1;i < NumberOfTabs;i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    static string EncryptText(string Text, short EncryptionKey)
    {
        for (int a = 0;a < Text.length();a++)
        {
            Text[a] = char((int)Text[a] + EncryptionKey);
        }
        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey)
    {
        for (int a = 0;a < Text.length();a++)
        {
            Text[a] = char((int)Text[a] - EncryptionKey);
        }
        return Text;
    }

    static void SetColor(int Color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
    }

};
