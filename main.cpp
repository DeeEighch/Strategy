#include <iostream>
#include <list>
using namespace std;

class Observer {
public:
    virtual void update(int value) = 0;
};

class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void notify() = 0;
};

class NumberSubject : public Subject {
    int m_number;
    std::list<Observer*> m_observers;
public:
    virtual void attach(Observer* observer) override {
        m_observers.push_back(observer);
    }

    virtual void notify() override {
        for (Observer* obs: m_observers) {
            obs->update(m_number);
        }
    }

    void set_number(int number) {
        m_number = number;
        notify();
    }


};

class DivObserver : public Observer {
    int m_div;
public:
    DivObserver(Subject* model, int div) {
        model->attach(this);
        m_div = div;
    }

    virtual void update(int value) {
        cout << "DivObserver: div {"<< m_div <<"} is " << value / m_div << endl;
    }
};

class ModObserver : public Observer {
    int m_mod;
public:
    ModObserver(Subject* model, int mod) {
        model->attach(this);
        m_mod = mod;
    }

    virtual void update(int value) {
        cout << "ModObserver: mod {"<< m_mod <<"} is " << value % m_mod << endl;
    }
};





int main()
{
    NumberSubject sub;
    DivObserver d1(&sub, 4);
    DivObserver d2(&sub, 3);
    ModObserver m1(&sub, 3);

    sub.set_number(5);

    return 0;
}
