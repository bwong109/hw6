#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::vector<unsigned long long> w(5, 0);

        int len = k.size();
        int groupCount = (len + 5) / 6;

        for (int i = 0; i < groupCount; ++i) {
            unsigned long long total = 0;
            int startIndex = std::max(0, len - (i + 1) * 6);
            for (int j = startIndex; j < len - i * 6; ++j) {
                total = 36 * total + letterDigitToNumber(std::tolower(k[j]));
            }
            w[4 - i] = total;
        }
        
        // Debug output for 'w' values
        std::cout << "Intermediate 'w' values:" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << "w[" << i << "] = " << w[i] << std::endl;
        }

        HASH_INDEX_T hashValue = 0;
        for (int i = 0; i < 5; ++i) {
            hashValue += rValues[i] * w[i];
        }

        return hashValue;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'a' && letter <= 'z') {
            return letter - 'a';
        } 

        else if (letter >= '0' && letter <= '9') {
            return letter - '0' + 26;
        } 
        
        else {
            return -1;  
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
