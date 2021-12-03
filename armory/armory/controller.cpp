#include "controller.h"
#include "parse.h"
#include "process.h"
#include "affix-base/string_extensions.h"
#include "affix-base/ios.h"
#include <filesystem>

namespace fs = std::filesystem;

void armory::input_line(
	const std::string& a_line
)
{
	if (affix_base::data::string_can_query(a_line, "aes generate*"))
	{
		aes_generate_decl l_decl = parse_aes_generate_decl(a_line);
		call_aes_generate(l_decl);
	}
	else if (affix_base::data::string_can_query(a_line, "aes encrypt*"))
	{
		aes_encrypt_decl l_decl = parse_aes_encrypt_decl(a_line);
		call_aes_encrypt(l_decl);
	}
	else if (affix_base::data::string_can_query(a_line, "aes decrypt*"))
	{
		aes_decrypt_decl l_decl = parse_aes_decrypt_decl(a_line);
		call_aes_decrypt(l_decl);
	}
	else if (affix_base::data::string_can_query(a_line, "rsa generate*"))
	{
		rsa_generate_decl l_decl = parse_rsa_generate_decl(a_line);
		call_rsa_generate(l_decl);
	}
	else if (affix_base::data::string_can_query(a_line, "rsa encrypt*"))
	{
		rsa_encrypt_decl l_decl = parse_rsa_encrypt_decl(a_line);
		call_rsa_encrypt(l_decl);
	}
	else if (affix_base::data::string_can_query(a_line, "rsa decrypt*"))
	{
		rsa_decrypt_decl l_decl = parse_rsa_decrypt_decl(a_line);
		call_rsa_decrypt(l_decl);
	}
}

void armory::call_aes_generate(
	const aes_generate_decl& a_decl
)
{
	process_aes_generate(
		fs::absolute(a_decl.m_key_path).u8string()
	);
}

void armory::call_aes_encrypt(
	const aes_encrypt_decl& a_decl
)
{
	std::vector<uint8_t> l_key;
	affix_base::ios::file_read(a_decl.m_key_path, l_key);
	process_aes_encrypt(l_key, a_decl.m_data_path, a_decl.m_recursive);
}

void armory::call_aes_decrypt(
	const aes_decrypt_decl& a_decl
)
{
	std::vector<uint8_t> l_key;
	affix_base::ios::file_read(a_decl.m_key_path, l_key);
	process_aes_decrypt(l_key, a_decl.m_data_path, a_decl.m_recursive);
}

void armory::call_rsa_generate(
	const rsa_generate_decl& a_decl
)
{
	process_rsa_generate(
		a_decl.m_private_key_path, 
		a_decl.m_public_key_path, 
		a_decl.m_key_size
	);
}

void armory::call_rsa_encrypt(
	const rsa_encrypt_decl& a_decl
)
{
	CryptoPP::RSA::PublicKey l_pub_key;

	if (!affix_base::cryptography::rsa_try_import(l_pub_key, a_decl.m_key_path))
	{
		std::cerr << "Error: could not import RSA public key from: " << a_decl.m_key_path << std::endl;
	}

	process_rsa_encrypt(l_pub_key, a_decl.m_data_path, a_decl.m_recursive);

}

void armory::call_rsa_decrypt(
	const rsa_decrypt_decl& a_decl
)
{
	CryptoPP::RSA::PrivateKey l_pri_key;

	if (!affix_base::cryptography::rsa_try_import(l_pri_key, a_decl.m_key_path))
	{
		std::cerr << "Error: could not import RSA private key from: " << a_decl.m_key_path << std::endl;
	}

	process_rsa_decrypt(l_pri_key, a_decl.m_data_path, a_decl.m_recursive);

}
