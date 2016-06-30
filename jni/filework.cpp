#include "filework.h"
#include <fstream>

FileWork::FileWork()
{
	root_dir = "/sdcard/cryptowrist/";
}

//std::vector<std::string>


void FileWork::save_address(BtcSender addr)
{
	std::ofstream output((root_dir+addr.address).c_str());

	if(!output.is_open())
		throw IO_Error();

	output << addr.address << " " << addr.public_key() << " " << addr.private_key();

	output.close();
}

BtcSender FileWork::read_address(std::string address)
{
	std::ifstream input((root_dir+address).c_str());

	BtcSender res;

	std::getline(input, res.address);
	std::getline(input, res._public_key);
	std::getline(input, res._private_key);

	return res;
}
