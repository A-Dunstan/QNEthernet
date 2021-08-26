// EthernetClient.h defines the TCP client interface.
// (c) 2021 Shawn Silverman

// C++ includes
#include <vector>

#include <Client.h>
#include <lwip/tcp.h>

namespace qindesign {
namespace network {

class EthernetClient final : public Client {
 public:
  EthernetClient();
  ~EthernetClient();

  int connect(IPAddress ip, uint16_t port) override;
  int connect(const char *host, uint16_t port) override;
  size_t write(uint8_t b) override;
  size_t write(const uint8_t *buf, size_t size) override;
  int available() override;
  int read() override;
  int read(uint8_t *buf, size_t size) override;
  int peek() override;
  void flush() override;
  void stop() override;
  uint8_t connected() override;
  operator bool() override;

 private:
  static void dnsFoundFunc(const char *name, const ip_addr_t *ipaddr,
                           void *callback_arg);
  static err_t connectedFunc(void *arg, struct tcp_pcb *tpcb, err_t err);
  static void errFunc(void *arg, err_t err);
  static err_t recvFunc(void *arg, struct tcp_pcb *tpcb, struct pbuf *p,
                        err_t err);

  // Check if there's data still available in the buffer.
  bool isAvailable();

  tcp_pcb *pcb_;
  bool connecting_;
  bool connected_;

  std::vector<unsigned char> inBuf_;
  int inBufPos_;
};

}  // namespace network
}  // namespace qindesign