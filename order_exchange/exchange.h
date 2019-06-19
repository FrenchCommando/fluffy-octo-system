//
// Created by frenchcommando on 6/7/2019.
//

#ifndef PERSOTOOLS_EXCHANGE_H
#define PERSOTOOLS_EXCHANGE_H

#include <string>
#include <deque>
#include <map>
#include <sstream>
#include <memory>


using TimeType = std::string; // no need to bother about conversion - inputs are ordered anyways
using ClientIdType = int; // id of client - could be a string
using DirectionType = char; // buy of sell
using SizeType = size_t; // number of shares
using OrderType = char; // market order or limit order
using PriceType = double; // smaller difference being 1 cent
                        // - it should behave like a int representing the number of cents


struct DirectionHelper{
    static DirectionType swap(const DirectionType& d){
        if (d == 'b')
            return 's';
        if (d == 's')
            return 'b';
        throw std::logic_error("Direction is neither buy or sell");
    }
};

class InputOrder{
    TimeType time;
    ClientIdType client;
    DirectionType direction;
    SizeType size;
    OrderType type;
    PriceType price;
public:
    InputOrder(TimeType time, ClientIdType client, DirectionType direction, SizeType size, OrderType type,
               PriceType price);

    const TimeType &getTime() const;

    ClientIdType getClient() const;

    DirectionType getDirection() const;

    SizeType getSize() const;

    OrderType getType() const;

    PriceType getPrice() const;

    // this is usually the only time you see the friend keyword
    friend std::ostream& operator<<(std::ostream &strm, const InputOrder &a);
};

std::ostream& operator<<(std::ostream &strm, const InputOrder &a);


class RestingOrder{
    ClientIdType client;
    SizeType size;
public:
    RestingOrder(ClientIdType client, SizeType size);

    ClientIdType getClient() const;

    SizeType getSize() const;

    void reduce_size(SizeType size){
        this->size -= size;
    }
};

// let's build an exchange
class DirectionBook{
protected:
    virtual SizeType get_level(PriceType price) const = 0;
    virtual void increase_level_size(PriceType price, SizeType size) = 0;
    virtual void decrease_level_size(PriceType price, SizeType size) = 0;
    virtual void empty_level_size(PriceType price) = 0;
    virtual SizeType get_available_size(PriceType price) const = 0;
    virtual PriceType nextPrice(PriceType price) = 0; // 0 if empty
    virtual std::deque<RestingOrder>& get_book_content(PriceType price) = 0;
    virtual void execute(const InputOrder & input_order, RestingOrder & resting_order, PriceType price, std::ostream& stream) = 0;
    virtual void execute_partial(const InputOrder & input_order, RestingOrder & resting_order, PriceType price, SizeType size, std::ostream& stream) = 0;
    virtual void emplace_order_to_price(const RestingOrder& order, PriceType price) = 0;

public:
    bool check_order(const InputOrder& order) const{
        const auto available_size = get_available_size(order.getPrice());
        if (available_size > 0)
            return true;
        // for FOC order
        return available_size >= order.getSize();
    } // returns true if anything has to be executed
    SizeType execute_order(const InputOrder& order, std::ostream& stream){
        const auto price = order.getPrice();
        auto remaining_size = order.getSize();
        PriceType exec_price;
        while ((exec_price = nextPrice(price)) != 0 and remaining_size > 0){
            if (remaining_size >= get_level(exec_price)){
                remaining_size -= get_level(exec_price);
                empty_level_size(exec_price);
                auto l = get_book_content(exec_price);
                while (not l.empty()){
                    auto u = l.front();
                    l.pop_front();
                    execute(order, u, exec_price, stream);
                }
            }
            else{
                auto& l = get_book_content(exec_price);
                while (not l.empty() and remaining_size > 0){
                    auto& u = l.front();
                    SizeType size;
                    if ((size = u.getSize()) <= remaining_size){
                        l.pop_front();
                        execute(order, u, exec_price, stream);
                        decrease_level_size(exec_price, size);
                        remaining_size -= size;
                    }
                    else{
                        execute_partial(order, u, exec_price, remaining_size, stream);
                        decrease_level_size(exec_price, remaining_size);
                        remaining_size = 0;
                        break;
                    }
                }
                break;
            }
        }
        return remaining_size;
    } // executes the order - returns potential resting size
    void append_order(const RestingOrder& order, PriceType price){
        emplace_order_to_price(order, price);
        increase_level_size(price, order.getSize());
    } // appends resting order to book
};

class AskDirectionBook: public DirectionBook{
protected:
    SizeType get_level(PriceType price) const override{
        return level_size.at(price);
    }
    void increase_level_size(PriceType price, SizeType size) override {
        level_size[price] += size;
    }

