//
// Created by dmytro on 13.10.20.
//

#include "db_operations.h"

void insert_row(PGconn *conn, const std::string& tab_name, const std::vector<std::string>& vec_params){

    std::string query = "INSERT INTO ";
    query.append(tab_name);
    query.append(" VALUES (");
    for(int i = 1; i <= vec_params.size(); i++){
        query.append("$");
        query.append(std::to_string(i));
        query.append(",");
    }
    query.pop_back();
    query.append(");");

    /*Converting vector to array*/
    std::vector<const char*> vec_char_params;
    vec_char_params.reserve(vec_params.size());
    for (auto & vec_param : vec_params){
        vec_char_params.push_back(vec_param.c_str());
    }
    const char** arr_params = new const char*[vec_char_params.size()];
    std::copy(vec_char_params.begin(), vec_char_params.end(), arr_params);

    PGresult *res = PQexecParams(conn, query.c_str(), vec_char_params.size(), nullptr, arr_params,
                       nullptr, nullptr, 0);

    if(PQresultStatus(res) != PGRES_COMMAND_OK) {
        PG_error_handler(conn, res, tab_name);
    }
    else{
        std::cout << "\nINSERT successful";
    }
    PQclear(res);
}

void delete_row(PGconn *conn, const std::string& tab_name, const std::string& col, const std::string& del_val){

    std::string query = "DELETE FROM ";
    query.append(tab_name);
    query.append(" WHERE ");
    query.append(col);
    query.append(" = '");
    query.append(del_val);
    query.append("' RETURNING *");

    PGresult *res = PQexec(conn, query.c_str());

    if(PQresultStatus(res) != PGRES_COMMAND_OK) {
        PG_error_handler(conn, res, tab_name);
    }

    PQclear(res);
}

void update_row(PGconn *conn, const std::string& tab_name, const std::string& key_col, const std::string& key_val,
                const std::string& upd_col, const std::string& upd_val){

    std::string query = "UPDATE ";
    query.append(tab_name);
    query.append(" SET ");
    query.append(upd_col);
    query.append(" = '");
    query.append(upd_val);
    query.append("'WHERE ");
    query.append(key_col);
    query.append(" = '");
    query.append(key_val);
    query.append("';");

    PGresult *res = PQexec(conn, query.c_str());

    if(PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cout << "\nERROR: No column \"" << upd_col << "\" in table \"" << tab_name << "\"\n";
    }
    else{
        std::cout << "\nUPDATE " << upd_col << " = " << upd_val <<  " successful";
    }

    PQclear(res);
}

void gen_rand_rows(PGconn * conn, const std::string& tab_name, int num_rows){
    std::vector<std::string> col_types = get_col_types(conn, tab_name);

    std::string query = "INSERT INTO ";
    query.append(tab_name);
    query.append(" SELECT ");

    for( auto & col_type : col_types){
        if(col_type == "integer"){
            query.append(" round(random()*999999999),");
        }
        else if(col_type == "character varying"){
            query.append(" chr(trunc(65 + random()*50000)::int) || chr(trunc(65 + random()*50000)::int) "
                         "|| chr(trunc(65 + random()*50000)::int),");
        }
        else if(col_type == "date"){
            query.append(" NOW() + (random() * (interval '90 days')) + '30 days',");
        }
        else {
            std::cerr << "\nERROR: Unknown type: \"" << col_type << "\"\n";
        }
    }
    query.pop_back();

    query.append(" FROM generate_series(1,");
    query.append(std::to_string(num_rows));
    query.append(")");

    PGresult *res = PQexec(conn, query.c_str());

    std::cout << "\n" << query << "\n";

    if(PQresultStatus(res) != PGRES_COMMAND_OK) {

        PG_error_handler(conn, res, tab_name);
    }
    else{
        std::cout << "\nGenerating " << num_rows << " rows " << "in " << tab_name << " successful";
    }

    PQclear(res);
}

std::vector<std::vector<std::string>> search_rows(
        PGconn *conn, const std::string& subquery, const std::string& tab_name){
    PGresult *res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PG_error_handler(conn, res, tab_name);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    std::string query = "DECLARE myportal CURSOR FOR SELECT * FROM ";
    query.append(tab_name);
    query.append(" WHERE ");
    query.append(subquery);

    res = PQexec(conn, query.c_str());

    std::cout << "\n" << query << "\n";

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        PG_error_handler(conn, res, tab_name);
        PQclear(res);
        exit_nicely(conn);
    }
    PQclear(res);

    res = PQexec(conn, "FETCH ALL in myportal");
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PG_error_handler(conn, res, tab_name);
        PQclear(res);
        exit_nicely(conn);
    }

    int nFields = PQnfields(res);
    std::vector<std::vector<std::string>> srch_res;

    for (int i = 0; i < PQntuples(res); i++)
    {
        std::vector<std::string> subvector;
        subvector.reserve(nFields);
        for (int j = 0; j < nFields; j++) {
            subvector.emplace_back(PQgetvalue(res, i, j));
        }
        srch_res.push_back(subvector);
    }

    PQclear(res);

    res = PQexec(conn, "CLOSE myportal");
    PQclear(res);

    res = PQexec(conn, "END");
    PQclear(res);

    return srch_res;
}



