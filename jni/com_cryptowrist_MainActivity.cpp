#include "com_cryptowrist_MainActivity.h"
#include "utils.h"
#include <sstream>

JNIEXPORT jstring JNICALL Java_com_cryptowrist_MainActivity_load_1str
  (JNIEnv *pEnv, jobject senderObject)
{
	WebClient web_client;
	std::string res;

	try{
		res = web_client.load_url("https://mail.ru");
	}

	catch(WebClient::Load_Error err)
	{
		return pEnv->NewStringUTF(("Load Error! Code: " + utils::ToString(err.code)).c_str());
	//	return pEnv->NewStringUTF("Load Error!");
	}

	return pEnv->NewStringUTF(res.c_str());
}
