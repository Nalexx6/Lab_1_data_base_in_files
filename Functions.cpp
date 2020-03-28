//
// Created by Win10Pro on 26.01.2020.
//

#include "Functions.h"


void Functions::create_new_product() {

    cout << "Enter name\n";
    string Name_1;
    cin >> Name_1;

    cout << "Enter unit of measure (Press: k - kilos, l - litres , b - bunches,  p - pieces) \n";
    string Unit_1;
    char k;
    cin>>k;
    switch (k)  {
        case 'k' : Unit_1 = "kilos";
            break;
        case 'l' : Unit_1 = "litres";
            break;
        case 'b' : Unit_1 = "bunches";
            break;
        case 'p' : Unit_1 = "pieces";
            break;
        default: Unit_1 = "unknown";
    }


    cout << "Enter quantity\n";
    int Quantity_1;
    cin >> Quantity_1;

    cout<< "Press 0 if you want to use default date(defined by ctime), or 1 if you want to enter your own date\n";
    int key,Day, Month, Year, Hours, Mins, Seconds;
    cin>>key;

        time_t t;
        time(&t);
    tm *time = localtime(&t);
    if( key == 0) {
        Day = time->tm_mday;
        Month = time->tm_mon + 1;
        Year = time->tm_year + 1900;
    }
    else {
        cout<<"Enter date: day (1-31), month(1-12), year(2020-2029)\n";
        cin>>Day>>Month>>Year;
    }

    Hours = time->tm_hour;
    Mins = time->tm_min;
    Seconds = time->tm_sec;
    cout << "Date of production is " << asctime(time);
    cout << "Enter expiry period(days) \n";
    int Expiry_period_1;
    cin >> Expiry_period_1;


    auto *product = new Product (Product::id_1, Name_1, Unit_1, Quantity_1,
                                    Day, Month, Year, Hours, Mins, Seconds, Expiry_period_1, false);

    store.push_back(*product);
    //ar_id[product->id_1]++;


}

void Functions::save_all_products_from_memory_to_file(vector <Product> &vector1) {

    ofstream f_w("../Files/Products.txt", ios::app);
    ofstream f_b("../Files/Products_bin.txt", ios::binary | ios::app);
    ifstream f_r("../Files/Products.txt");
    string line;
    bool empty_file = true;
    if(getline(f_r, line))
        empty_file = false;
    f_r.close();
    int k =0;
    for(auto & i : vector1){

        if( !i.Been_saved) {

            i.save_to_file(f_w, empty_file);
            i.save_to_bin_file(f_b);
            empty_file = false;
            k++;

        }
    }

    cout << "All " << k << " unsaved products successfuly saved to files\n";

    f_w.close();
    f_b.close();
}

void Functions::print_all_data_from_file() {

    string line;
    ifstream f("../Files/Products.txt");
    cout<<"id\tName\tUnit\tQuantity\tDate\tTime\tExpiry period\n";
    while (!f.eof()) {

        getline(f, line);
        cout << line << '\n';

    }

    f.close();

}

void Functions::print_all_data_from_vector(vector <Product> &vector1) {

    cout<<"idV\tid\tName\tUnit\tQuantity\tDate\tTime\tExpiry period\n";

    for(unsigned int i = 0; i < vector1.size(); i++){

        cout<< i << '\t' << vector1[i].Id << "\t" << vector1[i].Name << "\t" << vector1[i].Unit << "\t"
        << vector1[i].Quantity << "\t" << vector1[i].Day << "." << vector1[i].Month << "." << vector1[i].Year << "\t" <<
        vector1[i].Hours << ":" << vector1[i].Mins << ":" << vector1[i].Seconds << "\t"
            << vector1[i].Expiry_period << "\n";

    }


}

