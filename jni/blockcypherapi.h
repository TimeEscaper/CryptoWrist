#ifndef BLOCKCYPHERAPI_H
#define BLOCKCYPHERAPI_H

#include <string>
#include "jansson/jansson.h"
#include "webclient.h"
#include "btcaddress.h"

class BlockCypherAPI
{
    public:
        BlockCypherAPI();

        enum API_Mode{ MAIN, TESTNET3, TEST };
        BlockCypherAPI(std::string token, API_Mode mode);
        
        void set_token(std::string token);

        long get_balance_satoshi(BtcAddress address);
        std::string create_new_address();

        std::string create_new_transaction(BtcAddress sender, BtcAddress receiver, long amount);
        std::string get_digest(std::string transaction);
        std::string get_signature(BtcSender sender, std::string data);
        std::string add_signature(BtcSender sender, std::string signature, std::string transaction);
        std::string push_transaction(std::string transaction);
        
        class Mode_Init_Error{};
        class Web_Init_Error{};
        class Web_Load_Error{
        	public:
        		Web_Load_Error(int error_code);
        		int code;
        };
        class Json_Struct_Error{
        	public:
        		Json_Struct_Error(std::string error_text);
        		std::string text;
        };
        class Push_Error{
        	public:
        		Push_Error(std::string error_text);
        		std::string text;
        };
    
            
    private:
        WebClient _web;
        std::string _token; 
        std::string _api_url;
};

#endif /* BLOCKCYPHERAPI_H */ 
