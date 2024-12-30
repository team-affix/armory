#pragma once
#include "affix-base/pch.h"
#include <filesystem>
#include "cryptopp/rsa.h"
#include "CLI/CLI.hpp"

namespace armory
{
	struct func_decl_aes_generate
	{
	protected:
		std::filesystem::path m_key_path;
		std::filesystem::path m_iv_path;
		bool m_truncate = false;

	protected:
		void execute();
		void generate_key() const;
		void generate_iv() const;

	public:
		func_decl_aes_generate(
			CLI::App* a_aes_app
		);

	};
}
