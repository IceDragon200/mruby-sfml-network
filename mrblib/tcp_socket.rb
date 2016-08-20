module SFML
  class TcpSocket
    # (see #send_data)
    alias :send :send_data
  end
end
