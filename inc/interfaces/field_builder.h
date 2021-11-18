#ifndef FIELD_BUILDER_H
#define FIELD_BUILDER_H

#include "igameplay_manager.h"
#include "../field.h"

class FieldBuilder {
public:
	virtual void reset() =0;
	virtual void setup_cells() =0;
	virtual void spawn_items() =0;
	virtual void spawn_entities() =0;
	virtual Field&& get_result() =0;
	virtual ~FieldBuilder() =default;
};

#endif
