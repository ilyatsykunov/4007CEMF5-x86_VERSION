/*#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "libsqlite.hpp"
#include <string>

#endif // !DATABASE_H

void ConnectToDatabase(std::string chosenDB) {

	sqlite::sqlite db(chosenDB);

	auto cur = db.get_statement();
	cur->set_sql(" SELECT * FROM Creeps;");
	cur->prepare();

	while (cur->step()) {
		std::cout << cur->get_int(0) << " " << cur->get_text(1) << std::endl;
	}
		
}*/