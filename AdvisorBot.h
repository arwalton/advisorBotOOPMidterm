#ifndef ADVISORBOT_H
#define ADVISORBOT_H
#pragma once

#include <string>
#include <vector>


	
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


};
#endif