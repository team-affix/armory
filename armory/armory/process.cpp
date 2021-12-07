#include "process.h"
#include "affix-base/aes.h"
#include "cryptopp/osrng.h"
#include <fstream>
#include "affix-base/file_ios.h"
#include <filesystem>
#include "affix-base/string_extensions.h"
#include "affix-base/timing.h"

namespace fs = std::filesystem;

void prepend_timestamp(
	std::string& a_string
)
{
	a_string = std::to_string(affix_base::timing::utc_time()) + "-" + a_string;
}


void armory::process_aes_generate(
	const aes_generate_decl& a_decl
)
{
	if (a_decl.m_generate_key)
	{
		std::string l_output_path = a_decl.m_key_path.u8string();

		// CONDITIONALLY INCLUDE TIMESTAMP
		if (a_decl.m_include_timestamp)
			prepend_timestamp(l_output_path);

		bool l_key_path_valid = !fs::is_directory(l_output_path);
		bool l_key_path_exists = fs::exists(l_output_path);

		if (!l_key_path_valid)
			throw std::exception("Invalid key path.");

		if (l_key_path_exists && !a_decl.m_truncate)
			throw std::exception("Key path already exists.");

		std::vector<uint8_t> l_key = affix_base::cryptography::aes_generate_key();
		affix_base::ios::file_write(l_output_path, l_key);

	}

	if (a_decl.m_generate_iv)
	{
		std::string l_output_path = a_decl.m_iv_path.u8string();

		// CONDITIONALLY INCLUDE TIMESTAMP
		if (a_decl.m_include_timestamp)
			prepend_timestamp(l_output_path);

		bool l_iv_path_valid = !fs::is_directory(l_output_path);
		bool l_iv_path_exists = fs::exists(l_output_path);

		if (!l_iv_path_valid)
			throw std::exception("Invalid iv path.");

		if (l_iv_path_exists && !a_decl.m_truncate)
			throw std::exception("IV path already exists.");

		std::vector<uint8_t> l_iv = affix_base::cryptography::aes_generate_iv();
		affix_base::ios::file_write(l_output_path, l_iv);

	}

}

void armory::process_aes_encrypt(
	const aes_encrypt_decl& a_decl
)
{
	// PRE-ORDER TRAVERSAL
	if (fs::is_directory(a_decl.m_data_path))
	{
		for (const auto& entry : fs::directory_iterator(a_decl.m_data_path))
			if (!fs::is_directory(entry) || a_decl.m_recursive)
			{
				aes_encrypt_decl l_decl = a_decl;
				l_decl.m_data_path = entry.path();
				process_aes_encrypt(l_decl);
			}
		return;
	}

	// MAKE SURE FILE EXISTS
	if (!fs::exists(a_decl.m_data_path))
	{
		std::cerr << "Error: The file/folder specified does not exist: " << a_decl.m_data_path << std::endl;
		return;
	}

	// CREATE OUTPUT PATH
	std::string l_output_path = a_decl.m_data_path.u8string();
	l_output_path += ".aes";

	// CONDITIONALLY INCLUDE TIMESTAMP
	if (a_decl.m_include_timestamp)
		prepend_timestamp(l_output_path);

	// CHECK FOR TRUNCATION
	if (fs::exists(l_output_path) && !a_decl.m_truncate)
	{
		std::cerr << "Error: The file already exists: " << l_output_path << std::endl;
		return;
	}

	std::ifstream l_ifs(a_decl.m_data_path, std::ios::in | std::ios::binary);
	std::ofstream l_ofs(l_output_path, std::ios::out | std::ios::binary | std::ios::trunc);
	affix_base::cryptography::aes_encrypt(l_ifs, l_ofs, a_decl.m_key, a_decl.m_iv);

}

void armory::process_aes_decrypt(
	const aes_decrypt_decl& a_decl
)
{
	// PRE-ORDER TRAVERSAL
	if (fs::is_directory(a_decl.m_data_path))
	{
		for (const auto& entry : fs::directory_iterator(a_decl.m_data_path))
			if (!fs::is_directory(entry) || a_decl.m_recursive)
			{
				aes_decrypt_decl l_decl = a_decl;
				l_decl.m_data_path = entry.path();
				process_aes_decrypt(l_decl);
			}
		return;
	}

	// MAKE SURE FILE EXISTS
	if (!fs::exists(a_decl.m_data_path))
	{
		std::cerr << "Error: The file specified does not exist: " << a_decl.m_data_path << std::endl;
		return;
	}

	if (!affix_base::data::string_can_query(a_decl.m_data_path.u8string(), "*.aes"))
	{
		std::cerr << "Error: The file specified does not have the .aes extension: " << a_decl.m_data_path << std::endl;
		return;
	}

	// CREATE OUTPUT PATH
	std::string l_output_path = a_decl.m_data_path.u8string();
	l_output_path.erase(l_output_path.end() - 4, l_output_path.end());

	// CONDITIONALLY INCLUDE TIMESTAMP
	if (a_decl.m_include_timestamp)
		prepend_timestamp(l_output_path);

	// CHECK FOR TRUNCATION
	if (fs::exists(l_output_path) && !a_decl.m_truncate)
	{
		std::cerr << "Error: The file already exists: " << l_output_path << std::endl;
		return;
	}

	std::ifstream l_ifs(a_decl.m_data_path, std::ios::in | std::ios::binary);
	std::ofstream l_ofs(l_output_path, std::ios::out | std::ios::binary | std::ios::trunc);
	affix_base::cryptography::aes_decrypt(l_ifs, l_ofs, a_decl.m_key, a_decl.m_iv);

}

void armory::process_rsa_generate(
	const rsa_generate_decl& a_decl
)
{

}

void armory::process_rsa_encrypt(
	const rsa_encrypt_decl& a_decl
)
{

}

void armory::process_rsa_decrypt(
	const rsa_decrypt_decl& a_decl
)
{

}
