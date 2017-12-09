#ifndef __WIFISOCKETTIMINGTASK_H__
#define __WIFISOCKETTIMINGTASK_H__
class WIFISocketTimingTaskClass
{
 public:
	 WIFISocketTimingTaskClass();
	 void begin();
	 void loop();
	 void updateSettings(int id);
};

extern WIFISocketTimingTaskClass WIFISocketTimingTask;

#endif

