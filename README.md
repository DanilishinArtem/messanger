# How to use messanger:

**Example of the POST command**:

	curl -X POST http://127.0.0.1:5000/send -H "Content-Type: application/json" -d '{"sender": "Alice", "receiver": "Bob", "message": "someText"}'


**Example of the GET command**:

	curl "http://172.31.239.69:5000/receive?user=Bob"


**Database**:
---
*Installing PostgreSQL:*
	
	sudo apt update
	sudo apt install postgresql postgresql-contrib

*Creating database and users:*

	sudo -i -u postgres
	psql

*Inside 'psql':*
	
	CREATE DATABASE messenger_db;
	CREATE USER name_of_user WITH ENCRYPTED PASSWORD 'password';
	GRANT ALL PRIVILEGES ON DATABASE messenger_db TO name_of_user;

*Creating table of messages:*

	\c messenger_db
	CREATE TABLE messages (
		id SERIAL PRIMARY KEY,
		sender VARCHAR(50),
		receiver VARCHAR(50),
		message TEXT,
		timestamp TIMESTAMPTZ DEFAULT NOW()
	);