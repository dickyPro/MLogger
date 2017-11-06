#include "DirectLoggerStream.h"
#include "IOStreamManager.h"
using namespace logging;
namespace logging
{
	DirectLoggerStream::DirectLoggerStream(Priority pri):
		LoggerStream(pri)
	{
		_outputStreams=logging::IOStreamManager::GetInstance().GetDefaultOutputStreams(pri);
	}


	DirectLoggerStream::~DirectLoggerStream()
	{
	}

	void DirectLoggerStream::Output(const string&message)
	{
		for(const auto & outputStream : _outputStreams)
		{
			*outputStream << message;
		}
	}
	
	void DirectLoggerStream::Submit()
	{
		
	}
}


