require_relative 'lib/server'

def start_server(host, port)
    server = GRPC::RpcServer.new
    server.add_http2_port("#{host}:#{port}", :this_port_is_insecure)
    server.handle(FraudServiceImpl.new)
    puts "server listening at #{host}:#{port}"
    $stdout.flush
    server.run_till_terminated
end

start_server('0.0.0.0', 50051)
puts 'Server terminated'
$stdout.flush
