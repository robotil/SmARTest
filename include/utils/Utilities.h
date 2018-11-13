#ifndef UTILITIES_H
#define UTILITIES_H

/**
* Utilities.h
* Author: Binyamin Appelbaum
* Date: 3.12.17
* Author: Michele Hallak-Stamler
* Date: 13.11.18
*/

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::ptime
#include <boost/filesystem.hpp> // boost::filesystem::perms
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/algorithm/string/replace.hpp"


namespace fs = boost::filesystem;

namespace Utilities {

    /******************************************************** File System **********************************************************/

    
    void copyDirectoryRecursively(const fs::path& sourceDir, const fs::path& destinationDir);
}

#endif //UTILITIES_H