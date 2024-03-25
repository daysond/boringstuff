#include <iostream>
#include <fstream>
#include <string>
#include "DBTesting.cpp"

using namespace std;

bool exists(std::string path){
    ifstream file;
    return file.good();
}

void writeToCSV(std::string filename,  int iterations, double mapTime, double avlTime) {
    bool fileExists = exists(filename);
    std::ofstream csv(filename, ios::app);

    if(csv.is_open() && !fileExists)
        csv << "iterations, map_time_taken, avl_time_taken\n";
    
    if (csv.is_open()) 
        csv << iterations << "," << mapTime << "," << avlTime << "\n"; 
    else 
        cout << "Error opening file \n";

    csv.close();
}

ofstream outfile;

int main(){
    DBTesting dbt;
    Timer t;
    int size = 3;
    int iter[size] = {100, 500, 1000};
    int idx = 0;

    double avl_t = 0;
    double map_t = 0;

    while(idx < size){
        t.reset();
        t.start();
        dbt.test_load(dbt.TestType::AVLTREE, iter[idx]);
        t.stop();

        avl_t = t.starttime() - t.currtime(); 

        t.reset();
        t.start();
        dbt.test_load(dbt.TestType::MAP, iter[idx]);
        t.stop();

        map_t = t.starttime() - t.currtime(); 

        writeToCSV("loadPerformance.csv", iter[idx], map_t, avl_t);
    }

    return 0;
}