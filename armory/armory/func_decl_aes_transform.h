#pragma once
#include "affix-base/pch.h"
#include <filesystem>
#include "cryptopp/rsa.h"
#include "CLI/CLI.hpp"

namespace armory
{
	struct func_decl_aes_transform {
	protected:
		std::filesystem::path m_key_path;
		std::filesystem::path m_iv_path;
		std::filesystem::path m_input_path;
		std::filesystem::path m_output_path;
		std::vector<uint8_t> m_key;
		std::vector<uint8_t> m_iv;
		bool m_decrypt = false;
		bool m_delete_after = false;
		bool m_recursive = false;
		bool m_truncate = false;
		bool m_use_iv = false;

	protected:
		void pre_execute();
		void process_key_path();
		void process_iv_path();
		void process_data_path();

	protected:
		void execute() const;
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

	protected:
		void post_execute();

	public:
		func_decl_aes_transform(
			CLI::App* a_aes_app
		);

	};
}
