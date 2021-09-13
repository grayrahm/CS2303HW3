/*
 * Room.h
 *
 *  Created on: Sep 9, 2021
 *      Author: CyberPower
 */

#ifndef ROOM_H_
#define ROOM_H_

#include <stdbool.h>

typedef struct
{
	int roomNumber;
	float treasure;
	bool searched;
}Room;

#endif /* ROOM_H_ */
