#pragma once
#include "affix-base/pch.h"

namespace armory {
	
	struct aes_generate_decl {
		std::string m_key_path;
	};

	struct aes_encrypt_decl {
		std::string m_key_path;
		std::string m_data_path;
		bool m_recursive;
	};

	struct aes_decrypt_decl {
		std::string m_key_path;
		std::string m_data_path;
		bool m_recursive;
	};

	struct rsa_generate_decl {
		std::string m_private_key_path;
		std::string m_public_key_path;
		uint16_t m_key_size;
	};

	struct rsa_encrypt_decl {
		std::string m_key_path;
		std::string m_data_path;
		bool m_recursive;
	};

	struct rsa_decrypt_decl {
		std::string m_key_path;
		std::string m_data_path;
		bool m_recursive;
	};

	aes_generate_decl parse_aes_generate_decl(
		const std::string& a_line
	);

	aes_encrypt_decl parse_aes_encrypt_decl(
		const std::string& a_line
	);

	aes_decrypt_decl parse_aes_decrypt_decl(
		const std::string& a_line
	);

	rsa_generate_decl parse_rsa_generate_decl(
		const std::string& a_line
	);

	rsa_encrypt_decl parse_rsa_encrypt_decl(
		const std::string& a_line
	);

	rsa_decrypt_decl parse_rsa_decrypt_decl(
		const std::string& a_line
	);

}
