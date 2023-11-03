# Server

Accept requests to validate fraudulent transactions.

## Build

```
docker build -t fraud_server -f docker/server.Dockerfile . --progress=plain
```

## Run

```
docker run -p 50051:50051 fraud_server
```
