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
		/**
		 * @brief Get an input command from the user
		 * 
		 * @return std::vector<std::string> a vector of the split input string.
		 */
		std::vector<std::string> getUserOption();

		/**
		 * @brief Process the user input and call the relevant function
		 * 
		 * @param input The input take from the user and tokenised into a vector
		 */
		void processUserOption(std::vector<std::string>& input);


};
#endif