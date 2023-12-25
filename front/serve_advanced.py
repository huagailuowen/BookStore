from flask import Flask
from flask import render_template
from flask import Flask, redirect, url_for, request
import subprocess
from flask_bootstrap import Bootstrap
app = Flask(__name__)
bootstrap=Bootstrap(app)
@app.route('/log',methods = ['GET'])
def log():
    if request.method == 'GET':
        p.stdin.write(('log'+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("0_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
@app.route('/finance',methods = ['GET'])
def finance():
    if request.method == 'GET':
        p.stdin.write(('report finance'+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("0_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
@app.route('/emp',methods = ['GET'])
def emp():
    if request.method == 'GET':
        p.stdin.write(('report employee'+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("0_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])

@app.route('/count',methods = ['GET'])
def count():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        # command1 =str(request.args.get('command1'))
        p.stdin.write(('log '+command+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("1_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
@app.route('/login',methods = ['GET'])
def login():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        command1 =str(request.args.get('command1'))
        p.stdin.write(('su '+command+' '+command1+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("2_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
@app.route('/buy',methods = ['GET'])
def buy():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        command1 =str(request.args.get('command1'))
        p.stdin.write(('buy '+command+' '+command1+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("2_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
@app.route('/import',methods = ['GET'])
def import_book():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        command1 =str(request.args.get('command1'))
        p.stdin.write(('import '+command+' '+command1+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("2_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
    
@app.route('/regi',methods = ['GET'])
def regi():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        command1 =str(request.args.get('command1'))
        command2 =str(request.args.get('command2'))
        
        p.stdin.write(('register '+command+' '+command1+' '+command2+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("3_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
@app.route('/passwd',methods = ['GET'])
def passwd():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        command1 =str(request.args.get('command1'))
        command2 =str(request.args.get('command2'))
        
        p.stdin.write(('passwd '+command+' '+command1+' '+command2+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("3_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])

@app.route('/useradd',methods = ['GET'])
def useradd():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        command1 =str(request.args.get('command1'))
        command2 =str(request.args.get('command2'))
        command3 =str(request.args.get('command3'))
        
        p.stdin.write(('useradd '+command+' '+command1+' '+command2+' '+command3+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("4_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
    
@app.route('/qu',methods = ['GET'])
def show():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        command1 =str(request.args.get('command1'))
        command2 =str(request.args.get('command2'))
        command3 =str(request.args.get('command3'))
        # command4 =str(request.args.get('command4'))
        if command!='':
            command='-ISBN='+command
        if command1!='':
            command1='-name=\"'+command1+"\""
        if command2!='':
            command2='-author=\"'+command2+"\""
        
        if command3!='':
            command3='-keyword=\"'+command3+"\""
        
        p.stdin.write(('show '+command+' '+command1+' '+command2+' '+command3+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("5_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])

@app.route('/modi',methods = ['GET'])
def modi():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        command1 =str(request.args.get('command1'))
        command2 =str(request.args.get('command2'))
        command3 =str(request.args.get('command3'))
        command4 =str(request.args.get('command4'))
        if command!='':
            command='-ISBN='+command
        if command1!='':
            command1='-name=\"'+command1+"\""
        if command2!='':
            command2='-author=\"'+command2+"\""
        
        if command3!='':
            command3='-keyword=\"'+command3+"\""
        if command4!='':
            command4='-price='+command4
        
        p.stdin.write(('modify '+command+' '+command1+' '+command2+' '+command3+' '+command4+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("5_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])

@app.route('/del',methods = ['GET'])
def delete():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        
        p.stdin.write(('delete '+command+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("1_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
@app.route('/select',methods = ['GET'])
def select():
    if request.method == 'GET':
        command =str(request.args.get('command'))
        
        p.stdin.write(('select '+command+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode())
        return render_template("1_in.html",res=[[s for s in line.split('\t')]for line in res.split("\n")])
 
@app.route('/exit')
def exit ():
    return redirect("https://ys.mihoyo.com/?utm_source=backup53&from_channel=backup53&msclkid=2fd1ac930e561e998585c9169e06de7b#/")
    return render_template("exit.html")

@app.route('/')
def none ():
    return redirect('/base?res=Welcome',code=302,Response="aaaaa")
@app.route('/logout')
def  logout ():
    if request.method == 'GET':
        
        p.stdin.write(('logout'+"\n").encode())
        p.stdin.flush()
        res=str(p.stdout.read1().decode()).split('\n')[0]
        return redirect('/base?res='+res,code=302,Response="aaaaa")

@app.route('/base',methods = ['GET'])
def base():
    if request.method == 'GET':
        res=str(request.args.get('res'))
        return render_template('base.html',res=[[s for s in line.split('\t')]for line in res.split("\n")])
    # return redirect(url_for('success',name = user))
    return render_template('base.html',res=[])


@app.route('/hello/<usr>')
def index(usr):
   return render_template("hello.html",name=usr)
if __name__ == '__main__':
    global p 
    p=subprocess.Popen(["../build/code"],stdin=subprocess.PIPE,stdout=subprocess.PIPE)
    print("begin to run")
    app.run(host="127.0.0.1",port=8081,debug=True)