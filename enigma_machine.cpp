#include <iostream>
#include <vector>
#include <string>

class EnigmaMachine {
private:
    std::vector<int> rotors;
    int reflector;
    std::vector<int> rotorPositions;

public:
    EnigmaMachine(std::vector<int> rotorConfig, int reflectorConfig, std::vector<int> initialPositions) {
        rotors = rotorConfig;
        reflector = reflectorConfig;
        rotorPositions = initialPositions;
    }

    char encrypt(char letter) {
        int index = letter - 'A';
        for (int i = 0; i < rotors.size(); ++i) {
            index = (index + rotorPositions[i]) % 26;
            index = (index + rotors[i]) % 26;
        }
        index = (index + reflector) % 26;
        for (int i = rotors.size() - 1; i >= 0; --i) {
            index = (index - rotors[i] + 26) % 26;
            index = (index - rotorPositions[i] + 26) % 26;
        }
        return static_cast<char>('A' + index);
    }

    std::string encryptMessage(const std::string& message) {
        std::string encryptedMessage = "";
        for (char letter : message) {
            if (isalpha(letter)) {
                encryptedMessage += encrypt(toupper(letter));
            } else {
                encryptedMessage += letter;
            }
        }
        return encryptedMessage;
    }

    std::string decryptMessage(const std::string& encryptedMessage) {
        std::string decryptedMessage = "";
        for (char letter : encryptedMessage) {
            if (isalpha(letter)) {
                decryptedMessage += encrypt(toupper(letter));
            } else {
                decryptedMessage += letter;
            }
        }
        return decryptedMessage;
    }
};

int main() {
    std::vector<int> rotorConfig = { 3, 5, 7 };
    int reflectorConfig = 10;
    std::vector<int> initialPositions = { 0, 0, 0 };

    EnigmaMachine enigma(rotorConfig, reflectorConfig, initialPositions);

    std::string choice;
    std::string message;

    std::cout << "Seleccione una opción: \n";
    std::cout << "1. Cifrar mensaje\n";
    std::cout << "2. Descifrar mensaje\n";
    std::getline(std::cin, choice);

    if (choice == "1") {
        std::cout << "Ingrese el mensaje a cifrar: ";
        std::getline(std::cin, message);
        std::string encryptedMessage = enigma.encryptMessage(message);
        std::cout << "Mensaje cifrado: " << encryptedMessage << std::endl;
    } else if (choice == "2") {
        std::cout << "Ingrese el mensaje cifrado: ";
        std::getline(std::cin, message);
        std::string decryptedMessage = enigma.decryptMessage(message);
        std::cout << "Mensaje descifrado: " << decryptedMessage << std::endl;
    } else {
        std::cout << "Opción inválida\n";
    }

    return 0;
}
