//LL1 deque simulation
#include <iostream> // input/output (cin, cout)
#include <deque>    // container std::deque
#include <string>
using namespace std;//чтою не писать std каждый раз

struct Process {
    string name;
    int remainingTime; //время выполнения
    int priority; // 1 - высшая приоритетность
};

int main() {
    deque<Process> dq;
    //методы либы из стандартной библиотеки с++
    dq.push_back({"P2", 5, 2});//usual
    dq.push_front({"P1", 3, 1});//important

    while (!dq.empty()) {
        Process p = dq.front();//ссылка на 1й элем дека
        dq.pop_front();//удаляет 1й элем
        cout << "carring out process " << p.name << endl;
        p.remainingTime--;

        if (p.remainingTime > 0) {
            dq.push_back(p); // process is not ended -> return into end
        } else {
            cout << "Process " << p.name  << " is ended \n";
        }
    }
    return 0;
}
