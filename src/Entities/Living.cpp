#include "Entities/Living.hpp"

void Living::printDetailed() const {
    std::cout << "with name: " << name            << '\n';
    std::cout << "- Level: "   << level           << '\n';
    std::cout << "- Health: "  << hp.getCurrent() << '\n';
}

void Living::printBaseStatistics() const {
    std::cout << "- Health: " << hp.getBase() << '\n';
}