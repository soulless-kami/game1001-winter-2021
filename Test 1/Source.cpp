#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int WeeklyPay = 200; 
	double item1 = 0;
	double item2 = 0;
	double item3 = 0;
	double item4 = 0; 
	double item5 = 0; 


	cout << "This is a program that will calculate your total earnings weekly\n\n" << endl; 
	
	
	cout << "This is the item list below\n" << endl; 
	cout << "===============================\n" << endl; 
	
	//Item List 
	cout << "Item 1 is listed at (299.99)\n " << endl;
	cout << "Item 2 is listed at (89.75)\n " << endl;
	cout << "Item 3 is listed at (189.95)\n " << endl;
	cout << "Item 4 is listed at (150.89)\n " << endl;
	cout << "Item 5 is listed at (429.45)\n " << endl;

	cout << "================================\n\n";
	cout << "Please enter the number of sold units of item 1 " << endl;
	cin >> item1;

	cout << "Please enter the number of sold units of item 2 " << endl;
	cin >> item2;

	cout << "Please enter the number of sold units of item 3 " << endl;
	cin >> item3;

	cout << "Please enter the number of sold units of item 4 " << endl;
	cin >> item4;

	cout << "Please enter the number of sold units of item 5 " << endl;
	cin >> item5;
	cout << "\n\n"; 

	double item1Total = item1 * 299.99;
	double item2Total = item2 * 89.75;
	double item3Total = item3 * 189.95;
	double item4Total = item4 * 150.89;
	double item5Total = item5 * 429.45;

	double TotalSales = item1Total + item2Total + item3Total + item4Total + item5Total; 

	double Commission = TotalSales * 0.09;

	double FinalPay = WeeklyPay + Commission;

	cout << "This is your total comissions for this week " << Commission << " Dollars ";
	cout << "\nThis is your total pay for this week " << FinalPay << " Dollars\n\n ";







	
	return 0;
}