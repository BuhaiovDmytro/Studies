//
// Created by dmytro on 17.10.20.
//

#ifndef LAB2_SUBMENU_H
#define LAB2_SUBMENU_H

#include <algorithm>
#include <libpq-fe.h>
#include <ctime>
#include <chrono>
#include "db_operations.h"

void insert_menu(PGconn *conn);
void delete_menu(PGconn *conn);
void update_menu(PGconn *conn);
void generate_menu(PGconn *conn);
int search_menu(PGconn *conn);

#endif //LAB2_SUBMENU_H
