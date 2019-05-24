
#ifndef CC_SQLITE3_HH
#define CC_SQLITE3_HH

#include <sqlite3.h>

#include <iostream>
#include <string>

#include "cc_sqlite3_exception.hh"
#include "cc_sqlite3_blob.hh"
#include "cc_sqlite3_type.hh"

using namespace std;

namespace std_cc_sqlite3 {

	class cc_sqlite3 {
	private:
		sqlite3 * db;
		sqlite3_stmt * stmt;
		int code;
		
		void throw_if_err(int code);
		
	public:
		static const string MEMORY;

		cc_sqlite3(const string & filename);
		virtual ~cc_sqlite3();

		string err_msg(int code);
		
		void exec(const string & sql);
		int last_insert_row_id();
		
		void prepare(const string & query);
		void reset();
		
		int bind_parameter_count();
		
		void bind_null(const string & field);
		void bind(const string & field, int value);
		void bind(const string & field, double value);
		void bind(const string & field, const string & value);
		void bind(const string & field, const void * blob, off_t size);
		void bind(const string & field, const cc_sqlite3_blob & sqlite_blob);

		bool step();
		
		int column_count();
		int column_type(int idx);
		cc_sqlite3_type column_type_name(int idx);
		
		int column_int(int idx);
		double column_double(int idx);
		string column_text(int idx);
		cc_sqlite3_blob column_blob(int idx);
		
		void finalize();
        void close();
		
		bool get_autocommit();
		
		string libversion(void);
		string sourceid(void);
		int libversion_number(void);
	};

};

#endif

