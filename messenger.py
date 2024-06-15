from flask import Flask, request, jsonify
import subprocess
from flask_cors import CORS

app = Flask(__name__)
CORS(app)  # применяем CORS ко всем маршрутам

@app.route('/send', methods=['POST'])
def send_message():
    sender = request.json['sender']
    receiver = request.json['receiver']
    message = request.json['message']
    
    result = subprocess.run(['./messenger_server', 'send', sender, receiver, message], capture_output=True, text=True)
    return result.stdout

@app.route('/receive', methods=['GET'])
def receive_messages():
    user = request.args.get('user')
    
    result = subprocess.run(['./messenger_server', 'receive', user], capture_output=True, text=True)
    return jsonify(result.stdout.splitlines())

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
