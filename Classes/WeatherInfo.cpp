#include "WeatherInfo.h"
#include "JSON\writer.h"
#include "JSON\reader.h"
#include "JSON\value.h"
#include "Tinyxml\tinyxml.h"

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
		callfuncO_selector(WeatherInfo::finishGetIp),
		"getIp",
		NULL
	);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(WeatherInfo::finishGetCityInfo),
		"getCityInfo",
		NULL
	);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(WeatherInfo::finishGetWeatherInfo),
		"getWeatherInfo",
		NULL
	);
	return true;
}

void WeatherInfo::getWeatherInfo() {
	httpGet(GET_IP_URL, "getIp");
}


void WeatherInfo::httpGet(string url, string notificationType) {
	log(("GET : " + url).c_str());
	log(notificationType.c_str());
	HttpRequest* request = new HttpRequest();
	request = new HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl(url.c_str());
	request->setResponseCallback(CC_CALLBACK_2(WeatherInfo::onHttpRequestCompleted, this, notificationType));
	HttpClient::getInstance()->send(request);
	request->release();
}

void WeatherInfo::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response, string notificationType) {
	if (!response) {
		return;
	}
	if (strlen(response->getHttpRequest()->getTag()) != 0) {
		log("%s completed", response->getHttpRequest()->getTag());
	}
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	log("response code: %s", statusString);
	if (!response->isSucceed()) {
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	/* dump data */
	string responseStr = "";
	std::vector<char> *buffer = response->getResponseData();
	for (unsigned int i = 0; i < buffer->size(); ++i) {
		responseStr += (*buffer)[i];
	}
	if (responseStr != "") {
		NotificationCenter::getInstance()->postNotification(notificationType, (Ref*)responseStr.c_str());
	}
	else {
		log("response empty");
	}
}

void WeatherInfo::finishGetIp(Ref* data) {
	if (data == NULL) {
		log("get ip fail");
		return;
	}
	httpGet(GET_CITY_INFO_URL + string((const char*)data), "getCityInfo");
}

void WeatherInfo::finishGetCityInfo(Ref* data) {
	if (data == NULL) {
		log("get city code fail");
		return;
	}
	string cityCode = parseCityCode((const char*)data);
	if (cityCode == "") {
		log("parse city code fail");
		return;
	}
	httpGet(StringUtils::format(GET_WEATHER_INFO, cityCode.c_str()), "getWeatherInfo");

}

void WeatherInfo::finishGetWeatherInfo(Ref* data) {
	if (data == NULL) {
		log("get weather info fail");
		return;
	}
	parseWeatherInfoAndSave((const char*)data);
}

string WeatherInfo::parseCityCode(string jsonStr) {
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(jsonStr, root, false)) {
		string cityName = root["city"].asString();
		
		if (cityName == "") {
			return "";
		}
		TiXmlDocument* cityList = new TiXmlDocument(CITYLIST_XML);
		cityList->LoadFile();
		TiXmlNode* citiesElement = cityList->RootElement()->FirstChildElement();
		string a = citiesElement->Value();
		if (citiesElement == NULL) {
			return "";
		}
		
		TiXmlNode* cityElement = NULL;
		for (auto curElement = citiesElement->FirstChildElement(); curElement != NULL;
			curElement = curElement->NextSiblingElement()) {
			if (curElement->Attribute("d2") == cityName) {
				return curElement->Attribute("d1");
			}
		}
	}
	return "";
}

void WeatherInfo::parseWeatherInfoAndSave(string jsonStr) {
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(jsonStr, root, false)) {
		string date_y;
		string weathers[6];
		ValueMap dict;
		dict["date_y"] = root["weatherinfo"]["date_y"].asString();
		for (int i = 0; i < 6; ++i) {
			dict[StringUtils::format("weather%d", i + 1)] = Value(root["weatherinfo"][StringUtils::format("weather%d", i + 1)].asString());
		}
		FileUtils::getInstance()->writeToFile(dict, WEATHER_DATA_FILE);
	}
	else {
		log("parse weather info fail");
	}
}


