//Lecture 5: Big Four
/* Four special functions of any Class */
/* Call to the functions is implicit -> Not explicitly called by name
1. Constructor: Function called RIGHT after an object is created
                ans used to initialize objects of the class.
2. Destructor: Function used to do some "teardown" tasks RIGHT before an object is deleted from memory.
3. Copy Constructor: Variation on the constructor.
    Complex c1(c2); c1 and c2 are both of type Complex
4. Copy assignment operator
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
        }

        //member functions
        void conjugate(){ // a - jb

        }

        void add(){

        }

        double getMagnitude(){
            return 10;
        }
};

int main(int argc, char const *argv[]){
    Complex c; // c is an object of type Complex or c is an instance of Complex
    //c.real = 0; Not allowed because real and imag are private variables
    cout<<c.getMagnitude();

    Complex *b = new Complex{10,20};
    delete b;

    Complex* c1 = new Complex{20,40}; //20 + 40j
    Complex c3(*c1); //20 + 40j
    Complex c4(c); //0 + 0j

    return 0;
}

//Adding two complex numbers together
