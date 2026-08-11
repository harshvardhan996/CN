#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// Function to calculate number of redundant bits required
int getRedundantBits(int m) {
    int r = 0;
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }
    return r;
}

// Function to generate the total encoded message frame
vector<int> generateHammingCode(string data) {
    int m = data.length();
    int r = getRedundantBits(m);
    int totalLen = m + r;
    
    // Using 1-based indexing for ease of calculation (size = totalLen + 1)
    vector<int> code(totalLen + 1, 0);
    
    // Map data bits to non-power-of-2 positions
    int dataPtr = 0;
    for (int i = 1; i <= totalLen; i++) {
        if ((i & (i - 1)) == 0) {
            code[i] = 0; // Temp placeholder for parity bits
        } else {
            code[i] = data[dataPtr] - '0';
            dataPtr++;
        }
    }

    // Compute even parity values for each parity position
    for (int i = 0; i < r; i++) {
        int parityPos = 1 << i; 
        int parityValue = 0;
        
        for (int j = 1; j <= totalLen; j++) {
            // Check if parity position bit covers index j
            if ((j & parityPos) != 0) {
                parityValue ^= code[j];
            }
        }
        code[parityPos] = parityValue;
    }
    return code;
}

// Function to detect and fix data stream errors
void detectAndCorrectError(vector<int>& receivedCode, int r) {
    int totalLen = receivedCode.size() - 1;
    int errorPosition = 0;

    // Recalculate parity values at the receiver
    for (int i = 0; i < r; i++) {
        int parityPos = 1 << i;
        int parityCheck = 0;
        
        for (int j = 1; j <= totalLen; j++) {
            if ((j & parityPos) != 0) {
                parityCheck ^= receivedCode[j];
            }
        }
        if (parityCheck != 0) {
            errorPosition += parityPos;
        }
    }

    if (errorPosition == 0) {
        cout << "\n[Success] No transmission errors detected." << endl;
    } else {
        cout << "\n[Alert] Single-bit error detected at position: " << errorPosition << endl;
        // Correcting the corrupted bit
        receivedCode[errorPosition] ^= 1;
        cout << "Fixed Data Frame: ";
        for (int i = 1; i <= totalLen; i++) cout << receivedCode[i];
        cout << endl;
    }
}

int main() {
    string dataWord = "1011"; 
    cout << "Original Data Word: " << dataWord << endl;

    // Encoding Step
    vector<int> transmittedFrame = generateHammingCode(dataWord);
    int totalLen = transmittedFrame.size() - 1;
    int r = getRedundantBits(dataWord.length());

    cout << "Generated Hamming Code Frame: ";
    for (int i = 1; i <= totalLen; i++) cout << transmittedFrame[i];
    cout << endl;

    // Error Simulation Step (Injecting error at index 3)
    int corruptIndex = 3; 
    vector<int> receivedFrame = transmittedFrame;
    receivedFrame[corruptIndex] ^= 1; 

    cout << "Simulated Corrupted Frame:    ";
    for (int i = 1; i <= totalLen; i++) cout << receivedFrame[i];
    cout << endl;

    // Error Correction Step
    detectAndCorrectError(receivedFrame, r);

    return 0;
}