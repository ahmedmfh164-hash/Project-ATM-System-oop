
#include <iostream>
#include"clsLogicScreen.h"

using namespace std;


int main()
{
    while(true)
    {

        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }

    system("pause>0");

}
