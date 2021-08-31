import _thread
import sys
import time
import threading


import param_gen
import login
import math
import spike
from datetime import datetime


dev_id = "_f1qJucbm08DiWZA"
phone = "19160384323"
pwd = "miss1183989659"
youpindistinct = "1795beacd71-0c2ad86ced3b82-90d1"
youpinsession = "179790965b0-0b0a4d1d5ee787-6677"
# login.callback_auth(dev_id, phone, pwd)
# spike.doOrder(dev_id, phone, pwd, youpindistinct, youpinsession)

# serviceToken = ""
# cUserId = ""
# startTime = '2021-08-23 09:59:59.781286'

class Account(threading.Thread):
    def __init__(self, phone, pwd, dev_id):
        threading.Thread.__init__(self)
        self.phone = phone
        self.pwd = pwd
        self.dev_id = dev_id

    def run(self):
        self.job()

    def job(self):
        try:
            print("线程ID：", threading.current_thread().ident)
            serviceToken, cUserId = login.callback_auth(self.dev_id, self.phone, self.pwd)
            count = 0
            t = float(time.mktime(time.strptime(startTime, '%Y-%m-%d %H:%M:%S.%f')))
            while True:
                now = time.time()
                print(self.phone, "等待开始\n")
                if now > t:
                    print(u"到点\n")
                    break
                time.sleep(1)
            while True:
                spike.doSpike(youpindistinct, youpinsession, serviceToken, cUserId, self.phone)
                count += 1
                time.sleep(0.1)
                if count > 20:
                    break
        except:
            print()


    def order(self):
        try:
            spike.doOrder(self.dev_id,  self.phone, self.pwd, youpindistinct, youpinsession)
        except:
            print("预约创建线程失败")


def read_account(file):
    accounts = []
    try:
        index = 1
        global startTime
        with open(file, newline='\n') as f:
            for line in f:
                if index == 1:
                    startTime = line.replace('\r\n', '')
                    index += 1
                    continue
                index += 1
                s = line.split("--")
                if "#" in s[0]:
                    continue
                acc = Account(s[0], s[1], s[2].replace('\r\n', ''))
                accounts.append(acc)
                pass
    except IndexError as arg:
        print("读取文件失败:", arg)
    return accounts


if __name__ == '__main__':
    str = """
    小米有品抢购 1.0
    功能列表：
    1.预约
    2.抢购
    """
    print(str)
    accounts = read_account("acc.txt")
    code = input("请选择：")
    if code == '1':

        for t in accounts:
            t.order()

    elif code == '2':
        threads = []
        for acc in accounts:
            acc.start()
            threads.append(acc)
        for t in threads:
            t.join()
    else:
        print("没有此功能")
        sys.exit(1)
