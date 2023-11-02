# Protocol Buffers

`FraudService` contains:

- `rpc` called `IsTransactionValid` defined at [transaction.proto](./transaction.proto).

## Install

```
brew install protobuf
gem install grpc --user-install
gem install grpc-tools --user-install
```

## Generate

### Python

```

```

### Ruby

```
grpc_tools_ruby_protoc -I proto --ruby_out=proto/generated/ruby --grpc_out=proto/generated/ruby proto/transaction.proto
```
