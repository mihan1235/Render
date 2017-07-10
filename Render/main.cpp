#include <cstdio>
#include <core.hpp>
#include <exception>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;


int main(int argc, char** argv){
	try{
		kr::Core& render=kr::Core::Instance();
		render.launch();
	}
	catch(std::exception& err){
		cout<<err.what()<<"\n";
		return 1;
	}
	return 0;
}
