#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
using namespace std;
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
        vector<int> a(6, 0);
        string temp;
        //vector<int>;
        vector<unsigned long long> w(5, 0);

        //Setting up w values
        int atrack = 6;
        int wtrack = 4;
        for (int i = k.size()-1; i > -1; i--){
            //cout << "Letter: " << k[i] << endl;
            atrack--;
            a[atrack] = letterDigitToNumber(k[i]);
            //cout << "a at " << atrack << ": " << a[atrack] << endl;
            if (atrack == 0){
                w[wtrack] = decinator(a);
                a.assign(6,0);
                atrack=6;
                wtrack--;
            }
        }
        if (atrack!=6){
            //cout <<"Finishing up" << endl;
            w[wtrack] = decinator(a);
            wtrack--;
        }

        //Debug print values
        /*
        cout << "W Values: ";
        for (int i = 0; i < w.size(); i++){
            cout << i << ": " << w[i] << " ";
        }
        cout << endl;
         */

        //Debug set values
        /*
        w[0] = 0;
        w[1] = 0;
        w[2] = 0;
        w[3] = 0;
        w[4] = 38;
         */

        unsigned long long rtotal = 0;
        for (int i = 0; i < 5; i++){
            rtotal += rValues[i] * w[i];
        }

        return rtotal;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        int out;
        if (letter < 48 ||
            (letter > 57 && letter < 65) ||
            (letter > 90 && letter < 97) ||
            letter > 122){
            out = 0;
        }
        //lowercase
        else if (letter > 96) out = letter - 97;
        //capital
        else if (letter > 64) out = letter - 65;
        //numerical
        else{
            out = letter - 22;
        }


        //cout << "Char: " << letter << "out:" << out << endl;
        return out;
    }

    unsigned long long decinator (vector<int> digs) const {
        //Improve efficiency here

        unsigned long long total = 0;
        for (int i = 0; i < 6; i++){
            //cout << digs[i] <<" * " << pow(36, 5-i) << endl;
            total+= digs[i] * pow(36, 5-i);
            //cout << "current total: " << total << endl;
        }
        return total;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i = { 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
