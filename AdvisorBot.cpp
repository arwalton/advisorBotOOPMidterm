#include "AdvisorBot.h"
#include <iostream>
#include <sstream>
#include <cctype>

	
AdvisorBot::AdvisorBot()
{
	
}
	
AdvisorBot::~AdvisorBot()
{
	
}

void AdvisorBot::init(){
    std::vector<std::string> input;
    
    while(running){
        input = getUserOption();

        processUserOption(input);
    }
}

//*********Handling menu and input**********

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

    std::cout << std::endl;
    return optionVector;
}


void AdvisorBot::processUserOption(std::vector<std::string>& input){
    std::string command = input[0];

    if(command == commands[0]){ //help
        if(input.size() > 1){ //help with additional params
            printCommands(input);
        }else{ //help with no params
            printCommands();
        }
    }else if(command == commands[1]){ //prod
        std::cout << "Still need to implement prod" << std::endl;
    }else if(command == commands[2]){ //min
        std::cout << "Still need to implement min" << std::endl;
    }else if(command == commands[3]){ //max
        std::cout << "Still need to implement max" << std::endl;
    }else if(command == commands[4]){ //avg
        std::cout << "Still need to implement avg" << std::endl;
    }else if(command == commands[5]){ //predict
        std::cout << "Still need to implement predict" << std::endl;
    }else if(command == commands[6]){ //time
        printCurrentTime();
    }else if(command == commands[7]){ //step
        std::cout << "Still need to implement step"  << std::endl;
    }else if(command == commands[8]){ //owncommand
        std::cout << "Still need to implement owncommand"  << std::endl;
    }else if(command == commands[9]){ //exit
        std::cout << "Thanks for playing. See you next time!"  << std::endl;
        running = false;
    }else{ //Bad input
        std::cout << "I don't understand that command. Please check the spelling."  << std::endl;
    }
    std::cout << std::endl;
}

//**********Execute user commands************

//Called on help
void AdvisorBot::printCommands(){
    std::cout << "Here are the available commands:" << std::endl;
    for(auto& command : commands){
        std::cout << command << std::endl;
    }
    std::cout << "Type help followed by the name of a command for more information on specific commands. For example: help avg" << std::endl;
}

//Called on help cmd
void AdvisorBot::printCommands(std::vector<std::string>& input){
    if(input.size() != 2){
        std::cout << "The help command can only be alone or followed by a single command." << std::endl;
        return;
    }
    std::string command = input[1];

    if(command == commands[0]){ //help
        std::cout << "Type 'help' to get a list of commands. Alternatively, type help followed by a command" << std::endl <<
        "to get more information on that specific command. Example: 'help avg'" << std::endl;
    }else if(command == commands[1]){ //prod
        std::cout << "Type 'prod' to get a list of available products." << std::endl;
    }else if(command == commands[2]){ //min
        std::cout << "Type 'min' followed by a product and either 'bid' or 'ask' to get the minimum bid or ask" << std::endl <<
        "for that product in the current time step. Example: 'min ETH/BTC ask'" << std::endl;
    }else if(command == commands[3]){ //max
        std::cout << "Type 'max' followed by a product and either 'bid' or 'ask' to get the maximum bid or ask" << std::endl <<
        "for that product in the current time step. Example: 'max ETH/BTC ask'" << std::endl;
    }else if(command == commands[4]){ //avg
        std::cout << "Type 'avg' followed by a product, either 'bid' or 'ask', and a number of timesteps to get" << std::endl <<
        "the average ask or bid of that product over that timeframe. Example: avg ETH/BTC bid 10" << std::endl;
    }else if(command == commands[5]){ //predict
        std::cout << "Type 'predict' followed by 'max' or 'min', a product, and either 'ask' or 'bid' to get a" << std::endl <<
        "prediction of that product for the next timestep. Example predict max ETH/BTC bid" << std::endl;
    }else if(command == commands[6]){ //time
        std::cout << "Type 'time' to get the current time in the dataset, i.e. which timeframe you are looking at." << std::endl;
    }else if(command == commands[7]){ //step
        std::cout << "Type 'step' to advance the simulation to the next step."  << std::endl;
    }else if(command == commands[8]){ //owncommand
        std::cout << "Type 'owncommand' to be blown away by my brilliance."  << std::endl;
    }else if(command == commands[9]){ //exit
        std::cout << "Type 'exit' to end the simulation." << std::endl;
    }else{ //Bad input
        std::cout << "I don't understand that command. Please check the spelling or type 'help' for a list of commands."  << std::endl;
    }  
}

//Called on prod
//TODO implement this

//Called on min
//TODO implement this

//Called on max
//TODO implement this

//Called on avg
//TODO implement this

//Called on predict
//TODO implement this

//Called on time
void AdvisorBot::printCurrentTime(){
    std::cout << "TODO Implement this function, after implementing OrderBookEntry and OrderBook classes" << std::endl;
}

//Called on step
//TODO implement this

//Called on owncommand
//TODO implement this