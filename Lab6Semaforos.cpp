#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

struct Car {
    int carNumber;
};

const int numCars = 50;
const int numGatesStation1 = 5;
const int numGatesStation2 = 6;

std::mutex station1Mutex;
std::mutex station2Mutex;

void payAtStation(int carNumber, int stationNumber, int gateNumber) {
    std::string stationType = (stationNumber == 1) ? "station 1" : "station 2";
    std::cout << "Car No. " << carNumber << " is paying in gate " << gateNumber << " at " << stationType << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simular tiempo de pago
    std::cout << "Car No. " << carNumber << " is leaving payment gate " << gateNumber << " at " << stationType << "\n";
}

void carFlow(int carNumber) {
    std::cout << "Car No. " << carNumber << " waiting in line 1\n";

    {
        std::lock_guard<std::mutex> lock(station1Mutex);
        std::cout << "Car No. " << carNumber << " is paying in station 1\n";
        payAtStation(carNumber, 1, carNumber % numGatesStation1);
    }

    std::cout << "Car No. " << carNumber << " waiting in line 2\n";

  
    {
        std::lock_guard<std::mutex> lock(station2Mutex);
        std::cout << "Car No. " << carNumber << " is paying in station 2\n";
        payAtStation(carNumber, 2, carNumber % numGatesStation2);
    }
}

int main() {
    std::vector<std::thread> carThreads;

    for (int i = 0; i < numCars; ++i) {
        carThreads.emplace_back(carFlow, i);
    }

    for (auto& thread : carThreads) {
        thread.join();
    }

    return 0;
}