#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include <ctime>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>

namespace extractor {
	std::string getCurrDate();
	std::string getCurrTime();
}

#endif