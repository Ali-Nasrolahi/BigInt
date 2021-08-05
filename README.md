# BigInt
* [Description](#description)   
* [Storing](#storing)
* [Constructors](#constructors)
* [Operators](#operators)
  * [Addition](#addition)
  * [Subtraction](#subtraction)
  * [Multiplication](#multiplication)
  * [Input & Output](#IO)
  * [Power](#pwr)


# Description
Awesome BigInt implementation. Thanks to Kaspars For [Original Source](https://github.com/kasparsklavins/bigint).

 Well this code ,kind of, is forked from original project, however here I'm going to explain some of algorithms behind the implementations; for those who want to learn. enjoy! ;) 
 
# Storing 
Well, we using vectors; awesome STL container which is perfect for our need. Imagine you have a 12-digits number that you want to store in a BigInt object. 

How we handle a number is pretty straight-forward; start with our `base` which essentially is a variable that specify how many digits of the number we want to push_back to our vector. And in this project; base by default going to store an int (10^9). 

So we start with our vector and push_back mod of our 12-digit number like shown below:
```C++
long long N = 1234; //input number; you could use string instead, idea won't change.
std::vector<int> v;
const int Base = 1000* 1000* 1000;
while(N){
    v.push_back(N % Base);
    N /= Base;
}
// for our 12-digit number first its 9 trailing digits will be pushed then rest 3.
// And in our stack numbers store kind of line this (first 9 digits)-(second 9 digits) -... so forth.
// i.e. 123456789012 will be 456789012-> fist element and 123-> second element.
```
# Constructors
Basically, in **BigInt** class we have 2 constructors; you could just give the object a string or nothing. 
```C++
BigInt A; // no parameter
BigInt B("123425"); //or a string
```
No Parm function will just do basic initialization, however on using string we have to do a little work.

If we want to pass string to the constructor we should parse the string to numerical version and push to our stack.
```C++

        for(int i = (size - 1); i > -1 && i >= size - 9; i--){
            if (StrInt[i] < '0' || StrInt[i] > '9') break;
            num += (StrInt[i] - '0') * prefix;
            prefix *= 10;
            len++;
        }
```
In here we try to iterator over each character, first check if input format is correct then by each jump our prefix multiply by 10 (decimal value place) and sum up with previous result;
i.e. 11111 parsed into 1, 10, 100, 1000, 10000 respectively.
# Operators
Well let's move on operators; this part is little bit tricky. :)
## Addition
There's 2 main operator initialization, You intend to sum up two BigInt type or one BigInt object while the other one is just a number in range of long long type.
And of course 
```C++
    // 2 Obj
    BigInt operator+  (BigInt const &) const;
    BigInt &operator+= (BigInt const);
    // Long Long + obj
    BigInt operator+  (long long const &) const;
    BigInt &operator+= (long long);
```
