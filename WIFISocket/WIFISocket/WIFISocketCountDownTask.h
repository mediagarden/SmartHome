#ifndef __WIFISOCKETCOUNTDOWNTASK_H__
#define __WIFISOCKETCOUNTDOWNTASK_H__

class WIFISocketCountDownTaskClass
{
 public:
	WIFISocketCountDownTaskClass();
	void begin();
	void loop();
	void updateSettings();
};

extern WIFISocketCountDownTaskClass WIFISocketCountDownTask;

#endif

