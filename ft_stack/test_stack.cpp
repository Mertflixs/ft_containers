#include <iostream>
#include <vector>

template <typename T>
class Stack
{
private:
    std::vector<T> data;  // stack verilerini saklayan vektör

public:
    // Yığına veri ekler
    void push(T value)
    {
        data.push_back(value);
    }

    // Yığından en üstteki veriyi çıkartır ve döndürür
    T pop()
    {
        T value = data.back();
        data.pop_back();
        return value;
    }

    // Yığındaki en üstteki veriyi döndürür
    T top()
    {
        return data.back();
    }

    // Yığının boş olup olmadığını kontrol eder
    bool empty()
    {
        return data.empty();
    }

    // Yığındaki veri sayısını döndürür
    int size()
    {
        return data.size();
    }
};

int main()
{
    Stack<int> s;  // stack veri yapısı tanımlanıyor

    // Yığına veriler ekleniyor
    s.push(5);
    s.push(10);
    s.push(15);

    // Yığındaki veriler yazdırılıyor
    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;

    return 0;
}