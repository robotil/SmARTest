#include "utils/Utilities.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/algorithm/string/replace.hpp"


namespace fs = boost::filesystem;

void Utilities::copyDirectoryRecursively(const fs::path& sourceDir, const fs::path& destinationDir)
{
    if (!fs::exists(sourceDir) || !fs::is_directory(sourceDir))
    {
        throw std::runtime_error("Source directory " + sourceDir.string() + " does not exist or is not a directory");
    }
    if (fs::exists(destinationDir))
    {
        throw std::runtime_error("Destination directory " + destinationDir.string() + " already exists");
    }
    if (!fs::create_directory(destinationDir))
    {
        throw std::runtime_error("Cannot create destination directory " + destinationDir.string());
    }

    for (const auto& dirEnt : fs::recursive_directory_iterator{sourceDir})
    {
        const auto& path = dirEnt.path();
        auto relativePathStr = path.string();
        boost::replace_first(relativePathStr, sourceDir.string(), "");
        fs::copy(path, destinationDir / relativePathStr);
    }
}