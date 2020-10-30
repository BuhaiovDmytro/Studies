//
// Created by dmytro on 13.10.20.
//

#ifndef LAB2_DB_OPERATIONS_H
#define LAB2_DB_OPERATIONS_H

#include "iostream"
#include "psql_getters.h"
#include <vector>

void insert_row(PGconn *conn, const std::string& tab_name, const std::vector<std::string>& vec_params);
void delete_row(PGconn *conn, const std::string& tab_name, const std::string& column, const std::string& del_value);
void update_row(PGconn *conn, const std::string& tab_name, const std::string& key_col, const std::string& key_val,
                const std::string& upd_col, const std::string& upd_val);
void gen_rand_rows(PGconn * conn, const std::string& tab_name, int num_rows);
std::vector<std::vector<std::string>> search_rows( PGconn *conn, const std::string& subquery);

#endif //LAB2_DB_OPERATIONS_H
