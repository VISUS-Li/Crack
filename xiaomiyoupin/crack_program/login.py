import requests
import json

import param_gen
from param_gen import hashmd5
from urllib.parse import urlencode

# proxy='192.168.2.130:8888'  #本地代理
# proxies={
#     'http':'http://'+proxy,
#     'https':'https://'+proxy
# }
proxies = {}

def service_login(dev_id, phone):
    url = "https://account.xiaomi.com/pass/serviceLogin?_json=true&sid=miotstore"
    headers = {
        "User-Agent":"Dalvik/2.1.0 (Linux; U; Android 8.1.0; MI 8 MIUI/8.6.18) APP/xiaomi.youpin APPV/300 MK/TUkgOA== "
                     "PassportSDK/3.3.5 passport-ui/3.3.5 Dalvik/2.1.0 (Linux; U; Android 8.1.0; MI 8 "
                     "MIUI/8.6.18)Mobile MIOTWeex/2.0.2 ("
                     "YouPin;4.15.0;0D2F912ED0CA5ECA432C98814A0F1842;0.20.1;A"
                     ";49CB1FE12BE10DDE7B6D5223DFAE234879D601D3;MiAppStore;_f1qJucbm08DiWYZ;) MIOTStore/20191212 ("
                     "YouPin;4.15.0;0D2F912ED0CA5ECA432C98814A0F1842;20210623194554;A"
                     ";49CB1FE12BE10DDE7B6D5223DFAE234879D601D3;MiAppStore;_f1qJucbm08DiWYZ;) ",
        "Cookie":"userId=+86"+phone+"; deviceId="+dev_id+"; sdkVersion=accountsdk-2020.01.09"
    }
    resp = requests.get(url, headers=headers)
    r = resp.text[11:]
    res = json.loads(r)
    return res


def service_login_auth(device_id, phone, pwd):
    sveloginresp = service_login(device_id, phone)
    url = "https://account.xiaomi.com/pass/serviceLoginAuth2"
    headers = {
        "User-Agent": "Dalvik/2.1.0 (Linux; U; Android 8.1.0; MI 8 MIUI/8.6.18) APP/xiaomi.youpin APPV/300 "
                      "MK/TUkgOA== PassportSDK/3.3.5 passport-ui/3.3.5 Dalvik/2.1.0 (Linux; U; Android 8.1.0; MI 8 "
                      "MIUI/8.6.18)Mobile MIOTWeex/2.0.2 ("
                      "YouPin;4.15.0;0D2F912ED0CA5ECA432C98814A0F1842;0.20.1;A"
                      ";49CB1FE12BE10DDE7B6D5223DFAE234879D601D3;MiAppStore;_f1qJucbm08DiWYZ;) MIOTStore/20191212 ("
                      "YouPin;4.15.0;0D2F912ED0CA5ECA432C98814A0F1842;20210623194554;A"
                      ";49CB1FE12BE10DDE7B6D5223DFAE234879D601D3;MiAppStore;_f1qJucbm08DiWYZ;)",
        "Cookie": "sdkVersion=accountsdk-2020.01.09; deviceId=" + device_id,
        "Content-Type": "application/x-www-form-urlencoded",
    }
    hashpwd = hashmd5(pwd)
    bodys = {
        "cc": "+86",
        "qs":sveloginresp["qs"],
        "callback":sveloginresp["callback"],
        "_json": "true",
        "_sign": sveloginresp["_sign"],
        "user" : "+86"+phone,
        "hash" : hashpwd,
        "sid"  : sveloginresp["sid"]
    }
    enbody = urlencode(bodys)
    resp = requests.post(url, headers=headers, data=enbody, proxies=proxies, verify=False)
    r = resp.text[11:]
    res = json.loads(r)
    return res

#登录获取serviceToken
def callback_auth(dev_id, phone, pwd):
    cbauth_resp = service_login_auth(dev_id, phone, pwd)
    ssecurity = cbauth_resp["ssecurity"]
    nonce = int(float(cbauth_resp["nonce"]))
    query = "nonce=" + str(nonce) + "&" + ssecurity
    clientSign = param_gen.hashsha1(query)
    t = {
        "clientSign": clientSign
    }
    e = urlencode(t)
    url = cbauth_resp["location"] + "&_userIdNeedEncrypt=true&" + e
    resp = requests.get(url)
    r = resp.text[11:]
    srvtoken = resp.cookies.get("serviceToken")
    cUserId = resp.cookies.get("cUserId")
    return srvtoken, cUserId
