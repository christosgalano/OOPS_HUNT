#pragma once
#include <iostream>
#include <string>
#include <cmath>

/// Abstract class that represents an attribute of a living being ///

class Attribute {
protected:
    int base_stat;
    int current_stat;
    
    // Method upgrade(int) uses a general formula in order to adjust the attribute based on the being's level.
    // Lower and upper bound are used in that formula.
    int lower_bound;        
    int upper_bound {};

public:
    // Constructor - Destructor
    Attribute(int in_stat)
        : base_stat(in_stat), current_stat(in_stat), lower_bound(in_stat) {}
    virtual ~Attribute() {}
    
    // Accessors
    int getCurrent() const { return current_stat;  }
    int getBase()    const { return base_stat;     }

    // Mutators
    void setUpperBound(int amount)  { upper_bound = amount; }

    void setCurrentAsBase() {
        // We set the current_value to be equal to the base_value - regardless 
        // if the current value of an attribute is different that its base value.
        current_stat = base_stat; 
    }

    // Virtual Methods
    virtual void increaseCurrent(int amount)  { current_stat += amount; }
    
    virtual void reduceCurrent(int amount) {
        current_stat -= amount;
        if (current_stat < 0)
            current_stat = 0;
    }

    virtual void upgrade(int level) = 0;
};