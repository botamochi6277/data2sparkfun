// httpモジュールを読み込み、インスタンスを生成
var dgram = require('dgram');
var moment = require('moment');
var fs = require('fs');

// HTTPサーバーのイベントハンドラを定義
var express = require('express');
var http = require('http');
var app = express();
var server = http.createServer(app);
app.get('/', function (req, res) {
		res.sendFile(__dirname + '/index.html');
});
server.listen(8888);
console.log("Please access to http://localhost:8888");
