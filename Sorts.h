//
// Created by Win10Pro on 22.03.2020.
//

#ifndef LAB_1_DATA_BASE_IN_FILES__SORTS_H
#define LAB_1_DATA_BASE_IN_FILES__SORTS_H

#include "Product.h"

class Sorts {

private:

    //Auxiliary

    static int limit;
    static int compare_string(string& a, string& b);
    static int compare_int(int& a, int& b);
    static int compare_date(Product& a, Product& b);
    static int compare_product(Product& a, Product& b, string& key);

    //Sorts

    static void counting_sort_for_unit(vector <Product> &vector1);
    static void radix_sort_for_exp_per(vector <Product> &vector1);
    static void insertion_sort(vector <Product> &vector1, int lo, int hi, string &key);
    static void merge(vector <Product> &vector1, vector <Product> &for_merge, int lo, int mid, int hi, string& key);
    static void sort(vector<Product> &vector1, vector <Product> &for_merge, int lo, int hi, string &key);
    static void smart_merge_sort_for_memory(vector <Product> &vector1, int lo, int hi, string& key);

public:
    static void sort_by_any_par(string& key, vector <Product> &vector1, int lo, int hi);
    //void rewrite_id_after_sort(vector <Product> &vector1);

};


#endif //LAB_1_DATA_BASE_IN_FILES__SORTS_H
