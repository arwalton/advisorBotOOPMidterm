#ifndef ADVISORBOT_H
#define ADVISORBOT_H
#pragma once

#include "OrderBook.h"
#include <string>
#include <vector>
#include <utility>
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
		OrderBook orderBook{"small-test.csv"};

		//Stored the averages for each product seen.
		//The key pair is the product name and the OrderBookType.
		//The value pair is the avg for the timestep and the amount of that product seen.
		std::map<std::pair<std::string, OrderBookType>,std::vector<std::pair<double, double>>> averages;

		//Stores the average ask for each product seen.
		//String is the product, first double is the avg, second double is the amount
		std::map<std::string,std::vector<std::pair<double, double>>> askAverages;

		//Stores the average bid for each product seen.
		//String is the product, first double is the avg, second double is the amount
		std::map<std::string,std::vector<std::pair<double,double>>> bidAverages;		

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
		 * @param input The tokenized string of user input
		 */
		void printMin(std::vector<std::string>& input);

		/**
		 * @brief Prints the maximum value for a specific currency and OrderType
		 * 
		 * @param input The tokenized string of user input
		 */
		void printMax(std::vector<std::string>& input);

		/**
		 * @brief 
		 * 
		 * @param input The tokenized string of user input 
		 */
		void printAverage(std::vector<std::string>& input);

		/**
		 * @brief Adds all of the averages from the current time step to the averages map.
		 * 
		 */
		void populateAverages();

		/**
		 * @brief Calculates the average price per unit over the given set of timesteps
		 * 
		 * @param orderType 
		 * @param steps The number of steps to use
		 * @return double The average
		 */
		double calculateAverageTimeSteps(std::string product, OrderBookType orderType, int steps);
};
#endif