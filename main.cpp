#include <iostream>
#include <chrono>

#ifdef _WIN32
#include <format>
namespace afmt = std;
#else
#include <fmt/format.h>
namespace afmt = fmt;
#endif

int modulo(long long& value, int div)
{
	int r = value % div;
	value /= div;
	return r;
}

std::string getTimeStamp()
{
	auto now = std::chrono::system_clock::now();
#ifdef _WIN32
	// operator<< not supported on gcc
	std::cout << now << std::endl;
#endif
	auto duration = now.time_since_epoch();
	auto value = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	auto ms = modulo(value, 1000);
	auto sec = modulo(value, 60);
	auto min = modulo(value, 60);
	auto hour = modulo(value, 24);
	return afmt::format("{}d {}:{}:{}.{}", value, hour, min, sec, ms);
}

int main(int argc, char** argv)
{
	std::cout << "Hello world" << std::endl;
	std::cout << getTimeStamp() << std::endl;
}
