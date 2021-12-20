#ifndef CSVREADER_H
#define CSVREADER_H
#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader  
{
	private:

	public:

		CSVReader();
		~CSVReader();

		/**
		 * @brief Reads the data in csvFile and returns a vector of OrderBookEntry
		 * 
		 * @param csvFile 
		 * @return std::vector<OrderBookEntry> 
		 */
		static std::vector<OrderBookEntry> readCSV(std::string csvFile);

		/**
		 * @brief Tokenises a string on the separator passed to the function
		 * 
		 * @param csvLine 
		 * @param separator 
		 * @return std::vector<std::string> 
		 */
		static std::vector<std::string> tokenise(std::string csvLine, char separator);


	private:
		/**
		 * @brief Take a series of strings and an OrderBookType and returns an OrderBookEntry
		 * 
		 * @param price 
		 * @param amount 
		 * @param timestamp 
		 * @param product 
		 * @param orderType 
		 * @return OrderBookEntry 
		 */
		static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);

};
#endif