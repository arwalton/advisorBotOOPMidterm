#include "OrderBookEntry.h"  
	
OrderBookEntry::OrderBookEntry(
    double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _orderType
)
: price(_price),
  amount(_amount),
  timestamp(_timestamp),
  product(_product),
  orderType(_orderType)
{
	
}
	
OrderBookEntry::~OrderBookEntry()
{
	
}

//TODO test current version vs branchless version
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s){
    if(s == "ask"){
        return OrderBookType::ask;
    }
    if(s == "bid"){
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;

    /*
    My attempt at a branchless version
    return (OrderBookType)((s == "ask") + 2*(s == "bid"));
    */
}

std::string OrderBookEntry::obtToString(){
    switch(orderType){
        case OrderBookType::ask:
            return "ask";
            break;
        case OrderBookType::bid:
            return "bid";
            break;
        default:
            return "unknown";
    }
}

std::ostream& operator<<(std::ostream& os, OrderBookEntry& obe){
    os << obe.toString();
    return os;
}

std::string OrderBookEntry::toString(){
    std::string entry = "";

    entry = entry + "price: " + std::to_string(price) + "\n";
    entry = entry + "amount: " + std::to_string(amount) + "\n";
    entry = entry + "timestamp: " + timestamp + "\n";
    entry = entry + "product: " + product + "\n";
    entry = entry + "ordertype: " + obtToString() + "\n";
    
    return entry;
}

