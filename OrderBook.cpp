#include "OrderBook.h"
#include "CSVReader.h"

#include <chrono>
#include <iostream>
	
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