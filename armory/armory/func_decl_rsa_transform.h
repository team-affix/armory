#pragma once
#include "affix-base/pch.h"
#include <filesystem>
#include "cryptopp/rsa.h"
#include "CLI/CLI.hpp"

namespace armory
{
	struct func_decl_rsa_transform {
	public:
		std::filesystem::path m_public_key_path;
		std::filesystem::path m_private_key_path;
		std::filesystem::path m_data_path;
		CryptoPP::RSA::PublicKey m_public_key;
		CryptoPP::RSA::PrivateKey m_private_key;
		bool m_remove_input_files = false;
		bool m_recursive = false;
		bool m_truncate = false;

	protected:
		void pre_execute();

	protected:
		void execute() const;

	protected:
		void post_execute();

	public:
		func_decl_rsa_transform(
			CLI::App* a_rsa_app
		);

	};
}
