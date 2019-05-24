
#ifndef CC_SQLITE3_TYPE_HH
#define CC_SQLITE3_TYPE_HH

#include <sqlite3.h>

#include <string>

#include "cc_sqlite3_exception.hh"

using namespace std;

namespace std_cc_sqlite3 {
	
	class cc_sqlite3_type {
	private:
		static const int MINOR_TYPE;
		static const int MAJOR_TYPE;
		static const string TYPES[];
		
		int type;
		
	public:		
		cc_sqlite3_type(int type);
		virtual ~cc_sqlite3_type();
		
		const string & to_string();
		bool equals(int type);
		bool equals(const string & type);
	};

};

#endif
