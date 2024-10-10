#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>  // For sorting

using namespace std;

// Base class Employee
class Employee {
protected:
    int id;
    string name;
    int age;
    double salary;
    
public:
    Employee(int _id, string _name, int _age, double _salary)
        : id(_id), name(_name), age(_age), salary(_salary) {}
    
    virtual void displayInfo() const {
        cout << "ID: " << id << ", Name: " << name
             << ", Age: " << age << ", Salary: " << salary << endl;
    }
    
    virtual double getSalary() const {
        return salary;
    }
    
    string getName() const {
        return name;
    }
    
    int getID() const {
        return id;
    }
    
    int getAge() const {
        return age;
    }

    virtual void increaseSalary(double amount) {
        salary += amount;
    }

    // Destructor
    virtual ~Employee() {}
};

// Manager class inheriting from Employee
class Manager : public Employee {
private:
    int teamSize;

public:
    Manager(int _id, string _name, int _age, double _salary, int _teamSize)
        : Employee(_id, _name, _age, _salary), teamSize(_teamSize) {}
    
    void displayInfo() const override {
        Employee::displayInfo();
        cout << "Team size: " << teamSize << endl;
    }
    
    double getSalary() const override {
        return salary + (teamSize * 1000); // Manager allowance
    }
};

// Hourly Employee class inheriting from Employee
class HourlyEmployee : public Employee {
private:
    int hoursWorked;
    double hourlyRate;

public:
    HourlyEmployee(int _id, string _name, int _age, int _hoursWorked, double _hourlyRate)
        : Employee(_id, _name, _age, _hoursWorked * _hourlyRate), hoursWorked(_hoursWorked), hourlyRate(_hourlyRate) {}
    
    double getSalary() const override {
        return hoursWorked * hourlyRate;
    }
    
    void displayInfo() const override {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Hours Worked: " << hoursWorked 
             << ", Hourly Rate: " << hourlyRate << ", Salary: " << getSalary() << endl;
    }
};

// Department class to manage employees in a department
class Department {
private:
    string departmentName;
    vector<Employee*> employees;

public:
    Department(string _name) : departmentName(_name) {}

    void addEmployee(Employee* emp) {
        employees.push_back(emp);
    }

    void displayAllEmployees() const {
        cout << "Department: " << departmentName << endl;
        for (const auto& emp : employees) {
            emp->displayInfo();
            cout << "------------------------" << endl;
        }
    }

    // Search employee by name or ID
    Employee* searchEmployeeByName(const string& empName) const {
        for (const auto& emp : employees) {
            if (emp->getName() == empName) {
                return emp;
            }
        }
        return nullptr;
    }

    Employee* searchEmployeeByID(int empID) const {
        for (const auto& emp : employees) {
            if (emp->getID() == empID) {
                return emp;
            }
        }
        return nullptr;
    }

    // Sort employees by salary
    void sortEmployeesBySalary() {
        sort(employees.begin(), employees.end(), [](Employee* a, Employee* b) {
            return a->getSalary() < b->getSalary();
        });
    }

    // Sort employees by age
    void sortEmployeesByAge() {
        sort(employees.begin(), employees.end(), [](Employee* a, Employee* b) {
            return a->getAge() < b->getAge();
        });
    }

    // Write employee list to file
    void writeToFile(const string& filePath) const {
        ofstream file(filePath);
        if (file.is_open()) {
            for (const auto& emp : employees) {
                file << emp->getID() << " " << emp->getName() << " "
                     << emp->getAge() << " " << emp->getSalary() << endl;
            }
            file.close();
        } else {
            cout << "Cannot open file to write!" << endl;
        }
    }

    // Read employee list from file
    void readFromFile(const string& filePath) {
        ifstream file(filePath);
        if (file.is_open()) {
            int id, age;
            double salary;
            string name;
            while (file >> id >> name >> age >> salary) {
                employees.push_back(new Employee(id, name, age, salary));
            }
            file.close();
        } else {
            cout << "Cannot open file to read!" << endl;
        }
    }

    ~Department() {
        for (auto emp : employees) {
            delete emp;
        }
    }
};

// Main function
int main() {
    // Create a Department
    Department keToan("Ke Toan");

    // Add employees to the department
    keToan.addEmployee(new Employee(1, "Nguyen Van A", 30, 10000000));
    keToan.addEmployee(new HourlyEmployee(2, "Tran Thi B", 25, 120, 50000));
    keToan.addEmployee(new Manager(3, "Le Van C", 40, 20000000, 3));

    // Display all employees
    keToan.displayAllEmployees();

    // Search for an employee by name
    Employee* emp = keToan.searchEmployeeByName("Tran Thi B");
    if (emp) {
        cout << "\nEmployee found:" << endl;
        emp->displayInfo();
    } else {
        cout << "Employee not found!" << endl;
    }

    // Sort employees by salary
    cout << "\nEmployees sorted by salary:" << endl;
    keToan.sortEmployeesBySalary();
    keToan.displayAllEmployees();

    // Write employees to file
    keToan.writeToFile("employees.txt");

    // Create a new department and read employees from file
    Department newDept("New Department");
    newDept.readFromFile("employees.txt");
    cout << "\nEmployees in new department read from file:" << endl;
    newDept.displayAllEmployees();

    return 0;
}
