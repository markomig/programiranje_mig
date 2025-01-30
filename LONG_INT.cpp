#include <bits/stdc++.h>

using namespace std;
class LONG_INT
{
private:
    bool is_negative;
    vector<int> data;

    static int abs_compare(const LONG_INT& a, const LONG_INT& b)
    {
        if (a.data.size() != b.data.size()) return a.data.size() - b.data.size();
        for (int i = a.data.size() - 1; i >= 0; --i)
        {
            if (a.data[i] != b.data[i]) return a.data[i] - b.data[i];
        }
        return 0;
    }

    static LONG_INT abs(const LONG_INT& x)
    {
        LONG_INT result = x;
        result.is_negative = false;
        return result;
    }

public:
    LONG_INT() : is_negative(false) {}

    LONG_INT(const string& str)
    {
        is_negative = (str[0] == '-');
        for (int i = str.length() - 1; i >= is_negative; --i)
        {
            data.push_back(str[i] - '0');
        }
        if (data.empty())
        {
            data.push_back(0);
            is_negative = false;
        }
    }

    void print() const
    {
        if (is_negative && !(data.size() == 1 && data[0] == 0)) cout << '-';
        for (int i = data.size() - 1; i >= 0; --i)
        {
            cout << data[i];
        }
        cout << endl;
    }

    LONG_INT operator+(const LONG_INT& other) const
    {
        if (is_negative == other.is_negative)
        {
            LONG_INT result;
            result.is_negative = is_negative;
            int carry = 0;
            for (int i = 0; i < max(data.size(), other.data.size()) || carry; ++i)
            {
                int sum = carry;
                if (i < data.size()) sum += data[i];
                if (i < other.data.size()) sum += other.data[i];
                result.data.push_back(sum % 10);
                carry = sum / 10;
            }
            return result;
        }
        else
        {

            if (is_negative)
            {
                return other - (-(*this));
            }
            else
            {
                return *this - (-other);
            }
        }
    }

    LONG_INT operator-() const
    {
        LONG_INT result = *this;
        if (!(data.size() == 1 && data[0] == 0))
        {
            result.is_negative = !is_negative;
        }
        return result;
    }

    LONG_INT operator-(const LONG_INT& other) const
    {
        if (is_negative != other.is_negative)
        {
            return *this + (-other);
        }
        else
        {
            if (abs_compare(*this, other) >= 0)
            {
                LONG_INT result;
                result.is_negative = is_negative;
                int borrow = 0;
                for (int i = 0; i < data.size(); ++i)
                {
                    int left = (i < data.size()) ? data[i] : 0;
                    int right = (i < other.data.size()) ? other.data[i] : 0;

                    int diff = left - right - borrow;
                    if (diff < 0)
                    {
                        diff += 10;
                        borrow = 1;
                    }
                    else
                    {
                        borrow = 0;
                    }
                    result.data.push_back(diff);
                }
                while (result.data.size() > 1 && result.data.back() == 0)
                {
                    result.data.pop_back();
                }
                return result;
            }
            else
            {
                return -(other - *this);
            }
        }
    }

    LONG_INT operator*(const LONG_INT& other) const
    {
        LONG_INT result("0");
        result.is_negative = (is_negative != other.is_negative);
        result.data.resize(data.size() + other.data.size(), 0);

        for (int i = 0; i < data.size(); ++i)
        {
            int carry = 0;
            for (int j = 0; j < other.data.size() || carry; ++j)
            {
                int sum = result.data[i + j] + data[i] * (j < other.data.size() ? other.data[j] : 0) + carry;
                result.data[i + j] = sum % 10;
                carry = sum / 10;
            }
        }

        while (result.data.size() > 1 && result.data.back() == 0)
        {
            result.data.pop_back();
        }

        return result;
    }


    LONG_INT operator/(const LONG_INT& other) const
    {

        LONG_INT result, remainder;
        result.is_negative = (is_negative != other.is_negative);

        for (int i = data.size() - 1; i >= 0; --i)
        {
            remainder.data.insert(remainder.data.begin(), data[i]);
            while (remainder.data.size() > 1 && remainder.data.back() == 0)
            {
                remainder.data.pop_back();
            }
            int count = 0;
            while (abs_compare(remainder, other) >= 0)
            {
                remainder = remainder - abs(other);
                count++;
            }
            result.data.insert(result.data.begin(), count);
        }

        while (result.data.size() > 1 && result.data.back() == 0)
        {
            result.data.pop_back();
        }

        return result;
    }

    bool operator==(const LONG_INT& other) const
    {
        return is_negative == other.is_negative && data == other.data;
    }
};

int NZD_recursive(int a, int b)
{
    if (b == 0)
        return a;
    return NZD_recursive(b, a % b);
}

int NZD(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int NZS(int a, int b)
{
    return (a / NZD(a, b)) * b;
}

int main()
{
    LONG_INT num1("100");
    LONG_INT num2("2");

    (num1 + num2).print();

    (num1 - num2).print();

    (num1 * num2).print();

    (num1 / num2).print();

int num3=64, num4=24;
    cout <<  NZD_recursive(num3, num4) << endl;

    cout <<  NZD(num3, num4) << endl;

    cout << NZS(num3, num4) << endl;


    return 0;
}
