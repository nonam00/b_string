//программа завершается с ошибкой
//если пройтись через отладчик, ошибку выдаёт просле окончания функции main, а также сообщает об отсутствии некого файла

#include <iostream>
#include <regex>
#include <Windows.h>

class String
{

public:

    String()
    {
        size = 0;
        str = new char[size + 1];
        str[0] = '\0';
    }

    String(const char* _str)
    {
        size = (int)strlen(_str);
        str = new char[size + 1];
        strcpy_s(str, size + 1, _str);
    }

    String(const String& obj) : size{ obj.size }
    {
        str = new char[size + 1];
        strcpy_s(str, size + 1, obj.str);
    }

    ~String() { delete[]str; }

    void del()
    {
        size = 0;
        delete[]str;
        str = new char[size + 1];
        str[0] = '\0';
    }

    String& operator=(const String& obj)
    {
        size = obj.size;
        delete[]str;
        str = new char[size + 1];
        strcpy_s(str, size + 1, obj.str);
        return*this;
    }

    friend String operator+(const String& obj1, const String& obj2)
    {
        int new_size = obj1.size + obj2.size;
        char* new_str = new char[new_size + 1];
        strcpy_s(new_str, new_size, obj1.str);
        strcat_s(new_str, new_size + 1, obj2.str);
        return String(new_str);
    }

    String& operator+=(const String& obj)
    {
        size += obj.size;
        char* new_str = new char[size + 1];
        strcpy_s(new_str, size, str);
        delete[]str;
        str = new char[size + 1];
        strcpy_s(str, size, new_str);
        strcat_s(str, size + 1, obj.str);
        return*this;
    }

    friend bool operator==(const String& obj1, const String& obj2)
    {
        if (strcmp(obj1.str, obj2.str) == 0)
            return true;
        else
            return false;
    }
    friend bool operator!=(const String& obj1, const String& obj2)
    {
        if (strcmp(obj1.str, obj2.str) == 0)
            return false;
        else
            return true;
    }
    char& operator[](int index)
    {
        return str[index];
    }

    friend std::ostream& operator<<(std::ostream& out, const String& obj)
    {
        out << obj.str << " " << obj.size << std::endl;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, String& obj)
    {
        in >> obj.size;
        delete[]obj.str;
        obj.str = new char[obj.size + 1];
        in >> obj.str;
        return in;
    }

protected:

    char* str;
    int size;

};


void reg_del(char*& str, int& size)
{
    std::regex bin("(?:0|1)");
    std::string buf;
    std::string simbol;
    for (int i = 0; i < size; i++)
    {
        simbol = str[i];
        if (!std::regex_search(simbol, bin))
        {
            size = 0;
            delete[]str;
            str = new char[size + 1];
            str[0] = '\0';
        }
    }
}


class B_string : protected String
{
public:
    B_string()
    {
        size = 0;
        str = new char[size + 1];
        str[0] = '\0';
    }

    B_string(const char* _str)
    {
        size = (int)strlen(_str);
        str = new char[size + 1];
        strcpy_s(str, size + 1, _str);
        reg_del(str, size);
    }

    B_string(const B_string& obj)
    {
        size = obj.size;
        str = new char[size + 1];
        strcpy_s(str, size + 1, obj.str);
        reg_del(str, size);
    }
    
    ~B_string() { delete[]str; }

    
    B_string& operator=(const B_string& obj)
    {
        size = obj.size;
        delete[]str;
        str = new char[size + 1];
        strcpy_s(str, size + 1, obj.str);
        return*this;
    }

    friend B_string operator+(const B_string& obj1, const B_string& obj2)
    {
        int new_size = obj1.size + obj2.size;
        char* new_str = new char[new_size + 1];
        strcpy_s(new_str, new_size, obj1.str);
        strcat_s(new_str, new_size + 1, obj2.str);
        return B_string(new_str);
    }

    B_string& operator+=(const B_string& obj)
    {
        size += obj.size;
        char* new_str = new char[size + 1];
        strcpy_s(new_str, size, str);
        delete[]str;
        str = new char[size + 1];
        strcpy_s(str, size, new_str);
        strcat_s(str, size + 1, obj.str);
        return*this;
    }

    friend bool operator==(const B_string& obj1, const B_string& obj2)
    {
        if (strcmp(obj1.str, obj2.str) == 0)
            return true;
        else
            return false;
    }
    friend bool operator!=(const B_string& obj1, const B_string& obj2)
    {
        if (strcmp(obj1.str, obj2.str) == 0)
            return false;
        else
            return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const B_string& obj)
    {
        out << obj.str << " " << obj.size << std::endl;
        return out;
    }

    friend std::istream& operator>>(std::istream& in, B_string& obj)
    {
        in >> obj.size;
        delete[]obj.str;
        obj.str = new char[obj.size + 1];
        in >> obj.str;
        return in;
    }
};


int main()
{
    B_string n("101");
    B_string m("110");
    m += n;
    std::cout << m;
    return 0;
}