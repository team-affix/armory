#include "parse.h"
#include "affix-base/string_extensions.h"
#include "process.h"
#include "affix-base/ptr.h"
#include "affix-base/ios.h"
#include <exception>
#include "affix-base/utc_time.h"

using namespace armory;
namespace fs = std::filesystem;

aes_generate_decl::aes_generate_decl(
	CLI::App* a_aes_app,
	bool& a_on_selected
)
{
	CLI::App* l_app = a_aes_app->add_subcommand("generate", "Generates an AES key or an AES IV (or both).");

	l_app->callback(
		[&] 
		{ 
			a_on_selected = true; 
		});
	
	CLI::Option* l_key_path_option = l_app->add_option("-k,--key_path", m_key_path, "The path where the AES key will be stored.");
	CLI::Option* l_iv_path_option = l_app->add_option("-i,--iv_path", m_iv_path, "The path where the IV will be stored.");
	CLI::Option* l_truncate_option = l_app->add_flag("-t,--truncate", m_truncate, "Configures overwriting of files that share the output name.");
	CLI::Option* l_include_timestamp_option = l_app->add_flag("--timestamp", m_include_timestamp, "Prepends a timestamp to the beginning of the outputted files' names.");

	l_app->require_option(1, 2);
}

void aes_generate_decl::post_process()
{
	m_generate_key = m_key_path != "";
	m_generate_iv = m_iv_path != "";

}

aes_encrypt_decl::aes_encrypt_decl(
	CLI::App* a_aes_app,
	bool& a_on_selected
)
{
	CLI::App* l_app = a_aes_app->add_subcommand("encrypt", "Encrypts a file (or folder) using an AES key (and potentially an IV, as well).");

	l_app->callback(
		[&] 
		{ 
			a_on_selected = true; 
			post_process();
		});

	CLI::Option* l_key_path_option = l_app->add_option("-k,--key_path", m_key_path, "The path to the AES key.");
	l_key_path_option->required(true);

	CLI::Option* l_iv_path_option = l_app->add_option("-i,--iv_path", m_iv_path, "The path to the AES IV.");

	CLI::Option* l_data_path_option = l_app->add_option("-d,--data_path", m_data_path, "The path to the file (or folder) intending to be encrypted.");
	l_data_path_option->required(true);

	CLI::Option* l_recursive_option = l_app->add_flag("-r,--recursive", m_recursive, "Set this flag to recursively encrypt all subfolders as well.");

	CLI::Option* l_truncate_option = l_app->add_flag("-t,--truncate", m_truncate, "Configures overwriting of files that share the output name.");
	CLI::Option* l_include_timestamp_option = l_app->add_flag("--timestamp", m_include_timestamp, "Prepends a timestamp to the beginning of the outputted files' names.");

}

void aes_encrypt_decl::post_process()
{
	bool l_key_path_valid = fs::exists(m_key_path) && !fs::is_directory(m_key_path);
	bool l_use_iv = m_iv_path.u8string() != "";
	bool l_iv_path_valid = fs::exists(m_iv_path) && !fs::is_directory(m_iv_path);

	if (!l_key_path_valid)
	{
		throw std::exception("Key path is not a valid path.");
	}
	if (l_use_iv && !l_iv_path_valid)
	{
		throw std::exception("IV path is not a valid path.");
	}
	if (!fs::exists(m_data_path))
	{
		throw std::exception("Data path is not a valid path.");
	}

	affix_base::ios::file_read(m_key_path.u8string(), m_key);

	if (l_use_iv)
	{
		affix_base::ios::file_read(m_iv_path.u8string(), m_iv);
	}

}

aes_decrypt_decl::aes_decrypt_decl(
	CLI::App* a_aes_app,
	bool& a_on_selected
)
{
	CLI::App* l_app = a_aes_app->add_subcommand("decrypt", "Decrypts a file (or folder) using an AES key (and potentially an IV, as well).");

	l_app->callback(
		[&]
		{
			a_on_selected = true;
			post_process();
		});

	CLI::Option* l_key_path_option = l_app->add_option("-k,--key_path", m_key_path, "The path to the AES key.");
	l_key_path_option->required(true);

	CLI::Option* l_iv_path_option = l_app->add_option("-i,--iv_path", m_iv_path, "The path to the AES IV.");

	CLI::Option* l_data_path_option = l_app->add_option("-d,--data_path", m_data_path, "The path to the file (or folder) intending to be decrypted.");
	l_data_path_option->required(true);

	CLI::Option* l_recursive_option = l_app->add_flag("-r,--recursive", m_recursive, "Set this flag to recursively decrypt all subfolders as well.");

	CLI::Option* l_truncate_option = l_app->add_flag("-t,--truncate", m_truncate, "Configures overwriting of files that share the output name.");
	CLI::Option* l_include_timestamp_option = l_app->add_flag("--timestamp", m_include_timestamp, "Prepends a timestamp to the beginning of the outputted files' names.");

}

