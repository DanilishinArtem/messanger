# How to use messanger:

**Example of the POST command**:

	curl -X POST http://127.0.0.1:5000/send -H "Content-Type: application/json" -d '{"sender": "Alice", "receiver": "Bob", "message": "someText"}'


**Example of the GET command**:

	curl "http://172.31.239.69:5000/receive?user=Bob"


