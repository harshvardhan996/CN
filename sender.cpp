#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // Received 11-bit codeword from the image: "10101101110"
    // Indexing is 1-based from right to left:
    // Pos:  11 10  9  8  7  6  5  4  3  2  1
    // Bits:  1  0  1  0  1  1  0  1  1  1  0
    string received;
    cout << "Enter the 11-bit received codeword: ";
    if (!(cin >> received) || received.length() != 11) {
        received = "10101101110"; // Default from the image
        cout << received << " (using default from image)\n";
    }

    // Reverse the string to make 1-based indexing easier (index 0 corresponds to position 1)
    string r_code = received;
    reverse(r_code.begin(), r_code.end());

    // Calculate parity checks (XOR sum for even parity)
    // Position 1 (P1): checks positions 1, 3, 5, 7, 9, 11
    int p1 = (r_code[0]-'0') ^ (r_code[2]-'0') ^ (r_code[4]-'0') ^ (r_code[6]-'0') ^ (r_code[8]-'0') ^ (r_code[10]-'0');

    // Position 2 (P2): checks positions 2, 3, 6, 7, 10, 11
    int p2 = (r_code[1]-'0') ^ (r_code[2]-'0') ^ (r_code[5]-'0') ^ (r_code[6]-'0') ^ (r_code[9]-'0') ^ (r_code[10]-'0');

    // Position 4 (P4): checks positions 4, 5, 6, 7
    int p4 = (r_code[3]-'0') ^ (r_code[4]-'0') ^ (r_code[5]-'0') ^ (r_code[6]-'0');

    // Position 8 (P8): checks positions 8, 9, 10, 11
    int p8 = (r_code[7]-'0') ^ (r_code[8]-'0') ^ (r_code[9]-'0') ^ (r_code[10]-'0');

    // Form the syndrome word (P8 P4 P2 P1) to find the decimal equivalent
    int error_position = (p8 << 3) | (p4 << 2) | (p2 << 1) | p1;

    cout << "\n--- Analysis ---" << endl;
    cout << "P1 check bit: " << p1 << endl;
    cout << "P2 check bit: " << p2 << endl;
    cout << "P4 check bit: " << p4 << endl;
    cout << "P8 check bit: " << p8 << endl;
    cout << "Syndrome word (P8 P4 P2 P1): " << p8 << p4 << p2 << p1 << endl;
    cout << "Decimal equivalent: " << error_position << endl;

    if (error_position == 0) {
        cout << "\nResult: The received codeword is CORRECT." << endl;
    } else {
        cout << "\nResult: Error exists at position " << error_position << " from the right." << endl;
        
        // Correct the error by flipping the bit at the error position
        if (r_code[error_position - 1] == '0') {
            r_code[error_position - 1] = '1';
        } else {
            r_code[error_position - 1] = '0';
        }

        // Reverse back to original order
        reverse(r_code.begin(), r_code.end());
        cout << "Corrected codeword is: " << r_code << endl;
    }

    return 0;
}