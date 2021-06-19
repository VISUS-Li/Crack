
/*****获取商品详情页面(不用登录)*****/
//request:
POST https://shopapi.io.mi.com/api/gateway/detail HTTP/1.1
user-agent: Dalvik/2.1.0 (Linux; U; Android 5.1.1; WLZ-AN00 Build/LMY49I)Mobile MIOTWeex/2.0.2 (YouPin;4.10.0;41D70D966E115AB4B99EB4BD9320E0CD;0.20.1;A;A54FF940741271417BCC377D91887868D6E932B8;Wandoujia;NFAfERt6rN5PrPVL;) MIOTStore/20191212 (YouPin;4.10.0;41D70D966E115AB4B99EB4BD9320E0CD;20210508204259;A;A54FF940741271417BCC377D91887868D6E932B8;Wandoujia;NFAfERt6rN5PrPVL;)
ua-pixels: 1080x1920
x-yp-app-source: front-RN-old
x-user-agent: channel/youpin platform/youpin.android smDeviceId/20210320155628a14a56e65fb5befd644fdb95212f51c201843ddbf74ef6c8
dtoken: 
referer: https://shopapi.io.mi.com
Content-Type: application/json
Content-Length: 108
Host: shopapi.io.mi.com
Connection: Keep-Alive
Accept-Encoding: gzip
Cookie: 
    cUserId=giFmEITsAjTrWSiOKVfW5HoIuSk; 
    serviceToken=OkCwa0RNCBmodebQU8t9LpJup9wMbsps5dGZJ7/d5gx/idVOoahpPdQyVXBasQ4+hF7ErJRoBQhBQGEbFzsdEZQgYvaNTU0bqZEAH6CJzrl6mqyOxnJr/2MXLT4M2EgoXSlasAcf4a5YlxgWo2q62w==; 
    cUserId=giFmEITsAjTrWSiOKVfW5HoIuSk; 
    youpin_sessionid=1620734128212_688985550; 
    userId=1517309208; 
    masid=101.000; 
    client_id=180100031044; 
    jc

{"groupName":"details","groupParams":[["135927"]],"methods":[],"version":"1.0.0","debug":false,"channel":""}

//response:
HTTP/1.1 200 OK
Server: nginx
Date: Wed, 12 May 2021 01:30:24 GMT
Content-Type: application/json
Connection: keep-alive
Vary: Accept-Encoding
Content-Length: 22425

