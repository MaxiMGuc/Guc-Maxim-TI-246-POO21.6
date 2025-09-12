#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Node {
private:
    string phone;
    string adres;
    float square;
    Node* next;

public:
    Node(const string& phone, const string& adres, float square)
        : phone(phone), adres(adres), square(square), next(nullptr) {}

    // --- getters & setters ---
    string getPhone() const { return phone; }
    string getAdres() const { return adres; }
    float getSquare() const { return square; }
    Node* getNext() const { return next; }

    void setPhone(const string& p) { phone = p; }
    void setAdres(const string& a) { adres = a; }
    void setSquare(float s) { square = s; }
    void setNext(Node* n) { next = n; }
};

// --- Функции работы со списком ---
void append(Node*& head, const string& phone, const string& adres, float square) {
    Node* newNode = new Node(phone, adres, square);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->getNext()) temp = temp->getNext();
    temp->setNext(newNode);
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << "Phone: " << temp->getPhone()
             << ", Adres: " << temp->getAdres()
             << ", Square: " << temp->getSquare() << endl;
        temp = temp->getNext();
    }
}

void writeToTextFile(Node* head) {
    ofstream file("list.txt");
    if (!file) {
        cout << "Error opening file\n";
        return;
    }
    Node* temp = head;
    while (temp) {
        file << temp->getPhone() << ";" << temp->getAdres() << ";" << temp->getSquare() << "\n";
        temp = temp->getNext();
    }
    cout << "List is written to text.\n";
}

void readFromTextFile(Node*& head) {
    ifstream file("list.txt");
    if (!file) {
        cout << "Error opening file\n";
        return;
    }
    string phone, adres;
    float square;
    while (getline(file, phone, ';') &&
           getline(file, adres, ';') &&
           (file >> square)) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        append(head, phone, adres, square);
    }
    cout << "List is read from text.\n";
}

void freeList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->getNext();
        delete temp;
    }
    cout << "Memory freed\n";
}

void enterElements(Node*& head) {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string phone, adres;
        float square;
        cout << "Phone: ";
        cin >> phone;
        cin.ignore();
        cout << "Adres: ";
        getline(cin, adres);
        cout << "Square: ";
        cin >> square;
        append(head, phone, adres, square);
    }
}

void searchForElement(Node* head) {
    string phone;
    cout << "Enter phone: ";
    cin >> phone;

    Node* temp = head;
    while (temp) {
        if (temp->getPhone() == phone) {
            cout << "Found: " << temp->getPhone() << ", " << temp->getAdres()
                 << ", " << temp->getSquare() << endl;
            return;
        }
        temp = temp->getNext();
    }
    cout << "Element not found.\n";
}

void sortList(Node*& head) {
    if (!head || !head->getNext()) return;
    for (Node* i = head; i; i = i->getNext()) {
        for (Node* j = i->getNext(); j; j = j->getNext()) {
            if (i->getPhone() > j->getPhone()) {
                string p = i->getPhone(); i->setPhone(j->getPhone()); j->setPhone(p);
                string a = i->getAdres(); i->setAdres(j->getAdres()); j->setAdres(a);
                float s = i->getSquare(); i->setSquare(j->getSquare()); j->setSquare(s);
            }
        }
    }
    cout << "List sorted.\n";
}

void editElement(Node* head) {
    string phone;
    cout << "Enter phone to edit: ";
    cin >> phone;
    Node* temp = head;
    while (temp) {
        if (temp->getPhone() == phone) {
            cout << "New phone: ";
            string newPhone; cin >> newPhone;
            temp->setPhone(newPhone);
            cin.ignore();
            cout << "New adres: ";
            string newAdres; getline(cin, newAdres);
            temp->setAdres(newAdres);
            cout << "New square: ";
            float sq; cin >> sq;
            temp->setSquare(sq);
            cout << "Edited.\n";
            return;
        }
        temp = temp->getNext();
    }
    cout << "Not found.\n";
}

