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
    populateMaximums();
    populateMinimums();
    
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
        printPrediction(input);
    }else if(command == commands[6]){ //time
        printCurrentTime();
    }else if(command == commands[7]){ //step
        advanceTime();
    }else if(command == commands[8]){ //stdev
        std::cout << "Still need to implement stdev"  << std::endl;
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
    }else if(command == commands[8]){ //stdev
        std::cout << "Type 'stdev' followed by a product and either 'bid' or 'ask' to get the standard deviation" << std::endl <<
        " of the product and ordertype in the current timestep."  << std::endl;
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

    //Check that last number will convert to a integer
    int steps = 0;
    try{
        steps = std::stoi(input[3]);
        if(steps <= 0){
            throw std::invalid_argument("The number of steps must be a positive integer.");
        }
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

    double average = calculateAverageTimeSteps(product,orderType,steps);

    std::cout << "The average " << product << " " << OrderBookEntry::obtToString(orderType) << " price per unit over the last " << std::to_string(steps) << " timestep(s) was " << std::to_string(average) << std::endl;
}

//Called on predict

void AdvisorBot::printPrediction(std::vector<std::string>& input){
    //Check for correct number of arguments
    if(input.size() != 4){
        std::cout << "This is not the correct format for the 'predict' command." << std::endl;
        std::cout << "Please type 'help predict' for an example of the correct format." << std::endl;
        return;
    }

    //Put product and orderType into variables
    std::string product = input[2];
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(input[3]);

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

    //Check for max or min
    if(input[1] == "max"){
        //Predict the max
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

        double currentHigh = orderBook.getHighPrice(entries);
;
        double prediction = 0;
        if(maximums[std::make_pair(product,orderType)].size() == 1){
            prediction = currentHigh;
        }else{
            prediction = calculateEMAMax(product,orderType,calculateSMAMax(product,orderType,5));
        }
        
        std::cout << "Using an exponential moving average, my best prediction for the max " << OrderBookEntry::obtToString(orderType) << " for " << product << " is " << prediction << "." << std::endl;

    }else if(input[1] == "min"){
        //Predict the min
        std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

        double currentLow = orderBook.getLowPrice(entries);
;
        double prediction = 0;
        if(minimums[std::make_pair(product,orderType)].size() == 1){
            prediction = currentLow;
        }else{
            prediction = calculateEMAMin(product,orderType,calculateSMAMin(product,orderType,5));
        }
        
        std::cout << "Using an exponential moving average, my best prediction for the min " << OrderBookEntry::obtToString(orderType) << " for " << product << " is " << prediction << "." << std::endl;


    }else{
        std::cout << "This is not the correct format for the 'predict' command." << std::endl;
        std::cout << "There appears to be a problem with the third argument (max/min)." << std::endl;
        std::cout << "Please type 'help predict' for an example of the correct format." << std::endl;
        return;
    }
}

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
    populateMaximums();
    populateMinimums();
    printCurrentTime();
    
}

//Called on stdev
//TODO implement this

void AdvisorBot::printStDev(std::vector<std::string>& input){
    
}


//*********Helper functions**********

void AdvisorBot::populateAverages(){
    for(std::string currency : orderBook.getKnownProducts()){
        try{
            averages[std::make_pair(currency, OrderBookType::ask)].push_back(OrderBook::getMeanPPU(orderBook.getOrders(OrderBookType::ask,currency,currentTime)));
        }catch(const std::range_error& e){
            std::cout << "An error occurred with the averages data." << std::endl;
            std::cout << "Currency: " << currency << std::endl;
            std::cout << "OrderType: Ask" << std::endl;
            std::cout << "Timestep: " << currentTime << std::endl;
            std::cout << "Error Message: " << e.what() << std::endl;
            averages[std::make_pair(currency, OrderBookType::ask)].push_back(std::pair<double,double>(0,0));
        }

        try{
            averages[std::make_pair(currency, OrderBookType::bid)].push_back(OrderBook::getMeanPPU(orderBook.getOrders(OrderBookType::bid,currency,currentTime)));
        }catch(const std::range_error& e){
            std::cout << "An error occurred with the averages data." << std::endl;
            std::cout << "Currency: " << currency << std::endl;
            std::cout << "OrderType: Bid" << std::endl;
            std::cout << "Timestep: " << currentTime << std::endl;
            std::cout << "Error Message: " << e.what() << std::endl;
            averages[std::make_pair(currency, OrderBookType::bid)].push_back(std::pair<double,double>(0,0));
        }
    }
}

void AdvisorBot::populateMaximums(){
    for(std::string currency : orderBook.getKnownProducts()){
        try{
            maximums[std::make_pair(currency, OrderBookType::ask)].push_back(OrderBook::getHighPrice(orderBook.getOrders(OrderBookType::ask,currency,currentTime)));
        }catch(const std::range_error& e){
            std::cout << "An error occurred with the maximums data." << std::endl;
            std::cout << "Currency: " << currency << std::endl;
            std::cout << "OrderType: Ask" << std::endl;
            std::cout << "Timestep: " << currentTime << std::endl;
            std::cout << "Error Message: " << e.what() << std::endl;
            maximums[std::make_pair(currency, OrderBookType::ask)].push_back(0);
        }

        try{
            maximums[std::make_pair(currency, OrderBookType::bid)].push_back(OrderBook::getHighPrice(orderBook.getOrders(OrderBookType::bid,currency,currentTime)));
        }catch(const std::range_error& e){
            std::cout << "An error occurred with the maximums data." << std::endl;
            std::cout << "Currency: " << currency << std::endl;
            std::cout << "OrderType: Bid" << std::endl;
            std::cout << "Timestep: " << currentTime << std::endl;
            std::cout << "Error Message: " << e.what() << std::endl;
            maximums[std::make_pair(currency, OrderBookType::bid)].push_back(0);
        }
    }
}

