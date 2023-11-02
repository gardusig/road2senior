# Fraud service

The goal of this project is to build a solution for [this](https://gist.github.com/cloudwalk-tests/76993838e65d7e0f988f40f1b1909c97) problem statement from CloudWalk interview process.

- [Client](#client)
- [Protocol Buffer](#proto)
- [Server](#server)

## [Client](./client/)

`/client` folder contains Python code for instantiating clients capable of sending requests with transactions to be validated.

![PythonClient](./pictures/client.png)

## [Protocol Buffer](./proto/)

`/proto` folder contains Protocol Buffers (gRPC) defining the communication channel between clients and servers.

![CommunicationChannel](./pictures/grpc.png)

## [Server](./server/)

`/server` folder contains Ruby code for a server capable of receiving requests with transactions to be validated.

![RubyServer](./pictures/server.png)
