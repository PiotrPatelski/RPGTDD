#include <AssetsManager.hpp>

namespace FileMgmt
{

std::string AssetsManager::buildPath = std::filesystem::current_path().string() + "/../build/";

}