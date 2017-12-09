#ifndef _WIFISOCKETRTCDEVICE_H
#define _WIFISOCKETRTCDEVICE_H
#include "RTClib.h"
/*JinZhu 17/12/3 Review */
#define		MAX_MILLIS				4294967295
#define		UPDATE_MILLIS			3600000
#define		RETRY_MILLIS				10000

class WIFISocketRTCDeviceClass
{
 public:
	 WIFISocketRTCDeviceClass();
	 void begin();
	 void loop();
	 DateTime getCurrentTime();
	 void setCurrentTime(DateTime dateTime);
	 bool  isAvailable();
private:
	void updateCurrentTime();
private:
	RTC_Millis		mRTC_Millis;
	uint32_t		mUpdateMillis;
	uint32_t		mTryMills;
	bool				mTryStatus;
	bool				mIsAvailable;
};

extern WIFISocketRTCDeviceClass WIFISocketRTCDevice;

#endif

