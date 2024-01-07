from multiprocessing import Process
from flask import Flask, send_file

def serve_gif(port, gif_path):
    app = Flask(__name__)

    @app.route('/')
    def serve():
        return send_file(gif_path, mimetype='image/gif')

    app.run(port=port)

if __name__ == "__main__":
    # Define your ports and corresponding gif paths here
    ports = [5000, 5001, 5002, 5003, 5004, 5005, 5006]
    gif_paths = ['../data/images/cam_1.gif', '../data/images/cam_2.gif', '../data/images/cam_3.gif',
                 '../data/images/cam_4.gif', '../data/images/cam_5.gif', '../data/images/cam_6.gif',
                 '../data/images/cam_7.gif']

    # Create and start a separate process for each port
    for port, gif_path in zip(ports, gif_paths):
        Process(target=serve_gif, args=(port, gif_path)).start()

