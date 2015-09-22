/*
 * Logger.h
 *
 *  Created on: Sep 18, 2015
 *      Author: norayu
 */

#ifndef SRC_LOGGING_LOGGER_H_
#define SRC_LOGGING_LOGGER_H_

#include <vector>
#include <string>

class Logger
{
private:
	static std::vector<std::string> queue;
	static void clearLine();
public:
	static void addToQueue(std::string add);
	static void updateLogs();
};

#endif /* SRC_LOGGING_LOGGER_H_ */
