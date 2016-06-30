#include "blockcypherapi.h"
#include "utils.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
/*#include "nayuki-lib/Ecdsa.hpp"
#include "nayuki-lib/Ecdsa.cpp"
#include "nayuki-lib/CurvePoint.hpp"
#include "nayuki-lib/CurvePoint.cpp"
#include "nayuki-lib/FieldInt.hpp"
#include "nayuki-lib/FieldInt.cpp"
#include "nayuki-lib/Sha256.hpp"
#include "nayuki-lib/Sha256.cpp"
#include "nayuki-lib/Sha256Hash.hpp"
#include "nayuki-lib/Sha256Hash.cpp"
#include "nayuki-lib/Uint256.hpp"
#include "nayuki-lib/Uint256.cpp"
#include "nayuki-lib/Utils.hpp"
#include "nayuki-lib/Utils.cpp"*/


BlockCypherAPI::Web_Load_Error::Web_Load_Error(int error_code)
{
	code = error_code;
}

BlockCypherAPI::Json_Struct_Error::Json_Struct_Error(std::string error_text)
{
	text = error_text;
}

BlockCypherAPI::BlockCypherAPI()
{
    _api_url = "https://api.blockcypher.com/v1/bcy/test/";
}

BlockCypherAPI::Push_Error::Push_Error(std::string error_text)
{
	text = error_text;
}

BlockCypherAPI::BlockCypherAPI(std::string token, API_Mode mode)
{
    _token = token;
    
    switch( mode )
    {
        case MAIN: {
            _api_url = "https://api.blockcypher.com/v1/btc/main/";
            break; }
        
        case TESTNET3: {
            _api_url = "https://api.blockcypher.com/v1/btc/test3/";
            break; }
            
        case TEST: {
            _api_url = "https://api.blockcypher.com/v1/bcy/test/";
            break; }
            
        default: 
            throw Mode_Init_Error();
    }
}

void BlockCypherAPI::set_token(std::string token)
{
    _api_url = "https://api.blockcypher.com/v1/bcy/test/";
    _token = token;
}

long BlockCypherAPI::get_balance_satoshi(BtcAddress address)
{
    std::string api_query = _api_url + "addrs/" + address.address + "/balance";
    
    std::string api_response;
    try
       {  api_response = _web.load_url(api_query); }
    catch( WebClient::Load_Error err)
       { throw Web_Load_Error(err.code); }
        
    json_t *root;
    json_error_t err;
    json_t *balance;
    
    root = json_loads(api_response.c_str(), 0, &err);
    balance = json_object_get(root, "balance");
    
    long res = (long)json_integer_value(balance);
    
    json_decref(root);
    
    return res;

}

std::string BlockCypherAPI::create_new_address()
{
	std::string api_query = _api_url + "addrs";

	std::string api_response;

	try
	{
		api_response = _web.post(api_query);
	}
	catch(WebClient::Load_Error err)
	{
		throw Web_Load_Error(err.code);
	}

	return api_response;
}

std::string BlockCypherAPI::create_new_transaction(BtcAddress sender, BtcAddress receiver, long amount)
{
    std::string query_url =  _api_url + "txs/new";
    std::string amount_str = utils::ToString(amount);
    std::string data = "{\"inputs\":[{\"addresses\": [\"" + sender.address + "\"]}],\"outputs\":[{\"addresses\": [\"" + receiver.address + "\"], \"value\": " + amount_str + "}]}";

    std::string response;

    try
    {
    	response = _web.post(query_url, data);
    }
    catch(WebClient::Load_Error err)
    {
    	throw Web_Load_Error(err.code);
    }
    
    return response;
}

std::string BlockCypherAPI::get_digest(std::string transaction)
{
	json_t *rootj;
	json_error_t errj;
	json_t *tosign_arrayj;
	json_t *tosignj;

	rootj = json_loads(transaction.c_str(), 0, &errj);

	if(!rootj)
	{
		throw Json_Struct_Error(errj.text);
	}

	tosign_arrayj = json_object_get(rootj, "tosign");

	if(!json_is_array(tosign_arrayj))
	{
		json_decref(rootj);
		throw Json_Struct_Error("Failed to find tosign in body");
	}

	tosignj = json_array_get(tosign_arrayj, 0);

	if(!json_is_string(tosignj))
	{
		json_decref(rootj);
		throw Json_Struct_Error("Failed to find tosign in array");
	}

	std::string tosign(json_string_value(tosignj));
	json_decref(rootj);

	return tosign;

}

std::string BlockCypherAPI::get_signature(BtcSender sender, std::string data)
{
	std::string result=" ";

	try
	{
		result = _web.post("http://185.62.103.104:8000/sign/",
							"pr="+sender.private_key()+
							"&pub="+sender.public_key()+
							"&data="+data);
	}
	catch(WebClient::Load_Error err)
	{
		throw Web_Load_Error(err.code);
	}

	return result;
}

std::string BlockCypherAPI::add_signature(BtcSender sender, std::string signature, std::string transaction)
{
	if(transaction.length() == 0)
	{
		throw Json_Struct_Error("Empty transaction!");
	}

	transaction[transaction.length()-1] = ',';
	//transaction = ";";
	transaction.append("\"signatures\": [ \"" + signature + "\" ], \"pubkeys\": [ \"" + sender.public_key() + "\" ]}");

	return transaction;
}

std::string BlockCypherAPI::push_transaction(std::string transaction)
{
	std::string result;
	std::string query_url =  _api_url + "txs/send?token=" + _token;

	try
	{
		result = _web.post(query_url, transaction);
	}
	catch(WebClient::Load_Error err)
	{
		throw Web_Load_Error(err.code);
	}

	json_t *rootj;
	json_error_t errj;
	json_t *errorj;

	rootj = json_loads(transaction.c_str(), 0, &errj);

	if(!rootj)
	{
		throw Json_Struct_Error(errj.text);
	}

	errorj = json_object_get(rootj, "error");
	if(json_is_string(errorj))
	{
		std::string error_text(json_string_value(errorj));
		json_decref(rootj);

		throw Push_Error(error_text);
	}

	json_decref(rootj);

	return result;
}






