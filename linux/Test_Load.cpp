#include "DBTesting.cpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool exists(std::string path) {
    ifstream file;
    return file.good();
}

void writeToCSV(std::string filename, int iterations, double mapTime,
                double avlTime) {
    bool fileExists = exists(filename);
<<<<<<< HEAD

    ios_base::openmode mode = exists(filename) ? ios::trunc : ios::app;
    std::ofstream csv(filename, mode);
=======
    std::ofstream csv(filename, ios::app);
>>>>>>> test-map

    if (csv.is_open() && !fileExists)
        csv << "iterations, map_time_taken, avl_time_taken\n";

    if (csv.is_open())
        csv << iterations << "," << mapTime << "," << avlTime << "\n";
    else
        cout << "Error opening file \n";

    csv.close();
}

ofstream outfile;

int main() {
    DBTesting dbt;
    Timer t;
    
    int iter =  10000;
    int size = 1000000;
    int idx = 0;

    double avl_t = 0;
    double map_t = 0;

    while (idx < size) {
        t.reset();
        t.start();
        dbt.test_load(TestType::AVLTREE, iter);
        t.stop();

        avl_t = t.starttime() - t.currtime();

        t.reset();
        t.start();
        dbt.test_load(TestType::MAP, iter);
        t.stop();

        map_t = t.starttime() - t.currtime();

        writeToCSV("loadPerformance.csv", iter, map_t, avl_t);
        idx++;
        iter += 10000;
    }

    std::cout << "Press enter to continue...";
    std::cin.get();

    std::cout << "All load tests done.\n";

    return 0;
}