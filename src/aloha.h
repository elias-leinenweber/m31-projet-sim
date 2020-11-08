#ifndef ALOHA_H
#define ALOHA_H

#define P	0.01
#define K	4
#define SLOTS	250

struct result {
	uint32_t	useful_slots;	/* le nombre de slots utiles */
	uint32_t	queued_msgs;	/* le nombre de messages en attente */
};

struct result	slotted_aloha(double, uint32_t, uint32_t, uint32_t);

#endif
