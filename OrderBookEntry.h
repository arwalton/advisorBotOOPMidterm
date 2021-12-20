#ifndef ORDERBOOKENTRY_H
#define ORDERBOOKENTRY_H
#pragma once

#include <string>

enum class OrderBookType{unknown = 0, bid = 1, ask = 2};
	
class OrderBookEntry  
{
	public:
		double price;
		double amount;
		std::string timestamp;
		std::string product;
		OrderBookType orderType;

		/**
		 * @brief Construct a new Order Book Entry object
		 * 
		 * @param _price 
		 * @param _amount 
		 * @param _timestamp 
		 * @param _product 
		 * @param _orderType 
		 */
		OrderBookEntry(
			double _price,
			double _amount,
			std::string _timestamp,
			std::string _product,
			OrderBookType _orderType
		);
		~OrderBookEntry();

		/**
		 * @brief Converts a string from the dataset into an OrderBookEntry
		 * 
		 * @param s A string from the dataset
		 * @return OrderBookType 
		 */
		static OrderBookType stringToOrderBookType(std::string s);

		/**
		 * @brief Converts the OrderBookEntry into a string
		 * 
		 * @return std::string 
		 */
		std::string toString();

		/**
		 * @brief Overloads the << operator so that it can be used directly on an OrderBookEntry
		 * 
		 * @param os 
		 * @param obe 
		 * @return std::ostream 
		 */
		friend std::ostream& operator<<(std::ostream& os, OrderBookEntry& obe);

				/**
		 * @brief Converts an OrderBookType to a string
		 * 
		 * @return std::string 
		 */
		static std::string obtToString(OrderBookType obt);

		/**
		 * @brief Overloads the << operator so that it can be used directly on an OrderBookType
		 * 
		 * @param os 
		 * @param obt 
		 * @return std::ostream& 
		 */
		friend std::ostream& operator<<(std::ostream& os, OrderBookType& obt);


};
#endif