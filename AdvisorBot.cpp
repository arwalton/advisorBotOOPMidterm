#include "AdvisorBot.h"
#include <iostream>
#include <sstream>

	
AdvisorBot::AdvisorBot()
{
	
}
	
AdvisorBot::~AdvisorBot()
{
	
}

void AdvisorBot::init(){
    std::vector<std::string> input;
    
    while(true){
        input = getUserOption();
        std::cout << "You chose: " << std::endl;
        for(std::string const& str : input){
            std::cout << str << std::endl;
        }
    }
}

std::vector<std::string> AdvisorBot::getUserOption(){
    std::string line;
    std::string word;
    std::vector<std::string> optionVector;
    std::cout << "Please enter a command, or type 'help' for a list of commands" << std::endl;

    std::getline(std::cin, line);

    //Used to parse the string into individual words
    std::stringstream ss(line);

    while(ss >> word){
        optionVector.push_back(word);
    }

    return optionVector;
}

//TODO implement this function and call it
void AdvisorBot::processUserOption(std::vector<std::string>& input){

}