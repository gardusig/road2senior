# Server

Accept requests to validate fraudulent transactions. Criteria for rejecting a transaction:

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

## Build

```
docker build -t fraud_server -f docker/server.Dockerfile . --progress=plain
```

## Run

```
docker run -p 50051:50051 fraud_server
```
