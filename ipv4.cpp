#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    string ip;
    int a, b, c, d;
    char dot;

    cout << "Enter IPv4 address: ";
    cin >> ip;

    stringstream ss(ip);
    ss >> a >> dot >> b >> dot >> c >> dot >> d;

    if (a >= 0 && a <= 255 &&
        b >= 0 && b <= 255 &&
        c >= 0 && c <= 255 &&
        d >= 0 && d <= 255)
    {
        cout << "Valid IP: Yes" << endl;
        cout << "First Byte: " << a << endl;

        if (a >= 1 && a <= 126)
        {
            cout << "Class: A" << endl;
            cout << "NetID: " << a << ".0.0.0" << endl;
            cout << "HostID: 0." << b << "." << c << "." << d;
        }
        else if (a >= 128 && a <= 191)
        {
            cout << "Class: B" << endl;
            cout << "NetID: " << a << "." << b << ".0.0" << endl;
            cout << "HostID: 0.0." << c << "." << d;
        }
        else if (a >= 192 && a <= 223)
        {
            cout << "Class: C" << endl;
            cout << "NetID: " << a << "." << b << "." << c << ".0" << endl;
            cout << "HostID: 0.0.0." << d;
        }
        else if (a >= 224 && a <= 239)
            cout << "Class: D";
        else
            cout << "Class: E";
    }
    else
    {
        cout << "Valid IP: No";
    }

    return 0;
}
