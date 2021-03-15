#include <iostream>
using namespace std;

double Fahrenheit, Celcius;
double i; 

void Cel()
{
    Celcius = 5 * (Fahrenheit - 32) / 9;
    cout << "Celcius " << Celcius;
}
void Table()
{
    Celcius = 5 * (i - 32) / 9;
    cout << Celcius;

}
int main()
{
    cout << "==============================================================================\n";
    cout << "Please input a temperature in Fahrenheit between the values of: -20 and 100\n";
    cout << "==============================================================================\n";
    cout << "Fahrenheit: ";
    cin >> Fahrenheit;
    
    cout << "=================================\n";
    cout << "This is your converted value\n";
    cout << "=================================\n";
   
    if (Fahrenheit > -21, Fahrenheit < 101)
    {
        Cel();
        cout << "\n";
        cout << endl << "Fahrenheit \t Celcius \n";
        for (i = -20; i < 101; i++)
        {
            cout << i << "\t \t";
            Table();
            cout << endl;
        }
    }
    else
    {
        cout << "Not a vaild number";
    }


    return 0;
}