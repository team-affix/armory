#pragma once
#include "affix-base/pch.h"
#include <filesystem>
#include "cryptopp/rsa.h"
#include "CLI/CLI.hpp"

namespace armory
{
	struct func_decl_rsa_generate {
	public:
		std::filesystem::path m_private_key_path;
		std::filesystem::path m_public_key_path;
		uint32_t m_key_size = 0;
		bool m_truncate = false;

	protected:
		void pre_execute();
		void process_private_key_path();
		void process_public_key_path();
		void process_key_size();

	protected:
		void execute() const;

	protected:
		void post_execute();

	public:
		func_decl_rsa_generate(
			CLI::App* a_rsa_app
		);

	};
}
