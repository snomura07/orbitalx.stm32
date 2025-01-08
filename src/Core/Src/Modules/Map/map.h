#ifndef SRC_MODULES_MAP_H_
#define SRC_MODULES_MAP_H_

#include <main.h>
#include <UsartInterface/usart_interface.h>

class Map : public UsartInterface{
public:
	Map();
	~Map();
};

#endif
