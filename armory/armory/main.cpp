#include <iostream>
#include <string>
#include "CLI/CLI.hpp"
#include "func_decls.h"
#include "affix-base/string_extensions.h"

int main(int argc, char** argv)
{

#if _DEBUG

	// FOR TESTING ONLY -------------------------------
	std::string l_input_string = "arm rsa transform -d -I output -O output2 -k private.dat";
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

	armory::func_decl_aes_generate l_decl_aes_generate(l_aes_app);
	armory::func_decl_aes_transform l_decl_aes_transform(l_aes_app);
	armory::func_decl_rsa_generate l_decl_rsa_generate(l_rsa_app);
	armory::func_decl_rsa_transform l_decl_rsa_transform(l_rsa_app);
	
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

}
