# README 
 
**In this file you'll find the documentation for the bigint class, which is a class that implements infinite-precision integers**

## Overview

The class bigint is an implementation of infinite-precision integers using strings.  It supports various arithmetic operations, including addition, subtraction, and multiplication, as well as comparison operations. Additionally, it includes utility functions for handling large integers.The implementation ensures proper handling of negative integers and performs input validation to ensure the integrity of the stored data.The class provides a set of constructors and overloaded operators to facilitate the creation and manipulation of bigint instances. Operations like addition, subtraction, and multiplication are implemented as friend functions to allow seamless usage with other bigint instances.

## Private members

The only class private member is called "biginteger" and it stores the integer value as a string. So, when in the following documentation we refer to "string of the bigint object" we mean the private data member that stores the integer number of the object as a string.

## Public members
All the member functions of the class are declared as public.

## Constructors

The class has three constructors:

* The default constructor that takes no arguments and initializes the integer as zero:

```cpp
bigint()
    {
        biginteger = "0";
    }
```

* The constructor that takes a 64-bit integer as argument. The constructor transform that integer into a string using the `stoi()` function:
  
```cpp
bigint(const int64_t x_);
```  

* The constructor that takes a string as argument. The constructor uses the member function `set_string` to check if the string passed is a valid integer, and then store the value as the private member of the class. If the string given is not a valid integer, a `invalid_argument error` is thrown.

```cpp
bigint(const string &x_);
``` 

## Member functions

The first member function of the class is the `set_string` function. This function is used to assign a given string to the private data member of a bigint object and properly check if the string is a valid integer.

```cpp
void set_string(const string &x_)
```

This function is also used by the overloaded assignment operator `=` that gives the private data member of a bigint object the value of a given string. This ensures that the assignment operator ensures the reliability of the data.

Then, three other member functions of the class are overloaded versions for the assignment operator for bigint objects. Let's start with:

```cpp
bigint &operator=(const bigint &a);
```

This member function takes as argument a constant reference to an `bigint` object and assigns its value to the current object. Internally, what this function does is to use the string assignment operator to give the value of the private member of `a` to the current bigint object.

As usual for integer manipulation, if we have two integers `i`,`j`, we would like to use the assignment operator as `i=j`, but we also would like to use it as e.g. `i=5`. Since in our case the bigint object can receive 64-bit integers or integers as string, then we have to define two more overloads for the assignment operator:
  
```cpp
bigint &operator=(const int64_t &i);
```

This member function takes as argument a constant reference to a 64-bit integer object and assigns its value to the current object. Internally, what this function does is to transform the integer to a string using the `to_string` function and assign the value to the current bigint object.

```cpp
bigint &operator=(const string &s);
```

This member function takes as argument a constant reference to string and assigns its value to the current object. Internally, what this function does is to give the value of the string to the private data member of the current object.

The last member function of the class is called `erase_left_zeros`:

```cpp
bigint &erase_left_zeros();
```

This function takes a `bigint` object and erase all the left zeros it has. This will be useful when using the subtraction operator, since as we gonna se later, to sum or subtract two bigint objects we will have to make their string of the same size, therefore, the result of something like 20-15=05 which then we use the function `erase_left_zeros` to get rid of the left zero.

## Friend functions

### Comparison Operators

This class implements comparison operators for integers. The first comparison operator defined is the equality operator.

```cpp
friend bool operator==(const bigint &lhs, const bigint &rhs);
```

This operator takes two constant references to `bigint` object and compares them, returning a `boolean` object, true if the objects are equal, false otherwise. This is done by comparing character by character the private member of each object.

The second comparison operator defined is the less-than operator.

```cpp
friend bool operator<(const bigint &lhs, const bigint &rhs);
```

This operator takes two constant references to `bigint` object and compares them, returning a `bool` object, true if lhs is less-than rhs and false otherwise. This function is slightly more elaborated than the equality comparison.

First, this function evaluates if one of the bigint objects is negative and the other no by looking at the first character of the private data member of each object. If lhs is negative and rhs is not, then it returns true, false in the other way.

