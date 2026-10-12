#include <iostream>
#include <string>
using namespace std;

// 1. Patient Node Design
struct PatientNode {
    int patientID;
    string patientName;
    string condition;
    int priority; // 1 = Critical, 2 = Urgent, 3 = Non-Urgent
    PatientNode* next;
};

// 2. Priority Queue Class for Hospital Triage
class HospitalPriorityQueue {
private:
    PatientNode* front;
    PatientNode* rear;
    int count;

public:
    HospitalPriorityQueue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    // Add Patient according to Triage Priority
    void Add(PatientNode* newPatient) {
        newPatient->next = nullptr;

        // Case 1: Queue is empty
        if (front == nullptr) {
            front = newPatient;
            rear = newPatient;
        }
        // Case 2: New patient has higher priority (smaller number = higher priority)
        else if (newPatient->priority < front->priority) {
            newPatient->next = front;
            front = newPatient;
        }
        // Case 3: Insert after front based on priority order
        else {
            PatientNode* current = front;
            while (current->next != nullptr && current->next->priority <= newPatient->priority) {
                current = current->next;
            }
            newPatient->next = current->next;
            current->next = newPatient;
            if (newPatient->next == nullptr) {
                rear = newPatient;
            }
        }
        count++;
    }

    // Remove / Attend highest priority patient
    PatientNode* Remove() {
        if (front == nullptr) {
            return nullptr;
        }
        PatientNode* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        temp->next = nullptr;
        count--;
        return temp;
    }

    bool IsEmpty() {
        return front == nullptr;
    }

    void DisplayQueue() {
        if (IsEmpty()) {
            cout << "No patients waiting in queue.\n";
            return;
        }
        PatientNode* current = front;
        while (current != nullptr) {
            cout << "ID: " << current->patientID 
                 << " | Name: " << current->patientName 
                 << " | Condition: " << current->condition 
                 << " | Priority: P" << current->priority << endl;
            current = current->next;
        }
    }

    ~HospitalPriorityQueue() {
        while (front != nullptr) {
            PatientNode* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

// Helper function to dynamically create node
PatientNode* CreatePatient(int id, string name, string condition, int priority) {
    PatientNode* node = new PatientNode;
    node->patientID = id;
    node->patientName = name;
    node->condition = condition;
    node->priority = priority;
    node->next = nullptr;
    return node;
}

int main() {
    HospitalPriorityQueue triageQueue;
    int choice = 0;

    while (choice != 5) {
        cout << "\n============================================\n";
        cout << "   Hospital Emergency Triage System\n";
        cout << "============================================\n";
        cout << "1. Register New Patient\n";
        cout << "2. Attend Highest Priority Patient\n";
        cout << "3. Display All Waiting Patients\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Select Option (1-5): ";
        cin >> choice;

        if (choice == 1) {
            int id, priority;
            string name, condition;

            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter Patient Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Condition/Issue: ";
            getline(cin, condition);
            cout << "Enter Triage Level (1: Critical, 2: Urgent, 3: Non-Urgent): ";
            cin >> priority;

            PatientNode* p = CreatePatient(id, name, condition, priority);
            triageQueue.Add(p);
            cout << "Patient added to queue successfully!\n";

        } else if (choice == 2) {
            PatientNode* attended = triageQueue.Remove();
            if (attended != nullptr) {
                cout << "\n--- Attending Patient ---\n";
                cout << "Patient Name: " << attended->patientName << endl;
                cout << "Condition: " << attended->condition << endl;
                cout << "Priority: P" << attended->priority << endl;
                delete attended;
            } else {
                cout << "Queue is empty! No patients waiting.\n";
            }

        } else if (choice == 3) {
            cout << "\n--- Patients Waiting in Order of Priority ---\n";
            triageQueue.DisplayQueue();

        } else if (choice == 4) {
            if (triageQueue.IsEmpty()) {
                cout << "Status: Emergency Room Queue is Empty.\n";
            } else {
                cout << "Status: Patients are currently waiting in the ER.\n";
            }

        } else if (choice == 5) {
            cout << "Exiting system...\n";
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}