//
// Created by dmytro on 13.10.20.
//

#include "psql_getters.h"

#define PG_UNDEFINED_TABLE "42P01"
#define PG_FOREIGN_KEY_VIOLATION "23503"
#define PG_UNIQUE_KEY_VIOLATION "23505"

PGconn* psql_init(){
    //TODO: Hide password
    PGconn *conn = PQconnectdb("user = postgres password = kukurudza25 host = 127.0.0.1 dbname = postgres");

    if (PQstatus(conn) != CONNECTION_OK)
    {
        std::cerr << "ERROR: No connection to database" ;
        exit_nicely(conn);
    }

    return conn;
}

void exit_nicely(PGconn *conn)
{
    PQfinish(conn);
    exit(1);
}

std::vector<std::string> get_tab_names(PGconn *conn){

    PGresult *res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        std::cerr << "BEGIN command failed: " << PQerrorMessage(conn);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    res = PQexec(conn, "DECLARE myportal CURSOR FOR SELECT tablename FROM pg_tables"
                       " WHERE schemaname = 'public'");

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        std::cerr << "DECLARE CURSOR failed: " << PQerrorMessage(conn);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    res = PQexec(conn, "FETCH ALL in myportal");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cerr << "FETCH ALL failed: " << PQerrorMessage(conn);
        PQclear(res);
        exit_nicely(conn);
    }

    int nFields = PQnfields(res);
    std::vector<std::string> tab_names;

    for (int i = 0; i < PQntuples(res); i++)
    {
        for (int j = 0; j < nFields; j++) {
            tab_names.emplace_back(PQgetvalue(res, i, j));
        }
    }

    PQclear(res);

    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    res = PQexec(conn, "END");
    PQclear(res);

    return tab_names;
}

std::vector<std::string> get_col_names(PGconn *conn, const std::string& table){
    PGresult *res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PG_error_handler(conn, res, table);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    std::string query = "DECLARE myportal CURSOR FOR SELECT * FROM public.";
    query.append(table);
    query.append(" WHERE false");

    res = PQexec(conn, query.c_str());

    std::vector<std::string> col_names;

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PG_error_handler(conn, res, table);
        PQclear(res);
        return col_names;
    }
    PQclear(res);

    res = PQexec(conn, "FETCH ALL in myportal");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PG_error_handler(conn, res, table);
        PQclear(res);
    }

    int nFields = PQnfields(res);
    col_names.reserve(nFields);
    for (int i = 0; i < nFields; i++) {
        col_names.emplace_back(PQfname(res, i));
    }

    PQclear(res);

    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    res = PQexec(conn, "END");
    PQclear(res);

    return col_names;
}

std::vector<std::string> get_col_types(PGconn *conn, const std::string& table){//TODO: ERROR HANDLING
    PGresult *res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PG_error_handler(conn, res, table);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    std::string query = "DECLARE myportal CURSOR FOR SELECT data_type\n"
                        "FROM INFORMATION_SCHEMA.COLUMNS\n"
                        "WHERE TABLE_NAME = '";
    query.append(table);
    query.append("'");

    res = PQexec(conn, query.c_str());


    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PG_error_handler(conn, res, table);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    res = PQexec(conn, "FETCH ALL in myportal");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PG_error_handler(conn, res, table);
        PQclear(res);
        exit_nicely(conn);
    }

    std::vector<std::string> col_names;
    int nFields = PQnfields(res);

    for (int i = 0; i < PQntuples(res); i++)
    {
        for (int j = 0; j < nFields; j++) {
            col_names.emplace_back(PQgetvalue(res, i, j));
        }
    }

    PQclear(res);

    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    res = PQexec(conn, "END");
    PQclear(res);

    return col_names;
}

std::string get_col_type(PGconn *conn, const std::string& col_name){
    PGresult *res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PG_error_handler(conn, res);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    std::string query = "DECLARE myportal CURSOR FOR SELECT data_type\n"
                        "FROM INFORMATION_SCHEMA.COLUMNS\n"
                        "WHERE COLUMN_NAME = '";
    query.append(col_name);
    query.append("'");

    res = PQexec(conn, query.c_str());


    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PG_error_handler(conn, res);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    res = PQexec(conn, "FETCH ALL in myportal");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PG_error_handler(conn, res);
        PQclear(res);
        exit_nicely(conn);
    }

    std::string col_type = PQgetvalue(res, 0, 0);

    PQclear(res);

    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    res = PQexec(conn, "END");
    PQclear(res);

    return col_type;
}

bool are_cols_in_tab(PGconn *conn, std::vector<std::string> cols, const std::string& tab){

    std::vector<std::string> cols_in_tab = get_col_names(conn, tab);

    return std::includes(cols_in_tab.begin(), cols_in_tab.end(),
                         cols.begin(), cols.end());
}

void PG_error_handler(PGconn *conn, PGresult *res, const std::string& tab_name){

    if(strcmp(PQresultErrorField(res, PG_DIAG_SQLSTATE), PG_UNDEFINED_TABLE) == 0){
        std::cout << "\nERROR: No table with the name \"" << tab_name << "\"";
    }
    else if(strcmp(PQresultErrorField(res, PG_DIAG_SQLSTATE), PG_FOREIGN_KEY_VIOLATION) == 0){
        std::cout << "\nERROR: Some generated fields of \"" << tab_name << "\" do not exist in table it depends on";
    }
    else if(strcmp(PQresultErrorField(res, PG_DIAG_SQLSTATE), PG_UNIQUE_KEY_VIOLATION) == 0){
        std::cout << "\nERROR: Fields of \"" << tab_name << "\" must be unique";
    }
    else {
        std::cerr << PQerrorMessage(conn);
    }
}