#pragma once
#include "affix-base/aes.h"
#include "affix-base/rsa.h"
#include <string>
#include "parse.h"

namespace armory {
	
	const size_t ENCRYPTION_INPUT_BUFFER_SIZE = 100000;
	const size_t AES_DECRYPTION_INPUT_BUFFER_SIZE = 100016;

	void process_aes_generate(
		const std::string& a_key_path
	);

	void process_aes_encrypt(
		const std::vector<uint8_t>& a_key,
		const std::string& a_data_path,
		const bool& a_recursive
	);

	void process_aes_decrypt(
		const std::vector<uint8_t>& a_key,
		const std::string& a_data_path,
		const bool& a_recursive
	);

	void process_rsa_generate(
		const std::string& a_private_key_path,
		const std::string& a_public_key_path,
		const uint16_t& a_key_size
	);

	void process_rsa_encrypt(
		const CryptoPP::RSA::PublicKey& a_key,
		const std::string& a_data_path,
		const bool& a_recursive
	);

	void process_rsa_decrypt(
		const CryptoPP::RSA::PrivateKey& a_key,
		const std::string& a_data_path,
		const bool& a_recursive
	);

}
