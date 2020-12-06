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
    void insert( const std::shared_ptr< OdbT >& obj )
    {
        tr_.database().persist( *obj );
    }

    template< typename OdbT >
    void update( const std::shared_ptr< OdbT >& obj )
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
