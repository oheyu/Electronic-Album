#ifndef __ASYNC_LOG__
#define __ASYNC_LOG__

#include <QThread>
#include <condition_variable>
#include <mutex>
#include <QDebug>
#include <QQueue>
#include <iostream>
#include <QVariant>
namespace AsyncLog {
    enum LogLv {
		DEBUGS = 0,
		INFO = 1,
		WARN = 2,
		ERRORS = 3,
	};


    class  LogTask {
	public:
        LogTask(){}
        LogTask(const LogTask& src):_level(src._level), _logdatas(src._logdatas){}
        LogTask(const LogTask&& src):_level(src._level),
            _logdatas(std::move(src._logdatas)){}
        LogLv _level;
        QQueue<QVariant> _logdatas;
	};


    class  AsyncLog : public QThread {

	public:


        static AsyncLog& Instance(){
            static AsyncLog instance;
            return instance;
        }

        //如果不支持C++17,可采用如下函数入队
        template<typename Arg, typename ...Args>
        void TaskEnque(std::shared_ptr<LogTask> task, Arg&& arg, Args&&... args){
            task->_logdatas.enqueue(QVariant(std::forward<Arg>(arg)));
            qDebug() << "enque task data is " << arg << endl;
            TaskEnque(task,std::forward<Args>(args)...);
        }

        template<typename Arg>
        void TaskEnque(std::shared_ptr<LogTask> task, Arg&& arg){
            task->_logdatas.enqueue(QVariant(std::forward<Arg>(arg)));
            qDebug() << "enque task data is " << arg << endl;
        }

        //可变参数列表，异步写
        template<typename...  Args>
        void AsyncWrite(LogLv level, Args&&... args) {
            auto task = std::make_shared<LogTask>();
            //折叠表达式依次将可变参数写入队列,需C++17版本支持
            (task->_logdatas.enqueue(QVariant(std::forward<Args>(args))), ...);
            //如不支持C++17 请用这个版本入队
            //TaskEnque(task, args...);
            task->_level = level;
            std::unique_lock<std::mutex> lock(_mtx);
            _queue.enqueue(task);
            bool notify = (_queue.size() == 1)?true:false;
            lock.unlock();
            // 通知等待的线程有新的任务可处理
            if(notify){
                 _empty_cond.notify_one();
            }

		}

        void Stop(){
            _b_stop = true;
            _empty_cond.notify_one();
        }



	private:

        AsyncLog(const AsyncLog&) = delete;
        AsyncLog& operator = (const AsyncLog&) = delete;

        AsyncLog(QObject* parent = nullptr):QThread(parent),_b_stop(false){

        }

        void run(){
            for(;;){
                std::unique_lock<std::mutex> lock(_mtx);

                while(_queue.empty() && !_b_stop){
                    _empty_cond.wait(lock);
                }

                if(_b_stop){
                    return;
                }

                auto logtask = _queue.dequeue();
                lock.unlock();
                processTask(logtask);
            }
        }

        void processTask(std::shared_ptr<LogTask> task){
            qDebug() << "log level is " << task->_level << endl;

            if(task->_logdatas.empty()){
                return;
            }
            // 队列首元素
            auto head = task->_logdatas.dequeue();
            auto formatstr = head.toString().toStdString();

            for(;!(task->_logdatas.empty());){
                auto data = task->_logdatas.dequeue();
                qDebug() << "deque task data is " << data;
                formatstr=formatString(formatstr, data);

            }

            qDebug() << "formatstr is " << QString::fromStdString(formatstr) << endl;
        }


        template<typename... Args>
        std::string formatString(const std::string& format, Args&&... args) {
               std::string result = format;
               size_t pos = 0;
                //lambda表达式查找并替换字符串
               auto replacePlaceholder = [&](const std::string& placeholder, const std::string& replacement) {
                       size_t placeholderPos = result.find(placeholder, pos);
                       if (placeholderPos != std::string::npos) {
                           result.replace(placeholderPos, placeholder.length(), replacement);
                           pos = placeholderPos + replacement.length();
                       }else{
                            result = result + " " + replacement;
                       }
                   };

              (replacePlaceholder("{}", QVariant(std::forward<Args>(args)).toString().toStdString()), ...);

               qDebug() << "result is : " << QString::fromStdString(result) << endl;
               return result;
           }

        std::condition_variable _empty_cond;
        QQueue<std::shared_ptr<LogTask> >  _queue;
        bool _b_stop;
        std::mutex _mtx;
	};


}

#endif
