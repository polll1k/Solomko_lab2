#ifndef MANAGER_H
#define MANAGER_H
#include <unordered_map>
#include <vector>
#include <iostream>
#include "Pipe.h"
#include "CompressorStation.h"
class Manager {
private:
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, CompressorStation> stations;
    void addPipe();
    void addStation();
    void showObjects();
    void searchPipes();
    void searchStations();
    void saveData();
    void loadData();
    template <typename T, typename Predicate>
    std::vector<int> findMatches(
        const std::unordered_map<int, T>& items,
        Predicate check
    ) {
        std::vector<int> ids;

        for (const auto& pair : items) {
            if (check(pair.second)) {
                pair.second.print();
                std::cout << std::endl;
                ids.push_back(pair.first);
            }
        }
        return ids;
    }
public:
    void run();
};

#endif