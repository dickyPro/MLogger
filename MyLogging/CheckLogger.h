#ifndef CHECKLOGGER_H
#define CHECKLOGGER_H

#include "ExpressionLogger.h"
#include "Priority.h"
namespace logging
{
	class CheckLogger:public ExpressionLogger
	{
		CheckLogger(Priority pri,const string& srcFile,int32_t srcLine,const string& expression);
		virtual ~CheckLogger();
		virtual void OutputPrefix()override;
	};
}
#endif