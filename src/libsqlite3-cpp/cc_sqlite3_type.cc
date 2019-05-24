
#include "cc_sqlite3_type.hh"

using namespace std_cc_sqlite3;

const int cc_sqlite3_type::MINOR_TYPE = 1;
const int cc_sqlite3_type::MAJOR_TYPE = 5;

const string cc_sqlite3_type::TYPES[] = {
	"",
	"INTEGER",
	"FLOAT",
	"TEXT",
	"BLOB",
	"NULL",
};

cc_sqlite3_type::cc_sqlite3_type(int type) {
	if(MINOR_TYPE <= type && type <= MAJOR_TYPE) {
		this->type = type;
	} else {
		throw cc_sqlite3_exception("Invalid code type " + std::to_string(type));
	}
}

cc_sqlite3_type::~cc_sqlite3_type() {
}

const string & cc_sqlite3_type::to_string() {
	return cc_sqlite3_type::TYPES[this->type];
}

bool cc_sqlite3_type::equals(int type) {
	return this->type == type;
}

bool cc_sqlite3_type::equals(const string & type) {
	return TYPES[this->type].compare(type) == 0;
	return true;
}
