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
		OrderBook orderBook{"20200601.csv"};


		/**
		 * @brief Stores the averages for each product seen.
		 * The key pair is the product name and the OrderBookType.
		 * The value pair is the avg for the timestep and the amount of that product seen.
		 */
		std::map<std::pair<std::string, OrderBookType>,std::vector<std::pair<double, double>>> averages;

		/**
		 * @brief Stores the maximums for each product seen.
		 * The key pair is the product name and the OrderBookType.
		 */
		std::map<std::pair<std::string, OrderBookType>,std::vector<double>> maximums;

		/**
		 * @brief Stores the minimums for each product seen.
		 * The key pair is the product name and the OrderBookType.
		 */
		std::map<std::pair<std::string, OrderBookType>,std::vector<double>> minimums;

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
		 * @brief Prints the average for a specific currency over the given timeframe.
		 * 
		 * @param input The tokenized string of user input 
		 */
		void printAverage(std::vector<std::string>& input);

		/**
		 * @brief Prints a prediction for the value of a specific currency in the next timestep.
		 * 
		 * @param input The tokenized string of user input 
		 */
		void printPrediction(std::vector<std::string>& input);

		/**
		 * @brief Adds all of the averages from the current time step to the averages map.
		 * 
		 */
		void populateAverages();

		/**
		 * @brief Adds all of the maximums from the current time step to the maximums map.
		 * 
		 */
		void populateMaximums();

		/**
		 * @brief Adds all of the minimums from the current time step to the minimums map.
		 * 
		 */
		void populateMinimums();

		/**
		 * @brief Calculates the average price per unit over the given set of timesteps
		 * 
		 * @param orderType 
		 * @param steps The number of steps to use
		 * @return double The average
		 */
		double calculateAverageTimeSteps(std::string product, OrderBookType orderType, int steps);

		/**
		 * @brief Calculates the simple moving average maximum value over the specified number of timesteps, 
		 * not including currentTime
		 * 
		 * @param product The product string we are interested in.
		 * @param orderType The OrderBookType we are interested in
		 * @param steps The number of time steps to consider
		 * @return double The average maximum value
		 */
		double calculateSMAMax(std::string product, OrderBookType orderType, int steps);

		/**
		 * @brief Calculates the simple moving average minimum value over the specified number of timesteps,
		 * not including currentTime
		 * 
		 * @param product The product string we are interested in.
		 * @param orderType The OrderBookType we are interested in
		 * @param steps The number of time steps to consider
		 * @return double The average minimum value
		 */
		double calculateSMAMin(std::string product, OrderBookType orderType, int steps);

		/**
		 * @brief Calculates the exponential moving average maximum value
		 * 
		 * @param product The product string 
		 * @param orderType The OrderBookType
		 * @param sma The simple moving average up to the previous timestep
		 * @return double The exponential moving average maximum
		 */
		double calculateEMAMax(std::string product, OrderBookType orderType, double sma);

		/**
		 * @brief Calculates the exponential moving average minimum value
		 * 
		 * @param product The product string 
		 * @param orderType The OrderBookType
		 * @param sma The simple moving average up to the previous timestep
		 * @return double The exponential moving average minimum
		 */
		double calculateEMAMin(std::string product, OrderBookType ordertype, double sma);
};
#endif