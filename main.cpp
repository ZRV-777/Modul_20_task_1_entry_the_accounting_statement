#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

enum
{
    JANUARY = 1, FEBRUARY, MARCH,
    APRIL, MAY, JUNE, JULY, AUGUST,
    SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};

const size_t DATE_LENGTH = 10;
const int DATE_IN_STRING_BEGIN = 0;
const int MONTH_IN_STRING_BEGIN = 3;
const int YEAR_IN_STRING_BEGIN = 6;

bool isLeapYear(int year)
{
    if (year % 4 == 0 && year % 100 != 0)
        return true;
    if (year % 100 == 0 && year % 400 == 0)
        return true;
    return false;
}

bool isValidDateFormat(string date)
{
    if (date.length() != DATE_LENGTH) return false;

    if (date[2] != '.' || date[5] != '.') return false;

    for (size_t i = 0; i < DATE_LENGTH; i++)
    {
        if (i == 2 || i == 5)
            i++;

        if (!isdigit(date[i]))
            return false;
    }

    int day = stoi(date.substr(DATE_IN_STRING_BEGIN, 2));
    int month = stoi(date.substr(MONTH_IN_STRING_BEGIN, 2));
    int year = stoi(date.substr(YEAR_IN_STRING_BEGIN, 4));

    if (day < 1) return false;

    if (month < JANUARY || month > DECEMBER) return false;

    if ((month == JANUARY || month == MARCH || month == MAY || month == JULY || month == AUGUST || month == OCTOBER
        || month == DECEMBER) && day > 31) return false;

    if ((month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) && day > 30) return false;

    if (!isLeapYear(year) && month == FEBRUARY && day > 28) return false;

    if (isLeapYear(year) && month == FEBRUARY && day > 29) return false;

    return true;
}

void inputDate (string &str)
{
    cin >> str;

    while (!isValidDateFormat(str))
    {
        cout << "Wrong date, try again: ";
        cin >> str;
    }
}

void inputSalary (double &d)
{
    while (!(cin >> d))
    {
        cin.clear();
        while (cin.get() != '\n') continue;
        cout << "Wrong salary format, try again: ";
    }
    while (cin.get() != '\n') continue;
}

int main()
{
    string name = " ";
    string date = " ";
    double salary = 0.0;
    char nextEntry = 'y';

    ofstream outFile("C:\\develop\\test\\build\\modul_20_task_1\\salary.txt", ios::app);
    if (!outFile.is_open())
    {
        cerr << "Error, file is not open";
        return 1;
    }

    outFile.setf(ios::fixed);
    outFile.precision(2);

    while (nextEntry == 'y')
    {
        cout << "Enter name: ";
        getline (cin, name);

        cout << "Enter date (dd.mm.yyyy): ";
        inputDate(date);

        cout << "Enter salary: ";
        inputSalary(salary);

        outFile << name << " " << date << " " << salary << endl;

        cout << "Continue? y/n: ";
        cin >> nextEntry;
        cin.get();
    }

    outFile.close();
}
