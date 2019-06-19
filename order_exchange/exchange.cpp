//
// Created by frenchcommando on 6/7/2019.
//
#include <utility>
#include "exchange.h"


std::ostream &operator<<(std::ostream &strm, const InputOrder &a) {
    return strm << a.time << " " << a.client << " " << a.direction << " " << a.size << " " << a.type << " " << a.price;
}

InputOrder::InputOrder(TimeType time, ClientIdType client, DirectionType direction, SizeType size,
                       OrderType type, PriceType price) : time(std::move(time)), client(client), direction(direction), size(size),
                                                          type(type), price(price) {}

const TimeType &InputOrder::getTime() const {
    return time;
}

ClientIdType InputOrder::getClient() const {
    return client;
}

DirectionType InputOrder::getDirection() const {
    return direction;
}

SizeType InputOrder::getSize() const {
    return size;
}

OrderType InputOrder::getType() const {
    return type;
}

PriceType InputOrder::getPrice() const {
    return price;
}

std::string Book::view_execs() const {
    return execs.str();
}

std::string Book::view_order() const {
    return orders.str();
}

Book Book::build_from_string(std::string &s) {
    std::stringstream ss(s);
    Book b;
    std::string time;
    while (ss >> time){
        int client;
        ss >> client;
        char direction;
        ss >> direction;
        int size;
        ss >> size;
        char type;
        ss >> type;
        double price;
        ss >> price;
        InputOrder o (time, client, direction, size, type, price);
        b.add_order(o);
    }
    return b;
}

void Book::process_order(InputOrder &order) {
    // check if order matches
    // executes the order
    // add RestingOrder if applicable
    auto a = books[order.getDirection()];
    auto b = books[DirectionHelper::swap(order.getDirection())];
    if(a->check_order(order)){
        SizeType resting;
        if((resting = a->execute_order(order, execs)) != 0)
            b->append_order(RestingOrder(order.getClient(), resting), order.getPrice());
    }
    else{
        b->append_order(RestingOrder(order.getClient(), order.getSize()), order.getPrice());
    }
}

Book::Book()
: books({{'b', std::make_shared<AskDirectionBook>()}, {'s', std::make_shared<BidDirectionBook>()}}) {}

RestingOrder::RestingOrder(ClientIdType client, SizeType size) : client(client), size(size) {}

SizeType RestingOrder::getSize() const {
    return size;
}

ClientIdType RestingOrder::getClient() const {
    return client;
}
