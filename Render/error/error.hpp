#include <exception>
#include <string>
#pragma once
class Error :public std::exception{
public:
	Error()throw(){};
	Error(const Error& err) throw(){
		this->buf=err.buf;
	}
protected:
	std::string buf;
};
