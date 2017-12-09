#include "WIFISocketFsTools.h"
#include "WIFISocketCommon.h"
WIFISocketFsToolsClass::WIFISocketFsToolsClass()
{
}

size_t WIFISocketFsToolsClass::ReadFile(const String file, char buffer[], size_t len)
{
	SPIFFS.begin();
	if (!SPIFFS.exists(file))
	{
		SPIFFS.end();
		return false;
	}
	File fp = SPIFFS.open(file, "r");
	int totalsize = fp.read((uint8_t*)buffer, len);
	fp.close();
	SPIFFS.end();
	return totalsize;
}

size_t WIFISocketFsToolsClass::WriteFile(const String file, char buffer[], size_t len)
{
	SPIFFS.begin();
	if (SPIFFS.exists(file))
	{
		SPIFFS.remove(file);
	}
	File fp = SPIFFS.open(file, "w");
	int totalsize = fp.write((uint8_t*)buffer, len);
	fp.close();
	SPIFFS.end();
	return totalsize;
}

bool WIFISocketFsToolsClass::CopyFile(const String destFile, const String srcFile)
{
	char* Buffer = new char[CONFIG_FILE_MAXSIZE];
	memset(Buffer, 0, sizeof(Buffer));
	SPIFFS.begin();
	if (!SPIFFS.exists(srcFile))
	{
		SPIFFS.end();
		delete[] Buffer;
		return false;
	}
	if (SPIFFS.exists(destFile))
	{
		SPIFFS.remove(destFile);
	}
	File srcfp = SPIFFS.open(srcFile, "r");
	int totalsize=srcfp.read((uint8_t*)Buffer, CONFIG_FILE_MAXSIZE);
	srcfp.close();
	File destfp = SPIFFS.open(destFile, "w");
	destfp.write((uint8_t*)Buffer, totalsize);
	destfp.close();
	SPIFFS.end();
	delete[] Buffer;
	return true;
}

void WIFISocketFsToolsClass::PrintFile(const String file)
{
	char* Buffer = new char[CONFIG_FILE_MAXSIZE];
	memset(Buffer, 0, sizeof(Buffer));
	SPIFFS.begin();
	if (!SPIFFS.exists(file))
	{
		SPIFFS.end();
		delete[] Buffer;
		return;
	}
	File srcfp = SPIFFS.open(file, "r");
	srcfp.read((uint8_t*)Buffer, CONFIG_FILE_MAXSIZE);
	srcfp.close();
	SPIFFS.end();
	Serial.println(Buffer);
	delete[] Buffer;
}

WIFISocketFsToolsClass WIFISocketFsTools;