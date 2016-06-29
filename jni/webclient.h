#ifndef WEBCLIENT_H
#define WEBCLIENT_H

//#include "curl/curl.h"
//#include "curl/easy.h"
#include <curl/curl.h>
#include <cstring>
#include <string>
#include <memory>


size_t _write_function_callback(char* ptr, size_t size, size_t nmemb, std::string* userdata);
size_t _read_function_callback(char* ptr, size_t size, size_t nmemb, std::string* userdata);

class WebClient
{
    public:
        WebClient();
        std::string load_url(const std::string &url);
        std::string post(const std::string &url, const std::string &data_fields);

        class Load_Error{
        	public:
        		int code;
        		Load_Error(int error_code);
        };
        class Init_Error{};
        class Post_Error{};

    private:
        std::shared_ptr<CURL> _curl;
        std::string _buffer;
        std::string _url_buff;
        std::string _post_buff;

};

#endif /* WEBCLIENT_H */
