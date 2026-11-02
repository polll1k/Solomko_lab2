#include "Logger.h"
#include <fstream>
using namespace std;

void Logger::write(const string& text) {
    ofstream file("log.txt",ios::app);
    file<<text<<endl;
}
void Logger::write(int number) {
    ofstream file("log.txt",ios::app);
    file<<number<<endl;
}
void Logger::write(double number) {
    ofstream file("log.txt",ios::app);
    file<<number<<endl;
}