#pragma once
#include "socket/ISocketMaker.h"


class MacSocketMaker : public ISocketMaker {
  int socket_fd = -1;

public:
  int createSocket() override;
  void deleteSocket() override;
};