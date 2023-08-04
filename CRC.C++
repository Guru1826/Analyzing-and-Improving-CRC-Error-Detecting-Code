#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// Function to calculate the CRC value
string calculateCRC(const vector<bool>& message, unsigned int polynomial)
{
    unsigned int crcRegister = 0xFFFFFFFF; // Initialize CRC register to all ones

    // Append zeros to the message to match the degree of the polynomial minus 1
    vector<bool> extendedMessage = message;
    for (int i = 0; i < 32; i++)
    {
        extendedMessage.push_back(false);
    }

    // Perform CRC calculation for each part
    for (const bool bit : extendedMessage)
    {
        crcRegister ^= (bit ? 1 : 0) << 31; // XOR the most significant bit of the CRC register with the current bit

        if (crcRegister & 0x80000000) // If the most significant bit of the CRC register is 1
        {
            crcRegister = (crcRegister << 1) ^ polynomial; // Left shift CRC register and XOR with the polynomial
        }
        else
        {
            crcRegister = crcRegister << 1; // Left shift CRC register
        }
    }

    bitset<32> crcBits(crcRegister); // Convert the CRC value to binary representation
    return crcBits.to_string();
}

int main()
{
    vector<bool> message = {true, false, true, false, true}; // Example input message

    unsigned int polynomial1 = 1001001001001011; // First polynomial (binary representation)
    unsigned int polynomial2 = 1001001001001011;  // Second polynomial (binary representation)

    string crcValue1 = calculateCRC(message, polynomial1);
    string crcValue2 = calculateCRC(message, polynomial2);

    cout << "CRC value with polynomial 1 1001001001001011:"<<"  " << crcValue1 << endl;
    cout << "CRC value with polynomial 2 1001001001001011:"<<"  " << crcValue2 << endl;

    // Compare CRC values
    if (crcValue1 == crcValue2)
    {
        cout << "CRC values are the same." << endl;
    }
    else
    {
        cout << "CRC values are different." << endl;
    }

    return 0;
}
