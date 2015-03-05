#include "WeatherInfo.h"

WeatherInfo* WeatherInfo::_weatherInfo = NULL;

WeatherInfo* WeatherInfo::getInstance() {
	if (_weatherInfo == NULL) {
		_weatherInfo = new WeatherInfo();
		if (_weatherInfo && _weatherInfo->init()) {
			_weatherInfo->autorelease();
			_weatherInfo->retain();
		}
		else {
			CC_SAFE_DELETE(_weatherInfo);
			_weatherInfo = NULL;
		}
	}
	return _weatherInfo;
}

bool WeatherInfo::init() {
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(WeatherInfo::finshGetData),
		"getData",
		NULL
	);
	return true;
}

string WeatherInfo::getWeatherInfo(string url) {
	/*
	HttpRequest* request = new HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl(url.c_str());
	request->setResponseCallback(CC_CALLBACK_2(WeatherInfo::onHttpRequestCompleted, this));
	HttpClient::getInstance()->send(request);
	request->release();
	*/
	return "";
}
void WeatherInfo::finshGetData(Ref* data) {

}

