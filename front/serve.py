from flask import Flask
from flask import render_template
from flask import Flask, redirect, url_for, request
import subprocess
def str_2_bin(str):
    """
    字符串转换为二进制
    """
    return ' '.join([bin(ord(c)).replace('0b', '') for c in str])


def bin_2_str(bin):
    """
    二进制转换为字符串
    """
    return ''.join([chr(i) for i in [int(b, 2) for b in bin.split(' ')]])
# from subprocess import Popen, PIPE
app = Flask(__name__)
@app.route('/')
def no ():
    return redirect('/menu?command=start',code=302,Response="aaaaa")
@app.route('/menu',methods = ['GET'])
def menu():
#    if request.method == 'POST':
#       user = request.form['nm']
#       return redirect(url_for('success',name = user))
#    else:
    if request.method == 'GET':
        command = request.args.get('command')
        p.stdin.write((command+"\n").encode())
        p.stdin.flush()
        # p.stdin.write(b'1\n')
        # res=str(command)
        res=str(p.stdout.read1().decode())
        # if command!=None:
        #     res+=str(command)
        # res+="          hahaaaa 这里没有后端"
        return render_template('menu.html',res=[[s for s in line.split('\t')]for line in res.split("\n")])
    # return redirect(url_for('success',name = user))
    return render_template('menu.html',res="\n")


@app.route('/hello/<usr>')
def index(usr):
   return render_template("hello.html",name=usr)
if __name__ == '__main__':
#    subprocess.run("ls",shell=True    ,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    # p=subprocess.Popen.communicate("ls",stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    # p.stdin.write(command)
    global p 
    p=subprocess.Popen(["../build/code"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    # print(p.stdout.read())
    # res=p.stdout.read()
    print("begin to run")
    app.run(host="127.0.0.1",port=8081,debug=True)