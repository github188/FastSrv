#! /usr/local/bin python3
import urllib.request
import json

def requestAmap(req):
	send = urllib.request.Request(req)
	try:
		receive = urllib.request.urlopen(send)
		origin = receive.read().decode("utf-8")
		receive.close()
		content = json.loads(origin)
		location = content["result"]["location"]
		print("py_http.py : " + location)
		L = location.split(',')
		T = (L[0], L[1])
		return T
	#网络不正常，则抛出错误给 C++ ，以便 C++ 重新处理
	except urllib.error.HTTPError as e:
		print(e.code)
		print(e.read().decode("utf8"))
		raise
	#如果是其它的问题（比如查询无结果），则返回全0
	except:
		return ("000000000000", "000000000000")

def requestAmapUseAddr(req):
	send = urllib.request.Request(req)
	try:
		receive = urllib.request.urlopen(send)
		origin = receive.read().decode("utf-8")
		receive.close()
		content = json.loads(origin)
		location = "".join(content["regeocode"]["addressComponent"]["province"])
		location = location[0:] + "".join(content["regeocode"]["addressComponent"]["city"])
		location = location[0:] + "".join(content["regeocode"]["addressComponent"]["district"])
		location = location[0:] + "".join(content["regeocode"]["addressComponent"]["streetNumber"]["street"])
		location = location[0:] + "".join(content["regeocode"]["addressComponent"]["streetNumber"]["number"])
		print("py_http.py : " + location)
		T = (location[0:],)
		return T
	#网络不正常，则抛出错误给 C++ ，以便 C++ 重新处理
	except urllib.error.HTTPError as e:
		print(e.code)
		print(e.read().decode("utf8"))
		raise
	#如果是其它的问题（比如查询无结果），则返回全0
	except:
		return ("0",)

# if __name__ == '__main__':
	# requestAmap("http://apilocate.amap.com/position?accesstype=0&imei=866104021101384&cdma=0&bts=460,0,6338,62755,-66&nearbts=460,0,6338,62755,-66|460,0,6338,62755,-66&output=json&key=fe0d26ade7f0dc72e2d2efa4d10fc259")
	# requestAmap("http://apilocate.amap.com/position?accesstype=0&imei=866104021101384&cdma=0&bts=460,0,25013,10,-83&output=json&key=fe0d26ade7f0dc72e2d2efa4d10fc259")
	# requestAmapUseAddr("http://restapi.amap.com/v3/geocode/regeo?location=116.355,39.9876&extensions=all&output=json&key=44e606a9c5a628e9a8bd42226249f84c")