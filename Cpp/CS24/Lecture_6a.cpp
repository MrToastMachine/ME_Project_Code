//Lecture 6: Big Four
/*
Automate Compiling C++ Program

*/

#include <iostream>

using namespace std;


class Complex{

    private:
        //member variables
        double real;
        double imag;
    public:
        //constructor: same name as the class. no return type, default provided by c++ is just an empty function.
        /* Can use:
            Complex c(10,10);
            Complex c {10,10}; C++11 syntax
            Complex c;
        */
        Complex(double re=0, double im=0){
            cout<<"Inside the constructor"<<endl;
            // real=imag = 0;
            real = re;
            imag = im;
        }

        //destructor : default provided by c++
        // called RIGHT before an object of type complex is about to be deleted from memory (Stach OR Heap)
        ~Complex(){
            cout<<"Inside the destructor"<<endl;
        }

        Complex(Complex& other){
            real = other.real;
            imag = other.imag;
            cout<<"Inside Copy Constructor"<<endl;
        }

        //Assignment operator (C++ Provides a default version)
        Complex& operator=(Complex& other){
            real = other.real;
            imag = other.imag;
            cout<<"Inside Copy Assignment"<<endl;
            return *this;
        }

        Complex operator+(Complex& other){
            Complex result; //CHECK THIS FUNCTION
            result.real = real + other.real;
            result.imag = imag + other.imag;
            return result;
        }
};

int main(int argc, char const *argv[]){
    Complex c; // c is an object of type Complex or c is an instance of Complex
    //c.real = 0; Not allowed because real and imag are private variables

    Complex *b = new Complex{10,20};
    delete b;

    Complex* c1 = new Complex{20,40}; //20 + 40j
    Complex c3(*c1); //20 + 40j
    Complex c4(c); //0 + 0j

    return 0;
}

//Adding two complex numbers together
