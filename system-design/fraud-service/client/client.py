from proto.generated import transaction_pb2_grpc
from proto.generated import transaction_pb2
import grpc


class FraudServiceClient:
    def __init__(self, host: str, port: int):
        self.channel = grpc.insecure_channel(f"{host}:{port}")
        self.stub = transaction_pb2_grpc.FraudServiceStub(self.channel)

    def is_transaction_valid(self, request: transaction_pb2.IsTransactionValidRequest) -> transaction_pb2.IsTransactionValidResponse:
        return self.stub.IsTransactionValid(request)
