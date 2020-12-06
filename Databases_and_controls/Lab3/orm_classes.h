#ifndef ORM_CLASSES_H
#define ORM_CLASSES_H

#include <string>
#include <cstddef>
#include <memory>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <odb/core.hxx>

#define DEFAULT_CAPACITY 0
#define DEFAULT_ADDRESS ""

class depot;
class trolleybus;
class route;
class where_serviced;
class service;

#pragma db object session
class depot
{
public:
    depot (const unsigned long& id,
           const std::string& address)
      : id_(id), address_ (address)
  {
  }

  const unsigned long& id () const
  {
    return id_;
  }

  const std::string& address () const
  {
    return address_;
  }

  void address (const std::string& address)
  {
        address_ = address;
  }

private:
  friend class odb::access;

    depot () {}

  std::string address_;

#pragma db id
    unsigned long id_;

#pragma db value_not_null inverse(depot_id_)
    std::weak_ptr<where_serviced> where_serviced_;
};

#pragma db object session
class trolleybus
{
public:
    trolleybus (
            const unsigned long& id,
           const unsigned long& capacity)
            :
            id_ (id),
            capacity_ (capacity)
    {
    }

    trolleybus () {
        id_ = 0;
        capacity_ = 0;
    }

    const unsigned long& id () const
    {
        return id_;
    }

    const unsigned long& capacity () const
    {
        return capacity_;
    }

    void capacity (const unsigned long& capacity)
    {
        capacity_ = capacity;
    }



private:
    friend class odb::access;

#pragma db id
    unsigned long id_;

    unsigned long capacity_;

#pragma db inverse(trolleybus_id_)
    std::vector<std::weak_ptr<where_serviced>> where_serviced_;

#pragma db inverse(trolleybus_id_)
    std::vector<std::weak_ptr<route>> route_;

#pragma db inverse(trolleybus_id_)
    std::weak_ptr<service> service_;

};

#pragma db object session pointer(std::shared_ptr)
class route
{
public:
    route (const unsigned long& number,
           const std::string& final_stops,
           const std::vector<std::shared_ptr<trolleybus>>& trolleybus_id)
            : number_ (number), final_stops_ (final_stops), trolleybus_id_ (trolleybus_id)
    {
    }

    const unsigned long& number () const
    {
        return number_;
    }

    const std::string& final_stops () const
    {
        return final_stops_;
    }

    void final_stops (const std::string& final_stops)
    {
        final_stops_ = final_stops;
    }

    const std::vector<std::shared_ptr<trolleybus>>& trolleybus_id () const
    {
        return trolleybus_id_;
    }

private:
    friend class odb::access;

    route () {}

#pragma db id
    unsigned long number_;

    std::string final_stops_;

#pragma db value_not_null unordered
    std::vector<std::shared_ptr<trolleybus>> trolleybus_id_;
};

#pragma db object session pointer(std::shared_ptr)
class where_serviced
{
public:
    where_serviced (
            const std::shared_ptr<trolleybus>& trolleybus_id,
           const std::shared_ptr<depot>& depot_id)
            :
            trolleybus_id_ (trolleybus_id),
            depot_id_ (depot_id)
    {
    }

    const std::shared_ptr<trolleybus>& trolleybus_id () const
    {
        return trolleybus_id_;
    }

    const std::shared_ptr<depot>& depot_id () const
    {
        return depot_id_;
    }

    void depot_id (const std::shared_ptr<depot>& depot_id)
    {
        depot_id_ = depot_id;
    }

private:
    friend class odb::access;

    where_serviced () {}

#pragma db id auto
    unsigned long id_;

#pragma db not_null
    std::shared_ptr<trolleybus> trolleybus_id_;

#pragma db not_null
    std::shared_ptr<depot> depot_id_;

};

#pragma db object session pointer(std::shared_ptr)
class service
{
public:
    service (
            const std::shared_ptr<trolleybus>& trolleybus_id,
            const boost::gregorian::date& next)
            :
            trolleybus_id_ (trolleybus_id),
            next_ (next)
    {
    }

    const std::shared_ptr<trolleybus>& trolleybus_id () const
    {
        return trolleybus_id_;
    }

    const boost::gregorian::date& next () const
    {
        return next_;
    }

    void next (const boost::gregorian::date& next)
    {
        next_ = next;
    }

private:
    friend class odb::access;

    service () {}

#pragma db id auto
    unsigned long id_;

#pragma db not_null
    std::shared_ptr<trolleybus> trolleybus_id_;

#pragma db not_null
    boost::gregorian::date next_;
};

#endif // ORM_CLASSES_H