{"code":0,"message":"ok","channel":"","version":"1.0.0","serverTime":1620783024,"orgData":null,"data":{"address":null,"gid":135927,"activity":{"gidAct":{"actType":"","actInfo":{},"salePromotion":[],"salePromotionPreview":[],"couponDetailCheckoutInfo":null,"photoAtmosphereInfo":null},"pidAct":{"253309":{"actType":"","actInfo":{},"salePromotion":[],"salePromotionPreview":[],"couponDetailCheckoutInfo":null,"photoAtmosphereInfo":null}}},"youpinLogo":{"needYoupinLogo":1,"youpinLogoUrl":"https://img.youpin.mi-img.com/editor1/ce497b9d0341ac785d77e343dddab7e7.png?w=1080&h=111"},"viewRecord":null,"couponsInfo":{"gidCoupons":{"fetchableCoupons":[],"ownedCoupons":[]},"pidCoupons":{},"gidMixSortedCoupons":[],"pidMixSortedCoupons":{}},"goods":{"goodsVirtualInfo":[],"shareInfo":{"contentMap":{"pyq":"link","mx":"link","wb":"link","title":"【自营】飞天53%vol 500ml贵州茅台酒（带杯）","wbContent":"贵州茅台酒，酿造高品位生活","pics":"https://api.io.mi.com/app/shop/zimg2?thumb=https%3A%2F%2Fimg.youpin.mi-img.com%2Fshopmain%2F695ee059d7c4048ed35264a182cd9143.png%40base%40tag%3DimgScale%26h%3D350%26w%3D350%26et%3D1%26eth%3D480%26etw%3D480%26etc%3DFFFFFF&pic=https%3A%2F%2Fimg.youpin.mi-img.com%2Fshopmain%2Fb9dc5fa23180870aad33e3ddf2cbf063.jpg%3Fw%3D1080%26h%3D1080","content":"贵州茅台酒，酿造高品位生活","url":"https://m.xiaomiyoupin.com/detail?gid=135927","ml":"link"},"poster":{"title":"【自营】飞天53%vol 500ml贵州茅台酒（带杯）","desc":"贵州茅台酒，酿造高品位生活","img":"https://img.youpin.mi-img.com/shopmain/465ac895e0fad3102dfeeb0c4ecaedd9.jpg?w=800&h=800","price":149900,"priceMore":0,"tag":""}},"carouselMapList":[{"type":0,"url":"https://img.youpin.mi-img.com/shopmain/b9dc5fa23180870aad33e3ddf2cbf063.jpg?w=1080&h=1080"},{"type":0,"url":"https://img.youpin.mi-img.com/shopmain/e88252b001ab399dec7baeb643cd9b82.jpg?w=1080&h=1080"},{"type":0,"url":"https://img.youpin.mi-img.com/shopmain/e1cc0f81e5026ca68077f57a41c90704.jpg?w=1080&h=1080"},{"type":0,"url":"https://img.youpin.mi-img.com/shopmain/3a6833ef980f28b7ba968eb0c4e53bdd.jpg?w=1080&h=1080"},{"type":0,"url":"https://img.youpin.mi-img.com/shopmain/84a1806006beb88f3aea0a153796c3bf.jpg?w=1080&h=1080"}],"goodTypeForButton":1,"shopTags":[{"tid":372,"name":"规格","parentId":null,"rootId":0,"level":1,"oder":0,"cid":0,"visible":1,"tags":[{"tid":933,"name":"500ml","parentId":372,"rootId":0,"level":2,"oder":0,"cid":0,"visible":1,"tags":null}]}],"customSupport":null,"services":{"1":{"type":null,"text":"包邮","serviceStatus":"SUPPORT"},"8":{"type":null,"text":"不支持7天无理由","serviceStatus":"NOT_SUPPORT"},"11":{"type":null,"text":"有品配送","serviceStatus":"SUPPORT"}},"specialPromotionPrice":null,"productInfo":{"253309":{"pid":253309,"gid":135927,"picURL":null,"summary":"贵州茅台酒，酿造高品位生活","name":"飞天53%vol 500ml贵州茅台酒（带杯）","firstTime":1602214500,"latestTime":1619166161,"inventory":99999,"marketPrice":149900,"price":149900,"status":0,"buyLimit":2,"saled":832,"buyURL":"","mapId":0,"refoundPolicyMap":{"description":"不支持7天无理由退货","is_support":false,"policy_id":"0"},"skuId":0,"depot":0,"usePrice":1,"labels":null,"postWeight":0,"proprietor":451,"consignor":451,"afterSaleAgent":451,"brandPrincipalPart":451,"specialPostage":0,"customerServiceAgent":0,"postageType":0,"img":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png?w=800&h=800","img800":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png?w=800&h=800","img800s":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png?w=800&h=800","compressedImg800":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png?w=800&h=800@base@tag=imgScale&w=240&h=240","saleWeight":0,"ypSkuList":[{"skuId":12000010,"pssSkuId":5000010,"count":1}],"service":[1,8,11],"oder":0,"onSale":false,"preDeliveryTime":0,"scheduleOnSaleTime":1759802400,"totalInventory":null,"totalSaled":null,"validate":0,"promotionType":null,"isPromote":false,"saleMode":"YOUPIN_SELF_MARKETING","attributeValues":["500ml"],"tradeModeInfo":{"tradeMode":"NORMAL","startTime":null,"endTime":null,"extra":null},"protectionPrice":null,"youPinDelivery":true,"isVMI":null,"purchasePrice":null,"vmiGoodsInfo":null,"freeShipping":true,"isMFInsurance":null,"isMFInsuranceVMI":null,"freePostageAfterSale":false,"freePostageAfterSaleVMI":null,"mfInsuranceInfos":null,"productBuyLimitInfo":{"productBuyLimit":0,"startTime":0,"endTime":0,"idtype":"PID"},"snapshotVersion":"81381f6879f03f80b3542aae432608f5#1620644993","productAtmosphereList":[],"virtualInfoList":null}},"labels":null,"crowdFunding":null,"aiSupport":{"gidAi":{"isAi":0,"aiType":0,"aiInfo":null},"pidAi":{}},"buySupport":null,"propTags":[{"pid":253309,"tid":933,"oder":0}],"oneYuanSupport":{"isOneYuan":0,"oneYuanInfo":null,"groupBuyInfo":null},"category":{"oldCid1":309,"oldCname1":"内测","oldCid2":478,"oldCname2":"内测","cid1":2146,"cname1":"其他","cid2":2226,"cname2":"其他","cid3":2563,"cname3":"其他","newCid1":23,"newCname1":"生鲜酒水","newCid2":259,"newCname2":"白酒","newCid3":2794,"newCname3":"白酒"},"brand":{"brandName":"茅台","brandId":5388,"brandLogo":"https://img.youpin.mi-img.com/youpinoper/f2f010c43a25900d4b3b61c4540fdb0c.jpeg?w=300&h=300","brandSlogan":"贵州茅台，香飘世界","jumpURL":null,"type":0,"merchantContact":"4001001199","merchantName":"小米有品科技有限公司","merchantAddress":"南京市建邺区白龙江东街8号3栋903","miMerchantId":36476,"merchantQualification":"{\"scope\":\"智能技术研发、技术咨询、技术服务；企业管理咨询；信息技术咨询；仪器仪表维修；办公设备维修；展览展示服务；会议服务；庆典活动组织策划；设计、制作、代理、发布国内各类广告；摄影服务、仓储服务、货运代理、票务代理（不含机票、火车票销售代理）；音像制品、出版物销售（须取得许可或批准后方可经营）；化妆品及卫生用品、文具用品、五金交电、厨房用品、电子产品、视听设备、Ⅰ类Ⅱ类医疗器械、玩具、工艺美术品、服装鞋帽、计生用品、钟表眼镜、针纺织品、陶瓷、玻璃器皿、家用电器、家具、初级农产品、花卉、苗木、动物用清洁剂、种子、照相器材、礼品、计算机硬件、软件及辅助设备、珠宝首饰、宠物食品、摩托车及零部件、体育用品及器材、装饰材料、建筑材料、婴儿用品销售；食品、Ⅲ类医疗器械销售（须取得许可或批准后方可经营）；新能源汽车销售农药销售（须取得许可或批准后方可经营）；自营和代理各类商品及技术的进出口业务。（依法须经批准的项目，经相关部门批准后方可开展经营活动）\",\"expiry_dates\":\"长期\",\"operating_start\":\"-\",\"operating_end\":\"-\"}","miSkillId":"public_3647600001","qualificationPic":null,"merchantShortName":"小米有品科技有限公司","merchantLogo":null,"merchantId":451,"merchantSignKey":null,"merchantDesc":null,"merchantSlogan":null,"merchantPinkage":0,"merchantFreight":0,"merchantPostageDescription":"","merchantStatus":null,"quitNoticePic":null},"goodsInfo":{"gid":135927,"priceMin":149900,"priceTag":false,"marketPrice":149900,"name":"【自营】飞天53%vol 500ml贵州茅台酒（带杯）","shortName":"飞天茅台酒53度","shortSummary":"贵州飞天茅台酒53度","summary":"贵州茅台酒，酿造高品位生活","imgSquare":"https://img.youpin.mi-img.com/shopmain/465ac895e0fad3102dfeeb0c4ecaedd9.jpg?w=800&h=800","imgHorizon":"https://img.youpin.mi-img.com/shopmain/2af244c32c18b44e2c7cabf8b951a29e.jpg?w=1020&h=615","img800":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png?w=800&h=800","img800s":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png?w=800&h=800","jumpUrl":"https://m.xiaomiyoupin.com/detail?gid=135927","pids":[253309],"saleStatus":0,"saleType":"NORMAL","inventory":0,"saleMode":"YOUPIN_SELL","firstTime":1602214500,"latestTime":1619166161,"scheduleOnSaleTime":1759802400,"shareDescMap":{},"isCustom":0,"attrExtMap":{"custom_name":"飞天茅台酒53度","custom_summary":"贵州飞天茅台酒53度","price_tag":0},"imgSafeArea":1,"primaryPid":0,"colorNum":null,"service":[1,8,11],"introExt":[{"id":"","url":"https://m.xiaomiyoupin.com/api/zhaoshang/miGoodsDetailService/get?gid=135927&title=%E4%BA%A7%E5%93%81%E4%BB%8B%E7%BB%8D","title":"产品介绍","imagesArray":["https://img.youpin.mi-img.com/shopmain/99e2fcfff9999076d188e583594798a1.jpg?w=1080&h=1562","https://img.youpin.mi-img.com/shopmain/8892fd77d491d577e5a5b9e69300d3c6.jpg?w=1080&h=1511","https://img.youpin.mi-img.com/shopmain/c8aba667fd8eee33daa7d39b83531a21.jpg?w=1080&h=1917","https://img.youpin.mi-img.com/shopmain/d93b2a62508935692d132082618ab42f.jpg?w=1080&h=875","https://img.youpin.mi-img.com/shopmain/5a8709a9bdd1c76b6398e32066aa5947.jpg?w=1080&h=1348","https://img.youpin.mi-img.com/shopmain/a36eebd4c29b0c4eef64959448d7acf8.jpg?w=1080&h=220","https://img.youpin.mi-img.com/shopmain/02f231215bf746eae134089afa3e7860.jpg?w=1080&h=541","https://img.youpin.mi-img.com/shopmain/22b5d62822d9f4b3e769a581e9c5bdd0.jpg?w=1080&h=541","https://img.youpin.mi-img.com/shopmain/b838bfc854fd6c3d0d7173c72e744b3d.jpg?w=1080&h=542","https://img.youpin.mi-img.com/shopmain/3cd08c09d43b84190825cdab646a8f64.jpg?w=1080&h=973"]},{"id":"","url":"https://m.xiaomiyoupin.com/api/zhaoshang/miGoodsDetailService/get?gid=135927&title=%E5%B8%B8%E8%A7%81%E9%97%AE%E9%A2%98","title":"常见问题","imagesArray":["https://img.youpin.mi-img.com/shopmain/30a4fae60bdf7441e07e30665a75a9aa.jpg?w=1080&h=2117"]}],"evaluateAvg":0,"imgSafeAreaUrl":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png?w=800&h=800","onSale":false,"picUrl":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png@base@tag=imgScale&h=350&w=350&et=1&eth=480&etw=480&etc=FFFFFF","ctime":1600930219,"saled":832,"saledFee":0,"businessId":12,"businessName":"饮食酒水行业运营中心","compressedImg800":"https://img.youpin.mi-img.com/shopmain/695ee059d7c4048ed35264a182cd9143.png?w=800&h=800@base@tag=imgScale&w=240&h=240","platform":64,"youPinDelivery":true,"freeShipping":true,"miSdkId":null,"youPinSelfMarketing":false,"pinkage":null,"specialPostage":null,"pricePrimaryPid":253309,"commentInfo":null,"videoUrl":"","saleAlone":true,"virtual":false}},"cartCount":0,"paySupport":{"gidPay":null,"pidPay":{"253309":null}},"button":{"gidButton":[{"type":2,"text":"商品未开售","url":null,"postcouponPriceText":"","postcouponScm":null}],"pidButton":{"253309":[{"type":2,"text":"商品未开售","url":null,"postcouponPriceText":"","postcouponScm":null}]},"oneYuanButton":null},"isTarget":true,"comment":{"index":{"noshow":null,"avg_score":5.0,"positive_rate":100,"positive":null,"tags":[{"id":"__all__","type":"__all__","name":"全部","count":137109,"category":"good"},{"id":"__img__","type":"__img__","name":"有图","count":9297,"category":"good"},{"id":"__append__","type":"__append__","name":"追评","count":786,"category":"good"},{"id":"__good__","type":"__good__","name":"好评","count":15158,"category":"good"},{"id":"6188b708ddf05a72be74a05bb357ff65","type":"6188b708ddf05a72be74a05bb357ff65","name":"价格实惠","count":13763,"category":"good"},{"id":"2d2858070fbedeed73102ece4cb9bd92","type":"2d2858070fbedeed73102ece4cb9bd92","name":"服务一流","count":11993,"category":"good"},{"id":"9d597c7af5cfbadca732d26a49d08ec8","type":"9d597c7af5cfbadca732d26a49d08ec8","name":"清香扑鼻","count":516,"category":"good"},{"id":"222ce29a3b1728e0c663a84ef65ad4ba","type":"222ce29a3b1728e0c663a84ef65ad4ba","name":"口感俱佳","count":6564,"category":"good"},{"id":"84f8dff8b903fb07c2ddcb069b2dfe51","type":"84f8dff8b903fb07c2ddcb069b2dfe51","name":"质量上乘","count":1055,"category":"good"},{"id":"058de61d1de4a6cceba8303d15ee11f6","type":"058de61d1de4a6cceba8303d15ee11f6","name":"运输速度快","count":116,"category":"good"},{"id":"7469df067d15d68342d004fd7a8f9975","type":"7469df067d15d68342d004fd7a8f9975","name":"效果显著","count":69,"category":"good"},{"id":"20c5eb3359d40f416e0f406e00529e1b","type":"20c5eb3359d40f416e0f406e00529e1b","name":"入口顺滑","count":430,"category":"good"},{"id":"74ecf45c7ad4b7e72e23b40ddb3c4731","type":"74ecf45c7ad4b7e72e23b40ddb3c4731","name":"品相一流","count":10,"category":"good"},{"id":"39b7cfe55e46327b20236e0c81721a60","type":"39b7cfe55e46327b20236e0c81721a60","name":"日期新鲜","count":89,"category":"good"}],"total_count":137109,"effective_count":0,"folding_count":0,"bigdata_meta":null},"content":[{"uid":null,"pid":253309,"score":5,"ctime":1617633302,"comment_id":38552410,"pics":["https://img.youpin.mi-img.com/comment/fb9d74c1626b41822373bded0c44bffe.jpg?w=500&h=667","https://img.youpin.mi-img.com/comment/2dfcb63b180246649d43f9acbef0f2dd.jpg?w=500&h=552"],"comment_imgs":[{"img":"https://img.youpin.mi-img.com/comment/fb9d74c1626b41822373bded0c44bffe.jpg?w=500&h=667","thumbnail":"https://img.youpin.mi-img.com/comment/fb9d74c1626b41822373bded0c44bffe.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/2dfcb63b180246649d43f9acbef0f2dd.jpg?w=500&h=552","thumbnail":"https://img.youpin.mi-img.com/comment/2dfcb63b180246649d43f9acbef0f2dd.jpg@base@tag=imgScale&h=200&w=200"}],"text":"非常好的酒，包装保护很到位，酒瓶没有任何磕碰等问题。快递员也很细心。 特别幸运能抢到好酒！感谢能让我买到好酒！！谢谢小米有品，质量上乘，希望能再给一瓶，永远的米粉，家里用的都是小米的品牌，哈哈，质量好","txt":"非常好的酒，包装保护很到位，酒瓶没有任何磕碰等问题。快递员也很细心。 特别幸运能抢到好酒！感谢能让我买到好酒！！谢谢小米有品，质量上乘，希望能再给一瓶，永远的米粉，家里用的都是小米的品牌，哈哈，质量好","is_feature":false,"pid_name":null,"pid_spec":null,"avatar":"https://cdn.cnbj1.fds.api.mi-img.com/user-avatar/f49eddb9-0bce-420b-9f5f-fd1c2eb05e6a.jpg","nick_name":"姚*坤"},{"uid":null,"pid":253309,"score":5,"ctime":1618311036,"comment_id":39207256,"pics":["https://img.youpin.mi-img.com/comment/30a763fd4270504f632091e9fffb525d.jpg?w=864&h=1280","https://img.youpin.mi-img.com/comment/0ec9f391487d75095b9657519f5edadb.jpg?w=864&h=1280","https://img.youpin.mi-img.com/comment/68419b5e6a0da9bdac0d80abdf1527f7.jpg?w=864&h=1280","https://img.youpin.mi-img.com/comment/acc3506874a0c850cc40f82026277c2b.jpg?w=864&h=1280","https://img.youpin.mi-img.com/comment/1a694a86eab5b36e7defdeb823e6c63c.jpg?w=1080&h=1440","https://img.youpin.mi-img.com/comment/7fba6f64babb52acc972910943bd125e.jpg?w=1080&h=1440"],"comment_imgs":[{"img":"https://img.youpin.mi-img.com/comment/30a763fd4270504f632091e9fffb525d.jpg?w=864&h=1280","thumbnail":"https://img.youpin.mi-img.com/comment/30a763fd4270504f632091e9fffb525d.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/0ec9f391487d75095b9657519f5edadb.jpg?w=864&h=1280","thumbnail":"https://img.youpin.mi-img.com/comment/0ec9f391487d75095b9657519f5edadb.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/68419b5e6a0da9bdac0d80abdf1527f7.jpg?w=864&h=1280","thumbnail":"https://img.youpin.mi-img.com/comment/68419b5e6a0da9bdac0d80abdf1527f7.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/acc3506874a0c850cc40f82026277c2b.jpg?w=864&h=1280","thumbnail":"https://img.youpin.mi-img.com/comment/acc3506874a0c850cc40f82026277c2b.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/1a694a86eab5b36e7defdeb823e6c63c.jpg?w=1080&h=1440","thumbnail":"https://img.youpin.mi-img.com/comment/1a694a86eab5b36e7defdeb823e6c63c.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/7fba6f64babb52acc972910943bd125e.jpg?w=1080&h=1440","thumbnail":"https://img.youpin.mi-img.com/comment/7fba6f64babb52acc972910943bd125e.jpg@base@tag=imgScale&h=200&w=200"}],"text":"失去什么都别失去前进的勇气，感谢有品平台 让我喝到平价茅台 希望平台越做越好。价格实惠，服务一流，清香扑鼻，入口顺滑，运输速度快，质量上乘，价格实惠，运输速度快，服务一流，清香扑鼻，效果显著，口感俱佳","txt":"失去什么都别失去前进的勇气，感谢有品平台 让我喝到平价茅台 希望平台越做越好。价格实惠，服务一流，清香扑鼻，入口顺滑，运输速度快，质量上乘，价格实惠，运输速度快，服务一流，清香扑鼻，效果显著，口感俱佳","is_feature":false,"pid_name":null,"pid_spec":null,"avatar":"https://cdn.cnbj1.fds.api.mi-img.com/user-avatar/04927f47-70de-4c0a-84ce-4aab0cc76a55.jpg","nick_name":"c**s"},{"uid":null,"pid":253309,"score":5,"ctime":1617637166,"comment_id":38554380,"pics":["https://img.youpin.mi-img.com/comment/65cb142eafe81429ac92af59bfca3a85.jpg?w=1080&h=2400"],"comment_imgs":[{"img":"https://img.youpin.mi-img.com/comment/65cb142eafe81429ac92af59bfca3a85.jpg?w=1080&h=2400","thumbnail":"https://img.youpin.mi-img.com/comment/65cb142eafe81429ac92af59bfca3a85.jpg@base@tag=imgScale&h=200&w=200"}],"text":"第一次在小米有品抢到了一瓶茅台！感谢感谢！\n还送了袋子和验酒器！\n客服说30天内能抢两瓶，希望这个月能够抢到第二瓶！\n价格实惠，服务一流，清香扑鼻，口感俱佳，质量上乘，运输速度快，效果显著，入口顺滑！","txt":"第一次在小米有品抢到了一瓶茅台！感谢感谢！\n还送了袋子和验酒器！\n客服说30天内能抢两瓶，希望这个月能够抢到第二瓶！\n价格实惠，服务一流，清香扑鼻，口感俱佳，质量上乘，运输速度快，效果显著，入口顺滑！","is_feature":false,"pid_name":null,"pid_spec":null,"avatar":"","nick_name":"莫**年穷"},{"uid":null,"pid":253309,"score":5,"ctime":1617697270,"comment_id":38641732,"pics":["https://img.youpin.mi-img.com/comment/144cf9c299b6bac01372cdf97e18cddd.jpg?w=888&h=1973","https://img.youpin.mi-img.com/comment/b1e624f353385f8f8148d62840e51e32.jpg?w=888&h=1973","https://img.youpin.mi-img.com/comment/7b66e231cc830fd0cbc31ffd48922a0b.jpg?w=986&h=444"],"comment_imgs":[{"img":"https://img.youpin.mi-img.com/comment/144cf9c299b6bac01372cdf97e18cddd.jpg?w=888&h=1973","thumbnail":"https://img.youpin.mi-img.com/comment/144cf9c299b6bac01372cdf97e18cddd.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/b1e624f353385f8f8148d62840e51e32.jpg?w=888&h=1973","thumbnail":"https://img.youpin.mi-img.com/comment/b1e624f353385f8f8148d62840e51e32.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/7b66e231cc830fd0cbc31ffd48922a0b.jpg?w=986&h=444","thumbnail":"https://img.youpin.mi-img.com/comment/7b66e231cc830fd0cbc31ffd48922a0b.jpg@base@tag=imgScale&h=200&w=200"}],"text":"第七次过来评价，还是感谢小米生生不息息息相关关怀备至！非常荣幸又抢到，美滋滋，还是20年的酒，而且一瓶还送袋子、验酒器，越来越周到了！品相完美，快递速度，主要是舒服，小米出品无可挑剔，祝愿小米越做越好","txt":"第七次过来评价，还是感谢小米生生不息息息相关关怀备至！非常荣幸又抢到，美滋滋，还是20年的酒，而且一瓶还送袋子、验酒器，越来越周到了！品相完美，快递速度，主要是舒服，小米出品无可挑剔，祝愿小米越做越好","is_feature":false,"pid_name":null,"pid_spec":null,"avatar":"https://cdn.cnbj1.fds.api.mi-img.com/user-avatar/aa015e3e-4787-452e-8351-edf352910dd3.jpg","nick_name":"小**钱"},{"uid":null,"pid":253309,"score":5,"ctime":1617628465,"comment_id":38549232,"pics":["https://img.youpin.mi-img.com/comment/877d8664413a49123d45e961aeab68b9.jpg?w=1000&h=1333","https://img.youpin.mi-img.com/comment/8ffc3f8815adeaaf0b4bc3e18521147f.jpg?w=1000&h=1333","https://img.youpin.mi-img.com/comment/8035759a87ae9161a8c463152638a15f.jpg?w=1000&h=1333","https://img.youpin.mi-img.com/comment/7427c868217d440dc9c04fe819faa144.jpg?w=1000&h=1333"],"comment_imgs":[{"img":"https://img.youpin.mi-img.com/comment/877d8664413a49123d45e961aeab68b9.jpg?w=1000&h=1333","thumbnail":"https://img.youpin.mi-img.com/comment/877d8664413a49123d45e961aeab68b9.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/8ffc3f8815adeaaf0b4bc3e18521147f.jpg?w=1000&h=1333","thumbnail":"https://img.youpin.mi-img.com/comment/8ffc3f8815adeaaf0b4bc3e18521147f.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/8035759a87ae9161a8c463152638a15f.jpg?w=1000&h=1333","thumbnail":"https://img.youpin.mi-img.com/comment/8035759a87ae9161a8c463152638a15f.jpg@base@tag=imgScale&h=200&w=200"},{"img":"https://img.youpin.mi-img.com/comment/7427c868217d440dc9c04fe819faa144.jpg?w=1000&h=1333","thumbnail":"https://img.youpin.mi-img.com/comment/7427c868217d440dc9c04fe819faa144.jpg@base@tag=imgScale&h=200&w=200"}],"text":"茅台酒作为典型的大曲坤沙酒，不仅拥有上乘的口感，入口柔滑。还拥有持久留香，回味悠长的典型特征。酒体晶莹剔透，微黄。令人陶醉。开瓶即可感受到香气扑鼻，入口满嘴生香。回味优雅细腻，实属令人赞叹！","txt":"茅台酒作为典型的大曲坤沙酒，不仅拥有上乘的口感，入口柔滑。还拥有持久留香，回味悠长的典型特征。酒体晶莹剔透，微黄。令人陶醉。开瓶即可感受到香气扑鼻，入口满嘴生香。回味优雅细腻，实属令人赞叹！","is_feature":false,"pid_name":null,"pid_spec":null,"avatar":"https://cdn.cnbj1.fds.api.mi-img.com/user-avatar/p01W31n5BB9U/dkwCUjWxo4HClR.jpg","nick_name":"武*"}]},"operation":{"tt":null,"wzl":{"topImgRadio":"1.0","location":"1.0","url":"","maskUrl":"","href":"https://m.xiaomiyoupin.com/mr/5fa529d1c9e77c000148d30f","staticWords":"","hyperlinkWords":"茅台预约抢购火热进行中，速戳参与","shareText":"","shareUrl":"","gray":"0"},"hdBanner":null,"ggBanner":null,"yd":null,"lbq":null},"isFavorite":false},"traceId":"b4265c3190a24742dc3da2d2311dbc3e","cacheTime":0}




