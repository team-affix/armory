#pragma once
#include "affix-base/pch.h"
#include <filesystem>
#include "cryptopp/rsa.h"
#include "CLI/CLI.hpp"

namespace armory {
	
	struct aes_generate_decl {
	public:
		std::filesystem::path m_key_path;
		std::filesystem::path m_iv_path;
		bool m_generate_key = false;
		bool m_generate_iv = false;
		bool m_avoid_conflicts = false;
		bool m_truncate = false;

	public:
		aes_generate_decl(
			CLI::App* a_aes_app,
			bool& a_on_selected
		);

	protected:
		void post_process();

	};

	struct aes_encrypt_decl {
	public:
		std::vector<uint8_t> m_key;
		std::vector<uint8_t> m_iv;
		std::filesystem::path m_data_path;
		bool m_truncate = false;
		bool m_avoid_conflicts = false;
		bool m_recursive = false;

	public:
		aes_encrypt_decl(
			CLI::App* a_aes_app,
			bool& a_on_selected
		);

	protected:
		std::filesystem::path m_key_path;
		std::filesystem::path m_iv_path;
		void post_process();

	};

	struct aes_decrypt_decl {
	public:
		std::vector<uint8_t> m_key;
		std::vector<uint8_t> m_iv;
		std::filesystem::path m_data_path;
		bool m_truncate = false;
		bool m_avoid_conflicts = false;
		bool m_recursive = false;

	public:
		aes_decrypt_decl(
			CLI::App* a_aes_app,
			bool& a_on_selected
		);

	protected:
		std::filesystem::path m_key_path;
		std::filesystem::path m_iv_path;
		void post_process();

	};

	struct rsa_generate_decl {
	public:
		std::filesystem::path m_private_key_path;
		std::filesystem::path m_public_key_path;
		uint16_t m_key_size = 0;
		bool m_truncate = false;
		bool m_avoid_conflicts = false;

	public:
		rsa_generate_decl(
			CLI::App* a_rsa_app,
			bool& a_on_selected
		);

	};

	struct rsa_encrypt_decl {
	public:
		CryptoPP::RSA::PublicKey m_public_key;
		std::filesystem::path m_data_path;
		bool m_truncate = false;
		bool m_avoid_conflicts = false;
		bool m_recursive = false;

	public:
		rsa_encrypt_decl(
			CLI::App* a_rsa_app,
			bool& a_on_selected
		);

	protected:
		std::filesystem::path m_public_key_path;
		void post_process();

	};

	struct rsa_decrypt_decl {
	public:
		CryptoPP::RSA::PrivateKey m_private_key;
		std::filesystem::path m_data_path;
		bool m_truncate = false;
		bool m_avoid_conflicts = false;
		bool m_recursive = false;

	public:
		rsa_decrypt_decl(
			CLI::App* a_rsa_app,
			bool& a_on_selected
		);

	protected:
		std::filesystem::path m_private_key_path;
		void post_process();

	};

}
