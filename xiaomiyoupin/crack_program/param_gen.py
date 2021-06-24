# 生成请求的参数


import random
import requests
import json
import hashlib

def gen_hash(actid):
    #get_server_timestamp()
    # a = gen_act_token_str(actid, actid)
    # to_sort_char_array(a)
    t = "1624547101823&306165493&"""""""",,000000000011333344445555668888::I[]aaabbcdddddddddeeeeeeeknott{{}}&K1qTCxMsHOkJID@!#FJWIPlQ5uypYZ3wnF"
    hashmd5(t)

def get_server_timestamp():
    url = "https://m.xiaomiyoupin.com/app/shopv3/timestamp"
    a = requests.get(url).text
    res = json.loads(a)
    timestamp = res["data"]
    return int(timestamp)

def gen_9num_random():
    r = random.random()
    a = round(1e9 * r)
    return a


def gen_act_token_str(actId, token):
    a = "[{},{\"actId\":\""+ actId +"\",\"token\":\""+token+"\"}]"
    return a


def to_sort_char_array(string):
    a = []
    for i in string:
        a.append(i)
    a.sort()
    s = ""
    dst = s.join(a)
    return dst


def hashmd5(t):
    out = hashlib.md5(t.encode('utf-8')).hexdigest()
    print(out)
    # 目标：12976A8EB453C9A3534A1842315722CB
    return out