/*****获取预约茅台界面请求地址（不用登录）*****/
//request:
GET https://m.xiaomiyoupin.com/mr/5fa529d1c9e77c000148d30f?spmref=YouPin_A.$Detail$_135927.text_url.0.36913700 HTTP/1.1
Host: m.xiaomiyoupin.com
Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Dalvik/2.1.0 (Linux; U; Android 5.1.1; WLZ-AN00 Build/LMY49I)Mobile MIOTWeex/2.0.2 (YouPin;4.10.0;41D70D966E115AB4B99EB4BD9320E0CD;0.20.1;A;A54FF940741271417BCC377D91887868D6E932B8;Wandoujia;NFAfERt6rN5PrPVL;) MIOTStore/20191212 (YouPin;4.10.0;41D70D966E115AB4B99EB4BD9320E0CD;20210508204259;A;A54FF940741271417BCC377D91887868D6E932B8;Wandoujia;NFAfERt6rN5PrPVL;) XiaoMi/HybridView/
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/;q=0.8
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,en-US;q=0.8
Cookie: cUserId=giFmEITsAjTrWSiOKVfW5HoIuSk; serviceToken=N21aTeS9T5YpiQX+45U7WzezS0JCuEuDdZZOe3CRT3A2aaL+UUNCxVri5Z56VNSNtHhNqqU+OkPc/jRfQrvUdPvBbeKXFUX05oC6wm3X8Q3AQCYdxtO0mN4EXJS8auf6/TtTozJgBfkINj2AdTtG6g== //该请求可以不用带cookie
X-Requested-With: com.xiaomi.youpin

