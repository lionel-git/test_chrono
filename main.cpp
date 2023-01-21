#include <iostream>
#include <chrono>

#ifdef _WIN32
#include <format>
namespace afmt = std;
#else
#include <fmt/format.h>
namespace afmt = fmt;
#endif

int getTzOffset()
{
	const std::time_t epoch_plus_11h = 60 * 60 * 11;
	struct tm lt;
	struct tm gmt;
#ifdef _WIN32
	localtime_s(&lt, &epoch_plus_11h);
	gmtime_s(&gmt, &epoch_plus_11h);
#else
	localtime_r(&epoch_plus_11h, &lt);
	gmtime_r(&epoch_plus_11h, &gmt);
#endif
	return lt.tm_hour - gmt.tm_hour;
}

template<typename T>
int modulo(T& value, int div)
{
	int r = value % div;
	value /= div;
	return r;
}

std::string getTimeStamp()
{
	static int tzOffset = getTzOffset();

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
	value += tzOffset;
	auto hour = modulo(value, 24);
	return afmt::format("{}d {:02}:{:02}:{:02}.{:03}", value, hour, min, sec, ms);
}

int main(int argc, char** argv)
{
	std::cout << "Hello world" << std::endl;
	std::cout << getTimeStamp() << std::endl;
}
