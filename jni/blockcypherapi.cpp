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
   /* json_t *root;
    json_error_t err;
    json_t *tosign_array;
    json_t *tosign;
    
    root = json_loads(response.c_str(), 0, &err);
    tosign_array = json_object_get(root, "tosign");
    
    tosign = json_array_get(tosign_array, 0);
    
    std::string tosign_string(json_string_value(tosign));
    
    json_decref(root);    
    
    return tosign_string;*/
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
	/*try
	{
		result = _web.post("http://185.62.103.104:8000/sign/",
							"v="+tosign+"&p="+sender.private_key());
	}
	catch(WebClient::Load_Error err)
	{
		throw Web_Load_Error(err.code);
	}*/
}

/*std::string BlockCypherAPI::sign_transaction(BtcSender sender, std::string transaction_hash)
{
    elliptic_curve_key c;
    c.set_private_key(sender.private_key().begin(), sender.private_key().end());
    payment_address address; 
    set_public_key(address, c.public_key());
    std::cout<<address.encoded()<<std::endl;*/
    
    /*Uint256 key(sender.private_key().c_str());
    Sha256Hash res(transaction_hash.c_str());*/
    /*Uint256 key("FF4FFB81BBED24D48975AE17A50B8B16FA63DFBBD4A457EA39BA60B1BBD19FC9");
    Sha256Hash res("FE2AC4337F4144A9BC3845CBB8F507B14EEA5E3C0215F54CCA22EE1D3F8A20D0");
    Uint256 r, s;
    bool is_signed = Ecdsa::signWithHmacNonce(key, res, r, s);
    
    std::cout<<"Is Signed: "<<is_signed<<std::endl;
    uint8_t bigen_r [32];
    r.getBigEndianBytes(bigen_r);
    uint8_t bigen_s [32];
    s.getBigEndianBytes(bigen_s);
    std::stringstream res_stream;
    
    for(int i = 0; i < 32; i++)
        res_stream<<std::hex<<unsigned(bigen_r[i]);
    
    res_stream << "\n";    
        
    for(int i = 0; i < 32; i++)
        res_stream<<std::hex<<unsigned(bigen_s[i]);
    
   // std::cout<<"\n"<<std::endl;
    //std::cout<<r<<std::endl;
  //  std::cout<<s<<std::endl;
    std::string result(res_stream.str());
    
    return result;
    
}*/