//response
HTTP/1.1 302
Server: nginx
Date: Wed, 12 May 2021 05:03:48 GMT
Content-Length: 0
Connection: keep-alive
Location: https://m.xiaomiyoupin.com/app/shop/ugg/subscribeBuy.html?actId=6094c8b3c9e77c00015da351&spmref=YouPin_A.$Detail$_135927.text_url.0.36913700
Content-Language: zh-CN


/*****请求预约网页（不用登录）*****/
//request:
GET https://m.xiaomiyoupin.com/app/shop/ugg/subscribeBuy.html?actId=6094c8b3c9e77c00015da351&spmref=YouPin_A.$Detail$_135927.text_url.0.36913700 HTTP/1.1
Host: m.xiaomiyoupin.com
Connection: keep-alive
Upgrade-Insecure-Requests: 1
User-Agent: Dalvik/2.1.0 (Linux; U; Android 5.1.1; WLZ-AN00 Build/LMY49I)Mobile MIOTWeex/2.0.2 (YouPin;4.10.0;41D70D966E115AB4B99EB4BD9320E0CD;0.20.1;A;A54FF940741271417BCC377D91887868D6E932B8;Wandoujia;NFAfERt6rN5PrPVL;) MIOTStore/20191212 (YouPin;4.10.0;41D70D966E115AB4B99EB4BD9320E0CD;20210508204259;A;A54FF940741271417BCC377D91887868D6E932B8;Wandoujia;NFAfERt6rN5PrPVL;) XiaoMi/HybridView/
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/;q=0.8
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,en-US;q=0.8
Cookie: cUserId=giFmEITsAjTrWSiOKVfW5HoIuSk; serviceToken=N21aTeS9T5YpiQX+45U7WzezS0JCuEuDdZZOe3CRT3A2aaL+UUNCxVri5Z56VNSNtHhNqqU+OkPc/jRfQrvUdPvBbeKXFUX05oC6wm3X8Q3AQCYdxtO0mN4EXJS8auf6/TtTozJgBfkINj2AdTtG6g== //该请求可以不用带cookie
X-Requested-With: com.xiaomi.youpin