Then the operator considers if both objects are negative or positive. Assuming both are positive, the function compares their private members character by character. This comparison involves transforming each character into an integer and utilizing the standard `<` operator for integers. To enhance efficiency, the function employs a for loop that iterates through the characters one at a time, starting with the character containing the largest digit of the integer number.

If the first character of `rhs` is less than the first character of `lhs`, the function returns true. Conversely, if the first digit of `lhs` is greater than the first digit of `rhs`, it returns false. In the case of equality, a `continue` statement is used to proceed with the comparison of subsequent characters.

The rest of comparison operators are defined as external function acting on objects of the class and will be discussed later.

### Arithmetic Operators

For readability and optimization reasons, two auxiliary arithmetic functions were defined, `unsigned_sum` and `unsigned_subtraction`. The former, is a function that has the basic algorithm to the summation of positive integer, and the later has the basic algorithm for the subtraction of positive integers given that the result is also positive. In our implementation both function had to be a friend function instead of a member functions since we need direct manipulation to the objects instead of only the private data members. Besides, neither of the two arguments are taken as `const`, since for the summation and subtraction algorithm we may need to make changes in both, however, the algorithms guarantee that the second object is the same after the function. Let's first explain `unsigned_sum`:

```cpp
friend void unsigned_sum(bigint &x, bigint &y);
```

This function takes two `bigint` objects by reference, adds them, and stores the result in the first bigint object. The addition follows the conventional method for summing two positive integers, involving a character-by-character addition of their string representations, starting with the units, then the tens, and so on.

However, a challenge arises when the strings of the two bigint objects have different sizes. In such cases, a straightforward addition is not viable. For instance, consider a bigint `x` with the private member "45" and another bigint `y` with the private member "5". Adding the first characters of `x` and `y` without considering their sizes would result in combining a digit from the tens place and a digit from the units place, leading to an incorrect sum. To address this, we ensure both strings are of the same size.

In our implementation, achieving equal-sized strings involves appending zeros to the left of the string with the smaller size. Once this alignment is completed, the summation proceeds character by character in the usual manner. An essential consideration is the use of an if-else statement to assess whether the sum of two digits exceeds ten. If this is the case, only the unit digit is retained, and an auxiliary variable named `tens` is introduced. `tens` assumes a value of 1 and is added to the summation of the next digit in the usual fashion.

Now, consider the `unsigned_subtraction`

```cpp
    friend void unsigned_subtraction(bigint &x, bigint &y);
```

This function takes two `bigint` objects by reference, subtracts them (`x-y`), and stores the result in the first bigint object. The subtraction adheres to the standard method for subtracting two positive integers, involving a character-by-character subtraction of their string representations, starting with the units, then the tens, and so on.

To ensure proper execution, the function addresses the scenario where the integers have different sizes, employing the same method as the summation to align their sizes if needed. Additionally, the function considers a crucial condition for applying the usual subtraction algorithm: the first number must always be greater than the second. Consequently, an if-else statement is implemented. If `x` is greater than `y`, the function executes `(x-y)` and stores the result in `x`. Conversely, if `x` is less than `y`, it performs `(y-x)` and stores the negative of the result in `x`.

Assuming `x` is greater than `y` and both have the same size, the function proceeds with digit-by-digit subtraction of the strings. This involves transforming each character into an integer, subtracting them, and then converting the result back to a string. A noteworthy consideration is made when the result of a subtraction is less than zero. In such cases, the function adds 10 to the result and assigns the value of -1 to an auxiliary variable named `tens`. Subsequently, `tens` is added to the result of the next digit subtraction.

Even though this functions work correctly for positive integers, we have to define the overloaded operators `+=`,`-=`,`*=` for both positive and negative integers. The difficulty on this comes from the fact that the usual character by character summation can not be done for negative numbers, since one can not transform the minus sign `-` into a number using the `stoi` function. For that reason we define the overloaded operators `+=` and `-=` using mutual recursion.

```cpp
friend bigint &operator+=(bigint &x, bigint &y);
friend bigint &operator-=(bigint &x, bigint &y);
```

