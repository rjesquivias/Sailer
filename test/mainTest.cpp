#include <iostream>
#include <assert.h>

using namespace std;

int main()
{
	int returnCode;
    int i = 5;

    if(i != 6)
    {
        cout << "main failed" << endl;
        returnCode = -1;
    }
    else
    {
    	cout << "main passed case" << endl;
    	returnCode = 0;
    }

    return returnCode;
}