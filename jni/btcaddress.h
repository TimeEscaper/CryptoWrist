#pragma once

#ifndef BTCADDRESS_H
#define BTCADDRESS_H

#include <string>

class BtcAddress
{
    public:
        BtcAddress();
        BtcAddress(const BtcAddress& other);
        BtcAddress(std::string address);
        BtcAddress& operator=(const BtcAddress& other);
        std::string address;      
                
};



class BtcSender: public BtcAddress
{
    public:
        BtcSender(std::string address, std::string public_key, std::string private_key);
        std::string public_key();
        std::string private_key();
        
    private:
        std::string _public_key;
        std::string _private_key;
        
};

#endif /* BTCADDRESS_H */ 
