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

int sumDays[48] =
{
	31,		59,		90,		120,	151,	181,	212,	243,	273,	304,	334,	365, // 1970
	396,	424,	455,	485,	516,	546,	577,	608,	638,	669,	699,	730, // 1971
            //29F
	761,	790,	821,	851,	882,	912,	943,	974,	1004,	1035,	1065,	1096, // 1972, leap year
	1127,	1155,	1186,	1216,	1247,	1277,	1308,	1339,	1369,	1400,	1430,	1461  // 1973
};

// Input: Nb of days since 1-Jan-1970
std::string getDate(int days)
{
	// 4 years = 4*365+1 = 1461
	int group4y = days / 1461;
	days = 1 + days - 1461 * group4y;  // 1<= days <= 1461
	int month = 0;
	while (days > sumDays[month])
		month++;
	if (month > 0)
		days = days - sumDays[month - 1];
	int extra_years = month / 12; // [0,..,3]
	month = month - 12 * extra_years;
	return afmt::format("{:04}/{:02}/{:02}", 1970 + 4 * group4y + extra_years, month + 1, days);
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

	auto str = getDate((int)value);


	return afmt::format("{} : {}d {:02}:{:02}:{:02}.{:03}", str, value, hour, min, sec, ms);
}

double some_work(int k)
{
	double s = 0.0;
	for (int i = 0; i < 100000; i++)
		s += 1.0 / (k + cos(i) * cos(i));
	return s;
}

void test()
{
	for (int d = 17000; d <= 19000; d++)
	{
		std::cout << d << "," << getDate(d) << std::endl;
	}
}

void test2()
{
	int d = 17531;
	std::cout << d << "," << getDate(d) << std::endl;
}



int main(int argc, char** argv)
{
	test(); return 0;

	std::cout << "Hello world" << std::endl;
	std::cout << getTimeStamp() << std::endl;

	//
	for (int i = 1; i < 10; i++)
	{
		std::cout << some_work(i) << std::endl;
		std::cout << getTimeStamp() << std::endl;

	}
}
