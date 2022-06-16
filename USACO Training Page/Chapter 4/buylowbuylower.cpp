/*
ID: david.y3
LANG: C++17
TASK: buylow
*/
// NAME                 :   David Shen
// GROUP                :
// LAST MODIFIED        :   16 June 2022
// PROBLEM ID           :   buylow
// PROBLEM DESCRIPTION  :   Determine longest decreasing subset and how many exist
//                          Dynamic programming, BigInt
// SOURCES              :   USACO Website
// PEOPLE WHO HELPED ME :
// PEOPLE I HELPED      :

#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>


// An incomplete BigInt type
class BigInt
{
  public:
    BigInt(long long num = 0) : digits{}
    {
        negative = num < 0;
        if (negative)
        {
            num *= -1;
        }
        if (num == 0)
        {
            digits.push_back(0);
        }
        while (num > 0)
        {
            digits.push_back(num % BASE);
            num /= BASE;
        }
    }

    BigInt(std::string num) : digits{}
    {
        for (auto it = num.rbegin(); it != num.rend(); it++)
        {
            if (*it == '-')
            {
                negative = true;
                break;
            }
            if (*it > '9' || *it < '0')
            {
                throw std::domain_error("Could not parse character into BigInt: " + std::string{*it});
            }
            digits.push_back((*it) - '0');
        }
    }
    BigInt(const BigInt& bi) : digits{bi.getDigitsBackwards()}, negative{bi.isNegative()} {}
    // Operator overloads
    // Casting
    operator std::string() const
    {
        std::string num = (negative) ? "-" : "";
        for (auto it = digits.rbegin(); it != digits.rend(); it++)
        {
            num.push_back(*it + '0');
        }
        return num;
    }
    // Comparisons
    bool operator<=(const BigInt &other) const
    {
        ComparisonState compared = compare(other);
        return compared == ComparisonState::LESS_THAN || compared == ComparisonState::EQUAL;
    }
    bool operator==(const BigInt &other) const
    {
        ComparisonState compared = compare(other);
        return compared == ComparisonState::EQUAL;
    }
    bool operator!=(const BigInt &other) const
    {
        return !(*this == other);
    }
    bool operator>=(const BigInt &other) const
    {
        ComparisonState compared = compare(other);
        return compared == ComparisonState::GREATER_THAN || compared == ComparisonState::EQUAL;
    }
    bool operator<(const BigInt &other) const
    {
        ComparisonState compared = compare(other);
        return compared == ComparisonState::LESS_THAN;
    }
    bool operator>(const BigInt &other) const
    {
        ComparisonState compared = compare(other);
        return compared == ComparisonState::GREATER_THAN;
    }

    // Math operators
    BigInt operator+=(const BigInt &other)
    {
        for (int i = 0; i < other.numDigits(); i++)
        {
            setDigit(i, other.getDigit(i) + getDigit(i));
        }
        return *this;
    }

    BigInt operator+(const BigInt &other) const
    {
        BigInt copy = *this;
        copy += other;
        return copy;
    }

    // Stream operator
    friend std::ostream &operator<<(std::ostream &os, const BigInt &bi);

    // Equals operator
    BigInt& operator=(const BigInt& other)
    {
        set(other);
        return *this;
    }

    BigInt& operator=(long long other)
    {
        return (*this) = BigInt{other};
    }

