#include "Logger.h"
#include <fstream>
using namespace std;

void Logger::write(const string& message) {
    ofstream log("log.txt",ios::app);
    if (log) {
        log<<message<<endl;
    }
}