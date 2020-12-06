#ifndef SQL_ORM_CLIENT_SERVER_CONTEXT_H
#define SQL_ORM_CLIENT_SERVER_CONTEXT_H

#include <odb/database.hxx>
#include "orm_classes_odb.h"

class server_context
{
public:
    explicit server_context( odb::transaction& tr )
            : tr_( tr )
    {}

    template< typename OdbT >
    void insert_row( const std::shared_ptr< OdbT >& obj )
    {
        tr_.database().persist( *obj );
    }

    template< typename OdbT >
    void delete_row( const unsigned long& id)
    {
        tr_.database().erase<OdbT>( id );
    }

    template< typename OdbT >
    void update_row( const std::shared_ptr< OdbT >& obj )
    {
        tr_.database().update( *obj );
    }

    odb::transaction& transaction()
    {
        return tr_;
    }

private:
    odb::transaction& tr_;
};

#endif //SQL_ORM_CLIENT_SERVER_CONTEXT_H
