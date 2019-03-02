#include <iostream>
#include <ctime>
#include <cstdlib>

#include <Windows.h>

using namespace std;

int main()
{
    int counter = 0;

    bool b1,b2,b3,b4,b5,b6 = false;
    
    while (!b6)
    {
        srand(static_cast<int>(time(0)));
        counter = (1 + rand() % 5);
        cout << counter << endl;

        switch (counter)
        {
            case 1:
                b1 = true;
                break;
            case 2:
                b2 = true;
                break;
            case 3:
                b3 = true;
                break;
            case 4:
                b4 = true;
                break;
            case 5:
                b5 = true;
                break;
        }
        if (b1 == true && b2 == true && b3 == true && b4 == true && b5 == true)
        {
            b6 = true;
        }

        Sleep(1000);
    }




    return 0;
}