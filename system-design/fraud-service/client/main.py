if __name__ == "__main__":
    client = FraudServiceClient("localhost", 50051)

    request = transaction_pb2.IsTransactionValidRequest(
        transactionId="12345",
        merchantId="merchant123",
        userId="user123",
        cardNumber="1234-5678-9012-3456",
        # ... fill in other fields ...
    )

    response = client.is_transaction_valid(request)
    print(f"Is Transaction Valid: {response.isValid}")
