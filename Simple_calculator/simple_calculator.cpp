#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
void displayMenu();
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);

int main() {
    int choice;
    double num1, num2, result;

    do {
        displayMenu();
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        if (choice == 5) {
            cout << "\nThank you for using the Simple Calculator. Goodbye!" << endl;
            break;
        }

        if (choice < 1 || choice > 5) {
            cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
            continue;
        }

        cout << "\nEnter two numbers: ";
        cin >> num1 >> num2;

        cout << fixed << setprecision(2); // Setting precision for floating-point numbers

        switch (choice) {
            case 1:
                result = add(num1, num2);
                cout << "\nResult: " << num1 << " + " << num2 << " = " << result << endl;
                break;
            case 2:
                result = subtract(num1, num2);
                cout << "\nResult: " << num1 << " - " << num2 << " = " << result << endl;
                break;
            case 3:
                result = multiply(num1, num2);
                cout << "\nResult: " << num1 << " * " << num2 << " = " << result << endl;
                break;
            case 4:
                if (num2 != 0) {
                    result = divide(num1, num2);
                    cout << "\nResult: " << num1 << " / " << num2 << " = " << result << endl;
                } else {
                    cout << "\nError: Division by zero is not allowed." << endl;
                }
                break;
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    cout << "\n====================================" << endl;
    cout << "          Simple Calculator         " << endl;
    cout << "====================================" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Multiplication" << endl;
    cout << "4. Division" << endl;
    cout << "5. Exit" << endl;
    cout << "====================================" << endl;
}

double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}
