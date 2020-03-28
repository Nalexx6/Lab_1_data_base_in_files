//
// Created by Win10Pro on 26.01.2020.
//

#ifndef LAB_1_DATA_BASE_IN_FILES__FUNCTIONS_H
#define LAB_1_DATA_BASE_IN_FILES__FUNCTIONS_H

#include "Product.h"
//3b Lab
#include "Sorts.h"

class Functions {

private:

public:

    //Memory

    vector <Product> store = {};
    vector <Product> searched_1 = {};
    vector <Product> for_delete_update = {};
    //3b lab (sort)
    vector <Product> for_sort = {};

    //Functions

    void create_new_product();
    void static save_all_products_from_memory_to_file(vector <Product> &vector1);
    void static print_all_data_from_file();
    void static print_all_data_from_binary_file();
    void static print_all_data_from_vector(vector <Product> &vector1);
    void static load_all_products_from_file(vector <Product> &vector1);
    void static load_all_products_from_binary_file(vector <Product> &vector1);
    void create_N_random_products_and_append_them_to_memory(int &N);
    void delete_all_products_from_files();
    void delete_all_products_from_memory();
    void delete_certain_product(char &source, int &idV);
    void search_interactive();
    void search_by_name(string &name);
    void search_by_quantity(char &unit, int &bottom, int &top);
    void search_by_date(int &day, int &month, int &year);
    void update_certain_product_from_memory(char &source,vector <Product> &vector1, int &idv);
    void update_certain_product(char &source, int &idv);
    int static find_exact_pos_in_vector(vector <Product> &vector1, int &id);
    int static bin_search(vector <Product> &vector1, int &id);
    void search_for_demo(string &name, char &unit, int &bottom, int &top, int &day, int &month, int &year);
    void update_for_demo(char &source, int &idv, string &name, string &unit, int &quantity,
            int &day, int &month, int &year, int &exp_per);
    void search_by_name_for_bm(string &name);
    void search_by_quantity_for_bm(char &unit, int &bottom, int &top);
    void search_by_date_for_bm(int &day, int &month, int &year);
    void sort_interactive();
    void sort_demo(string& key_1, string& key_2);
    clock_t sort_benchmark(string& key);

};

/*Need to be fixed


 */


#endif //LAB_1_DATA_BASE_IN_FILES__FUNCTIONS_H
