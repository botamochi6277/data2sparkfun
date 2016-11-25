# data2sparkfun
c++ program to push data to [https://www.sparkfun.com](data.sparkfun) or local [http://phant.io](phant) server

### Requirements
* boost::asio
* cmake

### compile c++ program
```
cmake.
make
```
### Directories
**to_public**: for Raspberry Pi to push data to data.sparkfun(public phant server).

**to_local**: for Raspberry Pi to push data to local phant server(localhost:8080)

**node** : online ploting program using node.js and GoogleChart.

Execute following code and access to [http://localhost:8888](localhost:8888)
```
node ./server.js
```
