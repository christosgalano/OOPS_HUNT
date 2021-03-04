#include "World/Square.hpp"
#include "Utilities/Inputter.hpp"
#include "Utilities/ColouredLogger.hpp"
#include <chrono>
#include <thread>


bool NonAccessible::enter(const std::vector<Hero*>& heroes_to_enter) {
    std::cout << "You cannot enter this square\n";
    return false;
}

void NonAccessible::printColoured() const {
    ColouredLogger::LogMessageColoured("#", ColouredLogger::BLACK);
}


bool Plain::enter(const std::vector<Hero*>& heroes_to_enter) {
    for (Hero* h : heroes_to_enter)
        heroes.push_back(h);
    access(); 
    return true;    
}

void Plain::access() {
    system("clear");
    ColouredLogger::LogMessageColoured("Plain\n", ColouredLogger::Colour::YELLOW);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::YELLOW);
    std::cout << "You are currently occupying a plain square\n";
    std::cout << "Nothing special happens here\n";
    ColouredLogger::PauseAndClearWithMessage("Press enter to return to main menu...");    
}

void Plain::printColoured() const {
    ColouredLogger::LogMessageColoured("~", ColouredLogger::YELLOW);
}


bool Camp::enter(const std::vector<Hero*>& heroes_to_enter) {
    for (Hero* h : heroes_to_enter)
        heroes.push_back(h);
    access();
    return true;
}

void Camp::access() {
    system("clear");
    ColouredLogger::LogMessageColoured("Camp\n", ColouredLogger::Colour::GREEN);
    ColouredLogger::LogMessageColoured("-----------------------------------------------------------------------------\n", ColouredLogger::Colour::GREEN);
    std::cout << "You are currently occupying a camp square\n";
    std::string answer = Inputter::GetInput("Do you wish to rest (yes / no): ", "yes", "no");
    if (answer == "no") return;

    std::cout << "Wait for 5 seconds\n" << std::flush; // std::flush so that the message will be logged before the thread is put to sleep
    for (Hero* h : heroes)
        h->rest();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "All heroes have rested\n";
    ColouredLogger::PauseAndClearWithMessage("Press enter to return to main menu...");
}

void Camp::printColoured() const {
    ColouredLogger::LogMessageColoured("^", ColouredLogger::GREEN);
}