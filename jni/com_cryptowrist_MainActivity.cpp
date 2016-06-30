#include "com_cryptowrist_MainActivity.h"
#include "utils.h"
#include <sstream>



JNIEXPORT jstring JNICALL Java_com_cryptowrist_MainActivity_load_1str
  (JNIEnv *pEnv, jobject senderObject)
{
	WebClient web_client;
	std::string res;

	//std::string to_sign = "9cc2c536d9c90b105e9c77a360cc85443f4169a5284be42c164d5a1da64c9d08";

	try{

		std::string tx = btc_api.create_new_transaction(address_1, address_2, 10000);
		std::string digest = btc_api.get_digest(tx);
 		std::string sig = btc_api.get_signature(address_1, digest);
		tx = btc_api.add_signature(address_1, sig, tx);
		res = tx;
		//res = btc_api.push_transaction(tx);
	}

	catch(BlockCypherAPI::Web_Load_Error err)
	{
		return pEnv->NewStringUTF(("Load Error! Code: " + utils::ToString(err.code)).c_str());
	}
	catch(BlockCypherAPI::Json_Struct_Error err)
	{
		return pEnv->NewStringUTF(("JSON Error: " + err.text).c_str());
	}

	return pEnv->NewStringUTF(res.c_str());
}
