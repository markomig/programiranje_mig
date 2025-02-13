#include <bits/stdc++.h>


using namespace std;

class LONG_INT {
private:
    bool neg;
    vector<int> cifri;

    static int abs_compare(const LONG_INT& a, const LONG_INT& b) {
        if (a.cifri.size() != b.cifri.size()) return a.cifri.size() - b.cifri.size();
        for (int i = a.cifri.size() - 1; i >= 0; --i) {
            if (a.cifri[i] != b.cifri[i]) return a.cifri[i] - b.cifri[i];
        }
        return 0;
    }

    static LONG_INT abs(const LONG_INT& x) {
        LONG_INT rez = x;
        rez.neg = false;
        return rez;
    }

public:
    LONG_INT() : neg(false) {}


    LONG_INT(const string& str) {
        neg = (str[0] == '-');
        for (int i = str.length() - 1; i >= neg; --i) {
            cifri.push_back(str[i] - '0');
        }
        if (cifri.empty()) {
            cifri.push_back(0);
            neg = false;
        }
    }

    void print() const {
        if (neg && !(cifri.size() == 1 && cifri[0] == 0)) cout << '-';
        for (int i = cifri.size() - 1; i >= 0; --i) {
            cout << cifri[i];
        }
        cout << endl;
    }


    LONG_INT operator+(const LONG_INT& o) const {
        if (neg == o.neg) {
            LONG_INT rez;
            rez.neg = neg;
            int nosi = 0;
            for (int i = 0; i < max(cifri.size(), o.cifri.size()) || nosi; ++i) {
                int sum = nosi;
                if (i < cifri.size()) sum += cifri[i];
                if (i < o.cifri.size()) sum += o.cifri[i];
                rez.cifri.push_back(sum % 10);
                nosi = sum / 10;
            }
            return rez;
        } else {
            if (neg) return o - (-(*this));
            else return *this - (-o);
        }
    }


    LONG_INT operator-() const {
        LONG_INT rez = *this;
        if (!(cifri.size() == 1 && cifri[0] == 0)) {
            rez.neg = !neg;
        }
        return rez;
    }



    LONG_INT operator-(const LONG_INT& o) const {
        if (neg != o.neg) {
            return *this + (-o);
        } else {
            if (abs_compare(*this, o) >= 0) {
                LONG_INT rez;
                rez.neg = neg;
                int poz = 0;
                for (int i = 0; i < cifri.size(); ++i) {
                    int lev, desen;

                    if (i < cifri.size()) {
                        lev = cifri[i];
                    } else {
                        lev = 0;
                    }

                    if (i < o.cifri.size()) {
                        desen = o.cifri[i];
                    } else {
                        desen = 0;
                    }

                    int diff = lev - desen - poz;
                    if (diff < 0) {
                        diff += 10;
                        poz = 1;
                    } else {
                        poz = 0;
                    }
                    rez.cifri.push_back(diff);
                }
                while (rez.cifri.size() > 1 && rez.cifri.back() == 0) {
                    rez.cifri.pop_back();
                }
                return rez;
            } else {
                return -(o - *this);
            }
        }
    }


    LONG_INT operator*(const LONG_INT& o) const {
        LONG_INT rez("0");
        rez.neg = (neg != o.neg);
        rez.cifri.resize(cifri.size() + o.cifri.size(), 0);

        for (int i = 0; i < cifri.size(); ++i) {
            int nosi = 0;
            for (int j = 0; j < o.cifri.size() || nosi; ++j) {
                int sum;
                int mnozitel;

                if (j < o.cifri.size()) {
                    mnozitel = o.cifri[j];
                } else {
                    mnozitel = 0;
                }

                sum = rez.cifri[i + j] + cifri[i] * mnozitel + nosi;

                rez.cifri[i + j] = sum % 10;
                nosi = sum / 10;
            }
        }

        while (rez.cifri.size() > 1 && rez.cifri.back() == 0) {
            rez.cifri.pop_back();
        }

        return rez;
    }