    void decrease_level_size(PriceType price, SizeType size) override {
        level_size[price] -= size;
    }

    void empty_level_size(PriceType price) override {
        level_size.erase(price);
    }

    SizeType get_available_size(PriceType price) const override {
        auto p = level_size.begin();
        const auto p_price = level_size.lower_bound(price);
        SizeType s = 0; // initialisation redundant
        while(p != p_price){
            s += (p++)->second;
        }
        return s;
    }

    PriceType nextPrice(PriceType price) override {
        const auto p_price = level_size.lower_bound(price);
        if(p_price == level_size.end())
            return 0;
        if (p_price == level_size.begin()){
            if(p_price->first == level_size.begin()->first)
                return price;
            return 0;
        }
        return p_price->first;
    }

    std::deque<RestingOrder>& get_book_content(PriceType price) override{
        return book_content[price];
    }

    void execute(const InputOrder &input_order, RestingOrder &resting_order, PriceType price, std::ostream &stream) override {
        stream << input_order.getTime() << " ";
        stream << input_order.getClient() << " ";
        stream << resting_order.getClient() << " ";
        stream << price << " ";
        stream << resting_order.getSize() << " ";
        stream << "\n";
    }

    void execute_partial(const InputOrder &input_order, RestingOrder &resting_order, PriceType price, SizeType size, std::ostream &stream) override {
        resting_order.reduce_size(size);
        stream << input_order.getTime() << " ";
        stream << input_order.getClient() << " ";
        stream << resting_order.getClient() << " ";
        stream << price << " ";
        stream << size << " ";
        stream << "\n";
    }

    void emplace_order_to_price(const RestingOrder &order, PriceType price) override {
        book_content[price].emplace_back(order);
    }

private:
    std::map<PriceType, std::deque<RestingOrder>> book_content;
    std::map<PriceType, SizeType> level_size;  // for efficiency - essential for FOK orders

};

class BidDirectionBook: public DirectionBook{
protected:
    SizeType get_level(PriceType price) const override{
        return level_size.at(price);
    }
    void increase_level_size(PriceType price, SizeType size) override {
        level_size[price] += size;
    }

    void decrease_level_size(PriceType price, SizeType size) override {
        level_size[price] -= size;
    }

    void empty_level_size(PriceType price) override {
        level_size.erase(price);
    }

    SizeType get_available_size(PriceType price) const override {
        auto p = level_size.begin();
        const auto p_price = level_size.lower_bound(price);
        SizeType s = 0; // initialisation redundant
        while(p != p_price){
            s += (p++)->second;
        }
        return s;
    }

    PriceType nextPrice(PriceType price) override {
        const auto p_price = level_size.lower_bound(price);
        if(p_price == level_size.end())
            return 0;
        if (p_price == level_size.begin()){
            if(p_price->first == level_size.begin()->first)
                return price;
            return 0;
        }
        return p_price->first;
    }

    std::deque<RestingOrder>& get_book_content(PriceType price) override{
        return book_content[price];
    }

    void execute(const InputOrder &input_order, RestingOrder &resting_order, PriceType price, std::ostream &stream) override {
        stream << input_order.getTime() << " ";
        stream << resting_order.getClient() << " ";
        stream << input_order.getClient() << " ";
        stream << price << " ";
        stream << resting_order.getSize() << " ";
        stream << "\n";
    }

    void execute_partial(const InputOrder &input_order, RestingOrder &resting_order, PriceType price, SizeType size, std::ostream &stream) override {
        resting_order.reduce_size(size);
        stream << input_order.getTime() << " ";
        stream << resting_order.getClient() << " ";
        stream << input_order.getClient() << " ";
        stream << price << " ";
        stream << size << " ";
        stream << "\n";
    }

    void emplace_order_to_price(const RestingOrder &order, PriceType price) override {
        book_content[price].emplace_back(order);
    }

private:
    std::map<PriceType, std::deque<RestingOrder>, std::greater<>> book_content;
    std::map<PriceType, SizeType, std::greater<>> level_size;  // for efficiency - essential for FOK orders

};

class Book{
    std::map<DirectionType, std::shared_ptr<DirectionBook>> books; // keep it separate - ask and bid

    std::ostringstream orders;
    std::ostringstream execs;

    void process_order(InputOrder& order);
public:
    Book();

    void add_order(InputOrder & order) {
        if(orders.str().length() != 0)
            orders << "\n";
        orders << order;
        process_order(order);
    }

    std::string view_order() const;

    std::string view_execs() const;

    static Book build_from_string(std::string& s);
};

#endif //PERSOTOOLS_EXCHANGE_H
