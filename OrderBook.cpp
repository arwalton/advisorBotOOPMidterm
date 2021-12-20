#include "OrderBook.h"
#include "CSVReader.h"

#include <chrono>
#include <iostream>
#include <map>
	
OrderBook::OrderBook(std::string filename)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Starting to read csv file" << std::endl;
	orders = CSVReader::readCSV(filename);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "CSVReader::readCSV took " << duration.count() << " microseconds to process the data." << std::endl;
}
	
OrderBook::~OrderBook()
{
	
}

std::vector<std::string> OrderBook::getKnownProducts(){
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    //Add products to map, ignoring doubles.
    for(OrderBookEntry& e : orders){
        prodMap[e.product] = true;
    }

    //now flatten the map to vector of strings
    for(auto const& e : prodMap){
        products.push_back(e.first);
    }

    return products;

}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
	std::string product,
	std::string timestamp){

    std::vector<OrderBookEntry> ordersSub;
    for(OrderBookEntry& e : orders){
        if(e.orderType == type &&
        e.product == product &&
        e.timestamp == timestamp){
            ordersSub.push_back(e);
        }
    }
    return ordersSub;
}

std::string OrderBook::getEarliestTime(){
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp){
    std::string next_timestamp = "";
    for(OrderBookEntry& e : orders){
        if(e.timestamp > timestamp){
            next_timestamp = e.timestamp;
            break;
        }
    }
    if(next_timestamp == ""){
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max = orders[0].price;
    for(OrderBookEntry& e : orders){
        if(e.price > max)max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    double min = orders[0].price;
    for(OrderBookEntry& e : orders){
        if(e.price < min)min = e.price;
    }
    return min;
}

double OrderBook::getMeanPPU(std::vector<OrderBookEntry>& orders){
    return 1.0;
}

double OrderBook::getStDevPPU(std::vector<OrderBookEntry>& orders){
    return 1.0;
}