    LONG_INT operator/(const LONG_INT& o) const {

        LONG_INT rez, ostatok;
        rez.neg = (neg != o.neg);

        for (int i = cifri.size() - 1; i >= 0; --i) {
            ostatok.cifri.insert(ostatok.cifri.begin(), cifri[i]);
            while (ostatok.cifri.size() > 1 && ostatok.cifri.back() == 0) {
                ostatok.cifri.pop_back();
            }
            int count = 0;
            while (abs_compare(ostatok, o) >= 0) {
                ostatok = ostatok - abs(o);
                count++;
            }
            rez.cifri.insert(rez.cifri.begin(), count);
        }

        while (rez.cifri.size() > 1 && rez.cifri.back() == 0) {
            rez.cifri.pop_back();
        }

        return rez;
    }
    string to_string() const {
        string res = "";
        if (neg)
            res += "-";
        for (int i = cifri.size() - 1; i >= 0; --i)
        {
            res += (char)(cifri[i] + '0');
        }
        return res;
    }

    LONG_INT operator%(const LONG_INT& o) const {
        if (o == LONG_INT("0")) {
            throw runtime_error("Modul so 0!");
        }

        LONG_INT ostatok = *this;

        while (abs_compare(ostatok, o) >= 0) {
            ostatok = ostatok - o;
        }

        return ostatok;
    }


    bool operator==(const LONG_INT& o) const {
        return neg == o.neg && cifri == o.cifri;
    }

    bool operator!=(const LONG_INT& o) const {
        return !(*this == o);
    }






};
void faktorizacija(LONG_INT number) {
    LONG_INT curr("2");
    string rez = "";

    while (number != LONG_INT("1")) {
        LONG_INT count("0");

        while ((number % curr) == LONG_INT("0")) {
            count = count + LONG_INT("1");
            number = number / curr;
        }

        if (count != LONG_INT("0")) {
            if (!rez.empty()) rez += " * ";
            rez += curr.to_string();
            if (count != LONG_INT("1")) {
                rez += "^" + count.to_string();
            }
        }

        curr = curr + LONG_INT("1");
    }

    cout << rez << endl;
}


LONG_INT mod_exp(LONG_INT base, LONG_INT exp, LONG_INT mod)
{
    LONG_INT rez("1");
    base = base % mod;

    while (exp != LONG_INT("0"))
    {
        if ((exp % LONG_INT("2")) == LONG_INT("1"))
        {
            rez = (rez * base) % mod;
        }
        exp = exp / LONG_INT("2");
        base = (base * base) % mod;
    }
    return rez;
}


bool miller_rabin_test(LONG_INT n, int k)
{
    if (n == LONG_INT("2") || n == LONG_INT("3"))
        return true;
    if (n == LONG_INT("1") || (n % LONG_INT("2")) == LONG_INT("0"))
        return false;

    LONG_INT d = n - LONG_INT("1");
    int s = 0;
    while ((d % LONG_INT("2")) == LONG_INT("0"))
    {
        d = d / LONG_INT("2");
        s++;
    }

    for (int i = 0; i < k; i++)
    {
        LONG_INT a = LONG_INT(to_string(rand() % (stoi(n.to_string()) - 3) + 2));
        LONG_INT x = mod_exp(a, d, n);
        if (x == LONG_INT("1") || x == n - LONG_INT("1"))
            continue;

        bool passed = false;
        for (int r = 0; r < s - 1; r++)
        {
            x = (x * x) % n;
            if (x == LONG_INT("1"))
                return false;
            if (x == n - LONG_INT("1"))
            {
                passed = true;
                break;
            }
        }
        if (!passed)
            return false;
    }
    return true;
}

int main()
{
    LONG_INT num1("-10");
    LONG_INT num2("-5");

    cout << "Sobiranje: ";
    (num1 + num2).print();

    cout << "Odzimanje: ";
    (num1 - num2).print();

    cout << "Mnozenje: ";
    (num1 * num2).print();

    cout << "Delenje: ";
    (num1 / num2).print();

    LONG_INT num3("2");
    LONG_INT num4("100");

    cout << "Odzimanje za negativen: ";
    (num3 - num4).print();

    LONG_INT num("100");
    cout << "Faktorizacija: ";
    faktorizacija(num);

    LONG_INT prime_test("100");
    bool is_prime = miller_rabin_test(prime_test, 5);
    if (is_prime)
    {
        cout << "Miller-Rabin test: Prost" << endl;
    }
    else
    {
        cout << "Miller-Rabin test: slozen" << endl;
    }


    return 0;
}

