//Name: William Denson, Constantine Ewan, Taylor Montgomery, Cesar Ortiz Machin, John Parker, Riley Pence
//Description:  Week 8 Project: Virtual Library Management System
//Date:  06/29/2024

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& word : msg) {
        cout << word << " ";
    }
    cout << endl;
}