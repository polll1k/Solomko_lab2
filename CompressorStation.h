#include <iostream>
#include <string>

class CompressorStation {
private:
    int id;
    std::string name;
    int workshops;
    int workshopsInWork;
    int stationClass;
    static int nextId;

public:
    CompressorStation();
    int getId() const;
    std::string getName() const;
    void input();
    void print() const;
    void startWorkshop();
    void stopWorkshop();
    double getIdlePercent() const;
    bool matchesName(const std::string& text) const;
    bool matchesIdlePercent(double percent) const;

    friend std::ostream& operator<<(std::ostream& out,const CompressorStation& cs);
    friend std::istream& operator>>(std::istream& in,CompressorStation& cs);
};