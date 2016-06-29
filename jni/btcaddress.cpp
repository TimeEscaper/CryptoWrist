#include "btcaddress.h"

BtcAddress::BtcAddress() { };

BtcAddress::BtcAddress(const BtcAddress& other)
{
    this->address = other.address;
}

BtcAddress::BtcAddress(std::string btc_address)
{
    this->address = btc_address;
}

BtcAddress& BtcAddress::operator=(const BtcAddress& other)
{
    this->address = other.address;
    
    return *this;
}

BtcSender::BtcSender(std::string btc_address, std::string public_key, std::string private_key)
{
    this->address = btc_address;
    this->_public_key = public_key;
    this->_private_key = private_key;
}

std::string BtcSender::public_key()
{
    return this->_public_key;
}

std::string BtcSender::private_key()
{
    return this->_private_key;
}
