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

/* 外网获取IP */
#define GET_IP_URL "http://ip.dnsexit.com/"

/* 获取位置信息 */
#define GET_CITY_INFO_URL "http://int.dpool.sina.com.cn/iplookup/iplookup.php?format=json&ip=" // + "ip"

/* 获取天气信息 */
#define GET_WEATHER_INFO "http://m.weather.com.cn/data/" // + "city_code.html"

class WeatherInfo : public Ref {
public:
	static WeatherInfo* getInstance();
	virtual bool init();
	string getWeatherInfo(string url);

private:
	void finshGetData(Ref* data);
	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);

private:
	string responseStr;
	static WeatherInfo* _weatherInfo;
};

#endif // !_WEATHERINFO_H_