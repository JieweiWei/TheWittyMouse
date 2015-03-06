#ifndef _WEATHERINFO_H_
#define _WEATHERINFO_H_

#include "cocos2d.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace cocos2d::network;
using std::string;

#define WEATHER_DATA_FILE "data/weathers.xml"

#define CITYLIST_XML "data/citylist.xml"

/* 外网获取IP */
#define GET_IP_URL "http://ip.dnsexit.com/"

/* 获取位置信息 */
#define GET_CITY_INFO_URL "http://int.dpool.sina.com.cn/iplookup/iplookup.php?format=json&ip=" // + "ip"

/* 获取天气信息 */
#define GET_WEATHER_INFO "http://m.weather.com.cn/data/%s.html"

class WeatherInfo : public Ref {
public:
	static WeatherInfo* getInstance();
	virtual bool init();
	void getWeatherInfo();

private:
	void httpGet(string url, string notificationType);
	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response, string notificationType);

	void finishGetIp(Ref* data);
	void finishGetCityInfo(Ref* data);
	void finishGetWeatherInfo(Ref* data);

	string parseCityCode(string jsonStr);
	void parseWeatherInfoAndSave(string jsonStr);

private:
	static WeatherInfo* _weatherInfo;
};

#endif // !_WEATHERINFO_H_