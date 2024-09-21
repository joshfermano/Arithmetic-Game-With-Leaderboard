/*
    Josh Khovick T. Fermano
    2022
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <thread>
#include <chrono>
using namespace std;

class PlayerUser {
    public:
        string username;
        string password;
        int add;
        int sub;
        int mul;
        int div;
        float ave;

    PlayerUser(const string& username, const string& password)
        : username(username), password(password), add(0), sub(0), mul(0), div(0), ave(0.0) {}

    PlayerUser() {}
};

// Node class for linked list
class Node {
public:
    PlayerUser user;
    Node* next;

    Node(const PlayerUser& user) : user(user), next(nullptr) {}
};

// PlayerList class
class PlayerList {
private:
    Node* head;
    int size;

public:
    PlayerList() : head(nullptr), size(0) {}

    Node* getHead() const {
        return head;
}

    ~PlayerList() {
        clear();
}

void addUser(const PlayerUser& user) {
        Node* newNode = new Node(user);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
}

PlayerUser* getUser(const string& username) {
        Node* current = head;
        while (current != nullptr) {
            if (current->user.username == username) {
                return &(current->user);
        }
        current = current->next;
    }
    return nullptr;
}

    int getSize() const {
        return size;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;
    }
};

// Global variables
PlayerList PlList;
PlayerUser* currentUser = nullptr;

// Function declarations
class Gamefunction {
public:
    //Register/Save functions
    void Register();
    void LogIn();
    void setCurrentUser(const string& username);
    void SaveUser();
    void Retrieve();
    //Animation functions
    void loading();
    void loadingbar(int total, int progress);
    //Display functions
    void display();
    void displayLog(const string& currentUser);
    void displayAdd();
    void displaySub();
    void displayMul();
    void displayDiv();
    void displayOperation();
    //Leaderboard functions
    void boardAve();
    void boardAdd();
    void boardMul();
    void boardSub();
    void boardDiv();
    //Arithmetic Functions
    int addition(int n);
    int multiplication(int n);
    int subtraction(int n);
    int division(int n);
    //Game utilities
    void practiceGame();
    int menu();
    float avg(int a, int b, int c, int d);
};

//Animation
void sleep();
void delay(int number_of_seconds);

// File handling
void Gamefunction::SaveUser() {
    Node* current = PlList.getHead();
    ofstream file("Playerdata.txt");
    if (file.is_open()) {
        while (current != nullptr) {
            file << current->user.username << " " << current->user.password << " "
                 << current->user.add << " " << current->user.sub << " " << current->user.mul << " "
                 << current->user.div << " " << current->user.ave << "\n";
            current = current->next;
        }
        file.close();
    } else {
        cout << "There is an Error Opening File.\n";
    }
}

void Gamefunction::Retrieve() {
    ifstream file("Playerdata.txt");
    if (file.is_open()) {
        string username, password;
        int add, sub, mul, div;
        float ave;
        while (file >> username >> password >> add >> sub >> mul >> div >> ave) {
            PlayerUser user(username, password);
            user.add = add;
            user.sub = sub;
            user.mul = mul;
            user.div = div;
            user.ave = ave;
            PlList.addUser(user);
        }
        file.close();
    } else {
        cout << "There is an Error Opening File.\n";
        system("pause");
    }
}

// Other functions
void Gamefunction::setCurrentUser(const string& username) {
    currentUser = PlList.getUser(username);
}

void sleep() {
     for (int i = 0; i <= 11; i++) {
        system("cls");
        switch ((i % 4) + 1) {
            case 1:
                cout << "\n\n\n\n\n\n\t\t\t\t\tWelcome to the Game\n"
                        "\t\t\t\t\t\tLoading";
                break;
            case 2:
                cout << "\n\n\n\n\n\n\t\t\t\t\tWelcome to the Game\n"
                        "\t\t\t\t\t\tLoading.";
                break;
            case 3:
                cout << "\n\n\n\n\n\n\t\t\t\t\tWelcome to the Game\n"
                        "\t\t\t\t\t\tLoading..";
                break;
            case 4:
                cout << "\n\n\n\n\n\n\t\t\t\t\tWelcome to the Game\n"
                        "\t\t\t\t\t\tLoading...";
                break;
        }
        Sleep(100);
    }
}


void Gamefunction::loading() {
    char a = 177, b = 219;
    cout << "\n\n\n\n";
    cout << "\n\n\n\n\t\t\t\t\t""Loading...\n\n";
    cout << "\t\t\t\t\t";
    for (int i = 0; i < 26; i++)
        cout << a;
    cout << '\r';
    cout << "\t\t\t\t\t";
    for (int i = 0; i < 26; i++) {
        cout << b;
        Sleep(100);
    }
}


void Gamefunction::loadingbar(int total, int progress) {
        int barWidth = 40;
        int percent = (progress * 100) / total;
        int numBars = (progress * barWidth) / total;
        cout << "[";
        for (int i = 0; i < barWidth; i++) {
        if (i < numBars) {
            cout << "=";
        } else {
            cout << " ";
        }
    }
    cout << "] " << percent << "%\r";
    cout.flush();
}
void Gamefunction::display() {
    loading();
    system("cls");
    int items = 10;
     cout << "\t\t\t===================================================================\t\t\t" << '\n';
    cout << "\t\t\t                     L E A D E R  B O A R D                        \t\t\t" << '\n';
    cout << "\t\t\t===================================================================\t\t\t" << '\n';
    cout << left << setw(5) << "Rank" << setw(30) << "Name" << setw(15)  << "Addition" << setw(15) << "Subtraction" << setw(15) << "Multiplication" << setw(15) << "Division" << setw(15) << "Average" << endl;

    Node* current = PlList.getHead();
    int rank = 1;
    while (current != nullptr) {
        float ave = avg(current->user.add, current->user.sub, current->user.mul, current->user.div);
        current->user.ave = ave;
        cout << setw(5)<< rank << setw(30) << current->user.username << setw(15) << current->user.add << setw(15) << current->user.sub << setw(15) << current->user.mul << setw(15) << current->user.div << setw(15) << fixed << setprecision(2) << ave << endl;
        current = current->next;
        rank++;
    }
    cout << "\t\t\t===================================================================\t\t\t";
    system("pause");
}


void Gamefunction::displayLog(const string& currentUser) {
    loading();
    system("cls");
    cout << "\t\t\t===================================================================\t\t\t" << '\n';
    cout << "\t\t\t                     L E A D E R  B O A R D                        \t\t\t" << '\n';
    cout << "\t\t\t===================================================================\t\t\t" << '\n';
    cout << left << setw(5) << "Rank" << setw(30) << "Name" << setw(15) << "Addition" << setw(15) << "Subtraction" << setw(15) << "Multiplication" << setw(15) << "Division" << setw(15) << "Average" << endl;

    Node* current = PlList.getHead();
    int rank = 1;
    while (current != nullptr) {
        float ave = avg(current->user.add, current->user.sub, current->user.mul, current->user.div);
        current->user.ave = ave;

        if (current->user.username == currentUser) {
        }
        cout << setw(5) << rank << setw(30) << current->user.username << setw(15) << current->user.add << setw(15) << current->user.sub << setw(15) << current->user.mul << setw(15) << current->user.div << setw(15) << fixed << setprecision(2) << ave << endl;
        if (current->user.username == currentUser) {
        }
        current = current->next;
        rank++;
    }
    cout << "\t\t\t===================================================================\t\t\t";
    system("pause");
}

void Gamefunction::displayAdd() {
    loading();
    system("cls");
    boardAdd();
    cout << "\t\t\t===================================================================================\t\t\t" << '\n';
    cout << "\t\t\t                     A D D I T I O N  L E A D E R  B O A R D                       \t\t\t" << '\n';
    cout << "\t\t\t===================================================================================\t\t\t" << '\n';
    cout << left << setw(5) << "Rank" << setw(30) << "Name" << setw(25) << "Score" << setw(25) << "Average" << setw(25) << "REMARK" << endl;

    Node* current = PlList.getHead();
    int rank = 1;
    while (current != nullptr) {
        float average = (static_cast<float>(current->user.add) / 10.0) * 100.0;
        cout << setw(5) << rank << setw(30) << current->user.username << setw(25) << current->user.add << setw(25) << fixed << setprecision(2) << average << "\t\t\t\t\t" << (average >= 75.0 ? "VERY GOOD!" : "NOT ENOUGH!") << endl;
        current = current->next;
        rank++;
    }
    cout << "\t\t\t===================================================================\t\t\t";
    system("pause");
}


void Gamefunction::displaySub() {
    boardSub();
    loading();
    system("cls");
    cout << "\t\t\t===================================================================================\t\t\t" << '\n';
    cout << "\t\t\t                    S U B T R A C T I O N  L E A D E R  B O A R D                  \t\t\t" << '\n';
    cout << "\t\t\t===================================================================================\t\t\t" << '\n';
    cout << left << setw(5) << "Rank" << setw(30) << "Name" << setw(25) << "Score" << setw(25) << "Average" << setw(25) << "REMARK" << endl;

    Node* current = PlList.getHead();
    int rank = 1;
    while (current != nullptr) {
        float average = (static_cast<float>(current->user.sub) / 10.0) * 100.0;
        cout << setw(5) << rank << setw(30) << current->user.username << setw(25) << current->user.sub << setw(25) << fixed << setprecision(2) << average << setw(25) << (average >= 75.0 ? "VERY GOOD!" : "NOT ENOUGH!") << endl;
        current = current->next;
        rank++;
    }
    cout << "\t\t\t===================================================================\t\t\t";
    system("pause");
}

void Gamefunction::displayMul() {
    boardMul();
    loading();
    system("cls");
    cout << "\t\t\t=========================================================================================\t\t\t" << '\n';
    cout << "\t\t\t                    M U L T I P L I C A T I O N  L E A D E R  B O A R D                  \t\t\t" << '\n';
    cout << "\t\t\t=========================================================================================\t\t\t" << '\n';
    cout << left << setw(5) << "Rank" << setw(30) << "Name" << setw(25) << "Score" << setw(25) << "Average" << setw(25) << "REMARK" << endl;

    Node* current = PlList.getHead();
    int rank = 1;
    while (current != nullptr) {
        float average = (static_cast<float>(current->user.mul) / 10.0) * 100.0;
        cout << setw(5) << rank << setw(30) << current->user.username << setw(25) << current->user.mul << setw(25) << fixed << setprecision(2) << average << setw(25) << (average >= 75.0 ? "VERY GOOD!" : "NOT ENOUGH!") << endl;
        current = current->next;
        rank++;
    }
    cout << "\t\t\t===================================================================\t\t\t";
    system("pause");
}

void Gamefunction::displayDiv() {
    boardDiv();
    loading();
    system("cls");
    cout << "\t\t\t=========================================================================================\t\t\t" << '\n';
    cout << "\t\t\t                         D I V I S I O N    L E A D E R  B O A R D                       \t\t\t" << '\n';
    cout << "\t\t\t=========================================================================================\t\t\t" << '\n';
    cout << left << setw(5) << "Rank" << setw(30) << "Name" << setw(25) << "Score" << setw(25) << "Average" << setw(25) << "REMARK" << endl;

    Node* current = PlList.getHead();
    int rank = 1;
    while (current != nullptr) {
        float average = (static_cast<float>(current->user.div) / 10.0) * 100.0;
        cout << setw(5) << rank << setw(30) << current->user.username << setw(25) << current->user.div << setw(25) << fixed << setprecision(2) << average << setw(25) << (average >= 75.0 ? "VERY GOOD!" : "NOT ENOUGH!") << endl;
        current = current->next;
        rank++;
    }
    cout << "\t\t\t===================================================================\t\t\t";
    system("pause");
}


void Gamefunction::displayOperation() {
    int choice;
    bool piliin = true;

    while (piliin) {
        system("cls");
        cout << "\t\t\t=======================================================================================\t\t\t" << '\n';
        cout << "\t\t\t                     O P E R A T I O N   L E A D E R  B O A R D                        \t\t\t" << '\n';
        cout << "\t\t\t=======================================================================================\t\t\t" << '\n';
        cout << "\t\t\t[1] Addition Leaderboard\n";
        cout << "\t\t\t[2] Subtraction Leaderboard\n";
        cout << "\t\t\t[3] Multiplication Leaderboard\n";
        cout << "\t\t\t[4] Division Leaderboard\n";
        cout << "\t\t\t[5] Return to Main Menu\n";
        cout << "\t\t\tPlease Input Numbers (1-5): \n";

        cin >> choice;

        switch (choice) {
            case 1:
                displayAdd();
                break;
            case 2:
                displaySub();
                break;
            case 3:
                displayMul();
                break;
            case 4:
                displayDiv();
                break;
            case 5:
                piliin = false;
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
                break;
        }
    }
}


void Gamefunction::boardAve() {
    Node* current = PlList.getHead();
    int size = PlList.getSize();

    for (int i = 0; i < size; i++) {
        for (int p = 0; p < size - 1; p++) {
            if (current->user.ave < current->next->user.ave) {
                PlayerUser temp = current->user;
                current->user = current->next->user;
                current->next->user = temp;
            }
            current = current->next;
        }
        current = PlList.getHead();
    }
}

void Gamefunction::boardMul() {
    Node* current = PlList.getHead();
    int size = PlList.getSize();

    for (int i = 0; i < size; i++) {
        for (int p = 0; p < size - 1; p++) {
            if (current->user.mul < current->next->user.mul) {
                PlayerUser temp = current->user;
                current->user = current->next->user;
                current->next->user = temp;
            }
            current = current->next;
        }
        current = PlList.getHead();
    }
}

void Gamefunction::boardSub() {
    Node* current = PlList.getHead();
    int size = PlList.getSize();

    for (int i = 0; i < size; i++) {
        for (int p = 0; p < size - 1; p++) {
            if (current->user.sub < current->next->user.sub) {
                PlayerUser temp = current->user;
                current->user = current->next->user;
                current->next->user = temp;
            }
            current = current->next;
        }
        current = PlList.getHead();
    }
}

void Gamefunction::boardDiv() {
    Node* current = PlList.getHead();
    int size = PlList.getSize();

    for (int i = 0; i < size; i++) {
        for (int p = 0; p < size - 1; p++) {
            if (current->user.div < current->next->user.div) {
                PlayerUser temp = current->user;
                current->user = current->next->user;
                current->next->user = temp;
            }
            current = current->next;
        }
        current = PlList.getHead();
    }
}

void Gamefunction::boardAdd() {
    Node* current = PlList.getHead();
    int size = PlList.getSize();

    for (int i = 0; i < size; i++) {
        for (int p = 0; p < size - 1; p++) {
            if (current->user.add < current->next->user.add) {
                PlayerUser temp = current->user;
                current->user = current->next->user;
                current->next->user = temp;
            }
            current = current->next;
        }
        current = PlList.getHead();
    }
}

int Gamefunction::addition(int n) {
    int i, a, b, ans, cor = 0, score = 0;
    system("cls");
    cout << "ADDITION GAME WILL STARTS IN\n";
    ::this_thread::sleep_for(::chrono::seconds(3));
    cout << endl;
    cout << "\tADDITION EXCERCISE\n\n";
    for (i = 0; i < n; i++) {
        a = rand() % 50 + 1;
        b = rand() % 50 + 1;
        cout << i + 1 << ".) What is " << a << " + " << b << "?: ";
        cin >> ans;
        if (ans == a + b) {
            cout << "\t\t\t\t\tWell Played! Your Answer is Correct.\n\n";
            cor++;
        }
        else {
            cout << "\t\t\t\t\tNice Try! The Correct Answer is: " << a + b << ".\n";
        }
    }
    score = cor;
    if (currentUser != nullptr) {
        currentUser->add = score;
    }
    return score;
}

int Gamefunction::subtraction(int n) {
    int i, a, b, ans, cor = 0, score = 0;
    system("cls");
    cout << "SUBTRACTION GAME WILL STARTS IN\n";
    ::this_thread::sleep_for(::chrono::seconds(3));
    cout << endl;
    cout << "\tSUBTRACTION EXCERCISE\n\n";
    for (i = 0; i < n; i++) {
        a = rand() % 50 + 1;
        b = rand() % 50 + 1;
        cout << i + 1 << ".) What is " << a << " - " << b << "?: ";
        cin >> ans;
        if (ans == a - b) {
            cout << "\t\t\t\t\tWell Played! Your Answer is Correct.\n\n";
            cor++;
        }
        else {
            cout << "\t\t\t\t\tNice Try! The Correct Answer is: " << a - b << ".\n";
        }
    }
    score = cor;
    if (currentUser != nullptr) {

        currentUser->sub = score;
    }
    return score;
}

int Gamefunction::multiplication(int n) {
    int i, a, b, ans, cor = 0, score = 0;
    system("cls");
    cout << "MULTIPLICATION GAME WILL STARTS IN\n";
    ::this_thread::sleep_for(::chrono::seconds(3));
    cout << endl;
    cout << "\tMULTIPLICATION EXCERCISE\n\n";
    for (i = 0; i < n; i++) {
        a = rand() % 50 + 1;
        b = rand() % 50 + 1;
        cout << i + 1 << ".) What is " << a << " x " << b << "?: ";
        cin >> ans;
        if (ans == a * b) {
            cout << "\t\t\t\t\tWell Played! Your Answer is Correct.\n\n";
            cor++;
        }
        else {
            cout << "\t\t\t\t\tNice Try! The Correct Answer is: " << a * b << ".\n";
        }
    }
    score = cor;
    if (currentUser != nullptr) {

        currentUser->mul = score;
    }
    return score;
}

int Gamefunction::division(int n) {
    int i, a, b, ans, cor = 0, score = 0;
    system("cls");
    cout << "DIVISION GAME WILL STARTS IN ";
    ::this_thread::sleep_for(::chrono::seconds(3));
    cout << endl;
    cout << "\tDIVISION EXCERCISE\n\n";
    for (i = 0; i < n; i++) {
        b = rand() % 15 + 1;
        a = b * (rand() % 15 + 1);
        cout << i + 1 << ".) What is " << a << " / " << b << "?: ";
        cin >> ans;
        if (ans == a / b && a % b == 0) {
            cout << "\t\t\t\t\tWell Played! Your Answer is Correct.\n\n";
            cor++;
        }
        else {
            cout << "\t\t\t\t\tNice Try! The Correct Answer is: " << a / b << ".\n";
        }
    }
    score = cor;
    if (currentUser != nullptr) {

        currentUser->div = score;
    }
    return score;
}



void Gamefunction::practiceGame() {

    int choice, score, items = 10;
    float finalGrade;
    srand(time(NULL));
    loading();

    while (true) {
        system("cls");
        cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
        cout << "\t\t\t                     J O S H' S  A R I T H M E T I C  G A M E                        \t\t\t" << '\n';
        cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
        cout << "\t\t\t[1]Addition Game\n";
        cout << "\t\t\t[2]Subtraction Game\n";
        cout << "\t\t\t[3]Multiplication Game\n";
        cout << "\t\t\t[4]Division Game\n";
        cout << "\t\t\t[5]Leaderboard Rankings\n";
        cout << "\t\t\t[6]Exit Game\n";
        cout << "\t\t\tInput Action [1-6]: ";
        cin >> choice;

        switch (choice) {
            case 1:
                score = addition(items);
                finalGrade = static_cast<float>(score) / items * 100;
                system("cls");
                cout << "Out of " << items << " Questions, You got " << score << " Correct Answer.\n";
                cout << "You got " << finalGrade << "% for Addition!\n";
                SaveUser();
                system("pause");
                system("cls");
                break;

            case 2:
                score = subtraction(items);
                finalGrade = static_cast<float>(score) / items * 100;
                system("cls");
                cout << "Out of " << items << " Questions, You got " << score << " Correct Answer.\n";
                cout << "You got " << finalGrade << "% for subtraction!\n";
                SaveUser();
                system("pause");
                system("cls");
                break;

            case 3:
                score = multiplication(items);
                finalGrade = static_cast<float>(score) / items * 100;
                system("cls");
                cout << "Out of " << items << " Questions, You got " << score << " Correct Answer.\n";
                cout << "You got " << finalGrade << "% for multiplication!\n";
                SaveUser();
                system("pause");
                system("cls");
                break;

            case 4:
                score = division(items);
                finalGrade = static_cast<float>(score) / items * 100;
                system("cls");
                cout << "Out of " << items << " Questions, You got " << score << " Correct Answer.\n";
                cout << "You got " << finalGrade << "% for Division!\n";
                SaveUser();
                system("pause");
                system("cls");
                break;

            case 5:
                displayLog(currentUser->username);
                break;

            case 6:
                system("cls");
                cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
                cout << "\t\t\t                                    G A M E  S A V E D!                             \t\t\t" << '\n';
                cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
                cout << "\t\t\t                                     Exit in 3 Seconds...                            \t\t\t" << '\n';
                SaveUser();
                cout << "\t\t\t\t\t";
                delay(3);
                menu();

            default:
                system("cls");
                cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
                cout << "\t\t\t                                     INVALID OPTION                                  \t\t\t" << '\n';
                cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
                cout << "\t\t\t                                    INPUT NUMBER 1-5                                  \t\t\t" << '\n';
                break;
        }
    }
}

int Gamefunction::menu() {

    int action;
    int opt = 1;
    sleep();

    while (1) {
        system("cls");
        cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
        cout << "\t\t\t                                 M A I N  M E N U                                    \t\t\t" << '\n';
        cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
        cout << "\t\t\t[1]Register\n";
        cout << "\t\t\t[2]Log-In\n";
        cout << "\t\t\t[3]Overall Leaderboards\n";
        cout << "\t\t\t[4]Operations Leaderboards\n";
        cout << "\t\t\t[5]Exit\n";
        cout << "\t\t\tInput Action [1-5]: ";
        cin >> action;

        switch (action) {
            case 1: {
            Register();
            break;
        }
        case 2: {
            LogIn();
            break;
        }
        case 3: {
            display();
            break;
        }
        case 4: {
            displayOperation();
            break;
        }
        case 5: {
            cout << "\t\t\t\t\tLoading...Thank You!\n";
            cout << "\t\t\t\t\t";
            system("pause");
            SaveUser();
            delay(3);
            exit(0);
        }
        default: {
            cout << "\t\t\t\t\tInvalid Option!\n";
            cout << "\t\t\t\t\t";
            system("pause");
        }
        }
    }
        return 0;

}
float Gamefunction::avg(int a, int b, int c, int d) {
    return ((a + b + c + d) / 4.00) * 20;
}

void delay(int number_of_seconds) {
    ::chrono::milliseconds duration(number_of_seconds * 1000);
    ::this_thread::sleep_for(duration);
}


void Gamefunction::Register() {
    int i;
    bool taken = false;
    string username, password;
    system("cls");
        cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
        cout << "\t\t\t                           C R E A T E  A N  A C C O U N T                           \t\t\t" << '\n';
        cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
        cout << "\t\t\t                                 R E G I S T E R                                     \t\t\t" << '\n';
        cout << "\t\t\tEnter Username: ";
    cin >> username;
    for (i = 0; i <= PlList.getSize(); i++) {
        PlayerUser* user = PlList.getUser(username);
        if (user != nullptr) {
            taken = true;
            cout << "\t\t\tUsername is already used. Try Again!\n";
            cout << "\t\t\t\t\t";
            system("pause");
            break;
        }
    }
    if (!taken) {
        cout << "\t\t\tEnter Password: ";
        cin >> password;
        if (password == password) {
            PlayerUser user(username, password);
            PlList.addUser(user);
            cout << "\t\t\tSuccessfully created!\n";
            cout << "\t\t\t\t\t";
            system("pause");
        } else {
            cout << "\t\t\tYour Password is incorrect!\n";
            cout << "\t\t\t\t\t";
            system("pause");
        }
    }
    taken = false;
    SaveUser();
    menu();
}

// Logging of user account
void Gamefunction::LogIn() {
    string username, password;
    system("cls");
        cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
        cout << "\t\t\t                         L O G - I N  Y O U R  A C C O U N T                         \t\t\t" << '\n';
        cout << "\t\t\t=====================================================================================\t\t\t" << '\n';
        cout << "\t\t\t                                     L O G - I N                                     \t\t\t" << '\n';
        cout << "\t\t\tEnter Username: ";
        cin >> username;

    PlayerUser* user = PlList.getUser(username);
    if (user == nullptr) {
        cout << "\t\t\t\t\tUsername not available\n";
        cout << "\t\t\t\t\t";
        system("pause");
        return;
}
    cout << "\t\t\tEnter Password: ";
    cin >> password;
    if (user->password == password) {
        system("cls");
        cout << "\n\n\n\n\n\n\t\t\t\t\t\tWELCOME, Player: " << username << "!\n\n";
        setCurrentUser(username);
        cout << "\t\t\t\t\t  ";
        system("pause");
        displayLog(currentUser->username);
        practiceGame();
}
    else {
        cout << "\t\t\t\t\tInvalid password!\n";
        cout << "\t\t\t\t\t";
        system("pause");
        menu();
    }
}
int main() {
    Gamefunction ret;
    system("color 1f");
    ret.Retrieve();
    ret.menu();
    return 0;
}
