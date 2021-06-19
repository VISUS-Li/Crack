(function () {

    if (document.domain == ("m.mi.com")) {
        setTimeout(function () {
            var head = document.head || document.getElementsByTagName("head")[0];
            var csstext = ".fixed-header, .header{display:none !important;}";
            var style = document.createElement("style");
            style.type = "text/css";
            head.appendChild(style);
            style.innerHTML = csstext;
        }, 150)
    }
    if (document.domain == ("api.ucashier.mipay.com")) {
        setTimeout(function () {
            var head = document.head || document.getElementsByTagName("head")[0];
            var csstext = ".form-control.bottom-fixed{position:static !important;margin-top:30px}";
            var style = document.createElement("style");
            style.type = "text/css";
            head.appendChild(style);
            style.innerHTML = csstext;
        }, 150)
    }
    if (document.domain == ("m.mi.com")) {
        window.onhashchange = function () {
            if (location.hash.indexOf("/cart/index") > 0 || location.hash.indexOf("/shopping") > 0 || location.hash.indexOf("/index") > 0) {
                location.href = "https://m.xiaomiyoupin.com/jump?source=" + encodeURIComponent(location.href);
            }
        };
    }


    window._MiHomeStore = {
        platform: 'android',
        rnMakeTime: '20210529182442',
        appVersion: '4.15.0',
        statusBarHeight: 40,
        injectJSVersion: '1.0.0'
    };
    window.rnMakeTime = 20210529182442;
    window.appVersion = '4.15.0';
    window.statusBarHeight = 40;

    function rnSendWebEvent(name, value) {
        location.href = "https://m.xiaomiyoupin.com/webEvent?name=" + encodeURIComponent(name) + "&value=" + encodeURIComponent(value);
    }

    function rnSendWebEventOnMessage(id, name, value) {
        const s = JSON.stringify({
            stackType: 'request',
            id,
            name,
            value
        });
        window.ReactNativeWebView.postMessage(s)
    }

    function showShareIcon(data) {
        if (typeof data == 'object') {
            var s = JSON.stringify(data);
            rnSendWebEvent('showShareIconJson', s);
        } else if (typeof data == 'string') {
            rnSendWebEvent('showShareIconString', data);
        }
    }
    setTimeout(function () {
        if (document.title) {
            rnSendWebEvent('titleChanged', document.title);
        }
    }, 400);

    function showShareView(data) {
        if (data) {
            var s = JSON.stringify(data);
            rnSendWebEvent('showShareView', s);
        }
    }

    function shareByChannel(data) {
        if (data) {
            var s = JSON.stringify(data);
            rnSendWebEvent('shareByChannel', s);
        }
    }

    function checkCameraAccess(data) {
        if (typeof data === 'boolean') {
            rnSendWebEvent('checkCameraAccess', data);
        }
    }

    function getActSalt(data) {
        if (data) {
            var s = JSON.stringify(data);
            rnSendWebEvent('getActSalt', s);
        }
    }

    window._MiHomeStore.showShareView = showShareView;
    window._MiHomeStore.showShareIcon = showShareIcon;
    window._MiHomeStore.shareByChannel = shareByChannel;
    window._MiHomeStore.checkCameraAccess = checkCameraAccess;
    window._MiHomeStore.getActSalt = getActSalt;
    window._MiHomeStore.rnSendWebEvent = rnSendWebEvent;
    window._MiHomeStore.rnSendWebEventOnMessage = rnSendWebEventOnMessage;
    window._MiHomeStore.jsFunctionMap = {
        "showShareView2": 1,
        "showShareIcon2Json": 1,
        "showShareIcon2String": 1,
        "reportStat": 1,
        "showToast": 1,
        "onBackPress": 1,
        "onCloseWeb": 1,
        "shareToPyqWithImage": 1,
        "insertEventToCalendar": 1,
        "saveImageToLocal": 1,
        "isRn54": 1,
        "resetShareImageData": 1,
        "pushShareImageData": 1,
        "openNewWeb": 1,
        "showInputModal": 1,
        "onCheckIMPress": 1,
        "shareByChannel": 1,
        "checkCameraAccess": 1,
        "getActSalt": 1,
        "webPaySuccess": 1
    };;
})();






