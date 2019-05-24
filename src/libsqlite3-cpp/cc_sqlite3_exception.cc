
#include "cc_sqlite3_exception.hh"

using namespace std_cc_sqlite3;

cc_sqlite3_exception::cc_sqlite3_exception(const char * message) {
	this->exception_message = string(message);
}

cc_sqlite3_exception::cc_sqlite3_exception(const string & message) {
	this->exception_message = string(message);
}

cc_sqlite3_exception::~cc_sqlite3_exception() {}

const char * cc_sqlite3_exception::what() {
	return this->exception_message.c_str();
}
