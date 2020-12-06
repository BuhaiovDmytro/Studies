#include "submenu.h"

std::vector<std::string> db_tab_names = {
        "trolleybus",
        "depot",
        "route",
        "where_serviced",
        "service"
};

int safe_uint_input(){
    std::string s_input;
    std::cin >> s_input;

    int int_input;

    try {
        int_input = std::stoi(s_input);
        if(int_input < 0){
            throw std::invalid_argument(s_input);
        }
        return int_input;
    }
    catch(std::invalid_argument&){
        std::cout << "\nERROR: Wrong input, must be integer above 0\n";
        return 0;
    }
}

void print_vec_str(const std::vector<std::string>& vec){
    for(auto & row : vec){
        std::cout << row << "\n";
    }
}

void insert_menu(server_context& ctx){
    std::cout << "\nChoose the table you want to insert the row:\n\n";

    print_vec_str(db_tab_names);

    std::cout << "\n>> ";
    std::string tab_name;
    std::cin >> tab_name;

    if(tab_name == "trolleybus"){
        std::cout << "\nInput trolleybus id >> ";
        int tr_id = safe_uint_input();
        std::cout << "\nInput trolleybus capacity >> ";
        int tr_capacity = safe_uint_input();

        ctx.insert_row(std::make_shared<trolleybus>(tr_id, tr_capacity));
    }
    else if(tab_name == "depot"){
        std::cout << "\nInput depot id >> ";
        int dep_id = safe_uint_input();

        std::cout << "\nInput depot address >> ";
        std::string dep_addr;
        std::cin >> dep_addr;

        ctx.insert_row(std::make_shared<depot>(dep_id, dep_addr));
    }
    else if(tab_name == "route"){
        std::cout << "\nInput number of the route >> ";
        int route_num = safe_uint_input();

        std::cout << "\nInput final stops >> ";
        std::string fin_stops;
        std::cin >> fin_stops;

        std::cout << "\nInput quantity of trolleybuses to serve the route >> ";
        int tr_num = safe_uint_input();

        std::vector<int> tr_ids;
        int input;
        for(int i = 1; i <= tr_num; i++){
            std::cout << "\nInput id of trolleybus to serve the route (" << i << "/"<< tr_num << ") >> ";
            input = safe_uint_input();
            tr_ids.push_back(input);
        }

        std::vector<std::shared_ptr<trolleybus>> tr_obj_vec;
        tr_obj_vec.reserve(tr_ids.size());
        for(auto & tr_id : tr_ids){
            tr_obj_vec.push_back(std::make_shared<trolleybus>(tr_id, DEFAULT_CAPACITY));
        }
        ctx.insert_row(std::make_shared<route>(route_num, fin_stops, tr_obj_vec));
    }
    else if(tab_name == "where_serviced") {
        std::cout << "\nInput id of the trolleybus to serve in the depot >> ";
        int tr_id = safe_uint_input();

        std::cout << "\nInput id of the depot >> ";
        int dep_id = safe_uint_input();

        ctx.insert_row(std::make_shared<where_serviced>(
                std::make_shared<trolleybus>(tr_id, DEFAULT_CAPACITY),
                        std::make_shared<depot>(dep_id, DEFAULT_ADDRESS)));
    }
    else if(tab_name == "service") {
        std::cout << "\nInput id of the trolleybus >> ";
        int tr_id = safe_uint_input();

        std::cout << "\nInput day of the next service >> ";
        int d_input = safe_uint_input();
        std::cout << "\nInput month of the next service >> ";
        int m_input = safe_uint_input();
        std::cout << "\nInput year of the next service >> ";
        int y_input = safe_uint_input();

        ctx.insert_row(std::make_shared<service>(
                std::make_shared<trolleybus>(tr_id, DEFAULT_CAPACITY),
                boost::gregorian::date(y_input,m_input,d_input)));
    }
    else{
        std::cout << "\nError: No such table\n";
    }
}

void delete_menu(server_context& ctx){
    std::cout << "\nChoose the table you want to delete the row:\n\n";

    print_vec_str(db_tab_names);

    std::cout << "\n>> ";
    std::string tab_name;
    std::cin >> tab_name;

    if(tab_name == "trolleybus"){
        std::cout << "\nInput trolleybus id >> ";
        unsigned long tr_id = safe_uint_input();

        ctx.delete_row<trolleybus>(tr_id);
    }
    else if(tab_name == "depot"){
        std::cout << "\nInput depot id >> ";
        unsigned long dep_id = safe_uint_input();

        ctx.delete_row<depot>(dep_id);
    }
    else if(tab_name == "route"){
        std::cout << "\nInput rote number >> ";
        unsigned long route_num = safe_uint_input();

        ctx.delete_row<route>(route_num);
    }
    else if(tab_name == "where_serviced") {
        std::cout << "\nInput row id >> ";
        unsigned long row_id = safe_uint_input();

        ctx.delete_row<where_serviced>(row_id);
    }
    else if(tab_name == "service") {
        std::cout << "\nInput row id >> ";
        unsigned long row_id = safe_uint_input();

        ctx.delete_row<service>(row_id);
    }
    else{
        std::cout << "\nError: No such table\n";
    }
}

void update_menu(server_context& ctx){

}