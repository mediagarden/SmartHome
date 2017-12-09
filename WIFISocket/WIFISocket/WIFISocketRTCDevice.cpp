#include "WIFISocketDebug.h"
#include "WIFISocketNTPClient.h"
#include "WIFISocketRTCDevice.h"


WIFISocketRTCDeviceClass::WIFISocketRTCDeviceClass()
{
	mUpdateMillis = MAX_MILLIS;
	mTryMills = MAX_MILLIS;
	mIsAvailable = false;
	mTryStatus = false;
}

void WIFISocketRTCDeviceClass::begin()
{
	mRTC_Millis.begin(DateTime(__DATE__, __TIME__));
}
void WIFISocketRTCDeviceClass::loop()
{
	if (WiFi.isConnected())
	{
		if (abs(((long long int)mUpdateMillis) - ((long long int)millis()))>UPDATE_MILLIS)
		{
			updateCurrentTime();
		}
		else if ((!mTryStatus) && (abs(((long long int)mTryMills) - ((long long int)millis())) > RETRY_MILLIS))
		{
			updateCurrentTime();
		}
	}
}
void WIFISocketRTCDeviceClass::updateCurrentTime()
{
	DateTime dateTime;
	if (WIFISocketNTPClient.getDateTime(dateTime))
	{
		mRTC_Millis.adjust(dateTime);
		mRTC_Millis.begin();
		mIsAvailable = true;
		mUpdateMillis = millis();
		mTryMills = millis();
		mTryStatus = true;
		WIFISocketDebug.Debug("WIFISocket:Update Current Time Success!");
		DateTime now = mRTC_Millis.now();
		WIFISocketDebug.Debug("WIFISocket:Now Time:%d/%d/%d %d:%d:%d!", 
			now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
	}
	else
	{
		mTryMills = millis();
		mTryStatus = false;
		WIFISocketDebug.Debug("WIFISocket:Update Current Time Failed!");
	}
}

DateTime WIFISocketRTCDeviceClass::getCurrentTime()
{
	return mRTC_Millis.now();
}

void WIFISocketRTCDeviceClass::setCurrentTime(DateTime dateTime)
{
	mRTC_Millis.adjust(dateTime);
	mRTC_Millis.begin();
	mUpdateMillis = millis();
	mTryMills = millis();
	mIsAvailable = true;
	WIFISocketDebug.Debug("WIFISocket:Set Current Time Success!");
	DateTime now = mRTC_Millis.now();
	WIFISocketDebug.Debug("WIFISocket:Now Time:%d/%d/%d %d:%d:%d!",
		now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
}

bool WIFISocketRTCDeviceClass::isAvailable()
{
	return mIsAvailable;
}

WIFISocketRTCDeviceClass WIFISocketRTCDevice;

