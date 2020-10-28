//
// Created by dmytro on 13.10.20.
//

#ifndef LAB2_PSQL_GETTERS_H
#define LAB2_PSQL_GETTERS_H

#include <libpq-fe.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

PGconn* psql_init();
void exit_nicely(PGconn *conn);
std::vector<std::string> get_tab_names(PGconn *conn);
std::vector<std::string> get_col_names(PGconn *conn, const std::string& table);
std::vector<std::string> get_col_types(PGconn *conn, const std::string& table);
std::string get_col_type(PGconn *conn, const std::string& col_name);
bool are_cols_in_tab(PGconn *conn, std::vector<std::string> cols, const std::string& tab);
void PG_error_handler(PGconn *conn, PGresult *res, const std::string& tab_name = "");

#endif //LAB2_PSQL_GETTERS_H