These functions take two `bigint` objects by reference, add (subtract) them, and store the result in the first `bigint` object. Similar to the reasoning explained earlier, the object `y` is not declared as `const`. When both bigint objects are positive, the `+=` (`-=`) operator simply calls the function `unsigned_sum` (`unsigned_subtraction`).

Now, let's delve into the distinct cases for the `+=` operator. If `x` is positive and `y` is negative, the operator enters an if statement that removes the negative sign from `y`, calls the function `unsigned_subtraction(x, y)` and returns `x`. On the other hand, if `x` is negative and `y` is positive, another if statement is triggered, eliminating the negative sign from `x`, calling the function `unsigned_subtraction(x, y)` and returning -x. Finally, if both `x`,`y` are negative, a third if statement is executed that erases both minus signs, calls the function `unsigned_sum(x,y)` , uses the unary operator `-` (explained later) to give the minus sign back to `y` and to `x` and returns x. A parallel process is followed for the -= operator, carefully considering the various scenarios based on the signs of the integers involved.

With the `+=` sign already define we can use it to define the `*=` operator.

```cpp
friend bigint &operator*=(bigint &x, bigint &y);
```

For the sake of simplicity, we define the multiplication assignment operator as a repeated sum. This function takes two `bigint` objects by reference, multiplies them, and stores the result in the first `bigint` object.

Initially, the operator checks whether one of the objects has a value of zero. If this is the case, it assigns the value `0` to `x` and returns it. Following a similar approach to the `+=` operator, the `*=` operator examines the signs of the two `bigint` objects. Based on their signs, a corresponding code block is executed. Broadly, the operator removes the minus sign from the objects and then executes a for loop that adds `x` to itself `y` times.

Subsequently, the operator restores the minus sign to the objects and the result, considering the sign rules to determine whether the result should have a minus sign or not.

Finally, for the arithmetic friend functions we define the negation operator: 

```cpp
    friend bigint operator-(bigint a);
```

This operator takes a copy of a `bigint` object and returns that copy with the opposite sign as the original object. This is done by taking the first two characters of the string, transforming them to integers, then multiplying the result by -1 and transforming it back to string.

### Insertion operator

Also as a friend function we defined the interstion operator:

```cpp
    friend ostream &operator<<(ostream &out, const bigint &a);
```

This operator takes as arguments a `ostream` object and a constant `bigint` object passed by reference. The operator just takes advantage of the insertion `<<` operator for strings to print the private data member of the `bigint` object.

## External functions

### Comparison Operators

With the help of the already defined `==` and `<` operators, we define the rest of comparison functions as external functions.

```cpp
bool operator!=(const bigint &lhs, const bigint &rhs);
bool operator>(const bigint &lhs, const bigint &rhs);
bool operator<=(const bigint &lhs, const bigint &rhs);
bool operator>=(const bigint &lhs, const bigint &rhs);
```

All these functions take two `bigint` `const` objects by reference and return a boolean object. First, the `!=` checks if the two objects are different, returning true if they are, and false otherwise. This functions is just defined as the negation of the `==` operator. Second, the operator "bigger-than" `>` is defined, which returns true if `lhs` is bigger-than `rhs` and false otherwise. For that purpose, the function uses the negation of the `<`. Besides, in the case they are equal, the function returns false.

For the `<=`, `>=` operators, we only combine the `<`,`>` with the `==` operator.

### Arithmetic operators

Finally, we define the operators `+`, `-` and `*` as external functions.

```cpp
bigint operator+(bigint x, bigint &y);
bigint operator-(bigint x, bigint &y);
bigint operator*(bigint x, bigint &y);
```

The three operators take as arguments a copy of a `bigint` object `x` and other `bigint` object as reference. They return the copy of `x` with the modification given by the corresponding operator. The definitions of these functions is very simple and just make use of the previously defined `+=`,`-=`,`*=`. Remember that, the object `y` is not passed as `const` because, as explained before, to use `+=`,`-=`,`*=` we need to be able to modify `y`, however, the algorithm guarantees that at after the operator is used, `y` stays the same.
