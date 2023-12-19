import subprocess

# 创建一个子进程，执行cat命令
process = subprocess.Popen(['cat'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

# 向子进程的stdin写入数据
process.stdin.write(b'Hello World\n')
# process.stdin.close()

# 读取子进程的标准输出
output, error = process.communicate()

print(output.decode().strip())  # 输出："Hello World"
