#include "parse.h"
#include "affix-base/string_extensions.h"
#include "process.h"

armory::aes_generate_decl armory::parse_aes_generate_decl(
	const std::string& a_line
)
{
	std::vector<std::string> l_split = affix_base::data::string_split(a_line, ' ');
	std::string l_path = l_split[2];
	return armory::aes_generate_decl { l_path };
}

armory::aes_encrypt_decl armory::parse_aes_encrypt_decl(
	const std::string& a_line
)
{
	std::vector<std::string> l_split = affix_base::data::string_split(a_line, ' ');
	std::string l_key_path = l_split[2];
	std::string l_data_path = l_split[3];
	bool l_recursive = false;
	if (l_split.size() > 4 && l_split[4] == "-r")
	{
		l_recursive = true;
	}
	return armory::aes_encrypt_decl { l_key_path, l_data_path, l_recursive };
}

armory::aes_decrypt_decl armory::parse_aes_decrypt_decl(
	const std::string& a_line
)
{
	std::vector<std::string> l_split = affix_base::data::string_split(a_line, ' ');
	std::string l_key_path = l_split[2];
	std::string l_data_path = l_split[3];
	bool l_recursive = false;
	if (l_split.size() > 4 && l_split[4] == "-r")
	{
		l_recursive = true;
	}
	return armory::aes_decrypt_decl{ l_key_path, l_data_path, l_recursive };
}

armory::rsa_generate_decl armory::parse_rsa_generate_decl(
	const std::string& a_line
)
{
	std::vector<std::string> l_split = affix_base::data::string_split(a_line, ' ');
	std::string l_private_key_path = l_split[2];
	std::string l_public_key_path = l_split[3];
	uint16_t l_key_size = 4096;
	if (l_split.size() > 4)
	{
		l_key_size = std::stoi(l_split[4]);
	}
	return armory::rsa_generate_decl{ l_private_key_path, l_public_key_path, l_key_size };
}

armory::rsa_encrypt_decl armory::parse_rsa_encrypt_decl(
	const std::string& a_line
)
{
	std::vector<std::string> l_split = affix_base::data::string_split(a_line, ' ');
	std::string l_key_path = l_split[2];
	std::string l_data_path = l_split[3];
	bool l_recursive = false;
	if (l_split.size() > 4 && l_split[4] == "-r")
	{
		l_recursive = true;
	}
	return armory::rsa_encrypt_decl{ l_key_path, l_data_path, l_recursive };
}

armory::rsa_decrypt_decl armory::parse_rsa_decrypt_decl(
	const std::string& a_line
)
{
	std::vector<std::string> l_split = affix_base::data::string_split(a_line, ' ');
	std::string l_key_path = l_split[2];
	std::string l_data_path = l_split[3];
	bool l_recursive = false;
	if (l_split.size() > 4 && l_split[4] == "-r")
	{
		l_recursive = true;
	}
	return armory::rsa_decrypt_decl{ l_key_path, l_data_path, l_recursive };
}
