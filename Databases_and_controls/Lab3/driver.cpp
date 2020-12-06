#include <memory>
#include <iostream>

#include <odb/database.hxx>
#include <odb/transaction.hxx>

#include "database.h" // create_database

#include "submenu.h"
#include "server_context.h"


int main (int argc, char* argv[])
{
  try{
    std::unique_ptr<odb::database> db (create_database (argc, argv));

    while(true) {
        std::cout << "\n\nMain menu:";
        std::cout << "\n1. Insert row";
        std::cout << "\n2. Delete row";
        std::cout << "\n3. Update row";
        std::cout << "\n4. Quit";
        std::cout << "\n>> ";

        char main_menu;
        std::cin >> main_menu;

        switch (main_menu) {
            case '1': {
                odb::transaction tr( db->begin() );
                server_context ctx( tr );

                insert_menu(ctx);

                tr.commit();
                break;
            }
            case '2': {
                odb::transaction tr( db->begin() );
                server_context ctx( tr );

                delete_menu(ctx);

                tr.commit();
                break;
            }
            case '3': {
                odb::transaction tr( db->begin() );
                server_context ctx( tr );

                update_menu(ctx);

                tr.commit();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                std::cout << "\nERROR: Wrong input\n";
                break;
            }
        }
    }
  }
  catch (const odb::exception& e)
  {
      std::cerr << e.what () << std::endl;
      return 1;
  }
}

