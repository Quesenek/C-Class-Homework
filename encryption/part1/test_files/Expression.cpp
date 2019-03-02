#include <iostream>

using namespace std;

int main()
{
for (int i = 1; i <= 3; i++)
{
	cout << '(';
	for (int j = 0; j < (i*2); j++)
		cout << 'x';
	cout << ')';
}
    

    return 0;
}