#ifndef _WEATHERINFO_H_
#define _WEATHERINFO_H_

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "JSON\writer.h"
#include "JSON\reader.h"
#include "JSON\value.h"

USING_NS_CC;
using namespace cocos2d::network;
using std::string;

/* ������ȡIP */
#define GET_IP_URL "http://ip.dnsexit.com/"

/* ��ȡλ����Ϣ */
#define GET_CITY_INFO_URL "http://int.dpool.sina.com.cn/iplookup/iplookup.php?format=json&ip=" // + "ip"

/* ��ȡ������Ϣ */
#define GET_WEATHER_INFO "http://m.weather.com.cn/data/" // + "city_code.html"

class WeatherInfo : public Ref {
public:
	static WeatherInfo* getInstance();
	virtual bool init();
	string getWeatherInfo(string url);

private:
	void finshGetData(Ref* data);

private:
	string responseStr;
	static WeatherInfo* _weatherInfo;
};

#endif // !_WEATHERINFO_H_