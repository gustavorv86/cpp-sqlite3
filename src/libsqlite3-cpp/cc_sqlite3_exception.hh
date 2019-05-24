
#ifndef CC_SQLITE3EXCEPTION_H
#define CC_SQLITE3EXCEPTION_H

#include <string>

using namespace std;

namespace std_cc_sqlite3 {

	class cc_sqlite3_exception : public exception {
	private:
		string exception_message;
		
	public:
		cc_sqlite3_exception(const char * message);
		cc_sqlite3_exception(const string& orig);
		virtual ~cc_sqlite3_exception();
		virtual const char * what();

	};

};

#endif
