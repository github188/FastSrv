#! /usr/local/bin python3
import urllib.request
import json

if __name__ == '__main__':
	send = urllib.request.Request('http://apilocate.amap.com/position?&accesstype=0&imei=1111&cdma=0&bts=460,01,40977,2205409,-65&output=json&key=fe0d26ade7f0dc72e2d2efa4d10fc259')
	try:
		receive = urllib.request.urlopen(send)
		origin = receive.read().decode("utf-8")
		receive.close()
		print(origin)
		content = json.loads(origin)
		location = content["result"]["location"]
		print(location)
	except urllib.error.HTTPError as e:
		print(e.code)
		print(e.read().decode("utf8"))