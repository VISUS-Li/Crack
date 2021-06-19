# 生成请求的参数


import random
import requests
import json

def gen_hash(actid):
    get_server_timestamp()
    # a = gen_act_token_str(actid, actid)
    # to_sort_char_array(a)


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


# "1624077940740&574326571&"""""""",,000000000011113333336677778899::I[]aaacccccccccccccdeeeeeknott{{}}&K1qTCxMsHOkJID@!#FJWIPlQ5uypYZ3wnF"
