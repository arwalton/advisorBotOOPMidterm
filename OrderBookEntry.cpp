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

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s){
    //Replaced original code with branchless version to optimize for speed
    return (OrderBookType)((s == "bid") + 2*(s == "ask"));
    
}

std::string OrderBookEntry::obtToString(OrderBookType obt){
    switch(obt){
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
    entry = entry + "ordertype: " + obtToString(orderType) + "\n";
    
    return entry;
}

std::ostream& operator<<(std::ostream& os, OrderBookType& obt){
    os << OrderBookEntry::obtToString(obt);
    return os;
}