void AdvisorBot::populateMinimums(){
    for(std::string currency : orderBook.getKnownProducts()){
        try{
            minimums[std::make_pair(currency, OrderBookType::ask)].push_back(OrderBook::getLowPrice(orderBook.getOrders(OrderBookType::ask,currency,currentTime)));
        }catch(const std::range_error& e){
            std::cout << "An error occurred with the minimums data." << std::endl;
            std::cout << "Currency: " << currency << std::endl;
            std::cout << "OrderType: Ask" << std::endl;
            std::cout << "Timestep: " << currentTime << std::endl;
            std::cout << "Error Message: " << e.what() << std::endl;
            minimums[std::make_pair(currency, OrderBookType::ask)].push_back(0);
        }

        try{
            minimums[std::make_pair(currency, OrderBookType::bid)].push_back(OrderBook::getLowPrice(orderBook.getOrders(OrderBookType::bid,currency,currentTime)));
        }catch(const std::range_error& e){
            std::cout << "An error occurred with the minimums data." << std::endl;
            std::cout << "Currency: " << currency << std::endl;
            std::cout << "OrderType: Bid" << std::endl;
            std::cout << "Timestep: " << currentTime << std::endl;
            std::cout << "Error Message: " << e.what() << std::endl;
            minimums[std::make_pair(currency, OrderBookType::bid)].push_back(0);
        }
    }
}

double AdvisorBot::calculateSMAMax(std::string product, OrderBookType orderType, int steps){
    int step = 1;
    int num = 0;
    double sumMaximums = 0;
    //Making the key for the maximums vector
    std::pair<std::string,OrderBookType> key = std::make_pair(product, orderType);
    
    //Iterate through vector in reverse
    for(auto it = maximums[key].rbegin(); it != maximums[key].rend(); ++it){
        if(step > 1){
            sumMaximums += *it;
            ++num;
        }
        //Break if loop has run enough times.
        if(step >= steps){
            break;
        }
        ++step;
    }
    
    return sumMaximums / num;
}

double AdvisorBot::calculateEMAMax(std::string product, OrderBookType orderType, double sma){
    //The factor used in weighting the data - based on a five-day sma
    double weightFactor = 2.0/6.0;
    //Making the key for the maximums vector
    std::pair<std::string,OrderBookType> key = std::make_pair(product, orderType);

    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

    double currentMax = orderBook.getHighPrice(entries);

    return (currentMax * weightFactor) + (sma * (1 - weightFactor));
}

double AdvisorBot::calculateSMAMin(std::string product, OrderBookType orderType, int steps){
    int step = 1;
    int num = 0;
    double sumMinimums = 0;
    //Making the key for the maximums vector
    std::pair<std::string,OrderBookType> key = std::make_pair(product, orderType);
    
    //Iterate through vector in reverse
    for(auto it = minimums[key].rbegin(); it != minimums[key].rend(); ++it){
        if(step > 1){
            sumMinimums += *it;
            ++num;
        }
        //Break if loop has run enough times.
        if(step >= steps){
            break;
        }
        ++step;
    }
    
    return sumMinimums / num;
}

double AdvisorBot::calculateEMAMin(std::string product, OrderBookType orderType, double sma){
    //The factor used in weighting the data - based on a five-day sma
    double weightFactor = 2.0/6.0;
    //Making the key for the maximums vector
    std::pair<std::string,OrderBookType> key = std::make_pair(product, orderType);

    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

    double currentMin = orderBook.getLowPrice(entries);

    return (currentMin * weightFactor) + (sma * (1 - weightFactor));
}

double AdvisorBot::calculateAverageTimeSteps(std::string product, OrderBookType orderType, int steps){
    int step = 1;
    double sumPrice = 0;
    double numShares = 0;
    //Making the key for the averages vector
    std::pair<std::string,OrderBookType> key = std::make_pair(product, orderType);
    
    //Iterate through vector in reverse
    for(auto it = averages[key].rbegin(); it != averages[key].rend(); ++it){
        sumPrice += it->first * it->second;
        numShares += it->second;
        
        //Break if loop has run enough times.
        if(step >= steps){
            break;
        }
        ++step;
    }
    return sumPrice / numShares;
}

double AdvisorBot::calculateStDev(std::string product, OrderBookType orderType){
    double mean = averages[std::make_pair(product,orderType)].back().first;

    std::vector<OrderBookEntry> entries = orderBook.getOrders(orderType, product, currentTime);

    for(auto it = entries.begin(); it != entries.end(); ++it){

    }

    return 0;
}