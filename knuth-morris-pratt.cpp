#include <bits/stdc++.h>
using namespace std;

class String
{
    char *chars;
    unsigned int length;

public:
    String()
    {
        length = 0;
        chars = nullptr;
    }

    String(const char *other)
    {
        int len = 0;
        while (other[len] != '\0')
        {
            len++;
        }
        length = len;
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            chars[i] = other[i];
        }
        chars[length] = '\0';
    }

    String(const String &other)
    {
        length = other.length;
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            chars[i] = other.chars[i];
        }
        chars[length] = '\0';
    }

    ~String()
    {
        delete[] chars;
    }

    String operator+(const char *other)
    {
        int len = 0;
        while (other[len] != '\0')
        {
            len++;
        }

        int new_len = length + len;
        char *new_chars = new char[new_len + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            new_chars[i] = chars[i];
        }
        for (unsigned int i = 0; i < len; i++)
        {
            new_chars[length + i] = other[i];
        }
        new_chars[new_len] = '\0';

        String new_str(new_chars);
        delete[] new_chars;
        return new_str;
    }

    String operator+(const String &other)
    {
        char *new_chars = new char[length + other.length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            new_chars[i] = chars[i];
        }
        for (unsigned int i = 0; i < other.length; i++)
        {
            new_chars[length + i] = other.chars[i];
        }
        new_chars[length + other.length] = '\0';

        String new_str(new_chars);
        delete[] new_chars;
        return new_str;
    }

    String operator=(const char *other)
    {
        int len = 0;
        while (other[len] != '\0')
        {
            len++;
        }
        length = len;
        delete[] chars;
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            chars[i] = other[i];
        }
        chars[length] = '\0';
        return *this;
    }

    String operator=(const String &other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] chars;
        length = other.length;
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            chars[i] = other.chars[i];
        }
        chars[length] = '\0';
        return *this;
    }
    char &operator[](unsigned int index)
    {
        if (index < 0 || index >= length)
        {
            throw out_of_range("Index out of range!");
        }
        return chars[index];
    }
    const char &operator[](unsigned int index) const
    {
        if (index < 0 || index >= length)
        {
            throw out_of_range("Index out of range!");
        }
        return chars[index];
    }
    friend ostream &operator<<(ostream &o, const String &other)
    {
        for (unsigned int i = 0; i < other.length; i++)
        {
            o << other.chars[i];
        }
        return o;
    }

    void computeLPSArray(const String &subStr, int lps[])
    {
        int len = 0;
        lps[0] = 0;
        for (int i = 1; i < subStr.length; i++)
        {
            while (len > 0 && subStr[i] != subStr[len])
            {
                len = lps[len - 1];
            }
            if (subStr[i] == subStr[len])
            {
                len++;
            }
            lps[i] = len;
        }
    }
    void computeLPSArrayReverse(const String &subStr, int lps[])
    {
        int n = subStr.length;
        int len = 0;
        lps[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            while (len > 0 && subStr[i] != subStr[n - len - 1])
            {
                len = lps[n - len];
            }
            if (subStr[i] == subStr[n - len - 1])
            {
                len++;
            }
            lps[i] = len;
        }
    }

    int *findAllSubStr(const String &subStr)
    {
        int *res = new int[length];
        int *lps = new int[subStr.length];
        int count = 0;
        computeLPSArray(subStr, lps);

        int j = 0;
        for (int i = 0; i < length; i++)
        {
            while (j > 0 && chars[i] != subStr[j])
            {
                j = lps[j - 1];
            }
            if (chars[i] == subStr[j])
            {
                j++;
            }
            if (j == subStr.length)
            {
                res[count++] = i - j + 1;
                j = lps[j - 1];
            }
        }

        int *final_res = new int[count];
        for (int i = 0; i < count; i++)
        {
            final_res[i] = res[i];
        }
        delete[] res;
        delete[] lps;
        return final_res;
    }

    int findFirstSubStr(const String &subStr)
    {
        int *lps = new int[subStr.length];
        computeLPSArray(subStr, lps);

        int j = 0;
        for (int i = 0; i < length; i++)
        {
            while (j > 0 && chars[i] != subStr[j])
            {
                j = lps[j - 1];
            }
            if (chars[i] == subStr[j])
            {
                j++;
            }
            if (j == subStr.length)
            {
                delete[] lps;
                return i - j + 1;
            }
        }

        delete[] lps;
        return -1;
    }

    int findLastSubStr(const String &subStr)
    {
        int *lps = new int[subStr.length];
        computeLPSArrayReverse(subStr, lps);

        int j = subStr.length - 1;
        for (int i = length - 1; i >= 0; i--)
        {
            while (j > 0 && chars[i] != subStr[j])
            {
                j = lps[j - 1];
            }
            if (chars[i] == subStr[j])
            {
                j--;
            }
            if (j == -1)
            {
                delete[] lps;
                return i;
            }
        }

        delete[] lps;
        return -1;
    }

    int *findAllSubStrReverse(const String &subStr)
    {
        int *res = new int[length];
        int *lps = new int[subStr.length];
        int count = 0;
        computeLPSArrayReverse(subStr, lps);

        int j = subStr.length - 1;
        for (int i = length - 1; i >= 0; i--)
        {
            while (j < subStr.length - 1 && chars[i] != subStr[j])
            {
                j = subStr.length - lps[j + 1] - 1;
            }
            if (chars[i] == subStr[j])
            {
                j--;
            }
            if (j == -1)
            {
                res[count++] = i;
                j = subStr.length - lps[0] - 1;
            }
        }

        int *final_res = new int[count];
        for (int i = 0; i < count; i++)
        {
            final_res[i] = res[i];
        }
        delete[] res;
        delete[] lps;
        return final_res;
    }
};

int main()
{
    String s = "dobra vecer kako ste vecer vecer ste";
    cout << s << endl;

    cout <<  s.findFirstSubStr("ste") << endl;
    cout <<  s.findLastSubStr("vecer") << endl;

    
    int *res = s.findAllSubStr("vecer");
    int n = sizeof(res) / sizeof(res[0]);
    for (int i = 0; i <= n; i++)
    {
        cout << res[i] << endl;
    }

    
    int *res_rev = s.findAllSubStrReverse("vecer");
    int n_rev = sizeof(res_rev) / sizeof(res_rev[0]);
    for (int i = 0; i <= n_rev; i++)
    {
        cout << res_rev[i] << endl;
    }

    return 0;
}