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
		bool m_generate_key = false;
		bool m_generate_iv = false;
		bool m_truncate = false;

	protected:
		void pre_execute();
		void process_key_path();
		void process_iv_path();

	protected:
		void execute() const;
		void generate_key() const;
		void generate_iv() const;

	protected:
		void post_execute();

	public:
		func_decl_aes_generate(
			CLI::App* a_aes_app
		);

	};
}
