#include "../include/BigInt.hpp"

//Constructor
BigInt::BigInt(std::string StrInt){

    int size = StrInt.length();

    base = BigInt::bdefault;
    isPositive = (StrInt[0] != '-');
    
    while (true){
        if(size < 1) break;
        if(!isPositive && size < 2) break;

        int len(0), num(0) ,prefix(1);

        for(int i = (size - 1); i > -1 && i >= size - 9; i--){
            if (StrInt[i] < '0' || StrInt[i] > '9') break;
            num += (StrInt[i] - '0') * prefix;
            prefix *= 10;
            len++;
        }
        
        numbs.push_back(num);
        size -= len;
    }
    
}

BigInt::BigInt(){
        isPositive = true;
        base = BigInt::bdefault;
}
//Addition
BigInt BigInt::operator+ (long long const &b) const{
        
        BigInt c = *this;
        c += b;
        return c;
}

BigInt &BigInt::operator+= (long long b){

    std::vector<int>::iterator iter = this->numbs.begin();
    
   do{
       if(iter != this->numbs.end()){
            *iter += b % base;
            b /= base;
            b += *iter / base;
            *iter %= base;

            iter++;
       }
       else{
           numbs.push_back(0);
           iter = numbs.end() - 1;
       }
    }while(b);     

    return *this;        
   } 
BigInt BigInt::operator+(BigInt const &b) const{
    
    BigInt c  = *this;
    c += b;
    return c;
}
BigInt &BigInt::operator+=(BigInt const &b){
    if(b.isPositive){return *this -= b;}

    std::vector<int>::iterator it1 = this->numbs.begin();
    std::vector<int>::const_iterator it2 = b.numbs.begin();

    int sum = 0;
    while(it1 != numbs.end() || it2 != b.numbs.end()){
        if(it1 != numbs.end())
            sum += *it1;
        else
            numbs.push_back(0), it1 = numbs.end() - 1;
        
        if(it2 != b.numbs.end())
            sum += *it2, ++it2;

        *it1 = sum % base; ++it1;
        sum /= base;
    }
    if(sum) numbs.push_back(1);

    return *this;
}
//Subtraction
BigInt BigInt::operator- (BigInt const &nm) const{

    BigInt x = *this;
    x -= nm;
    return x; 
}
BigInt &BigInt::operator-= (BigInt const &nm){
    std::vector<int>::iterator iter1 = numbs.begin(); 
    std::vector<int>::const_iterator iter2 = nm.numbs.begin();
    int diff = 0;
    while (iter1 != numbs.end() || iter2 != nm.numbs.end()){
        if(iter1 != numbs.end())
            diff += *iter1, ++iter1;
        if(iter2 != nm.numbs.end())
            diff -= *iter2, ++iter2; 
        if(diff < 0)
            *(iter1 - 1) = diff + base ,diff = -1;
        else
            *(iter1-1) = diff % base, diff /= base;
        if(diff < 0) isPositive = false;
    }
        
        while (numbs.size()){
            iter1 = numbs.end() - 1;
            if(!*iter1) numbs.pop_back();
            else break;
        }

    return *this;
        
}

//Multiply
BigInt BigInt::operator*(BigInt const &n) {
    
    std::vector<int>::iterator iter1 = this->numbs.begin();
    std::vector<int>::const_iterator iter2 = n.numbs.begin();
    BigInt c;
    for(;iter1 != numbs.end(); ++iter1)
        for(iter2 = n.numbs.begin(); iter2 != n.numbs.end(); iter2++){
            
            c += (long long) (*iter1) * (*iter2);

        }
        
    return c;
}
BigInt BigInt::operator*(long long const &b){
    BigInt c = *this;
    c *= b;
    return c;
}
BigInt &BigInt::operator*= (int const &a){
    std::vector<int>::iterator it = numbs.begin();
    long long res = 0;
    while (it != numbs.end()) {
        res += (long long) (*it) * a;     
        *it = res % base;
        res /= base;
        it++;
    }
    if(res) numbs.push_back(int (res));

    return *this;
}
BigInt &BigInt::operator*= (BigInt const &b){
    *this = *this * b;

    return *this;
} 

//Power
BigInt &BigInt::pow (int const &n){
    std::map<int ,BigInt> lkp;
    if(!(n&1) && !isPositive) isPositive = true;
    *this = pow(n, lkp);
    return *this;
}
BigInt BigInt::pow (int const &pwr ,std::map<int, BigInt> &lkp){
    if (pwr == 1) return *this;
    if (lkp.count(pwr)) return lkp[pwr];

    int closestPower = 1;
    while (closestPower < pwr) closestPower <<= 1;
    closestPower >>= 1;

    if (pwr == closestPower) lkp[pwr] = pow(pwr/ 2, lkp) * pow(pwr / 2, lkp);
    else lkp[pwr] = pow(closestPower, lkp) * pow(pwr- closestPower, lkp);

    return lkp[pwr];
}
// Input And Outpus
std::ostream &operator <<(std::ostream &o, BigInt const &n){
    if (!n.numbs.size()) return o << 0;
    int i = n.numbs.size() - 1;
    for (; i>=0 && n.numbs[i] == 0; --i);

    if (i == -1) return o << 0;
    if (!n.isPositive) o << '-';

    std::vector<int>::const_reverse_iterator it = n.numbs.rbegin() + (n.numbs.size() - i - 1);

    o << *it++;
    for (; it != n.numbs.rend(); ++it) {
        for (int i(0), len = n.seg_leg(*it); i < 9 - len; ++i) o << '0';
        if (*it) o << *it;
    }
    return o;

}
std::istream &operator >>(std::istream &in, BigInt &nm){
    std::string str;
    in >> str;
    nm = str;
    return in;
}
//Initialize
BigInt BigInt::operator= (const long long &a){
    
    numbs.clear();
    long long ll = a;
    do{
        numbs.push_back(int (ll % base));
        ll /= base;
    }while (ll != 0);

    return *this;
}
uint8_t BigInt::seg_leg(int a) const{
    uint8_t len = 0;
    while(a)
        a /= 10, len++;
    return len;
}



int main(){
    BigInt b,a;
    a = 123456789012;
    b = 123455888880;
    std::cout << (a + b) << std::endl;
    return EXIT_SUCCESS;

}