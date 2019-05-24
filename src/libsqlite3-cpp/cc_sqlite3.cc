
#include "cc_sqlite3.hh"

using namespace std_cc_sqlite3;

const string cc_sqlite3::MEMORY = ":memory:";

cc_sqlite3::cc_sqlite3(const string & filename) {
	this->db = nullptr;
	this->stmt = nullptr;
	this->code = sqlite3_open(filename.c_str(), &this->db);
	this->throw_if_err();
}

cc_sqlite3::~cc_sqlite3() {
	sqlite3_finalize(this->stmt);
	sqlite3_close(this->db);
}

string cc_sqlite3::err_msg(int code) {
	return string("ERROR(" + to_string(code) + "): " + sqlite3_errmsg(this->db));
}

void cc_sqlite3::throw_if_err() {
	if(this->code != SQLITE_OK) {
		throw cc_sqlite3_exception(this->err_msg(this->code));
	}
}

void cc_sqlite3::exec(const string & sql) {
	// prepare, step and finalize
	this->code = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, nullptr);
	this->throw_if_err();
}

int cc_sqlite3::last_insert_row_id() {
	return sqlite3_last_insert_rowid(this->db);
}

void cc_sqlite3::prepare(const string & sql) {
	this->code = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &this->stmt, nullptr);
	this->throw_if_err();
}

void cc_sqlite3::reset() {
	this->code = sqlite3_reset(this->stmt);
	this->throw_if_err();
}

int cc_sqlite3::bind_parameter_count() {
	return sqlite3_bind_parameter_count(this->stmt);
}

void cc_sqlite3::bind_null(const string & field) {
	int idx = sqlite3_bind_parameter_index(this->stmt, field.c_str());
	if(idx > 0) {
		this->code = sqlite3_bind_null(this->stmt, idx);
		this->throw_if_err();
	} else {
		throw cc_sqlite3_exception("Cannot bind field " + field);
	}
}

void cc_sqlite3::bind(const string & field, int value) {
	int idx = sqlite3_bind_parameter_index(this->stmt, field.c_str());
	if(idx > 0) {
		this->code = sqlite3_bind_int(this->stmt, idx, value);
		this->throw_if_err();
	} else {
		throw cc_sqlite3_exception("Cannot bind field " + field);
	}
}

void cc_sqlite3::bind(const string & field, double value) {
	int idx = sqlite3_bind_parameter_index(this->stmt, field.c_str());
	if(idx > 0) {
		this->code = sqlite3_bind_double(this->stmt, idx, value);
		this->throw_if_err();
	} else {
		throw cc_sqlite3_exception("Cannot bind field " + field);
	}
}

void cc_sqlite3::bind(const string & field, const string & value) {
	int idx = sqlite3_bind_parameter_index(this->stmt, field.c_str());
	if(idx > 0) {
		this->code = sqlite3_bind_text(this->stmt, idx, value.c_str(), value.length(), nullptr);
		this->throw_if_err();
	} else {
		throw cc_sqlite3_exception("Cannot bind field " + field);
	}
}

void cc_sqlite3::bind(const string & field, const void * blob, off_t size) {
	int idx = sqlite3_bind_parameter_index(this->stmt, field.c_str());
	if(idx > 0) {
		this->code = sqlite3_bind_blob(this->stmt, idx, blob, size, SQLITE_STATIC);
		this->throw_if_err();
	} else {
		throw cc_sqlite3_exception("Cannot bind field " + field);
	}
}

void cc_sqlite3::bind(const string & field, const cc_sqlite3_blob & sqlite_blob) {
	this->bind(field, sqlite_blob.get_blob(), sqlite_blob.get_bytes());
}

bool cc_sqlite3::step() {
	this->code = sqlite3_step(this->stmt);
	if(this->code == SQLITE_ROW) {
		return true;
	} else if(this->code == SQLITE_DONE) {
		return false;
	} else {
		throw cc_sqlite3_exception(this->err_msg(code));
	}
}

