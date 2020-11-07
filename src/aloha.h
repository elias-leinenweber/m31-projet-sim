#ifndef ALOHA_H
#define ALOHA_H

#define SLOTS	100

struct result {
	uint32_t	useful_slots;	/* le nombre de slots utiles */
	uint32_t	queued_msgs;	/* le nombre de messages en attente */
};

struct result	slotted_aloha(float, uint32_t, uint32_t);

#endif
