require 'grpc'
require_relative '/app/generated/transaction_services_pb'

class FraudServiceImpl < FraudService::FraudService::Service
  def is_transaction_valid(request, _call)
    puts "Received a request for transaction ID: #{request.transactionId}"
    response = FraudService::IsTransactionValidResponse.new
    response.transactionId = request.transactionId
    response.isValid = true
    puts "Sending a response with transaction ID: #{response.transactionId}"
    response
  end
end
