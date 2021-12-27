#include "AdvisorBot.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

	
AdvisorBot::AdvisorBot()
{
	
}
	
AdvisorBot::~AdvisorBot()
{
	
}

void AdvisorBot::init(){
    std::vector<std::string> input;
    currentTime = orderBook.getEarliestTime();
    populateAverages();
    
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
        printProducts();
    }else if(command == commands[2]){ //min
        printMin(input);
    }else if(command == commands[3]){ //max
        printMax(input);
    }else if(command == commands[4]){ //avg
        printAverage(input);
    }else if(command == commands[5]){ //predict
        std::cout << "Still need to implement predict" << std::endl;
    }else if(command == commands[6]){ //time
        printCurrentTime();
    }else if(command == commands[7]){ //step
        advanceTime();
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
        "the weighted average ask or bid of that product over that timeframe. Example: avg ETH/BTC bid 10" << std::endl;
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

void AdvisorBot::printProducts(){
    std::vector<std::string> products = orderBook.getKnownProducts();
    std::cout << "Here are the available products:" << std::endl;

    for(std::string& product : products){
        std::cout << product << std::endl;
    }
}

//Called on min

void AdvisorBot::printMin(std::vector<std::string>& input){
    if(input.size() != 3){
        std::cout << "This is not the correct format for the 'min' command." << std::endl;
        std::cout << "Please type 'help min' for an example of the correct format." << std::endl;
        return;
    }

    std::string product = input[1];
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(input[2]);

    std::vector<std::string> products = orderBook.getKnownProducts();
    if(std::find(products.begin(),products.end(), product) == products.end()){
        std::cout << "That product does not exist in this simulation. Please check the name and try again." << std::endl;
        return;
    }
    if(orderType == OrderBookType::unknown){
        std::cout << "That is not a valid Order type. Valid types are 'ask' and 'bid'." << std::endl;
        return;
    }
    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);
    double min = orderBook.getLowPrice(entries);

    std::cout << "The minimum " << OrderBookEntry::obtToString(orderType) << " for " << product << " is " << min << "." << std::endl;
}

//Called on max

void AdvisorBot::printMax(std::vector<std::string>& input){
    if(input.size() != 3){
        std::cout << "This is not the correct format for the 'max' command." << std::endl;
        std::cout << "Please type 'help max' for an example of the correct format." << std::endl;
        return;
    }

    std::string product = input[1];
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(input[2]);

    std::vector<std::string> products = orderBook.getKnownProducts();
    if(std::find(products.begin(),products.end(), product) == products.end()){
        std::cout << "That product does not exist in this simulation. Please check the name and try again." << std::endl;
        return;
    }
    if(orderType == OrderBookType::unknown){
        std::cout << "That is not a valid Order type. Valid types are 'ask' and 'bid'." << std::endl;
        return;
    }
    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);
    double max = orderBook.getHighPrice(entries);

    std::cout << "The maximum " << OrderBookEntry::obtToString(orderType) << " for " << product << " is " << max << "." << std::endl;
}

//Called on avg

void AdvisorBot::printAverage(std::vector<std::string>& input){
    //Check for correct number of arguments
    if(input.size() != 4){
        std::cout << "This is not the correct format for the 'avg' command." << std::endl;
        std::cout << "Please type 'help avg' for an example of the correct format." << std::endl;
        return;
    }

    //Put product and orderType into variables
    std::string product = input[1];
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(input[2]);

    //Check that last number will convert to an integer
    int steps = 0;
    try{
        steps = std::stoi(input[3]);
    }catch(const std::invalid_argument& e){
        std::cout << "The final argument must be a positive integer." << std::endl;
        std::cout << "Please type 'help avg' for an example of the correct format." << std::endl;
        return;
    }

    //Check that product is formatted correctly and it exists
    std::vector<std::string> products = orderBook.getKnownProducts();
    if(std::find(products.begin(),products.end(), product) == products.end()){
        std::cout << "That product does not exist in this simulation. Please check the name and try again." << std::endl;
        return;
    }
    //Check orderType
    if(orderType == OrderBookType::unknown){
        std::cout << "That is not a valid Order type. Valid types are 'ask' and 'bid'." << std::endl;
        return;
    }

    //TODO implement the actual code.
    double average = calculateAverageTimeSteps(product,orderType,steps);


}

//Called on predict
//TODO implement this

//Called on time

void AdvisorBot::printCurrentTime(){
    std::cout << "The current time in the simulation is: " << currentTime << std::endl;
}

//Called on step

void AdvisorBot::advanceTime(){
    std::cout << "Advancing the simulation time..." <<std::endl;

    //TODO, more logic will go here with other functions to save data for calculations
    std::cout << "..." << std::endl;

    currentTime = orderBook.getNextTime(currentTime);
    populateAverages();
    printCurrentTime();
    
}

//Called on owncommand
//TODO implement this


//*********Helper functions**********

void AdvisorBot::populateAverages(){
    for(std::string currency : orderBook.getKnownProducts()){
        try{
            averages[std::make_pair(currency, OrderBookType::ask)].push_back(OrderBook::getMeanPPU(orderBook.getOrders(OrderBookType::ask,currency,currentTime)));
        }catch(const std::range_error& e){
            std::cout << "An error occurred with the data." << std::endl;
            std::cout << "Currency: " << currency << std::endl;
            std::cout << "OrderType: Ask" << std::endl;
            std::cout << "Timestep: " << currentTime << std::endl;
            std::cout << "Error Message: " << e.what() << std::endl;
            averages[std::make_pair(currency, OrderBookType::ask)].push_back(std::pair<double,double>(0,0));
        }

        try{
            averages[std::make_pair(currency, OrderBookType::bid)].push_back(OrderBook::getMeanPPU(orderBook.getOrders(OrderBookType::bid,currency,currentTime)));
        }catch(const std::range_error& e){
            std::cout << "An error occurred with the data." << std::endl;
            std::cout << "Currency: " << currency << std::endl;
            std::cout << "OrderType: Bid" << std::endl;
            std::cout << "Timestep: " << currentTime << std::endl;
            std::cout << "Error Message: " << e.what() << std::endl;
            averages[std::make_pair(currency, OrderBookType::bid)].push_back(std::pair<double,double>(0,0));
        }
    }
}

double AdvisorBot::calculateAverageTimeSteps(std::string product, OrderBookType orderType, int steps){
    int i = 0;
    for(auto it = averages.rbegin(); it != averages.rend(); ++it){
        std::cout << "This is loop " << i << std::endl;
        if(i >= steps){
            break;
        }
        ++i;
    }
    
    //TODO implement logic for this.
    std::cout << "Still needs to be implemented fully, but this is the averages vector" << std::endl;
    for(const auto& avg : averages){
        std::cout << avg.first.first << " " << OrderBookEntry::obtToString(avg.first.second) << std::endl;
        
        for(const auto& value : avg.second){
            std::cout << value.first << " " << value.second << std::endl;
        }
    }
    return 0;
}