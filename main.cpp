#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Please provide three arguments: loan amount, yearly interest rate, and monthly payment." << endl;
        return -1;
    }

    if (argc > 4)
    {
        cout << "Too many arguments. Cannot pass in more than three." << endl;
        return -1;
    }

    double loan_amount;
    double yearly_interest_rate;
    double monthly_payment;

    try
    {
        loan_amount = stod(argv[1]);
        yearly_interest_rate = stod(argv[2]);
        monthly_payment = stod(argv[3]);
    }
    catch (const invalid_argument&)
    {
        cout << "Invalid input. Please enter numbers only." << endl;
        return -1;
    }

    // Validate loan amount
    if (loan_amount <= 0)
    {
        cout << "Warning: Invalid loan amount." << endl;
        return -1;
    }

    // Validate interest rate
    if (yearly_interest_rate < 0)
    {
        cout << "Warning: Invalid interest rate." << endl;
        return -1;
    }

    // Validate payment
    if (monthly_payment <= 0)
    {
        cout << "Warning: Invalid payment amount." << endl;
        return -1;
    }

    double monthly_interest_rate = yearly_interest_rate / 12.0 / 100.0;

    // Payment must be greater than the monthly interest,
    // otherwise the loan will never be paid off.
    double first_month_interest = loan_amount * monthly_interest_rate;

    if (monthly_payment <= first_month_interest && loan_amount > monthly_payment)
    {
        cout << "Warning: Insufficient payment. Loan will never be paid off." << endl;
        return -1;
    }

    double remaining_debt = loan_amount;
    double total_interest = 0.0;
    int months = 0;

    cout << fixed << setprecision(2);

    cout << "Month\tRemaining Debt\tPayment\tInterest\tPrincipal" << endl;

    cout << months << "\t$" << remaining_debt
         << "\t\tN/A\tN/A\t\tN/A" << endl;

    while (remaining_debt > 0.005)
    {
        months++;

        double interest = remaining_debt * monthly_interest_rate;

        double payment = monthly_payment;

        // Final payment may be smaller than the normal payment.
        if (remaining_debt + interest < monthly_payment)
        {
            payment = remaining_debt + interest;
        }

        double principal = payment - interest;

        remaining_debt = remaining_debt + interest - payment;

        if (remaining_debt < 0.005)
        {
            remaining_debt = 0.0;
        }

        total_interest += interest;

        cout << months << "\t$" << remaining_debt
             << "\t\t$" << payment
             << "\t$" << interest
             << "\t\t$" << principal << endl;
    }

    cout << endl;
    cout << "Number of months: " << months << endl;
    cout << "Total interest paid: $" << total_interest << endl;

    return 0;
}
