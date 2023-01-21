#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
	std::cout << "Hello world" << std::endl;
	
	auto now = std::chrono::system_clock::now();

#ifdef _WIN32
	// operator<< not supported on gcc
	std::cout << now << std::endl;
#endif

	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	std::cout << "millis: " << millis << std::endl;
}
