#ifndef LOGGING_H
#define LOGGING_H
#include "Interface.h"
#include "Logger.h"
#include "ExpressionLogger.h"
#include "Check.h"
#include "CheckLogger.h"
#include "IOStreamManager.h"
using namespace logging;

namespace logging
{
	class Logging
	{
	public:
		static void SetLogFile(const std::string& fileName)
		{
			IOStreamManager::GetInstance().SetOutputFile(fileName);
		}
		static void SetLogFile(Priority pri, const std::string& fileName)
		{
			IOStreamManager::GetInstance().SetOutputFile(pri,fileName);
		}
		static void SetLogFile(const std::vector<Priority> pris, const std::string& fileName)
		{
			IOStreamManager::GetInstance().SetOutputFile(pris, fileName);

		}
	};
}

#endif