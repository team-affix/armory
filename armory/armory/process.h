#pragma once
#include "affix-base/aes.h"
#include "affix-base/rsa.h"
#include <string>
#include "parse.h"

namespace armory {
	
	void process_aes_generate(
		const aes_generate_decl& a_decl
	);

	void process_aes_encrypt(
		const aes_encrypt_decl& a_decl
	);

	void process_aes_decrypt(
		const aes_decrypt_decl& a_decl
	);

	void process_rsa_generate(
		const rsa_generate_decl& a_decl
	);

	void process_rsa_encrypt(
		const rsa_encrypt_decl& a_decl
	);

	void process_rsa_decrypt(
		const rsa_decrypt_decl& a_decl
	);

}
