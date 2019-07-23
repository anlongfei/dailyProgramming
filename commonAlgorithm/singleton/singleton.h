
/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : anlongfei
#   Email         : 在 vimrc 文件中添加 let g:file_copyright_email = 'your email'
#   File Name     : singleton.h
#   Last Modified : 2019-07-23 17:18
#   Describe      :
#
# ====================================================*/

#ifndef  _SINGLETON_H
#define  _SINGLETON_H

template<typename T>
class singleton {
    public:
        static T* getInstance() {
            static T obj;
            return &obj;
        }
    private:
        singleton(){}
};


/*
template<class T>
class singleton {
	public:
		class creater { // TODO 用途？？？
			public:
				creater() {
					singleton<T>::getInstance();
				}
				inline void do_nothing() const{}
		};
		static T* getInstance() {
			static T obj;
			m_creater.do_nothing();
			return &obj;
		}

	public:
		static creater m_creater;
	private:
		singleton(){}
};
*/

#endif // _SINGLETON_H


