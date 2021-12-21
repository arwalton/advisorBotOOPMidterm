#ifndef ADVISORBOT_H
#define ADVISORBOT_H
#pragma once

#include "OrderBook.h"
#include <string>
#include <vector>
#include <map>


	
class AdvisorBot  
{
	public:
		/**
		 * @brief Construct a new AdvisorBot object. This is the
		 * main control for the application
		 * 
		 */
		AdvisorBot();

		/**
		 * @brief Destroy the AdvisorBot object
		 * 
		 */
		~AdvisorBot();

		/**
		 * @brief Initialize the AdvisorBot and start the simulation
		 * 
		 */
		void init();

	private:
		//Tells the function to continue the while loop until instructed not to.
		bool running = true;
		
		//Stores the current time step of the simulation
		std::string currentTime;

		//Stores the OrderBook for the simulation
		OrderBook orderBook{"20200601.csv"};

		//Stores the average ask for each product seen.
		std::map<std::string,std::vector<double>> askAverages;

		//Stores the average bid for each product seen.
		std::map<std::string,std::vector<double>> bidAverages;		

		//Stores the command key words available to the user.
		const std::vector<std::string> commands{
			"help",
			"prod",
			"min",
			"max",
			"avg",
			"predict",
			"time",
			"step",
			"owncommand",
			"exit"
		};

		/**
		 * @brief Get an input command from the user
		 * 
		 * @return std::vector<std::string> a vector of the split input string.
		 */
		std::vector<std::string> getUserOption();

		/**
		 * @brief Process the user input and call the relevant function
		 * 
		 * @param input The input taken from the user and tokenised into a vector of words
		 */
		void processUserOption(std::vector<std::string>& input);

		/**
		 * @brief Prints the commands vector, which stores a list of the 
		 * commands available to the user
		 * 
		 */
		void printCommands();

		/**
		 * @brief Prints specific information about commands
		 * 
		 * @param input A tokenized string from user of at least size 2
		 */
		void printCommands(std::vector<std::string>& input);

		/**
		 * @brief Prints the current time in the simulation
		 * 
		 */
		void printCurrentTime();

		/**
		 * @brief Advances current time to the next timeframe in the data
		 * 
		 */
		void advanceTime();

		/**
		 * @brief Prints a list of the available products in the simulation
		 * 
		 */
		void printProducts();

		/**
		 * @brief Prints the mininum value for a specific currency and OrderType
		 * 
		 */
		void printMin(std::vector<std::string>& input);

		/**
		 * @brief Prints the maximum value for a specific currency and OrderType
		 * 
		 */
		void printMax(std::vector<std::string>& input);

		/**
		 * @brief Adds all of the averages from the current time stamp to the averages map.
		 * 
		 */
		void populateAverages();
};
#endif