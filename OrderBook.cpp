#include "OrderBook.h"  
	
OrderBook::OrderBook(std::string filename)
{
	
}
	
OrderBook::~OrderBook()
{
	
}

std::vector<std::string> OrderBook::getKnownProducts(){
    return std::vector<std::string>{};
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
	std::string product,
	std::string timestamp){

    return std::vector<OrderBookEntry>{};
}

std::string OrderBook::getEarliestTime(){
    return "";
}

std::string OrderBook::getNextTime(std::string timestamp){
    return "";
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    return 1.0;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    return 1.0;
}

double OrderBook::getMeanPPU(std::vector<OrderBookEntry>& orders){
    return 1.0;
}

double OrderBook::getStDevPPU(std::vector<OrderBookEntry>& orders){
    return 1.0;
}