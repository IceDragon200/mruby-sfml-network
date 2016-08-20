module SFML
  class Socket
    # @return [Boolean] true if the socket is blocking, false otherwise
    def is_blocking?
      blocking
    end
  end
end
