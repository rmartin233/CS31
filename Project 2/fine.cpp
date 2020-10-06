#include <iostream>
using namespace std;

int main()
{
    cout << "Defendant: ";
    string name;
    getline(cin, name);
    
    double pay = 0;
    cout << "Amount paid (in thousands): ";
    cin >> pay;

    cin.ignore(10000, '\n');
    
    string athlete;
    cout << "Fake athlete? (y/n): ";
    getline(cin, athlete);

    
    double fine;
    
    cout.setf(ios::fixed);
    cout.precision(1);//precision to 1 digit
    
    if (athlete == "n") //fine for
    {
        if (pay <= 40.0)
            fine = 20 + pay * 0.66;
        else if (pay > 40.0 && pay <= 250.0)
            fine = 20 + 26.4 + 0.10 * (pay - 40.0);
        else if (pay > 250.0)
            fine = 20 + 47.4 + 0.14 * (pay - 250.0);
    }
    
    else if (athlete == "y") //fine for Faked athletic credentials involved
    {
        if (pay <= 40.0)
            fine = 20 + pay * 0.66;
        else if (pay > 40.0 && pay <= 250.0)
            fine = 20 + 26.4 + 0.22 * (pay - 40.0);
        else if (pay > 250.0)
            fine = 20 + 72.6 + 0.14 * (pay -250.0);
    }
        
    cout << "---" << endl;
    
    if (name == "") // determine whether the user has typied letters.
        cout << "You must enter a defendant name." << endl;
    else if (pay < 0)
        cout << "The amount paid must not be negative." << endl;
    else if (not(athlete == "y" || athlete == "n"))
        cout << "You must enter y or n." << endl;
    else
        cout << "The suggested fine for " << name << " is $" << fine << " thousand." << endl;
    

}