void addToEnd(Node*& head) {
    string phone, adres;
    float square;
    cout << "Phone: ";
    cin >> phone;
    cin.ignore();
    cout << "Adres: ";
    getline(cin, adres);
    cout << "Square: ";
    cin >> square;
    append(head, phone, adres, square);
}

void deleteElement(Node*& head) {
    string phone;
    cout << "Enter phone to delete: ";
    cin >> phone;

    Node* temp = head;
    Node* prev = nullptr;
    while (temp && temp->getPhone() != phone) {
        prev = temp;
        temp = temp->getNext();
    }
    if (!temp) {
        cout << "Not found.\n";
        return;
    }
    if (!prev) head = temp->getNext();
    else prev->setNext(temp->getNext());
    delete temp;
    cout << "Deleted.\n";
}

void insertElement(Node*& head) {
    string phone, adres;
    float square;
    int pos;
    cout << "Phone: ";
    cin >> phone;
    cin.ignore();
    cout << "Adres: ";
    getline(cin, adres);
    cout << "Square: ";
    cin >> square;
    cout << "Position: ";
    cin >> pos;

    Node* newNode = new Node(phone, adres, square);
    if (pos == 0) {
        newNode->setNext(head);
        head = newNode;
        return;
    }
    Node* temp = head;
    for (int i = 0; temp && i < pos - 1; i++) temp = temp->getNext();
    if (!temp) {
        cout << "Wrong position\n";
        delete newNode;
        return;
    }
    newNode->setNext(temp->getNext());
    temp->setNext(newNode);
}

void readFromBinaryFile(Node*& head) {
    ifstream file("list.bin", ios::binary);
    if (!file) {
        cout << "Error opening file\n";
        return;
    }
    string phone, adres;
    float square;
    while (true) {
        size_t len1, len2;
        if (!file.read((char*)&len1, sizeof(len1))) break;
        phone.resize(len1);
        file.read(&phone[0], len1);
        file.read((char*)&len2, sizeof(len2));
        adres.resize(len2);
        file.read(&adres[0], len2);
        file.read((char*)&square, sizeof(square));
        append(head, phone, adres, square);
    }
    cout << "Read from binary.\n";
}

void writeToBinaryFile(Node* head) {
    ofstream file("list.bin", ios::binary);
    if (!file) {
        cout << "Error opening file\n";
        return;
    }
    Node* temp = head;
    while (temp) {
        size_t len1 = temp->getPhone().size();
        size_t len2 = temp->getAdres().size();
        file.write((char*)&len1, sizeof(len1));
        file.write(temp->getPhone().data(), len1);
        file.write((char*)&len2, sizeof(len2));
        file.write(temp->getAdres().data(), len2);
        float sq = temp->getSquare();
        file.write((char*)&sq, sizeof(sq));
        temp = temp->getNext();
    }
    cout << "Written to binary.\n";
}

int main() {
    Node* head = nullptr;
    int choice;

    while (true) {
        cout << "\nMenu:\n"
             << "1) Enter elements\n"
             << "2) Search element\n"
             << "3) Sort list\n"
             << "4) Edit element\n"
             << "5) Add to end\n"
             << "6) Delete element\n"
             << "7) Insert element\n"
             << "8) Write binary\n"
             << "9) Read binary\n"
             << "10) Write text\n"
             << "11) Read text\n"
             << "12) Print list\n"
             << "13) Free memory\n"
             << "14) Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: enterElements(head); break;
            case 2: searchForElement(head); break;
            case 3: sortList(head); break;
            case 4: editElement(head); break;
            case 5: addToEnd(head); break;
            case 6: deleteElement(head); break;
            case 7: insertElement(head); break;
            case 8: writeToBinaryFile(head); break;
            case 9: readFromBinaryFile(head); break;
            case 10: writeToTextFile(head); break;
            case 11: readFromTextFile(head); break;
            case 12: printList(head); break;
            case 13: freeList(head); break;
            case 14: freeList(head); cout << "Exit.\n"; return 0;
            default: cout << "Wrong choice.\n";
        }
    }
}