    // Other methods
    void set(const BigInt &other)
    {
        digits = other.getDigitsBackwards();
        negative = other.isNegative();
    }
    void setDigit(unsigned int index, int value)
    {
        if (index >= digits.size() && value == 0)
        {
            return;
        }
        if (index >= digits.size() && value != 0)
        {
            digits.resize(index + 2, 0);
        }
        if (value >= BASE)
        {
            setDigit(index + 1, getDigit(index + 1) + value / BASE);
            value %= BASE;
        }
        else if (value < 0)
        {
            int count = 0;
            while (value < 0)
            {
                count++;
                value += BASE;
            }
            setDigit(index + 1, getDigit(index + 1) - count);
        }
        digits.at(index) = value;

        unsigned int size = digits.size();

        for (auto it = digits.rbegin(); it != digits.rend(); it++)
        {
            if (*it != 0)
            {
                break;
            }
            size--;
        }
        if (size < digits.size())
        {
            digits.resize(size);
        }
    }
    int getDigit(unsigned int index) const
    {
        if (index >= digits.size())
        {
            return 0;
        }
        return digits.at(index);
    }
    bool isNegative() const
    {
        return negative;
    }
    int numDigits() const
    {
        return digits.size();
    }
    std::vector<uint_fast8_t> getDigitsBackwards() const
    {
        return digits;
    }

  private:
    enum ComparisonState
    {
        LESS_THAN,
        EQUAL,
        GREATER_THAN,
    };
    ComparisonState compare(const BigInt &other) const
    {
        if (isNegative())
        {
            if (!other.isNegative())
            {
                return ComparisonState::LESS_THAN;
            }
            // Both are negative
            if (other.numDigits() < numDigits())
            {
                return ComparisonState::LESS_THAN;
            }
            if (other.numDigits() > numDigits())
            {
                return ComparisonState::GREATER_THAN;
            }
            // Both have the same number of digits
            for (int i = 0; i < numDigits(); i++)
            {
                if (other.getDigit(i) < getDigit(i))
                {
                    return ComparisonState::LESS_THAN;
                }
                else if (other.getDigit(i) > getDigit(i))
                {
                    return ComparisonState::GREATER_THAN;
                }
            }
        }
        else
        {
            if (other.isNegative())
            {
                return ComparisonState::GREATER_THAN;
            }
            // Both are positive
            if (other.numDigits() > numDigits())
            {
                return ComparisonState::LESS_THAN;
            }
            if (other.numDigits() < numDigits())
            {
                return ComparisonState::GREATER_THAN;
            }
            // Both have the same number of digits
            for (int i = 0; i < numDigits(); i++)
            {
                if (other.getDigit(i) > getDigit(i))
                {
                    return ComparisonState::LESS_THAN;
                }
                else if (other.getDigit(i) < getDigit(i))
                {
                    return ComparisonState::GREATER_THAN;
                }
            }
        }
        return ComparisonState::EQUAL;
    }
    std::vector<uint_fast8_t> digits; // Backwards!
    bool negative = false;
    const int BASE = 10;
};
std::ostream &operator<<(std::ostream &os, const BigInt &bi)
{
    os << std::string(bi);
    return os;
}
int longestDecreasing[5000];
BigInt counts[5000];

int main()
{
    std::ifstream fin("buylow.in");
    int n, p;
    std::vector<int> prices;

    fin >> n;

    for (int i = 0; i < n; i++)
    {
        fin >> p;
        prices.push_back(p);
    }
    int maxLen = 1;

    for (int i = 0; i < n; i++)
    {
        longestDecreasing[i] = 1;
        for (int j = 0; j < i; j++)
        {
            if (prices[j] > prices[i])
            {
                longestDecreasing[i] = std::max(longestDecreasing[j] + 1, longestDecreasing[i]);
                maxLen = std::max(maxLen, longestDecreasing[i]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (longestDecreasing[i] == 1)
        {
            counts[i] = 1;
        }
        else
        {
            int last = -1;

            for (int j = i - 1; j >= 0; j--)
            {
                if (prices[j] > prices[i] && longestDecreasing[j] == longestDecreasing[i] - 1 && last != prices[j])
                {
                    counts[i] += counts[j];

                    last = prices[j];
                }
            }
        }
    }
    BigInt count = 0;
    int last = -1;

    for (int i = n - 1; i >= 0; i--)
    {
        if (longestDecreasing[i] == maxLen && last != prices[i])
        {
            count += counts[i];
            last = prices[i];
        }
    }

    std::ofstream fout("buylow.out");
    fout << maxLen << ' ' << count << '\n';
}