//response:
HTTP/1.1 200 OK
Server: nginx
Date: Wed, 12 May 2021 05:03:48 GMT
Content-Type: text/html
Last-Modified: Tue, 11 May 2021 09:17:24 GMT
Connection: keep-alive
Vary: Accept-Encoding
ETag: W/"609a4ba4-9df"
Content-Length: 2527

<!DOCTYPE html><html lang=zh-cmn-Hans><head><meta charset=UTF-8><meta name=screen-orientation content=portrait><meta name=x5-orientation content=portrait><meta name=viewport content="width=device-width,initial-scale=1,maximum-scale=1,minimum-scale=1,user-scalable=no,shrink-to-fit=no"><title>小米有品</title><script src=//fe.res.youpin.mi-img.com/log_sdk/youpin-bridge-iife.js></script><style>html,body{
      height: 100%;
    }</style><script>window.lib10Config = { fastclick: false };
    (function () {
      var
        docEl = document.documentElement,
        // scale = 1 / window.devicePixelRatio,
        recalc = function () {
          var uiWidth = 1080;
          var clientWidth = docEl.clientWidth;
          if (clientWidth > 800) clientWidth = 800;
          docEl.style.fontSize = 100 * (clientWidth / uiWidth) + 'px';

          console.log(clientWidth, '<===clientWidth');
        };
      // document.querySelector('meta[name="viewport"]').setAttribute('content', 'width=device-width, initial-scale=' + scale + ', maximum-scale=' + scale + ', minimum-scale=' + scale + ', user-scalable = no, shrink-to-fit=no');

      if (!document.addEventListener) return;
      window.addEventListener('resize', function () { setTimeout(recalc, 300) }, false);
      document.addEventListener('DOMContentLoaded', function () {
        recalc()
        setTimeout(function (){
          // 修复安卓客户端获取clientWidth无效的问题
          recalc()
        }, 333)
      }, false);
    })();</script><link rel="shortcut icon" href=//m.xiaomiyoupin.com/favicon.ico type=image/x-icon><link rel=stylesheet href=//fe.res.youpin.mi-img.com/lib10/youpin-lib10.min.css><script src="//fe.res.youpin.mi-img.com/lib10/youpin-lib10.min.js?update=66"></script><link href=css/chunk-vendors.c412edf5.css rel=preload as=style><link href=css/subscribeBuy.9029bdc6.css rel=preload as=style><link href=js/chunk-common.521dbf39.js rel=preload as=script><link href=js/chunk-vendors.0f30157a.js rel=preload as=script><link href=js/subscribeBuy.5616b460.js rel=preload as=script><link href=css/chunk-vendors.c412edf5.css rel=stylesheet><link href=css/subscribeBuy.9029bdc6.css rel=stylesheet></head><body><noscript><strong>We're sorry but test doesn't work properly without JavaScript enabled. Please enable it to continue.</strong></noscript><div id=app></div><script src=js/chunk-vendors.0f30157a.js></script><script src=js/chunk-common.521dbf39.js></script><script src=js/subscribeBuy.5616b460.js></script></body></html>


