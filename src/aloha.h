#ifndef ALOHA_H
#define ALOHA_H

struct result {
	uint32_t	useful_slots;	/* le nombre de slots utiles */
	uint32_t	queued_msgs;	/* le nombre de messages en attente */
};

struct result	slotted_aloha(double, uint32_t, uint32_t, uint32_t, bool);

#endif
