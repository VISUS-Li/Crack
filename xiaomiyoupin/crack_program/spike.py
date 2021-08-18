import datetime
import time
import json
import requests
from urllib.parse import urlparse, parse_qs, parse_qsl, urlencode
import login
import param_gen

def get_mt_order_page():
    url = "https://m.xiaomiyoupin.com/mr/5fa529d1c9e77c000148d30f"
    resp = requests.get(url, allow_redirects=False, verify=False)
    l = resp.headers.get("Location")
    u = parse_qs(urlparse(l).query)
    a = u.get("actId")[0]
    return l, a

def doOrder(dev_id, phone, pwd, youpindistinct, youpinsession):
    serviceToken, cUserId = login.callback_auth(dev_id, phone, pwd)
    refer, actId = get_mt_order_page()
    url = "https://m.xiaomiyoupin.com/mtop/act/orderspike/order?_=" + str(int(round(time.time() * 1000)))
    headers = {
        "User-Agent": "Dalvik/2.1.0 (Linux; U; Android 8.1.0; MI 8 MIUI/8.6.18) APP/xiaomi.youpin APPV/300 "
                      "MK/TUkgOA== PassportSDK/3.3.5 passport-ui/3.3.5 Dalvik/2.1.0 (Linux; U; Android 8.1.0; MI 8 "
                      "MIUI/8.6.18)Mobile MIOTWeex/2.0.2 ("
                      "YouPin;4.15.0;0D2F912ED0CA5ECA432C98814A0F1842;0.20.1;A"
                      ";49CB1FE12BE10DDE7B6D5223DFAE234879D601D3;MiAppStore;_f1qJucbm08DiWYZ;) MIOTStore/20191212 ("
                      "YouPin;4.15.0;0D2F912ED0CA5ECA432C98814A0F1842;20210623194554;A"
                      ";49CB1FE12BE10DDE7B6D5223DFAE234879D601D3;MiAppStore;_f1qJucbm08DiWYZ;)",
        "Cookie": "cUserId=" + cUserId + ";serviceToken=" + serviceToken + ";youpindistinct_id=" + youpindistinct + ";mjclient=YouPin" + ";youpin_sessionid" + youpinsession,
        "Content-Type": "application/json",
        "Referer": refer,
    }
    bodys = [{},{
        "actId": actId,
        "tel": "",
    }]
    enbody = json.dumps(bodys)
    resp = requests.post(url, headers=headers, data=enbody, verify=False)
    r = resp.text
    rr = json.loads(r)
    s = bool(rr["success"])
    if s:
        print("预约成功:\n")
        print(rr)
    else:
        print("预约失败:\n")
        print(rr)
    return r


def doSpike(youpindistinct, youpinsession, serviceToken, cUserId):
    refer, actId = get_mt_order_page()
    rand, stime, hashval = param_gen.get_param(actId)
    url = "https://m.xiaomiyoupin.com/mtop/act/orderspike/spike?_=" + str(int(round(time.time() * 1000)))
    headers = {
        "User-Agent": "Dalvik/2.1.0 (Linux; U; Android 8.1.0; MI 8 MIUI/8.6.18) APP/xiaomi.youpin APPV/300 "
                      "MK/TUkgOA== PassportSDK/3.3.5 passport-ui/3.3.5 Dalvik/2.1.0 (Linux; U; Android 8.1.0; MI 8 "
                      "MIUI/8.6.18)Mobile MIOTWeex/2.0.2 ("
                      "YouPin;4.15.0;0D2F912ED0CA5ECA432C98814A0F1842;0.20.1;A"
                      ";49CB1FE12BE10DDE7B6D5223DFAE234879D601D3;MiAppStore;_f1qJucbm08DiWYZ;) MIOTStore/20191212 ("
                      "YouPin;4.15.0;0D2F912ED0CA5ECA432C98814A0F1842;20210623194554;A"
                      ";49CB1FE12BE10DDE7B6D5223DFAE234879D601D3;MiAppStore;_f1qJucbm08DiWYZ;)",
        "Cookie": "cUserId=" + cUserId + ";serviceToken=" + serviceToken + ";youpindistinct_id=" + youpindistinct + ";mjclient=YouPin" + ";youpin_sessionid" + youpinsession,
        "Content-Type": "application/json",
        "Referer": refer,
        "yp-srs": str(rand),
        "yp-srt": str(stime),
        "yp-ss": hashval,
    }
    bodys = [{},{
        "actId": actId,
        "token": actId,
    }]
    enbody = json.dumps(bodys)
    resp = requests.post(url, headers=headers, data=enbody, verify=False)
    r = resp.text
    rr = json.loads(r)
    s = bool(rr["data"]["success"])
    if s:
        print("抢购成功:\n")
        print(rr)
    else:
        print("抢购失败:\n")
        print(rr)
    return r

