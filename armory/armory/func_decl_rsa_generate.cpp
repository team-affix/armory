#include "func_decl_rsa_generate.h"

using namespace armory;

func_decl_rsa_generate::func_decl_rsa_generate(
	CLI::App* a_rsa_app
)
{

	CLI::App* l_app = a_rsa_app->add_subcommand("generate", "Generates an RSA (public, private) key pair, and stores them in separate files.");

	l_app->callback(
		[&]
		{
			pre_execute();
			execute();
			post_execute();
		}
	);

	CLI::Option* l_private_key_path_option = l_app->add_option("--pr,--private_key_path", m_private_key_path, "The path where the RSA private key is to be stored.");
	l_private_key_path_option->required(true);

	CLI::Option* l_public_key_path_option = l_app->add_option("--pu,--public_key_path", m_public_key_path, "The path where the RSA public key is to be stored.");
	l_public_key_path_option->required(true);

	CLI::Option* l_key_size_option = l_app->add_option("-s,--key_size", m_key_size, "Size of RSA modulus in bits (2048, 4096, etc.).");
	l_key_size_option->required(true);

	CLI::Option* l_truncate_option = l_app->add_flag("--truncate", m_truncate, "Configures overwriting of files that share the output name.");

}

void func_decl_rsa_generate::pre_execute()
{

}

void func_decl_rsa_generate::execute() const
{

}

void func_decl_rsa_generate::post_execute()
{

}
