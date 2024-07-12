#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Account {
private:
    string AccountNo;
    string Password;
    int Balance;

public:
    Account() : AccountNo(""), Password(""), Balance(0) {}
    void setAccountNo(string id) {
        AccountNo = id;
    }
    void setPassword(string pw) {
        Password = pw;
    }
    void setBalance(int balance) {
        Balance = balance;
    }
    string getAccountNo(){
        return AccountNo;
    }
    string getPassword(){
        return Password;
    }
    int getBalance(){
        return Balance;
    }
};

void openAccount(Account &user){
    system("cls");
    string id, pw;
    cout << "\t Enter Account No: ";
    cin >> id;
    user.setAccountNo(id);
    cout << "\t Enter Password: ";
    cin >> pw;
    user.setPassword(pw);

    user.setBalance(0);

    ofstream outfile("C:\\Users\\VANSHIKA\\project_c++\\Banking_system\\Account.txt", ios::app);
    if(!outfile){
        perror("\t Error in opening file");
        cout << endl;
    } else {
        outfile << user.getAccountNo() << ":" << user.getPassword() << ":" << user.getBalance() << endl;
        cout << "\tAccount Created Successfully! " << endl;
    } 
    outfile.close();

    Sleep(5000);
}

void addCash(Account &user){
    system("cls");
    string id;
    cout << "\tEnter Account No: ";
    cin >> id;

    ifstream infile("C:\\Users\\VANSHIKA\\project_c++\\Banking_system\\Account.txt");
    ofstream outfile("C:\\Users\\VANSHIKA\\project_c++\\Banking_system\\Account_temp.txt");
    if(!infile || !outfile){
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;

    while(getline(infile, line)){
        stringstream ss(line);
        string userID, userPW;
        int userBalance;
        char delimiter;

        getline(ss, userID, ':');
        getline(ss, userPW, ':');
        ss >> userBalance;

        if(id == userID){
            found = true;
            int cash;
            cout << "\tEnter Cash: ";
            cin >> cash;

            int newBalance = userBalance + cash;
            user.setBalance(newBalance);
            outfile << userID << ":" << userPW << ":" << newBalance << endl;
            cout << "\tNew Balance Is: " << newBalance << endl;
        } else {
            outfile << line << endl;
        }
    }
    if(!found){
        cout << "\tAccount not found!" << endl;
    }
    outfile.close();
    infile.close();
    remove("C:\\Users\\VANSHIKA\\project_c++\\Banking_system\\Account.txt");
    rename("C:\\Users\\VANSHIKA\\project_c++\\Banking_system\\Account_temp.txt", "C:\\Users\\VANSHIKA\\project_c++\\Banking_system\\Account.txt");
    Sleep(5000);
}

void withdrawCash(Account &user){
    system("cls");
    string id, pw;
    cout << "\tEnter Account No: ";
    cin >> id;
    cout << "\tEnter Password: ";
    cin >> pw;

    ifstream infile("C:\\Users\\VANSHIKA\\project_c++\\Banking_system\\Account.txt");
    ofstream outfile("C:\\Users\\VANSHIKA\\project_c++\\Banking_system\\Account_temp.txt");
    if(!infile || !outfile){
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while(getline(infile, line)){
        stringstream ss(line);
        string userID, userPW;
        int userBalance;
        char delimiter;
        getline(ss, userID, ':');
        getline(ss, userPW, ':');
        ss >> userBalance;

        if(id == userID && pw == userPW){
            found = true;
            int cash;
            cout << "\tEnter Cash: ";
            cin >> cash;

            if(cash <= userBalance){
                int newBalance = userBalance - cash;
                user.setBalance(newBalance);
                outfile << userID << ":" << userPW << ":" << newBalance << endl;
                cout << "\tTransaction Successful! " << endl;
                cout << "\tRemaining Balance: " << newBalance << endl;
            } else {
                cout << "\tInsufficient Balance!" << endl;
                outfile << userID << ":" << userPW << ":" << userBalance << endl;
            }
        } else {
            outfile << line << endl;
        }
    }
    if(!found){
        cout << "\tInvalid Account or Password!" << endl;
    }
    outfile.close();
    infile.close();
    remove("C:\\Users\\VANSHIKA\\project_c++\\Account.txt");
    rename("C:\\Users\\VANSHIKA\\project_c++\\Account_temp.txt", "C:\\Users\\VANSHIKA\\project_c++\\Account.txt");
    Sleep(5000);
}

int main(){
    Account user;
    bool exit = false;
    while(!exit){
        system("cls");
        int val;
        cout << "\t Welcome to Bank Account Management System" << endl;
        cout << "\t*******************************************" << endl;
        cout << "\t 1. Create New Account" << endl;
        cout << "\t 2. Add Cash" << endl;
        cout << "\t 3. Withdraw Cash" << endl;
        cout << "\t 4. Exit" << endl;
        cout << "\t Enter Your Choice: ";
        cin >> val;

        if(val == 1){
            openAccount(user);
        } else if (val == 2){
            addCash(user);
        } else if (val == 3){
            withdrawCash(user);
        } else if (val == 4){
            system("cls");
            exit = true;
            cout << "\tCome back soon!" << endl;
            Sleep(2000);
        }
        Sleep(3000);
    }
    return 0;
}
