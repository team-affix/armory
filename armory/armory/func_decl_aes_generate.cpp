#include "func_decl_aes_generate.h"
#include "affix-base/files.h"
#include "affix-base/cryptography.h"
#include <filesystem>

using namespace armory;
namespace fs = std::filesystem;

func_decl_aes_generate::func_decl_aes_generate(
	CLI::App* a_aes_app
)
{
	CLI::App* l_app = a_aes_app->add_subcommand("generate", "Generates an AES key or an AES IV (or both).");

	l_app->callback(
		[&]
		{
			pre_execute();
			execute();
			post_execute();
		}
	);

	CLI::Option_group* l_option_group = l_app->add_option_group("generation_options", "Options for generation.");
	l_option_group->require_option(1, 0);

	CLI::Option* l_key_path_option = l_option_group->add_option("-k,--key_path", m_key_path, "The path where the AES key will be stored.");
	CLI::Option* l_iv_path_option = l_option_group->add_option("-i,--iv_path", m_iv_path, "The path where the IV will be stored.");

	CLI::Option* l_truncate_option = l_app->add_flag("--truncate", m_truncate, "Configures overwriting of files that share the output name.");

}

void func_decl_aes_generate::pre_execute()
{
	process_key_path();
	process_iv_path();

}

void func_decl_aes_generate::process_key_path()
{
	m_generate_key = m_key_path != "";

	if (!m_generate_key)
		return;

	bool l_key_path_valid = !fs::is_directory(m_key_path);
	bool l_key_path_exists = fs::exists(m_key_path);
	
	if (!l_key_path_valid)
		throw std::exception("Invalid key path.");

	if (l_key_path_exists && !m_truncate)
		throw std::exception("Key path already exists.");

}

void func_decl_aes_generate::process_iv_path()
{
	m_generate_iv = m_iv_path != "";

	if (!m_generate_iv)
		return;

	bool l_iv_path_valid = !fs::is_directory(m_iv_path);
	bool l_iv_path_exists = fs::exists(m_iv_path);

	if (!l_iv_path_valid)
		throw std::exception("Invalid iv path.");

	if (l_iv_path_exists && !m_truncate)
		throw std::exception("IV path already exists.");

}

void func_decl_aes_generate::execute() const
{
	if (m_generate_key)
		generate_key();
	if (m_generate_iv)
		generate_iv();

}

void func_decl_aes_generate::generate_key() const
{
	std::vector<uint8_t> l_key = affix_base::cryptography::aes_generate_key();
	affix_base::files::file_write(m_key_path.u8string(), l_key);
}

void func_decl_aes_generate::generate_iv() const
{
	std::vector<uint8_t> l_iv = affix_base::cryptography::aes_generate_iv();
	affix_base::files::file_write(m_iv_path.u8string(), l_iv);
}

void func_decl_aes_generate::post_execute()
{

}