int cc_sqlite3::column_count() {
	return sqlite3_column_count(this->stmt);
}

int cc_sqlite3::column_type(int idx) {
    return sqlite3_column_type(this->stmt, idx);
}

cc_sqlite3_type cc_sqlite3::column_type_name(int idx) {
    int type = sqlite3_column_type(this->stmt, idx);
    return cc_sqlite3_type(type);
}

int cc_sqlite3::column_int(int idx) {
	int max_cols = this->column_count();
	if(idx >= max_cols) {
		throw cc_sqlite3_exception("Index column overflow: " + to_string(idx) + " >= " + to_string(max_cols));
	}
	int type = sqlite3_column_type(this->stmt, idx);
	if(type != SQLITE_INTEGER) {
		throw cc_sqlite3_exception("Cannot get data type: " + to_string(type) + " != " + to_string(SQLITE_INTEGER));
	}
	int value = sqlite3_column_int(this->stmt, idx);
	return value;
}

double cc_sqlite3::column_double(int idx) {
	int max_cols = this->column_count();
	if(idx >= max_cols) {
		throw cc_sqlite3_exception("Index column overflow: " + to_string(idx) + " >= " + to_string(max_cols));
	}
	int type = sqlite3_column_type(this->stmt, idx);
	if(type != SQLITE_FLOAT) {
		throw cc_sqlite3_exception("Cannot get data type: " + to_string(type) + " != " + to_string(SQLITE_FLOAT));
	}
	double value = sqlite3_column_double(this->stmt, idx);
	return value;
}

string cc_sqlite3::column_text(int idx) {
	int max_cols = this->column_count();
	if(idx >= max_cols) {
		throw cc_sqlite3_exception("Index column overflow: " + to_string(idx) + " >= " + to_string(max_cols));
	}
	int type = sqlite3_column_type(this->stmt, idx);
	if(type != SQLITE_TEXT) {
		throw cc_sqlite3_exception("Cannot get data type: " + to_string(type) + " != " + to_string(SQLITE_TEXT));
	}
	const unsigned char * c_str = sqlite3_column_text(this->stmt, idx);
	string value = string(reinterpret_cast<const char*>(c_str));
	return value;
}

cc_sqlite3_blob cc_sqlite3::column_blob(int idx) {
	int max_cols = this->column_count();
	if(idx >= max_cols) {
		throw cc_sqlite3_exception("Index column overflow: " + to_string(idx) + " >= " + to_string(max_cols));
	}
	int type = sqlite3_column_type(this->stmt, idx);
	if(type != SQLITE_BLOB) {
		throw cc_sqlite3_exception("Cannot get data type: " + to_string(type) + " != " + to_string(SQLITE_BLOB));
	}
	int bytes = sqlite3_column_bytes(this->stmt, idx);
	const void * value = sqlite3_column_blob(this->stmt, idx);

	return cc_sqlite3_blob(value, bytes);
}

void cc_sqlite3::finalize() {
	int code = sqlite3_finalize(this->stmt);
	if(code != SQLITE_OK) {
		throw cc_sqlite3_exception(this->err_msg(code));
	}
}

void cc_sqlite3::close() {
    int code = sqlite3_close(this->db);
	if(code != SQLITE_OK) {
		throw cc_sqlite3_exception(this->err_msg(code));
	}
}

bool cc_sqlite3::get_autocommit() {
	return sqlite3_get_autocommit(this->db) != 0;
}

string cc_sqlite3::libversion(void) {
	const char * c_str_buffer;

	c_str_buffer = sqlite3_libversion();
	string retval(c_str_buffer);
	return retval;
}

string cc_sqlite3::sourceid(void) {
	const char * c_str_buffer;

	c_str_buffer = sqlite3_sourceid();
	string retval(c_str_buffer);
	return retval;
}

int cc_sqlite3::libversion_number(void) {
	return sqlite3_libversion_number();
}
