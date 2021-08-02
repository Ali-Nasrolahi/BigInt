#ifndef __BigInt__
#define __BigInt__

#include <iostream>
#include <vector>
#include <map>

class BigInt{
 private:
    std::vector<int> numbs;
    bool isPositive;
    int base;
    static const int bdefault = 1000 * 1000 * 1000;
public:
    //Constructor
    BigInt(std::string);
    BigInt();

    //Adding
    BigInt operator+  (BigInt const &) const;
    BigInt &operator+= (BigInt const);
    BigInt operator+  (long long const &) const;
    BigInt &operator+= (long long);

    //Subtraction
    BigInt operator- (BigInt const &) const;
    BigInt &operator-= (BigInt const &);

    //Multiply
    BigInt operator*   (BigInt const &);
    BigInt &operator*= (BigInt const &);
    BigInt operator*   (long long const &);
    BigInt &operator*= (int const &); 

    //Initialize
    BigInt operator= (const long long &);

    //pow
    BigInt &pow(int const &); 


    //Output & Input
    friend std::istream &operator >>(std::istream &, BigInt &);
    friend std::ostream &operator <<(std::ostream &, BigInt const &);
private:
    BigInt pow(int const &, std::map<int, BigInt> &);
    uint8_t seg_leg(int) const;
};
#endif