//2
//这里是android端在向webview中的js前端发消息，消息名为"message"
//在js端 监听 "message"消息：
/*
document.addEventListener("message", (function(t) {
    var e = JSON.parse(t.data);
    "subBuySalt" === e.id && e.result && (m = e.result)
})),
*/

(function () {
    var event;
    var data = {
        "data": "{\"stackType\":\"respone\",\"id\":\"subBuySalt\",\"name\":\"getActSalt\",\"result\":\"K1qTCxMsHOkJID@!#FJWIPlQ5uypYZ3wnF\",\"data\":\"{}\"}"
    };
    try {
        event = new MessageEvent('message', data);
    } catch (e) {
        event = document.createEvent('MessageEvent');
        event.initMessageEvent('message', true, true, data.data, data.origin, data.lastEventId, data.source);
    }
    document.dispatchEvent(event);
})();



//3
var YPJsBridge = function (e) {
    "use strict";
    var n = function (e, n) {
        return e(n = {
            exports: {}
        }, n.exports), n.exports
    }((function (e) {
        function n(t) {
            return "function" == typeof Symbol && "symbol" == typeof Symbol.iterator ? e.exports = n = function (e) {
                return typeof e
            } : e.exports = n = function (e) {
                return e && "function" == typeof Symbol && e.constructor === Symbol && e !== Symbol.prototype ? "symbol" : typeof e
            }, n(t)
        }
        e.exports = n
    }));

    function t(e, n) {
        for (var t = String(e).split("."), r = String(n).split("."), o = Math.max(t.length, r.length); t.length < o;) t.push("0");
        for (; r.length < o;) r.push("0");
        for (var i = 0; i < o; i++) {
            var u = parseInt(t[i]),
                c = parseInt(r[i]);
            if (u > c) return 1;
            if (u < c) return -1
        }
        return 0
    }
    var r = ["titleChanged"];
    var o = function (e, n) {
        if (!window._MiHomeStore || !window._MiHomeStore.jsFunctionMap) return null;
        var t = window._MiHomeStore.jsFunctionMap[e];
        return void 0 !== t && t === n
    };

    function i() {
        var e = navigator.userAgent.match(/YouPin;\d*\.\d*\.\d*/g);
        if (e && e.length) {
            var n = e[0].split(";")[1];
            if (console.log("current version:", n), 1 === t(n, "4.3.0") || 0 === t(n, "4.3.0")) return !0
        }
        return !1
    }
    return i() && function (e) {
        if (window.WebViewJavascriptBridge) return e(window.WebViewJavascriptBridge);
        if (window.WVJBCallbacks) return window.WVJBCallbacks.push(e);
        window.WVJBCallbacks = [e];
        var n = document.createElement("iframe");
        n.style.display = "none", n.src = "wvjbscheme://__BRIDGE_LOADED__", document.documentElement.appendChild(n), setTimeout((function () {
            document.documentElement.removeChild(n)
        }), 0)
    }((function (e) {
        window.WebViewJavascriptBridge = e
    })), e.invoke = function (e, t, u, c, a) {
        return !o(t, a) && i() ? window.WebViewJavascriptBridge.callHandler(t, u, c) : o(t, a) || r.includes(t) ? function (e, t) {
            "object" === n(t) && t && (t = JSON.stringify(t));
            return window._MiHomeStore.rnSendWebEvent(e, t), !0
        }(t, u) : "function" == typeof c ? c({
            code: -1,
            msg: "当前客户端版本太低"
        }) : {
            code: -1,
            msg: "当前客户端版本太低"
        }
    }, Object.defineProperty(e, "__esModule", {
        value: !0
    }), e
}({});

