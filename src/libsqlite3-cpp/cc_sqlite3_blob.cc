
#include "cc_sqlite3_blob.hh"

using namespace std_cc_sqlite3;

cc_sqlite3_blob::cc_sqlite3_blob(const void * blob, int nbytes) {
	this->blob = nullptr;
	this->nbytes = nbytes;
	this->blob = calloc(this->nbytes, sizeof(uint8_t));
	memcpy(this->blob, blob, this->nbytes);
}

cc_sqlite3_blob::cc_sqlite3_blob(const string & filename) {
	this->blob = nullptr;
	int fd = open(filename.c_str(), O_RDONLY);
	if(fd == -1) {
		throw cc_sqlite3_exception("Cannot open file " + filename + ": " + strerror(errno));
	}
	struct stat file_info;
	if(fstat(fd, &file_info) == -1) {
		close(fd);
		throw cc_sqlite3_exception("Cannot stat file " + filename + ": " + strerror(errno));
	}
	this->nbytes = file_info.st_size;
	
	this->blob = calloc(this->nbytes, sizeof(uint8_t));
	
	read(fd, this->blob, this->nbytes);
	
	close(fd);
}

cc_sqlite3_blob::~cc_sqlite3_blob() {
	if(this->blob) {
		free(this->blob);
	}
}

const void * cc_sqlite3_blob::get_blob() const {
	return this->blob;
}

off_t cc_sqlite3_blob::get_bytes() const {
	return this->nbytes;
}

ssize_t cc_sqlite3_blob::write_file(const string & filename) {
	ssize_t write_bytes = 0;
	int fd = open(filename.c_str(), O_CREAT | O_WRONLY);
	if(fd == -1) {
		throw cc_sqlite3_exception("Cannot open file " + filename + ": " + strerror(errno));
	}
	write_bytes = write(fd, this->blob, this->nbytes);
	close(fd);
	return write_bytes;
}
