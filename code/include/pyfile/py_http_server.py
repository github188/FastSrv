from http.server import BaseHTTPRequestHandler , HTTPServer
import urllib.parse

class HttpImplement(BaseHTTPRequestHandler):
	def do_GET(self):
		self.index = open("html/index.html",'r',encoding="utf-8")
		self.output = self.index.read()
		self.index.close()

		self.send_response(200)
		self.send_header('content-type','text/html;charset=utf-8')
		self.end_headers()
		self.wfile.write(self.output.encode(encoding="utf-8"))

	def do_POST(self):
		self.len = int(self.headers['content-length'])
		self.input = self.rfile.read(self.len)
		self.origin = self.input.decode("utf-8")
		print("origin string is : " + self.origin)

		self.msg = {}

		for self.valist in self.origin.split('&'):
			self.args = self.valist.split('=')
			self.msg[self.args[0]] = urllib.parse.unquote(self.args[1])

		for self.key in self.msg:
			print("key = %s , value = %s" % (self.key,self.msg[self.key]))

		self.index = open("html/result.html",'r',encoding="utf-8")
		self.output = self.index.read()
		self.index.close()

		self.send_response(200)
		self.send_header('content-type','text/html;charset=utf-8')
		self.end_headers()

		#return
		self.result = self.output.replace('$TITLE',self.msg['title']).replace('$MESSAGE',self.msg['message']).replace('$RESULT','ok')
		self.wfile.write(self.result.encode(encoding="utf-8"))

if __name__ == '__main__':
	try:
		PORT = 8000
		server = HTTPServer(('',PORT),HttpImplement)
		print("serving at port",PORT)
		server.serve_forever()
	except:
		print("HTTPServer error")