# Protocol Buffers

`FraudService` contains:

- `rpc` called `IsTransactionValid` defined at [transaction.proto](./transaction.proto).

## Python (client)

### Install

```
brew install protobuf
python3 -m pip install grpcio
python3 -m pip install grpcio-tools
```

### Generate

```
python3 -m grpc_tools.protoc -Iproto --python_out=client/proto/generated --pyi_out=client/proto/generated --grpc_python_out=client/proto/generated proto/transaction.proto
```

## Ruby (server)

### Install

```
brew install protobuf
gem install grpc --user-install
gem install grpc-tools --user-install
```

### Generate

```
grpc_tools_ruby_protoc -I proto --ruby_out=server/proto/generated --grpc_out=server/proto/generated proto/transaction.proto
```

### TODO

Currently it is required to update `transaction_service_pb.rb` import.

From:

```rb
require 'transaction_pb'
```

To:

```rb
require_relative 'transaction_pb'
```
