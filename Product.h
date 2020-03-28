//
// Created by Win10Pro on 25.01.2020.
//

#ifndef LAB_1_DATA_BASE_IN_FILES__PRODUCTS_H
#define LAB_1_DATA_BASE_IN_FILES__PRODUCTS_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>


using namespace std;
class Product {

private:

public:

    //Variables

    string Name;
    string Unit;
    int Quantity;
    int Day;
    int Month;
    int Year;
    int Hours;
    int Mins;
    int Seconds;
    int Expiry_period;
    int Id;
    bool Been_saved;

    static int id_1;

    Product (int Id, string &Name, string &Unit, int Quantity,
             int Day, int Month, int Year, int Hours, int Mins, int Seconds, int Expiry_period, bool Been_saved);

    //Functions

    static void define_id();
    void save_to_file(ofstream &f, bool empty);
    void save_to_bin_file(ofstream &f);

};


#endif //LAB_1_DATA_BASE_IN_FILES__PRODUCTS_H
