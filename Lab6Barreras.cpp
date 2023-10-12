#include <iostream>
#include <thread>
#include <vector>

struct Student {
    std::string name;
    float score;
};

float generateRandomScore() {
    return (rand() % 101) / 10.0; 
}

void printTopScores(const std::vector<Student>& students) {
    std::cout << "Los 10 mejores puntajes son:\n";
    for (int i = 0; i < 10 && i < students.size(); ++i) {
        std::cout << students[i].name << ": " << students[i].score << "\n";
    }
}

int main() {
    const int numStudents = 80;
    const int numThreads = 5; 
    std::vector<Student> students(numStudents);

    for (int i = 0; i < numStudents; ++i) {
        students[i].name = "Estudiante " + std::to_string(i + 1);
        students[i].score = generateRandomScore();
    }
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.score > b.score;
    });

    std::thread printThread(printTopScores, std::ref(students));
    printThread.join();

    return 0;
}