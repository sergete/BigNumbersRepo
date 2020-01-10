/**
 * Calculate remainder of divide a9999 between 2^20-1
 * Where a1 = 5 and a2 = 13
* and an = an-1 + 2*an-2
                       * The serie is equal to multiply the obtained number by 2 and sum or subtract by 3 depending if the index
* of the next number is is even (sum 3) or odd (subtract 3)
* @author Sergio Sánchez-Uran López
* */

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long l;

const int MAX_ITERATIONS = 9999;

/**
 * Class to process all the mathematical operations to calculate final number and final remainder solution
 * */
class MathOperations{
    string finalNumber;
    string finalMod;

public:
    MathOperations(): finalNumber(""), finalMod(""){}
    MathOperations(string newNumber): finalNumber (newNumber), finalMod("0"){}

    const string &getNumber() const {
        return this->finalNumber;
    }

    void setNumber(const string &number) {
        MathOperations::finalNumber = number;
    }

    const string &getFinalMod() const {
        return finalMod;
    }

    void setFinalMod(const string &finalMod) {
        MathOperations::finalMod = finalMod;
    }

    friend ostream &operator<<(ostream &os, const MathOperations &operations) {
        os << "finalNumber: " << operations.finalNumber << "\n" << "finalMod: " << operations.finalMod;
        return os;
    }

    template<class T>
    void operator +=(T numberToSum){
        string sumNumber = std::to_string(numberToSum);
        int plus = atoi(sumNumber.c_str());

        int size = this->finalNumber.length();
        int carry = 0;
        int add = (this->finalNumber[size - 1]-'0')+(plus);
        std::string resultado = std::to_string(add);

        for(int i = size - 2 ; i >= 0; i--){
            if (add >= 10)
            {
                add = add % 10;
                carry = 1;
            }
            else
                carry = 0;

            add = this->finalNumber[i]-'0' + carry;
            resultado += std::to_string(add);
        }

        if(carry != 0){
            resultado += std::to_string(carry);
        }

        std::reverse(resultado.begin(), resultado.end());

        this->finalNumber = resultado;
    }

    template<class T>
    void operator -=(T numberToSubtract){
        string dimNumber = std::to_string(numberToSubtract);
        int minus = atoi(dimNumber.c_str());

        int size = this->finalNumber.length();
        int carry = 0;
        int sub = (this->finalNumber[size - 1] - '0')-(minus);
        std::string resultado = std::to_string(sub);

        for(int i = size - 2 ; i >= 0; i--){
            if (sub < 0)
            {
                sub = sub + 10;
                carry = 1;
            }
            else
                carry = 0;

            sub = this->finalNumber[i]-'0' - carry;
            resultado += std::to_string(sub);
        }

        std::reverse(resultado.begin(), resultado.end());

        this->finalNumber = resultado;
    }

    template<class T>
    void operator *=(T numberToMultiply){
        string mulNumber = std::to_string(numberToMultiply);
        int mul = atoi(mulNumber.c_str());

        std::string resultado = "";
        int carry = 0;

        for(int i = this->finalNumber.length() - 1; i >= 0 ; i--){
            int num = this->finalNumber[i] - '0';
            num = (num * mul) + carry;
            carry = num/10;
            num %= 10;
            resultado += std::to_string(num);
        }

        if(carry != 0){
            resultado += std::to_string(carry);
        }

        std::reverse(resultado.begin(), resultado.end());

        this->finalNumber = resultado;
    }

    template<class T>
    void operator %=(T numberToDivide){
        string mulNumber = std::to_string(numberToDivide);
        l div = stoll(mulNumber);

        // Store the modulus of big number
        l mod = 0;

        // Do step by step division
        for (int i = 0; i < this->finalNumber.length(); i++) {

            int digit = this->finalNumber[i] - '0';

            // Update modulo by concatenating
            // current digit.
            mod = mod * 10 + digit;

            // Update quotient
            int quo = mod / div;

            // Update mod for next iteration.
            mod = mod % div;
        }

        this->finalMod = to_string(mod);
    }

};

/**
* Calculate final serie using MathOperations class
 * @param N2 is the second number of the serie in this case = 13
 * @param divisor number to divide to get remainder
 * @param iterations
 * @param num to multiply
* */
void CalculateSerie(std::string N2, l divisor, int iterations = 50, int num = 2){

    MathOperations *res = new MathOperations(N2);
    //if we want to calculate num 9999 and we have N1 and N2 then the initial iteration is 3 to MAX_ITERATIONS 9999
    int startIndex = 3;
    //constant number to sum or subtract
    const int sumOrDim = 3;

    for(int i = startIndex ; i <= iterations; i++){
        //Multiply by 2 : n1 = an-2
        *res *= num;
        if(i % 2 == 0){
            //sum
            *res += sumOrDim;
        }
        else{
            //subtract
            *res -= sumOrDim;
        }
    }

    *res %= divisor;

    cout << "iterations: " << MAX_ITERATIONS << " : \n" << *res << endl;
}

int main() {
    //We start the operations calculating N3 like N2 * 2 - 3 and N4 = N3 * 2 + 3...
    std::string N2 = "13";

    //divisor
    l divisor = std::pow(2,20)-1;
    cout << "\nDivisor = " << divisor << endl << endl;
    CalculateSerie(N2, divisor, MAX_ITERATIONS);

    std::cout << "press enter to end" << std::endl;
    std::cin.ignore();
    return 0;
}