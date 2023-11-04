from proto.generated import transaction_pb2_grpc
import grpc


class FraudServiceClient:
    def __init__(self, host, port):
        self.channel = grpc.insecure_channel(f"{host}:{port}")
        self.stub = transaction_pb2_grpc.FraudServiceStub(self.channel)

    def is_transaction_valid(self, request):
        return self.stub.IsTransactionValid(request)
