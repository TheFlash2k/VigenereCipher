#include <iostream>
#include <string>
#include <fstream>

void toUpper(std::string&); // Converts an entire string to upperCase.
std::string setKey(std::string, size_t); // Repeats the key and builds it.
std::string Encrypt(std::string, std::string); // Main Function to encrypt
std::string Decrypt(std::string, std::string); // Main Function to decrypt
bool hasSpecials(std::string);
void menu(int&); // Printing menu
std::string readFromFile(); // Reading content from a file.
void writeToFile(std::string, std::string); // Function that writes to a file.
void displayFinal(std::string, std::string, std::string, bool);

int main() {
	
	std::string key;
	std::string plainText, cipherText, text;
	int uChoice;
	char reChoice = 'n';
	char readFile = 'n';
	bool dec = true;

	do {
		menu(uChoice);
		// Reading key from user:
		std::cout << "========================================\n";
		std::cout << "Enter the key: ";
		std::getline(std::cin, key);
		// Checking for existence of special characters in key
		bool hasSpecial = hasSpecials(key);
		while (hasSpecial) {
			std::cout << "Key cannot contain any other character besides alphabets. Try again: ";
			std::getline(std::cin, key);
			hasSpecial = hasSpecials(key);
		}
		std::cout << "========================================\n";
		// Converting key to uppercase:
		toUpper(key);
		// Checking if user wants to read data from file:
		std::cout << "Do you want to read from file? (Y/N): ";
		std::cin >> readFile;

		readFile = toupper(readFile);

		while (readFile != 'Y' && readFile != 'N') {
			std::cout << "Invalid Choice. Type either 'Y' or 'N': ";
			std::cin >> readFile;
			readFile = toupper(readFile);
		}

		if (readFile == 'Y') {
			size_t len;
			text = readFromFile();
			if (uChoice == 1) {
				plainText = text;
				key = setKey(key, plainText.length());
				toUpper(plainText);
				dec = false;
				cipherText = Encrypt(plainText, key);
			}
			else {
				cipherText = text;
				key = setKey(key, cipherText.length());
				toUpper(cipherText);
				dec = true;
				plainText = Decrypt(cipherText, key);
			}
		}
		else {
			std::cin.ignore();
			std::cout << "========================================\n";
			if (uChoice == 1) {
				std::cout << "Enter the plain text for encryption: ";
				std::getline(std::cin, plainText);
				// Converting plaintext to uppercase:
				toUpper(plainText);
				// Building the key based on the length of the plaintext:
				key = setKey(key, plainText.length());
				// Encrypting
				dec = false;
				cipherText = Encrypt(plainText, key);
			}
			else {
				std::cout << "Enter the cipher text for decryption: ";
				std::getline(std::cin, cipherText);
				// Converting ciphertext to uppercase:
				toUpper(cipherText);
				// Building the key based on the length of the ciphertext:
				key = setKey(key, cipherText.length());
				// Decrypting
				dec = true;
				plainText = Decrypt(cipherText, key);
			}
		}

		displayFinal(key, plainText, cipherText, dec);
		
		std::cout << "Do you want to continue: (Y/N): ";
		std::cin >> reChoice;
		reChoice = toupper(reChoice); // Converting to uppercase
		while (reChoice != 'Y' && reChoice != 'N') {
			std::cout << "Invalid value entered. Try again: ";
			std::cin >> reChoice;
			reChoice = toupper(reChoice);
		}
	} while (reChoice == 'Y');
	std::cout << "========================================\n";
	return 0;
}
void toUpper(std::string& str) {
	for (size_t i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
}
// Key -> String
// sizeText -> size_t -> Size of the plain/Cipher Text.
std::string setKey(std::string key, size_t sizeText) {
	if (key.length() >= sizeText)
		return key; // Returning the key as it is if it is greater.
	std::string cp_key = ""; // copying the current key over to the new string
	// Looping over the entire string character by character
	size_t i = 0;
	while (cp_key.length() != sizeText) {
		if (i == key.length())
			i = 0; // Resetting the iteration variable to first variable.
		cp_key += key[i];
		i++;
	}
	return cp_key;
}
std::string Encrypt(std::string plainText, std::string key) {
	std::string cipherText = "";
	int lKey = 0;
	for (size_t i = 0; i < plainText.length(); i++) {
		// Checking if its an alphabet, then encrypting it
		// Otherwise simply copying it.
		if(isalpha(plainText[i]))
			cipherText += char(((plainText[i] + key[lKey++]) % 26) + 65);
		else
			cipherText += plainText[i];
	}
	return cipherText;
}
std::string Decrypt(std::string cipherText, std::string key) {
	std::string plainText;
	int lKey = 0;
	for (size_t i = 0; i < cipherText.length(); i++) {
		if (isalpha(cipherText[i]))
			plainText += char(((cipherText[i] - key[lKey++] + 26) % 26) + 65);
		else
			plainText += cipherText[i];
	}
	return plainText;
}
bool hasSpecials(std::string text) {
	// Checking if anything besides a alphabet is found:
	for (char ch : text) {
		if (!isalpha(ch))
			return true;
	}
	return false;
}
void menu(int& uChoice) {
	system("cls");
	std::cout << "========================================\n";
	std::cout << "Vignere Cipher - Encryption Decryption.\n";
	std::cout << "In C++\n";
	std::cout << "========================================\n";
	std::cout << "Group Members:\n";
	std::cout << "190764 - Shameer Kashif\n";
	std::cout << "190770 - Mahnam Nasir\n";
	std::cout << "190787 - Amal Abrar\n";
	std::cout << "190792 - Ali Taqi Wajid\n";
	std::cout << "========================================\n";
	std::cout << "== MENU ==\n";
	std::cout << "1. Encrypt.\n";
	std::cout << "2. Decrypt.\n";
	std::cout << "Enter choice: ";

	std::cin >> uChoice;
	while (uChoice != 1 && uChoice != 2) {
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n'); // Ignoring any character passed into stdin
		std::cout << "Invalid choice. Try again: ";
		std::cin >> uChoice;
	}
	// Ignoring any thing currently in stdin as the next input is into a string:
	std::cin.ignore();
}
std::string readFromFile() {
	std::string fileName;
	int reChoice;
	std::string fileData;
	std::ifstream file;
	std::cin.ignore();
begin:
	std::cout << "Enter file name: ";
	std::getline(std::cin, fileName);

	file.open(fileName);
	if (!file.good()) {
		std::cout << "File doesn't exist. Do you want to read another file or exit? (1 or 2): ";
		std::cin >> reChoice;
		while (reChoice != 1 && reChoice != 2) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid Choice.Only choose 1 or 2... ";
			std::cin >> reChoice;
		}
		file.close();
		if (reChoice == 1)
			goto begin;
		else {
			std::cout << "========================================\n";
			exit(1);
		}
	}
	std::string temp;
	while (!file.eof()) {
		getline(file, temp);
		fileData += temp;
	}
	return fileData;
}
void writeToFile(std::string fileName, std::string content) {
	std::ofstream file(fileName);
	file << content;
	file.close();
}
void displayFinal(std::string key, std::string plainText, std::string cipherText, bool dec) {
	char choice;
	std::cout << "========================================\n";
	std::cout << "Key is: " << key << "\n";
	std::cout << "Encrypted text is: " << cipherText << "\n";
	std::cout << "Decrypted text is: " << plainText  << "\n";
	std::cout << "========================================\n";
	std::cout << "Do you want to write the output to file? (Y/N): ";
	std::cin >> choice;
	choice = toupper(choice);
	while (choice != 'Y' && choice != 'N') {
		std::cout << "Invalid Choice. Type either 'Y' or 'N': ";
		std::cin >> choice;
	}
	if (choice == 'Y') {
		std::string text;
		std::string fileName;
		text = (dec ? plainText : cipherText);
		fileName = (dec ? "decrypted.txt" : "encrypted.txt");
		writeToFile(fileName, text);
		text = (dec ? "Decrypted" : "Encrypted");
		std::cout << text << " text stored to file " << fileName << std::endl;
	}
	std::cout << "========================================\n";
}