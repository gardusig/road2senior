import sys
sys.path.append('/app/proto/generated')

from client import FraudServiceClient
import request_creator


def main():
    client = FraudServiceClient("server", 50051)
    requests = request_creator.get_requests_from_file()
    valid_requests = 0
    invalid_requests = 0
    for request in requests:
        response = client.is_transaction_valid(request)
        if response.isValid:
            valid_requests += 1
        else:
            invalid_requests += 1
    print(f'  valid transactions: {valid_requests:10d}')
    print(f'invalid transactions: {invalid_requests:10d}')
    assert (valid_requests == 2808)
    assert (invalid_requests == 391)


if __name__ == "__main__":
    main()
