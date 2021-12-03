#include "process.h"
#include "affix-base/aes.h"
#include "cryptopp/osrng.h"
#include <fstream>
#include "affix-base/file_ios.h"
#include <filesystem>
#include "affix-base/string_extensions.h"

namespace fs = std::filesystem;

void armory::process_aes_generate(
	const std::string& a_key_path
)
{
	std::vector<uint8_t> l_key = affix_base::cryptography::aes_generate_key();
	affix_base::ios::file_write(a_key_path, l_key);
}

void armory::process_aes_encrypt(
	const std::vector<uint8_t>& a_key,
	const std::string& a_data_path,
	const bool& a_recursive
)
{
	// PRE-ORDER TRAVERSAL
	if (fs::is_directory(a_data_path))
	{
		for (const auto& entry : fs::directory_iterator(a_data_path))
			if (!fs::is_directory(entry) || a_recursive)
				process_aes_encrypt(a_key, entry.path().u8string(), a_recursive);
		return;
	}

	// MAKE SURE FILE EXISTS
	if (!fs::exists(a_data_path))
	{
		std::cerr << "Error: The file specified does not exist: " << a_data_path << std::endl;
		return;
	}

	// GET LENGTH OF INPUT
	long long int l_data_size = fs::file_size(a_data_path);
	
	// OPEN IFS
	std::ifstream l_ifs(a_data_path, std::ios::in | std::ios::binary);
	l_ifs.seekg(0, std::ios::beg);
	
	// OPEN OFS
	std::string l_output_path = a_data_path + ".arm";
	std::ofstream l_ofs(l_output_path, std::ios::out | std::ios::binary | std::ios::trunc | std::ios::app);

	while (l_ifs.good() && l_ofs.good() && l_ifs.peek() != EOF)
	{
		// GET REMAINING DATA FROM INPUT FILE
		long long int l_remaining = l_data_size - l_ifs.tellg();

		// CREATE INPUT VECTOR OBJECT
		std::vector<uint8_t> l_input;

		// GET SIZE OF THIS ITERATIONS INPUT
		if (l_remaining >= ENCRYPTION_INPUT_BUFFER_SIZE)
			l_input.resize(ENCRYPTION_INPUT_BUFFER_SIZE);
		else
			l_input.resize(l_remaining);

		// READ FROM INPUT FILE
		l_ifs.read((char*)l_input.data(), l_input.size());

		// ENCRYPT DATA
		std::vector<uint8_t> l_encrypted = affix_base::cryptography::aes_encrypt(
			l_input, a_key
		);

		// WRITE TO OUTPUT FILE
		l_ofs.write((const char*)l_encrypted.data(), l_encrypted.size());
		
	}

	// SAFELY CLOSE THE STREAMS
	l_ifs.close();
	l_ofs.close();

}

void armory::process_aes_decrypt(
	const std::vector<uint8_t>& a_key,
	const std::string& a_data_path,
	const bool& a_recursive
)
{
	// PRE-ORDER TRAVERSAL
	if (fs::is_directory(a_data_path))
	{
		for (const auto& entry : fs::directory_iterator(a_data_path))
			if (!fs::is_directory(entry) || a_recursive)
				process_aes_encrypt(a_key, entry.path().u8string(), a_recursive);
		return;
	}

	// MAKE SURE FILE EXISTS
	if (!fs::exists(a_data_path))
	{
		std::cerr << "Error: The file specified does not exist: " << a_data_path << std::endl;
		return;
	}

	// ENSURE THE FILE WAS ORIGINALLY ENCRYPTED BY ARMORY
	if (!affix_base::data::string_can_query(a_data_path, "*.arm"))
	{
		std::cerr << "Error: The file specified does not have an appropriate file extention." << std::endl;
		return;
	}

	// GET LENGTH OF INPUT
	long long int l_data_size = fs::file_size(a_data_path);

	// OPEN IFS
	std::ifstream l_ifs(a_data_path, std::ios::in | std::ios::binary);

	// OPEN OFS
	std::string l_output_path = a_data_path.substr(0, a_data_path.size() - 4);
	std::ofstream l_ofs(l_output_path, std::ios::out | std::ios::binary | std::ios::trunc | std::ios::app);

	while (l_ifs.good() && l_ofs.good() && l_ifs.peek() != EOF)
	{
		// GET REMAINING DATA FROM INPUT FILE
		long long int l_remaining = l_data_size - l_ifs.tellg();

		// CREATE INPUT VECTOR OBJECT
		std::vector<uint8_t> l_input;

		// GET SIZE OF THIS ITERATIONS INPUT
		if (l_remaining >= AES_DECRYPTION_INPUT_BUFFER_SIZE)
			l_input.resize(AES_DECRYPTION_INPUT_BUFFER_SIZE);
		else
			l_input.resize(l_remaining);

		// READ FROM INPUT FILE
		l_ifs.read((char*)l_input.data(), l_input.size());

		// ENCRYPT DATA
		std::vector<uint8_t> l_decrypted = affix_base::cryptography::aes_decrypt(
			l_input, a_key
		);

		// WRITE TO OUTPUT FILE
		l_ofs.write((const char*)l_decrypted.data(), l_decrypted.size());

	}

	// SAFELY CLOSE THE STREAMS
	l_ifs.close();
	l_ofs.close();

}

void armory::process_rsa_generate(
	const std::string& a_private_key_path,
	const std::string& a_public_key_path,
	const uint16_t& a_key_size
)
{

}

void armory::process_rsa_encrypt(
	const CryptoPP::RSA::PublicKey& a_key,
	const std::string& a_data_path,
	const bool& a_recursive
)
{
	/*CryptoPP::RSAES<CryptoPP::OAEP<CryptoPP::SHA256>>::Encryptor encryptor(a_key);
	encryptor.CiphertextLength(plaintextlength);*/
}

void armory::process_rsa_decrypt(
	const CryptoPP::RSA::PrivateKey& a_key,
	const std::string& a_data_path,
	const bool& a_recursive
)
{

}
