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
python3 -m grpc_tools.protoc -Iproto --python_out=proto/generated/python --grpc_python_out=proto/generated/python proto/transaction.proto
```

### Ruby

```
grpc_tools_ruby_protoc -I proto --ruby_out=proto/generated/ruby --grpc_out=proto/generated/ruby proto/transaction.proto
```

#### TODO

Currently it is required to update `transaction_service_pb.rb` import.

From:

```rb
require 'transaction_pb'
```

To:

```rb
require_relative 'transaction_pb'
```
