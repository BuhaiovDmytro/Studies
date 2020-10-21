//
// Created by dmytro on 13.10.20.
//

#include <libpq-fe.h>
#include "psql_getters.h"
#include "submenu.h"

int main()
{
    PGconn *conn = psql_init();

    while(true) {
        std::cout << "\n\nMain menu:";
        std::cout << "\n1. Insert row";
        std::cout << "\n2. Delete row";
        std::cout << "\n3. Update row";
        std::cout << "\n4. Generate random rows";
        std::cout << "\n5. Search rows";
        std::cout << "\n6. Quit";
        std::cout << "\n>> ";
        char main_menu;
        std::cin >> main_menu;
        switch (main_menu) {
            case '1': {
                insert_menu(conn);
                break;
            }
            case '2': {
                delete_menu(conn);
                break;
            }
            case '3': {
                update_menu(conn);
                break;
            }
            case '4': {
                generate_menu(conn);
                break;
            }
            case '5': {
                search_menu(conn);
                break;
            }
            case '6': {
                exit_nicely(conn);
                PQfinish(conn);
                return 0;
            }
            default: {
                std::cout << "\nERROR: Wrong input\n";
                break;
            }
        }
    }
}





