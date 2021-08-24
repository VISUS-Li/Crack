import _thread
import re
import time

import numpy as np

import param_gen
import login
import math
import spike
from apscheduler.schedulers.blocking import BlockingScheduler
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


class Account:
    def __init__(self, phone, pwd, dev_id):
        self.phone = phone
        self.pwd = pwd
        self.dev_id = dev_id



    def job(self):
        global serviceToken
        global cUserId
        if serviceToken == "":
            serviceToken, cUserId = login.callback_auth(self.dev_id, self.phone, self.pwd)
            count = 0
        # tstr = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')
        tstr = '2021-08-23 09:59:59.781286'
        t = float(time.mktime(time.strptime(tstr, '%Y-%m-%d %H:%M:%S.%f')))
        while True:
            now = time.time()
            if now > t:
                print(u"到点")
                break
        while True:
            spike.doSpike(youpindistinct, youpinsession, serviceToken, cUserId)
            count += 1
            time.sleep(0.1)
            if count > 20:
                break


def job(phone, pwd, dev_id):
        global serviceToken
        global cUserId
        if serviceToken == "":
            serviceToken, cUserId = login.callback_auth(dev_id, phone, pwd)
            count = 0
        # tstr = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')
        tstr = '2021-08-24 09:59:59.781286'
        t = float(time.mktime(time.strptime(tstr, '%Y-%m-%d %H:%M:%S.%f')))
        while True:
            now = time.time()
            if now > t:
                print(u"到点")
                break
        while True:
            spike.doSpike(youpindistinct, youpinsession, serviceToken, cUserId)
            count += 1
            time.sleep(0.1)
            if count > 20:
                break
# scheduler = BlockingScheduler()
# scheduler.add_job(job, 'cron', hour=9, minute=59, second=10)
# print("start timer")
# scheduler.start()

try:
    _thread.start_new_thread(job, ("18875146084", "Ly080330..", "_f1qJucbm08DiWZA"))
    _thread.start_new_thread(job,("19160384323", "miss1183989659", "_f1qJucbm08DiWZA"))
except:
    print("创建线程失败")

while 1:
    pass
#x = Account("19160384323", "miss1183989659", "_f1qJucbm08DiWZA")


#
# fp = open("acc.txt", "rt", encoding="UTF-8")
# lines = fp.readlines()
# lineCount = len(lines)
# dataArr = np.zeros(lineCount)

#spike.doOrder(dev_id, phone, pwd, youpindistinct, youpinsession)