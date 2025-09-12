#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

struct Node {
    string phone;
    string adres;
    float square;
    Node* next;

    Node(const string& phone, const string& adres, float square)
        : phone(phone), adres(adres), square(square), next(nullptr) {}
};

// Добавление узла в конец
void append(Node*& head, const string& phone, const string& adres, float square) {
    Node* newNode = new Node(phone, adres, square);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

// Вывод списка
void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << "Phone: " << temp->phone
             << ", Adres: " << temp->adres
             << ", Square: " << temp->square << endl;
        temp = temp->next;
    }
}

// Запись в текстовый файл
void writeToTextFile(Node* head) {
    ofstream file("list.txt");
    if (!file) {
        cout << "Error opening file\n";
        return;
    }
    Node* temp = head;
    while (temp) {
        file << temp->phone << ";" << temp->adres << ";" << temp->square << "\n";
        temp = temp->next;
    }
    cout << "List is written to text.\n";
}

// Чтение из текстового файла
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

// Освобождение памяти
void freeList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "Memory freed\n";
}

// Ввод элементов
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

// Поиск по телефону
void searchForElement(Node* head) {
    string phone;
    cout << "Enter phone: ";
    cin >> phone;

    Node* temp = head;
    while (temp) {
        if (temp->phone == phone) {
            cout << "Found: " << temp->phone << ", " << temp->adres
                 << ", " << temp->square << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Element not found.\n";
}

// Сортировка по телефону
void sortList(Node*& head) {
    if (!head || !head->next) return;
    for (Node* i = head; i; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if (i->phone > j->phone) {
                swap(i->phone, j->phone);
                swap(i->adres, j->adres);
                swap(i->square, j->square);
            }
        }
    }
    cout << "List sorted.\n";
}

// Редактирование элемента
void editElement(Node* head) {
    string phone;
    cout << "Enter phone to edit: ";
    cin >> phone;
    Node* temp = head;
    while (temp) {
        if (temp->phone == phone) {
            cout << "New phone: ";
            cin >> temp->phone;
            cin.ignore();
            cout << "New adres: ";
            getline(cin, temp->adres);
            cout << "New square: ";
            cin >> temp->square;
            cout << "Edited.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Not found.\n";
}

// Добавление в конец
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

// Удаление
void deleteElement(Node*& head) {
    string phone;
    cout << "Enter phone to delete: ";
    cin >> phone;

    Node* temp = head;
    Node* prev = nullptr;
    while (temp && temp->phone != phone) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        cout << "Not found.\n";
        return;
    }
    if (!prev) head = temp->next;
    else prev->next = temp->next;
    delete temp;
    cout << "Deleted.\n";
}

// Вставка по позиции
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
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* temp = head;
    for (int i = 0; temp && i < pos - 1; i++) temp = temp->next;
    if (!temp) {
        cout << "Wrong position\n";
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

// Чтение из бинарного файла
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

// Запись в бинарный файл
void writeToBinaryFile(Node* head) {
    ofstream file("list.bin", ios::binary);
    if (!file) {
        cout << "Error opening file\n";
        return;
    }
    Node* temp = head;
    while (temp) {
        size_t len1 = temp->phone.size();
        size_t len2 = temp->adres.size();
        file.write((char*)&len1, sizeof(len1));
        file.write(temp->phone.data(), len1);
        file.write((char*)&len2, sizeof(len2));
        file.write(temp->adres.data(), len2);
        file.write((char*)&temp->square, sizeof(temp->square));
        temp = temp->next;
    }
    cout << "Written to binary.\n";
}

int main() {
    Node* head = nullptr;
    int choice;

    while (true) {
        cout << "\nMenu:\n"
             << "2) Enter elements\n"
             << "3) Search element\n"
             << "4) Sort list\n"
             << "5) Edit element\n"
             << "6) Add to end\n"
             << "7) Delete element\n"
             << "8) Insert element\n"
             << "9) Write binary\n"
             << "10) Read binary\n"
             << "11) Write text\n"
             << "12) Read text\n"
             << "13) Print list\n"
             << "14) Free memory\n"
             << "15) Exit\n"
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
