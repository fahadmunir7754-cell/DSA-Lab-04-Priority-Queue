#include <iostream>
#include <string>
using namespace std;

// Book Request Node
struct BookRequestNode {
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

// Priority Queue Class
class PriorityQueue {
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void Add(BookRequestNode* request) {
        request->next = nullptr;
        if (front == nullptr) {
            front = request;
            rear = request;
        } else if (request->priority < front->priority) {
            request->next = front;
            front = request;
        } else {
            BookRequestNode* current = front;
            while (current->next != nullptr && current->next->priority <= request->priority) {
                current = current->next;
            }
            request->next = current->next;
            current->next = request;
            if (request->next == nullptr) {
                rear = request;
            }
        }
        count++;
    }

    BookRequestNode* Remove() {
        if (front == nullptr) {
            return nullptr;
        }
        BookRequestNode* request = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        request->next = nullptr;
        count--;
        return request;
    }

    bool IsEmpty() {
        return front == nullptr;
    }

    bool IsNotEmpty() {
        return front != nullptr;
    }

    void PrintQueue() {
        if (IsEmpty()) {
            cout << "Queue khali hai.\n";
            return;
        }
        BookRequestNode* current = front;
        while (current != nullptr) {
            cout << "Student ID: " << current->studentID << endl;
            cout << "Student Name: " << current->studentName << endl;
            cout << "Book ID: " << current->bookID << endl;
            cout << "Book Title: " << current->bookTitle << endl;
            cout << "Priority: " << current->priority << endl;
            cout << "-----------------------------------" << endl;
            current = current->next;
        }
    }

    ~PriorityQueue() {
        while (front != nullptr) {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

BookRequestNode* CreateRequest(int studentID, string studentName, int bookID, string bookTitle, int priority) {
    BookRequestNode* request = new BookRequestNode;
    request->studentID = studentID;
    request->studentName = studentName;
    request->bookID = bookID;
    request->bookTitle = bookTitle;
    request->priority = priority;
    request->next = nullptr;
    return request;
}

int main() {
    PriorityQueue requests;
    int choice = 0;

    while (choice != 5) {
        cout << "\n=========================================\n";
        cout << "       Library Book Request System\n";
        cout << "=========================================\n";
        cout << "1. Add Book Request\n";
        cout << "2. Process Highest Priority Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Option select karein (1-5): ";
        cin >> choice;

        if (choice == 1) {
            int sID, bID, prio;
            string sName, bTitle;

            cout << "Enter Student ID: ";
            cin >> sID;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, sName);
            cout << "Enter Book ID: ";
            cin >> bID;
            cout << "Enter Book Title: ";
            getline(cin, bTitle);
            cout << "Enter Priority (1: Exam/Urgent, 2: Assignment, 3: Normal): ";
            cin >> prio;

            BookRequestNode* newNode = CreateRequest(sID, sName, bID, bTitle, prio);
            requests.Add(newNode);
            cout << "Request successfully add ho gayi!\n";

        } else if (choice == 2) {
            BookRequestNode* processed = requests.Remove();
            if (processed != nullptr) {
                cout << "\n--- Processing Request ---\n";
                cout << "Student: " << processed->studentName << " (ID: " << processed->studentID << ")\n";
                cout << "Book: " << processed->bookTitle << " (ID: " << processed->bookID << ")\n";
                cout << "Priority: " << processed->priority << "\n";
                delete processed;
            } else {
                cout << "Queue khali hai! Koi request process karne ke liye nahi hai.\n";
            }

        } else if (choice == 3) {
            cout << "\n--- All Pending Requests ---\n";
            requests.PrintQueue();

        } else if (choice == 4) {
            if (requests.IsEmpty()) {
                cout << "Status: Queue bilkul khali (Empty) hai.\n";
            } else {
                cout << "Status: Queue mein requests pending hain (Not Empty).\n";
            }

        } else if (choice == 5) {
            cout << "Program close ho raha hai...\n";
        } else {
            cout << "Invalid choice! Dubara koshish karein.\n";
        }
    }

    return 0;
}