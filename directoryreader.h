#ifndef DIRECTORYREADER_H_INCLUDED
#define DIRECTORYREADER_H_INCLUDED

#include "dirent.h"
#include <iostream>
#include <string>
#include <errno.h>
#include "vector.h"

static Vector<std::string> files; //global, dosent matter we tryna encrypt not secure these files

struct DirectoryReader
{
	static int parseDirectory(std::string readingDirectory, int level);
};

int DirectoryReader::parseDirectory(std::string readingDirectory, int level)
{
	DIR *dp; // directory
	struct dirent *dirp; // used to redirect diectories
	if ((dp = opendir(readingDirectory.c_str())) == NULL)
	{
		files.push(readingDirectory);
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_name[0] != '.')
			parseDirectory(readingDirectory + "/" + dirp->d_name, level + 1);
		// redirects to next directory
	}
	closedir(dp);
	return 0;
}

#endif // DIRECTORYREADER_H_INCLUDED