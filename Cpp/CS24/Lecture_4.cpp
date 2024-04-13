//Lecture 4: Object oriented programming
// Object are central to how we organize and think about our code
// - Code objects by their attributes and behaviour
// Example: Complex numbers a + jb, j = sqrt(-1)

//Class is a struct with some functions

class Complex{

    private:
        //member variables
        double real;
        double imag;
    public:
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
    return 0;
}

//Adding two complex numbers together