/*****预约请求（需登录）*****/
//request:
POST https://m.xiaomiyoupin.com/mtop/act/orderspike/order?_=1620919234469 HTTP/1.1
Host: m.xiaomiyoupin.com
Connection: keep-alive
Content-Length: 50
Origin: https://m.xiaomiyoupin.com
User-Agent: Dalvik/2.1.0 (Linux; U; Android 5.1.1; WLZ-AN00 Build/LMY49I)Mobile MIOTWeex/2.0.2 (YouPin;4.10.0;41D70D966E115AB4B99EB4BD9320E0CD;0.20.1;A;A54FF940741271417BCC377D91887868D6E932B8;Wandoujia;NFAfERt6rN5PrPVL;) MIOTStore/20191212 (YouPin;4.10.0;41D70D966E115AB4B99EB4BD9320E0CD;20210508204259;A;A54FF940741271417BCC377D91887868D6E932B8;Wandoujia;NFAfERt6rN5PrPVL;) XiaoMi/HybridView/
Content-Type: application/json
yp-srs: 285949334       //从js页面生成，似乎不需要也能预约成功
Accept: application/json
yp-srt: 1620968085453   //从js页面生成，似乎不需要也能预约成功
X-Requested-With: XMLHttpRequest
yp-ss: 6C450C876BC92319D0F977E549A646F2   //从js页面生成，似乎不需要也能预约成功
Referer: https://m.xiaomiyoupin.com/app/shop/ugg/subscribeBuy.html?actId=609cfb75c9e77c00018a45d0&spmref=YouPin_A.%24Detail%24_135927.text_url.0.54986391
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,en-US;q=0.8
Cookie: cUserId=ZeiMM6l_IW-z_hnC02EJwAfjmVk;  //用户账户ID
        serviceToken=sx7yhS+2xsORXY2tLgLz31o2TrVHj04E17C39/ywQUM6eedB1jp2vYvKCOdGK0E4c1S7zNMUSg7Au6Nw9GRLUMtYQm/WsQSMQ9ENpgDDr08JIYEKmzsnwufGvNtDFWjwnErGBhekbPqz18yWwlKmVg==;   //token，有效期一天
        youpindistinct_id=1794a825c61-026881c7c15381-6570; //有品识别码，目前不清楚是干什么的，好像和账号耶没有关系，和时间和商品有关
        mjclient=YouPin; 
        youpin_sessionid=179665089f2-0f60be05d21c1f-656f 

