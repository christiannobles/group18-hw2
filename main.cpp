#include <iostream>

using namespace std;

//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3
int main( int argc, char * argv[] )
{
    if (argc > 4) 
    {
        cout << "Too many arguments. Cannot pass in more than three." << endl;
        return -1;
    }

    int i = 1;
    double loan_amount, yearly_interest_rate, monthly_payment;

    double arguments [3];

    if (argc > 1)
    {
        while ( i < argc )
        {
            try
            {
                arguments[i-1] = stod(argv[i]);
            }
            catch(const std::invalid_argument&)
            {
                if(i==1)
                    cout << "(Invalid loan amount): " << argv[i] << endl;
                else if (i==2)
                    cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
                else
                    cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
                return -2;
            }
            i++;
        }
    }

    if (argc != 4)
    {
        cout << "Please enter three arguments." << endl;
        return -3;
    }

    loan_amount = arguments[0];
    yearly_interest_rate = arguments[1];
    monthly_payment = arguments[2];

    yearly_interest_rate /= 12;
    double interestRateC = yearly_interest_rate / 100;
    int currentMonth = 0;
    double interestTotal = 0;
    double principle;

    cout << endl;

    cout << "******************************************************" << endl;
    cout << "\tAmortized Table"<< endl;
    cout << "******************************************************" << endl;

    cout << "Month\tBalance\tPayment\tRate\tIntrest\tPrinciple" << endl;
    cout << currentMonth << "\t$" << loan_amount << "\tN/A\tN/A\tN/A\t\tN/A\n";

    while(loan_amount > 0)
    {
        double interest = loan_amount * interestRateC;

        if (monthly_payment <= interest)
        {
            cout << "Monthly payment is too small to pay off the loan." << endl;
            return -4;
        }

        principle = monthly_payment - interest;

        currentMonth++;

        if (loan_amount + interest > monthly_payment)
        {
            loan_amount -= principle;
            interestTotal += interest;

            cout << currentMonth << "\t" << loan_amount << "\t" 
                 << monthly_payment << "\t" << yearly_interest_rate 
                 << "\t" << interest << "\t" << principle << endl;
        }
        else
        {
            monthly_payment = loan_amount + interest;
            principle = loan_amount;
            loan_amount = 0;
            interestTotal += interest;

            cout << currentMonth << "\t" << loan_amount << "\t" 
                 << monthly_payment << "\t" << yearly_interest_rate 
                 << "\t" << interest << "\t" << principle << endl;
        }
    }

    cout <<"******************************************************\n"<< endl;
    cout <<"It takes "<< currentMonth <<" month(s) to pay off the loan."<< endl;
    cout <<"Total intrest paid is: $"<< interestTotal << endl;
    cout << endl << endl;

    return 0;
}

