#include "func_decl_rsa_transform.h"
#include "affix-base/files.h"
#include "affix-base/cryptography.h"

using namespace armory;
namespace fs = std::filesystem;

func_decl_rsa_transform::func_decl_rsa_transform(
	CLI::App* a_rsa_app
)
{
	CLI::App* l_app = a_rsa_app->add_subcommand("encrypt", "Encrypts (in digestable chunks) a file (or folder) using an RSA public key.");

	l_app->callback([&] { execute(); });

	CLI::Option* l_public_key_path_option = l_app->add_option("--pu,--public_key_path", m_public_key_path, "Path to RSA public key.");
	l_public_key_path_option->required(true);

	CLI::Option* l_data_path_option = l_app->add_option("-d,--data_path", m_data_path, "Path to file (or folder) intended to be encrypted.");
	l_data_path_option->required(true);

	CLI::Option* l_remote_original_file = l_app->add_flag("--delete", m_remove_input_files, "Deletes the input files after process is completed.");
	CLI::Option* l_recursive_option = l_app->add_flag("--recursive", m_recursive, "Set this flag to recursively process all subfolders as well.");
	CLI::Option* l_truncate_option = l_app->add_flag("--truncate", m_truncate, "Configures overwriting of files that share the output name.");

}

void func_decl_rsa_transform::pre_execute()
{

}

void func_decl_rsa_transform::execute() const
{

}

void func_decl_rsa_transform::post_execute()
{
	if (!fs::exists(m_public_key_path) || fs::is_directory(m_public_key_path))
	{
		throw std::exception("Public key path is not a valid path.");
	}
	if (!fs::exists(m_data_path))
	{
		throw std::exception("Data path is not a valid path.");
	}
	if (!affix_base::cryptography::rsa_try_import(m_public_key, m_public_key_path.u8string()))
	{
		throw "Malformed public key imported.";
	}

}
