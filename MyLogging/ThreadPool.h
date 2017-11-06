#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <vector>
#include<queue>
#include<memory>
#include<thread>
#include<condition_variable>
#include<future>
#include<functional>
#include "BlockQueue.h"
using namespace std;
#define  MIN_THREAD_NUM 256
namespace CommonUtils
{
	template<typename _Ty> class CThreadPool
	{
		//��������õĺ�����ʽ��һ����
		using Task = function<void(_Ty&record)>;
		//��ֹ�̳߳ظ���
		CThreadPool&operator=(const CThreadPool&) = delete;
		CThreadPool(const CThreadPool&) = delete;
	public:
		CThreadPool(int32_t threadsCnt, Task handler):
			: _shutdown(false),threads(threadsCnt),
			_handler(handler), _workers(), _tasks()
		{
			if (_threads < MIN_THREADS)
			{
				_threads = MIN_THREADS;
			}

			for (int32_t i = 0; i < _threads; ++i)
			{
				_workers.emplace_back([this]{
					while (!_shutdown)
					{
						_Ty record;
						_tasks.Pop(record);
						_handler(record);
					}
				});
			}
		}
		//��������
		virtual ~CThreadPool()
		{
			 
			for (const thread & worker : _workers)
			{
				if (worker.joinable())
				{
					worker.join();
				}
			}
		}
		//�ύ����
		void Submit(_Ty record)
		{
			_tasks.Push(record);
		}
	private:
		bool _shudown;
		int32_t _threads;
		Task _handler;
		vector<thread> _workers;
		CBlockingQueue<_Ty> _tasks;
	};
}
#endif