void Functions::load_all_products_from_file(vector <Product> &vector1){

    ifstream f("../Files/Products.txt");
    string name, unit;
    int i = 0, id, quant, day, month, year, hours, mins, secs, exp_per;
    if(f.is_open()) {

        while (!f.eof() && Product::id_1 > 0) {


            f >> id >> name >> unit >> quant >> day >> month >> year >> hours >> mins >> secs >> exp_per;

            if (find_exact_pos_in_vector(vector1, id) != -1) {

                i++;
                vector1.insert(vector1.begin() + find_exact_pos_in_vector(vector1, id),
                        Product(id, name, unit, quant, day, month, year, hours, mins, secs, exp_per, true));

            }
        }

    }

    f.close();

    cout<< "All " << i << " unloaded products loaded to memory\n";

}

void Functions::load_all_products_from_binary_file(vector <Product> &vector1) {

    ifstream f ("../Files/Products_bin.txt", ios::binary);

    string name, unit;
    char ch;
    int i = 0, id, name_l, unit_l, quant, day, month, year, hours, mins, secs, exp_per, end_file;
    if(f.is_open()) {
        f.seekg(0, ios::end);
        end_file = f.tellg();
        f.seekg(0, ios::beg);
        while (f.tellg() != end_file) {
            f.read((char *) &id, sizeof(id));
            f.read((char *) &name_l, sizeof(name_l));
            for (int j = 0; j < name_l; j++) {

                f.get(ch);
                name += ch;

            }
            f.read((char *) &unit_l, sizeof(unit_l));
            for(int j = 0; j < unit_l; j++) {

                f.get(ch);
                unit += ch;

            }
            f.read((char *) &quant, sizeof(quant));
            f.read((char *) &day, sizeof(day));
            f.read((char *) &month, sizeof(month));
            f.read((char *) &year, sizeof(year));
            f.read((char *) &hours, sizeof(hours));
            f.read((char *) &mins, sizeof(mins));
            f.read((char *) &secs, sizeof(secs));
            f.read((char *) &exp_per, sizeof(exp_per));

            //cout << id << name_l << name << unit << quant << '\n';

            if (find_exact_pos_in_vector(vector1,id) != -1) {

                i++;
                vector1.insert(vector1.begin() + find_exact_pos_in_vector(vector1,id),Product(id, name, unit, quant,
                                           day, month, year, hours, mins, secs, exp_per, true));

            }

            name = "";
            unit = "";

        }
    }
    f.close();

    cout<< "All " << i << " unloaded products loaded to memory\n";

}

void Functions::print_all_data_from_binary_file() {

    ifstream f ("../Files/Products_bin.txt", ios::binary);

    string name, unit;
    char ch;
    int id, name_l, unit_l, quant, day, month, year, hours, mins, secs, exp_per, end_file;

    f.seekg(0, ios::end);
    end_file = f.tellg();
    f.seekg(0, ios::beg);
    cout<<"idV\tid\tName\tUnit\tQuantity\tDate\tTime\tExpiry period\n";
    while (f.tellg() != end_file) {
        f.read((char *) &id, sizeof(id));
        f.read((char *) &name_l, sizeof(name_l));
        for (int i = 0; i < name_l; i++) {

            f.get(ch);
            name += ch;

        }
        f.read((char *) &unit_l, sizeof(unit_l));
        for (int i = 0; i < unit_l; i++) {

            f.get(ch);
            unit += ch;

        }
        f.read((char *) &quant, sizeof(quant));
        f.read((char *) &day, sizeof(day));
        f.read((char *) &month, sizeof(month));
        f.read((char *) &year, sizeof(year));
        f.read((char *) &hours, sizeof(hours));
        f.read((char *) &mins, sizeof(mins));
        f.read((char *) &secs, sizeof(secs));
        f.read((char *) &exp_per, sizeof(exp_per));

        cout<< id << "\t" << name << "\t" << unit << "\t" << quant << "\t"
            << day << "." << month << "." << year << "\t" <<
            hours << ":" << mins << ":" << secs << "\t" << exp_per << "\n";

        name = "";
        unit = "";

    }

    f.close();

}

