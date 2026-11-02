#include <string>

class Logger {
public:
    static void write(const std::string& text);
    static void write(int number);
    static void write(double number);
};