#include <iostream>
#include <vector>
using namespace std;

class Subject {
    // 1. "independent" functionality
    vector < class Observer * > views; // 3. Coupled only to "interface"
    int value;
public:
    void attach(Observer *obs) {
        views.push_back(obs);
    }
    void setVal(int val) {
        value = val;
        notify();
    }
    int getVal() {
        return value;
    }
    void notify();
};



class Observer {
    // 2. "dependent" functionality
    Subject *model;
    int denom;
public:
    Observer(Subject *mod, int div) {
        model = mod;
        denom = div;
        // 4. Observers register themselves with the Subject
        model->attach(this);
    }
    virtual void update() = 0;
protected:
    Subject *getSubject() {
        return model;
    }
    int getDivisor() {
        return denom;
    }
};


void Subject::notify() {
    // 5. Publisher broadcasts
    for (int i = 0; i < views.size(); i++)
        views[i]->update();
}

class DivObserver: public Observer {
public:
    DivObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        // 6. "Pull" information of interest
        int v = getSubject()->getVal(), d = getDivisor();
        cout << v << " div " << d << " is " << v / d << '\n';
    }
};

class ModObserver: public Observer {
public:
    ModObserver(Subject *mod, int div): Observer(mod, div){}
    void update() {
        int v = getSubject()->getVal(), d = getDivisor();
        cout << v << " mod " << d << " is " << v % d << '\n';
    }
};

int main() {
    Subject subj;
    int divisor, dividendo, opcion;
    cout << "1. División \n2. Módulo \n" << endl;
    cin >> opcion;
    if (opcion == 1) {
        cout << "Escriba el divisor" << endl;
        cin >> divisor;
        cout << "Escriba el dividendo" << endl;
        cin >> dividendo;
        DivObserver divObs1(&subj, dividendo); // 7. Client configures the number and //    type of Observers
        subj.setVal(divisor);


    } else if (opcion == 2) {
        cout << "Escriba el divisor" << endl;
        cin >> divisor;
        cout << "Escriba el dividendo" << endl;
        cin >> dividendo;
    ModObserver modObs3(&subj, dividendo);
    subj.setVal(divisor);
}
}