void Functions::create_N_random_products_and_append_them_to_memory(int &N) {

    int Id = 0;

    char alphabet[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for(int i = 1; i <= N; i++){

        string Name;
        int length = rand() % 3 + 4;
        for(int i = 0; i < length; i++){

            Name += alphabet[rand() % 52];
        }

        string Unit_1;
        short key = rand() % 4;
        //cout<< key <<'\t';
        switch (key)  {
            case 0 : Unit_1 = "kilos";
                    break;
            case 1 : Unit_1 = "litres";
                    break;
            case 2 : Unit_1 = "bunches";
                    break;
            case 3 : Unit_1 = "pieces";
                    break;
            default: Unit_1 = "unknown";
        }

        int Quantity = rand() % 51;

        time_t t;
        time (&t);
        tm* time = localtime(&t);
        int Day = rand() % 31 + 1;
        int Month = rand() % 12 + 1;
        int Year = rand() % 2 + 2019;
        int Hours = time->tm_hour;
        int Mins = time->tm_min;
        int Seconds = time->tm_sec;

        int Exp_per = rand() % 999 + 1;

        auto *product = new Product (Id, Name, Unit_1, Quantity,
                Day, Month, Year, Hours, Mins, Seconds, Exp_per, false);

        store.push_back(*product);


    }
    cout<<"\nAll " << N << " random products successfully created\n";

}

void Functions::delete_all_products_from_files() {

    ofstream f_1( "../Files/Products_bin.txt", ofstream::trunc);
    f_1.close();

    ofstream f( "../Files/Products.txt", ofstream::trunc);
    f.close();
    for(auto & i : store){

        i.Been_saved = false;
    }

}

void Functions::search_interactive() {

    this->load_all_products_from_file(store);
    this->print_all_data_from_vector(store);

    for (const auto & i : store){

        searched_1.push_back(i);
    }
    char response = 'y';
    char key;

    while(response == 'y') {

        cout<< "Please choose parameter (n - name, q - quantity, d - date of production)\n";

        cin>>key;
        if(key == 'n') {
            string name;
            cout << "Please enter the filter - beginning of name of products wanted to be found\n";
            cin >> name;
            this->search_by_name(name);
        }
         if(key == 'q') {
             char unit;
             cout << "Please enter the first filter - unit of measure of products wanted to be found\n"
                     "(k - kilos, l - litres, b - bunches, p - pieces)\n";
             cin >> unit;
             int top, bottom;
             cout
                     << "Please enter the second filter - bottom and upper bound of quantity of products wanted to be found\n";
             cin >> bottom >> top;
             this->search_by_quantity(unit, bottom, top);
         }
          if(key == 'd'){
                int day, month, year;
                cout<<"Please enter date: day (1-31), month(1-12), year(2020-2029)\n";
                cin>>day>>month>>year;
                this->search_by_date(day, month, year);
          }

        cout<<"Do you want to continue searching? (Press y to continue, or n to reset filters)\n";
        char k;
        cin>>k;
        response = k;
    }

    searched_1.clear();

}

void Functions::search_by_name(string &name) {

    for(int j = 0; j < searched_1.size(); j++){

            for(int k = 0; k < name.size(); k++) {

                if (searched_1[j].Name[k] != name[k]) {
                    searched_1.erase(searched_1.begin() + j);
                    j--;
                    break;

                }
            }

        }


    cout<<"There are all products which names begin from: "<< name<< '\n';
    print_all_data_from_vector(searched_1);

}

void Functions::search_by_quantity(char &unit, int &bottom, int &top) {

    string filter;
    switch (unit){
        case 'k': filter = "kilos";
            break;
        case 'l': filter = "litres";
            break;
        case 'b': filter = "bunches";
            break;
        case 'p': filter = "pieces";
            break;
        default: filter = "unknown";


    }

    for(int i = 0; i < searched_1.size(); i++){

        if(searched_1[i].Unit[0] != filter[0] || searched_1[i].Quantity > top || searched_1[i].Quantity < bottom){

            searched_1.erase(searched_1.begin() + i);
            i--;

        }

    }

    cout<< "There are all products which have quantity: " << bottom << '-'<< top << " in unit of measure"<<unit<<'\n';
    print_all_data_from_vector(searched_1);


}

void Functions::search_by_date(int &day, int &month, int &year) {

    for(unsigned int i = 0; i < searched_1.size(); i++){

        if(searched_1[i].Year > year){

            searched_1.erase(searched_1.begin() + i);
            i--;

        }
        else{
            if(searched_1[i].Year == year && searched_1[i].Month > month){

                searched_1.erase(searched_1.begin() + i);
                i--;

            } else{
                if(searched_1[i].Year == year && searched_1[i].Month == month && searched_1[i].Day > day){

                    searched_1.erase(searched_1.begin() + i);
                    i--;

                }
            }
        }
    }

    cout<< "There are all products which have been done before: "<< day<<':'<<month<<':'<<year<<'\n';
    print_all_data_from_vector(searched_1);


}

void Functions::delete_all_products_from_memory() {

    store.clear();
    cout<<"Memory is successfully cleared\n";

}

void Functions::delete_certain_product(char &source, int &idv) {

    if(source == 'f') {
        store.erase(store.begin() + bin_search(store, for_delete_update[idv].Id));
        for_delete_update.erase(for_delete_update.begin() + idv);
        cout << "Product successfully deleted\n";
    }
    if(source == 'm'){
        for_delete_update.erase(for_delete_update.begin() + bin_search(for_delete_update, store[idv].Id));
        store.erase(store.begin() + idv);
        cout << "Product successfully deleted\n";
    }


}

void Functions::update_certain_product_from_memory(char &source, vector <Product> &vector1, int &idv) {


    char key_1;
    string new_par;
    int new_p, day, month, year;
    cout << "Please enter parameter which you want to update:\n"
            "n - name, u - unit, q - quantity, d - date, e - expiry period\n";
    cin >> key_1;

    switch (key_1) {
        case 'n' :
            cout << "Enter new name:\n";
            cin >> new_par;
            vector1[idv].Name = new_par;
            break;
        case 'u' :
            cout << "Enter new unit of measure "
                    "(Press: k - kilos, l - litres , b - bunches,  p - pieces) \n";
            char k;
            cin >> k;
            switch (k) {
                case 'k' :
                    new_par = "kilos";
                    break;
                case 'l' :
                    new_par = "litres";
                    break;
                case 'b' :
                    new_par = "bunches";
                    break;
                case 'p' :
                    new_par = "pieces";
                    break;
                default: new_par = "unknown";

            }
            vector1[idv].Unit = new_par;
            break;
        case 'q' :
            cout << "Enter new quantity\n";
            cin >> new_p;
            vector1[idv].Quantity = new_p;
            break;
        case 'd' :
            cout << "Enter date: day (1-31), month(1-12), year(2020-2029)\n";
            cin >> day >> month >> year;
            vector1[idv].Day = day;
            vector1[idv].Month = month;
            vector1[idv].Year = year;
            break;
        case 'e' :
            cout << "Enter new expiry period(days)\n";
            cin >> new_p;
            vector1[idv].Expiry_period = new_p;
            break;
        default:
            break;
    }

    int idv_1;
    if(source == 'm'){
        idv_1 = bin_search(for_delete_update,vector1[idv].Id);
        for_delete_update[idv_1].Name = vector1[idv].Name;
        for_delete_update[idv_1].Unit = vector1[idv].Unit;
        for_delete_update[idv_1].Quantity = vector1[idv].Quantity;
        for_delete_update[idv_1].Day = vector1[idv].Day;
        for_delete_update[idv_1].Month = vector1[idv].Month;
        for_delete_update[idv_1].Year = vector1[idv].Year;
        for_delete_update[idv_1].Expiry_period = vector1[idv].Expiry_period;

    }
    if(source == 'f'){
        idv_1 = bin_search(store,vector1[idv].Id);
        store[idv_1].Name = vector1[idv].Name;
        store[idv_1].Unit = vector1[idv].Unit;
        store[idv_1].Quantity = vector1[idv].Quantity;
        store[idv_1].Day = vector1[idv].Day;
        store[idv_1].Month = vector1[idv].Month;
        store[idv_1].Year = vector1[idv].Year;
        store[idv_1].Expiry_period = vector1[idv].Expiry_period;

    }
    cout << "Product successfully updated\n";



}

void Functions::update_certain_product(char &source, int &idv) {

    if(source == 'f')
        this->update_certain_product_from_memory(source, for_delete_update, idv);
    if(source == 'm')
        this->update_certain_product_from_memory(source, store, idv);

}

 int Functions::find_exact_pos_in_vector(vector <Product> &vector1, int &id) {

    if(vector1.empty()){
        return 0;
    }
    int a = 0, b = vector1.size() - 1;
    int middle = 0;
    while(a <= b){
        middle = (a + b) / 2;
        if(vector1[middle].Id == id)
            return -1;
        if(vector1[middle].Id < id) {
            a = middle + 1;

        } else{
            b = middle - 1;

        }

    }
    if(middle + 1 == vector1.size()){
        return middle + 1;
    }
     return middle;


 }

int Functions::bin_search(vector <Product> &vector1, int &id) {


    if(vector1.empty()){
        return -1;
    }
    int a = 0, b = vector1.size() - 1;
    int middle = 0;
    while(a <= b){
        middle = (a + b) / 2;
        if(vector1[middle].Id == id)
            return middle;
        if(vector1[middle].Id < id) {
            a = middle + 1;

        } else{
            b = middle - 1;

        }

    }
//    if(middle + 1 == vector1.size()){
//        return middle + 1;
//    }
//    return middle;
    return -1;
}

void Functions::search_for_demo(string &name, char &unit, int &bottom, int &top, int &day, int &month, int &year) {

    load_all_products_from_file(store);
    print_all_data_from_vector(store);

    for (const auto & i : store){
        searched_1.push_back(i);
    }
    string cont;
    search_by_name(name);
    cout<<"cin anything to continue\n";
    cin>>cont;
    search_by_quantity(unit, bottom, top);
    cout<<"cin anything to continue\n";
    cin>>cont;
    search_by_date(day, month, year);
    cout<<"cin anything to continue\n";
    cin>>cont;

    searched_1.clear();
}

void Functions::update_for_demo(char &source, int &idv, string &name, string &unit, int &quantity,
                                int &day, int &month, int &year, int &exp_per) {

    load_all_products_from_file(for_delete_update);
    print_all_data_from_vector(store);
    int idv_1;
    if(source == 'm'){
        store[idv].Name = name;
        store[idv].Unit = unit;
        store[idv].Quantity = quantity;
        store[idv].Day = day;
        store[idv].Month = month;
        store[idv].Year = year;
        store[idv].Expiry_period = exp_per;
        idv_1 = bin_search(for_delete_update,store[idv].Id);
        for_delete_update[idv_1].Name = name;
        for_delete_update[idv_1].Unit = unit;
        for_delete_update[idv_1].Quantity = quantity;
        for_delete_update[idv_1].Day = day;
        for_delete_update[idv_1].Month = month;
        for_delete_update[idv_1].Year = year;
        for_delete_update[idv_1].Expiry_period = exp_per;

    }
    if(source == 'f'){
        for_delete_update[idv].Name = name;
        for_delete_update[idv].Unit = unit;
        for_delete_update[idv].Quantity = quantity;
        for_delete_update[idv].Day = day;
        for_delete_update[idv].Month = month;
        for_delete_update[idv].Year = year;
        for_delete_update[idv].Expiry_period = exp_per;
        idv_1 = bin_search(store, for_delete_update[idv].Id);
        store[idv_1].Name = name;
        store[idv_1].Unit = unit;
        store[idv_1].Quantity = quantity;
        store[idv_1].Day = day;
        store[idv_1].Month = month;
        store[idv_1].Year = year;
        store[idv_1].Expiry_period = exp_per;

    }
    cout << "Product successfully updated\n";



}

void Functions::search_by_name_for_bm(string &name) {

    for(int j = 0; j < store.size(); j++){
        int i = 0;
        for(int k = 0; k < name.size(); k++) {

            if (store[j].Name[k] != name[k]) {
                i++;
                break;

            }
        }
    if(i == 0)
        searched_1.push_back(store[j]);
    }


    cout<<"Number of products which names begin from: "<< name<<" is: "<<searched_1.size()<<'\n';

}

void Functions::search_by_quantity_for_bm(char &unit, int &bottom, int &top) {

    string filter;
    switch (unit){
        case 'k': filter = "kilos";
            break;
        case 'l': filter = "litres";
            break;
        case 'b': filter = "bunches";
            break;
        case 'p': filter = "pieces";
            break;
        default: filter = "unknown";


    }

    for(int i = 0; i < store.size(); i++){
        int j = 0;
        if(store[i].Unit[0] != filter[0] || store[i].Quantity > top || store[i].Quantity < bottom){

            j++;

        }
        if(j == 0)
            searched_1.push_back(store[i]);
    }

    cout<< "Number of products which have quantity: " << bottom << '-'<< top <<
    " in unit of measure "<<unit<<" is: "<<searched_1.size()<<'\n' ;


}

void Functions::search_by_date_for_bm(int &day, int &month, int &year) {

    for(int i = 0; i < store.size(); i++){
        int j = 0;
        if(store[i].Year > year){

            j++;

        }
        else{
            if(store[i].Year == year && store[i].Month > month){

                j++;


            } else{
                if(store[i].Year == year && store[i].Month == month && store[i].Day > day){

                    j++;


                }
            }
        }
        if(j == 0)
            searched_1.push_back(store[i]);
    }

    cout<< "Number of products which have been done before: "
        << day<<':'<<month<<':'<<year<<" is: "<< searched_1.size()<<'\n';

}

void Functions::sort_interactive() {


    string combination;
    for (const auto &i : store) {
        for_sort.push_back(i);
    }
    char response = 'y';
    while (response == 'y') {
        cout << "Please enter the combination of parameters by which you want to sort\n"
                "(enter your parameters without SPACE, and when you finish press ENTER)\n"
                "keys: n - name, u - unit, q - quantity, d - date, e - expiry period\n";
        cin >> combination;
        Sorts::sort_by_any_par(combination, for_sort, 0, for_sort.size() - 1);
        cout<<"This is result of sorting\n";
        print_all_data_from_vector(for_sort);
        cout<<"If you want to sort by another key, press 'y', press 'n' if you don`t\n";
        cin>>response;
    }
    for_sort.clear();

}

void Functions::sort_demo(string &key_1 , string& key_2) {

    string breakpoint;
    for (const auto &i : store) {
        for_sort.push_back(i);
    }
    cout<<"Now we will sort our elements by key: "<<key_1<<"\n"
                "cin any to continue\n";
    cin>>breakpoint;
    Sorts::sort_by_any_par(key_1, for_sort, 0, for_sort.size() - 1);
    print_all_data_from_vector(for_sort);
    cout<<"As we can see our memory is sorted by our key\n"
         "cin any to continue\n";
    cin>>breakpoint;
    cout<<"Now we will sort our elements by combination of keys: "<<key_2<<"\n"
            "cin any to continue\n";
    cin>>breakpoint;
    Sorts::sort_by_any_par(key_2, for_sort, 0, for_sort.size() - 1);
    print_all_data_from_vector(for_sort);
    cout<<"As we can see our memory is sorted by our combination\n"
          "cin any to continue\n";
    cin>>breakpoint;

}

clock_t Functions::sort_benchmark(string &key) {

    for(int i = 0; i < store.size(); i++){
        for_sort.push_back(store[i]);
    }
    clock_t start = clock();
    Sorts::sort_by_any_par(key, for_sort, 0, for_sort.size() - 1);
    clock_t end = clock();
    for_sort.clear();
    cout<<"Memory was sorted by key: "<<key<<"\n";
    return end - start;
}













