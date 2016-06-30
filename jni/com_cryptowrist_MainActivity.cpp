#include "com_cryptowrist_MainActivity.h"
#include "utils.h"
#include "test.h"
#include <sstream>



JNIEXPORT jstring JNICALL Java_com_cryptowrist_MainActivity_load_1str
  (JNIEnv *pEnv, jobject senderObject)
{
	std::string res;

	try{

		std::string tx = btc_api.create_new_transaction(address_1, address_2, 10000);
		std::string digest = btc_api.get_digest(tx);
 		std::string sig = btc_api.get_signature(address_1, digest);
		tx = btc_api.add_signature(address_1, sig, tx);
		//res = tx;
		res = btc_api.push_transaction(tx);
	}

	catch(BlockCypherAPI::Web_Load_Error err)
	{
		return pEnv->NewStringUTF(("Load Error! Code: " + utils::ToString(err.code)).c_str());
	}
	catch(BlockCypherAPI::Json_Struct_Error err)
	{
		return pEnv->NewStringUTF(("JSON Error: " + err.text).c_str());
	}
	catch(BlockCypherAPI::Push_Error err)
	{
		return pEnv->NewStringUTF(("Tx Push Error: " + err.text).c_str());
	}

	return pEnv->NewStringUTF(res.c_str());

	/*std::string result;
	try
	{
		result = btc_api.create_new_address();
	}
	catch(BlockCypherAPI::Web_Load_Error err)
	{
		return pEnv->NewStringUTF(("Load Error! Code: " + utils::ToString(err.code)).c_str());
	}*/
}

JNIEXPORT jstring JNICALL Java_com_cryptowrist_MainActivity_create_1address
  (JNIEnv *pEnv, jobject senderObject)
{
	//return pEnv->NewStringUTF("Hello!");
	BtcSender new_addr;
	try
	{
		new_addr = btc_api.create_new_address();
	}
	catch(BlockCypherAPI::Web_Load_Error err)
	{
		return pEnv->NewStringUTF(("Load Error! Code: " + utils::ToString(err.code)).c_str());
	}

	return pEnv->NewStringUTF(new_addr.address.c_str());
}





