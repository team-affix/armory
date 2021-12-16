#include "func_decl_rsa_transform.h"
#include "affix-base/files.h"
#include "affix-base/cryptography.h"

using namespace armory;
namespace fs = std::filesystem;
using namespace affix_base::cryptography;

func_decl_rsa_transform::func_decl_rsa_transform(
	CLI::App* a_rsa_app
)
{
	CLI::App* l_app = a_rsa_app->add_subcommand("transform", "Transforms (in digestable chunks) a file (or folder) using an RSA public/private key.");

	l_app->callback(
		[&] 
		{
			pre_execute();
			execute();
			post_execute();
		});

	CLI::Option_group* l_transform_option = l_app->add_option_group("transform_options", "Available transformations.");
	l_transform_option->require_option(1);

	l_transform_option->add_flag("-e,--encrypt", "Encrypts the file or folder.");
	l_transform_option->add_flag("-d,--decrypt", m_decrypt, "Decrypts the file or folder");

	CLI::Option* l_public_key_path_option = l_app->add_option("-k,--key", m_key_path, "Path to RSA public/private key.");
	l_public_key_path_option->required(true);

	CLI::Option* l_input_path_option = l_app->add_option("-I,--input", m_input_path, "Path to file (or folder) intended to be transformed.");
	l_input_path_option->required(true);

	CLI::Option* l_output_path_option = l_app->add_option("-O,--output", m_output_path, "Path where the outputted contents are intended to be stored.");
	l_output_path_option->required(true);

	CLI::Option* l_remote_original_file = l_app->add_flag("--delete", m_remove_input_files, "Deletes the input files after process is completed.");
	CLI::Option* l_recursive_option = l_app->add_flag("--recursive", m_recursive, "Set this flag to recursively process all subfolders as well.");
	CLI::Option* l_truncate_option = l_app->add_flag("--truncate", m_truncate, "Configures overwriting of files that share the output name.");

}

void func_decl_rsa_transform::pre_execute()
{
	process_key_path();
	process_input_path();

}

void func_decl_rsa_transform::process_key_path()
{
	if (!fs::exists(m_key_path) || fs::is_directory(m_key_path))
	{
		throw std::exception("Key path does not point to a file.");
	}

	if (!m_decrypt)
	{
		if (!rsa_try_import(m_public_key, m_key_path.u8string()))
		{
			throw std::exception("Failed to import public key.");
		}
	}
	else
	{
		if (!rsa_try_import(m_private_key, m_key_path.u8string()))
		{
			throw std::exception("Failed to import private key.");
		}
	}

}

void func_decl_rsa_transform::process_input_path()
{
	if (!fs::exists(m_key_path))
	{
		throw std::exception("Input path invalid.");
	}
}

void func_decl_rsa_transform::execute() const
{
	transform(m_input_path, m_output_path, true);
}

void func_decl_rsa_transform::transform(
	const std::filesystem::path& a_input_path,
	const std::filesystem::path& a_output_path,
	const bool& a_is_root
) const
{
	if (fs::is_directory(a_input_path))
		transform_directory(a_input_path, a_output_path, a_is_root);
	else
		transform_file(a_input_path, a_output_path);
}

void func_decl_rsa_transform::transform_directory(
	const std::filesystem::path& a_input_path,
	const std::filesystem::path& a_output_path,
	const bool& a_is_root
) const
{
	// IF RECURSION IS DISABLED, RETURN
	if (!a_is_root && !m_recursive)
		return;

	// CREATE OUTPUT FOLDER IF DOESN'T ALREADY EXIST
	if (!fs::exists(a_output_path))
	{
		fs::create_directories(a_output_path);
	}
	else if (!fs::is_directory(a_output_path))
	{
		std::cerr << "Error: " << a_output_path << " is not a directory name." << std::endl;
		return;
	}

	// LOOP THROUGH FILES/FOLDERS
	for (const auto& entry : fs::directory_iterator(a_input_path))
	{
		std::string l_entry_output_path =
			a_output_path.u8string() + "/" + entry.path().filename().u8string();
		transform(entry.path(), l_entry_output_path, false);
	}

}

void func_decl_rsa_transform::transform_file(
	const std::filesystem::path& a_input_path,
	const std::filesystem::path& a_output_path
) const
{
	// MAKE SURE FILE EXISTS
	if (!fs::exists(a_input_path))
	{
		std::cerr << "Error: The file/folder specified does not exist: " << a_input_path << std::endl;
		return;
	}

	// CHECK FOR TRUNCATION
	if (fs::exists(a_output_path) && !m_truncate)
	{
		std::cerr << "Error: The file already exists: " << a_output_path << std::endl;
		return;
	}

	std::ifstream l_ifs(a_input_path, std::ios::in | std::ios::binary);
	std::ofstream l_ofs(a_output_path, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!m_decrypt)
		affix_base::cryptography::rsa_encrypt(l_ifs, l_ofs, m_public_key);
	else
		affix_base::cryptography::rsa_decrypt(l_ifs, l_ofs, m_private_key);

}

void func_decl_rsa_transform::post_execute()
{

}
