import _thread
import re
import time
import threading
import pandas as pd

import numpy as np

import param_gen
import login
import math
import spike
from datetime import datetime

# # "[{},{"actId":"60ccc3e1c9e77c000130ac38","token":"60ccc3e1c9e77c000130ac38"}]"
# actid = "60ccc3e1c9e77c000130ac38"
# a = param_gen.gen_hash(actid)
# print(a)
dev_id = "_f1qJucbm08DiWZA"
phone = "19160384323"
pwd = "miss1183989659"
youpindistinct = "1795beacd71-0c2ad86ced3b82-90d1"
youpinsession = "179790965b0-0b0a4d1d5ee787-6677"
# login.callback_auth(dev_id, phone, pwd)
# spike.doOrder(dev_id, phone, pwd, youpindistinct, youpinsession)

serviceToken = ""
cUserId = ""
startTime = '2021-08-23 09:59:59.781286'

class Account:
    def __init__(self, phone, pwd, dev_id):
        self.phone = phone
        self.pwd = pwd
        self.dev_id = dev_id



    def job(self):
        global cUserId
        try:
            serviceToken, cUserId = login.callback_auth(self.dev_id, self.phone, self.pwd)
            count = 0
            t = float(time.mktime(time.strptime(startTime, '%Y-%m-%d %H:%M:%S.%f')))
            while True:
                now = time.time()
                if now > t:
                    print(u"到点")
                    break
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
            _thread.start_new_thread(spike.doOrder, (self.dev_id,  self.phone, self.pwd, youpindistinct, youpinsession))
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
    print(accounts[:])
    return accounts

accounts = read_account("acc.txt")
threads = []
for acc in accounts:
    t = threading.Thread(target=acc.job)
    t.setDaemon(True)
    t.start()
    #acc.order()
    # try:
    #     _thread.start_new_thread(acc.spike())
    # except:
    #     print("抢购创建线程失败")

 # for t in threads:
 #        t.setDaemon(True)
 #        t.start()
while 1:
    pass
