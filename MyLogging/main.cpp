#include "logging.h"
 
using namespace std;
using namespace logging;
int main()
{
	 

	Logging::SetLogFile(Priority::Info, "main.log");
	  
    LOG(LOG_INFO) << "创建成功";
		  
	  
	return 0;
}