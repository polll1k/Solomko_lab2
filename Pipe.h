#include <iostream>
#include <string>

class Pipe {
private:
    int id;
    std::string name;
    double length;
    int diameter;
    bool inRepair;
    static int nextId;
public:
    Pipe();
    int getId() const;
    void input();
    void print() const;
    void setRepair(bool value);
    bool matchesName(const std::string& text) const;
    bool matchesRepair(bool value) const;   
};