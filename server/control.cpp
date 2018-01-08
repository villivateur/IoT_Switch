#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	char val='0';

	while (1)
	{
		cin >> val;
		cout << val << endl;

		ofstream ctrl;
		ctrl.open("ctrl.in");
		ctrl << val;
		ctrl.close();
	}

	return 0;
}
