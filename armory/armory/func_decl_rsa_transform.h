#pragma once
#include "affix-base/pch.h"
#include <filesystem>
#include "cryptopp/rsa.h"
#include "CLI/CLI.hpp"

namespace armory
{
	struct func_decl_rsa_transform {
	public:
		std::filesystem::path m_key_path;
		std::filesystem::path m_input_path;
		std::filesystem::path m_output_path;
		bool m_decrypt = false;
		bool m_remove_input_files = false;
		bool m_recursive = false;
		bool m_truncate = false;

	protected:
		CryptoPP::RSA::PublicKey m_public_key;
		CryptoPP::RSA::PrivateKey m_private_key;

	protected:
		void execute();
		void transform(
			const std::filesystem::path& a_input_path,
			const std::filesystem::path& a_output_path,
			const bool& a_is_root
		) const;
		void transform_directory(
			const std::filesystem::path& a_input_path,
			const std::filesystem::path& a_output_path,
			const bool& a_is_root
		) const;
		void transform_file(
			const std::filesystem::path& a_input_path,
			const std::filesystem::path& a_output_path
		) const;

	public:
		func_decl_rsa_transform(
			CLI::App* a_rsa_app
		);

	};
}