[{},{"actId":"609cfb75c9e77c00018a45d0","tel":""}] //actId:由服务器生成，和请求的商品和时间有关，和账号无关

//response:
{
    "msg": "ok",
    "code": 0,
    "data": {
        "award": {
            "awardStartTime": 1619681014,
            "couponDiscountPrice": 0,
            "awardEndTime": 1669796861,
            "awardName": "新人首单29元减10元券",
            "couponValue": 1000,
            "awardDesc": "不包含新人专享，有品秒杀，限量抢和其他特殊商品",
            "couponBottomPrice": 2900,
            "couponDiscountType": 2,
            "couponDiscountValue": 0,
            "awardType": 1
        },
        "newUser": true,
        "orderCount": 6709
    },
    "success": true
}






/*****抢购接口(15002326234-20210516:15:20~)*****/
//request:
POST https://m.xiaomiyoupin.com/mtop/act/orderspike/spike?_=1621233331813 HTTP/1.1
Host: m.xiaomiyoupin.com
Connection: keep-alive
Content-Length: 76
Origin: https://m.xiaomiyoupin.com
User-Agent: Dalvik/2.1.0 (Linux; U; Android 5.1.1; TAS-AN00 Build/LMY49I)Mobile MIOTWeex/2.0.2 (YouPin;4.10.0;B5B9D9546FC5E63619405DE0E8B0AED9;0.20.1;A;29AFD1C2C9B4B3C7C8143CE95603DA2A81404719;Wandoujia;XnVIcL7JRbqXvHwF;) MIOTStore/20191212 (YouPin;4.10.0;B5B9D9546FC5E63619405DE0E8B0AED9;20210513203541;A;29AFD1C2C9B4B3C7C8143CE95603DA2A81404719;Wandoujia;XnVIcL7JRbqXvHwF;) XiaoMi/HybridView/
Content-Type: application/json
yp-srs: 247515552
Accept: application/json
yp-srt: 1621149204518
d: 63
X-Requested-With: XMLHttpRequest
yp-ss: 707DAD05AE9579DB92C3E3FFE357FF37
c: 0
Referer: https://m.xiaomiyoupin.com/app/shop/ugg/subscribeBuy.html?actId=609cfb75c9e77c00018a45d0&spmref=YouPin_A.%24Detail%24_135927.text_url.0.67953720
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,en-US;q=0.8
Cookie: cUserId=giFmEITsAjTrWSiOKVfW5HoIuSk; serviceToken=ffa3jRIR1uuAu0yd/oGlKwUTWi5e/O+2YuiMca7D0K4bXc7Q8xA3+8BLeiiDlUsXMBsarQ2/MhH9Vf/kU0xPWygFEKqejadHxkfAY8lHGGhqHxoh62Na+VkGP4uceFQdhJoKSJLJYodygaEnl7i8Xw==; youpindistinct_id=1795beacd71-0c2ad86ced3b82-90d1; mjclient=YouPin; youpin_sessionid=179790965b0-0b0a4d1d5ee787-6677

