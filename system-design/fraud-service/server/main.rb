require_relative 'lib/server'

puts 'Initializing gRPC server...'
$stdout.flush
server = GRPC::RpcServer.new
puts 'Running the server...'
$stdout.flush
server.add_http2_port('localhost:50051', :this_port_is_insecure)
server.handle(FraudServiceImpl.new)
server.run_till_terminated
puts 'Server is running.'
