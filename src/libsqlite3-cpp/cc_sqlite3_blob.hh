
#ifndef CC_SQLITE3BLOB_HH
#define CC_SQLITE3BLOB_HH

#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string>

#include "cc_sqlite3_exception.hh"

using namespace std;

namespace std_cc_sqlite3 {

	class cc_sqlite3_blob {
	private:
		void * blob;
		off_t nbytes;
		
	public:
		cc_sqlite3_blob(const void * blob, int nbytes);
		cc_sqlite3_blob(const string & filename);
		virtual ~cc_sqlite3_blob();
		
		const void * get_blob() const;
		off_t get_bytes() const;
		
		ssize_t write_file(const string & filename);
	};
	
};

#endif
