#include "webclient.h"
//#include "curl/curl.h"
//#include "curl/easy.h"
#include <curl/curl.h>
#include <string>
#include <sstream>

size_t _write_function_callback(char* ptr, size_t size, size_t nmemb, std::string* userdata)
{
	userdata->clear();
	if(!userdata)
		return 0;
	else
	{
		size_t write_size = size*nmemb;
		userdata->append(ptr, write_size);

		return write_size;
	}
}

WebClient::Load_Error::Load_Error(int error_code)
{
	code = error_code;
}

WebClient::WebClient()
{
    std::shared_ptr<CURL> _curl_temp(curl_easy_init(), curl_easy_cleanup);
    _curl = _curl_temp;

    if( _curl.get() == nullptr )
        throw Init_Error();

    curl_easy_setopt(_curl.get(), CURLOPT_WRITEFUNCTION, _write_function_callback);
    curl_easy_setopt(_curl.get(), CURLOPT_WRITEDATA, &_buffer);
    curl_easy_setopt(_curl.get(), CURLOPT_SSL_VERIFYPEER, false);

}

std::string WebClient::load_url(const std::string &url)
{
    _url_buff = url;

    curl_easy_setopt(_curl.get(), CURLOPT_URL, _url_buff.c_str());

    CURLcode result = curl_easy_perform(_curl.get());

    if( result != CURLE_OK )
    {
    	throw Load_Error(result);
    }

    return _buffer;

}

std::string WebClient::post(const std::string &url, const std::string &data_fields)
{
    _url_buff = url;
    _post_buff = data_fields;

    curl_easy_setopt(_curl.get(), CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(_curl.get(), CURLOPT_URL, _url_buff.c_str());
    curl_easy_setopt(_curl.get(), CURLOPT_POSTFIELDS, _post_buff.c_str());

    CURLcode result = curl_easy_perform(_curl.get());

    if( result != CURLE_OK )
        throw Load_Error(result);

    return _buffer;
}

std::string WebClient::post(const std::string &url)
{
    _url_buff = url;

    curl_easy_setopt(_curl.get(), CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(_curl.get(), CURLOPT_URL, _url_buff.c_str());

    CURLcode result = curl_easy_perform(_curl.get());

    if( result != CURLE_OK )
        throw Load_Error(result);

    return _buffer;
}







