from socketIO_client import SocketIO
import logging

#logging.basicConfig(level=logging.INFO)


def on_socket_connect_ack(args):
    # 连接到服务器，开始鉴权
    socketIO.emit('connect', {'appkey': '597d9a6dd3a02f2c5910926a', 'customid': 'smarthome'})


def on_connack(args):
    # appkey 鉴权成功，可以订阅/发布消息
    #socketIO.emit('subscribe', {'topic': 'testtopic2'})
    socketIO.emit('subscribe', {'topic': 'Hello', 'messageId':'11833652203486491112'})


def on_message(args):
    print('on_messagev', str(args))
    if(str(args).__contains__("Hello")):
        socketIO.emit('publish', {'topic': 'Hello', 'msg': 'hello, Yunba', 'qos': 1})


socketIO = SocketIO('sock.yunba.io', 3000)
socketIO.emit('connect', {'appkey': '597d9a6dd3a02f2c5910926a', 'customid': 'smarthome'})
socketIO.emit('subscribe', {'topic': 'Hello', 'messageId':'11833652203486491112'})
#socketIO.on('socketconnectack', on_socket_connect_ack)
#socketIO.on('connack', on_connack)
socketIO.on('message', on_message)

socketIO.wait()
