#include <iostream>
#include <fstream>
#include <string>
#include"Task_3_header.h"
using namespace std;

int main() {
    const char* filename = "Employeedata.txt"; 
    const int maxEmployees = 10; 

    EmployeeData<string> employees[maxEmployees];
    int result = ReadEmployeeData(filename, employees, maxEmployees);

    return result;
}
