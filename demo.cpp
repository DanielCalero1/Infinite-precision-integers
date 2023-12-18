#include <iostream>
#include "bigint.hpp"
using namespace std;

int main()
{

    bigint A; /*Creating a bigint object using the default constructor*/
    cout << A << "\n";
    int64_t i = 4;
    bigint B(i); /*Creating a bigint object taking a 64-bit integer as argument*/
    cout << B << "\n";
    string s1 = "-5";
    bigint C(s1); /*Creating a bigint object taking a string as argument*/
    cout << C << "\n";
    try
    {
        string s2 = "12oinsdcoi#"; /*The constructor correctly checks if the string is a valid integer*/
        bigint D(s2);
    }
    catch (const invalid_argument &e)
    {
        cout << "Error:" << e.what() << "\n";
    }
    string s3 = "100000000000000000000";
    bigint F(s3); /*The biginter class supports integer numbers out of the precision of the 64-bit
    integer.*/
    cout << F << "\n";
    string s4 = "4000000000000000000000";
    bigint G(s4);
    bigint E = B; /*The class supports the assignment operator "=" between bigint objects*/
    cout << E << "\n";
    E = s3; /*The class supports the assignment operator "=" for strings */
    cout << E << "\n";
    E = 4; /*The class supports the assignment operator "=" for integers*/
    cout << E << "\n";
    cout << "F < G ? " << (F < G) << "\n";   /*The class supports less-than "<" comparison operator*/
    cout << "B > C ? " << (B > C) << "\n";   /*The class supports bigger-than ">" comparison operator*/
    cout << "E == B ? " << (E == B) << "\n"; /*The class supports equality "==" comparison operator*/
    cout << "E != B ? " << (E != B) << "\n"; /*The class supports inequality "!=" comparison operator*/
    string s5 = "45830000000000000000";
    string s6 = "52190000000000000000";
    A = s5;
    B = s6;
    cout << -A << "\n";                 // The class supports the negation operator
    cout << "A+B =? " << A + B << "\n"; // The class supports the addition operator "+"
    A += B;                             // The class supports the addition assignment operator "+="
    cout << A << "\n";
    cout << B << "\n";                  // The object B stays unchanged after the use of the "+=" operator
    cout << "A-B =? " << A - B << "\n"; // The class supports the subtraction operator "-"
    A -= B;                             // The class supports the subtraction assignment operator "-="
    cout << A << "\n";
    cout << B << "\n"; // The object B stays unchanged after the use of the "-=" operator
    string s7 = "2396";
    string s8 = "-47596";
    A = s7;
    B = s8;
    cout << "A*B =? " << A * B << "\n"; // The class supports the multiplication operator "*"
    A *= B;                             // The class supports the multiplication assignment operator "-="
    cout << A << "\n";
    cout << B << "\n"; // The object B stays unchanged after the use of the "*=" operator
}