#ifndef SQL_ORM_CLIENT_SUBMENU_H
#define SQL_ORM_CLIENT_SUBMENU_H

#include <algorithm>
#include <memory>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "database.h"
#include "orm_classes.h"
#include "server_context.h"


void insert_menu(server_context& ctx);
void delete_menu(server_context& ctx);
void update_menu(server_context& ctx);

#endif //SQL_ORM_CLIENT_SUBMENU_H
