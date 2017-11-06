#ifndef PRIORITY_H
#define PRIORITY_H
namespace logging
{
	//√∂æŸ¿‡
	enum class Priority {
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};
}
const logging::Priority LOG_DEBUG = logging::Priority::Debug;
const logging::Priority LOG_INFO = logging::Priority::Info;
const logging::Priority LOG_WARNING = logging::Priority::Warning;
const logging::Priority LOG_ERROR = logging::Priority::Error;
const logging::Priority LOG_FATAL = logging::Priority::Fatal;

#endif