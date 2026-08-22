#include <iostream>
#include <string>

//checkpoint project for codedex C++ course

using namespace std;

int sum(int a, int b)
{
    int sum = a + b;

    return sum;
}

int sub(int a, int b)
{
    int sub = a - b;

    return sub;
}

int multi(int a, int b)
{
    int multi = a * b;

    return multi;
}

int divi(int a, int b)
{
    if(b == 0)
    {
        cout << "Error, can't div by 0";

        return 0;
    }

    int div = a/b;

    return div;
}

int main()
{
    int num, num2, result;
    char op;

    cout << "=================" << endl;
    cout << "Simple Calculator" << endl;
    cout << "=================" << endl;

    cout << "\nEnter first number (int): ";
    cin >> num;
    cout << "Enter operator (+, -, *, /): ";
    cin >> op;
    cout << "Enter second number: ";
    cin >> num2;

    switch (op)
    {
    case '+':
        result = sum(num, num2);
        break;
    case '-':
        result = sub(num, num2);
        break;
    case '*':
        result = multi(num, num2);
        break;
    case '/':
        result = divi(num, num2);
        break;
    default:
        cout << "\nInvalid operator.";
        return 1;
        break;
    }

    cout << "Result: " << result << endl;

    return 0;
}