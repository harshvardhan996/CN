#include <iostream>
#include <string>
using namespace std;

int main() {
    string codeword, divisor;

    cout << "Enter received codeword: ";
    cin >> codeword;

    cout << "Enter divisor: ";
    cin >> divisor;

    int n = divisor.length();
    string temp = codeword;

    for (int i = 0; i <= temp.length() - n; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < n; j++) {
                temp[i + j] =
                    (temp[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    string remainder =
        temp.substr(temp.length() - (n - 1));

    cout << "\nRemainder: " << remainder << endl;

    bool error = false;

    for (char bit : remainder) {
        if (bit == '1') {
            error = true;
            break;
        }
    }

    if (error)
        cout << "Error Detected!" << endl;
    else
        cout << "No Error Detected!" << endl;

    return 0;
}