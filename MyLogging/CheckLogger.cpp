#include<cassert>
#include "CheckLogger.h"
#include "Logger.h"
namespace logging
{
	CheckLogger::CheckLogger(Priority pri,const string& srcFile,int32_t srcLine,const string& expression):
	ExpressionLogger(pri,srcFile,srcLine,expression){
		
	}
	
	CheckLogger::~CheckLogger()
	{
		Output("\n");
		_loggerStreamPtr->Output(_bufferStream.str());
		_loggerStreamPtr->Submit();
		WaitLoggerThread();
		#ifdef WIN32
		#undef NDEBUG
			assert(0);
		#else
			exit(EXIT_FAILURE);
		#endif
	}
	
	void CheckLogger::OutputPrefix()
	{
		Logger::OutputPrefix();
		Output(string("Expression '")+GetExpression()+"' failed.");
	}
}