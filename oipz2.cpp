
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <limits>
#include <vector>
#include <utility>
#include "Function.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    try
    {
        string input;
        double a, b, h;
        int n;

        cout << "Enter n (n > 4): ";
        cin >> input;

        double nValue = checkValidInput(input);

        if (nValue != floor(nValue) ||
            nValue < numeric_limits<int>::min() ||
            nValue > numeric_limits<int>::max())
        {
            throw invalid_argument("n must be an integer");
        }

        n = static_cast<int>(nValue);
        CheckValidParams(n);

        cout << "Enter a: ";
        cin >> input;
        a = checkValidInput(input);

        cout << "Enter b: ";
        cin >> input;
        b = checkValidInput(input);

        cout << "Enter step h: ";
        cin >> input;
        h = checkValidInput(input);

        if (h <= 0 || a > b)
        {
            throw invalid_argument("h must be positive and a <= b");
        }

        vector<pair<double, double>> results;

        cout << fixed << setprecision(4);
        cout << "\n=== UPDATED CALCULATION RESULTS ===\n";
        cout << "X\t\tY\n";
        cout << "-------------------------\n";

        for (double x = a; x <= b + h * 1e-9; x += h)
        {
            double y = calculate(x, n);

            cout << x << "\t\t" << y << endl;

            results.push_back({ x, y });
        }

        int choice;

        do
        {
            cout << "\n=== RESULTS MENU ===";
            cout << "\n1 - Save calculation results";
            cout << "\n2 - Display saved results";
            cout << "\n0 - Close program";
            cout << "\nChoose an action: ";

            if (!(cin >> choice))
            {
                throw invalid_argument("Invalid menu choice");
            }

            if (choice == 1)
            {
                ifstream checkFile("results.txt");
                bool isEmpty = !checkFile || checkFile.peek() == EOF;
                checkFile.close();

                ofstream file("results.txt", ios::app);

                if (!file.is_open())
                {
                    throw runtime_error("Cannot open file");
                }

                file << fixed << setprecision(4);

                if (isEmpty)
                {
                    file << "x\t\ty\n";
                }

                for (const auto& item : results)
                {
                    file << item.first << "\t\t"
                        << item.second << endl;
                }

                file.close();

                cout << "Results successfully saved to results.txt" << endl;
            }
            else if (choice == 2)
            {
                ifstream file("results.txt");

                if (!file.is_open())
                {
                    cout << "File not found" << endl;
                }
                else
                {
                    string line;

                    cout << "\nSaved calculation results:\n";

                    while (getline(file, line))
                    {
                        cout << line << endl;
                    }

                    file.close();
                }
            }
            else if (choice != 0)
            {
                cout << "Invalid menu choice" << endl;
            }

        } while (choice != 0);
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
