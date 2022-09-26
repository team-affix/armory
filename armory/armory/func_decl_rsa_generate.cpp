#include "func_decl_rsa_generate.h"
#include "affix-base/rsa.h"

using namespace armory;
namespace fs = std::filesystem;

func_decl_rsa_generate::func_decl_rsa_generate(
	CLI::App* a_rsa_app
)
{

	CLI::App* l_app = a_rsa_app->add_subcommand("generate", "Generates an RSA (public, private) key pair, and stores them in separate files.");

	l_app->callback(
		[&]
		{
			execute();
		}
	);

	CLI::Option* l_private_key_path_option = l_app->add_option("--pr,--private", m_private_key_path, "The path where the RSA private key is to be stored.");
	l_private_key_path_option->required(true);

	CLI::Option* l_public_key_path_option = l_app->add_option("--pu,--public", m_public_key_path, "The path where the RSA public key is to be stored.");
	l_public_key_path_option->required(true);

	CLI::Option* l_key_size_option = l_app->add_option("-s,--key_size", m_key_size, "Size of RSA modulus in bits (1024, 2048, 4096, etc.).");
	l_key_size_option->required(true);

	CLI::Option* l_truncate_option = l_app->add_flag("--truncate", m_truncate, "Configures overwriting of files that share the output name.");

}

void func_decl_rsa_generate::execute()
{
	using namespace affix_base::cryptography;

	// Check private key path
	if (fs::exists(m_private_key_path))
	{
		if (fs::is_directory(m_private_key_path))
		{
			throw std::exception("Private key path already exists as a directory.");
		}
		else if (!m_truncate)
		{
			throw std::exception("Private key path already occupied.");
		}
	}

	// Check public key path
	if (fs::exists(m_public_key_path))
	{
		if (fs::is_directory(m_public_key_path))
		{
			throw std::exception("Public key path already exists as a directory.");
		}
		else if (!m_truncate)
		{
			throw std::exception("Public key path already occupied.");
		}
	}

	// Check key size
	if (m_key_size % 1024 != 0)
	{
		throw std::exception("Key size is not a multiple of 1024.");
	}

	rsa_key_pair l_key_pair = rsa_generate_key_pair(m_key_size);
	
	rsa_export(l_key_pair.private_key, m_private_key_path.u8string());
	rsa_export(l_key_pair.public_key, m_public_key_path.u8string());

}
