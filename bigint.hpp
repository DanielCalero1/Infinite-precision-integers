#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <typeinfo>
using namespace std;

/**
 * @brief A class representing arbitrary-precision integers (bigint).
 *
 * The `bigint` class allows the representation and manipulation of integers with
 * arbitrary precision. It supports various arithmetic operations, including
 * addition, subtraction, and multiplication, as well as comparison operations.
 * Additionally, it includes utility functions for handling large integers.
 *
 * @note The implementation ensures proper handling of negative integers and
 *       performs input validation to ensure the integrity of the stored data.
 *
 * @details The class provides a set of constructors and overloaded operators to
 *          facilitate the creation and manipulation of bigint instances.
 *          Operations like addition, subtraction, and multiplication are implemented
 *          as friend functions to allow seamless usage with other bigint instances.
 */
class bigint
{

public:
    /**
     * @brief Default constructor initializing the bigint to 0.
     */
    bigint()
    {
        biginteger = "0";
    }
    /**
     * @brief Constructor initializing the bigint with a 64-bit integer.
     *
     * @param a The 64-bit integer to initialize the bigint with.
     */
    bigint(const int64_t x_)
    {
        biginteger = to_string(x_);
    }
    /**
     * @brief Set function that stores the value of a given integer passed as string to the private
     * member of the bigint object.
     *
     * @param s The string to initialize the bigint with.
     *
     * @note The implementation ensures proper handling of negative integers and
     * performs input validation to ensure the integrity of the stored data. If string with an
     * invalid integer is give, an invalid_argument error is thrown.
     */
    void set_string(const string &x_)
    {
        if (x_[0] == '-')
        {
            for (uint64_t i = 1; i < x_.size(); i++)
            {
                try
                {
                    stoi(string(1, x_[i]));
                }
                catch (const invalid_argument &e)
                {
                    throw invalid_argument("invalid integer");
                }
            }
        }
        else
        {
            for (uint64_t i = 0; i < x_.size(); i++)
            {
                try
                {
                    stoi(string(1, x_[i]));
                }
                catch (const invalid_argument &e)
                {
                    throw invalid_argument("invalid integer");
                }
            }
        }
        biginteger = x_;
    }
    /**
     * @brief Constructor initializing the bigint with a string.
     *
     * @param a The string to initialize the bigint with.
     * @note The implementation ensures proper handling of negative integers and
     * performs input validation to ensure the integrity of the stored data. If string with an
     * invalid integer is give, an invalid_argument error is thrown.
     */
    bigint(const string &x_)
    {
        set_string(x_);
    }
    /**
     * @brief Copy constructor creating a new bigint object from another bigint.
     *
     * @param other The bigint object to copy.
     */
    bigint(const bigint &other) : biginteger(other.biginteger) {}
    /**
     * @brief Assignment operator for bigint objects.
     *
     * @param a The bigint object to assign.
     *
     * @return Reference to the assigned bigint object.
     */
    bigint &operator=(const bigint &a);
    /**
     * @brief Overloaded assignment operator..
     *
     * @param s The string that contains the integer to assign.
     *
     * @return Reference to the assigned bigint object.
     */
    bigint &operator=(const string &s);
    /**
     * @brief Assignment operator for bigint objects.
     *
     * @param i  The 64-bit integer to assign.
     *
     * @return Reference to the assigned bigint object.
     */
    bigint &operator=(const int64_t &i);
    /**
     * @brief Equality comparison operator for bigint objects.
     *
     * @param lhs The left-hand-side bigint object to compare.
     *
     * @param rhs The right-hand-side bigint object to compare.
     *
     * @details The objects are equal if their private data member storing the integer is the same.
     *
     * @return A boolean object, true if the objects are equal, false if the objects are not.
     */
    friend bool operator==(const bigint &lhs, const bigint &rhs);
    /**
     * @brief Less-than comparison operator for bigint objects.
     *
     * @param lhs The left-hand-side bigint object to compare.
     *
     * @param rhs The right-hand-side bigint object to compare.
     *
     * @details lhs is said to be less than rhs if the integer it represents is less than the integer
     * rhs represents
     *
     * @return A boolean object, true if lhs is less than rhs, false otherwise
     */
    friend bool operator<(const bigint &lhs, const bigint &rhs);
    /**
     * @brief Addition assignment operator for bigint objects.
     *
     * @param x The left bigint.
     *
     * @param y The right side bigint.
     *
     * @return Reference to the modified left-hand side bigint.
     */
    friend bigint &operator+=(bigint &x, bigint &y);
    /**
     * @brief Unsigned addition operation for bigint instances.
     *
     * @param x The left-hand side bigint.
     *
     * @param y The right-hand side bigint.
     *
     * @details This function has the basic algorithm for the summation of two integers. The result
     * of the summation lhs+rhs is stored in lhs. Even though rhs is not defined as const due to the
     * nature of the algorithm, it is not modified after the function implementation. This function
     * is used on other basic functions of the class such ass +=,+,*=,* to optimize calculations and
     * increase readability.
     */
    friend void unsigned_sum(bigint &x, bigint &y);
    /**
     * @brief Unsigned subtraction operation for bigint instances.
     *
     * @param x The left bigint.
     *
     * @param y The right bigint.
     *
     * @details This function has the basic algorithm for the subtraction of two integers.
     * The result of the subtraction lhs-rhs is stored in lhs. Even though rhs is not defined as
     * const due to the nature of the algorithm, it is not modified after the function implementation.
     * This function is used on other basic functions of the class such ass -=,- to increase readability.
     */
    friend void unsigned_subtraction(bigint &x, bigint &y);
    /**
     * @brief Subtraction assignment operator for bigint objects.
     *
     * @param x The left-hand side bigint.
     *
     * @param y The right-hand side bigint.
     *
     * @return Reference to the modified left-hand side bigint.
     */
    friend bigint &operator-=(bigint &x, bigint &y);
    /**
     * @brief Multiplication assignment operator for bigint objects.
     *
     * @param x The left-hand side bigint.
     *
     * @param y The right-hand side bigint.
     *
     * @return Reference to the modified left-hand side bigint.
     */
    friend bigint &operator*=(bigint &x, bigint &y);
    /**
     * @brief A function that eliminates the left zeros of a bigint object.
     * This is useful cause after a summation or subtraction operation some the result could be
     * e.g. "002", this function then erase the left zeros of the result.
     * @param a A reference to a bigint object
     * @return The same bigint object
     */
    bigint &erase_left_zeros();
    /**
     * @brief Output stream operator for bigint objects.
     *
     * @param os The output stream.
     * @param a The bigint to be output.
     * @return Reference to the output stream.
     */
    friend ostream &operator<<(ostream &out, const bigint &a);
    /**
     * @brief Negation operator for bigint objects.
     *
     * @param a A copy of the bigint object
     *
     * @return The copy of the bigint object but with a minus sign.
     */
    friend bigint operator-(bigint a);

private:
    string biginteger = "0";
};
bigint &bigint::erase_left_zeros()
{
    if (biginteger.size() > 1)
    {
        for (size_t i = 0; i < biginteger.size(); i++)
        {
            if (biginteger[0] == '0')
            {
                biginteger.erase(0, 1);
            }
            else
            {
                break;
            }
        }
    }
    return *this;
};
bigint &bigint::operator=(const bigint &y)
{
    biginteger = y.biginteger;
    return *this;
}
bigint &bigint::operator=(const string &s)
{
    set_string(s);
    return *this;
}
bigint &bigint::operator=(const int64_t &i)
{
    biginteger = to_string(i);
    return *this;
}

