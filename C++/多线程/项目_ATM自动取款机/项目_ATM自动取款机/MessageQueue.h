#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

namespace messaging
{
	struct message_base  // 队列项的基础类
	{
		virtual ~message_base()
		{
		}
	};

	template<typename Msg>
	struct wrapped_message :  // 每个消息类型都需要特化
		message_base
	{
		Msg contents;

		explicit wrapped_message(Msg const& contents_) :
			contents(contents_)
		{
		}
	};

	class queue  // 我们的队列
	{
		std::mutex m;
		std::condition_variable c;
		std::queue<std::shared_ptr<message_base> > q;  // 实际存储指向message_base类指针的队列
	public:
		template<typename T>
		void push(T const& msg)
		{
			std::lock_guard<std::mutex> lk(m);
			q.push(std::make_shared<wrapped_message<T> >(msg));  // 包装已传递的信息，存储指针
			c.notify_all();
		}

		std::shared_ptr<message_base> wait_and_pop()
		{
			std::unique_lock<std::mutex> lk(m);
			c.wait(lk, [&] {return !q.empty(); });  // 当队列为空时阻塞
			auto res = q.front();
			q.pop();
			return res;
		}
	};
}

//sender
namespace messaging
{
	class sender
	{
		queue*q;  // sender是一个队列指针的包装类
	public:
		sender() :  // sender无队列(默认构造函数)
			q(nullptr)
		{
		}

		explicit sender(queue*q_) :  // 从指向队列的指针进行构造
			q(q_)
		{
		}

		template<typename Message>
		void send(Message const& msg)
		{
			if(q)
			{
				q->push(msg);  // 将发送信息推送给队列
			}
		}
	};
}

//receiver
namespace messaging
{
	class receiver
	{
		queue q;  // 接受者拥有对应队列
	public:
		operator sender()  // 允许将类中队列隐式转化为一个sender队列
		{
			return sender(&q);
		}
		dispatcher wait()  // 等待对队列进行调度
		{
			return dispatcher(&q);
		}
	};
}


//diapatcher
namespace messaging
{
	class close_queue  // 用于关闭队列的消息
	{
	};

	class dispatcher
	{
		queue* q;
		bool chained;

		dispatcher(dispatcher const&) = delete;  // dispatcher实例不能被拷贝
		dispatcher& operator=(dispatcher const&) = delete;

		template<
			typename Dispatcher,
			typename Msg,
			typename Func>  // 允许TemplateDispatcher实例访问内部成员
			friend class TemplateDispatcher;

		void wait_and_dispatch()
		{
			for(;;)  // 1 循环，等待调度消息
			{
				auto msg = q->wait_and_pop();
				dispatch(msg);
			}
		}

		bool dispatch(  // 2 dispatch()会检查close_queue消息，然后抛出
					  std::shared_ptr<message_base> const& msg)
		{
			if(dynamic_cast<wrapped_message<close_queue>*>(msg.get()))
			{
				throw close_queue();
			}
			return false;
		}
	public:
		dispatcher(dispatcher&& other) :  // dispatcher实例可以移动
			q(other.q), chained(other.chained)
		{
			other.chained = true;  // 源不能等待消息
		}

		explicit dispatcher(queue* q_) :
			q(q_), chained(false)
		{
		}

		template<typename Message, typename Func>
		TemplateDispatcher<dispatcher, Message, Func>
			handle(Func&& f)  // 3 使用TemplateDispatcher处理指定类型的消息
		{
			return TemplateDispatcher<dispatcher, Message, Func>(
				q, this, std::forward<Func>(f));
		}

		~dispatcher() noexcept(false)  // 4 析构函数可能会抛出异常
		{
			if(!chained)
			{
				wait_and_dispatch();
			}
		}
	};
}

namespace messaging
{
	template<typename PreviousDispatcher, typename Msg, typename Func>
	class TemplateDispatcher
	{
		queue* q;
		PreviousDispatcher* prev;
		Func f;
		bool chained;

		TemplateDispatcher(TemplateDispatcher const&) = delete;
		TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

		template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
		friend class TemplateDispatcher;  // 所有特化的TemplateDispatcher类型实例都是友元类

		void wait_and_dispatch()
		{
			for(;;)
			{
				auto msg = q->wait_and_pop();
				if(dispatch(msg))  // 1 如果消息处理过后，会跳出循环
					break;
			}
		}

		bool dispatch(std::shared_ptr<message_base> const& msg)
		{
			if(wrapped_message<Msg>* wrapper =
			   dynamic_cast<wrapped_message<Msg>*>(msg.get()))  // 2 检查消息类型，并且调用函数
			{
				f(wrapper->contents);
				return true;
			}
			else
			{
				return prev->dispatch(msg);  // 3 链接到之前的调度器上
			}
		}
	public:
		TemplateDispatcher(TemplateDispatcher&& other) :
			q(other.q), prev(other.prev), f(std::move(other.f)),
			chained(other.chained)
		{
			other.chained = true;
		}
		TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_) :
			q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false)
		{
			prev_->chained = true;
		}

		template<typename OtherMsg, typename OtherFunc>
		TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
			handle(OtherFunc&& of)  // 4 可以链接其他处理器
		{
			return TemplateDispatcher<
				TemplateDispatcher, OtherMsg, OtherFunc>(
					q, this, std::forward<OtherFunc>(of));
		}

		~TemplateDispatcher() noexcept(false)  // 5 这个析构函数也是noexcept(false)的
		{
			if(!chained)
			{
				wait_and_dispatch();
			}
		}
	};
}