#include <iostream>
#include <string>
#include "parse.h"
#include "process.h"
#include "CLI/CLI.hpp"
#include "affix-base/string_extensions.h"

int main(int argc, char** argv)
{

#if _DEBUG

	// FOR TESTING ONLY -------------------------------
	std::string l_input_string = "arm aes decrypt -d 1638859030-data.txt.aes -k key.dat";
	std::vector<std::string> l_input = affix_base::data::string_split(l_input_string, ' ');
	argc = l_input.size();
	std::vector<char*> l_input_converted;
	for (int i = 0; i < l_input.size(); i++)
	{
		l_input_converted.push_back(l_input[i].data());
	}
	argv = l_input_converted.data();
	// ------------------------------------------------

#endif


	CLI::App l_app("Armory: local file encryption.", "arm");
	l_app.require_subcommand(1);

	CLI::App* l_aes_app = l_app.add_subcommand("aes", "AES (Advanced Encryption Standard) symmetric cryptographic algorithms.");
	CLI::App* l_rsa_app = l_app.add_subcommand("rsa", "RSA (Rivest Shamir Adleman) asymmetric cryptographic algorithms.");

	bool l_aes_generate_selected = false;
	armory::aes_generate_decl l_aes_generate_decl(l_aes_app, l_aes_generate_selected);

	bool l_aes_encrypt_selected = false;
	armory::aes_encrypt_decl l_aes_encrypt_decl(l_aes_app, l_aes_encrypt_selected);

	bool l_aes_decrypt_selected = false;
	armory::aes_decrypt_decl l_aes_decrypt_decl(l_aes_app, l_aes_decrypt_selected);

	bool l_rsa_generate_selected = false;
	armory::rsa_generate_decl l_rsa_generate_decl(l_rsa_app, l_rsa_generate_selected);

	bool l_rsa_encrypt_selected = false;
	armory::rsa_encrypt_decl l_rsa_encrypt_decl(l_rsa_app, l_rsa_encrypt_selected);

	bool l_rsa_decrypt_selected = false;
	armory::rsa_decrypt_decl l_rsa_decrypt_decl(l_rsa_app, l_rsa_decrypt_selected);
	
	// PARSE ACTUAL DATA
	try {
		l_app.parse(argc, argv);
	}
	catch (const CLI::ParseError& e) {
		return l_app.exit(e);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	try
	{
		if (l_aes_generate_selected)
		{
			armory::process_aes_generate(l_aes_generate_decl);
		}
		else if (l_aes_encrypt_selected)
		{
			armory::process_aes_encrypt(l_aes_encrypt_decl);
		}
		else if (l_aes_decrypt_selected)
		{
			armory::process_aes_decrypt(l_aes_decrypt_decl);
		}
		else if (l_rsa_generate_selected)
		{
			armory::process_rsa_generate(l_rsa_generate_decl);
		}
		else if (l_rsa_encrypt_selected)
		{
			armory::process_rsa_encrypt(l_rsa_encrypt_decl);
		}
		else if (l_rsa_decrypt_selected)
		{
			armory::process_rsa_decrypt(l_rsa_decrypt_decl);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

}