bool operator==(const bigint &lhs, const bigint &rhs)
{
    if (lhs.biginteger.size() != rhs.biginteger.size())
    {
        return false;
    }
    for (size_t i = 0; i < lhs.biginteger.size(); i++)
    {
        if (lhs.biginteger[i] != rhs.biginteger[i])
        {
            return false;
        }
    }
    return true;
}
/**
 * @brief Inequality comparison operator for bigint instances.
 *
 * @details Checks whether two bigint instances are not equal.
 *
 * @param x The left-hand side bigint.
 * @param y The right-hand side bigint.
 * @return True if the bigints are not equal, false otherwise.
 */
bool operator!=(const bigint &lhs, const bigint &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const bigint &x, const bigint &y)
{

    if (x.biginteger[0] == '-' && y.biginteger[0] != '-')
    {
        return true;
    }
    else if (y.biginteger[0] == '-' && x.biginteger[0] != '-')
    {
        return false;
    }
    else
    {
        if (y.biginteger[0] == '-' && x.biginteger[0] == '-')
        {
            if (x.biginteger.size() < y.biginteger.size())
            {
                return false;
            }
            else if (y.biginteger.size() < x.biginteger.size())
            {
                return true;
            }
            else
            {
                for (size_t i = 1; i < x.biginteger.size(); i++)
                {
                    if (stoi(string(1, x.biginteger[i])) < stoi(string(1, y.biginteger[i])))
                    {
                        return false;
                    }
                    else if (stoi(string(1, y.biginteger[i])) < stoi(string(1, x.biginteger[i])))
                    {
                        return true;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        else
        {
            if (x.biginteger.size() < y.biginteger.size())
            {
                return true;
            }
            else if (y.biginteger.size() < x.biginteger.size())
            {
                return false;
            }
            else
            {
                for (size_t i = 0; i < x.biginteger.size(); i++)
                {
                    if (stoi(string(1, x.biginteger[i])) < stoi(string(1, y.biginteger[i])))
                    {
                        return true;
                    }
                    else if (stoi(string(1, y.biginteger[i])) < stoi(string(1, x.biginteger[i])))
                    {
                        return false;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
    return false;
}
/**
 * @brief Bigger-than comparison operator for bigint objects.
 *
 * @param lhs The left-hand-side bigint object to compare.
 *
 * @param rhs The right-hand-side bigint object to compare.
 *
 * @details lhs is said to be greater than rhs if the integer it represents is bigger than the integer
 * rhs represents
 *
 * @return A boolean object, true if lhs is bigger than rhs, false otherwise
 */
bool operator>(const bigint &lhs, const bigint &rhs)
{
    if (lhs == rhs)
    {
        return false;
    }
    else
    {
        return !(lhs < rhs);
    }
};
/**
 * @brief Less or equal to comparison operator for bigint objects.
 *
 * @param lhs The left-hand-side bigint object to compare.
 *
 * @param rhs The right-hand-side bigint object to compare.
 *
 * @details the function uses the pre-define less than and equal to operators.
 *
 * @return A boolean object, true if lhs is les or equal to rhs, false otherwise
 */
bool operator<=(const bigint &lhs, const bigint &rhs)
{
    return ((lhs < rhs) || (lhs == rhs));
}
/**
 * @brief Bigger or equal to comparison operator for bigint objects.
 *
 * @param lhs The left-hand-side bigint object to compare.
 *
 * @param rhs The right-hand-side bigint object to compare.
 *
 * @details the function uses the pre-define bigger-than and equal-to operators.
 *
 * @return A boolean object, true if lhs is les or equal to rhs, false otherwise
 */
bool operator>=(const bigint &lhs, const bigint &rhs)
{
    return ((lhs > rhs) || (lhs == rhs));
};

bigint operator-(bigint x)
{
    x.biginteger.replace(0, 2, to_string(-1 * stoi(x.biginteger.substr(0, 2))));
    return x;
}

void unsigned_sum(bigint &x, bigint &y) /*Sum of two positive numbers*/
{
    if (x.biginteger.size() <= y.biginteger.size())
    {
        int8_t tens = 0;
        x.biginteger.insert(0, string(y.biginteger.size() - x.biginteger.size(), '0'));
        for (uint64_t i = y.biginteger.size() - 1; i > 0; i--)
        {
            int8_t c = stoi(string(1, x.biginteger[i])) + stoi(string(1, y.biginteger[i]));
            if (c + tens >= 10)
            {
                c -= 10;
                x.biginteger.replace(i, 1, to_string(c + tens));
                tens = 1;
            }
            else
            {
                x.biginteger.replace(i, 1, to_string(c + tens));
                tens = 0;
            }
        }
        int8_t c = stoi(string(1, x.biginteger[0])) + stoi(string(1, y.biginteger[0]));
        x.biginteger.replace(0, 1, to_string(c + tens));
    }
    else
    {
        int8_t tens = 0;
        y.biginteger.insert(0, string(x.biginteger.size() - y.biginteger.size(), '0'));
        for (uint64_t i = y.biginteger.size() - 1; i > 0; i--)
        {
            int8_t c = stoi(string(1, x.biginteger[i])) + stoi(string(1, y.biginteger[i]));
            if (c + tens >= 10)
            {
                c -= 10;
                x.biginteger.replace(i, 1, to_string(c + tens));
                tens = 1;
            }
            else
            {
                x.biginteger.replace(i, 1, to_string(c + tens));
                tens = 0;
            }
        }
        int8_t c = stoi(string(1, x.biginteger[0])) + stoi(string(1, y.biginteger[0]));
        x.biginteger.replace(0, 1, to_string(c + tens));
        y.erase_left_zeros(); // ask if use this is better than passing a copy
    }
}

void unsigned_subtraction(bigint &x, bigint &y) /*Difference of two positive numbers*/
{
    if (x <= y)
    {
        int8_t tens = 0;
        x.biginteger.insert(0, string(y.biginteger.size() - x.biginteger.size(), '0'));
        for (uint64_t i = y.biginteger.size() - 1; i > 0; i--)
        {
            int8_t c = stoi(string(1, y.biginteger[i])) - stoi(string(1, x.biginteger[i]));
            if (c + tens < 0)
            {
                c += 10;
                x.biginteger.replace(i, 1, to_string(c + tens));
                tens = -1;
            }
            else
            {
                x.biginteger.replace(i, 1, to_string(c + tens));
                tens = 0;
            }
        }
        int8_t c = stoi(string(1, y.biginteger[0])) - stoi(string(1, x.biginteger[0]));
        x.biginteger.replace(0, 1, to_string(c + tens));
        x.erase_left_zeros();
        y.erase_left_zeros();
        x = -x;
    }
    else
    {
        int8_t tens = 0;
        y.biginteger.insert(0, string(x.biginteger.size() - y.biginteger.size(), '0'));
        for (uint64_t i = y.biginteger.size() - 1; i > 0; i--)
        {
            int8_t c = stoi(string(1, x.biginteger[i])) - stoi(string(1, y.biginteger[i]));
            if (c + tens < 0)
            {
                c += 10;
                x.biginteger.replace(i, 1, to_string(c + tens));
                tens = -1;
            }
            else
            {
                x.biginteger.replace(i, 1, to_string(c + tens));
                tens = 0;
            }
        }
        int8_t c = stoi(string(1, x.biginteger[0])) - stoi(string(1, y.biginteger[0]));
        x.biginteger.replace(0, 1, to_string(c + tens));
        x.erase_left_zeros();
        y.erase_left_zeros();
    }
}

bigint &operator+=(bigint &x, bigint &y) // I think I can pass "y" as reference
{
    if (x.biginteger[0] == '-' && y.biginteger[0] != '-')
    {
        x.biginteger.erase(0, 1);
        unsigned_subtraction(x, y);
        x = -x;
        return x;
    }
    else if (y.biginteger[0] == '-' && x.biginteger[0] != '-')
    {
        y.biginteger.erase(0, 1);
        unsigned_subtraction(x, y);
        y.biginteger.insert(0, "-");
        return x;
    }
    else if (x.biginteger[0] == '-' && y.biginteger[0] == '-')
    {
        x.biginteger.erase(0, 1);
        y.biginteger.erase(0, 1);
        unsigned_sum(x, y);
        x = -x;
        y = -y;
        return x;
    }
    else
    {
        unsigned_sum(x, y);
        return x;
    }
}
/**
 * @brief Summation operation for bigint instances.
 *
 * @param x The left-hand side bigint.
 *
 * @param y The right-hand side bigint.
 *
 * @details This function computes the summation x+y and returns a new bigint with the result of
 * the sum. This function uses the pre-defined += operator.
 */
bigint operator+(bigint x, bigint &y)
{
    x += y;
    return x;
}

bigint &operator-=(bigint &x, bigint &y)
{
    if (x.biginteger[0] == '-' && y.biginteger[0] != '-')
    {
        y = -y;
        x += y;
        y = -y;
        return x;
    }
    else if (y.biginteger[0] == '-' && x.biginteger[0] != '-')
    {
        y.biginteger.erase(0, 1);
        x += y;
        y.biginteger.insert(0, "-");
        return x;
    }
    else if (x.biginteger[0] == '-' && y.biginteger[0] == '-')
    {
        x.biginteger.erase(0, 1);
        y.biginteger.erase(0, 1);
        unsigned_subtraction(x, y);
        x = -x;
        y = -y;
        return x;
    }
    else
    {
        unsigned_subtraction(x, y);
        return x;
    }
}
/**
 * @brief Subtraction operation for bigint instances.
 *
 * @param x The left-hand side bigint.
 *
 * @param y The right-hand side bigint.
 *
 * @details This function computes the subtraction x-y and returns a new bigint with the result of
 * the subtraction. This function uses the pre-defined -= and erase_left_zeros operators.
 */
bigint operator-(bigint x, bigint &y)
{
    x -= y;
    x.erase_left_zeros();
    return x;
}
ostream &operator<<(ostream &out, const bigint &x)
{
    out << x.biginteger;
    return out;
};

bigint &operator*=(bigint &x, bigint &y)
{
    if ((x.biginteger[0] != '0' && y.biginteger[0] == '0'))
    {
        x = 0;
        return x;
    }
    bigint a(1);
    if ((x.biginteger[0] != '-' && y.biginteger[0] == '-'))
    {
        y = -y;
        bigint z = x;
        for (bigint i(1); i < y; unsigned_sum(i, a))
        {
            unsigned_sum(x, z);
        }
        y = -y;
        x = -x;
        return x;
    }
    else if (x.biginteger[0] == '-' && y.biginteger[0] != '-')
    {
        x = -x;
        bigint z = x;
        for (bigint i(1); i < y; unsigned_sum(i, a))
        {
            unsigned_sum(x, z);
        }
        x = -x;
        return x;
    }
    else if (x.biginteger[0] == '-' && y.biginteger[0] == '-')
    {
        x = -x;
        y = -y;
        bigint z = x;
        for (bigint i(1); i < y; unsigned_sum(i, a))
        {
            unsigned_sum(x, z);
        }
        y = -y;
        return x;
    }
    else
    {
        bigint z = x;
        for (bigint i(1); i < y; unsigned_sum(i, a))
        {
            unsigned_sum(x, z);
        }
        return x;
    }
}
/**
 * @brief Multiplication operation for bigint instances.
 *
 * @param x The left-hand side bigint.
 *
 * @param y The right-hand side bigint.
 *
 * @details This function computes the multiplication x*y and returns a new bigint with the result
 * of the multiplication. This function uses the pre-defined *= and operator.
 */
bigint operator*(bigint x, bigint y)
{
    x *= y;
    x.erase_left_zeros();
    return x;
}
