#include "CompressorStation.h"
using namespace std;

int CompressorStation::nextId=1;

CompressorStation::CompressorStation()
    :id(nextId++),name(""),workshops(0),workshopsInWork(0),stationClass(0) {
}

int CompressorStation::getId() const {
    return id;
}

string CompressorStation::getName() const {
    return name;
}

void CompressorStation::input() {
    cout<<"Название КС: ";
    getline(cin>>ws,name);
    cout<<"Количество цехов: ";
    cin>>workshops;
    while (cin.fail() || workshops<=0) {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Введите количество цехов еще раз: ";
        cin>>workshops;
    }
    cin.ignore(100,'\n');
    cout<<"Цехов в работе: ";
    cin>>workshopsInWork;
    while (cin.fail() || workshopsInWork<0 || workshopsInWork>workshops) {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Введите количество работающих цехов еще раз: ";
        cin>>workshopsInWork;
    }
    cin.ignore(100,'\n');
    cout<<"Класс: ";
    cin>>stationClass;
    while (cin.fail() || stationClass<=0) {
        cin.clear();
        cin.ignore(100,'\n');
        cout<<"Введите класс еще раз: ";
        cin>>stationClass;
    }
    cin.ignore(100,'\n');
}

void CompressorStation::print() const {
    cout<<"КС ID: "<<id<<endl;
    cout<<"Название: "<<name<<endl;
    cout<<"Цехов: "<<workshops<<endl;
    cout<<"Работает: "<<workshopsInWork<<endl;
    cout<<"Класс: "<<stationClass<<endl;
    cout<<"Незадействовано: "<<getIdlePercent()<<"%"<<endl;
}

void CompressorStation::startWorkshop() {
    if (workshopsInWork<workshops) {
        workshopsInWork++;
    }
    else {
        cout<<"Все цеха уже работают"<<endl;
    }
}

void CompressorStation::stopWorkshop() {
    if (workshopsInWork>0) {
        workshopsInWork--;
    }
    else {
        cout<<"Нет работающих цехов"<<endl;
    }
}

double CompressorStation::getIdlePercent() const {
    if (workshops==0) {
        return 0;
    }
    return (workshops-workshopsInWork)*100.0/workshops;
}

bool CompressorStation::matchesName(const string& text) const {
    return name.find(text)!=string::npos;
}

bool CompressorStation::matchesIdlePercent(double percent) const {
    return getIdlePercent()>=percent;
}

ostream& operator<<(ostream& out,const CompressorStation& cs) {
    out<<cs.id<<endl;
    out<<cs.name<<endl;
    out<<cs.workshops<<endl;
    out<<cs.workshopsInWork<<endl;
    out<<cs.stationClass<<endl;
    return out;
}

istream& operator>>(istream& in,CompressorStation& cs) {
    in>>cs.id;
    in.ignore(100,'\n');
    getline(in,cs.name);
    in>>cs.workshops;
    in>>cs.workshopsInWork;
    in>>cs.stationClass;
    in.ignore(100,'\n');
    return in;
}