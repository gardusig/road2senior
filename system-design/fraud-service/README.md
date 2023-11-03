# Fraud service

The goal of this project is to build a solution for [this](https://gist.github.com/cloudwalk-tests/76993838e65d7e0f988f40f1b1909c97) problem statement from CloudWalk interview process.

- [Client](#client)
- [Protocol Buffer](#protocol-buffer)
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

## Transaction rejection criteria

- Chargeback
  - Like retrieving the same received value amount
  - Rejects any transaction with parameter `hasCbk` with value `true`
- Rate limiter
  - Like too many requests from the same user
  - Accepts at most:
    - 1 per second
    - 5 per minute
    - 50 per hour
    - 100 per day
  - Which means, evaluate requests with same `userId` and reject potential frauds
- Maybe to evaluate relation between:
  - `cardNumber` and `transactionAmount` and `userId`
    - users don't have that many cards in general, guess less than 5 on average
    - any new card for an user, suspicious
    - unusual high amount for an user, suspicious
  - `transactionAmount` and `userId`
    - unusual high amount for an user, suspicious
  - `transactionAmount` and `transactionDate` and `userId`
    - unusual high value for an user at an odd day/time, suspicious
  - `deviceId` and `transactionAmount` and `userId`
    - users don't have that many devices in general, guess less than 10 on average
    - any amount from a new device, suspicious
    - unusual high amount from a device, suspicious
  - `merchantId` and `transactionAmount` and `userId`
    - unusual item for user, if high value and odd item, suspicious
