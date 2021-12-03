#pragma once
#include "affix-base/pch.h"
#include "parse.h"

namespace armory {

	void input_line(
		const std::string& a_line
	);

	void call_aes_generate(
		const aes_generate_decl& a_decl
	);

	void call_aes_encrypt(
		const aes_encrypt_decl& a_decl
	);

	void call_aes_decrypt(
		const aes_decrypt_decl& a_decl
	);

	void call_rsa_generate(
		const rsa_generate_decl& a_decl
	);

	void call_rsa_encrypt(
		const rsa_encrypt_decl& a_decl
	);

	void call_rsa_decrypt(
		const rsa_decrypt_decl& a_decl
	);

}
