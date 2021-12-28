#include "OrderBook.h"
#include "CSVReader.h"

#include <chrono>
#include <iostream>
#include <map>
#include <exception>
	
OrderBook::OrderBook(std::string filename)
{
    //Use a timer to see how long it takes to read in the data.

    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Starting to read csv file" << std::endl;
	orders = CSVReader::readCSV(filename);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "CSVReader::readCSV took " << duration.count() << " microseconds to process the data." << std::endl;

    //Populate the products vector

    std::map<std::string, bool> prodMap;
    //Add products to map, ignoring doubles.
    for(OrderBookEntry& e : orders){
        prodMap[e.product] = true;
    }
    //now flatten the map to vector of strings
    for(auto const& e : prodMap){
        products.push_back(e.first);
    }
}
	
OrderBook::~OrderBook()
{
	
}

std::vector<std::string> OrderBook::getKnownProducts(){
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

double OrderBook::getHighPrice(std::vector<OrderBookEntry> orders){
    double max = orders[0].price;
    for(OrderBookEntry& e : orders){
        if(e.price > max)max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> orders){
    double min = orders[0].price;
    for(OrderBookEntry& e : orders){
        if(e.price < min)min = e.price;
    }
    return min;
}

std::pair<double, double> OrderBook::getMeanPPU(std::vector<OrderBookEntry> orders){
    double sumPrice = 0;
    double numShares = 0;
    std::pair<double,double> avgAndNum;
    for(const OrderBookEntry& order : orders){
        numShares = numShares + order.amount;
        sumPrice = sumPrice + (order.amount * order.price);
    }
    //Check for divide by zero and throw exception if so.
    if(numShares <= 0){
        throw std::range_error("Attempt to divide by zero. Some currency has orders but unusable amounts.");
    }
    
    avgAndNum.first = sumPrice / numShares;
    avgAndNum.second = numShares;
    return avgAndNum;
}

double OrderBook::getStDevPPU(std::vector<OrderBookEntry>& orders){
    return 1.0;
}