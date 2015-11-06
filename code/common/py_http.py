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
	except urllib.error.HTTPError as e:
		print(e.code)
		print(e.read().decode("utf8"))
		return ("000000000000", "000000000000")

#if __name__ == '__main__':
#	requestAmap("http://apilocate.amap.com/position?accesstype=0&imei=866104021101384&cdma=0&bts=460,0,6338,62755,-66&nearbts=460,0,6338,62755,-66|460,0,6338,62755,-66&output=json&key=fe0d26ade7f0dc72e2d2efa4d10fc259")