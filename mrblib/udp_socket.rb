module SFML
  class UdpSocket
    def send(object)
      if object.is_a?(SFML::Packet)
        send_packet object
      else
        send_data object
      end
    end

    def receive(object)
      if object.is_a?(SFML::Packet)
        receive_packet object
      else
        receive_data object
      end
    end
  end
end
