#ifndef ALOHA_H
#define ALOHA_H

#define SLOTS	100

struct result {
	uint32_t	useful_slots;
	uint32_t	queued_msgs;
};

struct result	slotted_aloha(float, uint32_t, uint32_t);

#endif
