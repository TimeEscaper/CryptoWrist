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
        std::string create_new_transaction(BtcAddress sender, BtcAddress receiver, long amount);
       // std::string sign_transaction(BtcSender sender, std::string transaction_hash);
        
        class WebClient_Init_Error{};
        class Mode_Init_Error{};
        class WebClient_Load_Error{};
    
            
    private:
        WebClient _web;
        std::string _token; 
        std::string _api_url;
};

#endif /* BLOCKCYPHERAPI_H */ 
