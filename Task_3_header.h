//Muhammad_Abdullah_Abdullah_Iqbal_22i2504
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Date {
    int year;
    int month;
    int day;

    Date() : year(0), month(0), day(0) {}

    Date(int year, int month, int day) : year(year), month(month), day(day) {}
};

template <typename T>
struct EmployeeData {
    T name;
    T employeeID;
    double salary;
    Date dateOfJoining;
    T designation;

    EmployeeData(const T& name, const T& employeeID, double salary, const Date& dateOfJoining, const T& designation)
        : name(name), employeeID(employeeID), salary(salary), dateOfJoining(dateOfJoining), designation(designation) {}

    EmployeeData() = default;
};

template <typename T>
int ReadEmployeeData(const char* filename, EmployeeData<T> employees[], int maxEmployees) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    int employeeCount = 0;

    for (int i = 0; i < maxEmployees; ++i) {
        inputFile.ignore(100, ':');
        getline(inputFile, employees[i].name);

        inputFile.ignore(100, ':');
        getline(inputFile, employees[i].employeeID);

        inputFile.ignore(100, '$');
        inputFile >> employees[i].salary;

        inputFile.ignore(100, ':');
        int year, month, day;
        char dash;
        inputFile >> year >> dash >> month >> dash >> day;
        employees[i].dateOfJoining = Date(year, month, day);

        inputFile.ignore(100, ':');
        getline(inputFile, employees[i].designation);
        inputFile.ignore(2, '\n');

        employeeCount++;
    }

    inputFile.close();

    if (employeeCount > 0) {
        int LongestTenureIndex = 0;
        for (int i = 1; i < maxEmployees; i++) {
            if (employees[i].dateOfJoining.year < employees[LongestTenureIndex].dateOfJoining.year
                || (employees[i].dateOfJoining.year == employees[LongestTenureIndex].dateOfJoining.year && employees[i].dateOfJoining.month < employees[LongestTenureIndex].dateOfJoining.month)
                || (employees[i].dateOfJoining.year == employees[LongestTenureIndex].dateOfJoining.year && employees[i].dateOfJoining.month == employees[LongestTenureIndex].dateOfJoining.month && employees[i].dateOfJoining.day < employees[LongestTenureIndex].dateOfJoining.day)) {
                LongestTenureIndex = i;
            }
        }
        cout << "The Longest tenure Employee is: " << employees[LongestTenureIndex].name << endl;

        int ShortestTenureIndex = 0;
        for (int i = 1; i < maxEmployees; i++) {
            if (employees[i].dateOfJoining.year > employees[ShortestTenureIndex].dateOfJoining.year
                || (employees[i].dateOfJoining.year == employees[ShortestTenureIndex].dateOfJoining.year && employees[i].dateOfJoining.month > employees[ShortestTenureIndex].dateOfJoining.month)
                || (employees[i].dateOfJoining.year == employees[ShortestTenureIndex].dateOfJoining.year && employees[i].dateOfJoining.month == employees[ShortestTenureIndex].dateOfJoining.month && employees[i].dateOfJoining.day > employees[ShortestTenureIndex].dateOfJoining.day)) {
                ShortestTenureIndex = i;
            }
        }
        cout << "The Shortest tenure Employee is: " << employees[ShortestTenureIndex].name << endl;
        cout << "The average tenure for each designation category:\n";
        for (int i = 0; i < 50; i++) {
            cout << "-";
        }
        cout << endl;
        double TotalTenureInDaysAccordingToDesignation[10] = { 0 };
        double CountAccordingToDesignation[10] = { 0 };

        for (int i = 0; i < maxEmployees; i++) {
            for (int j = 0; j < maxEmployees; j++) {
                if (employees[i].designation == employees[j].designation) {
                    TotalTenureInDaysAccordingToDesignation[i] = TotalTenureInDaysAccordingToDesignation[i] + ((employees[j].dateOfJoining.year) * 365) + ((employees[j].dateOfJoining.month) * 30) + (employees[j].dateOfJoining.day);
                    CountAccordingToDesignation[i]++;
                }
            }
        }
        cout << "Average tenure for designation: \n";
        for (int i = 0; i < 8; i++) {
            if (CountAccordingToDesignation[i] > 0&& i !=6) {
                cout << employees[i].designation << ": " << (2023 - (TotalTenureInDaysAccordingToDesignation[i] / CountAccordingToDesignation[i] / 365.0)) << " years" << endl;
            }
        }

        for (int i = 0; i < 50; i++) {
            cout << "-";
        }
        cout << endl;

        double TotalSalary[10] = { 0 };
        int highestTotalSalaryIndex = 0;

        for (int i = 0; i < maxEmployees; i++) {
            TotalSalary[i] = employees[i].salary;
            for (int j = i + 1; j < maxEmployees; j++) {
                if (employees[i].designation == employees[j].designation) {
                    TotalSalary[i] += employees[j].salary;
                }
            }
        }

        for (int i = 0; i < maxEmployees; i++) {
            if (TotalSalary[i] > TotalSalary[highestTotalSalaryIndex]) {
                highestTotalSalaryIndex = i;
            }
        }

        cout << "The highest salary designation is: " << employees[highestTotalSalaryIndex].designation << endl;
    }
    else {
        cout << "No employee data found." << endl;
    }

    return 0;
}

