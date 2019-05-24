
#include <iostream>

#include <cc_sqlite3.hh>
#include <cc_sqlite3_exception.hh>

using namespace std;
using namespace std_cc_sqlite3;

int main() {
	
	cc_sqlite3 * conn = nullptr;
	string query;
	
	try {
		
		conn = new cc_sqlite3("/tmp/sqlite.db");
		
		cout << endl << "---------------    TEST: Create table and inserts    ---------------" << endl << endl;
		
		conn->exec(
			"DROP TABLE IF EXISTS friends;"
			"CREATE TABLE friends(id INTEGER PRIMARY KEY, name TEXT, phone TEXT UNIQUE);"
		);

		conn->exec(
			"INSERT INTO friends(name, phone) VALUES ('Tom',     '600000000');"
			"INSERT INTO friends(name, phone) VALUES ('Rebecca', '600000001');"
			"INSERT INTO friends(name, phone) VALUES ('Jim',     '600000002');"
			"INSERT INTO friends(name, phone) VALUES ('Roger',   '600000003');"
			"INSERT INTO friends(name, phone) VALUES ('Robert',  '600000004');"
			"INSERT INTO friends(name, phone) VALUES ('Paul',    '600000005');"
			"INSERT INTO friends(name, phone) VALUES ('Tony',    '600000006');"
			"INSERT INTO friends(name, phone) VALUES ('Mary',    '600000007');"
		);

		cout << "Last insert row id into friends: " << conn->last_insert_row_id() << endl;
		
		cout << endl << "---------------    TEST: Create table and inserts    ---------------" << endl << endl;
		
		conn->exec(
			"DROP TABLE IF EXISTS cars;"
			"CREATE TABLE cars(id INTEGER PRIMARY KEY, mark TEXT, model TEXT);"
		);

		conn->exec(
			"INSERT INTO cars(mark, model) VALUES ('Alfa',           'Romeo');"
			"INSERT INTO cars(mark, model) VALUES ('Audi',           'A3');"
			"INSERT INTO cars(mark, model) VALUES ('Volvo',          'S60');"
			"INSERT INTO cars(mark, model) VALUES ('Mercedes Benz',  'C220');"
			"INSERT INTO cars(mark, model) VALUES ('Volkswagen',     'Golf');"
			"INSERT INTO cars(mark, model) VALUES ('Renault',        'Megane');"
			"INSERT INTO cars(mark, model) VALUES ('Ford',           'Focus');"
			"INSERT INTO cars(mark, model) VALUES ('Peugeot',        '307');"
			"INSERT INTO cars(mark, model) VALUES ('Citroen',        'C5');"
			"INSERT INTO cars(mark, model) VALUES ('Opel',           'Astra');"
			"INSERT INTO cars(mark, model) VALUES ('Mazda',          '3');"
			"INSERT INTO cars(mark, model) VALUES ('Alfa',           'Mito');"
			"INSERT INTO cars(mark, model) VALUES ('Volvo',          'V40');"
			"INSERT INTO cars(mark, model) VALUES ('Volkswagen',     'Passat');"
			"INSERT INTO cars(mark, model) VALUES ('Ford',           'Mondeo');"
			"INSERT INTO cars(mark, model) VALUES ('Citroen',        'C3');"
			"INSERT INTO cars(mark, model) VALUES ('Mazda',          'MX5');"
			"INSERT INTO cars(mark, model) VALUES ('Volvo',          'C60');"
			"INSERT INTO cars(mark, model) VALUES ('Ford',           'Fiesta');"
		);

		cout << "Last insert row id into cars: " << conn->last_insert_row_id() << endl;
		
		cout << endl << "---------------    TEST: Select by id    ---------------" << endl << endl;
		
		query = string("SELECT id, mark, model FROM cars WHERE id < @id;");
		conn->prepare(query);
		conn->bind("@id", 4);
		
		cout << query << endl;
		bool first = true;
		while(conn->step()) {
			if(first) {
				string id_type = conn->column_type(0).to_string();
				string mark_type = conn->column_type(1).to_string();
				string model_type = conn->column_type(2).to_string();
				cout << "id(" << id_type << ") \t mark(" << mark_type << ") \t model(" << model_type << ")" << endl;
				cout << "-------------------" << endl;
				first = false;
			}
			
			int idx      = conn->column_int(0);
			string mark  = conn->column_text(1);
			string model = conn->column_text(2);
			
			cout << idx << "\t" << mark << "\t" << model << endl;
		}
		cout << endl;
		
		cout << endl << "---------------    TEST: Select by two marks    ---------------" << endl << endl;
		
		query = string("SELECT id, mark, model FROM cars WHERE mark = @mark1 OR mark = @mark2 ORDER BY mark;");
		conn->prepare(query);
		conn->bind("@mark1", "Volvo");
		conn->bind("@mark2", "Mazda");
		
		cout << query << endl;
		first = true;
		while(conn->step()) {
			if(first) {
				string id_type = conn->column_type(0).to_string();
				string mark_type = conn->column_type(1).to_string();
				string model_type = conn->column_type(2).to_string();
				cout << "id(" << id_type << ") \t mark(" << mark_type << ") \t model(" << model_type << ")" << endl;
				cout << "-------------------" << endl;
				first = false;
			}
			int idx      = conn->column_int(0);
			string mark  = conn->column_text(1);
			string model = conn->column_text(2);
			cout << idx << "\t" << mark << "\t" << model << endl;
		}
		cout << endl;
		
		cout << endl << "---------------    TEST: Create table, inserts and begin transaction    ---------------" << endl << endl;
		
		conn->exec(
			"DROP TABLE IF EXISTS fruits;"
			"CREATE TABLE fruits(id INTEGER PRIMARY KEY, name TEXT UNIQUE NOT NULL, count INTEGER NOT NULL);"
		);
		
		conn->exec(
			"BEGIN;"
			"INSERT INTO fruits(name, count) VALUES ('Apple',       10);"
			"INSERT INTO fruits(name, count) VALUES ('Pear',        2);"
			"INSERT INTO fruits(name, count) VALUES ('Blackberry',  8);"
			"INSERT INTO fruits(name, count) VALUES ('Raspberry',   8);"
			"INSERT INTO fruits(name, count) VALUES ('Banana',      11);"
			"INSERT INTO fruits(name, count) VALUES ('Pineapple',   4);"
			"INSERT INTO fruits(name, count) VALUES ('Orange',      7);"
			"INSERT INTO fruits(name, count) VALUES ('Cherry',      5);"
			"INSERT INTO fruits(name, count) VALUES ('Peach',       9);"
			"INSERT INTO fruits(name, count) VALUES ('Grape',       6);"
			"INSERT INTO fruits(name, count) VALUES ('Kiwi',        3);"
		);
		
		cout << "BEFORE:" << endl;
		cout << "Autocommit: " << conn->get_autocommit() << endl;
		
		conn->exec("COMMIT;");
		
		cout << "AFTER:" << endl;
		cout << "Autocommit: " << conn->get_autocommit() << endl << endl;
		
		cout << endl << "---------------    TEST: Create table and insert blob    ---------------" << endl << endl;
		
		conn->exec(
			"DROP TABLE IF EXISTS images;"
			"CREATE TABLE images(id INTEGER PRIMARY KEY, name TEXT, nbytes INTEGER, raw BLOB);"
		);
		
		const char * home = getenv("HOME");
		if(home != nullptr) {
			
			string image_path = string(home) + "/projects/cpp-sqlite/images/calculator.png";
					
			cc_sqlite3_blob * sqlite_blob = new cc_sqlite3_blob(image_path);

			conn->prepare("INSERT INTO images(name, nbytes, raw) VALUES (@name, @nbytes, @raw);");
			conn->bind("@name", "calculator.png");
			conn->bind("@nbytes", static_cast<int>(sqlite_blob->get_bytes()));
			conn->bind("@raw", *sqlite_blob);
			conn->step();
			
			delete sqlite_blob;
			
			conn->prepare("SELECT * FROM images WHERE (name = 'calculator.png')");
			if(conn->step()) {
				string name = conn->column_text(1);
				int nbytes = conn->column_int(2);
				cc_sqlite3_blob sqlite_blob_recovery = conn->column_blob(3);
				
				cout << "Name: " << name << ", bytes: " << nbytes << endl;
				sqlite_blob_recovery.write_file("/tmp/" + name);
			}
			
		} else {
			cerr << "Environ variable HOME is not set" << endl;
		}
		
	} catch(cc_sqlite3_exception & ex) {
		cout << "Exception: " << ex.what() << endl;
	}
	
	//////////  Test Exceptions  //////////
	
	try {
		
		cout << endl << "---------------    TEST: Unique constraint    ---------------" << endl << endl;
		conn->exec("INSERT INTO cars(id, mark, model) VALUES (1, 'Alfa', 'Romeo');");
		
	} catch(cc_sqlite3_exception & ex) {
		cout << "Exception: " << ex.what() << endl;
	}
	
	if(conn) {
		delete conn;
	}
	
	cout << endl << "Done" << endl << endl;
	
	return 0;
}
