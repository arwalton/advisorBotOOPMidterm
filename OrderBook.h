#ifndef ORDERBOOK_H
#define ORDERBOOK_H
#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>
#include <utility>
	
class OrderBook  
{
	private:
		std::vector<OrderBookEntry> orders;
		std::vector<std::string> products;

	public:

		/**
		 * @brief Construct a new Order Book object
		 * 
		 * @param filename the path to a csv file
		 */
		OrderBook(std::string filename);
		~OrderBook();

		/**
		 * @brief Return a vector of all known products in the dataset
		 * 
		 * @return std::vector<std::string> 
		 */
		std::vector<std::string> getKnownProducts();

		/**
		 * @brief Return a vector of orders according to the sent filters
		 * 
		 * @param type bid or ask
		 * @param product A product string
		 * @param timestamp a timestamp string
		 * @return std::vector<OrderBookEntry> 
		 */
		std::vector<OrderBookEntry> getOrders(OrderBookType type,
			std::string product,
			std::string timestamp);

		/**
		 * @brief Get the earliest time in our dataset. Used for initializing AdvisorBot.
		 * 
		 * @return std::string the earliest timestamp string
		 */
		std::string getEarliestTime();

		/**
		 * @brief Returns the next time after timestamp argument. If there is no next timestamp
		 * it wraps around back to the starting time.
		 * 
		 * @param timestamp a timestamp string
		 * @return std::string 
		 */
		std::string getNextTime(std::string timestamp);

		/**
		 * @brief Get the highest price in a vector of orders
		 * 
		 * @param orders a vector of OrderBookEntry - Should all be the same currency
		 * @return double the highest price
		 */
		static double getHighPrice(std::vector<OrderBookEntry>& orders);

		/**
		 * @brief Get the lowest price in a vector of orders
		 * 
		 * @param orders a vector of OrderBookEntry - Should all be the same currency
		 * @return double the lowest price
		 */
		static double getLowPrice(std::vector<OrderBookEntry>& orders);

		/**
		 * @brief Get the price per unit of a vector of OrderbookEntry
		 * 
		 * @param orders a vector of OrderBookEntry - Should all be the same currency
		 * @return std::pair<double, double> The mean price per unit and the total number of units.
		 */
		static std::pair<double, double> getMeanPPU(std::vector<OrderBookEntry> orders);

		/**
		 * @brief Get the standard deviation per unit of a vector of OrderBookEntry
		 * 
		 * @param orders a vector of OrderBookEntry - Should all be the same currency
		 * @return double the standard devaition per unit
		 */
		static double getStDevPPU(std::vector<OrderBookEntry>& orders);

};
#endif