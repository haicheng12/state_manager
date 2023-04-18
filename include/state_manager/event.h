#ifndef _EVENT_H_
#define _EVENT_H_

namespace HSMState // HSM状态机
{
	enum EventDeal // 事件处理
	{
		FINISH = 0, // 事件结束处理
		CONTINUE	// 事件继续传递
	};

	// 事件数据
	class EventData
	{
	public:
		EventData(int event_type)
		{
			event_type_ = event_type;
			data_ = nullptr;
		}

		template <class T>
		void setData(T *t)
		{
			data_ = t;
		}

		template <class T>
		T *getData()
		{
			return (T *)data_;
		}

		int event_type_;

	private:
		void *data_;
	};
}

#endif
