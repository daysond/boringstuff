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
    
    int iter =  10000;
    int size = 1000000;

    double avl_t = 0;
    double map_t = 0;

    while(iter < size){
        t.reset();
        t.start();
        dbt.test_load(dbt.TestType::AVLTREE, iter);
        t.stop();

        avl_t = t.currtime(); 

        t.reset();
        t.start();
        dbt.test_load(dbt.TestType::MAP, iter);
        t.stop();

        map_t = t.currtime(); 

        writeToCSV("loadPerformance.csv", iter, map_t, avl_t);

        iter += 10000;
    }

    return 0;
}