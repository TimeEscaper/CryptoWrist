#include "com_cryptowrist_AddressActivity.h"
#include "utils.h"
#include "filework.h"

JNIEXPORT jstring JNICALL Java_com_cryptowrist_AddressActivity_get_1balance
  (JNIEnv *pEnv, jobject senderObject, jstring j_addr)
{
	BlockCypherAPI btc_api("da44ddd295714dcdaa27683072a4e8c3", BlockCypherAPI::API_Mode::TEST);

	const char *n_addr = pEnv->GetStringUTFChars(j_addr, JNI_FALSE);

	BtcAddress addr = BtcAddress(std::string(n_addr));

	long amount = btc_api.get_balance_satoshi(addr);

	std::string result = utils::ToString(amount);

	pEnv->ReleaseStringUTFChars(j_addr, n_addr);



	return pEnv->NewStringUTF(result.c_str());
}


JNIEXPORT jstring JNICALL Java_com_cryptowrist_AddressActivity_transaction(JNIEnv *pEnv, jobject objectSender, jstring j_sender, jstring j_receiver, jint j_amount)
{
	BlockCypherAPI btc_api("da44ddd295714dcdaa27683072a4e8c3", BlockCypherAPI::API_Mode::TEST);

	const char *r_addr = pEnv->GetStringUTFChars(j_receiver, JNI_FALSE);
	BtcAddress receiver = BtcAddress(std::string(r_addr));

	const char *s_addr = pEnv->GetStringUTFChars(j_sender, JNI_FALSE);
	std::string path(s_addr);

	int amount = (int)j_amount;

	FileWork expl;
	BtcSender sender = expl.read_address(path);

	std::string res;



	try
	{
		std::string tx = btc_api.create_new_transaction(sender, receiver, 10000);
		std::string digest = btc_api.get_digest(tx);
 		std::string sig = btc_api.get_signature(sender, digest);
		tx = btc_api.add_signature(sender, sig, tx);

		res = btc_api.push_transaction(tx);
	}
	catch(BlockCypherAPI::Web_Load_Error err)
	{
		pEnv->ReleaseStringUTFChars(j_sender, s_addr);
		pEnv->ReleaseStringUTFChars(j_receiver, r_addr);
		return pEnv->NewStringUTF(("Load Error! Code: " + utils::ToString(err.code)).c_str());
	}
	catch(BlockCypherAPI::Push_Error err)
	{
		pEnv->ReleaseStringUTFChars(j_sender, s_addr);
		pEnv->ReleaseStringUTFChars(j_receiver, r_addr);
		return pEnv->NewStringUTF(("Tx Push Error: " + err.text).c_str());
	}

	pEnv->ReleaseStringUTFChars(j_sender, s_addr);
	pEnv->ReleaseStringUTFChars(j_receiver, r_addr);


	pEnv->ReleaseStringUTFChars(j_sender, s_addr);
	pEnv->ReleaseStringUTFChars(j_receiver, r_addr);

	return pEnv->NewStringUTF(res.c_str());

	//return pEnv->NewStringUTF("Hello!");

}
