#include "logging.h"
 
using namespace std;
using namespace logging;
int main()
{
	 

	Logging::SetLogFile(Priority::Info, "main.log");
	  
    LOG(LOG_INFO) << "�����ɹ�";
		  
	  
	return 0;
}