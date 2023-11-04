import sys
sys.path.append('/app/proto/generated')


from client import FraudServiceClient
from google.protobuf.timestamp_pb2 import Timestamp
from proto.generated import transaction_pb2
import datetime


def get_timestamp_from_str(timestamp: str) -> Timestamp:
    datetime_obj = datetime.datetime.fromisoformat(timestamp)
    timestamp_message = Timestamp()
    timestamp_message.FromDatetime(datetime_obj)
    return timestamp_message


def generate_request() -> transaction_pb2.IsTransactionValidRequest:
    return transaction_pb2.IsTransactionValidRequest(
        transactionId="21320398",
        merchantId="29744",
        userId="97051",
        cardNumber="434505******9116",
        transactionDate=get_timestamp_from_str('2019-12-01T23:16:32.812632'),
        transactionAmount=374.56,
        deviceId='285475',
        hasCbk=False,
    )


def main():
    client = FraudServiceClient("server", 50051)
    print('Created client')
    request = generate_request()
    response = client.is_transaction_valid(request)
    print(f"Is Transaction Valid: {response.isValid}")


if __name__ == "__main__":
    main()
