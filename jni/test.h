#include "webclient.h"
#include "blockcypherapi.h"
#include "btcaddress.h"

BlockCypherAPI btc_api("da44ddd295714dcdaa27683072a4e8c3", BlockCypherAPI::API_Mode::TEST);

BtcSender address_1("BtcjpqURLTiezkoXPCT9V6SGenNZ3YtPv4",
		"024a16269157b543355bd3f9dc0cc8bae3667b20135a5d74343fa3dd106bd33bfc",
		"0c5249345c9406074f00b70d49d55a89de14c8d1bbdbe36f1e1fcf8830549181"
					);

BtcAddress address_2("BvAtdF3a16Rt3gKK619ZH2fY8jkUZFfGS2");