[{},{"actId":"609cfb75c9e77c00018a45d0","token":"609cfb75c9e77c00018a45d0"}]



//response:
HTTP/1.1 200 OK
Server: nginx
Date: Sun, 16 May 2021 07:13:25 GMT
Content-Type: application/json; charset=utf-8
Content-Length: 61
Connection: keep-alive
Access-Control-Allow-Origin: https://m.xiaomiyoupin.com
Access-Control-Allow-Credentials: true
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,token

{"msg":"ok","code":0,"success":true,"data":{"success":false}}



/*****抢购接口(19160384323-20210516 15:27)*****/
//request:

                  //yp-srs:871993980 //随机数
                  //yp-srt:1621167898797  //服务器时间
                  //yp-ss:"F89DE81F213CC78AE01FABB3CD61EA56" //计算的hash
                  //url参数 _=1621234102952 //时间戳，毫秒为单位
POST https://m.xiaomiyoupin.com/mtop/act/orderspike/spike?_=1621234102952 HTTP/1.1
Host: m.xiaomiyoupin.com
Connection: keep-alive
Content-Length: 76
Origin: https://m.xiaomiyoupin.com
User-Agent: Dalvik/2.1.0 (Linux; U; Android 5.1.1; TAS-AN00 Build/LMY49I)Mobile MIOTWeex/2.0.2 (YouPin;4.10.0;B5B9D9546FC5E63619405DE0E8B0AED9;0.20.1;A;29AFD1C2C9B4B3C7C8143CE95603DA2A81404719;Wandoujia;XnVIcL7JRbqXvHwF;) MIOTStore/20191212 (YouPin;4.10.0;B5B9D9546FC5E63619405DE0E8B0AED9;20210513203541;A;29AFD1C2C9B4B3C7C8143CE95603DA2A81404719;Wandoujia;XnVIcL7JRbqXvHwF;) XiaoMi/HybridView/
Content-Type: application/json
yp-srs: 210755960
Accept: application/json
yp-srt: 1621149975951
X-DevTools-Emulate-Network-Conditions-Client-Id: 259d54f5-c88c-4e09-b21e-610ff671e28b
d: 37
X-Requested-With: XMLHttpRequest
yp-ss: A22ACA56B2AC2E8E324C5E626851E477
c: 0
Referer: https://m.xiaomiyoupin.com/app/shop/ugg/subscribeBuy.html?actId=609cfb75c9e77c00018a45d0&spmref=YouPin_A.%24Detail%24_135927.text_url.0.76651979
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,en-US;q=0.8
Cookie: cUserId=ZeiMM6l_IW-z_hnC02EJwAfjmVk; serviceToken=3qy58DMpEG7ZoIk4eaL86jeU29lH0F6r/qyhy1qSVGbuvmLC/Npp5aHKVfVBD5hudQMdzgZHMt5u+KBrYlkPrYo2gomSBUXNfjHc7GIHmX72tHfhj+CdQAFB++IC5YVZVkYnzZsE4DsFDP+UT7P40Q==; youpindistinct_id=1795beacd71-0c2ad86ced3b82-90d1; mjclient=YouPin; youpin_sessionid=1797914235c-0cf1a9b6818c1e-6677

[{},{"actId":"609cfb75c9e77c00018a45d0","token":"609cfb75c9e77c00018a45d0"}]

//response:
HTTP/1.1 200 OK
Server: nginx
Date: Sun, 16 May 2021 07:26:16 GMT
Content-Type: application/json; charset=utf-8
Content-Length: 61
Connection: keep-alive
Access-Control-Allow-Origin: https://m.xiaomiyoupin.com
Access-Control-Allow-Credentials: true
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,token

{"msg":"ok","code":0,"success":true,"data":{"success":false}}



