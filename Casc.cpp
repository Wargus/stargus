/*
 * Casc.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Casc.h"
#include "FileUtil.h"

// System
#include "CascLib.h"
#include <cstdio>
#include <iostream>

using namespace std;

Casc::Casc()
{

}

Casc::~Casc()
{

}

// Not in class member to be not expose Casc to public header
PCASC_FILE_SPAN_INFO GetFileSpanInfo(HANDLE hFile)
{
    PCASC_FILE_SPAN_INFO pSpans = NULL;
    size_t cbLength = 0;

    // Retrieve the full file info
    CascGetFileInfo(hFile, CascFileSpanInfo, pSpans, cbLength, &cbLength);
    if(cbLength != 0)
    {
        if((pSpans = (PCASC_FILE_SPAN_INFO)(new BYTE[cbLength])) != NULL)
        {
            if(CascGetFileInfo(hFile, CascFileSpanInfo, pSpans, cbLength, NULL))
                return pSpans;

            // in case of error...
            free(pSpans);
            pSpans = NULL;
        }
    }

    return pSpans;
}

bool Casc::extractFile(const std::string &archivedFile, const std::string &extractedName, bool compress)
{
    HANDLE hStorage = NULL;        // Open storage handle
    HANDLE hFile  = NULL;          // Storage file handle
    FILE *fileHandle  = NULL;
    bool result = true;

	if(CascOpenStorage(archivedFile.c_str(), 0, &hStorage))
	{
		// Open a file in the storage
		if(CascOpenFile(hStorage, archivedFile.c_str(), 0, 0, &hFile))
		{
			// Read the data from the file
			char  szBuffer[0x10000];
			DWORD dwBytes = 1;

			// quick check if file has valid info
			// TODO: later more details to read out!
			PCASC_FILE_SPAN_INFO cascFileInfo = GetFileSpanInfo(hFile);

			if(cascFileInfo)
			{
				CheckPath(extractedName.c_str());
				fileHandle = fopen(extractedName.c_str(), "wb");

				while(dwBytes != 0)
				{
					CascReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes);
					if(dwBytes == 0)
						break;

					fwrite(szBuffer, 1, dwBytes, fileHandle);
				}

				if(fileHandle != NULL)
				{
					fclose(fileHandle);
				}

				if(hFile != NULL)
				{
					CascCloseFile(hFile);
				}
			}
			else
			{
				cout << "*NOT* Extracting file (invalid info!): " << extractedName << endl;
			}

		}
		else
		{
			cout << "Error: CascOpenFile" << endl;
			result = false;
		}

	}
	else
	{
		cout << "Error: CascOpenStorage" << endl;
		result = false;
	}

    if(hStorage != NULL)
        CascCloseStorage(hStorage);

    return result;
}


