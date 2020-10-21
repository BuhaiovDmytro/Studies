//
// Created by dmytro on 17.10.20.
//

#include "submenu.h"

int safe_uint_input(){
    std::string s_input;
    std::cin >> s_input;

    int int_input;

    try {
        int_input = std::stoi(s_input);
        if(int_input < 0){
            throw std::invalid_argument(s_input);
        }
        else return int_input;
    }
    catch(std::invalid_argument&){
        std::cout << "\nERROR: Wrong input, must be integer above 0\n";
        return 0;
    }
}

void print_vec_str(const std::vector<std::string>& vec){
    for(auto & i : vec){
        std::cout << i << "\n";
    }
}

void insert_menu(PGconn *conn){
    std::cout << "\nChoose the table you want to insert the row:\n\n";

    std::vector<std::string> tab_names = get_tab_names(conn);
    print_vec_str(tab_names);

    std::cout << "\n>> ";
    std::string tab_name, col_val;
    std::cin >> tab_name;
    std::vector<std::string> col_names = get_col_names(conn, tab_name);
    std::vector<std::string> col_values;

    for(auto & col_name : col_names){
        std::cout  << "\nInput " << col_name << " of the " << tab_name << " >> ";
        std::cin >> col_val;
        col_values.push_back(col_val);
    }

    insert_row(conn, tab_name, col_values);
}

void delete_menu(PGconn *conn){
    std::cout << "\nChoose the table you want to delete the row:\n\n";

    std::vector<std::string> tab_names = get_tab_names(conn);
    print_vec_str(tab_names);

    std::cout << "\n>> ";
    std::string tab_name, del_val;
    std::cin >> tab_name;
    std::vector<std::string> col_names = get_col_names(conn, tab_name);
    std::cout  << "\nInput " << col_names.front() << " of the " << tab_name << " to delete" << " >> ";
    std::cin >> del_val;

    delete_row(conn, tab_name, col_names.front(), del_val);
}

void update_menu(PGconn *conn){

    std::cout << "\nChoose the table you want to update the row:\n\n";

    std::vector<std::string> tab_names = get_tab_names(conn);
    print_vec_str(tab_names);

    std::cout << "\n>> ";
    std::string tab_name, upd_col;
    std::cin >> tab_name;

    std::vector<std::string> col_names = get_col_names(conn, tab_name);
    std::cout  << "\nInput " << col_names.front() << " of the " << tab_name << " to update" << " >> ";
    std::string key_val;
    std::cin >> key_val;

    if(col_names.size() > 2) {
        std::cout << "\nChoose the column of the " << tab_name << " you want to update:\n";
        print_vec_str(col_names);
        std::cout << "\n\n>> ";
        std::cin >> upd_col;
    }
    else{
        upd_col = col_names.back();
    }

    std::cout << "\nInput new value of the " << upd_col << " >> ";
    std::string upd_val;
    std::cin >> upd_val;

    update_row(conn, tab_name, col_names.front(), key_val, upd_col, upd_val);
}

void generate_menu(PGconn *conn){
    std::cout << "\nChoose the table you want to generate rows:\n\n";

    std::vector<std::string> tab_names = get_tab_names(conn);
    print_vec_str(tab_names);

    std::cout << "\n>> ";
    std::string tab_name, upd_col;
    std::cin >> tab_name;

    std::cout << "\nInput quantity of rows to generate >> ";

    int num_rows_int = safe_uint_input();
    gen_rand_rows(conn, tab_name, num_rows_int);
}

int search_menu(PGconn *conn){
    std::cout << "\nInput quantity of attributes to search by >> ";

    int num_attrs_int = safe_uint_input();

    std::string subquery;
    std::vector<std::string> srch_col_names;

    for(int i = 1; i <= num_attrs_int; i++){

        std::cout  << "\nInput name of the attribute number " << i << " to search by" << " >> ";
        std::string col_name;
        std::cin >> col_name;
        srch_col_names.push_back(col_name);

        std::string col_type;
        col_type = get_col_type(conn, col_name);

        if(col_type == "integer"){
            std::cout  << "\nInput left integer limit of " << col_name << " to search by" << " >> ";
            int left_lim = safe_uint_input();
            std::cout  << "\nInput right integer limit of " << col_name << " to search by" << " >> ";
            int right_lim = safe_uint_input();
            if(left_lim > right_lim) {
                std::swap(left_lim, right_lim);
            }
            subquery.append(col_name);
            subquery.append(" >= '");
            subquery.append(std::to_string(left_lim));
            subquery.append("' AND ");
            subquery.append(col_name);
            subquery.append(" < '");
            subquery.append(std::to_string(right_lim));
            subquery.append("' AND ");
        }
        else if(col_type == "character varying" || col_type == "text"){
            std::cout  << "\nInput string for " << col_name << " to search by" << " >> ";
            std::string srch_str;
            std::cin >> srch_str;

            subquery.append(col_name);
            subquery.append(" LIKE '");
            subquery.append(srch_str);
            subquery.append("' AND ");
        }
        else if(col_type == "date"){
            std::cout  << "\nInput left date limit of " << col_name << " to search by" << " >> ";
            std::string left_lim;
            std::cin >> left_lim;
            std::cout  << "\nInput right date limit of " << col_name << " to search by" << " >> ";
            std::string right_lim;
            std::cin >> right_lim;

            subquery.append(col_name);
            subquery.append(" >= '");
            subquery.append(left_lim);
            subquery.append("' AND ");
            subquery.append(col_name);
            subquery.append(" < '");
            subquery.append(right_lim);
            subquery.append("' AND ");
        }
        else{
            std::cerr << "\nERROR: Unknown type: \"" << col_type << "\"\n";
        }
    }
    subquery.erase(subquery.size() - 4);//Remove last "AND "

    std::vector<std::string> tab_names = get_tab_names(conn);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(auto & tab_name : tab_names) {

        if(are_cols_in_tab(conn, srch_col_names, tab_name)) {

            std::vector<std::string> col_names = get_col_names(conn, tab_name);
            std::vector<std::vector<std::string>> srch_res = search_rows(conn, subquery, tab_name);

            std::cout << "\n";
            if(!srch_res.empty()) {
                std::cout << "\nTable: \"" << tab_name << "\"\n\n";
                for (auto &col_name : col_names) {
                    std::cout << col_name << "\t\t";
                }
                std::cout << "\n\n";
            }

            for(auto& row : srch_res){
                for(auto& col : row){
                    std::cout << col << "\t\t";
                }
                std::cout << "\n";
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "\nTime taken: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
    << "[ms]" << "\n";

    return 0;
}
