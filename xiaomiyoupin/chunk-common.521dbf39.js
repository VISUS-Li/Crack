(window["webpackJsonp"] = window["webpackJsonp"] || []).push([["chunk-common"], {
    "19cf": function(t, e, n) {
        "use strict";
        n("456d"),
        n("ac6a"),
        n("6b54");
        var o = {
            emitShareToWxFriend: function(t) {
                var e = {
                    title: t.title,
                    content: t.content || " ",
                    image: t.image,
                    wxminiprogramImg: t.wxminiprogramImg || t.image,
                    miniProgramPath: t.miniProgramPath,
                    url: t.url || location.href,
                    direct: !0,
                    channel: "weixin_friend"
                };
                r.deleteEmptyParams(e),
                appShare3(e, {
                    mode: "channel",
                    direct: !0
                })
            },
            emitShareToPyq: function(t) {
                var e = {
                    title: t.pyqTitle || t.title,
                    content: t.pyqContent || t.content,
                    image: t.image,
                    url: t.url || location.href,
                    direct: !0,
                    channel: "weixin_pyq"
                };
                appShare3(e, {
                    mode: "channel",
                    direct: !0
                })
            },
            emitShareToPyqWithImage: function(t) {
                window.appApi && window.appApi("shareToPyqWithImage", t, 1)
            },
            emitShareToWeibo: function(t) {
                var e = {
                    title: t.wbTitle || t.title,
                    content: t.wbContent || t.content,
                    image: t.image,
                    url: t.url || location.href,
                    direct: !0,
                    channel: "weibo"
                };
                Object.assign(e),
                appShare3(e, {
                    mode: "channel",
                    direct: !0
                })
            },
            setIconShare: function(t, e) {
                if (ua.weixin)
                    return this.setWechatShare(t);
                var n = {
                    url: t.url,
                    title: t.title,
                    wbTitle: t.wbTitle || t.title,
                    pyqTitle: t.pyqTitle || t.title,
                    content: t.content,
                    wbContent: t.wbContent || t.content,
                    pyqContent: t.pyqContent || t.content,
                    image: t.image,
                    wxminiprogramImg: t.wxminiprogramImg || t.image,
                    miniProgramPath: t.miniProgramPath,
                    direct: 0
                };
                appShare3(n, {
                    mode: e ? "popup" : "icon"
                })
            },
            popRnShare: function(t) {
                this.setIconShare(t, !0)
            },
            setWechatShare: function(t) {
                function e(e) {
                    return t.apply(this, arguments)
                }
                return e.toString = function() {
                    return t.toString()
                }
                ,
                e
            }((function(t) {
                var e = {
                    title: t.title,
                    content: t.content,
                    url: t.url,
                    image: t.image,
                    pyqTitle: t.pyqTitle,
                    miniProgramPath: t.miniProgramPath
                };
                r.deleteEmptyParams(e);
                try {
                    setWechatShare(e)
                } catch (o) {}
                if (wx && wx.miniProgram && wx.miniProgram.postMessage) {
                    var n = {
                        shareImg: e.image,
                        shareTitle: e.title,
                        shareUrl: e.miniProgramPath || e.url
                    };
                    wx.miniProgram.postMessage({
                        data: n
                    })
                }
            })),
            interceptMpShareInfo: function(t, e) {
                if (!e)
                    return {};
                var n = e.default || {}
                  , o = t && t.target && t.target.dataset && t.target.dataset.tag;
                return o && e[o] ? r.getMpShareObj(e[o]) : r.getMpShareObj(n)
            }
        }
          , r = {
            deleteEmptyParams: function(t) {
                Object.keys(t).forEach((function(e) {
                    var n = t[e];
                    [void 0, null , ""].indexOf(n) > -1 && delete t[e]
                }))
            },
            getMpShareObj: function(t) {
                return {
                    title: t.title,
                    imageUrl: t.image,
                    path: t.miniProgramPath
                }
            }
        };
        e["a"] = o
    },
    "19e7": function(t, e) {
        function n(t, e) {
            var n = (65535 & t) + (65535 & e)
              , o = (t >> 16) + (e >> 16) + (n >> 16);
            return o << 16 | 65535 & n
        }
        function o(t, e) {
            return t << e | t >>> 32 - e
        }
        function r(t, e, r, a, i, c) {
            return n(o(n(n(e, t), n(a, c)), i), r)
        }
        function a(t, e, n, o, a, i, c) {
            return r(e & n | ~e & o, t, e, a, i, c)
        }
        function i(t, e, n, o, a, i, c) {
            return r(e & o | n & ~o, t, e, a, i, c)
        }
        function c(t, e, n, o, a, i, c) {
            return r(e ^ n ^ o, t, e, a, i, c)
        }
        function u(t, e, n, o, a, i, c) {
            return r(n ^ (e | ~o), t, e, a, i, c)
        }
        function s(t, e) {
            var o, r, s, m, d;
            t[e >> 5] |= 128 << e % 32,
            t[14 + (e + 64 >>> 9 << 4)] = e;
            var l = 1732584193
              , p = -271733879
              , f = -1732584194
              , h = 271733878;
            for (o = 0; o < t.length; o += 16)
                r = l,
                s = p,
                m = f,
                d = h,
                l = a(l, p, f, h, t[o], 7, -680876936),
                h = a(h, l, p, f, t[o + 1], 12, -389564586),
                f = a(f, h, l, p, t[o + 2], 17, 606105819),
                p = a(p, f, h, l, t[o + 3], 22, -1044525330),
                l = a(l, p, f, h, t[o + 4], 7, -176418897),
                h = a(h, l, p, f, t[o + 5], 12, 1200080426),
                f = a(f, h, l, p, t[o + 6], 17, -1473231341),
                p = a(p, f, h, l, t[o + 7], 22, -45705983),
                l = a(l, p, f, h, t[o + 8], 7, 1770035416),
                h = a(h, l, p, f, t[o + 9], 12, -1958414417),
                f = a(f, h, l, p, t[o + 10], 17, -42063),
                p = a(p, f, h, l, t[o + 11], 22, -1990404162),
                l = a(l, p, f, h, t[o + 12], 7, 1804603682),
                h = a(h, l, p, f, t[o + 13], 12, -40341101),
                f = a(f, h, l, p, t[o + 14], 17, -1502002290),
                p = a(p, f, h, l, t[o + 15], 22, 1236535329),
                l = i(l, p, f, h, t[o + 1], 5, -165796510),
                h = i(h, l, p, f, t[o + 6], 9, -1069501632),
                f = i(f, h, l, p, t[o + 11], 14, 643717713),
                p = i(p, f, h, l, t[o], 20, -373897302),
                l = i(l, p, f, h, t[o + 5], 5, -701558691),
                h = i(h, l, p, f, t[o + 10], 9, 38016083),
                f = i(f, h, l, p, t[o + 15], 14, -660478335),
                p = i(p, f, h, l, t[o + 4], 20, -405537848),
                l = i(l, p, f, h, t[o + 9], 5, 568446438),
                h = i(h, l, p, f, t[o + 14], 9, -1019803690),
                f = i(f, h, l, p, t[o + 3], 14, -187363961),
                p = i(p, f, h, l, t[o + 8], 20, 1163531501),
                l = i(l, p, f, h, t[o + 13], 5, -1444681467),
                h = i(h, l, p, f, t[o + 2], 9, -51403784),
                f = i(f, h, l, p, t[o + 7], 14, 1735328473),
                p = i(p, f, h, l, t[o + 12], 20, -1926607734),
                l = c(l, p, f, h, t[o + 5], 4, -378558),
                h = c(h, l, p, f, t[o + 8], 11, -2022574463),
                f = c(f, h, l, p, t[o + 11], 16, 1839030562),
                p = c(p, f, h, l, t[o + 14], 23, -35309556),
                l = c(l, p, f, h, t[o + 1], 4, -1530992060),
                h = c(h, l, p, f, t[o + 4], 11, 1272893353),
                f = c(f, h, l, p, t[o + 7], 16, -155497632),
                p = c(p, f, h, l, t[o + 10], 23, -1094730640),
                l = c(l, p, f, h, t[o + 13], 4, 681279174),
                h = c(h, l, p, f, t[o], 11, -358537222),
                f = c(f, h, l, p, t[o + 3], 16, -722521979),
                p = c(p, f, h, l, t[o + 6], 23, 76029189),
                l = c(l, p, f, h, t[o + 9], 4, -640364487),
                h = c(h, l, p, f, t[o + 12], 11, -421815835),
                f = c(f, h, l, p, t[o + 15], 16, 530742520),
                p = c(p, f, h, l, t[o + 2], 23, -995338651),
                l = u(l, p, f, h, t[o], 6, -198630844),
                h = u(h, l, p, f, t[o + 7], 10, 1126891415),
                f = u(f, h, l, p, t[o + 14], 15, -1416354905),
                p = u(p, f, h, l, t[o + 5], 21, -57434055),
                l = u(l, p, f, h, t[o + 12], 6, 1700485571),
                h = u(h, l, p, f, t[o + 3], 10, -1894986606),
                f = u(f, h, l, p, t[o + 10], 15, -1051523),
                p = u(p, f, h, l, t[o + 1], 21, -2054922799),
                l = u(l, p, f, h, t[o + 8], 6, 1873313359),
                h = u(h, l, p, f, t[o + 15], 10, -30611744),
                f = u(f, h, l, p, t[o + 6], 15, -1560198380),
                p = u(p, f, h, l, t[o + 13], 21, 1309151649),
                l = u(l, p, f, h, t[o + 4], 6, -145523070),
                h = u(h, l, p, f, t[o + 11], 10, -1120210379),
                f = u(f, h, l, p, t[o + 2], 15, 718787259),
                p = u(p, f, h, l, t[o + 9], 21, -343485551),
                l = n(l, r),
                p = n(p, s),
                f = n(f, m),
                h = n(h, d);
            return [l, p, f, h]
        }
        function m(t) {
            var e, n = "", o = 32 * t.length;
            for (e = 0; e < o; e += 8)
                n += String.fromCharCode(t[e >> 5] >>> e % 32 & 255);
            return n
        }
        function d(t) {
            var e, n = [];
            for (n[(t.length >> 2) - 1] = void 0,
            e = 0; e < n.length; e += 1)
                n[e] = 0;
            var o = 8 * t.length;
            for (e = 0; e < o; e += 8)
                n[e >> 5] |= (255 & t.charCodeAt(e / 8)) << e % 32;
            return n
        }
        function l(t) {
            return m(s(d(t), 8 * t.length))
        }
        function p(t) {
            var e, n, o = "0123456789abcdef", r = "";
            for (n = 0; n < t.length; n += 1)
                e = t.charCodeAt(n),
                r += o.charAt(e >>> 4 & 15) + o.charAt(15 & e);
            return r
        }
        function f(t) {
            return unescape(encodeURIComponent(t))
        }
        function h(t) {
            return l(f(t))
        }
        function g(t) {
            return p(h(t))
        }
        function v(t, e, n) {
            return g(t).toUpperCase()
        }
        t.exports = {
            hash: v
        }
    },
    "24de": function(t, e, n) {
        "use strict";
        var o = n("7618")
          , r = (n("55dd"),
        n("19e7"))
          , a = n.n(r)
          , i = n("2b0e")
          , c = n("48ee")
          , u = n("3a71")
          , s = n("f78e")
          , m = Object(u["a"])(s["a"]);
        function d() {
            window._MiHomeStore && window._MiHomeStore.rnSendWebEventOnMessage && window._MiHomeStore.rnSendWebEventOnMessage("subBuySalt", "getActSalt", {})
        }
        document.addEventListener("message", (function(t) {
            var e = JSON.parse(t.data);
            "subBuySalt" === e.id && e.result && (m = e.result)
        })),
        setTimeout(d, 300),
        setTimeout(d, 1e3);
        var l = {
            c: function(t) {
                var e = c["a"].getServerTime()
                  , n = Math.round(1e9 * Math.random())
                  //m = K1qTCxMm9L2sHOkPlQ5uypYZ3wnFgXhN，似乎是会变的
                  //e = 服务器时间
                  //n = 随机数，四舍五入
                  //l.create(t)的返回值固定（actId不变的话）："""""""",,00000000001144555566777777889999::I[]aaabbcccccccdddeeeffknott{{}}
                  //最终传入hash函数的参数：1621167898797&871993980&"""""""",,00000000001144555566777777889999::I[]aaabbcccccccdddeeeffknott{{}}&K1qTCxMm9L2sHOkPlQ5uypYZ3wnFgXhN
                  //采用e&n&l.create(t)&m
                  , o = a.a.hash([e, n, l.create(t), m].join("&"))
                  , r = {};

                  //yp-srs:871993980 //随机数
                  //yp-srt:1621167898797  //服务器时间
                  //yp-ss:"F89DE81F213CC78AE01FABB3CD61EA56" //计算的hash
                return r[Object(u["a"])("4,12,106,10,14,29")] = e,
                r[Object(u["a"])("4,12,106,10,14,10")] = n,
                r[Object(u["a"])("4,12,106,10,10")] = o,
                setTimeout((function() {
                    m === Object(u["a"])(s["a"]) && i["a"].prototype.$ypm.touch("useSalt", 0, JSON.stringify(window._MiHomeStore))
                }), 800),
                r
            },
            create: function(t) {
                var e = l.toCharArray(JSON.stringify(l.removeNull(t))) //将
                  , n = e.sort();
                return n = n.join(""),
                n
            },
            toCharArray: function(t) {
                for (var e = new Array(t.length), n = 0; n < t.length; n++)
                    e[n] = t.charAt(n);
                return e
            },
            removeNull: function(t) {
                if (t) {
                    for (var e in t)
                        null !== t[e] ? "object" === Object(o["a"])(t[e]) && l.removeNull(t[e]) : delete t[e];
                    return t
                }
            }
        };
        e["a"] = l
    },
    "3a71": function(t, e, n) {
        "use strict";
        n.d(e, "a", (function() {
            return r
        }));
        n("28a5");
        var o = "heavy boxes perform quick waltzes and jigs.HEAVY BOXES PERFORM QUICK WALTZES AND JIGS.1 2 3 4 5 6 7 8 9 0 -"
          , r = function(t) {
            return t.split(",").map((function(t) {
                return t >= 0 ? o[+t] : ""
            })).join("")
        }
    },
    "45c3": function(t, e, n) {
        "use strict";
        n("8e6e"),
        n("6762"),
        n("2fdb"),
        n("386d"),
        n("96cf");
        var o = n("3b8d")
          , r = (n("ac6a"),
        n("456d"),
        n("bd86"))
          , a = n("4538")
          , i = n("f9bc")
          , c = n("f8dd");
        function u(t, e) {
            var n = Object.keys(t);
            if (Object.getOwnPropertySymbols) {
                var o = Object.getOwnPropertySymbols(t);
                e && (o = o.filter((function(e) {
                    return Object.getOwnPropertyDescriptor(t, e).enumerable
                }))),
                n.push.apply(n, o)
            }
            return n
        }
        function s(t) {
            for (var e = 1; e < arguments.length; e++) {
                var n = null != arguments[e] ? arguments[e] : {};
                e % 2 ? u(Object(n), !0).forEach((function(e) {
                    Object(r["a"])(t, e, n[e])
                })) : Object.getOwnPropertyDescriptors ? Object.defineProperties(t, Object.getOwnPropertyDescriptors(n)) : u(Object(n)).forEach((function(e) {
                    Object.defineProperty(t, e, Object.getOwnPropertyDescriptor(n, e))
                }))
            }
            return t
        }
        var m = "/mtop/mf/resource/internal"
          , d = function() {
            var t = Array.prototype.slice.call(arguments);
            return a["ua"].app ? setTimeout((function() {
                return a["toast"].apply(window, t)
            }), 200) : a["toast"].apply(window, t)
        }
          , l = function(t) {
            var e = t.url
              , n = t.data
              , o = void 0 === n ? {} : n
              , r = t.noToast
              , c = void 0 !== r && r
              , u = t.method
              , m = void 0 === u ? "post" : u;
            return new Promise((function(t, n) {
                $.ajax({
                    url: e,
                    type: m,
                    contentType: "application/json",
                    dataType: "json",
                    headers: s({}, i["a"].c(o)),
                    timeout: 1e4,
                    cache: !1,
                    data: 0 === Object.keys(o).length ? "" : JSON.stringify(o),
                    success: function(e) {
                        switch (e.code) {
                        case 0:
                            t(e);
                            break;
                        case 401:
                            Object(a["jumptoLogin"])();
                            break;
                        default:
                            t(e);
                            break
                        }
                    },
                    error: function(t) {
                        c || d("遇到点问题，请稍后再试哦~"),
                        n(t)
                    }
                })
            }
            ))
        }
          , p = function() {
            var t = Object(o["a"])(regeneratorRuntime.mark((function t() {
                var e, n;
                return regeneratorRuntime.wrap((function(t) {
                    while (1)
                        switch (t.prev = t.next) {
                        case 0:
                            return e = [{}],
                            t.prev = 1,
                            t.next = 4,
                            l({
                                url: m,
                                data: e
                            });
                        case 4:
                            return n = t.sent,
                            t.abrupt("return", n);
                        case 8:
                            return t.prev = 8,
                            t.t0 = t["catch"](1),
                            console.log(t.t0),
                            t.abrupt("return", null );
                        case 12:
                        case "end":
                            return t.stop()
                        }
                }), t, null , [[1, 8]])
            })));
            return function() {
                return t.apply(this, arguments)
            }
        }()
          , f = window && window.location.search && window.location.search.includes("isDebug")
          , h = window && 0 !== window.location.hostname.indexOf("st.")
          , g = {
            data: function() {
                return {
                    IS_DEBUG: !1
                }
            },
            mounted: function() {
                var t = Object(o["a"])(regeneratorRuntime.mark((function t() {
                    var e, n, o, r = this;
                    return regeneratorRuntime.wrap((function(t) {
                        while (1)
                            switch (t.prev = t.next) {
                            case 0:
                                if (!f) {
                                    t.next = 12;
                                    break
                                }
                                if (console.log("测试内网环境"),
                                !h) {
                                    t.next = 10;
                                    break
                                }
                                return t.next = 5,
                                p();
                            case 5:
                                if (e = t.sent,
                                n = e.code,
                                o = e.data,
                                0 === n && o) {
                                    t.next = 10;
                                    break
                                }
                                return t.abrupt("return");
                            case 10:
                                this.IS_DEBUG = !0,
                                window.addEventListener("message", (function(t) {
                                    var e = t.data;
                                    switch (e.type) {
                                    case "dw_data":
                                        r.SKIN_CONFIG && (r.SKIN_CONFIG = e.content);
                                        break;
                                    case "dw_connect":
                                        window.parent.postMessage({
                                            type: "dw_connect",
                                            content: e.content
                                        }, "*");
                                        break
                                    }
                                }));
                            case 12:
                            case "end":
                                return t.stop()
                            }
                    }), t, this)
                })));
                function e() {
                    return t.apply(this, arguments)
                }
                return e
            }(),
            methods: {
                openUri: function(t) {
                    var e = arguments.length > 1 && void 0 !== arguments[1] && arguments[1]
                      , n = arguments.length > 2 && void 0 !== arguments[2] ? arguments[2] : {};
                    if (this.IS_DEBUG && window.parent.postMessage({
                        type: "dw_history",
                        content: window.location.href
                    }, "*"),
                    !1 === e) {
                        var o = Object(a["addParam"])(t, "spmref", c["a"].getSpm({
                            b: "".concat(n.b || "0"),
                            c: "".concat(n.c || "0"),
                            d: "".concat(n.d || "0")
                        }));
                        setTimeout((function() {
                            Object(a["jumpTo"])(o)
                        }), 20)
                    } else if (!0 === e) {
                        var r = Object(a["addParam"])(t, "spmref", c["a"].getSpm({
                            b: "".concat(n.b || "0"),
                            c: "".concat(n.c || "0"),
                            d: "".concat(n.d || "0")
                        }));
                        setTimeout((function() {
                            Object(a["openNewWeb"])(r)
                        }), 20)
                    }
                }
            }
        };
        e["a"] = g
    },
    "48ee": function(t, e, n) {
        "use strict";
        n.d(e, "a", (function() {
            return o
        }));
        var o = {
            timeDiff: 0,
            serverTimeOk: !1,
            getServerTime: function() {
                return this.serverTimeOk ? Date.now() + this.timeDiff : Date.now()
            },
            refreshServerTime: function() {
                try {
                    getServerTimestamp().then((function(t) {
                        o.serveTime = 1e3 * t,
                        o.timeDiff = o.serveTime - Date.now(),
                        o.serverTimeOk = !0
                    }))
                } catch (t) {}
            }
        };
        o.refreshServerTime()
    },
    "4dec": function(t, e, n) {
        "use strict";
        var o = n("f8dd");
        e["a"] = function(t) {
            t.prototype.$ypm = {
                touch: function(t, e) {
                    var n = arguments.length > 2 && void 0 !== arguments[2] ? arguments[2] : 0
                      , r = arguments.length > 3 && void 0 !== arguments[3] ? arguments[3] : ""
                      , a = arguments.length > 4 ? arguments[4] : void 0;
                    o["a"].touch(e, r, {
                        spm: {
                            b: a ? "$".concat(t, "_").concat(a, "$") : "$".concat(t, "$"),
                            c: e,
                            d: n
                        }
                    })
                },
                view: function(t, e) {
                    var n = e ? "".concat(t, "_").concat(e) : t;
                    o["a"].view(n, location.href, "", "", {})
                },
                getSpm: function(t, e) {
                    var n = arguments.length > 2 && void 0 !== arguments[2] ? arguments[2] : 0
                      , r = arguments.length > 3 ? arguments[3] : void 0
                      , a = r ? "".concat(t, "_").concat(r) : t;
                    return o["a"].getSpm({
                        b: "$".concat(a, "$"),
                        c: e,
                        d: n
                    })
                },
                context: o["a"]
            }
        }
    },
    "8e9e": function(t, e, n) {
        "use strict";
        function o(t) {
            var e = arguments.length > 1 && void 0 !== arguments[1] ? arguments[1] : 24;
            return r(t, e)
        }
        function r(t, e) {
            var n = Math.floor((1e3 * t - Date.now()) / 100)
              , o = "00"
              , r = "00"
              , i = "00"
              , c = "00"
              , u = 0;
            if (n <= 0)
                return {
                    hour: "00",
                    min: "00",
                    sec: "00",
                    miSec: 0
                };
            switch (e) {
            case 24:
                o = a(n / 864e3),
                r = a(n % 864e3 / 36e3),
                i = a(n / 600 % 60),
                c = a(n / 10 % 60),
                u = Math.floor(n % 10);
                break;
            case 72:
                o = a(n / 864e3),
                r = a(24 * Math.floor(n / 864e3) + n % 864e3 / 36e3),
                i = a(n / 600 % 60),
                c = a(n / 10 % 60),
                u = Math.floor(n % 10);
                break
            }
            return {
                day: o,
                hour: r,
                min: i,
                sec: c,
                miSec: u
            }
        }
        function a(t) {
            return t = Math.floor(t),
            0 === t ? "00" : t < 10 ? "0".concat(t) : "".concat(t)
        }
        n.d(e, "a", (function() {
            return o
        }))
    },
    a670: function(t, e, n) {
        "use strict";
        n("28a5");
        var o = "4.3.0"
          , r = "4.5.0"
          , a = ua.youpin;
        function i(t, e) {
            if (!t)
                return -2;
            t = t.split("."),
            e = e.split(".");
            var n = Math.max(t.length, e.length);
            while (t.length < n)
                t.push("0");
            while (e.length < n)
                e.push("0");
            for (var o = 0; o < n; o++) {
                var r = parseInt(t[o])
                  , a = parseInt(e[o]);
                if (r > a)
                    return 1;
                if (r < a)
                    return -1
            }
            return 0
        }
        e["a"] = function() {
            var t = arguments.length > 0 && void 0 !== arguments[0] ? arguments[0] : {};
            return new Promise((function(e, n) {
                var c = t.skip
                  , u = void 0 !== c && c
                  , s = t.type
                  , m = void 0 === s ? 0 : s
                  , d = t.skipVal
                  , l = void 0 === d ? 1 : d;
                if (u)
                    return l ? e(0) : n({
                        msg: "人脸认证失败(1003)",
                        code: 1003
                    });
                if (!a)
                    return n({
                        msg: "请在小米有品app中使用哦~",
                        code: 1001
                    });
                if (i(getAppVersion(), o) < 0)
                    return n({
                        msg: "请下载最新版本小米有品app",
                        code: 1002
                    });
                2 === m && i(getAppVersion(), r) < 0 && (m = 0);
                var p = window.YPJsBridge || window.youpinBridge;
                if (!p)
                    return n({
                        msg: "身份验证失败(1004)",
                        code: 1004
                    });
                try {
                    p.invoke("common", "cardFaceVerify", {
                        type: m
                    }, (function(t) {
                        if (0 === t.code)
                            return e(1);
                        var o = "身份验证失败";
                        return t.code && (o += "(".concat(t.code, ")")),
                        n({
                            msg: o,
                            detail: t,
                            code: 1005
                        })
                    }), 1)
                } catch (f) {
                    return n({
                        msg: "身份验证失败! (1006)",
                        detail: f && f.stack || "none",
                        code: 1006
                    })
                }
            }
            ))
        }
    },
    b434: function(t, e, n) {
        "use strict";
        n.d(e, "a", (function() {
            return r
        }));
        n("a481"),
        n("28a5");
        var o = n("ed08");
        function r() {
            var t = arguments.length > 0 && void 0 !== arguments[0] ? arguments[0] : {}
              , e = arguments.length > 1 && void 0 !== arguments[1] ? arguments[1] : {}
              , n = e.showZeroWhenNoDot
              , r = void 0 !== n && n
              , i = a(t, "award_type")
              , c = a(t, "award_name")
              , u = a(t, "award_desc")
              , s = a(t, "award_start_time")
              , m = a(t, "award_end_time")
              , d = a(t, "coupon_discount_type")
              , l = a(t, "coupon_discount_value")
              , p = a(t, "coupon_discount_price")
              , f = a(t, "coupon_value")
              , h = a(t, "award_value")
              , g = a(t, "third_part_page_url") || a(t, "jump_url") || a(t, "coupon_target") || a(t, "target");
            if (h && (h = 100 * parseFloat(h)),
            1 !== i && 4 !== i)
                return null ;
            var v = {
                type: i,
                name: c,
                desc: u,
                startTimer: new o["j"](s),
                endTimer: new o["j"](m),
                value: {},
                bottom: null ,
                jumpUrl: g,
                originData: t
            };
            if (1 === v.type) {
                if (0 === d || 1 === d ? v.bottom = {
                    text: "无门槛",
                    type: 1
                } : 2 === t.couponDiscountType && t.couponBottomPrice > 0 && (v.bottom = {
                    text: "满¥".concat(t.couponBottomPrice / 100, "可用"),
                    bottomValue: t.couponBottomPrice,
                    cutValue: t.couponValue / 100,
                    type: 2
                }),
                1 === d || 3 === d)
                    v.value.type = 1,
                    v.value.desc = "".concat(l / 100, "折"),
                    v.value.amount = l / 100,
                    v.value.amountDeco = [{
                        type: 0,
                        val: l / 100
                    }, {
                        type: 1,
                        val: "折"
                    }];
                else if (0 === d || 2 === d) {
                    v.value.type = 2,
                    v.value.desc = "¥".concat(f / 100),
                    v.value.amount = f / 100;
                    var w = v.value.amount.toFixed(2).split(".");
                    v.value.amountDeco = [{
                        type: 2,
                        val: "¥"
                    }, {
                        type: 0,
                        val: w[0]
                    }, {
                        type: 3,
                        val: "."
                    }, {
                        type: 4,
                        val: "".concat(w[1])
                    }],
                    r || "00" !== w[1] || (v.value.amountDeco.pop(),
                    v.value.amountDeco.pop())
                } else {
                    if (4 !== d)
                        return console.log("此奖品渲染出错(couponDiscountType类型错误):", v),
                        null ;
                    v.value.type = 3,
                    v.value.desc = "".concat(p / 100, "元购"),
                    v.value.amount = p / 100,
                    v.value.amountDeco = [{
                        type: 0,
                        val: v.value.amount
                    }, {
                        type: 5,
                        val: "元购"
                    }]
                }
                v.jumpUrl || (v.jumpUrl = "https://m.xiaomiyoupin.com/coupon")
            }
            if (4 === v.type) {
                v.value.type = 2,
                v.value.amount = (h || f) / 100;
                var b = v.value.amount.toFixed(2).split(".");
                v.value.desc = "¥".concat(v.value.amount),
                v.value.amountDeco = [{
                    type: 2,
                    val: "¥"
                }, {
                    type: 0,
                    val: b[0]
                }, {
                    type: 3,
                    val: "."
                }, {
                    type: 4,
                    val: "".concat(b[1])
                }],
                r || "00" !== b[1] || (v.value.amountDeco.pop(),
                v.value.amountDeco.pop())
            }
            return v.jumpUrl || (v.jumpUrl = "https://m.xiaomiyoupin.com/r/redenvelope"),
            v.value.amount ? v : (console.log("此奖品渲染出错(券金额计算错误):", v),
            null )
        }
        function a(t, e) {
            function n(t) {
                return t.replace(/_(\w)/g, (function(t, e) {
                    return e.toUpperCase()
                }))
            }
            var o = n(e);
            return void 0 !== t[e] ? t[e] : void 0 !== t[o] ? t[o] : void 0
        }
    },
    b893: function(t, e, n) {
        "use strict";
        n.d(e, "i", (function() {
            return r
        })),
        n.d(e, "g", (function() {
            return a
        })),
        n.d(e, "c", (function() {
            return i
        })),
        n.d(e, "e", (function() {
            return c
        })),
        n.d(e, "d", (function() {
            return u
        })),
        n.d(e, "f", (function() {
            return s
        })),
        n.d(e, "h", (function() {
            return m
        })),
        n.d(e, "b", (function() {
            return d
        })),
        n.d(e, "j", (function() {
            return l
        })),
        n.d(e, "a", (function() {
            return p
        }));
        n("28a5"),
        n("ac6a"),
        n("5df3");
        var o = n("4538");
        function r() {
            var t = Array.prototype.slice.call(arguments)
              , e = t.map((function(t) {
                return new Promise((function(e) {
                    var n = new Image;
                    n.src = t,
                    n.onload = function() {
                        var t = n.naturalWidth
                          , o = n.naturalHeight;
                        e({
                            naturalHeight: o,
                            naturalWidth: t
                        })
                    }
                }
                ))
            }));
            return Promise.all(e)
        }
        function a(t) {
            var e = /^1[0-9]{10}$/;
            return e.test("".concat(t))
        }
        function i(t) {
            var e = arguments.length > 1 && void 0 !== arguments[1] ? arguments[1] : 0
              , n = arguments.length > 2 && void 0 !== arguments[2] ? arguments[2] : 0;
            if (t) {
                var r = Object(o["getSpmFromCD"])(e, n);
                t = Object(o["addParam"])(t, "spmref", r),
                Object(o["jumpTo"])(t)
            }
        }
        function c(t, e) {
            t && (t = Object(o["addParam"])(t, "miniprogramurl", encodeURIComponent("/pages/detail/detail?gid=".concat(e))),
            Object(o["jumpTo"])(t))
        }
        function u(t, e, n) {
            t && (t = Object(o["addParam"])(t, "miniprogramurl", encodeURIComponent("/pages/groupbuy/groupbuy?gid=".concat(e, "&cid=").concat(n))),
            Object(o["jumpTo"])(t))
        }
        function s(t) {
            t && (t = Object(o["addParam"])(t, "miniprogramurl", encodeURIComponent("/pages/coupon/coupon")),
            Object(o["jumpTo"])(t))
        }
        function m(t) {
            try {
                var e = JSON.parse(t);
                return e
            } catch (n) {
                return Object(o["toast"])("error json str: ".concat(t)),
                console.log("error json str: ".concat(t)),
                null
            }
        }
        var d = function(t, e) {
            t = t || "";
            for (var n = {}, o = t.substring(t.indexOf("?") + 1, t.length).split("&"), r = 0, a = o.length; r < a; r++) {
                var i = o[r]
                  , c = i.split("=");
                n[c[0]] = c[1]
            }
            return n[e] || ""
        }
          , l = function(t) {
            return new Promise((function(e, n) {
                var o = new Image;
                o.crossOrigin = "anonymous",
                o.src = "".concat(t, "?v=").concat(Math.random()),
                o.onload = function() {
                    var t = document.createElement("canvas");
                    t.width = this.naturalWidth,
                    t.height = this.naturalHeight,
                    t.getContext("2d").drawImage(o, 0, 0);
                    var n = t.toDataURL("image/jpeg", .9);
                    e(n)
                }
                ,
                o.onerror = function(t) {
                    n(new Error(t))
                }
            }
            ))
        }
          , p = function() {
            return new Promise((function(t) {
                o["ua"].miniprogram ? o["args"].serviceToken ? t(!0) : t(!1) : Object(o["getLogin"])().then((function(e) {
                    return t(!!e)
                }))
            }
            ))
        }
    },
    ed08: function(t, e, n) {
        "use strict";
        n.d(e, "B", (function() {
            return g
        })),
        n.d(e, "v", (function() {
            return v
        })),
        n.d(e, "f", (function() {
            return i
        })),
        n.d(e, "d", (function() {
            return c
        })),
        n.d(e, "e", (function() {
            return u
        })),
        n.d(e, "g", (function() {
            return s
        })),
        n.d(e, "a", (function() {
            return m
        })),
        n.d(e, "l", (function() {
            return d
        })),
        n.d(e, "j", (function() {
            return O
        })),
        n.d(e, "i", (function() {
            return S
        })),
        n.d(e, "c", (function() {
            return T
        })),
        n.d(e, "b", (function() {
            return _
        })),
        n.d(e, "h", (function() {
            return P
        })),
        n.d(e, "k", (function() {
            return x
        })),
        n.d(e, "m", (function() {
            return M
        })),
        n.d(e, "x", (function() {
            return D["i"]
        })),
        n.d(e, "u", (function() {
            return D["g"]
        })),
        n.d(e, "q", (function() {
            return D["c"]
        })),
        n.d(e, "s", (function() {
            return D["e"]
        })),
        n.d(e, "r", (function() {
            return D["d"]
        })),
        n.d(e, "t", (function() {
            return D["f"]
        })),
        n.d(e, "w", (function() {
            return D["h"]
        })),
        n.d(e, "p", (function() {
            return D["b"]
        })),
        n.d(e, "A", (function() {
            return D["j"]
        })),
        n.d(e, "o", (function() {
            return D["a"]
        })),
        n.d(e, "n", (function() {
            return k
        })),
        n.d(e, "C", (function() {
            return C
        })),
        n.d(e, "D", (function() {
            return A
        })),
        n.d(e, "y", (function() {
            return q
        })),
        n.d(e, "z", (function() {
            return F
        }));
        var o = n("4538")
          , r = (n("a481"),
        "".concat(location.protocol, "//").concat(location.host, "/app/shop/login"),
        "".concat(location.protocol, "//").concat(location.host, "/app/shop/logout"),
        location.host.replace(/^st\./, ""))
          , a = "".concat(location.protocol, "//").concat(r, "/api/auth/login/wxlogin")
          , i = "https://m.youpin.mi.com/main"
          , c = "https://m.youpin.mi.com/coupon"
          , u = "https://m.youpin.mi.com/detail"
          , s = "https://m.youpin.mi.com/app/shop/pages/2018/act/newUser/index.html"
          , m = "https://app.xiaomiyoupin.com/allCommentList"
          , d = "https://m.youpin.mi.com/app/shop/content?id=s61bd7039bcb36cb5"
          , l = "wechatMiLogin"
          , p = window
          , f = p.localStorage
          , h = p.history;
        f.getItem(l) && (h.pushState(null , null , location.href),
        window.onpopstate = function() {
            WeixinJSBridge.call("closeWindow")
        }
        ,
        f.removeItem(l));
        var g = function() {
            return new Promise((function(t, e) {
                Object(o["getLogin"])().then((function(n) {
                    n ? t() : (v(),
                    e())
                })).catch((function() {
                    v(),
                    e()
                }))
            }
            ))
        }
          , v = function() {
            if (o["ua"].wechat && !o["ua"].wxminiprogram) {
                try {
                    f.setItem(l, !0)
                } catch (e) {}
                var t = Object(o["addParam"])(a, "followup", encodeURIComponent(location.href));
                Object(o["jumpTo"])(t, {
                    replace: !0
                })
            } else
                Object(o["jumptoLogin"])()
        }
          , w = n("d225")
          , b = n("b0b4");
        function y(t) {
            var e = Math.abs(parseInt(t))
              , n = e < 10 ? "0".concat(e) : "".concat(e);
            return t < 0 ? "-".concat(n) : n
        }
        function j() {
            var t = arguments.length > 0 && void 0 !== arguments[0] ? arguments[0] : 0
              , e = window.__timestamp__ || Math.round(Date.now() / 1e3)
              , n = new Date(1e3 * e).setHours(0, 0, 0, 0)
              , o = Math.round(new Date(n) / 1e3);
            return o += 86400 * t,
            o
        }
        window.__timestamp__ = Math.round(Date.now() / 1e3),
        setInterval((function() {
            return window.__timestamp__++
        }), 1e3);
        var O = function() {
            function t(e) {
                if (Object(w["a"])(this, t),
                "number" !== typeof e || e < 0)
                    return {};
                var n = 1e3 * parseInt(e || 0)
                  , o = j()
                  , r = j(-1)
                  , a = j(1)
                  , i = new Date(n);
                this.raw = e,
                this.year = "".concat(i.getFullYear()),
                this.month = y(i.getMonth() + 1),
                this.date = y(i.getDate()),
                this.day = Math.floor(e / 86400),
                this.hour = y(i.getHours()),
                this.minute = y(Math.floor(e % 3600 / 60)),
                this.second = y(e % 60),
                this.dateStr = "".concat(this.year, ".").concat(this.month, ".").concat(this.date);
                var c = this.dateStr;
                c = e >= a ? "".concat(Math.ceil((e - o) / 86400), "天后") : e >= o ? "今天" : e >= r ? "昨天" : "".concat(Math.ceil((o - e) / 86400), "天前"),
                this.descDate = c,
                this.timeStr = "".concat(this.hour, ":").concat(this.minute),
                this.timeSecStr = "".concat(this.hour, ":").concat(this.minute, ":").concat(this.second),
                this.relativeDateOrTime = "今天" === c ? this.timeStr : this.descDate
            }
            return Object(b["a"])(t, [{
                key: "trimMonth",
                value: function() {
                    this.month = parseInt(this.month) + ""
                }
            }, {
                key: "trimDate",
                value: function() {
                    this.date = parseInt(this.date) + ""
                }
            }]),
            t
        }()
          , S = function t(e) {
            if (Object(w["a"])(this, t),
            "number" !== typeof e || e < 0)
                return {};
            this.raw = e,
            this.day = Math.floor(e / 86400),
            this.hour = y(Math.floor(e % 86400 / 3600)),
            this.minute = y(Math.floor(e % 3600 / 60)),
            this.second = y(e % 60)
        }
          , T = "https://img.youpin.mi-img.com/editor1/691b9dcf87053971048312b7de06374f.png?w=79&h=79"
          , _ = "https://shop.io.mi-img.com/app/shop/img?id=shop_a5651ea382cedab9ae843b823ada7945.png&w=120&h=120"
          , P = "https://app.xiaomiyoupin.com/youpin/static/m/res/images/device_shop_right_arrow.png"
          , x = "https://app.xiaomiyoupin.com/youpin/static/m/res/images/evaluation_btn_level.a_sel_light.png"
          , M = "https://img.youpin.mi-img.com/editor1/37518693d48ac5508dc96cbcd5941fe2.png?w=1080&h=1920"
          , D = n("b893")
          , I = function(t) {
            requestAnimationFrame ? requestAnimationFrame(t) : setTimeout(t, 34)
        }
          , k = function() {
            return window.pageYOffset ? window.pageYOffset : document.documentElement && document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop ? document.body.scrollTop : 0
        }
          , C = function() {
            return "CSS1Compat" === document.compatMode ? document.documentElement.clientHeight : document.body.clientHeight
        }
          , A = function() {
            return "CSS1Compat" === document.compatMode ? document.documentElement.clientWidth : document.body.clientWidth
        }
          , E = function() {
            return void 0 !== document.height ? document.height : document.body.offsetHeight
        }
          , U = function() {
            return E() - C()
        }
          , N = function(t) {
            var e = t.getBoundingClientRect();
            return e.top
        }
          , W = function(t, e) {
            var n = .2;
            return new Promise((function(o) {
                function r(t, e) {
                    var a = parseFloat(e) - parseFloat(t)
                      , i = Math.abs(a) <= .5;
                    if (i)
                        return window.scrollTo(0, e),
                        void o();
                    t = parseFloat(t) * (1 - n) + parseFloat(e) * n,
                    window.scrollTo(0, Math.round(t)),
                    I((function() {
                        return r(t, e)
                    }))
                }
                r(t, e)
            }
            ))
        }
          , q = function(t) {
            var e = arguments.length > 1 && void 0 !== arguments[1] ? arguments[1] : 10
              , n = k() + N(t) - e
              , o = k()
              , r = U();
            return n > r && (n = r),
            W(o, n)
        }
          , F = function(t) {
            if (!t)
                return window.scrollTo(0, 0),
                Promise.resolve();
            var e = 0
              , n = k()
              , o = U();
            return e > o && (e = o),
            W(n, e)
        }
    },
    f3e4: function(t, e, n) {
        "use strict";
        n.d(e, "b", (function() {
            return o
        })),
        n.d(e, "a", (function() {
            return a
        }));
        n("4917"),
        n("3b2b");
        function o(t, e) {
            var n = 30
              , o = new Date;
            o.setTime(o.getTime() + 24 * n * 60 * 60 * 1e3),
            document.cookie = t + "=" + e + ";expires=" + o.toGMTString() + ";path=/"
        }
        function r(t) {
            var e = new RegExp("(^| )" + t + "=([^;]*)(;|$)")
              , n = document.cookie.match(e);
            return n ? unescape(n[2]) : null
        }
        function a(t) {
            var e = new Date;
            e.setTime(e.getTime() - 36e5);
            var n = r(t);
            null !== n && (document.cookie = t + "=" + n + ";expires=" + e.toGMTString() + ";domain=.xiaomiyoupin.com")
        }
    },
    f78e: function(t, e, n) {
        "use strict";
        e["a"] = "67,86,20,72,66,8,61,18,102,71,88,10,43,50,24,55,28,63,94,21,4,12,47,73,90,26,35,58,40,51,0,78"
    },
    f8dd: function(t, e, n) {
        "use strict";
        var o = n("6f4f")
          , r = n.n(o)
          , a = new r.a;
        e["a"] = a
    },
    f9bc: function(t, e, n) {
        "use strict";
        var o = n("7618")
          , r = (n("55dd"),
        n("19e7"))
          , a = n.n(r)
          , i = n("48ee")
          , c = n("3a71")
          , u = n("f78e")
          , s = {
            c: function(t) {
                var e = i["a"].getServerTime()
                  , n = Math.round(1e9 * Math.random())
                  , o = a.a.hash([e, n, s.create(t), Object(c["a"])(u["a"])].join("&"))
                  , r = {};
                return r[Object(c["a"])("4,12,106,10,14,29")] = e,
                r[Object(c["a"])("4,12,106,10,14,10")] = n,
                r[Object(c["a"])("4,12,106,10,10")] = o,
                r
            },
            create: function(t) {
                var e = s.toCharArray(JSON.stringify(s.removeNull(t)))
                  , n = e.sort();
                return n = n.join(""),
                n
            },
            toCharArray: function(t) {
                for (var e = new Array(t.length), n = 0; n < t.length; n++)
                    e[n] = t.charAt(n);
                return e
            },
            removeNull: function(t) {
                if (t) {
                    for (var e in t)
                        null !== t[e] ? "object" === Object(o["a"])(t[e]) && s.removeNull(t[e]) : delete t[e];
                    return t
                }
            }
        };
        e["a"] = s
    },
    fa7d: function(t, e, n) {
        "use strict";
        n("4917"),
        n("6b54"),
        n("a481"),
        n("aef6"),
        n("c5f6")
    }
}]);
