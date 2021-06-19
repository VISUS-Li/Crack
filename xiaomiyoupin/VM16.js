(function() {

    if (document.domain == ("m.mi.com")) {
        setTimeout(function(){
            var  head = document.head || document.getElementsByTagName("head")[0];
            var  csstext=".fixed-header, .header{display:none !important;}";
            var  style = document.createElement("style");
            style.type = "text/css";
            head.appendChild(style);
            style.innerHTML=csstext;
        } ,150)
    }
    if (document.domain == ("api.ucashier.mipay.com")) {
        setTimeout(function(){
            var  head = document.head || document.getElementsByTagName("head")[0];
            var csstext=".form-control.bottom-fixed{position:static !important;margin-top:30px}";
            var  style = document.createElement("style");
            style.type = "text/css";
            head.appendChild(style);
            style.innerHTML=csstext;
        } ,150)
    }
    if (document.domain == ("m.mi.com")) {
        window.onhashchange=function(){
            if (location.hash.indexOf("/cart/index") > 0 || location.hash.indexOf("/shopping") > 0 || location.hash.indexOf("/index") > 0) {
                location.href = "https://m.xiaomiyoupin.com/jump?source=" + encodeURIComponent(location.href);
            }
        };
    }
    
    
    window._MiHomeStore={platform:'android', rnMakeTime: '20210323224350', appVersion: '4.11.0', statusBarHeight: 40, injectJSVersion: '1.0.0'};
    window.rnMakeTime=20210323224350;
    window.appVersion='4.11.0';
    window.statusBarHeight=40;

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
    function showShareIcon(data){
        if(typeof data == 'object'){
            var s= JSON.stringify(data);
            rnSendWebEvent('showShareIconJson',s);
        }else if(typeof data =='string'){
            rnSendWebEvent('showShareIconString',data);
        }
    }
    setTimeout(function(){
        if (document.title) {
            rnSendWebEvent('titleChanged',document.title);
        }
    },400);
    function showShareView(data) {
        if (data) {
            var s= JSON.stringify(data);
            rnSendWebEvent('showShareView',s);
        }
    }
    function shareByChannel(data) {
        if (data) {
            var s= JSON.stringify(data);
            rnSendWebEvent('shareByChannel',s);
        }
    }
    function checkCameraAccess(data) {
        if (typeof data === 'boolean') {
            rnSendWebEvent('checkCameraAccess', data);
        }
    }
    function getActSalt(data) {
      if (data) {
          var s= JSON.stringify(data);
          rnSendWebEvent('getActSalt', s);
      }
  }

    window._MiHomeStore.showShareView=showShareView;
    window._MiHomeStore.showShareIcon=showShareIcon;
    window._MiHomeStore.shareByChannel=shareByChannel;
    window._MiHomeStore.checkCameraAccess=checkCameraAccess;
    window._MiHomeStore.getActSalt=getActSalt;
    window._MiHomeStore.rnSendWebEvent=rnSendWebEvent;
    window._MiHomeStore.rnSendWebEventOnMessage=rnSendWebEventOnMessage;
    window._MiHomeStore.jsFunctionMap={"showShareView2":1,"showShareIcon2Json":1,"showShareIcon2String":1,"reportStat":1,"showToast":1,"onBackPress":1,"onCloseWeb":1,"shareToPyqWithImage":1,"insertEventToCalendar":1,"saveImageToLocal":1,"isRn54":1,"resetShareImageData":1,"pushShareImageData":1,"openNewWeb":1,"showInputModal":1,"onCheckIMPress":1,"shareByChannel":1,"checkCameraAccess":1,"getActSalt":1,"webPaySuccess":1};
;
})();