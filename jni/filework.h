#include "btcaddress.h"
#include <vector>
#include <string>

/*class AddressFile
{
	public:
		AddressFile();

		char[270] address;
		char[270] public_key;
		char[270] private_key;

		void FromBtcSender(BtcSender addr);
};*/

class FileWork
{
	public:
		FileWork();

		std::string root_dir;

		//std::vector<std::string>list();
		BtcSender read_address(std::string address);
		void save_address(BtcSender addr);

		class IO_Error{};
};

