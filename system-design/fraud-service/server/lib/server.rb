require 'grpc'
require_relative '../proto/generated/transaction_services_pb'

class FraudServiceImpl < FraudService::FraudService::Service
  def is_transaction_valid(request, _call)
    puts "Received a request. transactionId: #{request.transactionId}, cbk: #{request.hasCbk}"
    response = FraudService::IsTransactionValidResponse.new
    response.transactionId = request.transactionId
    response.isValid = is_request_valid(request)
    puts "Sending response. transactionId: #{response.transactionId}, isValid: #{response.isValid}"
    return response
  end

  def is_request_valid(request)
    if request.hasCbk == true
      return false
    end
    # Additional steps or logic can go here
    return true
  end
end
