#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>

#include "dir.h"

int countFilesInFolder(char *folder) //Itt már nem fájlokat, hanem entryket számolok
{

	struct dirent *de;
    int fileCount = 0;

	DIR *dr = opendir(folder);

	if (dr == NULL)
	{
		return 0;
	}

	while ((de = readdir(dr)) != NULL)
    {
        if (de->d_name[0] != '.') {
            fileCount++;
        }
    }

	closedir(dr);

	return fileCount;
}

int countSubfoldersInFolder(char *folder)
{
	struct dirent *de;
    int folderCount = 0;

	DIR *dr = opendir(folder);

	if (dr == NULL)
	{
		return 0;
	}

	while ((de = readdir(dr)) != NULL)
    {
        if (de->d_name[0] != '.') {
            folderCount++;
        }
    }

	closedir(dr);

	return folderCount;
}

char **getSubfoldersInFolder(char *folder)
{
    struct dirent *de;
    int folderCount = countSubfoldersInFolder(folder);

    char ** subfolderNames = (char **) malloc(folderCount * sizeof(char *));

	DIR *dr = opendir(folder);

	if (dr == NULL)
	{
		return 0;
	}

	int i = 0;
	while ((de = readdir(dr)) != NULL)
    {
        if (de->d_name[0] != '.') {

            subfolderNames[i] = (char *) malloc(255);
            strcpy(subfolderNames[i], de->d_name);

            i++;
        }
    }

	closedir(dr);

	return subfolderNames;
}