void aes_decrypt_decl::post_process()
{
	bool l_key_path_valid = fs::exists(m_key_path) && !fs::is_directory(m_key_path);
	bool l_use_iv = m_iv_path.u8string() != "";
	bool l_iv_path_valid = fs::exists(m_iv_path) && !fs::is_directory(m_iv_path);

	if (!l_key_path_valid)
	{
		throw std::exception("Key path is not a valid path.");
	}
	if (l_use_iv && !l_iv_path_valid)
	{
		throw std::exception("IV path is not a valid path.");
	}
	if (!fs::exists(m_data_path))
	{
		throw std::exception("Data path is not a valid path.");
	}

	affix_base::ios::file_read(m_key_path.u8string(), m_key);

	if (l_use_iv)
	{
		affix_base::ios::file_read(m_iv_path.u8string(), m_iv);
	}

}

rsa_generate_decl::rsa_generate_decl(
	CLI::App* a_rsa_app,
	bool& a_on_selected
)
{

	CLI::App* l_app = a_rsa_app->add_subcommand("generate", "Generates an RSA (public, private) key pair, and stores them in separate files.");

	l_app->callback(
		[&]
		{
			a_on_selected = true;
		});

	CLI::Option* l_private_key_path_option = l_app->add_option("--pr,--private_key_path", m_private_key_path, "The path where the RSA private key is to be stored.");
	l_private_key_path_option->required(true);

	CLI::Option* l_public_key_path_option = l_app->add_option("--pu,--public_key_path", m_public_key_path, "The path where the RSA public key is to be stored.");
	l_public_key_path_option->required(true);

	CLI::Option* l_key_size_option = l_app->add_option("-s,--key_size", m_key_size, "Size of RSA modulus in bits (2048, 4096, etc.).");
	l_key_size_option->required(true);

	CLI::Option* l_truncate_option = l_app->add_flag("-t,--truncate", m_truncate, "Configures overwriting of files that share the output name.");
	CLI::Option* l_include_timestamp_option = l_app->add_flag("--timestamp", m_include_timestamp, "Prepends a timestamp to the beginning of the outputted files' names.");

}

rsa_encrypt_decl::rsa_encrypt_decl(
	CLI::App* a_rsa_app,
	bool& a_on_selected
)
{
	CLI::App* l_app = a_rsa_app->add_subcommand("encrypt", "Encrypts (in digestable chunks) a file (or folder) using an RSA public key.");

	l_app->callback(
		[&]
		{
			a_on_selected = true;
			post_process();
		});

	CLI::Option* l_public_key_path_option = l_app->add_option("--pu,--public_key_path", m_public_key_path, "Path to RSA public key.");
	l_public_key_path_option->required(true);

	CLI::Option* l_data_path_option = l_app->add_option("-d,--data_path", m_data_path, "Path to file (or folder) intended to be encrypted.");
	l_data_path_option->required(true);

	CLI::Option* l_recursive_option = l_app->add_flag("-r,--recursive", m_recursive, "Set this flag to recursively encrypt all subfolders as well.");

	CLI::Option* l_truncate_option = l_app->add_flag("-t,--truncate", m_truncate, "Configures overwriting of files that share the output name.");
	CLI::Option* l_include_timestamp_option = l_app->add_flag("--timestamp", m_include_timestamp, "Prepends a timestamp to the beginning of the outputted files' names.");

}

void rsa_encrypt_decl::post_process()
{
	if (!fs::exists(m_public_key_path) || fs::is_directory(m_public_key_path))
	{
		throw std::exception("Public key path is not a valid path.");
	}
	if (!fs::exists(m_data_path))
	{
		throw std::exception("Data path is not a valid path.");
	}
	if (!affix_base::cryptography::rsa_try_import(m_public_key, m_public_key_path.u8string()))
	{
		throw "Malformed public key imported.";
	}

}

rsa_decrypt_decl::rsa_decrypt_decl(
	CLI::App* a_rsa_app,
	bool& a_on_selected
)
{
	CLI::App* l_app = a_rsa_app->add_subcommand("decrypt", "Decrypts (in digestable chunks) a file (or folder) using an RSA private key.");

	l_app->callback(
		[&]
		{
			a_on_selected = true;
			post_process();
		});

	CLI::Option* l_public_key_path_option = l_app->add_option("--pr,--private_key_path", m_private_key_path, "Path to RSA private key.");
	l_public_key_path_option->required(true);

	CLI::Option* l_data_path_option = l_app->add_option("-d,--data_path", m_data_path, "Path to file (or folder) intended to be decrypted.");
	l_data_path_option->required(true);

	CLI::Option* l_recursive_option = l_app->add_flag("-r,--recursive", m_recursive, "Set this flag to recursively decrypt all subfolders as well.");

	CLI::Option* l_truncate_option = l_app->add_flag("-t,--truncate", m_truncate, "Configures overwriting of files that share the output name.");
	CLI::Option* l_include_timestamp_option = l_app->add_flag("--timestamp", m_include_timestamp, "Prepends a timestamp to the beginning of the outputted files' names.");

}

void rsa_decrypt_decl::post_process()
{
	if (!fs::exists(m_private_key_path) || fs::is_directory(m_private_key_path))
	{
		throw std::exception("Private key path is not a valid path.");
	}
	if (!fs::exists(m_data_path))
	{
		throw std::exception("Data path is not a valid path.");
	}
	if (!affix_base::cryptography::rsa_try_import(m_private_key, m_private_key_path.u8string()))
	{
		throw "Malformed private key imported.";
	}
}
