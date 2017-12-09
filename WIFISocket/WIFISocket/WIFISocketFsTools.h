#ifndef __WIFISOCKETFSTOOLS_H__
#define __WIFISOCKETFSTOOLS_H__
#include <Arduino.h>
#include <FS.h>
#include <ArduinoJson.h>
class WIFISocketFsToolsClass
{
public:
	WIFISocketFsToolsClass();

	size_t ReadFile(const String file, char buffer[], size_t len);
	size_t WriteFile(const String file, char buffer[], size_t len);

	bool CopyFile(const String destFile, const String srcFile);
	void PrintFile(const String file);
};
extern WIFISocketFsToolsClass WIFISocketFsTools;

#endif

